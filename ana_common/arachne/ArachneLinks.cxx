#include "include/CCQENuUtils.h"
#include "PlotUtils/ArachneUtils.h"
#include "TError.h"
#include "stdio.h"

using namespace CCQENU_ANA;

int MakeArachneLinks( string filename, int n_files = -1, int isMC = 1 ){

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

  int nevents_1track = 0;
  int nevents_2track = 0;
  ofstream links_1track;
  ofstream links_2track;
  links_1track.open( (filename+"_1track.txt").c_str() );
  links_2track.open( (filename+"_2track.txt").c_str() );

  string arachnelink("");
  for( int i = 0; i < entries; ++i ) {

    event->GetEntry(i);
 
  // 1-track case
    if( cutter->passDeadTimeCuts( event )  &&
        cutter->passNuHelicityCut( event ) &&
        (event->multiplicity==1)           &&
        cutter->passMichelCut( event )     &&
        cutter->passNBlobs( event )        &&
        //cutter->passEnuCut( event )        &&
	cutter->passSignalFunction( event, 0, 0 ) /*&&*/ 
	//(event->muon_minerva_trk_chi2PerDoF <= 1.0) 
	)
    {
      nevents_1track++;
      arachnelink = utils->printArachneLink( event, !isMC );
      cout << "n_nonvtx_iso_blobs " << event->n_nonvtx_iso_blobs << endl; 
      links_1track << arachnelink.c_str() << endl; 
    }

    // 2-track case
    if( cutter->passDeadTimeCuts( event )    &&
        cutter->passNuHelicityCut( event )   &&
        (event->multiplicity>=2)             &&
        cutter->passSingleProtonCut( event ) &&
        cutter->passExtraProtonsCut( event ) &&
        cutter->passMichelCut( event )       &&
        cutter->passNBlobs( event )          &&
        //cutter->passEnuCut( event )          &&
        cutter->passSignalFunction( event, 0, 0 ) /*&&*/  
	//(event->muon_minerva_trk_chi2PerDoF <= 1.0) 
	)
    {
      nevents_2track++;
      arachnelink = utils->printArachneLink( event, !isMC );
      cout << "n_nonvtx_iso_blobs " << event->n_nonvtx_iso_blobs << endl; 
      links_2track << arachnelink.c_str() << endl; 
    }
  } //end of tree loop
 
  cout <<"One track events: " << nevents_1track <<" "<<"Two track events: " << nevents_2track << endl; 
  links_1track.close();
  links_2track.close();

  return 0;
}
 
//====================================================
// main
//
//====================================================

int main( int argc, char *argv[]) {
  ROOT::Cintex::Cintex::Enable();   
  if (argc==1){
    std::cout<<"-----------------------------------------------------------------------------------------------"<< std::endl;
    std::cout<<"MACROS HELP:\n\n"<<
      "\t-./ArachneLinks  Name_and_path_to_Output_file  Number_of_files  MC_or_DATA \n\n"<<
      "\t-Name_and_path_to_Output_file\t =\t Name of and path to the Output TEXT file that will be created \n"<<
      "\t-Number_of_files\t =\t Number of MonteCarlo or Data files. To use all files, set this to: -1 \n"<< 
      "\t-MC_or_DATA\t =\t If DATA use: 0; If MC use: 1 \n"<< std::endl; 
    std::cout<<"-----------------------------------------------------------------------------------------------"<< std::endl;
    return 0; 
  }

  //! Default parameters
  std::vector<std::string> par;
  par.push_back("ArachneLinks");
  par.push_back( Form("%s/ana/arachnelinks/arachnelinks",getenv("CCQENUROOT") ) );
  par.push_back("-1");
  par.push_back("1");

  std::cout << endl << "Firing up ArachneLinks ....." << std::endl;
  //! Set user parameters
  for( int i=0; i<argc; ++i){
    par.at(i) = argv[i];
  }

  for( unsigned int i=0; i<par.size(); ++i)
    std::cout<<"Parameter "<< i << " : " << par[i] << std::endl;

  return MakeArachneLinks(par[1], atoi( par[2].c_str() ), atoi( par[3].c_str() ) );
}
