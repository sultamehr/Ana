#ifndef CCQENUBINNING_h
#define CCQENUBINNING_h 1

#include "include/GlobalIncludes.h"
#include "PlotUtils/AnaBinning.h"

using namespace PlotUtils;

namespace CCQENU_ANA{
  class CCQENuBinning {

   public:

      //! Constructor
      CCQENuBinning(){};

      //! Destructor
      ~CCQENuBinning(){};
        
      //! singleton gettor
      static CCQENuBinning& Get();
      axis_binning GetMuonPzBinsGeV()const;
      axis_binning GetTotalEnergyBinsGeV() const;
      axis_binning GetMuonEnergyUniformBinsGeV() const;
      axis_binning GetMuonEnergyUniform1DMEBinsGeV() const;
      axis_binning GetQ2BinsGeV( ) const;
      axis_binning GetQ2PIDScoreBinsGeV( ) const;
      axis_binning GetQ2UniformBinsGeV() const; //GeV^2
      axis_binning GetNuUniformBinsGeV() const; //GeV
      axis_binning GetNuUniform1DMEBinsGeV() const; //GeV
      axis_binning GetQ2UniformBins1DMEGeV() const; //GeV^2
      axis_binning GetHighQ2UniformBins1DMEGeV() const; //GeV^2
      axis_binning GetQ2Bins1DMEGeV() const; //GeV^2
      axis_binning GetQ2BinsGeV1Track() const;//GeV^2
      axis_binning GetQ2BinsGeV2Track() const;//GeV^2
      axis_binning GetProtonTBins() const; //GeV
      axis_binning GetBlobEnergyFractionBins() const;
      axis_binning GetBlobEnergyBinsGeV( ) const;
      axis_binning GetProtonTrackLengthBins() const;
      axis_binning GetProtonEnergyBinsGeV() const;
      axis_binning GetMuonPtUniformBinsGeV() const;
      axis_binning GetMuonPtBinsGeV() const;
      axis_binning GetMuonMEPtBinsGeV() const;
      axis_binning GetMuonPtBinsGeV1Track() const;
      axis_binning GetMuonPtBinsGeV2Track() const;
      axis_binning GetMuonCosThetaBins() const;
      axis_binning GetMuonThetaBins() const;
      axis_binning GetProtonThetaBins() const;
      axis_binning GetMuonThetaUniformBins() const;
      axis_binning GetProtonScoreBins() const;
      axis_binning GetBlobEnergyBinsMeV() const;
      axis_binning GetVtxBlobDistanceBins() const;
      axis_binning GetNumClusterBins() const;
      axis_binning GetClusterFoundOrNotBins() const;
      axis_binning GetEnergyDifferenceBinsMeV() const;
      axis_binning GetProtonClusterEnergyBins() const; 
      axis_binning GetProtonClusterFractionBins() const;
      axis_binning GetMuonCosThetaBinsMiniBoone() const;
      axis_binning GetMuonTBinsMiniBoone() const;

      axis_binning GetMuonPz_FinerBinsGeV( ) const; 
      axis_binning GetMuonPt_FinerBinsGeV( ) const; 

      axis_binning GetNuBinsGeV() const; 

      axis_binning GetVertexXYBins() const;
      axis_binning GetVertexZBins() const;
      axis_binning GetVertexZBinsModule() const;
      axis_binning GetVertexTBins() const;
      axis_binning GetVertexTBinsZoom() const;
      axis_binning GetQ2EnergyBinsGeV() const;
      axis_binning GetMinosVertexXYBins() const;
      axis_binning GetMinosQPBins() const;
      axis_binning GetMinosPlanesBins() const;
      axis_binning GetMuonEnergyBinsGeVfine() const;

  };
}
#endif
