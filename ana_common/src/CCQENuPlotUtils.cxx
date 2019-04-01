#ifndef MNV_CCQENUPLOTUTILS_cxx
#define MNV_CCQENUPLOTUTILS_cxx 1

#include "include/CCQENuPlotUtils.h"
//#include "include/GridCanvas.h"
#include "PlotUtils/HistogramUtils.h" //for MnvHist::IsAutoAxisLimit

using namespace CCQENU_ANA;

Color_t CCQENuPlotUtils::colors[nHistos] = {
  kBlack,      //Data
  kRed,        //MC
  kBlue-7,     //QE
  kGreen-6,    //QENot
  kOrange+1,   //RES
  kGreen-2,    //DIS
  kRed+4,      //OTH
  kBlue-7,     //QENot_PositivePions
  kOrange-3,   //QENot_PositivePions_TrueMichel
  kMagenta+3,  //QENot_PositivePions_TrueMichelNot
  kGreen-3,    //QENot_NegativePions
  kRed-4,      //QENot_pi0
  kRed+4,      //QENot_nopions
  kMagenta-4,  //QELike_QE
  kGreen-2,    //QELike_RES
  kOrange+1,   //QELike_DIS
  kBlack,      //QELike_OTH
  kMagenta-4,  //QELike
  kBlue-7,     //QELikeNot
  kRed+4,      //QELikeNot_NoPions
  kBlue-7,     //QELikeNot_PositivePions
  kOrange-3,   //QELikeNot_PositivePions_TrueMichel
  kMagenta+3,  //QELikeNot_PositivePions_TrueMichelNot
  kGreen-3,    //QELikeNot_NegativePions
  kRed-4,      //QELikeNot_pi0
  kBlue-7,     //QELikeNot_ChargedPions
  kOrange-3,   //QELikeNot_ChargedPions_TrueMichel
  kMagenta+3,  //QELikeNot_ChargedPions_TrueMichelNot
  kRed-4,      //QELikeNot_ChargedPionsNot
  kYellow-3,   //QELike_QENot
  kTeal+5,     //QELikeNot_QE
  kRed-7,      //QELikeNot_QENot
  kBlue-7,     //QELikeNot_SingleChargedPions
  kGreen-3,    //QELikeNot_SingleNeutralPions
  kRed-4,      //QELikeNot_MultiPion

};

string CCQENuPlotUtils::imageFiles[4] = {
  "png",
  "eps",
  "C",
  "root"
};

//--Default constructor
CCQENuPlotUtils::CCQENuPlotUtils()
{
  GlobalParameters::Get().m_useFluxConstraint = false;
  plotter = new MnvPlotter( PlotUtils::kCompactStyle );
}

CCQENuPlotUtils::CCQENuPlotUtils( bool useFluxConstraint )
{
  GlobalParameters::Get().m_useFluxConstraint = useFluxConstraint;
  plotter = new MnvPlotter( PlotUtils::kCompactStyle );
}

//--Destructor
CCQENuPlotUtils::~CCQENuPlotUtils()
{}

CCQENuPlotUtils& CCQENuPlotUtils::Get(){
  static CCQENuPlotUtils singleton;
  return singleton;
}

//==============================================================
// book histograms
//==============================================================
void CCQENuPlotUtils::bookHistos( TFile* file, TH1D** h, string var_name ){

  for( unsigned int i = 0; i < nHistos; i++ ){
    h[i] = (TH1D*)file->Get( ( var_name + '_' + names[i] ).c_str() );
    if( h[i] ){
      plotter->ApplyAxisStyle( h[i] );
    } else {
      cout << "Couldn't get TH1D from file: " << var_name + '_' + names[i] << endl;
    }
  }

}

void CCQENuPlotUtils::bookHistosByPID( TFile* file, TH1D** h, string var_name ){

  for( unsigned int i = 0; i < nHistosPID; i++ ){
    h[i] = (TH1D*)file->Get( ( var_name + '_' + namesPID[i] ).c_str() );
    if( h[i] ){
      plotter->ApplyAxisStyle( h[i] );
    } else {
      cout << "Couldn't get TH1D from file: " << var_name + '_' + namesPID[i] << endl;
    }
  }

}

void CCQENuPlotUtils::bookHistos( TFile* file, MnvH1D** h, string var_name ){


  for( unsigned int i = 0; i < nHistos; i++ ){
    h[i] = (MnvH1D*)file->Get( ( var_name + '_' + names[i] ).c_str() );
    /*
    MnvH1D* tmp = (MnvH1D*)file->Get( ( var_name + '_' + names[i] ).c_str() );
    h[i] = (MnvH1D*)tmp->Clone( ( var_name + "_clone_" + names[i] ).c_str() );
    */
    if( h[i] ){
      plotter->ApplyAxisStyle( h[i] );
    } else {
      cout << "Couldn't get MnvH1D from file: " << var_name + '_' + names[i] << endl;
    }
  }

}

void CCQENuPlotUtils::bookHistosByPID( TFile* file, MnvH1D** h, string var_name ){

  for( unsigned int i = 0; i < nHistosPID; i++ ){
    h[i] = (MnvH1D*)file->Get( ( var_name + '_' + namesPID[i] ).c_str() );
    if( h[i] ){
      plotter->ApplyAxisStyle( h[i] );
    } else {
      cout << "Couldn't get MnvH1D from file: " << var_name + '_' + namesPID[i] << endl;
    }
  }

}

void CCQENuPlotUtils::bookHistos( TFile* file, TH2D** h, string var_name ){

  for( unsigned int i = 0; i < nHistos; i++ ){
    h[i] = (TH2D*)file->Get( ( var_name + '_' + names[i] ).c_str() );
    if( h[i] ){
      plotter->ApplyAxisStyle( h[i] );
    } else {
      cout << "Couldn't get TH2D from file: " << var_name + '_' + names[i] << endl;
    }
  }

}

void CCQENuPlotUtils::bookHistosByPID( TFile* file, TH2D** h, string var_name ){

  for( unsigned int i = 0; i < nHistosPID; i++ ){
    h[i] = (TH2D*)file->Get( ( var_name + '_' + namesPID[i] ).c_str() );
    if( h[i] ){
      plotter->ApplyAxisStyle( h[i] );
    } else {
      cout << "Couldn't get TH2D from file: " << var_name + '_' + namesPID[i] << endl;
    }
  }

}

void CCQENuPlotUtils::bookHistos( TFile* file, MnvH2D** h, string var_name ){

  for( unsigned int i = 0; i < nHistos; i++ ){
    h[i] = (MnvH2D*)file->Get( ( var_name + '_' + names[i] ).c_str() );
    if( h[i] ){
      plotter->ApplyAxisStyle( h[i] );
    } else {
      cout << "Couldn't get MnvH2D from file: " << var_name + '_' + names[i] << endl;
    }
  }

}

void CCQENuPlotUtils::bookHistosByPID( TFile* file, MnvH2D** h, string var_name ){

  for( unsigned int i = 0; i < nHistosPID; i++ ){
    h[i] = (MnvH2D*)file->Get( ( var_name + '_' + namesPID[i] ).c_str() );
    if( h[i] ){
      plotter->ApplyAxisStyle( h[i] );
    } else {
      cout << "Couldn't get MnvH2D from file: " << var_name + '_' + namesPID[i] << endl;
    }
  }

}

void CCQENuPlotUtils::drawStackedByPID( MnvH1D** h_original, bool area_norm, double pot_data, double pot_mc, bool includeData, string xaxislabel, string yaxislabel, double min_x, double max_x, double min_y, double max_y )
{

  TH1D* h[nHistosPID];
  for( unsigned int i = 0; i < nHistosPID; i++ ){
    h[i] = (TH1D*)(h_original[i]->GetBinNormalizedCopy().GetCVHistoWithError().Clone(Form("%s_norm",h_original[i]->GetName())));
  }

  setHistoStylePID( h );
  TGaxis::SetMaxDigits(2);

  THStack* hs = new THStack();
  hs->Add( h[pOther] );
  hs->Add( h[pPion] );
  hs->Add( h[pProton] );

  TLegend* legend;
  legend = getLegend(0.6, 0.7);

  if (includeData) legend->AddEntry(h[kData],"DATA","LPE");
  legend->AddEntry(h[pProton],"proton","F");
  legend->AddEntry(h[pPion],"pion","F");
  legend->AddEntry(h[pOther],"other","F");

  hs->Draw("HIST");
  const char* x_title = strlen(xaxislabel.c_str())==0? h[kMC]->GetXaxis()->GetTitle() : xaxislabel.c_str();
  const char* y_title = strlen(yaxislabel.c_str())==0? h[kMC]->GetYaxis()->GetTitle() : yaxislabel.c_str();

  hs->GetHistogram()->GetXaxis()->SetTitle( x_title );
  hs->GetHistogram()->GetYaxis()->SetTitle( y_title  );

  //Set user range limits...
  if(min_x!=-1.0 && max_x!=-1.0) hs->GetHistogram()->GetXaxis()->SetRangeUser(min_x, max_x);
  if(min_y!=-1.0 && max_y!=-1.0) hs->GetHistogram()->GetYaxis()->SetRangeUser(min_y, max_y);

  double data_max = 0;
  if (includeData) data_max = h[kData]->GetBinContent( h[kData]->GetMaximumBin() );
  double mc_max   = h[kMC]->GetBinContent( h[kMC]->GetMaximumBin() );
  double max = ( mc_max>data_max ) ? mc_max : data_max;

  if (includeData)
  {
    h[kData]->SetMaximum( max*headroom );
    if( !gPad->GetLogy() ) h[kData]->SetMinimum(0.0);
    //Set user range limits
    if(min_x!=-1.0 && max_x!=-1.0) h[kData]->GetXaxis()->SetRangeUser(min_x, max_x);
    if(min_y!=-1.0 && max_y!=-1.0) h[kData]->GetYaxis()->SetRangeUser(min_y, max_y);

    h[kData]->Draw("X0 E1");
  }

  hs->Draw("SAME HIST");
  //hs->Draw("HIST");
  if (includeData) h[kData]->Draw("SAME X0 E1");

  legend->Draw();

  writeNorm( area_norm, pot_data, pot_mc, false );

  gPad->RedrawAxis();
  gPad->Update();

}

//==============================================================
// draw histograms
//==============================================================
void CCQENuPlotUtils::drawStacked( MnvH1D** h_original, string style, bool area_norm, double pot_data, double pot_mc, bool includeData, double mcscale, string xaxislabel, string yaxislabel, double min_x, double max_x, double min_y, double max_y )
{

  TH1D* h[nHistos];
  for( unsigned int i = 0; i < nHistos; i++ ){
    h[i] = (TH1D*)(h_original[i]->GetBinNormalizedCopy().GetCVHistoWithError().Clone(Form("%s_norm",h_original[i]->GetName())));
  }

  setHistoStyle( h );
  TGaxis::SetMaxDigits(2);

  THStack* hs = new THStack();
  if(style != "QE" && style != "QE_PionInFS" && style != "QELike" && style != "QELike_split"
     && style !=  "QELike_PionInFS" && style != "QELike_split_PionInFS"){
      cout<<"Warning: Style "<< style.c_str() << " does not exist.\nUsing style:QE instead"<<endl;
      style = "QE";
   }
  if(style == "QE"){
    hs->Add( h[kOTH] );
    hs->Add( h[kDIS] );
    hs->Add( h[kRES] );
    hs->Add( h[kQE] );
  }
  else if(style == "QE_PionInFS"){
    hs->Add( h[kQENot_NeutralPions] );
    hs->Add( h[kQENot_NegativePions] );
    hs->Add( h[kQENot_PositivePions] );
    hs->Add( h[kQENot_NoPions] );
    hs->Add( h[kQE] );
  }
  else if(style == "QELike"){
    hs->Add( h[kQELikeNot] );
    hs->Add( h[kQELike] );
  }
  else if(style == "QELike_split"){
    hs->Add( h[kQELikeNot] );
    hs->Add( h[kQELike_OTH] );
    hs->Add( h[kQELike_DIS] );
    hs->Add( h[kQELike_RES] );
    hs->Add( h[kQELike_QE] );
  }
  else if(style == "QELike_PionInFS"){
    hs->Add( h[kQELikeNot_NoPions] );
    hs->Add( h[kQELikeNot_SingleChargedPion] );
    hs->Add( h[kQELikeNot_SingleNeutralPion] );
    hs->Add( h[kQELikeNot_MultiPion] );
    hs->Add( h[kQELike] );
  }
  else if(style == "QELike_split_PionInFS"){
    hs->Add( h[kQELikeNot_NoPions] );
    hs->Add( h[kQELikeNot_SingleChargedPion] );
    hs->Add( h[kQELikeNot_SingleNeutralPion] );
    hs->Add( h[kQELikeNot_MultiPion] );
    hs->Add( h[kQELike_OTH] );
    hs->Add( h[kQELike_DIS] );
    hs->Add( h[kQELike_RES] );
    hs->Add( h[kQELike_QE] );
  }
  else if(style == "QELike_split_PionFS_MichelSplit"){
    hs->Add( h[kQELikeNot_NoPions] );
    hs->Add( h[kQELikeNot_NeutralPions] );
    hs->Add( h[kQELikeNot_NegativePions] );
    hs->Add( h[kQELikeNot_PositivePions_TrueMichel] );
    hs->Add( h[kQELikeNot_PositivePions_TrueMichelNot] );
    hs->Add( h[kQELike_OTH] );
    hs->Add( h[kQELike_DIS] );
    hs->Add( h[kQELike_RES] );
    hs->Add( h[kQELike_QE] );
  }
  else if(style == "QELike_QE"){
    hs->Add( h[kQELikeNot_QENot]);
    hs->Add( h[kQELikeNot_QE] );
    hs->Add( h[kQELike_QENot] );
    hs->Add( h[kQELike_QE] );
  }
  else if(style == "QELike_ChargedPionsInFS"){
    hs->Add( h[kQELikeNot_ChargedPionsNot] );
    hs->Add( h[kQELikeNot_ChargedPions] );
    hs->Add( h[kQELike] );
  }

  TLegend* legend;
  if(style == "QE"){
    legend = getLegend(0.6, 0.7);
  }
  else if(style == "QE_PionInFS"){
    legend = getLegend(0.6, 0.6);
  }
  else if(style == "QELike"){
    legend = getLegend(0.6, 0.7);
  }
  else if(style == "QELike_split"){
    legend = getLegend(0.5, 0.6);
  }
  else if(style == "QELike_PionInFS"){
    legend = getLegend(0.5, 0.6);
  }
  else if(style == "QELike_split_PionInFS"){
    legend = getLegend(0.5, 0.5);
  }

  if (includeData) legend->AddEntry(h[kData],"DATA","LPE");
  if(style == "QE"){
    legend->AddEntry(h[kQE],"#nu_{#mu} CC QE","F");
    legend->AddEntry(h[kRES],"#nu_{#mu} CC RES","F");
    legend->AddEntry(h[kDIS],"#nu_{#mu} CC DIS","F");
    legend->AddEntry(h[kOTH],"other","F");
  }
  else if(style == "QE_PionInFS"){
    legend->AddEntry(h[kQE],"#nu_{#mu} CC QE","F");
    legend->AddEntry(h[kQENot_NoPions],"No #pi in FS","F");
    legend->AddEntry(h[kQENot_PositivePions],"#pi+ in FS","F");
    legend->AddEntry(h[kQENot_NegativePions],"#pi- in FS","F");
    legend->AddEntry(h[kQENot_NeutralPions],"#pi^{0} in FS","F");
  }
  else if(style == "QELike"){
    legend->AddEntry(h[kQELike],"QE-Like","F");
    legend->AddEntry(h[kQELikeNot],"Not QE-Like","F");
  }
  else if(style == "QELike_split"){
    legend->AddEntry(h[kQELike_QE],"QE-Like && QE","F");
    legend->AddEntry(h[kQELike_RES],"QE-Like && RES","F");
    legend->AddEntry(h[kQELike_DIS],"QE-Like && DIS","F");
    legend->AddEntry(h[kQELike_OTH],"QE-Like && 2p2h","F");
    legend->AddEntry(h[kQELikeNot],"Not QE-Like","F");
  }
  else if(style == "QELike_PionInFS"){
    legend->AddEntry(h[kQELike],"QE-Like","F");
    legend->AddEntry(h[kQELikeNot_SingleChargedPion],"single #pi+/- in FS","F");
    legend->AddEntry(h[kQELikeNot_SingleNeutralPion],"single #pi0 in FS","F");
    legend->AddEntry(h[kQELikeNot_MultiPion],"N#pi in FS","F");
    legend->AddEntry(h[kQELikeNot_NoPions],"other","F");
  }
  else if(style =="QELike_split_PionInFS"){
    legend->AddEntry(h[kQELike_QE],"QE-Like && QE","F");
    legend->AddEntry(h[kQELike_RES],"QE-Like && RES","F");
    legend->AddEntry(h[kQELike_DIS],"QE-Like && DIS","F");
    legend->AddEntry(h[kQELike_OTH],"QE-Like && 2p2h","F");
    legend->AddEntry(h[kQELikeNot_SingleChargedPion],"single #pi+/- in FS","F");
    legend->AddEntry(h[kQELikeNot_SingleNeutralPion],"single #pi0 in FS","F");
    legend->AddEntry(h[kQELikeNot_MultiPion],"N#pi in FS","F");
    legend->AddEntry(h[kQELikeNot_NoPions],"other","F");
  }

  hs->Draw("HIST");
  const char* x_title = strlen(xaxislabel.c_str())==0? h[kMC]->GetXaxis()->GetTitle() : xaxislabel.c_str();
  const char* y_title = strlen(yaxislabel.c_str())==0? h[kMC]->GetYaxis()->GetTitle() : yaxislabel.c_str();

  hs->GetHistogram()->GetXaxis()->SetTitle( x_title );
  hs->GetHistogram()->GetYaxis()->SetTitle( y_title  );

  //Set user range limits...
  if(min_x!=-1.0 && max_x!=-1.0) hs->GetHistogram()->GetXaxis()->SetRangeUser(min_x, max_x);
  if(min_y!=-1.0 && max_y!=-1.0) hs->GetHistogram()->GetYaxis()->SetRangeUser(min_y, max_y);

  double data_max = 0;
  if (includeData) data_max = h[kData]->GetBinContent( h[kData]->GetMaximumBin() );
  double mc_max   = h[kMC]->GetBinContent( h[kMC]->GetMaximumBin() );
  double max = ( mc_max>data_max ) ? mc_max : data_max;

  if (includeData)
  {
    h[kData]->SetMaximum( max*headroom );
    if( !gPad->GetLogy() ) h[kData]->SetMinimum(0.0);
    //Set user range limits
    if(min_x!=-1.0 && max_x!=-1.0) h[kData]->GetXaxis()->SetRangeUser(min_x, max_x);
    if(min_y!=-1.0 && max_y!=-1.0) h[kData]->GetYaxis()->SetRangeUser(min_y, max_y);

    h[kData]->Draw("X0 E1");
  }

  hs->Draw("SAME HIST");
  //hs->Draw("HIST");
  if (includeData) h[kData]->Draw("SAME X0 E1");

  legend->Draw();

  writeNorm( area_norm, pot_data, pot_mc, false );

  if (mcscale!=-1.0)
  {
    int align;
    double size = 0.04;
    double xLabel, yLabel;
    plotter->DecodePosition( "TL", size, align, xLabel, yLabel );
    yLabel += -1.*size;
    const char* norm = (area_norm)? "Area" : "POT";
    plotter->AddPlotLabel( Form("%s Scale = %.3f", norm, mcscale), xLabel, yLabel, size, 1, 62, align );
  }

  gPad->RedrawAxis();
  gPad->Update();

}

void CCQENuPlotUtils::drawStacked( MnvH2D** h_original, string style, bool area_norm, double pot_data, double pot_mc, bool includeData, double mcscale, string xaxislabel, string yaxislabel, double min_x, double max_x, double min_y, double max_y, bool projX ){

  MnvH1D *tmp_hists[nHistos];
  for( unsigned int i = 0; i<nHistos; ++i){
    string name = h_original[i]->GetName();
    name+= "_proj";
    tmp_hists[i] = h_original[i]->Projection(name.c_str(),projX,0,-1,"");
  }
  drawStacked(tmp_hists,style,area_norm,pot_data,pot_mc,includeData,mcscale,xaxislabel,yaxislabel,min_x,max_x,min_y,max_y);


}


//==============================================================
// histogram style
//==============================================================
void CCQENuPlotUtils::setHistoStyle( TH1D** h ){

  for( unsigned int i = 0; i < nHistos; i++ ){
    h[i]->SetLineColor(colors[i]);
    h[i]->SetMarkerColor(colors[i]);
    h[i]->SetMarkerStyle(20);
  }

  for( unsigned int i = kQE; i < nHistos; i++ ){
    h[i]->SetFillColor(colors[i]);
    h[i]->SetFillStyle(fillStyle);
  }

  h[kMC]->SetMarkerColor(kBlack);

}
void CCQENuPlotUtils::setHistoStylePID( TH1D** h ){

  for( unsigned int i = 0; i < nHistosPID; i++ ){
    h[i]->SetLineColor(colors[i]);
    h[i]->SetMarkerColor(colors[i]);
    h[i]->SetMarkerStyle(20);
  }

  for( unsigned int i = pProton; i < nHistosPID; i++ ){
    h[i]->SetFillColor(colors[i]);
    h[i]->SetFillStyle(fillStyle);
  }

  h[kMC]->SetMarkerColor(kBlack);

}

TLegend* CCQENuPlotUtils::getLegend( double x1, double y1 ){
  double x2 = 1 - gStyle->GetPadRightMargin()-0.002;
  double y2 = 1 - gStyle->GetPadTopMargin();
  TLegend* legend = new TLegend(x1,y1,x2,y2);
  legend->SetFillColor(kWhite);
  legend->SetLineColor(kBlack);
  legend->SetTextSize(0.042);
  return legend;
}

void CCQENuPlotUtils::writeNorm( bool area_norm, double pot_data, double pot_mc, bool systematics_present ){

  plotter->WritePreliminary( "TL", 0.035 );

  int align;
  double xLabel, yLabel;
  plotter->DecodePosition( "TL", 0.045, align, xLabel, yLabel );
  if( systematics_present ) {
    //plotter->AddPlotLabel( "Stat. + Syst. Errors", xLabel, yLabel-0.04, 0.03, 9, 62, align);
  } else {
    //plotter->AddPlotLabel( "Statistical Errors Only", xLabel, yLabel-0.04, 0.03, 9, 62, align);
  }

  if( area_norm ){
    plotter->WriteNorm( "Area Normalized", "TL", 0.045, -0.08, 0, pot_data );
  } else {
    //plotter->WriteNorm( "POT Normalized", "TL", 0.045, -0.08, 0, pot );
    plotter->AddPOTNormBox( pot_data, pot_mc, 0.3, 0.85 );
  }
}

double CCQENuPlotUtils::getPOTData( TFile *f ){

  TVector2 *pot = (TVector2*)f->Get("pot");
  if( pot ){
    cout << "Data POT : " << pot->X() << endl;
    //HARDCODE TO MATCH POT CORRECTIONS (CHRIS FACTOR = 1.0182)
    // return pot->X() * 1.0182;

    //NO SCALING FACTOR SINCE JO IS TRYING TO CORRECT IT THRU CAL/GATEQUALITY
    //HAS THIS BEEN CORRECTED ?
    return pot->X();
  }
  else
    return 0;
}

double CCQENuPlotUtils::getPOTMC( TFile *f ){

  TVector2 *pot = (TVector2*)f->Get("pot");
  if( pot ){
    cout << "MC POT : " << pot->Y() << endl;
    return pot->Y();
  }
  else
    return 0;
}

void CCQENuPlotUtils::scaleMCHistos( TH1D** h, double scale ){
  for( unsigned int i = 0; i < nHistos; i++ ){
    if( i != kData )
      h[i]->Scale( scale );
  }
}

void CCQENuPlotUtils::scaleMCHistos( MnvH1D** h, double scale ){
  for( unsigned int i = 0; i < nHistos; i++ ){
    if( i != kData )
      h[i]->Scale( scale );
  }
}

void CCQENuPlotUtils::scaleMCHistos( TH2D** h, double scale ){
  for( unsigned int i = 0; i < nHistos; i++ ){
    if( i != kData )
      h[i]->Scale( scale );
  }
}

void CCQENuPlotUtils::scaleMCHistos( MnvH2D** h, double scale ){
  for( unsigned int i = 0; i < nHistos; i++ ){
    if( i != kData )
      h[i]->Scale( scale );
  }
}

void CCQENuPlotUtils::scaleMCHistosByPID( TH1D** h, double scale ){
  for( unsigned int i = 0; i < nHistosPID; i++ ){
    if( i != kData )
      h[i]->Scale( scale );
  }
}

void CCQENuPlotUtils::scaleMCHistosByPID( MnvH1D** h, double scale ){
  for( unsigned int i = 0; i < nHistosPID; i++ ){
    if( i != kData )
      h[i]->Scale( scale );
  }
}

void CCQENuPlotUtils::scaleMCHistosByPID( TH2D** h, double scale ){
  for( unsigned int i = 0; i < nHistosPID; i++ ){
    if( i != kData )
      h[i]->Scale( scale );
  }
}

void CCQENuPlotUtils::scaleMCHistosByPID( MnvH2D** h, double scale ){
  for( unsigned int i = 0; i < nHistosPID; i++ ){
    if( i != kData )
      h[i]->Scale( scale );
  }
}

//=========================================================
// printing output files
//=========================================================
std::vector<string> CCQENuPlotUtils::ImageFileTypes(){

  std::vector<string> images;
  for( unsigned int i = 0; i < NumImageFiles(); i++ )
    images.push_back( imageFiles[i] );

  return images;
}

void CCQENuPlotUtils::Print( TCanvas *c, string name ){

  const int oldVerbosity = gErrorIgnoreLevel;
  gErrorIgnoreLevel = kWarning;

  string plotsdir( Form( "%s/plots", getenv("MY_CCQENU") ) );
  if( getenv( "PLOTSDIR" ) ){
    string tmp( getenv( "PLOTSDIR" ) );
    if( ! tmp.empty() ){
      plotsdir = tmp;
    }
  }

  string imagepath( gSystem->DirName( Form("%s/%s.tmp", plotsdir.c_str(), name.c_str() ) ) );

  //Make directory if it doesn't exist
  if( !gSystem->OpenDirectory( imagepath.c_str() ) );
    gSystem->MakeDirectory( imagepath.c_str() );

  for( unsigned int i = 0; i < this->NumImageFiles(); i++ )
    c->Print( Form( "%s/%s.%s", plotsdir.c_str(), name.c_str(), this->ImageFileTypes()[i].c_str() ) );

  gErrorIgnoreLevel = oldVerbosity;
}

double CCQENuPlotUtils::getAreaNormFactor(MnvH1D** h, bool use_underflow, bool use_overflow){

  return getAreaNormFactor(h[kData], h[kMC], use_underflow, use_overflow);
}

double CCQENuPlotUtils::getAreaNormFactor(MnvH2D** h, bool use_underflow, bool use_overflow){

  return getAreaNormFactor(h[kData], h[kMC], use_underflow, use_overflow);
}

double CCQENuPlotUtils::getAreaNormFactor(MnvH1D* h_data, MnvH1D *h_mc, bool use_underflow, bool use_overflow){
   double scale = 1.0;

   double lowBin = (use_underflow)? 0: 1;
   double highBin_data = (use_overflow)? h_data->GetNbinsX()+1 : h_data->GetNbinsX();
   double highBin_mc = (use_overflow)? h_mc->GetNbinsX()+1 : h_mc->GetNbinsX();


   double area_data = h_data->Integral(lowBin, highBin_data);
   double area_mc   = h_mc->Integral(lowBin, highBin_mc);

   if( area_mc > 0 ) scale = area_data/area_mc;

   return scale;
}

double CCQENuPlotUtils::getAreaNormFactor(MnvH2D* h_data, MnvH2D *h_mc, bool use_underflow, bool use_overflow){
   double scale = 1.0;

   double lowBin = (use_underflow)? 0: 1;
   double highBin_data_x = (use_overflow)? h_data->GetNbinsX()+1 : h_data->GetNbinsX();
   double highBin_mc_x = (use_overflow)? h_mc->GetNbinsX()+1 : h_mc->GetNbinsX();
   double highBin_data_y = (use_overflow)? h_data->GetNbinsY()+1 : h_data->GetNbinsY();
   double highBin_mc_y = (use_overflow)? h_mc->GetNbinsY()+1 : h_mc->GetNbinsY();

   double area_data = h_data->Integral(lowBin, highBin_data_x, lowBin, highBin_data_y);
   double area_mc   = h_mc->Integral(lowBin, highBin_mc_x, lowBin, highBin_mc_y);

   if( area_mc > 0 ) scale = area_data/area_mc;

   return scale;
}

double CCQENuPlotUtils::getPOTNormFactor(TFile *f){

  double scale = 1.0;
  double data_pot = getPOTData( f );
  double mc_pot   = getPOTMC( f );

  if (mc_pot>0.) scale = data_pot / mc_pot;

  return scale;
}

void CCQENuPlotUtils::drawRatio(
    const MnvH1D* h1,
    const MnvH1D *h2,
    const bool     drawOneLine,  /*= true*/
    const double   plotMin,      /*=-1 (auto)*/
    const double   plotMax,      /*=-1 (auto)*/
    const char*    xaxisLabel,    /*=""*/
    const char*    yaxisLabel,    /*="Data / MC"*/
    const bool     useBinomialErrors /*false*/ //for correlated erros
                                )
{
  MnvH1D *h_ratio = (MnvH1D*)h1->Clone("h_ratio");
  h_ratio->Divide(h1, h2, 1., 1., (useBinomialErrors)? "B":"");

  if( plotMin != -1. )
    h_ratio->SetMinimum( plotMin );
  if( plotMax != -1. )
    h_ratio->SetMaximum( plotMax );

  // axis options
  const int axis_title_font_x = 62;
  const int axis_title_font_y = 62;
  const double axis_title_size_x = 0.06;
  const double axis_title_size_y = 0.06;
  //axis label options
  const int axis_label_font = 42;
  const double axis_label_size = 0.05;
  //-- marker settings
  const int ratio_marker = 20;
  const int ratio_line_width = 3;
  const int ratio_color = 1;

  //apply style
  if (string(xaxisLabel)!="") h_ratio->GetXaxis()->SetTitle( xaxisLabel );
  h_ratio->GetYaxis()->SetTitle( yaxisLabel );
  h_ratio->GetXaxis()->SetTitleFont(axis_title_font_x);
  h_ratio->GetYaxis()->SetTitleFont(axis_title_font_y);
  h_ratio->GetXaxis()->SetTitleSize(axis_title_size_x);
  h_ratio->GetYaxis()->SetTitleSize(axis_title_size_y);
  h_ratio->GetXaxis()->SetLabelFont(axis_label_font);
  h_ratio->GetYaxis()->SetLabelFont(axis_label_font);
  h_ratio->GetXaxis()->SetLabelSize(axis_label_size);
  h_ratio->GetYaxis()->SetLabelSize(axis_label_size);
  h_ratio->GetXaxis()->CenterTitle(kTRUE);
  h_ratio->SetMarkerStyle(ratio_marker);
  h_ratio->SetLineWidth(ratio_line_width);
  h_ratio->SetLineColor(ratio_color);
  h_ratio->GetXaxis()->SetNdivisions(509);
  h_ratio->DrawCopy("X0");

  //draw line at 1. if desired
  if( drawOneLine )
  {
    const TAxis *axis = h_ratio->GetXaxis();
    double lowX  = axis->GetBinLowEdge( axis->GetFirst() );
    double highX = axis->GetBinUpEdge(  axis->GetLast() );

    TLine line;
    line.SetLineStyle(2);
    line.SetLineWidth(3);
    line.SetLineColor(36);
    line.DrawLine(lowX, 1., highX, 1.); //creates a new line which is owned by gPad
  }

  gPad->RedrawAxis();
  gPad->Update();
}

void CCQENuPlotUtils::drawRatio(
    const MnvH2D* h1,
    const MnvH2D *h2,
    const char*    xaxisLabel,    /*=""*/
    const char*    yaxisLabel,    /*=""*/
    const char*    zaxisLabel,    /*="Data / MC"*/
    const bool     useBinomialErrors /*false*/ //for correlated erros
 					)
{
  MnvH2D *h_ratio = (MnvH2D*)h1->Clone("h_ratio");
  h_ratio->ClearAllErrorBands();

  //Verify ratio if needed
  /*
  for(int pT=1; pT<9; ++pT) {
    for( int pZ=1; pZ<9; ++pZ) {
      cout << pT <<" "<< pZ << " h1 " << h1->GetBinContent(pT, pZ) << " h2 "<< h2->GetBinContent(pT, pZ) << " div "<< h1->GetBinContent(pT, pZ)/ h2->GetBinContent(pT, pZ) << endl;
    }
  }
  */

  h_ratio->Divide(h1, h2, 1., 1., (useBinomialErrors)? "B":"");
  h_ratio->GetZaxis()->SetRangeUser(0.8,1.2);
  // axis options
  const int axis_title_font = 62;
  const double axis_title_size = 0.06;
  //axis label options
  const int axis_label_font = 42;
  const double axis_label_size = 0.05;

  //apply style
  if (string(xaxisLabel)!="") h_ratio->GetXaxis()->SetTitle( xaxisLabel );
  if (string(xaxisLabel)!="") h_ratio->GetYaxis()->SetTitle( yaxisLabel );
  h_ratio->GetZaxis()->SetTitle( zaxisLabel );
  h_ratio->GetXaxis()->SetTitleFont(axis_title_font);
  h_ratio->GetYaxis()->SetTitleFont(axis_title_font);
  h_ratio->GetZaxis()->SetTitleFont(axis_title_font);
  h_ratio->GetXaxis()->SetTitleSize(axis_title_size);
  h_ratio->GetYaxis()->SetTitleSize(axis_title_size);
  h_ratio->GetZaxis()->SetTitleSize(axis_title_size);
  h_ratio->GetXaxis()->SetLabelFont(axis_label_font);
  h_ratio->GetYaxis()->SetLabelFont(axis_label_font);
  h_ratio->GetZaxis()->SetLabelFont(axis_label_font);
  h_ratio->GetXaxis()->SetLabelSize(axis_label_size);
  h_ratio->GetYaxis()->SetLabelSize(axis_label_size);
  h_ratio->GetZaxis()->SetLabelSize(axis_label_size);

  gStyle->SetPaintTextFormat("2.2f");
  h_ratio->DrawCopy("colz text");

  gPad->RedrawAxis();
  gPad->Update();
}

//Miniboone Drawing Style
void CCQENuPlotUtils::draw2DMinibooneStyle(MnvH2D* h, bool includestats, bool ShapeOnly, double pot,  string xaxislabel, string yaxislabel, string zaxisLabel, double x_binwidth, double y_binwidth, bool isMC)
{
  TH2D h_data, *herr_plus, *herr_minus;
  if(isMC)
  {
    h_data        =  h->GetBinNormalizedCopy(x_binwidth, y_binwidth).GetCVHistoWithStatError( );
    herr_plus     = (TH2D*)h->GetBinNormalizedCopy(x_binwidth, y_binwidth).GetStatError( ).Clone("herr_plus");
    herr_minus    = (TH2D*)h->GetBinNormalizedCopy(x_binwidth, y_binwidth).GetStatError( ).Clone("herr_minus");
  }
  else
  {
    //Note, if binwidth=-1, the default binwidth for each axis is used (binwidth of first bin)
    h_data        =  h->GetBinNormalizedCopy(x_binwidth, y_binwidth).GetCVHistoWithError( includestats, ShapeOnly);
    herr_plus     = (TH2D*)h->GetBinNormalizedCopy(x_binwidth, y_binwidth).GetTotalError( includestats, false, ShapeOnly ).Clone("herr_plus");
    herr_minus    = (TH2D*)h->GetBinNormalizedCopy(x_binwidth, y_binwidth).GetTotalError( includestats, false, ShapeOnly ).Clone("herr_minus");
  }

  THStack *hs = new THStack("hs","Stack Histogram");

  //Let's start with the white part of the stack
  //which would be the cv - error
  TH2D *h_white = (TH2D*)h_data.Clone("h_white");
  h_white->Add( herr_plus, -1.0 );

  //Now, let's make a flat cv block that
  //will be between error_minus and error_plus
  //Define it as 1% of the max bin value
  TH2D *h_cv = (TH2D*)h_data.Clone("h_cv");
  const int    maxbin     = h_cv->GetMaximumBin();
  const double maxcontent = h_cv->GetBinContent( maxbin );
  const int Nbins = h_cv->GetBin( h_cv->GetNbinsX(), h_cv->GetNbinsY());
  for( int i=0; i<Nbins; ++i)
  {
    if( h_data.GetBinContent(i) > 0.0 ) h_cv->SetBinContent( i, maxcontent * 0.01 );
  }

  h_white->SetFillColor(kWhite+10);
  h_cv->SetFillColor(kRed);
  herr_plus->SetFillColor( kCyan);
  herr_minus->SetFillColor( kCyan);

  hs->Add( h_white );
  hs->Add( herr_minus );
  hs->Add( h_cv );
  hs->Add( herr_plus );

  hs->Draw();
  const char* x_title = strlen(xaxislabel.c_str())==0? h->GetXaxis()->GetTitle() : xaxislabel.c_str();
  const char* y_title = strlen(yaxislabel.c_str())==0? h->GetYaxis()->GetTitle() : yaxislabel.c_str();

  if(h->GetXaxis()->TestBit(TAxis::kAxisRange)) hs->GetHistogram()->GetXaxis()->SetRange( h->GetXaxis()->GetFirst(), h->GetXaxis()->GetLast() );
  if(h->GetYaxis()->TestBit(TAxis::kAxisRange)) hs->GetHistogram()->GetYaxis()->SetRange( h->GetYaxis()->GetFirst(), h->GetYaxis()->GetLast() );
  hs->GetHistogram()->GetXaxis()->SetTitle(x_title);
  hs->GetHistogram()->GetYaxis()->SetTitle(y_title);
  hs->GetHistogram()->GetXaxis()->SetTitleSize(0.04);
  hs->GetHistogram()->GetYaxis()->SetTitleSize(0.04);
  hs->GetHistogram()->GetXaxis()->SetTitleOffset(1.6);
  hs->GetHistogram()->GetYaxis()->SetTitleOffset(1.6);
  hs->GetHistogram()->GetXaxis()->SetLabelSize(0.03);
  hs->GetHistogram()->GetYaxis()->SetLabelSize(0.03);
  hs->GetHistogram()->GetZaxis()->SetLabelSize(0.03);


  TLegend *legend;
  legend = getLegend(0.6, 0.7);

  plotter->AddPlotLabel( "MINER#nuA Preliminary #bullet  #nu CH #rightarrow CCQE-like", .5, 0.95, .05, 4, 132,22);
  if (pot!=0.) plotter->AddPlotLabel( Form("%s %.2e POT", (isMC)? "MC":"DATA", pot), .5, 0.95-0.05, .05*0.8, 4, 132,22);
  plotter->AddPlotLabel( zaxisLabel.c_str(),  0.2, 0.87, .03);


  //gPad->RedrawAxis();
  gPad->Update();

}

void CCQENuPlotUtils::draw2DMinervaStyle(MnvH2D* h, bool includestats, bool ShapeOnly, double pot,  string xaxislabel, string yaxislabel, string zaxislabel, double x_binwidth, double y_binwidth, bool isMC )
{
  TH2D *h_temp =  (TH2D*)h->GetBinNormalizedCopy(x_binwidth, y_binwidth).GetCVHistoWithError( includestats, ShapeOnly).Clone("h_temp");

  const char* x_title = strlen(xaxislabel.c_str())==0? h->GetXaxis()->GetTitle() : xaxislabel.c_str();
  const char* y_title = strlen(yaxislabel.c_str())==0? h->GetYaxis()->GetTitle() : yaxislabel.c_str();
  const char* z_title = strlen(zaxislabel.c_str())==0? h->GetZaxis()->GetTitle() : zaxislabel.c_str();

  h_temp->GetXaxis()->SetTitle( x_title );
  h_temp->GetYaxis()->SetTitle( y_title );
  h_temp->GetZaxis()->SetTitle( z_title );
  h_temp->GetZaxis()->SetLabelOffset( 0.004);

  plotter->SetRedHeatPalette();
  h_temp->Draw("colz");

  TString toplabel = "#nu_{#mu} Tracker #rightarrow CCQE-like";
  plotter->AddHistoTitle((isMC)? "MC": "DATA");
  plotter->AddPlotLabel( toplabel.Data(), 0.285, 0.93, 0.033 );
  plotter->AddPlotLabel( "MINER#nuA Preliminary", 0.6, 0.93, 0.033,kBlue, 32, 11 );
  if (pot!=0.) plotter->AddPlotLabel( Form("%s %.2e POT", (isMC)? "MC":"DATA", pot), .5, 0.93-0.05, .05*0.8, 4, 132,22);

  //gPad->RedrawAxis();
  gPad->Update();
}

std::map< std::string, std::vector< std::string > > CCQENuPlotUtils::getSystematicGroupMap(bool include_genievar){

  cout << "CCQENUPlotUtils::GlobalParameters::Get().m_useFluxConstraint " << GlobalParameters::Get().m_useFluxConstraint << endl;
  std::map< string, std::vector< string> > systematicgroupmap;
  std::vector< string > flux;

  if( GlobalParameters::Get().m_useFluxConstraint ) {
    flux.push_back("Flux");
  } else {
    if( GlobalParameters::Get().m_usePPFX1Flux ) {
      flux.push_back("Flux_BeamFocus");
      flux.push_back("Flux_HadronProduction");
    }
    else{
      flux.push_back("Flux_NA49");
      flux.push_back("Flux_Tertiary");
      flux.push_back("Flux_BeamFocus");
    }
  }
  systematicgroupmap["Flux"] =  flux;

  /*
  std::vector< string > geniegroup;
  geniegroup.push_back( "GENIE_CCQEPauliSupViaKF" );
  geniegroup.push_back( "GENIE_EtaNCEL" );
  geniegroup.push_back( "GENIE_MaCCQE" );
  geniegroup.push_back( "GENIE_MaCCQEshape" );
  geniegroup.push_back( "GENIE_MaNCEL" );
  geniegroup.push_back( "GENIE_MaRES" );
  geniegroup.push_back( "GENIE_MvRES" );
  geniegroup.push_back( "GENIE_NormCCQE" );
  geniegroup.push_back( "GENIE_NormCCRES" );
  geniegroup.push_back( "GENIE_NormDISCC" );
  geniegroup.push_back( "GENIE_NormNCRES" );
  geniegroup.push_back( "GENIE_Rvn1pi" );
  geniegroup.push_back( "GENIE_Rvn2pi" );
  geniegroup.push_back( "GENIE_Rvp1pi" );
  geniegroup.push_back( "GENIE_Rvp2pi" );
  geniegroup.push_back( "GENIE_VecFFCCQEshape" );
  geniegroup.push_back( "GENIE_AGKYxF1pi" );
  geniegroup.push_back( "GENIE_FrAbs_N" );
  geniegroup.push_back( "GENIE_FrAbs_pi" );
  geniegroup.push_back( "GENIE_FrCEx_N" );
  geniegroup.push_back( "GENIE_FrCEx_pi" );
  geniegroup.push_back( "GENIE_FrElas_N" );
  geniegroup.push_back( "GENIE_FrElas_pi" );
  geniegroup.push_back( "GENIE_FrInel_N" );
  geniegroup.push_back( "GENIE_FrInel_pi" );
  geniegroup.push_back( "GENIE_FrPiProd_N" );
  geniegroup.push_back( "GENIE_FrPiProd_pi" );
  geniegroup.push_back( "GENIE_MFP_N" );
  geniegroup.push_back( "GENIE_MFP_pi" );
  geniegroup.push_back( "GENIE_RDecBR1gamma" );
  geniegroup.push_back( "GENIE_Theta_Delta2Npi" );
  geniegroup.push_back( "GENIE_AhtBY" );
  geniegroup.push_back( "GENIE_BhtBY" );
  geniegroup.push_back( "GENIE_CV1uBY" );
  geniegroup.push_back( "GENIE_CV2uBY" );
  systematicgroupmap["Interaction Model"] = geniegroup;
  */

  std::vector< string > xsection;
  xsection.push_back( "GENIE_CCQEPauliSupViaKF" );
  xsection.push_back( "GENIE_EtaNCEL" );
  //xsection.push_back( "GENIE_MaCCQE" );
  xsection.push_back( "GENIE_MaCCQEshape" );
  xsection.push_back( "GENIE_MaNCEL" );
  xsection.push_back( "GENIE_MaRES" );
  xsection.push_back( "GENIE_MvRES" );
  xsection.push_back( "GENIE_NormCCQE" );
  xsection.push_back( "GENIE_NormCCRES" );
  xsection.push_back( "GENIE_NormDISCC" );
  xsection.push_back( "GENIE_NormNCRES" );
  xsection.push_back( "GENIE_Rvn1pi" );
  xsection.push_back( "GENIE_Rvn2pi" );
  xsection.push_back( "GENIE_Rvp1pi" );
  xsection.push_back( "GENIE_Rvp2pi" );
  xsection.push_back( "GENIE_VecFFCCQEshape" );
  xsection.push_back( "GENIE_AhtBY" );
  xsection.push_back( "GENIE_BhtBY" );
  xsection.push_back( "GENIE_CV1uBY" );
  xsection.push_back( "GENIE_CV2uBY" );
  xsection.push_back( "RPA_HighQ2" );
  xsection.push_back( "RPA_LowQ2" );
  systematicgroupmap["XSection Models"] = xsection;

  std::vector< string > fsi;
  fsi.push_back( "GENIE_AGKYxF1pi" );
  fsi.push_back( "GENIE_FrAbs_N" );
  fsi.push_back( "GENIE_FrAbs_pi" );
  fsi.push_back( "GENIE_FrCEx_N" );
  fsi.push_back( "GENIE_FrCEx_pi" );
  fsi.push_back( "GENIE_FrElas_N" );
  fsi.push_back( "GENIE_FrElas_pi" );
  fsi.push_back( "GENIE_FrInel_N" );
  fsi.push_back( "GENIE_FrInel_pi" );
  fsi.push_back( "GENIE_FrPiProd_N" );
  fsi.push_back( "GENIE_FrPiProd_pi" );
  fsi.push_back( "GENIE_MFP_N" );
  fsi.push_back( "GENIE_MFP_pi" );
  fsi.push_back( "GENIE_RDecBR1gamma" );
  fsi.push_back( "GENIE_Theta_Delta2Npi" );
  systematicgroupmap["FSI Models"] = fsi;

  // std::vector< string > genievar;
  // genievar.push_back( "GENIE_nonreweightable" );
  // systematicgroupmap["Nonreweightable"] = genievar;

  // std::vector< string > genie2p2h;
  // genie2p2h.push_back( "GENIE_2p2h" );
  // systematicgroupmap["2p2h"] = genie2p2h;

  std::vector< string > lowrecoilfit;
  lowrecoilfit.push_back("Low_Recoil_Fit");
  systematicgroupmap["Low Recoil Fit"] = lowrecoilfit;

  std::vector< string > muon;
  muon.push_back( "Muon_Energy" );
  muon.push_back( "Muon_Theta" );
  //muon.push_back( "Normalization_Factors" );
  systematicgroupmap["Muon Reconstruction"] = muon;

  // std::vector< string > energy;

  // systematicgroupmap["Recoil Reconstruction"] = energy;

  // std::vector< string > protonreco;
  // systematicgroupmap["Proton Reconstruction"] = protonreco;

  // std::vector< string > hadronInteraction;
  // hadronInteraction.push_back( "Reweight_Pion" );
  // hadronInteraction.push_back( "Reweight_Proton" );
  // hadronInteraction.push_back( "Reweight_Neutron" );
  // systematicgroupmap["Hadron Interaction"] = hadronInteraction;


  std::vector< string > michel;
  michel.push_back( "Normalization_Factors" );
  michel.push_back( "Michel_Efficiency");
  michel.push_back( "Target_Mass" );
  michel.push_back( "GENIE_nonreweightable" );
  michel.push_back( "Muon_Response" );
  michel.push_back( "Proton_Response" );
  michel.push_back( "Low_Neutron_Response" );
  michel.push_back( "Mid_Neutron_Response" );
  michel.push_back( "High_Neutron_Response" );
  michel.push_back( "Pion_Response" );
  michel.push_back( "EM_Response" );
  michel.push_back( "Other_Response" );
  michel.push_back( "Crosstalk" );
  michel.push_back( "MEU_Recoil" );
  michel.push_back( "Binding_Energy" );
  michel.push_back( "Reweight_Pion" );
  michel.push_back( "Reweight_Proton" );
  michel.push_back( "Reweight_Neutron" );
  michel.push_back( "Bethe_Bloch" );
  michel.push_back( "MEU_Proton" );
  michel.push_back( "Mass_Model_Proton" );
  michel.push_back( "Birks_Response_Proton" );
  michel.push_back( "Proton_TrackEff" );
  systematicgroupmap["Others"] = michel;

  // std::vector< string > protonTrackEff;
  // protonTrackEff.push_back( "Proton_TrackEff" );
  // systematicgroupmap["Proton Track Eff"] = protonTrackEff;

  return systematicgroupmap;

}

std::map< std::string, int > CCQENuPlotUtils::getSystematicGroupMapColors() {
  std::map< string, int > systematicMap;

  systematicMap["Flux"]                    = kViolet+6;
  systematicMap["Recoil Reconstruction"]   = kOrange+2;
  systematicMap["XSection Models"]         = kMagenta;
  systematicMap["FSI Models"]              = kRed;
  //systematicMap["Interaction Model"]     = kMagenta;
  systematicMap["Muon Reconstruction"]     = kOrange-3;
  //  systematicMap["Proton Reconstruction"]   = kBlue-5;
  //  systematicMap["Hadron Interaction"]      = kGreen+3;
  systematicMap["Others"]                  = kGreen+3;
  //  systematicMap["Proton Track Eff"]        = kGreen-3;
  //  systematicMap["Nonreweightable"]         = kBlue-9;
  //  systematicMap["2p2h"]                    = kViolet;

  return systematicMap;
}

TF1* CCQENuPlotUtils::getEnuLine(double enu, double pz_min, double pz_max, int color) {

   // Parameters:
   //[0] = Enu
   //[1] = Binding Energy
   //[2] = M_N
   //[3] = M_mu
   //[4] = M_p
  TF1 *fenu = new TF1("fenu", "sqrt( pow((2*[0]*([1]-[2]-x)-pow([3],2)+pow([4],2)-pow([2]-[1],2))/([1]-2*([0]+[2])),2) - pow(x,2) - pow([3],2))", pz_min, pz_max);

  fenu->SetParameters( enu, bindingE/pow(10,3), M_n/pow(10,3), M_mu/pow(10,3), M_p/pow(10,3) );
  fenu->SetLineColor( color );
  fenu->SetLineWidth(2.5);

  return fenu;
}

TF1* CCQENuPlotUtils::getQ2Line(double q2, double pz_min, double pz_max, int color) {

   // Parameters:
   //[0] = Q2
   //[1] = Binding Energy
   //[2] = M_N
   //[3] = M_mu
   //[4] = M_p
  //D = Solution to sqrt(P_T^2 + P_Z^2 + M_mu^2)
  std::string D = "(sqrt(pow([0],2)+(2*pow([4],2) + 2*pow([1],2)+ (-8*[2] - 2*x)*[1] + 6*pow([2],2) + 4*x*[2])*[0] + pow([4],4) + (-2*pow([1],2) + (4*[2] - 2*x)*[1] - 2*pow([2],2) + 4*x*[2])*pow([4],2) + pow([1],4) + (2*x - 4*[2])*pow([1],3) + (6*pow([2],2) - 8*x*[2] + 4*pow([3],2) + pow(x,2))*pow([1],2) + (-4*pow([2],3) + 10*x*pow([2],2) + (-12*pow([3],2) - 4*pow(x,2))*[2])*[1]+pow([2],4) - 4*x*pow([2],3) + (8*pow([3],2) + 4*pow(x,2))*pow([2],2)) - [0] - pow([4],2) + pow([1],2) + (-2*[2] - x)*[1] + pow([2],2) + 2*x*[2])/(-2*[1] + 4*[2])";
  // so P_T = sqrt( D^2 - P_Z^2 - M_mu^2 )
  std::string PT = Form("sqrt(pow(%s,2) - pow(x,2) - pow([3],2))",D.c_str());
  TF1 *fq2 = new TF1("fq2", PT.c_str(), pz_min, pz_max);

  fq2->SetParameters( q2, bindingE/pow(10,3), M_n/pow(10,3), M_mu/pow(10,3), M_p/pow(10,3) );
  fq2->SetLineColor( color );
  fq2->SetLineWidth(2.5);

  return fq2;
}

void CCQENuPlotUtils::drawXSDataMCModelComparisons(const MnvH1D* dataHisto, const TObjArray* mcHistos, const Double_t mcScale,
							  const std::string& legPos, const bool covAreaNormalize, string xAxisLabel, string yAxisLabel) {

  unsigned int nHists = mcHistos->GetEntries();

  vector<string> histoTitles;
  histoTitles.push_back( dataHisto->GetTitle() );

  const char* xAxisTitle = strlen(xAxisLabel.c_str())==0? dataHisto->GetXaxis()->GetTitle() : xAxisLabel.c_str();
  const char* yAxisTitle = strlen(yAxisLabel.c_str())==0? dataHisto->GetYaxis()->GetTitle() : yAxisLabel.c_str();

  //Be sure to consider a logY axis
  //Find the maximum amongst all histograms
  //TO-DO: For logY we really want to know the minimum non-zero value !!!

  //Kenyi: Need to discuss the importance of minYValue here.

  double maxYValue = dataHisto->GetMaximum();
  double minYValue = dataHisto->GetMinimum();

  if( gPad->GetLogy() && minYValue < 1.E-8 ) {
    minYValue = -1.0; //Why is Kenyi doing this ?
  }

  for( unsigned int i=0; i != nHists; ++i ) {

    MnvH1D* mcMnv = (MnvH1D*)mcHistos->At(i);
    maxYValue = std::max( maxYValue, mcScale*mcMnv->GetMaximum() );
    if( 1.E-8 < mcMnv->GetMinimum() ) {
      minYValue = std::min( minYValue, mcScale*mcMnv->GetMinimum() );
    }
    histoTitles.push_back( mcMnv->GetTitle() );
  }
  if( gPad->GetLogy() ) {
    minYValue = std::max( minYValue, 1.E-8 );
  }

  //  size_t titleWidth = plotter->GetLegendWidthInLetters( histoTitles );

  TLegend *legend;
  legend = getLegend(0.6, 0.7);

  legend->SetNColumns( plotter->legend_n_columns );
  static int legB_n = 0;
  legend->SetName( Form("legend B - %d", legB_n++) );
  //plotter->AddToTmp( legend );

  legend->SetBorderSize( plotter->legend_border_size );
  legend->SetFillColor( plotter->legend_fill_color );
  if( plotter->legend_fill_color < 0 ) {
    legend->SetFillStyle(0);
  }
  legend->SetTextSize( plotter->legend_text_size );
  legend->SetTextFont( plotter->legend_text_font );

  //Make plots on the clone because it gets added to the legend ?
  //Kenyi: Why did he put a "?" and the above line is not clear to me
  TH1* tmpData(0);
  TH1* tmpDataStat(0);
  tmpData = (TH1*)dataHisto->GetCVHistoWithError(true, covAreaNormalize).Clone( Form("tmpData_%d", __LINE__) );
  tmpDataStat = (TH1*)dataHisto->GetCVHistoWithStatError().Clone( Form("tmpDataStat_%d", __LINE__) );
  //plotter->AddToTmp( tmpData );

  //Employ max/min settings as desired by user
  if( MnvHist::IsAutoAxisLimit( plotter->axis_minimum ) ) {
    if( plotter->hist_min_zero && !gPad->GetLogy() ) {
      tmpData->SetMinimum( 0.0 );
    } else {
      tmpData->SetMinimum( plotter->footroom*minYValue );
    }
  } else {
    tmpData->SetMinimum( plotter->axis_minimum );
  }

  if( MnvHist::IsAutoAxisLimit( plotter->axis_maximum ) ) {
    if( gPad->GetLogy() ) {
      tmpData->SetMaximum( pow( headroom*maxYValue, 10.0 ) );
    } else {
      tmpData->SetMaximum( headroom*maxYValue );
    }
  } else {
    tmpData->SetMaximum( plotter->axis_maximum );
  }

  //Draw data and legend
  legend->AddEntry( tmpData, "data", "ple" );
  tmpData->GetXaxis()->SetTitle( xAxisTitle );
  tmpData->GetYaxis()->SetTitle( yAxisTitle );
  tmpData->Draw( "X0 E1" );
  tmpDataStat->Draw( "SAME E1" );

  //Loop over the MC histograms. Apply style, add to legend and draw.
  for( unsigned int i=0; i<nHists; i++ ) {
    const MnvH1D *mnvMC = dynamic_cast<const MnvH1D*>( mcHistos->At(i) );
    if( !mnvMC ) {
      Error( "DrawDataMCVariations", "Could not cast one of the MC histograms to MnvH1D ! Your draw is incomplete." );
      continue;
    }

    std::cout << "Histo Title " << mnvMC->GetName() << " No. of bins " << mnvMC->GetNbinsX() << std::endl;

    TH1 *deHisto(0);
    deHisto = (TH1*)mnvMC->GetCVHistoWithError(true, covAreaNormalize).Clone( Form("tmp_MCHist_%d_%d", i, __LINE__) );
    //plotter->AddtoTmp( deHisto );

    if(i==0){
      plotter->ApplyNextLineStyle( deHisto, true, false );
    }
    else{
      plotter->ApplyNextLineStyle( deHisto, false, false );
    }
    deHisto->SetMarkerStyle(0);
    legend->AddEntry( deHisto, mnvMC->GetTitle(), "l" );
    deHisto->Scale( mcScale );
    deHisto->Draw("HIST C SAME");
    // deHisto->Reset();
  }

  if( legPos != "N" ) {
    legend->Draw();
  }

  gPad->Update();

}

void CCQENuPlotUtils::drawXSMultiDatasetComparisons(const MnvH1D* dataHisto, const TObjArray* varHistos, vector<string> radii, const Double_t mcScale,
							   const std::string& legPos, const bool covAreaNormalize, string xAxisLabel, string yAxisLabel) {
  unsigned int nHists = varHistos->GetEntries();
  vector<string> histoTitles;
  histoTitles.push_back( dataHisto->GetTitle() );
  const char* xAxisTitle = strlen(xAxisLabel.c_str())==0? dataHisto->GetXaxis()->GetTitle() : xAxisLabel.c_str();
  const char* yAxisTitle = strlen(yAxisLabel.c_str())==0? dataHisto->GetYaxis()->GetTitle() : yAxisLabel.c_str();
  //Be sure to consider a logY axis
  //Find the maximum amongst all histograms
  //TO-DO: For logY we really want to know the minimum non-zero value !!!

  //Kenyi: Need to discuss the importance of minYValue here.

  double maxYValue = dataHisto->GetMaximum();
  double minYValue = dataHisto->GetMinimum();

  if( gPad->GetLogy() && minYValue < 1.E-8 ) {
    minYValue = -1.0; //Why is Kenyi doing this ?
  }
  for( unsigned int i=0; i != nHists; ++i ) {
    MnvH1D* mcMnv = (MnvH1D*)varHistos->At(i);
    maxYValue = std::max( maxYValue, mcScale*mcMnv->GetMaximum() );
    if( 1.E-8 < mcMnv->GetMinimum() ) {
      minYValue = std::min( minYValue, mcScale*mcMnv->GetMinimum() );
    }
    histoTitles.push_back( mcMnv->GetTitle() );
  }
  if( gPad->GetLogy() ) {
    minYValue = std::max( minYValue, 1.E-8 );
  }

  //  size_t titleWidth = plotter->GetLegendWidthInLetters( histoTitles );

  TLegend *legend;
  legend = getLegend(0.6, 0.7);

  legend->SetNColumns( plotter->legend_n_columns );
  static int legB_n = 0;
  legend->SetName( Form("legend B - %d", legB_n++) );
  //  plotter->AddToTmp( legend );

  legend->SetBorderSize( plotter->legend_border_size );
  legend->SetFillColor( plotter->legend_fill_color );
  if( plotter->legend_fill_color < 0 ) {
    legend->SetFillStyle(0);
  }
  legend->SetTextSize( plotter->legend_text_size );
  legend->SetTextFont( plotter->legend_text_font );
    cout << "Starting MultiDataset Comparison: Get nom hist" << endl;
  //Make plots on the clone because it gets added to the legend ?
  //Kenyi: Why did he put a "?" and the above line is not clear to me
  TH1* tmpData(0);
  TH1* tmpDataStat(0);
  tmpData = (TH1*)dataHisto->GetCVHistoWithStatError().Clone( Form("tmpData_%d", __LINE__) );
  tmpDataStat = (TH1*)dataHisto->GetCVHistoWithStatError().Clone( Form("tmpDataStat_%d", __LINE__) );

  //  plotter->AddToTmp( tmpData );

  //Employ max/min settings as desired by user
  if( MnvHist::IsAutoAxisLimit( plotter->axis_minimum ) ) {
    if( plotter->hist_min_zero /*&&!gPad->GetLogy()*/ ) {
      tmpData->SetMinimum( 0.0 );
    } else {
      tmpData->SetMinimum( plotter->footroom*minYValue );
    }
  } else {
    tmpData->SetMinimum( plotter->axis_minimum );
  }

  if( MnvHist::IsAutoAxisLimit( plotter->axis_maximum ) ) {
    if( gPad->GetLogy() ) {
      tmpData->SetMaximum( pow( headroom*maxYValue, 10.0 ) );
    } else {
      tmpData->SetMaximum( headroom*maxYValue );
    }
  } else {
    tmpData->SetMaximum( plotter->axis_maximum );
  }

  //Draw data and legend
  legend->AddEntry( tmpData, Form("%s",radii[0].c_str()), "ple" );
  tmpData->GetXaxis()->SetTitle( xAxisTitle );
  tmpData->GetYaxis()->SetTitle( yAxisTitle );
  tmpData->Draw( "X0 E1" );
  tmpDataStat->Draw( "SAME E1" );
  cout << "Starting MultiDataset Comparison: loop over variation histograms" << endl;
  //Loop over the MC histograms. Apply style, add to legend and draw.
  for( unsigned int i=0; i<nHists; i++ ) {
    const MnvH1D *mnvMC = dynamic_cast<const MnvH1D*>( varHistos->At(i) );
    if( !mnvMC ) {
      Error( "DrawDataMCVariations", "Could not cast one of the MC histograms to MnvH1D ! Your draw is incomplete." );
      continue;
    }

    std::cout << "Histo Title " << mnvMC->GetName() << " No. of bins " << mnvMC->GetNbinsX() << std::endl;

    TH1 *deHisto(0);
    deHisto = (TH1*)mnvMC->GetCVHistoWithStatError().Clone( Form("tmp_MCHist_%d_%d", i, __LINE__) );
    //    plotter->AddtoTmp( deHisto );

    if(i==0){
      plotter->ApplyNextLineStyle( deHisto, true, false );
    }
    else{
      plotter->ApplyNextLineStyle( deHisto, false, false );
    }
    deHisto->SetMarkerStyle(0);
    legend->AddEntry( deHisto, Form("%s",radii[i+1].c_str()), "ple" );
    deHisto->Scale( mcScale );
    deHisto->Draw("HIST SAME");
    // deHisto->Reset();
  }

  if( legPos != "N" ) {
    legend->Draw();
  }

  gPad->Update();

}
void CCQENuPlotUtils::drawXSMultiDatasetComparisonsRatio(const MnvH1D* dataHisto, const TObjArray* varHistos, vector<string> radii, const Double_t mcScale,
							   const std::string& legPos, const bool covAreaNormalize, string xAxisLabel, string yAxisLabel) {
  unsigned int nHists = varHistos->GetEntries();
  vector<string> histoTitles;
  histoTitles.push_back( dataHisto->GetTitle() );
  const char* xAxisTitle = strlen(xAxisLabel.c_str())==0? dataHisto->GetXaxis()->GetTitle() : xAxisLabel.c_str();
  const char* yAxisTitle = strlen(yAxisLabel.c_str())==0? dataHisto->GetYaxis()->GetTitle() : yAxisLabel.c_str();
  //Be sure to consider a logY axis
  //Find the maximum amongst all histograms
  //TO-DO: For logY we really want to know the minimum non-zero value !!!

  //Kenyi: Need to discuss the importance of minYValue here.

  double maxYValue = 1.2;
  double minYValue = 0.8;

  if( gPad->GetLogy() && minYValue < 1.E-8 ) {
    minYValue = -1.0; //Why is Kenyi doing this ?
  }
  for( unsigned int i=0; i != nHists; ++i ) {
    MnvH1D* mcMnv = (MnvH1D*)varHistos->At(i);
    maxYValue = std::max( maxYValue, mcScale*mcMnv->GetMaximum() );
    if( 1.E-8 < mcMnv->GetMinimum() ) {
      minYValue = std::min( minYValue, mcScale*mcMnv->GetMinimum() );
    }
    histoTitles.push_back( mcMnv->GetTitle() );
  }
  if( gPad->GetLogy() ) {
    minYValue = std::max( minYValue, 1.E-8 );
  }

  //  size_t titleWidth = plotter->GetLegendWidthInLetters( histoTitles );

  TLegend *legend;
  legend = getLegend(0.6, 0.7);

  legend->SetNColumns( plotter->legend_n_columns );
  static int legB_n = 0;
  legend->SetName( Form("legend B - %d", legB_n++) );
  //  plotter->AddToTmp( legend );

  legend->SetBorderSize( plotter->legend_border_size );
  legend->SetFillColor( plotter->legend_fill_color );
  if( plotter->legend_fill_color < 0 ) {
    legend->SetFillStyle(0);
  }
  legend->SetTextSize( plotter->legend_text_size );
  legend->SetTextFont( plotter->legend_text_font );
    cout << "Starting MultiDataset Comparison: Get nom hist" << endl;
  //Make plots on the clone because it gets added to the legend ?
  //Kenyi: Why did he put a "?" and the above line is not clear to me
  TH1* tmpData(0);
  TH1* tmpDataStat(0);
  tmpData = (TH1*)dataHisto->GetCVHistoWithStatError().Clone( Form("tmpData_%d", __LINE__) );
  tmpDataStat = (TH1*)dataHisto->GetCVHistoWithStatError().Clone( Form("tmpDataStat_%d", __LINE__) );

  //  plotter->AddToTmp( tmpData );

  //Employ max/min settings as desired by user
  if( MnvHist::IsAutoAxisLimit( plotter->axis_minimum ) ) {
    if( plotter->hist_min_zero /*&&!gPad->GetLogy()*/ ) {
      tmpData->SetMinimum( 0.0 );
    } else {
      tmpData->SetMinimum( plotter->footroom*minYValue );
    }
  } else {
    tmpData->SetMinimum( plotter->axis_minimum );
  }

  if( MnvHist::IsAutoAxisLimit( plotter->axis_maximum ) ) {
    if( gPad->GetLogy() ) {
      tmpData->SetMaximum( pow( headroom*maxYValue, 10.0 ) );
    } else {
      tmpData->SetMaximum( headroom*maxYValue );
    }
  } else {
    tmpData->SetMaximum( plotter->axis_maximum );
  }
  //Draw data and legend
  legend->AddEntry( tmpData, Form("%s",radii[0].c_str()), "ple" );
  tmpData->GetXaxis()->SetTitle( xAxisTitle );
  tmpData->GetYaxis()->SetTitle( yAxisTitle );
  tmpData->Draw( "HX0 E1" );

  cout << "Starting MultiDataset Comparison: loop over variation histograms" << endl;
  //Loop over the MC histograms. Apply style, add to legend and draw.
  for( unsigned int i=0; i<nHists; i++ ) {
    const MnvH1D *mnvMC = dynamic_cast<const MnvH1D*>( varHistos->At(i) );
    if( !mnvMC ) {
      Error( "DrawDataMCVariations", "Could not cast one of the MC histograms to MnvH1D ! Your draw is incomplete." );
      continue;
    }

    std::cout << "Histo Title " << mnvMC->GetName() << " No. of bins " << mnvMC->GetNbinsX() << std::endl;

    TH1 *deHisto(0);
    deHisto = (TH1*)mnvMC->GetCVHistoWithStatError().Clone( Form("tmp_MCHist_%d_%d", i, __LINE__) );
    //    plotter->AddtoTmp( deHisto );
    deHisto->Divide(tmpData);
    if(i==0){
      plotter->ApplyNextLineStyle( deHisto, true, false );
    }
    else{
      plotter->ApplyNextLineStyle( deHisto, false, false );
    }
    deHisto->SetMarkerStyle(0);
    legend->AddEntry( deHisto, Form("%s",radii[i+1].c_str()), "ple" );
    deHisto->Scale( mcScale );
    deHisto->Draw("HIST SAME");
    // deHisto->Reset();
  }

  if( legPos != "N" ) {
    legend->Draw();
  }
  tmpData->Divide(tmpData);
  gPad->Update();

}


//draw 2D histograms broken down by bin
TCanvas* CCQENuPlotUtils::draw2DHistByBin( const MnvH2D* h, const std::string& legPos, bool doXProj){
  TCanvas *c1 = new TCanvas();
  c1->SetName(Form("c_%s_draw2D",h->GetName()));
  //This function assumes the input histogram has been correctly bin width normalized
  //Get number of bins
  int nbins_x = h->GetNbinsX();
  int nbins_y = h->GetNbinsY();
  //Divide Canvas into correct bins (this is where you can add the new plotutils GridCanvas stuff.
  int nbins = doXProj? nbins_y:nbins_x;
  string projDir = doXProj?"X":"Y";
  //  cout << "Plotting "<< h->GetName() << " with proj " << projDir  << " with " << nbins << " bins" << endl;
  int cells = ceil(sqrt(nbins));
  c1->Divide(cells, cells);
  //do projections
  for(int i=0;i<nbins;i++){
    MnvH1D *temp_h = doXProj ? h->ProjectionX(Form("h_proj_x_%s_bin_%d",h->GetName(),i+1),i+1,i+1) : h->ProjectionY(Form("h_proj_y_%s_bin_%d",h->GetName(),i+1),i+1,i+1);
    c1->cd(i+1);
    temp_h->Draw();
  }
  return c1;
}
//draw 2D histograms broken down by bin
TCanvas* CCQENuPlotUtils::draw2DHistsByBin( std::vector< MnvH2D* > h, const std::string& legPos, bool doXProj){
  TCanvas *c1 = new TCanvas();
  c1->SetName(Form("c_%s_draw2D",h[0]->GetName()));
  //This function assumes the input histogram has been correctly bin width normalized
  //Get number of bins
  int nbins_x = h[0]->GetNbinsX();
  int nbins_y = h[0]->GetNbinsY();
  //Divide Canvas into correct bins (this is where you can add the new plotutils GridCanvas stuff.
  int nbins = doXProj? nbins_y:nbins_x;
  string projDir = doXProj?"X":"Y";
  //  cout << "Plotting "<< h[0]->GetName() << " with proj " << projDir  << " with " << nbins << " bins" << endl;
  int cells = ceil(sqrt(nbins));
  c1->Divide(cells, cells);
  //do projections
  for(int i=0;i<nbins;i++){
    c1->cd(i+1);
    for(uint j=0;j<h.size();j++){
      MnvH1D *temp_h = doXProj ? h[j]->ProjectionX(Form("h_proj_x_%s_bin_%d",h[j]->GetName(),i+1),i+1,i+1) : h[j]->ProjectionY(Form("h_proj_y_%s_bin_%d",h[j]->GetName(),i+1),i+1,i+1);
      if(j==0) temp_h->Draw();
      else  temp_h->Draw("SAME");
    }
  }
  return c1;
}

//draw 2D histograms broken down by bin
TCanvas* CCQENuPlotUtils::draw2DHistsByBin( std::vector< TH2D* > h, const std::string& legPos, bool doXProj){
  TCanvas *c1 = new TCanvas();
  c1->SetName(Form("c_%s_draw2D",h[0]->GetName()));
  //This function assumes the input histogram has been correctly bin width normalized
  //Get number of bins
  int nbins_x = h[0]->GetNbinsX();
  int nbins_y = h[0]->GetNbinsY();
  //Divide Canvas into correct bins (this is where you can add the new plotutils GridCanvas stuff.
  int nbins = doXProj? nbins_y:nbins_x;
  string projDir = doXProj?"X":"Y";
  //  cout << "Plotting "<< h[0]->GetName() << " with proj " << projDir  << " with " << nbins << " bins" << endl;
  int cells = ceil(sqrt(nbins));
  c1->Divide(cells, cells);
  //do projections
  for(int i=0;i<nbins;i++){
    c1->cd(i+1);
    for(uint j=0;j<h.size();j++){
      TH1D *temp_h = doXProj ? h[j]->ProjectionX(Form("h_proj_x_%s_bin_%d",h[j]->GetName(),i+1),i+1,i+1) : h[j]->ProjectionY(Form("h_proj_y_%s_bin_%d",h[j]->GetName(),i+1),i+1,i+1);
      if(j==0) temp_h->Draw();
      else  temp_h->Draw("SAME");
    }
  }
  return c1;
}


TCanvas* CCQENuPlotUtils::draw2DHistByBinErrorSummary( const MnvH2D* h, const std::string& legPos, bool doXProj, double threshold, bool covAreaNormalize, bool asfrac){
  TCanvas *c1 = new TCanvas();
  c1->SetName(Form("c_%s_draw2DErrorSummary",h->GetName()));
  //This function assumes the input histogram has been correctly bin width normalized
  //Get number of bins
  int nbins_x = h->GetNbinsX();
  int nbins_y = h->GetNbinsY();
  //Divide Canvas into correct bins (this is where you can add the new plotutils GridCanvas stuff.
  int nbins = doXProj? nbins_y:nbins_x;
  string projDir = doXProj?"X":"Y";
  //  cout << "Plotting "<< h->GetName() << " with proj " << projDir  << " with " << nbins << " bins" << endl;
  //max 4 in a row
  int cells = ceil(sqrt(nbins));
  c1->Divide(cells, cells);
  //do projections
  for(int i=0;i<nbins;i++){
    MnvH1D *temp_h = doXProj ? h->ProjectionX(Form("h_proj_x_%s_bin_%d",h->GetName(),i+1),i+1,i+1) : h->ProjectionY(Form("h_proj_y_%s_bin_%d",h->GetName(),i+1),i+1,i+1);
    c1->cd(i+1);
    plotter->DrawErrorSummary(temp_h,legPos,true,true,threshold,covAreaNormalize,"",asfrac);
  }
  return c1;
}

/*
TCanvas* CCQENuPlotUtils::draw2DHistByBinErrorSummary( const MnvH2D* h, const std::string& legPos, bool doXProj, double threshold, bool covAreaNormalize, bool asfrac){

  //This function assumes the input histogram has been correctly bin width normalized
  //Get number of bins
  int nbins_x = h->GetNbinsX();
  int nbins_y = h->GetNbinsY();
  //Divide Canvas into correct bins (this is where you can add the new plotutils GridCanvas stuff.
  int nbins = doXProj? nbins_y:nbins_x;
  string projDir = doXProj?"X":"Y";
  //  cout << "Plotting "<< h->GetName() << " with proj " << projDir  << " with " << nbins << " bins" << endl;
  //max 4 in a row
  int cells = ceil(sqrt(nbins));
  GridCanvas* gc=new GridCanvas(Form("c_%s_draw2DErrorSummary",h->GetName()), cells, cells, 800, 500);
  gc->SetRightMargin(0.01);
  gc->SetLeftMargin(0.1);
  gc->ResetPads();
  //do projections
  for(int i=0;i<nbins;i++){
    MnvH1D *temp_h = doXProj ? h->ProjectionX(Form("h_proj_x_%s_bin_%d",h->GetName(),i+1),i+1,i+1) : h->ProjectionY(Form("h_proj_y_%s_bin_%d",h->GetName(),i+1),i+1,i+1);
    TPad* pad=(TPad*)gc->cd(i+1); // cd into the i'th subpad
    plotter->DrawErrorSummary(temp_h,legPos,true,true,threshold,covAreaNormalize,"",asfrac);
  }
  gc->SetXLimits(0, 0.59); // set the x range to be the same in all subpads
  gc->SetYLimits(0.01, 2.99); // set the y range in all the subpads
  gc->ResetPads(); // this makes changes propagate to the canvas

  TCanvas *c1 = new TCanvas();
  gc->Draw();
  return c1;
}
*/
TCanvas* CCQENuPlotUtils::draw2DHistByBinErrorCategory( const MnvH2D* h, const std::string& legPos, string category, bool doXProj, double threshold, bool covAreaNormalize, bool asfrac){
  TCanvas *c1 = new TCanvas();
  c1->SetName(Form("c_%s_draw2DErrorSummaryByCategory_%s",h->GetName(),category.c_str()));
  //This function assumes the input histogram has been correctly bin width normalized
  //Get number of bins
  int nbins_x = h->GetNbinsX();
  int nbins_y = h->GetNbinsY();
  //Divide Canvas into correct bins (this is where you can add the new plotutils GridCanvas stuff.
  int nbins = doXProj? nbins_y:nbins_x;
  string projDir = doXProj?"X":"Y";
  //  cout << "Plotting "<< h->GetName() << " with proj " << projDir  << " with " << nbins << " bins" << endl;
  int cells = ceil(sqrt(nbins));
  c1->Divide(cells, cells);
  //do projections
  for(int i=0;i<nbins;i++){
    MnvH1D *temp_h = doXProj ? h->ProjectionX(Form("h_proj_x_%s_bin_%d",h->GetName(),i+1),i+1,i+1) : h->ProjectionY(Form("h_proj_y_%s_bin_%d",h->GetName(),i+1),i+1,i+1);
    c1->cd(i+1);
    plotter->DrawErrorSummary(temp_h,legPos,true,true,threshold,covAreaNormalize,category,asfrac);
  }
  return c1;
}
TCanvas* CCQENuPlotUtils::draw2DHistDataMCRatio( const MnvH2D* h_data, const MnvH2D* h_mc){
  TCanvas *c1 = new TCanvas();
  c1->SetName(Form("c_%s_draw2DRatio",h_data->GetName()));
  MnvH2D* h_tmp = (MnvH2D*)h_data->Clone("tmp");
  h_tmp->Divide(h_data,h_mc);
  h_tmp->SetMaximum(0.75);
  h_tmp->SetMinimum(0);
  h_tmp->DrawClone("COLZ");

  return c1;
}


#endif
