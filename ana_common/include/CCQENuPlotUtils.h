#ifndef MNV_CCQENUPLOTUTILS_h
#define MNV_CCQENUPLOTUTILS_h 1

#include "include/GlobalIncludes.h"
#include "include/GlobalParameters.h" 
#include "PlotUtils/MnvH1D.h"
#include "PlotUtils/MnvH2D.h"
#include "PlotUtils/MnvPlotter.h"
#include "include/CCQENuUtils.h"

using namespace PlotUtils;

namespace CCQENU_ANA{
  class CCQENuPlotUtils {
  
    public:
  
    //! Default Constructor
    CCQENuPlotUtils();
    
    //! Constructor with parameters
    CCQENuPlotUtils( bool useFluxConstraint );
  
    //! Default Destructor
    ~CCQENuPlotUtils();
  
    //! singleton gettor
    static CCQENuPlotUtils& Get();
  
    private:
  
      static const int fillStyle = 3001;
  
    // How many universes to consider for systematic error bands
      static const int m_nUniverses = 100;
      
      //Some constants
      //!@todo: Move these to GlobalIncludes, since CCQENuUtils also make use of them
      static constexpr double M_n = 939.56536;
      static constexpr double M_p = 938.272013;
      static constexpr double M_mu= 105.6583;
      static constexpr double bindingE = 34.0;
  
      static const unsigned int numImages = 4;
      static string imageFiles[4];
  
      MnvPlotter *plotter;
  
    public:
      static Color_t colors[nHistos];
      static constexpr double headroom = 1.4;
  
  
    //==============================================================
    // Get POT Information
    //==============================================================
      double getPOTData( TFile *f );
      double getPOTMC( TFile *f );
    //==============================================================
    // Get Normalization Factor
    //==============================================================
      double getAreaNormFactor(MnvH1D* h_data, MnvH1D *h_mc, bool use_underflow = false, bool use_overflow = false);
      double getAreaNormFactor(MnvH1D** h, bool use_underflow = false, bool use_overflow = false);
      double getAreaNormFactor(MnvH2D* h_data, MnvH2D *h_mc, bool use_underflow, bool use_overflow);
      double getAreaNormFactor(MnvH2D** h, bool use_underflow = false, bool use_overflow = false);
      double getPOTNormFactor(TFile *f);

    //==============================================================
    // BookHistos (to be used int make_plots macros)
    //==============================================================
      void bookHistos( TFile* file, TH1D** h, string var_name );
      void bookHistosByPID( TFile* file, TH1D** h, string var_name );
      void bookHistos( TFile* file, TH2D** h, string var_name );
      void bookHistosByPID( TFile* file, TH2D** h, string var_name );
      void bookHistos( TFile* file, MnvH1D** h, string var_name );
      void bookHistosByPID( TFile* file, MnvH1D** h, string var_name );
      void bookHistos( TFile* file, MnvH2D** h, string var_name );
      void bookHistosByPID( TFile* file, MnvH2D** h, string var_name );
      
    //==============================================================
    // draw histograms
    // drawStacked styles available:
    // QE, QE_PionInFS, QELike, QELike_split, QELike_PionInFS, QELike_split_PionInFS
    //==============================================================
      void drawStacked( MnvH1D** h, string style = "QE", bool area_norm = false, double pot_data = 0., double pot_mc = 0., bool includeData = false, double mcscale = -1., string xaxislabel = "", string yaxislabel = "", double min_x = -1., double max_x = -1., double min_y = -1., double max_y = -1.);
      void drawStacked( MnvH2D** h, string style = "QE", bool area_norm = false, double pot_data = 0., double pot_mc = 0., bool includeData = false, double mcscale = -1., string xaxislabel = "", string yaxislabel = "", double min_x = -1., double max_x = -1., double min_y = -1., double max_y = -1., bool projX = true);
      void drawStackedByPID( MnvH1D** h_original, bool area_norm = false, double pot_data = 0., double pot_mc = 0., bool includeData = false, string xaxislabel = "", string yaxislabel = "", double min_x = -1., double max_x = -1., double min_y = -1., double max_y = -1.);
      void draw2DMinibooneStyle( MnvH2D* h, bool includestats = true, bool ShapeOnly = false, double pot = 0.,  string xaxislabel = "", string yaxislabel = "", string zaxislabel ="", double x_binwidth = -1.0, double y_binwidth = -1.0, bool isMC = false );
      void draw2DMinervaStyle( MnvH2D* h, bool includestats = true, bool ShapeOnly = false, double pot = 0.,  string xaxislabel = "", string yaxislabel = "", string zaxislabel = "",double x_binwidth = -1.0, double y_binwidth = -1.0, bool isMC = false );
      void drawRatio( 
      const MnvH1D* h1,
      const MnvH1D *h2,
      const bool     drawOneLine = true,
      const double   plotMin = -1, 
      const double   plotMax = -1,
      const char*    xaxisLabel = ""   /*="" (use default axis title)*/,
      const char*    yaxisLabel = "Data / MC",
      const bool     useBinomialErrors = false 
		      );

     void drawRatio( 
      const MnvH2D* h1,
      const MnvH2D *h2,
      const char*    xaxisLabel = ""/*(use default axis title)*/,
      const char*    yaxisLabel = "" /* (use default axis title)*/,   
      const char*    zaxisLabel = "Data / MC",    /*="Data / MC"*/
      const bool     useBinomialErrors = false /*false*/
		     );

      void setHistoStyle( TH1D** h );
      void setHistoStylePID( TH1D** h );
      TLegend* getLegend( double x1, double y1 );
 
    //==============================================================
    // Systematic groups
    //==============================================================
      std::map< std::string, std::vector< std::string > > getSystematicGroupMap(bool include_genievar = false);
      std::map< std::string, int > getSystematicGroupMapColors();
      
    //==============================================================
    // Q2_QE and Enu_QE lines in P_T vs P_Z space
    //==============================================================
      TF1* getQ2Line(double q2, double pz_min = 0.0, double pz_max = 10.0, int color = kBlack); //GeV^2
      TF1* getEnuLine(double enu, double pz_min = 0.0, double pz_max = 10.0, int color = kBlack); //GeV

    //==============================================================
    // printing output files
    //==============================================================
      unsigned int NumImageFiles(){ return numImages; };
      std::vector<string> ImageFileTypes();
      void Print( TCanvas *c, string name );
      
    //==============================================================
    // Miscellaneous
    //==============================================================
      void scaleMCHistos( TH1D** h, double scale );
      void scaleMCHistos( TH2D** h, double scale );
      void scaleMCHistosByPID( TH1D** h, double scale );
      void scaleMCHistosByPID( TH2D** h, double scale );
      void scaleMCHistos( MnvH1D** h, double scale );
      void scaleMCHistos( MnvH2D** h, double scale );
      void scaleMCHistosByPID( MnvH1D** h, double scale );
      void scaleMCHistosByPID( MnvH2D** h, double scale );
      void writeNorm( bool area_norm, double pot_data, double pot_mc, bool sys_present );
      MnvPlotter* getPlotter(){ return plotter; };

    //==============================================================
    // Model Comparisons
    //==============================================================
      void drawXSDataMCModelComparisons( const MnvH1D* dataHisto, const TObjArray* mcHistos, const Double_t mcScale = 1.0,
					 const std::string& legPos = "TR", const bool covAreaNormalize = false, string xAxisLabel = "", string yAxisLabel = "" );  

      void drawXSMultiDatasetComparisons( const MnvH1D* dataHisto, const TObjArray* mcHistos, std::vector<string> radii, const Double_t mcScale = 1.0,
					  const std::string& legPos = "TR", const bool covAreaNormalize = false, string xAxisLabel = "", string yAxisLabel = "");  

      void drawXSMultiDatasetComparisonsRatio( const MnvH1D* dataHisto, const TObjArray* mcHistos, std::vector<string> radii, const Double_t mcScale = 1.0,
					  const std::string& legPos = "TR", const bool covAreaNormalize = false, string xAxisLabel = "", string yAxisLabel = ""); 

    //===============================================================
    // draw 2D plots in projected bins
    //===============================================================
      TCanvas* draw2DHistByBin( const MnvH2D* h, const std::string& legPos = "TR",const bool doXProj = true);
      TCanvas* draw2DHistsByBin( std::vector< MnvH2D* > h, const std::string& legPos = "TR", bool doXProj = true);
      TCanvas* draw2DHistsByBin( std::vector< TH2D* > h, const std::string& legPos = "TR", bool doXProj = true);
      TCanvas* draw2DHistByBinErrorSummary( const MnvH2D* h, const std::string& legPos = "TR", const bool doXProj = false, const double threshold = 0.00001, const bool covAreaNormalize = false, const bool asfrac = true);
      TCanvas* draw2DHistByBinErrorCategory( const MnvH2D* h, const std::string& legPos = "TR", string category = "", const bool doXProj = false, const double threshold = 0.00001, const bool covAreaNormalize = false, const bool asfrac = true);
      TCanvas* draw2DHistDataMCRatio( const MnvH2D* h_data, const MnvH2D* h_mc );


  };
}
#endif
