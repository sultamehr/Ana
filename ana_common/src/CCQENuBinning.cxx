#ifndef CCQENUBINNING_cxx
#define CCQENUBINNING_cxx 1

#include "include/CCQENuBinning.h"

using namespace CCQENU_ANA;

CCQENuBinning& CCQENuBinning::Get(){
  static CCQENuBinning singleton;
    return singleton;
};

axis_binning CCQENuBinning::GetMuonPzBinsGeV( ) const{

  axis_binning tmp;
  tmp.default_width = 0.500;
  tmp.uniform = false;

  std::vector<double> bins;
  /*
  bins.push_back(0.0);
  bins.push_back( bins.back() + 3*tmp.default_width );
  for( int i = 1; i <= 4; i++ ){
    bins.push_back( bins.back() + 2*tmp.default_width );
  }
  bins.push_back( bins.back() + 4*tmp.default_width );
  bins.push_back( bins.back() + 5*tmp.default_width );
  //Extra bin for unfolding (10 to 30 GeV)
  bins.push_back( bins.back() + 40*tmp.default_width );
  */
  //  bins.push_back(0.0);
  //  bins.push_back(1.0);//Bin to keep physical acceptance... low acceptance here
  bins.push_back(1.5);
  bins.push_back(2.0);
  bins.push_back(2.5);
  bins.push_back(3.0);
  bins.push_back(3.5);
  bins.push_back(4.0);
  bins.push_back(4.5);
  bins.push_back(5.0);
  bins.push_back(6.0);
  bins.push_back(8.0);
  bins.push_back(10.0);
  bins.push_back(15.0);
  //bins.push_back(30.0);
  bins.push_back(20.0);

  //  bins.push_back(50.0);



  tmp.bin_edges = bins;
  tmp.nbins = bins.size()-1;
  tmp.min = bins.front();
  tmp.max = bins.back();

  return tmp;
}

axis_binning CCQENuBinning::GetMuonPtBinsGeV() const{
  axis_binning tmp;

  std::vector<double> bins;
 /*
  bins.push_back(0.0);
  tmp.default_width = 0.125;
  tmp.uniform = false; 
  for( int i = 1; i<= 4; i++  )  bins.push_back( bins.back() + tmp.default_width );
  for( int i = 1; i<= 2; i++  )  bins.push_back( bins.back() + 2*tmp.default_width );
  for( int i = 1; i<= 1; i++  )  bins.push_back( bins.back() + 4*tmp.default_width );
  //Extra bin for unfolding (1.5 - 4 GeV)
  //Changed limit of 4 to 2.5, hence the factor "20" now becomes an "8" 
  for( int i = 1; i<= 1; i++  )  bins.push_back( bins.back() + 20*tmp.default_width );
  */
  tmp.default_width = 0.025;
  tmp.uniform = false; 

  bins.push_back(0.0);
  bins.push_back(0.075);//added
  bins.push_back(0.15);
  bins.push_back(0.25);
  bins.push_back(0.325);//added
  bins.push_back(0.4);
  bins.push_back(0.475);//added
  bins.push_back(0.55);
  bins.push_back(0.7);
  bins.push_back(0.85);
  bins.push_back(1.0);
  bins.push_back(1.25);
  bins.push_back(1.5);
  bins.push_back(2.5);
  //bins.push_back(4.0);
  //  bins.push_back(8.0);


  tmp.bin_edges = bins;
  tmp.nbins = bins.size()-1;
  tmp.min = bins.front();
  tmp.max = bins.back();

  return tmp;

}

axis_binning CCQENuBinning::GetMuonMEPtBinsGeV() const{
  axis_binning tmp;

  std::vector<double> bins;
  tmp.default_width = 0.05;
  tmp.uniform = false;

  bins.push_back(0.00);
  bins.push_back(0.10);
  bins.push_back(0.20);
  bins.push_back(0.30);
  bins.push_back(0.40);
  bins.push_back(0.50);
  bins.push_back(0.65);
  bins.push_back(0.82);
  bins.push_back(1.00);
  bins.push_back(1.20);
  bins.push_back(1.40);
  bins.push_back(1.60);
  bins.push_back(1.80);
  bins.push_back(2.50);

  tmp.bin_edges = bins;
  tmp.nbins = bins.size()-1;
  tmp.min = bins.front();
  tmp.max = bins.back();

  return tmp;

}

axis_binning CCQENuBinning::GetMuonPz_FinerBinsGeV( ) const{

  axis_binning tmp;
  tmp.default_width = 0.75;
  tmp.uniform = false;

  std::vector<double> bins;

  bins.push_back(0.0);
  bins.push_back(0.75);
  bins.push_back(1.5);
  bins.push_back(2.0);
  bins.push_back(2.5);
  bins.push_back(3.0);
  bins.push_back(3.5);
  bins.push_back(4.0);
  bins.push_back(4.5);
  bins.push_back(5.0);
  bins.push_back(5.5); 
  bins.push_back(6.5); 
  bins.push_back(7.5); 
  bins.push_back(8.75); 
  bins.push_back(10.0);
  bins.push_back(20.0);  
  bins.push_back(30.0); 

  tmp.bin_edges = bins;
  tmp.nbins = bins.size()-1;
  tmp.min = bins.front();
  tmp.max = bins.back();

  return tmp;
}

axis_binning CCQENuBinning::GetMuonPt_FinerBinsGeV( ) const{

  axis_binning tmp; 
  tmp.default_width = 0.0625; 
  tmp.uniform = false; 

  std::vector<double> bins; 

  bins.push_back(0.0); 
  bins.push_back(0.0625);
  bins.push_back(0.125);
  bins.push_back(0.1875);
  bins.push_back(0.25);
  bins.push_back(0.3125);
  bins.push_back(0.375);
  bins.push_back(0.4375);
  bins.push_back(0.5);
  bins.push_back(0.625);
  bins.push_back(0.75); 
  bins.push_back(0.875);
  bins.push_back(1.0); 
  bins.push_back(1.25);
  bins.push_back(1.5);
  bins.push_back(2.0);
  bins.push_back(2.5);
  
  tmp.bin_edges = bins; 
  tmp.nbins = bins.size()-1; 
  tmp.min = bins.front(); 
  tmp.max = bins.back(); 

  return tmp; 
}

axis_binning CCQENuBinning::GetNuUniformBinsGeV( ) const{

  axis_binning tmp;

  std::vector<double> bins;
  int nbins = 500;
  double min = 0.0, max = 50.0;  // GeV^2 //1DME
  double binw = (max-min)/(double)nbins;

  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetNuUniform1DMEBinsGeV( ) const{

  axis_binning tmp;

  std::vector<double> bins;
  int nbins = 60;
  double min = 0.0, max = 15;  // GeV //1DME
  double binw = (max-min)/(double)nbins;

  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}


axis_binning CCQENuBinning::GetQ2BinsGeV( ) const{

  axis_binning tmp;

  std::vector<double> bins;
  double binw = 0.00625;

  bins.push_back(0.0);
  bins.push_back(0.00625);//added
  bins.push_back(0.0125);
  bins.push_back(0.025);
  bins.push_back(0.0375);
  bins.push_back(0.05);
  bins.push_back(0.1);
  bins.push_back(0.15);//added
  bins.push_back(0.2);
  bins.push_back(0.3);//added
  bins.push_back(0.4);
  bins.push_back(0.6);//added
  bins.push_back(0.8);
  bins.push_back(1.0);//added
  bins.push_back(1.2);
  bins.push_back(2.0);
  bins.push_back(4.0);
  bins.push_back(6.0);
  bins.push_back(8.0);
  bins.push_back(10.0);


  tmp.bin_edges = bins;
  tmp.nbins = bins.size()-1;
  tmp.min = bins[0];
  tmp.max = bins[bins.size()];
  tmp.uniform = false;
  tmp.default_width = binw;

  return tmp;
}


//[0,0.1) >0.25, [0.1,0.2) >0.2, [0.2,0.75) > 0.1, [0.75,∞)
axis_binning CCQENuBinning::GetQ2PIDScoreBinsGeV( ) const{

  axis_binning tmp;

  std::vector<double> bins;
  double binw = 0.05;

  bins.push_back(0.0);
  bins.push_back(0.1);
  bins.push_back(0.2);
  bins.push_back(0.75);
  bins.push_back(6);
  


  tmp.bin_edges = bins;
  tmp.nbins = bins.size()-1;
  tmp.min = bins[0];
  tmp.max = bins[bins.size()];
  tmp.uniform = false;
  tmp.default_width = binw;

  return tmp;
}



axis_binning CCQENuBinning::GetQ2UniformBinsGeV( ) const{

  axis_binning tmp;

  std::vector<double> bins;
  int nbins = 40;
  double min = 0.0, max = 2.0;  // GeV^2
  double binw = (max-min)/(double)nbins;

  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetQ2UniformBins1DMEGeV( ) const{

  axis_binning tmp;

  std::vector<double> bins;
  int nbins = 100;
  double min = 0.0, max = 10.0;  // GeV^2
  double binw = (max-min)/(double)nbins;

  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetQ2BinsGeV1Track( ) const{

  axis_binning tmp;

  std::vector<double> bins;
  bins.push_back(0.0);
  tmp.default_width = 0.1;
  tmp.uniform = false;
  bins.push_back( bins.back() + tmp.default_width );
  bins.push_back( bins.back() + tmp.default_width );
  bins.push_back( bins.back() + 2*tmp.default_width );
  bins.push_back( bins.back() + 16*tmp.default_width );

  tmp.bin_edges = bins;
  tmp.nbins = bins.size()-1;
  tmp.min = bins.front();
  tmp.max = bins.back();

  return tmp;

}

axis_binning CCQENuBinning::GetQ2Bins1DMEGeV( ) const{ 
   axis_binning tmp;
   tmp.default_width = 0.025;
   tmp.uniform = false;

   std::vector<double> bins;

   bins.push_back(  0.000 );
   bins.push_back(  0.015 );
   bins.push_back(  0.050 );
   bins.push_back(  0.150 );
   bins.push_back(  0.300 );
   bins.push_back(  0.500 );
   bins.push_back(  0.700 );
   bins.push_back(  0.900 );
   bins.push_back(  1.100 );
   bins.push_back(  1.300 );
   bins.push_back(  1.500 );
   bins.push_back(  1.700 );
   bins.push_back(  2.000 );
   bins.push_back(  2.500 );
   bins.push_back(  3.000 );
   //bins.push_back(  6.000 );
   //bins.push_back(  10.00 );

   tmp.bin_edges = bins;
   tmp.nbins = bins.size()-1;
   tmp.min = bins.front();
   tmp.max = bins.back();

   return tmp;
}

axis_binning CCQENuBinning::GetQ2BinsGeV2Track( ) const{

  axis_binning tmp;

  std::vector<double> bins;
  bins.push_back(0.0);
  tmp.default_width = 0.1;
  tmp.uniform = false;
  bins.push_back( bins.back() + 2*tmp.default_width );
  bins.push_back( bins.back() + 2*tmp.default_width );
  bins.push_back( bins.back() + 3*tmp.default_width );
  bins.push_back( bins.back() + 13*tmp.default_width );

  tmp.bin_edges = bins;
  tmp.nbins = bins.size()-1;
  tmp.min = bins.front();
  tmp.max = bins.back();

  return tmp;

}

axis_binning CCQENuBinning::GetMuonPtUniformBinsGeV() const{

  axis_binning tmp;
  std::vector<double> bins;
  int nbins = 30;
  double min = 0, max = 3.0;
  double binw = (max-min)/(double)nbins;
  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetMuonPtBinsGeV1Track() const{
  axis_binning tmp;
 
  std::vector<double> bins;
  bins.push_back(0.0);
  tmp.default_width = 0.25;
  tmp.uniform = false; 
  for( int i = 1; i<= 3; i++  )  bins.push_back( bins.back() + tmp.default_width );//0,0.25,0.50.75
  for( int i = 1; i<= 1; i++  )  bins.push_back( bins.back() + 3*tmp.default_width );//1.5
  //extra bin
  //Changed limit of 4 to 2.5, hence the factor "10" now becomes a "4" 
  bins.push_back( bins.back() + 4*tmp.default_width );//2.5
  //Need a bin from 2.5 to X?
  bins.push_back( bins.back() + 22*tmp.default_width );//8

  tmp.bin_edges = bins;
  tmp.nbins = bins.size()-1;
  tmp.min = bins.front();
  tmp.max = bins.back();

  return tmp;

}

axis_binning CCQENuBinning::GetMuonPtBinsGeV2Track() const{
  axis_binning tmp;

  std::vector<double> bins;
  bins.push_back(0.0);
  tmp.default_width = 0.25;
  tmp.uniform = false; 
  bins.push_back( bins.back() + 3*tmp.default_width );//0,0.75
  bins.push_back( bins.back() + 3*tmp.default_width );//1.5
  //extra bin
  //Changed limit of 4 to 2.5, hence the factor "10" now becomes a "4" 
  bins.push_back( bins.back() + 4*tmp.default_width );//2.5
  //Need a bin from 2.5 to X?
  bins.push_back( bins.back() + 22*tmp.default_width );//8

  tmp.bin_edges = bins;
  tmp.nbins = bins.size()-1;
  tmp.min = bins.front();
  tmp.max = bins.back();

  return tmp;

}

axis_binning CCQENuBinning::GetTotalEnergyBinsGeV() const{
  axis_binning tmp;

  std::vector<double> bins;
  bins.push_back(0.0);
  tmp.default_width = 0.250;
  tmp.uniform = false; 
  for( int i = 1; i<= 20; i++  )  bins.push_back( bins.back() + tmp.default_width );
  for( int i = 1; i<= 20; i++  )  bins.push_back( bins.back() + 2*tmp.default_width );
  for( int i = 1; i<= 5; i++  )  bins.push_back( bins.back() + 4*tmp.default_width );
  tmp.bin_edges = bins;
  tmp.nbins = bins.size()-1;
  tmp.min = bins.front();
  tmp.max = bins.back();

 return tmp;

}

axis_binning CCQENuBinning::GetMuonEnergyUniformBinsGeV() const{

  axis_binning tmp;
  std::vector<double> bins;
  int nbins = 100;
  double min = 0, max = 10.0;
  double binw = (max-min)/(double)nbins;
  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetMuonEnergyUniform1DMEBinsGeV() const{

  axis_binning tmp;
  std::vector<double> bins;
  int nbins = 60;
  double min = 0, max = 15.0;
  double binw = (max-min)/(double)nbins;
  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetBlobEnergyFractionBins() const{

  axis_binning tmp;
  std::vector<double> fractionbins;
  int nbins = 10;
  double min = 0, max = 1.0;
  double binw = (max-min)/(double)nbins;
  for( int i = 0; i <= nbins; i++ ){
    fractionbins.push_back( min + i*binw );
  }
  tmp.bin_edges = fractionbins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetBlobEnergyBinsGeV( ) const{

  axis_binning tmp;

  std::vector<double> bins;
  int nbins = 50;
  double min = 0, max = 2.0;  // GeV
  double binw = (max-min)/(double)nbins;
  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetBlobEnergyBinsMeV( ) const{

  axis_binning tmp;

  std::vector<double> bins;
  int nbins = 40; //25 MeV Bins
  double min = 0.0, max = 1000.0; // MeV
  double binw = (max-min)/(double)nbins;

  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetProtonEnergyBinsGeV( ) const{

  axis_binning tmp;

  std::vector<double> bins;
  int nbins = 50;
  double min = 0, max = 5.0;  // GeV
  double binw = (max-min)/(double)nbins;
  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetProtonTBins() const{

  axis_binning tmp;

  std::vector<double> protonbins;
  int nbins = 100;   
  double min = 0.0, max = 1000.0; 
  double binw = (max-min)/(double)nbins; 
  for( int i=0; i<=nbins; i++ ) { 
    protonbins.push_back(min + i*binw); 
  }
  tmp.bin_edges = protonbins;
  tmp.nbins = nbins; 
  tmp.min = min; 
  tmp.max = max; 
  tmp.uniform = true; 
  tmp.default_width = binw; 

  return tmp;
}

axis_binning CCQENuBinning::GetProtonTrackLengthBins() const{

  axis_binning tmp;

  std::vector<double> protonbins;
  int nbins = 25;
  double min = 0, max = 2500.0;
  double binw = (max-min)/(double)nbins;
  for( int i = 0; i <= nbins; i++ ){
    protonbins.push_back( min + i*binw );
  }
  tmp.bin_edges = protonbins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetProtonScoreBins( ) const{

  axis_binning tmp;

  std::vector<double> bins;
  int nbins = 20;
  double min = 0.0, max = 1.0;
  double binw = (max-min)/(double)nbins;

  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetProtonClusterEnergyBins() const{

  axis_binning tmp;

  std::vector<double> protonbins;
  protonbins.push_back(0.0);
  tmp.default_width = 5; 
  tmp.uniform = false; 
  for( int i = 1; i<= 4; i++  )  protonbins.push_back( protonbins.back() + tmp.default_width );
  for( int i = 1; i<= 4; i++  )  protonbins.push_back( protonbins.back() + 4*tmp.default_width );
  for( int i = 1; i<= 1; i++  )  protonbins.push_back( protonbins.back() + 20*tmp.default_width );
  for( int i = 1; i<= 1; i++  )  protonbins.push_back( protonbins.back() + 160*tmp.default_width );

  tmp.bin_edges = protonbins;
  tmp.nbins = protonbins.size()-1;
  tmp.min = protonbins.front(); 
  tmp.max = protonbins.back(); 
 
  return tmp;
}

axis_binning CCQENuBinning::GetProtonClusterFractionBins() const{ 
  
  axis_binning tmp; 
  
  std::vector<double> bins;
  bins.push_back(0.0);
  tmp.default_width = 0.01;
  tmp.uniform = false;
  for( int i = 1; i<= 5; i++  )  bins.push_back( bins.back() + 2*tmp.default_width );
  for( int i = 1; i<= 9; i++  )  bins.push_back( bins.back() + 10*tmp.default_width );
  
  tmp.bin_edges = bins;
  tmp.nbins = bins.size()-1;
  tmp.min = bins.front();
  tmp.max = bins.back();
  
  return tmp; 
}

axis_binning CCQENuBinning::GetMuonCosThetaBins() const{

  axis_binning tmp;
  
  std::vector<double> bins;
  bins.push_back(0.8);
  tmp.default_width = 0.002;
  tmp.uniform = false;
  for( int i = 1; i<= 1; i++  )  bins.push_back( bins.back() + 70*tmp.default_width );
  for( int i = 1; i<= 2; i++  )  bins.push_back( bins.back() + 5*tmp.default_width );
  for( int i = 1; i<= 4; i++  )  bins.push_back( bins.back() + 2*tmp.default_width );
  for( int i = 1; i<= 10; i++  )  bins.push_back( bins.back() + tmp.default_width );
  
  tmp.bin_edges = bins;
  tmp.nbins = bins.size()-1;
  tmp.min = bins.front();
  tmp.max = bins.back();
  
 return tmp;
}

axis_binning CCQENuBinning::GetMuonCosThetaBinsMiniBoone() const{

  axis_binning tmp;

  std::vector<double> bins;
  bins.push_back(-1.0);
  tmp.default_width = 0.1;
  tmp.uniform = false;
  for( int i = 1; i<= 20; i++  )  bins.push_back( bins.back() + tmp.default_width );

  tmp.bin_edges = bins;
  tmp.nbins = bins.size()-1;
  tmp.min = bins.front();
  tmp.max = bins.back();

  return tmp;
}

axis_binning CCQENuBinning::GetMuonTBinsMiniBoone() const{

  axis_binning tmp;

  std::vector<double> bins;
  bins.push_back(0.2);
  tmp.default_width = 0.1;
  tmp.uniform = false;
  for( int i = 1; i<= 18; i++  )  bins.push_back( bins.back() + tmp.default_width );

  tmp.bin_edges = bins;
  tmp.nbins = bins.size()-1;
  tmp.min = bins.front();
  tmp.max = bins.back();

  return tmp;
}

axis_binning CCQENuBinning::GetMuonThetaUniformBins() const{

  axis_binning tmp;

  std::vector<double> bins;
  bins.push_back(0.0);
  tmp.default_width = 1.0;
  tmp.uniform = false;
  for( int i = 1; i<= 10; i++  )  bins.push_back( bins.back() + 2.5*tmp.default_width );
  for( int i = 1; i<= 1; i++  )  bins.push_back( bins.back() + 15*tmp.default_width );

  tmp.bin_edges = bins;
  tmp.nbins = bins.size()-1;
  tmp.min = bins.front();
  tmp.max = bins.back();

 return tmp;
}

axis_binning CCQENuBinning::GetProtonThetaBins() const{

  axis_binning tmp;

  std::vector<double> bins;
  int nbins = 72;
  double min = 0.0, max = 180.0;
  double binw = (max-min)/(double)nbins;

  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetMuonThetaBins() const{

  axis_binning tmp;

  std::vector<double> bins;
  bins.push_back(0.0);
  tmp.default_width = 1.0;
  tmp.uniform = false;
  for( int i = 1; i<= 10; i++  )  bins.push_back( bins.back() + tmp.default_width );
  for( int i = 1; i<= 2; i++  )  bins.push_back( bins.back() + 2*tmp.default_width );
  for( int i = 1; i<= 2; i++  )  bins.push_back( bins.back() + 3*tmp.default_width );
  for( int i = 1; i<= 1; i++  )  bins.push_back( bins.back() + 5*tmp.default_width );
  for( int i = 1; i<= 1; i++  )  bins.push_back( bins.back() + 15*tmp.default_width );

  tmp.bin_edges = bins;
  tmp.nbins = bins.size()-1;
  tmp.min = bins.front();
  tmp.max = bins.back();

 return tmp;
}

axis_binning CCQENuBinning::GetVtxBlobDistanceBins( ) const{

  axis_binning tmp;

  std::vector<double> bins;
  int nbins = 30;
  double min = 0, max = 300.0;  // mm
  double binw = (max-min)/(double)nbins;
  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetNumClusterBins() const{

  axis_binning tmp;

  std::vector<double> protonbins;
  int nbins = 100;
  double min = 0, max = 100.0;
  double binw = (max-min)/(double)nbins;
  for( int i = 0; i <= nbins; i++ ){
    protonbins.push_back( min + i*binw );
  }
  tmp.bin_edges = protonbins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetClusterFoundOrNotBins() const{

  axis_binning tmp;

  std::vector<double> protonbins;
  int nbins = 3;
  double min = 0, max = 3.0;
  double binw = (max-min)/(double)nbins;
  for( int i = 0; i <= nbins; i++ ){
    protonbins.push_back( min + i*binw );
  }
  tmp.bin_edges = protonbins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetEnergyDifferenceBinsMeV() const{

  axis_binning tmp;

  std::vector<double> protonbins;
  int nbins = 1000;
  double min = -500, max = 500.0; // MeV
  double binw = (max-min)/(double)nbins;
  for( int i = 0; i <= nbins; i++ ) {
    protonbins.push_back( min + i*binw );
  }
  tmp.bin_edges = protonbins;
  tmp.nbins = protonbins.size()-1;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetNuBinsGeV() const{

  axis_binning tmp; 

  std::vector<double> nubins; 
  
  nubins.push_back(0.0); 
  nubins.push_back(0.1); 
  nubins.push_back(0.2); 
  nubins.push_back(0.3); 
  nubins.push_back(0.4);
  nubins.push_back(0.5); 
  nubins.push_back(0.6);
  nubins.push_back(0.7);  
  nubins.push_back(0.8);
  nubins.push_back(0.9);  
  nubins.push_back(1.0);
  nubins.push_back(5.0);  
  nubins.push_back(10.0); 
  nubins.push_back(20.0); 
  nubins.push_back(30.0); 
  nubins.push_back(50.0); 

  tmp.bin_edges = nubins; 
  tmp.nbins = nubins.size()-1;
  tmp.min = nubins.front(); 
  tmp.max = nubins.back(); 
  tmp.uniform = false; 
  tmp.default_width = 0.1; 

  return tmp; 
}

axis_binning CCQENuBinning::GetVertexZBinsModule()const{

  axis_binning tmp;

  double fullDetectorBins[] = {///*
        400.00,
        405.00,
        410.00,
        415.00,
        420.00,
        424.11224,
        428.22447,
        432.64595,
        437.06743,
        441.48891,
        445.91039,
        450.33188,
        454.75336,
        459.17484,
        463.59632,
        468.01780,
        472.43928,
        476.86077,
        481.28225,
        485.70373,
        490.12521,
        494.54669,
        498.96817,
        503.38965,
        507.81114,
        512.23262,
        516.44336,
        544.59410,
        549.01558,//*/
        553.43706,
        557.85854,
        562.28002,
        566.70151,
        571.12299,
        575.54447,
        579.91524,
        584.43814,
        588.96104,
        593.48394,
        598.00684,
        602.52974,
        607.05264,
        611.57554,
        616.09844,
        620.62134,
        625.14424,
        629.66714,
        634.19004,
        638.71294,
        643.23584,
        647.75874,
        652.28164,
        656.80454,
        661.32744,
        665.85034,
        670.37324,
        674.89614,
        679.41904,
        683.94194,
        688.46484,
        692.98774,
        697.51064,
        702.03354,
        706.55644,
        711.07934,
        715.60224,
        720.12514,
        724.64804,
        729.17094,
        733.69384,
        738.21674,
        742.73964,
        747.26254,
        751.78544,
        756.30834,
        760.83124,
        765.35414,
        769.87704,
        774.39994,
        778.92284,
        783.44574,
        787.96864,
        792.49154,
        797.01444,
        801.53734,
        806.06024,
        810.58314,
        815.10604,
        819.62894,
        824.15184,
        828.67474,
        833.19764,
        837.72054,
        842.24344,
        846.76634,
        851.28924,
        855.81214,
        860.35635,
        864.83663,
        869.31691,
        873.79718,
        878.27746,
        882.75774,
        887.23802,
        891.71830,
        896.19857,///*
        900.67885,
        905.17144,
        909.90470,
        914.63795,
        919.37121,
        924.10446,
        928.83772,
        933.57098,
        938.30423,
        943.03749,
        947.77075,
        952.50400,
        957.23726,
        961.97052,
        966.70377,
        971.43703,
        976.17029,
        980.90354,
        985.63680,
        990.37006,
        995.10331};
  std::vector<double> bins( fullDetectorBins, fullDetectorBins -1 + sizeof(fullDetectorBins)/sizeof(double) );
  int nbins = bins.size()-1;
  double min = bins.front(), max = bins.back();
  double binw = 5.0;

  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = false;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetVertexXYBins( )const{

  axis_binning tmp;

  std::vector<double> bins;
  int nbins = 40;
  double min = -100.0, max = 100.0;  // cm 
  double binw = (max-min)/(double)nbins;

  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetVertexZBins( )const{

  axis_binning tmp;

  std::vector<double> bins;
  int nbins = 100;
  double min = 600.0, max = 1100.0;  // cm 
  double binw = (max-min)/(double)nbins;

  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetVertexTBins()const{

  axis_binning tmp;

  std::vector<double> bins;
  int nbins = 100;
  double min = 0.0, max = 20.0;  // us 
  double binw = (max-min)/(double)nbins;

  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetVertexTBinsZoom()const{

  axis_binning tmp;

  std::vector<double> bins;
  int nbins = 100;
  double min = 0.0, max = 12.0;  // Mateus: Was 10.0 09-26-14 // us 
  double binw = (max-min)/(double)nbins;

  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetMuonEnergyBinsGeVfine() const{

  axis_binning tmp;

  std::vector<double> bins;
  bins.push_back(0.0);
  tmp.default_width = 0.250;
  tmp.uniform = false;
  for( int i = 1; i<= 20; i++  )  bins.push_back( bins.back() + tmp.default_width );
  for( int i = 1; i<= 20; i++  )  bins.push_back( bins.back() + 2*tmp.default_width );
  for( int i = 1; i<= 5; i++  )  bins.push_back( bins.back() + 4*tmp.default_width );
  tmp.bin_edges = bins;
  tmp.nbins = bins.size()-1;
  tmp.min = bins.front();
  tmp.max = bins.back();

 return tmp;
}

axis_binning CCQENuBinning::GetMinosVertexXYBins()const{

  axis_binning tmp;

  std::vector<double> bins;
  int nbins = 40;
  double min = -200.0, max = 200.0;  // cm 
  double binw = (max-min)/(double)nbins;

  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetMinosQPBins()const{

  axis_binning tmp;

  std::vector<double> bins;
  int nbins = 75;
  double min = -2.0, max = 1.0;
  double binw = (max-min)/(double)nbins;

  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

axis_binning CCQENuBinning::GetMinosPlanesBins()const{

  axis_binning tmp;

  std::vector<double> bins;
  int nbins = 60;
  double min = 0, max = 300.0;  // # planes 
  double binw = (max-min)/(double)nbins;

  for( int i = 0; i <= nbins; i++ ){
    bins.push_back( min + i*binw );
  }
  tmp.bin_edges = bins;
  tmp.nbins = nbins;
  tmp.min = min;
  tmp.max = max;
  tmp.uniform = true;
  tmp.default_width = binw;

  return tmp;
}

//====================================================
//------
#endif
