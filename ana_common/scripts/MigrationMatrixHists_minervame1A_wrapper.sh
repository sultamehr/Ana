#!/bin/sh
cd $CONDOR_DIR_INPUT
tar -xvzf myareatar_default.tar.gz
cd Tools/ProductionScripts/cmt
cmt config
source setup.sh
cd $CONDOR_DIR_INPUT
cd Ana/CCQENu/cmt/ 
cmt config
source setup.sh
cd ../../CCQENu1DME/cmt/
cmt config
source setup.sh
export LD_LIBRARY_PATH=$CCQENUROOT/ana_common/src:$LD_LIBRARY_PATH
cd $_CONDOR_SCRATCH_DIR
$MY_CCQENU/make_hists/MigrationMatrixHists $CONDOR_DIR_HISTS/Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-0_pzmu_minervame1A.root minervame1A 1 1 0 pzmu -1 >& $CONDOR_DIR_HISTS/Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-0_pzmu_minervame1A.log
$MY_CCQENU/make_hists/MigrationMatrixHists $CONDOR_DIR_HISTS/Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-0_q2_minervame1A.root minervame1A 1 1 0 q2 -1 >& $CONDOR_DIR_HISTS/Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-0_q2_minervame1A.log
$MY_CCQENU/make_hists/MigrationMatrixHists $CONDOR_DIR_HISTS/Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-0_enu_minervame1A.root minervame1A 1 1 0 enu -1 >& $CONDOR_DIR_HISTS/Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-0_enu_minervame1A.log
