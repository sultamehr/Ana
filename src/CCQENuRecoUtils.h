#ifndef CCQENURECOUTILS_H 
#define CCQENURECOUTILS_H 1 

//Inheritance
#include "MinervaUtils/MinervaHistoTool.h" 
#include "AnaUtils/MinervaAnalysisTool.h" 
#include "CCQENu/ICCQENuRecoUtils.h" 


//***Class Tools***//
class IMinervaObjectAssociator;
class IRecoObjectTimeTool;
class IMinervaMathTool;
class IMinervaCoordSysTool;

class IAnchoredTrackFormation; 
class IVertexEnergyStudyTool; 
class IIDAnchoredBlobCreator; 
class IBlobCreatorUtils; 

class ICalorimetryUtils;
class Cone; 
class IConeUtilsTool;
class IProngClassificationTool;

class IHitTaggerTool;

class IMuonUtils; 


//Forward declarations
#include "Event/MinervaEventFwd.h"

class CCQENuRecoUtils : public MinervaHistoTool, virtual public ICCQENuRecoUtils {

 public:

     // Standard constructor
     CCQENuRecoUtils( const std::string& type, const std::string& name, const IInterface* parent );

     // Destructor
     ~CCQENuRecoUtils(){};

     StatusCode initialize();
     StatusCode finalize(); 
  
     Minerva::IDClusterVect getInTimeAnalyzableIDClusters( const Minerva::PhysicsEvent *event, SmartRef<Minerva::Prong> muonProng) const;

     Minerva::IDClusterVect getInTimeAnalyzableNonMuonNonVtxIDClusters( const Minerva::PhysicsEvent *event, SmartRef<Minerva::Prong> muonProng, double vtxRejectionRadius) const;

     Minerva::IDClusterVect getInTimeAnalyzableNonMuonVtxIDClusters( const Minerva::PhysicsEvent *event, SmartRef<Minerva::Prong> muonProng, double vtxRejectionRadius) const;
     
     StatusCode runShortTrackers( Minerva::PhysicsEvent* physEvent, std::vector<Minerva::Track*> *deShortTrackVector, bool runVertexAnchoredShortTracker, bool runVertexEnergyStudyTool ) const;  
     
     StatusCode makeConeAtEndProtonTrack(Minerva::PhysicsEvent *event, SmartRef<Minerva::Prong> protonProng, SmartRef<Minerva::Prong> muonProng, bool &foundClustersInCone, double &ConeClusterMaxDistance, Minerva::IDClusterVect &clustersInCone, bool fillTruthTG4ProtonCone = false ) const;

     bool makeIsoEMMuonBlobs( Minerva::PhysicsEvent* event, SmartRef<Minerva::Prong> muonProng ) const;
     
     bool makeFuzzEMMuonBlobs( Minerva::PhysicsEvent* event, SmartRef<Minerva::Prong> muonProng ) const; 

     bool vertexTracksInTime( SmartRef<Minerva::Vertex> vertex, double muonTime) const;
     
     Minerva::ProngVect getInTimeTrackPID( Minerva::PhysicsEvent* event, double muonTime) const;

  
 private: 


     //Make Short Tracks 
     bool                m_runVertexAnchoredShortTracker; 
     bool                m_runVertexEnergyStudyTool; 
     double              m_maxSearchDistance_VESTool; 
     double              m_maxStartingDistance_VESTool; 
     double              m_maxAllowedSearchGap_VESTool; 


     //Muon time window parameters
     double              m_lowerTimeWindow;
     double              m_upperTimeWindow;
     //Track time window
     double              m_lowerTimeWindow_Tracks;
     double              m_upperTimeWindow_Tracks;


     //Prong, Blob and Cluster Colors 
     int                 m_clustersInConeProtonProngColor; 
     int                 m_muonFuzzBlobsColor; 
     int                 m_muonIsolatedBlobsColor; 
     int                 m_muonProngColor; 

      
     //Cone Length Parameter
     double              m_coneLength;

     //Make Iso/Fuzz EM Blobs 
     double              m_muonFuzzDistanceFromVertex;
     double              m_muonFuzzRadius; 
     
     bool                m_makeIsoMuonEMBlobs; 
     bool                m_makeFuzzMuonEMBlobs; 

     //Minerva Object Associator
     IMinervaObjectAssociator*     m_objectAssociator;
     std::string                   m_minObjAssocAlias; 

     //MuonUtils 
     IMuonUtils*                   m_muonUtils; 
     std::string                   m_muonUtilsAlias; 
     
     //Vertex Anchored Short Tracker 
     IAnchoredTrackFormation*      m_vtxAnchorShortTracker; 
     std::string                   m_vtxAnchorShortTrackerAlias;  

     //Reco Object Time Tool 
     IRecoObjectTimeTool*          m_recoObjTimeTool; 
     std::string                   m_recoObjTimeToolAlias; 

     //Prong Classification Tool 
     IProngClassificationTool*     m_prongIntersectionTool;
     std::string                   m_prongIntersectionToolAlias;

     //Blob Creator Utils 
     IBlobCreatorUtils*            m_blobCreatorUtils; 
     std::string                   m_blobCreatorUtilsAlias;     

     //Vertex Energy Short Tracker 
     IVertexEnergyStudyTool*       m_vertexEnergyStudyTool; 
     std::string                   m_vtxEngStudyToolAlias; 

     //Cone Utils Tool 
     IConeUtilsTool*               m_coneUtilsTool;
     std::string                   m_coneUtilsToolAlias;

     //Minerva Math Tool 
     IMinervaMathTool*             m_mathTool;
     std::string                   m_mathToolAlias;

     //Hit Tagger Tool
     IHitTaggerTool*               m_hitTaggerTool;
     std::string                   m_hitTaggerToolAlias;
     
     //Calorimetry Utils Tool
     ICalorimetryUtils*            m_caloUtils;
     std::string                   m_caloUtilsAlias;

     //Blob Creator Tool 
     IIDAnchoredBlobCreator*       m_vtxBlobCreatorTool; 
     std::string                   m_vtxBlobCreatorAlias; 
     
     //TruthMatcher 
     ITruthMatcher*                m_truthMatcher; 
     std::string                   m_truthMatcherAlias; 
 
     


     void setTrackDirection( Minerva::Track* track, Minerva::Vertex* vertex ) const; 
     
     StatusCode makeShortTracksAtInteractionVertex( Minerva::PhysicsEvent* physEvent, std::vector<Minerva::Track*> *deShortTrackVector, bool runVertexAnchoredShortTracker, bool runVertexEnergyStudyTool ) const; 

     StatusCode makeShortTracksAtKinkVertex( Minerva::PhysicsEvent* physEvent, std::vector<Minerva::Track*> *deShortTrackVector, bool runVertexAnchoredShortTracker, bool runVertexEnergyStudyTool ) const; 
        
     StatusCode makeShortTracks_VASTracker( Minerva::PhysicsEvent* physEvent, SmartRef<Minerva::Vertex> deVertex, std::vector<Minerva::Track*> *trackVec, int generation ) const;  

     StatusCode makeShortTracks_VESTool( Minerva::PhysicsEvent* physEvent, SmartRef<Minerva::Vertex> deVertex, std::vector<Minerva::Track*> *trackVec, int generation ) const; 

     SmartRef<Minerva::Vertex> getEndPointVertex( Minerva::PhysicsEvent* physEvent, SmartRef<Minerva::Track> deTrack ) const; 
     
     double getProtonTruthSecondaryMaxDistanceInCone( Minerva::PhysicsEvent *event, Cone cone, Minerva::IDClusterVect clusters) const; 

     StatusCode makeVertexBlobs( Minerva::IDClusterVect& idClusterVector, SmartRef<Minerva::Vertex> &deVertex, double searchStepSize, unsigned int numSearchRadii, std::vector<Minerva::IDBlob*>& vtxBlobVector ) const;


};

#endif //CCQENURECOUTILS_H 
