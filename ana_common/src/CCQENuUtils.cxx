#ifndef MNV_CCQENUUTILS_cxx
#define MNV_CCQENUUTILS_cxx 1


#include "include/CCQENuUtils.h"
#include "include/playlists/playlist_minerva.h"
#include "PlotUtils/MnvHadronReweight.h" 
#include "PlotUtils/FluxReweighter.h"
#include "PlotUtils/MinosMuonEfficiencyCorrection.h"

using namespace CCQENU_ANA; 

//--Default constructor
CCQENuUtils::CCQENuUtils()
{
  GlobalParameters::Get().m_useFluxConstraint = false; 
  GlobalParameters::Get().m_usePPFX1Flux = false; 
  cout << "Not using the nu_e flux constraint" << endl; 
  use_merged_files = false;
  GlobalParameters::Get().m_neutrinoMode = true; 
  incoming_pdg = 14;
  cout << "Initializing CCQENuUtils in Neutrino mode" << endl; 
  loaded_pot_mc = false;
  loaded_pot_data = false;
  myPlaylist = new std::string (Playlist::minervame1A);
  myAnalysis = new std::string (Analysis::ccqe);
  myProcessing = new std::string ("Inextinguishable");
  mnvNormalizer = new MnvNormalizer(*myProcessing, *myPlaylist);
  recoShifter = new MnvRecoShifter( false, m_nUniverses );
  use_norm_wgt = true;
  use_genie_split = true;
  cutter = new CCQENuCuts();
  wgt_CV = 1.0;
  wgt_CV_truth = 1.0;
  vert_error_band_wgts = NULL;
  lat_error_band_wgts = NULL; 
  doGenieTuning = getenv("DOPIONTUNE")!=NULL? true:false; // This just means you do it, go look at .cxx for which of the parameters below are used!!
  doRPA = getenv("DOCCQEPRA")!=NULL? true:false;
  do2p2h = getenv("DO2P2HTUNE")!=NULL? true:false;
  doRPA_Nieves_Resonant = getenv("DORPARESNIEVES")!=NULL? true:false;
  doRPA_MINOS_Resonant = getenv("DORPARESMINOS")!=NULL? true:false;

  cout << "My configuration for tunes is (pion,rpa,2p2h,resnieves,resminos)\tNonresPion=" << doGenieTuning << "\tCCQERPA=" << doRPA << "\t2p2hTune=" << do2p2h << "\tResRPANieves" << doRPA_Nieves_Resonant << "\tdoRPA_MINOS_Resonant" << doRPA_MINOS_Resonant << endl;
  frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minervame1A,FluxReweighter::gen2thin, FluxReweighter::g4numiv6);//new new variables for flux type (gen2thin) and g4numiv

  char *mparalocation = std::getenv("MPARAMFILESROOT");
  string directory_data = string(mparalocation)+"/data/Reweight/";
  weight_cv_2p2h= new weight_2p2h(directory_data+"/fit-mec-2d-noScaleDown-penalty00300-best-fit");
  weight_np_2p2h = new weight_2p2h(directory_data+"/fit-mec-2d-np-only-noScaleDown-penalty02000-best-fit");
  weight_nn_2p2h = new weight_2p2h(directory_data+"/fit-mec-2d-nn-only-noScaleDown-penalty00300-best-fit");
  weight_qe_2p2h = new weight_2p2h(directory_data+"/fit-qe-gaussian-noScaleDown-penalty02000-best-fit");
  weight_cv_and_var_RPA = new weightRPA(directory_data+"/outNievesRPAratio-nu12C-20GeV-20170202.root");

  //--------------------------------------------------------------
  // Initializing the reco efficiency normalization weights  
  // actual values filled inside updatePlaylistNorm() 
  //--------------------------------------------------------------
  c_normWgt_low = 1.0, c_normWgt_high = 1.0;
  c_normWgtErr_low = 1.0, c_normWgtErr_high = 1.0;

  //Target Mass uncertainty 
  target_mass_weights.push_back(0.986); //Uncertainty is 1.4% hence 1-0.014
  target_mass_weights.push_back(1.014); //Uncertainty is 1.4% hence 1+0.014  

  //---------------------------------------------------------------
  // Michel weights extracted for minerva1: 0.986196 & 1.0138 
  // Michel weights extracted for minerva13C: 0.986608 & 1.01339 
  // Use neutrino weights for general constructor
  // Vector declared in header file
  //---------------------------------------------------------------
  michel_weights.push_back(0.986);
  michel_weights.push_back(1.013);

  // HadronReweight
  mnvHadronReweight = new MnvHadronReweight(); 
}

CCQENuUtils::CCQENuUtils( bool neutrinoMode, bool use_mergedFiles )
{
  GlobalParameters::Get().m_useFluxConstraint = false; 
  GlobalParameters::Get().m_usePPFX1Flux = false; 
  cout << "Not using the nu_e flux constraint" << endl; 
  use_merged_files = use_mergedFiles;
  GlobalParameters::Get().m_neutrinoMode = neutrinoMode; 
  if( GlobalParameters::Get().m_neutrinoMode ) { 
    incoming_pdg = 14;
    cout << "Initializing CCQENuUtils in Neutrino mode" << endl; 
  } else { 
    incoming_pdg = -14;
    cout << "Initializing CCQENuUtils in Antineutrino mode" << endl; 
  }

  loaded_pot_mc = false;
  loaded_pot_data = false;
  myPlaylist = new std::string (Playlist::minervame1A);
  myAnalysis = new std::string (Analysis::ccqe);
  myProcessing = new std::string ("Inextinguishable");
  mnvNormalizer = new MnvNormalizer(*myProcessing, *myPlaylist);
  recoShifter = new MnvRecoShifter( false, m_nUniverses );
  use_norm_wgt = true;
  use_genie_split = true;
  cutter = new CCQENuCuts();
  wgt_CV = 1.0;
  wgt_CV_truth = 1.0;
  vert_error_band_wgts = NULL;
  lat_error_band_wgts = NULL; 
  doGenieTuning = getenv("DOPIONTUNE")!=NULL?true:false; // This just means you do it, go look at .cxx for which of the parameters below are used!!
  doRPA = getenv("DOCCQEPRA")!=NULL?true:false;
  do2p2h = getenv("DO2P2HTUNE")!=NULL?true:false;
  doRPA_Nieves_Resonant = getenv("DORPARESNIEVES")!=NULL?true:false;
  doRPA_MINOS_Resonant = getenv("DORPARESMINOS")!=NULL?true:false;

  cout << "My configuration for tunes is (pion,rpa,2p2h,resnieves,resminos)\tNonresPion=" << doGenieTuning << "\tCCQERPA=" << doRPA << "\t2p2hTune=" << do2p2h << "\tResRPANieves" << doRPA_Nieves_Resonant << "\tdoRPA_MINOS_Resonant" << doRPA_MINOS_Resonant << endl;
  frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minervame1A,FluxReweighter::gen2thin, FluxReweighter::g4numiv6);//new new variables for flux type (gen2thin) and g4numiv

  char *mparalocation = std::getenv("MPARAMFILESROOT");
  string directory_data = string(mparalocation)+"/data/Reweight/";
  weight_cv_2p2h= new weight_2p2h(directory_data+"/fit-mec-2d-noScaleDown-penalty00300-best-fit");
  weight_np_2p2h = new weight_2p2h(directory_data+"/fit-mec-2d-np-only-noScaleDown-penalty02000-best-fit");
  weight_nn_2p2h = new weight_2p2h(directory_data+"/fit-mec-2d-nn-only-noScaleDown-penalty00300-best-fit");
  weight_qe_2p2h = new weight_2p2h(directory_data+"/fit-qe-gaussian-noScaleDown-penalty02000-best-fit");
  weight_cv_and_var_RPA = new weightRPA(directory_data+"/outNievesRPAratio-nu12C-20GeV-20170202.root");
  //--------------------------------------------------------------
  // Initializing the reco efficiency normalization weights  
  // actual values filled inside updatePlaylistNorm() 
  //--------------------------------------------------------------
  c_normWgt_low = 1.0, c_normWgt_high = 1.0; 
  c_normWgtErr_low = 0.0, c_normWgtErr_high = 0.0; 
  
  //Target Mass uncertainty 
  target_mass_weights.push_back(0.986); //Uncertainty is 1.4% hence 1-0.014
  target_mass_weights.push_back(1.014); //Uncertainty is 1.4% hence 1+0.014  
  
  //------------------------------------------------------------------
  // Michel weights extracted for minerva1: 0.986196 & 1.0138 
  // Michel weights extracted for minerva13C: 0.986608 & 1.01339 
  //------------------------------------------------------------------
  if( neutrinoMode ){
    //Use neutrino weights for general constructor
    //Vector declared in header file
    michel_weights.push_back(0.986);
    michel_weights.push_back(1.013);
  } else{
    //For antineutrino, set weights to 0. at present 
    michel_weights.push_back(1.0);
    michel_weights.push_back(1.0);
  }
  
  // HadronReweight
  mnvHadronReweight = new MnvHadronReweight(); 
}

CCQENuUtils::CCQENuUtils( bool neutrinoMode, bool use_mergedFiles, bool useFluxConstraint )  
{ 
  GlobalParameters::Get().m_useFluxConstraint = useFluxConstraint; 
  GlobalParameters::Get().m_usePPFX1Flux = false; 
  use_merged_files = use_mergedFiles; 
  GlobalParameters::Get().m_neutrinoMode = neutrinoMode; 
  if( GlobalParameters::Get().m_neutrinoMode ) { 
    incoming_pdg = 14;
     cout << "Initializing CCQENuUtils in Neutrino mode" << endl; 
   } else { 
     incoming_pdg = -14;
     cout << "Initializing CCQENuUtils in Antineutrino mode" << endl; 
   }

   loaded_pot_mc = false;
   loaded_pot_data = false;
   myPlaylist = new std::string (Playlist::minervame1A);
   myAnalysis = new std::string (Analysis::ccqe);
   myProcessing = new std::string ("Inextinguishable");
   mnvNormalizer = new MnvNormalizer(*myProcessing, *myPlaylist);
   recoShifter = new MnvRecoShifter( false, m_nUniverses );
   use_norm_wgt = true;
   use_genie_split = true;
   cutter = new CCQENuCuts();
   wgt_CV = 1.0;
   wgt_CV_truth = 1.0;
   vert_error_band_wgts = NULL;
   lat_error_band_wgts = NULL; 
   doGenieTuning = getenv("DOPIONTUNE")!=NULL?true:false; // This just means you do it, go look at .cxx for which of the parameters below are used!!
   doRPA = getenv("DOCCQEPRA")!=NULL?true:false;
   do2p2h = getenv("DO2P2HTUNE")!=NULL?true:false;
   doRPA_Nieves_Resonant = getenv("DORPARESNIEVES")!=NULL?true:false;
   doRPA_MINOS_Resonant = getenv("DORPARESMINOS")!=NULL?true:false;

  cout << "My configuration for tunes is (pion,rpa,2p2h,resnieves,resminos)\tNonresPion=" << doGenieTuning << "\tCCQERPA=" << doRPA << "\t2p2hTune=" << do2p2h << "\tResRPANieves" << doRPA_Nieves_Resonant << "\tdoRPA_MINOS_Resonant" << doRPA_MINOS_Resonant << endl;
   frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minervame1A,FluxReweighter::gen2thin, FluxReweighter::g4numiv6);//new new variables for flux type (gen2thin) and g4numiv
 
  char *mparalocation = std::getenv("MPARAMFILESROOT");
  string directory_data = string(mparalocation)+"/data/Reweight/";

  weight_cv_2p2h= new weight_2p2h(directory_data+"/fit-mec-2d-noScaleDown-penalty00300-best-fit");
  weight_np_2p2h = new weight_2p2h(directory_data+"/fit-mec-2d-np-only-noScaleDown-penalty02000-best-fit");
  weight_nn_2p2h = new weight_2p2h(directory_data+"/fit-mec-2d-nn-only-noScaleDown-penalty00300-best-fit");
  weight_qe_2p2h = new weight_2p2h(directory_data+"/fit-qe-gaussian-noScaleDown-penalty02000-best-fit");

  weight_cv_and_var_RPA = new weightRPA(directory_data+"/outNievesRPAratio-nu12C-20GeV-20170202.root");

   //--------------------------------------------------------------
   // Initializing the reco efficiency normalization weights  
   // actual values filled inside updatePlaylistNorm() 
   //--------------------------------------------------------------
   c_normWgt_low = 1.0, c_normWgt_high = 1.0; 
   // ... and the errors on the weights 
   c_normWgtErr_low = 0.0, c_normWgtErr_high = 0.0; 

   //Target Mass uncertainty 
   target_mass_weights.push_back(0.986); //Uncertainty is 1.4% hence 1-0.014
   target_mass_weights.push_back(1.014); //Uncertainty is 1.4% hence 1+0.014  

   //-------------------------------------------------------------------
   // Michel weights extracted for minerva1: 0.986196 & 1.0138 
   // Michel weights extracted for minerva13C: 0.986608 & 1.01339 
   //-------------------------------------------------------------------
   if( neutrinoMode ){
     //Use neutrino weights for general constructor
     //Vector declared in header file
     michel_weights.push_back(0.986);
     michel_weights.push_back(1.013);
   } else{
     //For antineutrino, set weights to 0. at present 
     michel_weights.push_back(1.0);
     michel_weights.push_back(1.0);
   }

   // HadronReweight
   mnvHadronReweight = new MnvHadronReweight(); 
 }

 //--Destructor
 CCQENuUtils::~CCQENuUtils()
 {
   if( mnvNormalizer) delete mnvNormalizer;
   if( cutter ) delete cutter;
   if( recoShifter ) delete recoShifter;
   if( myPlaylist ) delete myPlaylist; 
   // HadronReweight
   if( mnvHadronReweight ) delete mnvHadronReweight;
 }

 CCQENuUtils& CCQENuUtils::Get(){
   static CCQENuUtils singleton;
   return singleton;
 }

 //=========================================================
 // Build a Tree of DATA entries from the available file bank
 // If "partial_sample" is true, then load the Tree with only 
 // events from the selected partial list of files
 //=========================================================
 TChain* CCQENuUtils::getDataTree( string name, int files_to_read, int first_file ){

   TChain* chain = new TChain( "chain" );
   TChain* tree  = new TChain( name.c_str() );

   if(use_merged_files) get_data_files_merged( chain ) ;
   else{
     get_data_files( chain, *myPlaylist );
     cout << "Getting files from " << *myPlaylist << endl;
   }

   //Disable MC Truth variables in Data
   chain->SetBranchStatus("mc_*",kFALSE);
   chain->SetBranchStatus("truth_*",kFALSE);

   int nfiles = 0;

   if( files_to_read > 0 ) {
     TObjArray *fileElements=chain->GetListOfFiles();
     TIter next(fileElements);
     TChainElement *chEl=0;
     int count = 1;
     while (( chEl=(TChainElement*)next() ) && count <= first_file + files_to_read ) {
       if( count >= first_file ) {
	 tree->Add(chEl->GetTitle());
	 nfiles++;
       }
       count++;
     }
   }
   else {
     TObjArray *fileElements=chain->GetListOfFiles();
     TIter next(fileElements);
     TChainElement *chEl=0;
     while (( chEl=(TChainElement*)next() )) {
       tree->Add(chEl->GetTitle());
       nfiles++;
     }
   }

   cout << "Loaded " << nfiles << " DATA files from TTree : " << name << endl;

   if( name != "Meta" && !loaded_pot_data ){
     cout<<"Trying to find DATA POT"<<endl;
     TChain *meta = getDataTree( "Meta", files_to_read, first_file );
     setPOTData( meta );
     delete meta;
   }

   delete chain;

   return tree;
 }

 //=========================================================
 // Build a TChain of MC files
 // @name = 
 //=========================================================
 TChain* CCQENuUtils::getMCTree( string name, int files_to_read )
 {
   TChain* chain  = new TChain( "chain" );
   TChain* tree   = new TChain( name.c_str() );

   //HadronReweight
   //   const char* cache_filename = Form("%s/ana_common/data/", getenv("CCQENUROOT") );

   //HadronReweight 2.0
   //std::string projectname = "HadronReweight-tracker-";
   std::string myplaylist = *myPlaylist;
   //   projectname += myplaylist;
   //const char* project_name = projectname.c_str(); 

   mnvHadronReweight->useDefaultParticles();
   mnvHadronReweight->setBasicFiducial();

   if( name=="Truth" )
   {
     if(use_merged_files) get_truth_files_merged( chain ) ;
     else{
       get_truth_files( chain, *myPlaylist );
       cout << "Getting TRUTH files from " << *myPlaylist << endl;
     }
   }
   else if( name=="CCQENu" || name=="Meta")
   {
     if(use_merged_files) get_mc_files_merged( chain ) ;
     else{
       get_mc_files( chain, *myPlaylist );
       cout << "Getting MC files from " << *myPlaylist << endl;
     }
     
     // // HadronReweight
     // if( name=="CCQENu" && !mnvHadronReweight->tryLoadingFromFile(cache_filename,project_name) ) {
     //    getMCTree("Truth", files_to_read);
     // 	TChain* truth = getMCTree("Truth", files_to_read);
     // 	mnvHadronReweight->getRenormFactors(cache_filename, truth);
     // 	delete truth;
     // }
     
   }
   else
   {
     Error("CCQENuUtils::getMCTree",Form("Did not find TTree with name: %s",name.c_str()));
   }

   int nfiles = 0;
   if( files_to_read > 0 ) {
     TObjArray *fileElements=chain->GetListOfFiles();
     TIter next(fileElements);
     TChainElement *chEl=0;
     int count = 1;
     while (( chEl=(TChainElement*)next() ) && count <= files_to_read ) {
       if( count >= 1 ) {
	 tree->Add(chEl->GetTitle());
	 nfiles++;
       }
       count++;
     }
   }
   else {
     TObjArray *fileElements=chain->GetListOfFiles();
     TIter next(fileElements);
     TChainElement *chEl=0;
     while (( chEl=(TChainElement*)next() )) {
       tree->Add(chEl->GetTitle());
       nfiles++;
     }
   }

   cout << "Loaded " << nfiles << " MC files from TTree : " << name << endl;
   // HadronReweight
   if (name == "Truth"){
     //     mnvHadronReweight->setTruthTree(tree);
     //if (!mnvHadronReweight->tryLoadingFromFile(cache_filename,project_name)) {
       //       mnvHadronReweight->setTruthTree(tree);
     //mnvHadronReweight->getRenormFactors(cache_filename, project_name);
     //}
     cout << "skip" << endl;
   }
   else if (name == "CCQENu"){
     //mnvHadronReweight->setDataTree(tree);
     cout << "skip" << endl;
   }
   if( name != "Meta" && !loaded_pot_mc ){
     cout<<"Trying to find MC POT"<<endl;
     TChain *meta = getMCTree( "Meta", files_to_read );
     setPOTMC( meta );
     delete meta;
   }

   delete chain;
   return tree;
 }

void CCQENuUtils::setmnvHadronReweightTruthTree(TChain *tree){
  mnvHadronReweight->setTruthTree(tree);
}

void CCQENuUtils::setmnvHadronReweightDataTree(TChain *tree){
  mnvHadronReweight->setDataTree(tree);
  const char* cache_filename = Form("%s/ana_common/data/", getenv("CCQENUROOT") );
  std::string projectname = "HadronReweight-tracker-";
  std::string myplaylist = *myPlaylist;
  projectname += myplaylist;
  const char* project_name = projectname.c_str(); 
  if(!mnvHadronReweight->tryLoadingFromFile(cache_filename,project_name) ){
    cout << "IN HERE" << endl;
    mnvHadronReweight->getRenormFactors(cache_filename,project_name, tree);
    cout << "Got norm" << endl;
  }
}


 double CCQENuUtils::getPOTData(){

   if( loaded_pot_data ) return global_pot_data;
   else{
     cout << "You have not loaded a Data Tree!  use getMCTree()" << endl;
     return 0;
   }
 }

 void CCQENuUtils::setPOTData( TChain *data ){

   Int_t Ndata  = data->GetEntries();
   TObjArray* files = data->GetListOfFiles();
   int subruns = 0;

   TIter next(files);
   TChainElement* file = 0;
/*
   while( (file=(TChainElement*)next()) ) {

     string name = string(file->GetTitle()).substr( string(file->GetTitle()).find("MV") );
     if( (int)name.find("Subruns") == -1 ) continue;

     //name = name.erase( name.find("_CCQENu") );
     //name = name.substr( name.find("Subruns") + string("Subruns_").length() );

     std::vector< string > subs = split_line(name,"-");

     subruns += (int)subs.size();
     subs.clear();
   }*/
   cout<< "Number of subruns in DATA file list = "<< subruns << endl;

   //-------------------------------------------------
   // For data, loop over the AnaDST files and sum
   // the POT_Used variable in the Meta Tree
   // There is one entry in this tree per file which
   // is written during the finalize routine of AnaDST
   //-------------------------------------------------
   double pot_data = 0; 
   double total_pot_data = 0;
   TBranch *b_pot_data; 
   data->SetBranchAddress( "POT_Used", &pot_data, &b_pot_data );
   for( Int_t i=0; i<Ndata; i++ ){
     data->GetEntry(i);
     total_pot_data += pot_data; 
     //cout << "DATA File " << i <<" : POT in this file: " << pot_data << ", Total: " << total_pot_data << endl;
   }
   loaded_pot_data = true;
   global_pot_data = total_pot_data;
   cout << "DATA POT = " << total_pot_data << endl;
 }

 double CCQENuUtils::getPOTMC( bool single_nu_mc ){

   if( loaded_pot_mc ) return global_used_pot_mc;
   else{
     cout << "You have not loaded a MC Tree!  use getMCTree()" << endl;
     return 0;
   }
 }

 double CCQENuUtils::GetPOTWeight(){

   if( loaded_pot_mc ){

     return global_used_pot_mc/global_total_pot_mc;
   }
   else{
     cout << "You have not loaded a MC Tree!  use getMCTree()" << endl;
     return 0;
   }
 }

 std::vector< std::string > CCQENuUtils::split_line( std::string line, const char* split_var )
 {
     std::vector< std::string > col;
     std::string str = "";

     for(unsigned int i = 0; i < line.size(); i++) {
       std::string s(1,line[i]);
       if( s.find(split_var) != std::string::npos ) { col.push_back( str ); str.clear(); }
       else {
	 str += s;
	 if( i == line.size()-1 ) col.push_back( str );
       }
     }

     return col;
 }

 void CCQENuUtils::setPOTMC( TChain *mc ){

   Int_t Nmc  = mc->GetEntries();
   TObjArray* files = mc->GetListOfFiles();
   int subruns = 0;

   TIter next(files);
   TChainElement* file = 0;
/*
   while( (file=(TChainElement*)next()) ) {

     string name = string(file->GetTitle()).substr( string(file->GetTitle()).find("SIM") );
     if( (int)name.find("Subruns") == -1 ) continue;

     //name = name.erase( name.find("_CCQENu") );
     //name = name.substr( name.find("Subruns") + string("Subruns_").length() );

     std::vector< string > subs = split_line(name,"-");

     subruns += (int)subs.size();
     subs.clear();
   }*/
   cout<< "Number of subruns in MC file list = "<< subruns << endl;

   //----------------------------------------------------------------------------------------
   // Pre-EROICA we count POT by: No. of subruns * POT per MC file 
   // EROICA onwards we count POT by: sum over the spills in the simulation POT per file  
   // (EROICA has overlay, handles spill-by-spill intensity correctly) 
   //----------------------------------------------------------------------------------------

   double used_pot_mc = 0;
   double total_pot_mc = 0;

   double final_used_pot_mc = 0;
   double final_total_pot_mc = 0;

   TBranch *b_used_pot_mc;
   TBranch *b_total_pot_mc;

   mc->SetBranchAddress( "POT_Used", &used_pot_mc, &b_used_pot_mc );
   mc->SetBranchAddress( "POT_Total", &total_pot_mc, &b_total_pot_mc );
   for( Int_t i=0; i<Nmc; i++ ){
     mc->GetEntry(i);
     final_total_pot_mc += total_pot_mc;
     final_used_pot_mc += used_pot_mc;
     cout << "MC File " << i  << "\t" << mc->GetFile()->GetName()<< " : POT in this file: "<< " Total: " << total_pot_mc << ", Used: " << used_pot_mc << endl;
   }
   loaded_pot_mc = true;
   global_total_pot_mc = final_total_pot_mc;
   global_used_pot_mc = final_used_pot_mc;
   cout << "MC (Used) POT = " << global_used_pot_mc << endl;
   cout << "MC (Total) POT = " << global_total_pot_mc << endl;
 }

void CCQENuUtils::getPOT( double& total_pot_data, double& total_pot_mc, bool single_nu_mc ){
  
  total_pot_data = getPOTData();
  total_pot_mc   = getPOTMC( single_nu_mc );
  
  cout << "DATA pot = " << total_pot_data << endl;
  cout << "MC pot   = " << total_pot_mc << endl;
  
}

void CCQENuUtils::writePOT( TFile *f ){
  
  double data = getPOTData();
  double mc   = getPOTMC();
  
  TVector2 *pot = new TVector2( data, mc );
   f->WriteTObject( pot, "pot" );
   
 }

void CCQENuUtils::setPlaylist(string playlist){
   *myPlaylist = playlist;
 }

void CCQENuUtils::setFluxReweighterPlaylist(){
  if(GlobalParameters::Get().m_useFluxConstraint) cout << "Using flux constraint" << endl;
  else cout << "NOT using flux constraint" << endl;
  string myplaylist = *myPlaylist;
  if(myplaylist.find("me")!=string::npos){//I found a medium energy list
    if(myplaylist.find("1A")==string::npos){
      frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minervame1A,FluxReweighter::gen2thin, FluxReweighter::g4numiv6);//new new variables for flux type (gen2thin) and g4numiv
    }
    else if(myplaylist.find("1B")==string::npos){
      frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minervame1B,FluxReweighter::gen2thin, FluxReweighter::g4numiv6);//new new variables for flux type (gen2thin) and g4numiv
    }
    else if(myplaylist.find("1C")==string::npos){
      frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minervame1C,FluxReweighter::gen2thin, FluxReweighter::g4numiv6);//new new variables for flux type (gen2thin) and g4numiv
    }
    else if(myplaylist.find("1D")==string::npos){
      frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minervame1D,FluxReweighter::gen2thin, FluxReweighter::g4numiv6);//new new variables for flux type (gen2thin) and g4numiv
    }
    else if(myplaylist.find("1E")==string::npos){
      frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minervame1E,FluxReweighter::gen2thin, FluxReweighter::g4numiv6);//new new variables for flux type (gen2thin) and g4numiv
    }
    else if(myplaylist.find("1F")==string::npos){
      frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minervame1F,FluxReweighter::gen2thin, FluxReweighter::g4numiv6);//new new variables for flux type (gen2thin) and g4numiv
    }
    else if(myplaylist.find("1G")==string::npos){
      frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minervame1G,FluxReweighter::gen2thin, FluxReweighter::g4numiv6);//new new variables for flux type (gen2thin) and g4numiv
    }
    else if(myplaylist.find("1L")==string::npos){
      frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minervame1L,FluxReweighter::gen2thin, FluxReweighter::g4numiv6);//new new variables for flux type (gen2thin) and g4numiv
    }
    else if(myplaylist.find("1M")==string::npos){
      frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minervame1M,FluxReweighter::gen2thin, FluxReweighter::g4numiv6);//new new variables for flux type (gen2thin) and g4numiv
    }
    else if(myplaylist.find("1N")==string::npos){
      frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minervame1N,FluxReweighter::gen2thin, FluxReweighter::g4numiv6);//new new variables for flux type (gen2thin) and g4numiv
    }
    else if(myplaylist.find("1O")==string::npos){
      frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minervame1O,FluxReweighter::gen2thin, FluxReweighter::g4numiv6);//new new variables for flux type (gen2thin) and g4numiv
    }
    else if(myplaylist.find("1P")==string::npos){
      frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minervame1P,FluxReweighter::gen2thin, FluxReweighter::g4numiv6);//new new variables for flux type (gen2thin) and g4numiv
    }
    else cout << "Playlist not found" << endl;
  }
  else{//
    if(myplaylist.find("13")!=string::npos){//use 13
      frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minerva13,FluxReweighter::gen2thin, FluxReweighter::g4numiv5);//new new variables for flux type (gen2thin) and g4numiv
    }
    else if (myplaylist.find("7")!=string::npos){//use 1
      frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minerva13,FluxReweighter::gen2thin, FluxReweighter::g4numiv5);//new new variables for flux type (gen2thin) and g4numiv
    }
    else if (myplaylist.find("9")!=string::npos){//use 1
      frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minerva13,FluxReweighter::gen2thin, FluxReweighter::g4numiv5);//new new variables for flux type (gen2thin) and g4numiv
    }
    else if (myplaylist.find("1")!=string::npos){//use 1
      frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minerva13,FluxReweighter::gen2thin, FluxReweighter::g4numiv5);//new new variables for flux type (gen2thin) and g4numiv
    }
    else{//default to minerva13
      cout << "This is an LE processing? Playlist not recognized. Defaulting to minerva13" << endl;
      frw = new FluxReweighter(incoming_pdg,GlobalParameters::Get().m_useFluxConstraint,FluxReweighter::minerva13,FluxReweighter::gen2thin, FluxReweighter::g4numiv5);//new new variables for flux type (gen2thin) and g4numiv
    }
  }
}

MnvH1D* CCQENuUtils::getReweightedFluxHist(){
  return frw->GetFluxReweighted(incoming_pdg);
}
MnvH1D* CCQENuUtils::getUnweightedFluxHist(){
  return frw->GetFluxGenerated(incoming_pdg);
}


 //============================================================================
 // BookHistos
 //===========================================================================
 void CCQENuUtils::bookHistos( MnvH1D** h, string var_name, string title, int nbins, double min, double max ){

   for( unsigned int i = 0; i < nHistos; ++i )
     h[i] = new MnvH1D( ( var_name + '_' + names[i] ). c_str(),title.c_str(),
			  nbins, min, max );

 }

 void CCQENuUtils::bookHistos( MnvH1D** h, string var_name, string title, axis_binning xbins ){

   for( unsigned int i = 0; i < nHistos; ++i )
     h[i] = new  MnvH1D( ( var_name + '_' + names[i] ).c_str(), title.c_str(),
			   xbins.nbins, &( xbins.bin_edges[0] ), xbins.default_width );

 }
 void CCQENuUtils::bookHistosByPID( MnvH1D** h, string var_name, string title, int nbins, double min, double max ){

   for( unsigned int i = 0; i < nHistosPID; ++i )
     h[i] = new MnvH1D( ( var_name + '_' + namesPID[i] ). c_str(),title.c_str(),
			  nbins, min, max );

 }

 void CCQENuUtils::bookHistosByPID( MnvH1D** h, string var_name, string title, axis_binning xbins ){

   for( unsigned int i = 0; i < nHistosPID; ++i )
     h[i] = new  MnvH1D( ( var_name + '_' + namesPID[i] ).c_str(), title.c_str(),
			   xbins.nbins, &( xbins.bin_edges[0] ), xbins.default_width );

 }

 void CCQENuUtils::bookHistos( MnvH2D** h, string var_name, string title, int xnbins, double xmin, double xmax, int ynbins, double ymin, double ymax ){

   for( unsigned int i = 0; i < nHistos; ++i )
     h[i] = new MnvH2D( ( var_name + '_' + names[i] ). c_str(),title.c_str(),
			  xnbins, xmin, xmax, ynbins, ymin, ymax );

 }

 void CCQENuUtils::bookHistosByPID( MnvH2D** h,string var_name,string title,axis_binning xbins, axis_binning ybins ){
   Double_t xbinsarray[xbins.nbins];
   for( unsigned int i = 0; i <= xbins.nbins; i++ )
     xbinsarray[i] = xbins.bin_edges[i];
   Double_t ybinsarray[ybins.nbins];
   for( unsigned int i = 0; i <= ybins.nbins; i++ )
     ybinsarray[i] = ybins.bin_edges[i];

   for( unsigned int i = 0; i < nHistosPID; i++ )
     h[i] = new MnvH2D((var_name+Form("_%s",namesPID[i].c_str())).c_str(),title.c_str(),xbins.nbins,xbinsarray,ybins.nbins,ybinsarray);

 }

 void CCQENuUtils::bookHistosByPID( MnvH2D** h, string var_name, string title, int xnbins, double xmin, double xmax, int ynbins, double ymin, double ymax ){

   for( unsigned int i = 0; i < nHistosPID; ++i )
     h[i] = new MnvH2D( ( var_name + '_' + namesPID[i] ). c_str(),title.c_str(),
			  xnbins, xmin, xmax, ynbins, ymin, ymax );

 }

 void CCQENuUtils::bookHistos( MnvH2D** h,string var_name,string title,axis_binning xbins, axis_binning ybins ){
   Double_t xbinsarray[xbins.nbins];
   for( unsigned int i = 0; i <= xbins.nbins; i++ )
     xbinsarray[i] = xbins.bin_edges[i];
   Double_t ybinsarray[ybins.nbins];
   for( unsigned int i = 0; i <= ybins.nbins; i++ )
     ybinsarray[i] = ybins.bin_edges[i];

   for( unsigned int i = 0; i < nHistos; i++ )
     h[i] = new MnvH2D((var_name+Form("_%s",names[i].c_str())).c_str(),title.c_str(),xbins.nbins,xbinsarray,ybins.nbins,ybinsarray);

 }

 void CCQENuUtils::bookHistos( MnvH3D** h, string var_name, string title, int xnbins, double xmin, double xmax, int ynbins, double ymin, double ymax, int znbins, double zmin, double zmax ){

   for( unsigned int i = 0; i < nHistos; ++i )
     h[i] = new MnvH3D( ( var_name + '_' + names[i] ). c_str(),title.c_str(),
			  xnbins, xmin, xmax, ynbins, ymin, ymax, znbins, zmin, zmax );

 }

 void CCQENuUtils::bookHistos( MnvH3D** h,string var_name,string title, axis_binning xbins, axis_binning ybins, axis_binning zbins ){
   Double_t xbinsarray[xbins.nbins];
   for( unsigned int i = 0; i <= xbins.nbins; i++ )
     xbinsarray[i] = xbins.bin_edges[i];
   Double_t ybinsarray[ybins.nbins];
   for( unsigned int i = 0; i <= ybins.nbins; i++ )
     ybinsarray[i] = ybins.bin_edges[i];
   Double_t zbinsarray[zbins.nbins];
   for( unsigned int i = 0; i <= zbins.nbins; i++ )
     zbinsarray[i] = zbins.bin_edges[i];

   for( unsigned int i = 0; i < nHistos; i++ )
     h[i] = new MnvH3D((var_name+Form("_%s",names[i].c_str())).c_str(),title.c_str(),xbins.nbins,xbinsarray,ybins.nbins,ybinsarray, zbins.nbins,zbinsarray);

 }
 void CCQENuUtils::bookDataHisto( MnvH2D** h,string var_name,string title,axis_binning xbins, axis_binning ybins ){
   Double_t xbinsarray[xbins.nbins];
   for( unsigned int i = 0; i <= xbins.nbins; i++ )
     xbinsarray[i] = xbins.bin_edges[i];
   Double_t ybinsarray[ybins.nbins];
   for( unsigned int i = 0; i <= ybins.nbins; i++ )
     ybinsarray[i] = ybins.bin_edges[i];

   h[kData] = new MnvH2D((var_name+"_data").c_str(),title.c_str(),xbins.nbins,xbinsarray,ybins.nbins,ybinsarray);

 }

 //==============================================================
 // Setup Response
 //==============================================================

 void CCQENuUtils::setupResponse( MinervaUnfold::MnvResponse*& response, string var_name, string title, axis_binning x_reco, axis_binning y_reco, axis_binning x_truth, axis_binning y_truth ){
   response = new MinervaUnfold::MnvResponse((var_name+"_qelike" ).c_str(), title.c_str(), x_reco, y_reco, x_truth, y_truth );
   cout << response << endl;
 }

 //====================================================================================
 // Fill Histos
 //====================================================================================
 void CCQENuUtils::fillHistos( MnvH1D** h, double var ){  // fill data
   h[kData]->Fill( var );
 }

 void CCQENuUtils::fillHistos( MnvH1D** h, double var, CCQENuEvent* event, double w ){  // fill mc

   h[kMC]->Fill( var, w );
   if( cutter->passTrueCCQE( event )  )  h[kQE]->Fill( var, w );
   else                                  h[kQENot]->Fill( var, w );

   if( cutter->passTrueCCRES( event ) )  h[kRES]->Fill( var, w );
   if( cutter->passTrueCCDIS( event ) )  h[kDIS]->Fill( var, w );
     if( !cutter->passTrueCCQE( event ) && !cutter->passTrueCCRES( event ) && !cutter->passTrueCCDIS( event ) )
    h[kOTH]->Fill( var, w);
  if( cutter->passTrueCCQELike( event ) ) h[kQELike]->Fill( var, w );
  else                                    h[kQELikeNot]->Fill( var, w );

  if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCQE( event )  )  h[kQELike_QE]->Fill( var, w );
  if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCRES( event ) )  h[kQELike_RES]->Fill( var, w );
  if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCDIS( event ) )  h[kQELike_DIS]->Fill( var, w ); 
  if( cutter->passTrueCCQELike( event ) && (!cutter->passTrueCCQE( event ) && (!cutter->passTrueCCRES( event ) && !cutter->passTrueCCDIS( event )) ) )
    h[kQELike_OTH]->Fill( var, w );
  
  if( !cutter->passTrueCCQELike( event ) && cutter->passTruePositivePion( event ) ){
      h[kQELikeNot_PositivePions]->Fill( var, w );
      if( event->truth_has_michel_electron )
        h[kQELikeNot_PositivePions_TrueMichel]->Fill( var, w );
      else 
        h[kQELikeNot_PositivePions_TrueMichelNot]->Fill( var, w );
  }
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueNegativePion( event ) )  h[kQELikeNot_NegativePions]->Fill( var, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueNeutralPion( event ) )   h[kQELikeNot_NeutralPions]->Fill( var, w );
  if( !cutter->passTrueCCQELike( event ) && !cutter->passTruePion( event ) )         h[kQELikeNot_NoPions]->Fill( var, w );

  if( !cutter->passTrueCCQELike( event ) && (cutter->passTruePositivePion( event ) || cutter->passTrueNegativePion( event )) ){
    h[kQELikeNot_ChargedPions]->Fill( var, w );
    if( event->truth_has_michel_electron )
      h[kQELikeNot_ChargedPions_TrueMichel]->Fill( var, w );
    else 
      h[kQELikeNot_ChargedPions_TrueMichelNot]->Fill( var, w );
  }
  if( !cutter->passTrueCCQELike( event ) &&  !cutter->passTruePositivePion( event ) && !cutter->passTrueNegativePion( event ) )
    h[kQELikeNot_ChargedPionsNot]->Fill( var, w );

  if( !cutter->passTrueCCQE( event ) && cutter->passTruePositivePion( event ) ){
      h[kQENot_PositivePions]->Fill( var, w );
      if( event->truth_has_michel_electron )
        h[kQENot_PositivePions_TrueMichel]->Fill( var, w );
      else 
        h[kQENot_PositivePions_TrueMichelNot]->Fill( var, w );
  }
  if( !cutter->passTrueCCQE( event ) && cutter->passTrueNegativePion( event ) )  h[kQENot_NegativePions]->Fill( var, w );
  if( !cutter->passTrueCCQE( event ) && cutter->passTrueNeutralPion( event ) )   h[kQENot_NeutralPions]->Fill( var, w );
  if( !cutter->passTrueCCQE( event ) && !cutter->passTruePion( event ) )         h[kQENot_NoPions]->Fill( var, w );
  
  if( cutter->passTrueCCQELike( event ) && !cutter->passTrueCCQE( event ) )  h[kQELike_QENot]->Fill( var, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueCCQE( event ) )  h[kQELikeNot_QE]->Fill( var, w );
  if( !cutter->passTrueCCQELike( event ) && !cutter->passTrueCCQE( event ) )  h[kQELikeNot_QENot]->Fill( var, w );

  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueSingleChargedPion( event ) )  h[kQELikeNot_SingleChargedPion]->Fill( var, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueSingleNeutralPion( event ) )  h[kQELikeNot_SingleNeutralPion]->Fill( var, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueMultiPion( event ) )  h[kQELikeNot_MultiPion]->Fill( var, w );
}

void CCQENuUtils::fillHistos( MnvH1D** h, double var, CCQENuTruth* event, double w ){  // fill mc

  h[kMC]->Fill( var, w );
  if( cutter->passTrueCCQE( event )  )  h[kQE]->Fill( var, w );
  else                                  h[kQENot]->Fill( var, w );

  if( cutter->passTrueCCRES( event ) )  h[kRES]->Fill( var, w );
  if( cutter->passTrueCCDIS( event ) )  h[kDIS]->Fill( var, w );
  if( !cutter->passTrueCCQE( event ) && !cutter->passTrueCCRES( event ) && !cutter->passTrueCCDIS( event ) )
    h[kOTH]->Fill( var, w);
  if( cutter->passTrueCCQELike( event ) ) h[kQELike]->Fill( var, w );
  else                                    h[kQELikeNot]->Fill( var, w );

  if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCQE( event )  )  h[kQELike_QE]->Fill( var, w );
  if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCRES( event ) )  h[kQELike_RES]->Fill( var, w );
  if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCDIS( event ) )  h[kQELike_DIS]->Fill( var, w ); 
  if( cutter->passTrueCCQELike( event ) && (!cutter->passTrueCCQE( event ) && (!cutter->passTrueCCRES( event ) && !cutter->passTrueCCDIS( event )) ) )
    h[kQELike_OTH]->Fill( var, w );
  
  if( !cutter->passTrueCCQELike( event ) && cutter->passTruePositivePion( event ) ){
    h[kQELikeNot_PositivePions]->Fill( var, w );
        /* Deactivate until truth_has_michel_electron branch is added tu truth
    if( event->truth_has_michel_electron )
      h[kQELikeNot_PositivePions_TrueMichel]->Fill( var, w );
    else 
      h[kQELikeNot_PositivePions_TrueMichelNot]->Fill( var, w );
        */
  }
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueNegativePion( event ) )  h[kQELikeNot_NegativePions]->Fill( var, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueNeutralPion( event ) )   h[kQELikeNot_NeutralPions]->Fill( var, w );
  if( !cutter->passTrueCCQELike( event ) && !cutter->passTruePion( event ) )         h[kQELikeNot_NoPions]->Fill( var, w );

  if( !cutter->passTrueCCQELike( event ) && (cutter->passTruePositivePion( event ) || cutter->passTrueNegativePion( event )) ){
    h[kQELikeNot_ChargedPions]->Fill( var, w );
    /* Deactivate until truth_has_michel_electron branch is added tu truth
    if( event->truth_has_michel_electron )
      h[kQELikeNot_ChargedPions_TrueMichel]->Fill( var, w );
    else 
      h[kQELikeNot_ChargedPions_TrueMichelNot]->Fill( var, w );
    */
  }
  if( !cutter->passTrueCCQELike( event ) &&  !cutter->passTruePositivePion( event ) && !cutter->passTrueNegativePion( event ) )
    h[kQELikeNot_ChargedPionsNot]->Fill( var, w );

  if( !cutter->passTrueCCQE( event ) && cutter->passTruePositivePion( event ) ){
    h[kQENot_PositivePions]->Fill( var, w );
        /* Deactivate until truth_has_michel_electron branch is added tu truth

    if( event->truth_has_michel_electron )
      h[kQENot_PositivePions_TrueMichel]->Fill( var, w );
    else 
      h[kQENot_PositivePions_TrueMichelNot]->Fill( var, w );
        */
  }
  if( !cutter->passTrueCCQE( event ) && cutter->passTrueNegativePion( event ) )  h[kQENot_NegativePions]->Fill( var, w );
  if( !cutter->passTrueCCQE( event ) && cutter->passTrueNeutralPion( event ) )   h[kQENot_NeutralPions]->Fill( var, w );
  if( !cutter->passTrueCCQE( event ) && !cutter->passTruePion( event ) )         h[kQENot_NoPions]->Fill( var, w );
  
  if( cutter->passTrueCCQELike( event ) && !cutter->passTrueCCQE( event ) )  h[kQELike_QENot]->Fill( var, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueCCQE( event ) )  h[kQELikeNot_QE]->Fill( var, w );
  if( !cutter->passTrueCCQELike( event ) && !cutter->passTrueCCQE( event ) )  h[kQELikeNot_QENot]->Fill( var, w );

  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueSingleChargedPion( event ) )  h[kQELikeNot_SingleChargedPion]->Fill( var, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueSingleNeutralPion( event ) )  h[kQELikeNot_SingleNeutralPion]->Fill( var, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueMultiPion( event ) )  h[kQELikeNot_MultiPion]->Fill( var, w );

}

void CCQENuUtils::fillHistosByPID( MnvH1D** h, double var, CCQENuEvent* event, double w){
  h[pMC]->Fill( var, w );
  if( abs(event->proton_prong_PDG) == 2212) 
    h[pProton]->Fill( var, w );
  else if( abs(event->proton_prong_PDG) == 211)
    h[pPion]->Fill( var, w);
  else{
    h[pOther]->Fill(var, w);
  }
}

void CCQENuUtils::fillHistosByPID( MnvH1D** h, double var){
  h[pData]->Fill( var );
}

void CCQENuUtils::fillHistos( MnvH2D** h, double var_x, double var_y ){  // fill data
  h[kData]->Fill( var_x, var_y );
}

void CCQENuUtils::fillHistos( MnvH2D** h, double var_x, double var_y, CCQENuEvent* event, double w ){  // fill mc

  h[kMC]->Fill( var_x, var_y, w );
  if( cutter->passTrueCCQE( event )  )  h[kQE]->Fill( var_x, var_y, w );
  else                                  h[kQENot]->Fill( var_x, var_y, w );

  if( cutter->passTrueCCRES( event ) )  h[kRES]->Fill( var_x, var_y, w );
  if( cutter->passTrueCCDIS( event ) )  h[kDIS]->Fill( var_x, var_y, w );
  if( !cutter->passTrueCCQE( event ) && !cutter->passTrueCCRES( event ) && !cutter->passTrueCCDIS( event ) )
    h[kOTH]->Fill( var_x, var_y, w);
  if( cutter->passTrueCCQELike( event ) ) h[kQELike]->Fill( var_x, var_y, w );
  else                                    h[kQELikeNot]->Fill( var_x, var_y, w );

  if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCQE( event )  )  h[kQELike_QE]->Fill( var_x, var_y, w );
  if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCRES( event ) )  h[kQELike_RES]->Fill( var_x, var_y, w );
  if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCDIS( event ) )  h[kQELike_DIS]->Fill( var_x, var_y, w );
  if( cutter->passTrueCCQELike( event ) && (!cutter->passTrueCCQE( event ) && (!cutter->passTrueCCRES( event ) && !cutter->passTrueCCDIS( event )) ) )
    h[kQELike_OTH]->Fill( var_x, var_y, w );
  
  if( !cutter->passTrueCCQELike( event ) && cutter->passTruePositivePion( event ) ){
    h[kQELikeNot_PositivePions]->Fill( var_x, var_y, w );
    if( event->truth_has_michel_electron )
      h[kQELikeNot_PositivePions_TrueMichel]->Fill( var_x, var_y, w );
    else 
      h[kQELikeNot_PositivePions_TrueMichelNot]->Fill( var_x, var_y, w );
  }
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueNegativePion( event ) )  h[kQELikeNot_NegativePions]->Fill( var_x, var_y, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueNeutralPion( event ) )   h[kQELikeNot_NeutralPions]->Fill( var_x, var_y, w );
  if( !cutter->passTrueCCQELike( event ) && !cutter->passTruePion( event ) )         h[kQELikeNot_NoPions]->Fill( var_x, var_y, w );

  if( !cutter->passTrueCCQELike( event ) && (cutter->passTruePositivePion( event ) || cutter->passTrueNegativePion( event )) ){
    h[kQELikeNot_ChargedPions]->Fill( var_x, var_y, w );
    if( event->truth_has_michel_electron )
      h[kQELikeNot_ChargedPions_TrueMichel]->Fill( var_x, var_y, w );
    else 
      h[kQELikeNot_ChargedPions_TrueMichelNot]->Fill( var_x, var_y, w );
  }
  if( !cutter->passTrueCCQELike( event ) &&  !cutter->passTruePositivePion( event ) && !cutter->passTrueNegativePion( event ) )
    h[kQELikeNot_ChargedPionsNot]->Fill( var_x, var_y, w );

  if( !cutter->passTrueCCQE( event ) && cutter->passTruePositivePion( event ) ){
    h[kQENot_PositivePions]->Fill( var_x, var_y, w );
    if( event->truth_has_michel_electron )
      h[kQENot_PositivePions_TrueMichel]->Fill( var_x, var_y, w );
    else 
      h[kQENot_PositivePions_TrueMichelNot]->Fill( var_x, var_y, w );
  }
  if( !cutter->passTrueCCQE( event ) && cutter->passTrueNegativePion( event ) )  h[kQENot_NegativePions]->Fill( var_x, var_y, w );
  if( !cutter->passTrueCCQE( event ) && cutter->passTrueNeutralPion( event ) )   h[kQENot_NeutralPions]->Fill( var_x, var_y, w );
  if( !cutter->passTrueCCQE( event ) && !cutter->passTruePion( event ) )         h[kQENot_NoPions]->Fill( var_x, var_y, w );
  
  if( cutter->passTrueCCQELike( event ) && !cutter->passTrueCCQE( event ) )  h[kQELike_QENot]->Fill( var_x, var_y, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueCCQE( event ) )  h[kQELikeNot_QE]->Fill( var_x, var_y, w );
  if( !cutter->passTrueCCQELike( event ) && !cutter->passTrueCCQE( event ) )  h[kQELikeNot_QENot]->Fill( var_x, var_y, w );

  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueSingleChargedPion( event ) )  h[kQELikeNot_SingleChargedPion]->Fill( var_x, var_y, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueSingleNeutralPion( event ) )  h[kQELikeNot_SingleNeutralPion]->Fill( var_x, var_y, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueMultiPion( event ) )  h[kQELikeNot_MultiPion]->Fill( var_x, var_y, w );

}

void CCQENuUtils::fillHistos( MnvH2D** h, double var_x, double var_y, CCQENuTruth* event, double w ){  // fill mc

  h[kMC]->Fill( var_x, var_y, w );
  if( cutter->passTrueCCQE( event )  )  h[kQE]->Fill( var_x, var_y, w );
  else                                  h[kQENot]->Fill( var_x, var_y, w );

  if( cutter->passTrueCCRES( event ) )  h[kRES]->Fill( var_x, var_y, w );
  if( cutter->passTrueCCDIS( event ) )  h[kDIS]->Fill( var_x, var_y, w );
  if( !cutter->passTrueCCQE( event ) && !cutter->passTrueCCRES( event ) && !cutter->passTrueCCDIS( event ) )
    h[kOTH]->Fill( var_x, var_y, w);
  if( cutter->passTrueCCQELike( event ) ) h[kQELike]->Fill( var_x, var_y, w );
  else                                    h[kQELikeNot]->Fill( var_x, var_y, w );

  if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCQE( event )  )  h[kQELike_QE]->Fill( var_x, var_y, w );
  if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCRES( event ) )  h[kQELike_RES]->Fill( var_x, var_y, w );
  if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCDIS( event ) )  h[kQELike_DIS]->Fill( var_x, var_y, w );
  if( cutter->passTrueCCQELike( event ) && (!cutter->passTrueCCQE( event ) && (!cutter->passTrueCCRES( event ) && !cutter->passTrueCCDIS( event )) ) )
    h[kQELike_OTH]->Fill( var_x, var_y, w );
  
  if( !cutter->passTrueCCQELike( event ) && cutter->passTruePositivePion( event ) ){
    h[kQELikeNot_PositivePions]->Fill( var_x, var_y, w );
        /* Deactivate until truth_has_michel_electron branch is added tu truth
    if( event->truth_has_michel_electron )
      h[kQELikeNot_PositivePions_TrueMichel]->Fill( var_x, var_y, w );
    else 
      h[kQELikeNot_PositivePions_TrueMichelNot]->Fill( var_x, var_y, w );
        */
  }
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueNegativePion( event ) )  h[kQELikeNot_NegativePions]->Fill( var_x, var_y, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueNeutralPion( event ) )   h[kQELikeNot_NeutralPions]->Fill( var_x, var_y, w );
  if( !cutter->passTrueCCQELike( event ) && !cutter->passTruePion( event ) )         h[kQELikeNot_NoPions]->Fill( var_x, var_y, w );

  if( !cutter->passTrueCCQELike( event ) && (cutter->passTruePositivePion( event ) || cutter->passTrueNegativePion( event )) ){
    h[kQELikeNot_ChargedPions]->Fill( var_x, var_y, w );
        /* Deactivate until truth_has_michel_electron branch is added tu truth
    if( event->truth_has_michel_electron )
      h[kQELikeNot_ChargedPions_TrueMichel]->Fill( var_x, var_y, w );
    else 
      h[kQELikeNot_ChargedPions_TrueMichelNot]->Fill( var_x, var_y, w );
        */
  }
  if( !cutter->passTrueCCQELike( event ) &&  !cutter->passTruePositivePion( event ) && !cutter->passTrueNegativePion( event ) )
    h[kQELikeNot_ChargedPionsNot]->Fill( var_x, var_y, w );

  if( !cutter->passTrueCCQE( event ) && cutter->passTruePositivePion( event ) ){
    h[kQENot_PositivePions]->Fill( var_x, var_y, w );
        /* Deactivate until truth_has_michel_electron branch is added tu truth

    if( event->truth_has_michel_electron )
      h[kQENot_PositivePions_TrueMichel]->Fill( var_x, var_y, w );
    else 
      h[kQENot_PositivePions_TrueMichelNot]->Fill( var_x, var_y, w );
        */
  }
  if( !cutter->passTrueCCQE( event ) && cutter->passTrueNegativePion( event ) )  h[kQENot_NegativePions]->Fill( var_x, var_y, w );
  if( !cutter->passTrueCCQE( event ) && cutter->passTrueNeutralPion( event ) )   h[kQENot_NeutralPions]->Fill( var_x, var_y, w );
  if( !cutter->passTrueCCQE( event ) && !cutter->passTruePion( event ) )         h[kQENot_NoPions]->Fill( var_x, var_y, w );
  
  if( cutter->passTrueCCQELike( event ) && !cutter->passTrueCCQE( event ) )  h[kQELike_QENot]->Fill( var_x, var_y, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueCCQE( event ) )  h[kQELikeNot_QE]->Fill( var_x, var_y, w );
  if( !cutter->passTrueCCQELike( event ) && !cutter->passTrueCCQE( event ) )  h[kQELikeNot_QENot]->Fill( var_x, var_y, w );

  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueSingleChargedPion( event ) )  h[kQELikeNot_SingleChargedPion]->Fill( var_x, var_y, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueSingleNeutralPion( event ) )  h[kQELikeNot_SingleNeutralPion]->Fill( var_x, var_y, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueMultiPion( event ) )  h[kQELikeNot_MultiPion]->Fill( var_x, var_y, w );

}

void CCQENuUtils::fillResponse( MinervaUnfold::MnvResponse* response, double var_x, double var_y, double var_xtrue, double var_ytrue, CCQENuEvent* event, double w ){  // fill mc


  // response[kMC]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  // if( cutter->passTrueCCQE( event )  )  response[kQE]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  // else                                  response[kQENot]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );

  // if( cutter->passTrueCCRES( event ) )  response[kRES]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  // if( cutter->passTrueCCDIS( event ) )  response[kDIS]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  // if( !cutter->passTrueCCQE( event ) && !cutter->passTrueCCRES( event ) && !cutter->passTrueCCDIS( event ) )
  //   response[kOTH]->Fill( var_x, var_y, var_xtrue, var_ytrue, w);
  if( cutter->passTrueCCQELike( event ) ) response->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  // else                                    response[kQELikeNot]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );

  // if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCQE( event )  )  response[kQELike_QE]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  // if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCRES( event ) )  response[kQELike_RES]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  // if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCDIS( event ) )  response[kQELike_DIS]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  // if( cutter->passTrueCCQELike( event ) && (!cutter->passTrueCCQE( event ) && (!cutter->passTrueCCRES( event ) && !cutter->passTrueCCDIS( event )) ) )
  //   response[kQELike_OTH]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  
  // if( !cutter->passTrueCCQELike( event ) && cutter->passTruePositivePion( event ) ){
  //   response[kQELikeNot_PositivePions]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  //       /* Deactivate until truth_has_michel_electron branch is added tu truth
  //   if( event->truth_has_michel_electron )
  //   response[kQELikeNot_PositivePions_TrueMichel]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  //   else 
  //   response[kQELikeNot_PositivePions_TrueMichelNot]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  //       */
  // }
  // if( !cutter->passTrueCCQELike( event ) && cutter->passTrueNegativePion( event ) )  response[kQELikeNot_NegativePions]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  // if( !cutter->passTrueCCQELike( event ) && cutter->passTrueNeutralPion( event ) )   response[kQELikeNot_NeutralPions]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  // if( !cutter->passTrueCCQELike( event ) && !cutter->passTruePion( event ) )         response[kQELikeNot_NoPions]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );

  // if( !cutter->passTrueCCQELike( event ) && (cutter->passTruePositivePion( event ) || cutter->passTrueNegativePion( event )) ){
  //   response[kQELikeNot_ChargedPions]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  //       /* Deactivate until truth_has_michel_electron branch is added tu truth
  //   if( event->truth_has_michel_electron )
  //   response[kQELikeNot_ChargedPions_TrueMichel]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  //   else 
  //   response[kQELikeNot_ChargedPions_TrueMichelNot]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  //       */
  // }
  // if( !cutter->passTrueCCQELike( event ) &&  !cutter->passTruePositivePion( event ) && !cutter->passTrueNegativePion( event ) )
  //   response[kQELikeNot_ChargedPionsNot]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );

  // if( !cutter->passTrueCCQE( event ) && cutter->passTruePositivePion( event ) ){
  //   response[kQENot_PositivePions]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  //       /* Deactivate until truth_has_michel_electron branch is added to truth

  //   if( event->truth_has_michel_electron )
  //   response[kQENot_PositivePions_TrueMichel]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  //   else 
  //   response[kQENot_PositivePions_TrueMichelNot]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  //       */
  // }
  // if( !cutter->passTrueCCQE( event ) && cutter->passTrueNegativePion( event ) )  response[kQENot_NegativePions]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  // if( !cutter->passTrueCCQE( event ) && cutter->passTrueNeutralPion( event ) )   response[kQENot_NeutralPions]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  // if( !cutter->passTrueCCQE( event ) && !cutter->passTruePion( event ) )         response[kQENot_NoPions]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  
  // if( cutter->passTrueCCQELike( event ) && !cutter->passTrueCCQE( event ) )  response[kQELike_QENot]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  // if( !cutter->passTrueCCQELike( event ) && cutter->passTrueCCQE( event ) )  response[kQELikeNot_QE]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );
  // if( !cutter->passTrueCCQELike( event ) && !cutter->passTrueCCQE( event ) )  response[kQELikeNot_QENot]->Fill( var_x, var_y, var_xtrue, var_ytrue, w );

}

void CCQENuUtils::fillHistosByPID( MnvH2D** h, double var_x, double var_y, CCQENuEvent* event, double w){
  h[pMC]->Fill( var_x, var_y, w );
  if( abs(event->proton_prong_PDG) == 2212) 
    h[pProton]->Fill( var_x, var_y, w );
  else if( abs(event->proton_prong_PDG) == 211)
    h[pPion]->Fill( var_x, var_y, w);
  else{
    h[pOther]->Fill(var_x, var_y, w);
  }
}

void CCQENuUtils::fillHistosByPID( MnvH2D** h, double var_x, double var_y){
  h[pData]->Fill( var_x, var_y );
}

void CCQENuUtils::fillHistos( MnvH3D** h, double var_x, double var_y, double var_z ){  // fill data
  h[kData]->Fill( var_x, var_y, var_z );
}

void CCQENuUtils::fillHistos( MnvH3D** h, double var_x, double var_y, double var_z, CCQENuEvent* event, double w ){  // fill mc

  h[kMC]->Fill( var_x, var_y, var_z, w );
  if( cutter->passTrueCCQE( event )  )  h[kQE]->Fill( var_x, var_y, var_z, w );
  else                                  h[kQENot]->Fill( var_x, var_y, var_z, w );

  if( cutter->passTrueCCRES( event ) )  h[kRES]->Fill( var_x, var_y, var_z, w );
  if( cutter->passTrueCCDIS( event ) )  h[kDIS]->Fill( var_x, var_y, var_z, w );
  if( !cutter->passTrueCCQE( event ) && !cutter->passTrueCCRES( event ) && !cutter->passTrueCCDIS( event ) )
    h[kOTH]->Fill( var_x, var_y, var_z, w);
  if( cutter->passTrueCCQELike( event ) ) h[kQELike]->Fill( var_x, var_y, var_z, w );
  else                                    h[kQELikeNot]->Fill( var_x, var_y, var_z, w );

  if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCQE( event )  )  h[kQELike_QE]->Fill( var_x, var_y, var_z, w );
  if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCRES( event ) )  h[kQELike_RES]->Fill( var_x, var_y, var_z, w );
  if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCDIS( event ) )  h[kQELike_DIS]->Fill( var_x, var_y, var_z, w );
  if( cutter->passTrueCCQELike( event ) && (!cutter->passTrueCCQE( event ) && (!cutter->passTrueCCRES( event ) && !cutter->passTrueCCDIS( event )) ) )
    h[kQELike_OTH]->Fill( var_x, var_y, var_z, w );
  
  if( !cutter->passTrueCCQELike( event ) && cutter->passTruePositivePion( event ) ){
    h[kQELikeNot_PositivePions]->Fill( var_x, var_y, var_z, w );
    if( event->truth_has_michel_electron )
      h[kQELikeNot_PositivePions_TrueMichel]->Fill( var_x, var_y, var_z, w );
    else 
      h[kQELikeNot_PositivePions_TrueMichelNot]->Fill( var_x, var_y, var_z, w );
  }
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueNegativePion( event ) )  h[kQELikeNot_NegativePions]->Fill( var_x, var_y, var_z, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueNeutralPion( event ) )   h[kQELikeNot_NeutralPions]->Fill( var_x, var_y, var_z, w );
  if( !cutter->passTrueCCQELike( event ) && !cutter->passTruePion( event ) )         h[kQELikeNot_NoPions]->Fill( var_x, var_y, var_z, w );

  if( !cutter->passTrueCCQELike( event ) && (cutter->passTruePositivePion( event ) || cutter->passTrueNegativePion( event )) ){
    h[kQELikeNot_ChargedPions]->Fill( var_x, var_y, var_z, w );
    if( event->truth_has_michel_electron )
      h[kQELikeNot_ChargedPions_TrueMichel]->Fill( var_x, var_y, var_z, w );
    else 
      h[kQELikeNot_ChargedPions_TrueMichelNot]->Fill( var_x, var_y, var_z, w );
  }
  if( !cutter->passTrueCCQELike( event ) &&  !cutter->passTruePositivePion( event ) && !cutter->passTrueNegativePion( event ) )
    h[kQELikeNot_ChargedPionsNot]->Fill( var_x, var_y, var_z, w );

  if( !cutter->passTrueCCQE( event ) && cutter->passTruePositivePion( event ) ){
    h[kQENot_PositivePions]->Fill( var_x, var_y, var_z, w );
    if( event->truth_has_michel_electron )
      h[kQENot_PositivePions_TrueMichel]->Fill( var_x, var_y, var_z, w );
    else 
      h[kQENot_PositivePions_TrueMichelNot]->Fill( var_x, var_y, var_z, w );
  }
  if( !cutter->passTrueCCQE( event ) && cutter->passTrueNegativePion( event ) )  h[kQENot_NegativePions]->Fill( var_x, var_y, var_z, w );
  if( !cutter->passTrueCCQE( event ) && cutter->passTrueNeutralPion( event ) )   h[kQENot_NeutralPions]->Fill( var_x, var_y, var_z, w );
  if( !cutter->passTrueCCQE( event ) && !cutter->passTruePion( event ) )         h[kQENot_NoPions]->Fill( var_x, var_y, var_z, w );
  
  if( cutter->passTrueCCQELike( event ) && !cutter->passTrueCCQE( event ) )  h[kQELike_QENot]->Fill( var_x, var_y, var_z, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueCCQE( event ) )  h[kQELikeNot_QE]->Fill( var_x, var_y, var_z, w );
  if( !cutter->passTrueCCQELike( event ) && !cutter->passTrueCCQE( event ) )  h[kQELikeNot_QENot]->Fill( var_x, var_y, var_z, w );

}

void CCQENuUtils::fillHistos( MnvH3D** h, double var_x, double var_y, double var_z, CCQENuTruth* event, double w ){  // fill mc

  h[kMC]->Fill( var_x, var_y, var_z, w );
  if( cutter->passTrueCCQE( event )  )  h[kQE]->Fill( var_x, var_y, var_z, w );
  else                                  h[kQENot]->Fill( var_x, var_y, var_z, w );

  if( cutter->passTrueCCRES( event ) )  h[kRES]->Fill( var_x, var_y, var_z, w );
  if( cutter->passTrueCCDIS( event ) )  h[kDIS]->Fill( var_x, var_y, var_z, w );
  if( !cutter->passTrueCCQE( event ) && !cutter->passTrueCCRES( event ) && !cutter->passTrueCCDIS( event ) )
    h[kOTH]->Fill( var_x, var_y, var_z, w);
  if( cutter->passTrueCCQELike( event ) ) h[kQELike]->Fill( var_x, var_y, var_z, w );
  else                                    h[kQELikeNot]->Fill( var_x, var_y, var_z, w );

  if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCQE( event )  )  h[kQELike_QE]->Fill( var_x, var_y, var_z, w );
  if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCRES( event ) )  h[kQELike_RES]->Fill( var_x, var_y, var_z, w );
  if( cutter->passTrueCCQELike( event ) && cutter->passTrueCCDIS( event ) )  h[kQELike_DIS]->Fill( var_x, var_y, var_z, w );
  if( cutter->passTrueCCQELike( event ) && (!cutter->passTrueCCQE( event ) && (!cutter->passTrueCCRES( event ) && !cutter->passTrueCCDIS( event )) ) )
    h[kQELike_OTH]->Fill( var_x, var_y, var_z, w );
  
  if( !cutter->passTrueCCQELike( event ) && cutter->passTruePositivePion( event ) ){
    h[kQELikeNot_PositivePions]->Fill( var_x, var_y, var_z, w );
        /* Deactivate until truth_has_michel_electron branch is added tu truth
    if( event->truth_has_michel_electron )
      h[kQELikeNot_PositivePions_TrueMichel]->Fill( var_x, var_y, var_z, w );
    else 
      h[kQELikeNot_PositivePions_TrueMichelNot]->Fill( var_x, var_y, var_z, w );
        */
  }
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueNegativePion( event ) )  h[kQELikeNot_NegativePions]->Fill( var_x, var_y, var_z, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueNeutralPion( event ) )   h[kQELikeNot_NeutralPions]->Fill( var_x, var_y, var_z, w );
  if( !cutter->passTrueCCQELike( event ) && !cutter->passTruePion( event ) )         h[kQELikeNot_NoPions]->Fill( var_x, var_y, var_z, w );

  if( !cutter->passTrueCCQELike( event ) && (cutter->passTruePositivePion( event ) || cutter->passTrueNegativePion( event )) ){
    h[kQELikeNot_ChargedPions]->Fill( var_x, var_y, var_z, w );
        /* Deactivate until truth_has_michel_electron branch is added tu truth
    if( event->truth_has_michel_electron )
      h[kQELikeNot_ChargedPions_TrueMichel]->Fill( var_x, var_y, var_z, w );
    else 
      h[kQELikeNot_ChargedPions_TrueMichelNot]->Fill( var_x, var_y, var_z, w );
        */
  }
  if( !cutter->passTrueCCQELike( event ) &&  !cutter->passTruePositivePion( event ) && !cutter->passTrueNegativePion( event ) )
    h[kQELikeNot_ChargedPionsNot]->Fill( var_x, var_y, var_z, w );

  if( !cutter->passTrueCCQE( event ) && cutter->passTruePositivePion( event ) ){
    h[kQENot_PositivePions]->Fill( var_x, var_y, var_z, w );
        /* Deactivate until truth_has_michel_electron branch is added tu truth
    if( event->truth_has_michel_electron )
      h[kQENot_PositivePions_TrueMichel]->Fill( var_x, var_y, var_z, w );
    else 
      h[kQENot_PositivePions_TrueMichelNot]->Fill( var_x, var_y, var_z, w );
        */
  }
  if( !cutter->passTrueCCQE( event ) && cutter->passTrueNegativePion( event ) )  h[kQENot_NegativePions]->Fill( var_x, var_y, var_z, w );
  if( !cutter->passTrueCCQE( event ) && cutter->passTrueNeutralPion( event ) )   h[kQENot_NeutralPions]->Fill( var_x, var_y, var_z, w );
  if( !cutter->passTrueCCQE( event ) && !cutter->passTruePion( event ) )         h[kQENot_NoPions]->Fill( var_x, var_y, var_z, w );
  
  if( cutter->passTrueCCQELike( event ) && !cutter->passTrueCCQE( event ) )  h[kQELike_QENot]->Fill( var_x, var_y, var_z, w );
  if( !cutter->passTrueCCQELike( event ) && cutter->passTrueCCQE( event ) )  h[kQELikeNot_QE]->Fill( var_x, var_y, var_z, w );
  if( !cutter->passTrueCCQELike( event ) && !cutter->passTrueCCQE( event ) )  h[kQELikeNot_QENot]->Fill( var_x, var_y, var_z, w );

}

double CCQENuUtils::GetCVWeight( CCQENuEvent *event , string sample, bool isTrue){

  double final_wgt = 1.0;

  final_wgt = frw->GetFluxCVWeight(event->mc_incomingE/1000.,event->mc_incoming);//new flux reweighter methodology
  //If Using Eroica+ production use the following final_weight definition to compensate for horn geometry hack.
  //final_wgt/=event->mc_hornCurrent_cvweight; //EROICA +
  //final_wgt*= frw->GetMELowNuFluxWeight(event->mc_incomingE/1000.); //ME Flux Wiggle
                   
  /*
  if ( GlobalParameters::Get().m_usePPFX1Flux)
    final_wgt = event->wgt; //"wgt" is same as "mc_cvweight_total" 
  else
    //final_wgt = event->mc_gen1_cvweight_total;
    final_wgt = event->mc_gen1_cvweight_total/event->mc_hornCurrent_cvweight; //EROICA +
  */

  // HadronReweight temp, this was code to create was is effectively a variation sample using reweighting
  // As opposed to adding a vertical error band
  //int entry_number = event->fChain->GetReadEntry();
  //InelXSecWeights weights = mnvHadronReweight->getWeights(entry_number, false);
  //final_wgt = weights.protonTotalWeightDown;

  if( 1E3 < final_wgt || fabs( final_wgt ) < 1E-3 ) final_wgt = 1.0; 
  
  //Update playlist normalization correction before calling mnvNormalizer
  updatePlaylistNorm(event); 

  if( use_norm_wgt ) final_wgt *= GetNormWeight( event ); 

  //Using pion data fits
  if ( doGenieTuning ){
    bool isGenieNonRes1pi = event->truth_genie_wgt_Rvn1pi[2] < 1.0 || event->truth_genie_wgt_Rvp1pi[2] < 1.0;
    //    bool isGenieCCRes = event->mc_current == 1 && event->mc_intType == 2;
    //See docdb 11524 and 11567 for central value and error band modification values
    /* //It was decided the resonant pion modifications were too much when used with the nonresonant pion modification.
    if(isGenieCCRes){
      final_wgt *= 1.15;
      final_wgt *= 1.0 + fabs( deuteriumMaRes - genieMaRes ) * ( event->truth_genie_wgt_MaRES[2] - 1.0 ) / genieMaRes1sig;
    }
    */
    //if NonResPion // Only doing this because the CV now includes the 2p2h signal which mostly preserves the total CC cross section

    if(isGenieNonRes1pi) final_wgt *= deuteriumNonResNorm; //0.43
  }

  //do I do RPA supression?
  if ( doRPA ){
    //cout << final_wgt << endl;
    final_wgt *= CCQENuUtils::GetRPAWeight( event, 0 );
    //cout << final_wgt << endl;
  }
  
  if ( do2p2h ){
    final_wgt *= CCQENuUtils::Get2p2hWeight( event , 0);
  }
  
  if (doRPA_Nieves_Resonant && doRPA_MINOS_Resonant){
    cout << "You cannot apply RPA weights from Nieves and MINOS. It's one or the other. Check your CCQENuUtils.h and turn one of them off" << endl;
    exit(1);
  }

  if ( doRPA_Nieves_Resonant ){
    final_wgt *= CCQENuUtils::GetRPANievesResonantWeight( event, 0);
  }
  if ( doRPA_MINOS_Resonant ){
    final_wgt *= CCQENuUtils::GetRPAMINOSResonantWeight( event, 0);
  }

  //fill all weights containers
  if( vert_error_band_wgts && !vert_error_band_wgts->empty() ){
    fillVertErrorBandWgts( event );
  }
  if( lat_error_band_wgts && !lat_error_band_wgts->empty() ){
    fillLatErrorBandWgts( event, sample, isTrue );
  }

  wgt_CV = final_wgt;
  return final_wgt;
}

double CCQENuUtils::GetCVWeight( CCQENuTruth *truth ){ 

  double final_wgt = 1.0;
  final_wgt = frw->GetFluxCVWeight(truth->mc_incomingE/1000.,truth->mc_incoming);//new flux reweighter methodology
  //If Using Eroica+ production use the following final_weight definition to compensate for horn geometry hack.
  //final_wgt/=truth->mc_hornCurrent_cvweight; //EROICA +
  //final_wgt*= frw->GetMELowNuFluxWeight(truth->mc_incomingE/1000.); //ME Flux Wiggle

  /*
  if ( GlobalParameters::Get().m_usePPFX1Flux)
    final_wgt = truth->wgt; //"wgt" is same as "mc_cvweight_total" 
  else
    //final_wgt = truth->mc_gen1_cvweight_total;
    //If Using Eroica+ production use the following final_weight definition to compensate for horn geometry hack.
    final_wgt = truth->mc_gen1f_cvweight_total/truth->mc_hornCurrent_cvweight; //EROICA +
    */

  // HadronReweight temp, this was code to create was is effectively a variation sample using reweighting
  // As opposed to adding a vertical error band
  //int entry_number = truth->fChain->GetReadEntry();
  //InelXSecWeights weights = mnvHadronReweight->getWeights(entry_number, true);
  //final_wgt = weights.protonTotalWeightDown;

  if( 1E3 < final_wgt || fabs( final_wgt ) < 1E-3 ) final_wgt = 1.0; 

  //Using pion data fits
  if ( doGenieTuning ){
    bool isGenieNonRes1pi = truth->truth_genie_wgt_Rvn1pi[2] < 1.0 || truth->truth_genie_wgt_Rvp1pi[2] < 1.0;
    //    bool isGenieCCRes = truth->mc_current == 1 && truth->mc_intType == 2;
    //See docdb 11524 and 11567 for central value and error band modification values
    /*//It was decided the resonant pion modifications were too much when used with the nonresonant pion modification.
    if(isGenieCCRes){
      final_wgt *= 1.15;
      final_wgt *= 1.0 + fabs( deuteriumMaRes - genieMaRes ) * ( truth->truth_genie_wgt_MaRES[2] - 1.0 ) / genieMaRes1sig;
    }
    */
    //if NonResPion // Only doing this because the CV now includes the 2p2h signal which mostly preserves the total CC cross section
    if(isGenieNonRes1pi) final_wgt *= deuteriumNonResNorm; //0.43
  }

  //do I do RPA supression?
  if ( doRPA ){
    final_wgt *= CCQENuUtils::GetRPAWeight( truth, 0 );
  }

  if ( do2p2h ){
    final_wgt *= CCQENuUtils::Get2p2hWeight( truth , 0);
  }

  if (doRPA_Nieves_Resonant && doRPA_MINOS_Resonant){
    cout << "You cannot apply RPA weights from Nieves and MINOS. It's one or the other. Check your CCQENuUtils.h and turn one of them off" << endl;
    exit(1);
  }

  if ( doRPA_Nieves_Resonant ){
    final_wgt *= CCQENuUtils::GetRPANievesResonantWeight( truth, 0);
  }
  if ( doRPA_MINOS_Resonant ){
    final_wgt *= CCQENuUtils::GetRPAMINOSResonantWeight( truth, 0);
  }

  //Set all weights
  if( vert_error_band_wgts && !vert_error_band_wgts->empty() ){
    fillVertErrorBandWgts( truth );
  }
  
  if( wgt_CV > 1.0e6 ){
    cout << "weight has a weird value" << endl;
    return 1.0;
  }

  wgt_CV_truth = final_wgt;
  wgt_CV = final_wgt;
  return final_wgt;
}

/*
double CCQENuUtils::GetNormWeight( CCQENuEvent *event ){

  const bool isLowP = event->CCQENu_minos_trk_p < MnvNorm::minosP_minos_trk_eff_threshP; 
  
  double effWgt = isLowP ? c_normWgt_low:c_normWgt_high; 

  double normWgt = effWgt; 

  return normWgt; 
}

double CCQENuUtils::GetNormWeightErr( CCQENuEvent *event ){

  const bool isLowP = event->CCQENu_minos_trk_p < MnvNorm::minosP_minos_trk_eff_threshP; 

  double err = isLowP ? c_normWgtErr_low: c_normWgtErr_high; 

  //Do I need to subtract the mass scale error ? I have asked experts (10/17/14)
  return err; 
}
*/

double CCQENuUtils::GetNormWeight( CCQENuEvent *event ){
  double effWgt = 1.0;
  double batch_pot = 0.;

  if(event->batch_structure==0 || event->batch_structure==3) batch_pot = event->numi_pot/6.;
  else if(event->batch_structure==1 && event->reco_vertex_batch < 3) batch_pot = event->numi_pot/4.;
  else if(event->batch_structure==1 && event->reco_vertex_batch > 2) batch_pot = event->numi_pot/8.;
  else if(event->batch_structure==2 && event->reco_vertex_batch < 5) batch_pot = event->numi_pot/5.;
  else if(event->batch_structure==2 && event->reco_vertex_batch > 4) batch_pot = event->numi_pot/10.;

  effWgt = MinosMuonEfficiencyCorrection::Get().GetCorrection(event->CCQENu_minos_trk_p, batch_pot);

  double normWgt = effWgt;

  return normWgt;
}

double CCQENuUtils::GetNormWeightErr( CCQENuEvent *event ){
  double err = 0.0;
  double batch_pot = 0.;

  if(event->batch_structure==0 || event->batch_structure==3) batch_pot = event->numi_pot/6.;
  else if(event->batch_structure==1 && event->reco_vertex_batch < 3) batch_pot = event->numi_pot/4.;
  else if(event->batch_structure==1 && event->reco_vertex_batch > 2) batch_pot = event->numi_pot/8.;
  else if(event->batch_structure==2 && event->reco_vertex_batch < 5) batch_pot = event->numi_pot/5.;
  else if(event->batch_structure==2 && event->reco_vertex_batch > 4) batch_pot = event->numi_pot/10.;

  err = MinosMuonEfficiencyCorrection::Get().GetCorrectionErr(event->CCQENu_minos_trk_p, event->CCQENu_muon_theta*(180./3.1415), batch_pot);

  return err;
}

double CCQENuUtils::GetHighestTrueProtonMomentum( CCQENuEvent *event){

  double proton_p = -1.0;
  for(int i=0; i<event->mc_nFSPart; ++i){
    if( event->mc_FSPartPDG[i]!=2212 ) continue;
    double proton_p_temp = sqrt( pow(event->mc_FSPartPx[i],2) + pow(event->mc_FSPartPy[i],2) + pow(event->mc_FSPartPz[i],2) );
    //Pick the highest proton
    if( proton_p_temp > proton_p ) proton_p = proton_p_temp;
    
  }
  return proton_p;
}

double CCQENuUtils::GetHighestTrueProtonMomentum( CCQENuTruth *truth){

  double proton_p = -1.0;
  for(int i=0; i<truth->mc_nFSPart; ++i){
    if( truth->mc_FSPartPDG[i]!=2212 ) continue;
    double proton_p_temp = sqrt( pow(truth->mc_FSPartPx[i],2) + pow(truth->mc_FSPartPy[i],2) + pow(truth->mc_FSPartPz[i],2) );
    //Pick the highest proton
    if( proton_p_temp > proton_p ) proton_p = proton_p_temp;
    
  }
  return proton_p;
  
}

double CCQENuUtils::GetTotalMomentum( double px, double py, double pz ){
  return sqrt(pow(px,2) + pow(py,2) + pow(pz,2));
}

double CCQENuUtils::GetTransverseMomentumWRTBeam( double px, double py, double pz, double bias ){

  double py_prime = -1.0 *sin( numi_beam_angle_rad +bias )*pz + cos( numi_beam_angle_rad +bias )*py;
  double pt       = sqrt( pow(px,2) + pow(py_prime,2) );
  return pt;
}

double CCQENuUtils::GetLongitudinalMomentumWRTBeam( double px, double py, double pz, double bias ){

  double pz_prime = cos( numi_beam_angle_rad +bias )*pz + sin( numi_beam_angle_rad +bias )*py;
  return pz_prime;
}

double CCQENuUtils::GetTrueCCQENeutrinoEnergy(double muonP, double muonTheta, const double bindingE){


 double nuE = -9999.0; 
 const double muonE = sqrt( pow( muonP, 2 ) + pow( M_mu, 2 ) );
 double nu_energy_num = pow( M_p, 2 ) - pow( M_n - bindingE, 2 ) - pow( M_mu, 2 ) + 2.0 * ( M_n - bindingE ) * muonE;
 double nu_energy_den = 2.0 * ( M_n - bindingE - muonE + muonP * cos( muonTheta ) );
 if (nu_energy_den)
   nuE = nu_energy_num / nu_energy_den;

 return nuE;
}

double CCQENuUtils::GetTrueCCQEQ2(double muonP, double muonTheta, const double bindingE ){

  double q2 = -9999.0;
  const double muonE = sqrt( pow( muonP, 2 ) + pow( M_mu, 2 ) );
  double nuE = GetTrueCCQENeutrinoEnergy( muonP, muonTheta, bindingE);
  q2 = 2.0 * nuE * ( muonE - muonP * cos( muonTheta ) ) - pow( M_mu, 2 );

  return q2;
}

double CCQENuUtils::GetTheta(double px, double py, double pz){
   double pyprime = -1.0*sin(numi_beam_angle_rad)*pz + cos(numi_beam_angle_rad)*py;
   double pzprime =  1.0*cos(numi_beam_angle_rad)*pz + sin(numi_beam_angle_rad)*py;
   //return atan( sqrt( px*px + pyprime*pyprime) / pzprime );
   double pSquare = pow(px,2) + pow(pyprime,2) + pow(pzprime,2);
   if( 0. == pSquare )
     return -999.;
   else
     return acos( pzprime / sqrt(pSquare) );
}


double CCQENuUtils::GetTrueQ0(CCQENuEvent *event){
  double q0 = -1;
  q0 = event->mc_incomingPartVec[3]-event->mc_primFSLepton[3];
  return q0/1000.0;
}

double CCQENuUtils::GetTrueQ0(CCQENuTruth *event){
  double q0 = -1;
  q0 = event->mc_incomingPartVec[3]-event->mc_primFSLepton[3];
  return q0/1000.0;
}

double CCQENuUtils::GetTrueQ3(CCQENuEvent *event){
  double px = event->mc_primFSLepton[0]-event->mc_incomingPartVec[0];
  double py = event->mc_primFSLepton[1]-event->mc_incomingPartVec[1];
  double pz = event->mc_primFSLepton[2]-event->mc_incomingPartVec[2];
  double q3 = sqrt(px*px+py*py+pz*pz);

  return q3/1000.0;
}

double CCQENuUtils::GetTrueQ3(CCQENuTruth *event){
  double px = event->mc_primFSLepton[0]-event->mc_incomingPartVec[0];
  double py = event->mc_primFSLepton[1]-event->mc_incomingPartVec[1];
  double pz = event->mc_primFSLepton[2]-event->mc_incomingPartVec[2];
  double q3 = sqrt(px*px+py*py+pz*pz);

  return q3/1000.0;
}

double CCQENuUtils::GetRPANievesResonantWeight(CCQENuEvent *event, int variation){
  double ret = 1.0;
  int inttype = event->mc_intType;
  if(inttype==2 ){
    ret = weight_cv_and_var_RPA->getWeight(event->mc_Q2/(1.0e6));//Requires Q2 in GeV^2 not MeV
  }
  return ret;
}
double CCQENuUtils::GetRPANievesResonantWeight(CCQENuTruth *event, int variation){
  double ret = 1.0;
  int inttype = event->mc_intType;
  if(inttype==2 ){
    ret = weight_cv_and_var_RPA->getWeight(event->mc_Q2/(1.0e6));//Requires Q2 in GeV^2 not MeV
  }
  return ret;
}

double CCQENuUtils::GetRPAMINOSResonantWeight(CCQENuEvent *event, int variation){
  //This is from arxiv.org:1410.8613 Adamson et al PRD 91 (2015) 012005
  double ret = 1.0;
  if(event->mc_intType!=2) return ret;
  ret = 1.010 / (1.0 + TMath::Exp(1.0 - TMath::Sqrt(event->mc_Q2/(1.0e6))/0.156));
  return ret;
}

double CCQENuUtils::GetRPAMINOSResonantWeight(CCQENuTruth *event, int variation){
  //This is from arxiv.org:1410.8613 Adamson et al PRD 91 (2015) 012005
  double ret = 1.0;
  if(event->mc_intType!=2) return ret;
  ret = 1.010 / (1.0 + TMath::Exp(1.0 - TMath::Sqrt(event->mc_Q2/(1.0e6))/0.156));
  return ret;
}


double CCQENuUtils::GetRPAWeight(CCQENuEvent *event,int variation){
  double ret = 1.0;

  //variations
  //0 : CV value
  //1 : hq2pos
  //2 : hq2neg
  //3 : lq2pos
  //4 : lq2neg

  if(variation > 4|| !doRPA){
    return 1.0;
  }
  if(event->mc_intType!=1) return 1.0;
  if(event->mc_targetZ<6) return 1.0;
  const double q3=GetTrueQ3( event );//GeV
  const double q0=GetTrueQ0( event );//GeV
  if(variation==0) ret=weight_cv_and_var_RPA->getWeight(q0,q3);
  else if(variation==1) ret=weight_cv_and_var_RPA->getWeightHighQ2(q0,q3,1);
  else if(variation==2) ret=weight_cv_and_var_RPA->getWeightHighQ2(q0,q3,-1);
  else if(variation==3) ret=weight_cv_and_var_RPA->getWeightLowQ2(q0,q3,1);
  else if(variation==4) ret=weight_cv_and_var_RPA->getWeightLowQ2(q0,q3,-1);
  else cout << "Should not have gotten here. CCQENuUtils::GetRPAWeight(CCQENuTruth *event, int variation)"<< endl;
  return ret;
}

double CCQENuUtils::GetRPAWeight(CCQENuTruth *event, int variation){
  double ret = 1.0;
  
  //variations
  //0 : CV value
  //1 : hq2pos
  //2 : hq2neg
  //3 : lq2pos
  //4 : lq2neg

  if(variation > 4|| !doRPA){
    return 1.0;
  }
  if(event->mc_intType!=1) return 1.0;
  if(event->mc_targetZ<6) return 1.0;
  const double q3=GetTrueQ3( event );//GeV
  const double q0=GetTrueQ0( event );//GeV
  if(variation==0) ret=weight_cv_and_var_RPA->getWeight(q0,q3);
  else if(variation==1) ret=weight_cv_and_var_RPA->getWeightHighQ2(q0,q3,1);
  else if(variation==2) ret=weight_cv_and_var_RPA->getWeightHighQ2(q0,q3,-1);
  else if(variation==3) ret=weight_cv_and_var_RPA->getWeightLowQ2(q0,q3,1);
  else if(variation==4) ret=weight_cv_and_var_RPA->getWeightLowQ2(q0,q3,-1);
  else cout << "Should not have gotten here. CCQENuUtils::GetRPAWeight(CCQENuTruth *event, int variation)"<< endl;

  return ret;
}

template<class T> T sqr(T x) { return x*x; }
double CCQENuUtils::Get2p2hWeight(CCQENuTruth *event, int variation){
  
  //variations
  //0 : CV value 
  //1 : nn+pp pair only
  //2 : np pair only
  //3 : qe 1p1h variation. 
  //4 : wgt = 1

  if(variation>=4 || !do2p2h ){
    return 1.0;
  }
  if(event->mc_intType!=1 && event->mc_intType!=8){
    return 1.0; //if given invalid variations or the user doesn't want to apply this modification or the MC event is not CCQE or MEC
  }
  bool applyOn2p2h = false;
  bool applyOn1p1h = false;
  
  if(variation==0 || variation==1 || variation==2) applyOn2p2h = true;//CV, nn+pp pair only, np pair only fits
  else if (variation ==3) applyOn1p1h = true;
  if(event->mc_intType==1 && !applyOn1p1h) return 1.0; //if CCQE and don't apply 1p1h don't apply weights
  if(event->mc_intType==8 && !applyOn2p2h) return 1.0; //if MEC and don't apply 2p2h don't apply weights
  if(event->mc_intType==8 && applyOn1p1h) return 1.0; //if MEC and apply 1p1h don't apply weights
  bool isnnorpp = false;
  bool isnp = false;

  //now target analysis
  int target = event->mc_targetNucleon;
  if(target-2000000200==0 || target-2000000200==2) isnnorpp = true;
  if(target-2000000200==1) isnp = true;

  if(variation==1 && !isnnorpp) return 1.0;//variation 1 is for nn/pp only interactions
  if(variation==2 && !isnp) return 1.0;//variation 2 is for np only interactions

  const double q3=GetTrueQ3( event );//GeV
  const double q0=GetTrueQ0( event );//GeV
  double ret = 1.0;
  //Add mcreweight code here
  if(variation==0) ret=weight_cv_2p2h->getWeight(q0,q3);
  else if(variation==1) ret=weight_nn_2p2h->getWeight(q0,q3);
  else if(variation==2) ret=weight_np_2p2h->getWeight(q0,q3);
  else if(variation==3) ret=weight_qe_2p2h->getWeight(q0,q3);
  else cout <<"Should not have gotten here. CCQENuUtils::Get2p2hWeight(CCQENuTruth *event, int variation)"<< endl;
  return ret;
}

double CCQENuUtils::Get2p2hWeight(CCQENuEvent *event, int variation){
  
  //variations
  //0 : CV value 
  //1 : nn+pp pair only
  //2 : np pair only
  //3 : qe 1p1h variation. 
  //4 : wgt = 1

  if(variation>=4 || !do2p2h ){
    return 1.0;
  }
  if(event->mc_intType!=1 && event->mc_intType!=8){
    return 1.0; //if given invalid variations or the user doesn't want to apply this modification or the MC event is not CCQE or MEC
  }
  bool applyOn2p2h = false;
  bool applyOn1p1h = false;
  
  if(variation==0 || variation==1 || variation==2) applyOn2p2h = true;//CV, nn+pp pair only, np pair only fits
  else if (variation ==3) applyOn1p1h = true;
  if(event->mc_intType==1 && !applyOn1p1h) return 1.0; //if CCQE and don't apply 1p1h don't apply weights
  if(event->mc_intType==8 && !applyOn2p2h) return 1.0; //if MEC and don't apply 2p2h don't apply weights
  if(event->mc_intType==8 && applyOn1p1h) return 1.0; //if MEC and don't apply 1p1h don't apply weights  
  bool isnnorpp = false;
  bool isnp = false;

  //now target analysis
  int target = event->mc_targetNucleon;
  if(target-2000000200==0 || target-2000000200==2) isnnorpp = true;
  if(target-2000000200==1) isnp = true;
  
  if(variation==1 && !isnnorpp) return 1.0;//variation 1 is for nn/pp only interactions
  if(variation==2 && !isnp) return 1.0;//variation 2 is for np only interactions
 

  const double q3=GetTrueQ3( event );//GeV
  const double q0=GetTrueQ0( event );//GeV
  double ret = 1.0;
  //Add mcreweight code here
  if(variation==0) ret=weight_cv_2p2h->getWeight(q0,q3);
  else if(variation==1) ret=weight_nn_2p2h->getWeight(q0,q3);
  else if(variation==2) ret=weight_np_2p2h->getWeight(q0,q3);
  else if(variation==3) ret=weight_qe_2p2h->getWeight(q0,q3);
  else cout <<"Should not have gotten here. CCQENuUtils::Get2p2hWeight(CCQENuEvent *event, int variation)"<< endl;

  return ret;
}

std::vector<string> CCQENuUtils::GetGenieKnobNames() 
{ 

  std::vector<string> genieKnobNames; 

  if( ! use_genie_split ){
    genieKnobNames.push_back( "GENIE" );
  } else {
    genieKnobNames.push_back( "GENIE_AGKYxF1pi" );
    genieKnobNames.push_back( "GENIE_CCQEPauliSupViaKF" );
    genieKnobNames.push_back( "GENIE_EtaNCEL" );
    genieKnobNames.push_back( "GENIE_FrAbs_N" );
    genieKnobNames.push_back( "GENIE_FrAbs_pi" );
    genieKnobNames.push_back( "GENIE_FrCEx_N" ); 
    genieKnobNames.push_back( "GENIE_FrCEx_pi" );
    genieKnobNames.push_back( "GENIE_FrElas_N" );
    genieKnobNames.push_back( "GENIE_FrElas_pi" );
    genieKnobNames.push_back( "GENIE_FrInel_N" );
    //    genieKnobNames.push_back( "GENIE_FrInel_pi" );//Removed after it was discovered FSI knobs are NOT independent. This was essentially double counting with absorption
    genieKnobNames.push_back( "GENIE_FrPiProd_N" );
    genieKnobNames.push_back( "GENIE_FrPiProd_pi" );
    genieKnobNames.push_back( "GENIE_MFP_N" );
    genieKnobNames.push_back( "GENIE_MFP_pi" );
    //genieKnobNames.push_back( "GENIE_MaCCQE" );
    genieKnobNames.push_back( "GENIE_MaCCQEshape" );
    genieKnobNames.push_back( "GENIE_MaNCEL" );
    genieKnobNames.push_back( "GENIE_MaRES" );
    genieKnobNames.push_back( "GENIE_MvRES" );
    genieKnobNames.push_back( "GENIE_NormCCQE" );
    genieKnobNames.push_back( "GENIE_NormCCRES" );
    genieKnobNames.push_back( "GENIE_NormDISCC" );
    genieKnobNames.push_back( "GENIE_NormNCRES" );
    genieKnobNames.push_back( "GENIE_RDecBR1gamma" );
    genieKnobNames.push_back( "GENIE_Rvn1pi" );
    genieKnobNames.push_back( "GENIE_Rvn2pi" );
    genieKnobNames.push_back( "GENIE_Rvp1pi" );
    genieKnobNames.push_back( "GENIE_Rvp2pi" );
    genieKnobNames.push_back( "GENIE_Theta_Delta2Npi" );
    genieKnobNames.push_back( "GENIE_VecFFCCQEshape" );
    genieKnobNames.push_back( "GENIE_AhtBY" ); 
    genieKnobNames.push_back( "GENIE_BhtBY" );
    genieKnobNames.push_back( "GENIE_CV1uBY" );
    genieKnobNames.push_back( "GENIE_CV2uBY" ); 
  }

  return genieKnobNames; 
}


//====================================================================
// Create and Get Error Band Functions
//====================================================================
void CCQENuUtils::createVertErrorBandWgts()
{

  vert_error_band_wgts = new StrVecMap();

  (*vert_error_band_wgts)["Flux"] = new vector<double>( m_nUniverses, 1.0 );
  /*
  if( GlobalParameters::Get().m_useFluxConstraint ) { 
    if( !GlobalParameters::Get().m_neutrinoMode ) throw std::runtime_error( "Flux constraint is available only for neutrino mode (FHC)" ); 
    (*vert_error_band_wgts)["Flux"] = new vector<double>( m_nUniverses, 1.0 );
  } else {
    if( GlobalParameters::Get().m_usePPFX1Flux ) {
      (*vert_error_band_wgts)["Flux_HadronProduction"] = new vector<double>( m_nUniverses, 1.0 );
      (*vert_error_band_wgts)["Flux_BeamFocus"] = new vector<double>( m_nUniverses, 1.0 );
    } else {  
      (*vert_error_band_wgts)["Flux_Tertiary"] = new vector<double>( m_nUniverses, 1.0 );
      (*vert_error_band_wgts)["Flux_BeamFocus"] = new vector<double>( m_nUniverses, 1.0 );
      (*vert_error_band_wgts)["Flux_NA49"] = new vector<double>( m_nUniverses, 1.0 );
    }
  }
  */
  (*vert_error_band_wgts)["Normalization_Factors"] = new vector<double>( 2, 1.0 ); 

  // HadronReweight
  (*vert_error_band_wgts)["Reweight_Pion"] = new vector<double>( 2, 1.0 ); 
  (*vert_error_band_wgts)["Reweight_Proton"] = new vector<double>( 2, 1.0 ); 
  (*vert_error_band_wgts)["Reweight_Neutron"] = new vector<double>( 2, 1.0 ); 

  (*vert_error_band_wgts)["Target_Mass"] = new vector<double>( 2, 1.0 ); 

  (*vert_error_band_wgts)["Proton_TrackEff"] = new vector<double>( 2, 1.0 ); 

  (*vert_error_band_wgts)["Michel_Efficiency"] = new vector<double>( 2, 1.0 ); 
  
  // rpa weight
  (*vert_error_band_wgts)["RPA_HighQ2"] = new vector<double>( 2 , 1.0 );
  (*vert_error_band_wgts)["RPA_LowQ2"] = new vector<double>( 2 , 1.0 );
  // 2p2h weights
  (*vert_error_band_wgts)["Low_recoil_fits"] = new vector<double>( 3, 1.0 );

  /*
  if( ! use_genie_split ){
    (*vert_error_band_wgts)["GENIE"] = new vector<double>( m_nUniverses, 1.0 );
  } else {
    (*vert_error_band_wgts)["GENIE_AGKYxF1pi"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_CCQEPauliSupViaKF"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_EtaNCEL"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_FrAbs_N"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_FrAbs_pi"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_FrCEx_N"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_FrCEx_pi"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_FrElas_N"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_FrElas_pi"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_FrInel_N"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_FrInel_pi"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_FrPiProd_N"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_FrPiProd_pi"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_MFP_N"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_MFP_pi"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_MaCCQE"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_MaCCQEshape"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_MaNCEL"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_MaRES"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_MvRES"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_NormCCQE"] = new vector<double>( 2, 1.0 );
//    (*vert_error_band_wgts)["GENIE_NormCCRES"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_NormDISCC"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_NormNCRES"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_RDecBR1gamma"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_Rvn1pi"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_Rvn2pi"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_Rvp1pi"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_Rvp2pi"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_Theta_Delta2Npi"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_VecFFCCQEshape"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_AhtBY"] = new vector<double>( 2, 1.0 ); 
    (*vert_error_band_wgts)["GENIE_BhtBY"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_CV1uBY"] = new vector<double>( 2, 1.0 );
    (*vert_error_band_wgts)["GENIE_CV2uBY"] = new vector<double>( 2, 1.0 ); 
  }
  */

  std::vector<string> genieKnobNames = GetGenieKnobNames();
  std::vector<string>::iterator itName = genieKnobNames.begin(); 
  if( genieKnobNames.size() ==1 ) { 
    (*vert_error_band_wgts)[*itName] = new vector<double>( m_nUniverses, 1.0 ); 
  } else {  
    for( ; itName != genieKnobNames.end(); ++itName ) { 
      (*vert_error_band_wgts)[*itName] = new vector<double>( 2, 1.0 ); 
    }
  }

} //End of createVertErrorBandWgts() 

void CCQENuUtils::createLatErrorBandWgts(){

  // create lat. error band weights ( minos matched muon systematics)
  lat_error_band_wgts = new StrVecMap();
  (*lat_error_band_wgts)["Muon_Energy"] = new vector<double>( m_nUniverses, 1.0 );
  (*lat_error_band_wgts)["Muon_Theta"] = new vector<double>( m_nUniverses, 1.0 );
  //(*lat_error_band_wgts)["Binding_Energy"] = new vector<double>( m_nUniverses, 1.0 ); 

  //Particle Response ErrorBand Names (non-vtx energy systematics)
  (*lat_error_band_wgts)["Proton_Response"] = new vector<double>( m_nUniverses, 1.0 );
  //(*lat_error_band_wgts)["Low_Neutron_Response"] = new vector<double>( m_nUniverses, 1.0 );
  //(*lat_error_band_wgts)["Mid_Neutron_Response"] = new vector<double>( m_nUniverses, 1.0 );
  //(*lat_error_band_wgts)["High_Neutron_Response"] = new vector<double>( m_nUniverses, 1.0 );
  (*lat_error_band_wgts)["Pion_Response"] = new vector<double>( m_nUniverses, 1.0 );
  (*lat_error_band_wgts)["Muon_Response"] = new vector<double>( m_nUniverses, 1.0 );
  (*lat_error_band_wgts)["EM_Response"] = new vector<double>( m_nUniverses, 1.0 );
  (*lat_error_band_wgts)["Other_Response"] = new vector<double>( m_nUniverses, 1.0 );
  (*lat_error_band_wgts)["Crosstalk"] = new vector<double>( m_nUniverses, 1.0 );
  //(*lat_error_band_wgts)["MEU_Recoil"] = new vector<double>( m_nUniverses, 1.0 );

  (*lat_error_band_wgts)["Bethe_Bloch"] = new vector<double>( 2, 1.0 ); 
  (*lat_error_band_wgts)["MEU_Proton"] = new vector<double>( 2, 1.0 ); 
  (*lat_error_band_wgts)["Mass_Model_Proton"] = new vector<double>( 2, 1.0 );  
  (*lat_error_band_wgts)["Birks_Response_Proton"] = new vector<double>( 2, 1.0 ); 


  // ... and shifts
  recoil_lat_shifts = new StrVecMap();
  tmu_lat_shifts = new StrVecMap();
  theta_lat_shifts = new StrVecMap();
  pT_lat_shifts = new StrVecMap();
  pZ_lat_shifts = new StrVecMap();
  q2_lat_shifts = new StrVecMap();
  enu_lat_shifts = new StrVecMap();
  for( StrVecMap::iterator it=lat_error_band_wgts->begin(); it!=lat_error_band_wgts->end(); ++it ){
    (*recoil_lat_shifts)[it->first] = new vector<double>( m_nUniverses, 0.0 );
    (*tmu_lat_shifts)[it->first] = new vector<double>( m_nUniverses, 0.0 );
    (*theta_lat_shifts)[it->first] = new vector<double>( m_nUniverses, 0.0 );
    (*pT_lat_shifts)[it->first] = new vector<double>( m_nUniverses, 0.0 );
    (*pZ_lat_shifts)[it->first] = new vector<double>( m_nUniverses, 0.0 );
    (*q2_lat_shifts)[it->first] = new vector<double>( m_nUniverses, 0.0 );
    (*enu_lat_shifts)[it->first] = new vector<double>( m_nUniverses, 0.0 );
  }

} //End of createLatErrorBandWgts() 


//=======================================================
// addVertErrorBands for MnvH1D, MnvH2D, MnvResponse
//=======================================================
void CCQENuUtils::addVertErrorBands( MnvH1D** h )
{

  if( vert_error_band_wgts==NULL ){
    createVertErrorBandWgts();
  }

  addVertErrorBands( h[kMC] );
  addVertErrorBands( h[kQE] );
  addVertErrorBands( h[kQENot] );
  addVertErrorBands( h[kQELike] );
  addVertErrorBands( h[kQELikeNot] );
  addVertErrorBands( h[kQELikeNot_NoPions] );
  addVertErrorBands( h[kQELikeNot_SingleNeutralPion] );
  addVertErrorBands( h[kQELikeNot_SingleChargedPion] );
  addVertErrorBands( h[kQELikeNot_MultiPion] );

}

void CCQENuUtils::addVertErrorBands( MnvH1D* h )
{

  for( StrVecMap::iterator it=vert_error_band_wgts->begin(); it!=vert_error_band_wgts->end(); ++it ){
    h->AddVertErrorBand( it->first, it->second->size() );
  }
}

void CCQENuUtils::addVertErrorBands( MnvH2D** h )
{

  if( vert_error_band_wgts==NULL ){
    createVertErrorBandWgts();
  }

  addVertErrorBands( h[kMC] );
  addVertErrorBands( h[kQE] );
  addVertErrorBands( h[kQENot] );
  addVertErrorBands( h[kQELike] );
  addVertErrorBands( h[kQELikeNot] );
  addVertErrorBands( h[kQELikeNot_NoPions] );
  addVertErrorBands( h[kQELikeNot_SingleNeutralPion] );
  addVertErrorBands( h[kQELikeNot_SingleChargedPion] );
  addVertErrorBands( h[kQELikeNot_MultiPion] );

}

void CCQENuUtils::addVertErrorBands( MnvH2D* h )
{

  for( StrVecMap::iterator it=vert_error_band_wgts->begin(); it!=vert_error_band_wgts->end(); ++it ){
    h->AddVertErrorBand( it->first, it->second->size() );
  } 
}

void CCQENuUtils::addVertErrorBands( MinervaUnfold::MnvResponse* response )
{

  if( vert_error_band_wgts==NULL ){
    createVertErrorBandWgts();
  }

  for( StrVecMap::iterator it=vert_error_band_wgts->begin(); it!=vert_error_band_wgts->end(); ++it ){
    response->AddVertErrorBand( it->first, it->second->size() );
  }

  
}

//=======================================================
// addLatErrorBands for MnvH1D, MnvH2D, MnvResponse
//=======================================================
void CCQENuUtils::addLatErrorBands( MnvH1D** h ){
  
  if( lat_error_band_wgts==NULL ){
    createLatErrorBandWgts();
  }
  
  addLatErrorBands( h[kMC] );
  addLatErrorBands( h[kQE] );
  addLatErrorBands( h[kQENot] );
  addLatErrorBands( h[kQELike] );
  addLatErrorBands( h[kQELikeNot] );
  addLatErrorBands( h[kQELikeNot_NoPions] );
  addLatErrorBands( h[kQELikeNot_SingleNeutralPion] );
  addLatErrorBands( h[kQELikeNot_SingleChargedPion] );
  addLatErrorBands( h[kQELikeNot_MultiPion] );
}

void CCQENuUtils::addLatErrorBands( MnvH1D* h ){

  for( StrVecMap::iterator it=lat_error_band_wgts->begin(); it!=lat_error_band_wgts->end(); ++it ){
    h->AddLatErrorBand( it->first, it->second->size() );
  }
}

void CCQENuUtils::addLatErrorBands( MnvH2D** h ){

  if( lat_error_band_wgts==NULL ){
    createLatErrorBandWgts();
  }

  addLatErrorBands( h[kMC] );
  addLatErrorBands( h[kQE] );
  addLatErrorBands( h[kQENot] );
  addLatErrorBands( h[kQELike] );
  addLatErrorBands( h[kQELikeNot] ); 
  addLatErrorBands( h[kQELikeNot_NoPions] );
  addLatErrorBands( h[kQELikeNot_SingleNeutralPion] );
  addLatErrorBands( h[kQELikeNot_SingleChargedPion] );
  addLatErrorBands( h[kQELikeNot_MultiPion] );

}

void CCQENuUtils::addLatErrorBands( MnvH2D* h ){

  for( StrVecMap::iterator it=lat_error_band_wgts->begin(); it!=lat_error_band_wgts->end(); ++it ){
    h->AddLatErrorBand( it->first, it->second->size() );
  }
}

void CCQENuUtils::addLatErrorBands( MinervaUnfold::MnvResponse* response ){

  if( lat_error_band_wgts==NULL ){
    createLatErrorBandWgts();
  }


  for( StrVecMap::iterator it=lat_error_band_wgts->begin(); it!=lat_error_band_wgts->end(); ++it ){
    response->AddLatErrorBand( it->first, it->second->size() );
  }

}

void CCQENuUtils::fillVertErrorBands( MnvH1D** h, double cvval, CCQENuTruth* event ){

  fillVertErrorBands( h[kMC], cvval, event );

  if( cutter->passTrueCCQE( event ) ){ 
    fillVertErrorBands( h[kQE], cvval, event );
  } else {
    fillVertErrorBands( h[kQENot], cvval, event );
  }
  if( cutter->passTrueCCQELike( event ) ){ 
    fillVertErrorBands( h[kQELike], cvval, event );
  } else {

    //Single pion categories
    if(!cutter->passTruePion( event ))fillVertErrorBands( h[kQELikeNot_NoPions], cvval, event );
    if(cutter->passTrueSingleNeutralPion( event ))fillVertErrorBands( h[kQELikeNot_SingleNeutralPion], cvval, event );
    if(cutter->passTrueSingleChargedPion( event ))fillVertErrorBands( h[kQELikeNot_SingleChargedPion], cvval, event );
    if(cutter->passTrueMultiPion( event ))fillVertErrorBands( h[kQELikeNot_MultiPion], cvval, event );
    
    

    fillVertErrorBands( h[kQELikeNot], cvval, event );
  }

}


void CCQENuUtils::fillVertErrorBands( MnvH1D** h, double cvval, CCQENuEvent* event ){
  fillVertErrorBands( h[kMC], cvval, event );

  if( cutter->passTrueCCQE( event ) ){ 
    fillVertErrorBands( h[kQE], cvval, event );
  } else {
    fillVertErrorBands( h[kQENot], cvval, event );
  }
  if( cutter->passTrueCCQELike( event ) ){ 
    fillVertErrorBands( h[kQELike], cvval, event );
  } else {
    //Single pion categories
    if(!cutter->passTruePion( event ))fillVertErrorBands( h[kQELikeNot_NoPions], cvval, event );
    if(cutter->passTrueSingleNeutralPion( event ))fillVertErrorBands( h[kQELikeNot_SingleNeutralPion], cvval, event );
    if(cutter->passTrueSingleChargedPion( event ))fillVertErrorBands( h[kQELikeNot_SingleChargedPion], cvval, event );
    if(cutter->passTrueMultiPion( event ))fillVertErrorBands( h[kQELikeNot_MultiPion], cvval, event );

    fillVertErrorBands( h[kQELikeNot], cvval, event );
  }

}

void CCQENuUtils::fillVertErrorBands( MnvH1D* h, double cvval, CCQENuTruth *event ){

  std::vector<std::string> names;
  names = h->GetVertErrorBandNames();
  for( unsigned int i=0; i<names.size(); ++i ){

    if( names[i]=="Flux" ) { 
      h->FillVertErrorBand( names[i], cvval, *(*vert_error_band_wgts)[names[i]], wgt_CV, frw->GetFluxCVWeight(event->mc_incomingE/1000.,event->mc_incoming));
    }
    else if ( names[i]=="Low_recoil_fits"){
      h->FillVertErrorBand( names[i], cvval, *(*vert_error_band_wgts)[names[i]], wgt_CV, CCQENuUtils::Get2p2hWeight( event , 0));
    }
    else if (names[i]=="RPA_HighQ2"){
      h->FillVertErrorBand( names[i], cvval, *(*vert_error_band_wgts)[names[i]], wgt_CV, CCQENuUtils::GetRPAWeight( event, 0 ));
    }
    else if (names[i]=="RPA_LowQ2"){
      h->FillVertErrorBand( names[i], cvval, *(*vert_error_band_wgts)[names[i]], wgt_CV, CCQENuUtils::GetRPAWeight( event, 0 ));
    } 
    else {
      h->FillVertErrorBand( names[i], cvval, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
  }
  
}
void CCQENuUtils::fillVertErrorBands( MnvH1D* h, double cvval, CCQENuEvent *event ){

  std::vector<std::string> names;
  names = h->GetVertErrorBandNames();
  for( unsigned int i=0; i<names.size(); ++i ){

    if( names[i]=="Flux" ) { 
      h->FillVertErrorBand( names[i], cvval, *(*vert_error_band_wgts)[names[i]], wgt_CV, frw->GetFluxCVWeight(event->mc_incomingE/1000.,event->mc_incoming));
    }
    else if ( names[i]=="Low_recoil_fits"){
      h->FillVertErrorBand( names[i], cvval, *(*vert_error_band_wgts)[names[i]], wgt_CV, CCQENuUtils::Get2p2hWeight( event , 0));
    }
    else if (names[i]=="RPA_HighQ2"){
      h->FillVertErrorBand( names[i], cvval, *(*vert_error_band_wgts)[names[i]], wgt_CV, CCQENuUtils::GetRPAWeight( event, 0 ));
    }
    else if (names[i]=="RPA_LowQ2"){
      h->FillVertErrorBand( names[i], cvval, *(*vert_error_band_wgts)[names[i]], wgt_CV, CCQENuUtils::GetRPAWeight( event, 0 ));
    } 
    //else if (names[i]=="GENIE_MFP_N"){
    //std::cout<<"Filling GENIE_MFP_N! cvval "<<cvval<<" wgt_CV "<<wgt_CV<<std::endl;
    //h->FillVertErrorBand( names[i], 1., *(*vert_error_band_wgts)[names[i]], wgt_CV );
    //}
    else {
      h->FillVertErrorBand( names[i], cvval, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
  }
  
}

void CCQENuUtils::fillVertErrorBands( MnvH2D** h, double cvval_x, double cvval_y, CCQENuTruth* event ){

  fillVertErrorBands( h[kMC], cvval_x, cvval_y, event );

  if( cutter->passTrueCCQE( event ) ){ 
    fillVertErrorBands( h[kQE], cvval_x, cvval_y, event );
  } else {
    fillVertErrorBands( h[kQENot], cvval_x, cvval_y, event );
  }
  if( cutter->passTrueCCQELike( event ) ){ 
    fillVertErrorBands( h[kQELike], cvval_x, cvval_y, event );
  } else {
    if(!cutter->passTruePion( event ))fillVertErrorBands( h[kQELikeNot_NoPions], cvval_x, cvval_y, event );
    if(cutter->passTrueSingleNeutralPion( event ))fillVertErrorBands( h[kQELikeNot_SingleNeutralPion], cvval_x, cvval_y, event );
    if(cutter->passTrueSingleChargedPion( event ))fillVertErrorBands( h[kQELikeNot_SingleChargedPion], cvval_x, cvval_y, event );
    if(cutter->passTrueMultiPion( event ))fillVertErrorBands( h[kQELikeNot_MultiPion], cvval_x, cvval_y, event );


    fillVertErrorBands( h[kQELikeNot], cvval_x, cvval_y, event );
  }

}

void CCQENuUtils::fillVertErrorBands( MnvH2D** h, double cvval_x, double cvval_y, CCQENuEvent* event ){

  fillVertErrorBands( h[kMC], cvval_x, cvval_y, event );

  if( cutter->passTrueCCQE( event ) ){
    fillVertErrorBands( h[kQE], cvval_x, cvval_y, event );
  } else {
    fillVertErrorBands( h[kQENot], cvval_x, cvval_y, event );
  }
  if( cutter->passTrueCCQELike( event ) ){
    fillVertErrorBands( h[kQELike], cvval_x, cvval_y, event );
  } else {
    if(!cutter->passTruePion( event ))fillVertErrorBands( h[kQELikeNot_NoPions], cvval_x, cvval_y, event );
    if(cutter->passTrueSingleNeutralPion( event ))fillVertErrorBands( h[kQELikeNot_SingleNeutralPion], cvval_x, cvval_y, event );
    if(cutter->passTrueSingleChargedPion( event ))fillVertErrorBands( h[kQELikeNot_SingleChargedPion], cvval_x, cvval_y, event );
    if(cutter->passTrueMultiPion( event ))fillVertErrorBands( h[kQELikeNot_MultiPion], cvval_x, cvval_y, event );

    fillVertErrorBands( h[kQELikeNot], cvval_x, cvval_y, event );
  }
  
}

void CCQENuUtils::fillVertErrorBands( MnvH2D* h, double cvval_x, double cvval_y, CCQENuTruth *event ){

  std::vector<std::string> names;
  names = h->GetVertErrorBandNames();
  for( unsigned int i=0; i<names.size(); ++i ){

    if( names[i]=="Flux" ) { 
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV, frw->GetFluxCVWeight(event->mc_incomingE/1000.,event->mc_incoming));
    } 
    else if ( names[i]=="Low_recoil_fits"){
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV, CCQENuUtils::Get2p2hWeight( event , 0));
    }
    else if (names[i]=="RPA_HighQ2"){
//    std::cout<<"Filling GENIE_CCQEPauliSupViaK! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV, CCQENuUtils::GetRPAWeight( event, 0 ));
    }
    else if (names[i]=="RPA_LowQ2"){
//    std::cout<<"Filling RPA_LowQ2! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV, CCQENuUtils::GetRPAWeight( event, 0 ));
    }/*
      else if (names[i]=="GENIE_CCQEPauliSupViaK"){
      std::cout<<"Filling GENIE_CCQEPauliSupViaK! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
    else if (names[i]=="GENIE_EtaNCEL"){
      std::cout<<"Filling GENIE_EtaNCEL! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
    else if (names[i]=="GENIE_MaCCQEshape"){
      std::cout<<"Filling GENIE_MaCCQEshape! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
    else if (names[i]=="GENIE_MaNCEL"){
      std::cout<<"Filling GENIE_MFP_N! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
    else if (names[i]=="GENIE_MaRES"){
      std::cout<<"Filling GENIE_MaRES! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
    else if (names[i]=="GENIE_MvRES"){
      std::cout<<"Filling GENIE_MvRES! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
    else if (names[i]=="GENIE_NormCCQE"){
      std::cout<<"Filling GENIE_NormCCQE! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
    else if (names[i]=="GENIE_NormDISCC"){
      std::cout<<"Filling GENIE_NormDISCC! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
    else if (names[i]=="GENIE_NormNCRES"){
      std::cout<<"Filling GENIE_NormNCRES! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
    else if (names[i]=="GENIE_Rvn1pi"){
      std::cout<<"GENIE_Rvn1pi! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
    else if (names[i]=="GENIE_Rvn2pi"){
      std::cout<<"Filling GENIE_Rvn2pi! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
    else if (names[i]=="GENIE_Rvp1pi"){
      std::cout<<"Filling GENIE_Rvp1pi! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
    else if (names[i]=="GENIE_Rvp2pi"){
      std::cout<<"Filling GENIE_Rvp2pi! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
    else if (names[i]=="GENIE_VecFFCCQEshape"){
      std::cout<<"Filling GENIE_VecFFCCQEshape! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
    else if (names[i]=="GENIE_AhtBY"){
      std::cout<<"Filling GENIE_AhtBY! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
    else if (names[i]=="GENIE_BhtBY"){
      std::cout<<"Filling GENIE_BhtBY! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
    else if (names[i]=="GENIE_CV1uBY"){
      std::cout<<"Filling GENIE_CV1uBY! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
    else if (names[i]=="GENIE_CV2uBY"){
      std::cout<<"Filling GENIE_CV2uBY! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
    else if (names[i]=="GENIE_MFP_N"){
      std::cout<<"Filling GENIE_MFP_N! cvval_x "<<cvval_x<<" cvval_y "<<cvval_y<<" wgt_CV "<<wgt_CV<<std::endl;
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }*/
    else {
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
  }
  
}
void CCQENuUtils::fillVertErrorBands( MnvH2D* h, double cvval_x, double cvval_y, CCQENuEvent *event ){
  std::vector<std::string> names;
  names = h->GetVertErrorBandNames();
  for( unsigned int i=0; i<names.size(); ++i ){

    if( names[i]=="Flux" ) { 
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV, frw->GetFluxCVWeight(event->mc_incomingE/1000.,event->mc_incoming));
    }
    else if ( names[i]=="Low_recoil_fits"){
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV, CCQENuUtils::Get2p2hWeight( event , 0));
    }
    else if (names[i]=="RPA_HighQ2"){
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV, CCQENuUtils::GetRPAWeight( event, 0 ));
    }
    else if (names[i]=="RPA_LowQ2"){
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV, CCQENuUtils::GetRPAWeight( event, 0 ));
    }
    else {
      h->FillVertErrorBand( names[i], cvval_x, cvval_y, *(*vert_error_band_wgts)[names[i]], wgt_CV );
    }
  }
  
}

void CCQENuUtils::fillVertErrorBands( MinervaUnfold::MnvResponse* response, double cvval_x, double cvval_y, double cvval_xtrue, double cvval_ytrue,  CCQENuEvent* event ){
  if( cutter->passTrueCCQELike( event ) ){

    for( StrVecMap::iterator it=vert_error_band_wgts->begin(); it!=vert_error_band_wgts->end(); ++it ){
      if( it->first=="Flux"){
	response->FillVertErrorBand( it->first, cvval_x, cvval_y, cvval_xtrue, cvval_ytrue, *(*vert_error_band_wgts)[it->first], wgt_CV, frw->GetFluxCVWeight(event->mc_incomingE/1000.,event->mc_incoming));
      } 
      else if ( it->first=="Low_recoil_fits"){
       	response->FillVertErrorBand( it->first, cvval_x, cvval_y, cvval_xtrue, cvval_ytrue, *(*vert_error_band_wgts)[it->first], wgt_CV, CCQENuUtils::Get2p2hWeight( event , 0));
      }
      else if (it->first=="RPA_HighQ2"){
       	response->FillVertErrorBand( it->first, cvval_x, cvval_y, cvval_xtrue, cvval_ytrue, *(*vert_error_band_wgts)[it->first], wgt_CV, CCQENuUtils::GetRPAWeight( event, 0 ));
      }
      else if (it->first=="RPA_LowQ2"){
       	response->FillVertErrorBand( it->first, cvval_x, cvval_y, cvval_xtrue, cvval_ytrue, *(*vert_error_band_wgts)[it->first], wgt_CV, CCQENuUtils::GetRPAWeight( event, 0 ));
      }
      else {
	response->FillVertErrorBand( it->first, cvval_x, cvval_y, cvval_xtrue, cvval_ytrue, *(*vert_error_band_wgts)[it->first], wgt_CV );
      }
    }
  }
}

//=======================================================
// fillLatErrorBands for MnvH1D, MnvH2D, MnvResponse
//=======================================================
void CCQENuUtils::fillLatErrorBands( MnvH1D** h, string var, double cvval, CCQENuEvent* event, bool passcv, bool doShift ){

  fillLatErrorBands( h[kMC], var, cvval, passcv, doShift );

  if( cutter->passTrueCCQE( event ) ){ 
    fillLatErrorBands( h[kQE], var, cvval, passcv, doShift );
  } else {
    fillLatErrorBands( h[kQENot], var, cvval, passcv, doShift );
  }
  if( cutter->passTrueCCQELike( event ) ){ 
    fillLatErrorBands( h[kQELike], var, cvval, passcv, doShift );
  } else {
    if(!cutter->passTruePion( event ))fillLatErrorBands( h[kQELikeNot_NoPions], var, cvval, passcv, doShift );
    if(cutter->passTrueSingleNeutralPion( event ))fillLatErrorBands( h[kQELikeNot_SingleNeutralPion], var, cvval, passcv, doShift );
    if(cutter->passTrueSingleChargedPion( event ))fillLatErrorBands( h[kQELikeNot_SingleChargedPion], var, cvval, passcv, doShift );
    if(cutter->passTrueMultiPion( event ))fillLatErrorBands( h[kQELikeNot_MultiPion], var, cvval, passcv, doShift );

    fillLatErrorBands( h[kQELikeNot], var, cvval, passcv, doShift );
  }

}

void CCQENuUtils::fillLatErrorBands( MnvH1D* h, string var, double cvval, bool passcv, bool doShift ){

  for( StrVecMap::iterator it=lat_error_band_wgts->begin(); it!=lat_error_band_wgts->end(); ++it ){
    if(doShift){
      if( var=="tmu" ){
	h->FillLatErrorBand( it->first, cvval, & ((*tmu_lat_shifts)[it->first]->at(0)), wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      } else if( var=="theta" ){
	h->FillLatErrorBand( it->first, cvval, & ((*theta_lat_shifts)[it->first]->at(0)), wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      } else if( var=="pT" ){
        h->FillLatErrorBand( it->first, cvval, & ((*pT_lat_shifts)[it->first]->at(0)), wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      } else if( var=="pZ" ){
        h->FillLatErrorBand( it->first, cvval, & ((*pZ_lat_shifts)[it->first]->at(0)), wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      } else if( var=="recoil" ){
        h->FillLatErrorBand( it->first, cvval, & ((*recoil_lat_shifts)[it->first]->at(0)), wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      }
    }
    else{
      if( var=="tmu" ){
	h->FillLatErrorBand( it->first, cvval, 0.0, wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      } else if( var=="theta" ){
	h->FillLatErrorBand( it->first, cvval, 0.0, wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      } else if( var=="pT" ){
        h->FillLatErrorBand( it->first, cvval, 0.0, wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      } else if( var=="pZ" ){
        h->FillLatErrorBand( it->first, cvval, 0.0, wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      } else if( var=="recoil" ){
        h->FillLatErrorBand( it->first, cvval, 0.0, wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      }
    }
  }
  

}

void CCQENuUtils::fillLatErrorBands( MnvH2D** h, string var_x, string var_y, double cvval_x, double cvval_y, CCQENuEvent* event, bool passcv, bool doShift ){

  fillLatErrorBands( h[kMC], var_x, var_y, cvval_x, cvval_y, passcv, doShift );

  if( cutter->passTrueCCQE( event ) ){ 
    fillLatErrorBands( h[kQE], var_x, var_y, cvval_x, cvval_y, passcv, doShift );
  } else {
    fillLatErrorBands( h[kQENot], var_x, var_y, cvval_x, cvval_y, passcv, doShift );
  }
  if( cutter->passTrueCCQELike( event ) ){ 
    fillLatErrorBands( h[kQELike], var_x, var_y, cvval_x, cvval_y, passcv, doShift );
  } else {
    if(!cutter->passTruePion( event ))fillLatErrorBands( h[kQELikeNot_NoPions], var_x, var_y, cvval_x, cvval_y, passcv, doShift );
    if(cutter->passTrueSingleNeutralPion( event ))fillLatErrorBands( h[kQELikeNot_SingleNeutralPion], var_x, var_y, cvval_x, cvval_y, passcv, doShift );
    if(cutter->passTrueSingleChargedPion( event ))fillLatErrorBands( h[kQELikeNot_SingleChargedPion], var_x, var_y, cvval_x, cvval_y, passcv, doShift );
    if(cutter->passTrueMultiPion( event ))fillLatErrorBands( h[kQELikeNot_MultiPion], var_x, var_y, cvval_x, cvval_y, passcv, doShift );

    fillLatErrorBands( h[kQELikeNot], var_x, var_y, cvval_x, cvval_y, passcv, doShift );

  }

}

void CCQENuUtils::fillLatErrorBands( MnvH2D* h, string var_x, string var_y, double cvval_x, double cvval_y, bool passcv , bool doShift){

  for( StrVecMap::iterator it=lat_error_band_wgts->begin(); it!=lat_error_band_wgts->end(); ++it ){
    if(doShift){
      if( var_x=="tmu" && var_y=="theta" ){
	h->FillLatErrorBand( it->first, cvval_x, cvval_y, & ((*tmu_lat_shifts)[it->first]->at(0)), & ((*theta_lat_shifts)[it->first]->at(0)), wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      }
      if( var_x=="pZ" && var_y=="pT" ){

        /*
        cout << ((*pZ_lat_shifts)[it->first]->at(0)) << endl;
        cout << ((*pT_lat_shifts)[it->first]->at(0)) << endl;
        cout << wgt_CV << endl;
        cout << passcv << endl;
        cout << ((*lat_error_band_wgts)[it->first]->at(0)) << endl;
        */

	h->FillLatErrorBand( it->first, cvval_x, cvval_y, & ((*pZ_lat_shifts)[it->first]->at(0)), & ((*pT_lat_shifts)[it->first]->at(0)), wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      }
      if( var_x=="enu" && var_y=="pT" ){
	h->FillLatErrorBand( it->first, cvval_x, cvval_y, & ((*enu_lat_shifts)[it->first]->at(0)), & ((*pT_lat_shifts)[it->first]->at(0)), wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      }
      if( var_x=="q2" && var_y=="pT" ){

        /*
        cout << "((*q2_lat_shifts)[it->first]->at(0)) = " << ((*q2_lat_shifts)[it->first]->at(0)) << endl;
        cout << "((*pT_lat_shifts)[it->first]->at(0)) = " << ((*pT_lat_shifts)[it->first]->at(0)) << endl;
        cout << "wgt_CV = " << wgt_CV << endl;
        cout << "passcv = " << passcv << endl;
        cout << "((*lat_error_band_wgts)[it->first]->at(0)) = " << ((*lat_error_band_wgts)[it->first]->at(0)) << endl;
        */        

	h->FillLatErrorBand( it->first, cvval_x, cvval_y, & ((*q2_lat_shifts)[it->first]->at(0)), & ((*pT_lat_shifts)[it->first]->at(0)), wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      }
    }
    else{
      double tmp_val = 0.0;
      if( var_x=="tmu" && var_y=="theta" ){
	h->FillLatErrorBand( it->first, cvval_x, cvval_y, &tmp_val, &tmp_val, wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      }
      if( var_x=="pZ" && var_y=="pT" ){
	h->FillLatErrorBand( it->first, cvval_x, cvval_y, &tmp_val, &tmp_val, wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      }
      if( var_x=="enu" && var_y=="pT" ){
	h->FillLatErrorBand( it->first, cvval_x, cvval_y, &tmp_val, &tmp_val, wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      }
      if( var_x=="q2" && var_y=="pT" ){
	h->FillLatErrorBand( it->first, cvval_x, cvval_y, &tmp_val, &tmp_val, wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      }
    }
  }
}

void CCQENuUtils::fillLatErrorBands( MinervaUnfold::MnvResponse* response, string var_x, string var_y, double cvval_x, double cvval_y, double cvval_xtrue, double cvval_ytrue, CCQENuEvent* event, bool passcv ){

  if( cutter->passTrueCCQELike( event ) ){
    for( StrVecMap::iterator it=lat_error_band_wgts->begin(); it!=lat_error_band_wgts->end(); ++it ){
      
      if( var_x=="tmu" && var_y=="theta" ){ 
	response->FillLatErrorBand( it->first, cvval_x, cvval_y, cvval_xtrue, cvval_ytrue, & ((*tmu_lat_shifts)[it->first]->at(0)), & ((*theta_lat_shifts)[it->first]->at(0)), wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      }
      
      if( var_x=="pZ" && var_y=="pT" ){
	response->FillLatErrorBand( it->first, cvval_x, cvval_y, cvval_xtrue, cvval_ytrue, & ((*pZ_lat_shifts)[it->first]->at(0)), & ((*pT_lat_shifts)[it->first]->at(0)), wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      }
      
      if( var_x=="enu" && var_y=="pT" ){
	response->FillLatErrorBand( it->first, cvval_x, cvval_y, cvval_xtrue, cvval_ytrue, & ((*enu_lat_shifts)[it->first]->at(0)), & ((*pT_lat_shifts)[it->first]->at(0)), wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      }
      
      if( var_x=="q2" && var_y=="pT" ){
	response->FillLatErrorBand( it->first, cvval_x, cvval_y, cvval_xtrue, cvval_ytrue, & ((*q2_lat_shifts)[it->first]->at(0)), & ((*pT_lat_shifts)[it->first]->at(0)), wgt_CV, passcv, & ((*lat_error_band_wgts)[it->first]->at(0)) );
      }
    }
  }
}

void CCQENuUtils::fillHadronReweightVertErrorBandWgts(Long64_t entry_number, bool usetruth, double wgt){
  InelXSecWeights weights = mnvHadronReweight->getWeights(entry_number, usetruth);
  //double wgt = 1;
  //HadronReweight 2.0:
  (*vert_error_band_wgts)["Reweight_Pion"]->at(0) = weights.weightDown[211]*wgt;
  (*vert_error_band_wgts)["Reweight_Pion"]->at(1) = weights.weightUp[211]*wgt;
  (*vert_error_band_wgts)["Reweight_Proton"]->at(0) = weights.weightDown[2212]*wgt;
  (*vert_error_band_wgts)["Reweight_Proton"]->at(1) = weights.weightUp[2212]*wgt;
  (*vert_error_band_wgts)["Reweight_Neutron"]->at(0) = weights.weightDown[2112]*wgt;
  (*vert_error_band_wgts)["Reweight_Neutron"]->at(1) = weights.weightUp[2112]*wgt;
  /*(*vert_error_band_wgts)["Reweight_Pion"]->at(0) = weights.pionTotalWeightDown*wgt;
  (*vert_error_band_wgts)["Reweight_Pion"]->at(1) = weights.pionTotalWeightUp*wgt;
  (*vert_error_band_wgts)["Reweight_Proton"]->at(0) = weights.protonTotalWeightDown*wgt;
  (*vert_error_band_wgts)["Reweight_Proton"]->at(1) = weights.protonTotalWeightUp*wgt;
  (*vert_error_band_wgts)["Reweight_Neutron"]->at(0) = weights.neutronTotalWeightDown*wgt;
  (*vert_error_band_wgts)["Reweight_Neutron"]->at(1) = weights.neutronTotalWeightUp*wgt;*/
  /*(*vert_error_band_wgts)["Reweight_Pion"]->at(0) = weights.pionTotalWeightDown;
  (*vert_error_band_wgts)["Reweight_Pion"]->at(1) = weights.pionTotalWeightUp;
  (*vert_error_band_wgts)["Reweight_Proton"]->at(0) = weights.protonTotalWeightDown;
  (*vert_error_band_wgts)["Reweight_Proton"]->at(1) = weights.protonTotalWeightUp;
  (*vert_error_band_wgts)["Reweight_Neutron"]->at(0) = weights.neutronTotalWeightDown;
  (*vert_error_band_wgts)["Reweight_Neutron"]->at(1) = weights.neutronTotalWeightUp;*/
}

//==============================================================
// Functions to get the weights of each universe
//==============================================================
void CCQENuUtils::fillVertErrorBandWgts( const CCQENuTruth* truth )
{
  CCQENuTruth *tmp_truth = (CCQENuTruth*)truth;//Guh, I don't want to make 4 functions so cast here.

  if(removeSignalError && cutter->passTrueCCQELike( tmp_truth )){//need to be remove signal error AND signal else you just apply weights as normal.

    if( vert_error_band_wgts==NULL ){
      throw std::runtime_error( "Error band weights map hasn't been created !" );
    }
    //Apply flux weights
    std::vector<double> totalFluxErrorWeights; 
    for( int iUnv=0; iUnv<m_nUniverses; ++iUnv ) { 
      totalFluxErrorWeights.push_back( frw->GetFluxErrorWeight(truth->mc_incomingE/1000.,truth->mc_incoming,iUnv));
    }
    (*vert_error_band_wgts)["Flux"]->assign( totalFluxErrorWeights.begin(), totalFluxErrorWeights.end() ); 

    // Apply HadronReweight weights 
    // int entry_number = truth->fChain->GetReadEntry();
    Long64_t entry_number = truth->fChain->GetReadEntry();
    //  double wgt = truth->wgt;
    double wgt = wgt_CV_truth;
    fillHadronReweightVertErrorBandWgts(entry_number, true, wgt);

    // Apply RPA weights
    (*vert_error_band_wgts)["RPA_HighQ2"]->at(0) = GetRPAWeight(tmp_truth,0);
    (*vert_error_band_wgts)["RPA_HighQ2"]->at(1) = GetRPAWeight(tmp_truth,0);

    (*vert_error_band_wgts)["RPA_LowQ2"]->at(0) = GetRPAWeight(tmp_truth,0);
    (*vert_error_band_wgts)["RPA_LowQ2"]->at(1) = GetRPAWeight(tmp_truth,0);

    // Apply 2p2h low recoil fit weights
    (*vert_error_band_wgts)["Low_recoil_fits"]->at(0) = Get2p2hWeight(tmp_truth,0);
    (*vert_error_band_wgts)["Low_recoil_fits"]->at(1) = Get2p2hWeight(tmp_truth,0);
    (*vert_error_band_wgts)["Low_recoil_fits"]->at(2) = Get2p2hWeight(tmp_truth,0);

    // Apply Target Mass weights 
    (*vert_error_band_wgts)["Target_Mass"]->at(0) = 1.0 * wgt;  
    (*vert_error_band_wgts)["Target_Mass"]->at(1) = 1.0 * wgt;  

    // Apply weights for Proton Tracking Efficiency 
    (*vert_error_band_wgts)["Proton_TrackEff"]->at(0) = 1.0 * wgt;  
    (*vert_error_band_wgts)["Proton_TrackEff"]->at(1) = 1.0 * wgt;  

    // Apply Michel Efficiency weights  
    if(truth->truth_reco_has_michel_electron){
      (*vert_error_band_wgts)["Michel_Efficiency"]->at(0) = michel_weights.at(0)*wgt;
      (*vert_error_band_wgts)["Michel_Efficiency"]->at(1) = michel_weights.at(1)*wgt;
    } else {
      // If there is no Michel tag (and with that, I mean a tag from the Michel Tool
      // applied to the reconstructed part), do not apply any weight.
      (*vert_error_band_wgts)["Michel_Efficiency"]->at(0) = 1 * wgt;
      (*vert_error_band_wgts)["Michel_Efficiency"]->at(1) = 1 * wgt;
    }

    // Apply GENIE weights 
    if( ! use_genie_split ){
      //Below 2 GENIE variable is missing from Dan's processing on 10/20/2015, but he should add them back in (update AnaTuple.cpp) 
      //(*vert_error_band_wgts)["GENIE"]->assign( truth->mc_wgt_GENIE, truth->mc_wgt_GENIE + m_nUniverses );
    } else {
      (*vert_error_band_wgts)["GENIE_AGKYxF1pi"]->at(0) = 1.0;
      (*vert_error_band_wgts)["GENIE_AGKYxF1pi"]->at(1) = 1.0;
      (*vert_error_band_wgts)["GENIE_CCQEPauliSupViaKF"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_CCQEPauliSupViaKF"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_EtaNCEL"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_EtaNCEL"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrAbs_N"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrAbs_N"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrAbs_pi"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrAbs_pi"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrCEx_N"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrCEx_N"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrCEx_pi"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrCEx_pi"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrElas_N"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrElas_N"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrElas_pi"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrElas_pi"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrInel_N"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrInel_N"]->at(1) = 1.0; 
      // (*vert_error_band_wgts)["GENIE_FrInel_pi"]->at(0) = truth->truth_genie_wgt_FrInel_pi[2];
      // (*vert_error_band_wgts)["GENIE_FrInel_pi"]->at(1) = truth->truth_genie_wgt_FrInel_pi[4];
      (*vert_error_band_wgts)["GENIE_FrPiProd_N"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrPiProd_N"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrPiProd_pi"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrPiProd_pi"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_MFP_N"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_MFP_N"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_MFP_pi"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_MFP_pi"]->at(1) = 1.0; 
      //(*vert_error_band_wgts)["GENIE_MaCCQE"]->at(0) = truth->truth_genie_wgt_MaCCQE[2];
      //(*vert_error_band_wgts)["GENIE_MaCCQE"]->at(1) = truth->truth_genie_wgt_MaCCQE[4];
      (*vert_error_band_wgts)["GENIE_MaCCQEshape"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_MaCCQEshape"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_MaNCEL"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_MaNCEL"]->at(1) = 1.0; 
      //(*vert_error_band_wgts)["GENIE_MaRES"]->at(0) = truth->truth_genie_wgt_MaRES[2];
      //(*vert_error_band_wgts)["GENIE_MaRES"]->at(1) = truth->truth_genie_wgt_MaRES[4];
      //(*vert_error_band_wgts)["GENIE_MvRES"]->at(0) = truth->truth_genie_wgt_MvRES[2];
      //(*vert_error_band_wgts)["GENIE_MvRES"]->at(1) = truth->truth_genie_wgt_MvRES[4];
      (*vert_error_band_wgts)["GENIE_NormCCQE"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_NormCCQE"]->at(1) = 1.0; 
      //(*vert_error_band_wgts)["GENIE_NormCCRES"]->at(0) = truth->truth_genie_wgt_NormCCRES[2];
      //(*vert_error_band_wgts)["GENIE_NormCCRES"]->at(1) = truth->truth_genie_wgt_NormCCRES[4];
      (*vert_error_band_wgts)["GENIE_NormDISCC"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_NormDISCC"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_NormNCRES"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_NormNCRES"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_RDecBR1gamma"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_RDecBR1gamma"]->at(1) = 1.0; 
      //    (*vert_error_band_wgts)["GENIE_Rvn1pi"]->at(0) = truth->truth_genie_wgt_Rvn1pi[2];
      //    (*vert_error_band_wgts)["GENIE_Rvn1pi"]->at(1) = truth->truth_genie_wgt_Rvn1pi[4];
      (*vert_error_band_wgts)["GENIE_Rvn2pi"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_Rvn2pi"]->at(1) = 1.0; 
      //    (*vert_error_band_wgts)["GENIE_Rvp1pi"]->at(0) = truth->truth_genie_wgt_Rvp1pi[2];
      //    (*vert_error_band_wgts)["GENIE_Rvp1pi"]->at(1) = truth->truth_genie_wgt_Rvp1pi[4];
      (*vert_error_band_wgts)["GENIE_Rvp2pi"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_Rvp2pi"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_Theta_Delta2Npi"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_Theta_Delta2Npi"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_VecFFCCQEshape"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_VecFFCCQEshape"]->at(1) = 1.0;
      (*vert_error_band_wgts)["GENIE_AhtBY"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_AhtBY"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_BhtBY"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_BhtBY"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_CV1uBY"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_CV1uBY"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_CV2uBY"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_CV2uBY"]->at(1) = 1.0; 
    
      if ( doGenieTuning ){
	//Bools checking CCRes and NonRes1pi
	bool isGenieNonRes1pi = truth->truth_genie_wgt_Rvn1pi[2] < 1.0 || truth->truth_genie_wgt_Rvp1pi[2] < 1.0;
	//      bool isGenieCCRes = truth->mc_current == 1 && truth->mc_intType == 2;
	/*//It was decided the resonant pion modifications were too much when used with the nonresonant pion modification
	// CC Resonance errors from deuterium and electroproduction data fits
	if ( isGenieCCRes ){

	(*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(0) =  (1.0 + fabs( deuteriumMaRes - deuteriumMaRes1sig  - genieMaRes ) * ( truth->truth_genie_wgt_MaRES[2] - 1.0 ) / genieMaRes1sig) / (1.0 + fabs( deuteriumMaRes - genieMaRes ) * ( truth->truth_genie_wgt_MaRES[2] - 1.0 ) / genieMaRes1sig);
	(*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(1) =  (1.0 + fabs( deuteriumMaRes + deuteriumMaRes1sig  - genieMaRes ) * ( truth->truth_genie_wgt_MaRES[4] - 1.0 ) / genieMaRes1sig) / (1.0 + fabs( deuteriumMaRes - genieMaRes ) * ( truth->truth_genie_wgt_MaRES[4] - 1.0 ) / genieMaRes1sig);
	(*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(0) = 1.0 + fabs(genieMvRes - electroProdMvRes1sig - genieMvRes ) * ( truth->truth_genie_wgt_MvRES[2] - 1.0 ) / genieMvRes1sig;
	(*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(1) = 1.0 + fabs(genieMvRes + electroProdMvRes1sig - genieMvRes ) * ( truth->truth_genie_wgt_MvRES[4] - 1.0 ) / genieMvRes1sig;

	(*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(0) =  1-deuteriumResNorm1sig ;
	(*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(1) =  1+deuteriumResNorm1sig ;
	}
	else{
	(*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(0) =  1.0 ;
	(*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(1) =  1.0 ;
	(*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(0) =  1.0 ;
	(*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(1) =  1.0 ;
	(*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(0) =  1.0 ;
	(*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(1) =  1.0 ;
	}
	*/
	// Non-resonant 1pi production normalization errors from deuterium fit
	if ( isGenieNonRes1pi ){
	  (*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(0) = 1.0; 
	  (*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(1) = 1.0; 
	  (*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(0) = 1.0; 
	  (*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(1) = 1.0; 
	}
	else{
	  (*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(0) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(1) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(0) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(1) =  1.0 ;

	}
      }
    
      else{//give the unmodified weights instead
	(*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(0) = 1.0;  
	(*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(1) = 1.0;  
	(*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(0) = 1.0;  
	(*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(1) = 1.0;  
	(*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(0) = 1.0;  
	(*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(1) = 1.0;  
	(*vert_error_band_wgts)[ "GENIE_Rvn1pi"    ]->at(0) = 1.0;  
	(*vert_error_band_wgts)[ "GENIE_Rvn1pi"    ]->at(1) = 1.0;  
	(*vert_error_band_wgts)[ "GENIE_Rvp1pi"    ]->at(0) = 1.0;  
	(*vert_error_band_wgts)[ "GENIE_Rvp1pi"    ]->at(1) = 1.0;  
      }
    
    }
  }//if removeSignalError AND signal
  else{
    if( vert_error_band_wgts==NULL ){
      throw std::runtime_error( "Error band weights map hasn't been created !" );
    }
    //Apply flux weights
    std::vector<double> totalFluxErrorWeights; 
    for( int iUnv=0; iUnv<m_nUniverses; ++iUnv ) { 
      totalFluxErrorWeights.push_back( frw->GetFluxErrorWeight(truth->mc_incomingE/1000.,truth->mc_incoming,iUnv));
    }
    (*vert_error_band_wgts)["Flux"]->assign( totalFluxErrorWeights.begin(), totalFluxErrorWeights.end() ); 

    // Apply HadronReweight weights 
    // int entry_number = truth->fChain->GetReadEntry();
    Long64_t entry_number = truth->fChain->GetReadEntry();
    //  double wgt = truth->wgt;
    double wgt = wgt_CV_truth;
    fillHadronReweightVertErrorBandWgts(entry_number, true, wgt);

    // Apply RPA weights
    (*vert_error_band_wgts)["RPA_HighQ2"]->at(0) = GetRPAWeight(tmp_truth,1);
    (*vert_error_band_wgts)["RPA_HighQ2"]->at(1) = GetRPAWeight(tmp_truth,2);

    (*vert_error_band_wgts)["RPA_LowQ2"]->at(0) = GetRPAWeight(tmp_truth,3);
    (*vert_error_band_wgts)["RPA_LowQ2"]->at(1) = GetRPAWeight(tmp_truth,4);


    // Apply 2p2h low recoil fit weights
    (*vert_error_band_wgts)["Low_recoil_fits"]->at(0) = Get2p2hWeight(tmp_truth,1);
    (*vert_error_band_wgts)["Low_recoil_fits"]->at(1) = Get2p2hWeight(tmp_truth,2);
    (*vert_error_band_wgts)["Low_recoil_fits"]->at(2) = Get2p2hWeight(tmp_truth,3);

    // Apply Target Mass weights 
    (*vert_error_band_wgts)["Target_Mass"]->at(0) = 1.0 * wgt;  
    (*vert_error_band_wgts)["Target_Mass"]->at(1) = 1.0 * wgt;  

    // Apply weights for Proton Tracking Efficiency 
    (*vert_error_band_wgts)["Proton_TrackEff"]->at(0) = 1.0 * wgt;  
    (*vert_error_band_wgts)["Proton_TrackEff"]->at(1) = 1.0 * wgt;  

    // Apply Michel Efficiency weights  
    if(truth->truth_reco_has_michel_electron){
      (*vert_error_band_wgts)["Michel_Efficiency"]->at(0) = michel_weights.at(0)*wgt;
      (*vert_error_band_wgts)["Michel_Efficiency"]->at(1) = michel_weights.at(1)*wgt;
    } else {
      // If there is no Michel tag (and with that, I mean a tag from the Michel Tool
      // applied to the reconstructed part), do not apply any weight.
      (*vert_error_band_wgts)["Michel_Efficiency"]->at(0) = 1 * wgt;
      (*vert_error_band_wgts)["Michel_Efficiency"]->at(1) = 1 * wgt;
    }

    // Apply GENIE weights 
    if( ! use_genie_split ){
      //Below 2 GENIE variable is missing from Dan's processing on 10/20/2015, but he should add them back in (update AnaTuple.cpp) 
      //(*vert_error_band_wgts)["GENIE"]->assign( truth->mc_wgt_GENIE, truth->mc_wgt_GENIE + m_nUniverses );
    } else {
      (*vert_error_band_wgts)["GENIE_AGKYxF1pi"]->at(0) = truth->truth_genie_wgt_AGKYxF1pi[2];
      (*vert_error_band_wgts)["GENIE_AGKYxF1pi"]->at(1) = truth->truth_genie_wgt_AGKYxF1pi[4];
      (*vert_error_band_wgts)["GENIE_CCQEPauliSupViaKF"]->at(0) = truth->truth_genie_wgt_CCQEPauliSupViaKF[2];
      (*vert_error_band_wgts)["GENIE_CCQEPauliSupViaKF"]->at(1) = truth->truth_genie_wgt_CCQEPauliSupViaKF[4];
      (*vert_error_band_wgts)["GENIE_EtaNCEL"]->at(0) = truth->truth_genie_wgt_EtaNCEL[2];
      (*vert_error_band_wgts)["GENIE_EtaNCEL"]->at(1) = truth->truth_genie_wgt_EtaNCEL[4];
      (*vert_error_band_wgts)["GENIE_FrAbs_N"]->at(0) = truth->truth_genie_wgt_FrAbs_N[2];
      (*vert_error_band_wgts)["GENIE_FrAbs_N"]->at(1) = truth->truth_genie_wgt_FrAbs_N[4];
      (*vert_error_band_wgts)["GENIE_FrAbs_pi"]->at(0) = truth->truth_genie_wgt_FrAbs_pi[2];
      (*vert_error_band_wgts)["GENIE_FrAbs_pi"]->at(1) = truth->truth_genie_wgt_FrAbs_pi[4];
      (*vert_error_band_wgts)["GENIE_FrCEx_N"]->at(0) = truth->truth_genie_wgt_FrCEx_N[2];
      (*vert_error_band_wgts)["GENIE_FrCEx_N"]->at(1) = truth->truth_genie_wgt_FrCEx_N[4];
      (*vert_error_band_wgts)["GENIE_FrCEx_pi"]->at(0) = truth->truth_genie_wgt_FrCEx_pi[2];
      (*vert_error_band_wgts)["GENIE_FrCEx_pi"]->at(1) = truth->truth_genie_wgt_FrCEx_pi[4];
      (*vert_error_band_wgts)["GENIE_FrElas_N"]->at(0) = truth->truth_genie_wgt_FrElas_N[2];
      (*vert_error_band_wgts)["GENIE_FrElas_N"]->at(1) = truth->truth_genie_wgt_FrElas_N[4];
      (*vert_error_band_wgts)["GENIE_FrElas_pi"]->at(0) = truth->truth_genie_wgt_FrElas_pi[2];
      (*vert_error_band_wgts)["GENIE_FrElas_pi"]->at(1) = truth->truth_genie_wgt_FrElas_pi[4];
      (*vert_error_band_wgts)["GENIE_FrInel_N"]->at(0) = truth->truth_genie_wgt_FrInel_N[2];
      (*vert_error_band_wgts)["GENIE_FrInel_N"]->at(1) = truth->truth_genie_wgt_FrInel_N[4];
      // (*vert_error_band_wgts)["GENIE_FrInel_pi"]->at(0) = truth->truth_genie_wgt_FrInel_pi[2];
      // (*vert_error_band_wgts)["GENIE_FrInel_pi"]->at(1) = truth->truth_genie_wgt_FrInel_pi[4];
      (*vert_error_band_wgts)["GENIE_FrPiProd_N"]->at(0) = truth->truth_genie_wgt_FrPiProd_N[2];
      (*vert_error_band_wgts)["GENIE_FrPiProd_N"]->at(1) = truth->truth_genie_wgt_FrPiProd_N[4];
      (*vert_error_band_wgts)["GENIE_FrPiProd_pi"]->at(0) = truth->truth_genie_wgt_FrPiProd_pi[2];
      (*vert_error_band_wgts)["GENIE_FrPiProd_pi"]->at(1) = truth->truth_genie_wgt_FrPiProd_pi[4];
      (*vert_error_band_wgts)["GENIE_MFP_N"]->at(0) = truth->truth_genie_wgt_MFP_N[2];
      (*vert_error_band_wgts)["GENIE_MFP_N"]->at(1) = truth->truth_genie_wgt_MFP_N[4];
      (*vert_error_band_wgts)["GENIE_MFP_pi"]->at(0) = truth->truth_genie_wgt_MFP_pi[2];
      (*vert_error_band_wgts)["GENIE_MFP_pi"]->at(1) = truth->truth_genie_wgt_MFP_pi[4];
      //(*vert_error_band_wgts)["GENIE_MaCCQE"]->at(0) = truth->truth_genie_wgt_MaCCQE[2];
      //(*vert_error_band_wgts)["GENIE_MaCCQE"]->at(1) = truth->truth_genie_wgt_MaCCQE[4];
      (*vert_error_band_wgts)["GENIE_MaCCQEshape"]->at(0) = truth->truth_genie_wgt_MaCCQEshape[2];
      (*vert_error_band_wgts)["GENIE_MaCCQEshape"]->at(1) = truth->truth_genie_wgt_MaCCQEshape[4];
      (*vert_error_band_wgts)["GENIE_MaNCEL"]->at(0) = truth->truth_genie_wgt_MaNCEL[2];
      (*vert_error_band_wgts)["GENIE_MaNCEL"]->at(1) = truth->truth_genie_wgt_MaNCEL[4];
      //(*vert_error_band_wgts)["GENIE_MaRES"]->at(0) = truth->truth_genie_wgt_MaRES[2];
      //(*vert_error_band_wgts)["GENIE_MaRES"]->at(1) = truth->truth_genie_wgt_MaRES[4];
      //(*vert_error_band_wgts)["GENIE_MvRES"]->at(0) = truth->truth_genie_wgt_MvRES[2];
      //(*vert_error_band_wgts)["GENIE_MvRES"]->at(1) = truth->truth_genie_wgt_MvRES[4];
      (*vert_error_band_wgts)["GENIE_NormCCQE"]->at(0) = truth->truth_genie_wgt_NormCCQE[2];
      (*vert_error_band_wgts)["GENIE_NormCCQE"]->at(1) = truth->truth_genie_wgt_NormCCQE[4];
      //(*vert_error_band_wgts)["GENIE_NormCCRES"]->at(0) = truth->truth_genie_wgt_NormCCRES[2];
      //(*vert_error_band_wgts)["GENIE_NormCCRES"]->at(1) = truth->truth_genie_wgt_NormCCRES[4];
      (*vert_error_band_wgts)["GENIE_NormDISCC"]->at(0) = truth->truth_genie_wgt_NormDISCC[2];
      (*vert_error_band_wgts)["GENIE_NormDISCC"]->at(1) = truth->truth_genie_wgt_NormDISCC[4];
      (*vert_error_band_wgts)["GENIE_NormNCRES"]->at(0) = truth->truth_genie_wgt_NormNCRES[2];
      (*vert_error_band_wgts)["GENIE_NormNCRES"]->at(1) = truth->truth_genie_wgt_NormNCRES[4];
      (*vert_error_band_wgts)["GENIE_RDecBR1gamma"]->at(0) = truth->truth_genie_wgt_RDecBR1gamma[2];
      (*vert_error_band_wgts)["GENIE_RDecBR1gamma"]->at(1) = truth->truth_genie_wgt_RDecBR1gamma[4];
      //    (*vert_error_band_wgts)["GENIE_Rvn1pi"]->at(0) = truth->truth_genie_wgt_Rvn1pi[2];
      //    (*vert_error_band_wgts)["GENIE_Rvn1pi"]->at(1) = truth->truth_genie_wgt_Rvn1pi[4];
      (*vert_error_band_wgts)["GENIE_Rvn2pi"]->at(0) = truth->truth_genie_wgt_Rvn2pi[2];
      (*vert_error_band_wgts)["GENIE_Rvn2pi"]->at(1) = truth->truth_genie_wgt_Rvn2pi[4];
      //    (*vert_error_band_wgts)["GENIE_Rvp1pi"]->at(0) = truth->truth_genie_wgt_Rvp1pi[2];
      //    (*vert_error_band_wgts)["GENIE_Rvp1pi"]->at(1) = truth->truth_genie_wgt_Rvp1pi[4];
      (*vert_error_band_wgts)["GENIE_Rvp2pi"]->at(0) = truth->truth_genie_wgt_Rvp2pi[2];
      (*vert_error_band_wgts)["GENIE_Rvp2pi"]->at(1) = truth->truth_genie_wgt_Rvp2pi[4];
      (*vert_error_band_wgts)["GENIE_Theta_Delta2Npi"]->at(0) = truth->truth_genie_wgt_Theta_Delta2Npi[2];
      (*vert_error_band_wgts)["GENIE_Theta_Delta2Npi"]->at(1) = truth->truth_genie_wgt_Theta_Delta2Npi[4];
      (*vert_error_band_wgts)["GENIE_VecFFCCQEshape"]->at(0) = truth->truth_genie_wgt_VecFFCCQEshape[2];
      (*vert_error_band_wgts)["GENIE_VecFFCCQEshape"]->at(1) = truth->truth_genie_wgt_VecFFCCQEshape[4];
      (*vert_error_band_wgts)["GENIE_AhtBY"]->at(0) = truth->truth_genie_wgt_AhtBY[2];
      (*vert_error_band_wgts)["GENIE_AhtBY"]->at(1) = truth->truth_genie_wgt_AhtBY[4];
      (*vert_error_band_wgts)["GENIE_BhtBY"]->at(0) = truth->truth_genie_wgt_BhtBY[2];
      (*vert_error_band_wgts)["GENIE_BhtBY"]->at(1) = truth->truth_genie_wgt_BhtBY[4];
      (*vert_error_band_wgts)["GENIE_CV1uBY"]->at(0) = truth->truth_genie_wgt_CV1uBY[2]; 
      (*vert_error_band_wgts)["GENIE_CV1uBY"]->at(1) = truth->truth_genie_wgt_CV1uBY[4]; 
      (*vert_error_band_wgts)["GENIE_CV2uBY"]->at(0) = truth->truth_genie_wgt_CV2uBY[2]; 
      (*vert_error_band_wgts)["GENIE_CV2uBY"]->at(1) = truth->truth_genie_wgt_CV2uBY[4]; 
    
      if ( doGenieTuning ){
	//Bools checking CCRes and NonRes1pi
	bool isGenieNonRes1pi = truth->truth_genie_wgt_Rvn1pi[2] < 1.0 || truth->truth_genie_wgt_Rvp1pi[2] < 1.0;
	//      bool isGenieCCRes = truth->mc_current == 1 && truth->mc_intType == 2;
	/*//It was decided the resonant pion modifications were too much when used with the nonresonant pion modification
	// CC Resonance errors from deuterium and electroproduction data fits
	if ( isGenieCCRes ){

	(*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(0) =  (1.0 + fabs( deuteriumMaRes - deuteriumMaRes1sig  - genieMaRes ) * ( truth->truth_genie_wgt_MaRES[2] - 1.0 ) / genieMaRes1sig) / (1.0 + fabs( deuteriumMaRes - genieMaRes ) * ( truth->truth_genie_wgt_MaRES[2] - 1.0 ) / genieMaRes1sig);
	(*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(1) =  (1.0 + fabs( deuteriumMaRes + deuteriumMaRes1sig  - genieMaRes ) * ( truth->truth_genie_wgt_MaRES[4] - 1.0 ) / genieMaRes1sig) / (1.0 + fabs( deuteriumMaRes - genieMaRes ) * ( truth->truth_genie_wgt_MaRES[4] - 1.0 ) / genieMaRes1sig);
	(*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(0) = 1.0 + fabs(genieMvRes - electroProdMvRes1sig - genieMvRes ) * ( truth->truth_genie_wgt_MvRES[2] - 1.0 ) / genieMvRes1sig;
	(*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(1) = 1.0 + fabs(genieMvRes + electroProdMvRes1sig - genieMvRes ) * ( truth->truth_genie_wgt_MvRES[4] - 1.0 ) / genieMvRes1sig;

	(*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(0) =  1-deuteriumResNorm1sig ;
	(*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(1) =  1+deuteriumResNorm1sig ;
	}
	else{
	(*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(0) =  1.0 ;
	(*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(1) =  1.0 ;
	(*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(0) =  1.0 ;
	(*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(1) =  1.0 ;
	(*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(0) =  1.0 ;
	(*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(1) =  1.0 ;
	}
	*/
	// Non-resonant 1pi production normalization errors from deuterium fit
	if ( isGenieNonRes1pi ){
	  //(*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(0) = 1-deuteriumNonResNorm1sig ;
	  //(*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(1) = 1+deuteriumNonResNorm1sig ;
	  //(*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(0) = 1-deuteriumNonResNorm1sig ;
	  //(*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(1) = 1+deuteriumNonResNorm1sig ;
	  (*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(0) = (deuteriumNonResNorm-deuteriumNonResNorm1sig)/deuteriumNonResNorm ;
	  (*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(1) = (deuteriumNonResNorm+deuteriumNonResNorm1sig)/deuteriumNonResNorm ;
	  (*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(0) = (deuteriumNonResNorm-deuteriumNonResNorm1sig)/deuteriumNonResNorm ;
	  (*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(1) = (deuteriumNonResNorm+deuteriumNonResNorm1sig)/deuteriumNonResNorm ;
	}
	else{
	  (*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(0) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(1) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(0) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(1) =  1.0 ;

	}
      }
    
      else{//give the unmodified weights instead
	(*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(0) =  truth->truth_genie_wgt_MaRES[2] ;
	(*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(1) =  truth->truth_genie_wgt_MaRES[4] ;
	(*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(0) =  truth->truth_genie_wgt_MvRES[2] ;
	(*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(1) =  truth->truth_genie_wgt_MvRES[4] ;
	(*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(0) =  truth->truth_genie_wgt_NormCCRES[2] ;
	(*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(1) =  truth->truth_genie_wgt_NormCCRES[4] ;
	(*vert_error_band_wgts)[ "GENIE_Rvn1pi"    ]->at(0) =  truth->truth_genie_wgt_Rvn1pi[2] ;
	(*vert_error_band_wgts)[ "GENIE_Rvn1pi"    ]->at(1) =  truth->truth_genie_wgt_Rvn1pi[4] ;
	(*vert_error_band_wgts)[ "GENIE_Rvp1pi"    ]->at(0) =  truth->truth_genie_wgt_Rvp1pi[2] ;
	(*vert_error_band_wgts)[ "GENIE_Rvp1pi"    ]->at(1) =  truth->truth_genie_wgt_Rvp1pi[4] ;
      }
    
    }
  }
}

void CCQENuUtils::fillVertErrorBandWgts( const CCQENuEvent* event )
{
  CCQENuEvent *tmp_event = (CCQENuEvent*)event;//Guh, I don't want to make 4 functions so cast here.
  if(removeSignalError && cutter->passTrueCCQELike( tmp_event )){//need to be remove signal error AND signal else you just apply weights as normal.

    if( vert_error_band_wgts==NULL ){
      throw std::runtime_error( "Error band weights map hasn't been created !" );
    }

    //Update playlist normalization correction before filling errors
    updatePlaylistNorm(event);
    //Apply flux weights
    std::vector<double> totalFluxErrorWeights; 
    for( int iUnv=0; iUnv<m_nUniverses; ++iUnv ) { 
      totalFluxErrorWeights.push_back( frw->GetFluxErrorWeight(event->mc_incomingE/1000.,event->mc_incoming,iUnv));
    }
    (*vert_error_band_wgts)["Flux"]->assign( totalFluxErrorWeights.begin(), totalFluxErrorWeights.end() ); 

    (*vert_error_band_wgts)["Normalization_Factors"]->at(0) = 1 - GetNormWeightErr( tmp_event )/ GetNormWeight( tmp_event);
    (*vert_error_band_wgts)["Normalization_Factors"]->at(1) = 1 + GetNormWeightErr( tmp_event )/GetNormWeight( tmp_event);

    // Apply HadronReweight weights 
    // int entry_number = event->fChain->GetReadEntry();
    Long64_t entry_number = event->fChain->GetReadEntry();
    //  double wgt = event->wgt;
    double wgt = wgt_CV;
    fillHadronReweightVertErrorBandWgts(entry_number, false, wgt);


    // Apply RPA weights
    (*vert_error_band_wgts)["RPA_HighQ2"]->at(0) = GetRPAWeight(tmp_event,0);
    (*vert_error_band_wgts)["RPA_HighQ2"]->at(1) = GetRPAWeight(tmp_event,0);

    (*vert_error_band_wgts)["RPA_LowQ2"]->at(0) = GetRPAWeight(tmp_event,0);
    (*vert_error_band_wgts)["RPA_LowQ2"]->at(1) = GetRPAWeight(tmp_event,0);

    // Apply 2p2h low recoil fit weights
    (*vert_error_band_wgts)["Low_recoil_fits"]->at(0) = Get2p2hWeight(tmp_event,0);
    (*vert_error_band_wgts)["Low_recoil_fits"]->at(1) = Get2p2hWeight(tmp_event,0);
    (*vert_error_band_wgts)["Low_recoil_fits"]->at(2) = Get2p2hWeight(tmp_event,0);


    // Apply Target Mass weights 
    (*vert_error_band_wgts)["Target_Mass"]->at(0) = target_mass_weights.at(0) * wgt;  
    (*vert_error_band_wgts)["Target_Mass"]->at(1) = target_mass_weights.at(1) * wgt;  

    // Apply weights for Proton Tracking Efficiency 
    double protonTrackLength = event->proton_track_length; 
    double track_eff_error = 0.0;
    if (event->multiplicity>1){
      track_eff_error = protonTrackLength < 8*17.0 ? 0.046 : 0.003; //Ref: TN048
    }
    double track_eff_corr = 1.0; 
    double track_eff_weights_down = 1.0 - track_eff_error/track_eff_corr; 
    double track_eff_weights_up = 1.0 + track_eff_error/track_eff_corr; 

    (*vert_error_band_wgts)["Proton_TrackEff"]->at(0) = track_eff_weights_down * wgt;  
    (*vert_error_band_wgts)["Proton_TrackEff"]->at(1) = track_eff_weights_up * wgt;

    // Apply Michel Efficiency weights 
    (*vert_error_band_wgts)["Michel_Efficiency"]->at(0) = michel_weights.at(0) * wgt;
    (*vert_error_band_wgts)["Michel_Efficiency"]->at(1) = michel_weights.at(1) * wgt; 
  
    // Apply GENIE weights 
    if( ! use_genie_split ){
      //Below 2 GENIE variable is missing from Dan's processing on 10/20/2015, but he should add them back in (update AnaTuple.cpp) 
      //(*vert_error_band_wgts)["GENIE"]->assign( event->mc_wgt_GENIE, event->mc_wgt_GENIE + m_nUniverses );
    } else {
      (*vert_error_band_wgts)["GENIE_AGKYxF1pi"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_AGKYxF1pi"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_CCQEPauliSupViaKF"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_CCQEPauliSupViaKF"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_EtaNCEL"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_EtaNCEL"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrAbs_N"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrAbs_N"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrAbs_pi"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrAbs_pi"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrCEx_N"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrCEx_N"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrCEx_pi"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrCEx_pi"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrElas_N"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrElas_N"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrElas_pi"]->at(0) = 1.0;
      (*vert_error_band_wgts)["GENIE_FrElas_pi"]->at(1) = 1.0;
      (*vert_error_band_wgts)["GENIE_FrInel_N"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrInel_N"]->at(1) = 1.0; 
      // (*vert_error_band_wgts)["GENIE_FrInel_pi"]->at(0) = event->truth_genie_wgt_FrInel_pi[2];
      // (*vert_error_band_wgts)["GENIE_FrInel_pi"]->at(1) = event->truth_genie_wgt_FrInel_pi[4];
      (*vert_error_band_wgts)["GENIE_FrPiProd_N"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrPiProd_N"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_FrPiProd_pi"]->at(0) = 1.0;
      (*vert_error_band_wgts)["GENIE_FrPiProd_pi"]->at(1) = 1.0;
      (*vert_error_band_wgts)["GENIE_MFP_N"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_MFP_N"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_MFP_pi"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_MFP_pi"]->at(1) = 1.0; 
      //(*vert_error_band_wgts)["GENIE_MaCCQE"]->at(0) = event->truth_genie_wgt_MaCCQE[2];
      //(*vert_error_band_wgts)["GENIE_MaCCQE"]->at(1) = event->truth_genie_wgt_MaCCQE[4];
      (*vert_error_band_wgts)["GENIE_MaCCQEshape"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_MaCCQEshape"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_MaNCEL"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_MaNCEL"]->at(1) = 1.0; 
      //(*vert_error_band_wgts)["GENIE_MaRES"]->at(0) = event->truth_genie_wgt_MaRES[2];
      //(*vert_error_band_wgts)["GENIE_MaRES"]->at(1) = event->truth_genie_wgt_MaRES[4];
      //(*vert_error_band_wgts)["GENIE_MvRES"]->at(0) = event->truth_genie_wgt_MvRES[2];
      //(*vert_error_band_wgts)["GENIE_MvRES"]->at(1) = event->truth_genie_wgt_MvRES[4];
      (*vert_error_band_wgts)["GENIE_NormCCQE"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_NormCCQE"]->at(1) = 1.0; 
      //(*vert_error_band_wgts)["GENIE_NormCCRES"]->at(0) = event->truth_genie_wgt_NormCCRES[2];
      //(*vert_error_band_wgts)["GENIE_NormCCRES"]->at(1) = event->truth_genie_wgt_NormCCRES[4];
      (*vert_error_band_wgts)["GENIE_NormDISCC"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_NormDISCC"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_NormNCRES"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_NormNCRES"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_RDecBR1gamma"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_RDecBR1gamma"]->at(1) = 1.0; 
      //    (*vert_error_band_wgts)["GENIE_Rvn1pi"]->at(0) = event->truth_genie_wgt_Rvn1pi[2];
      //    (*vert_error_band_wgts)["GENIE_Rvn1pi"]->at(1) = event->truth_genie_wgt_Rvn1pi[4];
      (*vert_error_band_wgts)["GENIE_Rvn2pi"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_Rvn2pi"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_Rvp1pi"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_Rvp1pi"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_Rvp2pi"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_Rvp2pi"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_Theta_Delta2Npi"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_Theta_Delta2Npi"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_VecFFCCQEshape"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_VecFFCCQEshape"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_AhtBY"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_AhtBY"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_BhtBY"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_BhtBY"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_CV1uBY"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_CV1uBY"]->at(1) = 1.0; 
      (*vert_error_band_wgts)["GENIE_CV2uBY"]->at(0) = 1.0; 
      (*vert_error_band_wgts)["GENIE_CV2uBY"]->at(1) = 1.0; 
      if ( doGenieTuning ){
	//Bools checking CCRes and NonRes1pi
	bool isGenieNonRes1pi = event->truth_genie_wgt_Rvn1pi[2] < 1.0 || event->truth_genie_wgt_Rvp1pi[2] < 1.0;
	//      bool isGenieCCRes = event->mc_current == 1 && event->mc_intType == 2;
	// CC Resonance errors from deuterium and electroproduction data fits
	/*//It was decided the resonant pion modifications were too much when used with the nonresonant pion modification
	  if ( isGenieCCRes ){
	
	  (*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(0) =  (1.0 + fabs( deuteriumMaRes - deuteriumMaRes1sig  - genieMaRes ) * ( event->truth_genie_wgt_MaRES[2] - 1.0 ) / genieMaRes1sig) / (1.0 + fabs( deuteriumMaRes - genieMaRes ) * ( event->truth_genie_wgt_MaRES[2] - 1.0 ) / genieMaRes1sig);
	  (*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(1) =  (1.0 + fabs( deuteriumMaRes + deuteriumMaRes1sig  - genieMaRes ) * ( event->truth_genie_wgt_MaRES[4] - 1.0 ) / genieMaRes1sig) / (1.0 + fabs( deuteriumMaRes - genieMaRes ) * ( event->truth_genie_wgt_MaRES[4] - 1.0 ) / genieMaRes1sig);
	  (*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(0) = 1.0 + fabs(genieMvRes - electroProdMvRes1sig - genieMvRes ) * ( event->truth_genie_wgt_MvRES[2] - 1.0 ) / genieMvRes1sig;
	  (*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(1) = 1.0 + fabs(genieMvRes + electroProdMvRes1sig - genieMvRes ) * ( event->truth_genie_wgt_MvRES[4] - 1.0 ) / genieMvRes1sig;
	
	  (*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(0) =  1-deuteriumResNorm1sig ;
	  (*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(1) =  1+deuteriumResNorm1sig ;
	  }
	  else{
	  (*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(0) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(1) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(0) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(1) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(0) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(1) =  1.0 ;
	  }
	*/
	// Non-resonant 1pi production normalization errors from deuterium fit
	if ( isGenieNonRes1pi ){
	  (*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(0) = 1.0; 
	  (*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(1) = 1.0; 
	  (*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(0) = 1.0; 
	  (*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(1) = 1.0; 
	}
	else{
	  (*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(0) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(1) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(0) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(1) =  1.0 ;
	
	}
      }
      else{//give the unmodified weights instead
	(*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(0) = 1.0; 
	(*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(1) = 1.0; 
	(*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(0) = 1.0; 
	(*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(1) = 1.0; 
	(*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(0) = 1.0; 
	(*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(1) = 1.0; 
	(*vert_error_band_wgts)[ "GENIE_Rvn1pi"    ]->at(0) = 1.0; 
	(*vert_error_band_wgts)[ "GENIE_Rvn1pi"    ]->at(1) = 1.0; 
	(*vert_error_band_wgts)[ "GENIE_Rvp1pi"    ]->at(0) = 1.0; 
	(*vert_error_band_wgts)[ "GENIE_Rvp1pi"    ]->at(1) = 1.0;
      }
    }
  }//if remove signal and is signal
  else{

    if( vert_error_band_wgts==NULL ){
      throw std::runtime_error( "Error band weights map hasn't been created !" );
    }

    //Update playlist normalization correction before filling errors
    updatePlaylistNorm(event);
    //Apply flux weights
    std::vector<double> totalFluxErrorWeights; 
    for( int iUnv=0; iUnv<m_nUniverses; ++iUnv ) { 
      totalFluxErrorWeights.push_back( frw->GetFluxErrorWeight(event->mc_incomingE/1000.,event->mc_incoming,iUnv));
    }
    (*vert_error_band_wgts)["Flux"]->assign( totalFluxErrorWeights.begin(), totalFluxErrorWeights.end() ); 

    //(*vert_error_band_wgts)["Normalization_Factors"]->at(0) = 1 - mnvNormalizer->CorrectionErr( event->CCQENu_minos_trk_p )/ mnvNormalizer->Correction( event->CCQENu_minos_trk_p ); 
    //(*vert_error_band_wgts)["Normalization_Factors"]->at(1) = 1 + mnvNormalizer->CorrectionErr( event->CCQENu_minos_trk_p )/mnvNormalizer->Correction( event->CCQENu_minos_trk_p ); 

    (*vert_error_band_wgts)["Normalization_Factors"]->at(0) = 1 - GetNormWeightErr( tmp_event )/ GetNormWeight( tmp_event);
    (*vert_error_band_wgts)["Normalization_Factors"]->at(1) = 1 + GetNormWeightErr( tmp_event )/GetNormWeight( tmp_event);

    // Apply HadronReweight weights 
    // int entry_number = event->fChain->GetReadEntry();
    Long64_t entry_number = event->fChain->GetReadEntry();
    //  double wgt = event->wgt;
    double wgt = wgt_CV;
    fillHadronReweightVertErrorBandWgts(entry_number, false, wgt);

    // Apply RPA weights
    (*vert_error_band_wgts)["RPA_HighQ2"]->at(0) = GetRPAWeight(tmp_event,1);
    (*vert_error_band_wgts)["RPA_HighQ2"]->at(1) = GetRPAWeight(tmp_event,2);

    (*vert_error_band_wgts)["RPA_LowQ2"]->at(0) = GetRPAWeight(tmp_event,3);
    (*vert_error_band_wgts)["RPA_LowQ2"]->at(1) = GetRPAWeight(tmp_event,4);

    // Apply 2p2h low recoil fit weights
    (*vert_error_band_wgts)["Low_recoil_fits"]->at(0) = Get2p2hWeight(tmp_event,1);
    (*vert_error_band_wgts)["Low_recoil_fits"]->at(1) = Get2p2hWeight(tmp_event,2);
    (*vert_error_band_wgts)["Low_recoil_fits"]->at(2) = Get2p2hWeight(tmp_event,3);


    // Apply Target Mass weights 
    (*vert_error_band_wgts)["Target_Mass"]->at(0) = target_mass_weights.at(0) * wgt;  
    (*vert_error_band_wgts)["Target_Mass"]->at(1) = target_mass_weights.at(1) * wgt;  

    // Apply weights for Proton Tracking Efficiency 
    double protonTrackLength = event->proton_track_length; 
    double track_eff_error = 0.0;
    if (event->multiplicity>1){
      track_eff_error = protonTrackLength < 8*17.0 ? 0.046 : 0.003; //Ref: TN048
    }
    double track_eff_corr = 1.0; 
    double track_eff_weights_down = 1.0 - track_eff_error/track_eff_corr; 
    double track_eff_weights_up = 1.0 + track_eff_error/track_eff_corr; 

    (*vert_error_band_wgts)["Proton_TrackEff"]->at(0) = track_eff_weights_down * wgt;  
    (*vert_error_band_wgts)["Proton_TrackEff"]->at(1) = track_eff_weights_up * wgt;

    // Apply Michel Efficiency weights 
    (*vert_error_band_wgts)["Michel_Efficiency"]->at(0) = michel_weights.at(0) * wgt;
    (*vert_error_band_wgts)["Michel_Efficiency"]->at(1) = michel_weights.at(1) * wgt; 
  
    // Apply GENIE weights 
    if( ! use_genie_split ){
      //Below 2 GENIE variable is missing from Dan's processing on 10/20/2015, but he should add them back in (update AnaTuple.cpp) 
      //(*vert_error_band_wgts)["GENIE"]->assign( event->mc_wgt_GENIE, event->mc_wgt_GENIE + m_nUniverses );
    } else {
      (*vert_error_band_wgts)["GENIE_AGKYxF1pi"]->at(0) = event->truth_genie_wgt_AGKYxF1pi[2];
      (*vert_error_band_wgts)["GENIE_AGKYxF1pi"]->at(1) = event->truth_genie_wgt_AGKYxF1pi[4];
      (*vert_error_band_wgts)["GENIE_CCQEPauliSupViaKF"]->at(0) = event->truth_genie_wgt_CCQEPauliSupViaKF[2];
      (*vert_error_band_wgts)["GENIE_CCQEPauliSupViaKF"]->at(1) = event->truth_genie_wgt_CCQEPauliSupViaKF[4];
      (*vert_error_band_wgts)["GENIE_EtaNCEL"]->at(0) = event->truth_genie_wgt_EtaNCEL[2];
      (*vert_error_band_wgts)["GENIE_EtaNCEL"]->at(1) = event->truth_genie_wgt_EtaNCEL[4];
      (*vert_error_band_wgts)["GENIE_FrAbs_N"]->at(0) = event->truth_genie_wgt_FrAbs_N[2];
      (*vert_error_band_wgts)["GENIE_FrAbs_N"]->at(1) = event->truth_genie_wgt_FrAbs_N[4];
      (*vert_error_band_wgts)["GENIE_FrAbs_pi"]->at(0) = event->truth_genie_wgt_FrAbs_pi[2];
      (*vert_error_band_wgts)["GENIE_FrAbs_pi"]->at(1) = event->truth_genie_wgt_FrAbs_pi[4];
      (*vert_error_band_wgts)["GENIE_FrCEx_N"]->at(0) = event->truth_genie_wgt_FrCEx_N[2];
      (*vert_error_band_wgts)["GENIE_FrCEx_N"]->at(1) = event->truth_genie_wgt_FrCEx_N[4];
      (*vert_error_band_wgts)["GENIE_FrCEx_pi"]->at(0) = event->truth_genie_wgt_FrCEx_pi[2];
      (*vert_error_band_wgts)["GENIE_FrCEx_pi"]->at(1) = event->truth_genie_wgt_FrCEx_pi[4];
      (*vert_error_band_wgts)["GENIE_FrElas_N"]->at(0) = event->truth_genie_wgt_FrElas_N[2];
      (*vert_error_band_wgts)["GENIE_FrElas_N"]->at(1) = event->truth_genie_wgt_FrElas_N[4];
      (*vert_error_band_wgts)["GENIE_FrElas_pi"]->at(0) = event->truth_genie_wgt_FrElas_pi[2];
      (*vert_error_band_wgts)["GENIE_FrElas_pi"]->at(1) = event->truth_genie_wgt_FrElas_pi[4];
      (*vert_error_band_wgts)["GENIE_FrInel_N"]->at(0) = event->truth_genie_wgt_FrInel_N[2];
      (*vert_error_band_wgts)["GENIE_FrInel_N"]->at(1) = event->truth_genie_wgt_FrInel_N[4];
      // (*vert_error_band_wgts)["GENIE_FrInel_pi"]->at(0) = event->truth_genie_wgt_FrInel_pi[2];
      // (*vert_error_band_wgts)["GENIE_FrInel_pi"]->at(1) = event->truth_genie_wgt_FrInel_pi[4];
      (*vert_error_band_wgts)["GENIE_FrPiProd_N"]->at(0) = event->truth_genie_wgt_FrPiProd_N[2];
      (*vert_error_band_wgts)["GENIE_FrPiProd_N"]->at(1) = event->truth_genie_wgt_FrPiProd_N[4];
      (*vert_error_band_wgts)["GENIE_FrPiProd_pi"]->at(0) = event->truth_genie_wgt_FrPiProd_pi[2];
      (*vert_error_band_wgts)["GENIE_FrPiProd_pi"]->at(1) = event->truth_genie_wgt_FrPiProd_pi[4];
      (*vert_error_band_wgts)["GENIE_MFP_N"]->at(0) = event->truth_genie_wgt_MFP_N[2];
      //if(event->truth_genie_wgt_MFP_N[2]> 2.)std::cout<<"truth->truth_genie_wgt_MFP_N[2] = "<<event->truth_genie_wgt_MFP_N[2]<<std::endl;
      (*vert_error_band_wgts)["GENIE_MFP_N"]->at(1) = event->truth_genie_wgt_MFP_N[4];
      //if(event->truth_genie_wgt_MFP_N[4]> 2.)std::cout<<"truth->truth_genie_wgt_MFP_N[4] = "<<event->truth_genie_wgt_MFP_N[4]<<std::endl;
      (*vert_error_band_wgts)["GENIE_MFP_pi"]->at(0) = event->truth_genie_wgt_MFP_pi[2];
      (*vert_error_band_wgts)["GENIE_MFP_pi"]->at(1) = event->truth_genie_wgt_MFP_pi[4];
      //(*vert_error_band_wgts)["GENIE_MaCCQE"]->at(0) = event->truth_genie_wgt_MaCCQE[2];
      //(*vert_error_band_wgts)["GENIE_MaCCQE"]->at(1) = event->truth_genie_wgt_MaCCQE[4];
      (*vert_error_band_wgts)["GENIE_MaCCQEshape"]->at(0) = event->truth_genie_wgt_MaCCQEshape[2];
      (*vert_error_band_wgts)["GENIE_MaCCQEshape"]->at(1) = event->truth_genie_wgt_MaCCQEshape[4];
      (*vert_error_band_wgts)["GENIE_MaNCEL"]->at(0) = event->truth_genie_wgt_MaNCEL[2];
      (*vert_error_band_wgts)["GENIE_MaNCEL"]->at(1) = event->truth_genie_wgt_MaNCEL[4];
      //(*vert_error_band_wgts)["GENIE_MaRES"]->at(0) = event->truth_genie_wgt_MaRES[2];
      //(*vert_error_band_wgts)["GENIE_MaRES"]->at(1) = event->truth_genie_wgt_MaRES[4];
      //(*vert_error_band_wgts)["GENIE_MvRES"]->at(0) = event->truth_genie_wgt_MvRES[2];
      //(*vert_error_band_wgts)["GENIE_MvRES"]->at(1) = event->truth_genie_wgt_MvRES[4];
      (*vert_error_band_wgts)["GENIE_NormCCQE"]->at(0) = event->truth_genie_wgt_NormCCQE[2];
      (*vert_error_band_wgts)["GENIE_NormCCQE"]->at(1) = event->truth_genie_wgt_NormCCQE[4];
      //(*vert_error_band_wgts)["GENIE_NormCCRES"]->at(0) = event->truth_genie_wgt_NormCCRES[2];
      //(*vert_error_band_wgts)["GENIE_NormCCRES"]->at(1) = event->truth_genie_wgt_NormCCRES[4];
      (*vert_error_band_wgts)["GENIE_NormDISCC"]->at(0) = event->truth_genie_wgt_NormDISCC[2];
      (*vert_error_band_wgts)["GENIE_NormDISCC"]->at(1) = event->truth_genie_wgt_NormDISCC[4];
      (*vert_error_band_wgts)["GENIE_NormNCRES"]->at(0) = event->truth_genie_wgt_NormNCRES[2];
      (*vert_error_band_wgts)["GENIE_NormNCRES"]->at(1) = event->truth_genie_wgt_NormNCRES[4];
      (*vert_error_band_wgts)["GENIE_RDecBR1gamma"]->at(0) = event->truth_genie_wgt_RDecBR1gamma[2];
      (*vert_error_band_wgts)["GENIE_RDecBR1gamma"]->at(1) = event->truth_genie_wgt_RDecBR1gamma[4];
      //    (*vert_error_band_wgts)["GENIE_Rvn1pi"]->at(0) = event->truth_genie_wgt_Rvn1pi[2];
      //    (*vert_error_band_wgts)["GENIE_Rvn1pi"]->at(1) = event->truth_genie_wgt_Rvn1pi[4];
      (*vert_error_band_wgts)["GENIE_Rvn2pi"]->at(0) = event->truth_genie_wgt_Rvn2pi[2];
      (*vert_error_band_wgts)["GENIE_Rvn2pi"]->at(1) = event->truth_genie_wgt_Rvn2pi[4];
      (*vert_error_band_wgts)["GENIE_Rvp1pi"]->at(0) = event->truth_genie_wgt_Rvp1pi[2];
      (*vert_error_band_wgts)["GENIE_Rvp1pi"]->at(1) = event->truth_genie_wgt_Rvp1pi[4];
      (*vert_error_band_wgts)["GENIE_Rvp2pi"]->at(0) = event->truth_genie_wgt_Rvp2pi[2];
      (*vert_error_band_wgts)["GENIE_Rvp2pi"]->at(1) = event->truth_genie_wgt_Rvp2pi[4];
      (*vert_error_band_wgts)["GENIE_Theta_Delta2Npi"]->at(0) = event->truth_genie_wgt_Theta_Delta2Npi[2];
      (*vert_error_band_wgts)["GENIE_Theta_Delta2Npi"]->at(1) = event->truth_genie_wgt_Theta_Delta2Npi[4];
      (*vert_error_band_wgts)["GENIE_VecFFCCQEshape"]->at(0) = event->truth_genie_wgt_VecFFCCQEshape[2];
      (*vert_error_band_wgts)["GENIE_VecFFCCQEshape"]->at(1) = event->truth_genie_wgt_VecFFCCQEshape[4]; 
      (*vert_error_band_wgts)["GENIE_AhtBY"]->at(0) = event->truth_genie_wgt_AhtBY[2];
      (*vert_error_band_wgts)["GENIE_AhtBY"]->at(1) = event->truth_genie_wgt_AhtBY[4];
      (*vert_error_band_wgts)["GENIE_BhtBY"]->at(0) = event->truth_genie_wgt_BhtBY[2];
      (*vert_error_band_wgts)["GENIE_BhtBY"]->at(1) = event->truth_genie_wgt_BhtBY[4];
      (*vert_error_band_wgts)["GENIE_CV1uBY"]->at(0) = event->truth_genie_wgt_CV1uBY[2]; 
      (*vert_error_band_wgts)["GENIE_CV1uBY"]->at(1) = event->truth_genie_wgt_CV1uBY[4]; 
      (*vert_error_band_wgts)["GENIE_CV2uBY"]->at(0) = event->truth_genie_wgt_CV2uBY[2]; 
      (*vert_error_band_wgts)["GENIE_CV2uBY"]->at(1) = event->truth_genie_wgt_CV2uBY[4]; 
      if ( doGenieTuning ){
	//Bools checking CCRes and NonRes1pi
	bool isGenieNonRes1pi = event->truth_genie_wgt_Rvn1pi[2] < 1.0 || event->truth_genie_wgt_Rvp1pi[2] < 1.0;
	//      bool isGenieCCRes = event->mc_current == 1 && event->mc_intType == 2;
	// CC Resonance errors from deuterium and electroproduction data fits
	/*//It was decided the resonant pion modifications were too much when used with the nonresonant pion modification
	  if ( isGenieCCRes ){
	
	  (*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(0) =  (1.0 + fabs( deuteriumMaRes - deuteriumMaRes1sig  - genieMaRes ) * ( event->truth_genie_wgt_MaRES[2] - 1.0 ) / genieMaRes1sig) / (1.0 + fabs( deuteriumMaRes - genieMaRes ) * ( event->truth_genie_wgt_MaRES[2] - 1.0 ) / genieMaRes1sig);
	  (*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(1) =  (1.0 + fabs( deuteriumMaRes + deuteriumMaRes1sig  - genieMaRes ) * ( event->truth_genie_wgt_MaRES[4] - 1.0 ) / genieMaRes1sig) / (1.0 + fabs( deuteriumMaRes - genieMaRes ) * ( event->truth_genie_wgt_MaRES[4] - 1.0 ) / genieMaRes1sig);
	  (*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(0) = 1.0 + fabs(genieMvRes - electroProdMvRes1sig - genieMvRes ) * ( event->truth_genie_wgt_MvRES[2] - 1.0 ) / genieMvRes1sig;
	  (*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(1) = 1.0 + fabs(genieMvRes + electroProdMvRes1sig - genieMvRes ) * ( event->truth_genie_wgt_MvRES[4] - 1.0 ) / genieMvRes1sig;
	
	  (*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(0) =  1-deuteriumResNorm1sig ;
	  (*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(1) =  1+deuteriumResNorm1sig ;
	  }
	  else{
	  (*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(0) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(1) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(0) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(1) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(0) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(1) =  1.0 ;
	  }
	*/
	// Non-resonant 1pi production normalization errors from deuterium fit
	if ( isGenieNonRes1pi ){
	  //(*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(0) = 1-deuteriumNonResNorm1sig ;
	  //(*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(1) = 1+deuteriumNonResNorm1sig ;
	  //(*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(0) = 1-deuteriumNonResNorm1sig ;
	  //(*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(1) = 1+deuteriumNonResNorm1sig ;
	  (*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(0) = (deuteriumNonResNorm-deuteriumNonResNorm1sig)/deuteriumNonResNorm ;
	  (*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(1) = (deuteriumNonResNorm+deuteriumNonResNorm1sig)/deuteriumNonResNorm ;
	  (*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(0) = (deuteriumNonResNorm-deuteriumNonResNorm1sig)/deuteriumNonResNorm ;
	  (*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(1) = (deuteriumNonResNorm+deuteriumNonResNorm1sig)/deuteriumNonResNorm ;
	}
	else{
	  (*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(0) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_Rvn1pi" ]->at(1) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(0) =  1.0 ;
	  (*vert_error_band_wgts)[ "GENIE_Rvp1pi" ]->at(1) =  1.0 ;
	
	}
      }
      else{//give the unmodified weights instead
	(*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(0) =  event->truth_genie_wgt_MaRES[2] ;
	(*vert_error_band_wgts)[ "GENIE_MaRES"     ]->at(1) =  event->truth_genie_wgt_MaRES[4] ;
	(*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(0) =  event->truth_genie_wgt_MvRES[2] ;
	(*vert_error_band_wgts)[ "GENIE_MvRES"     ]->at(1) =  event->truth_genie_wgt_MvRES[4] ;
	(*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(0) =  event->truth_genie_wgt_NormCCRES[2] ;
	(*vert_error_band_wgts)[ "GENIE_NormCCRES" ]->at(1) =  event->truth_genie_wgt_NormCCRES[4] ;
	(*vert_error_band_wgts)[ "GENIE_Rvn1pi"    ]->at(0) =  event->truth_genie_wgt_Rvn1pi[2] ;
	(*vert_error_band_wgts)[ "GENIE_Rvn1pi"    ]->at(1) =  event->truth_genie_wgt_Rvn1pi[4] ;
	(*vert_error_band_wgts)[ "GENIE_Rvp1pi"    ]->at(0) =  event->truth_genie_wgt_Rvp1pi[2] ;
	(*vert_error_band_wgts)[ "GENIE_Rvp1pi"    ]->at(1) =  event->truth_genie_wgt_Rvp1pi[4] ;
      }
    }
  }//else
}
void CCQENuUtils::fillLatErrorBandWgts( CCQENuEvent* event, string sample, bool istrue ) {

  if( lat_error_band_wgts==NULL ){
    cout << "Error band weights map hasn't been created" << endl;
    return;
  }

  for( StrVecMap::iterator it=lat_error_band_wgts->begin(); it!=lat_error_band_wgts->end(); ++it ) {

    // fill lateral error bands weights
    (*lat_error_band_wgts)[it->first]->assign( m_nUniverses, 1.0 );

    // ... and shifts 
    for( int i=0; i<recoShifter->GetNumberOfUniverses(); ++i ){

      fillLatErrorBandShifts( event, it->first, i, sample, istrue );

    }
  }

}

void CCQENuUtils::fillLatErrorBandShiftsMuonVar( CCQENuEvent* event, string name, int universe, string sample, bool istrue ) {

  double muT_shift      = 0.0;
  double muTheta_shift  = 0.0;
  double muPT_shift     = 0.0;
  double muPZ_shift     = 0.0;
  double muQ2_shift     = 0.0;
  double recoil_shift   = 0.0; 
  double enu_shift      = 0.0;
  double primaryProton_scoreShift = 0.0; 
  double *secProtons_scoreShifts = NULL;  

  //--s------------------------------------------------------------------------------
  // Get Q2 shift (computed from muon arm) for this systematic for this universe 
  //--------------------------------------------------------------------------------
  getQ2Shift( muQ2_shift, event, name, universe );
  
  ///-------------------------------------------------------------------------------
  // Get Enu shift which is computer from the muon arm
  getEnuShift( enu_shift, event, name, universe );

  //------------------------------------------------------------------------------
  // Obtain the shifts in muon kinematics due to shifts in muonP and muonTheta 
  //------------------------------------------------------------------------------
  if( name == "Muon_Energy" ) {
    
    // Get shift due to muon momentum (actually momentum) 
    double muonP = event->CCQENu_muon_P; // MeV 
    double muonPErr = event->CCQENu_sys_muon_energy_shift[1]; // MeV
    double muonTheta = event->CCQENu_muon_theta; //rad 
    
    recoShifter->GetShift_ccqe_muonT_muonP( muT_shift, muonP, muonPErr, universe+1 );
    recoShifter->GetShift_ccqe_muonPT_muonP( muPT_shift, muonP, muonTheta, muonPErr, universe+1);
    recoShifter->GetShift_ccqe_muonPZ_muonP( muPZ_shift, muonP, muonTheta, muonPErr, universe+1 );

    muT_shift /= 1000.; //GeV
    muPT_shift /= 1000.; // GeV
    muPZ_shift /= 1000.; // GeV
    
    // cout << "DEBUG LATERAL ERROR BAND "<<endl;
    // cout << "muon PT (GeV) = " << muonP*sin(muonTheta)/1000. << endl;
    // cout<< "muon_PT shift (due to muonP) (GeV) = " << muPT_shift << endl;
    
  } else if( name == "Muon_Theta" ) {

    // Get shift due to muon angle 
    double muonP = event->CCQENu_muon_P; // MeV
    double muonTheta = event->CCQENu_muon_theta; //rad
    
    //This direct change to polar angle is not desired. Shifts in X and Y components are required  
    // double muonThetaErr = 0.002; //rad
   
    double muonThetaX = event->muon_thetaX; //rad
    double muonThetaY = event->muon_thetaY; //rad
    double muonThetaX_Err = 0.001;  //rad (error on beam angleX correction from Edgar Valencia's DocDB 11550) 
    double muonThetaY_Err = 0.0009; //rad (error on beam angleY correction from Edgar Valencia's DocDB 11550)
      
    recoShifter->GetShift_ccqe_muonThetaXY( muTheta_shift, muonTheta, muonThetaX, muonThetaX_Err, muonThetaY, muonThetaY_Err, universe+1 );
    recoShifter->GetShift_ccqe_muonPT_muonThetaXY( muPT_shift, muonP, muonTheta, muonThetaX, muonThetaX_Err, muonThetaY, muonThetaY_Err, universe+1 );
    recoShifter->GetShift_ccqe_muonPZ_muonThetaXY( muPZ_shift, muonP, muonTheta, muonThetaX, muonThetaX_Err, muonThetaY, muonThetaY_Err, universe+1 );

    muTheta_shift *= (180/3.14159); //Degrees
    muPT_shift /= 1000.; // GeV
    muPZ_shift /= 1000.; // GeV
    
  }
    
  //----------------------------------------------------------------------------------------------------
  // Does the "shifted in value" event pass the Non-Vtx Recoil vs Q2 cut? (shifts in MeV^2 and MeV)
  //----------------------------------------------------------------------------------------------------
  bool passRecoilCut = cutter->pass1DMECCQESelection( event, sample, primaryProton_scoreShift, secProtons_scoreShifts, muQ2_shift, recoil_shift );
  //  cout << "Doing muon vars " << passRecoilCut  << "\t" << istrue<< endl;
  // Convert Q2 to GeV^2 and enu GeV
  // recoilshift /= pow(10,3);
  muQ2_shift /= pow(10,6);
  enu_shift /= pow(10,3);
  // Filling recoil_lat_shifts not necessary here since they have been initialized to 0.0 
  // and recoilshift here is 0.0 
  //-----------------------------------------------------
  // Fill lateral shifts w.r.t muon kinematics 
  // Systematics with N Universes
  //-----------------------------------------------------
  if( passRecoilCut ){
    (*tmu_lat_shifts)[name]->at(universe) = istrue ? 0.0 : muT_shift; //GeV
    (*theta_lat_shifts)[name]->at(universe) = istrue ? 0.0 : muTheta_shift; //Degrees
    (*pT_lat_shifts)[name]->at(universe) = istrue ? 0.0 : muPT_shift; //GeV
    (*pZ_lat_shifts)[name]->at(universe) = istrue ? 0.0 : muPZ_shift; //GeV
    (*q2_lat_shifts)[name]->at(universe) = istrue ? 0.0 : muQ2_shift; //GeV^2
    (*enu_lat_shifts)[name]->at(universe) = istrue ? 0.0 : enu_shift; //GeV^2
  } else {
    (*tmu_lat_shifts)[name]->at(universe) = MnvHist::NotPhysicalShiftNumber;
    (*theta_lat_shifts)[name]->at(universe) = MnvHist::NotPhysicalShiftNumber;
    (*pT_lat_shifts)[name]->at(universe) = MnvHist::NotPhysicalShiftNumber;
    (*pZ_lat_shifts)[name]->at(universe) = MnvHist::NotPhysicalShiftNumber;
    (*q2_lat_shifts)[name]->at(universe) = MnvHist::NotPhysicalShiftNumber;
    (*enu_lat_shifts)[name]->at(universe) = MnvHist::NotPhysicalShiftNumber;
  }

} // End of method fillLatErrorBandShiftsMuonVar 


void CCQENuUtils::fillLatErrorBandShiftsParticleResponse( CCQENuEvent* event, string name, int universe, string sample, bool istrue ) { 

  double muQ2_shift    = 0.0; 
  double recoil_shift  = 0.0; 
  double enu_shift  = 0.0; 

  double primaryProton_scoreShift = 0.0; 
  double *secProtons_scoreShifts = NULL;  

  getQ2Shift( muQ2_shift, event, name, universe ); 

  getEnuShift( enu_shift, event, name, universe ); 
  
  if( name == "Proton_Response" ) {
    
    // Get shift due to proton response
    double recoilError = event->part_response_recoil_proton_id_err;
    // Do not consider cases when the +1 sigma shift is < 0 (-1)
    recoilError = (recoilError>0)? recoilError : 0;
    recoShifter->GetShift_ccqe_recoilE( recoil_shift, recoilError, universe+1 );
/*
  } else if( name == "Low_Neutron_Response" ) {
    
    // Get shift due to low neutron response (KE < 50 MeV)
    double recoilError = event->part_response_recoil_low_neutron_id_err;
    // Do not consider cases when the +1 sigma shift is < 0 (-1)
    recoilError = (recoilError>0)? recoilError : 0;
    recoShifter->GetShift_ccqe_recoilE( recoil_shift, recoilError, universe+1 );

  } else if( name == "Mid_Neutron_Response" ) {

    // Get shift due to  mid neutron response (50 < KE < 150 MeV)
    double recoilError = event->part_response_recoil_mid_neutron_id_err;
    // Do not consider cases when the +1 sigma shift is < 0 (-1)
    recoilError = (recoilError>0)? recoilError : 0;
    recoShifter->GetShift_ccqe_recoilE( recoil_shift, recoilError, universe+1 );

  } else if( name == "High_Neutron_Response" ) {
    
    // Get shift due to high neutron response ( KE > 150 MeV )
    double recoilError = event->part_response_recoil_high_neutron_id_err;
    // Do not consider cases when the +1 sigma shift is < 0 (-1)
    recoilError = (recoilError>0)? recoilError : 0;
    recoShifter->GetShift_ccqe_recoilE( recoil_shift, recoilError, universe+1 );
*/    
  } else if( name == "Pion_Response" ) {
    
    // Get shift due to a 5% variation of pion response
    double recoilError = event->part_response_recoil_meson_id_err;
    // Do not consider cases when the +1 sigma shift is < 0 (-1)
    recoilError = (recoilError>0)? recoilError : 0;
    recoShifter->GetShift_ccqe_recoilE( recoil_shift, recoilError, universe+1 );

  } else if( name == "Muon_Response" ) {
    
    // Get shift due to a 5% variation of pion response
    double recoilError = event->part_response_recoil_muon_id_err;
    // Do not consider cases when the +1 sigma shift is < 0 (-1)
    recoilError = (recoilError>0)? recoilError : 0;
    recoShifter->GetShift_ccqe_recoilE( recoil_shift, recoilError, universe+1 );
    
  } else if( name == "EM_Response" ) {
    
    // Get shift due to EM response
    double recoilError = event->part_response_recoil_em_id_err;
    // Do not consider cases when the +1 sigma shift is < 0 (-1)
    recoilError = (recoilError>0)? recoilError : 0;
    recoShifter->GetShift_ccqe_recoilE( recoil_shift, recoilError, universe+1 );

  } else if( name == "Other_Response" ) {
    
    // Get shift due to a other particles response
    double recoilError = event->part_response_recoil_other_id_err;
    // Do not consider cases when the +1 sigma shift is < 0 (-1)
    recoilError = (recoilError>0)? recoilError : 0;
    recoShifter->GetShift_ccqe_recoilE( recoil_shift, recoilError, universe+1 );
    
  } /*else if( name == "Crosstalk" ) {

    // Get shift due to xtalk 
    double recoilError = event->part_response_recoil_xtalk_id_err;
    // Do not consider cases when the +1 sigma shift is < 0 (-1)
    recoilError = (recoilError>0)? recoilError : 0;
    recoShifter->GetShift_ccqe_recoilE( recoil_shift, recoilError, universe+1 );

  }Already have Xtalk in GENIE Variation Sample*/ /*else if( name == "MEU_Recoil" ) {

    //Get shift due to MEU factor in Recoil
    double nonVtx_recoil = (event->nonvtx_iso_blobs_energy + event->dis_id_energy) / pow(10, 3); //GeV 
    double recoilError = nonVtx_recoil * 0.024; // assuming 2.4% variance on MEU  
    recoilError = (recoilError>0)? recoilError : 0;
    recoShifter->GetShift_ccqe_recoilE( recoil_shift, recoilError, universe+1 );
    
  }*//*Not needed, TB particle responses should be enough, do not double count*/
  
  //----------------------------------------------------------------------------------------------------
  // Does the "shifted in value" event pass the Non-Vtx Recoil vs Q2 cut? (shifts in MeV^2 and MeV)
  //----------------------------------------------------------------------------------------------------
  bool passRecoilCut = cutter->pass1DMECCQESelection( event, sample, primaryProton_scoreShift, secProtons_scoreShifts, muQ2_shift, recoil_shift );

  // Convert mQ2_shift to GeV^2 and enu to GeV. Keep recoil_shift in MeV
  muQ2_shift /= pow(10,6);
  enu_shift /= pow(10,3);
  //-----------------------------------------------
  // Fill recoil lateral shifts (MeV)
  //-----------------------------------------------
  (*recoil_lat_shifts)[name]->at(universe) = istrue ? 0.0 : recoil_shift; 
  
  if( !passRecoilCut ) { 
    (*tmu_lat_shifts)[name]->at(universe)   = MnvHist::NotPhysicalShiftNumber;
    (*theta_lat_shifts)[name]->at(universe) = MnvHist::NotPhysicalShiftNumber;
    (*pT_lat_shifts)[name]->at(universe)    = MnvHist::NotPhysicalShiftNumber;
    (*pZ_lat_shifts)[name]->at(universe)    = MnvHist::NotPhysicalShiftNumber;
    (*q2_lat_shifts)[name]->at(universe)    = MnvHist::NotPhysicalShiftNumber;
    (*enu_lat_shifts)[name]->at(universe)    = MnvHist::NotPhysicalShiftNumber;
  }

} // End of method fillLatErrorBandShiftsParticleResponse  


void CCQENuUtils::fillLatErrorBandShiftsProtonScore( CCQENuEvent* event, string name, int universe, string sample, bool istrue ) { 

  double primaryProton_scoreShift = 0.0; 
  double *secProtons_scoreShifts = NULL;  
  
  double muQ2_shift    = 0.0; 
  double recoil_shift  = 0.0; 
  double enu_shift     = 0.0; 

  getQ2Shift( muQ2_shift, event, name, universe );
  getEnuShift( enu_shift, event, name, universe );

  // TO DO !!!!! 
  // What do we do if universe > 1 since this is a void function ? 
  // What to do if +1 sigma shift is <0 ? 

  if( name == "Bethe_Bloch" ) { 
    
    // Get shift in proton score from variations in Bethe-Bloch 
    if( universe == 0 ) { 
      primaryProton_scoreShift      = event->CCQENu_proton_score1_BetheBloch_biasUp; 
      secProtons_scoreShifts        = event->CCQENu_sec_protons_score1_BetheBloch_biasUp; 
    } else { 
      primaryProton_scoreShift      = event->CCQENu_proton_score1_BetheBloch_biasDown; 
      secProtons_scoreShifts        = event->CCQENu_sec_protons_score1_BetheBloch_biasDown; 
    }
  } else if( name == "MEU_Proton" ) { 
    
    // Get shift in proton score from variations in MEU scale  
    if( universe == 0 ) { 
      primaryProton_scoreShift      = event->CCQENu_proton_score1_MEU_biasUp; 
      secProtons_scoreShifts        = event->CCQENu_sec_protons_score1_MEU_biasUp; 
    } else { 
      primaryProton_scoreShift      = event->CCQENu_proton_score1_MEU_biasDown; 
      secProtons_scoreShifts        = event->CCQENu_sec_protons_score1_MEU_biasDown; 
    }    
  } else if( name == "Mass_Model_Proton" ) { 

    // Get shift in proton score from variations in Mass Model estimates 
    if( universe == 0 ) { 
      primaryProton_scoreShift      = event->CCQENu_proton_score1_Mass_biasUp; 
      secProtons_scoreShifts        = event->CCQENu_sec_protons_score1_Mass_biasUp; 
    } else { 
      primaryProton_scoreShift      = event->CCQENu_proton_score1_Mass_biasDown; 
      secProtons_scoreShifts        = event->CCQENu_sec_protons_score1_Mass_biasDown; 
    }
  } else if( name == "Birks_Response_Proton" ) { 
    
    // Get shift in proton score from variations in Birk's Response 
    primaryProton_scoreShift        = event->CCQENu_proton_score1_Birks_bias; 
    secProtons_scoreShifts          = event->CCQENu_sec_protons_score1_Birks_bias; 
  }

  //----------------------------------------------------------------------------------------------------
  // Does the "shifted in value" event pass the Non-Vtx Recoil vs Q2 cut? (shifts in MeV^2 and MeV)
  //----------------------------------------------------------------------------------------------------
  bool passRecoilCut = cutter->pass1DMECCQESelection( event, sample, primaryProton_scoreShift, secProtons_scoreShifts, muQ2_shift, recoil_shift );

  // Convert Q2 to GeV^2 and enu to GeV. Keep recoil_shift in MeV  
  muQ2_shift /= pow(10,6);
  enu_shift /= pow(10,3);
  // Filling recoil_lat_shifts not necessary here since they have been initialized to 0.0 
  // and recoil_shift here is 0.0 
  
  //-----------------------------------------------------
  // If event does not pass Non-Vtx Recoil vs. Q2 cut 
  //-----------------------------------------------------
  if( !passRecoilCut ) { 
    (*tmu_lat_shifts)[name]->at(universe) = MnvHist::NotPhysicalShiftNumber;
    (*theta_lat_shifts)[name]->at(universe) = MnvHist::NotPhysicalShiftNumber;
    (*pT_lat_shifts)[name]->at(universe) = MnvHist::NotPhysicalShiftNumber;
    (*pZ_lat_shifts)[name]->at(universe) = MnvHist::NotPhysicalShiftNumber;
    (*q2_lat_shifts)[name]->at(universe) = MnvHist::NotPhysicalShiftNumber;
    (*enu_lat_shifts)[name]->at(universe) = MnvHist::NotPhysicalShiftNumber;
  }

} // End of method fillLatErrorBandShiftsProtonScore 


void CCQENuUtils::fillLatErrorBandShiftsBindingEnergy( CCQENuEvent* event, string name, int universe, string sample, bool istrue ) { 

  double primaryProton_scoreShift = 0.0; 
  double *secProtons_scoreShifts = NULL;  
  
  double muQ2_shift    = 0.0; 
  double recoil_shift  = 0.0; 

  //Is this how we would do it ? Do this and below line with recoShifter ? Hmmm ... not sure  
  getQ2Shift( muQ2_shift, event, name, universe );

  double bindingE = 0.0; 
  if( event->CCQENu_nuHelicity == 1 /*neutrino*/ ){
    bindingE = 34.;//MeV
  } else if( event->CCQENu_nuHelicity == 2 /*antineutrino*/ ){
    bindingE = 30.;//MeV
  } else {
    cout << "Zero binding energy. No reconstructed muon charge?" << endl;
  }
 
  // get shift due to binding energy  
  double muonP = event->CCQENu_muon_P; // MeV
  double muonTheta = event->CCQENu_muon_theta; //rad
  double bindingE_Err = 5.0; // MeV 

  //if( name == "Binding_Energy" ) { 
  recoShifter->GetShift_ccqe_q2_bindingEnergy( muQ2_shift, muonP, muonTheta, bindingE, bindingE_Err, universe+1 ); 
    //}

  //----------------------------------------------------------------------------------------------------
  // Does the "shifted in value" event pass the Non-Vtx Recoil vs Q2 cut? (shifts in MeV^2)
  //----------------------------------------------------------------------------------------------------
  bool passRecoilCut = cutter->pass1DMECCQESelection( event, sample, primaryProton_scoreShift, secProtons_scoreShifts, muQ2_shift, recoil_shift );
  
  // Convert Q2 to GeV^2 
  muQ2_shift /= pow(10,6);

  //-----------------------------------------------
  // Fill Q2 lateral shifts (MeV)
  //-----------------------------------------------
  if( passRecoilCut ) { 
    (*q2_lat_shifts)[name]->at(universe) = istrue ? 0.0 : muQ2_shift; 
  } else {   
    (*tmu_lat_shifts)[name]->at(universe)   = MnvHist::NotPhysicalShiftNumber;
    (*theta_lat_shifts)[name]->at(universe) = MnvHist::NotPhysicalShiftNumber;
    (*pT_lat_shifts)[name]->at(universe)    = MnvHist::NotPhysicalShiftNumber;
    (*pZ_lat_shifts)[name]->at(universe)    = MnvHist::NotPhysicalShiftNumber;
    (*recoil_lat_shifts)[name]->at(universe)    = MnvHist::NotPhysicalShiftNumber;
  }

}  // End of method fillLatErrorBandShiftsBindingEnergy  


void CCQENuUtils::fillLatErrorBandShifts( CCQENuEvent* event, string name, int nUniverse, string sample, bool isTrue ) { 


  fillLatErrorBandShiftsMuonVar( event, name, nUniverse, sample, isTrue ); 

  fillLatErrorBandShiftsParticleResponse( event, name, nUniverse, sample, isTrue ); 

  //fillLatErrorBandShiftsBindingEnergy( event, name, nUniverse, sample, isTrue ); 

  if( nUniverse < 2 ) { 
    fillLatErrorBandShiftsProtonScore( event, name, nUniverse, sample, isTrue ); 
  } 


} // End of method fillLatErrorBandShifts  


void CCQENuUtils::getQ2Shift( double &q2shift, CCQENuEvent *event, string name, int universe ){

  // set binding energy for CCQE-hypothesis Q2
  double bindingE = 0.;
  if( event->CCQENu_nuHelicity == 1 /*neutrino*/ ){
    bindingE = 34.;//MeV
  } else if( event->CCQENu_nuHelicity == 2 /*antineutrino*/ ){
    bindingE = 30.;//MeV
  } else {
    cout << "Zero binding energy. No reconstructed muon charge?" << endl;
  }

  if( name == "Muon_Energy" ){

    // get shift due to muon momentum 
    double muonP = event->CCQENu_muon_P; // MeV
    double muonTheta = event->CCQENu_muon_theta; //rad
    double muonPErr = event->CCQENu_sys_muon_energy_shift[1]; // MeV
    recoShifter->GetShift_ccqe_q2_muonP( q2shift, muonP, muonTheta, bindingE, muonPErr, universe+1 );

  } else if( name == "Muon_Theta" ){

    // get shift due to muon angle 
    double muonP = event->CCQENu_muon_P; // MeV
    double muonTheta = event->CCQENu_muon_theta; //rad
    
    //This direct change to polar angle is not desired. Shifts in X and Y components are required  
    //double muonThetaErr = 0.002; //rad
    
    double muonThetaX = event->muon_thetaX; //rad
    double muonThetaY = event->muon_thetaY; //rad
    double muonThetaX_Err = 0.001;  //rad (error on beam angleX correction from Edgar Valencia's DocDB 11550) 
    double muonThetaY_Err = 0.0009; //rad (error on beam angleY correction from Edgar Valencia's DocDB 11550)
   
    recoShifter->GetShift_ccqe_q2_muonThetaXY( q2shift, muonP, muonTheta, bindingE, muonThetaX, muonThetaX_Err, muonThetaY, muonThetaY_Err, universe+1 );
    
  } /*else if( name == "Binding_Energy" ){ 

    // get shift due to binding energy 
    double muonP = event->CCQENu_muon_P; //MeV 
    double muonTheta = event->CCQENu_muon_theta; //rad 
    double bindingE_Err = 5.0; // MeV 

    recoShifter->GetShift_ccqe_q2_bindingEnergy( q2shift, muonP, muonTheta, bindingE, bindingE_Err, universe+1 ); 
  }*//*Do not use Binding Energy for shifting Q2. */

  //q2shift /= pow(10,6); //GeV^2

}


void CCQENuUtils::getEnuShift( double &enushift, CCQENuEvent *event, string name, int universe ){

  // set binding energy for CCQE-hypothesis Q2
  double bindingE = 0.;
  if( event->CCQENu_nuHelicity == 1 /*neutrino*/ ){
    bindingE = 34.;//MeV
  } else if( event->CCQENu_nuHelicity == 2 /*antineutrino*/ ){
    bindingE = 30.;//MeV
  } else {
    cout << "Zero binding energy. No reconstructed muon charge?" << endl;
  }

  if( name == "Muon_Energy" ){

    // get shift due to muon momentum 
    double muonP = event->CCQENu_muon_P; // MeV
    double muonTheta = event->CCQENu_muon_theta; //rad
    double muonPErr = event->CCQENu_sys_muon_energy_shift[1]; // MeV
    recoShifter->GetShift_ccqe_nuE_muonP( enushift, muonP, muonTheta, bindingE, muonPErr, universe+1 );

  } else if( name == "Muon_Theta" ){

    // get shift due to muon angle 
    double muonP = event->CCQENu_muon_P; // MeV
    double muonTheta = event->CCQENu_muon_theta; //rad
    
    //This direct change to polar angle is not desired. Shifts in X and Y components are required  
    double muonTheta_Err = 0.002; //rad
    
    // double muonThetaX = event->muon_thetaX; //rad
    // double muonThetaY = event->muon_thetaY; //rad
    // double muonThetaX_Err = 0.001;  //rad (error on beam angleX correction from Edgar Valencia's DocDB 11550) 
    // double muonThetaY_Err = 0.0009; //rad (error on beam angleY correction from Edgar Valencia's DocDB 11550)
    recoShifter->GetShift_ccqe_nuE_muonTheta( enushift, muonP, muonTheta, bindingE, muonTheta_Err, universe+1 );
    
  }

}

//============================================================================
// NameHistos
//============================================================================
void CCQENuUtils::nameHistos( MnvH1D** h,string var_name,string title ){

  for( unsigned int i = 0; i < nHistos; i++ )
  {
    if (h[i] != NULL)
    {
      h[i]->SetName((var_name+Form("_%s",names[i].c_str())).c_str() );
      h[i]->SetTitle(title.c_str());
    }
    else
      cout<<Form("CCQENuUtils::nameHistos[Warning]: %s_%s address is NULL",var_name.c_str(), names[i].c_str() ) << endl;
  }
}

void CCQENuUtils::nameHistos( MnvH2D** h,string var_name,string title ){

  for( unsigned int i = 0; i < nHistos; i++ )
  {
    if (h[i] != NULL)
    {
      h[i]->SetName((var_name+Form("_%s",names[i].c_str())).c_str() );
      h[i]->SetTitle(title.c_str());
    }
    else
      cout<<Form("CCQENuUtils::nameHistos[Warning]: %s_%s address is NULL",var_name.c_str(), names[i].c_str() ) << endl;
  }
}

void CCQENuUtils::getResponseObjects(MinervaUnfold::MnvResponse* response, MnvH2D*& h_migration, MnvH2D*& h_reco, MnvH2D*& h_truth)
{
  bool status = false;
  status = response->GetMigrationObjects( h_migration, h_reco, h_truth );
  if (!status)
    Error("CCQENuUtils::getResponseObjects", Form("Could not get migration objects for %s histograms", names[kQELike].c_str() ) ); 

  // for( unsigned int i = 0; i< nHistos; i++)
  // {
  //   if ( names[i] == "data" ) continue;
  //   status = response[i]->GetMigrationObjects( h_migration[i], h_reco[i], h_truth[i] );
  //   if (!status)
  //     Error("CCQENuUtils::getResponseObjects", Form("Could not get migration objects for %s histograms", names[i].c_str() ) ); 
  // }

}
/*
template void CCQENuUtils::applyFluxConstraint<MnvH1D, MnvVertErrorBand>( MnvH1D*& histo );
template<class MnvHistoType,class MnvResponse, class MnvVertErrBandType>
*/
void CCQENuUtils::splitObject(MnvH2D* orig, MnvH2D** histos) 
{ 

  //loop over vert and transfer
  vector<string> vert_names = orig->GetVertErrorBandNames();
  for(uint i=0;i<vert_names.size();i++){
    histos[i] = new MnvH2D(orig->GetCVHistoWithStatError());
    string name = orig->GetName();
    name+="_vert_";
    name+=vert_names[i];
    histos[i]->SetName(name.c_str());
    orig->TransferVertErrorBand(histos[i],vert_names[i],true);
  }

  //loop over lat and transfer
  vector<string> lat_names = orig->GetLatErrorBandNames();
  for(uint i=0;i<lat_names.size();i++){
    histos[i+vert_names.size()] = new MnvH2D(orig->GetCVHistoWithStatError());
    string name = orig->GetName();
    name+="_lat_";
    name+=lat_names[i];
    histos[i+vert_names.size()]->SetName(name.c_str());
    orig->TransferLatErrorBand(histos[i+vert_names.size()],lat_names[i],true);
  }
  

}

void CCQENuUtils::combineObject(MnvH2D* temp, MnvH2D*& target, string prefix, TFile* source_file){
  vector<string> vert_names = temp->GetVertErrorBandNames();
  vector<string> lat_names = temp->GetLatErrorBandNames();
  for(uint i=0;i<vert_names.size();i++){
    string name = prefix+"_vert_"+vert_names[i];
    cout << "vert: " << name << endl;
    MnvH2D* src = (MnvH2D*)source_file->Get(name.c_str());
    if(i==0){
      target = new MnvH2D(*src);
      target->SetName(prefix.c_str());
      target->SetTitle(prefix.c_str());
    }
    else src->TransferVertErrorBand(target,vert_names[i],false);
  }
  for(uint i=0;i<lat_names.size();i++){
    string name = prefix+"_lat_"+lat_names[i];
    cout << "lat: " << name << endl;
    MnvH2D* src = (MnvH2D*)source_file->Get(name.c_str());
    src->TransferLatErrorBand(target,lat_names[i],false);
  }
  

}


/*
void CCQENuUtils::updatePlaylistNorm(const CCQENuEvent *event)
{
  //Update playlist corrections according to respective run numbers
  //This is currently available for playlists 1, 7, 9 and 13 (LE-FHC) 

  //Will store values for low and high momenta 
  //Lookup using dummy values for minos track momentum 
  const double lowP  = MnvNorm::minosP_minos_trk_eff_threshP / 2.0; 
  const double highP = MnvNorm::minosP_minos_trk_eff_threshP * 2.0; 
  
    mnvNormalizer->LoadPlaylist( *myPlaylist );
    c_normWgt_low  = mnvNormalizer->GetCorrection( lowP ); 
    c_normWgt_high = mnvNormalizer->GetCorrection( highP ); 
    c_normWgtErr_low  = mnvNormalizer->GetCorrectionErr( lowP ); 
    c_normWgtErr_high = mnvNormalizer->GetCorrectionErr( highP ); 
}
*/
void CCQENuUtils::updatePlaylistNorm(const CCQENuEvent *event)
{
  double effWgt = 1.0;

  double batch_pot = 0.;
  if(event->batch_structure==0 || event->batch_structure==3) batch_pot = event->numi_pot/6.;
  if(event->batch_structure==1 && event->reco_vertex_batch < 3) batch_pot = event->numi_pot/4.;
  if(event->batch_structure==1 && event->reco_vertex_batch > 2) batch_pot = event->numi_pot/8.;
  if(event->batch_structure==2 && event->reco_vertex_batch < 5) batch_pot = event->numi_pot/5.;
  if(event->batch_structure==2 && event->reco_vertex_batch > 4) batch_pot = event->numi_pot/10.;

  c_normWgt_low  = MinosMuonEfficiencyCorrection::Get().GetCorrection(event->CCQENu_minos_trk_p, batch_pot);
  c_normWgt_high = MinosMuonEfficiencyCorrection::Get().GetCorrection(event->CCQENu_minos_trk_p, batch_pot);
  c_normWgtErr_low  = MinosMuonEfficiencyCorrection::Get().GetCorrectionErr(event->CCQENu_minos_trk_p,event->CCQENu_muon_theta*(180.0/3.1415),batch_pot);
  c_normWgtErr_high = MinosMuonEfficiencyCorrection::Get().GetCorrectionErr(event->CCQENu_minos_trk_p,event->CCQENu_muon_theta*(180.0/3.1415),batch_pot);

}

std::string CCQENuUtils::printArachneLink(const CCQENuEvent *event, bool isData)
{
  std::string arachnelink;

  const int run = isData ? event->ev_run : event->mc_run ;
  const int subrun = isData? event->ev_subrun : event->mc_subrun ;
  const int gate = isData ? event->ev_gate : event->mc_nthEvtInFile+1 ;
  const int slice = event->slice_numbers[0];
  TString filename =  event->GetCurrentFileName();
  filename.ReplaceAll("_Tuple_","_DST_");
  filename.ReplaceAll("/ana/","/dst/");


  if( isData ){
    arachnelink = Form("http://mnvevd1.fnal.gov/Arachne/arachne.html?entry=0&slice=%i&filename=%s&&selection=(ev_run==%i)*(ev_sub_run==%i)*(ev_gate==%i)", slice, filename.Data(), run, subrun, gate);
  }
  else{
    arachnelink = Form("http://mnvevd1.fnal.gov/Arachne/arachne.html?entry=0&slice=%i&filename=%s&&selection=(mc_run==%i)*(mc_subrun==%i)*(mc_spill==%i)", slice, filename.Data(), run, subrun, gate);
  }

  return arachnelink;
}

void CCQENuUtils::loadFluxConstraint() 
{ 

  if( !GlobalParameters::Get().m_neutrinoMode ) throw std::runtime_error( "Flux constraint available for neutrino mode (FHC) only" ); 
  cout << "Loading flux constraint" << endl; 

  m_fluxConstrainer = new MnvHistoConstrainer();
  m_fluxConstrainer->LoadConstraint( "nu+e", Form( "%s/FluxConstraints/nu+e_eroica.txt", getenv( "MPARAMFILES" ) ) ); 
  
  std::vector<string> genieKnobNames = GetGenieKnobNames(); 
  for( std::vector<string>::iterator itName = genieKnobNames.begin(); itName != genieKnobNames.end(); ++itName ) { 
    m_fluxConstrainer->SetSpectatorCorrectionStrategy( *itName, MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  }
  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Normalization_Factors", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Reweight_Pion", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Reweight_Proton", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Reweight_Neutron", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR );
 
  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Muon_Energy", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Muon_Theta", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 

  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Proton_Response", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  //m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Low_Neutron_Response", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  //m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Mid_Neutron_Response", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  //m_fluxConstrainer->SetSpectatorCorrectionStrategy( "High_Neutron_Response", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Pion_Response", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Muon_Response", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "EM_Response", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Other_Response", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Crosstalk", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  //m_fluxConstrainer->SetSpectatorCorrectionStrategy( "MEU_Recoil", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 

  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Bethe_Bloch", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "MEU_Proton", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Mass_Model_Proton", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Birks_Response_Proton", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 

  //m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Binding_Energy", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Target_Mass", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Michel_Efficiency", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 
  m_fluxConstrainer->SetSpectatorCorrectionStrategy( "Proton_TrackEff", MnvHistoConstrainer::PRESERVE_FRACTIONAL_ERR ); 

}

//============================================================================
// ApplyFluxConstraint
//============================================================================
// The pointer is passed by reference for the function to replace the input histogram, hence the "&" 
template<class MnvHistoType, class MnvVertErrBandType>
 void CCQENuUtils::applyFluxConstraint( MnvHistoType*& histo ) 
{ 

  if( !GlobalParameters::Get().m_neutrinoMode ) throw std::runtime_error( "Flux constraint available for neutrino mode (FHC) only" ); 
  std::string histoName = histo->GetName(); 
  bool isDataHisto = false; 
  if( histoName.find("data") != std::string::npos ) isDataHisto = true; 
  if( !isDataHisto ) { 
    if( histo->HasVertErrorBand( "Flux" ) ) { 
      cout << Form( "Applying flux constraint to \"%s\"", histo->GetName() ) << endl; 

      MnvHistoType* constrainedHisto = m_fluxConstrainer->ConstrainHisto<MnvHistoType, MnvVertErrBandType>( histo );
      // delete the old histogram and point 'histo' at the new one
      delete histo;
      histo = constrainedHisto;
    }
  }

} //End of applyFluxConstraint
template void CCQENuUtils::applyFluxConstraint<MnvH1D, MnvVertErrorBand>( MnvH1D*& histo );
template void CCQENuUtils::applyFluxConstraint<MnvH2D, MnvVertErrorBand2D>( MnvH2D*& histo );


#endif 
