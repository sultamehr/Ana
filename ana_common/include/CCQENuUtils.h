#ifndef MNV_CCQENUUTILS_h
#define MNV_CCQENUUTILS_h 1

#include "include/CCQENuEvent.h"
#include "include/CCQENuTruth.h" 
#include "include/GlobalIncludes.h"
#include "include/GlobalParameters.h" 
#include "include/CCQENuCuts.h"
#include "include/CCQENuBinning.h"

#include "PlotUtils/MnvH1D.h"
#include "PlotUtils/MnvH2D.h"
#include "PlotUtils/MnvH3D.h"
#include "PlotUtils/AnaBinning.h"
#include "PlotUtils/MnvNormalization.h"
#include "PlotUtils/MnvRecoShifter.h"
#include "PlotUtils/HistogramUtils.h"
#include "MinervaUnfold/MnvUnfold.h"
#include "MinervaUnfold/MnvResponse.h"
#include "PlotUtils/MnvFluxConstraint.h" 
#include "PlotUtils/FluxReweighter.h"

#include "MCReweight/weightRPA.h"
#include "MCReweight/weight_2p2h.h"

using namespace PlotUtils;

// HadronReweight
namespace PlotUtils{
  class MnvHadronReweight;
  class FluxReweighter;
}

namespace CCQENU_ANA{

  class CCQENuUtils {

    typedef std::map<std::string,std::vector<double>*> StrVecMap;


    public:
    //! Default Constructor
    CCQENuUtils();

    //! Constructor with parameters
    CCQENuUtils( bool neutrinoMode, bool use_mergedFiles );

    CCQENuUtils( bool neutrinoMode, bool use_mergedFiles, bool useFluxConstraint );

    //! Default Destructor
    ~CCQENuUtils();

    //! singleton gettor
    static CCQENuUtils& Get();

    public:
    // Some units
    //MinervaUnits::numi_beam_angle_rad
    static constexpr double numi_beam_angle_rad =  -0.05887;
    static constexpr double M_mu    = 105.6583;
    //CLHEP/Units/PhysicalConstants.h
    static constexpr double M_p     = 938.272013;
    static constexpr double M_n     = 939.56536; 
    
    //Genie tune variables - default is on!//
    bool   doGenieTuning;
    static constexpr double genieMaRes              = 1.12;
    static constexpr double genieMaRes1sig          = 0.2 * 1.12;
    // GENIE central value MvRES from electroproduction data fit
    static constexpr double genieMvRes              = 0.84;
    static constexpr double genieMvRes1sig          = 0.1 * 0.84;
    // Reduced MvRES error from electroproduction data fit
    static constexpr double electroProdMvRes1sig    = 0.03 * 0.84;
    // Pion production parameters and errors from deuterium fit
    static constexpr double deuteriumMaRes          = 0.94;
    static constexpr double deuteriumMaRes1sig      = 0.05;
    static constexpr double deuteriumNonResNorm     = 0.43; //See docdb 11524 and 11567 for central value and error band modification values
    static constexpr double deuteriumNonResNorm1sig = 0.04;
    static constexpr double deuteriumResNorm        = 1.15;
    static constexpr double deuteriumResNorm1sig    = 0.07;

    //RPA CV modification
    bool doRPA;
    //Low recoil modification
    bool do2p2h;
    //RPA method 1 (use Nieves on Resonant)
    bool doRPA_Nieves_Resonant;
    //RPA method 2 (use MINOS parameterization)
    bool doRPA_MINOS_Resonant;

    //Remove Signal errors (genie, rpa, 2p2h);
    static const bool removeSignalError = false;

    //Fit parameters from low recoild
    //2D gaussian so 6 parameters. 3 variations
    double low_recoil_fit_parameters[4][6];
    std::string *myPlaylist; 
    std::string *myAnalysis; 
    std::string *myProcessing;
   
    private:
      // HadronReweight
      MnvHadronReweight *mnvHadronReweight;
      //Flux
      PlotUtils::FluxReweighter *frw;
      //2p2h and rpa classes
      weight_2p2h *weight_cv_2p2h;
      weight_2p2h *weight_nn_2p2h;
      weight_2p2h *weight_np_2p2h;
      weight_2p2h *weight_qe_2p2h;
      weightRPA *weight_cv_and_var_RPA;

      static constexpr double POT_per_MC_file = 1.0e+17;
  
      // Keep a count of the Data and MC pot after the first call
      bool loaded_pot_data;
      bool loaded_pot_mc;
 
      double global_pot_data;
      double global_total_pot_mc;
      double global_used_pot_mc;
 
      //use merged ntuples?
      bool use_merged_files;
      
      //Do we split GENIE?
      bool use_genie_split;

      //How many universes per error band?
      static const int m_nUniverses = 100;

      //Get cutter object
      CCQENuCuts *cutter;
      
      //Get RecoShifter object
      MnvRecoShifter *recoShifter;
      
      //Neutrino or Antineutrino 
      int incoming_pdg;
      
      //Correction factors
      MnvNormalizer *mnvNormalizer;
      bool use_norm_wgt;

      //Vertical/Lateral error maps
      StrVecMap *vert_error_band_wgts;
      StrVecMap *lat_error_band_wgts;
      
      //CV Weights
      double wgt_CV;
      double wgt_CV_truth;

      // shift containers 
      StrVecMap *recoil_lat_shifts;
      StrVecMap *tmu_lat_shifts;
      StrVecMap *theta_lat_shifts;
      StrVecMap *pT_lat_shifts;
      StrVecMap *pZ_lat_shifts;
      StrVecMap *q2_lat_shifts;
      StrVecMap *enu_lat_shifts;

      //Normalization weights for different playlists 
      double c_normWgt_low, c_normWgt_high; 
      // ... and the errors on the weights 
      double c_normWgtErr_low, c_normWgtErr_high; 

      //Michel Weights 
      std::vector<double> michel_weights; 

      //Target Mass Weights 
      std::vector<double> target_mass_weights; 

     //Proton Tracking Efficiency Weights 
      std::vector<double> track_eff_weights; 

    public:
      void   getPOT( double& total_pot_data, double& total_pot_mc, bool single_nu_mc = true );
      void   writePOT( TFile *f );
      void setmnvHadronReweightTruthTree(TChain *tree);
      void setmnvHadronReweightDataTree(TChain *tree);
      double getPOTData();
      double getPOTMC( bool single_nu_mc = true );
      double GetPOTWeight();
      void   updatePlaylistNorm(const CCQENuEvent *event);

      std::string printArachneLink(const CCQENuEvent *event, bool isMC);
  
      TChain* getMCTree( string name="CCQENu", int files_to_read = 0 );
      TChain* getDataTree( string name="CCQENu", int files_to_read = 0, int first_file = 0);

      double GetCVWeight( CCQENuEvent *event , string sample="Signal", bool isTrue=false);      
      double GetCVWeight( CCQENuTruth *truth ); 

      double GetNormWeight( CCQENuEvent *event ); 
      double GetNormWeightErr( CCQENuEvent *event ); 

      double GetHighestTrueProtonMomentum( CCQENuEvent *event );
      double GetHighestTrueProtonMomentum( CCQENuTruth *truth );
      double GetTransverseMomentumWRTBeam( double px, double py, double pz, double bias=0.0 );
      double GetLongitudinalMomentumWRTBeam( double px, double py, double pz, double bias=0.0 );
      double GetTotalMomentum( double px, double py, double pz );
      double GetTheta( double px, double py, double pz );
      double GetTrueCCQENeutrinoEnergy(double muonP, double muonTheta, const double bindingE);
      double GetTrueCCQEQ2(double muonP, double muonTheta, const double bindingE);
      
      double GetRPAWeight(CCQENuEvent *event, int variation);
      double GetRPAWeight(CCQENuTruth *event, int variation);

      double Get2p2hWeight(CCQENuEvent *event, int variation);
      double Get2p2hWeight(CCQENuTruth *event, int variation);

      double GetRPANievesResonantWeight(CCQENuEvent *event, int variation);
      double GetRPANievesResonantWeight(CCQENuTruth *event, int variation);

      double GetRPAMINOSResonantWeight(CCQENuEvent *event, int variation);
      double GetRPAMINOSResonantWeight(CCQENuTruth *event, int variation);

      double GetTrueQ0(CCQENuEvent *event);
      double GetTrueQ0(CCQENuTruth *event);

      double GetTrueQ3(CCQENuEvent *event);
      double GetTrueQ3(CCQENuTruth *event);

      

      void setPlaylist(std::string playlist);
      void setFluxReweighterPlaylist();
      MnvH1D* getReweightedFluxHist();
      MnvH1D* getUnweightedFluxHist();
    private:
      void setPOTMC( TChain *mc );
      void setPOTData( TChain *data );
      std::vector< std::string > split_line( std::string line, const char* split_var );

    public:
    //==============================================================
    // BookHistos (to be used int make_hists macros)
    //==============================================================
      void bookHistos( MnvH1D** h, string var_name, string title, int nbins, double min, double max );
      void bookHistos( MnvH1D** h, string var_name, string title, axis_binning xbins );
      void bookHistosByPID( MnvH1D** h, string var_name, string title, int nbins, double min, double max );
      void bookHistosByPID( MnvH1D** h, string var_name, string title, axis_binning xbins );
      void bookHistos( MnvH2D** h,string var_name,string title,axis_binning xbins, axis_binning ybins );
      void bookHistos( MnvH2D** h,string var_name,string title,int xnbins,double xmin,double xmax, int ynbins, double ymin, double ymax );
      void bookHistosByPID( MnvH2D** h,string var_name,string title,axis_binning xbins, axis_binning ybins );
      void bookHistosByPID( MnvH2D** h,string var_name,string title,int xnbins,double xmin,double xmax, int ynbins, double ymin, double ymax );
      void bookHistos( MnvH3D** h,string var_name,string title, axis_binning xbins, axis_binning ybins, axis_binning zbins );
      void bookHistos( MnvH3D** h,string var_name,string title,int xnbins,double xmin,double xmax, int ynbins, double ymin, double ymax, int znbins, double zmin, double zmax );
      void bookDataHisto( MnvH2D** h,string var_name,string title,axis_binning xbins, axis_binning ybins );
      
      //Response object functions
      void addVertErrorBands( MinervaUnfold::MnvResponse* response );
      //      void addVertErrorBands( MinervaUnfold::MnvResponse* response );
      void addLatErrorBands( MinervaUnfold::MnvResponse* response );
      //      void addLatErrorBands( MinervaUnfold::MnvResponse* response );
      void setupResponse( MinervaUnfold::MnvResponse*& response, string var_name, string title, axis_binning x_reco, axis_binning y_reco, axis_binning x_truth, axis_binning y_truth );
      void fillResponse( MinervaUnfold::MnvResponse* response, double var_x, double var_y, double var_xt, double var_yt, CCQENuEvent* event, double w );
      void fillVertErrorBands( MinervaUnfold::MnvResponse* response, double cvval_x, double cvval_y, double cvval_xtrue, double cvval_ytrue,  CCQENuEvent* event );
      //void fillVertErrorBands( MinervaUnfold::MnvResponse* response, double cvval_x, double cvval_y,double cvval_xtrue, double cvval_ytrue, double wgt_CV_NA49 ); 
      //      void fillVertErrorBands( MinervaUnfold::MnvResponse* response, double cvval_x, double cvval_y,double cvval_xtrue, double cvval_ytrue, CCQENuEvent* event ); 
      void fillLatErrorBands( MinervaUnfold::MnvResponse* response, string var_x, string var_y, double cvval_x, double cvval_y, double cvval_xtrue, double cvval_ytrue, CCQENuEvent* event, bool passcv = true ); 
      void fillLatErrorBands( MinervaUnfold::MnvResponse* response, string var_x, string var_y, double cvval_x, double cvval_y, double cvval_xtrue, double cvval_ytrue, bool passcv = true ); 
      void getResponseObjects(MinervaUnfold::MnvResponse* response, MnvH2D*& h_migration, MnvH2D*& h_reco, MnvH2D*& h_truth);
      void splitObject(MnvH2D* orig, MnvH2D** histos) ;
      void combineObject(MnvH2D* temp, MnvH2D*& target, string prefix, TFile* source_file);  

    //==============================================================
    // Fill Histos
    //==============================================================
      void fillHistos( MnvH1D** h, double var ); //fill data
      void fillHistos( MnvH1D** h, double var, CCQENuEvent* event, double w = 1.0 );
      void fillHistos( MnvH1D** h, double var, CCQENuTruth* event, double w = 1.0 );
      void fillHistosByPID( MnvH1D** h, double var ); //fill data
      void fillHistosByPID( MnvH1D** h, double var, CCQENuEvent* event, double w = 1.0 );
      void fillHistos( MnvH2D** h, double var_x, double var_y );
      void fillHistos( MnvH2D** h, double var_x, double var_y, CCQENuEvent* event, double w = 1.0 );
      void fillHistos( MnvH2D** h, double var_x, double var_y, CCQENuTruth* event, double w = 1.0 );
      void fillHistosByPID( MnvH2D** h, double var_x, double var_y ); //fill data
      void fillHistosByPID( MnvH2D** h, double var_x, double var_y, CCQENuEvent* event, double w = 1.0 );
      void fillHistos( MnvH3D** h, double var_x, double var_y, double var_z );
      void fillHistos( MnvH3D** h, double var_x, double var_y, double var_z, CCQENuEvent* event, double w = 1.0 );
      void fillHistos( MnvH3D** h, double var_x, double var_y, double var_z, CCQENuTruth* event, double w = 1.0 );

      void nameHistos( MnvH2D** h,string var_name,string title );
      void nameHistos( MnvH1D** h,string var_name,string title );

    //==============================================================
    // Create and Get Error Band functions
    //==============================================================
    public:
      std::vector<string> GetGenieKnobNames(); 
      void createVertErrorBandWgts();
      void createLatErrorBandWgts();
      StrVecMap* GetVertErrorBandWgts(){ return vert_error_band_wgts; };
      StrVecMap* GetLatErrorBandWgts(){ return lat_error_band_wgts; };

    //==============================================================
    // Add error bands
    //==============================================================
    private:
      void addVertErrorBands( MnvH1D* h );
      void addLatErrorBands(  MnvH1D* h );
      void addVertErrorBands( MnvH2D* h );
      void addLatErrorBands(  MnvH2D* h );
    public:
      void addVertErrorBands( MnvH1D** h );
      void addLatErrorBands(  MnvH1D** h );
      void addVertErrorBands( MnvH2D** h );
      void addLatErrorBands(  MnvH2D** h );
    //==============================================================
    // Fill error bands 
    //==============================================================
    public:
      void fillVertErrorBands( MnvH1D** h, double cvval, CCQENuTruth* event );
      void fillVertErrorBands( MnvH1D** h, double cvval, CCQENuEvent* event );
      void fillLatErrorBands( MnvH1D** h, string var, double cvval, CCQENuEvent* event, bool passcv = true, bool doShift = true );
      void fillVertErrorBands( MnvH2D** h, double cvval_x, double cvval_y, CCQENuTruth* event );
      void fillVertErrorBands( MnvH2D** h, double cvval_x, double cvval_y, CCQENuEvent* event );
      void fillLatErrorBands( MnvH2D** h, string var_x, string var_y, double cvval_x, double cvval_y, CCQENuEvent* event, bool passcv = true, bool doShift = true );

    private:
      //void fillVertErrorBands( MnvH1D* h, double cvval, double wgt_CV_NA49 );
      void fillVertErrorBands( MnvH1D* h, double cvval, CCQENuEvent *event );
      void fillVertErrorBands( MnvH1D* h, double cvval, CCQENuTruth *event );
      void fillLatErrorBands( MnvH1D* h, string error_band_name, double cvval, bool passcv = true, bool doShift = true );
      //void fillVertErrorBands( MnvH2D* h, double cvval_x, double cvval_y, double wgt_CV_NA49 );
      void fillVertErrorBands( MnvH2D* h, double cvval_x, double cvval_y, CCQENuEvent *event );
      void fillVertErrorBands( MnvH2D* h, double cvval_x, double cvval_y, CCQENuTruth *event );
      void fillLatErrorBands( MnvH2D* h, string var_x, string var_y, double cvval_x, double cvval_y, bool passcv = true, bool doShift = true );

      //Functions to get the weights of each universe
      void fillVertErrorBandWgts( const CCQENuTruth* event );
      void fillVertErrorBandWgts( const CCQENuEvent* event );
      // HadronReweight
      //void fillHadronReweightVertErrorBandWgts( int entry_number, bool usetruth = false, double wgt=1);
      void fillHadronReweightVertErrorBandWgts( Long64_t entry_number, bool usetruth = false, double wgt=1 );
      void fillLatErrorBandWgts( CCQENuEvent* event, string sample = "Signal", bool istrue = false );
      void fillLatErrorBandShifts( CCQENuEvent* event, string name, int universe, string sample, bool istrue );
      void getQ2Shift( double &q2shift, CCQENuEvent *event, string name, int universe );
      void getEnuShift( double &enushift, CCQENuEvent *event, string name, int universe );
      
      void fillLatErrorBandShiftsMuonVar( CCQENuEvent* event, string name, int universe, string sample, bool istrue ); 
      void fillLatErrorBandShiftsParticleResponse( CCQENuEvent* event, string name, int universe, string sample, bool istrue ); 
      void fillLatErrorBandShiftsProtonScore( CCQENuEvent* event, string name, int universe, string sample, bool istrue ); 
      void fillLatErrorBandShiftsBindingEnergy( CCQENuEvent* event, string name, int universe, string sample, bool istrue );  

    public: 
      void loadFluxConstraint(); 

      //The input pointer is passed by reference for the function to replace the input histogram, hence the "&" 
      template<class MnvHistoType, class MnvVertErrbandType> 
      void applyFluxConstraint( MnvHistoType*& histo ); 

    private: 
      MnvHistoConstrainer* m_fluxConstrainer; 

  };
}
#endif
