#!/usr/env python

import os,sys,time
from optparse import OptionParser

ana_tool_location = "$MY_CCQENU"#Edit this for your specific tool location

parser = OptionParser()

parser.add_option('--outdir', dest='outdir', help='Directory to write output to', default = "%s/rootfiles/pass1_test_lats/"%(ana_tool_location))
parser.add_option('--MakeFluxConstraint', dest='MakeFluxConstraint', help='Run Flux Constraint?(default = 1)', default = "1")
parser.add_option('--ApplyFluxConstraint', dest='ApplyFluxConstraint', help='ApplyFluxConstraint? (defualt = 1)', default = "1")
#parser.add_option('--Multiplicity', dest='Multiplicity', help='Select all tracks (0), select 1 track sample (1), select N track sample (2) (default = 0)', default = "0")
parser.add_option('--BkgSample', dest='BkgSample', help='Sample for bkg templates. (default = EventSelection)', default = "EventSelection")
parser.add_option('--SelSample', dest='SelSample', help='Selection Sample. (default = Signal)', default = "Signal")
parser.add_option('--filelist', dest="filelist", help='Location of anatuple file list for flux creation', default = None)
parser.add_option("--playlist", dest="playlist", help="The playlist analyzed",default = "minerva1")
parser.add_option("--limitmc", dest="limitmc", help="Limit the number of MC files",default="-1")

#playlists = ["minerva1","minerva7","minerva9","minerva13","minerva2p2h","nonreweightables"]
playlists = ["minerva1","minerva7","minerva9","minerva13","minerva2p2h"]
machines = ["minervagpvm01","minervagpvm02","minervagpvm03","minervagpvm04","minervagpvm06","minervagpvm07"]

(opts,args) = parser.parse_args()

stages = ["MuonSelectionHists","EffPurityHists","MigrationHists","BackgroundTemplate","BackgroundWeights","ComputeFlux","CrossSectionHists"]

def runMuonSelection():
    print "Running the muon selection stage"
    cmd = "cd %s/make_hists;./MuonSelectionHists %s/MuonEventSelection_MakeFlux-%s_Multiplicity-%s_Sample-%s_%s.root %s %s %s %s %s&"%(ana_tool_location,opts.outdir,opts.MakeFluxConstraint,"1",opts.SelSample,opts.playlist,opts.playlist,opts.SelSample,opts.MakeFluxConstraint,"1",opts.limitmc)
    print cmd
    os.system(cmd)
    cmd = "cd %s/make_hists;./MuonSelectionHists %s/MuonEventSelection_MakeFlux-%s_Multiplicity-%s_Sample-%s_%s.root %s %s %s %s %s"%(ana_tool_location,opts.outdir,opts.MakeFluxConstraint,"2",opts.SelSample,opts.playlist,opts.playlist,opts.SelSample,opts.MakeFluxConstraint,"2",opts.limitmc)
    print cmd
    os.system(cmd)

def runSideBandSelection():
    print "Running the michel selection stage"
    cmd = "cd %s/make_hists;./MuonSelectionHists %s/MuonEventSelection_MakeFlux-%s_Multiplicity-%s_Sample-%s_%s.root %s %s %s %s %s&"%(ana_tool_location,opts.outdir,opts.MakeFluxConstraint,"1","MichelSideBand",opts.playlist,opts.playlist,"MichelSideBand",opts.MakeFluxConstraint,"1",opts.limitmc)
    print cmd
    os.system(cmd)
    cmd = "cd %s/make_hists;./MuonSelectionHists %s/MuonEventSelection_MakeFlux-%s_Multiplicity-%s_Sample-%s_%s.root %s %s %s %s %s"%(ana_tool_location,opts.outdir,opts.MakeFluxConstraint,"2","MichelSideBand",opts.playlist,opts.playlist,"MichelSideBand",opts.MakeFluxConstraint,"2",opts.limitmc)
    print cmd
    os.system(cmd)

    print "Running the blob selection stage"
    cmd = "cd %s/make_hists;./MuonSelectionHists %s/MuonEventSelection_MakeFlux-%s_Multiplicity-%s_Sample-%s_%s.root %s %s %s %s %s&"%(ana_tool_location,opts.outdir,opts.MakeFluxConstraint,"1","BlobSideBand",opts.playlist,opts.playlist,"BlobSideBand",opts.MakeFluxConstraint,"1",opts.limitmc)
    print cmd
    os.system(cmd)
    cmd = "cd %s/make_hists;./MuonSelectionHists %s/MuonEventSelection_MakeFlux-%s_Multiplicity-%s_Sample-%s_%s.root %s %s %s %s %s"%(ana_tool_location,opts.outdir,opts.MakeFluxConstraint,"2","BlobSideBand",opts.playlist,opts.playlist,"BlobSideBand",opts.MakeFluxConstraint,"2",opts.limitmc)
    print cmd
    os.system(cmd)

def runApplyFluxConstraint():
    print "Running the flux constraint stage"
    cmd = "cd %s/make_hists;./ApplyFluxConstraint %s/MuonEventSelection_MakeFlux-%s_Multiplicity-%s_Sample-%s_%s.root %s/MuonEventSelection_MakeFlux-%s_Multiplicity-%s_Sample-%s_FluxConstrained_%s.root %s 1"%(ana_tool_location,opts.outdir,opts.MakeFluxConstraint,"1",opts.SelSample,opts.playlist,opts.outdir,opts.MakeFluxConstraint,"1",opts.SelSample,opts.playlist,opts.playlist)
    print cmd
    os.system(cmd)

    cmd = "cd %s/make_hists;./ApplyFluxConstraint %s/MuonEventSelection_MakeFlux-%s_Multiplicity-%s_Sample-%s_%s.root %s/MuonEventSelection_MakeFlux-%s_Multiplicity-%s_Sample-%s_FluxConstrained_%s.root %s 1"%(ana_tool_location,opts.outdir,opts.MakeFluxConstraint,"2",opts.SelSample,opts.playlist,opts.outdir,opts.MakeFluxConstraint,"2",opts.SelSample,opts.playlist,opts.playlist)
    print cmd
    os.system(cmd)
#blobs
    cmd = "cd %s/make_hists;./ApplyFluxConstraint %s/MuonEventSelection_MakeFlux-%s_Multiplicity-%s_Sample-%s_%s.root %s/MuonEventSelection_MakeFlux-%s_Multiplicity-%s_Sample-%s_FluxConstrained_%s.root %s 1"%(ana_tool_location,opts.outdir,opts.MakeFluxConstraint,"1","BlobSideBand",opts.playlist,opts.outdir,opts.MakeFluxConstraint,"1","BlobSideBand",opts.playlist,opts.playlist)
    print cmd
    os.system(cmd)

    cmd = "cd %s/make_hists;./ApplyFluxConstraint %s/MuonEventSelection_MakeFlux-%s_Multiplicity-%s_Sample-%s_%s.root %s/MuonEventSelection_MakeFlux-%s_Multiplicity-%s_Sample-%s_FluxConstrained_%s.root %s 1"%(ana_tool_location,opts.outdir,opts.MakeFluxConstraint,"2","BlobSideBand",opts.playlist,opts.outdir,opts.MakeFluxConstraint,"2","BlobSideBand",opts.playlist,opts.playlist)
    print cmd
    os.system(cmd)
#michel
    cmd = "cd %s/make_hists;./ApplyFluxConstraint %s/MuonEventSelection_MakeFlux-%s_Multiplicity-%s_Sample-%s_%s.root %s/MuonEventSelection_MakeFlux-%s_Multiplicity-%s_Sample-%s_FluxConstrained_%s.root %s 1"%(ana_tool_location,opts.outdir,opts.MakeFluxConstraint,"1","MichelSideBand",opts.playlist,opts.outdir,opts.MakeFluxConstraint,"1","MichelSideBand",opts.playlist,opts.playlist)
    print cmd
    os.system(cmd)

    cmd = "cd %s/make_hists;./ApplyFluxConstraint %s/MuonEventSelection_MakeFlux-%s_Multiplicity-%s_Sample-%s_%s.root %s/MuonEventSelection_MakeFlux-%s_Multiplicity-%s_Sample-%s_FluxConstrained_%s.root %s 1"%(ana_tool_location,opts.outdir,opts.MakeFluxConstraint,"2","MichelSideBand",opts.playlist,opts.outdir,opts.MakeFluxConstraint,"2","MichelSideBand",opts.playlist,opts.playlist)
    print cmd
    os.system(cmd)

def runEffPurity():
    print "Running the efficiency purity stage"
    cmd = "cd %s/make_hists;./EffPurityHists %s/EffPurity_MakeFlux-%s_%s.root %s %s %s %s"%(ana_tool_location,opts.outdir,opts.MakeFluxConstraint,opts.playlist,opts.playlist,opts.MakeFluxConstraint,opts.ApplyFluxConstraint,opts.limitmc)
    print cmd
    os.system(cmd)

def runMigration():
    print "Running the migration stage"
    cmd = "cd %s/make_hists;./MigrationMatrixHists %s/Migration_MakeFlux-%s_ApplyFlux-%s_Multiplicity-%s_%s.root %s %s %s %s %s"%(ana_tool_location,opts.outdir,opts.MakeFluxConstraint,opts.ApplyFluxConstraint,"0",opts.playlist,opts.playlist,opts.MakeFluxConstraint,opts.ApplyFluxConstraint,"0",opts.limitmc)
    print cmd
    os.system(cmd)

def runBackgroundTemplate():
    print "Running the background template"
    cmd = "cd %s/background_tuning;./BackgroundTemplates %s/BackgroundTemplates_Sample-%s_MakeFlux-%s_ApplyFlux-%s_%s.root %s %s %s %s "%(ana_tool_location,opts.outdir,"EventSelection",opts.MakeFluxConstraint,opts.ApplyFluxConstraint,opts.playlist,opts.playlist,"EventSelection",opts.MakeFluxConstraint,opts.ApplyFluxConstraint)
    print cmd
    os.system(cmd)

def runBackgroundWeights():
    print "Running the background weights"   
    cmd = "cd %s/background_tuning;./BackgroundWeights %s/BackgroundTemplates_Sample-%s_MakeFlux-%s_ApplyFlux-%s_%s.root %s/BackgroundWeights_Sample-%s_MakeFlux-%s_ApplyFlux-%s_%s.root"%(ana_tool_location,opts.outdir,"EventSelection",opts.MakeFluxConstraint,opts.ApplyFluxConstraint,opts.playlist,opts.outdir,"EventSelection",opts.MakeFluxConstraint,opts.ApplyFluxConstraint,opts.playlist)
    print cmd
    os.system(cmd)

def runComputeFlux():
    print "Running compute flux"
    cmd = "cd %s/../Flux/python;python compute_flux.py --filelist %s --mean_pot_per_file 1E17 -o %s/Flux_Output_%s_%s.root"%(opts.filelist,opts.outdir,os.path.basename(opts.filelist))
    print cmd
    os.system(cmd)

def runCrossSection():
    print "Running cross section extaction"

def runRecoilTemplate():
    print "Running the recoil template"
    cmd = "cd %s/background_tuning;./RecoilTemplates %s/RecoilTemplates_Sample-%s_MakeFlux-%s_ApplyFlux-%s_%s.root %s %s %s %s "%(ana_tool_location,opts.outdir,"EventSelection",opts.MakeFluxConstraint,opts.ApplyFluxConstraint,opts.playlist,opts.playlist,"EventSelection",opts.MakeFluxConstraint,opts.ApplyFluxConstraint)
    print cmd
    os.system(cmd)

def runBlobtests():
    if(opts.playlist=="nonreweightables"):
        return
    print "Running Blob tests"
    cmd = "cd %s/make_hists;./BlobQualityHists %s/Blobs_signal_%s_%s.root %s %s %s"%(ana_tool_location,opts.outdir,"1",opts.playlist,opts.playlist,"1",opts.limitmc)
    os.system(cmd)
    cmd = "cd %s/make_hists;./BlobQualityHists %s/Blobs_signal_%s_%s.root %s %s %s"%(ana_tool_location,opts.outdir,"2",opts.playlist,opts.playlist,"2",opts.limitmc)
    os.system(cmd)

def runMicheltests():
    if(opts.playlist=="nonreweightables"):
        return
    print "Running Michel tests"
    cmd = "cd %s/make_hists;./MichelQualityHists %s/Michels_signal_%s_%s.root %s %s %s"%(ana_tool_location,opts.outdir,"1",opts.playlist,opts.playlist,"1",opts.limitmc)
    os.system(cmd)
    cmd = "cd %s/make_hists;./MichelQualityHists %s/Michels_signal_%s_%s.root %s %s %s"%(ana_tool_location,opts.outdir,"2",opts.playlist,opts.playlist,"2",opts.limitmc)
    os.system(cmd)

    cmd = "cd %s/make_hists;./MichelQualityHistsImproved %s/ImprovedMichels_signal_%s_%s.root %s %s %s"%(ana_tool_location,opts.outdir,"1",opts.playlist,opts.playlist,"1",opts.limitmc)
    os.system(cmd)
    cmd = "cd %s/make_hists;./MichelQualityHistsImproved %s/ImprovedMichels_signal_%s_%s.root %s %s %s"%(ana_tool_location,opts.outdir,"2",opts.playlist,opts.playlist,"2",opts.limitmc)
    os.system(cmd)



if opts.playlist.lower() != "all":
##This is how to run a full analysis
    runMuonSelection()
    runSideBandSelection()
#    runApplyFluxConstraint() # NOT NEEDED ANYMORE old flux constraint method
    runEffPurity()
    runMigration()
#    runBackgroundTemplate()#old constraint method
#    runBackgroundWeights()#old constraint method
#    runRecoilTemplate()#Old fit code
#    runBlobtests()
#    runMicheltests()
else:
    for i,pl in enumerate(playlists):
        opts.playlist = pl
        print opts.playlist
        cmd = "ssh %s 'python RunCCQENu.py --playlist %s --limitmc %s'&"%(machines[i],opts.playlist,opts.limitmc)
        print cmd
        os.system(cmd)
        time.sleep(10)
    
os.system("echo 'CCQENU Processing done for %s'|mail -s 'CCQENU Processing done' $USER@fnal.gov"%opts.playlist)
