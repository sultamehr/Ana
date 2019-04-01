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
$MY_CCQENU/make_hists/BlobQualityHists $CONDOR_DIR_HISTS/BlobQualityHists_minervame1A.root minervame1A 0 -1 >& $CONDOR_DIR_HISTS/BlobQualityHists-minervame1A.log
