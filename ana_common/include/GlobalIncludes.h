#ifndef MNV_GLOBALINCLUDES_h
#define MNV_GLOBALINCLUDES_h 1

//-----------------------------------------------------------
// Included files needed from ROOT and C++
//-----------------------------------------------------------
// C++ headers
#include<iomanip>
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<math.h>
#include<stdio.h>
#include<string>
#include<sstream>
#include<time.h>
#include<zlib.h>
#include<algorithm>
#include<map>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::flush;
using std::setw;
using std::streamsize;
using std::setprecision;
using std::string;
using std::stringstream;
using std::ifstream;
using std::ios;
using std::sort;
using std::map;
using std::pair;
using std::vector;

// ROOT headers
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "TApplication.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TFile.h"
#include "TMath.h"
#include "TChain.h"
#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TPostScript.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TAxis.h"
#include "TProfile.h"
#include "TVector3.h"
#include "TStyle.h"
#include "TText.h"
#include "TStyle.h"
#include "TRandom.h"
#include "TArrow.h"
#include "TLine.h"
#include "TMarker.h"
#include "TF1.h"
#include "TF2.h"
#include "TGraph.h"
#include "TSpline.h"
#include "TVector.h"
#include "TArray.h"
#include "TLegend.h"
#include "THStack.h"
#include "TChainElement.h"
#include "TCollection.h"
#include "TFractionFitter.h"
#include "TParameter.h" 
#endif

#include "Cintex/Cintex.h"

//-----------------------------------------------------------
// Global definitions 
//-----------------------------------------------------------

namespace CCQENU_ANA{
  static const unsigned int nHistos = 35;
  static const unsigned int nHistosPID = 5;
  static const bool RunCodeWithSystematics = true; // This variable will turn off and on systematics. This includes making all the lat/vert error bands. You CANNOT mix with/without processings

  /* Split MC in different templates and different ways
  * The different combinations are:
  *  kMC = kQE + kQENot
  *  kMC = kQELike + kQELikeNot
  *  kMC = kQE + kRES + kDIS + kOTH
  *  kMC = kQELike_QE + kQELike_RES + kQELike_OTH + kQELikeNot
  *  kMC = kQELike_QE + kQELike_RES + kQELike_OTH + kQELikeNot_PositivePions + kQELikeNot_NegativePions + kQELikeNot_NeutralPions + kQELikeNot_NoPions
  *  kMC = kQELike_QE + kQELike_RES + kQELike_OTH + kQELikeNot_PositivePions_TrueMichel + kQELikeNot_PositivePions_TrueMichelNot + kQELikeNot_NegativePions + kQELikeNot_NeutralPions + kQELikeNot_NoPions
  *  kMC = kQELike + kQELikeNot_PositivePions + kQELikeNot_NegativePions + kQELikeNot_NeutralPions + kQELikeNot_NoPions
  *  kMC = kQELike + kQELikeNot_PositivePions_TrueMichel + kQELikeNot_PositivePions_TrueMichelNot + kQELikeNot_NegativePions + kQELikeNot_NeutralPions + kQELikeNot_NoPions
  *  kMC = kQELike_QE + kQELike_QENot + kQELikeNot_QE + kQELikeNot_QENot
  *  kMC = kQELike + kQELikeNot_ChargedPions + kQELikeNot_NoChargedPions
  *  kMC = kQELike + kQELikeNot_ChargedPions_TrueMichel + kQELikeNot_NoChargedPions_TrueMichelNot + kQELikeNot_NoChargedPions
  */
  enum kHistos {
    kData,
    kMC,
    kQE,
    kQENot,
    kRES,
    kDIS,
    kOTH,
    kQENot_PositivePions,
    kQENot_PositivePions_TrueMichel,
    kQENot_PositivePions_TrueMichelNot,
    kQENot_NegativePions,
    kQENot_NeutralPions,
    kQENot_NoPions,
    kQELike_QE,
    kQELike_RES,
    kQELike_DIS,
    kQELike_OTH,
    kQELike,
    kQELikeNot,
    kQELikeNot_NoPions,
    kQELikeNot_PositivePions,
    kQELikeNot_PositivePions_TrueMichel,
    kQELikeNot_PositivePions_TrueMichelNot,
    kQELikeNot_NegativePions,
    kQELikeNot_NeutralPions,
    kQELikeNot_ChargedPions,
    kQELikeNot_ChargedPions_TrueMichel,
    kQELikeNot_ChargedPions_TrueMichelNot,
    kQELikeNot_ChargedPionsNot,
    kQELike_QENot,
    kQELikeNot_QE,
    kQELikeNot_QENot,
    kQELikeNot_SingleChargedPion,
    kQELikeNot_SingleNeutralPion,
    kQELikeNot_MultiPion
  };

  /* Split MC depending on the reconstructed 
  *primary proton track true PID information
  *  pMC = pProton + pPion + pOther
  */
  enum pHistos { //proton score histos
    pData,
    pMC,
    pProton,
    pPion,
    pOther
  };

  static string names[nHistos] = {
    "data",
    "mc",
    "qe",
    "qenot",
    "res",
    "dis",
    "oth",
    "qenot_positivepions",
    "qenot_positivepions_truemichel",
    "qenot_positivepions_truemichelnot",
    "qenot_negativepions",
    "qenot_neutralpions",
    "qenot_nopions",
    "qelike_qe",
    "qelike_res",
    "qelike_dis",
    "qelike_oth",
    "qelike",
    "qelikenot",
    "qelikenot_nopions",
    "qelikenot_positivepions",
    "qelikenot_positivepions_truemichel",
    "qelikenot_positivepions_truemichelnot",
    "qelikenot_negativepions",
    "qelikenot_neutralpions",
    "qelikenot_chargedpions",
    "qelikenot_chargedpions_truemichel",
    "qelikenot_chargedpions_truemichelnot",
    "qelikenot_chargedpionsnot",
    "qelike_qenot",
    "qelikenot_qe",
    "qelikenot_qenot",
    "qelikenot_singlechargedpion",
    "qelikenot_singleneutralpion",
    "qelikenot_multipion"

  };
  static string namesPID[nHistosPID] = {
    "data",
    "mc",
    "proton",
    "pion",
    "oth"
  };
}


namespace Playlist{ 
  const std::string minerva1 = "minerva1"; 
  const std::string minerva5 = "minerva5"; 
  const std::string minerva7 = "minerva7"; 
  const std::string minerva9 = "minerva9"; 
  const std::string minerva10 = "minerva10"; 
  const std::string minerva13A = "minerva13A"; 
  const std::string minerva13B = "minerva13B"; 
  const std::string minerva13C = "minerva13C"; 
  const std::string minerva13D = "minerva13D"; 
  const std::string minerva13E = "minerva13E"; 
  const std::string minerva13  = "minerva13"; 
  const std::string minervame1A  = "minervame1A"; 
  const std::string minervame1B  = "minervame1B"; 
  const std::string minervame1C  = "minervame1C"; 
  const std::string minervame1D  = "minervame1D"; 
  const std::string minervame1E  = "minervame1E"; 
  const std::string minervame1F  = "minervame1F"; 
  const std::string minervame1G  = "minervame1G"; 
  const std::string minervame1H  = "minervame1H"; 
  const std::string minervame1L  = "minervame1L"; 
  const std::string minervame1M  = "minervame1M"; 
  const std::string minervame1N  = "minervame1N"; 
  const std::string minervame1O  = "minervame1O"; 
  const std::string minervame1P  = "minervame1P"; 
  const std::string minervame5A  = "minervame5A"; 
  const std::string minervame6A  = "minervame6A"; 
  const std::string minervame6B  = "minervame6B"; 
 
  const std::string all_nu = "Nu"; 
  const std::string all_antinu = "AntiNu"; 
}

namespace Analysis{ 
  const std::string ccqe = "ccqe"; 
}

const std::string DEFAULT_PLAYLIST = Playlist::all_nu; 


#endif
