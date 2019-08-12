//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jan 12 10:22:52 2017 by ROOT version 5.34/05
// from TChain CCQENu/
//////////////////////////////////////////////////////////

#ifndef CCQENuEvent_h
#define CCQENuEvent_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
//#include "/grid/fermiapp/minerva/software_releases/lcgcmake/build/lcg_61/projects/ROOT-5.34.05/src/ROOT/5.34.05/cint/cint/lib/prec_stl/vector"

// Fixed size dimensions of array or collections stored in the TTree if any.
namespace CCQENU_ANA {
class CCQENuEvent {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        eventID;
   Int_t           physEvtNum;
   Int_t           n_hyps;
   Int_t           processType;
   Int_t           primaryPart;
   Int_t           n_slices;
   Int_t           slice_numbers[1];   //[n_slices]
   Int_t           shared_slice;
   Double_t        vtx[4];
   Double_t        vtxErr[4];
   Double_t        E[4];
   Bool_t          found_truth;
   Bool_t          phys_front_activity;
   Bool_t          phys_energy_in_road_upstream_is_rockmuon_consistent;
   Bool_t          rock_muons_removed;
   Bool_t          minos_track_match;
   Bool_t          minos_stub_match;
   Bool_t          unknown_helicity;
   Bool_t          minos_track_inside_partial_plane;
   Bool_t          prim_vtx_has_misassigned_track_direction;
   Bool_t          prim_vtx_has_broken_track;
   Int_t           broken_track_most_us_plane;
   Int_t           event_unused_start_vertices;
   Int_t           event_used_start_vertices;
   Int_t           has_interaction_vertex;
   Int_t           has_single_proton;
   Int_t           improved_nmichel;
   Int_t           multiplicity;
   Int_t           muon_fuzz_energy;
   Int_t           muon_is_minos_match_stub;
   Int_t           muon_is_minos_match_track;
   Int_t           n_anchored_long_trk_prongs;
   Int_t           n_anchored_short_trk_prongs;
   Int_t           n_iso_trk_prongs;
   Int_t           n_minos_matches;
   Int_t           n_muon_iso_blobs;
   Int_t           n_nonvtx_iso_blobs;
   Int_t           n_nonvtx_iso_blobs_all;
   Int_t           part_response_recoil_nClus;
   Int_t           pass_CCQENu_precuts;
   Int_t           phys_energy_in_road_downstream_nplanes;
   Int_t           phys_energy_in_road_upstream_nplanes;
   Int_t           phys_n_dead_discr_pair;
   Int_t           phys_n_dead_discr_pair_in_prim_track_region;
   Int_t           phys_n_dead_discr_pair_two_mod_downstream_prim_track;
   Int_t           phys_n_dead_discr_pair_two_mod_upstream_prim_vtx;
   Int_t           phys_n_dead_discr_pair_upstream_prim_track_proj;
   Int_t           phys_vertex_is_fiducial;
   Int_t           proton_prong_PDG;
   Int_t           proton_prong_traj_ID;
   Int_t           slice_n_hits;
   Int_t           truth_has_michel_electron;
   Int_t           truth_improved_michel_electron;
   Double_t        dis_id_energy;
   Double_t        energy_from_mc;
   Double_t        energy_from_mc_fraction;
   Double_t        energy_from_mc_fraction_of_highest;
   Double_t        muon_iso_blobs_energy;
   Double_t        muon_minerva_trk_chi2PerDoF;
   Double_t        muon_phi;
   Double_t        muon_theta;
   Double_t        muon_thetaX;
   Double_t        muon_thetaY;
   Double_t        nonvtx_iso_blobs_energy;
   Double_t        nonvtx_iso_blobs_energy_all;
   Double_t        numi_horn_curr;
   Double_t        numi_pot;
   Double_t        numi_x;
   Double_t        numi_x_width;
   Double_t        numi_y;
   Double_t        numi_y_width;
   Double_t        part_response_recoil_em_id;
   Double_t        part_response_recoil_em_id_err;
   Double_t        part_response_recoil_em_od;
   Double_t        part_response_recoil_em_od_err;
   Double_t        part_response_recoil_high_neutron_id;
   Double_t        part_response_recoil_high_neutron_id_err;
   Double_t        part_response_recoil_high_neutron_od;
   Double_t        part_response_recoil_high_neutron_od_err;
   Double_t        part_response_recoil_low_neutron_id;
   Double_t        part_response_recoil_low_neutron_id_err;
   Double_t        part_response_recoil_low_neutron_od;
   Double_t        part_response_recoil_low_neutron_od_err;
   Double_t        part_response_recoil_meson_id;
   Double_t        part_response_recoil_meson_id_err;
   Double_t        part_response_recoil_meson_od;
   Double_t        part_response_recoil_meson_od_err;
   Double_t        part_response_recoil_mid_neutron_id;
   Double_t        part_response_recoil_mid_neutron_id_err;
   Double_t        part_response_recoil_mid_neutron_od;
   Double_t        part_response_recoil_mid_neutron_od_err;
   Double_t        part_response_recoil_muon_id;
   Double_t        part_response_recoil_muon_id_err;
   Double_t        part_response_recoil_muon_od;
   Double_t        part_response_recoil_muon_od_err;
   Double_t        part_response_recoil_other_id;
   Double_t        part_response_recoil_other_id_err;
   Double_t        part_response_recoil_other_od;
   Double_t        part_response_recoil_other_od_err;
   Double_t        part_response_recoil_proton_id;
   Double_t        part_response_recoil_proton_id_err;
   Double_t        part_response_recoil_proton_od;
   Double_t        part_response_recoil_proton_od_err;
   Double_t        part_response_recoil_xtalk_id;
   Double_t        part_response_recoil_xtalk_id_err;
   Double_t        part_response_recoil_xtalk_od;
   Double_t        part_response_recoil_xtalk_od_err;
   Double_t        phys_energy_dispersed;
   Double_t        phys_energy_in_road_downstream;
   Double_t        phys_energy_in_road_upstream;
   Double_t        phys_energy_unattached;
   Double_t        prim_vtx_smallest_opening_angle;
   Double_t        proton_track_length;
   //-------------------------------------------------------
   Double_t        proton_track_endx;
   Double_t        proton_track_endy;
   Double_t        proton_track_endz;

   Double_t        CCQENu_proton_startPointX;
   Double_t        CCQENu_proton_startPointY;
   Double_t        CCQENu_proton_startPointZ;

   Double_t        CCQENu_proton_endPointX;
   Double_t        CCQENu_proton_endPointY;
   Double_t        CCQENu_proton_endPointZ;

   Double_t        CCQENu_proton_theta;
   Double_t        CCQENu_proton_thetaX;
   Double_t        CCQENu_proton_thetaY;
   Double_t        CCQENu_proton_phi;

   Double_t        CCQENu_proton_ekin;
   Double_t        CCQENu_proton_enu;
   Double_t        CCQENu_proton_q2;
   Double_t        CCQENu_proton_E;
   Double_t        CCQENu_proton_p;
   Double_t        CCQENu_proton_px;
   Double_t        CCQENu_proton_py;
   Double_t        CCQENu_proton_pz;
   //-------------------------------------------------------
   Double_t        recoil_energy_nonmuon_nonvtx0mm;
   Double_t        recoil_energy_nonmuon_nonvtx100mm;
   Double_t        recoil_energy_nonmuon_nonvtx150mm;
   Double_t        recoil_energy_nonmuon_nonvtx200mm;
   Double_t        recoil_energy_nonmuon_nonvtx250mm;
   Double_t        recoil_energy_nonmuon_nonvtx300mm;
   Double_t        recoil_energy_nonmuon_nonvtx50mm;
   Double_t        recoil_energy_nonmuon_vtx0mm;
   Double_t        recoil_energy_nonmuon_vtx100mm;
   Double_t        recoil_energy_nonmuon_vtx150mm;
   Double_t        recoil_energy_nonmuon_vtx200mm;
   Double_t        recoil_energy_nonmuon_vtx250mm;
   Double_t        recoil_energy_nonmuon_vtx300mm;
   Double_t        recoil_energy_nonmuon_vtx50mm;
   Double_t        vtx_blobs_energy;
   Double_t        vtx_iso_blobs_energy_outside_radius;
   Int_t           all_event_start_vertex_fv_minos_match_sz;
   Int_t           all_event_start_vertex_fv_minos_match[200];   //[all_event_start_vertex_fv_minos_match_sz]
   Int_t           clusters_found_at_end_proton_prong_sz;
   Int_t           clusters_found_at_end_proton_prong[200];   //[clusters_found_at_end_proton_prong_sz]
   Int_t           event_in_time_vertex_types_sz;
   Int_t           event_in_time_vertex_types[200];   //[event_in_time_vertex_types_sz]
   Int_t           event_track_nhits_sz;
   Int_t           event_track_nhits[200];   //[event_track_nhits_sz]
   Int_t           event_vertex_types_sz;
   Int_t           event_vertex_types[200];   //[event_vertex_types_sz]
   Int_t           has_michel_bgmodule_sz;
   Int_t           has_michel_bgmodule[200];   //[has_michel_bgmodule_sz]
   Int_t           has_michel_category_sz;
   Int_t           has_michel_category[200];   //[has_michel_category_sz]
   Int_t           has_michel_edmodule_sz;
   Int_t           has_michel_edmodule[200];   //[has_michel_edmodule_sz]
   Int_t           has_michel_in_vertex_point_sz;
   Int_t           has_michel_in_vertex_point[200];   //[has_michel_in_vertex_point_sz]
   Int_t           has_michel_matched_pdg_sz;
   Int_t           has_michel_matched_pdg[200];   //[has_michel_matched_pdg_sz]
   Int_t           has_michel_matched_primary_pdg_sz;
   Int_t           has_michel_matched_primary_pdg[200];   //[has_michel_matched_primary_pdg_sz]
   Int_t           has_michel_ndigits_sz;
   Int_t           has_michel_ndigits[200];   //[has_michel_ndigits_sz]
   Int_t           has_michel_nmodules_sz;
   Int_t           has_michel_nmodules[200];   //[has_michel_nmodules_sz]
   Int_t           has_michel_nplanes_sz;
   Int_t           has_michel_nplanes[200];   //[has_michel_nplanes_sz]
   Int_t           has_michel_ntracks_sz;
   Int_t           has_michel_ntracks[200];   //[has_michel_ntracks_sz]
   Int_t           has_michel_slice_number_sz;
   Int_t           has_michel_slice_number[200];   //[has_michel_slice_number_sz]
   Int_t           has_michel_vertex_type_sz;
   Int_t           has_michel_vertex_type[200];   //[has_michel_vertex_type_sz]
   Int_t           has_michel_view_sum_sz;
   Int_t           has_michel_view_sum[200];   //[has_michel_view_sum_sz]
   Int_t           improved_michel_in_vertex_point_sz;
   Int_t           improved_michel_in_vertex_point[200];   //[improved_michel_in_vertex_point_sz]
   Int_t           improved_michel_match_vec_sz;
   Int_t           improved_michel_match_vec[200];   //[improved_michel_match_vec_sz]
   Int_t           improved_michel_matched_pdg_sz;
   Int_t           improved_michel_matched_pdg[200];   //[improved_michel_matched_pdg_sz]
   Int_t           improved_michel_matched_primary_pdg_sz;
   Int_t           improved_michel_matched_primary_pdg[200];   //[improved_michel_matched_primary_pdg_sz]
   Int_t           improved_michel_vertex_type_sz;
   Int_t           improved_michel_vertex_type[200];   //[improved_michel_vertex_type_sz]
   Int_t           improved_michel_view_vec_sz;
   Int_t           improved_michel_view_vec[200];   //[improved_michel_view_vec_sz]
   Int_t           nonvtx_iso_blobs_n_hits_in_prong_sz;
   Int_t           nonvtx_iso_blobs_n_hits_in_prong[200];   //[nonvtx_iso_blobs_n_hits_in_prong_sz]
   Int_t           nonvtx_iso_blobs_particle_pdg_in_prong_sz;
   Int_t           nonvtx_iso_blobs_particle_pdg_in_prong[200];   //[nonvtx_iso_blobs_particle_pdg_in_prong_sz]
   Int_t           nonvtx_iso_blobs_primary_particle_pdg_in_prong_sz;
   Int_t           nonvtx_iso_blobs_primary_particle_pdg_in_prong[1200];   //[nonvtx_iso_blobs_primary_particle_pdg_in_prong_sz]
   Int_t           number_clusters_at_end_proton_prong_sz;
   Int_t           number_clusters_at_end_proton_prong[200];   //[number_clusters_at_end_proton_prong_sz]
   Int_t           recoil_lower_time_limit_sz;
   Int_t           recoil_lower_time_limit[700];   //[recoil_lower_time_limit_sz]
   Int_t           recoil_upper_time_limit_sz;
   Int_t           recoil_upper_time_limit[700];   //[recoil_upper_time_limit_sz]
   Int_t           all_event_start_vertex_time_sz;
   Double_t        all_event_start_vertex_time[200];   //[all_event_start_vertex_time_sz]
   Int_t           all_event_start_vertex_time_minos_match_sz;
   Double_t        all_event_start_vertex_time_minos_match[200];   //[all_event_start_vertex_time_minos_match_sz]
   Int_t           calibE_clusters_at_end_proton_prong_sz;
   Double_t        calibE_clusters_at_end_proton_prong[200];   //[calibE_clusters_at_end_proton_prong_sz]
   Int_t           clusters_found_at_end_proton_prong_max_distance_sz;
   Double_t        clusters_found_at_end_proton_prong_max_distance[200];   //[clusters_found_at_end_proton_prong_max_distance_sz]
   Int_t           event_extra_track_PID_sz;
   Double_t        event_extra_track_PID[200];   //[event_extra_track_PID_sz]
   Int_t           event_in_time_tracks_energy_sz;
   Double_t        event_in_time_tracks_energy[200];   //[event_in_time_tracks_energy_sz]
   Int_t           event_track_hit_energy_sz;
   Double_t        event_track_hit_energy[2000];   //[event_track_hit_energy_sz]
   Int_t           event_track_hit_time_sz;
   Double_t        event_track_hit_time[2000];   //[event_track_hit_time_sz]
   Int_t           event_track_time_diff_sz;
   Double_t        event_track_time_diff[200];   //[event_track_time_diff_sz]
   Int_t           event_tracks_energy_sz;
   Double_t        event_tracks_energy[200];   //[event_tracks_energy_sz]
   Int_t           event_vertex_time_diff_sz;
   Double_t        event_vertex_time_diff[200];   //[event_vertex_time_diff_sz]
   Int_t           has_michel_data_energy_fraction_sz;
   Double_t        has_michel_data_energy_fraction[200];   //[has_michel_data_energy_fraction_sz]
   Int_t           has_michel_distance_sz;
   Double_t        has_michel_distance[200];   //[has_michel_distance_sz]
   Int_t           has_michel_energy_sz;
   Double_t        has_michel_energy[200];   //[has_michel_energy_sz]
   Int_t           has_michel_hit_charges_sz;
   Double_t        has_michel_hit_charges[200];   //[has_michel_hit_charges_sz]
   Int_t           has_michel_hit_time_diff_cluster_sz;
   Double_t        has_michel_hit_time_diff_cluster[200];   //[has_michel_hit_time_diff_cluster_sz]
   Int_t           has_michel_hit_time_diff_vtx_sz;
   Double_t        has_michel_hit_time_diff_vtx[200];   //[has_michel_hit_time_diff_vtx_sz]
   Int_t           has_michel_hit_times_sz;
   Double_t        has_michel_hit_times[200];   //[has_michel_hit_times_sz]
   Int_t           has_michel_matched_energy_fraction_sz;
   Double_t        has_michel_matched_energy_fraction[200];   //[has_michel_matched_energy_fraction_sz]
   Int_t           has_michel_slice_energy_sz;
   Double_t        has_michel_slice_energy[200];   //[has_michel_slice_energy_sz]
   Int_t           has_michel_time_diff_sz;
   Double_t        has_michel_time_diff[200];   //[has_michel_time_diff_sz]
   Int_t           improved_michel_data_energy_fraction_sz;
   Double_t        improved_michel_data_energy_fraction[200];   //[improved_michel_data_energy_fraction_sz]
   Int_t           improved_michel_dist_vec_sz;
   Double_t        improved_michel_dist_vec[200];   //[improved_michel_dist_vec_sz]
   Int_t           improved_michel_ecalo_vec_sz;
   Double_t        improved_michel_ecalo_vec[200];   //[improved_michel_ecalo_vec_sz]
   Int_t           improved_michel_evis_vec_sz;
   Double_t        improved_michel_evis_vec[200];   //[improved_michel_evis_vec_sz]
   Int_t           improved_michel_hit_charges_sz;
   Double_t        improved_michel_hit_charges[200];   //[improved_michel_hit_charges_sz]
   Int_t           improved_michel_hit_time_diff_cluster_sz;
   Double_t        improved_michel_hit_time_diff_cluster[200];   //[improved_michel_hit_time_diff_cluster_sz]
   Int_t           improved_michel_hit_time_diff_vtx_sz;
   Double_t        improved_michel_hit_time_diff_vtx[200];   //[improved_michel_hit_time_diff_vtx_sz]
   Int_t           improved_michel_hit_times_sz;
   Double_t        improved_michel_hit_times[36];   //[improved_michel_hit_times_sz]
   Int_t           improved_michel_matched_energy_fraction_sz;
   Double_t        improved_michel_matched_energy_fraction[200];   //[improved_michel_matched_energy_fraction_sz]
   Int_t           improved_michel_tdiff_vec_sz;
   Double_t        improved_michel_tdiff_vec[200];   //[improved_michel_tdiff_vec_sz]
   Int_t           improved_michel_tvec_sz;
   Double_t        improved_michel_tvec[200];   //[improved_michel_tvec_sz]
   Int_t           improved_michel_uvec_sz;
   Double_t        improved_michel_uvec[200];   //[improved_michel_uvec_sz]
   Int_t           improved_michel_vvec_sz;
   Double_t        improved_michel_vvec[200];   //[improved_michel_vvec_sz]
   Int_t           improved_michel_xvec_sz;
   Double_t        improved_michel_xvec[200];   //[improved_michel_xvec_sz]
   Int_t           improved_michel_yvec_sz;
   Double_t        improved_michel_yvec[200];   //[improved_michel_yvec_sz]
   Int_t           improved_michel_zvec_sz;
   Double_t        improved_michel_zvec[200];   //[improved_michel_zvec_sz]


   // Need these variables for michel end pointers
   Int_t           improved_michel_u1vec_sz;
   Double_t        improved_michel_u1vec[200];   //[improved_michel_uvec_sz]
   Int_t           improved_michel_v1vec_sz;
   Double_t        improved_michel_v1vec[200];   //[improved_michel_vvec_sz]
   Int_t           improved_michel_x1vec_sz;
   Double_t        improved_michel_x1vec[200];   //[improved_michel_xvec_sz]
   Int_t           improved_michel_z1vec_sz;
   Double_t        improved_michel_z1vec[200];   //[improved_michel_zvec_sz]

   Int_t           improved_michel_u2vec_sz;
   Double_t        improved_michel_u2vec[200];   //[improved_michel_uvec_sz]
   Int_t           improved_michel_v2vec_sz;
   Double_t        improved_michel_v2vec[200];   //[improved_michel_vvec_sz]
   Int_t           improved_michel_x2vec_sz;
   Double_t        improved_michel_x2vec[200];   //[improved_michel_xvec_sz]
   Int_t           improved_michel_z2vec_sz;
   Double_t        improved_michel_z2vec[200];   //[improved_michel_zvec_sz]

//-------------- Adding variables for Aaron's Michel Tool

   Int_t           improved_michel_fitCode_vec_sz;
   Int_t           improved_michel_fitCode_vec[200];  //[Optimal Michel Fit Code]

   Int_t           improved_michel_fitPass_vec_sz;
   Int_t           improved_michel_fitPass_vec[200];  //[Optimal Michel Fit Code]

   Double_t        improved_michel_MatchedEndDist_vec[200];
   Int_t           improved_michel_MatchedEndDist_vec_sz;

   Double_t        improved_michel_matchedvtx_energy_vec[200];
   Int_t           improved_michel_matchedvtx_energy_vec_sz;

   Double_t        improved_michel_transdist_vec[200];
   Int_t           improved_michel_transdist_vec_sz;


   Double_t        improved_michel_polarangle_vec[200];
   Int_t           improved_michel_polarangle_vec_sz;

   Int_t        improved_michel_nplanes[200];
   Int_t           improved_michel_nplanes_sz;

   Int_t        improved_michel_clussize[200];
   Int_t           improved_michel_clussize_sz;

   Int_t           improved_allmichels;


   ////////////// -------------- MehchelTool ==========

   Double_t   mehtool_closestclusterX_distance[200];
   Double_t   mehtool_closestclusterX_energy[200];
   Double_t   mehtool_closestclusterX_time[200];
   Int_t      mehtool_closestclusterX_endpoint[200];
   Double_t   mehtool_closestclusterXZ_distance[200];

   Double_t   mehtool_closestclusterU_distance[200];
   Double_t   mehtool_closestclusterU_energy[200];
   Double_t   mehtool_closestclusterU_time[200];
   Int_t      mehtool_closestclusterU_endpoint[200];
   Double_t   mehtool_closestclusterUZ_distance[200];

   Double_t   mehtool_closestclusterV_distance[200];
   Double_t   mehtool_closestclusterV_energy[200];
   Double_t   mehtool_closestclusterV_time[200];
   Int_t      mehtool_closestclusterV_endpoint[200];
   Double_t   mehtool_closestclusterVZ_distance[200];


   Int_t      mehtool_nmichelsmatch;
   Int_t      mehtool_duplicate_michelindex[200];
   Int_t      mehtool_closestclusterX_nclusz[200];
   Int_t      mehtool_closestclusterU_nclusz[200];
   Int_t      mehtool_closestclusterV_nclusz[200];

   Double_t   mehtool_closestclusterX_Z_pos[200];
   Double_t   mehtool_closestclusterU_Z_pos[200];
   Double_t   mehtool_closestclusterV_Z_pos[200];

   Double_t   mehtool_closestclusterX_pos[200];
   Double_t   mehtool_closestclusterU_pos[200];
   Double_t   mehtool_closestclusterV_pos[200];

   Double_t   mehtool_closestclusterX_clustime[200];
   Double_t   mehtool_closestclusterU_clustime[200];
   Double_t   mehtool_closestclusterV_clustime[200];

   Int_t   mehtool_closestclusterX_clustime_sz;
   Int_t   mehtool_closestclusterU_clustime_sz;
   Int_t   mehtool_closestclusterV_clustime_sz;

   Int_t   mehtool_closestclusterX_Z_pos_sz;
   Int_t   mehtool_closestclusterU_Z_pos_sz;
   Int_t   mehtool_closestclusterV_Z_pos_sz;

   Int_t   mehtool_closestclusterX_pos_sz;
   Int_t   mehtool_closestclusterU_pos_sz;
   Int_t   mehtool_closestclusterV_pos_sz;





   Int_t      mehtool_nmichelsmatch_sz;
   Int_t      mehtool_duplicate_michelindex_sz;
   Int_t      mehtool_closestclusterX_nclusz_sz;
   Int_t      mehtool_closestclusterU_nclusz_sz;
   Int_t      mehtool_closestclusterV_nclusz_sz;




   Int_t mehtool_closestclusterX_distance_sz;
   Int_t mehtool_closestclusterX_energy_sz;
   Int_t mehtool_closestclusterX_time_sz;
   Int_t mehtool_closestclusterX_endpoint_sz;
   Int_t mehtool_closestclusterXZ_distance_sz;


   Int_t mehtool_closestclusterU_distance_sz;
   Int_t mehtool_closestclusterU_energy_sz;
   Int_t mehtool_closestclusterU_time_sz;
   Int_t mehtool_closestclusterU_endpoint_sz;
   Int_t mehtool_closestclusterUZ_distance_sz;


   Int_t mehtool_closestclusterV_distance_sz;
   Int_t mehtool_closestclusterV_energy_sz;
   Int_t mehtool_closestclusterV_time_sz;
   Int_t mehtool_closestclusterV_endpoint_sz;
   Int_t mehtool_closestclusterVZ_distance_sz;

   Double_t mehtool_michel_time[200];
   Int_t mehtool_michel_time_sz;

   Double_t mehtool_michel_energy[200];
   Int_t mehtool_michel_energy_sz;

   Int_t mehtool_michel_Xclusters[200];
   Int_t mehtool_michel_Xclusters_sz;

   Int_t mehtool_michel_Uclusters[200];
   Int_t mehtool_michel_Uclusters_sz;

   Int_t mehtool_michel_Vclusters[200];
   Int_t mehtool_michel_Vclusters_sz;

   Double_t mehtool_michel_x1[200];
   Double_t mehtool_michel_x2[200];
   Double_t mehtool_michel_u1[200];
   Double_t mehtool_michel_u2[200];
   Double_t mehtool_michel_v1[200];
   Double_t mehtool_michel_v2[200];
   Double_t mehtool_michel_z1[200];
   Double_t mehtool_michel_z2[200];

   Int_t mehtool_michel_x1_sz;
   Int_t mehtool_michel_x2_sz;
   Int_t mehtool_michel_u1_sz;
   Int_t mehtool_michel_u2_sz;
   Int_t mehtool_michel_v1_sz;
   Int_t mehtool_michel_v2_sz;
   Int_t mehtool_michel_z1_sz;
   Int_t mehtool_michel_z2_sz;

   Double_t mehtool_michel_maxmeandiff[200];
   Int_t mehtool_michel_maxmeandiff_sz;

   Int_t mehtool_istrueMichel[200];
   Int_t mehtool_istrueMichel_sz;



   Double_t mehtool_michel_allmichelenergy[200];
   Int_t    mehtool_michel_allmichelenergy_sz;

   Int_t    mehtool_michel_from_decay[200];
   Double_t mehtool_michel_from_decay_sz;

   Int_t    mehtool_true_michel_pdg[200];
   Double_t mehtool_true_michel_pdg_sz;








   // ----------------- True Matched Michel Info ------------------

   Int_t           has_michel_primary_particle_trackID;

   Int_t           michel_from_decay;

   Int_t           true_michel_pdg;

   Double_t        true_michel_x1vec[200];
   Double_t        true_michel_y1vec[200];
   Double_t        true_michel_z1vec[200];
   Double_t        true_michel_x2vec[200];
   Double_t        true_michel_y2vec[200];
   Double_t        true_michel_z2vec[200];

   Int_t           michel_parent_PDG;
   Int_t           michel_parent_trackID;

  //Int_t           mehtool_michel_from_decay[200];
  //Int_t           mehtool_true_michel_pdg[200];
  //Int_t           mehtool_michel_parent_PDG[200];
  //Double_t        mehtool_michel_truetime[200];


   Int_t           muon_thetaX_allNodes_sz;
   Double_t        muon_thetaX_allNodes[500];   //[muon_thetaX_allNodes_sz]
   Int_t           muon_thetaY_allNodes_sz;
   Double_t        muon_thetaY_allNodes[500];   //[muon_thetaY_allNodes_sz]
   Int_t           muon_theta_allNodes_sz;
   Double_t        muon_theta_allNodes[500];   //[muon_theta_allNodes_sz]
   Int_t           nonvtx_iso_blobs_data_energy_fraction_in_prong_sz;
   Double_t        nonvtx_iso_blobs_data_energy_fraction_in_prong[200];   //[nonvtx_iso_blobs_data_energy_fraction_in_prong_sz]
   Int_t           nonvtx_iso_blobs_distance_in_prong_sz;
   Double_t        nonvtx_iso_blobs_distance_in_prong[200];   //[nonvtx_iso_blobs_distance_in_prong_sz]
   Int_t           nonvtx_iso_blobs_earliest_hit_time_in_prong_sz;
   Double_t        nonvtx_iso_blobs_earliest_hit_time_in_prong[200];   //[nonvtx_iso_blobs_earliest_hit_time_in_prong_sz]
   Int_t           nonvtx_iso_blobs_energy_in_prong_sz;
   Double_t        nonvtx_iso_blobs_energy_in_prong[200];   //[nonvtx_iso_blobs_energy_in_prong_sz]
   Int_t           nonvtx_iso_blobs_highest_hit_energy_in_prong_sz;
   Double_t        nonvtx_iso_blobs_highest_hit_energy_in_prong[200];   //[nonvtx_iso_blobs_highest_hit_energy_in_prong_sz]
   Int_t           nonvtx_iso_blobs_highest_module_u_in_prong_sz;
   Double_t        nonvtx_iso_blobs_highest_module_u_in_prong[200];   //[nonvtx_iso_blobs_highest_module_u_in_prong_sz]
   Int_t           nonvtx_iso_blobs_highest_module_v_in_prong_sz;
   Double_t        nonvtx_iso_blobs_highest_module_v_in_prong[200];   //[nonvtx_iso_blobs_highest_module_v_in_prong_sz]
   Int_t           nonvtx_iso_blobs_highest_module_x_in_prong_sz;
   Double_t        nonvtx_iso_blobs_highest_module_x_in_prong[200];   //[nonvtx_iso_blobs_highest_module_x_in_prong_sz]
   Int_t           nonvtx_iso_blobs_latest_hit_time_in_prong_sz;
   Double_t        nonvtx_iso_blobs_latest_hit_time_in_prong[200];   //[nonvtx_iso_blobs_latest_hit_time_in_prong_sz]
   Int_t           nonvtx_iso_blobs_lowest_module_u_in_prong_sz;
   Double_t        nonvtx_iso_blobs_lowest_module_u_in_prong[200];   //[nonvtx_iso_blobs_lowest_module_u_in_prong_sz]
   Int_t           nonvtx_iso_blobs_lowest_module_v_in_prong_sz;
   Double_t        nonvtx_iso_blobs_lowest_module_v_in_prong[200];   //[nonvtx_iso_blobs_lowest_module_v_in_prong_sz]
   Int_t           nonvtx_iso_blobs_lowest_module_x_in_prong_sz;
   Double_t        nonvtx_iso_blobs_lowest_module_x_in_prong[200];   //[nonvtx_iso_blobs_lowest_module_x_in_prong_sz]
   Int_t           nonvtx_iso_blobs_matched_energy_fraction_in_prong_sz;
   Double_t        nonvtx_iso_blobs_matched_energy_fraction_in_prong[200];   //[nonvtx_iso_blobs_matched_energy_fraction_in_prong_sz]
   Int_t           nonvtx_iso_blobs_start_position_x_in_prong_sz;
   Double_t        nonvtx_iso_blobs_start_position_x_in_prong[200];   //[nonvtx_iso_blobs_start_position_x_in_prong_sz]
   Int_t           nonvtx_iso_blobs_start_position_y_in_prong_sz;
   Double_t        nonvtx_iso_blobs_start_position_y_in_prong[200];   //[nonvtx_iso_blobs_start_position_y_in_prong_sz]
   Int_t           nonvtx_iso_blobs_start_position_z_in_prong_sz;
   Double_t        nonvtx_iso_blobs_start_position_z_in_prong[200];   //[nonvtx_iso_blobs_start_position_z_in_prong_sz]
   Int_t           nonvtx_iso_blobs_time_difference_in_prong_sz;
   Double_t        nonvtx_iso_blobs_time_difference_in_prong[200];   //[nonvtx_iso_blobs_time_difference_in_prong_sz]
   Int_t           nonvtx_iso_blobs_time_in_prong_sz;
   Double_t        nonvtx_iso_blobs_time_in_prong[200];   //[nonvtx_iso_blobs_time_in_prong_sz]
   Double_t        proton_prong_4p[4];
   Double_t        proton_prong_tpos[4];
   Int_t           recoil_data_fraction_sz;
   Double_t        recoil_data_fraction[700];   //[recoil_data_fraction_sz]
   Int_t           recoil_summed_energy_sz;
   Double_t        recoil_summed_energy[700];   //[recoil_summed_energy_sz]
   Int_t           slice_hit_energy_sz;
   Double_t        slice_hit_energy[5000];   //[slice_hit_energy_sz]
   Int_t           slice_hit_time_sz;
   Double_t        slice_hit_time[5000];   //[slice_hit_time_sz]
   Int_t           truth_has_michel_from_pion_minus_momentum_sz;
   Double_t        truth_has_michel_from_pion_minus_momentum[200];   //[truth_has_michel_from_pion_minus_momentum_sz]
   Int_t           truth_has_michel_from_pion_plus_momentum_sz;
   Double_t        truth_has_michel_from_pion_plus_momentum[200];   //[truth_has_michel_from_pion_plus_momentum_sz]
   Int_t           visE_clusters_at_end_proton_prong_sz;
   Double_t        visE_clusters_at_end_proton_prong[200];   //[visE_clusters_at_end_proton_prong_sz]
   Int_t           vtx_blobs_iso_distance_in_prong_sz;
   Double_t        vtx_blobs_iso_distance_in_prong[200];   //[vtx_blobs_iso_distance_in_prong_sz]
   Int_t           vtx_blobs_iso_energy_clusters_outside_radius_in_prong_sz;
   Double_t        vtx_blobs_iso_energy_clusters_outside_radius_in_prong[200];   //[vtx_blobs_iso_energy_clusters_outside_radius_in_prong_sz]
   Int_t           vtx_blobs_iso_energy_in_prong_sz;
   Double_t        vtx_blobs_iso_energy_in_prong[200];   //[vtx_blobs_iso_energy_in_prong_sz]
   Int_t           vtx_blobs_vtx_distance_in_prong_sz;
   Double_t        vtx_blobs_vtx_distance_in_prong[200];   //[vtx_blobs_vtx_distance_in_prong_sz]
   Int_t           vtx_blobs_vtx_energy_in_prong_sz;
   Double_t        vtx_blobs_vtx_energy_in_prong[200];   //[vtx_blobs_vtx_energy_in_prong_sz]
   Bool_t          truth_has_physics_event;
   Bool_t          truth_is_fiducial;
   //Int_t           truth_primTrajN;

   Int_t           truth_hadronReweightNPaths; //HadronReweight 2.0
   Int_t           truth_hadronReweightNPoints; //HadronReweight 2.0

   Int_t           truth_reco_has_michel_electron;
   Int_t           truth_reco_has_muon_charge;
   Int_t           truth_reco_has_single_proton;
   Int_t           truth_reco_is_fiducial;
   Int_t           truth_reco_is_minos_match;
   Int_t           truth_reco_muon_is_minos_match_stub;
   Int_t           truth_reco_muon_is_minos_match_track;
   Int_t           truth_reco_pass_CCQENu_precuts;
   //Double_t        truth_neutron_kevinwgt10down;
   //Double_t        truth_neutron_kevinwgt10up;
   //Double_t        truth_neutron_kevinwgt20down;
   //Double_t        truth_neutron_kevinwgt20up;
   //Double_t        truth_neutron_kevinwgt50down;
   //Double_t        truth_neutron_kevinwgt50up;
   //Double_t        truth_neutron_kevinwgtvardown;
   //Double_t        truth_neutron_kevinwgtvarup;
   //Int_t           truth_primTrajInelasticReweightCode_sz;
   //Int_t           truth_primTrajInelasticReweightCode[200];   //[truth_primTrajInelasticReweightCode_sz]
   //Int_t           truth_primTrajPDG_sz;
   //Int_t           truth_primTrajPDG[200];   //[truth_primTrajPDG_sz]
   //Int_t           truth_primTrajReweightFiducialContained_sz;
   //Int_t           truth_primTrajReweightFiducialContained[200];   //[truth_primTrajReweightFiducialContained_sz]

   Int_t           truth_hadronReweightPDG_sz;
   Int_t           truth_hadronReweightPDG[200];   // HadronReweight 2.0
   Int_t           truth_hadronReweightIntCode_sz;
   Int_t           truth_hadronReweightIntCode[200];   // HadronReweight 2.0
   Int_t           truth_hadronReweightTrackID_sz;
   Int_t           truth_hadronReweightTrackID[200];   // HadronReweight 2.0
   Int_t           truth_hadronReweightNuke_sz;
   Int_t           truth_hadronReweightNuke[200];   // HadronReweight 2.0

   Int_t           genie_wgt_n_shifts;
   Double_t        truth_genie_wgt_AGKYxF1pi[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_AhtBY[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_BhtBY[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_CCQEPauliSupViaKF[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_CV1uBY[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_CV2uBY[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_EtaNCEL[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_FrAbs_N[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_FrAbs_pi[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_FrCEx_N[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_FrCEx_pi[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_FrElas_N[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_FrElas_pi[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_FrInel_N[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_FrInel_pi[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_FrPiProd_N[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_FrPiProd_pi[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_MFP_N[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_MFP_pi[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_MaCCQE[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_MaCCQEshape[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_MaNCEL[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_MaRES[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_MvRES[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_NormCCQE[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_NormCCRES[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_NormDISCC[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_NormNCRES[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_RDecBR1gamma[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_Rvn1pi[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_Rvn2pi[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_Rvp1pi[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_Rvp2pi[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_Theta_Delta2Npi[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_VecFFCCQEshape[7];   //[genie_wgt_n_shifts]
   Double_t        truth_genie_wgt_shifts[7];   //[genie_wgt_n_shifts]
   //Int_t           truth_primTrajFinalP_sz;
   //Double_t        truth_primTrajFinalP[200];   //[truth_primTrajFinalP_sz]
   //Int_t           truth_primTrajInitialP_sz;
   //Double_t        truth_primTrajInitialP[200];   //[truth_primTrajInitialP_sz]
   //Int_t           truth_primTrajReweightPathLength_sz;
   //Double_t        truth_primTrajReweightPathLength[200];   //[truth_primTrajReweightPathLength_sz]
   //Int_t           truth_primTrajTotalPathLength_sz;
   //Double_t        truth_primTrajTotalPathLength[200];   //[truth_primTrajTotalPathLength_sz]

   Int_t           truth_hadronReweightInitialE_sz;
   Double_t        truth_hadronReweightInitialE[200];   // HadronReweight 2.0
   Int_t           truth_hadronReweightFinalE_sz;
   Double_t        truth_hadronReweightFinalE[200];   // HadronReweight 2.0
   Int_t           truth_hadronReweightInitialSigmaE_sz;
   Double_t        truth_hadronReweightInitialSigmaE[200];   // HadronReweight 2.0
   Int_t           truth_hadronReweightFinalSigmaE_sz;
   Double_t        truth_hadronReweightFinalSigmaE[200];   // HadronReweight 2.0
   Int_t           truth_hadronReweightColumnarDensity_sz;
   Double_t        truth_hadronReweightColumnarDensity[200];   // HadronReweight 2.0
   Int_t           truth_hadronReweightPosX_sz;
   Double_t        truth_hadronReweightPosX[200];   // HadronReweight 2.0
   Int_t           truth_hadronReweightPosY_sz;
   Double_t        truth_hadronReweightPosY[200];   // HadronReweight 2.0
   Int_t           truth_hadronReweightPosZ_sz;
   Double_t        truth_hadronReweightPosZ[200];   // HadronReweight 2.0

   Int_t           CCQENu_nuFlavor;
   Int_t           CCQENu_nuHelicity;
   Int_t           CCQENu_intCurrent;
   Int_t           CCQENu_intType;
   Double_t        CCQENu_E;
   Double_t        CCQENu_Q2;
   Double_t        CCQENu_x;
   Double_t        CCQENu_y;
   Double_t        CCQENu_W;
   Double_t        CCQENu_score;
   Double_t        CCQENu_leptonE[4];
   Double_t        CCQENu_vtx[4];
   Bool_t          CCQENu_minos_trk_is_contained;
   Bool_t          CCQENu_minos_trk_is_ok;
   Bool_t          CCQENu_minos_used_range;
   Bool_t          CCQENu_minos_used_curvature;
   Int_t           CCQENu_minos_trk_end_plane;
   Int_t           CCQENu_minos_trk_quality;
   Int_t           CCQENu_r_minos_trk_vtx_plane;
   Int_t           CCQENu_t_minos_trk_numFSMuons;
   Int_t           CCQENu_t_minos_trk_primFSLeptonPDG;
   Double_t        CCQENu_enu_muon;
   Double_t        CCQENu_enu_proton;
   Double_t        CCQENu_minos_trk_bave;
   Double_t        CCQENu_minos_trk_chi2;
   Double_t        CCQENu_minos_trk_end_u;
   Double_t        CCQENu_minos_trk_end_v;
   Double_t        CCQENu_minos_trk_end_x;
   Double_t        CCQENu_minos_trk_end_y;
   Double_t        CCQENu_minos_trk_end_z;
   Double_t        CCQENu_minos_trk_eqp;
   Double_t        CCQENu_minos_trk_eqp_qp;
   Double_t        CCQENu_minos_trk_fit_pass;
   Double_t        CCQENu_minos_trk_ndf;
   Double_t        CCQENu_minos_trk_p;
   Double_t        CCQENu_minos_trk_p_curvature;
   Double_t        CCQENu_minos_trk_p_range;
   Double_t        CCQENu_minos_trk_qp;
   Double_t        CCQENu_minos_trk_vtx_x;
   Double_t        CCQENu_minos_trk_vtx_y;
   Double_t        CCQENu_minos_trk_vtx_z;
   Double_t        CCQENu_muon_E;
   Double_t        CCQENu_muon_P;
   Double_t        CCQENu_muon_T;
   Double_t        CCQENu_muon_score;
   Double_t        CCQENu_muon_theta;
   //Double_t        CCQENu_recoil_calE;
   Double_t        CCQENu_pion_score;
   Double_t        CCQENu_pion_score1;
   Double_t        CCQENu_pion_score2;
   Double_t        CCQENu_proton_E_BetheBloch_biasDown;
   Double_t        CCQENu_proton_E_BetheBloch_biasUp;
   Double_t        CCQENu_proton_E_Birks_bias;
   Double_t        CCQENu_proton_E_MEU_biasDown;
   Double_t        CCQENu_proton_E_MEU_biasUp;
   Double_t        CCQENu_proton_E_Mass_biasDown;
   Double_t        CCQENu_proton_E_Mass_biasUp;
   Double_t        CCQENu_proton_E_fromdEdx;
   Double_t        CCQENu_proton_P_fromdEdx;
   Double_t        CCQENu_proton_T_fromdEdx;
   Double_t        CCQENu_proton_calib_energy;
   Double_t        CCQENu_proton_score;
   Double_t        CCQENu_proton_score1;
   Double_t        CCQENu_proton_score1_BetheBloch_biasDown;
   Double_t        CCQENu_proton_score1_BetheBloch_biasUp;
   Double_t        CCQENu_proton_score1_Birks_bias;
   Double_t        CCQENu_proton_score1_MEU_biasDown;
   Double_t        CCQENu_proton_score1_MEU_biasUp;
   Double_t        CCQENu_proton_score1_Mass_biasDown;
   Double_t        CCQENu_proton_score1_Mass_biasUp;
   Double_t        CCQENu_proton_score2;
   Double_t        CCQENu_proton_theta_fromdEdx;
   Double_t        CCQENu_r_minos_trk_bdL;
   Double_t        CCQENu_r_minos_trk_end_dcosx;
   Double_t        CCQENu_r_minos_trk_end_dcosy;
   Double_t        CCQENu_r_minos_trk_end_dcosz;
   Double_t        CCQENu_r_minos_trk_vtx_dcosx;
   Double_t        CCQENu_r_minos_trk_vtx_dcosy;
   Double_t        CCQENu_r_minos_trk_vtx_dcosz;
   Double_t        CCQENu_t_minos_trk_primFSLepMinosInitProjPx;
   Double_t        CCQENu_t_minos_trk_primFSLepMinosInitProjPy;
   Double_t        CCQENu_t_minos_trk_primFSLepMinosInitProjPz;
   Double_t        CCQENu_t_minos_trk_primFSLepMinosInitProjX;
   Double_t        CCQENu_t_minos_trk_primFSLepMinosInitProjY;
   Double_t        CCQENu_t_minos_trk_primFSLepMinosInitProjZ;
   Double_t        CCQENu_t_minos_trk_primFSLepMnvFinalPx;
   Double_t        CCQENu_t_minos_trk_primFSLepMnvFinalPy;
   Double_t        CCQENu_t_minos_trk_primFSLepMnvFinalPz;
   Double_t        CCQENu_t_minos_trk_primFSLepMnvFinalX;
   Double_t        CCQENu_t_minos_trk_primFSLepMnvFinalY;
   Double_t        CCQENu_t_minos_trk_primFSLepMnvFinalZ;
   Double_t        CCQENu_t_minos_trk_primFSLepMnvInitPx;
   Double_t        CCQENu_t_minos_trk_primFSLepMnvInitPy;
   Double_t        CCQENu_t_minos_trk_primFSLepMnvInitPz;
   Double_t        CCQENu_t_minos_trk_primFSLepMnvInitX;
   Double_t        CCQENu_t_minos_trk_primFSLepMnvInitY;
   Double_t        CCQENu_t_minos_trk_primFSLepMnvInitZ;
   Int_t           CCQENu_sec_protons_E_BetheBloch_biasDown_sz;
   Double_t        CCQENu_sec_protons_E_BetheBloch_biasDown[200];   //[CCQENu_sec_protons_E_BetheBloch_biasDown_sz]
   Int_t           CCQENu_sec_protons_E_BetheBloch_biasUp_sz;
   Double_t        CCQENu_sec_protons_E_BetheBloch_biasUp[200];   //[CCQENu_sec_protons_E_BetheBloch_biasUp_sz]
   Int_t           CCQENu_sec_protons_E_Birks_bias_sz;
   Double_t        CCQENu_sec_protons_E_Birks_bias[200];   //[CCQENu_sec_protons_E_Birks_bias_sz]
   Int_t           CCQENu_sec_protons_E_MEU_biasDown_sz;
   Double_t        CCQENu_sec_protons_E_MEU_biasDown[200];   //[CCQENu_sec_protons_E_MEU_biasDown_sz]
   Int_t           CCQENu_sec_protons_E_MEU_biasUp_sz;
   Double_t        CCQENu_sec_protons_E_MEU_biasUp[200];   //[CCQENu_sec_protons_E_MEU_biasUp_sz]
   Int_t           CCQENu_sec_protons_E_Mass_biasDown_sz;
   Double_t        CCQENu_sec_protons_E_Mass_biasDown[200];   //[CCQENu_sec_protons_E_Mass_biasDown_sz]
   Int_t           CCQENu_sec_protons_E_Mass_biasUp_sz;
   Double_t        CCQENu_sec_protons_E_Mass_biasUp[200];   //[CCQENu_sec_protons_E_Mass_biasUp_sz]
   Int_t           CCQENu_sec_protons_E_fromdEdx_sz;
   Double_t        CCQENu_sec_protons_E_fromdEdx[200];   //[CCQENu_sec_protons_E_fromdEdx_sz]
   Int_t           CCQENu_sec_protons_P_fromdEdx_sz;
   Double_t        CCQENu_sec_protons_P_fromdEdx[200];   //[CCQENu_sec_protons_P_fromdEdx_sz]
   Int_t           CCQENu_sec_protons_T_fromCalo_sz;
   Double_t        CCQENu_sec_protons_T_fromCalo[200];   //[CCQENu_sec_protons_T_fromCalo_sz]
   Int_t           CCQENu_sec_protons_T_fromdEdx_sz;
   Double_t        CCQENu_sec_protons_T_fromdEdx[200];   //[CCQENu_sec_protons_T_fromdEdx_sz]
   Int_t           CCQENu_sec_protons_pion_scores_sz;
   Double_t        CCQENu_sec_protons_pion_scores[200];   //[CCQENu_sec_protons_pion_scores_sz]
   Int_t           CCQENu_sec_protons_pion_scores1_sz;
   Double_t        CCQENu_sec_protons_pion_scores1[200];   //[CCQENu_sec_protons_pion_scores1_sz]
   Int_t           CCQENu_sec_protons_pion_scores2_sz;
   Double_t        CCQENu_sec_protons_pion_scores2[200];   //[CCQENu_sec_protons_pion_scores2_sz]
   Int_t           CCQENu_sec_protons_proton_scores_sz;
   Double_t        CCQENu_sec_protons_proton_scores[200];   //[CCQENu_sec_protons_proton_scores_sz]
   Int_t           CCQENu_sec_protons_proton_scores1_sz;
   Double_t        CCQENu_sec_protons_proton_scores1[200];   //[CCQENu_sec_protons_proton_scores1_sz]
   Int_t           CCQENu_sec_protons_proton_scores2_sz;
   Double_t        CCQENu_sec_protons_proton_scores2[200];   //[CCQENu_sec_protons_proton_scores2_sz]
   Int_t           CCQENu_sec_protons_score1_BetheBloch_biasDown_sz;
   Double_t        CCQENu_sec_protons_score1_BetheBloch_biasDown[200];   //[CCQENu_sec_protons_score1_BetheBloch_biasDown_sz]
   Int_t           CCQENu_sec_protons_score1_BetheBloch_biasUp_sz;
   Double_t        CCQENu_sec_protons_score1_BetheBloch_biasUp[200];   //[CCQENu_sec_protons_score1_BetheBloch_biasUp_sz]
   Int_t           CCQENu_sec_protons_score1_Birks_bias_sz;
   Double_t        CCQENu_sec_protons_score1_Birks_bias[200];   //[CCQENu_sec_protons_score1_Birks_bias_sz]
   Int_t           CCQENu_sec_protons_score1_MEU_biasDown_sz;
   Double_t        CCQENu_sec_protons_score1_MEU_biasDown[200];   //[CCQENu_sec_protons_score1_MEU_biasDown_sz]
   Int_t           CCQENu_sec_protons_score1_MEU_biasUp_sz;
   Double_t        CCQENu_sec_protons_score1_MEU_biasUp[200];   //[CCQENu_sec_protons_score1_MEU_biasUp_sz]
   Int_t           CCQENu_sec_protons_score1_Mass_biasDown_sz;
   Double_t        CCQENu_sec_protons_score1_Mass_biasDown[200];   //[CCQENu_sec_protons_score1_Mass_biasDown_sz]
   Int_t           CCQENu_sec_protons_score1_Mass_biasUp_sz;
   Double_t        CCQENu_sec_protons_score1_Mass_biasUp[200];   //[CCQENu_sec_protons_score1_Mass_biasUp_sz]
   Int_t           CCQENu_sec_protons_theta_fromdEdx_sz;
   Double_t        CCQENu_sec_protons_theta_fromdEdx[200];   //[CCQENu_sec_protons_theta_fromdEdx_sz]
   Double_t        CCQENu_sys_muon_curve_energy_shift[200];
   Double_t        CCQENu_sys_muon_energy_shift[200];
   Double_t        CCQENu_sys_muon_minerva_energy_shift[200];
   Double_t        CCQENu_sys_muon_qSquared_shift[200];
   Double_t        CCQENu_sys_muon_range_energy_shift[200];
   Double_t        CCQENu_sys_muon_wSquared_shift[200];
   Double_t        CCQENu_sys_muon_xbj_shift[200];
   Double_t        CCQENu_sys_muon_y_shift[200];
   Double_t        CCQENu_sys_nu_energy_shift[200];
   Double_t        CCQENu_sys_recoil_energy_shift[200];
   Double_t        CCQENu_sys_recoil_qSquared_shift[200];
   Double_t        CCQENu_sys_recoil_wSquared_shift[200];
   Double_t        CCQENu_sys_recoil_xbj_shift[200];
   Double_t        CCQENu_sys_recoil_y_shift[200];
   Double_t        CCQENu_sys_total_qSquared_shift[200];
   Double_t        CCQENu_sys_total_wSquared_shift[200];
   Double_t        CCQENu_sys_total_xbj_shift[200];
   Double_t        CCQENu_sys_total_y_shift[200];
   Int_t           ev_run;
   Int_t           ev_subrun;
   Int_t           ev_detector;
   Int_t           ev_triggerType;
   Int_t           ev_gate;
   Int_t           ev_global_gate;
   Int_t           ev_gps_time_sec;
   Int_t           ev_gps_time_usec;
   Int_t           mc_run;
   Int_t           mc_subrun;
   Int_t           mc_nInteractions;
   Int_t           mc_MIState;
   Double_t        mc_pot;
   Int_t           mc_beamConfig;
   Int_t           mc_processType;
   Int_t           mc_nthEvtInSpill;
   Int_t           mc_nthEvtInFile;
   Int_t           mc_intType;
   Int_t           mc_current;
   Int_t           mc_charm;
   Double_t        mc_weight;
   Double_t        mc_XSec;
   Double_t        mc_diffXSec;
   Int_t           mc_incoming;
   Double_t        mc_fluxDriverProb;
   Int_t           mc_targetNucleus;
   Int_t           mc_targetZ;
   Int_t           mc_targetA;
   Int_t           mc_targetNucleon;
   Int_t           mc_struckQuark;
   Int_t           mc_seaQuark;
   Int_t           mc_resID;
   Int_t           mc_primaryLepton;
   Double_t        mc_incomingE;
   Double_t        mc_Bjorkenx;
   Double_t        mc_Bjorkeny;
   Double_t        mc_Q2;
   Double_t        mc_nuT;
   Double_t        mc_w;
   Double_t        mc_vtx[4];
   Double_t        mc_incomingPartVec[4];
   Double_t        mc_initNucVec[4];
   Double_t        mc_primFSLepton[4];
   Int_t           mc_nFSPart;
   Double_t        mc_FSPartPx[200];   //[mc_nFSPart]
   Double_t        mc_FSPartPy[200];   //[mc_nFSPart]
   Double_t        mc_FSPartPz[200];   //[mc_nFSPart]
   Double_t        mc_FSPartE[200];   //[mc_nFSPart]
   Int_t           mc_FSPartPDG[200];   //[mc_nFSPart]
   Int_t           mc_er_nPart;
   Int_t           mc_er_ID[200];   //[mc_er_nPart]
   Int_t           mc_er_status[200];   //[mc_er_nPart]
   Double_t        mc_er_posInNucX[200];   //[mc_er_nPart]
   Double_t        mc_er_posInNucY[200];   //[mc_er_nPart]
   Double_t        mc_er_posInNucZ[200];   //[mc_er_nPart]
   Double_t        mc_er_Px[200];   //[mc_er_nPart]
   Double_t        mc_er_Py[200];   //[mc_er_nPart]
   Double_t        mc_er_Pz[200];   //[mc_er_nPart]
   Double_t        mc_er_E[200];   //[mc_er_nPart]
   Int_t           mc_er_FD[200];   //[mc_er_nPart]
   Int_t           mc_er_LD[200];   //[mc_er_nPart]
   Int_t           mc_er_mother[200];   //[mc_er_nPart]
   Int_t           mc_fr_nNuAncestorIDs;
   Int_t           mc_fr_nuAncestorIDs[200];   //[mc_fr_nNuAncestorIDs]
   Int_t           mc_fr_nuParentID;
   Int_t           mc_fr_decMode;
   Double_t        mc_fr_primProtonVtx[3];
   Double_t        mc_fr_primProtonP[4];
   Double_t        mc_fr_nuParentDecVtx[3];
   Double_t        mc_fr_nuParentProdVtx[3];
   Double_t        mc_fr_nuParentProdP[4];
   Double_t        mc_cvweight_total;
   Double_t        wgt;
   Double_t        mc_cvweight_totalFlux;
   Double_t        mc_cvweight_totalXsec;
   Double_t        mc_ppfx1_cvweight;
   Double_t        mc_hornCurrent_cvweight;
   Double_t        mc_gen1_cvweight_total;
   Double_t        gen1_wgt;
   Double_t        mc_gen1_cvweight_totalFlux;
   Double_t        mc_gen1_cvweight_NA49;
   Int_t           mc_wgt_Flux_BeamFocus_sz;
   Double_t        mc_wgt_Flux_BeamFocus[100];   //[mc_wgt_Flux_BeamFocus_sz]
   Int_t           mc_wgt_gen1_Flux_Tertiary_sz;
   Double_t        mc_wgt_gen1_Flux_Tertiary[100];   //[mc_wgt_gen1_Flux_Tertiary_sz]
   Int_t           mc_wgt_gen1_Flux_NA49_sz;
   Double_t        mc_wgt_gen1_Flux_NA49[100];   //[mc_wgt_gen1_Flux_NA49_sz]
   Int_t           mc_wgt_Norm_sz;
   Double_t        mc_wgt_Norm[1];   //[mc_wgt_Norm_sz]
   Int_t           mc_wgt_ppfx1_Total_sz;
   Double_t        mc_wgt_ppfx1_Total[100];   //[mc_wgt_ppfx1_Total_sz]
   Int_t           n_prongs;
   Int_t           prong_nParticles[200];   //[n_prongs]
   Double_t        prong_part_score[200];   //[n_prongs]
   Double_t        prong_part_mass[200];   //[n_prongs]
   Int_t           prong_part_charge[200];   //[n_prongs]
   Int_t           prong_part_pid[200];   //[n_prongs]
   //   vector<vector<double> > *prong_part_E;
   //   vector<vector<double> > *prong_part_pos;
   Int_t           batch_structure;
   Int_t           reco_vertex_batch;

   // List of branches
   TBranch        *b_eventID;   //!
   TBranch        *b_physEvtNum;   //!
   TBranch        *b_n_hyps;   //!
   TBranch        *b_processType;   //!
   TBranch        *b_primaryPart;   //!
   TBranch        *b_n_slices;   //!
   TBranch        *b_slice_numbers;   //!
   TBranch        *b_shared_slice;   //!
   TBranch        *b_vtx;   //!
   TBranch        *b_vtxErr;   //!
   TBranch        *b_E;   //!
   TBranch        *b_found_truth;   //!
   TBranch        *b_phys_front_activity;   //!
   TBranch        *b_phys_energy_in_road_upstream_is_rockmuon_consistent;   //!
   TBranch        *b_rock_muons_removed;   //!
   TBranch        *b_minos_track_match;   //!
   TBranch        *b_minos_stub_match;   //!
   TBranch        *b_unknown_helicity;   //!
   TBranch        *b_minos_track_inside_partial_plane;   //!
   TBranch        *b_prim_vtx_has_misassigned_track_direction;   //!
   TBranch        *b_prim_vtx_has_broken_track;   //!
   TBranch        *b_broken_track_most_us_plane;   //!
   TBranch        *b_event_unused_start_vertices;   //!
   TBranch        *b_event_used_start_vertices;   //!
   TBranch        *b_has_interaction_vertex;   //!
   TBranch        *b_has_single_proton;   //!
   TBranch        *b_improved_nmichel;   //!
   TBranch        *b_multiplicity;   //!
   TBranch        *b_muon_fuzz_energy;   //!
   TBranch        *b_muon_is_minos_match_stub;   //!
   TBranch        *b_muon_is_minos_match_track;   //!
   TBranch        *b_n_anchored_long_trk_prongs;   //!
   TBranch        *b_n_anchored_short_trk_prongs;   //!
   TBranch        *b_n_iso_trk_prongs;   //!
   TBranch        *b_n_minos_matches;   //!
   TBranch        *b_n_muon_iso_blobs;   //!
   TBranch        *b_n_nonvtx_iso_blobs;   //!
   TBranch        *b_n_nonvtx_iso_blobs_all;   //!
   TBranch        *b_part_response_recoil_nClus;   //!
   TBranch        *b_pass_CCQENu_precuts;   //!
   TBranch        *b_phys_energy_in_road_downstream_nplanes;   //!
   TBranch        *b_phys_energy_in_road_upstream_nplanes;   //!
   TBranch        *b_phys_n_dead_discr_pair;   //!
   TBranch        *b_phys_n_dead_discr_pair_in_prim_track_region;   //!
   TBranch        *b_phys_n_dead_discr_pair_two_mod_downstream_prim_track;   //!
   TBranch        *b_phys_n_dead_discr_pair_two_mod_upstream_prim_vtx;   //!
   TBranch        *b_phys_n_dead_discr_pair_upstream_prim_track_proj;   //!
   TBranch        *b_phys_vertex_is_fiducial;   //!
   TBranch        *b_proton_prong_PDG;   //!
   TBranch        *b_proton_prong_traj_ID;   //!
   TBranch        *b_slice_n_hits;   //!
   TBranch        *b_truth_has_michel_electron;   //!
   TBranch        *b_truth_improved_michel_electron;   //!
   TBranch        *b_dis_id_energy;   //!
   TBranch        *b_energy_from_mc;   //!
   TBranch        *b_energy_from_mc_fraction;   //!
   TBranch        *b_energy_from_mc_fraction_of_highest;   //!
   TBranch        *b_muon_iso_blobs_energy;   //!
   TBranch        *b_muon_minerva_trk_chi2PerDoF;   //!
   TBranch        *b_muon_phi;   //!
   TBranch        *b_muon_theta;   //!
   TBranch        *b_muon_thetaX;   //!
   TBranch        *b_muon_thetaY;   //!
   TBranch        *b_nonvtx_iso_blobs_energy;   //!
   TBranch        *b_nonvtx_iso_blobs_energy_all;   //!
   TBranch        *b_numi_horn_curr;   //!
   TBranch        *b_numi_pot;   //!
   TBranch        *b_numi_x;   //!
   TBranch        *b_numi_x_width;   //!
   TBranch        *b_numi_y;   //!
   TBranch        *b_numi_y_width;   //!
   TBranch        *b_part_response_recoil_em_id;   //!
   TBranch        *b_part_response_recoil_em_id_err;   //!
   TBranch        *b_part_response_recoil_em_od;   //!
   TBranch        *b_part_response_recoil_em_od_err;   //!
   TBranch        *b_part_response_recoil_high_neutron_id;   //!
   TBranch        *b_part_response_recoil_high_neutron_id_err;   //!
   TBranch        *b_part_response_recoil_high_neutron_od;   //!
   TBranch        *b_part_response_recoil_high_neutron_od_err;   //!
   TBranch        *b_part_response_recoil_low_neutron_id;   //!
   TBranch        *b_part_response_recoil_low_neutron_id_err;   //!
   TBranch        *b_part_response_recoil_low_neutron_od;   //!
   TBranch        *b_part_response_recoil_low_neutron_od_err;   //!
   TBranch        *b_part_response_recoil_meson_id;   //!
   TBranch        *b_part_response_recoil_meson_id_err;   //!
   TBranch        *b_part_response_recoil_meson_od;   //!
   TBranch        *b_part_response_recoil_meson_od_err;   //!
   TBranch        *b_part_response_recoil_mid_neutron_id;   //!
   TBranch        *b_part_response_recoil_mid_neutron_id_err;   //!
   TBranch        *b_part_response_recoil_mid_neutron_od;   //!
   TBranch        *b_part_response_recoil_mid_neutron_od_err;   //!
   TBranch        *b_part_response_recoil_muon_id;   //!
   TBranch        *b_part_response_recoil_muon_id_err;   //!
   TBranch        *b_part_response_recoil_muon_od;   //!
   TBranch        *b_part_response_recoil_muon_od_err;   //!
   TBranch        *b_part_response_recoil_other_id;   //!
   TBranch        *b_part_response_recoil_other_id_err;   //!
   TBranch        *b_part_response_recoil_other_od;   //!
   TBranch        *b_part_response_recoil_other_od_err;   //!
   TBranch        *b_part_response_recoil_proton_id;   //!
   TBranch        *b_part_response_recoil_proton_id_err;   //!
   TBranch        *b_part_response_recoil_proton_od;   //!
   TBranch        *b_part_response_recoil_proton_od_err;   //!
   TBranch        *b_part_response_recoil_xtalk_id;   //!
   TBranch        *b_part_response_recoil_xtalk_id_err;   //!
   TBranch        *b_part_response_recoil_xtalk_od;   //!
   TBranch        *b_part_response_recoil_xtalk_od_err;   //!
   TBranch        *b_phys_energy_dispersed;   //!
   TBranch        *b_phys_energy_in_road_downstream;   //!
   TBranch        *b_phys_energy_in_road_upstream;   //!
   TBranch        *b_phys_energy_unattached;   //!
   TBranch        *b_prim_vtx_smallest_opening_angle;   //!
   TBranch        *b_proton_track_length;   //!
   //-------------------------------------------------------
   TBranch        *b_proton_track_endx;   //!
   TBranch        *b_proton_track_endy;   //!
   TBranch        *b_proton_track_endz;   //!

   TBranch        *b_CCQENu_proton_startPointX;   //!
   TBranch        *b_CCQENu_proton_startPointY;   //!
   TBranch        *b_CCQENu_proton_startPointZ;   //!

   TBranch        *b_CCQENu_proton_endPointX;   //!
   TBranch        *b_CCQENu_proton_endPointY;   //!
   TBranch        *b_CCQENu_proton_endPointZ;   //!

   TBranch        *b_CCQENu_proton_theta;   //!
   TBranch        *b_CCQENu_proton_thetaX;   //!
   TBranch        *b_CCQENu_proton_thetaY;   //!
   TBranch        *b_CCQENu_proton_phi;   //!

   TBranch        *b_CCQENu_proton_ekin;   //!
   TBranch        *b_CCQENu_proton_enu;   //!
   TBranch        *b_CCQENu_proton_q2;   //!
   TBranch        *b_CCQENu_proton_E;   //!
   TBranch        *b_CCQENu_proton_p;   //!
   TBranch        *b_CCQENu_proton_px;   //!
   TBranch        *b_CCQENu_proton_py;   //!
   TBranch        *b_CCQENu_proton_pz;   //!
   //-------------------------------------------------------
   TBranch        *b_recoil_energy_nonmuon_nonvtx0mm;   //!
   TBranch        *b_recoil_energy_nonmuon_nonvtx100mm;   //!
   TBranch        *b_recoil_energy_nonmuon_nonvtx150mm;   //!
   TBranch        *b_recoil_energy_nonmuon_nonvtx200mm;   //!
   TBranch        *b_recoil_energy_nonmuon_nonvtx250mm;   //!
   TBranch        *b_recoil_energy_nonmuon_nonvtx300mm;   //!
   TBranch        *b_recoil_energy_nonmuon_nonvtx50mm;   //!
   TBranch        *b_recoil_energy_nonmuon_vtx0mm;   //!
   TBranch        *b_recoil_energy_nonmuon_vtx100mm;   //!
   TBranch        *b_recoil_energy_nonmuon_vtx150mm;   //!
   TBranch        *b_recoil_energy_nonmuon_vtx200mm;   //!
   TBranch        *b_recoil_energy_nonmuon_vtx250mm;   //!
   TBranch        *b_recoil_energy_nonmuon_vtx300mm;   //!
   TBranch        *b_recoil_energy_nonmuon_vtx50mm;   //!
   TBranch        *b_vtx_blobs_energy;   //!
   TBranch        *b_vtx_iso_blobs_energy_outside_radius;   //!
   TBranch        *b_all_event_start_vertex_fv_minos_match_sz;   //!
   TBranch        *b_all_event_start_vertex_fv_minos_match;   //!
   TBranch        *b_clusters_found_at_end_proton_prong_sz;   //!
   TBranch        *b_clusters_found_at_end_proton_prong;   //!
   TBranch        *b_event_in_time_vertex_types_sz;   //!
   TBranch        *b_event_in_time_vertex_types;   //!
   TBranch        *b_event_track_nhits_sz;   //!
   TBranch        *b_event_track_nhits;   //!
   TBranch        *b_event_vertex_types_sz;   //!
   TBranch        *b_event_vertex_types;   //!
   TBranch        *b_has_michel_bgmodule_sz;   //!
   TBranch        *b_has_michel_bgmodule;   //!
   TBranch        *b_has_michel_category_sz;   //!
   TBranch        *b_has_michel_category;   //!
   TBranch        *b_has_michel_edmodule_sz;   //!
   TBranch        *b_has_michel_edmodule;   //!
   TBranch        *b_has_michel_in_vertex_point_sz;   //!
   TBranch        *b_has_michel_in_vertex_point;   //!
   TBranch        *b_has_michel_matched_pdg_sz;   //!
   TBranch        *b_has_michel_matched_pdg;   //!
   TBranch        *b_has_michel_matched_primary_pdg_sz;   //!
   TBranch        *b_has_michel_matched_primary_pdg;   //!
   TBranch        *b_has_michel_ndigits_sz;   //!
   TBranch        *b_has_michel_ndigits;   //!
   TBranch        *b_has_michel_nmodules_sz;   //!
   TBranch        *b_has_michel_nmodules;   //!
   TBranch        *b_has_michel_nplanes_sz;   //!
   TBranch        *b_has_michel_nplanes;   //!
   TBranch        *b_has_michel_ntracks_sz;   //!
   TBranch        *b_has_michel_ntracks;   //!
   TBranch        *b_has_michel_slice_number_sz;   //!
   TBranch        *b_has_michel_slice_number;   //!
   TBranch        *b_has_michel_vertex_type_sz;   //!
   TBranch        *b_has_michel_vertex_type;   //!
   TBranch        *b_has_michel_view_sum_sz;   //!
   TBranch        *b_has_michel_view_sum;   //!
   TBranch        *b_improved_michel_in_vertex_point_sz;   //!
   TBranch        *b_improved_michel_in_vertex_point;   //!
   TBranch        *b_improved_michel_match_vec_sz;   //!
   TBranch        *b_improved_michel_match_vec;   //!
   TBranch        *b_improved_michel_matched_pdg_sz;   //!
   TBranch        *b_improved_michel_matched_pdg;   //!
   TBranch        *b_improved_michel_matched_primary_pdg_sz;   //!
   TBranch        *b_improved_michel_matched_primary_pdg;   //!
   TBranch        *b_improved_michel_vertex_type_sz;   //!
   TBranch        *b_improved_michel_vertex_type;   //!
   TBranch        *b_improved_michel_view_vec_sz;   //!
   TBranch        *b_improved_michel_view_vec;   //!
   TBranch        *b_nonvtx_iso_blobs_n_hits_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_n_hits_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_particle_pdg_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_particle_pdg_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_primary_particle_pdg_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_primary_particle_pdg_in_prong;   //!
   TBranch        *b_number_clusters_at_end_proton_prong_sz;   //!
   TBranch        *b_number_clusters_at_end_proton_prong;   //!
   TBranch        *b_recoil_lower_time_limit_sz;   //!
   TBranch        *b_recoil_lower_time_limit;   //!
   TBranch        *b_recoil_upper_time_limit_sz;   //!
   TBranch        *b_recoil_upper_time_limit;   //!
   TBranch        *b_all_event_start_vertex_time_sz;   //!
   TBranch        *b_all_event_start_vertex_time;   //!
   TBranch        *b_all_event_start_vertex_time_minos_match_sz;   //!
   TBranch        *b_all_event_start_vertex_time_minos_match;   //!
   TBranch        *b_calibE_clusters_at_end_proton_prong_sz;   //!
   TBranch        *b_calibE_clusters_at_end_proton_prong;   //!
   TBranch        *b_clusters_found_at_end_proton_prong_max_distance_sz;   //!
   TBranch        *b_clusters_found_at_end_proton_prong_max_distance;   //!
   TBranch        *b_event_extra_track_PID_sz;   //!
   TBranch        *b_event_extra_track_PID;   //!
   TBranch        *b_event_in_time_tracks_energy_sz;   //!
   TBranch        *b_event_in_time_tracks_energy;   //!
   TBranch        *b_event_track_hit_energy_sz;   //!
   TBranch        *b_event_track_hit_energy;   //!
   TBranch        *b_event_track_hit_time_sz;   //!
   TBranch        *b_event_track_hit_time;   //!
   TBranch        *b_event_track_time_diff_sz;   //!
   TBranch        *b_event_track_time_diff;   //!
   TBranch        *b_event_tracks_energy_sz;   //!
   TBranch        *b_event_tracks_energy;   //!
   TBranch        *b_event_vertex_time_diff_sz;   //!
   TBranch        *b_event_vertex_time_diff;   //!
   TBranch        *b_has_michel_data_energy_fraction_sz;   //!
   TBranch        *b_has_michel_data_energy_fraction;   //!
   TBranch        *b_has_michel_distance_sz;   //!
   TBranch        *b_has_michel_distance;   //!
   TBranch        *b_has_michel_energy_sz;   //!
   TBranch        *b_has_michel_energy;   //!
   TBranch        *b_has_michel_hit_charges_sz;   //!
   TBranch        *b_has_michel_hit_charges;   //!
   TBranch        *b_has_michel_hit_time_diff_cluster_sz;   //!
   TBranch        *b_has_michel_hit_time_diff_cluster;   //!
   TBranch        *b_has_michel_hit_time_diff_vtx_sz;   //!
   TBranch        *b_has_michel_hit_time_diff_vtx;   //!
   TBranch        *b_has_michel_hit_times_sz;   //!
   TBranch        *b_has_michel_hit_times;   //!
   TBranch        *b_has_michel_matched_energy_fraction_sz;   //!
   TBranch        *b_has_michel_matched_energy_fraction;   //!
   TBranch        *b_has_michel_slice_energy_sz;   //!
   TBranch        *b_has_michel_slice_energy;   //!
   TBranch        *b_has_michel_time_diff_sz;   //!
   TBranch        *b_has_michel_time_diff;   //!
   TBranch        *b_improved_michel_data_energy_fraction_sz;   //!
   TBranch        *b_improved_michel_data_energy_fraction;   //!
   TBranch        *b_improved_michel_dist_vec_sz;   //!
   TBranch        *b_improved_michel_dist_vec;   //!
   TBranch        *b_improved_michel_ecalo_vec_sz;   //!
   TBranch        *b_improved_michel_ecalo_vec;   //!
   TBranch        *b_improved_michel_evis_vec_sz;   //!
   TBranch        *b_improved_michel_evis_vec;   //!
   TBranch        *b_improved_michel_hit_charges_sz;   //!
   TBranch        *b_improved_michel_hit_charges;   //!
   TBranch        *b_improved_michel_hit_time_diff_cluster_sz;   //!
   TBranch        *b_improved_michel_hit_time_diff_cluster;   //!
   TBranch        *b_improved_michel_hit_time_diff_vtx_sz;   //!
   TBranch        *b_improved_michel_hit_time_diff_vtx;   //!
   TBranch        *b_improved_michel_hit_times_sz;   //!
   TBranch        *b_improved_michel_hit_times;   //!
   TBranch        *b_improved_michel_matched_energy_fraction_sz;   //!
   TBranch        *b_improved_michel_matched_energy_fraction;   //!
   TBranch        *b_improved_michel_tdiff_vec_sz;   //!
   TBranch        *b_improved_michel_tdiff_vec;   //!
   TBranch        *b_improved_michel_tvec_sz;   //!
   TBranch        *b_improved_michel_tvec;   //!
   TBranch        *b_improved_michel_uvec_sz;   //!
   TBranch        *b_improved_michel_uvec;   //!
   TBranch        *b_improved_michel_vvec_sz;   //!
   TBranch        *b_improved_michel_vvec;   //!
   TBranch        *b_improved_michel_xvec_sz;   //!
   TBranch        *b_improved_michel_xvec;   //!
   TBranch        *b_improved_michel_yvec_sz;   //!
   TBranch        *b_improved_michel_yvec;   //!
   TBranch        *b_improved_michel_zvec_sz;   //!
   TBranch        *b_improved_michel_zvec;   //!

   TBranch        *b_improved_michel_u1vec_sz;   //!
   TBranch        *b_improved_michel_u1vec;   //!
   TBranch        *b_improved_michel_v1vec_sz;   //!
   TBranch        *b_improved_michel_v1vec;   //!
   TBranch        *b_improved_michel_x1vec_sz;   //!
   TBranch        *b_improved_michel_x1vec;   //! //!
   TBranch        *b_improved_michel_z1vec_sz;   //!
   TBranch        *b_improved_michel_z1vec;   //!

   TBranch        *b_improved_michel_u2vec_sz;   //!
   TBranch        *b_improved_michel_u2vec;   //!
   TBranch        *b_improved_michel_v2vec_sz;   //!
   TBranch        *b_improved_michel_v2vec;   //!
   TBranch        *b_improved_michel_x2vec_sz;   //!
   TBranch        *b_improved_michel_x2vec;   //! //!
   TBranch        *b_improved_michel_z2vec_sz;   //!
   TBranch        *b_improved_michel_z2vec;   //!
// Adding Aaron's Michel Variable Branches

   TBranch        *b_improved_michel_fitCode_vec;
   TBranch        *b_improved_michel_fitCode_vec_sz;

   TBranch        *b_improved_michel_fitPass_vec;
   TBranch        *b_improved_michel_fitPass_vec_sz;

   TBranch        *b_improved_michel_MatchedEndDist_vec;
   TBranch        *b_improved_michel_MatchedEndDist_vec_sz;

   TBranch        *b_improved_michel_matchedvtx_energy_vec;
   TBranch        *b_improved_michel_matchedvtx_energy_vec_sz;

   TBranch        *b_improved_michel_transdist_vec;
   TBranch        *b_improved_michel_transdist_vec_sz;

   TBranch        *b_improved_michel_polarangle_vec;
   TBranch        *b_improved_michel_polarangle_vec_sz;

   TBranch        *b_improved_michel_nplanes;
   TBranch        *b_improved_michel_nplanes_sz;

   TBranch        *b_improved_michel_clussize;
   TBranch        *b_improved_michel_clussize_sz;

   TBranch        *b_improved_allmichels;


   // MehTool - Mehreen's tool Stuff

   TBranch *b_mehtool_closestclusterX_distance;
   TBranch *b_mehtool_closestclusterX_energy;
   TBranch *b_mehtool_closestclusterX_time;
   TBranch *b_mehtool_closestclusterX_endpoint;

   TBranch *b_mehtool_closestclusterU_distance;
   TBranch *b_mehtool_closestclusterU_energy;
   TBranch *b_mehtool_closestclusterU_time;
   TBranch *b_mehtool_closestclusterU_endpoint;

   TBranch *b_mehtool_closestclusterV_distance;
   TBranch *b_mehtool_closestclusterV_energy;
   TBranch *b_mehtool_closestclusterV_time;
   TBranch *b_mehtool_closestclusterV_endpoint;

   TBranch *b_mehtool_closestclusterX_distance_sz;
   TBranch *b_mehtool_closestclusterX_energy_sz;
   TBranch *b_mehtool_closestclusterX_time_sz;
   TBranch *b_mehtool_closestclusterX_endpoint_sz;

   TBranch *b_mehtool_closestclusterU_distance_sz;
   TBranch *b_mehtool_closestclusterU_energy_sz;
   TBranch *b_mehtool_closestclusterU_time_sz;
   TBranch *b_mehtool_closestclusterU_endpoint_sz;

   TBranch *b_mehtool_closestclusterV_distance_sz;
   TBranch *b_mehtool_closestclusterV_energy_sz;
   TBranch *b_mehtool_closestclusterV_time_sz;
   TBranch *b_mehtool_closestclusterV_endpoint_sz;

   TBranch *b_mehtool_closestclusterVZ_distance_sz;
   TBranch *b_mehtool_closestclusterUZ_distance_sz;
   TBranch *b_mehtool_closestclusterXZ_distance_sz;

   TBranch *b_mehtool_closestclusterVZ_distance;
   TBranch *b_mehtool_closestclusterUZ_distance;
   TBranch *b_mehtool_closestclusterXZ_distance;


   TBranch  *b_mehtool_nmichelsmatch;
   TBranch  *b_mehtool_duplicate_michelindex;
   TBranch  *b_mehtool_closestclusterX_nclusz;
   TBranch  *b_mehtool_closestclusterU_nclusz;
   TBranch  *b_mehtool_closestclusterV_nclusz;

   TBranch  *b_mehtool_closestclusterX_clustime;
   TBranch  *b_mehtool_closestclusterU_clustime;
   TBranch  *b_mehtool_closestclusterV_clustime;

   TBranch  *b_mehtool_closestclusterX_clustime_sz;
   TBranch  *b_mehtool_closestclusterU_clustime_sz;
   TBranch  *b_mehtool_closestclusterV_clustime_sz;

   TBranch *b_mehtool_michel_time;
   TBranch *b_mehtool_michel_time_sz;

   TBranch *b_mehtool_michel_energy;
   TBranch *b_mehtool_michel_energy_sz;

   TBranch *b_mehtool_michel_Xclusters;
   TBranch *b_mehtool_michel_Xclusters_sz;

   TBranch *b_mehtool_michel_Uclusters;
   TBranch *b_mehtool_michel_Uclusters_sz;

   TBranch *b_mehtool_michel_Vclusters;
   TBranch *b_mehtool_michel_Vclusters_sz;

   TBranch  *b_mehtool_michel_x1;
   TBranch  *b_mehtool_michel_x2;
   TBranch  *b_mehtool_michel_u1;
   TBranch  *b_mehtool_michel_u2;
   TBranch  *b_mehtool_michel_v1;
   TBranch  *b_mehtool_michel_v2;
   TBranch  *b_mehtool_michel_z1;
   TBranch  *b_mehtool_michel_z2;

   TBranch  *b_mehtool_michel_x1_sz;
   TBranch  *b_mehtool_michel_x2_sz;
   TBranch  *b_mehtool_michel_u1_sz;
   TBranch  *b_mehtool_michel_u2_sz;
   TBranch  *b_mehtool_michel_v1_sz;
   TBranch  *b_mehtool_michel_v2_sz;
   TBranch  *b_mehtool_michel_z1_sz;
   TBranch  *b_mehtool_michel_z2_sz;

   TBranch   *b_mehtool_closestclusterX_Z_pos;
   TBranch   *b_mehtool_closestclusterU_Z_pos;
   TBranch   *b_mehtool_closestclusterV_Z_pos;

   TBranch *b_mehtool_closestclusterX_Z_pos_sz;
   TBranch *b_mehtool_closestclusterU_Z_pos_sz;
   TBranch *b_mehtool_closestclusterV_Z_pos_sz;

   TBranch   *b_mehtool_closestclusterX_pos;
   TBranch   *b_mehtool_closestclusterU_pos;
   TBranch   *b_mehtool_closestclusterV_pos;

   TBranch *b_mehtool_closestclusterX_pos_sz;
   TBranch *b_mehtool_closestclusterU_pos_sz;
   TBranch *b_mehtool_closestclusterV_pos_sz;





  // TBranch  *b_mehtool_nmichelsmatch_sz;
  // TBranch  *b_mehtool_duplicate_michelindex_sz;
   TBranch  *b_mehtool_closestclusterX_nclusz_sz;
   TBranch  *b_mehtool_closestclusterU_nclusz_sz;
   TBranch  *b_mehtool_closestclusterV_nclusz_sz;


   TBranch *b_mehtool_michel_maxmeandiff;
   TBranch *b_mehtool_michel_maxmeandiff_sz;

   TBranch *b_mehtool_istrueMichel;
   TBranch *b_mehtool_istrueMichel_sz;

   TBranch *b_mehtool_michel_allmichelenergy;
   TBranch *b_mehtool_michel_allmichelenergy_sz;

   TBranch *b_mehtool_michel_from_decay;
   TBranch *b_mehtool_michel_from_decay_sz;

   TBranch *b_mehtool_true_michel_pdg;
   TBranch *b_mehtool_true_michel_pdg_sz;



   // -------------------- True Matched Michel Variables


   TBranch        *b_has_michel_primary_particle_trackID;
   TBranch        *b_michel_from_decay;
   TBranch        *b_true_michel_pdg;
   TBranch        *b_true_michel_x1vec;
   TBranch        *b_true_michel_y1vec;
   TBranch        *b_true_michel_z1vec;
   TBranch        *b_true_michel_x2vec;
   TBranch        *b_true_michel_y2vec;
   TBranch        *b_true_michel_z2vec;
   TBranch        *b_michel_parent_PDG;
   TBranch        *b_michel_parent_trackID;



   TBranch        *b_muon_thetaX_allNodes_sz;   //!
   TBranch        *b_muon_thetaX_allNodes;   //!
   TBranch        *b_muon_thetaY_allNodes_sz;   //!
   TBranch        *b_muon_thetaY_allNodes;   //!
   TBranch        *b_muon_theta_allNodes_sz;   //!
   TBranch        *b_muon_theta_allNodes;   //!
   TBranch        *b_nonvtx_iso_blobs_data_energy_fraction_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_data_energy_fraction_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_distance_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_distance_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_earliest_hit_time_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_earliest_hit_time_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_energy_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_energy_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_highest_hit_energy_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_highest_hit_energy_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_highest_module_u_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_highest_module_u_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_highest_module_v_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_highest_module_v_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_highest_module_x_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_highest_module_x_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_latest_hit_time_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_latest_hit_time_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_lowest_module_u_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_lowest_module_u_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_lowest_module_v_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_lowest_module_v_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_lowest_module_x_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_lowest_module_x_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_matched_energy_fraction_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_matched_energy_fraction_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_start_position_x_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_start_position_x_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_start_position_y_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_start_position_y_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_start_position_z_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_start_position_z_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_time_difference_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_time_difference_in_prong;   //!
   TBranch        *b_nonvtx_iso_blobs_time_in_prong_sz;   //!
   TBranch        *b_nonvtx_iso_blobs_time_in_prong;   //!
   TBranch        *b_proton_prong_4p;   //!
   TBranch        *b_proton_prong_tpos;   //!
   TBranch        *b_recoil_data_fraction_sz;   //!
   TBranch        *b_recoil_data_fraction;   //!
   TBranch        *b_recoil_summed_energy_sz;   //!
   TBranch        *b_recoil_summed_energy;   //!
   TBranch        *b_slice_hit_energy_sz;   //!
   TBranch        *b_slice_hit_energy;   //!
   TBranch        *b_slice_hit_time_sz;   //!
   TBranch        *b_slice_hit_time;   //!
   TBranch        *b_truth_has_michel_from_pion_minus_momentum_sz;   //!
   TBranch        *b_truth_has_michel_from_pion_minus_momentum;   //!
   TBranch        *b_truth_has_michel_from_pion_plus_momentum_sz;   //!
   TBranch        *b_truth_has_michel_from_pion_plus_momentum;   //!
   TBranch        *b_visE_clusters_at_end_proton_prong_sz;   //!
   TBranch        *b_visE_clusters_at_end_proton_prong;   //!
   TBranch        *b_vtx_blobs_iso_distance_in_prong_sz;   //!
   TBranch        *b_vtx_blobs_iso_distance_in_prong;   //!
   TBranch        *b_vtx_blobs_iso_energy_clusters_outside_radius_in_prong_sz;   //!
   TBranch        *b_vtx_blobs_iso_energy_clusters_outside_radius_in_prong;   //!
   TBranch        *b_vtx_blobs_iso_energy_in_prong_sz;   //!
   TBranch        *b_vtx_blobs_iso_energy_in_prong;   //!
   TBranch        *b_vtx_blobs_vtx_distance_in_prong_sz;   //!
   TBranch        *b_vtx_blobs_vtx_distance_in_prong;   //!
   TBranch        *b_vtx_blobs_vtx_energy_in_prong_sz;   //!
   TBranch        *b_vtx_blobs_vtx_energy_in_prong;   //!
   TBranch        *b_truth_has_physics_event;   //!
   TBranch        *b_truth_is_fiducial;   //!
   //TBranch        *b_truth_primTrajN;   //!

   TBranch        *b_truth_hadronReweightNPaths;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightNPoints;   //! HadronReweight 2.0

   TBranch        *b_truth_reco_has_michel_electron;   //!
   TBranch        *b_truth_reco_has_muon_charge;   //!
   TBranch        *b_truth_reco_has_single_proton;   //!
   TBranch        *b_truth_reco_is_fiducial;   //!
   TBranch        *b_truth_reco_is_minos_match;   //!
   TBranch        *b_truth_reco_muon_is_minos_match_stub;   //!
   TBranch        *b_truth_reco_muon_is_minos_match_track;   //!
   TBranch        *b_truth_reco_pass_CCQENu_precuts;   //!
   //TBranch        *b_truth_neutron_kevinwgt10down;   //!
   //TBranch        *b_truth_neutron_kevinwgt10up;   //!
   //TBranch        *b_truth_neutron_kevinwgt20down;   //!
   //TBranch        *b_truth_neutron_kevinwgt20up;   //!
   //TBranch        *b_truth_neutron_kevinwgt50down;   //!
   //TBranch        *b_truth_neutron_kevinwgt50up;   //!
   //TBranch        *b_truth_neutron_kevinwgtvardown;   //!
   //TBranch        *b_truth_neutron_kevinwgtvarup;   //!
   //TBranch        *b_truth_primTrajInelasticReweightCode_sz;   //!
   //TBranch        *b_truth_primTrajInelasticReweightCode;   //!
   //TBranch        *b_truth_primTrajPDG_sz;   //!
   //TBranch        *b_truth_primTrajPDG;   //!
   //TBranch        *b_truth_primTrajReweightFiducialContained_sz;   //!
   //TBranch        *b_truth_primTrajReweightFiducialContained;   //!

   TBranch        *b_truth_hadronReweightPDG_sz;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightPDG;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightIntCode_sz;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightIntCode;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightTrackID_sz;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightTrackID;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightNuke_sz;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightNuke;   //! HadronReweight 2.0

   TBranch        *b_genie_wgt_n_shifts;   //!
   TBranch        *b_truth_genie_wgt_AGKYxF1pi;   //!
   TBranch        *b_truth_genie_wgt_AhtBY;   //!
   TBranch        *b_truth_genie_wgt_BhtBY;   //!
   TBranch        *b_truth_genie_wgt_CCQEPauliSupViaKF;   //!
   TBranch        *b_truth_genie_wgt_CV1uBY;   //!
   TBranch        *b_truth_genie_wgt_CV2uBY;   //!
   TBranch        *b_truth_genie_wgt_EtaNCEL;   //!
   TBranch        *b_truth_genie_wgt_FrAbs_N;   //!
   TBranch        *b_truth_genie_wgt_FrAbs_pi;   //!
   TBranch        *b_truth_genie_wgt_FrCEx_N;   //!
   TBranch        *b_truth_genie_wgt_FrCEx_pi;   //!
   TBranch        *b_truth_genie_wgt_FrElas_N;   //!
   TBranch        *b_truth_genie_wgt_FrElas_pi;   //!
   TBranch        *b_truth_genie_wgt_FrInel_N;   //!
   TBranch        *b_truth_genie_wgt_FrInel_pi;   //!
   TBranch        *b_truth_genie_wgt_FrPiProd_N;   //!
   TBranch        *b_truth_genie_wgt_FrPiProd_pi;   //!
   TBranch        *b_truth_genie_wgt_MFP_N;   //!
   TBranch        *b_truth_genie_wgt_MFP_pi;   //!
   TBranch        *b_truth_genie_wgt_MaCCQE;   //!
   TBranch        *b_truth_genie_wgt_MaCCQEshape;   //!
   TBranch        *b_truth_genie_wgt_MaNCEL;   //!
   TBranch        *b_truth_genie_wgt_MaRES;   //!
   TBranch        *b_truth_genie_wgt_MvRES;   //!
   TBranch        *b_truth_genie_wgt_NormCCQE;   //!
   TBranch        *b_truth_genie_wgt_NormCCRES;   //!
   TBranch        *b_truth_genie_wgt_NormDISCC;   //!
   TBranch        *b_truth_genie_wgt_NormNCRES;   //!
   TBranch        *b_truth_genie_wgt_RDecBR1gamma;   //!
   TBranch        *b_truth_genie_wgt_Rvn1pi;   //!
   TBranch        *b_truth_genie_wgt_Rvn2pi;   //!
   TBranch        *b_truth_genie_wgt_Rvp1pi;   //!
   TBranch        *b_truth_genie_wgt_Rvp2pi;   //!
   TBranch        *b_truth_genie_wgt_Theta_Delta2Npi;   //!
   TBranch        *b_truth_genie_wgt_VecFFCCQEshape;   //!
   TBranch        *b_truth_genie_wgt_shifts;   //!
   //TBranch        *b_truth_primTrajFinalP_sz;   //!
   //TBranch        *b_truth_primTrajFinalP;   //!
   //TBranch        *b_truth_primTrajInitialP_sz;   //!
   //TBranch        *b_truth_primTrajInitialP;   //!
   //TBranch        *b_truth_primTrajReweightPathLength_sz;   //!
   //TBranch        *b_truth_primTrajReweightPathLength;   //!
   //TBranch        *b_truth_primTrajTotalPathLength_sz;   //!
   //TBranch        *b_truth_primTrajTotalPathLength;   //!

   TBranch        *b_truth_hadronReweightInitialE_sz;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightInitialE;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightFinalE_sz;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightFinalE;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightInitialSigmaE_sz;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightInitialSigmaE;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightFinalSigmaE_sz;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightFinalSigmaE;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightColumnarDensity_sz;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightColumnarDensity;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightPosX_sz;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightPosX;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightPosY_sz;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightPosY;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightPosZ_sz;   //! HadronReweight 2.0
   TBranch        *b_truth_hadronReweightPosZ;   //! HadronReweight 2.0

   TBranch        *b_CCQENu_nuFlavor;   //!
   TBranch        *b_CCQENu_nuHelicity;   //!
   TBranch        *b_CCQENu_intCurrent;   //!
   TBranch        *b_CCQENu_intType;   //!
   TBranch        *b_CCQENu_E;   //!
   TBranch        *b_CCQENu_Q2;   //!
   TBranch        *b_CCQENu_x;   //!
   TBranch        *b_CCQENu_y;   //!
   TBranch        *b_CCQENu_W;   //!
   TBranch        *b_CCQENu_score;   //!
   TBranch        *b_CCQENu_leptonE;   //!
   TBranch        *b_CCQENu_vtx;   //!
   TBranch        *b_CCQENu_minos_trk_is_contained;   //!
   TBranch        *b_CCQENu_minos_trk_is_ok;   //!
   TBranch        *b_CCQENu_minos_used_range;   //!
   TBranch        *b_CCQENu_minos_used_curvature;   //!
   TBranch        *b_CCQENu_minos_trk_end_plane;   //!
   TBranch        *b_CCQENu_minos_trk_quality;   //!
   TBranch        *b_CCQENu_r_minos_trk_vtx_plane;   //!
   TBranch        *b_CCQENu_t_minos_trk_numFSMuons;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLeptonPDG;   //!
   TBranch        *b_CCQENu_enu_muon;   //!
   TBranch        *b_CCQENu_enu_proton;   //!
   TBranch        *b_CCQENu_minos_trk_bave;   //!
   TBranch        *b_CCQENu_minos_trk_chi2;   //!
   TBranch        *b_CCQENu_minos_trk_end_u;   //!
   TBranch        *b_CCQENu_minos_trk_end_v;   //!
   TBranch        *b_CCQENu_minos_trk_end_x;   //!
   TBranch        *b_CCQENu_minos_trk_end_y;   //!
   TBranch        *b_CCQENu_minos_trk_end_z;   //!
   TBranch        *b_CCQENu_minos_trk_eqp;   //!
   TBranch        *b_CCQENu_minos_trk_eqp_qp;   //!
   TBranch        *b_CCQENu_minos_trk_fit_pass;   //!
   TBranch        *b_CCQENu_minos_trk_ndf;   //!
   TBranch        *b_CCQENu_minos_trk_p;   //!
   TBranch        *b_CCQENu_minos_trk_p_curvature;   //!
   TBranch        *b_CCQENu_minos_trk_p_range;   //!
   TBranch        *b_CCQENu_minos_trk_qp;   //!
   TBranch        *b_CCQENu_minos_trk_vtx_x;   //!
   TBranch        *b_CCQENu_minos_trk_vtx_y;   //!
   TBranch        *b_CCQENu_minos_trk_vtx_z;   //!
   TBranch        *b_CCQENu_muon_E;   //!
   TBranch        *b_CCQENu_muon_P;   //!
   TBranch        *b_CCQENu_muon_T;   //!
   TBranch        *b_CCQENu_muon_score;   //!
   TBranch        *b_CCQENu_muon_theta;   //!
   //TBranch        *b_CCQENu_recoil_calE;   //!
   TBranch        *b_CCQENu_pion_score;   //!
   TBranch        *b_CCQENu_pion_score1;   //!
   TBranch        *b_CCQENu_pion_score2;   //!
   TBranch        *b_CCQENu_proton_E_BetheBloch_biasDown;   //!
   TBranch        *b_CCQENu_proton_E_BetheBloch_biasUp;   //!
   TBranch        *b_CCQENu_proton_E_Birks_bias;   //!
   TBranch        *b_CCQENu_proton_E_MEU_biasDown;   //!
   TBranch        *b_CCQENu_proton_E_MEU_biasUp;   //!
   TBranch        *b_CCQENu_proton_E_Mass_biasDown;   //!
   TBranch        *b_CCQENu_proton_E_Mass_biasUp;   //!
   TBranch        *b_CCQENu_proton_E_fromdEdx;   //!
   TBranch        *b_CCQENu_proton_P_fromdEdx;   //!
   TBranch        *b_CCQENu_proton_T_fromdEdx;   //!
   TBranch        *b_CCQENu_proton_calib_energy;   //!
   TBranch        *b_CCQENu_proton_score;   //!
   TBranch        *b_CCQENu_proton_score1;   //!
   TBranch        *b_CCQENu_proton_score1_BetheBloch_biasDown;   //!
   TBranch        *b_CCQENu_proton_score1_BetheBloch_biasUp;   //!
   TBranch        *b_CCQENu_proton_score1_Birks_bias;   //!
   TBranch        *b_CCQENu_proton_score1_MEU_biasDown;   //!
   TBranch        *b_CCQENu_proton_score1_MEU_biasUp;   //!
   TBranch        *b_CCQENu_proton_score1_Mass_biasDown;   //!
   TBranch        *b_CCQENu_proton_score1_Mass_biasUp;   //!
   TBranch        *b_CCQENu_proton_score2;   //!
   TBranch        *b_CCQENu_proton_theta_fromdEdx;   //!
   TBranch        *b_CCQENu_r_minos_trk_bdL;   //!
   TBranch        *b_CCQENu_r_minos_trk_end_dcosx;   //!
   TBranch        *b_CCQENu_r_minos_trk_end_dcosy;   //!
   TBranch        *b_CCQENu_r_minos_trk_end_dcosz;   //!
   TBranch        *b_CCQENu_r_minos_trk_vtx_dcosx;   //!
   TBranch        *b_CCQENu_r_minos_trk_vtx_dcosy;   //!
   TBranch        *b_CCQENu_r_minos_trk_vtx_dcosz;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLepMinosInitProjPx;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLepMinosInitProjPy;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLepMinosInitProjPz;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLepMinosInitProjX;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLepMinosInitProjY;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLepMinosInitProjZ;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLepMnvFinalPx;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLepMnvFinalPy;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLepMnvFinalPz;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLepMnvFinalX;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLepMnvFinalY;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLepMnvFinalZ;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLepMnvInitPx;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLepMnvInitPy;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLepMnvInitPz;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLepMnvInitX;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLepMnvInitY;   //!
   TBranch        *b_CCQENu_t_minos_trk_primFSLepMnvInitZ;   //!
   TBranch        *b_CCQENu_sec_protons_E_BetheBloch_biasDown_sz;   //!
   TBranch        *b_CCQENu_sec_protons_E_BetheBloch_biasDown;   //!
   TBranch        *b_CCQENu_sec_protons_E_BetheBloch_biasUp_sz;   //!
   TBranch        *b_CCQENu_sec_protons_E_BetheBloch_biasUp;   //!
   TBranch        *b_CCQENu_sec_protons_E_Birks_bias_sz;   //!
   TBranch        *b_CCQENu_sec_protons_E_Birks_bias;   //!
   TBranch        *b_CCQENu_sec_protons_E_MEU_biasDown_sz;   //!
   TBranch        *b_CCQENu_sec_protons_E_MEU_biasDown;   //!
   TBranch        *b_CCQENu_sec_protons_E_MEU_biasUp_sz;   //!
   TBranch        *b_CCQENu_sec_protons_E_MEU_biasUp;   //!
   TBranch        *b_CCQENu_sec_protons_E_Mass_biasDown_sz;   //!
   TBranch        *b_CCQENu_sec_protons_E_Mass_biasDown;   //!
   TBranch        *b_CCQENu_sec_protons_E_Mass_biasUp_sz;   //!
   TBranch        *b_CCQENu_sec_protons_E_Mass_biasUp;   //!
   TBranch        *b_CCQENu_sec_protons_E_fromdEdx_sz;   //!
   TBranch        *b_CCQENu_sec_protons_E_fromdEdx;   //!
   TBranch        *b_CCQENu_sec_protons_P_fromdEdx_sz;   //!
   TBranch        *b_CCQENu_sec_protons_P_fromdEdx;   //!
   TBranch        *b_CCQENu_sec_protons_T_fromCalo_sz;   //!
   TBranch        *b_CCQENu_sec_protons_T_fromCalo;   //!
   TBranch        *b_CCQENu_sec_protons_T_fromdEdx_sz;   //!
   TBranch        *b_CCQENu_sec_protons_T_fromdEdx;   //!
   TBranch        *b_CCQENu_sec_protons_pion_scores_sz;   //!
   TBranch        *b_CCQENu_sec_protons_pion_scores;   //!
   TBranch        *b_CCQENu_sec_protons_pion_scores1_sz;   //!
   TBranch        *b_CCQENu_sec_protons_pion_scores1;   //!
   TBranch        *b_CCQENu_sec_protons_pion_scores2_sz;   //!
   TBranch        *b_CCQENu_sec_protons_pion_scores2;   //!
   TBranch        *b_CCQENu_sec_protons_proton_scores_sz;   //!
   TBranch        *b_CCQENu_sec_protons_proton_scores;   //!
   TBranch        *b_CCQENu_sec_protons_proton_scores1_sz;   //!
   TBranch        *b_CCQENu_sec_protons_proton_scores1;   //!
   TBranch        *b_CCQENu_sec_protons_proton_scores2_sz;   //!
   TBranch        *b_CCQENu_sec_protons_proton_scores2;   //!
   TBranch        *b_CCQENu_sec_protons_score1_BetheBloch_biasDown_sz;   //!
   TBranch        *b_CCQENu_sec_protons_score1_BetheBloch_biasDown;   //!
   TBranch        *b_CCQENu_sec_protons_score1_BetheBloch_biasUp_sz;   //!
   TBranch        *b_CCQENu_sec_protons_score1_BetheBloch_biasUp;   //!
   TBranch        *b_CCQENu_sec_protons_score1_Birks_bias_sz;   //!
   TBranch        *b_CCQENu_sec_protons_score1_Birks_bias;   //!
   TBranch        *b_CCQENu_sec_protons_score1_MEU_biasDown_sz;   //!
   TBranch        *b_CCQENu_sec_protons_score1_MEU_biasDown;   //!
   TBranch        *b_CCQENu_sec_protons_score1_MEU_biasUp_sz;   //!
   TBranch        *b_CCQENu_sec_protons_score1_MEU_biasUp;   //!
   TBranch        *b_CCQENu_sec_protons_score1_Mass_biasDown_sz;   //!
   TBranch        *b_CCQENu_sec_protons_score1_Mass_biasDown;   //!
   TBranch        *b_CCQENu_sec_protons_score1_Mass_biasUp_sz;   //!
   TBranch        *b_CCQENu_sec_protons_score1_Mass_biasUp;   //!
   TBranch        *b_CCQENu_sec_protons_theta_fromdEdx_sz;   //!
   TBranch        *b_CCQENu_sec_protons_theta_fromdEdx;   //!
   TBranch        *b_CCQENu_sys_muon_curve_energy_shift;   //!
   TBranch        *b_CCQENu_sys_muon_energy_shift;   //!
   TBranch        *b_CCQENu_sys_muon_minerva_energy_shift;   //!
   TBranch        *b_CCQENu_sys_muon_qSquared_shift;   //!
   TBranch        *b_CCQENu_sys_muon_range_energy_shift;   //!
   TBranch        *b_CCQENu_sys_muon_wSquared_shift;   //!
   TBranch        *b_CCQENu_sys_muon_xbj_shift;   //!
   TBranch        *b_CCQENu_sys_muon_y_shift;   //!
   TBranch        *b_CCQENu_sys_nu_energy_shift;   //!
   TBranch        *b_CCQENu_sys_recoil_energy_shift;   //!
   TBranch        *b_CCQENu_sys_recoil_qSquared_shift;   //!
   TBranch        *b_CCQENu_sys_recoil_wSquared_shift;   //!
   TBranch        *b_CCQENu_sys_recoil_xbj_shift;   //!
   TBranch        *b_CCQENu_sys_recoil_y_shift;   //!
   TBranch        *b_CCQENu_sys_total_qSquared_shift;   //!
   TBranch        *b_CCQENu_sys_total_wSquared_shift;   //!
   TBranch        *b_CCQENu_sys_total_xbj_shift;   //!
   TBranch        *b_CCQENu_sys_total_y_shift;   //!
   TBranch        *b_ev_run;   //!
   TBranch        *b_ev_subrun;   //!
   TBranch        *b_ev_detector;   //!
   TBranch        *b_ev_triggerType;   //!
   TBranch        *b_ev_gate;   //!
   TBranch        *b_ev_global_gate;   //!
   TBranch        *b_ev_gps_time_sec;   //!
   TBranch        *b_ev_gps_time_usec;   //!
   TBranch        *b_mc_run;   //!
   TBranch        *b_mc_subrun;   //!
   TBranch        *b_mc_nInteractions;   //!
   TBranch        *b_mc_MIState;   //!
   TBranch        *b_mc_pot;   //!
   TBranch        *b_mc_beamConfig;   //!
   TBranch        *b_mc_processType;   //!
   TBranch        *b_mc_nthEvtInSpill;   //!
   TBranch        *b_mc_nthEvtInFile;   //!
   TBranch        *b_mc_intType;   //!
   TBranch        *b_mc_current;   //!
   TBranch        *b_mc_charm;   //!
   TBranch        *b_mc_weight;   //!
   TBranch        *b_mc_XSec;   //!
   TBranch        *b_mc_diffXSec;   //!
   TBranch        *b_mc_incoming;   //!
   TBranch        *b_mc_fluxDriverProb;   //!
   TBranch        *b_mc_targetNucleus;   //!
   TBranch        *b_mc_targetZ;   //!
   TBranch        *b_mc_targetA;   //!
   TBranch        *b_mc_targetNucleon;   //!
   TBranch        *b_mc_struckQuark;   //!
   TBranch        *b_mc_seaQuark;   //!
   TBranch        *b_mc_resID;   //!
   TBranch        *b_mc_primaryLepton;   //!
   TBranch        *b_mc_incomingE;   //!
   TBranch        *b_mc_Bjorkenx;   //!
   TBranch        *b_mc_Bjorkeny;   //!
   TBranch        *b_mc_Q2;   //!
   TBranch        *b_mc_nuT;   //!
   TBranch        *b_mc_w;   //!
   TBranch        *b_mc_vtx;   //!
   TBranch        *b_mc_incomingPartVec;   //!
   TBranch        *b_mc_initNucVec;   //!
   TBranch        *b_mc_primFSLepton;   //!
   TBranch        *b_mc_nFSPart;   //!
   TBranch        *b_mc_FSPartPx;   //!
   TBranch        *b_mc_FSPartPy;   //!
   TBranch        *b_mc_FSPartPz;   //!
   TBranch        *b_mc_FSPartE;   //!
   TBranch        *b_mc_FSPartPDG;   //!
   TBranch        *b_mc_er_nPart;   //!
   TBranch        *b_mc_er_ID;   //!
   TBranch        *b_mc_er_status;   //!
   TBranch        *b_mc_er_posInNucX;   //!
   TBranch        *b_mc_er_posInNucY;   //!
   TBranch        *b_mc_er_posInNucZ;   //!
   TBranch        *b_mc_er_Px;   //!
   TBranch        *b_mc_er_Py;   //!
   TBranch        *b_mc_er_Pz;   //!
   TBranch        *b_mc_er_E;   //!
   TBranch        *b_mc_er_FD;   //!
   TBranch        *b_mc_er_LD;   //!
   TBranch        *b_mc_er_mother;   //!
   TBranch        *b_mc_fr_nNuAncestorIDs;   //!
   TBranch        *b_mc_fr_nuAncestorIDs;   //!
   TBranch        *b_mc_fr_nuParentID;   //!
   TBranch        *b_mc_fr_decMode;   //!
   TBranch        *b_mc_fr_primProtonVtx;   //!
   TBranch        *b_mc_fr_primProtonP;   //!
   TBranch        *b_mc_fr_nuParentDecVtx;   //!
   TBranch        *b_mc_fr_nuParentProdVtx;   //!
   TBranch        *b_mc_fr_nuParentProdP;   //!
   TBranch        *b_mc_cvweight_total;   //!
   TBranch        *b_wgt;   //!
   TBranch        *b_mc_cvweight_totalFlux;   //!
   TBranch        *b_mc_cvweight_totalXsec;   //!
   TBranch        *b_mc_ppfx1_cvweight;   //!
   TBranch        *b_mc_hornCurrent_cvweight;   //!
   TBranch        *b_mc_gen1_cvweight_total;   //!
   TBranch        *b_gen1_wgt;   //!
   TBranch        *b_mc_gen1_cvweight_totalFlux;   //!
   TBranch        *b_mc_gen1_cvweight_NA49;   //!
   TBranch        *b_mc_wgt_Flux_BeamFocus_sz;   //!
   TBranch        *b_mc_wgt_Flux_BeamFocus;   //!
   TBranch        *b_mc_wgt_gen1_Flux_Tertiary_sz;   //!
   TBranch        *b_mc_wgt_gen1_Flux_Tertiary;   //!
   TBranch        *b_mc_wgt_gen1_Flux_NA49_sz;   //!
   TBranch        *b_mc_wgt_gen1_Flux_NA49;   //!
   TBranch        *b_mc_wgt_Norm_sz;   //!
   TBranch        *b_mc_wgt_Norm;   //!
   TBranch        *b_mc_wgt_ppfx1_Total_sz;   //!
   TBranch        *b_mc_wgt_ppfx1_Total;   //!
   TBranch        *b_n_prongs;   //!
   TBranch        *b_prong_nParticles;   //!
   TBranch        *b_prong_part_score;   //!
   TBranch        *b_prong_part_mass;   //!
   TBranch        *b_prong_part_charge;   //!
   TBranch        *b_prong_part_pid;   //!
   //   TBranch        *b_prong_part_E;   //!
   //   TBranch        *b_prong_part_pos;   //!
   TBranch        *b_batch_structure;
   TBranch        *b_reco_vertex_batch;

   CCQENuEvent(TTree *tree=0, bool IsData=false);
   virtual ~CCQENuEvent();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual const char* GetCurrentFileName() const;
   virtual Long64_t    GetCurrentEntryNumber(Long64_t entry) const;
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree, bool IsData=false);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};
}

#endif

#ifdef CCQENuEvent_cxx
CCQENU_ANA::CCQENuEvent::CCQENuEvent(TTree *tree, bool IsData) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("CCQENu",tree);
   }
   Init(tree, IsData);
}
CCQENU_ANA::CCQENuEvent::~CCQENuEvent()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

const char* CCQENU_ANA::CCQENuEvent::GetCurrentFileName() const
{
  if (!fChain) return "";
  else return ((TChain*)(fChain))->GetFile()->GetName();

}

Long64_t CCQENU_ANA::CCQENuEvent::GetCurrentEntryNumber(Long64_t entry) const
{
  if (!fChain) return -1;
  else return ((TChain*)(fChain))->GetReadEntry();
}

Int_t CCQENU_ANA::CCQENuEvent::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

Long64_t CCQENU_ANA::CCQENuEvent::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void CCQENU_ANA::CCQENuEvent::Init(TTree *tree, bool IsData)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
  //   prong_part_E = 0;
  //   prong_part_pos = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("eventID", &eventID, &b_eventID);
   fChain->SetBranchAddress("physEvtNum", &physEvtNum, &b_physEvtNum);
   fChain->SetBranchAddress("n_hyps", &n_hyps, &b_n_hyps);
   fChain->SetBranchAddress("processType", &processType, &b_processType);
   fChain->SetBranchAddress("primaryPart", &primaryPart, &b_primaryPart);
   fChain->SetBranchAddress("n_slices", &n_slices, &b_n_slices);
   fChain->SetBranchAddress("slice_numbers", slice_numbers, &b_slice_numbers);
   fChain->SetBranchAddress("shared_slice", &shared_slice, &b_shared_slice);
   fChain->SetBranchAddress("vtx", vtx, &b_vtx);
   fChain->SetBranchAddress("vtxErr", vtxErr, &b_vtxErr);
   fChain->SetBranchAddress("E", E, &b_E);
   fChain->SetBranchAddress("found_truth", &found_truth, &b_found_truth);
   fChain->SetBranchAddress("phys_front_activity", &phys_front_activity, &b_phys_front_activity);
   fChain->SetBranchAddress("phys_energy_in_road_upstream_is_rockmuon_consistent", &phys_energy_in_road_upstream_is_rockmuon_consistent, &b_phys_energy_in_road_upstream_is_rockmuon_consistent);
   fChain->SetBranchAddress("rock_muons_removed", &rock_muons_removed, &b_rock_muons_removed);
   fChain->SetBranchAddress("minos_track_match", &minos_track_match, &b_minos_track_match);
   fChain->SetBranchAddress("minos_stub_match", &minos_stub_match, &b_minos_stub_match);
   fChain->SetBranchAddress("unknown_helicity", &unknown_helicity, &b_unknown_helicity);
   fChain->SetBranchAddress("minos_track_inside_partial_plane", &minos_track_inside_partial_plane, &b_minos_track_inside_partial_plane);
   fChain->SetBranchAddress("prim_vtx_has_misassigned_track_direction", &prim_vtx_has_misassigned_track_direction, &b_prim_vtx_has_misassigned_track_direction);
   fChain->SetBranchAddress("prim_vtx_has_broken_track", &prim_vtx_has_broken_track, &b_prim_vtx_has_broken_track);
   fChain->SetBranchAddress("broken_track_most_us_plane", &broken_track_most_us_plane, &b_broken_track_most_us_plane);
   fChain->SetBranchAddress("event_unused_start_vertices", &event_unused_start_vertices, &b_event_unused_start_vertices);
   fChain->SetBranchAddress("event_used_start_vertices", &event_used_start_vertices, &b_event_used_start_vertices);
   fChain->SetBranchAddress("has_interaction_vertex", &has_interaction_vertex, &b_has_interaction_vertex);
   fChain->SetBranchAddress("has_single_proton", &has_single_proton, &b_has_single_proton);
   fChain->SetBranchAddress("improved_nmichel", &improved_nmichel, &b_improved_nmichel);
   fChain->SetBranchAddress("multiplicity", &multiplicity, &b_multiplicity);
   fChain->SetBranchAddress("muon_fuzz_energy", &muon_fuzz_energy, &b_muon_fuzz_energy);
   fChain->SetBranchAddress("muon_is_minos_match_stub", &muon_is_minos_match_stub, &b_muon_is_minos_match_stub);
   fChain->SetBranchAddress("muon_is_minos_match_track", &muon_is_minos_match_track, &b_muon_is_minos_match_track);
   fChain->SetBranchAddress("n_anchored_long_trk_prongs", &n_anchored_long_trk_prongs, &b_n_anchored_long_trk_prongs);
   fChain->SetBranchAddress("n_anchored_short_trk_prongs", &n_anchored_short_trk_prongs, &b_n_anchored_short_trk_prongs);
   fChain->SetBranchAddress("n_iso_trk_prongs", &n_iso_trk_prongs, &b_n_iso_trk_prongs);
   fChain->SetBranchAddress("n_minos_matches", &n_minos_matches, &b_n_minos_matches);
   fChain->SetBranchAddress("n_muon_iso_blobs", &n_muon_iso_blobs, &b_n_muon_iso_blobs);
   fChain->SetBranchAddress("n_nonvtx_iso_blobs", &n_nonvtx_iso_blobs, &b_n_nonvtx_iso_blobs);
   fChain->SetBranchAddress("n_nonvtx_iso_blobs_all", &n_nonvtx_iso_blobs_all, &b_n_nonvtx_iso_blobs_all);
   fChain->SetBranchAddress("part_response_recoil_nClus", &part_response_recoil_nClus, &b_part_response_recoil_nClus);
   fChain->SetBranchAddress("pass_CCQENu_precuts", &pass_CCQENu_precuts, &b_pass_CCQENu_precuts);
   fChain->SetBranchAddress("phys_energy_in_road_downstream_nplanes", &phys_energy_in_road_downstream_nplanes, &b_phys_energy_in_road_downstream_nplanes);
   fChain->SetBranchAddress("phys_energy_in_road_upstream_nplanes", &phys_energy_in_road_upstream_nplanes, &b_phys_energy_in_road_upstream_nplanes);
   fChain->SetBranchAddress("phys_n_dead_discr_pair", &phys_n_dead_discr_pair, &b_phys_n_dead_discr_pair);
   fChain->SetBranchAddress("phys_n_dead_discr_pair_in_prim_track_region", &phys_n_dead_discr_pair_in_prim_track_region, &b_phys_n_dead_discr_pair_in_prim_track_region);
   fChain->SetBranchAddress("phys_n_dead_discr_pair_two_mod_downstream_prim_track", &phys_n_dead_discr_pair_two_mod_downstream_prim_track, &b_phys_n_dead_discr_pair_two_mod_downstream_prim_track);
   fChain->SetBranchAddress("phys_n_dead_discr_pair_two_mod_upstream_prim_vtx", &phys_n_dead_discr_pair_two_mod_upstream_prim_vtx, &b_phys_n_dead_discr_pair_two_mod_upstream_prim_vtx);
   fChain->SetBranchAddress("phys_n_dead_discr_pair_upstream_prim_track_proj", &phys_n_dead_discr_pair_upstream_prim_track_proj, &b_phys_n_dead_discr_pair_upstream_prim_track_proj);
   fChain->SetBranchAddress("phys_vertex_is_fiducial", &phys_vertex_is_fiducial, &b_phys_vertex_is_fiducial);
   fChain->SetBranchAddress("proton_prong_PDG", &proton_prong_PDG, &b_proton_prong_PDG);
   fChain->SetBranchAddress("proton_prong_traj_ID", &proton_prong_traj_ID, &b_proton_prong_traj_ID);
   fChain->SetBranchAddress("slice_n_hits", &slice_n_hits, &b_slice_n_hits);

   fChain->SetBranchAddress("dis_id_energy", &dis_id_energy, &b_dis_id_energy);
   fChain->SetBranchAddress("energy_from_mc", &energy_from_mc, &b_energy_from_mc);
   fChain->SetBranchAddress("energy_from_mc_fraction", &energy_from_mc_fraction, &b_energy_from_mc_fraction);
   fChain->SetBranchAddress("energy_from_mc_fraction_of_highest", &energy_from_mc_fraction_of_highest, &b_energy_from_mc_fraction_of_highest);
   fChain->SetBranchAddress("muon_iso_blobs_energy", &muon_iso_blobs_energy, &b_muon_iso_blobs_energy);
   fChain->SetBranchAddress("muon_minerva_trk_chi2PerDoF", &muon_minerva_trk_chi2PerDoF, &b_muon_minerva_trk_chi2PerDoF);
   fChain->SetBranchAddress("muon_phi", &muon_phi, &b_muon_phi);
   fChain->SetBranchAddress("muon_theta", &muon_theta, &b_muon_theta);
   fChain->SetBranchAddress("muon_thetaX", &muon_thetaX, &b_muon_thetaX);
   fChain->SetBranchAddress("muon_thetaY", &muon_thetaY, &b_muon_thetaY);
   fChain->SetBranchAddress("nonvtx_iso_blobs_energy", &nonvtx_iso_blobs_energy, &b_nonvtx_iso_blobs_energy);
   fChain->SetBranchAddress("nonvtx_iso_blobs_energy_all", &nonvtx_iso_blobs_energy_all, &b_nonvtx_iso_blobs_energy_all);
   fChain->SetBranchAddress("numi_horn_curr", &numi_horn_curr, &b_numi_horn_curr);
   fChain->SetBranchAddress("numi_pot", &numi_pot, &b_numi_pot);
   fChain->SetBranchAddress("numi_x", &numi_x, &b_numi_x);
   fChain->SetBranchAddress("numi_x_width", &numi_x_width, &b_numi_x_width);
   fChain->SetBranchAddress("numi_y", &numi_y, &b_numi_y);
   fChain->SetBranchAddress("numi_y_width", &numi_y_width, &b_numi_y_width);
   fChain->SetBranchAddress("part_response_recoil_em_id", &part_response_recoil_em_id, &b_part_response_recoil_em_id);
   fChain->SetBranchAddress("part_response_recoil_em_id_err", &part_response_recoil_em_id_err, &b_part_response_recoil_em_id_err);
   fChain->SetBranchAddress("part_response_recoil_em_od", &part_response_recoil_em_od, &b_part_response_recoil_em_od);
   fChain->SetBranchAddress("part_response_recoil_em_od_err", &part_response_recoil_em_od_err, &b_part_response_recoil_em_od_err);
   fChain->SetBranchAddress("part_response_recoil_high_neutron_id", &part_response_recoil_high_neutron_id, &b_part_response_recoil_high_neutron_id);
   fChain->SetBranchAddress("part_response_recoil_high_neutron_id_err", &part_response_recoil_high_neutron_id_err, &b_part_response_recoil_high_neutron_id_err);
   fChain->SetBranchAddress("part_response_recoil_high_neutron_od", &part_response_recoil_high_neutron_od, &b_part_response_recoil_high_neutron_od);
   fChain->SetBranchAddress("part_response_recoil_high_neutron_od_err", &part_response_recoil_high_neutron_od_err, &b_part_response_recoil_high_neutron_od_err);
   fChain->SetBranchAddress("part_response_recoil_low_neutron_id", &part_response_recoil_low_neutron_id, &b_part_response_recoil_low_neutron_id);
   fChain->SetBranchAddress("part_response_recoil_low_neutron_id_err", &part_response_recoil_low_neutron_id_err, &b_part_response_recoil_low_neutron_id_err);
   fChain->SetBranchAddress("part_response_recoil_low_neutron_od", &part_response_recoil_low_neutron_od, &b_part_response_recoil_low_neutron_od);
   fChain->SetBranchAddress("part_response_recoil_low_neutron_od_err", &part_response_recoil_low_neutron_od_err, &b_part_response_recoil_low_neutron_od_err);
   fChain->SetBranchAddress("part_response_recoil_meson_id", &part_response_recoil_meson_id, &b_part_response_recoil_meson_id);
   fChain->SetBranchAddress("part_response_recoil_meson_id_err", &part_response_recoil_meson_id_err, &b_part_response_recoil_meson_id_err);
   fChain->SetBranchAddress("part_response_recoil_meson_od", &part_response_recoil_meson_od, &b_part_response_recoil_meson_od);
   fChain->SetBranchAddress("part_response_recoil_meson_od_err", &part_response_recoil_meson_od_err, &b_part_response_recoil_meson_od_err);
   fChain->SetBranchAddress("part_response_recoil_mid_neutron_id", &part_response_recoil_mid_neutron_id, &b_part_response_recoil_mid_neutron_id);
   fChain->SetBranchAddress("part_response_recoil_mid_neutron_id_err", &part_response_recoil_mid_neutron_id_err, &b_part_response_recoil_mid_neutron_id_err);
   fChain->SetBranchAddress("part_response_recoil_mid_neutron_od", &part_response_recoil_mid_neutron_od, &b_part_response_recoil_mid_neutron_od);
   fChain->SetBranchAddress("part_response_recoil_mid_neutron_od_err", &part_response_recoil_mid_neutron_od_err, &b_part_response_recoil_mid_neutron_od_err);
   fChain->SetBranchAddress("part_response_recoil_muon_id", &part_response_recoil_muon_id, &b_part_response_recoil_muon_id);
   fChain->SetBranchAddress("part_response_recoil_muon_id_err", &part_response_recoil_muon_id_err, &b_part_response_recoil_muon_id_err);
   fChain->SetBranchAddress("part_response_recoil_muon_od", &part_response_recoil_muon_od, &b_part_response_recoil_muon_od);
   fChain->SetBranchAddress("part_response_recoil_muon_od_err", &part_response_recoil_muon_od_err, &b_part_response_recoil_muon_od_err);
   fChain->SetBranchAddress("part_response_recoil_other_id", &part_response_recoil_other_id, &b_part_response_recoil_other_id);
   fChain->SetBranchAddress("part_response_recoil_other_id_err", &part_response_recoil_other_id_err, &b_part_response_recoil_other_id_err);
   fChain->SetBranchAddress("part_response_recoil_other_od", &part_response_recoil_other_od, &b_part_response_recoil_other_od);
   fChain->SetBranchAddress("part_response_recoil_other_od_err", &part_response_recoil_other_od_err, &b_part_response_recoil_other_od_err);
   fChain->SetBranchAddress("part_response_recoil_proton_id", &part_response_recoil_proton_id, &b_part_response_recoil_proton_id);
   fChain->SetBranchAddress("part_response_recoil_proton_id_err", &part_response_recoil_proton_id_err, &b_part_response_recoil_proton_id_err);
   fChain->SetBranchAddress("part_response_recoil_proton_od", &part_response_recoil_proton_od, &b_part_response_recoil_proton_od);
   fChain->SetBranchAddress("part_response_recoil_proton_od_err", &part_response_recoil_proton_od_err, &b_part_response_recoil_proton_od_err);
   fChain->SetBranchAddress("part_response_recoil_xtalk_id", &part_response_recoil_xtalk_id, &b_part_response_recoil_xtalk_id);
   fChain->SetBranchAddress("part_response_recoil_xtalk_id_err", &part_response_recoil_xtalk_id_err, &b_part_response_recoil_xtalk_id_err);
   fChain->SetBranchAddress("part_response_recoil_xtalk_od", &part_response_recoil_xtalk_od, &b_part_response_recoil_xtalk_od);
   fChain->SetBranchAddress("part_response_recoil_xtalk_od_err", &part_response_recoil_xtalk_od_err, &b_part_response_recoil_xtalk_od_err);
   fChain->SetBranchAddress("phys_energy_dispersed", &phys_energy_dispersed, &b_phys_energy_dispersed);
   fChain->SetBranchAddress("phys_energy_in_road_downstream", &phys_energy_in_road_downstream, &b_phys_energy_in_road_downstream);
   fChain->SetBranchAddress("phys_energy_in_road_upstream", &phys_energy_in_road_upstream, &b_phys_energy_in_road_upstream);
   fChain->SetBranchAddress("phys_energy_unattached", &phys_energy_unattached, &b_phys_energy_unattached);
   fChain->SetBranchAddress("prim_vtx_smallest_opening_angle", &prim_vtx_smallest_opening_angle, &b_prim_vtx_smallest_opening_angle);
   fChain->SetBranchAddress("proton_track_length", &proton_track_length, &b_proton_track_length);
   //-------------------------------------------------------
   fChain->SetBranchAddress("proton_track_endx", &proton_track_endx, &b_proton_track_endx);
   fChain->SetBranchAddress("proton_track_endy", &proton_track_endy, &b_proton_track_endy);
   fChain->SetBranchAddress("proton_track_endz", &proton_track_endz, &b_proton_track_endz);
   fChain->SetBranchAddress("CCQENu_proton_endPointX", &CCQENu_proton_endPointX, &b_CCQENu_proton_endPointX);
   fChain->SetBranchAddress("CCQENu_proton_endPointY", &CCQENu_proton_endPointY, &b_CCQENu_proton_endPointY);
   fChain->SetBranchAddress("CCQENu_proton_endPointZ", &CCQENu_proton_endPointZ, &b_CCQENu_proton_endPointZ);
   fChain->SetBranchAddress("CCQENu_proton_startPointX", &CCQENu_proton_startPointX, &b_CCQENu_proton_startPointX);
   fChain->SetBranchAddress("CCQENu_proton_startPointY", &CCQENu_proton_startPointY, &b_CCQENu_proton_startPointY);
   fChain->SetBranchAddress("CCQENu_proton_startPointZ", &CCQENu_proton_startPointZ, &b_CCQENu_proton_startPointZ);
   fChain->SetBranchAddress("CCQENu_proton_theta", &CCQENu_proton_theta, &b_CCQENu_proton_theta);
   fChain->SetBranchAddress("CCQENu_proton_thetaX", &CCQENu_proton_thetaX, &b_CCQENu_proton_thetaX);
   fChain->SetBranchAddress("CCQENu_proton_thetaY", &CCQENu_proton_thetaY, &b_CCQENu_proton_thetaY);
   fChain->SetBranchAddress("CCQENu_proton_phi", &CCQENu_proton_phi, &b_CCQENu_proton_phi);
   fChain->SetBranchAddress("CCQENu_proton_ekin", &CCQENu_proton_ekin, &b_CCQENu_proton_ekin);
   fChain->SetBranchAddress("CCQENu_proton_enu", &CCQENu_proton_enu, &b_CCQENu_proton_enu);
   fChain->SetBranchAddress("CCQENu_proton_q2", &CCQENu_proton_q2, &b_CCQENu_proton_q2);
   fChain->SetBranchAddress("CCQENu_proton_p", &CCQENu_proton_p, &b_CCQENu_proton_p);
   fChain->SetBranchAddress("CCQENu_proton_px", &CCQENu_proton_px, &b_CCQENu_proton_px);
   fChain->SetBranchAddress("CCQENu_proton_py", &CCQENu_proton_py, &b_CCQENu_proton_py);
   fChain->SetBranchAddress("CCQENu_proton_pz", &CCQENu_proton_pz, &b_CCQENu_proton_pz);
   fChain->SetBranchAddress("CCQENu_proton_E", &CCQENu_proton_E, &b_CCQENu_proton_E);
   //-------------------------------------------------------
   fChain->SetBranchAddress("recoil_energy_nonmuon_nonvtx0mm", &recoil_energy_nonmuon_nonvtx0mm, &b_recoil_energy_nonmuon_nonvtx0mm);
   fChain->SetBranchAddress("recoil_energy_nonmuon_nonvtx100mm", &recoil_energy_nonmuon_nonvtx100mm, &b_recoil_energy_nonmuon_nonvtx100mm);
   fChain->SetBranchAddress("recoil_energy_nonmuon_nonvtx150mm", &recoil_energy_nonmuon_nonvtx150mm, &b_recoil_energy_nonmuon_nonvtx150mm);
   fChain->SetBranchAddress("recoil_energy_nonmuon_nonvtx200mm", &recoil_energy_nonmuon_nonvtx200mm, &b_recoil_energy_nonmuon_nonvtx200mm);
   fChain->SetBranchAddress("recoil_energy_nonmuon_nonvtx250mm", &recoil_energy_nonmuon_nonvtx250mm, &b_recoil_energy_nonmuon_nonvtx250mm);
   fChain->SetBranchAddress("recoil_energy_nonmuon_nonvtx300mm", &recoil_energy_nonmuon_nonvtx300mm, &b_recoil_energy_nonmuon_nonvtx300mm);
   fChain->SetBranchAddress("recoil_energy_nonmuon_nonvtx50mm", &recoil_energy_nonmuon_nonvtx50mm, &b_recoil_energy_nonmuon_nonvtx50mm);
   fChain->SetBranchAddress("recoil_energy_nonmuon_vtx0mm", &recoil_energy_nonmuon_vtx0mm, &b_recoil_energy_nonmuon_vtx0mm);
   fChain->SetBranchAddress("recoil_energy_nonmuon_vtx100mm", &recoil_energy_nonmuon_vtx100mm, &b_recoil_energy_nonmuon_vtx100mm);
   fChain->SetBranchAddress("recoil_energy_nonmuon_vtx150mm", &recoil_energy_nonmuon_vtx150mm, &b_recoil_energy_nonmuon_vtx150mm);
   fChain->SetBranchAddress("recoil_energy_nonmuon_vtx200mm", &recoil_energy_nonmuon_vtx200mm, &b_recoil_energy_nonmuon_vtx200mm);
   fChain->SetBranchAddress("recoil_energy_nonmuon_vtx250mm", &recoil_energy_nonmuon_vtx250mm, &b_recoil_energy_nonmuon_vtx250mm);
   fChain->SetBranchAddress("recoil_energy_nonmuon_vtx300mm", &recoil_energy_nonmuon_vtx300mm, &b_recoil_energy_nonmuon_vtx300mm);
   fChain->SetBranchAddress("recoil_energy_nonmuon_vtx50mm", &recoil_energy_nonmuon_vtx50mm, &b_recoil_energy_nonmuon_vtx50mm);
   fChain->SetBranchAddress("vtx_blobs_energy", &vtx_blobs_energy, &b_vtx_blobs_energy);
   fChain->SetBranchAddress("vtx_iso_blobs_energy_outside_radius", &vtx_iso_blobs_energy_outside_radius, &b_vtx_iso_blobs_energy_outside_radius);
   fChain->SetBranchAddress("all_event_start_vertex_fv_minos_match_sz", &all_event_start_vertex_fv_minos_match_sz, &b_all_event_start_vertex_fv_minos_match_sz);
   fChain->SetBranchAddress("all_event_start_vertex_fv_minos_match", all_event_start_vertex_fv_minos_match, &b_all_event_start_vertex_fv_minos_match);
   fChain->SetBranchAddress("clusters_found_at_end_proton_prong_sz", &clusters_found_at_end_proton_prong_sz, &b_clusters_found_at_end_proton_prong_sz);
   fChain->SetBranchAddress("clusters_found_at_end_proton_prong", clusters_found_at_end_proton_prong, &b_clusters_found_at_end_proton_prong);
   fChain->SetBranchAddress("event_in_time_vertex_types_sz", &event_in_time_vertex_types_sz, &b_event_in_time_vertex_types_sz);
   fChain->SetBranchAddress("event_in_time_vertex_types", event_in_time_vertex_types, &b_event_in_time_vertex_types);
   fChain->SetBranchAddress("event_track_nhits_sz", &event_track_nhits_sz, &b_event_track_nhits_sz);
   fChain->SetBranchAddress("event_track_nhits", event_track_nhits, &b_event_track_nhits);
   fChain->SetBranchAddress("event_vertex_types_sz", &event_vertex_types_sz, &b_event_vertex_types_sz);
   fChain->SetBranchAddress("event_vertex_types", event_vertex_types, &b_event_vertex_types);
   fChain->SetBranchAddress("has_michel_bgmodule_sz", &has_michel_bgmodule_sz, &b_has_michel_bgmodule_sz);
   fChain->SetBranchAddress("has_michel_bgmodule", has_michel_bgmodule, &b_has_michel_bgmodule);
   fChain->SetBranchAddress("has_michel_category_sz", &has_michel_category_sz, &b_has_michel_category_sz);
   fChain->SetBranchAddress("has_michel_category", has_michel_category, &b_has_michel_category);
   fChain->SetBranchAddress("has_michel_edmodule_sz", &has_michel_edmodule_sz, &b_has_michel_edmodule_sz);
   fChain->SetBranchAddress("has_michel_edmodule", has_michel_edmodule, &b_has_michel_edmodule);
   fChain->SetBranchAddress("has_michel_in_vertex_point_sz", &has_michel_in_vertex_point_sz, &b_has_michel_in_vertex_point_sz);
   fChain->SetBranchAddress("has_michel_in_vertex_point", has_michel_in_vertex_point, &b_has_michel_in_vertex_point);
   fChain->SetBranchAddress("has_michel_matched_pdg_sz", &has_michel_matched_pdg_sz, &b_has_michel_matched_pdg_sz);
   fChain->SetBranchAddress("has_michel_matched_pdg", has_michel_matched_pdg, &b_has_michel_matched_pdg);
   fChain->SetBranchAddress("has_michel_matched_primary_pdg_sz", &has_michel_matched_primary_pdg_sz, &b_has_michel_matched_primary_pdg_sz);
   fChain->SetBranchAddress("has_michel_matched_primary_pdg", has_michel_matched_primary_pdg, &b_has_michel_matched_primary_pdg);
   fChain->SetBranchAddress("has_michel_ndigits_sz", &has_michel_ndigits_sz, &b_has_michel_ndigits_sz);
   fChain->SetBranchAddress("has_michel_ndigits", has_michel_ndigits, &b_has_michel_ndigits);
   fChain->SetBranchAddress("has_michel_nmodules_sz", &has_michel_nmodules_sz, &b_has_michel_nmodules_sz);
   fChain->SetBranchAddress("has_michel_nmodules", has_michel_nmodules, &b_has_michel_nmodules);
   fChain->SetBranchAddress("has_michel_nplanes_sz", &has_michel_nplanes_sz, &b_has_michel_nplanes_sz);
   fChain->SetBranchAddress("has_michel_nplanes", has_michel_nplanes, &b_has_michel_nplanes);
   fChain->SetBranchAddress("has_michel_ntracks_sz", &has_michel_ntracks_sz, &b_has_michel_ntracks_sz);
   fChain->SetBranchAddress("has_michel_ntracks", has_michel_ntracks, &b_has_michel_ntracks);
   fChain->SetBranchAddress("has_michel_slice_number_sz", &has_michel_slice_number_sz, &b_has_michel_slice_number_sz);
   fChain->SetBranchAddress("has_michel_slice_number", &has_michel_slice_number, &b_has_michel_slice_number);
   fChain->SetBranchAddress("has_michel_vertex_type_sz", &has_michel_vertex_type_sz, &b_has_michel_vertex_type_sz);
   fChain->SetBranchAddress("has_michel_vertex_type", has_michel_vertex_type, &b_has_michel_vertex_type);
   fChain->SetBranchAddress("has_michel_view_sum_sz", &has_michel_view_sum_sz, &b_has_michel_view_sum_sz);
   fChain->SetBranchAddress("has_michel_view_sum", has_michel_view_sum, &b_has_michel_view_sum);
   fChain->SetBranchAddress("improved_michel_in_vertex_point_sz", &improved_michel_in_vertex_point_sz, &b_improved_michel_in_vertex_point_sz);
   fChain->SetBranchAddress("improved_michel_in_vertex_point", improved_michel_in_vertex_point, &b_improved_michel_in_vertex_point);
   fChain->SetBranchAddress("improved_michel_match_vec_sz", &improved_michel_match_vec_sz, &b_improved_michel_match_vec_sz);
   fChain->SetBranchAddress("improved_michel_match_vec", improved_michel_match_vec, &b_improved_michel_match_vec);
   fChain->SetBranchAddress("improved_michel_matched_pdg_sz", &improved_michel_matched_pdg_sz, &b_improved_michel_matched_pdg_sz);
   fChain->SetBranchAddress("improved_michel_matched_pdg", improved_michel_matched_pdg, &b_improved_michel_matched_pdg);
   fChain->SetBranchAddress("improved_michel_matched_primary_pdg_sz", &improved_michel_matched_primary_pdg_sz, &b_improved_michel_matched_primary_pdg_sz);
   fChain->SetBranchAddress("improved_michel_matched_primary_pdg", improved_michel_matched_primary_pdg, &b_improved_michel_matched_primary_pdg);
   fChain->SetBranchAddress("improved_michel_vertex_type_sz", &improved_michel_vertex_type_sz, &b_improved_michel_vertex_type_sz);
   fChain->SetBranchAddress("improved_michel_vertex_type", improved_michel_vertex_type, &b_improved_michel_vertex_type);
   fChain->SetBranchAddress("improved_michel_view_vec_sz", &improved_michel_view_vec_sz, &b_improved_michel_view_vec_sz);
   fChain->SetBranchAddress("improved_michel_view_vec", improved_michel_view_vec, &b_improved_michel_view_vec);

   // ADDING AARON'S TOOLS

   fChain->SetBranchAddress("improved_michel_fitCode_vec", improved_michel_fitCode_vec, &b_improved_michel_fitCode_vec);

   fChain->SetBranchAddress("improved_michel_fitPass_vec", improved_michel_fitPass_vec, &b_improved_michel_fitPass_vec);

   fChain->SetBranchAddress("improved_michel_MatchedEndDist_vec", improved_michel_MatchedEndDist_vec, &b_improved_michel_MatchedEndDist_vec);

   fChain->SetBranchAddress("improved_michel_matchedvtx_energy_vec", improved_michel_matchedvtx_energy_vec, &b_improved_michel_matchedvtx_energy_vec);

   fChain->SetBranchAddress("improved_michel_transdist_vec", improved_michel_transdist_vec, &b_improved_michel_transdist_vec);

   fChain->SetBranchAddress("improved_michel_polarangle_vec", improved_michel_polarangle_vec, &b_improved_michel_polarangle_vec);

   fChain->SetBranchAddress("improved_michel_nplanes", improved_michel_nplanes, &b_improved_michel_nplanes);

   fChain->SetBranchAddress("improved_michel_clussize", improved_michel_clussize, &b_improved_michel_clussize);

   fChain->SetBranchAddress("improved_allmichels", &improved_allmichels, &b_improved_allmichels);


   // True Matched Michel Variables ---------------------

   fChain->SetBranchAddress("has_michel_primary_particle_trackID", &has_michel_primary_particle_trackID, &b_has_michel_primary_particle_trackID);
   fChain->SetBranchAddress("michel_from_decay",&michel_from_decay, &b_michel_from_decay);
   fChain->SetBranchAddress("true_michel_pdg",&true_michel_pdg, &b_true_michel_pdg);
   fChain->SetBranchAddress("true_michel_x1vec", &true_michel_x1vec, &b_true_michel_x1vec);
   fChain->SetBranchAddress("true_michel_y1vec", &true_michel_y1vec, &b_true_michel_y1vec);
   fChain->SetBranchAddress("true_michel_z1vec", &true_michel_z1vec, &b_true_michel_z1vec);
   fChain->SetBranchAddress("true_michel_x2vec", &true_michel_x2vec, &b_true_michel_x2vec);
   fChain->SetBranchAddress("true_michel_y2vec", &true_michel_y2vec, &b_true_michel_y2vec);
   fChain->SetBranchAddress("true_michel_z2vec", &true_michel_z2vec, &b_true_michel_z2vec);
   fChain->SetBranchAddress("michel_parent_PDG", &michel_parent_PDG, &b_michel_parent_PDG);



   fChain->SetBranchAddress("nonvtx_iso_blobs_n_hits_in_prong_sz", &nonvtx_iso_blobs_n_hits_in_prong_sz, &b_nonvtx_iso_blobs_n_hits_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_n_hits_in_prong", nonvtx_iso_blobs_n_hits_in_prong, &b_nonvtx_iso_blobs_n_hits_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_particle_pdg_in_prong_sz", &nonvtx_iso_blobs_particle_pdg_in_prong_sz, &b_nonvtx_iso_blobs_particle_pdg_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_particle_pdg_in_prong", nonvtx_iso_blobs_particle_pdg_in_prong, &b_nonvtx_iso_blobs_particle_pdg_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_primary_particle_pdg_in_prong_sz", &nonvtx_iso_blobs_primary_particle_pdg_in_prong_sz, &b_nonvtx_iso_blobs_primary_particle_pdg_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_primary_particle_pdg_in_prong", nonvtx_iso_blobs_primary_particle_pdg_in_prong, &b_nonvtx_iso_blobs_primary_particle_pdg_in_prong);
   fChain->SetBranchAddress("number_clusters_at_end_proton_prong_sz", &number_clusters_at_end_proton_prong_sz, &b_number_clusters_at_end_proton_prong_sz);
   fChain->SetBranchAddress("number_clusters_at_end_proton_prong", number_clusters_at_end_proton_prong, &b_number_clusters_at_end_proton_prong);
   fChain->SetBranchAddress("recoil_lower_time_limit_sz", &recoil_lower_time_limit_sz, &b_recoil_lower_time_limit_sz);
   fChain->SetBranchAddress("recoil_lower_time_limit", recoil_lower_time_limit, &b_recoil_lower_time_limit);
   fChain->SetBranchAddress("recoil_upper_time_limit_sz", &recoil_upper_time_limit_sz, &b_recoil_upper_time_limit_sz);
   fChain->SetBranchAddress("recoil_upper_time_limit", recoil_upper_time_limit, &b_recoil_upper_time_limit);
   fChain->SetBranchAddress("all_event_start_vertex_time_sz", &all_event_start_vertex_time_sz, &b_all_event_start_vertex_time_sz);
   fChain->SetBranchAddress("all_event_start_vertex_time", all_event_start_vertex_time, &b_all_event_start_vertex_time);
   fChain->SetBranchAddress("all_event_start_vertex_time_minos_match_sz", &all_event_start_vertex_time_minos_match_sz, &b_all_event_start_vertex_time_minos_match_sz);
   fChain->SetBranchAddress("all_event_start_vertex_time_minos_match", all_event_start_vertex_time_minos_match, &b_all_event_start_vertex_time_minos_match);
   fChain->SetBranchAddress("calibE_clusters_at_end_proton_prong_sz", &calibE_clusters_at_end_proton_prong_sz, &b_calibE_clusters_at_end_proton_prong_sz);
   fChain->SetBranchAddress("calibE_clusters_at_end_proton_prong", calibE_clusters_at_end_proton_prong, &b_calibE_clusters_at_end_proton_prong);
   fChain->SetBranchAddress("clusters_found_at_end_proton_prong_max_distance_sz", &clusters_found_at_end_proton_prong_max_distance_sz, &b_clusters_found_at_end_proton_prong_max_distance_sz);
   fChain->SetBranchAddress("clusters_found_at_end_proton_prong_max_distance", clusters_found_at_end_proton_prong_max_distance, &b_clusters_found_at_end_proton_prong_max_distance);
   fChain->SetBranchAddress("event_extra_track_PID_sz", &event_extra_track_PID_sz, &b_event_extra_track_PID_sz);
   fChain->SetBranchAddress("event_extra_track_PID", event_extra_track_PID, &b_event_extra_track_PID);
   fChain->SetBranchAddress("event_in_time_tracks_energy_sz", &event_in_time_tracks_energy_sz, &b_event_in_time_tracks_energy_sz);
   fChain->SetBranchAddress("event_in_time_tracks_energy", event_in_time_tracks_energy, &b_event_in_time_tracks_energy);
   fChain->SetBranchAddress("event_track_hit_energy_sz", &event_track_hit_energy_sz, &b_event_track_hit_energy_sz);
   fChain->SetBranchAddress("event_track_hit_energy", event_track_hit_energy, &b_event_track_hit_energy);
   fChain->SetBranchAddress("event_track_hit_time_sz", &event_track_hit_time_sz, &b_event_track_hit_time_sz);
   fChain->SetBranchAddress("event_track_hit_time", event_track_hit_time, &b_event_track_hit_time);
   fChain->SetBranchAddress("event_track_time_diff_sz", &event_track_time_diff_sz, &b_event_track_time_diff_sz);
   fChain->SetBranchAddress("event_track_time_diff", event_track_time_diff, &b_event_track_time_diff);
   fChain->SetBranchAddress("event_tracks_energy_sz", &event_tracks_energy_sz, &b_event_tracks_energy_sz);
   fChain->SetBranchAddress("event_tracks_energy", event_tracks_energy, &b_event_tracks_energy);
   fChain->SetBranchAddress("event_vertex_time_diff_sz", &event_vertex_time_diff_sz, &b_event_vertex_time_diff_sz);
   fChain->SetBranchAddress("event_vertex_time_diff", event_vertex_time_diff, &b_event_vertex_time_diff);
   fChain->SetBranchAddress("has_michel_data_energy_fraction_sz", &has_michel_data_energy_fraction_sz, &b_has_michel_data_energy_fraction_sz);
   fChain->SetBranchAddress("has_michel_data_energy_fraction", has_michel_data_energy_fraction, &b_has_michel_data_energy_fraction);
   fChain->SetBranchAddress("has_michel_distance_sz", &has_michel_distance_sz, &b_has_michel_distance_sz);
   fChain->SetBranchAddress("has_michel_distance", has_michel_distance, &b_has_michel_distance);
   fChain->SetBranchAddress("has_michel_energy_sz", &has_michel_energy_sz, &b_has_michel_energy_sz);
   fChain->SetBranchAddress("has_michel_energy", has_michel_energy, &b_has_michel_energy);
   fChain->SetBranchAddress("has_michel_hit_charges_sz", &has_michel_hit_charges_sz, &b_has_michel_hit_charges_sz);
   fChain->SetBranchAddress("has_michel_hit_charges", has_michel_hit_charges, &b_has_michel_hit_charges);
   fChain->SetBranchAddress("has_michel_hit_time_diff_cluster_sz", &has_michel_hit_time_diff_cluster_sz, &b_has_michel_hit_time_diff_cluster_sz);
   fChain->SetBranchAddress("has_michel_hit_time_diff_cluster", has_michel_hit_time_diff_cluster, &b_has_michel_hit_time_diff_cluster);
   fChain->SetBranchAddress("has_michel_hit_time_diff_vtx_sz", &has_michel_hit_time_diff_vtx_sz, &b_has_michel_hit_time_diff_vtx_sz);
   fChain->SetBranchAddress("has_michel_hit_time_diff_vtx", has_michel_hit_time_diff_vtx, &b_has_michel_hit_time_diff_vtx);
   fChain->SetBranchAddress("has_michel_hit_times_sz", &has_michel_hit_times_sz, &b_has_michel_hit_times_sz);
   fChain->SetBranchAddress("has_michel_hit_times", has_michel_hit_times, &b_has_michel_hit_times);
   fChain->SetBranchAddress("has_michel_matched_energy_fraction_sz", &has_michel_matched_energy_fraction_sz, &b_has_michel_matched_energy_fraction_sz);
   fChain->SetBranchAddress("has_michel_matched_energy_fraction", has_michel_matched_energy_fraction, &b_has_michel_matched_energy_fraction);
   fChain->SetBranchAddress("has_michel_slice_energy_sz", &has_michel_slice_energy_sz, &b_has_michel_slice_energy_sz);
   fChain->SetBranchAddress("has_michel_slice_energy", has_michel_slice_energy, &b_has_michel_slice_energy);
   fChain->SetBranchAddress("has_michel_time_diff_sz", &has_michel_time_diff_sz, &b_has_michel_time_diff_sz);
   fChain->SetBranchAddress("has_michel_time_diff", has_michel_time_diff, &b_has_michel_time_diff);
   fChain->SetBranchAddress("improved_michel_data_energy_fraction_sz", &improved_michel_data_energy_fraction_sz, &b_improved_michel_data_energy_fraction_sz);
   fChain->SetBranchAddress("improved_michel_data_energy_fraction", improved_michel_data_energy_fraction, &b_improved_michel_data_energy_fraction);
   fChain->SetBranchAddress("improved_michel_dist_vec_sz", &improved_michel_dist_vec_sz, &b_improved_michel_dist_vec_sz);
   fChain->SetBranchAddress("improved_michel_dist_vec", improved_michel_dist_vec, &b_improved_michel_dist_vec);
   fChain->SetBranchAddress("improved_michel_ecalo_vec_sz", &improved_michel_ecalo_vec_sz, &b_improved_michel_ecalo_vec_sz);
   fChain->SetBranchAddress("improved_michel_ecalo_vec", improved_michel_ecalo_vec, &b_improved_michel_ecalo_vec);
   fChain->SetBranchAddress("improved_michel_evis_vec_sz", &improved_michel_evis_vec_sz, &b_improved_michel_evis_vec_sz);
   fChain->SetBranchAddress("improved_michel_evis_vec", improved_michel_evis_vec, &b_improved_michel_evis_vec);
   fChain->SetBranchAddress("improved_michel_hit_charges_sz", &improved_michel_hit_charges_sz, &b_improved_michel_hit_charges_sz);
   fChain->SetBranchAddress("improved_michel_hit_charges", improved_michel_hit_charges, &b_improved_michel_hit_charges);
   fChain->SetBranchAddress("improved_michel_hit_time_diff_cluster_sz", &improved_michel_hit_time_diff_cluster_sz, &b_improved_michel_hit_time_diff_cluster_sz);
   fChain->SetBranchAddress("improved_michel_hit_time_diff_cluster", improved_michel_hit_time_diff_cluster, &b_improved_michel_hit_time_diff_cluster);
   fChain->SetBranchAddress("improved_michel_hit_time_diff_vtx_sz", &improved_michel_hit_time_diff_vtx_sz, &b_improved_michel_hit_time_diff_vtx_sz);
   fChain->SetBranchAddress("improved_michel_hit_time_diff_vtx", improved_michel_hit_time_diff_vtx, &b_improved_michel_hit_time_diff_vtx);
   fChain->SetBranchAddress("improved_michel_hit_times_sz", &improved_michel_hit_times_sz, &b_improved_michel_hit_times_sz);
   fChain->SetBranchAddress("improved_michel_hit_times", improved_michel_hit_times, &b_improved_michel_hit_times);
   fChain->SetBranchAddress("improved_michel_matched_energy_fraction_sz", &improved_michel_matched_energy_fraction_sz, &b_improved_michel_matched_energy_fraction_sz);
   fChain->SetBranchAddress("improved_michel_matched_energy_fraction", improved_michel_matched_energy_fraction, &b_improved_michel_matched_energy_fraction);
   fChain->SetBranchAddress("improved_michel_tdiff_vec_sz", &improved_michel_tdiff_vec_sz, &b_improved_michel_tdiff_vec_sz);
   fChain->SetBranchAddress("improved_michel_tdiff_vec", improved_michel_tdiff_vec, &b_improved_michel_tdiff_vec);
   fChain->SetBranchAddress("improved_michel_tvec_sz", &improved_michel_tvec_sz, &b_improved_michel_tvec_sz);
   fChain->SetBranchAddress("improved_michel_tvec", improved_michel_tvec, &b_improved_michel_tvec);
   fChain->SetBranchAddress("improved_michel_uvec_sz", &improved_michel_uvec_sz, &b_improved_michel_uvec_sz);
   fChain->SetBranchAddress("improved_michel_uvec", improved_michel_uvec, &b_improved_michel_uvec);
   fChain->SetBranchAddress("improved_michel_vvec_sz", &improved_michel_vvec_sz, &b_improved_michel_vvec_sz);
   fChain->SetBranchAddress("improved_michel_vvec", improved_michel_vvec, &b_improved_michel_vvec);
   fChain->SetBranchAddress("improved_michel_xvec_sz", &improved_michel_xvec_sz, &b_improved_michel_xvec_sz);
   fChain->SetBranchAddress("improved_michel_xvec", improved_michel_xvec, &b_improved_michel_xvec);
   fChain->SetBranchAddress("improved_michel_yvec_sz", &improved_michel_yvec_sz, &b_improved_michel_yvec_sz);
   fChain->SetBranchAddress("improved_michel_yvec", improved_michel_yvec, &b_improved_michel_yvec);
   fChain->SetBranchAddress("improved_michel_zvec_sz", &improved_michel_zvec_sz, &b_improved_michel_zvec_sz);
   fChain->SetBranchAddress("improved_michel_zvec", improved_michel_zvec, &b_improved_michel_zvec);

//vec1

  fChain->SetBranchAddress("improved_michel_u1vec_sz", &improved_michel_u1vec_sz, &b_improved_michel_u1vec_sz);
  fChain->SetBranchAddress("improved_michel_u1vec",     improved_michel_u1vec,    &b_improved_michel_u1vec);
  fChain->SetBranchAddress("improved_michel_v1vec_sz", &improved_michel_v1vec_sz, &b_improved_michel_v1vec_sz);
  fChain->SetBranchAddress("improved_michel_v1vec",     improved_michel_v1vec,    &b_improved_michel_v1vec);
  fChain->SetBranchAddress("improved_michel_x1vec_sz", &improved_michel_x1vec_sz, &b_improved_michel_x1vec_sz);
  fChain->SetBranchAddress("improved_michel_x1vec",     improved_michel_x1vec,    &b_improved_michel_x1vec);
  fChain->SetBranchAddress("improved_michel_z1vec_sz", &improved_michel_z1vec_sz, &b_improved_michel_z1vec_sz);
  fChain->SetBranchAddress("improved_michel_z1vec",     improved_michel_z1vec,    &b_improved_michel_z1vec);


  fChain->SetBranchAddress("improved_michel_u2vec_sz", &improved_michel_u2vec_sz, &b_improved_michel_u2vec_sz);
  fChain->SetBranchAddress("improved_michel_u2vec",     improved_michel_u2vec,    &b_improved_michel_u2vec);
  fChain->SetBranchAddress("improved_michel_v2vec_sz", &improved_michel_v2vec_sz, &b_improved_michel_v2vec_sz);
  fChain->SetBranchAddress("improved_michel_v2vec",     improved_michel_v2vec,    &b_improved_michel_v2vec);
  fChain->SetBranchAddress("improved_michel_x2vec_sz", &improved_michel_x2vec_sz, &b_improved_michel_x2vec_sz);
  fChain->SetBranchAddress("improved_michel_x2vec",     improved_michel_x2vec,    &b_improved_michel_x2vec);
  fChain->SetBranchAddress("improved_michel_z2vec_sz", &improved_michel_z2vec_sz, &b_improved_michel_z2vec_sz);
  fChain->SetBranchAddress("improved_michel_z2vec",     improved_michel_z2vec,    &b_improved_michel_z2vec);



  fChain->SetBranchAddress("mehtool_closestclusterX_time"    , mehtool_closestclusterX_time, &b_mehtool_closestclusterX_time );
  fChain->SetBranchAddress("mehtool_closestclusterU_time"    , mehtool_closestclusterU_time, &b_mehtool_closestclusterU_time );
  fChain->SetBranchAddress("mehtool_closestclusterV_time"    , mehtool_closestclusterV_time, &b_mehtool_closestclusterV_time );

  fChain->SetBranchAddress("mehtool_closestclusterX_distance", mehtool_closestclusterX_distance, &b_mehtool_closestclusterX_distance );
  fChain->SetBranchAddress("mehtool_closestclusterU_distance", mehtool_closestclusterU_distance, &b_mehtool_closestclusterU_distance );
  fChain->SetBranchAddress("mehtool_closestclusterV_distance", mehtool_closestclusterV_distance, &b_mehtool_closestclusterV_distance );

  fChain->SetBranchAddress("mehtool_closestclusterXZ_distance", mehtool_closestclusterXZ_distance, &b_mehtool_closestclusterXZ_distance );
  fChain->SetBranchAddress("mehtool_closestclusterUZ_distance", mehtool_closestclusterUZ_distance, &b_mehtool_closestclusterUZ_distance );
  fChain->SetBranchAddress("mehtool_closestclusterVZ_distance", mehtool_closestclusterVZ_distance, &b_mehtool_closestclusterVZ_distance );

  fChain->SetBranchAddress("mehtool_closestclusterX_energy"  , mehtool_closestclusterX_energy, &b_mehtool_closestclusterX_energy );
  fChain->SetBranchAddress("mehtool_closestclusterU_energy"  , mehtool_closestclusterU_energy, &b_mehtool_closestclusterU_energy );
  fChain->SetBranchAddress("mehtool_closestclusterV_energy"  , mehtool_closestclusterV_energy, &b_mehtool_closestclusterV_energy );

  fChain->SetBranchAddress("mehtool_closestclusterX_endpoint", mehtool_closestclusterX_endpoint, &b_mehtool_closestclusterX_endpoint );
  fChain->SetBranchAddress("mehtool_closestclusterU_endpoint", mehtool_closestclusterU_endpoint, &b_mehtool_closestclusterU_endpoint );
  fChain->SetBranchAddress("mehtool_closestclusterV_endpoint", mehtool_closestclusterV_endpoint, &b_mehtool_closestclusterV_endpoint );


  fChain->SetBranchAddress("mehtool_nmichelsmatch", &mehtool_nmichelsmatch, &b_mehtool_nmichelsmatch);
  fChain->SetBranchAddress("mehtool_duplicate_michelindex", mehtool_duplicate_michelindex, &b_mehtool_duplicate_michelindex);
  fChain->SetBranchAddress("mehtool_closestclusterX_nclusz", mehtool_closestclusterX_nclusz, &b_mehtool_closestclusterX_nclusz);
  fChain->SetBranchAddress("mehtool_closestclusterU_nclusz", mehtool_closestclusterU_nclusz, &b_mehtool_closestclusterU_nclusz);
  fChain->SetBranchAddress("mehtool_closestclusterV_nclusz", mehtool_closestclusterV_nclusz, &b_mehtool_closestclusterV_nclusz);


  fChain->SetBranchAddress("mehtool_closestclusterX_time_sz"    , &mehtool_closestclusterX_time_sz, &b_mehtool_closestclusterX_time_sz );
  fChain->SetBranchAddress("mehtool_closestclusterU_time_sz"    , &mehtool_closestclusterU_time_sz, &b_mehtool_closestclusterU_time_sz );
  fChain->SetBranchAddress("mehtool_closestclusterV_time_sz"    , &mehtool_closestclusterV_time_sz, &b_mehtool_closestclusterV_time_sz );

  fChain->SetBranchAddress("mehtool_closestclusterX_distance_sz", &mehtool_closestclusterX_distance_sz, &b_mehtool_closestclusterX_distance_sz );
  fChain->SetBranchAddress("mehtool_closestclusterU_distance_sz", &mehtool_closestclusterU_distance_sz, &b_mehtool_closestclusterU_distance_sz );
  fChain->SetBranchAddress("mehtool_closestclusterV_distance_sz", &mehtool_closestclusterV_distance_sz, &b_mehtool_closestclusterV_distance_sz );

  fChain->SetBranchAddress("mehtool_closestclusterXZ_distance_sz", &mehtool_closestclusterXZ_distance_sz, &b_mehtool_closestclusterXZ_distance_sz );
  fChain->SetBranchAddress("mehtool_closestclusterUZ_distance_sz", &mehtool_closestclusterUZ_distance_sz, &b_mehtool_closestclusterUZ_distance_sz );
  fChain->SetBranchAddress("mehtool_closestclusterVZ_distance_sz", &mehtool_closestclusterVZ_distance_sz, &b_mehtool_closestclusterVZ_distance_sz );

  fChain->SetBranchAddress("mehtool_closestclusterX_energy_sz"  , &mehtool_closestclusterX_energy_sz, &b_mehtool_closestclusterX_energy_sz );
  fChain->SetBranchAddress("mehtool_closestclusterU_energy_sz"  , &mehtool_closestclusterU_energy_sz, &b_mehtool_closestclusterU_energy_sz );
  fChain->SetBranchAddress("mehtool_closestclusterV_energy_sz"  , &mehtool_closestclusterV_energy_sz, &b_mehtool_closestclusterV_energy_sz );

  fChain->SetBranchAddress("mehtool_closestclusterX_endpoint_sz", &mehtool_closestclusterX_endpoint_sz, &b_mehtool_closestclusterX_endpoint_sz );
  fChain->SetBranchAddress("mehtool_closestclusterU_endpoint_sz", &mehtool_closestclusterU_endpoint_sz, &b_mehtool_closestclusterU_endpoint_sz );
  fChain->SetBranchAddress("mehtool_closestclusterV_endpoint_sz", &mehtool_closestclusterV_endpoint_sz, &b_mehtool_closestclusterV_endpoint_sz );


  fChain->SetBranchAddress("mehtool_nmichelsmatch", &mehtool_nmichelsmatch, &b_mehtool_nmichelsmatch);
  fChain->SetBranchAddress("mehtool_duplicate_michelindex", mehtool_duplicate_michelindex, &b_mehtool_duplicate_michelindex);
  fChain->SetBranchAddress("mehtool_closestclusterX_nclusz_sz", mehtool_closestclusterX_nclusz, &b_mehtool_closestclusterX_nclusz);
  fChain->SetBranchAddress("mehtool_closestclusterU_nclusz_sz", mehtool_closestclusterU_nclusz, &b_mehtool_closestclusterU_nclusz);
  fChain->SetBranchAddress("mehtool_closestclusterV_nclusz_sz", mehtool_closestclusterV_nclusz, &b_mehtool_closestclusterV_nclusz);


  fChain->SetBranchAddress("mehtool_closestclusterX_clustime", mehtool_closestclusterX_clustime, &b_mehtool_closestclusterX_clustime);
  fChain->SetBranchAddress("mehtool_closestclusterU_clustime", mehtool_closestclusterU_clustime, &b_mehtool_closestclusterU_clustime);
  fChain->SetBranchAddress("mehtool_closestclusterV_clustime", mehtool_closestclusterV_clustime, &b_mehtool_closestclusterV_clustime);

  fChain->SetBranchAddress("mehtool_closestclusterX_clustime_sz", &mehtool_closestclusterX_clustime_sz, &b_mehtool_closestclusterX_clustime_sz);
  fChain->SetBranchAddress("mehtool_closestclusterU_clustime_sz", &mehtool_closestclusterU_clustime_sz, &b_mehtool_closestclusterU_clustime_sz);
  fChain->SetBranchAddress("mehtool_closestclusterV_clustime_sz", &mehtool_closestclusterV_clustime_sz, &b_mehtool_closestclusterV_clustime_sz);


  fChain->SetBranchAddress("mehtool_michel_time", mehtool_michel_time, &b_mehtool_michel_time);
  fChain->SetBranchAddress("mehtool_michel_time_sz", &mehtool_michel_time_sz, &b_mehtool_michel_time_sz);

  fChain->SetBranchAddress("mehtool_michel_energy", mehtool_michel_energy, &b_mehtool_michel_energy);
  fChain->SetBranchAddress("mehtool_michel_energy_sz", &mehtool_michel_energy_sz, &b_mehtool_michel_energy_sz);

  fChain->SetBranchAddress("mehtool_michel_Xclusters", mehtool_michel_Xclusters, &b_mehtool_michel_Xclusters);
  fChain->SetBranchAddress("mehtool_michel_Xclusters_sz", &mehtool_michel_Xclusters_sz, &b_mehtool_michel_Xclusters_sz);

  fChain->SetBranchAddress("mehtool_michel_Uclusters", mehtool_michel_Uclusters, &b_mehtool_michel_Uclusters);
  fChain->SetBranchAddress("mehtool_michel_Uclusters_sz", &mehtool_michel_Uclusters_sz, &b_mehtool_michel_Uclusters_sz);

  fChain->SetBranchAddress("mehtool_michel_Vclusters", mehtool_michel_Vclusters, &b_mehtool_michel_Vclusters);
  fChain->SetBranchAddress("mehtool_michel_Vclusters_sz", &mehtool_michel_Vclusters_sz, &b_mehtool_michel_Vclusters_sz);

  fChain->SetBranchAddress("mehtool_michel_x1", mehtool_michel_x1, &b_mehtool_michel_x1);
  fChain->SetBranchAddress("mehtool_michel_x2", mehtool_michel_x2, &b_mehtool_michel_x2);
  fChain->SetBranchAddress("mehtool_michel_u1", mehtool_michel_u1, &b_mehtool_michel_u1);
  fChain->SetBranchAddress("mehtool_michel_u2", mehtool_michel_u2, &b_mehtool_michel_u2);
  fChain->SetBranchAddress("mehtool_michel_v1", mehtool_michel_v1, &b_mehtool_michel_v1);
  fChain->SetBranchAddress("mehtool_michel_v2", mehtool_michel_v2, &b_mehtool_michel_v2);
  fChain->SetBranchAddress("mehtool_michel_z1", mehtool_michel_z1, &b_mehtool_michel_z1);
  fChain->SetBranchAddress("mehtool_michel_z2", mehtool_michel_z2, &b_mehtool_michel_z2);

  fChain->SetBranchAddress("mehtool_michel_x1_sz", &mehtool_michel_x1_sz, &b_mehtool_michel_x1_sz);
  fChain->SetBranchAddress("mehtool_michel_x2_sz", &mehtool_michel_x2_sz, &b_mehtool_michel_x2_sz);
  fChain->SetBranchAddress("mehtool_michel_u1_sz", &mehtool_michel_u1_sz, &b_mehtool_michel_u1_sz);
  fChain->SetBranchAddress("mehtool_michel_u2_sz", &mehtool_michel_u2_sz, &b_mehtool_michel_u2_sz);
  fChain->SetBranchAddress("mehtool_michel_v1_sz", &mehtool_michel_v1_sz, &b_mehtool_michel_v1_sz);
  fChain->SetBranchAddress("mehtool_michel_v2_sz", &mehtool_michel_v2_sz, &b_mehtool_michel_v2_sz);
  fChain->SetBranchAddress("mehtool_michel_z1_sz", &mehtool_michel_z1_sz, &b_mehtool_michel_z1_sz);
  fChain->SetBranchAddress("mehtool_michel_z2_sz", &mehtool_michel_z2_sz, &b_mehtool_michel_z2_sz);


  fChain->SetBranchAddress("mehtool_closestclusterX_Z_pos", mehtool_closestclusterX_Z_pos, &b_mehtool_closestclusterX_Z_pos) ;
  fChain->SetBranchAddress("mehtool_closestclusterU_Z_pos", mehtool_closestclusterU_Z_pos, &b_mehtool_closestclusterU_Z_pos) ;
  fChain->SetBranchAddress("mehtool_closestclusterV_Z_pos", mehtool_closestclusterV_Z_pos, &b_mehtool_closestclusterV_Z_pos) ;

  fChain->SetBranchAddress("mehtool_closestclusterX_Z_pos_sz", &mehtool_closestclusterX_Z_pos_sz, &b_mehtool_closestclusterX_Z_pos_sz);
  fChain->SetBranchAddress("mehtool_closestclusterU_Z_pos_sz", &mehtool_closestclusterU_Z_pos_sz, &b_mehtool_closestclusterU_Z_pos_sz);
  fChain->SetBranchAddress("mehtool_closestclusterV_Z_pos_sz", &mehtool_closestclusterV_Z_pos_sz, &b_mehtool_closestclusterV_Z_pos_sz);

  fChain->SetBranchAddress("mehtool_closestclusterX_pos", mehtool_closestclusterX_pos, &b_mehtool_closestclusterX_pos) ;
  fChain->SetBranchAddress("mehtool_closestclusterU_pos", mehtool_closestclusterU_pos, &b_mehtool_closestclusterU_pos) ;
  fChain->SetBranchAddress("mehtool_closestclusterV_pos", mehtool_closestclusterV_pos, &b_mehtool_closestclusterV_pos) ;

  fChain->SetBranchAddress("mehtool_closestclusterX_pos_sz", &mehtool_closestclusterX_pos_sz, &b_mehtool_closestclusterX_pos_sz);
  fChain->SetBranchAddress("mehtool_closestclusterU_pos_sz", &mehtool_closestclusterU_pos_sz, &b_mehtool_closestclusterU_pos_sz);
  fChain->SetBranchAddress("mehtool_closestclusterV_pos_sz", &mehtool_closestclusterV_pos_sz, &b_mehtool_closestclusterV_pos_sz);

  fChain->SetBranchAddress("mehtool_michel_maxmeandiff", mehtool_michel_maxmeandiff, &b_mehtool_michel_maxmeandiff);
  fChain->SetBranchAddress("mehtool_michel_maxmeandiff_sz", &mehtool_michel_maxmeandiff_sz, &b_mehtool_michel_maxmeandiff_sz);

  fChain->SetBranchAddress("mehtool_istrueMichel", mehtool_istrueMichel, &b_mehtool_istrueMichel);
  fChain->SetBranchAddress("mehtool_istrueMichel_sz", &mehtool_istrueMichel_sz, &b_mehtool_istrueMichel_sz);

  fChain->SetBranchAddress("mehtool_michel_allmichelenergy", mehtool_michel_allmichelenergy, &b_mehtool_michel_allmichelenergy);
  fChain->SetBranchAddress("mehtool_michel_allmichelenergy_sz", &mehtool_michel_allmichelenergy_sz, &b_mehtool_michel_allmichelenergy_sz);

  fChain->SetBranchAddress("mehtool_michel_from_decay", mehtool_michel_from_decay, &b_mehtool_michel_from_decay);
  fChain->SetBranchAddress("mehtool_michel_from_decay_sz", &mehtool_michel_from_decay_sz, &b_mehtool_michel_from_decay_sz);

  fChain->SetBranchAddress("mehtool_true_michel_pdg", mehtool_true_michel_pdg, &b_mehtool_true_michel_pdg);
  fChain->SetBranchAddress("mehtool_true_michel_pdg_sz", &mehtool_true_michel_pdg_sz, &b_mehtool_true_michel_pdg_sz);

   fChain->SetBranchAddress("muon_thetaX_allNodes_sz", &muon_thetaX_allNodes_sz, &b_muon_thetaX_allNodes_sz);
   fChain->SetBranchAddress("muon_thetaX_allNodes", muon_thetaX_allNodes, &b_muon_thetaX_allNodes);
   fChain->SetBranchAddress("muon_thetaY_allNodes_sz", &muon_thetaY_allNodes_sz, &b_muon_thetaY_allNodes_sz);
   fChain->SetBranchAddress("muon_thetaY_allNodes", muon_thetaY_allNodes, &b_muon_thetaY_allNodes);
   fChain->SetBranchAddress("muon_theta_allNodes_sz", &muon_theta_allNodes_sz, &b_muon_theta_allNodes_sz);
   fChain->SetBranchAddress("muon_theta_allNodes", muon_theta_allNodes, &b_muon_theta_allNodes);
   fChain->SetBranchAddress("nonvtx_iso_blobs_data_energy_fraction_in_prong_sz", &nonvtx_iso_blobs_data_energy_fraction_in_prong_sz, &b_nonvtx_iso_blobs_data_energy_fraction_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_data_energy_fraction_in_prong", nonvtx_iso_blobs_data_energy_fraction_in_prong, &b_nonvtx_iso_blobs_data_energy_fraction_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_distance_in_prong_sz", &nonvtx_iso_blobs_distance_in_prong_sz, &b_nonvtx_iso_blobs_distance_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_distance_in_prong", nonvtx_iso_blobs_distance_in_prong, &b_nonvtx_iso_blobs_distance_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_earliest_hit_time_in_prong_sz", &nonvtx_iso_blobs_earliest_hit_time_in_prong_sz, &b_nonvtx_iso_blobs_earliest_hit_time_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_earliest_hit_time_in_prong", nonvtx_iso_blobs_earliest_hit_time_in_prong, &b_nonvtx_iso_blobs_earliest_hit_time_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_energy_in_prong_sz", &nonvtx_iso_blobs_energy_in_prong_sz, &b_nonvtx_iso_blobs_energy_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_energy_in_prong", nonvtx_iso_blobs_energy_in_prong, &b_nonvtx_iso_blobs_energy_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_highest_hit_energy_in_prong_sz", &nonvtx_iso_blobs_highest_hit_energy_in_prong_sz, &b_nonvtx_iso_blobs_highest_hit_energy_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_highest_hit_energy_in_prong", nonvtx_iso_blobs_highest_hit_energy_in_prong, &b_nonvtx_iso_blobs_highest_hit_energy_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_highest_module_u_in_prong_sz", &nonvtx_iso_blobs_highest_module_u_in_prong_sz, &b_nonvtx_iso_blobs_highest_module_u_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_highest_module_u_in_prong", nonvtx_iso_blobs_highest_module_u_in_prong, &b_nonvtx_iso_blobs_highest_module_u_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_highest_module_v_in_prong_sz", &nonvtx_iso_blobs_highest_module_v_in_prong_sz, &b_nonvtx_iso_blobs_highest_module_v_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_highest_module_v_in_prong", nonvtx_iso_blobs_highest_module_v_in_prong, &b_nonvtx_iso_blobs_highest_module_v_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_highest_module_x_in_prong_sz", &nonvtx_iso_blobs_highest_module_x_in_prong_sz, &b_nonvtx_iso_blobs_highest_module_x_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_highest_module_x_in_prong", nonvtx_iso_blobs_highest_module_x_in_prong, &b_nonvtx_iso_blobs_highest_module_x_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_latest_hit_time_in_prong_sz", &nonvtx_iso_blobs_latest_hit_time_in_prong_sz, &b_nonvtx_iso_blobs_latest_hit_time_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_latest_hit_time_in_prong", nonvtx_iso_blobs_latest_hit_time_in_prong, &b_nonvtx_iso_blobs_latest_hit_time_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_lowest_module_u_in_prong_sz", &nonvtx_iso_blobs_lowest_module_u_in_prong_sz, &b_nonvtx_iso_blobs_lowest_module_u_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_lowest_module_u_in_prong", nonvtx_iso_blobs_lowest_module_u_in_prong, &b_nonvtx_iso_blobs_lowest_module_u_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_lowest_module_v_in_prong_sz", &nonvtx_iso_blobs_lowest_module_v_in_prong_sz, &b_nonvtx_iso_blobs_lowest_module_v_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_lowest_module_v_in_prong", nonvtx_iso_blobs_lowest_module_v_in_prong, &b_nonvtx_iso_blobs_lowest_module_v_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_lowest_module_x_in_prong_sz", &nonvtx_iso_blobs_lowest_module_x_in_prong_sz, &b_nonvtx_iso_blobs_lowest_module_x_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_lowest_module_x_in_prong", nonvtx_iso_blobs_lowest_module_x_in_prong, &b_nonvtx_iso_blobs_lowest_module_x_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_matched_energy_fraction_in_prong_sz", &nonvtx_iso_blobs_matched_energy_fraction_in_prong_sz, &b_nonvtx_iso_blobs_matched_energy_fraction_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_matched_energy_fraction_in_prong", nonvtx_iso_blobs_matched_energy_fraction_in_prong, &b_nonvtx_iso_blobs_matched_energy_fraction_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_start_position_x_in_prong_sz", &nonvtx_iso_blobs_start_position_x_in_prong_sz, &b_nonvtx_iso_blobs_start_position_x_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_start_position_x_in_prong", nonvtx_iso_blobs_start_position_x_in_prong, &b_nonvtx_iso_blobs_start_position_x_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_start_position_y_in_prong_sz", &nonvtx_iso_blobs_start_position_y_in_prong_sz, &b_nonvtx_iso_blobs_start_position_y_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_start_position_y_in_prong", nonvtx_iso_blobs_start_position_y_in_prong, &b_nonvtx_iso_blobs_start_position_y_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_start_position_z_in_prong_sz", &nonvtx_iso_blobs_start_position_z_in_prong_sz, &b_nonvtx_iso_blobs_start_position_z_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_start_position_z_in_prong", nonvtx_iso_blobs_start_position_z_in_prong, &b_nonvtx_iso_blobs_start_position_z_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_time_difference_in_prong_sz", &nonvtx_iso_blobs_time_difference_in_prong_sz, &b_nonvtx_iso_blobs_time_difference_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_time_difference_in_prong", nonvtx_iso_blobs_time_difference_in_prong, &b_nonvtx_iso_blobs_time_difference_in_prong);
   fChain->SetBranchAddress("nonvtx_iso_blobs_time_in_prong_sz", &nonvtx_iso_blobs_time_in_prong_sz, &b_nonvtx_iso_blobs_time_in_prong_sz);
   fChain->SetBranchAddress("nonvtx_iso_blobs_time_in_prong", nonvtx_iso_blobs_time_in_prong, &b_nonvtx_iso_blobs_time_in_prong);
   fChain->SetBranchAddress("proton_prong_4p", proton_prong_4p, &b_proton_prong_4p);
   fChain->SetBranchAddress("proton_prong_tpos", proton_prong_tpos, &b_proton_prong_tpos);
   fChain->SetBranchAddress("recoil_data_fraction_sz", &recoil_data_fraction_sz, &b_recoil_data_fraction_sz);
   fChain->SetBranchAddress("recoil_data_fraction", recoil_data_fraction, &b_recoil_data_fraction);
   fChain->SetBranchAddress("recoil_summed_energy_sz", &recoil_summed_energy_sz, &b_recoil_summed_energy_sz);
   fChain->SetBranchAddress("recoil_summed_energy", recoil_summed_energy, &b_recoil_summed_energy);
   fChain->SetBranchAddress("slice_hit_energy_sz", &slice_hit_energy_sz, &b_slice_hit_energy_sz);
   fChain->SetBranchAddress("slice_hit_energy", slice_hit_energy, &b_slice_hit_energy);
   fChain->SetBranchAddress("slice_hit_time_sz", &slice_hit_time_sz, &b_slice_hit_time_sz);
   fChain->SetBranchAddress("slice_hit_time", slice_hit_time, &b_slice_hit_time);
   fChain->SetBranchAddress("visE_clusters_at_end_proton_prong_sz", &visE_clusters_at_end_proton_prong_sz, &b_visE_clusters_at_end_proton_prong_sz);
   fChain->SetBranchAddress("visE_clusters_at_end_proton_prong", visE_clusters_at_end_proton_prong, &b_visE_clusters_at_end_proton_prong);
   fChain->SetBranchAddress("vtx_blobs_iso_distance_in_prong_sz", &vtx_blobs_iso_distance_in_prong_sz, &b_vtx_blobs_iso_distance_in_prong_sz);
   fChain->SetBranchAddress("vtx_blobs_iso_distance_in_prong", vtx_blobs_iso_distance_in_prong, &b_vtx_blobs_iso_distance_in_prong);
   fChain->SetBranchAddress("vtx_blobs_iso_energy_clusters_outside_radius_in_prong_sz", &vtx_blobs_iso_energy_clusters_outside_radius_in_prong_sz, &b_vtx_blobs_iso_energy_clusters_outside_radius_in_prong_sz);
   fChain->SetBranchAddress("vtx_blobs_iso_energy_clusters_outside_radius_in_prong", vtx_blobs_iso_energy_clusters_outside_radius_in_prong, &b_vtx_blobs_iso_energy_clusters_outside_radius_in_prong);
   fChain->SetBranchAddress("vtx_blobs_iso_energy_in_prong_sz", &vtx_blobs_iso_energy_in_prong_sz, &b_vtx_blobs_iso_energy_in_prong_sz);
   fChain->SetBranchAddress("vtx_blobs_iso_energy_in_prong", vtx_blobs_iso_energy_in_prong, &b_vtx_blobs_iso_energy_in_prong);
   fChain->SetBranchAddress("vtx_blobs_vtx_distance_in_prong_sz", &vtx_blobs_vtx_distance_in_prong_sz, &b_vtx_blobs_vtx_distance_in_prong_sz);
   fChain->SetBranchAddress("vtx_blobs_vtx_distance_in_prong", &vtx_blobs_vtx_distance_in_prong, &b_vtx_blobs_vtx_distance_in_prong);
   fChain->SetBranchAddress("vtx_blobs_vtx_energy_in_prong_sz", &vtx_blobs_vtx_energy_in_prong_sz, &b_vtx_blobs_vtx_energy_in_prong_sz);
   fChain->SetBranchAddress("vtx_blobs_vtx_energy_in_prong", vtx_blobs_vtx_energy_in_prong, &b_vtx_blobs_vtx_energy_in_prong);
   if(!IsData){
     fChain->SetBranchAddress("truth_has_michel_from_pion_minus_momentum_sz", &truth_has_michel_from_pion_minus_momentum_sz, &b_truth_has_michel_from_pion_minus_momentum_sz);
     fChain->SetBranchAddress("truth_has_michel_from_pion_minus_momentum", &truth_has_michel_from_pion_minus_momentum, &b_truth_has_michel_from_pion_minus_momentum);
     fChain->SetBranchAddress("truth_has_michel_from_pion_plus_momentum_sz", &truth_has_michel_from_pion_plus_momentum_sz, &b_truth_has_michel_from_pion_plus_momentum_sz);
     fChain->SetBranchAddress("truth_has_michel_from_pion_plus_momentum", truth_has_michel_from_pion_plus_momentum, &b_truth_has_michel_from_pion_plus_momentum);
     fChain->SetBranchAddress("truth_has_michel_electron", &truth_has_michel_electron, &b_truth_has_michel_electron);
     fChain->SetBranchAddress("truth_improved_michel_electron", &truth_improved_michel_electron, &b_truth_improved_michel_electron);
     fChain->SetBranchAddress("truth_has_physics_event", &truth_has_physics_event, &b_truth_has_physics_event);
     fChain->SetBranchAddress("truth_is_fiducial", &truth_is_fiducial, &b_truth_is_fiducial);
     //fChain->SetBranchAddress("truth_primTrajN", &truth_primTrajN, &b_truth_primTrajN);

     fChain->SetBranchAddress("truth_hadronReweightNPaths", &truth_hadronReweightNPaths, &b_truth_hadronReweightNPaths); // HadronReweight 2.0
     fChain->SetBranchAddress("truth_hadronReweightNPoints", &truth_hadronReweightNPoints, &b_truth_hadronReweightNPoints); // HadronReweight 2.0

     fChain->SetBranchAddress("truth_reco_has_michel_electron", &truth_reco_has_michel_electron, &b_truth_reco_has_michel_electron);
     fChain->SetBranchAddress("truth_reco_has_muon_charge", &truth_reco_has_muon_charge, &b_truth_reco_has_muon_charge);
     fChain->SetBranchAddress("truth_reco_has_single_proton", &truth_reco_has_single_proton, &b_truth_reco_has_single_proton);
     fChain->SetBranchAddress("truth_reco_is_fiducial", &truth_reco_is_fiducial, &b_truth_reco_is_fiducial);
     fChain->SetBranchAddress("truth_reco_is_minos_match", &truth_reco_is_minos_match, &b_truth_reco_is_minos_match);
     fChain->SetBranchAddress("truth_reco_muon_is_minos_match_stub", &truth_reco_muon_is_minos_match_stub, &b_truth_reco_muon_is_minos_match_stub);
     fChain->SetBranchAddress("truth_reco_muon_is_minos_match_track", &truth_reco_muon_is_minos_match_track, &b_truth_reco_muon_is_minos_match_track);
     fChain->SetBranchAddress("truth_reco_pass_CCQENu_precuts", &truth_reco_pass_CCQENu_precuts, &b_truth_reco_pass_CCQENu_precuts);
     //fChain->SetBranchAddress("truth_neutron_kevinwgt10down", &truth_neutron_kevinwgt10down, &b_truth_neutron_kevinwgt10down);
     //fChain->SetBranchAddress("truth_neutron_kevinwgt10up", &truth_neutron_kevinwgt10up, &b_truth_neutron_kevinwgt10up);
     //fChain->SetBranchAddress("truth_neutron_kevinwgt20down", &truth_neutron_kevinwgt20down, &b_truth_neutron_kevinwgt20down);
     //fChain->SetBranchAddress("truth_neutron_kevinwgt20up", &truth_neutron_kevinwgt20up, &b_truth_neutron_kevinwgt20up);
     //fChain->SetBranchAddress("truth_neutron_kevinwgt50down", &truth_neutron_kevinwgt50down, &b_truth_neutron_kevinwgt50down);
     //fChain->SetBranchAddress("truth_neutron_kevinwgt50up", &truth_neutron_kevinwgt50up, &b_truth_neutron_kevinwgt50up);
     //fChain->SetBranchAddress("truth_neutron_kevinwgtvardown", &truth_neutron_kevinwgtvardown, &b_truth_neutron_kevinwgtvardown);
     //fChain->SetBranchAddress("truth_neutron_kevinwgtvarup", &truth_neutron_kevinwgtvarup, &b_truth_neutron_kevinwgtvarup);
     //fChain->SetBranchAddress("truth_primTrajInelasticReweightCode_sz", &truth_primTrajInelasticReweightCode_sz, &b_truth_primTrajInelasticReweightCode_sz);
     //fChain->SetBranchAddress("truth_primTrajInelasticReweightCode", truth_primTrajInelasticReweightCode, &b_truth_primTrajInelasticReweightCode);
     //fChain->SetBranchAddress("truth_primTrajPDG_sz", &truth_primTrajPDG_sz, &b_truth_primTrajPDG_sz);
     //fChain->SetBranchAddress("truth_primTrajPDG", truth_primTrajPDG, &b_truth_primTrajPDG);
     //fChain->SetBranchAddress("truth_primTrajReweightFiducialContained_sz", &truth_primTrajReweightFiducialContained_sz, &b_truth_primTrajReweightFiducialContained_sz);
     //fChain->SetBranchAddress("truth_primTrajReweightFiducialContained", truth_primTrajReweightFiducialContained, &b_truth_primTrajReweightFiducialContained);

     fChain->SetBranchAddress("truth_hadronReweightPDG_sz", &truth_hadronReweightPDG_sz, &b_truth_hadronReweightPDG_sz);
     fChain->SetBranchAddress("truth_hadronReweightPDG", truth_hadronReweightPDG, &b_truth_hadronReweightPDG);
     fChain->SetBranchAddress("truth_hadronReweightIntCode_sz", &truth_hadronReweightIntCode_sz, &b_truth_hadronReweightIntCode_sz);
     fChain->SetBranchAddress("truth_hadronReweightIntCode", truth_hadronReweightIntCode, &b_truth_hadronReweightIntCode);
     fChain->SetBranchAddress("truth_hadronReweightTrackID_sz", &truth_hadronReweightTrackID_sz, &b_truth_hadronReweightTrackID_sz);
     fChain->SetBranchAddress("truth_hadronReweightTrackID", truth_hadronReweightTrackID, &b_truth_hadronReweightTrackID);
     fChain->SetBranchAddress("truth_hadronReweightNuke_sz", &truth_hadronReweightNuke_sz, &b_truth_hadronReweightNuke_sz);
     fChain->SetBranchAddress("truth_hadronReweightNuke", truth_hadronReweightNuke, &b_truth_hadronReweightNuke);

     fChain->SetBranchAddress("genie_wgt_n_shifts", &genie_wgt_n_shifts, &b_genie_wgt_n_shifts);
     fChain->SetBranchAddress("truth_genie_wgt_AGKYxF1pi", truth_genie_wgt_AGKYxF1pi, &b_truth_genie_wgt_AGKYxF1pi);
     fChain->SetBranchAddress("truth_genie_wgt_AhtBY", truth_genie_wgt_AhtBY, &b_truth_genie_wgt_AhtBY);
     fChain->SetBranchAddress("truth_genie_wgt_BhtBY", truth_genie_wgt_BhtBY, &b_truth_genie_wgt_BhtBY);
     fChain->SetBranchAddress("truth_genie_wgt_CCQEPauliSupViaKF", truth_genie_wgt_CCQEPauliSupViaKF, &b_truth_genie_wgt_CCQEPauliSupViaKF);
     fChain->SetBranchAddress("truth_genie_wgt_CV1uBY", truth_genie_wgt_CV1uBY, &b_truth_genie_wgt_CV1uBY);
     fChain->SetBranchAddress("truth_genie_wgt_CV2uBY", truth_genie_wgt_CV2uBY, &b_truth_genie_wgt_CV2uBY);
     fChain->SetBranchAddress("truth_genie_wgt_EtaNCEL", truth_genie_wgt_EtaNCEL, &b_truth_genie_wgt_EtaNCEL);
     fChain->SetBranchAddress("truth_genie_wgt_FrAbs_N", truth_genie_wgt_FrAbs_N, &b_truth_genie_wgt_FrAbs_N);
     fChain->SetBranchAddress("truth_genie_wgt_FrAbs_pi", truth_genie_wgt_FrAbs_pi, &b_truth_genie_wgt_FrAbs_pi);
     fChain->SetBranchAddress("truth_genie_wgt_FrCEx_N", truth_genie_wgt_FrCEx_N, &b_truth_genie_wgt_FrCEx_N);
     fChain->SetBranchAddress("truth_genie_wgt_FrCEx_pi", truth_genie_wgt_FrCEx_pi, &b_truth_genie_wgt_FrCEx_pi);
     fChain->SetBranchAddress("truth_genie_wgt_FrElas_N", truth_genie_wgt_FrElas_N, &b_truth_genie_wgt_FrElas_N);
     fChain->SetBranchAddress("truth_genie_wgt_FrElas_pi", truth_genie_wgt_FrElas_pi, &b_truth_genie_wgt_FrElas_pi);
     fChain->SetBranchAddress("truth_genie_wgt_FrInel_N", truth_genie_wgt_FrInel_N, &b_truth_genie_wgt_FrInel_N);
     fChain->SetBranchAddress("truth_genie_wgt_FrInel_pi", truth_genie_wgt_FrInel_pi, &b_truth_genie_wgt_FrInel_pi);
     fChain->SetBranchAddress("truth_genie_wgt_FrPiProd_N", truth_genie_wgt_FrPiProd_N, &b_truth_genie_wgt_FrPiProd_N);
     fChain->SetBranchAddress("truth_genie_wgt_FrPiProd_pi", truth_genie_wgt_FrPiProd_pi, &b_truth_genie_wgt_FrPiProd_pi);
     fChain->SetBranchAddress("truth_genie_wgt_MFP_N", truth_genie_wgt_MFP_N, &b_truth_genie_wgt_MFP_N);
     fChain->SetBranchAddress("truth_genie_wgt_MFP_pi", truth_genie_wgt_MFP_pi, &b_truth_genie_wgt_MFP_pi);
     fChain->SetBranchAddress("truth_genie_wgt_MaCCQE", truth_genie_wgt_MaCCQE, &b_truth_genie_wgt_MaCCQE);
     fChain->SetBranchAddress("truth_genie_wgt_MaCCQEshape", truth_genie_wgt_MaCCQEshape, &b_truth_genie_wgt_MaCCQEshape);
     fChain->SetBranchAddress("truth_genie_wgt_MaNCEL", truth_genie_wgt_MaNCEL, &b_truth_genie_wgt_MaNCEL);
     fChain->SetBranchAddress("truth_genie_wgt_MaRES", truth_genie_wgt_MaRES, &b_truth_genie_wgt_MaRES);
     fChain->SetBranchAddress("truth_genie_wgt_MvRES", truth_genie_wgt_MvRES, &b_truth_genie_wgt_MvRES);
     fChain->SetBranchAddress("truth_genie_wgt_NormCCQE", truth_genie_wgt_NormCCQE, &b_truth_genie_wgt_NormCCQE);
     fChain->SetBranchAddress("truth_genie_wgt_NormCCRES", truth_genie_wgt_NormCCRES, &b_truth_genie_wgt_NormCCRES);
     fChain->SetBranchAddress("truth_genie_wgt_NormDISCC", truth_genie_wgt_NormDISCC, &b_truth_genie_wgt_NormDISCC);
     fChain->SetBranchAddress("truth_genie_wgt_NormNCRES", truth_genie_wgt_NormNCRES, &b_truth_genie_wgt_NormNCRES);
     fChain->SetBranchAddress("truth_genie_wgt_RDecBR1gamma", truth_genie_wgt_RDecBR1gamma, &b_truth_genie_wgt_RDecBR1gamma);
     fChain->SetBranchAddress("truth_genie_wgt_Rvn1pi", truth_genie_wgt_Rvn1pi, &b_truth_genie_wgt_Rvn1pi);
     fChain->SetBranchAddress("truth_genie_wgt_Rvn2pi", truth_genie_wgt_Rvn2pi, &b_truth_genie_wgt_Rvn2pi);
     fChain->SetBranchAddress("truth_genie_wgt_Rvp1pi", truth_genie_wgt_Rvp1pi, &b_truth_genie_wgt_Rvp1pi);
     fChain->SetBranchAddress("truth_genie_wgt_Rvp2pi", truth_genie_wgt_Rvp2pi, &b_truth_genie_wgt_Rvp2pi);
     fChain->SetBranchAddress("truth_genie_wgt_Theta_Delta2Npi", truth_genie_wgt_Theta_Delta2Npi, &b_truth_genie_wgt_Theta_Delta2Npi);
     fChain->SetBranchAddress("truth_genie_wgt_VecFFCCQEshape", truth_genie_wgt_VecFFCCQEshape, &b_truth_genie_wgt_VecFFCCQEshape);
     fChain->SetBranchAddress("truth_genie_wgt_shifts", truth_genie_wgt_shifts, &b_truth_genie_wgt_shifts);
     //fChain->SetBranchAddress("truth_primTrajFinalP_sz", &truth_primTrajFinalP_sz, &b_truth_primTrajFinalP_sz);
     //fChain->SetBranchAddress("truth_primTrajFinalP", truth_primTrajFinalP, &b_truth_primTrajFinalP);
     //fChain->SetBranchAddress("truth_primTrajInitialP_sz", &truth_primTrajInitialP_sz, &b_truth_primTrajInitialP_sz);
     //fChain->SetBranchAddress("truth_primTrajInitialP", truth_primTrajInitialP, &b_truth_primTrajInitialP);
     //fChain->SetBranchAddress("truth_primTrajReweightPathLength_sz", &truth_primTrajReweightPathLength_sz, &b_truth_primTrajReweightPathLength_sz);
     //fChain->SetBranchAddress("truth_primTrajReweightPathLength", truth_primTrajReweightPathLength, &b_truth_primTrajReweightPathLength);
     //fChain->SetBranchAddress("truth_primTrajTotalPathLength_sz", &truth_primTrajTotalPathLength_sz, &b_truth_primTrajTotalPathLength_sz);
     //fChain->SetBranchAddress("truth_primTrajTotalPathLength", truth_primTrajTotalPathLength, &b_truth_primTrajTotalPathLength);

     fChain->SetBranchAddress("truth_hadronReweightInitialE_sz", &truth_hadronReweightInitialE_sz, &b_truth_hadronReweightInitialE_sz); // HadronReweight 2.0
     fChain->SetBranchAddress("truth_hadronReweightInitialE", &truth_hadronReweightInitialE, &b_truth_hadronReweightInitialE); // HadronReweight 2.0
     fChain->SetBranchAddress("truth_hadronReweightFinalE_sz", &truth_hadronReweightFinalE_sz, &b_truth_hadronReweightFinalE_sz); // HadronReweight 2.0
     fChain->SetBranchAddress("truth_hadronReweightFinalE", &truth_hadronReweightFinalE, &b_truth_hadronReweightFinalE); // HadronReweight 2.0
     fChain->SetBranchAddress("truth_hadronReweightInitialSigmaE_sz", &truth_hadronReweightInitialSigmaE_sz, &b_truth_hadronReweightInitialSigmaE_sz); // HadronReweight 2.0
     fChain->SetBranchAddress("truth_hadronReweightInitialSigmaE", &truth_hadronReweightInitialSigmaE, &b_truth_hadronReweightInitialSigmaE); // HadronReweight 2.0
     fChain->SetBranchAddress("truth_hadronReweightFinalSigmaE_sz", &truth_hadronReweightFinalSigmaE_sz, &b_truth_hadronReweightFinalSigmaE_sz); // HadronReweight 2.0
     fChain->SetBranchAddress("truth_hadronReweightFinalSigmaE", &truth_hadronReweightFinalSigmaE, &b_truth_hadronReweightFinalSigmaE); // HadronReweight 2.0
     fChain->SetBranchAddress("truth_hadronReweightColumnarDensity_sz", &truth_hadronReweightColumnarDensity_sz, &b_truth_hadronReweightColumnarDensity_sz); // HadronReweight 2.0
     fChain->SetBranchAddress("truth_hadronReweightColumnarDensity", &truth_hadronReweightColumnarDensity, &b_truth_hadronReweightColumnarDensity); // HadronReweight 2.0
     fChain->SetBranchAddress("truth_hadronReweightPosX_sz", &truth_hadronReweightPosX_sz, &b_truth_hadronReweightPosX_sz); // HadronReweight 2.0
     fChain->SetBranchAddress("truth_hadronReweightPosX", &truth_hadronReweightPosX, &b_truth_hadronReweightPosX); // HadronReweight 2.0
     fChain->SetBranchAddress("truth_hadronReweightPosY_sz", &truth_hadronReweightPosY_sz, &b_truth_hadronReweightPosY_sz); // HadronReweight 2.0
     fChain->SetBranchAddress("truth_hadronReweightPosY", &truth_hadronReweightPosY, &b_truth_hadronReweightPosY); // HadronReweight 2.0
     fChain->SetBranchAddress("truth_hadronReweightPosZ_sz", &truth_hadronReweightPosZ_sz, &b_truth_hadronReweightPosZ_sz); // HadronReweight 2.0
     fChain->SetBranchAddress("truth_hadronReweightPosZ", &truth_hadronReweightPosZ, &b_truth_hadronReweightPosZ); // HadronReweight 2.0

   }//end !IsData

   fChain->SetBranchAddress("CCQENu_nuFlavor", &CCQENu_nuFlavor, &b_CCQENu_nuFlavor);
   fChain->SetBranchAddress("CCQENu_nuHelicity", &CCQENu_nuHelicity, &b_CCQENu_nuHelicity);
   fChain->SetBranchAddress("CCQENu_intCurrent", &CCQENu_intCurrent, &b_CCQENu_intCurrent);
   fChain->SetBranchAddress("CCQENu_intType", &CCQENu_intType, &b_CCQENu_intType);
   fChain->SetBranchAddress("CCQENu_E", &CCQENu_E, &b_CCQENu_E);
   fChain->SetBranchAddress("CCQENu_Q2", &CCQENu_Q2, &b_CCQENu_Q2);
   fChain->SetBranchAddress("CCQENu_x", &CCQENu_x, &b_CCQENu_x);
   fChain->SetBranchAddress("CCQENu_y", &CCQENu_y, &b_CCQENu_y);
   fChain->SetBranchAddress("CCQENu_W", &CCQENu_W, &b_CCQENu_W);
   fChain->SetBranchAddress("CCQENu_score", &CCQENu_score, &b_CCQENu_score);
   fChain->SetBranchAddress("CCQENu_leptonE", CCQENu_leptonE, &b_CCQENu_leptonE);
   fChain->SetBranchAddress("CCQENu_vtx", CCQENu_vtx, &b_CCQENu_vtx);
   fChain->SetBranchAddress("CCQENu_minos_trk_is_contained", &CCQENu_minos_trk_is_contained, &b_CCQENu_minos_trk_is_contained);
   fChain->SetBranchAddress("CCQENu_minos_trk_is_ok", &CCQENu_minos_trk_is_ok, &b_CCQENu_minos_trk_is_ok);
   fChain->SetBranchAddress("CCQENu_minos_used_range", &CCQENu_minos_used_range, &b_CCQENu_minos_used_range);
   fChain->SetBranchAddress("CCQENu_minos_used_curvature", &CCQENu_minos_used_curvature, &b_CCQENu_minos_used_curvature);
   fChain->SetBranchAddress("CCQENu_minos_trk_end_plane", &CCQENu_minos_trk_end_plane, &b_CCQENu_minos_trk_end_plane);
   fChain->SetBranchAddress("CCQENu_minos_trk_quality", &CCQENu_minos_trk_quality, &b_CCQENu_minos_trk_quality);
   fChain->SetBranchAddress("CCQENu_r_minos_trk_vtx_plane", &CCQENu_r_minos_trk_vtx_plane, &b_CCQENu_r_minos_trk_vtx_plane);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_numFSMuons", &CCQENu_t_minos_trk_numFSMuons, &b_CCQENu_t_minos_trk_numFSMuons);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLeptonPDG", &CCQENu_t_minos_trk_primFSLeptonPDG, &b_CCQENu_t_minos_trk_primFSLeptonPDG);
   fChain->SetBranchAddress("CCQENu_enu_muon", &CCQENu_enu_muon, &b_CCQENu_enu_muon);
   fChain->SetBranchAddress("CCQENu_enu_proton", &CCQENu_enu_proton, &b_CCQENu_enu_proton);
   fChain->SetBranchAddress("CCQENu_minos_trk_bave", &CCQENu_minos_trk_bave, &b_CCQENu_minos_trk_bave);
   fChain->SetBranchAddress("CCQENu_minos_trk_chi2", &CCQENu_minos_trk_chi2, &b_CCQENu_minos_trk_chi2);
   fChain->SetBranchAddress("CCQENu_minos_trk_end_u", &CCQENu_minos_trk_end_u, &b_CCQENu_minos_trk_end_u);
   fChain->SetBranchAddress("CCQENu_minos_trk_end_v", &CCQENu_minos_trk_end_v, &b_CCQENu_minos_trk_end_v);
   fChain->SetBranchAddress("CCQENu_minos_trk_end_x", &CCQENu_minos_trk_end_x, &b_CCQENu_minos_trk_end_x);
   fChain->SetBranchAddress("CCQENu_minos_trk_end_y", &CCQENu_minos_trk_end_y, &b_CCQENu_minos_trk_end_y);
   fChain->SetBranchAddress("CCQENu_minos_trk_end_z", &CCQENu_minos_trk_end_z, &b_CCQENu_minos_trk_end_z);
   fChain->SetBranchAddress("CCQENu_minos_trk_eqp", &CCQENu_minos_trk_eqp, &b_CCQENu_minos_trk_eqp);
   fChain->SetBranchAddress("CCQENu_minos_trk_eqp_qp", &CCQENu_minos_trk_eqp_qp, &b_CCQENu_minos_trk_eqp_qp);
   fChain->SetBranchAddress("CCQENu_minos_trk_fit_pass", &CCQENu_minos_trk_fit_pass, &b_CCQENu_minos_trk_fit_pass);
   fChain->SetBranchAddress("CCQENu_minos_trk_ndf", &CCQENu_minos_trk_ndf, &b_CCQENu_minos_trk_ndf);
   fChain->SetBranchAddress("CCQENu_minos_trk_p", &CCQENu_minos_trk_p, &b_CCQENu_minos_trk_p);
   fChain->SetBranchAddress("CCQENu_minos_trk_p_curvature", &CCQENu_minos_trk_p_curvature, &b_CCQENu_minos_trk_p_curvature);
   fChain->SetBranchAddress("CCQENu_minos_trk_p_range", &CCQENu_minos_trk_p_range, &b_CCQENu_minos_trk_p_range);
   fChain->SetBranchAddress("CCQENu_minos_trk_qp", &CCQENu_minos_trk_qp, &b_CCQENu_minos_trk_qp);
   fChain->SetBranchAddress("CCQENu_minos_trk_vtx_x", &CCQENu_minos_trk_vtx_x, &b_CCQENu_minos_trk_vtx_x);
   fChain->SetBranchAddress("CCQENu_minos_trk_vtx_y", &CCQENu_minos_trk_vtx_y, &b_CCQENu_minos_trk_vtx_y);
   fChain->SetBranchAddress("CCQENu_minos_trk_vtx_z", &CCQENu_minos_trk_vtx_z, &b_CCQENu_minos_trk_vtx_z);
   fChain->SetBranchAddress("CCQENu_muon_E", &CCQENu_muon_E, &b_CCQENu_muon_E);
   fChain->SetBranchAddress("CCQENu_muon_P", &CCQENu_muon_P, &b_CCQENu_muon_P);
   fChain->SetBranchAddress("CCQENu_muon_T", &CCQENu_muon_T, &b_CCQENu_muon_T);
   fChain->SetBranchAddress("CCQENu_muon_score", &CCQENu_muon_score, &b_CCQENu_muon_score);
   fChain->SetBranchAddress("CCQENu_muon_theta", &CCQENu_muon_theta, &b_CCQENu_muon_theta);
   //fChain->SetBranchAddress("CCQENu_recoil_calE", &CCQENu_recoil_calE, &b_CCQENu_recoil_calE);
   fChain->SetBranchAddress("CCQENu_pion_score", &CCQENu_pion_score, &b_CCQENu_pion_score);
   fChain->SetBranchAddress("CCQENu_pion_score1", &CCQENu_pion_score1, &b_CCQENu_pion_score1);
   fChain->SetBranchAddress("CCQENu_pion_score2", &CCQENu_pion_score2, &b_CCQENu_pion_score2);
   fChain->SetBranchAddress("CCQENu_proton_E_BetheBloch_biasDown", &CCQENu_proton_E_BetheBloch_biasDown, &b_CCQENu_proton_E_BetheBloch_biasDown);
   fChain->SetBranchAddress("CCQENu_proton_E_BetheBloch_biasUp", &CCQENu_proton_E_BetheBloch_biasUp, &b_CCQENu_proton_E_BetheBloch_biasUp);
   fChain->SetBranchAddress("CCQENu_proton_E_Birks_bias", &CCQENu_proton_E_Birks_bias, &b_CCQENu_proton_E_Birks_bias);
   fChain->SetBranchAddress("CCQENu_proton_E_MEU_biasDown", &CCQENu_proton_E_MEU_biasDown, &b_CCQENu_proton_E_MEU_biasDown);
   fChain->SetBranchAddress("CCQENu_proton_E_MEU_biasUp", &CCQENu_proton_E_MEU_biasUp, &b_CCQENu_proton_E_MEU_biasUp);
   fChain->SetBranchAddress("CCQENu_proton_E_Mass_biasDown", &CCQENu_proton_E_Mass_biasDown, &b_CCQENu_proton_E_Mass_biasDown);
   fChain->SetBranchAddress("CCQENu_proton_E_Mass_biasUp", &CCQENu_proton_E_Mass_biasUp, &b_CCQENu_proton_E_Mass_biasUp);
   fChain->SetBranchAddress("CCQENu_proton_E_fromdEdx", &CCQENu_proton_E_fromdEdx, &b_CCQENu_proton_E_fromdEdx);
   fChain->SetBranchAddress("CCQENu_proton_P_fromdEdx", &CCQENu_proton_P_fromdEdx, &b_CCQENu_proton_P_fromdEdx);
   fChain->SetBranchAddress("CCQENu_proton_T_fromdEdx", &CCQENu_proton_T_fromdEdx, &b_CCQENu_proton_T_fromdEdx);
   fChain->SetBranchAddress("CCQENu_proton_calib_energy", &CCQENu_proton_calib_energy, &b_CCQENu_proton_calib_energy);
   fChain->SetBranchAddress("CCQENu_proton_score", &CCQENu_proton_score, &b_CCQENu_proton_score);
   fChain->SetBranchAddress("CCQENu_proton_score1", &CCQENu_proton_score1, &b_CCQENu_proton_score1);
   fChain->SetBranchAddress("CCQENu_proton_score1_BetheBloch_biasDown", &CCQENu_proton_score1_BetheBloch_biasDown, &b_CCQENu_proton_score1_BetheBloch_biasDown);
   fChain->SetBranchAddress("CCQENu_proton_score1_BetheBloch_biasUp", &CCQENu_proton_score1_BetheBloch_biasUp, &b_CCQENu_proton_score1_BetheBloch_biasUp);
   fChain->SetBranchAddress("CCQENu_proton_score1_Birks_bias", &CCQENu_proton_score1_Birks_bias, &b_CCQENu_proton_score1_Birks_bias);
   fChain->SetBranchAddress("CCQENu_proton_score1_MEU_biasDown", &CCQENu_proton_score1_MEU_biasDown, &b_CCQENu_proton_score1_MEU_biasDown);
   fChain->SetBranchAddress("CCQENu_proton_score1_MEU_biasUp", &CCQENu_proton_score1_MEU_biasUp, &b_CCQENu_proton_score1_MEU_biasUp);
   fChain->SetBranchAddress("CCQENu_proton_score1_Mass_biasDown", &CCQENu_proton_score1_Mass_biasDown, &b_CCQENu_proton_score1_Mass_biasDown);
   fChain->SetBranchAddress("CCQENu_proton_score1_Mass_biasUp", &CCQENu_proton_score1_Mass_biasUp, &b_CCQENu_proton_score1_Mass_biasUp);
   fChain->SetBranchAddress("CCQENu_proton_score2", &CCQENu_proton_score2, &b_CCQENu_proton_score2);
   fChain->SetBranchAddress("CCQENu_proton_theta_fromdEdx", &CCQENu_proton_theta_fromdEdx, &b_CCQENu_proton_theta_fromdEdx);
   fChain->SetBranchAddress("CCQENu_r_minos_trk_bdL", &CCQENu_r_minos_trk_bdL, &b_CCQENu_r_minos_trk_bdL);
   fChain->SetBranchAddress("CCQENu_r_minos_trk_end_dcosx", &CCQENu_r_minos_trk_end_dcosx, &b_CCQENu_r_minos_trk_end_dcosx);
   fChain->SetBranchAddress("CCQENu_r_minos_trk_end_dcosy", &CCQENu_r_minos_trk_end_dcosy, &b_CCQENu_r_minos_trk_end_dcosy);
   fChain->SetBranchAddress("CCQENu_r_minos_trk_end_dcosz", &CCQENu_r_minos_trk_end_dcosz, &b_CCQENu_r_minos_trk_end_dcosz);
   fChain->SetBranchAddress("CCQENu_r_minos_trk_vtx_dcosx", &CCQENu_r_minos_trk_vtx_dcosx, &b_CCQENu_r_minos_trk_vtx_dcosx);
   fChain->SetBranchAddress("CCQENu_r_minos_trk_vtx_dcosy", &CCQENu_r_minos_trk_vtx_dcosy, &b_CCQENu_r_minos_trk_vtx_dcosy);
   fChain->SetBranchAddress("CCQENu_r_minos_trk_vtx_dcosz", &CCQENu_r_minos_trk_vtx_dcosz, &b_CCQENu_r_minos_trk_vtx_dcosz);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLepMinosInitProjPx", &CCQENu_t_minos_trk_primFSLepMinosInitProjPx, &b_CCQENu_t_minos_trk_primFSLepMinosInitProjPx);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLepMinosInitProjPy", &CCQENu_t_minos_trk_primFSLepMinosInitProjPy, &b_CCQENu_t_minos_trk_primFSLepMinosInitProjPy);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLepMinosInitProjPz", &CCQENu_t_minos_trk_primFSLepMinosInitProjPz, &b_CCQENu_t_minos_trk_primFSLepMinosInitProjPz);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLepMinosInitProjX", &CCQENu_t_minos_trk_primFSLepMinosInitProjX, &b_CCQENu_t_minos_trk_primFSLepMinosInitProjX);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLepMinosInitProjY", &CCQENu_t_minos_trk_primFSLepMinosInitProjY, &b_CCQENu_t_minos_trk_primFSLepMinosInitProjY);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLepMinosInitProjZ", &CCQENu_t_minos_trk_primFSLepMinosInitProjZ, &b_CCQENu_t_minos_trk_primFSLepMinosInitProjZ);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLepMnvFinalPx", &CCQENu_t_minos_trk_primFSLepMnvFinalPx, &b_CCQENu_t_minos_trk_primFSLepMnvFinalPx);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLepMnvFinalPy", &CCQENu_t_minos_trk_primFSLepMnvFinalPy, &b_CCQENu_t_minos_trk_primFSLepMnvFinalPy);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLepMnvFinalPz", &CCQENu_t_minos_trk_primFSLepMnvFinalPz, &b_CCQENu_t_minos_trk_primFSLepMnvFinalPz);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLepMnvFinalX", &CCQENu_t_minos_trk_primFSLepMnvFinalX, &b_CCQENu_t_minos_trk_primFSLepMnvFinalX);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLepMnvFinalY", &CCQENu_t_minos_trk_primFSLepMnvFinalY, &b_CCQENu_t_minos_trk_primFSLepMnvFinalY);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLepMnvFinalZ", &CCQENu_t_minos_trk_primFSLepMnvFinalZ, &b_CCQENu_t_minos_trk_primFSLepMnvFinalZ);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLepMnvInitPx", &CCQENu_t_minos_trk_primFSLepMnvInitPx, &b_CCQENu_t_minos_trk_primFSLepMnvInitPx);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLepMnvInitPy", &CCQENu_t_minos_trk_primFSLepMnvInitPy, &b_CCQENu_t_minos_trk_primFSLepMnvInitPy);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLepMnvInitPz", &CCQENu_t_minos_trk_primFSLepMnvInitPz, &b_CCQENu_t_minos_trk_primFSLepMnvInitPz);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLepMnvInitX", &CCQENu_t_minos_trk_primFSLepMnvInitX, &b_CCQENu_t_minos_trk_primFSLepMnvInitX);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLepMnvInitY", &CCQENu_t_minos_trk_primFSLepMnvInitY, &b_CCQENu_t_minos_trk_primFSLepMnvInitY);
   fChain->SetBranchAddress("CCQENu_t_minos_trk_primFSLepMnvInitZ", &CCQENu_t_minos_trk_primFSLepMnvInitZ, &b_CCQENu_t_minos_trk_primFSLepMnvInitZ);
   fChain->SetBranchAddress("CCQENu_sec_protons_E_BetheBloch_biasDown_sz", &CCQENu_sec_protons_E_BetheBloch_biasDown_sz, &b_CCQENu_sec_protons_E_BetheBloch_biasDown_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_E_BetheBloch_biasDown", CCQENu_sec_protons_E_BetheBloch_biasDown, &b_CCQENu_sec_protons_E_BetheBloch_biasDown);
   fChain->SetBranchAddress("CCQENu_sec_protons_E_BetheBloch_biasUp_sz", &CCQENu_sec_protons_E_BetheBloch_biasUp_sz, &b_CCQENu_sec_protons_E_BetheBloch_biasUp_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_E_BetheBloch_biasUp", CCQENu_sec_protons_E_BetheBloch_biasUp, &b_CCQENu_sec_protons_E_BetheBloch_biasUp);
   fChain->SetBranchAddress("CCQENu_sec_protons_E_Birks_bias_sz", &CCQENu_sec_protons_E_Birks_bias_sz, &b_CCQENu_sec_protons_E_Birks_bias_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_E_Birks_bias", CCQENu_sec_protons_E_Birks_bias, &b_CCQENu_sec_protons_E_Birks_bias);
   fChain->SetBranchAddress("CCQENu_sec_protons_E_MEU_biasDown_sz", &CCQENu_sec_protons_E_MEU_biasDown_sz, &b_CCQENu_sec_protons_E_MEU_biasDown_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_E_MEU_biasDown", CCQENu_sec_protons_E_MEU_biasDown, &b_CCQENu_sec_protons_E_MEU_biasDown);
   fChain->SetBranchAddress("CCQENu_sec_protons_E_MEU_biasUp_sz", &CCQENu_sec_protons_E_MEU_biasUp_sz, &b_CCQENu_sec_protons_E_MEU_biasUp_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_E_MEU_biasUp", CCQENu_sec_protons_E_MEU_biasUp, &b_CCQENu_sec_protons_E_MEU_biasUp);
   fChain->SetBranchAddress("CCQENu_sec_protons_E_Mass_biasDown_sz", &CCQENu_sec_protons_E_Mass_biasDown_sz, &b_CCQENu_sec_protons_E_Mass_biasDown_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_E_Mass_biasDown", CCQENu_sec_protons_E_Mass_biasDown, &b_CCQENu_sec_protons_E_Mass_biasDown);
   fChain->SetBranchAddress("CCQENu_sec_protons_E_Mass_biasUp_sz", &CCQENu_sec_protons_E_Mass_biasUp_sz, &b_CCQENu_sec_protons_E_Mass_biasUp_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_E_Mass_biasUp", CCQENu_sec_protons_E_Mass_biasUp, &b_CCQENu_sec_protons_E_Mass_biasUp);
   fChain->SetBranchAddress("CCQENu_sec_protons_E_fromdEdx_sz", &CCQENu_sec_protons_E_fromdEdx_sz, &b_CCQENu_sec_protons_E_fromdEdx_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_E_fromdEdx", CCQENu_sec_protons_E_fromdEdx, &b_CCQENu_sec_protons_E_fromdEdx);
   fChain->SetBranchAddress("CCQENu_sec_protons_P_fromdEdx_sz", &CCQENu_sec_protons_P_fromdEdx_sz, &b_CCQENu_sec_protons_P_fromdEdx_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_P_fromdEdx", CCQENu_sec_protons_P_fromdEdx, &b_CCQENu_sec_protons_P_fromdEdx);
   fChain->SetBranchAddress("CCQENu_sec_protons_T_fromCalo_sz", &CCQENu_sec_protons_T_fromCalo_sz, &b_CCQENu_sec_protons_T_fromCalo_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_T_fromCalo", CCQENu_sec_protons_T_fromCalo, &b_CCQENu_sec_protons_T_fromCalo);
   fChain->SetBranchAddress("CCQENu_sec_protons_T_fromdEdx_sz", &CCQENu_sec_protons_T_fromdEdx_sz, &b_CCQENu_sec_protons_T_fromdEdx_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_T_fromdEdx", CCQENu_sec_protons_T_fromdEdx, &b_CCQENu_sec_protons_T_fromdEdx);
   fChain->SetBranchAddress("CCQENu_sec_protons_pion_scores_sz", &CCQENu_sec_protons_pion_scores_sz, &b_CCQENu_sec_protons_pion_scores_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_pion_scores", CCQENu_sec_protons_pion_scores, &b_CCQENu_sec_protons_pion_scores);
   fChain->SetBranchAddress("CCQENu_sec_protons_pion_scores1_sz", &CCQENu_sec_protons_pion_scores1_sz, &b_CCQENu_sec_protons_pion_scores1_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_pion_scores1", CCQENu_sec_protons_pion_scores1, &b_CCQENu_sec_protons_pion_scores1);
   fChain->SetBranchAddress("CCQENu_sec_protons_pion_scores2_sz", &CCQENu_sec_protons_pion_scores2_sz, &b_CCQENu_sec_protons_pion_scores2_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_pion_scores2", CCQENu_sec_protons_pion_scores2, &b_CCQENu_sec_protons_pion_scores2);
   fChain->SetBranchAddress("CCQENu_sec_protons_proton_scores_sz", &CCQENu_sec_protons_proton_scores_sz, &b_CCQENu_sec_protons_proton_scores_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_proton_scores", CCQENu_sec_protons_proton_scores, &b_CCQENu_sec_protons_proton_scores);
   fChain->SetBranchAddress("CCQENu_sec_protons_proton_scores1_sz", &CCQENu_sec_protons_proton_scores1_sz, &b_CCQENu_sec_protons_proton_scores1_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_proton_scores1", CCQENu_sec_protons_proton_scores1, &b_CCQENu_sec_protons_proton_scores1);
   fChain->SetBranchAddress("CCQENu_sec_protons_proton_scores2_sz", &CCQENu_sec_protons_proton_scores2_sz, &b_CCQENu_sec_protons_proton_scores2_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_proton_scores2", CCQENu_sec_protons_proton_scores2, &b_CCQENu_sec_protons_proton_scores2);
   fChain->SetBranchAddress("CCQENu_sec_protons_score1_BetheBloch_biasDown_sz", &CCQENu_sec_protons_score1_BetheBloch_biasDown_sz, &b_CCQENu_sec_protons_score1_BetheBloch_biasDown_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_score1_BetheBloch_biasDown", CCQENu_sec_protons_score1_BetheBloch_biasDown, &b_CCQENu_sec_protons_score1_BetheBloch_biasDown);
   fChain->SetBranchAddress("CCQENu_sec_protons_score1_BetheBloch_biasUp_sz", &CCQENu_sec_protons_score1_BetheBloch_biasUp_sz, &b_CCQENu_sec_protons_score1_BetheBloch_biasUp_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_score1_BetheBloch_biasUp", CCQENu_sec_protons_score1_BetheBloch_biasUp, &b_CCQENu_sec_protons_score1_BetheBloch_biasUp);
   fChain->SetBranchAddress("CCQENu_sec_protons_score1_Birks_bias_sz", &CCQENu_sec_protons_score1_Birks_bias_sz, &b_CCQENu_sec_protons_score1_Birks_bias_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_score1_Birks_bias", CCQENu_sec_protons_score1_Birks_bias, &b_CCQENu_sec_protons_score1_Birks_bias);
   fChain->SetBranchAddress("CCQENu_sec_protons_score1_MEU_biasDown_sz", &CCQENu_sec_protons_score1_MEU_biasDown_sz, &b_CCQENu_sec_protons_score1_MEU_biasDown_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_score1_MEU_biasDown", CCQENu_sec_protons_score1_MEU_biasDown, &b_CCQENu_sec_protons_score1_MEU_biasDown);
   fChain->SetBranchAddress("CCQENu_sec_protons_score1_MEU_biasUp_sz", &CCQENu_sec_protons_score1_MEU_biasUp_sz, &b_CCQENu_sec_protons_score1_MEU_biasUp_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_score1_MEU_biasUp", CCQENu_sec_protons_score1_MEU_biasUp, &b_CCQENu_sec_protons_score1_MEU_biasUp);
   fChain->SetBranchAddress("CCQENu_sec_protons_score1_Mass_biasDown_sz", &CCQENu_sec_protons_score1_Mass_biasDown_sz, &b_CCQENu_sec_protons_score1_Mass_biasDown_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_score1_Mass_biasDown", CCQENu_sec_protons_score1_Mass_biasDown, &b_CCQENu_sec_protons_score1_Mass_biasDown);
   fChain->SetBranchAddress("CCQENu_sec_protons_score1_Mass_biasUp_sz", &CCQENu_sec_protons_score1_Mass_biasUp_sz, &b_CCQENu_sec_protons_score1_Mass_biasUp_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_score1_Mass_biasUp", CCQENu_sec_protons_score1_Mass_biasUp, &b_CCQENu_sec_protons_score1_Mass_biasUp);
   fChain->SetBranchAddress("CCQENu_sec_protons_theta_fromdEdx_sz", &CCQENu_sec_protons_theta_fromdEdx_sz, &b_CCQENu_sec_protons_theta_fromdEdx_sz);
   fChain->SetBranchAddress("CCQENu_sec_protons_theta_fromdEdx", CCQENu_sec_protons_theta_fromdEdx, &b_CCQENu_sec_protons_theta_fromdEdx);
   fChain->SetBranchAddress("CCQENu_sys_muon_curve_energy_shift", CCQENu_sys_muon_curve_energy_shift, &b_CCQENu_sys_muon_curve_energy_shift);
   fChain->SetBranchAddress("CCQENu_sys_muon_energy_shift", CCQENu_sys_muon_energy_shift, &b_CCQENu_sys_muon_energy_shift);
   fChain->SetBranchAddress("CCQENu_sys_muon_minerva_energy_shift", CCQENu_sys_muon_minerva_energy_shift, &b_CCQENu_sys_muon_minerva_energy_shift);
   fChain->SetBranchAddress("CCQENu_sys_muon_qSquared_shift", CCQENu_sys_muon_qSquared_shift, &b_CCQENu_sys_muon_qSquared_shift);
   fChain->SetBranchAddress("CCQENu_sys_muon_range_energy_shift", CCQENu_sys_muon_range_energy_shift, &b_CCQENu_sys_muon_range_energy_shift);
   fChain->SetBranchAddress("CCQENu_sys_muon_wSquared_shift", CCQENu_sys_muon_wSquared_shift, &b_CCQENu_sys_muon_wSquared_shift);
   fChain->SetBranchAddress("CCQENu_sys_muon_xbj_shift", CCQENu_sys_muon_xbj_shift, &b_CCQENu_sys_muon_xbj_shift);
   fChain->SetBranchAddress("CCQENu_sys_muon_y_shift", CCQENu_sys_muon_y_shift, &b_CCQENu_sys_muon_y_shift);
   fChain->SetBranchAddress("CCQENu_sys_nu_energy_shift", CCQENu_sys_nu_energy_shift, &b_CCQENu_sys_nu_energy_shift);
   fChain->SetBranchAddress("CCQENu_sys_recoil_energy_shift", CCQENu_sys_recoil_energy_shift, &b_CCQENu_sys_recoil_energy_shift);
   fChain->SetBranchAddress("CCQENu_sys_recoil_qSquared_shift", CCQENu_sys_recoil_qSquared_shift, &b_CCQENu_sys_recoil_qSquared_shift);
   fChain->SetBranchAddress("CCQENu_sys_recoil_wSquared_shift", CCQENu_sys_recoil_wSquared_shift, &b_CCQENu_sys_recoil_wSquared_shift);
   fChain->SetBranchAddress("CCQENu_sys_recoil_xbj_shift", CCQENu_sys_recoil_xbj_shift, &b_CCQENu_sys_recoil_xbj_shift);
   fChain->SetBranchAddress("CCQENu_sys_recoil_y_shift", CCQENu_sys_recoil_y_shift, &b_CCQENu_sys_recoil_y_shift);
   fChain->SetBranchAddress("CCQENu_sys_total_qSquared_shift", CCQENu_sys_total_qSquared_shift, &b_CCQENu_sys_total_qSquared_shift);
   fChain->SetBranchAddress("CCQENu_sys_total_wSquared_shift", CCQENu_sys_total_wSquared_shift, &b_CCQENu_sys_total_wSquared_shift);
   fChain->SetBranchAddress("CCQENu_sys_total_xbj_shift", CCQENu_sys_total_xbj_shift, &b_CCQENu_sys_total_xbj_shift);
   fChain->SetBranchAddress("CCQENu_sys_total_y_shift", CCQENu_sys_total_y_shift, &b_CCQENu_sys_total_y_shift);
   fChain->SetBranchAddress("ev_run", &ev_run, &b_ev_run);
   fChain->SetBranchAddress("ev_subrun", &ev_subrun, &b_ev_subrun);
   fChain->SetBranchAddress("ev_detector", &ev_detector, &b_ev_detector);
   fChain->SetBranchAddress("ev_triggerType", &ev_triggerType, &b_ev_triggerType);
   fChain->SetBranchAddress("ev_gate", &ev_gate, &b_ev_gate);
   fChain->SetBranchAddress("ev_global_gate", &ev_global_gate, &b_ev_global_gate);
   fChain->SetBranchAddress("ev_gps_time_sec", &ev_gps_time_sec, &b_ev_gps_time_sec);
   fChain->SetBranchAddress("ev_gps_time_usec", &ev_gps_time_usec, &b_ev_gps_time_usec);
   if(!IsData){
     fChain->SetBranchAddress("mc_run", &mc_run, &b_mc_run);
     fChain->SetBranchAddress("mc_subrun", &mc_subrun, &b_mc_subrun);
     fChain->SetBranchAddress("mc_nInteractions", &mc_nInteractions, &b_mc_nInteractions);
     fChain->SetBranchAddress("mc_MIState", &mc_MIState, &b_mc_MIState);
     fChain->SetBranchAddress("mc_pot", &mc_pot, &b_mc_pot);
     fChain->SetBranchAddress("mc_beamConfig", &mc_beamConfig, &b_mc_beamConfig);
     fChain->SetBranchAddress("mc_processType", &mc_processType, &b_mc_processType);
     fChain->SetBranchAddress("mc_nthEvtInSpill", &mc_nthEvtInSpill, &b_mc_nthEvtInSpill);
     fChain->SetBranchAddress("mc_nthEvtInFile", &mc_nthEvtInFile, &b_mc_nthEvtInFile);
     fChain->SetBranchAddress("mc_intType", &mc_intType, &b_mc_intType);
     fChain->SetBranchAddress("mc_current", &mc_current, &b_mc_current);
     fChain->SetBranchAddress("mc_charm", &mc_charm, &b_mc_charm);
     fChain->SetBranchAddress("mc_weight", &mc_weight, &b_mc_weight);
     fChain->SetBranchAddress("mc_XSec", &mc_XSec, &b_mc_XSec);
     fChain->SetBranchAddress("mc_diffXSec", &mc_diffXSec, &b_mc_diffXSec);
     fChain->SetBranchAddress("mc_incoming", &mc_incoming, &b_mc_incoming);
     fChain->SetBranchAddress("mc_fluxDriverProb", &mc_fluxDriverProb, &b_mc_fluxDriverProb);
     fChain->SetBranchAddress("mc_targetNucleus", &mc_targetNucleus, &b_mc_targetNucleus);
     fChain->SetBranchAddress("mc_targetZ", &mc_targetZ, &b_mc_targetZ);
     fChain->SetBranchAddress("mc_targetA", &mc_targetA, &b_mc_targetA);
     fChain->SetBranchAddress("mc_targetNucleon", &mc_targetNucleon, &b_mc_targetNucleon);
     fChain->SetBranchAddress("mc_struckQuark", &mc_struckQuark, &b_mc_struckQuark);
     fChain->SetBranchAddress("mc_seaQuark", &mc_seaQuark, &b_mc_seaQuark);
     fChain->SetBranchAddress("mc_resID", &mc_resID, &b_mc_resID);
     fChain->SetBranchAddress("mc_primaryLepton", &mc_primaryLepton, &b_mc_primaryLepton);
     fChain->SetBranchAddress("mc_incomingE", &mc_incomingE, &b_mc_incomingE);
     fChain->SetBranchAddress("mc_Bjorkenx", &mc_Bjorkenx, &b_mc_Bjorkenx);
     fChain->SetBranchAddress("mc_Bjorkeny", &mc_Bjorkeny, &b_mc_Bjorkeny);
     fChain->SetBranchAddress("mc_Q2", &mc_Q2, &b_mc_Q2);
     fChain->SetBranchAddress("mc_nuT", &mc_nuT, &b_mc_nuT);
     fChain->SetBranchAddress("mc_w", &mc_w, &b_mc_w);
     fChain->SetBranchAddress("mc_vtx", mc_vtx, &b_mc_vtx);
     fChain->SetBranchAddress("mc_incomingPartVec", mc_incomingPartVec, &b_mc_incomingPartVec);
     fChain->SetBranchAddress("mc_initNucVec", mc_initNucVec, &b_mc_initNucVec);
     fChain->SetBranchAddress("mc_primFSLepton", mc_primFSLepton, &b_mc_primFSLepton);
     fChain->SetBranchAddress("mc_nFSPart", &mc_nFSPart, &b_mc_nFSPart);
     fChain->SetBranchAddress("mc_FSPartPx", mc_FSPartPx, &b_mc_FSPartPx);
     fChain->SetBranchAddress("mc_FSPartPy", mc_FSPartPy, &b_mc_FSPartPy);
     fChain->SetBranchAddress("mc_FSPartPz", mc_FSPartPz, &b_mc_FSPartPz);
     fChain->SetBranchAddress("mc_FSPartE", mc_FSPartE, &b_mc_FSPartE);
     fChain->SetBranchAddress("mc_FSPartPDG", mc_FSPartPDG, &b_mc_FSPartPDG);
     fChain->SetBranchAddress("mc_er_nPart", &mc_er_nPart, &b_mc_er_nPart);
     fChain->SetBranchAddress("mc_er_ID", mc_er_ID, &b_mc_er_ID);
     fChain->SetBranchAddress("mc_er_status", mc_er_status, &b_mc_er_status);
     fChain->SetBranchAddress("mc_er_posInNucX", mc_er_posInNucX, &b_mc_er_posInNucX);
     fChain->SetBranchAddress("mc_er_posInNucY", mc_er_posInNucY, &b_mc_er_posInNucY);
     fChain->SetBranchAddress("mc_er_posInNucZ", mc_er_posInNucZ, &b_mc_er_posInNucZ);
     fChain->SetBranchAddress("mc_er_Px", mc_er_Px, &b_mc_er_Px);
     fChain->SetBranchAddress("mc_er_Py", mc_er_Py, &b_mc_er_Py);
     fChain->SetBranchAddress("mc_er_Pz", mc_er_Pz, &b_mc_er_Pz);
     fChain->SetBranchAddress("mc_er_E", mc_er_E, &b_mc_er_E);
     fChain->SetBranchAddress("mc_er_FD", mc_er_FD, &b_mc_er_FD);
     fChain->SetBranchAddress("mc_er_LD", mc_er_LD, &b_mc_er_LD);
     fChain->SetBranchAddress("mc_er_mother", mc_er_mother, &b_mc_er_mother);
     fChain->SetBranchAddress("mc_fr_nNuAncestorIDs", &mc_fr_nNuAncestorIDs, &b_mc_fr_nNuAncestorIDs);
     fChain->SetBranchAddress("mc_fr_nuAncestorIDs", mc_fr_nuAncestorIDs, &b_mc_fr_nuAncestorIDs);
     fChain->SetBranchAddress("mc_fr_nuParentID", &mc_fr_nuParentID, &b_mc_fr_nuParentID);
     fChain->SetBranchAddress("mc_fr_decMode", &mc_fr_decMode, &b_mc_fr_decMode);
     fChain->SetBranchAddress("mc_fr_primProtonVtx", mc_fr_primProtonVtx, &b_mc_fr_primProtonVtx);
     fChain->SetBranchAddress("mc_fr_primProtonP", mc_fr_primProtonP, &b_mc_fr_primProtonP);
     fChain->SetBranchAddress("mc_fr_nuParentDecVtx", mc_fr_nuParentDecVtx, &b_mc_fr_nuParentDecVtx);
     fChain->SetBranchAddress("mc_fr_nuParentProdVtx", mc_fr_nuParentProdVtx, &b_mc_fr_nuParentProdVtx);
     fChain->SetBranchAddress("mc_fr_nuParentProdP", mc_fr_nuParentProdP, &b_mc_fr_nuParentProdP);
     fChain->SetBranchAddress("mc_cvweight_total", &mc_cvweight_total, &b_mc_cvweight_total);
     fChain->SetBranchAddress("wgt", &wgt, &b_wgt);
     fChain->SetBranchAddress("mc_cvweight_totalFlux", &mc_cvweight_totalFlux, &b_mc_cvweight_totalFlux);
     fChain->SetBranchAddress("mc_cvweight_totalXsec", &mc_cvweight_totalXsec, &b_mc_cvweight_totalXsec);
     fChain->SetBranchAddress("mc_ppfx1_cvweight", &mc_ppfx1_cvweight, &b_mc_ppfx1_cvweight);
     fChain->SetBranchAddress("mc_hornCurrent_cvweight", &mc_hornCurrent_cvweight, &b_mc_hornCurrent_cvweight);
     fChain->SetBranchAddress("mc_gen1_cvweight_total", &mc_gen1_cvweight_total, &b_mc_gen1_cvweight_total);
     fChain->SetBranchAddress("gen1_wgt", &gen1_wgt, &b_gen1_wgt);
     fChain->SetBranchAddress("mc_gen1_cvweight_totalFlux", &mc_gen1_cvweight_totalFlux, &b_mc_gen1_cvweight_totalFlux);
     fChain->SetBranchAddress("mc_gen1_cvweight_NA49", &mc_gen1_cvweight_NA49, &b_mc_gen1_cvweight_NA49);
     fChain->SetBranchAddress("mc_wgt_Flux_BeamFocus_sz", &mc_wgt_Flux_BeamFocus_sz, &b_mc_wgt_Flux_BeamFocus_sz);
     fChain->SetBranchAddress("mc_wgt_Flux_BeamFocus", mc_wgt_Flux_BeamFocus, &b_mc_wgt_Flux_BeamFocus);
     fChain->SetBranchAddress("mc_wgt_gen1_Flux_Tertiary_sz", &mc_wgt_gen1_Flux_Tertiary_sz, &b_mc_wgt_gen1_Flux_Tertiary_sz);
     fChain->SetBranchAddress("mc_wgt_gen1_Flux_Tertiary", mc_wgt_gen1_Flux_Tertiary, &b_mc_wgt_gen1_Flux_Tertiary);
     fChain->SetBranchAddress("mc_wgt_gen1_Flux_NA49_sz", &mc_wgt_gen1_Flux_NA49_sz, &b_mc_wgt_gen1_Flux_NA49_sz);
     fChain->SetBranchAddress("mc_wgt_gen1_Flux_NA49", mc_wgt_gen1_Flux_NA49, &b_mc_wgt_gen1_Flux_NA49);
     fChain->SetBranchAddress("mc_wgt_Norm_sz", &mc_wgt_Norm_sz, &b_mc_wgt_Norm_sz);
     fChain->SetBranchAddress("mc_wgt_Norm", &mc_wgt_Norm, &b_mc_wgt_Norm);
     fChain->SetBranchAddress("mc_wgt_ppfx1_Total_sz", &mc_wgt_ppfx1_Total_sz, &b_mc_wgt_ppfx1_Total_sz);
     fChain->SetBranchAddress("mc_wgt_ppfx1_Total", mc_wgt_ppfx1_Total, &b_mc_wgt_ppfx1_Total);

   fChain->SetBranchAddress("batch_structure", &batch_structure, &b_batch_structure);
   fChain->SetBranchAddress("reco_vertex_batch", &reco_vertex_batch, &b_reco_vertex_batch);
   }//end !IsData
   fChain->SetBranchAddress("n_prongs", &n_prongs, &b_n_prongs);
   fChain->SetBranchAddress("prong_nParticles", prong_nParticles, &b_prong_nParticles);
   fChain->SetBranchAddress("prong_part_score", prong_part_score, &b_prong_part_score);
   fChain->SetBranchAddress("prong_part_mass", prong_part_mass, &b_prong_part_mass);
   fChain->SetBranchAddress("prong_part_charge", prong_part_charge, &b_prong_part_charge);
   fChain->SetBranchAddress("prong_part_pid", prong_part_pid, &b_prong_part_pid);
   //   fChain->SetBranchAddress("prong_part_E", &prong_part_E, &b_prong_part_E);
   //   fChain->SetBranchAddress("prong_part_pos", &prong_part_pos, &b_prong_part_pos);
   Notify();
}

Bool_t CCQENU_ANA::CCQENuEvent::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void CCQENU_ANA::CCQENuEvent::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t CCQENU_ANA::CCQENuEvent::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

#endif // #ifdef CCQENuEvent_cxx
