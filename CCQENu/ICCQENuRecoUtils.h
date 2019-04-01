#ifndef ICCQENURECOUTILS_H 
#define ICCQENURECOUTILS_H 1 

// Inheritance 
#include "GaudiKernel/IAlgTool.h" 

// Forwards 
#include "Event/VectorTypeDefs.h" //Note: includes Event/MinervaEventFwd.h   

static const InterfaceID IID_ICCQENuRecoUtils( "ICCQENuRecoUtils", 1, 0 ); 

class ICCQENuRecoUtils : virtual public IAlgTool { 

   public : 

  //Return the interface ID 
  static const InterfaceID& interfaceID() { return IID_ICCQENuRecoUtils; } 

  virtual StatusCode initialize() = 0; 
  virtual StatusCode finalize()   = 0; 

  virtual Minerva::IDClusterVect getInTimeAnalyzableIDClusters( const Minerva::PhysicsEvent *event, SmartRef<Minerva::Prong> muonProng) const=0; 

  virtual Minerva::IDClusterVect getInTimeAnalyzableNonMuonNonVtxIDClusters( const Minerva::PhysicsEvent *event, SmartRef<Minerva::Prong> muonProng, double vtxRejectionRadius) const=0; 

  virtual Minerva::IDClusterVect getInTimeAnalyzableNonMuonVtxIDClusters( const Minerva::PhysicsEvent *event, SmartRef<Minerva::Prong> muonProng, double vtxRejectionRadius) const=0; 

  virtual StatusCode runShortTrackers( Minerva::PhysicsEvent* physEvent, std::vector<Minerva::Track*> *deShortTrackVector, bool runVertexAnchoredShortTracker, bool runVertexEnergyStudyTool ) const=0;  
  
  virtual StatusCode makeConeAtEndProtonTrack( Minerva::PhysicsEvent *event, SmartRef<Minerva::Prong> protonProng, SmartRef<Minerva::Prong> muonProng, bool &foundClustersInCone, double &ConeClusterMaxDistance, Minerva::IDClusterVect &clustersInCone, bool fillTruthTG4ProtonCone = false ) const=0;

  virtual bool makeIsoEMMuonBlobs( Minerva::PhysicsEvent* event, SmartRef<Minerva::Prong> muonProng ) const=0;
     
  virtual bool makeFuzzEMMuonBlobs( Minerva::PhysicsEvent* event, SmartRef<Minerva::Prong> muonProng ) const=0; 

  virtual bool vertexTracksInTime( SmartRef<Minerva::Vertex> vtx, double muonTime ) const=0;
  
  virtual Minerva::ProngVect getInTimeTrackPID( Minerva::PhysicsEvent* event, double muonTime) const=0;



}; 

#endif // ICCQENURECOUTILS_H
     
