 #include "CCQENu.h"

#include "GiGaCnv/IGiGaGeomCnvSvc.h"

//Tools - General and Analysis Specific
#include "MinervaUtils/IMinervaObjectAssociator.h"
#include "RecInterfaces/IRecoObjectTimeTool.h"
#include "RecInterfaces/IFiducialPointTool.h"
#include "GeoUtils/IMinervaCoordSysTool.h"
#include "MinervaUtils/IMinervaMathTool.h"

#include "CCQENu/ICCQENuRecoUtils.h"
#include "BlobFormation/IBlobCreatorUtils.h"
#include "EventRecInterfaces/IPrimaryBlobProngTool.h"
#include "ProngMaker/IMichelTool.h"
#include "EnergyRecTools/ICalorimetryUtils.h"
#include "AnaUtils/IProtonUtils.h"
#include "AnaUtils/AnaFilterTags.h"
#include "AnaUtils/IMuonUtils.h"
#include "AnaUtils/IPhysicsCalculator.h"
#include "TruthMatcher/ITruthMatcher.h"
#include "ParticleMaker/IParticleMakerTool.h"
#include "RecUtils/ParticleExtraDataDefs.h"

#include "MinervaUtils/IHitTaggerTool.h"

#include "Event/DAQHeader.h"
#include "Event/GenMinHeader.h"
#include "Event/PhysicsEvent.h"
#include "Event/TimeSlice.h"

#include "ProngMaker/IImprovedMichelTool.h" //ImprovedMichelTool

//From GaudiException
#include "GaudiKernel/PhysicalConstants.h"

DECLARE_TOOL_FACTORY( CCQENu );



// m_mathTool is STATIC so it has to be initialized
// somewhere outside of class scope.
IMinervaMathTool* CCQENu::m_mathTool = NULL;

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
CCQENu::CCQENu(const std::string& type, const std::string& name, const IInterface* parent )
  : MinervaAnalysisTool( type, name, parent ) {

  declareInterface<IInteractionHypothesis>(this);
  m_anaSignature = "CCQENu";

  m_hypMeths.push_back( "CCQENu" );
  declareProperty("HypothesisMethods", m_hypMeths  );

  //! Time Window parameters for cluster selections
  declareProperty( "LowerTimeWindow",m_lowerTimeWindow = -20 * CLHEP::ns );
  declareProperty( "UpperTimeWindow",m_upperTimeWindow =  35 * CLHEP::ns );

  //! Particles Scores
  declareProperty( "MinMuonScore", m_minMuonScore  = 0.9 );
  declareProperty( "MinProtonScore", m_minProtonScore  = 0.05 );
  //! Muon q/p cut
  declareProperty( "qOverpChargeCut", m_qOverpChargeCut = 0. );
  //! Binding Energy
  declareProperty( "NuCCQEBindingEnergyMeV", m_nuCCQEBindingEnergyMeV = 34.0 * CLHEP::MeV );

  //! Making Short Tracks
  declareProperty( "MakeShortTracks",                           m_makeShortTracks                         = true );
  declareProperty( "MakeShortTracksvtxAnchoredShortTracker",   m_runVertexAnchoredShortTracker           = true );
  declareProperty( "DoRecursiveVertexAnchoredShortTracking",    m_doRecursiveVertexAnchoredShortTracking  = true );
  declareProperty( "MakeShortTracksvtxEnergyStudyTool",        m_runVertexEnergyStudyTool                = true );
  declareProperty( "DoRecursiveVESTool",                        m_doRecursiveVESTool                      = true );

  //! Make EM and Fuzz Blobs for the Muon
  declareProperty( "MakeIsoMuonEMBlobs",                        m_makeIsoMuonEMBlobs              = true );
  declareProperty( "MakeFuzzMuonEMBlobs",                       m_makeFuzzMuonEMBlobs             = true );

  //! Primary Tag names
  declareProperty( "PrimaryHadronTagName",   m_primaryHadron     = "PrimaryHadron" );
  declareProperty( "PrimaryProtonTagName",   m_primaryProton     = "PrimaryProton" );
  declareProperty( "SecondaryProtonTagName", m_secondaryProtons  = "SecondaryProtons" );

  //! Maximum number of isolated blobs
  declareProperty( "MaxIsoBlobs", m_maxIsoBlobs = 2);

  //! For making Vertex Blobs
  declareProperty( "SearchStepSize",                    m_searchStepSize                       = 300.0 * CLHEP::mm );
  declareProperty( "NumSearchRadii",                    m_numSearchRadii                       = 1 );
  declareProperty( "FStyleMaxSearchDistance",          m_maxSearchDistance                    = 300.0 * CLHEP::mm ); //mm
  declareProperty( "FStyleMaxStartingDistance",        m_maxStartingDistance                  = 300.0 * CLHEP::mm ); //mm
  declareProperty( "FStyleMaxAllowedSearchGap",        m_maxAllowedSearchGap                  = 1e6 * CLHEP::mm );   //mm

  //! For making Vertex Blob Prongs
  declareProperty( "MakeFilamentStyleVtxBlobProngs",       m_makeFilamentStyleVtxBlobProngs        = false );
  declareProperty( "MakeMultipleRadiiStyleVtxBlobProngs",  m_makeMultipleRadiiStyleVtxBlobProngs   = true );
  declareProperty( "MaxAllowedSeparationBlobVertex",       m_maxSeparationBlobVertex               = 300.0 * CLHEP::mm );

  //! Loose Fiducial truth Michel electron cut
  declareProperty( "MichelDownstreamZ",          m_michel_downstreamZ          = 8524.19 * CLHEP::mm ); //mm // Module 83?
  declareProperty( "MichelUpstreamZ",            m_michel_upstreamZ            = 5900.91 * CLHEP::mm ); //mm //Module 25?

  //! Cone Parameters
  declareProperty("FillTruthTG4ProtonCone",     m_fillTruthTG4ProtonCone       = false); //mm

  //! Use OD Match prongs for finding protons
  declareProperty( "UseODMatchProtons",       m_useOdMatchProtons       = false);
  declareProperty( "MaxProtonChi2",           m_maxProtonChi2           = 50.  );
  declareProperty( "ProtonEndPointZLow",      m_ProtonZLow              = 4000.0  );  //-- mm
  declareProperty( "ProtonEndPointZHigh",     m_ProtonZHigh             = 10000.0 );  //-- mm
  declareProperty( "ProtonEndPointApothem",   m_ProtonApothem           = 1200  );  //-- mm

  //! Prong, Blob and Cluster Colors
  declareProperty( "IsolatedBlobProngColor",      m_isolatedBlobProngColor       = 0xFF0000 ); // pure red
  declareProperty( "DispersedEnergyColor",        m_dispersedEnergyColor         = 0x00CCFF ); // cyan
  declareProperty( "VertexBlobProngColor",        m_vertexBlobProngColor         = 0x996600 ); // brown
  declareProperty( "ProtonProngColor",            m_protonProngColor             = 0x990000 ); // maroon
  declareProperty( "HadronProngsColor",           m_hadronProngsColor            = 0xFFFF00);  // pure yellow
  declareProperty( "ConeEnergyColor",             m_coneEnergyColor              = 0xFF00FF ); // magenta

  //! Tools and their Aliases
  declareProperty( "MinervaObjAssocAlias",        m_minObjAssocAlias           = "CCQENUMinObjAssociator" );
  declareProperty( "RecoObjTimeToolAlias",        m_recoObjTimeToolAlias       = "CCQENURecoObjTimeTool" );
  declareProperty( "MinervaCoordSysToolAlias",    m_minCoordSysToolAlias       = "CCQENUMinCoordSysTool" );
  declareProperty( "MinervaMathToolAlias",        m_mathToolAlias              = "CCQENUMinMathTool" );

  declareProperty( "CCQENURecoUtilsAlias",       m_MMDRecoUtilsAlias          = "CCQENURecoUtilsTool" );
  declareProperty( "BlobCreatorUtilsAlias",       m_blobCreatorUtilsAlias      = "CCQENUBlobCreatorUtils" );
  declareProperty( "PrimaryBlobProngToolAlias",   m_primaryBlobProngToolAlias  = "CCQENUPrimaryBlobProngTool" );
  declareProperty( "MichelToolAlias",             m_michelToolAlias            = "CCQENUMichelFinderTool" );
  declareProperty( "ImprovedMichelToolAlias",     m_improvedmichelToolAlias    = "CCQENUImprovedMichelFinderTool" );
  declareProperty( "CalorimetryUtilsAlias",       m_caloUtilsAlias             = "CCQENUCaloUtils" );
  declareProperty( "ProtonUtilsAlias",            m_protonUtilsAlias           = "CCQENUProtonUtils" );
  declareProperty( "ParticleToolAlias",           m_particleMakerAlias         = "CCQENUParticleMaker" );

  declareProperty( "HitTaggerToolAlias",          m_hitTaggerToolAlias         = "CCQENUHitTaggerTool" );

  declareProperty( "UseMuonIsPlausible",          m_useMuonIsPlausible         = true );

  //For Mehreen...

  //declareProperty( "maxClusTime",      double  m_maxClusTime        = 35.0*CLHEP::ns );
  //declareProperty( "minClusTime",      double  m_minClusTime        = -20*CLHEP::ns );
}


//=============================================================================
// Initialize
//=============================================================================

StatusCode CCQENu::initialize() {

  debug()<<"Entering CCQENu::initialize() ....."<<endmsg;

  StatusCode sc = this->MinervaAnalysisTool::initialize();
  if( sc.isFailure() ) { return Error( "Failed to initialize!", sc ); }

  //Get MinervaObjectAssociator
  try{
    m_objectAssociator = tool<IMinervaObjectAssociator>("MinervaObjectAssociator", m_minObjAssocAlias);
  } catch( GaudiException& e ) {
    error() << "Could not obtain tool: " << m_minObjAssocAlias << endmsg;
    return StatusCode::FAILURE;
  }

  //Get RecoObjectTime Tool
  try{
    m_recoObjTimeTool = tool<IRecoObjectTimeTool>("RecoObjectTimeTool", m_recoObjTimeToolAlias);
  } catch(GaudiException& e){
    error()<<"Could not obtain tool: " << m_recoObjTimeToolAlias << endmsg;
    return StatusCode::FAILURE;
  }

  //Get MinervaCoordSys Tool
  try{
    m_minCoordSysTool = tool<IMinervaCoordSysTool>("MinervaCoordSysTool", m_minCoordSysToolAlias);
  } catch( GaudiException& e ) {
    error() << "Could not obtain tool: " << m_minCoordSysToolAlias << endmsg;
    return StatusCode::FAILURE;
  }

  //Get MinervaMath Tool
  try{
    m_mathTool = tool<IMinervaMathTool>("MinervaMathTool", m_mathToolAlias);
  } catch( GaudiException& e ) {
    error() << "Could not obtain tool: " << m_mathToolAlias << endmsg;
    return StatusCode::FAILURE;
  }

  //Get CCQENURecoUtils Tool
  try{
    m_minModDepCCQERecoUtils = tool<ICCQENuRecoUtils>("CCQENuRecoUtils", m_MMDRecoUtilsAlias);
  } catch(GaudiException& e) {
    error() << "Could not obtain tool: " << m_MMDRecoUtilsAlias <<endmsg;
    return StatusCode::FAILURE;
  }

  //Get BlobCreatorUtils Tool
  try{
    m_blobCreatorUtils = tool<IBlobCreatorUtils>("BlobCreatorUtils", m_blobCreatorUtilsAlias);
  } catch( GaudiException& e ){
    error() << "Could not obtain BlobCreatorUtils: " << m_blobCreatorUtilsAlias << endmsg;
    return StatusCode::FAILURE;
  }

  //Get PrimaryBlobProng Tool
  try{
    m_primaryBlobProngTool = tool<IPrimaryBlobProngTool>("PrimaryBlobProngTool", m_primaryBlobProngToolAlias);
  } catch( GaudiException& e ) {
    error() << "Could not obtain tool: " << m_primaryBlobProngToolAlias << endmsg;
    return StatusCode::FAILURE;
  }

  //Get Michel Tool
  try{
    m_michelTool = tool<IMichelTool>("MichelTool", m_michelToolAlias);
  } catch(GaudiException& e){
    error()<<"Could not obtain tool: " << m_michelToolAlias << endmsg;
    return StatusCode::FAILURE;
  }

  //Get Improved Michel Tool //ImprovedMichelTool
  try{
    m_improvedmichelTool = tool<IImprovedMichelTool>("ImprovedMichelTool");
  } catch (GaudiException& e) {
    error() << "Could not obtain tool: ImprovedMichelTool" << endmsg;
    return StatusCode::FAILURE;
  }

  //Get Calorimetry Tool
  try{
    m_caloUtils = tool<ICalorimetryUtils>("CalorimetryUtils", m_caloUtilsAlias);
  } catch( GaudiException& e ) {
    error() << "Could not obtain tool: " << m_caloUtilsAlias << endmsg;
    return StatusCode::FAILURE;
  }

  //Get ProtonUtils Tool
  try{
    m_protonUtils = tool<IProtonUtils>("ProtonUtils", m_protonUtilsAlias);
  } catch( GaudiException& e ){
    error() << "Could not obtain tool: " << m_protonUtilsAlias << endmsg;
    return StatusCode::FAILURE;
  }

  //Get ParticleMaker Tool
  try{
    m_particleMaker = tool<IParticleMakerTool>("ParticleMakerTool", m_particleMakerAlias);
  } catch( GaudiException& e ){
    error() << "Could not obtain tool: " << m_particleMakerAlias << endmsg;
    return StatusCode::FAILURE;
  }

  //Get HitTagger Tool
  try{
    m_hitTaggerTool = tool<IHitTaggerTool>("HitTaggerTool", m_hitTaggerToolAlias);
  } catch( GaudiException& e ) {
    error() << "Could not obtain tool: " << m_hitTaggerToolAlias << endmsg;
    return StatusCode::FAILURE;
  }




  //---------------------------------------------------------------------------
  //! Declare common ntuple branches that will be present in your AnaTuple
  //---------------------------------------------------------------------------
  declareCommonPhysicsAnaBranches();
  declareNuMIBranches();
  declareMinosMuonBranches();
  declareGenieWeightBranches();
  //declareVertexActivityStudyBranches();
  declareSystematicShiftsBranches();
  declareParticleResponseBranches();
  // For HadronReweightTool
  declareHadronReweightBranches();

  //---------------------------------------
  //! Declare branches for own ntuples
  //---------------------------------------

  //! Event - Truth
  declareBoolTruthBranch( "is_fiducial" );
  declareIntTruthBranch( "reco_is_fiducial", -1 );
  declareIntTruthBranch( "reco_is_minos_match", -1 );
  declareIntTruthBranch( "reco_has_muon_charge", -1 );
  declareIntTruthBranch( "reco_muon_is_minos_match_track", -1 );
  declareIntTruthBranch( "reco_muon_is_minos_match_stub", -1 );
  declareIntTruthBranch( "reco_pass_CCQENu_precuts", 0 );
  declareIntTruthBranch( "reco_has_single_proton", 0 );
  declareIntTruthBranch( "reco_has_michel_electron", 0 );

  //! Event - general reco
  declareIntEventBranch( "multiplicity", -1 );
  declareIntEventBranch( "has_single_proton", -1 );
  declareIntEventBranch( "pass_CCQENu_precuts", -1 );
  declareIntEventBranch( "n_iso_trk_prongs", -1 );
  declareIntEventBranch( "n_anchored_short_trk_prongs", -1 );
  declareIntEventBranch( "n_anchored_long_trk_prongs", -1 );
  declareContainerIntEventBranch( "event_vertex_types" );
  declareContainerIntEventBranch( "event_in_time_vertex_types" );
  declareContainerDoubleEventBranch( "event_vertex_time_diff" );
  declareContainerDoubleEventBranch( "event_track_time_diff" );
  declareContainerDoubleEventBranch( "event_tracks_energy" );
  declareContainerDoubleEventBranch( "event_in_time_tracks_energy" );
  declareContainerDoubleEventBranch( "event_track_hit_energy" );
  declareContainerDoubleEventBranch( "event_track_hit_time" );
  declareContainerIntEventBranch( "event_track_nhits" );
  declareIntEventBranch( "slice_n_hits", -1);
  declareContainerDoubleEventBranch( "slice_hit_time");
  declareContainerDoubleEventBranch( "slice_hit_energy");
  declareContainerDoubleEventBranch("all_event_start_vertex_time");
  declareContainerDoubleEventBranch("all_event_start_vertex_time_minos_match");
  declareContainerIntEventBranch("all_event_start_vertex_fv_minos_match");
  declareIntEventBranch( "has_interaction_vertex", -1);
  declareIntEventBranch( "n_minos_matches", -1);
  declareContainerIntEventBranch("recoil_lower_time_limit");
  declareContainerIntEventBranch("recoil_upper_time_limit");
  declareContainerDoubleEventBranch("recoil_summed_energy");
  declareContainerDoubleEventBranch("recoil_data_fraction");
  declareIntEventBranch( "event_used_start_vertices",-1);
  declareIntEventBranch( "event_unused_start_vertices",-1);
  declareContainerDoubleEventBranch( "event_extra_track_PID");//will store pid values from tracks not in the interaction vertex.
  //! Event - reco Muon
  declareIntEventBranch( "muon_is_minos_match_track", -1 );
  declareIntEventBranch( "muon_is_minos_match_stub", -1 );
  declareDoubleEventBranch( "muon_minerva_trk_chi2PerDoF", -1 );
  declareContainerDoubleEventBranch( "muon_theta_allNodes" );
  declareContainerDoubleEventBranch( "muon_thetaX_allNodes" );
  declareContainerDoubleEventBranch( "muon_thetaY_allNodes" );

  //! Event - Muon Iso Blobs/Fuzz
  declareIntEventBranch("n_muon_iso_blobs", -1 );
  declareDoubleEventBranch("muon_iso_blobs_energy", -9999.0);
  declareIntEventBranch("muon_fuzz_energy", -9999.0);

  //! Event - Blobs & energies
  declareIntEventBranch( "n_nonvtx_iso_blobs", -1 );
  declareIntEventBranch( "n_nonvtx_iso_blobs_all", -1 );
  declareDoubleEventBranch( "nonvtx_iso_blobs_energy" , -9999.0 );
  declareDoubleEventBranch( "nonvtx_iso_blobs_energy_all" , -9999.0 );
  declareDoubleEventBranch( "vtx_blobs_energy" , -9999.0 );
  declareDoubleEventBranch( "dis_id_energy", -9999.0 );
  declareDoubleEventBranch( "vtx_iso_blobs_energy_outside_radius", -9999.0 );
  declareDoubleEventBranch( "recoil_energy_nonmuon_nonvtx0mm", -9999.0);
  declareDoubleEventBranch( "recoil_energy_nonmuon_nonvtx50mm", -9999.0);
  declareDoubleEventBranch( "recoil_energy_nonmuon_nonvtx100mm", -9999.0);
  declareDoubleEventBranch( "recoil_energy_nonmuon_nonvtx150mm", -9999.0);
  declareDoubleEventBranch( "recoil_energy_nonmuon_nonvtx200mm", -9999.0);
  declareDoubleEventBranch( "recoil_energy_nonmuon_nonvtx250mm", -9999.0);
  declareDoubleEventBranch( "recoil_energy_nonmuon_nonvtx300mm", -9999.0);
  declareDoubleEventBranch( "recoil_energy_nonmuon_vtx0mm", -9999.0);
  declareDoubleEventBranch( "recoil_energy_nonmuon_vtx50mm", -9999.0);
  declareDoubleEventBranch( "recoil_energy_nonmuon_vtx100mm", -9999.0);
  declareDoubleEventBranch( "recoil_energy_nonmuon_vtx150mm", -9999.0);
  declareDoubleEventBranch( "recoil_energy_nonmuon_vtx200mm", -9999.0);
  declareDoubleEventBranch( "recoil_energy_nonmuon_vtx250mm", -9999.0);
  declareDoubleEventBranch( "recoil_energy_nonmuon_vtx300mm", -9999.0);
  declareContainerDoubleEventBranch( "vtx_blobs_vtx_energy_in_prong" );
  declareContainerDoubleEventBranch( "vtx_blobs_iso_energy_in_prong" );
  declareContainerDoubleEventBranch( "vtx_blobs_iso_energy_clusters_outside_radius_in_prong" );
  declareContainerDoubleEventBranch( "vtx_blobs_vtx_distance_in_prong" );
  declareContainerDoubleEventBranch( "vtx_blobs_iso_distance_in_prong" );
  declareContainerDoubleEventBranch( "nonvtx_iso_blobs_energy_in_prong" );
  declareContainerDoubleEventBranch( "nonvtx_iso_blobs_distance_in_prong" );
  declareContainerDoubleEventBranch( "nonvtx_iso_blobs_start_position_x_in_prong" );
  declareContainerDoubleEventBranch( "nonvtx_iso_blobs_start_position_y_in_prong" );
  declareContainerDoubleEventBranch( "nonvtx_iso_blobs_start_position_z_in_prong" );
  declareContainerDoubleEventBranch( "nonvtx_iso_blobs_time_in_prong" );
  declareContainerDoubleEventBranch( "nonvtx_iso_blobs_time_difference_in_prong" );
  declareContainerDoubleEventBranch( "nonvtx_iso_blobs_lowest_module_x_in_prong" );
  declareContainerDoubleEventBranch( "nonvtx_iso_blobs_lowest_module_u_in_prong" );
  declareContainerDoubleEventBranch( "nonvtx_iso_blobs_lowest_module_v_in_prong" );
  declareContainerDoubleEventBranch( "nonvtx_iso_blobs_highest_module_x_in_prong" );
  declareContainerDoubleEventBranch( "nonvtx_iso_blobs_highest_module_u_in_prong" );
  declareContainerDoubleEventBranch( "nonvtx_iso_blobs_highest_module_v_in_prong" );
  declareContainerDoubleEventBranch( "nonvtx_iso_blobs_earliest_hit_time_in_prong" );
  declareContainerDoubleEventBranch( "nonvtx_iso_blobs_latest_hit_time_in_prong" );
  declareContainerDoubleEventBranch( "nonvtx_iso_blobs_highest_hit_energy_in_prong" );
  declareContainerIntEventBranch( "nonvtx_iso_blobs_n_hits_in_prong" );
  declareContainerIntEventBranch( "nonvtx_iso_blobs_particle_pdg_in_prong" );
  declareContainerIntEventBranch( "nonvtx_iso_blobs_primary_particle_pdg_in_prong" );
  declareContainerDoubleEventBranch( "nonvtx_iso_blobs_matched_energy_fraction_in_prong" );
  declareContainerDoubleEventBranch( "nonvtx_iso_blobs_data_energy_fraction_in_prong" );


  //! Event - Off-proton track cluster info
  declareContainerIntEventBranch( "clusters_found_at_end_proton_prong" );
  declareContainerDoubleEventBranch( "clusters_found_at_end_proton_prong_max_distance" );
  declareContainerIntEventBranch( "number_clusters_at_end_proton_prong" );
  declareContainerDoubleEventBranch( "visE_clusters_at_end_proton_prong" );
  declareContainerDoubleEventBranch( "calibE_clusters_at_end_proton_prong" );

  //! Event - Michel variables
  //declareContainerIntEventBranch( "has_michel_track_in_region");
  declareContainerIntEventBranch( "has_michel_vertex_type");
  declareContainerIntEventBranch( "has_michel_in_vertex_point");
  declareContainerIntEventBranch( "has_michel_category");
  declareContainerIntEventBranch( "has_michel_ndigits");
  declareContainerIntEventBranch( "has_michel_bgmodule");
  declareContainerIntEventBranch( "has_michel_edmodule");
  declareContainerIntEventBranch( "has_michel_nmodules");
  declareContainerIntEventBranch( "has_michel_nplanes");
  declareContainerIntEventBranch( "has_michel_view_sum");
  declareContainerIntEventBranch( "has_michel_ntracks");
  declareContainerIntEventBranch( "has_michel_slice_number");
  declareContainerIntEventBranch("has_michel_matched_pdg");
  declareContainerIntEventBranch("has_michel_matched_primary_pdg");

  declareContainerDoubleEventBranch("has_michel_distance");
  declareContainerDoubleEventBranch("has_michel_energy");
  declareContainerDoubleEventBranch("has_michel_time_diff");
  declareContainerDoubleEventBranch("has_michel_slice_energy");
  declareContainerDoubleEventBranch("has_michel_matched_energy_fraction");
  declareContainerDoubleEventBranch("has_michel_data_energy_fraction");
  declareContainerDoubleEventBranch("has_michel_hit_charges");
  declareContainerDoubleEventBranch("has_michel_hit_times");
  declareContainerDoubleEventBranch("has_michel_hit_time_diff_vtx");
  declareContainerDoubleEventBranch("has_michel_hit_time_diff_cluster");

  declareIntEventBranch( "truth_has_michel_electron", 0 );
  declareIntEventBranch( "truth_improved_michel_electron", 0 );
  declareContainerDoubleEventBranch( "truth_has_michel_from_pion_plus_momentum" );
  declareContainerDoubleEventBranch( "truth_has_michel_from_pion_minus_momentum" );

  //! Event - Improved Michel Tool variables //ImprovedMichelTool
  declareIntEventBranch("improved_nmichel");
  declareIntEventBranch("improved_allmichels");

  declareContainerIntEventBranch("improved_michel_vertex_type");
  declareContainerIntEventBranch("improved_michel_in_vertex_point");

  declareContainerIntEventBranch("improved_michel_match_vec");
  declareContainerDoubleEventBranch("improved_michel_tvec");
  declareContainerDoubleEventBranch("improved_michel_tdiff_vec");
  declareContainerDoubleEventBranch("improved_michel_xvec");
  declareContainerDoubleEventBranch("improved_michel_yvec");
  declareContainerDoubleEventBranch("improved_michel_uvec");
  declareContainerDoubleEventBranch("improved_michel_vvec");
  declareContainerDoubleEventBranch("improved_michel_zvec");
  declareContainerDoubleEventBranch("improved_michel_dist_vec");

  declareContainerDoubleEventBranch("improved_michel_evis_vec");
  declareContainerDoubleEventBranch("improved_michel_ecalo_vec");
  declareContainerDoubleEventBranch("improved_michel_polarangle_vec");

  declareContainerDoubleEventBranch("improved_michel_truepion_energy_vec");


  declareContainerIntEventBranch("improved_michel_view_vec");
  declareContainerDoubleEventBranch("improved_michel_hit_charges");
  declareContainerDoubleEventBranch("improved_michel_hit_times");
  declareContainerDoubleEventBranch("improved_michel_hit_time_diff_vtx");
  declareContainerDoubleEventBranch("improved_michel_hit_time_diff_cluster");
  declareContainerIntEventBranch("improved_michel_ndigits");
  declareContainerIntEventBranch("improved_michel_nplanes");
  declareContainerIntEventBranch("improved_michel_clussize");

  declareContainerIntEventBranch("improved_michel_matched_pdg");
  declareContainerIntEventBranch("improved_michel_matched_primary_pdg");
  declareContainerDoubleEventBranch("improved_michel_matched_energy_fraction");
  declareContainerDoubleEventBranch("improved_michel_data_energy_fraction");


  // Aaron's Michel variables

  declareContainerIntEventBranch("improved_michel_SliceNumber_vec");
  declareContainerIntEventBranch("improved_michel_fitCode_vec");
  declareContainerIntEventBranch("improved_michel_fitPass_vec");
  declareContainerDoubleEventBranch("improved_michel_MatchedEndDist_vec");
  declareContainerDoubleEventBranch("improved_michel_matchedvtx_energy_vec");
  declareContainerDoubleEventBranch("improved_michel_transdist_vec");

  declareContainerDoubleEventBranch("improved_michel_x1vec");
  declareContainerDoubleEventBranch("improved_michel_y1vec");
  declareContainerDoubleEventBranch("improved_michel_u1vec");
  declareContainerDoubleEventBranch("improved_michel_v1vec");
  declareContainerDoubleEventBranch("improved_michel_z1vec");

  declareContainerDoubleEventBranch("improved_michel_x2vec");
  declareContainerDoubleEventBranch("improved_michel_y2vec");
  declareContainerDoubleEventBranch("improved_michel_u2vec");
  declareContainerDoubleEventBranch("improved_michel_v2vec");
  declareContainerDoubleEventBranch("improved_michel_z2vec");


  declareContainerDoubleEventBranch("improved_michel_vtx_xvec");
  declareContainerDoubleEventBranch("improved_michel_vtx_yvec");
  declareContainerDoubleEventBranch("improved_michel_vtx_uvec");
  declareContainerDoubleEventBranch("improved_michel_vtx_vvec");
  declareContainerDoubleEventBranch("improved_michel_vtx_zvec");

  declareContainerDoubleEventBranch("improved_michel_vtxangle_vec");


// Adding some variables for Mehreen's michel tool... MehTool or MehchelTool

  declareContainerDoubleEventBranch("mehtool_closestclusterX_distance");
  declareContainerDoubleEventBranch("mehtool_closestclusterU_distance");
  declareContainerDoubleEventBranch("mehtool_closestclusterV_distance");

  declareContainerDoubleEventBranch("mehtool_closestclusterXZ_distance");
  declareContainerDoubleEventBranch("mehtool_closestclusterUZ_distance");
  declareContainerDoubleEventBranch("mehtool_closestclusterVZ_distance");

  // Energy of closest cluster to michel

  declareContainerDoubleEventBranch("mehtool_closestclusterX_energy");
  declareContainerDoubleEventBranch("mehtool_closestclusterU_energy");
  declareContainerDoubleEventBranch("mehtool_closestclusterV_energy");

  // Difference in time between michel and cluster

  declareContainerDoubleEventBranch("mehtool_closestclusterX_time");
  declareContainerDoubleEventBranch("mehtool_closestclusterU_time");
  declareContainerDoubleEventBranch("mehtool_closestclusterV_time");

  //Want to know which end point of the michel is the cluster closest to. 0 = Endpoint info not available (not fitted michels or no match), 1 = Endpoint 1 match, 2, Endpoint 2 match

  declareContainerIntEventBranch("mehtool_closestclusterX_endpoint");
  declareContainerIntEventBranch("mehtool_closestclusterU_endpoint");
  declareContainerIntEventBranch("mehtool_closestclusterV_endpoint");


  //Want to know the number of planes between Pion cluster and Michel endpoint


    declareContainerDoubleEventBranch("mehtool_closestclusterX_zdist");
    declareContainerDoubleEventBranch("mehtool_closestclusterU_zdist");
    declareContainerDoubleEventBranch("mehtool_closestclusterV_zdist");

    declareContainerIntEventBranch("mehtool_closestclusterX_nclusz");
    declareContainerIntEventBranch("mehtool_closestclusterU_nclusz");
    declareContainerIntEventBranch("mehtool_closestclusterV_nclusz");

    declareContainerIntEventBranch("mehtool_nmichelsmatch");
    declareIntEventBranch("mehtool_nclustermatchmichel");

    declareContainerIntEventBranch("mehtool_Xclus_michelmatchindex");
    declareContainerIntEventBranch("mehtool_Uclus_michelmatchindex");
    declareContainerIntEventBranch("mehtool_Vclus_michelmatchindex");

    declareContainerIntEventBranch("mehtool_Xclus_clusterindex");
    declareContainerIntEventBranch("mehtool_Uclus_clusterindex");
    declareContainerIntEventBranch("mehtool_Vclus_clusterindex");

    declareContainerIntEventBranch("mehtool_michel_clusterindex");
    declareContainerIntEventBranch("mehtool_duplicate_michelindex"); //means the same cluster matched to two michels and this is the index of the second michel. I need to figure out how to map cluster index to michel index..

    declareContainerDoubleEventBranch("mehtool_closestclusterX_pos");
    declareContainerDoubleEventBranch("mehtool_closestclusterU_pos");
    declareContainerDoubleEventBranch("mehtool_closestclusterV_pos");
    declareContainerDoubleEventBranch("mehtool_closestclusterX_Z_pos");
    declareContainerDoubleEventBranch("mehtool_closestclusterV_Z_pos");
    declareContainerDoubleEventBranch("mehtool_closestclusterU_Z_pos");



    declareContainerDoubleEventBranch("mehtool_closestclusterX_clustime");
    declareContainerDoubleEventBranch("mehtool_closestclusterV_clustime");
    declareContainerDoubleEventBranch("mehtool_closestclusterU_clustime");

    declareContainerDoubleEventBranch("mehtool_matchedclusters_datafraction");
    declareContainerIntEventBranch( "mehtool_pion_primary_particle_trackID");
    declareContainerIntEventBranch("mehtool_true_pion_pdg");
    declareContainerDoubleEventBranch("mehtool_true_pion_x1vec");
    declareContainerDoubleEventBranch("mehtool_true_pion_y1vec");
    declareContainerDoubleEventBranch("mehtool_true_pion_z1vec");
    declareContainerDoubleEventBranch("mehtool_true_pion_x2vec");
    declareContainerDoubleEventBranch("mehtool_true_pion_y2vec");
    declareContainerDoubleEventBranch("mehtool_true_pion_z2vec");
    declareContainerIntEventBranch( "mehtool_pion_parent_PDG");
    declareContainerIntEventBranch( "mehtool_pion_from_decay");
    declareContainerIntEventBranch("mehtool_pion_parent_trackID");
    declareContainerDoubleEventBranch("mehtool_pion_truetime");

    declareContainerDoubleEventBranch("mehtool_michel_time");
    declareContainerDoubleEventBranch("mehtool_michel_energy");
    declareContainerIntEventBranch("mehtool_michel_Xclusters");
    declareContainerIntEventBranch("mehtool_michel_Uclusters");
    declareContainerIntEventBranch("mehtool_michel_Vclusters");
    declareContainerDoubleEventBranch("mehtool_michel_x1");
    declareContainerDoubleEventBranch("mehtool_michel_x2");
    declareContainerDoubleEventBranch("mehtool_michel_u1");
    declareContainerDoubleEventBranch("mehtool_michel_u2");
    declareContainerDoubleEventBranch("mehtool_michel_v1");
    declareContainerDoubleEventBranch("mehtool_michel_v2");
    declareContainerDoubleEventBranch("mehtool_michel_z1");
    declareContainerDoubleEventBranch("mehtool_michel_z2");

    declareContainerDoubleEventBranch("mehtool_michel_maxmeandiff");
    declareContainerIntEventBranch("mehtool_istrueMichel");
    declareContainerDoubleEventBranch("mehtool_michel_allmichelenergy");

    declareContainerIntEventBranch("mehtool_michel_fitPass");


    //Add Truth Michel information
    //-- Variables for Michel truth matching
    declareContainerIntEventBranch( "mehtool_primary_particle_trackID");
    declareContainerIntEventBranch("mehtool_true_michel_pdg");
    declareContainerDoubleEventBranch("mehtool_true_michel_x1vec");
    declareContainerDoubleEventBranch("mehtool_true_michel_y1vec");
    declareContainerDoubleEventBranch("mehtool_true_michel_z1vec");
    declareContainerDoubleEventBranch("mehtool_true_michel_x2vec");
    declareContainerDoubleEventBranch("mehtool_true_michel_y2vec");
    declareContainerDoubleEventBranch("mehtool_true_michel_z2vec");
    declareContainerIntEventBranch( "mehtool_michel_parent_PDG");
    declareContainerIntEventBranch( "mehtool_michel_from_decay");
    declareContainerIntEventBranch("mehtool_michel_parent_trackID");
    declareContainerDoubleEventBranch("mehtool_michel_truetime");


  //Add Truth Michel information
  //-- Variables for Michel truth matching
  declareContainerIntEventBranch( "has_michel_primary_particle_trackID");
  declareContainerIntEventBranch("true_michel_pdg");
  declareContainerDoubleEventBranch("true_michel_x1vec");
  declareContainerDoubleEventBranch("true_michel_y1vec");
  declareContainerDoubleEventBranch("true_michel_z1vec");
  declareContainerDoubleEventBranch("true_michel_x2vec");
  declareContainerDoubleEventBranch("true_michel_y2vec");
  declareContainerDoubleEventBranch("true_michel_z2vec");
  declareContainerIntEventBranch( "michel_parent_PDG");
  declareContainerIntEventBranch( "michel_from_decay");
  declareContainerIntEventBranch("michel_parent_trackID");
  //declareContainerIntEventBranch("michel_is_true_match");

  //! Event - Proton truth matcher
  declareDoubleEventBranch( "proton_track_length", -9999. );
  declareDoubleEventBranch( "proton_track_endx", -9999. );
  declareDoubleEventBranch( "proton_track_endy", -9999. );
  declareDoubleEventBranch( "proton_track_endz", -9999. );
  declareIntEventBranch("proton_prong_PDG", -1);
  declareIntEventBranch("proton_prong_traj_ID", -1);
  declareContainerDoubleEventBranch("proton_prong_4p", 4, -1.0);
  declareContainerDoubleEventBranch("proton_prong_tpos", 4, -1.0);

  //-----------------------------------------------------
  //! Neutrino CCQE Interaction Hypothesis branches
  //-----------------------------------------------------

  //! Neutrino Interaction - Muon
  declareDoubleBranch( m_hypMeths, "muon_theta",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "muon_E",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "muon_P",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "muon_T",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "muon_score",  -9999.0 );

  //! Neutrino Interaction - Primary Proton
  declareDoubleBranch( m_hypMeths, "proton_E_fromdEdx",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_P_fromdEdx",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_T_fromdEdx",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_theta_fromdEdx",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_calib_energy",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_score", -9999.0);
  declareDoubleBranch( m_hypMeths, "proton_score1", -9999.0);
  declareDoubleBranch( m_hypMeths, "proton_score2", -9999.0);



  /*




  declareContainerDoubleBranch( m_hypMeths, "protonE");

  declareDoubleEventBranch("proton_startPointX", -9999.0 );
  declareDoubleEventBranch("proton_startPointY", -9999.0 );
  declareDoubleEventBranch("proton_startPointZ", -9999.0 );
  declareDoubleEventBranch("proton_endPointX", -9999.0 );
  declareDoubleEventBranch("proton_endPointY", -9999.0 );
  declareDoubleEventBranch("proton_endPointZ", -9999.0 );
  declareDoubleEventBranch("proton_theta", -9999.0 );
  declareDoubleEventBranch("proton_thetaX", -9999.0 );
  declareDoubleEventBranch("proton_thetaY", -9999.0 );
  declareDoubleEventBranch("proton_phi", -9999.0 );
  declareDoubleEventBranch("proton_ekin", -9999.0 );
  declareDoubleEventBranch("proton_enu", -9999.0 );
  declareDoubleEventBranch("proton_q2", -9999.0 );
  declareDoubleEventBranch("proton_E", -9999.0 );
  declareDoubleEventBranch("proton_p", -9999.0 );
  declareDoubleEventBranch("proton_px", -9999.0 );
  declareDoubleEventBranch("proton_py", -9999.0 );
  declareDoubleEventBranch("proton_pz", -9999.0 );
  */

  declareDoubleBranch( m_hypMeths, "proton_startPointX", -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_startPointY", -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_startPointZ", -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_endPointX", -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_endPointY", -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_endPointZ", -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_theta", -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_thetaX", -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_thetaY", -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_phi", -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_ekin", -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_enu", -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_q2", -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_E", -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_p", -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_px", -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_py", -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_pz", -9999.0 );

  //! Neutrino Interaction - Secondary Protons
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_E_fromdEdx" );
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_P_fromdEdx" );
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_T_fromdEdx" );
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_theta_fromdEdx" );
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_T_fromCalo" );
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_proton_scores");
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_proton_scores1");
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_proton_scores2");

  //! Neutrino Interaction - Primary Pion
  declareDoubleBranch( m_hypMeths, "pion_score", -9999.0);
  declareDoubleBranch( m_hypMeths, "pion_score1", -9999.0);
  declareDoubleBranch( m_hypMeths, "pion_score2", -9999.0);

  //! Neutrino Interaction - Secondary Pions
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_pion_scores");
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_pion_scores1");
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_pion_scores2");

  //! Neutrino Interaction - Neutrino Energy
  declareDoubleBranch( m_hypMeths, "enu_muon",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "enu_proton",  -9999.0 );

  //! dEdXTool Variations to Primary Proton
  declareDoubleBranch( m_hypMeths, "proton_score1_Mass_biasUp",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_score1_Mass_biasDown",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_score1_BetheBloch_biasUp",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_score1_BetheBloch_biasDown",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_score1_MEU_biasUp",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_score1_MEU_biasDown",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_score1_Birks_bias",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_E_Mass_biasUp",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_E_Mass_biasDown",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_E_BetheBloch_biasUp",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_E_BetheBloch_biasDown",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_E_MEU_biasUp",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_E_MEU_biasDown",  -9999.0 );
  declareDoubleBranch( m_hypMeths, "proton_E_Birks_bias",  -9999.0 );

  //! dEdXTool Variations to Secondary Protons
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_score1_Mass_biasUp");
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_score1_Mass_biasDown");
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_score1_BetheBloch_biasUp");
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_score1_BetheBloch_biasDown");
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_score1_MEU_biasUp");
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_score1_MEU_biasDown");
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_score1_Birks_bias");
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_E_Mass_biasUp");
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_E_Mass_biasDown");
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_E_BetheBloch_biasUp");
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_E_BetheBloch_biasDown");
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_E_MEU_biasUp");
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_E_MEU_biasDown");
  declareContainerDoubleBranch( m_hypMeths, "sec_protons_E_Birks_bias");



  debug()<<"Exiting CCQENu::initialize() ....."<<endmsg;

  return sc;
}


//=============================================================================
// reconstructEvent()
//=============================================================================
StatusCode CCQENu::reconstructEvent( Minerva::PhysicsEvent *event, Minerva::GenMinInteraction* truth ) const {

  debug() << "Entering CCQENu::reconstructEvent() now ....." << endmsg;
  StatusCode sc;

  if( getDAQHeader()->isMCTrigger() ) {
    debug() << truthData() << " Truth Process Type " << truth->processType() << endmsg;
  }

  //-----------------------------------------------------------------------------------
  //! Skip events with a truth pointer whose processType is insufficiently defined
  //! The Truth pointer will be NULL while processing data
  //-----------------------------------------------------------------------------------
  if( truth && ( truth->processType()==Minerva::GenMinInteraction::kNoProcess || truth->processType()==Minerva::GenMinInteraction::kUnknownProcess ) ) {
    debug() << "Truth pointer points to an insufficiently defined process - no sense in proceeding !" << endmsg;
    return StatusCode::SUCCESS;
  }

  //----------------------------------------------------------------------
  //! CUT : Does this event carry a reco object with a BadObject flag?
  //----------------------------------------------------------------------
  if( event->filtertaglist()->isFilterTagTrue( AnaFilterTags::BadObject() ) ) {
    error() << "Found an event flagged with a BadObject! Refusing to analyze ..." << endmsg;
    counter("REFUSED_A_BADOBJECT") += 1;
    return StatusCode::SUCCESS; // Things are bad, but we didn't crash.
  }

  //--------------------------------------------------------------------
  //! NOTE: WE DO NOT CUT ON INTERACTION VERTICES ANYMORE. IF YOU WANT
  //! THE ANALYSIS TO BEHAVE AS BEFORE YOU NEED TO CUT ON HAS_INTERACTION_VERTEX
  //--------------------------------------------------------------------


  //count vertices of the start variety used and unused
  VertexVect unused_vtx = event->select<Minerva::Vertex>( "Unused", "StartPoint" );
  VertexVect used_vtx = event->select<Minerva::Vertex>( "Used", "StartPoint" );

  event->setIntData("event_unused_start_vertices",unused_vtx.size());
  event->setIntData("event_used_start_vertices",used_vtx.size());
  //get the number of minos matches in the event
  //get primary prongs. Get output of stubs+matches
  int count_matches = 0;
  std::vector<double> allvtxtimes;
  std::vector<double> allvtxtimes_minos_match;
  std::vector<int> allvtxfv_minos_match;
  for( Minerva::VertexVect::iterator itvtx=used_vtx.begin(); itvtx!=used_vtx.end(); ++itvtx ) {
       debug() << "  Vertex Position          = " << (*itvtx)->position() << endmsg;
       allvtxtimes.push_back((*itvtx)->getTime());
       ProngVect primProngs; ProngVect unattachedProngs;
       m_objectAssociator->getProngs_fromSourceVertex( primProngs, unattachedProngs, *itvtx );

       ProngVect minosTrackProngs, minosStubProngs;
       minosTrackProngs.clear();
       minosStubProngs.clear();

       int isFV = m_minCoordSysTool->inFiducial((*itvtx)->position().X(),(*itvtx)->position().Y(),(*itvtx)->position().Z(),850.0,6127,8183)?1:0;


       for( ProngVect::const_iterator itProng = primProngs.begin(); itProng != primProngs.end(); ++itProng ) {
	 if( (*itProng)->MinosTrack() )     minosTrackProngs.push_back( *itProng );
	 else if( (*itProng)->MinosStub() ) minosStubProngs.push_back(  *itProng );
       }


       if( !minosTrackProngs.empty() ) {
	 allvtxtimes_minos_match.push_back((*itvtx)->getTime());
	 allvtxfv_minos_match.push_back(isFV);
         debug() << " Found a vertex with " << minosTrackProngs.size() << " MinosTrack Prong(s)..." << endmsg;
         ++count_matches;

       } else if( !minosStubProngs.empty() ) {
 	 allvtxtimes_minos_match.push_back((*itvtx)->getTime());
	 allvtxfv_minos_match.push_back(isFV);
         debug() << " Found a MinosStub Prong..." << endmsg;
         ++count_matches;

       } // end check for MinosTrack/Stub prongs
  } //end loop over "used" vertices. There never seem to be unused vertices

  event->setContainerDoubleData("all_event_start_vertex_time", allvtxtimes);
  event->setContainerDoubleData("all_event_start_vertex_time_minos_match",allvtxtimes_minos_match);
  event->setContainerIntData("all_event_start_vertex_fv_minos_match",allvtxfv_minos_match);
  event->setIntData("n_minos_matches",count_matches);


  //---------------------------------------------------
  //! Let's Get all slice hits and energies
  //---------------------------------------------------
  std::cout << "Doing slice variables" << std::endl;
  Minerva::IDClusterVect sliceclusters = event->select<Minerva::IDCluster>("All","!LowActivity&!XTalkCandidate");
  std::vector<double> slice_hit_time;
  std::vector<double> slice_hit_energy;
  int slice_n_hits = 0;
  for( Minerva::IDClusterVect::iterator itsc=sliceclusters.begin(); itsc!=sliceclusters.end(); itsc++ ) {
    SmartRefVector<Minerva::IDDigit> digits = (*itsc)->digits();
    for ( SmartRefVector<Minerva::IDDigit>::const_iterator itDig = digits.begin(); itDig != digits.end(); ++itDig ) {
      slice_hit_time.push_back((*itDig)->time());
      slice_hit_energy.push_back((*itDig)->normEnergy());
      slice_n_hits++;
    }
  }

  event->setContainerDoubleData("slice_hit_time",slice_hit_time);
  event->setContainerDoubleData("slice_hit_energy",slice_hit_energy);
  event->setIntData("slice_n_hits",slice_n_hits);

  std::cout << "This slice has " << slice_n_hits << " hits" << std::endl;
  //--------------------------------------------------
  //! CUT: Check if there is an interaction vertex
  //--------------------------------------------------
  counter("has_vertex") += event->hasInteractionVertex();
  if( !event->hasInteractionVertex() ){
    debug() << "Event doesn't have an interaction vertex" << endmsg;
    std::cout << "NO INTERACTION VERTEX" << std::endl;
    event->setIntData("has_interaction_vertex",0);

    //Check if at least one start vertex is in FV. Don't save rock muons.
    int fv_count = 0;
    for(int fv_e=0;fv_e<allvtxfv_minos_match.size();fv_e++){
      fv_count+=allvtxfv_minos_match[fv_e];
    }
    if(fv_count==0) return StatusCode::SUCCESS; //none of the minos matches orginate from vertices in the FV or there were no minos matches. Both cases we don't care about.


    markEvent( event );
    //-------------------------------
    //! Interpret event
    //-------------------------------
    std::vector<Minerva::NeutrinoInt*> nuInt;
    interpretEvent( event, truth, nuInt );

    //---------------------------------------------------
    //! Add interaction hypothesis to physics event
    //---------------------------------------------------
    sc = addInteractionHyp( event, nuInt );

    return sc;
  }
  else{
    event->setIntData("has_interaction_vertex",1);
  }

  //---------------------------------------------------------------
  //! Get the interaction vertex
  //! If you can't get the vertex, tag the event as a BadObject
  //---------------------------------------------------------------
  SmartRef< Minerva::Vertex > vertexOfPhysEvent = (event->interactionVertex()).target();
  if( !vertexOfPhysEvent ) {
    bool pass = true; std::string tag = "BadObject";
    event->filtertaglist()->addFilterTag(tag,pass);
    event->setIntData("NullVertex",1);
    error() << "This vertex is NULL! Flag this event as bad!" << endmsg;
    return StatusCode::SUCCESS;
  }

  //---------------------------------------------------------------------------
  //! CUT: Check if vertex is inside fiducial volume
  //! according to SignalApothem, SignalUpstreamZ, and SignalDownstreamZ.
  //---------------------------------------------------------------------------
  bool is_fiducial = eventVertexIsFiducial( event );
  if( truth ) {
    truth->filtertaglist()->setOrAddFilterTag( "reco_fiducial", is_fiducial );
    truth->setIntData( "reco_is_fiducial", (int)is_fiducial );
  }
  counter("is_fiducial") += is_fiducial;
  if( !is_fiducial ) {
    debug() << "Event vertex is outside fiducial volume" << endmsg;
    return StatusCode::SUCCESS;
  }

  //-----------------------------------------------------------------
  //! Look at muon properties (charge, score, MINOS-match etc.)
  //! CUT: Skip if no muons present in event
  //-----------------------------------------------------------------
  SmartRef<Minerva::Prong> muonProng;
  SmartRef<Minerva::Particle> muonPart;
  bool is_minos_track = false, is_minos_stub = false;

  bool has_muon = MuonUtils->findMuonProng( event, muonProng, muonPart );
  if( !has_muon ){
    debug() << "There is no muon in the event." << endmsg;
    return StatusCode::SUCCESS;
  }

  //-----------------------------------------------------
  //! Use virtual bool function truthIsPlausible( ) to
  //! look for plausible muon
  //-----------------------------------------------------
  muonProng->setIntData( "look_for_plausibility", 1 );

  //--------------------------------------
  //! CUT: Skip events with no muon
  //--------------------------------------
  if( truth ) {
    truth->filtertaglist()->setOrAddFilterTag( "reco_minos_match", has_muon );
    truth->setIntData( "reco_is_minos_match", (int)has_muon );
  }
  counter("has_muon")+=has_muon;

  //--------------------------------------
  //! CUT: Skip muons with no charge
  //--------------------------------------
  int muon_charge = 0;
  MuonUtils->muonCharge( muonProng, muon_charge, m_qOverpChargeCut );
  if( truth ) {
    truth->filtertaglist()->setOrAddFilterTag( "reco_muon_charge", ( muon_charge!=0 ) );
    truth->setIntData( "reco_has_muon_charge", (int)( muon_charge!=0 ) );
  }
  counter("muon_charge") += ( muon_charge!=0 );
  if( muon_charge==0 ){
    debug() << "Muon doesn't have charge" << endmsg;
    return StatusCode::SUCCESS;
  }

  //--------------------------------------------------
  //! CUT: Only keep muons with a certain score
  //! Find out if muons are MINOS-matched or not
  //--------------------------------------------------
  debug() << "Muon Particle Score: " << muonPart->score() << endmsg;
  if (muonPart->score() >= m_minMuonScore) {
    muonProng->filtertaglist()->setOrAddFilterTag( AnaFilterTags::PrimaryMuon(), true );

    if (muonProng->MinosTrack()) is_minos_track = true;
    if (muonProng->MinosStub())  is_minos_stub  = true;
    if (is_minos_stub && is_minos_track) counter("MuonHasMinosStubAndTrack")++;
    if (!is_minos_stub && !is_minos_track) counter("MuonIsNotMinosMatched")++;

    event->filtertaglist()->setOrAddFilterTag("isMinosMatchTrack", is_minos_track );
    event->filtertaglist()->setOrAddFilterTag("isMinosMatchStub", is_minos_stub );
    if (truth) {
      truth->filtertaglist()->setOrAddFilterTag( "reco_isMinosMatchTrack", is_minos_track );
      truth->filtertaglist()->setOrAddFilterTag( "reco_isMinosMatchStub", is_minos_stub );
      truth->setIntData("reco_muon_is_minos_match_track", (int)is_minos_track);
      truth->setIntData("reco_muon_is_minos_match_stub", (int)is_minos_stub);
    }
  } else {
    debug()<<"Muon prong does not pass score cut"<<endmsg;
    return StatusCode::SUCCESS;
  }

  //--------------------------------------------------------------------------------------------------------------------
  // Find chi2 of MINERvA part (not MINOS) of muon track (for comparisons with J. Wolcott's chiPerDoF for electrons)
  //--------------------------------------------------------------------------------------------------------------------
  SmartRef<Minerva::Track> muonTrack;
  bool foundMinervaPart = findLongestMinervaTrack( muonProng, muonTrack );
  if( foundMinervaPart && muonTrack->nNodes() ) {
    verbose() <<"Chi2 of the MINERvA part of the muon track is " << muonTrack->chi2PerDoF() <<" Nodes: "<< muonTrack->nNodes() << endmsg;
    event->setDoubleData( "muon_minerva_trk_chi2PerDoF", muonTrack->chi2PerDoF() );
  }

  //Get muontime
  double muonTime = m_recoObjTimeTool->trackVertexTime(muonProng->minervaTracks()[0]);
  //---------------------------------------------------
  //! Store all node angles to fix angular biases due to hadronic energy near the vertex (docdb 12047)
  //---------------------------------------------------
  std::vector<double> thetaNodes, thetaXNodes, thetaYNodes;
  for(uint i=0; i<muonTrack->nNodes(); i++){
    const Minerva::Node* node=muonTrack->nodes()[i];
    double ax=node->state().ax();
    double ay=node->state().ay();
    double theta=m_minCoordSysTool->thetaWRTBeam( ax, ay, 1 );
    double thetaX=m_minCoordSysTool->thetaXWRTBeam( ax, ay, 1 );
    double thetaY=m_minCoordSysTool->thetaYWRTBeam( ay, 1 );
    thetaNodes.push_back(theta);
    thetaXNodes.push_back(thetaX);
    thetaYNodes.push_back(thetaY);
  }

  event->setContainerDoubleData("muon_theta_allNodes", thetaNodes);
  event->setContainerDoubleData("muon_thetaX_allNodes", thetaXNodes);
  event->setContainerDoubleData("muon_thetaY_allNodes", thetaYNodes);

  //----------------------------------------------------------------------------------------
  //! Add PID to prongs not associated with the interaction vertex, but are in time
  //----------------------------------------------------------------------------------------

  Minerva::ProngVect extraProngs = m_minModDepCCQERecoUtils->getInTimeTrackPID(event,muonTime);
  std::vector<double> extraPID;
  std::vector<Minerva::Particle::ID> particleHypotheses;
  particleHypotheses.push_back(Minerva::Particle::Pion);
  particleHypotheses.push_back(Minerva::Particle::Proton);

  for( Minerva::ProngVect::iterator itProng = extraProngs.begin(); itProng!= extraProngs.end();++itProng){
    debug()<<"Make particles from extra prongs"<<endmsg;
    IParticleMakerTool::NameAliasListType toolsToUse;
    toolsToUse.push_back( std::make_pair("dEdXTool", "dEdXTool") );  // name, alias pair

    StatusCode sc_dEdX = m_particleMaker->makeParticles( *itProng, particleHypotheses, toolsToUse );
    if (!sc_dEdX) {
      debug()<<"Could not make particles in extra prong!"<<endmsg;
    }
  }//End loop over prongs to create particles
  Minerva::ProngVect extrasecondaryProtonProngs;
  SmartRef<Minerva::Prong> extraprotonProng;
  SmartRef<Minerva::Particle> extraprotonPart;
  bool hasextraProton = getProtonProngs( extraProngs, extrasecondaryProtonProngs, extraprotonProng, extraprotonPart );
  //now get PID scores for each prong (only save the equivalent of score1 which is used for protons associated with the primary vtx
  //TODO: add systematic variations into the flow....
  if(hasextraProton){
    extraPID.push_back(extraprotonPart->getDoubleData(ParticleExtraDataDefs::dEdXScore1()));
    for(Minerva::ProngVect::iterator itProng = extrasecondaryProtonProngs.begin(); itProng!= extrasecondaryProtonProngs.end();++itProng){
      SmartRef<Minerva::Particle> extraprotonpart = (*itProng)->bestParticle();
      extraPID.push_back(extraprotonpart->getDoubleData(ParticleExtraDataDefs::dEdXScore1()));
    }
  }//end if has protons
  event->setContainerDoubleData("event_extra_track_PID",extraPID);

  //-------------------------------------------------------------------------------------
  //! Create vertex-anchored short track Prongs, refit vertex
  //! Does it make sense to refit the Vtx reliably with such short tracks ? Not sure
  //-------------------------------------------------------------------------------------
  int n_anchored_long_trk_prongs = event->primaryProngs().size() - 1;
  event->setIntData("n_anchored_long_trk_prongs", n_anchored_long_trk_prongs );

  //-------------------------------------------------------------------------------
  //! Do you want to obtain the vector of ID Clusters from the PhysEvent first ?
  //-------------------------------------------------------------------------------
  Minerva::IDClusterVect idClusterVector = m_minModDepCCQERecoUtils->getInTimeAnalyzableIDClusters( event, muonProng );
  if( !idClusterVector.size() ) {
    debug() << "Size of vector containing ID Clusters is " << idClusterVector.size() << " - nothing to make short Tracks from !" << endmsg;
    return StatusCode::SUCCESS;
  }

  //-------------------------------------------------------------------------------------------
  //! A vector for holding all the newly made short tracks (from the clusters near the Vtx)
  //-------------------------------------------------------------------------------------------
  std::vector<Minerva::Track*> *deShortTrackVector = new std::vector<Minerva::Track*>;

  //----------------------------------------------------------------------------------------------------
  //! Make short tracks either with the VertexAnchoredShortTracker or VertexEnergyStudyTool or both
  //----------------------------------------------------------------------------------------------------
  if( m_makeShortTracks ) {
    sc = m_minModDepCCQERecoUtils->runShortTrackers( event, deShortTrackVector, m_runVertexAnchoredShortTracker, m_runVertexEnergyStudyTool );
    if( sc.isFailure() ) return sc;
  }

  //---------------------------------------------------------------------
  //! Delete the vector created, don't need it anymore
  //! Do you need to delete the track pointers (commented out line) ?
  //---------------------------------------------------------------------
  // for (std::vector<Minerva::Track*>::iterator itTrk =deShortTrackVector->begin(); itTrk != deShortTrackVector->end(); ++itTrk) { delete *itTrk; }
  deShortTrackVector->clear();
  delete deShortTrackVector;

  int n_anchored_short_trk_prongs = event->primaryProngs().size() - n_anchored_long_trk_prongs - 1;
  event->setIntData("n_anchored_short_trk_prongs", n_anchored_short_trk_prongs);

  //---------------------------------------------------------------------
  //! CUT: check if the number of outgoing tracks == 2 (multiplicity)
  //---------------------------------------------------------------------
  int multiplicity = vertexOfPhysEvent->getNOutgoingTracks();
  event->setIntData( "multiplicity",  multiplicity );

  debug()<<"Multiplicity = "<<multiplicity<<endmsg;
  SmartRefVector<Minerva::Track> Tracks = vertexOfPhysEvent->getOutgoingTracks();
  debug()<<"Outgoing tracks size =" << Tracks.size() << endmsg;
  for(SmartRefVector<Minerva::Track>::iterator itTrack = Tracks.begin(); itTrack != Tracks.end() ; ++itTrack) {
    verbose() << "Track address = "<< *itTrack << " Track Pat Rec History = " << (*itTrack)->patRecHistory()
	      << " Track type = " << (*itTrack)->type() << " Track nodes = " << (*itTrack)->nNodes()
	      << " Track VisE = " << (*itTrack)->visibleEnergy() << " Track theta = " << (*itTrack)->theta()
	      << " Track phi = " << (*itTrack)->phi() << " Track first cluster time = " << (*itTrack)->firstNode()->idcluster()->time()
	      << " Track time = " << (*itTrack)->time() << endmsg;
  }

  //---------------------------------------------------
  //! Start using dEdX Tool
  //---------------------------------------------------
  debug() <<"Making particle hypotheses" << endmsg;
  ProngVect hadronProngs;

  //--------------------------------------------
  //! Create Particles and get hadronProngs
  //--------------------------------------------
  if( !createParticles( event, hadronProngs ) )
    debug()<<"Could not create Particles"<<endmsg;

  //---------------------------------------------------
  //! Look and tag michels
  //---------------------------------------------------
  bool hasMichels = tagMichels( event, truth );
  event->filtertaglist()->setOrAddFilterTag("hasNoMichelElectrons", !hasMichels );
  debug() << "Finished tagging Michels " << endmsg;

  //---------------------------------------------------
  //! Look and Tag with the ImprovedMichelTool
  //---------------------------------------------------
  bool hasImprovedMichels = ImprovedtagMichels( event, truth );
  event->filtertaglist()->setOrAddFilterTag("hasNoImprovedMichelElectrons", !hasImprovedMichels );
  debug() << "Finished tagging Improved Michels " << endmsg;
  //---------------------------------------------------
  //! Let's count vertex types
  //---------------------------------------------------
  std::vector<int> vtx_types_all;
  std::vector<int> vtx_types_intime;
  std::vector<double> vtx_time_diff;

  const SmartRefVector<Minerva::Vertex> tmp_vertices = event->select<Minerva::Vertex>();
  for ( SmartRefVector<Minerva::Vertex>::const_iterator itVtx = tmp_vertices.begin(); itVtx != tmp_vertices.end(); ++itVtx ) {
    double vertex_time = (*itVtx)->getTime();//m_recoObjTimeTool->trackVertexTime((*itVtx));
    double time_diff = vertex_time - muonTime;
    vtx_time_diff.push_back(time_diff);
    if( time_diff > m_lowerTimeWindow && time_diff < m_upperTimeWindow )vtx_types_intime.push_back((*itVtx)->type());
    vtx_types_all.push_back((*itVtx)->type());
  }
  event->setContainerIntData("event_vertex_types", vtx_types_all);
  event->setContainerIntData("event_in_time_vertex_types", vtx_types_intime);
  event->setContainerDoubleData("event_vertex_time_diff", vtx_time_diff);
  //-----------------------------------------------------
  //! Let's count tracks
  //-----------------------------------------------------
  std::vector<double> track_energy_all;
  std::vector<double> track_energy_intime;
  std::vector<double> track_time_diff;
  std::vector<double >track_hit_time;
  std::vector<double >track_hit_energy;
  std::vector<int > track_nhits;
  const SmartRefVector<Minerva::Track> tmp_tracks = event->select<Minerva::Track>();
  for ( SmartRefVector<Minerva::Track>::const_iterator itTrack = tmp_tracks.begin(); itTrack != tmp_tracks.end(); ++itTrack ) {
    double track_time = m_recoObjTimeTool->trackVertexTime((*itTrack));
    double time_diff =  track_time - muonTime;
    track_time_diff.push_back(time_diff);
    if( time_diff > m_lowerTimeWindow && time_diff < m_upperTimeWindow )track_energy_intime.push_back((*itTrack)->type());
    track_energy_all.push_back((*itTrack)->type());

    //now lets had track by track hit time and charge information
    int n_hits = 0;
    //get clusters to get digits
    std::vector<Minerva::IDCluster*> clusters = (*itTrack)->idclusters();
    for(uint i=0;i<clusters.size();i++){
      SmartRefVector<Minerva::IDDigit> digits = clusters[i]->digits();
      for ( SmartRefVector<Minerva::IDDigit>::const_iterator itDig = digits.begin(); itDig != digits.end(); ++itDig ) {
	track_hit_time.push_back((*itDig)->time());
	track_hit_energy.push_back((*itDig)->normEnergy());
	n_hits++;
      }
    }//end cluster
    track_nhits.push_back(n_hits);
  }//end tracks
  event->setContainerDoubleData("event_tracks_energy",track_energy_all);
  event->setContainerDoubleData("event_in_time_tracks_energy",track_energy_intime);
  event->setContainerDoubleData("event_track_time_diff", track_time_diff);
  event->setContainerDoubleData("event_track_hit_time", track_hit_time);
  event->setContainerDoubleData("event_track_hit_energy", track_hit_energy);
  event->setContainerIntData("event_track_nhits",track_nhits);


  //-------------------------------------------------------
  //! Let's Get recoil values for various windows
  //-------------------------------------------------------
  std::cout << "Doing recoil variables" << std::endl;
  std::vector<double> recoil_summed_energy;
  std::vector<double> recoil_data_fraction;
  std::vector<int> recoil_lower_time_limit;
  std::vector<int> recoil_upper_time_limit;
  Minerva::IDClusterVect  muonClusters = muonProng->getAllIDClusters();
  Minerva::IDClusterVect mod_slice_clusters;
  for( Minerva::IDClusterVect::iterator itsc=sliceclusters.begin(); itsc!=sliceclusters.end(); itsc++ ) {
    bool nonMuonCluster = true;
    for( Minerva::IDClusterVect::iterator muit = muonClusters.begin(); muit!=muonClusters.end();muit++){
      if((*muit)==(*itsc)){
	nonMuonCluster = false;
	break;
      }
    }
    if(nonMuonCluster) mod_slice_clusters.push_back(*itsc);
  }

  for(int low=-20;low!=0;low++){
    for(int high=35;high!=0;high--){
      Minerva::IDClusterVect selectedclusters;
      for( Minerva::IDClusterVect::iterator itsc=mod_slice_clusters.begin(); itsc!=mod_slice_clusters.end(); itsc++ ) {
	double time_diff = (*itsc)->time()-muonTime;
	if(time_diff>low && time_diff <high){
	  selectedclusters.push_back(*itsc);
	}
      }
      std::vector<const Minerva::IDCluster*> idclusters;
      idclusters.insert(idclusters.begin(), selectedclusters.begin(), selectedclusters.end());
      if(truth)recoil_data_fraction.push_back(TruthMatcher->getDataFraction(idclusters));
      else recoil_data_fraction.push_back(-1);
      //now apply constants
      double rec_energy = m_caloUtils->applyCalConsts( selectedclusters, "Default", false );
      //now store
      recoil_summed_energy.push_back(rec_energy);
      recoil_lower_time_limit.push_back(low);
      recoil_upper_time_limit.push_back(high);

    }
  }
  //now store
  event->setContainerDoubleData("recoil_summed_energy",recoil_summed_energy);
  event->setContainerIntData("recoil_lower_time_limit",recoil_lower_time_limit);
  event->setContainerIntData("recoil_upper_time_limit",recoil_upper_time_limit);
  event->setContainerDoubleData("recoil_data_fraction",recoil_data_fraction);


  //----------------------------------------------------------------
  //! Get a single proton coming out from the interaction vertex
  //! Now, let's look for the most energetic proton...
  //----------------------------------------------------------------
  std::cout << "On to protons " << std::endl;
  debug()<<"Looking for a proton"<<endmsg;
  Minerva::ProngVect secondaryProtonProngs;
  SmartRef<Minerva::Prong> protonProng;
  SmartRef<Minerva::Particle> protonPart;

  bool hasProton = getProtonProngs( hadronProngs, secondaryProtonProngs, protonProng, protonPart );
  event->filtertaglist()->setOrAddFilterTag("hasProton", hasProton );
  event->setIntData("has_proton",hasProton);
  if( hasProton ) {
    debug()<<"A proton was found"<<endmsg;
    counter("has_Proton")+=1;
    if( truth ) tagProtonProngTruth( event, protonProng );
  }
  debug() <<"Number of secondary proton prongs = "<< secondaryProtonProngs.size() << endmsg;

  //----------------------------------------------------
  // Assigning vectors for storing info from clusters
  // found at the end of the proton track
  //----------------------------------------------------
  std::vector<int> clustersFoundAtEndOfProtonProng;
  std::vector<double> maxDistanceClusterFromEndOfProtonProng;
  std::vector<int> numOfClustersAtEndOfProtonProng;
  std::vector<double> visEnergyOfClustersAtEndOfProtonProng;
  std::vector<double> calibEnergyOfClustersAtEndOfProtonProng;

  if( hasProton ) {
    //Make a Cone at the end of the proton track
    bool foundClusters = false;
    double max_cluster_distance = -9999.;
    Minerva::IDClusterVect idClustersInsideCone;
    double totalVisEAtProtonTrackEnd = 0;
    sc = m_minModDepCCQERecoUtils->makeConeAtEndProtonTrack( event, protonProng, muonProng, foundClusters, max_cluster_distance, idClustersInsideCone, m_fillTruthTG4ProtonCone );

    verbose() << "Number of clusters inside cone in CCQENu.cpp (hasProton=true) " << idClustersInsideCone.size() << endmsg;
    verbose() << "Value of foundClusters (hasProton=true) " << foundClusters << endmsg;

    //----------------------------------------------------------------------------------
    // Find total visible energy of clusters present at end of Primary Proton track
    //----------------------------------------------------------------------------------
    for( Minerva::IDClusterVect::iterator itClust = idClustersInsideCone.begin(); itClust != idClustersInsideCone.end(); ++itClust ) {
      totalVisEAtProtonTrackEnd += (*itClust)->energy();
    }

    //-----------------------------------------------------------------------------------
    // Find total calibrated energy of clusters present at end of Primary Proton track
    //-----------------------------------------------------------------------------------
    double calibEAtProtonTrackEnd = m_caloUtils->applyCalConsts( idClustersInsideCone, "Default", false );

    //-------------------------------------------
    //Storing variables for the Primary Proton
    //-------------------------------------------
    clustersFoundAtEndOfProtonProng.push_back( (int)foundClusters );
    maxDistanceClusterFromEndOfProtonProng.push_back( max_cluster_distance );
    numOfClustersAtEndOfProtonProng.push_back( idClustersInsideCone.size() );
    visEnergyOfClustersAtEndOfProtonProng.push_back( totalVisEAtProtonTrackEnd );
    calibEnergyOfClustersAtEndOfProtonProng.push_back( calibEAtProtonTrackEnd );

    //-------------------------------------
    // Fill Primary Proton track length
    //-------------------------------------
    SmartRef<Minerva::Vertex> BackVertex;
    m_objectAssociator->getVertex_fromTrackBack( BackVertex, protonProng->minervaTracks()[0] );
    double protonTrackLength = -9999.;
    if( BackVertex ) {
      const Gaudi::XYZPoint protonTrackEndPos = BackVertex->position();
      protonTrackLength = m_mathTool->distanceBetween( vertexOfPhysEvent->position(), protonTrackEndPos );
      event->setDoubleData("proton_track_length", protonTrackLength);
      event->setDoubleData("proton_track_endx", protonTrackEndPos.x());
      event->setDoubleData("proton_track_endy", protonTrackEndPos.y());
      event->setDoubleData("proton_track_endz", protonTrackEndPos.z());
    }

    //----------------------------------------------------
    // Color the clusters belonging to the cone
    //----------------------------------------------------
    for( Minerva::IDClusterVect::iterator itClust = idClustersInsideCone.begin(); itClust != idClustersInsideCone.end(); ++itClust ) {
      if( 0 <= m_coneEnergyColor ) m_hitTaggerTool->applyColorTag( *itClust, m_coneEnergyColor );
    }

  } //End of if condition for hasProton

  if( secondaryProtonProngs.size()>0 ) {
    debug() << "Secondary proton(s) found" << endmsg;
    for( ProngVect::iterator secProtonProng = secondaryProtonProngs.begin(); secProtonProng != secondaryProtonProngs.end(); ++secProtonProng ) {
      bool foundClusters = false;
      double max_cluster_distance = -9999.;
      Minerva::IDClusterVect idClustersInsideCone;
      double totalVisEAtProtonTrackEnd = 0;
      sc = m_minModDepCCQERecoUtils->makeConeAtEndProtonTrack( event, *secProtonProng, muonProng, foundClusters, max_cluster_distance, idClustersInsideCone, false );

      verbose() << "Number of clusters inside cone in CCQENu.cpp (secondaryProtonProngs.size()>0) " << idClustersInsideCone.size() << endmsg;
      verbose() << "Value of foundClusters (secondaryProtonProngs.size()>0) " << foundClusters << endmsg;

      //-----------------------------------------------------------------------------------
      // Find total visible energy of clusters present at end of Secondary Proton track
      //-----------------------------------------------------------------------------------
      for( Minerva::IDClusterVect::iterator itClust = idClustersInsideCone.begin(); itClust != idClustersInsideCone.end(); ++itClust ) {
	totalVisEAtProtonTrackEnd += (*itClust)->energy();
      }

      //-------------------------------------------------------------------------------------
      // Find total calibrated energy of clusters present at end of Secondary Proton track
      //-------------------------------------------------------------------------------------
      double calibEAtProtonTrackEnd = m_caloUtils->applyCalConsts( idClustersInsideCone, "Default", false );

      //---------------------------------------------
      //Storing variables for each Secondary Proton
      //---------------------------------------------
      clustersFoundAtEndOfProtonProng.push_back( (int)foundClusters );
      maxDistanceClusterFromEndOfProtonProng.push_back( max_cluster_distance );
      numOfClustersAtEndOfProtonProng.push_back( idClustersInsideCone.size() );
      visEnergyOfClustersAtEndOfProtonProng.push_back( totalVisEAtProtonTrackEnd );
      calibEnergyOfClustersAtEndOfProtonProng.push_back( calibEAtProtonTrackEnd );

      //----------------------------------------------------
      // Color the clusters belonging to the cone
      //----------------------------------------------------
      for( Minerva::IDClusterVect::iterator itClust = idClustersInsideCone.begin(); itClust != idClustersInsideCone.end(); ++itClust ) {
	if( 0 <= m_coneEnergyColor ) m_hitTaggerTool->applyColorTag( *itClust, m_coneEnergyColor );
      }
    } //End of for loop over secondaryProtonProngs
  } //End of if condition for secondaryProtonProngs

  //---------------------------------------------------------------
  //Storing variables for Primary+Secondary Protons in the event
  //---------------------------------------------------------------
  event->setContainerIntData("clusters_found_at_end_proton_prong", clustersFoundAtEndOfProtonProng);
  event->setContainerDoubleData("clusters_found_at_end_proton_prong_max_distance", maxDistanceClusterFromEndOfProtonProng);
  event->setContainerIntData("number_clusters_at_end_proton_prong", numOfClustersAtEndOfProtonProng);
  event->setContainerDoubleData("visE_clusters_at_end_proton_prong", visEnergyOfClustersAtEndOfProtonProng);
  event->setContainerDoubleData("calibE_clusters_at_end_proton_prong", calibEnergyOfClustersAtEndOfProtonProng);


  //----------------------------------------------------------------------------------------------------------------
  //! Blobbing Stuff
  //! JO has chosen to make VertexBlobProngs first, then add EM Blobs to MuonProng, then make IsoBlobProngs
  //! Reason for this is to pick out the recoil "near the Vertex" first, attach "muon-related brems/deltas"
  //! to the MuonProng second, then determine the "non-Vertex" recoil.
  //! Kenyi - please let me know if you disagree with this !
  //----------------------------------------------------------------------------------------------------------------

  //----------------------------------------------------------------------------------------------------
  //! Create Vertex Blob Prongs
  //! User can choose to make VtxBlobProngs either "Filament Style" or "Multiple Radii Style"
  // V.V.I. - The vector of clusters 'idClusterVector' contains clusters "in time" with the muon
  // V.V.I. - Is this okay ? What if there is an out-of-time overlay activity right near the vertex
  // V.V.I. - INVESTIGATE !
  //----------------------------------------------------------------------------------------------------

  // Minerva::ProngVect newVtxBlobProngs;
  // if( (RecoilUtils->createVtxBlobProngs( event, newVtxBlobProngs )).isFailure() )
  // return StatusCode::FAILURE;

  debug() << "Creating vertex blob prongs" << endmsg;
  std::vector<Minerva::Prong*> *newVtxBlobProngs = new std::vector<Minerva::Prong*>;
  if( m_makeFilamentStyleVtxBlobProngs ) {
    sc = m_primaryBlobProngTool->makeFilamentStyleVtxBlobProngs( event, idClusterVector, vertexOfPhysEvent,
								 m_maxSearchDistance, m_maxStartingDistance, m_maxAllowedSearchGap,
								 m_maxSeparationBlobVertex, newVtxBlobProngs );

  } else if( m_makeMultipleRadiiStyleVtxBlobProngs ) {
    sc = m_primaryBlobProngTool->makeMultipleRadiiStyleVtxBlobProngs( event, idClusterVector, vertexOfPhysEvent,
								      m_searchStepSize, m_numSearchRadii,
								      m_maxSeparationBlobVertex, newVtxBlobProngs );

  } else {
    debug() << "You have not specified a preference for making VtxBlobProngs, please specify one if you would like Vertex Blob Prongs !" << endmsg;
  }

  if( sc.isFailure() ) return sc;

  debug() << "Found " << newVtxBlobProngs->size() << " new Vertex Blob Prongs ....." << endmsg;

  //-----------------------------------------------------------------------
  //! You can add other conditions here, for examining the VtxBlobProngs
  //! before you start adding them to the evtMgr, user has control !
  //-----------------------------------------------------------------------
  if( newVtxBlobProngs->size() ) addObject( event, *newVtxBlobProngs );

  //---------------------------------------------------------------
  //! If there are Vertex Prongs, always promote them to primary
  //! V.V.I.- INVESTIGATE WHY THIS IS CAUSING CONFUSION
  //---------------------------------------------------------------
  /*Comment this part temporarily
  for( std::vector<Minerva::Prong*>::iterator p=newVtxBlobProngs->begin(); p!=newVtxBlobProngs->end(); ++p ) {
    event->promoteProngToPrimary( *p );
  }
  */

  //-----------------------------------------------------------------
  //! Color the clusters belonging to the Vertex Blob Prong
  //-----------------------------------------------------------------
  for( std::vector<Minerva::Prong*>::iterator itProng =newVtxBlobProngs->begin(); itProng != newVtxBlobProngs->end(); ++itProng ) {
    if( 0 <= m_vertexBlobProngColor ) m_hitTaggerTool->applyColorTag( *itProng, m_vertexBlobProngColor );
  }

  //-----------------------------------------------------------
  //! Delete vector newVtxBlobProngs but not their elements
  //-----------------------------------------------------------
  delete newVtxBlobProngs;

  //------------------------------------------------------------------------------
  //! Create Isolated 3D EM Blobs and add it to muonProng
  //! These attach the muon-related activity (brems/deltas) to the muon track
  //------------------------------------------------------------------------------
  if ( m_makeIsoMuonEMBlobs ) {
    debug()<<"Create Isolated 3D EM Blobs and add it to muon Prong"<<endmsg;
    m_minModDepCCQERecoUtils->makeIsoEMMuonBlobs( event, muonProng );
  }
  if ( m_makeFuzzMuonEMBlobs ) {
    debug()<<"Create Fuzz EM Blobs and add it to muon Prong"<<endmsg;
    m_minModDepCCQERecoUtils->makeFuzzEMMuonBlobs( event, muonProng );
  }

  //Temporary check of number of tracks in muon prong
  Minerva::TrackVect muontracks = muonProng->minervaTracks();
  debug()<<" tracks in muon prong = " << muontracks.size() << endmsg;

  //!Create primary Blob Prongs - NOT SURE IF WE SHOULD RUN THIS GENERAL METHOD NOW !
  // m_primaryBlobProngTool->makePrimaryBlobProngs( event );

  //------------------------------------------------------------------------------------------------------------------------------
  //! Create Shower Blob Prongs from the remaining "Unused" clusters
  //! They become the non-Vertex recoil Prong
  //! V.V.I. - We have noticed events (10200/69/521, 10203/54/601) where there is activity from overlay in the time slice.
  //! However this is out-of-time (i.e. -20, 35 ns) with the muon time.
  //! This activity will not be blobbed if we stick to "in time" clusters only.
  //! Hence we are resorting to collecting "ALL UNUSED" clusters (except XTalk & LowAct) in the event, for blobbing purposes.
  //! For event selection, we cut only on the blobs that are in time with the neutrino interaction we are interested in.
  //------------------------------------------------------------------------------------------------------------------------------
  debug() << "Create Shower Blob Prongs from remaining \"unused\" clusters" << endmsg;

  std::vector<Minerva::Prong*> *newIsoIdProngs = new std::vector<Minerva::Prong*>;

  Minerva::IDClusterVect  unusedClustsForBlobs = event->select<Minerva::IDCluster>("Unused","!LowActivity&!XTalkCandidate");

  sc = m_primaryBlobProngTool->makeShowerBlobProngs( event, unusedClustsForBlobs, newIsoIdProngs );
  if( sc.isFailure() ) return sc;

  //-----------------------------------------------------------------
  //! Color the clusters belonging to the non-Vertex recoil Prong
  //-----------------------------------------------------------------
  for( std::vector<Minerva::Prong*>::iterator itProng = newIsoIdProngs->begin(); itProng != newIsoIdProngs->end(); ++itProng ) {
    if( 0 <= m_isolatedBlobProngColor ) m_hitTaggerTool->applyColorTag( *itProng, m_isolatedBlobProngColor );

    debug() << "Prong Type " << (*itProng)->type() << endmsg;

    SmartRefVector<Minerva::IDCluster> prongClusts = (*itProng)->getAllIDClusters();
    for( SmartRefVector<Minerva::IDCluster>::iterator itClust = prongClusts.begin(); itClust != prongClusts.end(); ++itClust ) {
      debug() << "Prong Cluster Time " << (*itClust)->time() << endmsg;
    }
  }

  // ProngVect newIsoIdProngs;
  // if( (RecoilUtils->createIsoBlobProngs( event, newIsoIdProngs )).isFailure() )
  // return StatusCode::FAILURE;

  debug() << "Found " << newIsoIdProngs->size() << " new Isolated ID Blob Prongs ....." << endmsg;

  //--------------------------------------------------------------------------
  //! You can add other conditions here, for examining the ShowerBlobProngs
  //! before you start adding them to the evtMgr, user has control !
  //--------------------------------------------------------------------------
  if( newIsoIdProngs->size() ) addObject( event, *newIsoIdProngs );

  //Delete vector newIsoIdProngs but not their elements
  delete newIsoIdProngs;

  //!@todo cut on number of isolated blobs (<= 2)?
  //! I think the actual cut should be performed on the isolated blobs outside
  //! a certain (spheric?) region from the vertex to still be defined (30cm radius?)
  int n_nonvtx_iso_blobs_all = 0, n_nonvtx_iso_blobs = 0;
  double nonvtx_iso_blobs_energy_all = 0., nonvtx_iso_blobs_energy = 0.;
  double vtx_blobs_energy = 0.;
  double vtxisoblob_clusE_outsideradius = 0.;
  //  double muonTime = m_recoObjTimeTool->trackVertexTime(muonProng->minervaTracks()[0]);

  std::vector<double> vtxBlobEnergyInVtxBlobProng;
  std::vector<double> isoBlobEnergyInVtxBlobProng;
  std::vector<double> isoBlobDistanceInVtxBlobProng;
  std::vector<double> nonVtxIsoBlobEnergyInProng;
  std::vector<double> nonVtxIsoBlobDistanceInProng;
  std::vector<double> isoBlobEnergyOutsideRadiusInVtxBlobProng;
  std::vector<double> nonVtxIsoBlobStartXInProng;
  std::vector<double> nonVtxIsoBlobStartYInProng;
  std::vector<double> nonVtxIsoBlobStartZInProng;
  std::vector<double> nonVtxIsoBlobTimeInProng;
  std::vector<double> nonVtxIsoBlobTimeDiffInProng;
  std::vector<double> nonVtxIsoBlobLowestModuleXInProng;
  std::vector<double> nonVtxIsoBlobLowestModuleUInProng;
  std::vector<double> nonVtxIsoBlobLowestModuleVInProng;
  std::vector<double> nonVtxIsoBlobHighestModuleXInProng;
  std::vector<double> nonVtxIsoBlobHighestModuleUInProng;
  std::vector<double> nonVtxIsoBlobHighestModuleVInProng;
  std::vector<double> nonVtxIsoBlobEarliestHitTimeInProng;
  std::vector<double> nonVtxIsoBlobLatestHitTimeInProng;
  std::vector<double> nonVtxIsoBlobHighestHitEnergyInProng;
  std::vector<int> nonVtxIsoBlobNHitsInProng;
  std::vector<int> nonVtxIsoBlobParticlePDGInProng;
  std::vector<int> nonVtxIsoBlobPrimaryParticlePDGInProng;
  std::vector<double> nonVtxIsoBlobMatchedEnergyFractionInProng;
  std::vector<double> nonVtxIsoBlobDataEnergyFractionInProng;

  Minerva::ProngVect prongs = event->select<Minerva::Prong>( "Used:Unused", "All" );
  debug() << "Event has now " << prongs.size() << " prongs" << endmsg;

  for( Minerva::ProngVect::iterator p=prongs.begin(); p!=prongs.end(); p++ ) {
    debug() << "Prong Creation Signature = "<< (*p)->creationSignature() << endmsg;
    //Get calibrated vertex energy
    if( ((*p)->creationSignature()== PrimaryBlobProngExtraDataDefs::InteractionVtxBlobProngName()) ||
        ((*p)->creationSignature()== PrimaryBlobProngExtraDataDefs::StartPointVtxBlobProngName()) ){

      double calE = m_caloUtils->applyCalConsts( *p, "Default", false );
      vtx_blobs_energy += calE;
      debug() << "Found a " << (*p)->creationSignature() << ", nblobs: " << (*p)->idblobs().size() << ", energy: " << calE << " MeV" << endmsg;

      // loop over blobs in prong
      Minerva::IDBlobVect idBlobs = (*p)->idblobs();
      for( Minerva::IDBlobVect::iterator itBlob=idBlobs.begin(); itBlob!=idBlobs.end(); itBlob++ ){
        if( (*itBlob)->patRecHistory() == Minerva::IDBlob::VertexBlobPatRec ) {
          double vtxE = m_caloUtils->applyCalConsts( *itBlob, "Default", false );
          vtxBlobEnergyInVtxBlobProng.push_back(vtxE);
        }
        else if( (*itBlob)->patRecHistory() == Minerva::IDBlob::IsolatedIDBlobPatRec ) {
          double isoE = m_caloUtils->applyCalConsts( *itBlob, "Default", false );
          isoBlobEnergyInVtxBlobProng.push_back(isoE);

          const Gaudi::XYZPoint blob_pos = (*itBlob)->startPoint();
          const Gaudi::XYZPoint vtx_pos = vertexOfPhysEvent->position();

          double distance = m_mathTool->distanceBetween(blob_pos, vtx_pos);
          isoBlobDistanceInVtxBlobProng.push_back(distance);
          /*
          const Gaudi::XYZPoint blob_pos_us = m_blobCreatorUtils->calcUpstreamBlobStartPoint(*itBlob);
          const Gaudi::XYZPoint blob_pos_ds = m_blobCreatorUtils->calcDownstreamBlobStartPoint(*itBlob);
          const Gaudi::XYZPoint vtx_pos = vertexOfPhysEvent->position();
          double distance1 = m_mathTool->distanceBetween(blob_pos_us, vtx_pos);
          double distance2 = m_mathTool->distanceBetween(blob_pos_ds, vtx_pos);
          double distance = (distance1<distance2)? distance1 : distance2;
          isoBlobDistanceInVtxBlobProng.push_back(distance);
          debug()<<"Iso vertex blob US (x,y,z) = "<< blob_pos_us.x() << ", "<< blob_pos_us.y()<<", "<< blob_pos_us.z()<< endmsg;
          debug()<<"Iso vertex blob DS (x,y,z) = "<< blob_pos_ds.x() << ", "<< blob_pos_ds.y()<<", "<< blob_pos_ds.z()<< endmsg;
          debug()<<"vertex position (x,y,z) = "<< vtx_pos.x() << ", "<< vtx_pos.y()<<", "<< vtx_pos.z()<< endmsg;
          debug()<<"distance iso vertex blob US from vertex="<< distance1<<endmsg;
          debug()<<"distance iso vertex blob DS from vertex ="<< distance2<<endmsg;
          debug()<<"distance iso vertex blob minimum from vertex="<< distance<<endmsg;
          debug()<<"distance iso vertex blob default start point ="<< (*itBlob)->startPoint()<<endmsg;
          */

          debug()<< "Vertex Iso Blob centroid position X,Z = " << ((*itBlob)->energyCentroidXZ()).first<< ", " << ((*itBlob)->energyCentroidXZ()).second <<endmsg;
          debug()<< "Vertex Iso Blob centroid position U,Z = " << (*itBlob)->energyCentroidUZ().first<< ", " << (*itBlob)->energyCentroidXZ().second <<endmsg;
          debug()<< "Vertex Iso Blob centroid position V,Z = " << (*itBlob)->energyCentroidVZ().first<< ", " << (*itBlob)->energyCentroidXZ().second <<endmsg;
          //! Also, calculate the energy of the clusters from these blobs that are outside
          //! the sphere of radius: m_searchStepSize
          SmartRefVector<Minerva::IDCluster> vtxisoblobClusters = (*itBlob)->clusters();
          SmartRefVector<Minerva::IDCluster> vtxisoblobClusters_outside;
          SmartRefVector<Minerva::IDCluster>::iterator itCluster = vtxisoblobClusters.begin();
          double minclus_distance = 1e6;
          for (; itCluster!=vtxisoblobClusters.end(); itCluster++ ) {
            double dist = m_mathTool->twoDDistance(*itCluster,vertexOfPhysEvent->position());
            if (minclus_distance>dist) minclus_distance = dist;
            if (dist> m_searchStepSize){
              vtxisoblobClusters_outside.push_back(*itCluster);
            }
          }
          debug()<<"Distance vtx iso blob to vertex = "<< distance<< endmsg;
          debug()<<"Distance iso vertex blob min cluster = " << minclus_distance << endmsg;
          double clusE_outside = m_caloUtils->applyCalConsts( vtxisoblobClusters_outside, "Default", false );
          isoBlobEnergyOutsideRadiusInVtxBlobProng.push_back(clusE_outside);
          vtxisoblob_clusE_outsideradius += clusE_outside;
        }
      }
    }

    //------------------------------------------------------------------------------------------------------------------------------
    //! Get calibrated non-vertex energy for ALL the isolated blobs
    //! Here we have blobbed up "ALL UNUSED" clusters (except XTalk & LowAct) in the event, in time or out of time w.r.t. muon
    //! So activity from overlay will also appear as blobs, if they are in the same time slice.
    //------------------------------------------------------------------------------------------------------------------------------
    if( (*p)->creationSignature() == PrimaryBlobProngExtraDataDefs::IsolatedIDBlobProngName() ) {
      n_nonvtx_iso_blobs_all += (*p)->idblobs().size();
      double calE = m_caloUtils->applyCalConsts( *p, "Default", false );
      nonvtx_iso_blobs_energy_all += calE;

      //------------------------------------------------------------------------------------------------------------------
      //! Loop over Isolated Blobs in prong that are in time with the neutrino interaction that we are interested in.
      //! Get their calibrated energy.
      //! For event selection purposes, we cut ONLY on these blobs
      //------------------------------------------------------------------------------------------------------------------
      Minerva::IDBlobVect isoBlobs = (*p)->idblobs();
      for( Minerva::IDBlobVect::iterator itBlob=isoBlobs.begin(); itBlob!=isoBlobs.end(); itBlob++ ) {
        double time_diff = (*itBlob)->time() - muonTime;
	// get calibrated energy of isolated blob prong
	//@channel = "Defaul"
	//@applyPolyLine = false
        if( time_diff > m_lowerTimeWindow && time_diff < m_upperTimeWindow ) {
          n_nonvtx_iso_blobs++;
          double calE_inTime = m_caloUtils->applyCalConsts( *itBlob, "Default", false );
          nonvtx_iso_blobs_energy += calE_inTime;
          nonVtxIsoBlobEnergyInProng.push_back(calE_inTime);

          const Gaudi::XYZPoint blob_pos = (*itBlob)->startPoint();
          const Gaudi::XYZPoint vtx_pos = vertexOfPhysEvent->position();
          double distance = m_mathTool->distanceBetween(blob_pos, vtx_pos);
          /*
          const Gaudi::XYZPoint blob_pos_us = m_blobCreatorUtils->calcUpstreamBlobStartPoint(*itBlob);
          const Gaudi::XYZPoint blob_pos_ds = m_blobCreatorUtils->calcDownstreamBlobStartPoint(*itBlob);

          double distance1 = m_mathTool->distanceBetween(blob_pos_us, vtx_pos);
          double distance2 = m_mathTool->distanceBetween(blob_pos_ds, vtx_pos);
          double distance = (distance1<distance2)? distance1 : distance2;
          */
          //double distance = sqrt( pow(blob_pos.x()-vtx_pos.x(),2) + pow(blob_pos.y()-vtx_pos.y(),2) + pow(blob_pos.z()-vtx_pos.z(),2) );
	  nonVtxIsoBlobDistanceInProng.push_back(distance);
	  nonVtxIsoBlobStartXInProng.push_back(blob_pos.X());
	  nonVtxIsoBlobStartYInProng.push_back(blob_pos.Y());
	  nonVtxIsoBlobStartZInProng.push_back(blob_pos.Z());
	  nonVtxIsoBlobTimeInProng.push_back((*itBlob)->time());
	  nonVtxIsoBlobTimeDiffInProng.push_back(time_diff);
	  nonVtxIsoBlobLowestModuleXInProng.push_back((*itBlob)->moduleLowX());
	  nonVtxIsoBlobLowestModuleUInProng.push_back((*itBlob)->moduleLowU());
	  nonVtxIsoBlobLowestModuleVInProng.push_back((*itBlob)->moduleLowV());
	  nonVtxIsoBlobHighestModuleXInProng.push_back((*itBlob)->moduleHighX());
	  nonVtxIsoBlobHighestModuleUInProng.push_back((*itBlob)->moduleHighU());
	  nonVtxIsoBlobHighestModuleVInProng.push_back((*itBlob)->moduleHighV());
          verbose()<<"Distance non-vtx iso blob-vertex = "<< distance<<endmsg;

	  Minerva::IDDigitVect blobhits = (*itBlob)->getAllDigits();
	  std::vector<const Minerva::IDCluster*> blobidclusters;
	  SmartRefVector<Minerva::IDCluster> clustersblob = (*itBlob)->clusters();
	  blobidclusters.insert(blobidclusters.begin(), clustersblob.begin(), clustersblob.end());

	  double earlyhit = 1e20;
	  double latehit = -1e20;
	  double highesthitenergy = 0;
	  int nblobhits = 0;
	  for(Minerva::IDDigitVect::iterator itBlobHits=blobhits.begin(); itBlobHits!=blobhits.end();itBlobHits++){
	    if( (*itBlobHits)->calTime() < earlyhit) earlyhit =(*itBlobHits)->time();
	    if( (*itBlobHits)->calTime() > latehit)  latehit =(*itBlobHits)->time();
	    if( (*itBlobHits)->normEnergy() > highesthitenergy) highesthitenergy=(*itBlobHits)->normEnergy();
	    nblobhits+=1;
	  }
	  nonVtxIsoBlobEarliestHitTimeInProng.push_back(earlyhit);
	  nonVtxIsoBlobLatestHitTimeInProng.push_back(latehit);
	  nonVtxIsoBlobHighestHitEnergyInProng.push_back(highesthitenergy);
	  nonVtxIsoBlobNHitsInProng.push_back(nblobhits);

	  //Match truth
	  Minerva::IDBlob myblob = (*(*itBlob).data());
	  std::vector<double> bestPart = tagBlobTruth(myblob);
	  double data_fraction = TruthMatcher->getDataFraction(blobidclusters);
	  nonVtxIsoBlobParticlePDGInProng.push_back(bestPart[0]);
	  nonVtxIsoBlobPrimaryParticlePDGInProng.push_back(bestPart[1]);
	  nonVtxIsoBlobMatchedEnergyFractionInProng.push_back(bestPart[2]);
	  nonVtxIsoBlobDataEnergyFractionInProng.push_back(data_fraction);

        }
      }
    }
  } //End of for loop over Prongs

  verbose()<<"nonvtx_iso_blobs_energy = " << nonvtx_iso_blobs_energy << endmsg;
  verbose()<<"nonvtx_iso_blobs_energy_all = " << nonvtx_iso_blobs_energy_all << endmsg;

  event->setDoubleData("vtx_blobs_energy", vtx_blobs_energy);
  event->setDoubleData("vtx_iso_blobs_energy_outside_radius", vtxisoblob_clusE_outsideradius);
  event->setContainerDoubleData("vtx_blobs_vtx_energy_in_prong", vtxBlobEnergyInVtxBlobProng);
  event->setContainerDoubleData("vtx_blobs_iso_energy_in_prong", isoBlobEnergyInVtxBlobProng);
  event->setContainerDoubleData("vtx_blobs_iso_energy_clusters_outside_radius_in_prong", isoBlobEnergyOutsideRadiusInVtxBlobProng);
  event->setContainerDoubleData("vtx_blobs_iso_distance_in_prong", isoBlobDistanceInVtxBlobProng);
  event->setIntData("n_nonvtx_iso_blobs", n_nonvtx_iso_blobs);
  event->setIntData("n_nonvtx_iso_blobs_all", n_nonvtx_iso_blobs_all);
  event->setDoubleData("nonvtx_iso_blobs_energy", nonvtx_iso_blobs_energy);
  event->setDoubleData("nonvtx_iso_blobs_energy_all", nonvtx_iso_blobs_energy_all);
  event->setContainerDoubleData("nonvtx_iso_blobs_energy_in_prong", nonVtxIsoBlobEnergyInProng);
  event->setContainerDoubleData("nonvtx_iso_blobs_distance_in_prong", nonVtxIsoBlobDistanceInProng);
  event->setContainerDoubleData("nonvtx_iso_blobs_start_position_x_in_prong",nonVtxIsoBlobStartXInProng);
  event->setContainerDoubleData("nonvtx_iso_blobs_start_position_y_in_prong",nonVtxIsoBlobStartYInProng);
  event->setContainerDoubleData("nonvtx_iso_blobs_start_position_z_in_prong",nonVtxIsoBlobStartZInProng);
  event->setContainerDoubleData("nonvtx_iso_blobs_time_in_prong",nonVtxIsoBlobTimeInProng);
  event->setContainerDoubleData("nonvtx_iso_blobs_time_difference_in_prong",nonVtxIsoBlobTimeDiffInProng);
  event->setContainerDoubleData("nonvtx_iso_blobs_lowest_module_x_in_prong",nonVtxIsoBlobLowestModuleXInProng);
  event->setContainerDoubleData("nonvtx_iso_blobs_lowest_module_u_in_prong",nonVtxIsoBlobLowestModuleUInProng);
  event->setContainerDoubleData("nonvtx_iso_blobs_lowest_module_v_in_prong",nonVtxIsoBlobLowestModuleVInProng);
  event->setContainerDoubleData("nonvtx_iso_blobs_highest_module_x_in_prong",nonVtxIsoBlobHighestModuleXInProng);
  event->setContainerDoubleData("nonvtx_iso_blobs_highest_module_u_in_prong",nonVtxIsoBlobHighestModuleUInProng);
  event->setContainerDoubleData("nonvtx_iso_blobs_highest_module_v_in_prong",nonVtxIsoBlobHighestModuleVInProng);
  event->setContainerDoubleData("nonvtx_iso_blobs_earliest_hit_time_in_prong",nonVtxIsoBlobEarliestHitTimeInProng);
  event->setContainerDoubleData("nonvtx_iso_blobs_latest_hit_time_in_prong",nonVtxIsoBlobLatestHitTimeInProng);
  event->setContainerDoubleData("nonvtx_iso_blobs_highest_hit_energy_in_prong",nonVtxIsoBlobHighestHitEnergyInProng);
  event->setContainerIntData("nonvtx_iso_blobs_n_hits_in_prong",nonVtxIsoBlobNHitsInProng);
  event->setContainerIntData("nonvtx_iso_blobs_particle_pdg_in_prong",nonVtxIsoBlobParticlePDGInProng);
  event->setContainerIntData("nonvtx_iso_blobs_primary_particle_pdg_in_prong",nonVtxIsoBlobPrimaryParticlePDGInProng);
  event->setContainerDoubleData("nonvtx_iso_blobs_matched_energy_fraction_in_prong",nonVtxIsoBlobMatchedEnergyFractionInProng);
  event->setContainerDoubleData("nonvtx_iso_blobs_data_energy_fraction_in_prong",nonVtxIsoBlobDataEnergyFractionInProng);

  //-------------------------------------------------------------------------------------
  //! Look at the remaining ID clusters in the Tracker/ECAL regions (dispersed energy)
  //! in the [-20,35] ns time window
  //-------------------------------------------------------------------------------------
  Minerva::IDClusterVect unusedIDClusters = m_minModDepCCQERecoUtils->getInTimeAnalyzableIDClusters( event, muonProng );
  double iddisEnergy = m_caloUtils->applyCalConsts( unusedIDClusters, "Default", false );

  event->setDoubleData("dis_id_energy", iddisEnergy);

  //-------------------------------------------------------------------------------------
  //! Look at all ID clusters in the Tracker/ECAL regions
  //! in the [-20,35] ns time window which are not associated with the muon
  //! and do not occur inside various vertex regions
  //-------------------------------------------------------------------------------------

  Minerva::IDClusterVect nonMuonNonVtxClusters0mm = m_minModDepCCQERecoUtils->getInTimeAnalyzableNonMuonNonVtxIDClusters( event, muonProng, 0);
  Minerva::IDClusterVect nonMuonNonVtxClusters50mm = m_minModDepCCQERecoUtils->getInTimeAnalyzableNonMuonNonVtxIDClusters( event, muonProng, 50);
  Minerva::IDClusterVect nonMuonNonVtxClusters100mm = m_minModDepCCQERecoUtils->getInTimeAnalyzableNonMuonNonVtxIDClusters( event, muonProng, 100);
  Minerva::IDClusterVect nonMuonNonVtxClusters150mm = m_minModDepCCQERecoUtils->getInTimeAnalyzableNonMuonNonVtxIDClusters( event, muonProng, 150);
  Minerva::IDClusterVect nonMuonNonVtxClusters200mm = m_minModDepCCQERecoUtils->getInTimeAnalyzableNonMuonNonVtxIDClusters( event, muonProng, 200);
  Minerva::IDClusterVect nonMuonNonVtxClusters250mm = m_minModDepCCQERecoUtils->getInTimeAnalyzableNonMuonNonVtxIDClusters( event, muonProng, 250);
  Minerva::IDClusterVect nonMuonNonVtxClusters300mm = m_minModDepCCQERecoUtils->getInTimeAnalyzableNonMuonNonVtxIDClusters( event, muonProng, 300);

  double nonMuonNonVtxEnergy0mm = m_caloUtils->applyCalConsts( nonMuonNonVtxClusters0mm, "Default", false );
  double nonMuonNonVtxEnergy50mm = m_caloUtils->applyCalConsts( nonMuonNonVtxClusters50mm, "Default", false );
  double nonMuonNonVtxEnergy100mm = m_caloUtils->applyCalConsts( nonMuonNonVtxClusters100mm, "Default", false );
  double nonMuonNonVtxEnergy150mm = m_caloUtils->applyCalConsts( nonMuonNonVtxClusters150mm, "Default", false );
  double nonMuonNonVtxEnergy200mm = m_caloUtils->applyCalConsts( nonMuonNonVtxClusters200mm, "Default", false );
  double nonMuonNonVtxEnergy250mm = m_caloUtils->applyCalConsts( nonMuonNonVtxClusters250mm, "Default", false );
  double nonMuonNonVtxEnergy300mm = m_caloUtils->applyCalConsts( nonMuonNonVtxClusters300mm, "Default", false );

  event->setDoubleData("recoil_energy_nonmuon_nonvtx0mm",nonMuonNonVtxEnergy0mm);
  event->setDoubleData("recoil_energy_nonmuon_nonvtx50mm",nonMuonNonVtxEnergy50mm);
  event->setDoubleData("recoil_energy_nonmuon_nonvtx100mm",nonMuonNonVtxEnergy100mm);
  event->setDoubleData("recoil_energy_nonmuon_nonvtx150mm",nonMuonNonVtxEnergy150mm);
  event->setDoubleData("recoil_energy_nonmuon_nonvtx200mm",nonMuonNonVtxEnergy200mm);
  event->setDoubleData("recoil_energy_nonmuon_nonvtx250mm",nonMuonNonVtxEnergy250mm);
  event->setDoubleData("recoil_energy_nonmuon_nonvtx300mm",nonMuonNonVtxEnergy300mm);


  Minerva::IDClusterVect nonMuonVtxClusters0mm = m_minModDepCCQERecoUtils->getInTimeAnalyzableNonMuonVtxIDClusters( event, muonProng, 0);
  Minerva::IDClusterVect nonMuonVtxClusters50mm = m_minModDepCCQERecoUtils->getInTimeAnalyzableNonMuonVtxIDClusters( event, muonProng, 50);
  Minerva::IDClusterVect nonMuonVtxClusters100mm = m_minModDepCCQERecoUtils->getInTimeAnalyzableNonMuonVtxIDClusters( event, muonProng, 100);
  Minerva::IDClusterVect nonMuonVtxClusters150mm = m_minModDepCCQERecoUtils->getInTimeAnalyzableNonMuonVtxIDClusters( event, muonProng, 150);
  Minerva::IDClusterVect nonMuonVtxClusters200mm = m_minModDepCCQERecoUtils->getInTimeAnalyzableNonMuonVtxIDClusters( event, muonProng, 200);
  Minerva::IDClusterVect nonMuonVtxClusters250mm = m_minModDepCCQERecoUtils->getInTimeAnalyzableNonMuonVtxIDClusters( event, muonProng, 250);
  Minerva::IDClusterVect nonMuonVtxClusters300mm = m_minModDepCCQERecoUtils->getInTimeAnalyzableNonMuonVtxIDClusters( event, muonProng, 300);

  double nonMuonVtxEnergy0mm = m_caloUtils->applyCalConsts( nonMuonVtxClusters0mm, "Default", false );
  double nonMuonVtxEnergy50mm = m_caloUtils->applyCalConsts( nonMuonVtxClusters50mm, "Default", false );
  double nonMuonVtxEnergy100mm = m_caloUtils->applyCalConsts( nonMuonVtxClusters100mm, "Default", false );
  double nonMuonVtxEnergy150mm = m_caloUtils->applyCalConsts( nonMuonVtxClusters150mm, "Default", false );
  double nonMuonVtxEnergy200mm = m_caloUtils->applyCalConsts( nonMuonVtxClusters200mm, "Default", false );
  double nonMuonVtxEnergy250mm = m_caloUtils->applyCalConsts( nonMuonVtxClusters250mm, "Default", false );
  double nonMuonVtxEnergy300mm = m_caloUtils->applyCalConsts( nonMuonVtxClusters300mm, "Default", false );

  event->setDoubleData("recoil_energy_nonmuon_vtx0mm",nonMuonVtxEnergy0mm);
  event->setDoubleData("recoil_energy_nonmuon_vtx50mm",nonMuonVtxEnergy50mm);
  event->setDoubleData("recoil_energy_nonmuon_vtx100mm",nonMuonVtxEnergy100mm);
  event->setDoubleData("recoil_energy_nonmuon_vtx150mm",nonMuonVtxEnergy150mm);
  event->setDoubleData("recoil_energy_nonmuon_vtx200mm",nonMuonVtxEnergy200mm);
  event->setDoubleData("recoil_energy_nonmuon_vtx250mm",nonMuonVtxEnergy250mm);
  event->setDoubleData("recoil_energy_nonmuon_vtx300mm",nonMuonVtxEnergy300mm);

  //---------------------------------------------------
  // Color the clusters in the dispersed energy
  //---------------------------------------------------
  for( Minerva::IDClusterVect::iterator itClust = unusedIDClusters.begin(); itClust != unusedIDClusters.end(); ++itClust ) {
    if( 0 <= m_dispersedEnergyColor ) m_hitTaggerTool->applyColorTag( *itClust, m_dispersedEnergyColor );
  }

  //--------------------------------------------------
  //! If we got to this line, set pass precuts to true
  //--------------------------------------------------
  bool pass_CCQENu_precuts = true;
  event->setIntData("pass_CCQENu_precuts",(int)pass_CCQENu_precuts);
  event->filtertaglist()->setOrAddFilterTag("pass_CCQENu_precuts", pass_CCQENu_precuts );

  //---------------------------------------------------
  //! Fill common physics ana branches
  //---------------------------------------------------
  fillCommonPhysicsAnaBranches( event );
  //---------------------------------------------------
  //! Fill NuMI branches
  //---------------------------------------------------
  fillNuMIBranches(event);

  //---------------------------------------------------
  //! Fill Particle Reponse branches
  // Create a vector of all clusters associated
  // to the Non-vtx Isolated Blobs and the Non-vtx
  // dispersed blobs and use it as the input
  // for the fill function
  //---------------------------------------------------
  Minerva::IDClusterVect nonVtxIDClusters;

  //First, attach all clusters associated with the non-vtx isolated blobs
  Minerva::ProngVect isoProngs = event->select<Minerva::Prong>( "Used:Unused", "All" );
  debug() << "Event has now " << prongs.size() << " prongs" << endmsg;

  for( Minerva::ProngVect::iterator p=prongs.begin(); p!=prongs.end(); p++ ) {
    if( (*p)->creationSignature() == PrimaryBlobProngExtraDataDefs::IsolatedIDBlobProngName() ){
      Minerva::IDClusterVect clusters = (*p)->getAllIDClusters();
      for(Minerva::IDClusterVect::iterator itCluster=clusters.begin(); itCluster!=clusters.end(); itCluster++)
	{
        nonVtxIDClusters.push_back( *itCluster );
      }
    }
  }

  //Now, attach dispersed clusters
  for(Minerva::IDClusterVect::iterator itCluster=unusedIDClusters.begin(); itCluster!=unusedIDClusters.end(); itCluster++)
    nonVtxIDClusters.push_back( *itCluster );

  // Finally, Fill Particle Responses
  fillParticleResponseBranches(event,nonVtxIDClusters,"cal");

  //-------------------------------
  //! Mark event
  //-------------------------------
  markEvent( event );

  //-------------------------------
  //! Interpret event
  //-------------------------------
  std::vector<Minerva::NeutrinoInt*> nuInt;
  interpretEvent( event, truth, nuInt );

  //---------------------------------------------------
  //! Add interaction hypothesis to physics event
  //---------------------------------------------------
  sc = addInteractionHyp( event, nuInt );

  debug() << "Exiting CCQENu::reconstructEvent() now ....." << endmsg;

  return sc;
} //End of reconstructEvent( )


//=============================================================================
// interpretEvent() --
//=============================================================================
StatusCode CCQENu::interpretEvent( const Minerva::PhysicsEvent *event, const Minerva::GenMinInteraction* truth, std::vector<Minerva::NeutrinoInt*>& nuInt ) const {

  debug() << "Entering CCQENu::interpretEvent() now ....." << endmsg;
  if( truth ){
    debug() << "This event has a matched MC interaction" << endmsg;
  }

  if(!event->hasInteractionVertex()){
    //! Construct neutrino hypothesis
    Minerva::NeutrinoInt* ccqeHyp = new Minerva::NeutrinoInt( "CCQENu" );
    nuInt.push_back( ccqeHyp );

    ccqeHyp->setNeutrinoFlavor( Minerva::NeutrinoInt::MuonFlavor );
    ccqeHyp->setInteractionCurrent( Minerva::NeutrinoInt::ChargedCurrent );
    ccqeHyp->setInteractionType( Minerva::NeutrinoInt::QuasiElastic );

    return StatusCode::SUCCESS; // have to do this for events without interaction vertices because basically all the objects below are not valid. The code will crash and burn.
  }

  //!Get Muon prong
  SmartRef<Minerva::Prong> muonProng;
  SmartRef<Minerva::Particle> muonPart;
  MuonUtils->findMuonProng( event, muonProng, muonPart );

  //!Get charge
  int muon_charge = 0;
  MuonUtils->muonCharge( muonProng, muon_charge, m_qOverpChargeCut );

  //!Get muon momentum, energy and angle
  double muon_P = muonPart->momentumVec().P();
  double muon_E = muonPart->momentumVec().E();
  double muon_T = muon_E - MinervaUnits::M_mu;
  double muon_theta = MuonUtils->muTheta( muonPart );
  double muon_score = muonPart->score();

  //-----------------------------------------------
  //! Get proton kinematics stuff from dEdx info
  //-----------------------------------------------
  double proton_P = -9999., proton_E = -9999., proton_T = -9999., proton_theta = -9999.;
  ProngVect primaryProngs = event->primaryProngs();
  SmartRef<Minerva::Prong> protonProng;
  SmartRef<Minerva::Particle> protonPart;
  SmartRef<Minerva::Particle> pionPart;
  double totalCalibEPrimaryProton   = -9999.;

  ProngVect secondaryProtonProngs;
  std::vector<double> sec_protons_E;
  std::vector<double> sec_protons_P;
  std::vector<double> sec_protons_T;
  std::vector<double> sec_protons_T_Calo;
  std::vector<double> sec_protons_theta;
  std::vector<double> sec_protons_proton_scores;
  std::vector<double> sec_protons_proton_scores1;
  std::vector<double> sec_protons_proton_scores2;
  std::vector<double> sec_protons_pion_scores;
  std::vector<double> sec_protons_pion_scores1;
  std::vector<double> sec_protons_pion_scores2;

  //------------------------------------------------------------------------
  //! dEdx Tool variations parameters for Primary and Secondary Protons
  //------------------------------------------------------------------------
  double proton_score1_Mass_Up=-9999.9, proton_score1_Mass_Down=-9999.9, proton_score1_BetheBloch_Up=-9999.9, proton_score1_BetheBloch_Down=-9999.9;
  double proton_score1_MEU_Up=-9999.9, proton_score1_MEU_Down=-9999.9, proton_score1_Birks=-9999.9;
  double proton_E_Mass_Up=-9999.9, proton_E_Mass_Down=-9999.9, proton_E_BetheBloch_Up=-9999.9, proton_E_BetheBloch_Down=-9999.9;
  double proton_E_MEU_Up=-9999.9, proton_E_MEU_Down=-9999.9, proton_E_Birks=-9999.9;

  std::vector<double> sec_protons_score1_Mass_Up, sec_protons_score1_Mass_Down, sec_protons_score1_BetheBloch_Up, sec_protons_score1_BetheBloch_Down;
  std::vector<double> sec_protons_score1_MEU_Up, sec_protons_score1_MEU_Down, sec_protons_score1_Birks;
  std::vector<double> sec_protons_E_Mass_Up, sec_protons_E_Mass_Down, sec_protons_E_BetheBloch_Up, sec_protons_E_BetheBloch_Down;
  std::vector<double> sec_protons_E_MEU_Up, sec_protons_E_MEU_Down, sec_protons_E_Birks;

  debug()<< "Getting most energetic (Primary) proton and Secondary proton prongs" << endmsg;
  bool protonFound = false;
  bool secondaryProtonsFound = false;

  for (ProngVect::iterator itProngs = primaryProngs.begin(); itProngs != primaryProngs.end(); ++itProngs) {
    if( (*itProngs)->filtertaglist()->filterTagExists( m_primaryProton ) ) {
      protonProng = (*itProngs);

      totalCalibEPrimaryProton = m_caloUtils->applyCalConsts( protonProng, "Default", false, true );
      debug() << "Total calib energy of primary proton " << totalCalibEPrimaryProton << endmsg;

      SmartRefVector<Minerva::Particle> pionparticles = (*itProngs)->particlesWithIDCode(Minerva::Particle::Pion, "dEdX");
      if (pionparticles.size()>0) pionPart = pionparticles[0];
      protonPart  = (*itProngs)->bestParticle();
      if (protonPart) protonFound = true;
    }
    else if( (*itProngs)->filtertaglist()->filterTagExists( m_secondaryProtons ) ) {
      secondaryProtonProngs.push_back( *itProngs );
      secondaryProtonsFound = true;
    }
  }

  double proton_score = -9999., proton_score1 = -9999., proton_score2 = -9999.;
  double pion_score = -9999., pion_score1 = -9999., pion_score2 = -9999.;

  std::vector<double> protonE;
  double proton_startPointX = -9999., proton_startPointY = -9999., proton_startPointZ = -9999.;
  double proton_endPointX = -9999., proton_endPointY = -9999., proton_endPointZ = -9999.;
  double proton_p = -9999., proton_px = -9999., proton_py = -9999., proton_pz = -9999.;
  double proton_e = -9999., proton_ekin = -9999., proton_enu = -9999., proton_q2 = -9999.;
  double proton_thetaX = -9999., proton_thetaY = -9999., proton_phi = -9999.;

  if (protonFound) {
    debug() << "Proton prongs gotten"<<endmsg;

    proton_score  = protonPart->score();
    proton_score1 = protonPart->getDoubleData(ParticleExtraDataDefs::dEdXScore1());
    proton_score2 = protonPart->getDoubleData(ParticleExtraDataDefs::dEdXScore2());

    debug() << "Proton range score1: "<< proton_score1 << endmsg;

    proton_P = protonPart->momentumVec().P();
    proton_E = protonPart->momentumVec().E();
    proton_T = proton_E - MinervaUnits::M_p;
    protonE.push_back( protonPart->momentumVec().E() );
    protonE.push_back( protonPart->momentumVec().px() );
    protonE.push_back( protonPart->momentumVec().py() );
    protonE.push_back( protonPart->momentumVec().pz() );

    //-----------------------------------------------------------
    //-----------------------------------------------------------
    double theta = protonProng->minervaTracks().front()->theta();
    double phi   = protonProng->minervaTracks().front()->phi();

    proton_thetaX  = m_minCoordSysTool->thetaXWRTBeam(protonPart->momentumVec());
    proton_thetaY  = m_minCoordSysTool->thetaYWRTBeam(protonPart->momentumVec());
    proton_phi     = m_minCoordSysTool->phiWRTBeam(protonPart->momentumVec());

    proton_e  = sqrt( pow(totalCalibEPrimaryProton,2) + MinervaUnits::M_proton*MinervaUnits::M_proton );
    proton_px = totalCalibEPrimaryProton*sin(theta)*cos(phi);
    proton_py = totalCalibEPrimaryProton*sin(theta)*sin(phi);
    proton_pz = totalCalibEPrimaryProton*cos(theta);
    proton_p  = sqrt(pow(proton_px,2) + pow(proton_py,2) + pow(proton_pz,2) );

    proton_ekin = proton_e - MinervaUnits::M_p;
    proton_enu  = m_protonUtils->nuEnergyCCQE(proton_theta,proton_ekin,m_nuCCQEBindingEnergyMeV);
    proton_q2   = m_protonUtils->qSquaredCCQE(proton_ekin,m_nuCCQEBindingEnergyMeV,"quasi-elastic");

    proton_endPointX   = (protonProng->minervaTracks().back())->lastState().x();
    proton_endPointY   = (protonProng->minervaTracks().back())->lastState().y();
    proton_endPointZ   = (protonProng->minervaTracks().back())->lastState().z();

    proton_startPointX = (protonProng->minervaTracks().back())->firstState().x();
    proton_startPointY = (protonProng->minervaTracks().back())->firstState().y();
    proton_startPointZ = (protonProng->minervaTracks().back())->firstState().z();

    //------------------------------------------------------
    // dEdx Tool variations for Primary Proton
    //------------------------------------------------------
    if( protonPart->hasDoubleData("score1_Mass_Up") ) {
      proton_score1_Mass_Up = protonPart->getDoubleData("score1_Mass_Up") - proton_score1;
      proton_E_Mass_Up      = protonPart->getDoubleData("FitE_Mass_Up") - proton_E;
    }
    if( protonPart->hasDoubleData("score1_Mass_Down") ) {
      proton_score1_Mass_Down = protonPart->getDoubleData("score1_Mass_Down") - proton_score1;
      proton_E_Mass_Down      = protonPart->getDoubleData("FitE_Mass_Down") - proton_E;
    }
    if( protonPart->hasDoubleData("score1_BetheBloch_Up") ) {
      proton_score1_BetheBloch_Up = protonPart->getDoubleData("score1_BetheBloch_Up") - proton_score1;
      proton_E_BetheBloch_Up      = protonPart->getDoubleData("FitE_BetheBloch_Up") - proton_E;
    }
    if( protonPart->hasDoubleData("score1_BetheBloch_Down") ) {
      proton_score1_BetheBloch_Down = protonPart->getDoubleData("score1_BetheBloch_Down") - proton_score1;
      proton_E_BetheBloch_Down      = protonPart->getDoubleData("FitE_BetheBloch_Down") - proton_E;
    }
    if( protonPart->hasDoubleData("score1_MEU_Up") ) {
      proton_score1_MEU_Up = protonPart->getDoubleData("score1_MEU_Up") - proton_score1;
      proton_E_MEU_Up      = protonPart->getDoubleData("FitE_MEU_Up") - proton_E;
    }
    if( protonPart->hasDoubleData("score1_MEU_Down") ) {
      proton_score1_MEU_Down = protonPart->getDoubleData("score1_MEU_Down") - proton_score1;
      proton_E_MEU_Down      = protonPart->getDoubleData("FitE_MEU_Down") - proton_E;
    }
    if( protonPart->hasDoubleData("score1_Birks") ) {
      proton_score1_Birks  = protonPart->getDoubleData("score1_Birks") - proton_score1;
      proton_E_Birks       = protonPart->getDoubleData("FitE_Birks") - proton_E;
    }

    //----------------------------------------
    // Rotated proton's angle w.r.t beam
    //----------------------------------------
    proton_theta  = m_minCoordSysTool->thetaWRTBeam(protonPart->momentumVec());

    //double proton_thetaX = m_minCoordSysTool->thetaXWRTBeam(protonPart->momentumVec());
    //double proton_thetaY = m_minCoordSysTool->thetaYWRTBeam(protonPart->momentumVec());

    debug()<< "Calculated from dEdx: proton_E, proton_T, proton_P, proton_theta"<<endmsg;

  } else debug() << " Could not get Primary proton prong" << endmsg;

  if (secondaryProtonsFound) {
    for(ProngVect::iterator secprongs = secondaryProtonProngs.begin(); secprongs != secondaryProtonProngs.end(); ++secprongs) {
      double secproton_proton_score = -9999., secproton_proton_score1 = -9999., secproton_proton_score2 = -999.;
      double totalCalibESecondaryProton = -9999.;

      totalCalibESecondaryProton = m_caloUtils->applyCalConsts( (*secprongs), "Default", false, true );
      debug() << "Total calib energy of secondary proton " << totalCalibESecondaryProton << endmsg;

      SmartRef<Minerva::Particle> secprongPart = (*secprongs)->bestParticle();
      secproton_proton_score  = secprongPart->score();
      secproton_proton_score1 = secprongPart->getDoubleData(ParticleExtraDataDefs::dEdXScore1());
      secproton_proton_score2 = secprongPart->getDoubleData(ParticleExtraDataDefs::dEdXScore2());

      sec_protons_proton_scores.push_back( secproton_proton_score );
      sec_protons_proton_scores1.push_back( secproton_proton_score1 );
      sec_protons_proton_scores2.push_back( secproton_proton_score2 );

      sec_protons_E.push_back( secprongPart->momentumVec().E() );
      sec_protons_P.push_back( secprongPart->momentumVec().P() );
      sec_protons_T.push_back( secprongPart->momentumVec().E() - MinervaUnits::M_p );
      sec_protons_T_Calo.push_back( totalCalibESecondaryProton );


      //------------------------------------------------
      // dEdx Tool variations for Secondary Protons
      //------------------------------------------------
      if( secprongPart->hasDoubleData("score1_Mass_Up") ) {
	sec_protons_score1_Mass_Up.push_back( secprongPart->getDoubleData("score1_Mass_Up") - proton_score1 );
	sec_protons_E_Mass_Up.push_back( secprongPart->getDoubleData("FitE_Mass_Up") - proton_E );
      }
      if( secprongPart->hasDoubleData("score1_Mass_Down") ) {
	sec_protons_score1_Mass_Down.push_back( secprongPart->getDoubleData("score1_Mass_Down") - proton_score1 );
	sec_protons_E_Mass_Down.push_back( secprongPart->getDoubleData("FitE_Mass_Down") - proton_E );
      }
      if( secprongPart->hasDoubleData("score1_BetheBloch_Up") ) {
	sec_protons_score1_BetheBloch_Up.push_back( secprongPart->getDoubleData("score1_BetheBloch_Up") - proton_score1 );
	sec_protons_E_BetheBloch_Up.push_back( secprongPart->getDoubleData("FitE_BetheBloch_Up") - proton_E );

	debug() << "Proton Score1 BB Up Variation " << secprongPart->getDoubleData("score1_BetheBloch_Up") << endmsg;
      }
      if( secprongPart->hasDoubleData("score1_BetheBloch_Down") ) {
	sec_protons_score1_BetheBloch_Down.push_back( secprongPart->getDoubleData("score1_BetheBloch_Down") - proton_score1 );
	sec_protons_E_BetheBloch_Down.push_back( secprongPart->getDoubleData("FitE_BetheBloch_Down") - proton_E );

	debug() << "Proton Score1 BB Down Variation " << secprongPart->getDoubleData("score1_BetheBloch_Down") << endmsg;
      }
      if( secprongPart->hasDoubleData("score1_MEU_Up") ) {
	sec_protons_score1_MEU_Up.push_back( secprongPart->getDoubleData("score1_MEU_Up") - proton_score1 );
	sec_protons_E_MEU_Up.push_back( secprongPart->getDoubleData("FitE_MEU_Up") - proton_E );
      }
      if( secprongPart->hasDoubleData("score1_MEU_Down") ) {
	sec_protons_score1_MEU_Down.push_back( secprongPart->getDoubleData("score1_MEU_Down") - proton_score1 );
	sec_protons_E_MEU_Down.push_back( secprongPart->getDoubleData("FitE_MEU_Down") - proton_E );
      }
      if( secprongPart->hasDoubleData("score1_Birks") ) {
	sec_protons_score1_Birks.push_back( secprongPart->getDoubleData("score1_Birks") - proton_score1 );
	sec_protons_E_Birks.push_back( secprongPart->getDoubleData("FitE_Birks") - proton_E );
      }

      //----------------------------------------
      // Rotated proton's angle w.r.t beam
      //----------------------------------------
      sec_protons_theta.push_back( m_minCoordSysTool->thetaWRTBeam(secprongPart->momentumVec()) );

    } //End of for loop over Secondary proton prongs

  } else verbose() << "No secondary protons were found" << endmsg;

  //--------------------------------------------------------
  //! Set pion scores
  //--------------------------------------------------------
  //Primary prong pion particle
  if( pionPart) {
    if ( !pionPart->isMultiMass() ){
      pion_score  = pionPart->score();
      pion_score1 = pionPart->getDoubleData(ParticleExtraDataDefs::dEdXScore1());
      pion_score2 = pionPart->getDoubleData(ParticleExtraDataDefs::dEdXScore2());
    }
  }

  if (secondaryProtonsFound) {
    for(ProngVect::iterator secprongs = secondaryProtonProngs.begin(); secprongs != secondaryProtonProngs.end(); ++secprongs) {
      double secproton_pion_score = -9999., secproton_pion_score1 = -9999., secproton_pion_score2 = -999.;

      SmartRefVector<Minerva::Particle> secpionparticles = (*secprongs)->particlesWithIDCode(Minerva::Particle::Pion, "dEdX");
      if (secpionparticles.size()>0) {
	SmartRef<Minerva::Particle> secprongPart = secpionparticles[0];
	if( !secprongPart->isMultiMass() ) {
	  secproton_pion_score  = secprongPart->score();
	  secproton_pion_score1 = secprongPart->getDoubleData(ParticleExtraDataDefs::dEdXScore1());
	  secproton_pion_score2 = secprongPart->getDoubleData(ParticleExtraDataDefs::dEdXScore2());

	  sec_protons_pion_scores.push_back( secproton_pion_score );
	  sec_protons_pion_scores1.push_back( secproton_pion_score1 );
	  sec_protons_pion_scores2.push_back( secproton_pion_score2 );
	}
      }
    }
  }

  //--------------------------------------------------------------------------------
  //! Reconstruct Neutrino Energy based on CCQE hypotheses with muon information
  //--------------------------------------------------------------------------------
  double enu_muon = -9999., enu_proton = -9999., q2_muon = -9999.;
  enu_muon = PhysicsCalculator->nuEnergyCCQE( muon_E, muon_P, muon_theta, muon_charge, m_nuCCQEBindingEnergyMeV );
  q2_muon  = PhysicsCalculator->qSquaredCCQE( muon_E, muon_P, muon_theta, muon_charge, m_nuCCQEBindingEnergyMeV );

  //--------------------------------------------------------
  //! Reconstruct Neutrino Energy using proton kinematics
  //--------------------------------------------------------
  if (protonFound)
    enu_proton = m_protonUtils->nuEnergyCCQE(proton_theta,proton_T,m_nuCCQEBindingEnergyMeV);

  //! Construct neutrino hypothesis
  Minerva::NeutrinoInt* ccqeHyp = new Minerva::NeutrinoInt( "CCQENu" );
  nuInt.push_back( ccqeHyp );

  ccqeHyp->setNeutrinoFlavor( Minerva::NeutrinoInt::MuonFlavor );
  ccqeHyp->setInteractionCurrent( Minerva::NeutrinoInt::ChargedCurrent );
  ccqeHyp->setInteractionType( Minerva::NeutrinoInt::QuasiElastic );

  ccqeHyp->setNeutrinoHelicity( PhysicsCalculator->getHelicity( muon_charge ) );
  ccqeHyp->setLeptonEnergy( muonPart->momentumVec() );
  ccqeHyp->setEnergy( enu_muon ); //should I also use enu_proton somewhow?
  ccqeHyp->setVertex( event->interactionVertex() );

  ccqeHyp->setDoubleData( "muon_P", muon_P );
  ccqeHyp->setDoubleData( "muon_E", muon_E );
  ccqeHyp->setDoubleData( "muon_T", muon_T );
  ccqeHyp->setDoubleData( "muon_theta", muon_theta );
  ccqeHyp->setDoubleData( "muon_score", muon_score );
  ccqeHyp->setDoubleData( "enu_muon", enu_muon );
  ccqeHyp->setDoubleData( "proton_P_fromdEdx", proton_P );
  ccqeHyp->setDoubleData( "proton_E_fromdEdx", proton_E );
  ccqeHyp->setDoubleData( "proton_T_fromdEdx", proton_T );
  ccqeHyp->setDoubleData( "proton_theta_fromdEdx", proton_theta );
  ccqeHyp->setDoubleData( "proton_calib_energy", totalCalibEPrimaryProton );
  ccqeHyp->setDoubleData( "enu_proton", enu_proton );
  ccqeHyp->setDoubleData( "proton_score", proton_score );
  ccqeHyp->setDoubleData( "proton_score1", proton_score1 );
  ccqeHyp->setDoubleData( "proton_score2", proton_score2 );
  ccqeHyp->setDoubleData( "pion_score", pion_score );
  ccqeHyp->setDoubleData( "pion_score1", pion_score1 );
  ccqeHyp->setDoubleData( "pion_score2", pion_score2 );
  ccqeHyp->setContainerDoubleData( "sec_protons_E_fromdEdx", sec_protons_E );
  ccqeHyp->setContainerDoubleData( "sec_protons_P_fromdEdx", sec_protons_P );
  ccqeHyp->setContainerDoubleData( "sec_protons_T_fromdEdx", sec_protons_T );
  ccqeHyp->setContainerDoubleData( "sec_protons_theta_fromdEdx", sec_protons_theta );
  ccqeHyp->setContainerDoubleData( "sec_protons_T_fromCalo", sec_protons_T_Calo );
  ccqeHyp->setContainerDoubleData( "sec_protons_proton_scores", sec_protons_proton_scores );
  ccqeHyp->setContainerDoubleData( "sec_protons_proton_scores1", sec_protons_proton_scores1 );
  ccqeHyp->setContainerDoubleData( "sec_protons_proton_scores2", sec_protons_proton_scores2 );
  ccqeHyp->setContainerDoubleData( "sec_protons_pion_scores", sec_protons_pion_scores );
  ccqeHyp->setContainerDoubleData( "sec_protons_pion_scores1", sec_protons_pion_scores1 );
  ccqeHyp->setContainerDoubleData( "sec_protons_pion_scores2", sec_protons_pion_scores2 );
  ccqeHyp->setQ2( q2_muon );

  //----------------------------------------------------------------
  //----------------------------------------------------------------

  ccqeHyp->setDoubleData("proton_endPointX",proton_endPointX);
  ccqeHyp->setDoubleData("proton_endPointY",proton_endPointY);
  ccqeHyp->setDoubleData("proton_endPointZ",proton_endPointZ);

  ccqeHyp->setDoubleData("proton_startPointX",proton_startPointX);
  ccqeHyp->setDoubleData("proton_startPointY",proton_startPointY);
  ccqeHyp->setDoubleData("proton_startPointZ",proton_startPointZ);

  ccqeHyp->setDoubleData("proton_p",proton_p);
  ccqeHyp->setDoubleData("proton_px",proton_px);
  ccqeHyp->setDoubleData("proton_py",proton_py);
  ccqeHyp->setDoubleData("proton_pz",proton_pz);
  ccqeHyp->setDoubleData("proton_e",proton_e);

  ccqeHyp->setDoubleData("proton_theta",proton_theta);
  ccqeHyp->setDoubleData("proton_thetaX",proton_thetaX);
  ccqeHyp->setDoubleData("proton_thetaY",proton_thetaY);
  ccqeHyp->setDoubleData("proton_phi",proton_phi);

  ccqeHyp->setDoubleData("proton_ekin", proton_ekin);
  ccqeHyp->setDoubleData("proton_enu", proton_enu);
  ccqeHyp->setDoubleData("proton_q2", proton_q2);

  //--------------------------------------
  //! dEdx biasing information
  //--------------------------------------
  ccqeHyp->setDoubleData( "proton_score1_Mass_biasUp", proton_score1_Mass_Up );
  ccqeHyp->setDoubleData( "proton_score1_Mass_biasDown", proton_score1_Mass_Down );
  ccqeHyp->setDoubleData( "proton_score1_BetheBloch_biasUp", proton_score1_BetheBloch_Up );
  ccqeHyp->setDoubleData( "proton_score1_BetheBloch_biasDown", proton_score1_BetheBloch_Down );
  ccqeHyp->setDoubleData( "proton_score1_MEU_biasUp", proton_score1_MEU_Up );
  ccqeHyp->setDoubleData( "proton_score1_MEU_biasDown", proton_score1_MEU_Down );
  ccqeHyp->setDoubleData( "proton_score1_Birks_bias", proton_score1_Birks );
  ccqeHyp->setDoubleData( "proton_E_Mass_biasUp", proton_E_Mass_Up );
  ccqeHyp->setDoubleData( "proton_E_Mass_biasDown", proton_E_Mass_Down );
  ccqeHyp->setDoubleData( "proton_E_BetheBloch_biasUp", proton_E_BetheBloch_Up );
  ccqeHyp->setDoubleData( "proton_E_BetheBloch_biasDown", proton_E_BetheBloch_Down );
  ccqeHyp->setDoubleData( "proton_E_MEU_biasUp", proton_E_MEU_Up );
  ccqeHyp->setDoubleData( "proton_E_MEU_biasDown", proton_E_MEU_Down );
  ccqeHyp->setDoubleData( "proton_E_Birks_bias", proton_E_Birks );

  ccqeHyp->setContainerDoubleData( "sec_protons_score1_Mass_biasUp", sec_protons_score1_Mass_Up );
  ccqeHyp->setContainerDoubleData( "sec_protons_score1_Mass_biasDown", sec_protons_score1_Mass_Down );
  ccqeHyp->setContainerDoubleData( "sec_protons_score1_BetheBloch_biasUp", sec_protons_score1_BetheBloch_Up );
  ccqeHyp->setContainerDoubleData( "sec_protons_score1_BetheBloch_biasDown", sec_protons_score1_BetheBloch_Down );
  ccqeHyp->setContainerDoubleData( "sec_protons_score1_MEU_biasUp", sec_protons_score1_MEU_Up );
  ccqeHyp->setContainerDoubleData( "sec_protons_score1_MEU_biasDown", sec_protons_score1_MEU_Down );
  ccqeHyp->setContainerDoubleData( "sec_protons_score1_Birks_bias", sec_protons_score1_Birks );
  ccqeHyp->setContainerDoubleData( "sec_protons_E_Mass_biasUp", sec_protons_E_Mass_Up );
  ccqeHyp->setContainerDoubleData( "sec_protons_E_Mass_biasDown", sec_protons_E_Mass_Down );
  ccqeHyp->setContainerDoubleData( "sec_protons_E_BetheBloch_biasUp", sec_protons_E_BetheBloch_Up );
  ccqeHyp->setContainerDoubleData( "sec_protons_E_BetheBloch_biasDown", sec_protons_E_BetheBloch_Down );
  ccqeHyp->setContainerDoubleData( "sec_protons_E_MEU_biasUp", sec_protons_E_MEU_Up );
  ccqeHyp->setContainerDoubleData( "sec_protons_E_MEU_biasDown", sec_protons_E_MEU_Down );
  ccqeHyp->setContainerDoubleData( "sec_protons_E_Birks_bias", sec_protons_E_Birks );



  fillMinosMuonBranches( ccqeHyp, muonProng );
  //! Fill the systematic shifts. See SystematicShiftsExtensions.cc.
  fillSystematicShiftsBranches( ccqeHyp, event );

  debug() << "Exiting CCQENu::interpretEvent() now ....." << endmsg;

  return StatusCode::SUCCESS;
} //End of interpretEvent( )


//=============================================================================
// Finalize --
//=============================================================================

StatusCode CCQENu::finalize() {

  StatusCode sc = this->MinervaAnalysisTool::finalize();
  if( sc.isFailure() ) { return Error( "Failed to finalize!", sc ); }

  return sc;

}


//===================================================================================================================
// Investigate if it is plausible for the true event to be a signal event
// truthIsPlausible( ) is now a pure virtual function of MinervaAnalysisTool, so you must implement it.
// It is called automatically by PhysicsEventAnalysisAlg AFTER reconstructEvent() and interpretEvent() are run.
// If it returns false, the event is not included in the analysis ntuple
//===================================================================================================================
bool CCQENu::truthIsPlausible( const Minerva::PhysicsEvent *physEvent ) const {

  debug() << "Entering truthIsPlausible( ) now ..... " << endmsg;

  if( NULL == physEvent ) {
    debug() << "Physics Event is a NULL pointer - no sense in proceeding !" << endmsg;
    return false;
  }

  //This might need more work.
  //Look at all prongs. If ONE prong is the mc event as defined below then true else false
  if(!physEvent->hasInteractionVertex()){
    bool isPlausible = false;
    VertexVect used_vtx = physEvent->select<Minerva::Vertex>( "Used", "StartPoint" );
    for( Minerva::VertexVect::iterator itvtx=used_vtx.begin(); itvtx!=used_vtx.end(); ++itvtx ) {
      ProngVect primProngs; ProngVect unattachedProngs;
      m_objectAssociator->getProngs_fromSourceVertex( primProngs, unattachedProngs, *itvtx );
      for( ProngVect::const_iterator itProng = primProngs.begin(); itProng != primProngs.end(); ++itProng ) {
	if( (*itProng)->MinosTrack() || (*itProng)->MinosStub()) isPlausible = muonIsPlausible( (*itProng));
	if(isPlausible) return true;
      }
    }//end loop over vertices


    return false;
  }

  //------------------------------------------------------------------------------------------------------------
  //There are 2 methods available here. One uses muonIsPlausible( ), the other is a more general method.
  //The general method could be used for the muon or proton analysis, if using this tool.
  //------------------------------------------------------------------------------------------------------------
  if( m_useMuonIsPlausible ) {

    bool foundDeProng = false;
    ProngVect primaryProngs = physEvent->primaryProngs();
    if( primaryProngs.size() ) {
      for( ProngVect::iterator itProng = primaryProngs.begin(); itProng != primaryProngs.end(); ++itProng ) {
	if( (*itProng)->hasIntData("look_for_plausibility") ) {
	  if( (*itProng)->getIntData("look_for_plausibility") == 1 ) {
	    foundDeProng = true;
	    bool is_muon_plausible = muonIsPlausible( (*itProng) );
	    if( !is_muon_plausible ) {
	      debug() << "This MC muon is not plausible because it has a MC energy fraction below threshold !" << endmsg;
	      return false;
	    } else {
	      debug() << "This MC muon is plausible !" << endmsg;
	      counter("muon_plausible")+=is_muon_plausible;
	      return true;
	    }
	  }
	} else {
	  debug() << "This primary Prong does not have look_for_plausibility set and is probably not a muon Prong !" << endmsg;
	}
      }
      if( !foundDeProng ) throw MinervaException( "truthIsPlausible: Did not find muon Prong amongst primary Prongs, even though you had marked it earlier !" );

    } else {
      debug() << "There are no Primary Prongs in this Physics Event !" << endmsg;
      return false;
    }

  } else {

    //------------------------------------------------------------------------------------------
    // Obtain a vector of Primary Prongs from the event
    // Should the other prongs (non-primary) be included here too ?
    // Find the longest track from all the prongs (could be muon, proton, etc.)
    // This relies on the assumption that rock muons are filtered out early on and are
    // not part of the physics event.
    //------------------------------------------------------------------------------------------
    SmartRef<Minerva::Track> deLongestTrack;
    bool foundaTrack = findLongestMinervaTrack( physEvent, deLongestTrack );
    verbose() << "Inside truthIsPlausible(): Value of foundaTrack " << foundaTrack << endmsg;
    if( foundaTrack && deLongestTrack->nNodes() ) {
      debug() <<"Inside truthIsPlausible(): Chi2 of deLongestTrack from findLongestMinervaTrack( ) is " << deLongestTrack->chi2PerDoF() <<" Nodes: "<< deLongestTrack->nNodes() << endmsg;
    } else {
      debug() <<"Did not find any tracks in this PhysicsEvent !" << endmsg;
      return false;
    }

    //----------------------------------------------------------------------------------------------------------------
    // Find all the Prongs that hold this track and verify if they all carry MC identities
    // If not, then the track probably comes from a data overlay and not MC. Hence it is not your signal event !
    //----------------------------------------------------------------------------------------------------------------
    SmartRefVector<Minerva::Prong> prongsFromLongestTrack;
    StatusCode sc = m_objectAssociator->getProngs_containingMinervaTrack( prongsFromLongestTrack, deLongestTrack );
    if( sc.isFailure() ) {
      debug() << "The method did not work correctly!" << endmsg;
      return false;
    }

    if( prongsFromLongestTrack.size() ) {
      for( SmartRefVector<Minerva::Prong>::iterator itProng = prongsFromLongestTrack.begin(); itProng != prongsFromLongestTrack.end(); ++itProng ) {
	if( !prongIsMC( *itProng ) ) return false;
      }
    } else {
      throw MinervaException( "The longest track does not belong to a Prong! Please investigate!" );
    }

  } //End of condition m_useMuonIsPlausible

  debug() << "Exiting truthIsPlausible( ) now ..... " << endmsg;
  return true;

} //End of truthIsPlausible( )


//=============================================================================
// Tag truth events as signal
//=============================================================================
StatusCode CCQENu::tagTruth(Minerva::GenMinInteraction* truth) const {

  debug()<<"CCQENu::tagTruth"<<endmsg;
  fillGenieWeightBranches( truth );
  // for HadronReweightTool
  fillHadronReweightBranches( truth );

  //--------------------------------
  // Is it inside fiducial vol ?
  //--------------------------------
  bool is_fiducial = FiducialPointTool->isFiducial( truth, m_signalApothem, m_signalUpstreamZ, m_signalDownstreamZ );
  if( truth ) {
    truth->filtertaglist()->setOrAddFilterTag( "is_fiducial", is_fiducial );
  }

  //!@todo Tag true-CCQE events and fill variables for efficiency corrections...

  return StatusCode::SUCCESS;
}

void CCQENu::tagProtonProngTruth( Minerva::PhysicsEvent *event, SmartRef<Minerva::Prong> protonProng ) const {

  StatusCode sc;
  if ( !haveNeutrinoMC() ) return;

  const Minerva::TG4Trajectory* prong_traj = NULL;
  double prong_traj_fractionE = -1.0, prong_traj_otherE = -1.0;
  int prong_traj_PDG = -1, prong_traj_ID;
  std::vector<double> prong_traj_4p;
  std::vector<double> prong_traj_final_tpos;

  //------------------------------------------------------------------
  //! Let's tag the highest energy primary trajectory first (proton candidate)
  //------------------------------------------------------------------
  sc = TruthMatcher->getPrimaryTG4Trajectory(protonProng, prong_traj, prong_traj_fractionE, prong_traj_otherE);
  if (sc == StatusCode::FAILURE){
    debug()<<"Truth Matching Failed while getting the proton candidate trajectory"<<endmsg;
    return;
  }
  //! Set proton candidate PDG, four-momentum and position
  prong_traj_PDG = prong_traj->GetPDGCode();
  prong_traj_ID = prong_traj->GetTrackId();

  prong_traj_4p.push_back( prong_traj->GetInitialMomentum().E() );
  prong_traj_4p.push_back( prong_traj->GetInitialMomentum().px() );
  prong_traj_4p.push_back( prong_traj->GetInitialMomentum().py() );
  prong_traj_4p.push_back( prong_traj->GetInitialMomentum().pz() );

  prong_traj_final_tpos.push_back( prong_traj->GetFinalPosition().T() );
  prong_traj_final_tpos.push_back( prong_traj->GetFinalPosition().x() );
  prong_traj_final_tpos.push_back( prong_traj->GetFinalPosition().y() );
  prong_traj_final_tpos.push_back( prong_traj->GetFinalPosition().z() );

  event->setIntData("proton_prong_PDG", prong_traj_PDG);
  event->setIntData("proton_prong_traj_ID", prong_traj_ID);
  event->setContainerDoubleData("proton_prong_4p", prong_traj_4p);
  event->setContainerDoubleData("proton_prong_tpos", prong_traj_final_tpos);

}

std::vector<double> CCQENu::tagMichelProngTruth( Minerva::Prong michelProng ) const {

  StatusCode sc;

  //  Minerva::Prong *tmp_prong = &michelProng;
  std::vector<const Minerva::IDCluster*> idclusters;
  SmartRefVector<Minerva::IDCluster> clustersFromProng = michelProng.getAllIDClusters();
  idclusters.insert(idclusters.begin(), clustersFromProng.begin(), clustersFromProng.end());
  const Minerva::TG4Trajectory* prong_traj = NULL;
  const Minerva::TG4Trajectory* prong_parent_traj = NULL;
  double prong_traj_fractionE = -1.0, prong_traj_otherE=-1.0;
  //  double prong_parent_traj_fractionE = -1.0, prong_parent_traj_otherE=-1.0;
  double prong_traj_PDG = -1;
  double prong_parent_traj_PDG = -1;
  std::vector<double> bestPart;
  bestPart.push_back(prong_traj_PDG);
  bestPart.push_back(prong_parent_traj_PDG);
  bestPart.push_back(prong_traj_fractionE);
  if ( !haveNeutrinoMC() ) return bestPart;
  //------------------------------------------------------------------
  //! Let's tag the highest energy primary trajectory first (michel candidate)
  //------------------------------------------------------------------
  sc = TruthMatcher->getTG4Trajectory(idclusters, prong_traj, prong_traj_fractionE, prong_traj_otherE);
  if (sc == StatusCode::FAILURE){
    debug()<<"Truth Matching Failed while getting the michel candidate trajectory"<<endmsg;
    return bestPart;
  }
  prong_parent_traj = TruthMatcher->getPrimaryTG4Trajectory(prong_traj,false);
  //! Set michel candidate PDG, four-momentum and position
  prong_traj_PDG = prong_traj->GetPDGCode();
  prong_parent_traj_PDG = prong_parent_traj->GetPDGCode();
  bestPart[0] = prong_traj_PDG;
  bestPart[1] = prong_parent_traj_PDG;
  bestPart[2] = prong_traj_fractionE;
  debug() << "This is the matched information(pdg,pdg,fraction): (" <<bestPart[0]<<","<<bestPart[1] << "," << bestPart[2] << ")" << endmsg;


  return bestPart;
}

std::vector<double> CCQENu::tagBlobTruth( Minerva::IDBlob blob ) const {

  StatusCode sc;

  //  Minerva::Prong *tmp_prong = &blobProng;
  std::vector<const Minerva::IDDigit*> iddigits;
  SmartRefVector<Minerva::IDDigit> digitsFromBlob = blob.getAllDigits();
  iddigits.insert(iddigits.begin(), digitsFromBlob.begin(), digitsFromBlob.end());
  const Minerva::TG4Trajectory* blob_traj = NULL;
  const Minerva::TG4Trajectory* blob_parent_traj = NULL;
  double blob_traj_fractionE = -1.0, blob_traj_otherE=-1.0;

  double blob_traj_PDG = -1;
  double blob_parent_traj_PDG = -1;
  std::vector<double> bestPart;
  bestPart.push_back(blob_traj_PDG);
  bestPart.push_back(blob_parent_traj_PDG);
  bestPart.push_back(blob_traj_fractionE);
  if ( !haveNeutrinoMC() ) return bestPart;
  //------------------------------------------------------------------
  //! Let's tag the highest energy primary trajectory first (michel candidate)
  //------------------------------------------------------------------
  sc = TruthMatcher->getTG4Trajectory(iddigits, blob_traj, blob_traj_fractionE, blob_traj_otherE);
  if (sc == StatusCode::FAILURE){
    debug()<<"Truth Matching Failed while getting the blob candidate trajectory"<<endmsg;
    return bestPart;
  }
  blob_parent_traj = TruthMatcher->getPrimaryTG4Trajectory(blob_traj,false);
  //! Set michel candidate PDG, four-momentum and position
  blob_traj_PDG = blob_traj->GetPDGCode();
  blob_parent_traj_PDG = blob_parent_traj->GetPDGCode();
  bestPart[0] = blob_traj_PDG;
  bestPart[1] = blob_parent_traj_PDG;
  bestPart[2] = blob_traj_fractionE;
  debug() << "This is the matched information(pdg,pdg,fraction): (" <<bestPart[0]<<","<<bestPart[1] << "," << bestPart[2] << ")" << endmsg;


  return bestPart;
}

std::vector<double> CCQENu::tagDigitsTruth( SmartRefVector<Minerva::IDDigit> digits ) const {

  StatusCode sc;

  //  Minerva::Prong *tmp_prong = &blobProng;
  std::vector<const Minerva::IDDigit*> iddigits;
  iddigits.insert(iddigits.begin(), digits.begin(), digits.end());
  const Minerva::TG4Trajectory* digits_traj = NULL;
  const Minerva::TG4Trajectory* digits_parent_traj = NULL;
  double digits_traj_fractionE = -1.0, digits_traj_otherE=-1.0;

  double digits_traj_PDG = -1;
  double digits_parent_traj_PDG = -1;
  std::vector<double> bestPart;
  bestPart.push_back(digits_traj_PDG);
  bestPart.push_back(digits_parent_traj_PDG);
  bestPart.push_back(digits_traj_fractionE);
  if ( !haveNeutrinoMC() ) return bestPart;
  //------------------------------------------------------------------
  //! Let's tag the highest energy primary trajectory first (michel candidate)
  //------------------------------------------------------------------
  sc = TruthMatcher->getTG4Trajectory(iddigits, digits_traj, digits_traj_fractionE, digits_traj_otherE);
  if (sc == StatusCode::FAILURE){
    debug()<<"Truth Matching Failed while getting the digits candidate trajectory"<<endmsg;
    return bestPart;
  }
  digits_parent_traj = TruthMatcher->getPrimaryTG4Trajectory(digits_traj,false);
  //! Set michel candidate PDG, four-momentum and position
  digits_traj_PDG = digits_traj->GetPDGCode();
  digits_parent_traj_PDG = digits_parent_traj->GetPDGCode();
  bestPart[0] = digits_traj_PDG;
  bestPart[1] = digits_parent_traj_PDG;
  bestPart[2] = digits_traj_fractionE;
  debug() << "This is the matched information(pdg,pdg,fraction): (" <<bestPart[0]<<","<<bestPart[1] << "," << bestPart[2] << ")" << endmsg;


  return bestPart;
}


//==================================================
// createParticles
//==================================================
bool CCQENu::createParticles( Minerva::PhysicsEvent* event, Minerva::ProngVect& hadronProngs ) const
{
  bool status = true;

  ProngVect primaryProngs = event->primaryProngs();
  std::vector<Minerva::Particle::ID> particleHypotheses;
  particleHypotheses.push_back(Minerva::Particle::Pion);
  particleHypotheses.push_back(Minerva::Particle::Proton);

  for (ProngVect::iterator itProngs = primaryProngs.begin(); itProngs != primaryProngs.end(); ++itProngs) {

    // only non-muon prongs...
    if( (*itProngs)->filtertaglist()->filterTagExists( AnaFilterTags::PrimaryMuon() ) ) continue;

    hadronProngs.push_back(*itProngs);
    (*itProngs)->filtertaglist()->setOrAddFilterTag( m_primaryHadron, true );

    //Let's color hadron prongs
    m_hitTaggerTool->applyColorTag( *itProngs, m_hadronProngsColor );

    debug()<<"Make particles"<<endmsg;
    IParticleMakerTool::NameAliasListType toolsToUse;
    toolsToUse.push_back( std::make_pair("dEdXTool", "dEdXTool") );  // name, alias pair

    StatusCode sc_dEdX = m_particleMaker->makeParticles( *itProngs, particleHypotheses, toolsToUse );
    if (!sc_dEdX) {
      debug()<<"Could not make particles in prong!"<<endmsg;
    }
  }//end loop over primary prongs

  return status;
}


//=======================================================================================================
// Find proton prongs, pick the most energetic one and save the others in a vector of prongs
// -protonProng and protonPart are the Minerva::Prong and Minerva::Particle of the
//  most energetic proton found
// secondaryProtonProngs is a vector of all extra proton prongs found besides the most energetic one.
//=======================================================================================================
bool CCQENu::getProtonProngs( Minerva::ProngVect prongs, Minerva::ProngVect& secondaryProtonProngs, SmartRef<Minerva::Prong> &protonProng, SmartRef<Minerva::Particle> &protonPart ) const
{
  debug() << "Enter CCQENu::getProtonProngs" << endmsg;

  bool foundProton = false;
  double max_proton_E = -1.0;
  std::map< SmartRef<Minerva::Prong>, SmartRef<Minerva::Particle> > protonProngPartMap;

  //-- loop over prongs
  Minerva::ProngVect::iterator prong;
  for( prong = prongs.begin(); prong != prongs.end(); prong++ ){

    verbose() << "   prong bit-field signature = " << (*prong)->typeBitsToString() << endmsg;
    int numProtonPartsinProng  = 0;
    bool prongHasProtonPartandPassProtonCuts = false;
    SmartRef<Minerva::Particle> prongPart;

    //-- continue only with prongs that have tracks in the inner detector
    Minerva::TrackVect tracks = (*prong)->minervaTracks();
    if( tracks.empty() ) {
      warning() << "  This prong contains an empty vector of tracks, skipping!" << endmsg;
      continue;
    } else if( (*prong)->MinosTrack() || (*prong)->MinosStub() ) {
      verbose() << "  This is a MINOS matched prong, skipping!" << endmsg;
      continue;
    }

    //-- make use odMatch prongs an option
    if( !m_useOdMatchProtons && (*prong)->OdMatch() ) {
      verbose() << "  The prong is OdMatch, skipping!" << endmsg;
      continue;
    }

    //-- get the endpoint of the prong's last track
    SmartRef<Minerva::Track> track = tracks[tracks.size() -1];
    Gaudi::XYZPoint endpoint = track->lastState().position();

    //-- check the prong's destruction vertex is within the specify volume
    if( m_minCoordSysTool->inFiducial(endpoint.x(),endpoint.y(),endpoint.z(),m_ProtonApothem,m_ProtonZLow,m_ProtonZHigh) ) {

      //-- get the prong's particles
      Minerva::ParticleVect partHypVec = (*prong)->particles();
      Minerva::ParticleVect::iterator part;

      debug() << "  Considering a prong with " << partHypVec.size() << " particle hypotheses and " << tracks.size() << " tracks." << endmsg;

      //-- loop over all particle hypotheses
      for( part = partHypVec.begin(); part != partHypVec.end(); part++ ){

        debug() << "   Found a " << (*part)->idcode() << " with signature: "
            << (*part)->methodSignature() << " and score: " << (*part)->score() << endmsg;

        //---------------------------------------------------------------------------------------
        //! for now we will only accept protons whose mass was not change during the fit.
        //! there has not been sufficient studies for us to choose the proton-pion fit over
        //! the proton-proton fit based on the score alone.
        //!--------------------------------------------------------------------------------------

        //-- proton conditional statement
        if( (*part)->idcode() == Minerva::Particle::Proton && !(*part)->isMultiMass() ) {
          bool passProtonCut = false;

          debug() << "   Found a proton particle hypothesis!" << endmsg;

          //-- proton's requirements
          if( (*part)->methodSignature().find("dEdX") != std::string::npos ) {
            if ( track->chi2PerDoF() < m_maxProtonChi2 && (*part)->score() > m_minProtonScore ) {
              prongHasProtonPartandPassProtonCuts = true;
              passProtonCut = true;
            } else {
              debug() << "  Chi2/DoF and/or score is not consistent with a proton" << endmsg;
            }
          } else {
            debug() << "  Method signature is not consistent with a proton" << endmsg;
          }

          //-- proton's pass cut conditional
          if( passProtonCut ) {
            prongPart = (*part);
            debug() << "   Method signature and/or score is consistent with a proton!" << endmsg;
            numProtonPartsinProng++;

          } //-- if pass cut
        } //-- if proton particle
      } //-- for (parts)
    } //-- if pass z requirements
    debug() << "numProtonPartsinProng = " << numProtonPartsinProng << endmsg;

    debug() << "Adding prongs with one single proton part" <<endmsg;
    //-- Only accept prongs with one proton part
    if ( numProtonPartsinProng == 1 ){
      (*prong)->updateBestParticle( prongPart );
      protonProngPartMap[ (*prong) ] = prongPart;
      (*prong)->filtertaglist()->setOrAddFilterTag(m_secondaryProtons, true);
      if (prongPart->momentumVec().E() > max_proton_E)
        max_proton_E = prongPart->momentumVec().E();
    }
  } //-- for(prongs)

  //-----------------------------------------------------------------
  // -- Look for the most energetic proton prong
  //-----------------------------------------------------------------
  debug()<< " Look for most energetic proton prong in event " << endmsg;
  if (max_proton_E < 0 )
  {
    debug()<<" Ups, max_proton_E = " << max_proton_E << endmsg;
    return false;
  }
  for( std::map< SmartRef<Minerva::Prong>, SmartRef<Minerva::Particle> >::iterator it = protonProngPartMap.begin(); it != protonProngPartMap.end(); ++it ) {
    SmartRef<Minerva::Prong> prong = it->first;
    SmartRef<Minerva::Particle> part = it->second;
    if ( part->momentumVec().E() == max_proton_E )
    {
      protonProng = prong;
      protonPart  = part;
      foundProton = true;
      //-- color the proton prong
      m_hitTaggerTool->applyColorTag( protonProng, m_protonProngColor );
      //tag most energetic proton as the primary Proton
      protonProng->filtertaglist()->setFilterTag(m_secondaryProtons, false);
      protonProng->filtertaglist()->setOrAddFilterTag(m_primaryProton, true);
    }
    else
      secondaryProtonProngs.push_back( prong );
  }
  return foundProton;

}


//========================================
// ImprovedtagMichels
//========================================
bool CCQENu::ImprovedtagMichels(Minerva::PhysicsEvent* event, Minerva::GenMinInteraction* truth) const
{
  bool foundImprovedMichel = false;
  std::cout << "attempting new michel" << std::endl;
  //--tag truth michel
  if (truth){
    bool hasTruthMichelFiducial = hasTruthMichelElectron(event);
    event->setIntData("truth_improved_michel_electron",hasTruthMichelFiducial);
  }

  Minerva::DAQHeader *header;
  if( exist<Minerva::DAQHeader>( Minerva::DAQHeaderLocation::Default ))
  header = get<Minerva::DAQHeader>( Minerva::DAQHeaderLocation::Default );
  else{
    error() << "Could not locate DAQHeader" << endmsg;
    return StatusCode::FAILURE;
  }

  Minerva::GenMinHeader *genMinHeader;
  if( truth ){
    if( exist<Minerva::GenMinHeader>( Minerva::GenMinHeaderLocation::Default ) ){
      genMinHeader = get<Minerva::GenMinHeader>( Minerva::GenMinHeaderLocation::Default );
    }
    else {
      error() << "No GenMinHeader in this event!" << endmsg;
      return StatusCode::FAILURE;
    }
  }

  //--get the tagged muon prong
  Minerva::ProngVect primaryProngs = event->primaryProngs();
  SmartRef<Minerva::Prong> muonProng;

    for (ProngVect::iterator itProngs = primaryProngs.begin(); itProngs !=primaryProngs.end(); ++itProngs) {
      if( (*itProngs)->filtertaglist()->filterTagExists( AnaFilterTags::PrimaryMuon() ) ) {
        muonProng = *itProngs;
        break;
      }
    }

    //--look for michel electrons in vertices
    Minerva::Prong vtx_improvedmichelProng;
    const SmartRefVector<Minerva::Vertex> vertices = event->select<Minerva::Vertex>();
    debug()<<"Looking for Improved michels in " << vertices.size()-1<<" vertex points" <<endmsg;
    //event->setIntData("has_n_vertex_points", vertices.size()-1);
    warning()<<"Loking for Improved michels in " << vertices.size()-1<<" vertex points" <<endmsg;

    debug() << "Initiate set of containers for michel tool" << endmsg;
    std::vector<int> improved_michel_vertex_type;
    std::vector<int> improved_michel_in_vertex_point;

    std::vector<double> improved_michel_tvec;
    std::vector<double> improved_michel_tdiff_vec;
    std::vector<double> improved_michel_xvec;
    std::vector<double> improved_michel_yvec;
    std::vector<double> improved_michel_uvec;
    std::vector<double> improved_michel_vvec;
    std::vector<double> improved_michel_zvec;
    std::vector<double> improved_michel_dist_vec;
    std::vector<double> improved_michel_transdist_vec;
    std::vector<double> improved_michel_evis_vec;
    std::vector<double> improved_michel_ecalo_vec;

    std::vector<double> improved_michel_polarangle_vec;


    std::vector<double> improved_michel_hit_charges;
    std::vector<double> improved_michel_hit_times;
    std::vector<double> improved_michel_hit_time_diff_vtx;
    std::vector<double> improved_michel_hit_time_diff_cluster;
    std::vector<double> improved_michel_matched_energy_fraction;
    std::vector<double> improved_michel_data_energy_fraction;

    std::vector<int> improved_michel_match_vec;
    std::vector<int> improved_michel_view_vec;
    std::vector<int> improved_michel_matched_pdg;
    std::vector<int> improved_michel_matched_primary_pdg;
    std::vector<int> improved_michel_ndigits;
    std::vector<int> improved_michel_nplanes;
    std::vector<int> improved_michel_clussize;



    std::vector<int> improved_michel_fitCode_vec;
    std::vector<int> improved_michel_fitPass_vec;
    std::vector<double> improved_michel_MatchedEndDist_vec;
    std::vector<double> improved_michel_matchedvtx_energy_vec;

    std::vector<double> improved_michel_x1vec;
    std::vector<double> improved_michel_y1vec;
    std::vector<double> improved_michel_u1vec;
    std::vector<double> improved_michel_v1vec;
    std::vector<double> improved_michel_z1vec;

    std::vector<double> improved_michel_x2vec;
    std::vector<double> improved_michel_y2vec;
    std::vector<double> improved_michel_u2vec;
    std::vector<double> improved_michel_v2vec;
    std::vector<double> improved_michel_z2vec;

    std::vector<double>improved_michel_vtx_xvec;
    std::vector<double>improved_michel_vtx_yvec;
    std::vector<double>improved_michel_vtx_uvec;
    std::vector<double>improved_michel_vtx_vvec;
    std::vector<double>improved_michel_vtx_zvec;

    std::vector<double>improved_michel_vtxangle_vec;

    std::vector<int> has_michel_primary_particle_trackID;
    std::vector<int> true_michel_pdg;
    std::vector<double> true_michel_x1;
    std::vector<double> true_michel_y1;
    std::vector<double> true_michel_z1;
    std::vector<double> true_michel_x2;
    std::vector<double> true_michel_y2;
    std::vector<double> true_michel_z2;
    std::vector<int> michel_from_decay;
    std::vector<int> michel_parent_PDG;
    std::vector<int> michel_parent_trackID;
    std::vector<double> michel_true_time;
    //std::vector<int> michel_truematch;

    debug() << "Get muon time" << endmsg;
    double muonTime = m_recoObjTimeTool->trackVertexTime(muonProng->minervaTracks()[0]);
    const double max_distance = 300.0; //in mm

    debug() << "Finding Michel in Improved tool" << endmsg;

    //-- look for the Improved Michel
    //while( improved_michel ) {
    m_improvedmichelTool->Reset();
    m_improvedmichelTool->FindMichel(event->earliestSliceNumber());
    m_improvedmichelTool->ApplyQualityCuts();

    ////////////////////////////// =====================================================================================================================================

    //New Michel matching code.

    //Let's get our vector of fitted michel electrons!

    //I want to now loop over nmichels. And create a distance plot for each michel and a cluster in the event. Time cut on the cluster since it has to be BEFORE michel time.

     //also since I am only looking at fitted michels right now, we have 3D information on the michel with EndPoint1 and EndPoint2
     int nmichels = m_improvedmichelTool->GetMichelCount();

     debug() << "Finding Unused clusters" << endmsg;

     SmartRefVector<Minerva::IDCluster> allclusters = event->select<Minerva::IDCluster>("Used:Unused", "!LowActivity&!XTalkCandidate");
     SmartRefVector<Minerva::IDCluster> unusedclusters;

     const Minerva::IDClusterVect& muonClustersID = muonProng->getAllIDClusters();
     Minerva::IDClusterVect::iterator i_allClustersID = allclusters.begin();

     for (; i_allClustersID != allclusters.end(); ++i_allClustersID)
     {
       if( std::find( muonClustersID.begin(), muonClustersID.end(), (*i_allClustersID) ) != muonClustersID.end() ) continue;
       unusedclusters.push_back(*i_allClustersID);
     }

     double muontime = m_recoObjTimeTool->trackVertexTime(muonProng->minervaTracks()[0]);

     std::vector<double> mehtool_closestclusterX_distancevec;
     std::vector<double> mehtool_closestclusterU_distancevec;
     std::vector<double> mehtool_closestclusterV_distancevec;

     std::vector<double> mehtool_closestclusterX_energyvec;
     std::vector<double> mehtool_closestclusterU_energyvec;
     std::vector<double> mehtool_closestclusterV_energyvec;

     std::vector<double> mehtool_closestclusterX_timevec;
     std::vector<double> mehtool_closestclusterU_timevec;
     std::vector<double> mehtool_closestclusterV_timevec;

     std::vector<int> mehtool_closestclusterX_endpointvec;
     std::vector<int> mehtool_closestclusterU_endpointvec;
     std::vector<int> mehtool_closestclusterV_endpointvec;

     std::vector<int> mehtool_closestclusterX_nplanesvec;
     std::vector<int> mehtool_closestclusterU_nplanesvec;
     std::vector<int> mehtool_closestclusterV_nplanesvec;

     std::vector<double> mehtool_closestclusterXZ_distancevec;
     std::vector<double> mehtool_closestclusterUZ_distancevec;
     std::vector<double> mehtool_closestclusterVZ_distancevec;

     std::vector<int> mehtool_closestclusterX_ncluszvec;
     std::vector<int> mehtool_closestclusterU_ncluszvec;
     std::vector<int> mehtool_closestclusterV_ncluszvec;

     std::vector<int> mehtool_Xclus_michelmatchindexvec;
     std::vector<int> mehtool_Uclus_michelmatchindexvec;
     std::vector<int> mehtool_Vclus_michelmatchindexvec;


     std::vector<int> mehtool_nclustermatchpermichel;
     //std::vector<int> mehtool_nmichelmatchvec;

     std::vector<int> mehtool_michel_clusterindexvec;

     std::vector<int> mehtool_duplicate_michelindexvec;

     std::vector<double> mehtool_closestclusterX_zdistvec;
     std::vector<double> mehtool_closestclusterU_zdistvec;
     std::vector<double> mehtool_closestclusterV_zdistvec;

     std::vector<double> mehtool_closestclusterX_clustimevec;
     std::vector<double> mehtool_closestclusterU_clustimevec;
     std::vector<double> mehtool_closestclusterV_clustimevec;

     std::vector<double> mehtool_michel_timevec  ;
     std::vector<double> mehtool_michel_energyvec;

     std::vector<int> mehtool_michel_Xclustersvec;
     std::vector<int> mehtool_michel_Uclustersvec;
     std::vector<int> mehtool_michel_Vclustersvec;

     std::vector<double> mehtool_michel_x1_vec;
     std::vector<double> mehtool_michel_x2_vec;
     std::vector<double> mehtool_michel_u1_vec;
     std::vector<double> mehtool_michel_u2_vec;
     std::vector<double> mehtool_michel_v1_vec;
     std::vector<double> mehtool_michel_v2_vec;
     std::vector<double> mehtool_michel_z1_vec;
     std::vector<double> mehtool_michel_z2_vec;

     std::vector<double> mehtool_closestclusterX_posvec;
     std::vector<double> mehtool_closestclusterU_posvec;
     std::vector<double> mehtool_closestclusterV_posvec;
     std::vector<double> mehtool_closestclusterX_Z_posvec;
     std::vector<double> mehtool_closestclusterU_Z_posvec;
     std::vector<double> mehtool_closestclusterV_Z_posvec;

     std::vector<double> mehtool_michel_maxmeandiffvec;

     std::vector<int> mehtool_istrueMichelvec;

     std::vector<double> mehtool_michel_allmichelenergyvec;

     std::vector<int> mehtool_parent_PDG;
     std::vector<int> mehtool_michel_PDG;
     std::vector<int> mehtool_michel_from_decay;
     std::vector<double> mehtool_michel_truetime;

     std::vector<int> mehtool_michel_fitpass;
     std::vector<double> mehtool_matchedclus_fraction;

     std::vector<int>    mehtool_pion_primary_particle_trackID;
     std::vector<int>    mehtool_pion_pdg                      ;
     std::vector<double> mehtool_true_pion_x1vec               ;
     std::vector<double> mehtool_true_pion_y1vec               ;
     std::vector<double> mehtool_true_pion_z1vec               ;
     std::vector<double> mehtool_true_pion_x2vec               ;
     std::vector<double> mehtool_true_pion_y2vec               ;
     std::vector<double> mehtool_true_pion_z2vec               ;
     std::vector<int>    mehtool_pion_parent_PDG               ;
     std::vector<int>    mehtool_pion_from_decay               ;
     std::vector<int>    mehtool_pion_parent_trackID           ;
     std::vector<double> mehtool_pion_truetime                 ;



     std::cout <<"Looping over all " << nmichels <<" michels" << std::endl;

     // set counter for "matched" michel-ClUSTER

     int nmichelmatch = 0;

     int michelindex = 0;


     for (int imichel = 0; imichel < nmichels; imichel++)
     {
       double michelenergy = m_improvedmichelTool->GetMichelCalorimetricEnergy(imichel);
       mehtool_michel_allmichelenergyvec.push_back(michelenergy);

       int fitpass = m_improvedmichelTool->GetMichelFitPass(imichel);
       //if ( fitpass == 0) continue; //Only look at fitted Michels in the event


       mehtool_michel_fitpass.push_back(fitpass);

       //std::cout <<"Skipped UnFitted Michels" << std::endl;


       int michel_view  = m_improvedmichelTool->GetMichelViewCode(imichel);



       //if (michel_view < 20) continue; // remove 1 view michels


       std::cout << "Michel view is  "  << michel_view << std::endl;

       double michelX1 = m_improvedmichelTool->GetMichelEndpointX1(imichel);
       double michelY1 = m_improvedmichelTool->GetMichelEndpointY1(imichel);
       double michelU1 = m_improvedmichelTool->GetMichelEndpointU1(imichel);
       double michelV1 = m_improvedmichelTool->GetMichelEndpointV1(imichel);
       double michelZ1 = m_improvedmichelTool->GetMichelEndpointZ1(imichel);

       std::cout << "Getting Michel EndPoint 2 " << std::endl;

       double michelX2 = m_improvedmichelTool->GetMichelEndpointX2(imichel);
       double michelY2 = m_improvedmichelTool->GetMichelEndpointY2(imichel);
       double michelU2 = m_improvedmichelTool->GetMichelEndpointU2(imichel);
       double michelV2 = m_improvedmichelTool->GetMichelEndpointV2(imichel);
       double michelZ2 = m_improvedmichelTool->GetMichelEndpointZ2(imichel);

       double micheltime = m_improvedmichelTool->GetMichelTime(imichel);

       std::vector<double> zpositions_michclus;

       std::vector<const Minerva::IDCluster*> idclusters;
       std::vector<const Minerva::IDCluster*> michelclusters;
       const SmartRefVector<Minerva::IDCluster> clustersfromcandidate = m_improvedmichelTool->GetMichelClusters(imichel);
       idclusters.insert(idclusters.begin(), clustersfromcandidate.begin(), clustersfromcandidate.end());

       for( SmartRefVector<Minerva::IDCluster>::const_iterator itClus = clustersfromcandidate.begin(); itClus != clustersfromcandidate.end(); ++itClus ){
         double clus_t = (*itClus)->time();

         double zpos1 = (*itClus)->z();

         zpositions_michclus.push_back(zpos1);
         michelclusters.push_back(*itClus);

       }

       Minerva::TG4Trajectories* trajectories=NULL;

       Minerva::TG4Trajectory* trueMichel = NULL;
       const Minerva::TG4Trajectory* MichelParent = NULL;
       const Minerva::TG4Trajectory* MichelPrimaryParent = NULL;
       double fraction;
       double other_energy;


       int istrueMichel = 0;

         if (truth){
           trajectories = get<Minerva::TG4Trajectories>( "MC/TG4Trajectories" );
           fraction = TruthMatcher->getDataFraction(michelclusters);
         if(TruthMatcher->getDataFraction(michelclusters) < 0.5) { // check if overlay

           StatusCode parent_sc = TruthMatcher->getTG4Trajectory(michelclusters, MichelParent, fraction, other_energy); //find   TG4Trajectory that created the Michel leading the the Michel track
           if(!parent_sc) continue;

           //use final position of Michel parent to get Michel trajectory
           for(Minerva::TG4Trajectories::iterator it = trajectories->begin(); it != trajectories->end(); ++it) {
             Minerva::TG4Trajectory * traject = *it;

             //           if(traject->GetInitialPosition() == MichelParent->GetFinalPosition()) {
             if(traject->GetParentId() == MichelParent->GetTrackId()){
               if(abs(traject->GetPDGCode())==14) continue;
               trueMichel = traject;
               //Check if the Michel came from a decay or some kind of scattering
               if(trueMichel->GetProcessName().find("Decay") != std::string::npos)
               {
                 //std::cout << "Line 3143" << std::endl;
                 istrueMichel = 1;
                 mehtool_michel_from_decay.push_back(int(true));
                 mehtool_michel_PDG.push_back(trueMichel->GetPDGCode());
                 mehtool_parent_PDG.push_back(MichelParent->GetPDGCode());
                 mehtool_michel_truetime.push_back(trueMichel->GetInitialPosition().T());

                 break;
               }//If true Michel

             } //Where Michel CAme from
           } // For Michel Trajectory
          } //Get Data Fraction
        } //if truth

        mehtool_istrueMichelvec.push_back(istrueMichel);

       double sum =std::accumulate(zpositions_michclus.begin(), zpositions_michclus.end(), 0.0);

       double mean = sum/zpositions_michclus.size();

       std::vector<double> diff(zpositions_michclus.size());
       std::transform(zpositions_michclus.begin(), zpositions_michclus.end(), diff.begin(),
               std::bind2nd(std::minus<double>(), mean));
       double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
       double stdev = std::sqrt(sq_sum / zpositions_michclus.size());

       int ncluster = -1;

       double meandiff = -1.;

       for( SmartRefVector<Minerva::IDCluster>::const_iterator itClus = clustersfromcandidate.begin(); itClus != clustersfromcandidate.end(); ++itClus ){
         double clus_t = (*itClus)->time();

         double zpos1 = (*itClus)->z();

         double imeandiff = abs(mean - zpos1);

         if (imeandiff > meandiff) meandiff = imeandiff;

       }

       mehtool_michel_maxmeandiffvec.push_back(meandiff);

       //this is where I would remove that cluster from the michel candidate

       /*for( SmartRefVector<Minerva::IDCluster>::const_iterator itClus = clustersfromcandidate.begin(); itClus != clustersfromcandidate.end(); ++itClus ){
         double clus_t = (*itClus)->time();

         double zpos1 = (*itClus)->z();

         double imeandiff = abs(mean - zpos1);

         if (imeandiff == meandiff) ;

       }
       */

       // I need containers to collect michel distances to all clusters in each view

       std::vector<double> udistances;
       std::vector<double> xdistances;
       std::vector<double> vdistances;

       double closestxdist = 99999.;
       double closestudist = 99999.;
       double closestvdist = 99999.;

       Gaudi::XYZPoint end1;
       end1.SetCoordinates(michelX1, michelY1, michelZ1);
       Gaudi::XYZPoint end2;
       end2.SetCoordinates(michelX2, michelY2, michelZ2);


       SmartRefVector<Minerva::IDCluster> closestxclusters;
       SmartRefVector<Minerva::IDCluster> closestuclusters;
       SmartRefVector<Minerva::IDCluster> closestvclusters;

       //std::cout << "MICHEL TIME IS " << micheltime << " ns " << " << std::endl;
       //std::cout << "MICHEL END1 IS " << michelX1 << " X, " << michelU1 << " U, " << michelV1 << "V " << michelZ1 << "Z " << //std::endl;

       //std::cout << "MICHEL END2 IS " << michelX2 << " X, " << michelU2 << " U, " << michelV2 << "V " << michelZ2 << "Z" << std::endl;


      std::cout << "MICHEL TIME IS " << micheltime << " ns and Michel energy " <<  michelenergy  << " \n" << std::endl;
      std::cout << "MICHEL END1 IS " << michelX1 << " X, " << michelU1 << " U, " << michelV1 << "V " << michelZ1 << " Z \n" << std::endl;

      std::cout << "MICHEL END2 IS " << michelX2 << " X, " << michelU2 << " U, " << michelV2 << "V " << michelZ2 << " Z \n" << std::endl;


       for (SmartRefVector<Minerva::IDCluster>::iterator iclus = unusedclusters.begin(); iclus!= unusedclusters.end(); iclus++)
       {
         double clustime = (*iclus)->time();
         Minerva::IDCluster::View cview = (*iclus)->view();

         if (clustime > micheltime) continue; // Only want clusters that are before michel in time

         double muontimediff = abs(muontime - clustime);
         if (muontimediff > 0.5) continue; // Only get clusters associated with primary muon slice..

         double clusterenergy = (*iclus)->energy();

         double clusterz = (*iclus)->z();

         if (clusterenergy < 2.) continue;

         //std::cout << "CLUSTER Time " << clustime << " CLUSTER Position " << (*iclus)->position() << std::endl;


         //This is transverse distance - View distnace

         double viewdistance1 = m_mathTool->viewDistance((*iclus), end1 );
         double viewdistance2 = m_mathTool->viewDistance((*iclus), end2 );

         std::cout << "Printing out distance between cluster and michel dist1: " << viewdistance1 << " dist2: " << viewdistance2 << std::endl;

         if (abs(viewdistance1) < abs(viewdistance2)) {
           double zdist = abs(end1.Z() - clusterz);
           if (zdist > 100.) continue;
            if( cview == Minerva::IDCluster::X ) {
              xdistances.push_back(viewdistance1);

            } else if( cview == Minerva::IDCluster::U ) {
              udistances.push_back(viewdistance1);

            } else if( cview == Minerva::IDCluster::V ) {
              vdistances.push_back(viewdistance1);
            }

          }

         if (abs(viewdistance1) > abs(viewdistance2)) {
           double zdist = abs(end2.Z() - clusterz);
           if (zdist > 100.) continue;
           if( cview == Minerva::IDCluster::X ) {
             xdistances.push_back(viewdistance2);

           } else if( cview == Minerva::IDCluster::U ) {
             udistances.push_back(viewdistance2);

           } else if( cview == Minerva::IDCluster::V ) {
             vdistances.push_back(viewdistance2);
           }
          }


           double minx = -99999.9;
           double minu = -99999.9;
           double minv = -99999.9;

           for (unsigned int i = 0; i < xdistances.size(); i++)
           {
            if (abs(xdistances[i]) < abs(minx))
            minx = abs(xdistances[i]);
           }
           for (unsigned int i = 0; i < udistances.size(); i++)
           {
            if (abs(udistances[i]) < abs(minu))
            minu = abs(udistances[i]);
           }
           for (unsigned int i = 0; i < vdistances.size(); i++)
           {
            if (abs(vdistances[i]) < abs(minv))
            minv = abs(vdistances[i]);
           }


           closestxdist = minx;
           closestudist = minu;
           closestvdist = minv;

           std::cout << "CLOSEST X DISTANCE IS " << closestxdist << std::endl;
           std::cout << "CLOSEST U DISTANCE IS " << closestudist << std::endl;
           std::cout << "CLOSEST V DISTANCE IS " << closestvdist << std::endl;



       } // After looping over all clusters, I want to get the cluster in X and U and V that is closest to the michel. And then I want to see if there close to each other in Z. Then I can do 1 view, 2view, or 3 view matching to clusters based on how they are correlated in Z.


       // Now I take the closest distance values and redo the matching and save my closest clusters in a vector!

       int iclusindex = 0;

       int nclustermatch = 0;
       for (SmartRefVector<Minerva::IDCluster>::iterator iclus = unusedclusters.begin(); iclus!= unusedclusters.end(); iclus++)
       {

         std::cout << "Line 3170 " <<  std::endl;

         double clustime = (*iclus)->time();
         Minerva::IDCluster::View cview = (*iclus)->view();

         ++iclusindex;

         if (clustime > micheltime) continue; // Only want clusters that are before michel in time
         double clusterenergy = (*iclus)->energy();

         if (clusterenergy < 2.) continue;

         double viewdistance1 = m_mathTool->viewDistance( (*iclus), end1 );
         double viewdistance2 = m_mathTool->viewDistance((*iclus), end2 );

         double clusterz = (*iclus)->z();

         double cluspos = (*iclus)->position();

         double clustertimediff = micheltime - clustime;
         std::cout << "Line 3188 " <<  std::endl;
         if (abs(viewdistance1) < abs(viewdistance2))
         {
           std::cout << "Checking to see if vewdist1<viewdist2" << std::endl;
           double zdist = abs(end1.Z() - clusterz);
           std::cout << "Line 3192 " <<  std::endl;
           if (zdist > 100.) continue;
           std::cout << "Now checking to see if ID Cluster is X view" << std::endl;
           if( cview == Minerva::IDCluster::X ) {
             std::cout << "ID Cluster is X view! " <<  std::endl;
             double closedist = abs(abs(viewdistance1) - abs(closestxdist));
             if (closedist < 5.)
             { closestxclusters.push_back(*iclus);
             std::cout << "CLOSEST DISTANCE TO MICHEL END POINT 1 in X " << viewdistance1 <<  std::endl;
             std::cout << "CLOSEST CLUSTER HAS POSTION X " << (*iclus)->position() <<  std::endl;
             mehtool_closestclusterX_timevec.push_back(clustertimediff);
             mehtool_closestclusterX_energyvec.push_back(clusterenergy);
             mehtool_closestclusterX_distancevec.push_back(viewdistance1);

             mehtool_closestclusterX_endpointvec.push_back(1);

             mehtool_closestclusterXZ_distancevec.push_back(zdist);
             mehtool_closestclusterX_clustimevec.push_back(clustime);

             mehtool_closestclusterX_posvec.push_back(cluspos);
             mehtool_closestclusterX_Z_posvec.push_back(clusterz);


           }
           } else if( cview == Minerva::IDCluster::U ) {
             std::cout << "ID Cluster is U View " <<  std::endl;

             if (abs(abs(viewdistance1) - abs(closestudist)) < 5.)
             { closestuclusters.push_back(*iclus);
             std::cout << "CLOSEST DISTANCE TO MICHEL END POINT 1 in U " << viewdistance1 <<  std::endl;
             std::cout << "CLOSEST CLUSTER HAS POSTION U " << (*iclus)->position() <<  std::endl;
             mehtool_closestclusterU_timevec.push_back(clustertimediff);
             mehtool_closestclusterU_energyvec.push_back(clusterenergy);
             mehtool_closestclusterU_distancevec.push_back(viewdistance1);
             mehtool_closestclusterU_endpointvec.push_back(1);
             mehtool_closestclusterUZ_distancevec.push_back(zdist);
             mehtool_closestclusterU_clustimevec.push_back(clustime);
             mehtool_closestclusterU_posvec.push_back(cluspos);
             mehtool_closestclusterU_Z_posvec.push_back(clusterz);


           }

           } else if( cview == Minerva::IDCluster::V ) {
             std::cout << "ID Cluster is V View! " <<  std::endl;

             if (abs(abs(viewdistance1) - abs(closestvdist)) < 5.)
             { closestvclusters.push_back(*iclus);
             std::cout << "CLOSEST DISTANCE TO MICHEL END POINT 1 in V " << viewdistance1 <<  std::endl;
             std::cout << "CLOSEST CLUSTER HAS POSTION V " << (*iclus)->position() <<  std::endl;

             mehtool_closestclusterV_timevec.push_back(clustertimediff);
             mehtool_closestclusterV_energyvec.push_back(clusterenergy);
             mehtool_closestclusterV_distancevec.push_back(viewdistance1);
             mehtool_closestclusterV_endpointvec.push_back(1);
             mehtool_closestclusterVZ_distancevec.push_back(zdist);
             mehtool_closestclusterV_clustimevec.push_back(clustime);
             mehtool_closestclusterV_posvec.push_back(cluspos);
             mehtool_closestclusterV_Z_posvec.push_back(clusterz);

            }
          } //end of vview
         }



           //Now we need to do it for endpoint2 being closer:

           if ((abs(viewdistance1) > abs(viewdistance2)))
           {
             double zdist = abs(end2.Z() - clusterz);
             if (zdist > 100.) continue;
             if( cview == Minerva::IDCluster::X ) {
               std::cout << "Line 3262 " <<  std::endl;

               if (abs(abs(viewdistance2) - abs(closestxdist)) < 5.)
               { closestxclusters.push_back(*iclus);
               std::cout << "CLOSEST DISTANCE TO MICHEL END POINT 2 in X " << viewdistance2 <<  std::endl;
               std::cout << "CLOSEST CLUSTER HAS POSTION X " << (*iclus)->position() <<  std::endl;

               mehtool_closestclusterX_timevec.push_back(clustertimediff);
               mehtool_closestclusterX_energyvec.push_back(clusterenergy);
               mehtool_closestclusterX_distancevec.push_back(viewdistance2);
               mehtool_closestclusterX_endpointvec.push_back(2);
               mehtool_closestclusterXZ_distancevec.push_back(zdist);
               mehtool_closestclusterX_clustimevec.push_back(clustime);

               mehtool_closestclusterX_posvec.push_back(cluspos);
               mehtool_closestclusterX_Z_posvec.push_back(clusterz);


             }
             } else if( cview == Minerva::IDCluster::U ) {
               std::cout << "Line 3278 " <<  std::endl;

               if (abs(abs(viewdistance2) - abs(closestudist)) < 5.)
               { closestuclusters.push_back(*iclus);
               std::cout << "CLOSEST DISTANCE TO MICHEL END POINT 2 in U " << viewdistance2 <<  std::endl;
               std::cout << "CLOSEST CLUSTER HAS POSTION U " << (*iclus)->position() <<  std::endl;
               mehtool_closestclusterU_timevec.push_back(clustertimediff);
               mehtool_closestclusterU_energyvec.push_back(clusterenergy);
               mehtool_closestclusterU_distancevec.push_back(viewdistance2);
               mehtool_closestclusterU_endpointvec.push_back(2);
               mehtool_closestclusterUZ_distancevec.push_back(zdist);
               mehtool_closestclusterU_clustimevec.push_back(clustime);
               mehtool_closestclusterU_posvec.push_back(cluspos);
               mehtool_closestclusterU_Z_posvec.push_back(clusterz);

             }

             } else if( cview == Minerva::IDCluster::V ) {
               std::cout << "Line 3296 " <<  std::endl;

               if (abs(abs(viewdistance2) - abs(closestvdist)) < 5.)
               { closestvclusters.push_back(*iclus);
               std::cout << "CLOSEST DISTANCE TO MICHEL END POINT 2 in V " << viewdistance2 <<  std::endl;
               std::cout << "CLOSEST CLUSTER HAS POSTION V " << (*iclus)->position() <<  std::endl;

               mehtool_closestclusterV_timevec.push_back(clustertimediff);
               mehtool_closestclusterV_energyvec.push_back(clusterenergy);
               mehtool_closestclusterV_distancevec.push_back(viewdistance2);
               mehtool_closestclusterV_endpointvec.push_back(2);
               mehtool_closestclusterVZ_distancevec.push_back(zdist);
               mehtool_closestclusterV_clustimevec.push_back(clustime);
               mehtool_closestclusterV_posvec.push_back(cluspos);
               mehtool_closestclusterV_Z_posvec.push_back(clusterz);

             }

             }
           }// end of abs(viewdistance1) > abs(viewdistance2)

           std::cout << "End of looping over all unused clusters!" << std::endl;
             int nclusx = closestxclusters.size();
             int nclusu = closestxclusters.size();
             int nclusv = closestxclusters.size();




             if (nclusx > 0 || nclusu > 0 || nclusv > 0)
             {
               mehtool_michel_clusterindexvec.push_back(iclusindex);


             }

            }// End of Cluster matching loop. At the end of this loop, we should have three closest untracked clusters to the michel!


       //From here, we can get the information we want from the clusters!
       //1. We want to see if they are close in Z
       //2. We want to get position, distance, slicenumber, energy, and views of these clusters
       //3. We want to also find out which end point the cluster is matched to.

       std::vector<const Minerva::IDCluster*> matchedclusters;
       SmartRefVector<Minerva::IDCluster> picandidateclusters;

       for (SmartRefVector<Minerva::IDCluster>::iterator iclus = closestxclusters.begin(); iclus != closestxclusters.end(); iclus++)
       {

         std::cout << "ClUSTER time (ns)" << (*iclus)->time() << " view " << (*iclus)->view() << " position " << (*iclus)->position() << " energy " << (*iclus)->energy() << "  === \n" << std::endl;
         matchedclusters.push_back(*iclus);

       }

       for (SmartRefVector<Minerva::IDCluster>::iterator iclus = closestuclusters.begin(); iclus != closestuclusters.end(); iclus++)
       {
         std::cout << "Cluster time (ns)" << (*iclus)->time() << " view " << (*iclus)->view() << " position " << (*iclus)->position() << " energy " << (*iclus)->energy() << "  === \n" << std::endl;
         matchedclusters.push_back(*iclus);

       }

       for (SmartRefVector<Minerva::IDCluster>::iterator iclus = closestvclusters.begin(); iclus != closestvclusters.end(); iclus++)
       {

         std::cout << "Cluster time (ns)" << (*iclus)->time() << " view " << (*iclus)->view() << " position " << (*iclus)->position() << " energy " << (*iclus)->energy() << "  === \n" << std::endl;
         matchedclusters.push_back(*iclus);
       }

       mehtool_closestclusterX_ncluszvec.push_back(closestxclusters.size());
       mehtool_closestclusterU_ncluszvec.push_back(closestuclusters.size());
       mehtool_closestclusterV_ncluszvec.push_back(closestvclusters.size());


       std::cout << "Getting Truth Pion info " << std::endl;
       Minerva::TG4Trajectories* pioncantrajectories=NULL;

       Minerva::TG4Trajectory* truePion = NULL;
       const Minerva::TG4Trajectory* PionParent = NULL;
       const Minerva::TG4Trajectory* PionPrimaryParent = NULL;
       double pionfraction;
       double pion_other_energy;


       int istruePion = 0;

       if (truth){
         std::cout << "Getting Truth Pion Trajectories " << std::endl;
         pioncantrajectories = get<Minerva::TG4Trajectories>( "MC/TG4Trajectories" );

         std::cout << "Using Truth Matcher " << std::endl;

         pionfraction = TruthMatcher->getDataFraction(matchedclusters);
         std::cout << "Getting Data Fraction" << std::endl;

       if(TruthMatcher->getDataFraction(matchedclusters) < 0.5) { // check if overlay
         std::cout << "Getting trajectories using truth matcher" << std::endl;

         StatusCode parent_sc = TruthMatcher->getTG4Trajectory(matchedclusters, PionParent, pionfraction, pion_other_energy); //find   TG4Trajectory that created the Michel leading the the Michel track

         std::cout << "Got Trajectories now continueing if there is none" << std::endl;

         if(!parent_sc) continue;

         //use final position of Michel parent to get Michel trajectory
         std::cout << "Looping over trajectories" << std::endl;

         for(Minerva::TG4Trajectories::iterator it = pioncantrajectories->begin(); it != pioncantrajectories->end(); ++it) {
           Minerva::TG4Trajectory * traject = *it;
           std::cout << "Got Trajectory" << std::endl;


           //           if(traject->GetInitialPosition() == MichelParent->GetFinalPosition()) {
           if(traject->GetParentId() == PionParent->GetTrackId()){
             if(abs(traject->GetPDGCode())==14) continue; //avoiding nu
             truePion = traject;
             //Check if the Michel came from a decay or some kind of scattering
             if(truePion->GetProcessName().find("Decay") != std::string::npos)
             {
               //std::cout << "Line 3143" << std::endl;
               if (abs(truePion->GetPDGCode()) == 211){
                 istruePion = 1;
               }
               mehtool_matchedclus_fraction.push_back(pionfraction);
               mehtool_pion_from_decay.push_back(int(true));
               mehtool_pion_pdg.push_back(truePion->GetPDGCode());
               mehtool_pion_parent_PDG.push_back(PionParent->GetPDGCode());
               mehtool_pion_truetime.push_back(truePion->GetInitialPosition().T());

               mehtool_true_pion_x1vec.push_back(truePion->GetInitialPosition().X());
               mehtool_true_pion_y1vec.push_back(truePion->GetInitialPosition().Y());
               mehtool_true_pion_z1vec.push_back(truePion->GetInitialPosition().Z());
               mehtool_true_pion_x2vec.push_back(truePion->GetFinalPosition().X());
               mehtool_true_pion_y2vec.push_back(truePion->GetFinalPosition().Y());
               mehtool_true_pion_z2vec.push_back(truePion->GetFinalPosition().Z());

               break;
             }//If true Pion
           } //Where Pion CAme from
         } // For Pion Trajectory
        } //Get Data Fraction
      } //if truth

       int nclusx = closestxclusters.size();
       int nclusu = closestuclusters.size();
       int nclusv = closestvclusters.size();

       mehtool_closestclusterV_ncluszvec.push_back(nclusv);
       mehtool_closestclusterX_ncluszvec.push_back(nclusx);
       mehtool_closestclusterU_ncluszvec.push_back(nclusu);
       mehtool_nclustermatchpermichel.push_back(nclustermatch);



       /*

       for (SmartRefVector<Minerva::IDCluster>::iterator pclus = picandidateclusters.begin()+1; pclus != matchedclusters.end(); pclus++)
       {
         Minerva::IDCluster::View cview = (*pclus)->view();
         double clustime = (*pclus)->time();
         double clusterenergy = (*pclus)->energy();
         double viewdistance1 = m_mathTool->viewDistance( (*pclus), end1 );
         double viewdistance2 = m_mathTool->viewDistance((*pclus), end2 );
         double clusterz = (*pclus)->z();
         double cluspos = (*pclus)->position();
         double clustertimediff = micheltime - clustime;


       }
       */

       SmartRefVector<Minerva::IDCluster> Xclustersmichel = m_improvedmichelTool->GetMichelXClusters(imichel);
       //std::cout << "Line 3392" << std::endl;

       SmartRefVector<Minerva::IDCluster> Uclustersmichel = m_improvedmichelTool->GetMichelUClusters(imichel);
       //std::cout << "Line 3395" << std::endl;

       SmartRefVector<Minerva::IDCluster> Vclustersmichel = m_improvedmichelTool->GetMichelVClusters(imichel);
       //std::cout << "Line 3398" << std::endl;




       int michelnclusx = Xclustersmichel.size();
       int michelnclusu = Uclustersmichel.size();
       int michelnclusv = Vclustersmichel.size();

       /*

       for (int i = 0; i < mehtool_michel_clusterindexvec.size(); ++i)
       {
         for (int j = i+1; j < mehtool_michel_clusterindexvec.size(); ++j)
         {
           if (mehtool_michel_clusterindexvec[i] == mehtool_michel_clusterindexvec[j])
           {
             std::cout << "Michel # " << imichel << " is double matched with a unused cluster " << i << " - " << j << std::endl;

             mehtool_duplicate_michelindexvec.push_back(imichel);



           }
         }
       }
       */

       if (nclusx >= 1 || nclusu >= 1 || nclusv >= 1)
       {
         ++nmichelmatch;

         double michel_time = m_improvedmichelTool->GetMichelTime(imichel);

         mehtool_michel_timevec.push_back(michel_time);
         mehtool_michel_energyvec.push_back(michelenergy);
         mehtool_michel_x1_vec.push_back(michelX1);
         mehtool_michel_x2_vec.push_back(michelX2);
         mehtool_michel_u1_vec.push_back(michelU1);
         mehtool_michel_u2_vec.push_back(michelU2);
         mehtool_michel_v1_vec.push_back(michelV1);
         mehtool_michel_v2_vec.push_back(michelV2);
         mehtool_michel_z1_vec.push_back(michelZ1);
         mehtool_michel_z2_vec.push_back(michelZ2);

         mehtool_michel_Xclustersvec.push_back(michelnclusx);
         mehtool_michel_Uclustersvec.push_back(michelnclusu);
         mehtool_michel_Vclustersvec.push_back(michelnclusv);

       }





       //if (truth && (closestvclusters.size() > 0 || closestuclusters.size() > 0 || closestxclusters.size() > 0))

        // {
          // std::cout <<  "http://minerva05.fnal.gov/Arachne/arachne.html\?det=SIM_minerva&recoVer=v21r1p1&run="<< genMinHeader->RunNumber()<<"&subrun=" << genMinHeader->SubRunNumber() << "&gate=" << truth-/>NumEventInFile()+1 << "&slice="<< event->sliceNumbers()[0] << " \n " << std::endl;
        // }


         //char link[500];
         //sprintf(link, "http://minerva05.fnal.gov/Arachne/arachne.html\?det=SIM_minerva&recoVer=v21r1p1&run=%d&subrun=%d&gate=%d&slice=%d", (int)mc->mc_run, (int)mc->mc_subrun, (int)mc->mc_nthEvtInFile+1, (int)mc->slice_numbers[0]);

     }// End of Michels loop



     event->setContainerIntData("mehtool_michel_fitPass", mehtool_michel_fitpass);
     event->setContainerIntData("mehtool_istrueMichel", mehtool_istrueMichelvec);
     event->setContainerIntData("mehtool_michel_from_decay", mehtool_michel_from_decay);
     event->setContainerIntData("mehtool_true_michel_pdg", mehtool_michel_PDG);
     event->setContainerIntData("mehtool_michel_parent_PDG",  mehtool_parent_PDG);
     event->setContainerDoubleData("mehtool_michel_truetime", mehtool_michel_truetime);

     event->setContainerDoubleData("mehtool_matchedclusters_datafraction", mehtool_matchedclus_fraction);

     event->setContainerIntData("mehtool_pion_primary_particle_trackID", mehtool_pion_primary_particle_trackID);
     event->setContainerIntData("mehtool_true_pion_pdg"                , mehtool_pion_pdg                     );
     event->setContainerDoubleData("mehtool_true_pion_x1vec"              , mehtool_true_pion_x1vec              );
     event->setContainerDoubleData("mehtool_true_pion_y1vec"              , mehtool_true_pion_y1vec              );
     event->setContainerDoubleData("mehtool_true_pion_z1vec"              , mehtool_true_pion_z1vec              );
     event->setContainerDoubleData("mehtool_true_pion_x2vec"              , mehtool_true_pion_x2vec              );
     event->setContainerDoubleData("mehtool_true_pion_y2vec"              , mehtool_true_pion_y2vec              );
     event->setContainerDoubleData("mehtool_true_pion_z2vec"              , mehtool_true_pion_z2vec              );
     event->setContainerIntData( "mehtool_pion_parent_PDG"             , mehtool_pion_parent_PDG              );
     event->setContainerIntData( "mehtool_pion_from_decay"             , mehtool_pion_from_decay              );
     event->setContainerIntData("mehtool_pion_parent_trackID"          , mehtool_pion_parent_trackID          );
     event->setContainerDoubleData("mehtool_pion_truetime"                , mehtool_pion_truetime                );

     event->setContainerDoubleData("mehtool_michel_allmichelenergy", mehtool_michel_allmichelenergyvec);

     event->setIntData("mehtool_nmichelsmatch", nmichelmatch);
     event->setContainerIntData("mehtool_duplicate_michelindex", mehtool_duplicate_michelindexvec);
     event->setContainerIntData("mehtool_nclustermatchmichel", mehtool_nclustermatchpermichel);

     event->setContainerIntData("mehtool_michel_clusterindex", mehtool_michel_clusterindexvec);

     event->setContainerIntData("mehtool_closestclusterX_nclusz", mehtool_closestclusterX_ncluszvec);
     event->setContainerIntData("mehtool_closestclusterU_nclusz", mehtool_closestclusterU_ncluszvec);
     event->setContainerIntData("mehtool_closestclusterV_nclusz", mehtool_closestclusterV_ncluszvec);

     event->setContainerIntData("mehtool_closestclusterX_endpoint", mehtool_closestclusterX_endpointvec);
     event->setContainerIntData("mehtool_closestclusterU_endpoint", mehtool_closestclusterU_endpointvec);
     event->setContainerIntData("mehtool_closestclusterV_endpoint", mehtool_closestclusterV_endpointvec);

     event->setContainerDoubleData("mehtool_closestclusterX_time", mehtool_closestclusterX_timevec);
     event->setContainerDoubleData("mehtool_closestclusterU_time", mehtool_closestclusterU_timevec);
     event->setContainerDoubleData("mehtool_closestclusterV_time", mehtool_closestclusterV_timevec);

     event->setContainerDoubleData("mehtool_closestclusterX_energy", mehtool_closestclusterX_energyvec);
     event->setContainerDoubleData("mehtool_closestclusterU_energy", mehtool_closestclusterU_energyvec);
     event->setContainerDoubleData("mehtool_closestclusterV_energy", mehtool_closestclusterV_energyvec);

     event->setContainerDoubleData("mehtool_closestclusterX_distance", mehtool_closestclusterX_distancevec);
     event->setContainerDoubleData("mehtool_closestclusterU_distance", mehtool_closestclusterU_distancevec);
     event->setContainerDoubleData("mehtool_closestclusterV_distance", mehtool_closestclusterV_distancevec);

     event->setContainerDoubleData("mehtool_closestclusterXZ_distance", mehtool_closestclusterXZ_distancevec);
     event->setContainerDoubleData("mehtool_closestclusterUZ_distance", mehtool_closestclusterUZ_distancevec);
     event->setContainerDoubleData("mehtool_closestclusterVZ_distance", mehtool_closestclusterVZ_distancevec);

     event->setContainerIntData("mehtool_closestclusterX_nclusz", mehtool_closestclusterX_ncluszvec);
     event->setContainerIntData("mehtool_closestclusterU_nclusz", mehtool_closestclusterU_ncluszvec);
     event->setContainerIntData("mehtool_closestclusterV_nclusz", mehtool_closestclusterV_ncluszvec);


     event->setContainerDoubleData("mehtool_michel_time", mehtool_michel_timevec  );
     event->setContainerDoubleData("mehtool_michel_energy", mehtool_michel_energyvec);

     event->setContainerIntData("mehtool_michel_Xclusters", mehtool_michel_Xclustersvec);
     event->setContainerIntData("mehtool_michel_Uclusters", mehtool_michel_Uclustersvec);
     event->setContainerIntData("mehtool_michel_Vclusters", mehtool_michel_Vclustersvec);

     event->setContainerDoubleData("mehtool_michel_x1", mehtool_michel_x1_vec);
     event->setContainerDoubleData("mehtool_michel_x2", mehtool_michel_x2_vec);
     event->setContainerDoubleData("mehtool_michel_u1", mehtool_michel_u1_vec);
     event->setContainerDoubleData("mehtool_michel_u2", mehtool_michel_u2_vec);
     event->setContainerDoubleData("mehtool_michel_v1", mehtool_michel_v1_vec);
     event->setContainerDoubleData("mehtool_michel_v2", mehtool_michel_v2_vec);
     event->setContainerDoubleData("mehtool_michel_z1", mehtool_michel_z1_vec);
     event->setContainerDoubleData("mehtool_michel_z2", mehtool_michel_z2_vec);

     event->setContainerDoubleData("mehtool_michel_maxmeandiff", mehtool_michel_maxmeandiffvec);

     event->setContainerDoubleData("mehtool_closestclusterX_clustime", mehtool_closestclusterX_clustimevec);
     event->setContainerDoubleData("mehtool_closestclusterV_clustime", mehtool_closestclusterV_clustimevec);
     event->setContainerDoubleData("mehtool_closestclusterU_clustime", mehtool_closestclusterU_clustimevec);


     event->setContainerDoubleData("mehtool_closestclusterX_pos", mehtool_closestclusterX_posvec);
     event->setContainerDoubleData("mehtool_closestclusterU_pos", mehtool_closestclusterU_posvec);
     event->setContainerDoubleData("mehtool_closestclusterV_pos", mehtool_closestclusterV_posvec);
     event->setContainerDoubleData("mehtool_closestclusterX_Z_pos", mehtool_closestclusterX_Z_posvec);
     event->setContainerDoubleData("mehtool_closestclusterV_Z_pos", mehtool_closestclusterV_Z_posvec);
     event->setContainerDoubleData("mehtool_closestclusterU_Z_pos", mehtool_closestclusterU_Z_posvec);



/*
      if (truth){
        std::vector<double> bestPart = tagDigitsTruth(micheldigits);

        double data_fraction = TruthMatcher->getDataFraction(michelclusters);
        improved_michel_matched_pdg.push_back(bestPart[0]);
        improved_michel_matched_primary_pdg.push_back(bestPart[1]);
        improved_michel_matched_energy_fraction.push_back(bestPart[2]);
        improved_michel_data_energy_fraction.push_back(data_fraction);

        //check if this is a true michel match or overlayed match

        //Minerva::TG4Trajectory* trueMichel = NULL;
        //const Minerva::TG4Trajectory* MichelParent = NULL;
        //const Minerva::TG4Trajectory* MichelPrimaryParent = NULL;
        //double fraction;
        //double other_energy;
        //std::vector<const Minerva::IDCluster*> FunctionalMichelClusters;

      }
      else{
        improved_michel_matched_pdg.push_back(-1);
        improved_michel_matched_primary_pdg.push_back(-1);
        improved_michel_matched_energy_fraction.push_back(-1.0);
        improved_michel_data_energy_fraction.push_back(-1.0);
      }
      */


      ////////////////////////////// =====================================================================================================================================



      //-- look for the Improved Michel
      //while( improved_michel ) {
      m_improvedmichelTool->Reset();
      m_improvedmichelTool->FindMichel(event->earliestSliceNumber());
      m_improvedmichelTool->ApplyQualityCuts();

      SmartRefVector<Minerva::Vertex> aaronvertices;
      SmartRefVector<Minerva::Vertex> aaronvertex0;
      SmartRefVector<Minerva::Vertex> aaronvertex1;

      SmartRefVector<Minerva::Vertex> aaronvertex2;


      event->setIntData("improved_allmichels", nmichels);




      //--loop over the vertices
      for ( SmartRefVector<Minerva::Vertex>::const_iterator itVtx = vertices.begin(); itVtx != vertices.end(); ++itVtx ) {

        SmartRef<Minerva::Vertex> myvtx = (*itVtx);
        //--no need to look at the endpoint of the muon track
        if ( (*itVtx)->getIncomingTrack()==muonProng->minervaTracks()[0] ) continue;
        if ( !m_minModDepCCQERecoUtils->vertexTracksInTime(myvtx,muonTime)) continue;//if any tracks associated with the vertex are outside tracking time window don't use it

        verbose() << "This vertex is not at the end point of a Muon. Vertex type is = " << (*itVtx)->type() << endmsg;

        //bool improved_michel = true;

        //Get a set of vertices for Aaron's Tool

        aaronvertices.push_back(myvtx);


        //--grab vtx info
        int improved_vtx_type = -1;

        if( (*itVtx)->type() == Minerva::Vertex::StartPoint )
          {
              aaronvertex0.push_back(myvtx);
          }
        else if ( (*itVtx)->type() == Minerva::Vertex::Kinked )
          {
              aaronvertex1.push_back(myvtx);
          }
        else if ( (*itVtx)->type() == Minerva::Vertex::StopPoint )
          {
              aaronvertex2.push_back(myvtx);
          }
        else
          debug()<<"Could not determine vertex point!"<<endmsg;

      }

      double optimaldist = 150.;

      SmartRefVector<Minerva::Vertex> aaronvertices120;
      SmartRefVector<Minerva::Vertex> aaronvertices02;


      //Let's change the order of vertex filling... Fill container with 02 then 01 vertices

      for ( SmartRefVector<Minerva::Vertex>::iterator itVtx = aaronvertex1.begin(); itVtx != aaronvertex1.end(); ++itVtx ) {

        SmartRef<Minerva::Vertex> myvtx = (*itVtx);
        aaronvertices120.push_back(myvtx);
      }

      for ( SmartRefVector<Minerva::Vertex>::iterator itVtx = aaronvertex2.begin(); itVtx != aaronvertex2.end(); ++itVtx ) {

        SmartRef<Minerva::Vertex> myvtx = (*itVtx);
        aaronvertices120.push_back(myvtx);
      }

      for ( SmartRefVector<Minerva::Vertex>::iterator itVtx = aaronvertex0.begin(); itVtx != aaronvertex0.end(); ++itVtx ) {

        SmartRef<Minerva::Vertex> myvtx = (*itVtx);
        aaronvertices120.push_back(myvtx);
      }



      //Get Optimal distances between vertex clusters and michel clusters
      m_improvedmichelTool->OptimalDistance(aaronvertices,optimaldist,optimaldist);

      int ivtx = 0; //iterate over the number of vertices
      //loop over those vertices

      for ( SmartRefVector<Minerva::Vertex>::iterator itVtx = aaronvertices.begin(); itVtx != aaronvertices.end(); ++itVtx ) {

        SmartRef<Minerva::Vertex> myvtx = (*itVtx);

        Gaudi::XYZPoint pos = (*itVtx)->position();
        double x = pos.x(); double y = pos.y(); double z = pos.z();
        double t = (*itVtx)->getTime();

        double vtxE = 0;

        //--grab vtx info
        int improved_vtx_type = -1;


        if( (*itVtx)->type() == Minerva::Vertex::StartPoint )
          improved_vtx_type = 0;
        else if ( (*itVtx)->type() == Minerva::Vertex::Kinked )
          improved_vtx_type = 1;
        else if ( (*itVtx)->type() == Minerva::Vertex::StopPoint )
          improved_vtx_type = 2;
        else
          debug()<<"Could not determine vertex point!"<<endmsg;

        //Mehreen: Last edited on March 29, 2018 ==================================================
        //Let's get the isolated clusters that aren't attached to the vertex or the tracks...

        double tempVtxBoxVisE = 0.0;
        double tempVtxBoxCalE = 0.0;

        //First, we collect all the clusters that are on the outgoing tracks of the vertex.
        SmartRefVector<Minerva::IDCluster> vtxTrackClusters;
        SmartRefVector<Minerva::Track> vtxTracks = myvtx->getTracks();


        for ( SmartRefVector<Minerva::Track>::iterator itVtxTrack = vtxTracks.begin(); itVtxTrack != vtxTracks.end(); ++itVtxTrack )
        {
          std::vector<Minerva::Node*>& vtxNodes = (*itVtxTrack)->nodes();

          for ( std::vector<Minerva::Node*>::iterator itVtxNode = vtxNodes.begin(); itVtxNode != vtxNodes.end(); ++itVtxNode )
          {
            if ( !(*itVtxNode)->hasCluster() ) continue;
            // Correct node cluster energy to normal incidence
            double nodeCosThetaZ = fabs( (*itVtxNode)->trackVec().unit().z() );
            tempVtxBoxVisE += nodeCosThetaZ * (*itVtxNode)->idcluster()->energy();
            tempVtxBoxCalE += nodeCosThetaZ * m_caloUtils->applyCalConsts( (*itVtxNode)->idcluster() );
            vtxTrackClusters.push_back( (*itVtxNode)->idcluster() );

          }
        }

        //  //For Mehreen...

        //  declareProperty( "maxClusTime",      double  m_maxClusTime        = 35.0*CLHEP::ns );
        //  declareProperty( "minClusTime",      double  m_minClusTime        = -20*CLHEP::ns );

        double  m_maxClusTime        = 35.0*CLHEP::ns ;
        double  m_minClusTime        = -20*CLHEP::ns ;

        double tempnonVtxBoxVisE = 0.0;
        double tempnonVtxBoxCalE = 0.0;

        //Now we get all the clusters in the physics event and exclude the ones that match with the clusters above from our tracks
        SmartRefVector<Minerva::IDCluster> clusters = event->select<Minerva::IDCluster>("All","!LowActivity&!XTalkCandidate");
        SmartRefVector<Minerva::IDCluster> nonvtxclusters;
        //for ( SmartRefVector<Minerva::IDCluster>::iterator itCluster = //clusters.begin(); itCluster != clusters.end(); ++itCluster )
        //{
        //  if ( std::find( vtxTrackClusters.begin(), vtxTrackClusters.end(), //*itCluster ) != vtxTrackClusters.end() ) continue;
        //  double reltime = (*itCluster)->time() - event->time();

        //  if ( reltime < m_minClusTime || reltime > m_maxClusTime) continue;


        //  tempnonVtxBoxVisE += (*itCluster)->energy();
        //  tempnonVtxBoxCalE += m_caloUtils->applyCalConsts( *itCluster );
        //  nonvtxclusters.push_back( (*itCluster) );
        //}


      //  bool match = m_improvedmichelTool->Match( x, y, z, max_distance, max_distance); This is Trung's Tool.

      //Aaron's Tool is the following:

        bool match = m_improvedmichelTool->OptimalMatch(ivtx, optimaldist,optimaldist);

        ivtx++;
        if (!match){
        debug()<<"'Did NOT Found a michel electron' Said the ImprovedMichelTool" <<endmsg;
        improved_vtx_type = 99;
        continue;
        }
        debug()<<"'Found a michel electron' Said the ImprovedMichelTool" <<endmsg;


        //--reset michel variables
        double michel_t = -9999.9999;
        double michel_tdiff = -9999.9999;
        double michel_x = -9999.9999;
        double michel_y = -9999.9999;
        double michel_u = -9999.9999;
        double michel_v = -9999.9999;
        double michel_z = -9999.9999;
        double michel_x1 = -9999.9999;
        double michel_y1 = -9999.9999;
        double michel_u1 = -9999.9999;
        double michel_v1 = -9999.9999;
        double michel_z1 = -9999.9999;
        double michel_x2 = -9999.9999;
        double michel_y2 = -9999.9999;
        double michel_u2 = -9999.9999;
        double michel_v2 = -9999.9999;
        double michel_z2 = -9999.9999;

        double michel_vtx_x = -9999.9999;
        double michel_vtx_y = -9999.9999;
        double michel_vtx_u = -9999.9999;
        double michel_vtx_v = -9999.9999;
        double michel_vtx_z = -9999.9999;

        double michel_dist = -9999.9999;
        double michel_ecalo = -9999.9999;
        double michel_evis  = -9999.9999;
        double michel_polarangle = -99999.9999;
        int michel_view = -1;

        //Adding Variables from Aaron's Tool;
        int michel_fitCode = -1;
        int michel_fitPass = -1;
        double michel_matchedEndDist = -9999.9999;
        double michel_matchedvtxE = -9999.9999;
        double closestxydist = -9999.9999;
        int michel_clussize = -1;

        //int michel_truematch = -1;

        double michel_truetime = -1.0;


        // Need to check if Michel Electron is a true match or a fake/overlay match. So let's look at true michels and categorize them in true or fake

        int true_match = false;


        std::cout << "FOUND ONE" << std::endl;
        std::vector<const Minerva::IDCluster*> idclusters;
        std::vector<const Minerva::IDCluster*> michelclusters;
        const SmartRefVector<Minerva::IDCluster> clustersfromcandidate = m_improvedmichelTool->GetMichelClusters();
        idclusters.insert(idclusters.begin(), clustersfromcandidate.begin(), clustersfromcandidate.end());
        SmartRefVector<Minerva::IDDigit> alliddigits;
        SmartRefVector<Minerva::IDDigit> micheldigits;
        std::cout << "I JUST GOT CLUSTERS OF CANDIDATE Line 3041 " << std::endl;
        //Loop over id clusters, and extract hit information
        std::vector<double> zpositions;
        michel_clussize = clustersfromcandidate.size();
        for( SmartRefVector<Minerva::IDCluster>::const_iterator itClus = clustersfromcandidate.begin(); itClus != clustersfromcandidate.end(); ++itClus ){
          double clus_t = (*itClus)->time();
          SmartRefVector<Minerva::IDDigit> iddigits = (*itClus)->digits();
          alliddigits.insert(alliddigits.end(),iddigits.begin(),iddigits.end());

          double zpos = (*itClus)->z();
          zpositions.push_back(zpos);
          michelclusters.push_back((*itClus));

          for( SmartRefVector<Minerva::IDDigit>::const_iterator itDigit = iddigits.begin(); itDigit != iddigits.end(); ++itDigit ){
            improved_michel_hit_charges.push_back((*itDigit)->normEnergy());
            improved_michel_hit_times.push_back((*itDigit)->calTime());
            improved_michel_hit_time_diff_vtx.push_back((*itDigit)->calTime()-t);
            improved_michel_hit_time_diff_cluster.push_back((*itDigit)->calTime()-clus_t);
            micheldigits.push_back((*itDigit));
          }//end loop digits
        }//end loop clusters
        //Do truth matching if this is MC

      if (match){

        michel_vtx_x = x;
        michel_vtx_y = y;
        michel_vtx_z = z;

        /// LETS TAG TRUE MICHELS.....///

        std::cout << "NOW GETTING TG4 TRAJECTORIES TO FIND TRUE MICHEL" << std::endl;

        Minerva::TG4Trajectories* trajectories=NULL;

        std::cout << "NOW FINDING IF TRUE MICHEL" << std::endl;


        if (truth){

          std::cout << "Line 3109" << std::endl;

          trajectories = get<Minerva::TG4Trajectories>( "MC/TG4Trajectories" );
          Minerva::TG4Trajectory* trueMichel = NULL;
          const Minerva::TG4Trajectory* MichelParent = NULL;
          const Minerva::TG4Trajectory* MichelPrimaryParent = NULL;
          double fraction;
          double other_energy;
          //SmartRefVector<Minerva::IDCluster> MichelClusters = m_improvedmichelTool->GetMichelClusters();
          //std::vector<const Minerva::IDCluster*> FunctionalMichelClusters;
          //for(unsigned int c = 0; c < clustersfromcandidate.size(); c++) FunctionalMichelClusters.push_back(clustersfromcandidate[c]);

          if(TruthMatcher->getDataFraction(michelclusters) < 0.5) { // check if overlay
            std::cout << "Line 3122" << std::endl;

            StatusCode parent_sc = TruthMatcher->getTG4Trajectory(michelclusters,MichelParent,fraction,other_energy); //find TG4Trajectory that created the Michel leading the the Michel track
            if(!parent_sc) continue;

            std::cout << "Line 3127" << std::endl;


            //use final position of Michel parent to get Michel trajectory
            for(Minerva::TG4Trajectories::iterator it = trajectories->begin(); it != trajectories->end(); ++it) {
              Minerva::TG4Trajectory * traject = *it;
              std::cout << "Line 3133" << std::endl;

              //           if(traject->GetInitialPosition() == MichelParent->GetFinalPosition()) {
              if(traject->GetParentId() == MichelParent->GetTrackId()){
                if(abs(traject->GetPDGCode())==14) continue;
                trueMichel = traject;
                //Check if the Michel came from a decay or some kind of scattering
                if(trueMichel->GetProcessName().find("Decay") != std::string::npos)
                {
                  //std::cout << "Line 3143" << std::endl;

                  //michel_truematch.push_back(1);

                  michel_from_decay.push_back(int(true));
                  //std::cout << "Line 3145" << std::endl;

                  true_michel_pdg.push_back(trueMichel->GetPDGCode());
                  //std::cout << "Line 3148" << std::endl;

                  true_michel_x1.push_back(trueMichel->GetInitialPosition().X());
                  //std::cout << "Line 3151" << std::endl;

                  true_michel_y1.push_back(trueMichel->GetInitialPosition().Y());
                  //std::cout << "Line 3154" << std::endl;

                  true_michel_z1.push_back(trueMichel->GetInitialPosition().Z());
                  //std::cout << "Line 3157" << std::endl;

                  true_michel_x2.push_back(trueMichel->GetFinalPosition().X());
                  //std::cout << "Line 3161" << std::endl;

                  true_michel_y2.push_back(trueMichel->GetFinalPosition().Y());
                  //std::cout << "Line 3164" << std::endl;

                  true_michel_z2.push_back(trueMichel->GetFinalPosition().Z());
                  //std::cout << "Line 3167" << std::endl;

                  //has_michel_primary_particle_trackID.push_back(MichelPrimaryParent->GetTrackId());
                  //std::cout << "Line 3170" << std::endl;

                  michel_parent_PDG.push_back(MichelParent->GetPDGCode());
                  //std::cout << "Line 3172" << std::endl;

                  michel_parent_trackID.push_back(MichelParent->GetTrackId());

                  //std::cout << "Line 3176" << std::endl;

                  michel_true_time.push_back(trueMichel->GetInitialPosition().T());


                  break;
                }//If true Michel

              } //Where Michel CAme from
            } // For Michel Trajectory
          } //Get Data Fraction
        } //if truth

        michel_view  = m_improvedmichelTool->GetMichelViewCode();

        if (michel_view < 20) continue; // remove 1 view michels

        michel_t = m_improvedmichelTool->GetMichelTime();
        michel_tdiff = (michel_t - t);

        michel_x = m_improvedmichelTool->GetMichelPositionX();
        michel_y = m_improvedmichelTool->GetMichelPositionY();
        michel_u = m_improvedmichelTool->GetMichelPositionU();
        michel_v = m_improvedmichelTool->GetMichelPositionV();
        michel_z = m_improvedmichelTool->GetMichelPositionZ();

        michel_x1 = m_improvedmichelTool->GetMichelEndpointX1();
        michel_y1 = m_improvedmichelTool->GetMichelEndpointY1();
        michel_u1 = m_improvedmichelTool->GetMichelEndpointU1();
        michel_v1 = m_improvedmichelTool->GetMichelEndpointV1();
        michel_z1 = m_improvedmichelTool->GetMichelEndpointZ1();

        michel_x2 = m_improvedmichelTool->GetMichelEndpointX2();
        michel_y2 = m_improvedmichelTool->GetMichelEndpointY2();
        michel_u2 = m_improvedmichelTool->GetMichelEndpointU2();
        michel_v2 = m_improvedmichelTool->GetMichelEndpointV2();
        michel_z2 = m_improvedmichelTool->GetMichelEndpointZ2();

        double michelz1 = m_improvedmichelTool->GetMichelEndpointZ1();
        double michelz2 = m_improvedmichelTool->GetMichelEndpointZ2();


        michel_fitCode = m_improvedmichelTool->GetMichelFitCode();
        michel_fitPass = m_improvedmichelTool->GetMichelFitPass();

        if ( abs(michelz1 - z) > abs(michelz2 - z))
        {
          michel_dist = michelz2 - z;

        }
        else{
          michel_dist = michelz1 -z;
        }

       //let's use the z distance for michel...

        double michelx1 = m_improvedmichelTool->GetMichelEndpointX1();
        double michelx2 = m_improvedmichelTool->GetMichelEndpointX2();
        double michely1 = m_improvedmichelTool->GetMichelEndpointY1();
        double michely2 = m_improvedmichelTool->GetMichelEndpointY2();
        //double michelu1 = m_improvedmichelTool->GetMichelEndpointU1();
        //double michelu2 = m_improvedmichelTool->GetMichelEndpointU2();
        //double michelv1 = m_improvedmichelTool->GetMichelEndpointV1();
        //double michelv2 = m_improvedmichelTool->GetMichelEndpointV2();

        double xydist1 = sqrt(pow(x - michelx1, 2) + pow(y-michely1,2));
        double xydist2 = sqrt(pow(x - michelx2, 2) + pow(y-michely2,2));

        //double closestxydist = sqrt(pow(x - closestmichelx, 2) + pow(y-closestmichely,2));


        //double uvdist1 = sqrt(pow(u - michelu1, 2) + pow(v-michelv1,2));
        //double uvdist2 = sqrt(pow(u - michelu1, 2) + pow(v-michelv1,2));

        if (michel_fitPass == 1 ){
          if (xydist1 > xydist2) {
            closestxydist = xydist2;
          }
          else{
            closestxydist = xydist1;
          }
        }

        if (michel_fitPass == 0)
        {
          closestxydist= sqrt(pow(x - michel_x, 2) + pow(y - michel_y,2));

        }

        michel_ecalo = m_improvedmichelTool->GetMichelCalorimetricEnergy();
        michel_evis  = m_improvedmichelTool->GetMichelVisibleEnergy();

        double michelxslope = m_improvedmichelTool->GetMichelFitAX();
        double michelyslope = m_improvedmichelTool->GetMichelFitAY();

        double xyside = sqrt(pow(michelxslope, 2) + pow(michelyslope,2));

        michel_polarangle = atan(xyside/1.);

        double zmin = *std::min_element(zpositions.begin(),zpositions.end());
        double zmax = *std::max_element(zpositions.begin(), zpositions.end());

        double zspan = zmax - zmin;

        int michel_nplanes = int(zspan/17.0);

        //Need to write up distance of closest approach




        michel_matchedEndDist = m_improvedmichelTool->GetMatchedEndMichelDist();
        michel_matchedvtxE = tempnonVtxBoxCalE;

        //--push variable sin the vectors (ONLY if matched)
        improved_michel_vertex_type.push_back(improved_vtx_type);
        improved_michel_tvec.push_back(michel_t);
        improved_michel_tdiff_vec.push_back(michel_tdiff);
        improved_michel_xvec.push_back(michel_x);
        improved_michel_yvec.push_back(michel_y);
        improved_michel_uvec.push_back(michel_u);
        improved_michel_vvec.push_back(michel_v);
        improved_michel_zvec.push_back(michel_z);

        improved_michel_vtx_xvec.push_back(michel_vtx_x);
        improved_michel_vtx_yvec.push_back(michel_vtx_y);
        improved_michel_vtx_zvec.push_back(michel_vtx_z);

        improved_michel_x1vec.push_back(michel_x1);
        improved_michel_y1vec.push_back(michel_y1);
        improved_michel_u1vec.push_back(michel_u1);
        improved_michel_v1vec.push_back(michel_v1);
        improved_michel_z1vec.push_back(michel_z1);

        improved_michel_x2vec.push_back(michel_x2);
        improved_michel_y2vec.push_back(michel_y2);
        improved_michel_u2vec.push_back(michel_u2);
        improved_michel_v2vec.push_back(michel_v2);
        improved_michel_z2vec.push_back(michel_z2);

        improved_michel_dist_vec.push_back(michel_dist);
        improved_michel_transdist_vec.push_back(closestxydist);
        improved_michel_evis_vec.push_back(michel_evis);
        improved_michel_ecalo_vec.push_back(michel_ecalo);
        improved_michel_polarangle_vec.push_back(michel_polarangle);
        improved_michel_view_vec.push_back(michel_view);
        improved_michel_match_vec.push_back(int(match));
        improved_michel_ndigits.push_back(alliddigits.size());
        improved_michel_fitCode_vec.push_back(michel_fitCode);
        improved_michel_fitPass_vec.push_back(michel_fitPass);
        improved_michel_MatchedEndDist_vec.push_back(michel_matchedEndDist);
        improved_michel_matchedvtx_energy_vec.push_back(tempnonVtxBoxCalE);

        improved_michel_nplanes.push_back(michel_nplanes);
        improved_michel_clussize.push_back(michel_clussize);
      }


  } //End of loop over vertices

  event->setContainerIntData("improved_michel_vertex_type", improved_michel_vertex_type);
  event->setIntData("improved_nmichel", improved_michel_vertex_type.size());

  event->setContainerDoubleData("improved_michel_tvec", improved_michel_tvec);
  event->setContainerDoubleData("improved_michel_tdiff_vec", improved_michel_tdiff_vec);
  event->setContainerDoubleData("improved_michel_xvec", improved_michel_xvec);
  event->setContainerDoubleData("improved_michel_yvec", improved_michel_yvec);
  event->setContainerDoubleData("improved_michel_uvec", improved_michel_uvec);
  event->setContainerDoubleData("improved_michel_vvec", improved_michel_vvec);
  event->setContainerDoubleData("improved_michel_zvec", improved_michel_zvec);

  event->setContainerDoubleData("improved_michel_vtx_xvec", improved_michel_vtx_xvec);
  event->setContainerDoubleData("improved_michel_vtx_yvec", improved_michel_vtx_yvec);
  event->setContainerDoubleData("improved_michel_vtx_zvec", improved_michel_vtx_zvec);

  event->setContainerDoubleData("improved_michel_x1vec", improved_michel_x1vec);
  event->setContainerDoubleData("improved_michel_y1vec", improved_michel_y1vec);
  event->setContainerDoubleData("improved_michel_u1vec", improved_michel_u1vec);
  event->setContainerDoubleData("improved_michel_v1vec", improved_michel_v1vec);
  event->setContainerDoubleData("improved_michel_z1vec", improved_michel_z1vec);
  event->setContainerDoubleData("improved_michel_x2vec", improved_michel_x2vec);
  event->setContainerDoubleData("improved_michel_y2vec", improved_michel_y2vec);
  event->setContainerDoubleData("improved_michel_u2vec", improved_michel_u2vec);
  event->setContainerDoubleData("improved_michel_v2vec", improved_michel_v2vec);
  event->setContainerDoubleData("improved_michel_z2vec", improved_michel_z2vec);
  event->setContainerDoubleData("improved_michel_dist_vec", improved_michel_dist_vec);
  event->setContainerDoubleData("improved_michel_transdist_vec", improved_michel_transdist_vec);
  event->setContainerDoubleData("improved_michel_evis_vec", improved_michel_evis_vec);
  event->setContainerDoubleData("improved_michel_ecalo_vec", improved_michel_ecalo_vec);
  event->setContainerDoubleData("improved_michel_polarangle_vec", improved_michel_polarangle_vec);
  event->setContainerDoubleData("improved_michel_hit_charges", improved_michel_hit_charges);
  event->setContainerDoubleData("improved_michel_hit_times", improved_michel_hit_times);
  event->setContainerDoubleData("improved_michel_hit_time_diff_vtx", improved_michel_hit_time_diff_vtx);
  event->setContainerDoubleData("improved_michel_hit_time_diff_cluster", improved_michel_hit_time_diff_cluster);
  event->setContainerDoubleData("improved_michel_matched_energy_fraction",improved_michel_matched_energy_fraction);
  event->setContainerDoubleData("improved_michel_data_energy_fraction",improved_michel_data_energy_fraction);
  event->setContainerIntData("improved_michel_view_vec", improved_michel_view_vec);
  event->setContainerIntData("improved_michel_match_vec", improved_michel_match_vec); // whether this track is Michel tagged
  event->setContainerIntData("improved_michel_matched_pdg",improved_michel_matched_pdg);
  event->setContainerIntData("improved_michel_matched_primary_pdg",improved_michel_matched_primary_pdg);
  event->setContainerIntData("improved_michel_ndigits",improved_michel_ndigits);

  //Filling event containers for Aaron's Tool Variables
  event->setContainerIntData("improved_michel_fitCode_vec",improved_michel_fitCode_vec);
  event->setContainerIntData("improved_michel_fitPass_vec",improved_michel_fitPass_vec);
  event->setContainerIntData("improved_michel_clussize", improved_michel_clussize);
  event->setContainerIntData("improved_michel_nplanes", improved_michel_nplanes);
  event->setContainerDoubleData("improved_michel_MatchedEndDist_vec"    , improved_michel_MatchedEndDist_vec);
  event->setContainerDoubleData("improved_michel_matchedvtx_energy_vec", improved_michel_matchedvtx_energy_vec);


  //Get some True Michel Variables added

  if( haveNeutrinoMC() ){
    event->setContainerIntData("has_michel_primary_particle_trackID",has_michel_primary_particle_trackID);
    event->setContainerIntData("michel_from_decay",michel_from_decay);
    event->setContainerIntData("true_michel_pdg",true_michel_pdg);
    event->setContainerDoubleData("true_michel_x1",true_michel_x1);
    event->setContainerDoubleData("true_michel_y1",true_michel_y1);
    event->setContainerDoubleData("true_michel_z1",true_michel_z1);
    event->setContainerDoubleData("true_michel_x2",true_michel_x2);
    event->setContainerDoubleData("true_michel_y2",true_michel_y2);
    event->setContainerDoubleData("true_michel_z2",true_michel_z2);
    event->setContainerIntData("michel_parent_PDG",michel_parent_PDG);
    event->setContainerIntData("michel_parent_trackID",michel_parent_trackID);
  }



  verbose() << "Finished setting Improved michel variables" << endmsg;

  if (improved_michel_view_vec.size()>0) foundImprovedMichel = true;

  return foundImprovedMichel;
}

//========================================
// tagMichels
//========================================
bool CCQENu::tagMichels(Minerva::PhysicsEvent* event, Minerva::GenMinInteraction* truth) const
{
  bool foundMichel = false;

  //--tag truth michel
  if (truth)
    {
      bool hasTruthMichelFiducial = hasTruthMichelElectron(event);
      event->setIntData("truth_has_michel_electron",hasTruthMichelFiducial);
    }

  //--get the tagged muon prong
  Minerva::ProngVect primaryProngs = event->primaryProngs();
  SmartRef<Minerva::Prong> muonProng;

  for (ProngVect::iterator itProngs = primaryProngs.begin(); itProngs != primaryProngs.end(); ++itProngs) {
    if( (*itProngs)->filtertaglist()->filterTagExists( AnaFilterTags::PrimaryMuon() ) ) {
      muonProng = *itProngs;
      break;
    }
  }

    //--look for michel electrons in vertices
    Minerva::Prong vtx_michelProng;
    const SmartRefVector<Minerva::Vertex> vertices = event->select<Minerva::Vertex>();
    debug()<<"Looking for michels in " <<vertices.size()-1<<" vertex points" <<endmsg;
    event->setIntData("has_n_vertex_points", vertices.size()-1);
    warning()<<"Looking for michels in " <<vertices.size()-1<<" vertex points" <<endmsg;

    //    std::vector<int> has_michel_track_in_region;
    std::vector<int> has_michel_in_vertex_point;
    std::vector<int> has_michel_vertex_type; //0: StartPoint, 1:Kinked Track, 2: Stop Point
    std::vector<int> has_michel_category;
    std::vector<int> has_michel_bgmodule;
    std::vector<int> has_michel_edmodule;
    std::vector<int> has_michel_nmodules;
    std::vector<int> has_michel_nplanes;
    std::vector<int> has_michel_view_sum;
    std::vector<int> has_michel_ntracks;
    std::vector<int> has_michel_ndigits;
    std::vector<int> has_michel_slice_number;
    std::vector<int> has_michel_matched_pdg;
    std::vector<int> has_michel_matched_primary_pdg;

    std::vector<double> has_michel_distance;
    std::vector<double> has_michel_time_diff;
    std::vector<double> has_michel_energy;
    std::vector<double> has_michel_slice_energy;
    std::vector<double> has_michel_matched_energy_fraction;
    std::vector<double> has_michel_data_energy_fraction;
    std::vector<double> has_michel_hit_charges;
    std::vector<double> has_michel_hit_times;
    std::vector<double> has_michel_hit_time_diff_vtx;
    std::vector<double> has_michel_hit_time_diff_cluster;

    double muonTime = m_recoObjTimeTool->trackVertexTime(muonProng->minervaTracks()[0]);


    for ( SmartRefVector<Minerva::Vertex>::const_iterator itVtx = vertices.begin(); itVtx != vertices.end(); ++itVtx ) {

      //--no need to look at the endpoint of the muon track
      if ( (*itVtx)->getIncomingTrack()==muonProng->minervaTracks()[0] ) continue;
      if ( !m_minModDepCCQERecoUtils->vertexTracksInTime((*itVtx),muonTime)) continue;//if any tracks associated with the vertex are outside tracking time window don't use it

      verbose() << "This vertex is not at the end point of a Muon. Vertex type is = " << (*itVtx)->type() << endmsg;

      bool michel = true;

      Gaudi::XYZPoint pos = (*itVtx)->position();
      int x = pos.x(); int y = pos.y(); int z = pos.z();

      double t = (*itVtx)->getTime();

      while( michel ) {
        michel = m_michelTool->findMichel( x, y, z, t, vtx_michelProng );
        if (!michel) break;
        debug()<<" Found a michel electron!" <<endmsg;
        int vtx_type = -1;
	std::vector<const Minerva::IDCluster*> idclusters;
	SmartRefVector<Minerva::IDCluster> clustersFromProng = vtx_michelProng.getAllIDClusters();
	idclusters.insert(idclusters.begin(), clustersFromProng.begin(), clustersFromProng.end());
        if( (*itVtx)->type() == Minerva::Vertex::StartPoint )
          vtx_type = 0;
        else if ( (*itVtx)->type() == Minerva::Vertex::Kinked )
          vtx_type = 1;
        else if ( (*itVtx)->type() == Minerva::Vertex::StopPoint )
          vtx_type = 2;
        else
          debug()<<"Could not determine vertex point!"<<endmsg;
	//Loop over id clusters, and extract hit information
	for( SmartRefVector<Minerva::IDCluster>::const_iterator itClus = clustersFromProng.begin(); itClus != clustersFromProng.end(); ++itClus ){
	  double clus_t = (*itClus)->time();
	  SmartRefVector<Minerva::IDDigit> iddigits = (*itClus)->digits();
	  for( SmartRefVector<Minerva::IDDigit>::const_iterator itDigit = iddigits.begin(); itDigit != iddigits.end(); ++itDigit ){
	    //	    alliddigits.push_back((*itDigit));
	    has_michel_hit_charges.push_back((*itDigit)->normEnergy());
	    has_michel_hit_times.push_back((*itDigit)->calTime());
	    has_michel_hit_time_diff_vtx.push_back((*itDigit)->calTime()-t);
	    has_michel_hit_time_diff_cluster.push_back((*itDigit)->calTime()-clus_t);
	  }//end loop digits
	}//end loop clusters

        //        has_michel_track_in_region.push_back( vtx_michelProng.getIntData("track_in_region"));
        has_michel_vertex_type.push_back( vtx_type);
        has_michel_category.push_back( vtx_michelProng.getIntData("category") );
        has_michel_in_vertex_point.push_back( itVtx - vertices.begin() );
        has_michel_energy.push_back( vtx_michelProng.getDoubleData("energy") );
        has_michel_distance.push_back( vtx_michelProng.getDoubleData("distance") );
        has_michel_time_diff.push_back( vtx_michelProng.getDoubleData("time_diff") );
        has_michel_ndigits.push_back( vtx_michelProng.getIntData("ndigits"));
        has_michel_bgmodule.push_back( vtx_michelProng.getIntData("bgmodule"));
        has_michel_edmodule.push_back( vtx_michelProng.getIntData("edmodule"));
        has_michel_nmodules.push_back( vtx_michelProng.getIntData("nmodules"));
        has_michel_nplanes.push_back( vtx_michelProng.getIntData("nplanes"));
	has_michel_view_sum.push_back( vtx_michelProng.getIntData("view_sum"));
        has_michel_ntracks.push_back( vtx_michelProng.getIntData("ntracks"));
	has_michel_slice_number.push_back( vtx_michelProng.timeSlice());

	has_michel_slice_energy.push_back( vtx_michelProng.getDoubleData("slice_energy") );


        if (truth){
          truth->setIntData("reco_has_michel_electron",1);
	  debug() << "here " <<vtx_michelProng.getIntData("ndigits") << endmsg;
	  std::vector<double> bestPart = tagMichelProngTruth(vtx_michelProng);
	  double data_fraction = TruthMatcher->getDataFraction(idclusters);
	  has_michel_matched_pdg.push_back(bestPart[0]);
	  has_michel_matched_primary_pdg.push_back(bestPart[1]);
	  has_michel_matched_energy_fraction.push_back(bestPart[2]);
	  has_michel_data_energy_fraction.push_back(data_fraction);
	}
	else{
	  has_michel_matched_pdg.push_back(-1);
	  has_michel_matched_primary_pdg.push_back(-1);
	  has_michel_matched_energy_fraction.push_back(-1.0);
	  has_michel_data_energy_fraction.push_back(-1.0);
	}

        t += vtx_michelProng.getDoubleData("meantime_diff") + 100;



      }
    } // End of for loop over vertices

    //    event->setContainerIntData("has_michel_track_in_region", has_michel_track_in_region);
    event->setContainerIntData("has_michel_vertex_type", has_michel_vertex_type);
    event->setContainerIntData("has_michel_in_vertex_point", has_michel_in_vertex_point);
    event->setContainerIntData("has_michel_category", has_michel_category);
    event->setContainerIntData("has_michel_ndigits", has_michel_ndigits);
    event->setContainerIntData("has_michel_bgmodule", has_michel_bgmodule);
    event->setContainerIntData("has_michel_edmodule", has_michel_edmodule);
    event->setContainerIntData("has_michel_nmodules", has_michel_nmodules);
    event->setContainerIntData("has_michel_nplanes", has_michel_nplanes);
    event->setContainerIntData("has_michel_view_sum", has_michel_view_sum);
    event->setContainerIntData("has_michel_ntracks", has_michel_ntracks);
    event->setContainerIntData("has_michel_matched_pdg",has_michel_matched_pdg);
    event->setContainerIntData("has_michel_matched_primary_pdg",has_michel_matched_primary_pdg);

    event->setContainerDoubleData("has_michel_distance", has_michel_distance);
    event->setContainerDoubleData("has_michel_time_diff", has_michel_time_diff);
    event->setContainerDoubleData("has_michel_energy", has_michel_energy);
    event->setContainerDoubleData("has_michel_slice_energy", has_michel_slice_energy);
    event->setContainerDoubleData("has_michel_matched_energy_fraction",has_michel_matched_energy_fraction);
    event->setContainerDoubleData("has_michel_data_energy_fraction",has_michel_data_energy_fraction);
    event->setContainerDoubleData("has_michel_hit_charges", has_michel_hit_charges);
    event->setContainerDoubleData("has_michel_hit_times", has_michel_hit_times);
    event->setContainerDoubleData("has_michel_hit_time_diff_vtx", has_michel_hit_time_diff_vtx);
    event->setContainerDoubleData("has_michel_hit_time_diff_cluster", has_michel_hit_time_diff_cluster);

    verbose() << "Finished setting michel variables" << endmsg;

    if (has_michel_category.size()>0) foundMichel = true;

    return foundMichel;
}


//=====================================
// hasTruthMichelElectron
//=====================================
bool CCQENu::hasTruthMichelElectron(Minerva::PhysicsEvent* event) const {

  debug()<<"Entering CCQENu::hasTruthMichelElectron(  ) ....."<< endmsg;

  bool hasMichel = false;

  Gaudi::LorentzVector positron_pos;
  Gaudi::LorentzVector electron_pos;

  std::map<int,double> pion_plus_ids_momentum, pion_minus_ids_momentum;
  std::map<int,int> muon_plus_id_parent, muon_minus_id_parent;
  std::map<int,Gaudi::LorentzVector> electron_parent_pos, positron_parent_pos;
  std::vector<double> pion_plus_momentum, pion_minus_momentum;

  Minerva::TG4Trajectories* alltrajects = get<Minerva::TG4Trajectories>( "MC/TG4Trajectories" );
  for(Minerva::TG4Trajectories::iterator it = alltrajects->begin(); it != alltrajects->end(); ++it) {
    Minerva::TG4Trajectory* traject = *it;

    //! look for charged pions
    if( traject->GetPDGCode()==211 ){
      pion_plus_ids_momentum[traject->GetTrackId()] = (traject->GetInitialMomentum()).P();
    }
    if( traject->GetPDGCode()==-211 ){
      pion_minus_ids_momentum[traject->GetTrackId()] = (traject->GetInitialMomentum()).P();
    }

    //! look for muons from decays
    if( traject->GetProcessName() == "Decay" && traject->GetPDGCode() == -13 ) {
      muon_plus_id_parent[traject->GetTrackId()] = traject->GetParentId();
    }

    if( traject->GetProcessName() == "Decay" && traject->GetPDGCode() == 13 ) {
      muon_minus_id_parent[traject->GetTrackId()] = traject->GetParentId();
    }

    //! look for electrons from decays
    if( traject->GetProcessName() == "Decay" && traject->GetPDGCode() == -11 ) {
      positron_parent_pos[traject->GetParentId()] = traject->GetInitialPosition();
    }

    if( traject->GetProcessName() == "muMinusCaptureAtRest" && traject->GetPDGCode() == 11 ) {
      electron_parent_pos[traject->GetParentId()] = traject->GetInitialPosition();
    }

  } // End of TG4Trajectories loop

  //! loop over electrons
  for( std::map<int,Gaudi::LorentzVector>::iterator electron = electron_parent_pos.begin(); electron != electron_parent_pos.end(); ++electron ){
    // check if electron parent is a muon-
    if( muon_minus_id_parent.count( electron->first ) ){
      //check if electron is inside fiducial volume
      Gaudi::LorentzVector electron_pos = electron->second;
      Gaudi::XYZPoint p( electron_pos.x(), electron_pos.y(), electron_pos.z() );
      //if( FiducialPointTool->isFiducial( p, m_analyzeApothem, m_michel_upstreamZ, m_michel_downstreamZ ) ){
	event->setIntData("truth_has_michel_electron",1);
	hasMichel = true;
	// check if muon parent is a pion-
	if( pion_minus_ids_momentum.count( muon_minus_id_parent[electron->first] ) ){
	  pion_minus_momentum.push_back( pion_minus_ids_momentum[ muon_minus_id_parent[electron->first] ]  );
	}
      //}
    }
  }

  //! loop over positrons
  for( std::map<int,Gaudi::LorentzVector>::iterator positron = positron_parent_pos.begin(); positron != positron_parent_pos.end(); ++positron ){
    // check if positron parent is a muon+
    if( muon_plus_id_parent.count( positron->first ) ){
      // check if positron is inside fiducial volume
      Gaudi::LorentzVector positron_pos = positron->second;
      Gaudi::XYZPoint p( positron_pos.x(), positron_pos.y(), positron_pos.z() );
      //if( FiducialPointTool->isFiducial( p, m_analyzeApothem, m_michel_upstreamZ, m_michel_downstreamZ ) ){
	event->setIntData("truth_has_michel_electron",1);
	hasMichel = true;
	// check if muon parent is a pi+
	if( pion_plus_ids_momentum.count( muon_plus_id_parent[positron->first] ) ){
	  pion_plus_momentum.push_back( pion_plus_ids_momentum[ muon_plus_id_parent[positron->first] ]  );
	}
      //}
    }
  }

  event->setContainerDoubleData("truth_has_michel_from_pion_plus_momentum", pion_plus_momentum);
  event->setContainerDoubleData("truth_has_michel_from_pion_minus_momentum", pion_minus_momentum);

  debug()<<"Leaving CCQENu::hasTruthMichelElectron(  ) ....."<<endmsg;
  return hasMichel;
}

bool CCQENu::findLongestMinervaTrack( Minerva::Prong* deProng, SmartRef<Minerva::Track> &longestTrackInsideProng ) const {

  verbose() << "Entering CCQENu::findLongestMinervaTrack( ) ....." << endmsg;

  Minerva::TrackVect minervaTrkVec = deProng->minervaTracks();
  if( minervaTrkVec.size() ) {
    //Find the longest track inside the Prong (can be muon, proton, etc.)
    unsigned int most_nodes = 0;
    for( Minerva::TrackVect::iterator itTrk = minervaTrkVec.begin(); itTrk != minervaTrkVec.end(); ++itTrk ) {
      if( (*itTrk)->nNodes() > most_nodes ) {
	most_nodes = (*itTrk)->nNodes();
	longestTrackInsideProng = (*itTrk);
      }
    } //end of for loop over tracks

    if( longestTrackInsideProng->nNodes() )
      debug() <<"For each prong "<< longestTrackInsideProng->chi2PerDoF() <<" Nodes: "<< longestTrackInsideProng->nNodes() << endmsg;

  } else {
    debug() << "This Prong contains no MINERvA Tracks, so skipping !" << endmsg;
    return false;
  }

  verbose() << "Exiting CCQENu::findLongestMinervaTrack( ) ....." << endmsg;
  return true;
}

bool CCQENu::findLongestMinervaTrack( Minerva::ProngVect deProngVec, SmartRef<Minerva::Track> &longestMinervaTrack ) const {

  bool foundTrackInsideAProng = false;

  //------------------------------------------------------------------------------------------------------
  // This returns the longest track (whichever prong it belongs to) after looping over all the Prongs
  //------------------------------------------------------------------------------------------------------
  unsigned int prong_nodes = 0;
  SmartRef<Minerva::Track> insideProngTrack;

  for( ProngVect::iterator itProngs = deProngVec.begin(); itProngs != deProngVec.end(); ++itProngs ) {
    foundTrackInsideAProng = findLongestMinervaTrack( *itProngs, insideProngTrack );

    if( foundTrackInsideAProng && insideProngTrack->nNodes() ) {
      if( insideProngTrack->nNodes() > prong_nodes ) {
	prong_nodes = (insideProngTrack)->nNodes();
	longestMinervaTrack = insideProngTrack;
      }
    }

  } //End of for loop over Prongs

  if( !longestMinervaTrack->nNodes() ) {
    return false;
  } else {
    debug() << "After looping over all Prongs " << longestMinervaTrack->chi2PerDoF() <<" Nodes: "<< longestMinervaTrack->nNodes() << endmsg;
    return true;
  }
}

bool CCQENu::findLongestMinervaTrack( const Minerva::PhysicsEvent *physEvent, SmartRef<Minerva::Track> &longestMinervaTrack ) const {

  //----------------------------------------------------------------------------------------
  // This returns the longest track found (whichever Primary Prong it belongs to)
  //----------------------------------------------------------------------------------------
  ProngVect primaryProngs = physEvent->primaryProngs();
  if( !primaryProngs.size() ) {
    verbose() << "There are no Primary Prongs in this physics event!" << endmsg;
    return false;
  } else {
    return findLongestMinervaTrack( primaryProngs, longestMinervaTrack );
  }

  return false;
}



//#########################################################################################
//
// End CCQENu.cpp
//
//#########################################################################################
