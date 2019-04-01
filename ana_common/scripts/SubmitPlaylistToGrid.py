import os,sys,time
from optparse import OptionParser

def createTarball(outdir,tag):
    tooldir = os.environ["CCQENUROOT"]
    basedir = "%s/../../"%(tooldir)
    found = os.path.isfile("%s/myareatar_%s.tar.gz"%(outdir,tag))
    if(not found):
        cmd = "tar -czf /minerva/app/users/$USER/myareatar_%s.tar.gz %s"%(tag,basedir)
        print "Making tar",cmd
        os.system(cmd)
        cmd2 = "cp /minerva/app/users/$USER/myareatar_%s.tar.gz %s/"%(tag,outdir)
        print "Copying tar",cmd2
        os.system(cmd2)

def writeTarballProceedure(mywrapper,tag):
    #some uh magic to get the my_ccqenu setup using the submission setup... otherwise we don't know which one to setup on the grid node...
    myccqenu = os.environ["MY_CCQENU"]
    myversion = myccqenu.split("/")[-2]#Count from the end and skip the ana.
    print "I will be making the tarball upacking with this version"
    mywrapper.write("cd $CONDOR_DIR_INPUT\n")
    mywrapper.write("tar -xvzf myareatar_%s.tar.gz\n"%tag)
    mywrapper.write("cd Tools/ProductionScripts/cmt\n")
    mywrapper.write("cmt config\n")
    mywrapper.write("source setup.sh\n")
    mywrapper.write("cd $CONDOR_DIR_INPUT\n")
    mywrapper.write("cd Ana/CCQENu/cmt/ \n")
    mywrapper.write("cmt config\n")
    mywrapper.write("source setup.sh\n")
    mywrapper.write("cd ../../%s/cmt/\n"%myversion)
    mywrapper.write("cmt config\n")
    mywrapper.write("source setup.sh\n")
    mywrapper.write("export LD_LIBRARY_PATH=$CCQENUROOT/ana_common/src:$LD_LIBRARY_PATH\n")
    #need to kill and relink our main so
#    mywrapper.write("rm $CCQENU_ANA/lib/libCCQENU.so\n")
#    mywrapper.write("ln -s $CCQENU_ANA/src/libCCQENU.so $CCQENU_ANA/lib/\n")
    mywrapper.write("cd $_CONDOR_SCRATCH_DIR\n")#go back home...


#This script will submit the CCQENu processing to the grid. 
#Output will need to land on dCache
#Need to create new directories each time

#options I need
#stage,multiplicity,sample
valid_stages = ["MuonSelectionHists","ProtonSelectionHists","MigrationMatrixHists","EffPurityHists","MichelQualityHistsImproved","ProtonEfficiencyStudy"]
valid_samples = ["Signal","MichelSideBand","BlobSideBand","MicBlobSideBand"]
valid_multiplicity = ["0","1","2"]
parser = OptionParser()
parser.add_option('--outdir', dest='outdir', help='Directory to write output to', default = "/pnfs/minerva/persistent/users/drut1186/default_analysis_loc/")
parser.add_option('--stage', dest='stage', help='Process type', default="NONE")
parser.add_option('--sample', dest='sample', help='Sample type', default="NONE")
parser.add_option('--playlist', dest='playlist', help='Playlist type', default="NONE")
parser.add_option('--multiplicity', dest='multiplicity', help='Track Multiplicity', default="0")
parser.add_option('--limitmc', dest='limitmc', help='Limit number of mc files', default="-1")
parser.add_option('--limitdata', dest='limitdata', help='Limit number of data files', default="-1")
parser.add_option('--iterations', dest='iterations', help="How many unfolding iterations", default="4")
#configuration options
#pion tune, rpa, 2p2h tune (Phil tune), res rpa nieves, res rpa minos
parser.add_option('--piontune', dest='piontune', help='Do non-res pion tune', default=False, action="store_true")
parser.add_option('--rpa', dest='rpa', help='Do CCQE RPA tune', default=False, action="store_true")
parser.add_option('--2p2h', dest='do2p2h', help='Do 2p2h Phil tune', default=False, action="store_true")
parser.add_option('--resrpanieves', dest='resrpanieves', help='Do rpa on resonant pion, Nieves', default=False, action="store_true")
parser.add_option('--resrpaminos', dest='resrpaminos', help='Do rpa on resonant pion, MINOS', default=False, action="store_true")
parser.add_option('--tag', dest='tag', help="Tag your release",default="default")

(opts,args) = parser.parse_args()

if opts.stage not in valid_stages:
    print "Selected stage is not valid. Here are the valid options",valid_stages

if opts.sample not in valid_samples:
    print "Selected sample is not valid. Here are the valid options",valid_samples

if opts.multiplicity not in valid_multiplicity:
    print "Selected multiplicity is not valid. Here are the valid options",valid_multiplicity

if(not os.path.isdir(opts.outdir)):
    os.mkdir(opts.outdir)

memory = 2000
if(opts.stage=="MigrationMatrixHists"):
    memory = 7500
if(opts.stage=="MuonSelectionHists"):
    memory = 3900
if(opts.stage=="ProtonSelectionHists"):
    memory = 3900
#Create wrapper
wrapper_name = "%s_%s_wrapper.sh"%(opts.stage,opts.playlist)
my_wrapper = open(wrapper_name,"w")
my_wrapper.write("#!/bin/sh\n")

createTarball(opts.outdir,opts.tag)
#this will unpack the tarball we just made above
writeTarballProceedure(my_wrapper,opts.tag)

if(opts.stage=="MuonSelectionHists"):
    my_wrapper.write("$MY_CCQENU/make_hists/MuonSelectionHists $CONDOR_DIR_HISTS/MuonEventSelection_MakeFlux-1_Multiplicity-%s_Sample-%s_%s.root %s %s %s %s %s %s >& $CONDOR_DIR_HISTS/MuonEventSelection_MakeFlux-1_Multiplicity-%s_Sample-%s_%s.log\n"%(opts.multiplicity,opts.sample,opts.playlist,opts.playlist,opts.sample,"1",opts.multiplicity,opts.limitmc,opts.limitdata,opts.multiplicity,opts.sample,opts.playlist))

if(opts.stage=="ProtonEfficiencyStudy"):
    my_wrapper.write("$MY_CCQENU/make_hists/ProtonEfficiencyStudy $CONDOR_DIR_HISTS/ProtonEfficiencyStudy_%s.root %s >& $CONDOR_DIR_HISTS/ProtonEfficiencyStudy_%s.log\n"%(opts.playlist,opts.playlist,opts.playlist))

if(opts.stage=="ProtonSelectionHists"):
    my_wrapper.write("$MY_CCQENU/make_hists/ProtonSelectionHists $CONDOR_DIR_HISTS/ProtonEventSelection_MakeFlux-1_Multiplicity-%s_Sample-%s_%s.root %s %s %s %s %s %s >& $CONDOR_DIR_HISTS/ProtonEventSelection_MakeFlux-1_Multiplicity-%s_Sample-%s_%s.log\n"%(opts.multiplicity,opts.sample,opts.playlist,opts.playlist,opts.sample,"1",opts.multiplicity,opts.limitmc,opts.limitdata,opts.multiplicity,opts.sample,opts.playlist))

if(opts.stage=="MigrationMatrixHists"):
    my_wrapper.write("$MY_CCQENU/make_hists/MigrationMatrixHists $CONDOR_DIR_HISTS/Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-%s_pzmu_%s.root %s %s %s %s pzmu %s >& $CONDOR_DIR_HISTS/Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-%s_pzmu_%s.log\n"%(opts.multiplicity,opts.playlist,opts.playlist,"1","1",opts.multiplicity,opts.limitmc,opts.multiplicity,opts.playlist))
    my_wrapper.write("$MY_CCQENU/make_hists/MigrationMatrixHists $CONDOR_DIR_HISTS/Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-%s_q2_%s.root %s %s %s %s q2 %s >& $CONDOR_DIR_HISTS/Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-%s_q2_%s.log\n"%(opts.multiplicity,opts.playlist,opts.playlist,"1","1",opts.multiplicity,opts.limitmc,opts.multiplicity,opts.playlist))
    my_wrapper.write("$MY_CCQENU/make_hists/MigrationMatrixHists $CONDOR_DIR_HISTS/Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-%s_enu_%s.root %s %s %s %s enu %s >& $CONDOR_DIR_HISTS/Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-%s_enu_%s.log\n"%(opts.multiplicity,opts.playlist,opts.playlist,"1","1",opts.multiplicity,opts.limitmc,opts.multiplicity,opts.playlist))

if(opts.stage=="EffPurityHists"):
    my_wrapper.write("$MY_CCQENU/make_hists/EffPurityHists $CONDOR_DIR_HISTS/EffPurity_MakeFlux-1_%s.root %s %s %s %s >& $CONDOR_DIR_HISTS/EffPurity_MakeFlux-1_%s.log\n"%(opts.playlist,opts.playlist,"1","1",opts.limitmc,opts.playlist))
if(opts.stage=="MichelQualityHistsImproved"):
    my_wrapper.write("$MY_CCQENU/make_hists/MichelQualityHistsImproved $CONDOR_DIR_HISTS/MichelQualityHistsImproved_%s.root %s 0 %s >& $CONDOR_DIR_HISTS/MichelQualityHistsImproved-%s.log\n"%(opts.playlist,opts.playlist,opts.limitmc,opts.playlist))
if(opts.stage=="BlobQualityHists"):
    my_wrapper.write("$MY_CCQENU/make_hists/BlobQualityHists $CONDOR_DIR_HISTS/BlobQualityHists_%s.root %s 0 %s >& $CONDOR_DIR_HISTS/BlobQualityHists-%s.log\n"%(opts.playlist,opts.playlist,opts.limitmc,opts.playlist))
my_wrapper.close()
os.system("chmod 777 %s"%(wrapper_name))
configstring = ""
if(opts.piontune):
    configstring+=" -e DOPIONTUNE "
    os.environ["DOPIONTUNE"]="1"

if(opts.rpa):
    configstring+=" -e DOCCQEPRA "
    os.environ["DOCCQEPRA"]="1"

if(opts.do2p2h):
    configstring+=" -e DO2P2HTUNE "
    os.environ["DO2P2HTUNE"] = "1"

if(opts.resrpanieves):
    configstring+=" -e DORPARESNIEVES "
    os.environ["DORPARESNIEVES"] = "1"

if(opts.resrpaminos):
    configstring+=" -e DORPARESMINOS "
    os.environ["DORPARESMINOS"] ="1"


mnvRelease = os.environ["MINERVA_RELEASE"]
mnvRelease = mnvRelease[ :3]
print mnvRelease
if(mnvRelease == "v10" ):
    gccstring= "x86_64-slc6-gcc44-opt"
if(mnvRelease == "v20" or mnvRelease=="v21"):
    gccstring= "x86_64-slc6-gcc49-opt"

cmd = "jobsub_submit --group=minerva --cmtconfig %s -M --OS=SL6 --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC --role=Analysis --subgroup=Nightly --expected-lifetime 24h --memory %dMB %s -f %s/myareatar_%s.tar.gz -d HISTS %s -r %s -i /cvmfs/minerva.opensciencegrid.org/minerva/software_releases/%s  file://%s/%s"%(gccstring,memory,configstring,opts.outdir,opts.tag,opts.outdir,os.environ["MINERVA_RELEASE"],os.environ["MINERVA_RELEASE"],os.environ["PWD"],wrapper_name)
print cmd
os.system(cmd)
print "Sleeping"
time.sleep(10)
