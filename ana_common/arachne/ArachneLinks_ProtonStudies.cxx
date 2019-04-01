#include "include/CCQENuUtils.h"
#include "PlotUtils/ArachneUtils.h"
#include "TError.h"

using namespace CCQENU_ANA;

int MakeArachneLinks( string filename, int n_files = -1, bool isMC = true, double energyLowLimit = 0.0, double energyHighLimit = 1000.0 ) {

  CCQENuUtils  *utils  = new CCQENuUtils( true, false );
  CCQENuCuts   *cutter = new CCQENuCuts();

  //gErrorIgnoreLevel = kBreak;
  TChain* tree = NULL;
  if (isMC) { 
    cout << "Using MC" << endl;
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
 
    //--------------------------------------------------------------------------
    // Defining our selection cuts here
    //N.B.: We always require 1 muon with a vertex in the fiducial volume
    //--------------------------------------------------------------------------
    if( !cutter->passDeadTimeCuts( event ) )         continue;
    if( !cutter->passNuHelicityCut( event ) )        continue;
    if( !(event->multiplicity>=2) )                  continue; 
    if( !cutter->passSingleProtonCut( event ) )      continue; 
    if( !cutter->passExtraProtonsCut( event ) )      continue; 
    if( !cutter->passMichelCut( event ) )            continue; 
    if( !cutter->passNBlobs( event ) )               continue; 
    if( !cutter->passEnuCut( event ) )                continue;
    if( !cutter->passSignalFunction( event, 0, 0 ) ) continue; 
    
    //--------------------------------------------------------------------------------
    // Make Arachne links for events that have large amounts of energy in the form 
    // of clusters at the end of the reconstructed proton track 
    //--------------------------------------------------------------------------------
    // double calibEClustersProtonEnd = (event->calibE_clusters_at_end_proton_prong)[0]; 
    // if( calibEClustersProtonEnd > energyLowLimit || calibEClustersProtonEnd < energyHighLimit ) continue; //energy is in MeV 
    

    //--------------------------------------------------------------------------------------
    // Make Arachne links for events that have low proton range scores and low cluster 
    // energies at the end of the proton track. Assumption is that low score is due to 
    // proton interacting/showering/scattering which implies that there should be more 
    // energy off the track.Probing why there is less of it. 
    //--------------------------------------------------------------------------------------
    double calibEClustersProtonEnd = (event->calibE_clusters_at_end_proton_prong)[0]; 
    double proton_range_score1 = event->CCQENu_proton_score1; 

    if( proton_range_score1 > 0.1 || calibEClustersProtonEnd > energyLowLimit ) continue; 

    nevents++;
    arachnelink = utils->printArachneLink( event, !isMC ); 
    links << arachnelink.c_str() << endl; 

  } //end of tree loop
  
  links.close();
  return 0; 
}
 
//====================================================
// Main function caller 
//====================================================
int main( int argc, char *argv[]) { 

  ROOT::Cintex::Cintex::Enable();   
  if (argc==1) {
    std::cout<<"----------------------------------------------------------------------------------------------------------------"<< std::endl;
    std::cout<<"MACROS HELP:\n\n"<<
      "./ArachneLinks_ProtonStudies Name_and_path_to_Output_file Number_of_files MC_or_DATA Proton_Cluster_Energy_Lower_Limit Proton_Cluster_Energy_Higher_Limit \n\n"<<
      "\t-Name_and_path_to_Output_file\t =\t Name of and path to the Output text file that will be created  \n"<<
      "\t-Number_of_files\t =\t Number of MonteCarlo or Data files. To use all files, set this to: -1 \n"<<
      "\t-MC_or_DATA\t =\t If DATA use: 0; If MC use: 1 \n"<<
      "\t-Proton_Cluster_Energy_Lower_Limit\t=\t Value in MeV of the lower energy limit (above which you would like Arachne links made) \n\n"<< 
      "\t-Proton_Cluster_Energy_Higher_Limit\t=\t Value in MeV of the higher energy limit (below which you would like Arachne links made) \n\n"<< std::endl; 
    std::cout<<"---------------------------------------------------------------------------------------------------------------"<< std::endl; 
    return 0; 
  }

  //------------------------
  // Default parameters
  //------------------------
  std::vector<std::string> par;
  par.push_back("ArachneLinks_ProtonStudies");
  par.push_back( Form("%s/ana/textfiles/ArachneLinks_ProtonStudies.txt",getenv("CCQENUROOT") ) );
  par.push_back("-1");
  par.push_back("1");
  par.push_back("700.0"); 
  par.push_back("1000.0"); 
  
  std::cout << endl << "Firing up ArachneLinks_ProtonStudies ....." << std::endl;
  for( int i = 0; i<argc; ++i ) { 
    par.at(i) = argv[i]; 
  }

  for( unsigned int i=0; i<par.size(); ++i ) 
    std::cout << "Parameter " << i << " : " << argv[i] << std::endl;
  
  return MakeArachneLinks(par[1], atoi(par[2].c_str()), atoi(par[3].c_str()), atof(par[4].c_str()), atof(par[5].c_str()) ); 
}
