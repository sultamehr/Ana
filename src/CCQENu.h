#ifndef CCQENU_H 
#define CCQENU_H 1

//Inheritance
#include "AnaUtils/MinervaAnalysisTool.h"

//***Class Tools***//
class IMinervaObjectAssociator;
class IIDAnchoredBlobCreator;
class ICalorimetryUtils;
class IMichelTool;
class IImprovedMichelTool;
class IParticleMakerTool;
class IRecoObjectTimeTool;
class IHitTaggerTool;
class IPrimaryBlobProngTool;
class IProtonUtils;
class IMinervaCoordSysTool;
class IVertexEnergyStudyTool;
class IConeUtilsTool;
class Cone;
class IMinervaMathTool;
class IProngClassificationTool;
class IAnchoredTrackFormation; 
class ICCQENuRecoUtils; 



//Forward declarations
#include "Event/MinervaEventFwd.h"

class CCQENu : public MinervaAnalysisTool {

 public:

  // Standard constructor
  CCQENu( const std::string& type, const std::string& name, const IInterface* parent );

  // Destructor
  ~CCQENu(){};

  StatusCode initialize();
  StatusCode finalize();

  //mandatory method 
  StatusCode reconstructEvent( Minerva::PhysicsEvent* event, Minerva::GenMinInteraction* truth = NULL ) const;

  //mandatory
  StatusCode interpretEvent( const Minerva::PhysicsEvent* event, const Minerva::GenMinInteraction* truth, std::vector<Minerva::NeutrinoInt*>& nuInts ) const;

  //mandatory
  StatusCode tagTruth( Minerva::GenMinInteraction* truth) const;

 private:
      IGeomUtilSvc*       m_geomUtilSvc;

      //Muon q/p cut
      double              m_qOverpChargeCut;
      
      //Binding Energy
      double              m_nuCCQEBindingEnergyMeV;

      //Muon time window parameters
      double              m_lowerTimeWindow;
      double              m_upperTimeWindow;


      //Primary tag names
      std::string         m_primaryHadron;
      std::string         m_primaryProton;
      std::string         m_secondaryProtons;

      //Particle scores
      double              m_minMuonScore;
      double              m_minProtonScore;
      
      //Isolated EM Blobs parameters

      //Maximum number of isolated blobs
      double              m_maxIsoBlobs;
      
      //Prong, Blob and Cluster colors 
      int                 m_hadronProngsColor; 
      int                 m_vertexBlobProngColor; 
      int                 m_isolatedBlobProngColor; 
      int                 m_dispersedEnergyColor; 
      int                 m_protonProngColor; 
      int                 m_coneEnergyColor; 
      
      //Make Short Tracks 
      bool                m_makeShortTracks; 
      bool                m_runVertexAnchoredShortTracker;
      bool                m_runVertexEnergyStudyTool;

      bool                m_doRecursiveVertexAnchoredShortTracking; 
      bool                m_doRecursiveVESTool; 

      //Make Iso/Fuzz EM Blobs
      bool		  m_makeIsoMuonEMBlobs; 
      bool                m_makeFuzzMuonEMBlobs; 

      //Make Vertex Blobs 
      unsigned int        m_numSearchRadii; 
      double              m_searchStepSize; 

      double              m_maxSearchDistance; 
      double              m_maxStartingDistance; 
      double              m_maxAllowedSearchGap; 

      bool                m_makeFilamentStyleVtxBlobProngs; 
      bool                m_makeMultipleRadiiStyleVtxBlobProngs; 
      double              m_maxSeparationBlobVertex; 
      
      //Truth Michel Parameters
      double              m_michel_upstreamZ;
      double              m_michel_downstreamZ;

      bool                m_fillTruthTG4ProtonCone;
      
      //Proton Conditions
      bool                m_useOdMatchProtons;
      double              m_maxProtonChi2;
      double              m_ProtonZLow;
      double              m_ProtonZHigh;
      double              m_ProtonApothem;

      //muonIsPlausible
      bool                m_useMuonIsPlausible;


      //ParticleMaker Tool variables
      IParticleMakerTool*       m_particleMaker;
      std::string               m_particleMakerAlias;

      //Hit Tagger Tool
      IHitTaggerTool*           m_hitTaggerTool;
      std::string               m_hitTaggerToolAlias;

      //Calorimetry Utils Tool
      ICalorimetryUtils*        m_caloUtils;
      std::string               m_caloUtilsAlias;

      //PrimaryBlobProng Tool
      IPrimaryBlobProngTool*    m_primaryBlobProngTool;
      std::string               m_primaryBlobProngToolAlias; 

      //ProtonUtils Tool
      IProtonUtils*             m_protonUtils;
      std::string               m_protonUtilsAlias;

      //Michel Tool
      IMichelTool*              m_michelTool;
      std::string               m_michelToolAlias;
      
      //iImprovedMichelTool
      IImprovedMichelTool*      m_improvedmichelTool;
      std::string               m_improvedmichelToolAlias;

      //MinervaObjectAssociator 
      IMinervaObjectAssociator* m_objectAssociator;
      std::string               m_minObjAssocAlias; 

      IIDAnchoredBlobCreator*   m_vtxBlobCreatorTool; 
      std::string               m_vtxBlobCreatorAlias; 

      IRecoObjectTimeTool*      m_recoObjTimeTool; 
      std::string               m_recoObjTimeToolAlias; 

      IMinervaCoordSysTool*     m_minCoordSysTool; 
      std::string               m_minCoordSysToolAlias; 

      //VertexEnergyStudyTool 
      IVertexEnergyStudyTool*   m_vertexEnergyStudyTool; 
      std::string               m_vtxEngStudyToolAlias; 

      IBlobCreatorUtils*        m_blobCreatorUtils; 
      std::string               m_blobCreatorUtilsAlias; 

      IConeUtilsTool*           m_coneUtilsTool;
      std::string               m_coneUtilsToolAlias;

      static IMinervaMathTool*  m_mathTool;
      std::string               m_mathToolAlias; 

      IProngClassificationTool* m_prongIntersectionTool;
      std::string               m_prongIntersectionToolAlias;

      IAnchoredTrackFormation*  m_anchoredShortTracker; 
      std::string               m_shortTrackToolAlias; 

      ICCQENuRecoUtils*  m_minModDepCCQERecoUtils; 
      std::string               m_MMDRecoUtilsAlias; 

      //---------------------
      //Helper functions
      //---------------------

      // truthIsPlausible - a pure virtual method
      bool truthIsPlausible( const Minerva::PhysicsEvent *event ) const;

      bool getProtonProngs( Minerva::ProngVect prongs, Minerva::ProngVect& secondaryProtonProngs, SmartRef<Minerva::Prong> &protonProng, SmartRef<Minerva::Particle> &protonPart ) const;

      bool createParticles( Minerva::PhysicsEvent* event, Minerva::ProngVect& hadronProngs ) const;

      bool tagMichels( Minerva::PhysicsEvent* event, Minerva::GenMinInteraction* truth ) const;
      bool ImprovedtagMichels( Minerva::PhysicsEvent* event, Minerva::GenMinInteraction* truth ) const;

      bool hasTruthMichelElectron( Minerva::PhysicsEvent* event = NULL ) const; 

      void tagProtonProngTruth( Minerva::PhysicsEvent *event, SmartRef<Minerva::Prong> protonProng ) const;

      std::vector<double> tagMichelProngTruth( Minerva::Prong michelProng ) const;

      std::vector<double> tagBlobTruth( Minerva::IDBlob blob ) const;

      std::vector<double> tagDigitsTruth( SmartRefVector<Minerva::IDDigit> digits ) const;

      bool findLongestMinervaTrack( Minerva::Prong* deProng, SmartRef<Minerva::Track> &longestMinervaTrack ) const; 

      bool findLongestMinervaTrack( Minerva::ProngVect deProngVec, SmartRef<Minerva::Track> &longestMinervaTrack ) const; 

      bool findLongestMinervaTrack( const Minerva::PhysicsEvent *event, SmartRef<Minerva::Track> &longestMinervaTrack ) const;


};

#endif // CCQENU_H
