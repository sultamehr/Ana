#include "include/CCQENuUtils.h"
#include "PlotUtils/ArachneUtils.h"
#include "TError.h"

using namespace CCQENU_ANA;

int MakeArachneLinks( string filename, int n_files = -1, bool isMC = true){

  CCQENuUtils  *utils  = new CCQENuUtils( true, false );
  CCQENuCuts   *cutter = new CCQENuCuts();

  //gErrorIgnoreLevel = kBreak;
  TChain* tree = NULL;
  if (isMC) { 
    cout<<" Using MC" <<endl;
    tree  = utils->getMCTree( "CCQENu", n_files );
    filename = "MC_"+filename; 
  } else {
    cout << "Using DATA" << endl;
    tree  = utils->getDataTree( "CCQENu", n_files ); 
    filename = "DATA_"+filename; 
  }

  int entries = tree->GetEntries();
  if (isMC) cout << "MC entries: " << entries << endl;
  else cout << "DATA entries: " << entries << endl;
  
  CCQENuEvent* event = new CCQENuEvent( tree, !isMC );

  int nevents = 0;
  ofstream links;
  links.open( filename.c_str() );

  string arachnelink(""); 

  for( int i = 0; i < entries; ++i ) {
    
    event->GetEntry(i);
  
    //----------------------------------------------------------------------------------
    // Defining our cuts here. Remember these events are for studying the 
    // efficiency of two track events. 
    // N.B.: We always require 1 muon with a vertex in the fiducial volume
    // Inorder to have CCQE-like events, throw away events with Michel electrons 
    //----------------------------------------------------------------------------------
    if( !cutter->passDeadTimeCuts( event ) ) continue;
    if( !cutter->passNuHelicityCut( event )) continue;
    if( !cutter->passMichelAtInteractionVertexCut( event ) )    continue;
    
    double vtx_energy     = event->vtx_blobs_energy / pow(10,3); //GeV
    double nonvtx_energy = (event->nonvtx_iso_blobs_energy + event->dis_id_energy) / pow(10,3); //GeV
    double muon_energy = event->CCQENu_muon_E / pow(10,3); //GeV

    double total_energy = vtx_energy + nonvtx_energy + muon_energy;
    if( total_energy > 5.0 ) continue;
    
    nevents++;
    arachnelink =utils->printArachneLink( event, !isMC ); 
    links << arachnelink.c_str() << endl; 
    
  } //end of tree loop
 
  links.close();
  return 0; 
}
 

//====================================================
// main
//
//====================================================

int main( int argc, char *argv[] ) {

  ROOT::Cintex::Cintex::Enable();   
  if (argc==1){
    std::cout<<"----------------------------------------------------------------------------------------------------"<< std::endl;
    std::cout<<"MACROS HELP:\n\n"<<
      "./ArachneLinks_2trackeff  Name_and_path_to_Output_file  Number_of_files  MC_or_DATA \n\n"<<
      "\t-Name_and_path_to_Output_file\t =\t Name of and path to the Output TEXT file that will be created \n"<<
      "\t-Number_of_files\t =\t Number of MonteCarlo or Data files. To use all files, set this to: -1 \n"<<
      "\t-MC_or_DATA\t =\t If DATA use: 0; If MC use: 1 \n"<< std::endl; 
    std::cout<<"---------------------------------------------------------------------------------------------------"<< std::endl;
    return 0; 
  }

  //! Default parameters
  std::vector<std::string> par;
  par.push_back("ArachneLinks_2trackeff");
  par.push_back( Form("%s/ana/arachnelinks/arachnelinks",getenv("CCQENUROOT") ) );
  par.push_back("-1");
  par.push_back("1");

  std::cout << endl << "Firing up ArachneLinks_2trackeff ....." << std::endl;
  //! Set user parameters
  for( int i=0; i<argc; ++i){
    par.at(i) = argv[i];
  }

  for( unsigned int i=0; i<par.size(); ++i)
    std::cout<<"Parameter "<< i << " : " << par[i] << std::endl;
  
  return MakeArachneLinks(par[1], atoi( par[2].c_str() ), atoi( par[3].c_str() ) );
}
