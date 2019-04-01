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
$MY_CCQENU/make_hists/MuonSelectionHists $CONDOR_DIR_HISTS/MuonEventSelection_MakeFlux-1_Multiplicity-2_Sample-MicBlobSideBand_minervame1A.root minervame1A MicBlobSideBand 1 2 -1 -1 >& $CONDOR_DIR_HISTS/MuonEventSelection_MakeFlux-1_Multiplicity-2_Sample-MicBlobSideBand_minervame1A.log
