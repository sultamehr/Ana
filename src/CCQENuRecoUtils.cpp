#include "CCQENuRecoUtils.h" 

#include "GiGaCnv/IGiGaGeomCnvSvc.h"

//Tools - General and Analysis specific 
#include "MinervaUtils/IMinervaObjectAssociator.h" 
#include "RecInterfaces/IRecoObjectTimeTool.h" 
#include "GeoUtils/IMinervaCoordSysTool.h" 
#include "MinervaUtils/IMinervaMathTool.h"

#include "RecInterfaces/IAnchoredTrackFormation.h" 
#include "RecoStudies/IVertexEnergyStudyTool.h"
#include "BlobFormation/IIDAnchoredBlobCreator.h" 
#include "BlobFormation/IBlobCreatorUtils.h" 
#include "EnergyRecTools/ICalorimetryUtils.h" 
#include "RecUtils/Cone.h" 
#include "RecUtils/IConeUtilsTool.h" 
#include "ProngMaker/IProngClassificationTool.h"

#include "MinervaUtils/IHitTaggerTool.h"

#include "TruthMatcher/ITruthMatcher.h"
#include "AnaUtils/IMuonUtils.h"

#include "Event/DAQHeader.h"
#include "Event/PhysicsEvent.h" 
#include "Event/TimeSlice.h" 

//From GaudiException
#include "GaudiKernel/PhysicalConstants.h"

DECLARE_TOOL_FACTORY( CCQENuRecoUtils ); 


//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
CCQENuRecoUtils::CCQENuRecoUtils(const std::string& type, const std::string& name, const IInterface* parent ) : 
  MinervaHistoTool( type, name, parent ) {

  declareInterface<ICCQENuRecoUtils>(this);
 

  //! Tools and their Aliases 
  declareProperty( "MinervaObjAssocAlias",          m_minObjAssocAlias               = "MMDRecoUtilsMinObjAssociator" );
  declareProperty( "RecoObjTimeToolAlias",          m_recoObjTimeToolAlias           = "MMDRecoUtilsRecoObjTimeTool" ); 
  declareProperty( "MathToolAlias",                 m_mathToolAlias                  = "MMDRecoUtilsMathTool" );

  declareProperty( "VtxAnchorShortTrackerAlias",    m_vtxAnchorShortTrackerAlias     = "MMDRecoUtilsVtxAnchorShortTracker" ); 
  declareProperty( "VertexEnergyStudyToolAlias",    m_vtxEngStudyToolAlias           = "MMDRecoUtilsVtxEngStudyTool" ); 
  declareProperty( "VertexBlobCreatorToolAlias",    m_vtxBlobCreatorAlias            = "MMDRecoUtilsVtxBlobCreator" );
  declareProperty( "BlobCreatorUtilsAlias",         m_blobCreatorUtilsAlias          = "MMDRecoUtilsBlobCreatorUtils" );
  declareProperty( "CalorimetryUtilsAlias",         m_caloUtilsAlias                 = "MMDRecoUtilsCaloUtils" );
  declareProperty( "ConeUtilsToolAlias",            m_coneUtilsToolAlias             = "MMDRecoUtilsConeUtilsTool" );
  declareProperty( "ProngIntersectionToolAlias",    m_prongIntersectionToolAlias     = "MMDRecoUtilsProngIntersectionTool" ); 

  declareProperty( "HitTaggerToolAlias",            m_hitTaggerToolAlias             = "MMDRecoUtilsHitTaggerTool" );
  declareProperty( "MuonUtilsAlias",                m_muonUtilsAlias                 = "MMDRecoUtilsMuonUtils" ); 
  declareProperty( "TruthMatcherAlias",             m_truthMatcherAlias              = "MMDRecoUtilsTruthMatcher" ); 

  
  //! For making short tracks using VertexEnergyStudyTool 
  declareProperty( "MaxSearchDistance_VESTool",          m_maxSearchDistance_VESTool            = 400.0 * CLHEP::mm ); //mm  
  declareProperty( "MaxStartingDistance_VESTool",        m_maxStartingDistance_VESTool          = 400.0 * CLHEP::mm ); //mm  
  declareProperty( "MaxAllowedSearchGap_VESTool",        m_maxAllowedSearchGap_VESTool          = 1e6 * CLHEP::mm );   //mm

  //! Time Window parameters
  declareProperty( "LowerTimeWindow",m_lowerTimeWindow = -20 * CLHEP::ns );
  declareProperty( "UpperTimeWindow",m_upperTimeWindow =  35 * CLHEP::ns ); 

  //! Time Window parameters for track selections
  declareProperty( "LowerTimeWindow_tracks",m_lowerTimeWindow_Tracks = -5 * CLHEP::ns );
  declareProperty( "UpperTimeWindow_tracks",m_upperTimeWindow_Tracks = 10 * CLHEP::ns );

  //! Prong, Blob and Cluster Colors
  declareProperty( "ClustersInConeProtonProngColor",m_clustersInConeProtonProngColor = 0x660066 ); //dark purple 
  declareProperty( "MuonFuzzBlobsColor",          m_muonFuzzBlobsColor           = 0x003300 ); // dark green 
  declareProperty( "MuonIsolatedBlobsColor",      m_muonIsolatedBlobsColor       = 0x0000FF ); // pure blue 
  declareProperty( "MuonProngColor",              m_muonProngColor               = 0x00FF00 ); // pure green

  //! Cone length
  declareProperty("ConeLength",                   m_coneLength                = 300.0 * CLHEP::mm); //mm 

  //! Isolated/Fuzz EM Blob Parameters
  declareProperty( "MuonFuzzDistanceFromVertex",   m_muonFuzzDistanceFromVertex   = 300.0 * CLHEP::mm );
  declareProperty( "MuonFuzzRadius",               m_muonFuzzRadius               = 50.0  * CLHEP::mm );

}


//=============================================================================
// Initialize
//=============================================================================
StatusCode CCQENuRecoUtils::initialize() {
  
  debug() << "Entering CCQENuRecoUtils::initialize() now ....." << endmsg;

  StatusCode sc = this->MinervaHistoTool::initialize();
  if( sc.isFailure() ) { return Error( "Failed to initialize!", sc ); }   

  try {
    m_objectAssociator = tool<IMinervaObjectAssociator>("MinervaObjectAssociator", m_minObjAssocAlias);
  } catch( GaudiException& e ) {
    error() << "Could not obtain tool: " << m_minObjAssocAlias << endmsg;
    return StatusCode::FAILURE;
  }

  try{
    m_recoObjTimeTool = tool<IRecoObjectTimeTool>("RecoObjectTimeTool", m_recoObjTimeToolAlias);
  } catch(GaudiException& e){
    error()<<"Could not obtain tool: " << m_recoObjTimeToolAlias << endmsg;
    return StatusCode::FAILURE;
  }
  
  try {
    m_mathTool = tool<IMinervaMathTool>("MinervaMathTool", m_mathToolAlias);
  } catch( GaudiException& e ) {
    error() << "Could not obtain tool: " << m_mathToolAlias << endmsg;
    return StatusCode::FAILURE;
  }
  
  try {
    m_vtxAnchorShortTracker = tool<IAnchoredTrackFormation>("AnchoredShortTracker", m_vtxAnchorShortTrackerAlias);
  } catch(GaudiException& e) {
    error() << "Could not obtain tool: "<<m_vtxAnchorShortTrackerAlias<<endmsg;
    return StatusCode::FAILURE;
  }
  
  try{ 
    m_vertexEnergyStudyTool = tool<IVertexEnergyStudyTool>("VertexEnergyStudyTool", m_vtxEngStudyToolAlias); 
  } catch( GaudiException& e ) { 
    error() << "Could not obtain tool: " << m_vtxEngStudyToolAlias << endmsg; 
    return StatusCode::FAILURE; 
  }

  try { 
    m_blobCreatorUtils = tool<IBlobCreatorUtils>("BlobCreatorUtils", m_blobCreatorUtilsAlias); 
  } catch( GaudiException& e ){
    error() << "Could not obtain BlobCreatorUtils: " << m_blobCreatorUtilsAlias << endmsg;
    return StatusCode::FAILURE;
  }

  try {
    m_vtxBlobCreatorTool = tool<IIDAnchoredBlobCreator>("VertexBlobCreator", m_vtxBlobCreatorAlias); 
  } catch( GaudiException& e ){
    error() <<"Could not obtain tool: " << m_vtxBlobCreatorAlias <<endmsg;
    return StatusCode::FAILURE;
  }

  try { 
    m_caloUtils = tool<ICalorimetryUtils>("CalorimetryUtils", m_caloUtilsAlias);  
  } catch( GaudiException& e ) {    
    error() << "Could not obtain tool: " << m_caloUtilsAlias << endmsg;    
    return StatusCode::FAILURE;  
  }

  try {
    m_coneUtilsTool = tool<IConeUtilsTool>("ConeUtilsTool", m_coneUtilsToolAlias); 
  } catch( GaudiException& e ){
    error() << "Could not obtain ConeUtilsTool!" << endmsg;
    return StatusCode::FAILURE;
  }

  try {
    m_prongIntersectionTool = tool<IProngClassificationTool>( "ProngIntersectionTool", m_prongIntersectionToolAlias);
  } catch(GaudiException& e) {
    error() << "Could not obtain tool: "<<m_prongIntersectionToolAlias<<endmsg;
    return StatusCode::FAILURE;
  } 
  
  try {
    m_hitTaggerTool = tool<IHitTaggerTool>("HitTaggerTool", m_hitTaggerToolAlias);
  } catch( GaudiException& e ) {
    error() << "Could not obtain tool: " << m_hitTaggerToolAlias << endmsg;
    return StatusCode::FAILURE;
  }
  
  try { 
    m_muonUtils = tool<IMuonUtils>("MuonUtils", m_muonUtilsAlias);  
  } catch( GaudiException& e ) {    
    error() << "Could not obtain tool: " << m_muonUtilsAlias << endmsg;    
    return StatusCode::FAILURE;  
  }

  try { 
    m_truthMatcher = tool<ITruthMatcher>("TruthMatcher", m_truthMatcherAlias);  
  } catch( GaudiException& e ) {    
    error() << "Could not obtain tool: " << m_truthMatcherAlias << endmsg;    
    return StatusCode::FAILURE;  
  }

  debug() << "Exiting CCQENuRecoUtils::initialize() now ....." << endmsg;
  
  return sc; 
}


//=============================================================================
// Finalize
//=============================================================================
StatusCode CCQENuRecoUtils::finalize() 
{ 

  debug() << "Entering CCQENuRecoUtils::finalize() now ....." << endmsg; 
  StatusCode sc = this->MinervaHistoTool::finalize();
  if( sc.isFailure() ) { return Error( "Failed to finalize!", sc ); } 
  debug() << "Exiting CCQENuRecoUtils::finalize() now ....." << endmsg;       
  return sc;      
}       


//===============================================================================
// Select clusters within a [-20,35] ns of the muon track time summed over the 
// clusters of the Tracker and ECAL regions of the detector
//===============================================================================
Minerva::IDClusterVect CCQENuRecoUtils::getInTimeAnalyzableIDClusters( const Minerva::PhysicsEvent *event, SmartRef<Minerva::Prong> muonProng) const {

  debug() << "Entering CCQENuRecoUtils::getInTimeAnalyzableIDClusters() now ....." << endmsg; 

  Minerva::IDClusterVect  extraClusters = event->select<Minerva::IDCluster>("Unused","!LowActivity&!XTalkCandidate");

  double trackTime = m_recoObjTimeTool->trackVertexTime(muonProng->minervaTracks()[0]);
   //-- interaction vertex
  //SmartRef<Minerva::Vertex> vertex = event->interactionVertex();
  //double trackTime = vertex->getTime();
  
  Minerva::IDClusterVect analyzableIDClusters;
  //------------------------------------------------------------------------------------
  //! Do not use clusters outside [-20,35]ns time window (clusterTime - trackTime)
  //! Consider only IDCluster from Tracker, ECAL region
  //------------------------------------------------------------------------------------
  for( Minerva::IDClusterVect::iterator it=extraClusters.begin(); it!=extraClusters.end(); it++ ) {
    double time_diff = (*it)->time() - trackTime;
    if( ( time_diff > m_lowerTimeWindow && time_diff < m_upperTimeWindow ) &&
	( (*it)->subdet()==Minerva::IDCluster::Tracker || (*it)->subdet()==Minerva::IDCluster::ECAL ) ) {
        analyzableIDClusters.push_back( *it );
    }
  }

  debug() << "Exiting CCQENuRecoUtils::getInTimeAnalyzableIDClusters() with " << analyzableIDClusters.size() << " analyzable clusters" << endmsg;
  return analyzableIDClusters;

} // End of getInTimeAnalyzableIDClusters( ) 


//=================================================================================================
// Select clusters within a [-20,35] ns of the muon track time summed over the 
// clusters of the Tracker and ECAL regions of the detector. Remove muon and vtx region clusters
//=================================================================================================
Minerva::IDClusterVect CCQENuRecoUtils::getInTimeAnalyzableNonMuonNonVtxIDClusters( const Minerva::PhysicsEvent *event, SmartRef<Minerva::Prong> muonProng, double vtxRejectionRadius) const {

  debug() << "Entering CCQENuRecoUtils::getInTimeAnalyzabNonMuonNonVtxleIDClusters() now ....." << endmsg; 

  Minerva::IDClusterVect  extraClusters = event->select<Minerva::IDCluster>("All","!LowActivity&!XTalkCandidate");
  Minerva::IDClusterVect  muonClusters = muonProng->getAllIDClusters();

  double trackTime = m_recoObjTimeTool->trackVertexTime(muonProng->minervaTracks()[0]);
   //-- interaction vertex
  SmartRef<Minerva::Vertex> vertex = event->interactionVertex();
  const Gaudi::XYZPoint vtx_pos = vertex->position();
  
  Minerva::IDClusterVect analyzableIDClusters;
  //------------------------------------------------------------------------------------
  //! Do not use clusters outside [-20,35]ns time window (clusterTime - trackTime)
  //! Consider only IDCluster from Tracker, ECAL region
  //------------------------------------------------------------------------------------
  for( Minerva::IDClusterVect::iterator it=extraClusters.begin(); it!=extraClusters.end(); it++ ) {
    double time_diff = (*it)->time() - trackTime;
    double pos_diff = m_mathTool->twoDDistance((*it), vtx_pos);
    bool nonMuonCluster = true;
    for( Minerva::IDClusterVect::iterator muit = muonClusters.begin(); muit!=muonClusters.end();muit++){
      if((*muit)==(*it)){
	nonMuonCluster = false;
	break;
      }
    }
    if( ( time_diff > m_lowerTimeWindow && time_diff < m_upperTimeWindow ) &&                              //Time difference is >-20 and < 35
	( (*it)->subdet()==Minerva::IDCluster::Tracker || (*it)->subdet()==Minerva::IDCluster::ECAL ) &&   //Only look at track and ECal clusters, ignore HCal
	( pos_diff > vtxRejectionRadius) &&                                                                //vertex region to ignore
	( nonMuonCluster ) ){                                                                                // not a muon related cluster
      
      analyzableIDClusters.push_back( *it );
    }
  }

    debug() << "Exiting CCQENuRecoUtils::getInTimeAnalyzableNonMuonNonVtxIDClusters() with " << analyzableIDClusters.size() << " analyzable clusters from a set of " << extraClusters.size() << " clusters and " << muonClusters.size() << " muon clusters" << endmsg;
  return analyzableIDClusters;

} // End of getInTimeAnalyzableNonMuonNonVtxcdIDClusters( ) 

//=================================================================================================
// Select clusters within a [-20,35] ns of the muon track time summed over the 
// clusters of the Tracker and ECAL regions of the detector. Remove muon and vtx region clusters
//=================================================================================================
Minerva::IDClusterVect CCQENuRecoUtils::getInTimeAnalyzableNonMuonVtxIDClusters( const Minerva::PhysicsEvent *event, SmartRef<Minerva::Prong> muonProng, double vtxRejectionRadius) const {

  debug() << "Entering CCQENuRecoUtils::getInTimeAnalyzabNonMuonVtxleIDClusters() now ....." << endmsg; 

  Minerva::IDClusterVect  extraClusters = event->select<Minerva::IDCluster>("All","!LowActivity&!XTalkCandidate");
  Minerva::IDClusterVect  muonClusters = muonProng->getAllIDClusters();

  double trackTime = m_recoObjTimeTool->trackVertexTime(muonProng->minervaTracks()[0]);
   //-- interaction vertex
  SmartRef<Minerva::Vertex> vertex = event->interactionVertex();
  const Gaudi::XYZPoint vtx_pos = vertex->position();
  
  Minerva::IDClusterVect analyzableIDClusters;
  //------------------------------------------------------------------------------------
  //! Do not use clusters outside [-20,35]ns time window (clusterTime - trackTime)
  //! Consider only IDCluster from Tracker, ECAL region
  //------------------------------------------------------------------------------------
  for( Minerva::IDClusterVect::iterator it=extraClusters.begin(); it!=extraClusters.end(); it++ ) {
    double time_diff = (*it)->time() - trackTime;
    double pos_diff = m_mathTool->twoDDistance((*it), vtx_pos);
    bool nonMuonCluster = true;
    for( Minerva::IDClusterVect::iterator muit = muonClusters.begin(); muit!=muonClusters.end();muit++){
      if((*muit)==(*it)){
	nonMuonCluster = false;
	break;
      }
    }
    if( ( time_diff > m_lowerTimeWindow && time_diff < m_upperTimeWindow ) &&                              //Time difference is >-20 and < 35
	( (*it)->subdet()==Minerva::IDCluster::Tracker || (*it)->subdet()==Minerva::IDCluster::ECAL ) &&   //Only look at track and ECal clusters, ignore HCal
	( pos_diff < vtxRejectionRadius) &&                                                                //vertex region to use
	( nonMuonCluster ) ){                                                                                // not a muon related cluster
      
      analyzableIDClusters.push_back( *it );
    }
  }

    debug() << "Exiting CCQENuRecoUtils::getInTimeAnalyzableNonMuonVtxIDClusters() with " << analyzableIDClusters.size() << " analyzable clusters from a set of " << extraClusters.size() << " clusters and " << muonClusters.size() << " muon clusters" << endmsg;
  return analyzableIDClusters;

} // End of getInTimeAnalyzableNonMuonVtxcdIDClusters( ) 


//========================================================================================================
//Check if tracks associated with the vertex are within the valid time window
//========================================================================================================

bool CCQENuRecoUtils::vertexTracksInTime(SmartRef<Minerva::Vertex> vtx, double muonTime) const {
  bool allTracksInTime = true;
  SmartRefVector<Minerva::Track> allTracks = vtx->getTracks();
  //Loop over tracks and take time differences. Window was setup for track - muon time within defined window. 
  for(  SmartRefVector<Minerva::Track>::iterator itTrack = allTracks.begin(); itTrack != allTracks.end(); ++itTrack ){
    double track_time = m_recoObjTimeTool->trackVertexTime((*itTrack));
    double time_diff = track_time-muonTime;
    if(time_diff< m_lowerTimeWindow_Tracks || time_diff > m_upperTimeWindow_Tracks){
      allTracksInTime = false;
      break;
    }//end time diff if
  }//end loop over tracks
  return allTracksInTime;
}//end vertex tracks in time

//========================================================================================================
//get tracks and PID them if  within time window
//========================================================================================================
Minerva::ProngVect CCQENuRecoUtils::getInTimeTrackPID( Minerva::PhysicsEvent* event, double muonTime ) const{
  Minerva::ProngVect myprongs;
  SmartRef<Minerva::Vertex> vertex = event->interactionVertex();
  SmartRefVector<Minerva::Track> InteractionTracks = vertex->getTracks();
  SmartRefVector<Minerva::Prong> allProngs = event->select<Minerva::Prong>();

  for(  SmartRefVector<Minerva::Prong>::iterator itProng = allProngs.begin(); itProng != allProngs.end(); ++itProng){//loop over all prongs
    
    bool non_primary_prong = true;
    bool time_ok = true;
    
    SmartRefVector<Minerva::Track> allTracks = (*itProng)->minervaTracks();
    for(  SmartRefVector<Minerva::Track>::iterator itTrack = allTracks.begin(); itTrack != allTracks.end(); ++itTrack ){//loop over all track
      bool non_interaction_vertex_track = true;
      for(  SmartRefVector<Minerva::Track>::iterator itTrack_veto = InteractionTracks.begin(); itTrack_veto != InteractionTracks.end(); ++itTrack_veto ){
	if((*itTrack_veto)==(*itTrack)){
	  non_interaction_vertex_track = false;
	  break;
	}//end if pointer check
      }//end loop over interaction tracks.
      if(non_interaction_vertex_track){
	double track_time = m_recoObjTimeTool->trackVertexTime((*itTrack));
	double time_diff = track_time-muonTime;
	if(time_diff<m_lowerTimeWindow_Tracks || time_diff>m_upperTimeWindow_Tracks) time_ok=false;
      }
      else{
	non_primary_prong = false;
	break;//no sense in continuing to look at this prong
      }
    }//end loop of all tracks
    if(non_primary_prong && time_ok){
      myprongs.push_back((*itProng));
    }
  }//end loop over all prongs

  return myprongs;
}


//========================================================================================================
// runShortTrackers - This method runs both the short trackers, first at the interaction vertex 
// and then at each stopPoint vertex at the end of a track (long or short) in the hope of finding more 
// (may or may not be kinked) tracks 
//========================================================================================================
StatusCode CCQENuRecoUtils::runShortTrackers( Minerva::PhysicsEvent* physEvent, std::vector<Minerva::Track*> *deShortTrackVector, bool runVertexAnchoredShortTracker, bool runVertexEnergyStudyTool ) const { 

  debug() << "Entering CCQENuRecoUtils::runShortTrackers() now ..... " << endmsg; 
  StatusCode sc; 
  
  debug() << "The option for running the VertexAnchoredShortTracker is " << runVertexAnchoredShortTracker << endmsg; 
  debug() << "The option for running the VertexEnergyStudyTool is "      << runVertexEnergyStudyTool      << endmsg; 

  deShortTrackVector->clear(); 

  //-------------------------------------------------
  //! Make short tracks at the Interaction Vertex  
  //-------------------------------------------------
  sc = makeShortTracksAtInteractionVertex( physEvent, deShortTrackVector, runVertexAnchoredShortTracker, runVertexEnergyStudyTool ); 
  if( sc.isFailure() ) { 
    debug() << "Short trackers did not run successfully at the interaction vertex - please investigate failure mode !" << endmsg; 
    return sc; 
  }

  debug() << "Number of short tracks found at the interaction vertex " << deShortTrackVector->size() << endmsg; 

  //-------------------------------------------------
  //! Make short tracks at the kink Vertices  
  //-------------------------------------------------
  sc = makeShortTracksAtKinkVertex( physEvent, deShortTrackVector, runVertexAnchoredShortTracker, runVertexEnergyStudyTool ); 
  if( sc.isFailure() ) { 
    debug() << "Short trackers did not run successfully at the kinked vertices - please investigate failure mode !" << endmsg; 
    return sc; 
  }

  debug() << "Number of short tracks found at the kinked and interaction vertices " << deShortTrackVector->size() << endmsg; 

  // IS THERE MORE RECONSTRUCTION LEFT HERE ? I THINK WE'VE COVERED EVERYTHING, BUT MAKE THE FINAL INSPECTION 
 
  debug() << "Exiting CCQENuRecoUtils::runShortTrackers() now ..... " << endmsg;   
  return StatusCode::SUCCESS; 
  
} // End of runShortTrackers( ) 

 
//========================================================
// setTrackDirection  
//========================================================
void CCQENuRecoUtils::setTrackDirection( Minerva::Track* track, Minerva::Vertex* vertex ) const {

  debug() << "Entering CCQENuRecoUtils::setTrackDirection() now ..... " << endmsg;   

  int backward = 0, forward = 0;
  Minerva::Track::NodeContainer nodes = track->nodes();
  for(unsigned int node = 0; node < nodes.size(); node++) {
    if( nodes[node]->z() < vertex->position().z() )      backward++;
    else if( nodes[node]->z() > vertex->position().z() ) forward++;
  }
  if( backward > forward )      track->setDirection(Minerva::Track::Backward);
  else if( forward > backward ) track->setDirection(Minerva::Track::Forward);
  
  debug() << "Exiting CCQENuRecoUtils::setTrackDirection() now ..... " << endmsg;   

} // End of setTrackDirection( ) 


//========================================================
// makeShortTracksAtInteractionVertex    
//========================================================
StatusCode CCQENuRecoUtils::makeShortTracksAtInteractionVertex( Minerva::PhysicsEvent* physEvent, std::vector<Minerva::Track*> *deShortTrackVector, bool runVertexAnchoredShortTracker, bool runVertexEnergyStudyTool ) const { 

  debug() << "Entering CCQENuRecoUtils::makeShortTracksAtInteractionVertex() now ..... " << endmsg; 
  StatusCode sc; 

  debug() << "Size of vector that is passed back BEFORE running both trackers at interaction vertex " << deShortTrackVector->size() << endmsg; 

  //-------------------------------------------------------------------------------------
  //! Specify generation as 0 since you are making tracks at the interaction vertex 
  //-------------------------------------------------------------------------------------
  int generation = 0; 

  if( NULL == physEvent ) { 
    debug() << "Physics Event in CCQENuRecoUtils::makeShortTracksAtInteractionVertex() is a NULL pointer - no sense in proceeding !" << endmsg; 
    return StatusCode::FAILURE; 
  }

  //-----------------------------------------------------------
  //! Obtain the Interaction Vertex 
  //-----------------------------------------------------------
  SmartRef<Minerva::Vertex> intVertex; 
  if( physEvent->hasInteractionVertex() ) { 
    intVertex = (physEvent->interactionVertex()).target(); 
  } else { 
    debug() << "This Physics Event does not have an interaction Vertex !" << endmsg; 
    return StatusCode::SUCCESS; 
  }
  
  //-----------------------------------------------------------
  //! Preference for running short trackers 
  //-----------------------------------------------------------
  if( !runVertexAnchoredShortTracker & !runVertexEnergyStudyTool ) { 
    info() << "You have not specified a preference for running a short tracker, please indicate your preference if you would like to look for short Tracks at the interaction vertex ! " << endmsg; 
  } 
  
  //-------------------------------------------------------------------------------------------
  //! Making short tracks at the interaction vertex with the Vertex Anchored Short Tracker 
  //------------------------------------------------------------------------------------------- 
  if( runVertexAnchoredShortTracker ) { 

    debug() <<"Running the Vertex Anchored Short Tracker at the interaction vertex now ..... "<< endmsg; 
    std::vector<Minerva::Track*> shortTrackVector_VAST; 

    // sc = m_anchoredShortTracker->createAnchoredTracks( idClusterVector, intVertex, &shortTrackVector_VAST ); 

    sc = makeShortTracks_VASTracker( physEvent, intVertex, &shortTrackVector_VAST, generation ); 
    if( sc.isFailure() ) return sc; 
    
    info() << "Number of short tracks made by running VAST ONLY at the interaction vertex is " << shortTrackVector_VAST.size(); 
    if( haveNeutrinoMC() ) info() << " in " << truthData() << endmsg; 
    else info() << " and does not have truth data." << endmsg;

    for( std::vector<Minerva::Track*>::iterator itTrk = shortTrackVector_VAST.begin(); itTrk != shortTrackVector_VAST.end(); ++itTrk ) { 
      //----------------------------------------------------------------------
      //! Storing all short tracks in this vector, just for keeping count 
      //----------------------------------------------------------------------
      deShortTrackVector->push_back(*itTrk); 
    }
    shortTrackVector_VAST.clear(); 
  } //End of option runVertexAnchoredShortTracker 
  
  //-------------------------------------------------------------------------------------------
  //! Making short tracks at the interaction vertex with the Vertex Energy Study Tool 
  //-------------------------------------------------------------------------------------------
  if( runVertexEnergyStudyTool ) { 
    
    debug() << "Running the Vertex Energy Study Tool at the interaction vertex now ..... " << endmsg; 
    std::vector<Minerva::Track*> shortTrackVector_VEST; 
    
    sc = makeShortTracks_VESTool( physEvent, intVertex, &shortTrackVector_VEST, generation ); 
    if( sc.isFailure() ) return sc; 
    
    info() << "Number of short tracks made by running VEST ONLY at the interaction vertex is " << shortTrackVector_VEST.size();
    if( haveNeutrinoMC() ) info() << " in " << truthData() << endmsg; 
    else info() << " and does not have truth data." << endmsg;
  
    for( std::vector<Minerva::Track*>::iterator itTrk = shortTrackVector_VEST.begin(); itTrk != shortTrackVector_VEST.end(); ++itTrk ) { 
      //----------------------------------------------------------------------
      //! Storing all short tracks in this vector, just for keeping count 
      //----------------------------------------------------------------------
      deShortTrackVector->push_back(*itTrk); 
    }
    shortTrackVector_VEST.clear(); 
  } //End of option runVertexEnergyStudyTool  

  //--------------------------------------
  //! Check to see if TimeSlice present
  //-------------------------------------- 
  SmartRef<Minerva::TimeSlice> timeSlice; 
  try{ 
    timeSlice = getTimeSlice( intVertex ); 
  } catch( MinervaException &e ) { 
    warning() << "New tracks and prongs will not be associated with a TimeSlice because there seems to be no TimeSlice associated with a cluster !" << endmsg; 
  }
  
  //---------------------------------------------------------------
  //! Add the short tracks made (VAST/VEST ?) to Vertex objects 
  //! Question : Should all this be done HERE or inside each of the makeShortTracks_VEST/VAST() ????? 
  //--------------------------------------------------------------- 
  SmartRefVector<Minerva::Prong> shortTrackProngVector;
  for(std::vector<Minerva::Track*>::iterator itTrack = deShortTrackVector->begin(); itTrack != deShortTrackVector->end(); ++itTrack) { 
    
    //--------------------------------------------------------------------------------
    //! Promote these new short tracks at the Interaction Vertex to Primary Prongs
    //--------------------------------------------------------------------------------
    Minerva::Prong* shortTrackProng = new Minerva::Prong( "PrimaryShortTrackProng" );
    shortTrackProng->add(*itTrack);
    shortTrackProng->setSourceVertex(intVertex);
    addObject(physEvent, shortTrackProng);

    shortTrackProngVector.push_back( shortTrackProng );
      
    physEvent->promoteProngToPrimary( shortTrackProng );

  } // End of for loop over deShortTrackVector
  
  //------------------------------------------------------------
  //! Classify new prongs
  //------------------------------------------------------------
  m_prongIntersectionTool->classifyProng( shortTrackProngVector );
    
  debug() << "Size of vector that is passed back AFTER running both trackers at interaction vertex " << deShortTrackVector->size() << endmsg; 

  debug() << "Created " << deShortTrackVector->size() << " new short, primary tracks at the interaction Vertex !" << endmsg;  

  debug() << "Exiting CCQENuRecoUtils::makeShortTracksAtInteractionVertex() now ..... " << endmsg;   
  return StatusCode::SUCCESS; 

} // End of makeShortTracksAtInteractionVertex( )


//==========================================================================
// makeShortTracksAtKinkVertex 
//==========================================================================
StatusCode CCQENuRecoUtils::makeShortTracksAtKinkVertex( Minerva::PhysicsEvent* physEvent, std::vector<Minerva::Track*> *deShortTrackVector, bool runVertexAnchoredShortTracker, bool runVertexEnergyStudyTool ) const { 

  debug() << "Entering CCQENuRecoUtils::makeShortTracksAtKinkVertex() now ..... " << endmsg; 
  StatusCode sc; 

  debug() << "Size of vector that is passed back BEFORE running both trackers at kink vertex " << deShortTrackVector->size() << endmsg; 

  debug() << "There are " << physEvent->primaryProngs().size() << " primary prongs before running short trackers at the kink vertices !" << endmsg; 

  //-----------------------------------------------------------
  //! Preference for running short trackers 
  //-----------------------------------------------------------
  if( !runVertexAnchoredShortTracker & !runVertexEnergyStudyTool ) { 
    info() << "You have not specified a preference for running a short tracker, please indicate your preference if you would like to look for short Tracks at the end points of non-muon tracks ! " << endmsg; 
  }
  
  //-------------------------------------------------------------------------------------------
  //! Specify generation as 1 since you are making tracks at the kink vertices 
  //! So if it finds a track after kink vertex, it can proceed to the next end point vertex  
  //-------------------------------------------------------------------------------------------
  int generation = 1; 
  
  //-------------------------------------------------------------------------------------------
  //! Look at end points of Primary Prongs (LONG+SHORT tracks from the interaction vertex) 
  //! Create more short (secondary) tracks if kinks exist 
  //! Question : Are Primary Prongs always from interaction vertex ?  
  //-------------------------------------------------------------------------------------------
  ProngVect primaryProngVector = physEvent->primaryProngs(); 

  //-------------------------------------------------------------------------------------------
  //! Making short tracks at the kink vertices with the Vertex Anchored Short Tracker 
  //------------------------------------------------------------------------------------------- 
  if( runVertexAnchoredShortTracker ) { 

    debug() <<"Running the Vertex Anchored Short Tracker at the kink vertex now ..... "<< endmsg; 
    
    std::vector<Minerva::Track*> shortTrackVec_VAST; 
    for( ProngVect::iterator itProng = primaryProngVector.begin(); itProng != primaryProngVector.end(); ++itProng ) { 
      
      if( (*itProng)->minervaTracks().size() ==0 ) continue; 

      //-----------------------------------------------------
      //! No need to make tracks at endpoint of muon tracks
      //------------------------------------------------------
      if( (*itProng)->filtertaglist()->filterTagExists( "PrimaryMuon" ) ) continue; 
      
      SmartRef<Minerva::Track> refTrack = (*itProng)->minervaTracks().back(); 

      sc = makeShortTracks_VASTracker( physEvent, getEndPointVertex(physEvent, refTrack), &shortTrackVec_VAST, generation ); 
      if( sc.isFailure() ) return sc;  

      info() << "Number of short tracks made by running VAST ONLY at the kink vertex is " << shortTrackVec_VAST.size() << " "; 
      if( haveNeutrinoMC() ) info() << " in " << truthData() << endmsg; 
      else info() << " and does not have truth data." << endmsg;
      
      for( std::vector<Minerva::Track*>::iterator itSecTrk = shortTrackVec_VAST.begin(); itSecTrk != shortTrackVec_VAST.end(); ++itSecTrk ) { 
	(*itProng)->add(*itSecTrk); 

	//----------------------------------------------------------------------
	//! Storing all short tracks in this vector, just for keeping count 
	//----------------------------------------------------------------------
	deShortTrackVector->push_back(*itSecTrk); 
      }

    } //End of for loop over Primary Prongs 

    m_prongIntersectionTool->classifyProng( primaryProngVector ); 
    shortTrackVec_VAST.clear(); 

  } // End of option runVertexAnchoredShortTracker 

  //-------------------------------------------------------------------------------------------
  //! Making short tracks at the kink vertices with the Vertex Energy Study Tool  
  //------------------------------------------------------------------------------------------- 
  if( runVertexEnergyStudyTool ) { 

    debug() <<"Running the Vertex Energy Study Tool at the kink vertex now ..... "<< endmsg; 

    std::vector<Minerva::Track*> shortTrackVec_VEST; 
    for( ProngVect::iterator itProng = primaryProngVector.begin(); itProng != primaryProngVector.end(); ++itProng ) { 

      if( (*itProng)->minervaTracks().size() ==0 ) continue; 

      //-----------------------------------------------------
      //! No need to make tracks at endpoint of muon tracks
      //------------------------------------------------------
      if( (*itProng)->filtertaglist()->filterTagExists( "PrimaryMuon" ) ) continue; 

      SmartRef<Minerva::Track> refTrack = (*itProng)->minervaTracks().back(); 

      sc = makeShortTracks_VESTool( physEvent, getEndPointVertex(physEvent, refTrack), &shortTrackVec_VEST, generation ); 
      if( sc.isFailure() ) return sc; 

      info() << "Number of short tracks made by running VEST ONLY at the kink vertex is " << shortTrackVec_VEST.size() << " "; 
      if( haveNeutrinoMC() ) info() << " in " << truthData() << endmsg; 
      else info() << " and does not have truth data." << endmsg;
     
      for( std::vector<Minerva::Track*>::iterator itSecTrk = shortTrackVec_VEST.begin(); itSecTrk != shortTrackVec_VEST.end(); ++itSecTrk ) { 
	(*itProng)->add(*itSecTrk); 
	
	//----------------------------------------------------------------------
	//! Storing all short tracks in this vector, just for keeping count 
	//----------------------------------------------------------------------
	deShortTrackVector->push_back(*itSecTrk); 
      }
      
    } //End of for loop over Primary Prongs 

    m_prongIntersectionTool->classifyProng( primaryProngVector ); 
    shortTrackVec_VEST.clear(); 

  } // End of option runVertexEnergyStudyTool 

  debug() << "Size of vector that is passed back AFTER running both trackers at kink vertex " << deShortTrackVector->size() << endmsg; 

  // SHOULD WE REFIT THE PRIMARY VERTEX ???? IF YES, LOOK UP CCPIONINCUTILS FOR AN EXAMPLE   
  
  debug() << "There are " << physEvent->primaryProngs().size() << " primary prongs after running short trackers at the kink vertices !" << endmsg; 

  debug() << "Exiting CCQENuRecoUtils::makeShortTracksAtKinkVertex() now ..... " << endmsg; 
  return StatusCode::SUCCESS; 

} // End of makeShortTracksAtKinkVertex( ) 


//========================================================
// makeShortTracks_VASTracker  
//========================================================
StatusCode CCQENuRecoUtils::makeShortTracks_VASTracker( Minerva::PhysicsEvent* physEvent, SmartRef<Minerva::Vertex> deVertex, std::vector<Minerva::Track*> *trackVec, int generation ) const 
{ 

  debug() << "Entering CCQENuRecoUtils::makeShortTracks_VASTracker() now ....." << endmsg; 
  StatusCode sc; 
  
  debug() << "Size of trackVec while entering makeShortTracks_VASTracker " << trackVec->size() << endmsg; 

  if( !deVertex.target() ) { 
    debug() << "Vertex does not possess data - please investigate !" << endmsg; 
    return StatusCode::FAILURE; 
  }
  
  debug() << "Type of Vertex " << deVertex->type() << " Position " << deVertex->position() << endmsg; 
  
  debug() << "Number of out going tracks before running VASTracker " << deVertex->getNOutgoingTracks() << endmsg; 

  Minerva::IDClusterVect idClusterVector = physEvent->select<Minerva::IDCluster>("Unused", "!LowActivity&!XTalkCandidate"); 
  if( !idClusterVector.size() ) { 
    debug() << "Size of vector containing ID clusters is " << idClusterVector.size() << " - nothing to make short tracks from !" << endmsg; 
    return StatusCode::SUCCESS; 
  }

  SmartRef<Minerva::TimeSlice> timeSlice; 
  try{ 
    timeSlice = getTimeSlice( idClusterVector.front() ); 
  } catch( MinervaException &e ) { 
    warning() << "New tracks and prongs will not be associated with a TimeSlice ! Investigate if clusters have a TimeSlice !" << endmsg; 
  }

  //! Create a container for holding tracks made by the VASTracker 
  std::vector<Minerva::Track*> shortTrackVector; 
  sc = m_vtxAnchorShortTracker->createAnchoredTracks( idClusterVector, deVertex, &shortTrackVector ); 

  if( sc.isSuccess() && !shortTrackVector.empty() ) { 
    info() << "Size of shortTrackVector after running the VertexAnchoredShortTracker is " << shortTrackVector.size(); 
    if( haveNeutrinoMC() ) info() << " in " << truthData() << endmsg; 
    else info() << " and event does not have truth data." << endmsg; 

  } else { 
    info() << "VertexAnchoredShortTracker did not run successfully or the track container is empty - please investigate failure mode !" << endmsg; 
  }

  info() << "Created " << shortTrackVector.size() << " short tracks from VASTracker" << endmsg; 
  
  //----------------------------------------------------------------------------------
  //! Add the new track(s) to the physEvent, timeSlice and Vertex 
  //! Question: Does VertexAnchoredShortTracker already add its tracks to TES ?
  //----------------------------------------------------------------------------------
  for( std::vector<Minerva::Track*>::iterator itTrk = shortTrackVector.begin(); itTrk != shortTrackVector.end(); ++itTrk ) { 
    info() << "Track address " << (*itTrk) << " Track type " << (*itTrk)->type() << "Track chi2 " << (*itTrk)->chi2PerDoF() 
	   << " Track nodes " << (*itTrk)->nNodes() << " Track theta " << (*itTrk)->theta() << " Track phi " << (*itTrk)->phi() 
	   << " Track Visible Energy " << (*itTrk)->visibleEnergy() << " Track Time " << (*itTrk)->time() << endmsg;  
    
    SmartRef<Minerva::Track> refTrack(*itTrk); 
    (*itTrk)->setIntData( "createdTrack", 1 );
    setTrackDirection(*itTrk, deVertex);  
    deVertex->addOutgoingTrack(refTrack); 
    if( timeSlice.target() ) { 
      (*itTrk)->setTimeSlice( timeSlice->sliceNumber() ); 
      addObject( timeSlice, *itTrk ); 
    }
    addObject( physEvent, *itTrk ); 
    
    //-------------------------------------------------
    //! Create a stopPoint Vertex for the new track 
    //-------------------------------------------------
    Minerva::Vertex* stopPointVertex = new Minerva::Vertex();
    stopPointVertex->setIncomingTrack( refTrack );
    stopPointVertex->setPosition( (*itTrk)->lastState().position() );
    stopPointVertex->setTimeSlice( timeSlice->sliceNumber() );
    addObject(physEvent, stopPointVertex);
    
    debug() << "The new StopPoint vertex's position = " << stopPointVertex->position() << endmsg;   

    //---------------------------------------------------
    //! Filling up vector that carries back track info
    //---------------------------------------------------
    trackVec->push_back(*itTrk); 
    
  } // End of loop over shortTrackVector 
  
  info() << "Finished looping over shortTrackVector" << endmsg; 
  
  debug() << "Size of trackVec after running VASTracker " << trackVec->size() << endmsg; 
  
  //---------------------------------------------------------------------
  //! Follow the tracks to the next vertices (recursive tracking) 
  //! Put a switch on the generation here so that you start iterating 
  //! once you ALREADY have a short track at the intVertex  
  //---------------------------------------------------------------------
  SmartRefVector<Minerva::Track> outgoingTracksVector = deVertex->getOutgoingTracks(); 
  if( generation >0 ) { 
    for( SmartRefVector<Minerva::Track>::iterator itTrk = outgoingTracksVector.begin(); itTrk != outgoingTracksVector.end(); ++itTrk ) { 
      SmartRef<Minerva::Track> refTrack(*itTrk); 
      makeShortTracks_VASTracker( physEvent, getEndPointVertex(physEvent, refTrack), trackVec, generation+1 ); 
    }
  }
  
  debug() << "Number of out going tracks after running VASTracker " << deVertex->getNOutgoingTracks() << " Generation " << generation << endmsg;   
  debug() << "Exiting CCQENuRecoUtils::makeShortTracks_VASTracker() now ....." << endmsg; 
  return StatusCode::SUCCESS; 

} //End of makeShortTracks_VASTracker( )


//========================================================
// makeShortTracks_VESTool   
//========================================================
StatusCode CCQENuRecoUtils::makeShortTracks_VESTool( Minerva::PhysicsEvent* physEvent, SmartRef<Minerva::Vertex> deVertex, std::vector<Minerva::Track*> *trackVec, int generation ) const {

  debug() << "Entering CCQENuRecoUtils::makeShortTracks_VESTool() now ....." << endmsg; 
  StatusCode sc; 

  debug() << "Size of trackVec while entering makeShortTracks_VESTool " << trackVec->size() << endmsg; 
  
  if( !deVertex.target() ) { 
    debug() << "Vertex does not possess data - please investigate !" << endmsg; 
    return StatusCode::FAILURE; 
  }
  
  debug() << "Type of Vertex " << deVertex->type() << " Position " << deVertex->position() << endmsg; 
  
  debug() << "Number of out going tracks before running VESTool " << deVertex->getNOutgoingTracks() << endmsg; 

  //---------------------------------------------------------------------------
  //! Obtain a vector of ID clusters for the VertexEnergyStudyTool (VESTool)  
  //---------------------------------------------------------------------------
  Minerva::IDClusterVect idClusterVector = physEvent->select<Minerva::IDCluster>("Unused", "!LowActivity&!XTalkCandidate"); 
  if( !idClusterVector.size() ) { 
    debug() << "Size of vector containing ID clusters is " << idClusterVector.size() << " - nothing to make short tracks from !" << endmsg; 
    return StatusCode::SUCCESS; 
  }

  debug() << "Size of vector of unused clusters " << idClusterVector.size() << " . No LowActivity and XTalkCandidate clusters" << endmsg;
  
  //-------------------------------------------------
  //! TimeSlice for the clusters 
  //-------------------------------------------------
  SmartRef<Minerva::TimeSlice> timeSlice;

  //-------------------------------------------------------------------------
  //! Reference direction for the VertexEnergyStudyTool is the Z direction 
  //-------------------------------------------------------------------------
  Gaudi::XYZVector zDirectionVector(0, 0, 1); 
  
  //---------------------------------------------------------------
  //! Create a container for holding tracks made by the VESTool
  //---------------------------------------------------------------
  std::vector<Minerva::Track*> *deShortTrkVector = new std::vector<Minerva::Track*>; 
  
  //! Obtain clusters near the given Vertex 
  Gaudi::XYZPoint vertexPosition = deVertex->position(); 
  
  //! Create a container for holding only the clusters near the Vertex 
  Minerva::IDClusterVect clustersNearVtxVector; 

  sc = m_blobCreatorUtils->fillProximateClusterVec( vertexPosition, idClusterVector, clustersNearVtxVector, m_maxSearchDistance_VESTool, 
                                                    m_maxStartingDistance_VESTool, m_maxAllowedSearchGap_VESTool ); 
  
  if( sc.isSuccess() && !clustersNearVtxVector.empty() ) { 

    //--------------------------------------------------------
    //! Extract the Time Slice info here 
    //--------------------------------------------------------
    try {
      timeSlice = getTimeSlice( clustersNearVtxVector.front() );
    } catch( MinervaException &e ){
      warning() << "New tracks and prongs will not be associated with a TimeSlice ! Investigate if clusters have a TimeSlice !" << endmsg;
    }
    
    sc = m_vertexEnergyStudyTool->reconstructVertexActivity( physEvent, vertexPosition, zDirectionVector, clustersNearVtxVector, deShortTrkVector ); 
    
    if( sc.isSuccess() && !deShortTrkVector->empty() ) { 
      info() << "Size of deShortTrkVector after running the VertexEnergyStudyTool is " << deShortTrkVector->size() << " "; 
      if( haveNeutrinoMC() ) info() << " in " << truthData() << endmsg; 
      else info() << " and event does not have truth data." << endmsg; 
      
    } else { 
      info() << "VertexEnergyStudyTool did not run successfully or the track container is empty - please investigate failure mode !" << endmsg; 
    }
  } else { 
    info() << "fillProximateClusterVec() did not run successfully or cluster container is empty - please investigate failure mode !" << endmsg; 
  }
  
  info() << "Created " << deShortTrkVector->size() << " short tracks from VESTool" << endmsg; 

  //----------------------------------------------------------------
  //! Add the new track(s) to the physEvent, timeSlice and Vertex 
  //----------------------------------------------------------------
  for (std::vector<Minerva::Track*>::iterator itTrk =deShortTrkVector->begin(); itTrk != deShortTrkVector->end(); ++itTrk) {
    info() << "Track address " << (*itTrk) << " Track type " << (*itTrk)->type() << "Track chi2 " << (*itTrk)->chi2PerDoF() 
	   << " Track nodes " << (*itTrk)->nNodes() << " Track theta " << (*itTrk)->theta() << " Track phi " << (*itTrk)->phi() 
	   << " Track Visible Energy " << (*itTrk)->visibleEnergy() << " Track Time " << (*itTrk)->time() << endmsg;  

    //  (*itTrk)->setPatRecHistory( Minerva::Track::NotAssigned1 ); 
    
    SmartRef<Minerva::Track> refTrack(*itTrk); 
    (*itTrk)->setIntData( "createdTrack", 1 ); 
    setTrackDirection(*itTrk, deVertex);
    deVertex->addOutgoingTrack(refTrack);
    if( timeSlice.target() ) { 
      (*itTrk)->setTimeSlice( timeSlice->sliceNumber() ); 
      addObject( timeSlice, *itTrk );
    }
    addObject( physEvent, *itTrk );
    
    //-------------------------------------------------
    //! Create a stopPoint Vertex for the new track 
    //-------------------------------------------------
    Minerva::Vertex* stopPointVertex = new Minerva::Vertex();
    stopPointVertex->setIncomingTrack( refTrack );
    stopPointVertex->setPosition( (*itTrk)->lastState().position() );
    stopPointVertex->setTimeSlice( timeSlice->sliceNumber() );
    addObject(physEvent, stopPointVertex);
    
    debug() << "The new StopPoint vertex's position = " << stopPointVertex->position() << endmsg;   
    
    //---------------------------------------------------
    //! Filling up vector that carries back track info
    //---------------------------------------------------
    trackVec->push_back(*itTrk); 

  } // End of loop over deShortTrkVector   

  info() << "Finished looping over deShortTrkVector" << endmsg; 
  
  //--------------------------------------------------------------------
  //! Delete the new vector you had created 
  //! Do you need to delete the track pointers (commented out line) ? 
  //--------------------------------------------------------------------
  // for (std::vector<Minerva::Track*>::iterator itTrk =deShortTrkVector->begin(); itTrk != deShortTrkVector->end(); ++itTrk) { delete *itTrk; }
  deShortTrkVector->clear(); 
  delete deShortTrkVector; 

  debug() << "Size of trackVec after running VESTool " << trackVec->size() << endmsg; 
  
  //---------------------------------------------------------------------
  //! Follow the tracks to the next vertices (recursive tracking) 
  //! Put a switch on the generation here so that you start iterating 
  //! once you ALREADY have a short track at the intVertex  
  //---------------------------------------------------------------------
  SmartRefVector<Minerva::Track> outgoingTracksVector = deVertex->getOutgoingTracks(); 
  if( generation >0 ) { 
    for (SmartRefVector<Minerva::Track>::iterator itTrack = outgoingTracksVector.begin(); itTrack != outgoingTracksVector.end(); ++itTrack) {
      SmartRef<Minerva::Track> refTrack(*itTrack);
      makeShortTracks_VESTool( physEvent, getEndPointVertex(physEvent, refTrack), trackVec, generation+1 );
    }
  }
  
  debug() << "Number of out going tracks after running VESTool " << deVertex->getNOutgoingTracks() << " Generation " << generation << endmsg;   
  debug() << "Exiting CCQENuRecoUtils::makeShortTracks_VESTool() now ....." << endmsg;   
  return StatusCode::SUCCESS; 
  
} // End of makeShortTracks_VESTool( )


//==========================================================================
// getEndPointVertex 
//==========================================================================
SmartRef<Minerva::Vertex> CCQENuRecoUtils::getEndPointVertex( Minerva::PhysicsEvent* physEvent, SmartRef<Minerva::Track> deTrack ) const { 

  debug() << "Entering CCQENuRecoUtils::getEndPointVertex() now ..... " << endmsg; 

  SmartRef<Minerva::Vertex> endPointVertex = (Minerva::Vertex*)NULL; 
  m_objectAssociator->getVertex_fromTrackBack(endPointVertex, deTrack); 
  if( !endPointVertex ) { 
    Minerva::Vertex* endPointVertexPtr = new Minerva::Vertex(); 
    endPointVertexPtr->setIncomingTrack( deTrack ); 
    endPointVertexPtr->setPosition( deTrack->lastNode()->position() ); 

    Gaudi::XYZVector error( sqrt(deTrack->lastState().trackCovariance()(0,0)), sqrt(deTrack->lastState().trackCovariance()(1,1)), 8.5 ); 
    endPointVertexPtr->setPositionErr(error); 

    try{ 
      addObject( getTimeSlice(deTrack), endPointVertexPtr ); 
    }catch(MinervaException& e){ 
      warning() << "Could not add a new endPointVertex to a TimeSlice ! Investigate if incoming track is owned by a TimeSlice !" << endmsg; 
    }

    addObject( physEvent, endPointVertexPtr ); 
    endPointVertex = endPointVertexPtr; 
  }

  debug() << "Exiting CCQENuRecoUtils::getEndPointVertex() now ..... " << endmsg; 
  return endPointVertex; 

} // End of getEndPointVertex( ) 


//========================================================
// makeConeAtEndProtonTrack
//========================================================
StatusCode CCQENuRecoUtils::makeConeAtEndProtonTrack( Minerva::PhysicsEvent *event, SmartRef<Minerva::Prong> protonProng, SmartRef<Minerva::Prong> muonProng, bool &foundClustersInCone, double &ConeClusterMaxDistance, Minerva::IDClusterVect &idClustersInCone, bool fillTruthTG4ProtonCone ) const {

  StatusCode sc;
  debug() << "Entering CCQENuRecoUtils::makeConeAtEndProtonTrack() now ....." << endmsg;
  
  // Get the proton track inside the prong
  SmartRef<Minerva::Track> track = protonProng->minervaTracks()[0];
  debug()<<" There are:"<< protonProng->minervaTracks().size()<< " tracks in proton prong"<<endmsg;
  debug()<< "Track address = " << track <<endmsg;
  if( track==NULL ){
    info()<<"Could not get proton track from this prong"<<endmsg;
    return StatusCode::SUCCESS;
  }
  
  // Cone angle
  double coneAngle = 30*CLHEP::degree;

  // Create cone at the end of the track
  Gaudi::XYZPoint endpoint = track->lastState().position();
  double theta = track->theta();
  double phi   = track->phi();

  if( track->direction() == Minerva::Track::Backward ) {
    theta = Gaudi::Units::pi - theta;
    phi   = Gaudi::Units::twopi - phi;
  }

  Gaudi::Polar3DVector axis(1,theta,phi);
  Cone cone(endpoint,axis,coneAngle);

  debug() << " Cone's starting position = " << endpoint << "\t ;axis = " << axis << "\t cone Angle = "<< coneAngle << endmsg;
  
  Minerva::IDClusterVect idClusterVector = getInTimeAnalyzableIDClusters( event, muonProng );
  if( !idClusterVector.size() ) { 
    debug() << "There are no clusters to analyze!"<<endmsg;
    return StatusCode::SUCCESS;
  }

  //! Get clusters inside the cone and add them to proton prong
  //! Using a constant length parameter for truncating the cone for now
  //! @todo use a more sophisticated method based on the
  //! separation of clusters in nuclear interaction lengths
  // Minerva::IDClusterVect idClustersInCone;
  double max_cluster_distance = -1.0;
  for(Minerva::IDClusterVect::iterator itCluster=idClusterVector.begin(); itCluster!=idClusterVector.end(); itCluster++) {
    if( !m_coneUtilsTool->isInsideCone(*itCluster,cone) ) continue; 
    //Get amount of projection of this cluster into cone axis
    double cluster_projdistance = m_mathTool->axisProjection(cone.vertex(), cone.axis(), *itCluster) * CLHEP::mm;
    //max_cluster_distance = (max_cluster_distance > cluster_projdistance)? max_cluster_distance : cluster_projdistance;
    debug()<<"Cluster Distance from Cone axis = " << cluster_projdistance << endmsg;
    if(cluster_projdistance > m_coneLength ) continue;
    idClustersInCone.push_back( *itCluster );
  }

  debug() << "Number of clusters found at end of proton track " << idClustersInCone.size() << endmsg; 

  //------------------------------------------------------------------------------------------------
  //! The method below was used to obtain an estimate of the max distance of the clusters that  
  //! come from a proton showering or kinking. The distance is from the end of proton track. 
  //! This is turned OFF now, set to FALSE through 'fillTruthTG4ProtonCone' 
  //! An expansion of this could be to plot distance of every cluster that lies within Cone from 
  //! end of proton track, both in MC and Data. Time permitted.  
  //! In OFF mode, value of max_cluster_distance returned should be -9999 or -1.    
  //------------------------------------------------------------------------------------------------
  if( haveNeutrinoMC() && fillTruthTG4ProtonCone)
    max_cluster_distance = getProtonTruthSecondaryMaxDistanceInCone(event, cone, idClustersInCone);

  //Create a blob
  Minerva::IDBlob* endProtonBlob = new Minerva::IDBlob();
  m_blobCreatorUtils->insertIDClusters( idClustersInCone, endProtonBlob, Minerva::IDBlob::NotAssigned2 );
  //Color the clusters
  m_hitTaggerTool->applyColorTag( endProtonBlob, m_clustersInConeProtonProngColor );

  addObject( event, endProtonBlob );
  protonProng->add( endProtonBlob );
  foundClustersInCone = (idClustersInCone.size()>0)? true : false;
  ConeClusterMaxDistance = max_cluster_distance;

  debug() << "Value of foundClustersInCone " << foundClustersInCone << endmsg; 

  debug() << "Exiting CCQENuRecoUtils::makeConeAtEndProtonTrack() now ....." << endmsg;
  return StatusCode::SUCCESS;

} // End of makeConeAtEndProtonTrack( ) 


//======================================================================================
//! Given a set of clusters and a cone look at the projection in the cone axis 
//! of the farthest track final position associated with the proton prong candidate
//======================================================================================
double CCQENuRecoUtils::getProtonTruthSecondaryMaxDistanceInCone( Minerva::PhysicsEvent *event, Cone cone, IDClusterVect clusters ) const {

  debug() << "Entering CCQENuRecoUtils::getProtonTruthSecondaryMaxDistanceInCone() now ....." << endmsg; 

  double traj_maxdistance = -1.0 * CLHEP::mm;

  int proton_candidate_truth_traj_ID = event->getIntData("proton_prong_traj_ID");
  if(proton_candidate_truth_traj_ID==-1){
    verbose()<<"There was no true TG4trajectory ID for the proton prong candidate"<<endmsg;
    return traj_maxdistance;
  }
  std::vector<const Minerva::IDCluster*> coneClusters;
  for( unsigned int i=0; i<clusters.size();++i) coneClusters.push_back( clusters[i] );

  double otherEnergy = -1.0;
  std::map<const Minerva::TG4Trajectory*,double> cone_trajectories = m_truthMatcher->getTG4Trajectories( coneClusters, otherEnergy );
  if (cone_trajectories.empty() ){
    warning()<<"TruthMatcher didn't get any trajectories from the proton cone clusters"<<endmsg;
    return traj_maxdistance;
  }
  else{
    debug()<<"Found "<< cone_trajectories.size() <<" trajectories in cone clusters" << endmsg;
  }

  std::map<const Minerva::TG4Trajectory*,double>::iterator it = cone_trajectories.begin();
  for( ; it != cone_trajectories.end(); ++it) {
    const Minerva::TG4Trajectory* traj = it->first;
    debug()<<"non-proton secondary trajectory PDG/ID = "<< traj->GetPDGCode()<< "/"<< traj->GetTrackId()<< " from parentID = " << traj->GetParentId() 
	   << "; proton prong ID = " << proton_candidate_truth_traj_ID << endmsg;
    //Only trajectories coming from the proton prong candidate
    if( traj->GetParentId() == proton_candidate_truth_traj_ID || traj->GetTrackId()==proton_candidate_truth_traj_ID ){
      debug()<<"proton secondary trajectory PDG = "<< traj->GetPDGCode()<< endmsg;
      if ( fabs(traj->GetPDGCode())==2112 || fabs(traj->GetPDGCode())==111 || fabs(traj->GetPDGCode())==310 || fabs(traj->GetPDGCode())==130) continue; //exclude neutrons or pi0s/K0s

      Gaudi::XYZPoint traj_finalpos(traj->GetFinalPosition().x(), traj->GetFinalPosition().y(), traj->GetFinalPosition().z() );
      double traj_distance = m_mathTool->axisProjection(cone.vertex(), cone.axis(), traj_finalpos);
      debug()<<" proton secondary trajectory distance = " << traj_distance<<endmsg;
      traj_maxdistance = (traj_maxdistance > traj_distance)? traj_maxdistance : traj_distance;
    }
  }

  debug() << "Exiting CCQENuRecoUtils::getProtonTruthSecondaryMaxDistanceInCone() now ....." << endmsg; 
  return traj_maxdistance;

} //End of getProtonTruthSecondaryMaxDistanceInCone( )


//=====================================
// makeFuzzEMMuonBlobs 
//=====================================
bool CCQENuRecoUtils::makeFuzzEMMuonBlobs( Minerva::PhysicsEvent* event, SmartRef<Minerva::Prong> muonProng) const {

  debug() << "Entering CCQENuRecoUtils::makeFuzzEMMuonBlobs() now ....." << endmsg; 

  bool status = false;
  Minerva::IDClusterVect analyzableIDClusters = getInTimeAnalyzableIDClusters( event, muonProng );

  if( analyzableIDClusters.size() == 0 ) {
    debug()<<"No Clusters to analyze!"<<endmsg;
    return status;
  } else {
    Minerva::IDBlob* fuzzBlob = new Minerva::IDBlob();
    m_muonUtils->findMuonFuzz( muonProng, m_muonFuzzDistanceFromVertex, m_muonFuzzRadius, fuzzBlob );
    info() << "  Found " << fuzzBlob->nclusters() << " clusters in Muon Fuzz Blob" << endmsg;

    // add fuzz Muon blobs to event and Muon prong
    double muonFuzzEnergy = 0.0;
    if( fuzzBlob->nclusters() > 0 ) {
      muonFuzzEnergy = m_caloUtils->applyCalConsts( fuzzBlob, "Default", false );
      debug() << "Muon fuzz energy in event is " << muonFuzzEnergy << " MeV" << endmsg;
      event->setDoubleData( "muon_fuzz_energy", muonFuzzEnergy );

      addObject( event, fuzzBlob );
      muonProng->add( fuzzBlob );
      fuzzBlob->setHistory( Minerva::IDBlob::Used );
      if( 0 <= m_muonFuzzBlobsColor ) m_hitTaggerTool->applyColorTag( fuzzBlob, m_muonFuzzBlobsColor );
    
    } else {
      delete fuzzBlob;
    }
  }

  debug() << "Exiting CCQENuRecoUtils::makeFuzzEMMuonBlobs() now ....." << endmsg;
  return status;
  
} // End of makeFuzzEMMuonBlobs( ) 


//=====================================
// makeIsoEMMuonBlobs 
//=====================================
bool CCQENuRecoUtils::makeIsoEMMuonBlobs( Minerva::PhysicsEvent* event, SmartRef<Minerva::Prong> muonProng) const {

  debug() << "Entering CCQENuRecoUtils::makeIsoEMMuonBlobs() now ....." << endmsg;

  bool status = false;
  Minerva::IDClusterVect analyzableIDClusters = getInTimeAnalyzableIDClusters( event, muonProng );

  if( analyzableIDClusters.size() == 0 )
  {
    debug()<<"No Clusters to analyze!"<<endmsg;
    return status;
  } else {
    std::vector<Minerva::IDBlob*>* isoBlobs = new std::vector<Minerva::IDBlob*>;
    m_muonUtils->findMuonEMBlobs( muonProng, analyzableIDClusters, m_muonFuzzDistanceFromVertex, isoBlobs );

    info() << "  Found " << isoBlobs->size() << " Isolated Muon blobs" << endmsg;
    
    // add isolated Muon blobs to event and Muon prong
    double muonBlobEnergy = 0.0;
    for( std::vector<Minerva::IDBlob*>::iterator itBlob = isoBlobs->begin(); itBlob != isoBlobs->end(); itBlob++ ) {
      addObject( event, *itBlob );
      muonProng->add( *itBlob );
      (*itBlob )->setHistory( Minerva::IDBlob::Used );
      muonBlobEnergy += m_caloUtils->applyCalConsts( *itBlob, "Default", false );
      if( 0 <= m_muonIsolatedBlobsColor ) m_hitTaggerTool->applyColorTag( *itBlob, m_muonIsolatedBlobsColor );
    }
    info() << "Muon blob energy in event is " << muonBlobEnergy << " MeV" << endmsg;
    event->setIntData( "n_muon_iso_blobs", isoBlobs->size() );
    event->setDoubleData( "muon_iso_blobs_energy", muonBlobEnergy );
    delete isoBlobs;
    status = true;
  }

  if( 0 <= m_muonProngColor ) m_hitTaggerTool->applyColorTag( muonProng, m_muonProngColor );

  debug() << "Exiting CCQENuRecoUtils::makeIsoEMMuonBlobs() now ....." << endmsg;
  return status;
  
} // End of makeIsoEMMuonBlobs( )


//==================================================================================================================
// makeVertexBlobs - makes Vertex Blobs from the clusters at/near a specified Vertex (N.B.: not all vertices)  
//==================================================================================================================
StatusCode CCQENuRecoUtils::makeVertexBlobs( Minerva::IDClusterVect& idClusterVector, SmartRef<Minerva::Vertex> &deVertex, double searchStepSize, unsigned int numSearchRadii, std::vector<Minerva::IDBlob*>& vtxBlobVector ) const {
  
  debug() << "Entering CCQENuRecoUtils::makeVertexBlobs() now ....." << endmsg; 
  StatusCode sc; 
  vtxBlobVector.clear(); 

  //-------------------------------
  //! Set some search constants 
  //-------------------------------
  double maxStartingDistance = 0.0;
  double maxAllowedSearchGap = 1e6; 
  double totalVtxBlobEnergy  = 0.0; 
  
  for( unsigned int iradius=0; iradius<numSearchRadii; ++iradius ) { 
    
    double searchStep = searchStepSize; 
    double maxSearchDistance = searchStep * (double)( iradius + 1 ); 
    maxStartingDistance = maxSearchDistance; 

    Minerva::IDBlob* vertexBlob = new Minerva::IDBlob(); 

    sc = m_vtxBlobCreatorTool->createIDBlobs( idClusterVector, vertexBlob, deVertex, maxSearchDistance, maxStartingDistance, maxAllowedSearchGap, true ); 

    if( sc.isFailure() ) { 
      error() << "Failure to make Vertex Blobs. Deleting each vertexBlob ....." << endmsg; 
      delete vertexBlob; 
      return sc; 
    }

    if( vertexBlob->nclusters() ) { 
      totalVtxBlobEnergy += vertexBlob->energy();       
      vtxBlobVector.push_back( vertexBlob ); 
    } else { 
      delete vertexBlob; 
    }
  } // End of for loop over Blob searching distance (radii) 
  
  debug() << "Size of vtxBlobVector inside makeVertexBlobs() is = " << vtxBlobVector.size() << endmsg; 
  debug() << "Total visible energy from all the Blobs is = " << totalVtxBlobEnergy << endmsg; 

  debug() << "Exiting CCQENuRecoUtils::makeVertexBlobs() now ....." << endmsg; 
  return StatusCode::SUCCESS; 

} // End of makeVertexBlobs( )




//#########################################################################################
//
// End CCQENuRecoUtils.cpp
//
//######################################################################################### 






