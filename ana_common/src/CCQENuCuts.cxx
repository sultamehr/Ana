#ifndef MNV_CCQENUCUTS_cxx
#define MNV_CCQENUCUTS_cxx 1

#include "include/CCQENuCuts.h"
using namespace CCQENU_ANA;

/*ccqe1 track from paper q2 vs unattached
double CCQENuCuts::f_recoil_cut_nu_1track(double *x, double *p) {

  double result = 0;

  if( x[0] < 0.166 )
    result = 0.05;
  else if( x[0] < 1.61 ) 
    result = ( -0.05 + 0.64*x[0] - 0.22*x[0]*x[0] );
  else
    result = 0.41;

  return p[0]*( p[1] + result );

}
*/
/*ccqe - needs to polish q2 vs unattached
double CCQENuCuts::f_recoil_cut_nu_1track(double *x, double *p) {

  double result = 0;

  if( x[0] < 0.29 )
    result = 0.03;
  else if( x[0] < 1.50 )
    result = ( -0.05 + 0.64*x[0] - 0.22*x[0]*x[0] );
  else
    result = 0.51;

  return p[0]*( p[1] + result );

}
*/
//ccqe-like function cut based on 95% efficiency
double f_recoil_cut_nu_1track(double *x, double *p) {

  double result = 0;

  if ( CCQENuCuts::use_muonPt_vs_unattachedE_analysiscut )
  {
    /* 0.99 eff
    if( x[0] < 0.4375 )
      result = 0.18;
    else if( x[0] < 1.09 )
      result = 0.0488467 + 0.304038*x[0];
    else
      result = 0.38;
    */
    /* 0.97 eff */
    if( x[0] < 0.3125 )
      result = 0.1;
    else if( x[0] < 1.3125 )
      result = 0.02571 + 0.239908*x[0];
    else
      result = 0.34;

  }
  else if ( CCQENuCuts::use_muonT_vs_unattachedE_analysiscut )
  {
    if( x[0] < 1 )
      result = 0.14; // 0.0
    else if( x[0] < 1.75)
      result = 0.14;
    else if( x[0] < 6.5)
      result = -0.141581 + 0.18826*x[0] - 0.016872*pow(x[0],2) + 0.00024847*pow(x[0],3);
    else
      result = 0.4375;
  }
  else if( CCQENuCuts::use_q2_vs_unattachedE_analysiscut )
  {
  /* 95% Efficiency for all tracks sample
   * That means, function is optimized for both, 1 and 2 track samples
    if( x[0] < 1.6 )
      result =  0.100238 + 0.232411*x[0] - 0.0139368*pow(x[0],2) - 0.0234053*pow(x[0],3);
    else
      result = 0.3405;
  }

  */
  // 95% Efficiency for 1 track sample only
  // This means, function is optimized for 1 and 2 tracks separatedly
  /*
  if( x[0] < 0.1 )
    result = 0.138579;
  else
    result = 0.105441 + 0.300962*x[0] - 0.0442502*pow(x[0],2) - 0.0107347*pow(x[0],3);
  }
  */
  // 93% Efficiency for 1 track sample only
  // This means, function is optimized for 1 and 2 tracks separatedly
    /*    
  if( x[0] < 0.1 )
    result = 0.11;
  else
    result = 0.0811773 + 0.327679*x[0] - 0.0927141*pow(x[0],2);
    */
    
    result = 0.5;
  }
  return p[0]*( p[1] + result ) + 0.05;
}

//ccqe-like function cut based on maximum eff*pur signal
double f_recoil_cut_nu_2track(double *x, double *p) {

  double result = 0;


  if ( CCQENuCuts::use_muonPt_vs_unattachedE_analysiscut )
  {
    /* 0.97 eff */
    if( x[0] < 0.3125 )
      result = 0.1;
    else if( x[0] < 1.3125 )
      result = 0.02571 + 0.239908*x[0];
    else
      result = 0.34;
  }
  else if ( CCQENuCuts::use_muonT_vs_unattachedE_analysiscut)
  {
    if( x[0] < 1 )
      result = 0.14; // 0.0
    else if( x[0] < 1.75)
      result = 0.14;
    else if( x[0] < 6.5)
      result = -0.141581 + 0.18826*x[0] - 0.016872*pow(x[0],2) + 0.00024847*pow(x[0],3);
    else
      result = 0.4375;
  }
  else if( CCQENuCuts::use_q2_vs_unattachedE_analysiscut )
  {
  /* 95% Efficiency for all tracks sample
   * That means, function is optimized for both, 1 and 2 track samples
    if( x[0] < 1.6 )
      result =  0.100238 + 0.232411*x[0] - 0.0139368*pow(x[0],2) - 0.0234053*pow(x[0],3);
    else
      result = 0.3405;
  }
  */
  // 95% Efficiency for 2 track sample only
  // This means, function is optimized for 1 and 2 tracks separatedly
  /*
  if( x[0] < 1.6 )
    result = 0.206383 + 0.108676*x[0] - 0.151462*pow(x[0],2) + 0.191616*pow(x[0],3) - 0.0652131*pow(x[0],4);
  else
    result = 0.35;
  */
  // 93% Efficiency for 2 track sample only
  // This means, function is optimized for 1 and 2 tracks separatedly
  /*
  if( x[0] < 0.3)
    result = 0.21;
  else if( x[0] < 1.62)
    result = 0.1919 + 0.060686*x[0];
  else
    result = 0.29;
  */
  //result = 0.19;
  // 93% Efficiency for 2 track sample only, but priorize purity for first 5 bins
  // because 1 track events have most of statisics for those anyway
  // This means, function is optimized for 1 and 2 tracks separatedly
    /*
  if( x[0] < 0.29)
    result = 0.11;
  else if( x[0] < 1.45)
    result = 0.0122151 + 0.387161*x[0] - 0.135084*pow(x[0],2);
  else
    result = 0.2895;
    */
  result = 0.5;
  }
  
 return p[0]*( p[1] + result ) + 0.05;
}
/*
//ccqe-like function cut based on maximum 95%eff q2 vs unattachedE
double CCQENuCuts::f_recoil_cut_nu(double *x, double *p) {

  double result = 0;

  if( x[0] < 0.148 )
    result = 0.09;
  else if( x[0] < 1.4 )
    result =  0.0331118 + 0.492681*x[0] - 0.174512*x[0]*x[0];
  else
    result = 0.38;

  return p[0]*( p[1] + result );

}

//ccqe-like function cut based on maximum 95% eff
double CCQENuCuts::f_recoil_cut_nu_2track(double *x, double *p) {

  double result = 0;
  if( x[0] < 0.6 )
    result = 0.22;
  else
    result = 0.14 + 0.153333*x[0] - 0.0333333*x[0]*x[0];

  return p[0]*( p[1] + result );
}
*/

CCQENuCuts::CCQENuCuts() :
   nu_helicity_cut(1),
   multiplicity(100),
   nblobs_max(1),
   proton_score(0.35),
   cutline_signal_1track(NULL),
   cutline_signal_mev_1track(NULL),
   cutline_sideband_1track(NULL),
   cutline_sideband_mev_1track(NULL),
   cutline_signal_2track(NULL),
   cutline_signal_mev_2track(NULL),
   cutline_sideband_2track(NULL),
   cutline_sideband_mev_2track(NULL){};

  //! Destructor
CCQENuCuts::~CCQENuCuts()
{
  if( cutline_signal_1track ) delete cutline_signal_1track;
  if( cutline_signal_mev_1track ) delete cutline_signal_mev_1track;

  if( cutline_sideband_1track ) delete cutline_sideband_1track;
  if( cutline_sideband_mev_1track ) delete cutline_sideband_mev_1track;
  if( cutline_signal_2track ) delete cutline_signal_2track;
  if( cutline_signal_mev_2track ) delete cutline_signal_mev_2track;

  if( cutline_sideband_2track ) delete cutline_sideband_2track;
  if( cutline_sideband_mev_2track ) delete cutline_sideband_mev_2track;

}

CCQENuCuts& CCQENuCuts::Get(){
  static CCQENuCuts singleton;
  return singleton;
}

bool CCQENuCuts::passInteractionVertex( CCQENuEvent* event ){
  if(event->has_interaction_vertex!=1) return false;
  return true;
}


bool CCQENuCuts::passNuHelicityCut( CCQENuEvent* event ){
  if( event->CCQENu_nuHelicity != nu_helicity_cut ) return false;
  return true;
}

bool CCQENuCuts::passDeadTimeCuts( CCQENuEvent* event ){
  if( event->phys_n_dead_discr_pair_upstream_prim_track_proj > tdead_max ) return false;
  return true;
}

bool CCQENuCuts::passMultiplicity( CCQENuEvent *event ){
  if( event->multiplicity > multiplicity ) return false;
  //if( event->multiplicity != multiplicity ) return false;
  //cout<< "multiplicity = " << event->multiplicity << endl;
  return true;
}
bool CCQENuCuts::passMichelAtInteractionVertexCut( CCQENuEvent *event ){

   bool nomichel_invertex = false;
   if (event->has_michel_vertex_type_sz==0) nomichel_invertex = true;
   else{
     for( int i=0; i<event->has_michel_vertex_type_sz; ++i){
       if (event->has_michel_vertex_type[i]==0)
         nomichel_invertex = true;
     }
   }
 
   return nomichel_invertex;
}

/* Works for rejecting ALL michel views  */
bool CCQENuCuts::passMichelCut( CCQENuEvent *event, bool alternate_cuts ){

  bool has_michel = false;
  if (event->has_michel_category_sz>0){
    for( int i=0; i<event->has_michel_category_sz; ++i){

      if( alternate_cuts ) {

	bool pass_energy_cut  = (event->has_michel_energy[i] <= 55.0)? true: false;
	bool pass_ndigits_cut = (event->has_michel_ndigits[i] <= 35 )? true: false;
	bool pass_slices_cut  = (event->has_michel_slice_energy[i] <= 100 )? true: false;                                                                   

	bool pass_energy_ndigits_upper_cut = (event->has_michel_ndigits[i] < (0.7 * event->has_michel_energy[i]+3) ) ? true : false;
	bool pass_energy_ndigits_lower_cut = (event->has_michel_ndigits[i] > (0.2 * event->has_michel_energy[i]-1) ) ? true : false;

	if( pass_energy_cut && pass_ndigits_cut && pass_slices_cut && pass_energy_ndigits_upper_cut && pass_energy_ndigits_lower_cut) has_michel = true;

      }
      else
	has_michel = true;

    }
  }

  if (has_michel) return false;
  else return true;

}

bool CCQENuCuts::passImprovedMichelCut( CCQENuEvent *event, bool alternate_cuts ){

  bool improved_michel = false;
  if (event->improved_michel_vertex_type_sz>0)improved_michel = true;

  if (improved_michel) return false;
  else return true;

}

/*Reject only 2-3 view michels
bool CCQENuCuts::passMichelCut( CCQENuEvent *event ){

  bool has_2v_3v_michel = false;
  if (event->has_michel_category_sz>0){
    for( int i=0; i<event->has_michel_category_sz; ++i){
      //if( event->has_michel_category[i]==2 || event->has_michel_category[i]==3) has_2v_3v_michel = true;
      if( event->has_michel_category[i]==3) has_2v_3v_michel = true;
    }
  }
  
  if (has_2v_3v_michel) return false;
  else return true;

}
*/

bool CCQENuCuts::passSingleProtonCut( CCQENuEvent* event, double scoreShift, double q2Shift ) {

  // Keep around 81% efficiency in each Q2 region
  bool pass_proton = false;

  double q2_reco = event->CCQENu_Q2 + q2Shift; 
  q2_reco /= pow(10,6); 

  double protonScore1_reco = event->CCQENu_proton_score1 + scoreShift; 
  if( q2_reco < 0.1 ) {
    if( protonScore1_reco > 0.25 ) pass_proton = true;

  } else if( q2_reco >= 0.1 && q2_reco < 0.2 ) {
    if( protonScore1_reco > 0.20 ) pass_proton = true;

  } else if( q2_reco >= 0.2 && q2_reco < 0.75 ) {
    if( protonScore1_reco > 0.1 ) pass_proton = true;

  } else if( q2_reco >= 0.75 ) {
    //if( protonScore1_reco > 0.0) pass_proton = true;
    pass_proton = true; 
  }


  return pass_proton;
}

bool CCQENuCuts::passSingleProton1DMECut( CCQENuEvent* event, double scoreShift, double q2Shift ) {

  bool pass_proton = false;

  double q2_reco = event->CCQENu_Q2 + q2Shift; 
  q2_reco /= pow(10,6); 

  double protonScore1_reco = event->CCQENu_proton_score1 + scoreShift; 
  //if( protonScore1_reco > 0.1 ) pass_proton = true;
  if( q2_reco < 0.2 ) {
    if( protonScore1_reco > 0.2 ) pass_proton = true;
  } else if( q2_reco >= 0.2 && q2_reco < 0.6 ) {
    if( protonScore1_reco > 0.1 ) pass_proton = true;
  } else if( q2_reco >= 0.6 ) {
    if( protonScore1_reco > 0.0) pass_proton = true;
    pass_proton = true; 
  }

  return pass_proton;
}

//Extra tracks (other than the muon and primary proton) are required to be
//protons with a score greater than the imposed limits 
bool CCQENuCuts::passExtraProtonsCut( CCQENuEvent* event, double* scoreShifts, double q2Shift ) {
  
  bool extra_tracks_are_all_protons = true;
  
  double q2_reco = event->CCQENu_Q2 + q2Shift; 
  q2_reco /= pow(10,6); 
  
  double secProtons_protonScore1_reco = 0.0; 
  
  //-------------------------------------------------
  // Exit if there are no secondary protons 
  //-------------------------------------------------
  if( event->CCQENu_sec_protons_proton_scores1_sz == 0 )  { 
    return true; 
  } else {
    for( int i=0; i<event->CCQENu_sec_protons_proton_scores1_sz; ++i ) { 
      
      //------------------------------------------------------------------
      // scoreShifts[] will be NULL for the CV Monte-Carlo and Data ! 
      //------------------------------------------------------------------
      if( scoreShifts==NULL ) { 
	secProtons_protonScore1_reco = event->CCQENu_sec_protons_proton_scores1[i]; 
      } else { 
	secProtons_protonScore1_reco = event->CCQENu_sec_protons_proton_scores1[i] + scoreShifts[i]; 
      }
      if( q2_reco < 0.1 ) {
	if( secProtons_protonScore1_reco < 0.25 ) extra_tracks_are_all_protons = false;
	
      } else if( q2_reco >= 0.1 && q2_reco < 0.2 ) {
	if( secProtons_protonScore1_reco < 0.20 ) extra_tracks_are_all_protons = false;
	
      } else if( q2_reco >= 0.2 && q2_reco < 0.75 ) {
	if( secProtons_protonScore1_reco < 0.1 ) extra_tracks_are_all_protons = false;
	
      } else if( q2_reco >= 0.75 ) {
	if( secProtons_protonScore1_reco < 0.0 ) extra_tracks_are_all_protons = false;
      }
    }

  }
  return extra_tracks_are_all_protons;
}

bool CCQENuCuts::passExtraProtons1DMECut( CCQENuEvent* event, double* scoreShifts, double q2Shift ) {
  
  bool extra_tracks_are_all_protons = true;
  double secProtons_protonScore1_reco = 0.0; 
  double q2_reco = event->CCQENu_Q2 + q2Shift; 
  q2_reco /= pow(10,6); 
  
  //-------------------------------------------------
  // Exit if there are no secondary protons 
  //-------------------------------------------------
  if( event->CCQENu_sec_protons_proton_scores1_sz == 0 )  { 
    return true; 
  } else {
    
    for( int i=0; i<event->CCQENu_sec_protons_proton_scores1_sz; ++i ) { 
      
      //------------------------------------------------------------------
      // scoreShifts[] will be NULL for the CV Monte-Carlo and Data ! 
      //------------------------------------------------------------------
      if( scoreShifts==NULL ) { 
	secProtons_protonScore1_reco = event->CCQENu_sec_protons_proton_scores1[i]; 
      } else { 
	secProtons_protonScore1_reco = event->CCQENu_sec_protons_proton_scores1[i] + scoreShifts[i]; 
      }
      //if( secProtons_protonScore1_reco < 0.1 ) extra_tracks_are_all_protons = false;
      if( q2_reco < 0.2 ) {
	if( secProtons_protonScore1_reco < 0.2 ) extra_tracks_are_all_protons = false;
      } else if( q2_reco >= 0.2 && q2_reco < 0.6 ) {
	if( secProtons_protonScore1_reco < 0.1 ) extra_tracks_are_all_protons = false;
      } else if( q2_reco >= 0.6 ) {
	if( secProtons_protonScore1_reco < 0.0 ) extra_tracks_are_all_protons = false;
      }
	
    }
  }
  return extra_tracks_are_all_protons;
}

//Extra tracks (which are not part of the primary interaction vertex, but are in time) are required to be
//protons with a score greater than the imposed limits 
bool CCQENuCuts::passExtraTracksProtonsCut( CCQENuEvent* event, double* scoreShifts, double q2Shift ) {
  
  bool extra_tracks_are_all_protons = true;
  
  double q2_reco = event->CCQENu_Q2 + q2Shift; 
  q2_reco /= pow(10,6); 
  
  double extraTracks_protonScore1_reco = 0.0; 
  
  //-------------------------------------------------
  // Exit if there are no secondary protons 
  //-------------------------------------------------
  if( event->event_extra_track_PID_sz == 0 )  { 
    return true; 
  } else {
    for( int i=0; i<event->event_extra_track_PID_sz; ++i ) { 
      //------------------------------------------------------------------
      // scoreShifts[] will be NULL for the CV Monte-Carlo and Data ! 
      //------------------------------------------------------------------
      if( scoreShifts==NULL ) { 
	extraTracks_protonScore1_reco = event->event_extra_track_PID[i]; 
      } else { 
	extraTracks_protonScore1_reco = event->event_extra_track_PID[i] + scoreShifts[i]; 
      }
     
      if( extraTracks_protonScore1_reco < 0.25 ) extra_tracks_are_all_protons = false;
    }
  }
  return extra_tracks_are_all_protons;
}

/*
bool CCQENuCuts::passSingleProtonCut( CCQENuEvent* event, double scoreShift, double q2Shift ) {

  //Keep around 81% efficiency in each Q2 region
  bool pass_proton = false;
  if( event->CCQENu_Q2/pow(10,6)<0.2){
    if( event->CCQENu_proton_score1 > 0.35 ) pass_proton = true;
  }
  else if(event->CCQENu_Q2/pow(10,6)>=0.2 && event->CCQENu_Q2/pow(10,6)<0.4){
    if(  event->CCQENu_proton_score1 > 0.35 ) pass_proton = true;
  }
  else if( event->CCQENu_Q2/pow(10,6)>=0.4 && event->CCQENu_Q2/pow(10,6)<0.8){
    if( event->CCQENu_proton_score1 > 0.35 ) pass_proton = true;
  }
  else if( event->CCQENu_Q2/pow(10,6)>=0.8){
    if( event->CCQENu_proton_score1 > 0.35 ) pass_proton = true;
  }

  return pass_proton;
}

//Extra tracks (other than the muon and primary proton) are required to be
//protons with a score greater than 0.55
bool CCQENuCuts::passExtraProtonsCut( CCQENuEvent* event, double* scoreShifts, double q2Shift ) {

  bool extra_tracks_are_all_protons = true;

  if( event->CCQENu_extra_protons_proton_scores1_sz == 0 ) return true;
  else{
    for( int i=0; i<event->CCQENu_extra_protons_proton_scores1_sz; ++i){
      if(  event->CCQENu_Q2/pow(10,6)<0.2 ){
        if( event->CCQENu_extra_protons_proton_scores1[i] < 0.35 ) extra_tracks_are_all_protons = false;
      }
      else if( event->CCQENu_Q2/pow(10,6)>=0.2 && event->CCQENu_Q2/pow(10,6)<0.4){
        if( event->CCQENu_extra_protons_proton_scores1[i] < 0.35 ) extra_tracks_are_all_protons = false;
      }
      else if( event->CCQENu_Q2/pow(10,6)>=0.4 && event->CCQENu_Q2/pow(10,6)<0.8){
        if( event->CCQENu_extra_protons_proton_scores1[i] < 0.35 ) extra_tracks_are_all_protons = false;
      }
      else if( event->CCQENu_Q2/pow(10,6)>=0.8){
        if( event->CCQENu_extra_protons_proton_scores1[i] < 0.35 ) extra_tracks_are_all_protons = false;
      }
    }
  }

  return extra_tracks_are_all_protons;
}
*/


bool CCQENuCuts::passNBlobs( CCQENuEvent *event ){
  int n_blobs = 0;
  for(int k=0; k<event->nonvtx_iso_blobs_start_position_z_in_prong_sz; ++k){
    if(event->nonvtx_iso_blobs_start_position_z_in_prong[k] > 4750) n_blobs++;
  }
  if( n_blobs > nblobs_max ) return false;
  return true;
}

/*
bool CCQENuCuts::passNBlobs( CCQENuEvent *event ){
  double n_nonvtx_iso_blobs = event->n_nonvtx_iso_blobs;
  if( event->n_nonvtx_iso_blobs > nblobs_max ) return false;
  for(int k=0; k<event->vtx_blobs_iso_distance_in_prong_sz; ++k){
     double iso_energy_fraction = event->vtx_blobs_iso_energy_clusters_outside_radius_in_prong[k]/event->vtx_blobs_iso_energy_in_prong[k];
     if( iso_energy_fraction>0.1 && 
         event->vtx_blobs_iso_distance_in_prong[k]<300.){
       n_nonvtx_iso_blobs++;
     }
  }

  if (n_nonvtx_iso_blobs > nblobs_max) return false;
  return true;

}
*/
bool CCQENuCuts::passUnattachedEnergyCut( CCQENuEvent *event ){
  if( (event->nonvtx_iso_blobs_energy + event->dis_id_energy) > 10. ) return false;
  return true;
}

bool CCQENuCuts::passTrackAngleCut( CCQENuEvent *event){
  if( event->muon_theta_allNodes[20] > 0.349 ) return false;
  return true;
}

bool CCQENuCuts::passTrackPzCut( CCQENuEvent *event){
  double muon_theta     = event->muon_theta_allNodes[20]; // get theta from 20th node
      
  double reco_muon_px   =  event->CCQENu_leptonE[0];
  double reco_muon_py   =  event->CCQENu_leptonE[1];
  double reco_muon_pz   =  event->CCQENu_leptonE[2];
  double muon_p         = sqrt(pow(reco_muon_px,2) + pow(reco_muon_py,2) + pow(reco_muon_pz,2)) / pow(10,3); //GeV
  //New method (maybe temporary)
  double muon_pt_beam = sin(muon_theta)*muon_p;
  double muon_pz_beam = cos(muon_theta)*muon_p;

  if( muon_pt_beam > 15.0 ) return false;
  return true;
}

bool CCQENuCuts::passTrueCCQE( CCQENuEvent* event ){
  return passTrueCCQE( event->mc_incoming, event->mc_current, event->mc_intType, event->mc_charm );
}

bool CCQENuCuts::passTrueCCQE( CCQENuTruth* event ){
  return passTrueCCQE( event->mc_incoming, event->mc_current, event->mc_intType, event->mc_charm );
}

bool CCQENuCuts::passTrueCCQE( int pdg, int current, int type, bool charm ){
  return ( pdg == 14 && current == 1 && type == 1 && !charm );
}

bool CCQENuCuts::passTrueCCRES( CCQENuEvent* event ){
  return passTrueCCRES( event->mc_incoming, event->mc_current, event->mc_intType );
}

bool CCQENuCuts::passTrueCCRES( CCQENuTruth* event ){
  return passTrueCCRES( event->mc_incoming, event->mc_current, event->mc_intType );
}

bool CCQENuCuts::passTrueCCRES( int pdg, int current, int type ){
  return ( pdg == 14 && current == 1 && type == 2 );
}

bool CCQENuCuts::passTrueCCDIS( CCQENuEvent* event ){
  return passTrueCCDIS( event->mc_incoming, event->mc_current, event->mc_intType );
}

bool CCQENuCuts::passTrueCCDIS( CCQENuTruth* event ){
  return passTrueCCDIS( event->mc_incoming, event->mc_current, event->mc_intType );
}

bool CCQENuCuts::passTrueCCDIS( int pdg, int current, int type ){
  return ( pdg == 14 && current == 1 && type == 3 );
}

bool CCQENuCuts::passTrueMEC( CCQENuEvent* event ){
  return passTrueMEC( event->mc_incoming, event->mc_current, event->mc_intType, event->mc_charm );
}

bool CCQENuCuts::passTrueMEC( CCQENuTruth* event ){
  return passTrueMEC( event->mc_incoming, event->mc_current, event->mc_intType, event->mc_charm );
}

bool CCQENuCuts::passTrueMEC( int pdg, int current, int type, bool charm ){
    return ( pdg == 14 && current == 1 && type == 8 && !charm );
}

bool CCQENuCuts::passMECnn( CCQENuEvent* event ){
  return passMECnn( event->mc_incoming, event->mc_current, event->mc_intType, event->mc_charm, event->mc_targetNucleon );
}

bool CCQENuCuts::passMECnn( CCQENuTruth* event ){
  return passMECnn( event->mc_incoming, event->mc_current, event->mc_intType, event->mc_charm, event->mc_targetNucleon);
}

bool CCQENuCuts::passMECnn( int pdg, int current, int type, bool charm , int nucleonhit){
  return ( pdg == 14 && current == 1 && type == 8 && !charm && nucleonhit-2000000200==0);
}

bool CCQENuCuts::passMECnp( CCQENuEvent* event ){
  return passMECnp( event->mc_incoming, event->mc_current, event->mc_intType, event->mc_charm, event->mc_targetNucleon );
}

bool CCQENuCuts::passMECnp( CCQENuTruth* event ){
  return passMECnp( event->mc_incoming, event->mc_current, event->mc_intType, event->mc_charm, event->mc_targetNucleon);
}

bool CCQENuCuts::passMECnp( int pdg, int current, int type, bool charm , int nucleonhit){
  return ( pdg == 14 && current == 1 && type == 8 && !charm && nucleonhit-2000000200==1);
}

bool CCQENuCuts::passMECpp( CCQENuEvent* event ){
  return passMECpp( event->mc_incoming, event->mc_current, event->mc_intType, event->mc_charm, event->mc_targetNucleon );
}

bool CCQENuCuts::passMECpp( CCQENuTruth* event ){
  return passMECpp( event->mc_incoming, event->mc_current, event->mc_intType, event->mc_charm, event->mc_targetNucleon);
}

bool CCQENuCuts::passMECpp( int pdg, int current, int type, bool charm , int nucleonhit){
  return ( pdg == 14 && current == 1 && type == 8 && !charm && nucleonhit-2000000200==2);
}


bool CCQENuCuts::passTrueCCQELike( int* mc_FSPartPDG, double* mc_FSPartE, int mc_nFSPart )
{
  int genie_n_muons         = 0;
  int genie_n_mesons        = 0;
  int genie_n_heavy_baryons_plus_pi0s = 0;
  int genie_n_photons       = 0;

  for(int i = 0; i < mc_nFSPart; ++i) {
    int pdg =  mc_FSPartPDG[i];
    double energy = mc_FSPartE[i]; 

    //The photon energy cut is hard-coded at 10 MeV at present. We're happy to make it general, if the need arises ! 
    if( abs(pdg) == 13 ) genie_n_muons++;
    else if( pdg == 22 && energy >10 ) genie_n_photons++;
    else if( abs(pdg) == 211 || abs(pdg) == 321 || abs(pdg) == 323 || pdg == 111 || pdg == 130 || pdg == 310 || pdg == 311 || pdg == 313 ) genie_n_mesons++;
    else if( pdg == 3112 || pdg == 3122 || pdg == 3212 || pdg == 3222 || pdg == 4112 || pdg == 4122 || pdg == 4212 || pdg == 4222 || pdg == 411 || pdg == 421 || pdg == 111 ) genie_n_heavy_baryons_plus_pi0s++;
  }

  //Definition of CCQE-like: 1 muon (from neutrino) and no mesons/heavy baryons in final state
  //Any number of final state nucleons (protons or neutrons) allowed
  //Photons from nuclear de-excitation are kept. These tend to be < 10 MeV. Events with photons from other sources are excluded. 
  //GENIE simulates nuclear de-excitations only for Oxygen atoms at present.  
  if( genie_n_muons         == 1 && 
      genie_n_mesons        == 0 && 
      genie_n_heavy_baryons_plus_pi0s == 0 && 
      genie_n_photons       == 0 ) return true;
  return false;
}

bool CCQENuCuts::passTrueCCQELike( CCQENuEvent* event ){
  return ( event->mc_incoming==14 && event->mc_current==1 && passTrueCCQELike( event->mc_FSPartPDG, event->mc_FSPartE, event->mc_nFSPart ) );//ccqelike
  //return passTrueCCQE( event->mc_incoming, event->mc_current, event->mc_intType, event->mc_charm );//ccqe
}

bool CCQENuCuts::passTrueCCQELike( CCQENuTruth* event ){
  return ( event->mc_incoming==14 && event->mc_current==1 && passTrueCCQELike( event->mc_FSPartPDG, event->mc_FSPartE, event->mc_nFSPart ) );//ccqelike
  //return passTrueCCQE( event->mc_incoming, event->mc_current, event->mc_intType, event->mc_charm );//ccqe
}

bool CCQENuCuts::passTrueSingleChargedPion(CCQENuEvent* event){
  return passTrueSingleChargedPion(event->mc_nFSPart, event->mc_FSPartPDG);
}

bool CCQENuCuts::passTrueSingleChargedPion(CCQENuTruth* event){
  return passTrueSingleChargedPion(event->mc_nFSPart, event->mc_FSPartPDG);
}

bool CCQENuCuts::passTrueSingleChargedPion(int nfspart, int* fspartPDG){
  int num_pion = 0;
  int num_charged_pion = 0;
  for(int i = 0; i < nfspart; i++){
    if(  fspartPDG[i]  == 211 || fspartPDG[i] == -211 ){
      num_charged_pion++;
      num_pion++;
    }
    if(  fspartPDG[i]  == 111 ){
      num_pion++;
    }
  }
  if(num_charged_pion==1 && num_pion==1) return true; //only found 1 pion and it was charged
  return false;
}

bool CCQENuCuts::passTrueSingleNeutralPion(CCQENuEvent* event){
  return passTrueSingleNeutralPion(event->mc_nFSPart, event->mc_FSPartPDG);
}

bool CCQENuCuts::passTrueSingleNeutralPion(CCQENuTruth* event){
  return passTrueSingleNeutralPion(event->mc_nFSPart, event->mc_FSPartPDG);
}

bool CCQENuCuts::passTrueSingleNeutralPion(int nfspart, int* fspartPDG){
  int num_pion = 0;
  int num_neutral_pion = 0;
  for(int i = 0; i < nfspart; i++){
    if(  fspartPDG[i]  == 211 || fspartPDG[i] == -211 ){
      num_pion++;
    }
    if(  fspartPDG[i]  == 111 ){
      num_neutral_pion++;
      num_pion++;
    }
  }
  if(num_neutral_pion==1 && num_pion==1) return true; //only found 1 pion and it was neutral
  return false;
}


bool CCQENuCuts::passTrueMultiPion(CCQENuEvent* event){
  return passTrueMultiPion(event->mc_nFSPart, event->mc_FSPartPDG, event->mc_er_nPart, event->mc_er_ID, event->mc_er_status);
}

bool CCQENuCuts::passTrueMultiPion(CCQENuTruth* event){
  return passTrueMultiPion(event->mc_nFSPart, event->mc_FSPartPDG, event->mc_er_nPart, event->mc_er_ID, event->mc_er_status);
}

bool CCQENuCuts::passTrueMultiPion(int nfspart, int* fspartPDG, int nerpart, int* erpartID, int* erpartstatus){
  if( passTrueSingleChargedPion( nfspart, fspartPDG)|| passTrueSingleNeutralPion( nfspart, fspartPDG) ) return false; //Already ID'd as a single pion event
  int num_pion = 0;
  bool found_eta = false;
  for(int i = 0; i < nfspart; i++){
    if(  fspartPDG[i]  == 211 || fspartPDG[i] == -211 || fspartPDG[i] == 111){
      num_pion++;
    }
  }
  
  for(int i = 0; i < nerpart; i++){
    if( erpartstatus[i] == 14 && erpartID[i] == 221){
      found_eta = true;
      break;
    }
  }

  if(num_pion>1||found_eta) return true; //only found 1 pion and it was charged
  return false;
}




bool CCQENuCuts::passTruePositivePion(CCQENuEvent* event){
  return passTruePositivePion(event->mc_nFSPart, event->mc_FSPartPDG);
}

bool CCQENuCuts::passTruePositivePion(CCQENuTruth* event){
  return passTruePositivePion(event->mc_nFSPart, event->mc_FSPartPDG);
}

bool CCQENuCuts::passTruePositivePion(int nfspart, int* fspartPDG){
  for(int i = 0; i < nfspart; i++)
    if(  fspartPDG[i]  == 211 ) return true;

  return false;
}

bool CCQENuCuts::passTrueNegativePion(CCQENuEvent* event){
  return passTrueNegativePion(event->mc_nFSPart, event->mc_FSPartPDG);
}

bool CCQENuCuts::passTrueNegativePion(CCQENuTruth* event){
  return passTrueNegativePion(event->mc_nFSPart, event->mc_FSPartPDG);
}

bool CCQENuCuts::passTrueNegativePion(int nfspart, int* fspartPDG){
  //positive pions have priority
  if ( passTruePositivePion( nfspart, fspartPDG ) ) return false;
  for(int i = 0; i < nfspart; i++)
    if(  fspartPDG[i]  == -211 ) return true;

  return false;
}

bool CCQENuCuts::passTrueNeutralPion(CCQENuEvent* event){
  return passTrueNeutralPion(event->mc_nFSPart, event->mc_FSPartPDG);
}

bool CCQENuCuts::passTrueNeutralPion(CCQENuTruth* event){
  return passTrueNeutralPion(event->mc_nFSPart, event->mc_FSPartPDG);
}

bool CCQENuCuts::passTrueNeutralPion(int nfspart, int* fspartPDG){
  //charged pions have priority
  if ( passTruePositivePion( nfspart, fspartPDG ) || passTrueNegativePion( nfspart, fspartPDG ) ) return false;
  for(int i = 0; i < nfspart; i++)
   if( fspartPDG[i] == 111 ) return true;

  return false;
}

bool CCQENuCuts::passTruePion(CCQENuEvent* event){
  return passTruePion(event->mc_nFSPart, event->mc_FSPartPDG);
}

bool CCQENuCuts::passTruePion(CCQENuTruth* event){
  return passTruePion(event->mc_nFSPart, event->mc_FSPartPDG);
}

bool CCQENuCuts::passTruePion(int nfspart, int* fspartPDG){
  for(int i = 0; i < nfspart; i++)
    if( fabs( fspartPDG[i] ) == 211 || fspartPDG[i] == 111 ) return true;

  return false;
}
bool CCQENuCuts::passTrueNeutralPionAbsorbed(CCQENuEvent* event){
  return passTrueNeutralPionAbsorbed(event->mc_nFSPart, event->mc_FSPartPDG, event->mc_er_nPart, event->mc_er_ID);
}

bool CCQENuCuts::passTrueNeutralPionAbsorbed(CCQENuTruth* event){
  return passTrueNeutralPionAbsorbed(event->mc_nFSPart, event->mc_FSPartPDG, event->mc_er_nPart, event->mc_er_ID);
}

bool CCQENuCuts::passTrueNeutralPionAbsorbed(int nfspart, int* fspartPDG, int nerpart, int* erpartPDG) {
  for(int i = 0; i < nfspart; i++) //no Pi0 in FS
    if( fspartPDG[i] == 211 || fabs( fspartPDG[i] ) == 111 )  return false;

  for( int i=0; i< nerpart; i++ ) //Pi0 in Event Record
    if( erpartPDG[i] == 211 || fabs( erpartPDG[i] ) == 111 ) return true;

  return false;

}


bool CCQENuCuts::passPreSelection( CCQENuEvent* event, double primaryProtonScoreShift, double* secProtonsScoreShifts, double q2Shift ) { 
  if(!passInteractionVertex(event)) return false;
  bool passProtonCut = event->multiplicity==1? true : passSingleProtonCut( event, primaryProtonScoreShift, q2Shift );
  bool pass_ExtraProtonsCut = event->multiplicity==1? true : passExtraProtonsCut( event, secProtonsScoreShifts, q2Shift );
  if( passDeadTimeCuts( event )  && 
      passNuHelicityCut( event ) &&
     // passMultiplicity( event ) && 
      passProtonCut &&
      pass_ExtraProtonsCut &&
      passExtraTracksProtonsCut( event, NULL, 0 )&&///What do I do about the scoreshift and q2 shift??!
      passImprovedMichelCut( event ) && 
      passNBlobs( event ) &&
      passTrackAngleCut( event )
      ) return true;
  else
    return false;
}

bool CCQENuCuts::pass1DMEPreSelection( CCQENuEvent* event, double primaryProtonScoreShift, double* secProtonsScoreShifts, double q2Shift ) { 
  if(!passInteractionVertex(event)) return false;
  bool passProtonCut = event->multiplicity==1? true : passSingleProton1DMECut( event, primaryProtonScoreShift, q2Shift );
  bool pass_ExtraProtonsCut = event->multiplicity==1? true : passExtraProtons1DMECut( event, secProtonsScoreShifts, q2Shift );
  if( passDeadTimeCuts( event )  && 
      passNuHelicityCut( event ) &&
      passProtonCut &&
      pass_ExtraProtonsCut &&
      passExtraTracksProtonsCut( event, NULL, 0 )&&///What do I do about the scoreshift and q2 shift??!
      passImprovedMichelCut( event ) && 
      passNBlobs( event ) &&
      passTrackAngleCut( event )
      ) return true;
  else
    return false;
}

bool CCQENuCuts::passPreSelectionMichelSideBand( CCQENuEvent* event, double primaryProtonScoreShift, double* secProtonsScoreShifts, double q2Shift ) { 
  if(!passInteractionVertex(event)) return false;
  bool passProtonCut = event->multiplicity==1? true : passSingleProtonCut( event, primaryProtonScoreShift, q2Shift );
  bool pass_ExtraProtonsCut = event->multiplicity==1? true : passExtraProtonsCut( event, secProtonsScoreShifts, q2Shift );
  if( passDeadTimeCuts( event )  && 
      passNuHelicityCut( event ) &&
     // passMultiplicity( event ) && 
      passProtonCut &&
      pass_ExtraProtonsCut &&
      passExtraTracksProtonsCut( event, NULL, 0 )&&///What do I do about the scoreshift and q2 shift??!
      !passImprovedMichelCut( event ) &&  //Want these for michel sideband
      passNBlobs( event ) &&
      passTrackAngleCut( event )
      ) return true;
  else
    return false;
}

bool CCQENuCuts::pass1DMEPreSelectionMichelSideBand( CCQENuEvent* event, double primaryProtonScoreShift, double* secProtonsScoreShifts, double q2Shift ) { 
  if(!passInteractionVertex(event)) return false;
  bool passProtonCut = event->multiplicity==1? true : passSingleProton1DMECut( event, primaryProtonScoreShift, q2Shift );
  bool pass_ExtraProtonsCut = event->multiplicity==1? true : passExtraProtons1DMECut( event, secProtonsScoreShifts, q2Shift );
  if( passDeadTimeCuts( event )  && 
      passNuHelicityCut( event ) &&
     // passMultiplicity( event ) && 
      passProtonCut &&
      pass_ExtraProtonsCut &&
      passExtraTracksProtonsCut( event, NULL, 0 )&&///What do I do about the scoreshift and q2 shift??!
      !passImprovedMichelCut( event ) &&  //Want these for michel sideband
      passNBlobs( event ) &&
      passTrackAngleCut( event )
      ) return true;
  else
    return false;
}

bool CCQENuCuts::passPreSelectionBlobSideBand( CCQENuEvent* event, double primaryProtonScoreShift, double* secProtonsScoreShifts, double q2Shift ) { 
  if(!passInteractionVertex(event)) return false;
  bool passProtonCut = event->multiplicity==1? true : passSingleProtonCut( event, primaryProtonScoreShift, q2Shift );
  bool pass_ExtraProtonsCut = event->multiplicity==1? true : passExtraProtonsCut( event, secProtonsScoreShifts, q2Shift );
  if( passDeadTimeCuts( event )  && 
      passNuHelicityCut( event ) &&
     // passMultiplicity( event ) && 
      passProtonCut &&
      pass_ExtraProtonsCut &&
      passExtraTracksProtonsCut( event, NULL, 0 )&&///What do I do about the scoreshift and q2 shift??!
      passImprovedMichelCut( event ) && 
      !passNBlobs( event ) && //Want these for blob sideband
      passTrackAngleCut( event )
      ) return true;
  else
    return false;
}

bool CCQENuCuts::pass1DMEPreSelectionBlobSideBand( CCQENuEvent* event, double primaryProtonScoreShift, double* secProtonsScoreShifts, double q2Shift ) { 
  if(!passInteractionVertex(event)) return false;
  bool passProtonCut = event->multiplicity==1? true : passSingleProton1DMECut( event, primaryProtonScoreShift, q2Shift );
  bool pass_ExtraProtonsCut = event->multiplicity==1? true : passExtraProtons1DMECut( event, secProtonsScoreShifts, q2Shift );
  if( passDeadTimeCuts( event )  && 
      passNuHelicityCut( event ) &&
     // passMultiplicity( event ) && 
      passProtonCut &&
      pass_ExtraProtonsCut &&
      passExtraTracksProtonsCut( event, NULL, 0 )&&///What do I do about the scoreshift and q2 shift??!
      passImprovedMichelCut( event ) && 
      !passNBlobs( event ) && //Want these for blob sideband
      passTrackAngleCut( event )
      ) return true;
  else
    return false;
}
bool CCQENuCuts::passPreSelectionMicBlobSideBand( CCQENuEvent* event, double primaryProtonScoreShift, double* secProtonsScoreShifts, double q2Shift ) { 
  if(!passInteractionVertex(event)) return false;
  bool passProtonCut = event->multiplicity==1? true : passSingleProtonCut( event, primaryProtonScoreShift, q2Shift );
  bool pass_ExtraProtonsCut = event->multiplicity==1? true : passExtraProtonsCut( event, secProtonsScoreShifts, q2Shift );
  if( passDeadTimeCuts( event )  && 
      passNuHelicityCut( event ) &&
     // passMultiplicity( event ) && 
      passProtonCut &&
      pass_ExtraProtonsCut &&
      passExtraTracksProtonsCut( event, NULL, 0 )&&///What do I do about the scoreshift and q2 shift??!
      !passImprovedMichelCut( event ) && 
      !passNBlobs( event ) && //Want these for blob sideband
      passTrackAngleCut( event )
      ) return true;
  else
    return false;
}

bool CCQENuCuts::pass1DMEPreSelectionMicBlobSideBand( CCQENuEvent* event, double primaryProtonScoreShift, double* secProtonsScoreShifts, double q2Shift ) { 
  if(!passInteractionVertex(event)) return false;
  bool passProtonCut = event->multiplicity==1? true : passSingleProton1DMECut( event, primaryProtonScoreShift, q2Shift );
  bool pass_ExtraProtonsCut = event->multiplicity==1? true : passExtraProtons1DMECut( event, secProtonsScoreShifts, q2Shift );
  if( passDeadTimeCuts( event )  && 
      passNuHelicityCut( event ) &&
     // passMultiplicity( event ) && 
      passProtonCut &&
      pass_ExtraProtonsCut &&
      passExtraTracksProtonsCut( event, NULL, 0 )&&///What do I do about the scoreshift and q2 shift??!
      !passImprovedMichelCut( event ) && 
      !passNBlobs( event ) && //Want these for blob sideband
      passTrackAngleCut( event )
      ) return true;
  else
    return false;
}

bool CCQENuCuts::passCCQESelection( CCQENuEvent* event, string sample, double primaryProtonScoreShift, double* secProtonsScoreShifts, double q2Shift, double recoilShift ) {

  if( !passInteractionVertex( event ) ) return false;
  if( sample == "Signal" ){
    if(!passPreSelection( event, primaryProtonScoreShift, secProtonsScoreShifts, q2Shift )) return false;
  }
  if( sample == "MichelSideBand" ){
    if(!passPreSelectionMichelSideBand( event, primaryProtonScoreShift, secProtonsScoreShifts, q2Shift )) return false;
  }
  if( sample == "BlobSideBand" ){
    if(!passPreSelectionBlobSideBand( event, primaryProtonScoreShift, secProtonsScoreShifts, q2Shift )) return false;
  }
  if( sample == "MicBlobSideBand" ){
    if(!passPreSelectionMicBlobSideBand( event, primaryProtonScoreShift, secProtonsScoreShifts, q2Shift )) return false;
  }
  
  //Removing the Enu cut on events since it leads to model dependence for the 2D analysis. 
  //if( !passEnuCut( event ) ) return false;

  if( sample == "Signal" || sample == "BlobSideBand" || sample == "MichelSideBand" || sample == "MicBlobSideBand" ){
    return passSignalFunction( event, q2Shift, recoilShift );
  } 

  else if( sample == "Sideband" ){
    return passSidebandFunction( event, primaryProtonScoreShift, secProtonsScoreShifts, q2Shift, recoilShift );
  }
  else
    return false;
}

bool CCQENuCuts::pass1DMECCQESelection( CCQENuEvent* event, string sample, double primaryProtonScoreShift, double* secProtonsScoreShifts, double q2Shift, double recoilShift ) {

  if( !passInteractionVertex( event ) ) return false;
  if( sample == "Signal" ){
    if(!pass1DMEPreSelection( event, primaryProtonScoreShift, secProtonsScoreShifts, q2Shift )) return false;
  }
  if( sample == "MichelSideBand" ){
    if(!pass1DMEPreSelectionMichelSideBand( event, primaryProtonScoreShift, secProtonsScoreShifts, q2Shift )) return false;
  }
  if( sample == "BlobSideBand" ){
    if(!pass1DMEPreSelectionBlobSideBand( event, primaryProtonScoreShift, secProtonsScoreShifts, q2Shift )) return false;
  }
  if( sample == "MicBlobSideBand" ){
    if(!pass1DMEPreSelectionMicBlobSideBand( event, primaryProtonScoreShift, secProtonsScoreShifts, q2Shift )) return false;
  }
  
  //Removing the Enu cut on events since it leads to model dependence for the 2D analysis. 
  //if( !passEnuCut( event ) ) return false;

  if( sample == "Signal" || sample == "BlobSideBand" || sample == "MichelSideBand" || sample == "MicBlobSideBand" ){
    return passSignalFunction( event, q2Shift, recoilShift );
  } 

  else if( sample == "Sideband" ){
    return passSidebandFunction( event, primaryProtonScoreShift, secProtonsScoreShifts, q2Shift, recoilShift );
  }
  else
    return false;
}

TF1* CCQENuCuts::getRecoilCutFunctionMeV(bool is1track) { 
  if( !cutline_signal_mev_1track ){
    cutline_signal_mev_1track = new TF1( "cutline_signal_mev_1track", f_recoil_cut_nu_1track, 0, 10, 2 );
    cutline_signal_mev_1track->SetParameters( 1000.0, 0.0 );
  }
  if( !cutline_signal_mev_2track ){
    cutline_signal_mev_2track = new TF1( "cutline_signal_mev_2track", f_recoil_cut_nu_2track, 0, 10, 2 );
    cutline_signal_mev_2track->SetParameters( 1000.0, 0.0 );
  }
  if (is1track)
    return cutline_signal_mev_1track;
  else
    return cutline_signal_mev_2track;
}

TF1* CCQENuCuts::getSidebandFunctionMeV(bool is1track){ 
  if( !cutline_sideband_mev_1track ){
    cutline_sideband_mev_1track = new TF1( "cutline_sideband_mev_1track",  f_recoil_cut_nu_1track, 0, 10, 2 );
    cutline_sideband_mev_1track->SetParameters( 1000.0, 0.5 );
  }
  if( !cutline_sideband_mev_2track ){
    cutline_sideband_mev_2track = new TF1( "cutline_sideband_mev_2track",  f_recoil_cut_nu_2track, 0, 10, 2 );
    cutline_sideband_mev_2track->SetParameters( 1000.0, 0.5 );
  }
  if (is1track)
    return cutline_sideband_mev_1track;
  else
    return cutline_sideband_mev_2track;

}

TF1* CCQENuCuts::getRecoilCutFunction(bool is1track){
  if( !cutline_signal_1track ){
    cutline_signal_1track = new TF1( "cutline_signal_1track",  f_recoil_cut_nu_1track, 0, 10, 2 );
    cutline_signal_1track->SetParameters( 1.0, 0.0 );
  }
  if( !cutline_signal_2track ){
    cutline_signal_2track = new TF1( "cutline_signal_2track",  f_recoil_cut_nu_2track, 0, 10, 2 );
    cutline_signal_2track->SetParameters( 1.0, 0.0 );
  }
  if (is1track)
    return cutline_signal_1track;
  else
    return cutline_signal_2track;
}

TF1* CCQENuCuts::getSidebandFunction(bool is1track){ 
  if( !cutline_sideband_1track ){
    cutline_sideband_1track = new TF1( "cutline_sideband_1track",  f_recoil_cut_nu_1track, 0, 10, 2 );
    cutline_sideband_1track->SetParameters( 1.0, 0.5 );
  }
  if( !cutline_sideband_2track ){
    cutline_sideband_2track = new TF1( "cutline_sideband_2track",  f_recoil_cut_nu_2track, 0, 10, 2 );
    cutline_sideband_2track->SetParameters( 1.0, 0.5 );
  }
  if (is1track)
    return cutline_sideband_1track;
  else
    return cutline_sideband_2track;
}
//! @todo Check this cut, the OneTrack applies:
//! event->iso_blob_energy_in_time + event->dis_id_energy_in_time_no_HCAL
//! check how those variables  are reconstructed
double CCQENuCuts::getRecoilEnergy( CCQENuEvent* event ){ 
  return ( event->nonvtx_iso_blobs_energy + event->dis_id_energy );
}

/*
Try to select uniform sphere recoil energy
double CCQENuCuts::getRecoilEnergy( CCQENuEvent* event ){
  double n_nonvtx_iso_blobs = event->n_nonvtx_iso_blobs;
  double n_iso_blobs_reference = n_nonvtx_iso_blobs;
  double iso_energy_outside = 0.;
  for(int k=0; k<event->vtx_blobs_iso_distance_in_prong_sz; ++k){
     double iso_energy_fraction = event->vtx_blobs_iso_energy_clusters_outside_radius_in_prong[k]/event->vtx_blobs_iso_energy_in_prong[k];
     if( iso_energy_fraction>0.1 && 
         event->vtx_blobs_iso_distance_in_prong[k]<300.){
       n_nonvtx_iso_blobs++;
       iso_energy_outside += event->vtx_blobs_iso_energy_clusters_outside_radius_in_prong[k];
     }
  }

  double recoil_energy = event->nonvtx_iso_blobs_energy + event->dis_id_energy;
  if (n_nonvtx_iso_blobs>n_iso_blobs_reference) recoil_energy += iso_energy_outside;

  return recoil_energy;
}
*/

//!Here, varshift has to be either q2shift or muonTshift, depending on the analysis cut chosen
bool CCQENuCuts::passSignalFunction( CCQENuEvent *event, double varShift, double recoilShift ){

  double var = 0.; //q2 or emu
  if ( use_muonT_vs_unattachedE_analysiscut )
  {
    var = event->CCQENu_muon_T + varShift;
    var /= pow(10,3); //GeV
  }
  else if( use_q2_vs_unattachedE_analysiscut )
  {
    var = event->CCQENu_Q2 + varShift;
    var /= pow(10,6); //GeV^2
  }
  else if( use_muonPt_vs_unattachedE_analysiscut )
  {
    const double numi_beam_angle_rad =  -0.05887;
    double px   =  event->CCQENu_leptonE[0];
    double py   =  event->CCQENu_leptonE[1];
    double pz   =  event->CCQENu_leptonE[2];
    double py_prime =  -1.0 *sin( numi_beam_angle_rad )* pz + cos( numi_beam_angle_rad )*py;
    double pt   = sqrt( pow(px,2) +pow(py_prime,2) );
    var = pt + varShift;
    var /= pow(10,3); //GeV
  }

  //negative values don't pass the cut
  if( var < 0 ) return false;
  bool is1track = event->multiplicity==1? true : false;

  // get cut value for this q2 
  double nonVtx_recoil_energy_max = getRecoilCutFunctionMeV(is1track)->Eval( var );

  // get recoil energy
  double recoil_energy = getRecoilEnergy( event ) + recoilShift;

  // apply cut  
  if( recoil_energy > nonVtx_recoil_energy_max ) return false;
  else
    return true;
}

bool CCQENuCuts::passEnuCut( double enu, double enushift ){ //MeV
    if( (enu + enushift)/pow(10,3) > 10.0 ) return false;
    if( (enu + enushift)/pow(10,3) < 1.5 )  return false;
    return true;
}

bool CCQENuCuts::passEnuCut( CCQENuEvent *event, double enushift ){ //MeV
  
  return passEnuCut( event->CCQENu_E, enushift );
}

bool CCQENuCuts::passTrueEnuCut( CCQENuEvent *event ){
  return passEnuCut( event->mc_incomingE, 0 );
}

bool CCQENuCuts::passTrueEnuCut( CCQENuTruth *event ){
  return passEnuCut( event->mc_incomingE, 0 );
}


//!Here, varshift has to be either q2shift or muonTshift, depending on the analysis cut chosen
bool CCQENuCuts::passSidebandFunction( CCQENuEvent *event, double primaryProtonScoreShift, double* secProtonsScoreShifts, double varShift, double recoilShift ){

  if( !passPreSelection( event, primaryProtonScoreShift, secProtonsScoreShifts, varShift ) ) return false; 

  double var = 0.; //q2 or emu
  if ( use_muonT_vs_unattachedE_analysiscut )
  {
    var = event->CCQENu_muon_T + varShift;
    var /= pow(10,3); //GeV
  }
  else if( use_q2_vs_unattachedE_analysiscut )
  {
    var = event->CCQENu_Q2 + varShift;
    var /= pow(10,6); //GeV^2
  }
  else if( use_muonPt_vs_unattachedE_analysiscut )
  {
    const double numi_beam_angle_rad =  -0.05887;
    double px   =  event->CCQENu_leptonE[0];
    double py   =  event->CCQENu_leptonE[1];
    double pz   =  event->CCQENu_leptonE[2];
    double py_prime =  -1.0 *sin( numi_beam_angle_rad )* pz + cos( numi_beam_angle_rad )*py;
    double pt   = sqrt( pow(px,2) +pow(py_prime,2) );
    var = pt + varShift;
    var /= pow(10,3); //GeV
  }

  //negative values don't pass the cut
  if( var < 0 ) return false;
  bool is1track = event->multiplicity==1? true : false;

  // get cut value for this emu 
  double nonVtx_recoil_energy_min = getRecoilCutFunctionMeV(is1track)->Eval( var );
  double nonVtx_recoil_energy_max = getSidebandFunctionMeV(is1track)->Eval( var );

  // get recoil energy
  double recoil_energy = getRecoilEnergy( event ) + recoilShift;

  // apply cut
  if( recoil_energy < nonVtx_recoil_energy_min || recoil_energy > nonVtx_recoil_energy_max ) return false;
  else return true;

}

//Get the cuts sequentially... this means, cut i has to pass previous (i-1) cuts
map<int,bool> CCQENuCuts::getCutValues( CCQENuEvent* event ){
  map<int,bool> cutvalues;
  if(!passInteractionVertex(event)){
    for(int i=0;i<6;i++){
      cutvalues[i]=false;
    }
    return cutvalues;
  }
  //1 track events always pass the proton cut
  bool passProtonCut        = event->multiplicity==1? true : passSingleProtonCut( event, 0, 0 );
  bool pass_ExtraProtonsCut = event->multiplicity==1? true : passExtraProtonsCut( event, NULL, 0 );

  //cutvalues[0] = true;
  //Removing the Enu cut on events since it leads to model dependence for the 2D analysis. 
  //cutvalues[0] = passEnuCut( event );

  cutvalues[0] = passDeadTimeCuts( event );
  cutvalues[1] = passNuHelicityCut( event ) && cutvalues[0];
  cutvalues[2] = passNBlobs( event ) && cutvalues[1];
  cutvalues[3] = passImprovedMichelCut( event ) && cutvalues[2];
  cutvalues[4] = (passProtonCut && pass_ExtraProtonsCut) && cutvalues[3];
  cutvalues[5] = passSignalFunction( event, 0, 0 ) && cutvalues[4];

  return cutvalues;
}

//Get the cuts sequentially... this means, cut i has to pass previous (i-1) cuts
map<int,bool> CCQENuCuts::get1DMECutValues( CCQENuEvent* event ){
  map<int,bool> cutvalues;

  if(!passInteractionVertex(event)){
    for(int i=0;i<6;i++){
      cutvalues[i]=false;
    }
    return cutvalues;
  }

  //1 track events always pass the proton cut
  bool pass1DMEProtonCut        = event->multiplicity==1? true : passSingleProton1DMECut( event, 0, 0 );
  bool pass_1DMEExtraProtonsCut = event->multiplicity==1? true : passExtraProtons1DMECut( event, NULL, 0 );

  cutvalues[0] = passDeadTimeCuts( event );
  cutvalues[1] = passNuHelicityCut( event ) && cutvalues[0];
  cutvalues[2] = passNBlobs( event ) && cutvalues[1];
  cutvalues[3] = passImprovedMichelCut( event ) && cutvalues[2];
  cutvalues[4] = (pass1DMEProtonCut && pass_1DMEExtraProtonsCut) && cutvalues[3];
  cutvalues[5] = passSignalFunction( event, 0, 0 ) && cutvalues[4];

  return cutvalues;
}

map<int,bool> CCQENuCuts::get1DMEnminus1CutValues( CCQENuEvent* event ){
  map<int,bool> cutvalues;

  bool pass1DMEProtonCut        = event->multiplicity==1? true : passSingleProton1DMECut( event, 0, 0 );
  bool pass_1DMEExtraProtonsCut = event->multiplicity==1? true : passExtraProtons1DMECut( event, NULL, 0 );

  int cut0  = passDeadTimeCuts( event );
  int cut1  = passNuHelicityCut( event );
  int cut2  = passNBlobs( event );
  int cut3  = passImprovedMichelCut( event );
  int cut4  = (pass1DMEProtonCut && pass_1DMEExtraProtonsCut);
  int cut5  = passSignalFunction( event, 0, 0 );

  cutvalues[0] = cut1 && cut2 && cut3 && cut4 && cut5;
  cutvalues[1] = cut0 && cut2 && cut3 && cut4 && cut5;
  cutvalues[2] = cut0 && cut1 && cut3 && cut4 && cut5;
  cutvalues[3] = cut0 && cut1 && cut2 && cut4 && cut5;
  cutvalues[4] = cut0 && cut1 && cut2 && cut3 && cut5;
  cutvalues[5] = cut0 && cut1 && cut2 && cut3 && cut4;

  return cutvalues;
}

map<int,string> CCQENuCuts::getCutLabels(){
  map<int, string> cutlabels;
  /*
  cutlabels[0] = "#mu_{MINOS-match}+FV+1.5<E_{#nu}<10.0";
  cutlabels[1] = Form("tdead #leq %i", tdead_max);
  cutlabels[2] = (nu_helicity_cut==1) ? "MINOS q/p < 0" : "MINOS q/p > 0";
  cutlabels[3] = Form("N_{iso-blobs} #leq %i", nblobs_max);
  cutlabels[4] = "No michel e^{-/+}";
  cutlabels[5] = Form("proton_{score1} #geq %.2f", proton_score); 
  string properTag; 
  if( use_q2_vs_unattachedE_analysiscut ) { 
    properTag = "f(#mu Q^{2})"; 
  } else if( use_muonT_vs_unattachedE_analysiscut ) { 
    properTag = "f(#mu T)"; 
  } else if ( use_muonPt_vs_unattachedE_analysiscut ) { 
    properTag = "f(#mu P_{T})";
  }
  cutlabels[6] = Form("E_{nonvtx-recoil} < %s", properTag.c_str()); 
  return cutlabels;
  */

  cutlabels[0] = Form("#mu_{MINOS-match}+FV+tdead #leq %i", tdead_max);
  cutlabels[1] = (nu_helicity_cut==1) ? "MINOS q/p < 0" : "MINOS q/p > 0";
  cutlabels[2] = Form("N_{iso-blobs} #leq %i", nblobs_max);
  cutlabels[3] = "No Michel e^{-/+}";
  cutlabels[4] = Form("Proton ID"); 
  cutlabels[5] = Form("E_{nonvtx-recoil} < 0.5 GeV"); 
  /*
  string properTag; 
  if( use_q2_vs_unattachedE_analysiscut ) { 
    properTag = "f(#mu Q^{2})"; 
  } else if( use_muonT_vs_unattachedE_analysiscut ) { 
    properTag = "f(#mu T)"; 
  } else if ( use_muonPt_vs_unattachedE_analysiscut ) { 
    properTag = "f(#mu P_{T})";
  }
  cutlabels[5] = Form("E_{nonvtx-recoil} < %s", properTag.c_str()); 
  */
  return cutlabels;
}

map<int,string> CCQENuCuts::getCutLabels_CCQEOneTrack(){
  map<int, string> cutlabels;
  cutlabels[0] = "#mu{MINOS-match}+FV+1.5<E_{#nu}<10.0";
  cutlabels[1] = Form("$tdead #leq %i$", tdead_max);
  cutlabels[2] = (nu_helicity_cut==1) ? "MINOS q/p < 0" : "MINOS q/p > 0";
  cutlabels[3] = Form("N_{iso-blobs} #leq %i", 2);
  //cutlabels[4] = "$E_{recoil} < f(Q^{2})";
  cutlabels[4] = "$E_{recoil} < 0.5 GeV";
  return cutlabels;
}

map<int,Color_t> CCQENuCuts::getCutColors(){
  map<int, Color_t> cutcolors; 
  /*
  cutcolors[0] = kBlue-7;
  cutcolors[1] = kGreen-6;
  cutcolors[2] = kOrange+1;
  cutcolors[3] = kGreen-2;
  cutcolors[4] = kRed+4;
  cutcolors[5] = kMagenta-4;
  cutcolors[6] = kBlack;
  return cutcolors;
  */

  cutcolors[0] = kOrange+2;
  cutcolors[1] = kGreen;
  cutcolors[2] = kRed;
  cutcolors[3] = kBlue+1;
  cutcolors[4] = kMagenta-4;
  cutcolors[5] = kBlack;
  return cutcolors;
}
#endif

