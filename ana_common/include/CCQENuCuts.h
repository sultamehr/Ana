#ifndef MNV_CCQENUCUTS_h
#define MNV_CCQENUCUTS_h 1

#include "include/GlobalIncludes.h"
#include "include/CCQENuEvent.h"
#include "include/CCQENuTruth.h"

namespace CCQENU_ANA{
  class CCQENuCuts {
  
   public:
  
    //! Default Constructor
    CCQENuCuts();
  
    //! Destructor
    ~CCQENuCuts();
  
    //! singleton gettor
    static CCQENuCuts& Get();
  
    bool passInteractionVertex( CCQENuEvent* event );
    bool passNuHelicityCut( CCQENuEvent* event );
    bool passDeadTimeCuts( CCQENuEvent* event );
    bool passMultiplicity( CCQENuEvent* event );
    bool passSingleProtonCut( CCQENuEvent* event, double scoreShift = 0., double q2Shift = 0. ); 
    bool passSingleProton1DMECut( CCQENuEvent* event, double scoreShift = 0., double q2Shift = 0. ); 
    bool passExtraProtonsCut( CCQENuEvent* event, double* scoreShifts = NULL, double q2Shift = 0. ); 
    bool passExtraProtons1DMECut( CCQENuEvent* event, double* scoreShifts = NULL, double q2Shift = 0. );
    bool passExtraTracksProtonsCut( CCQENuEvent* event, double* scoreShifts = NULL, double q2Shift = 0. ); 
    bool passMichelCut( CCQENuEvent* event, bool alternate_cuts = true );
    bool passImprovedMichelCut( CCQENuEvent* event, bool alternate_cuts = true );
    bool passMichelAtInteractionVertexCut( CCQENuEvent* event );
    bool passNBlobs( CCQENuEvent *event );
    bool passUnattachedEnergyCut( CCQENuEvent *event );
    bool passTrackAngleCut (CCQENuEvent *event );
    bool passTrackPzCut( CCQENuEvent *event);
  
    bool passTrueCCQE( CCQENuEvent* event );
    bool passTrueCCQE( CCQENuTruth* event );
    bool passTrueCCQE( int pdg, int current, int type, bool charm );
    bool passTrueCCRES( CCQENuEvent* event );
    bool passTrueCCRES( CCQENuTruth* event );
    bool passTrueCCRES( int pdg, int current, int type );
    bool passTrueCCDIS( CCQENuEvent* event );
    bool passTrueCCDIS( CCQENuTruth* event );
    bool passTrueCCDIS( int pdg, int current, int type );
    bool passTrueMEC( CCQENuEvent* event );
    bool passTrueMEC( CCQENuTruth* event );
    bool passTrueMEC( int pdg, int current, int type, bool charm );
    bool passMECnn( CCQENuEvent* event );
    bool passMECnn( CCQENuTruth* event );
    bool passMECnn( int pdg, int current, int type, bool charm , int nucleonhit);
    bool passMECnp( CCQENuEvent* event );
    bool passMECnp( CCQENuTruth* event );
    bool passMECnp( int pdg, int current, int type, bool charm , int nucleonhit);
    bool passMECpp( CCQENuEvent* event );
    bool passMECpp( CCQENuTruth* event );
    bool passMECpp( int pdg, int current, int type, bool charm , int nucleonhit);

    bool passTrueCCQELike( int* mc_FSPart, double* mc_FSPartE, int mc_nFSPart );
    bool passTrueCCQELike( CCQENuEvent* event );
    bool passTrueCCQELike( CCQENuTruth* event );

    bool passTrueSingleChargedPion( CCQENuEvent* event );
    bool passTrueSingleChargedPion( CCQENuTruth* event );
    bool passTrueSingleChargedPion( int nfspart, int* fspartPDG );
    
    bool passTrueSingleNeutralPion( CCQENuEvent* event );
    bool passTrueSingleNeutralPion( CCQENuTruth* event );
    bool passTrueSingleNeutralPion( int nfspart, int* fspartPDG );
    
    bool passTrueMultiPion( CCQENuEvent* event );
    bool passTrueMultiPion( CCQENuTruth* event );
    bool passTrueMultiPion( int nfspart, int* fspartPDG , int nerpart, int* erpartID, int* erpartstatus);


    bool passTruePositivePion( CCQENuEvent* event );
    bool passTruePositivePion( CCQENuTruth* event );
    bool passTruePositivePion( int nfspart, int* fspartPDG );
    bool passTrueNegativePion( CCQENuEvent* event );
    bool passTrueNegativePion( CCQENuTruth* event );
    bool passTrueNegativePion( int nfspart, int* fspartPDG );
    bool passTrueNeutralPion( CCQENuEvent* event );
    bool passTrueNeutralPion( CCQENuTruth* event );
    bool passTrueNeutralPion( int nfspart, int* fspartPDG );
    bool passTruePion( CCQENuEvent* event );
    bool passTruePion( CCQENuTruth* event );
    bool passTruePion( int nfspart, int* fspartPDG );
    bool passTrueNeutralPionAbsorbed( CCQENuEvent* event );
    bool passTrueNeutralPionAbsorbed( CCQENuTruth* event );
    bool passTrueNeutralPionAbsorbed( int nfspart, int* fspartPDG, int nerpart, int* erpartPDG );
    bool passEnuCut( double enu, double enushift = 0.);
    bool passEnuCut( CCQENuEvent *event, double enushift = 0.);
    bool passTrueEnuCut( CCQENuEvent *event);
    bool passTrueEnuCut( CCQENuTruth *event);
  
    bool passPreSelection( CCQENuEvent* event, double primaryProtonScoreShift = 0., double* secProtonsScoreShifts = NULL, double q2Shift = 0. );  
    bool pass1DMEPreSelection( CCQENuEvent* event, double primaryProtonScoreShift = 0., double* secProtonsScoreShifts = NULL, double q2Shift = 0. );  
    bool passPreSelectionMichelSideBand( CCQENuEvent* event, double primaryProtonScoreShift = 0., double* secProtonsScoreShifts = NULL, double q2Shift = 0. );  
    bool pass1DMEPreSelectionMichelSideBand( CCQENuEvent* event, double primaryProtonScoreShift = 0., double* secProtonsScoreShifts = NULL, double q2Shift = 0. );  
    bool passPreSelectionBlobSideBand( CCQENuEvent* event, double primaryProtonScoreShift = 0., double* secProtonsScoreShifts = NULL, double q2Shift = 0. );  
    bool pass1DMEPreSelectionBlobSideBand( CCQENuEvent* event, double primaryProtonScoreShift = 0., double* secProtonsScoreShifts = NULL, double q2Shift = 0. );  
    bool passPreSelectionMicBlobSideBand( CCQENuEvent* event, double primaryProtonScoreShift = 0., double* secProtonsScoreShifts = NULL, double q2Shift = 0. );  
    bool pass1DMEPreSelectionMicBlobSideBand( CCQENuEvent* event, double primaryProtonScoreShift = 0., double* secProtonsScoreShifts = NULL, double q2Shift = 0. );  

    bool passCCQESelection( CCQENuEvent* event, string sample = "Signal", double primaryProtonScoreShift = 0., double* secProtonsScoreShifts = NULL, double q2Shift = 0., double recoilShift = 0. ); 
    bool pass1DMECCQESelection( CCQENuEvent* event, string sample = "Signal", double primaryProtonScoreShift = 0., double* secProtonsScoreShifts = NULL, double q2Shift = 0., double recoilShift = 0. ); 

    bool passSignalFunction( CCQENuEvent *event, double q2shift = 0., double recoilshift = 0. );
    bool passSidebandFunction( CCQENuEvent *event, double primaryProtonScoreShift = 0., double* secProtonsScoreShifts = NULL, double q2shift = 0., double recoilshift = 0. );

    map<int,bool> getCutValues( CCQENuEvent* event );
    map<int,bool> get1DMECutValues( CCQENuEvent* event );
    map<int,bool> get1DMEnminus1CutValues( CCQENuEvent* event );
    map<int,string> getCutLabels( );
    map<int,string> getCutLabels_CCQEOneTrack( );
    map<int,Color_t> getCutColors( );
    //Get Helicity
    int getNuHelicityCut(){ return nu_helicity_cut; };
    
    //SideBand helper functions
    TF1* getRecoilCutFunctionMeV(bool is1track = true);
    TF1* getSidebandFunctionMeV(bool is1track = true);
    TF1* getRecoilCutFunction(bool is1track = true);
    TF1* getSidebandFunction(bool is1track = true);
    double getRecoilEnergy( CCQENuEvent *event );
  
    private:
  
      int nu_helicity_cut;
      int multiplicity;
      int nblobs_max;
      double proton_score;
 
      // for q2-dependent cut in recoil
      TF1 *cutline_signal_1track;
      TF1 *cutline_signal_mev_1track;
      TF1 *cutline_sideband_1track;
      TF1 *cutline_sideband_mev_1track;
      // for q2-dependent cut in recoil
      TF1 *cutline_signal_2track;
      TF1 *cutline_signal_mev_2track;
      TF1 *cutline_sideband_2track;
      TF1 *cutline_sideband_mev_2track;
  
    public:
      //dead time cut
      static const int tdead_max = 1;

      //!Analysis cut method:
      //Using muonT vs Unattached by default
      static const bool use_q2_vs_unattachedE_analysiscut = true;
      static const bool use_muonT_vs_unattachedE_analysiscut = false;
      static const bool use_muonPt_vs_unattachedE_analysiscut = false;

  };
}
#endif
