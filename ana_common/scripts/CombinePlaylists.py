
import os,sys

#names = [#"BackgroundTemplates_Sample-EventSelection_MakeFlux-1_ApplyFlux-1_",
#names=["EffPurity_MakeFlux-1_",
#names=["MigrationMatrix_FluxConst_q2_"]
#       "Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-0_"]
names = ["MuonEventSelection_MakeFlux-1_Multiplicity-1_Sample-Signal_",
         "MuonEventSelection_MakeFlux-1_Multiplicity-2_Sample-Signal_",
         "MuonEventSelection_MakeFlux-1_Multiplicity-0_Sample-Signal_",
         "MuonEventSelection_MakeFlux-1_Multiplicity-1_Sample-MichelSideBand_",
         "MuonEventSelection_MakeFlux-1_Multiplicity-2_Sample-MichelSideBand_",
         "MuonEventSelection_MakeFlux-1_Multiplicity-0_Sample-MichelSideBand_",
         "MuonEventSelection_MakeFlux-1_Multiplicity-1_Sample-MicBlobSideBand_",
         "MuonEventSelection_MakeFlux-1_Multiplicity-2_Sample-MicBlobSideBand_",
         "MuonEventSelection_MakeFlux-1_Multiplicity-0_Sample-MicBlobSideBand_",
         "MuonEventSelection_MakeFlux-1_Multiplicity-1_Sample-BlobSideBand_",
         "MuonEventSelection_MakeFlux-1_Multiplicity-2_Sample-BlobSideBand_",
         "MuonEventSelection_MakeFlux-1_Multiplicity-0_Sample-BlobSideBand_",
         "BlobQualityHists_",
#         "Blobs_signal_2_",
         "MichelQualityHistsImproved_",
#         "Michels_signal_2_",
         "EffPurity_MakeFlux-1_",
         "Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-0_"]
         #"RecoilTemplates_Sample-EventSelection_MakeFlux-1_ApplyFlux-1_"]
#names = ["MuonEventSelection_MakeFlux-1_Multiplicity-1_Sample-MichelSideBand_FluxConstrained_",
#         "MuonEventSelection_MakeFlux-1_Multiplicity-2_Sample-MichelSideBand_FluxConstrained_"]
dirname = sys.argv[1]
#nonreweightables
for name in names:
    stage = name.split("_")[0]
    if(stage=="RecoilTemplates"):
        stage = "BackgroundTemplates"
    if(stage=="MigrationMatrix"):
        stage = "Migration"
    if(stage=="BlobsQualityHists" or stage=="MichelsQualityHistsImproved"):
        stage = "MuonEventSelection"
#    os.system("$MY_CCQENU/make_hists/PlaylistAdder %s/%s %s 0 minervanonreweightables"%(dirname,name,stage))
#    raw_input("Hit enter to continue. Stage run is: %s"%stage)
    print "mv %s/%sCombinedPlaylists.root %s/%sCombinedPlaylistsNonReweightables.root"%(dirname,name,dirname,name)
#    os.system("mv %s/%sCombinedPlaylists.root %s/%sCombinedPlaylistsNonReweightables.root"%(dirname,name,dirname,name))
#Now do the nonreweightsables which is effectively modified minerva13 + 2p2h. Output defaults to specialsampleincluded. So, need to modify that
for name in names:
    stage = name.split("_")[0]
    if(stage=="RecoilTemplates"):
        stage = "BackgroundTemplates"
    if(stage=="MigrationMatrix"):
        stage = "Migration"
    if(stage=="BlobsQualityHists" or stage=="MichelsQualityHistsImproved"):
        stage = "MuonEventSelection"
#    os.system("$MY_CCQENU/make_hists/PlaylistAdder %s/%s %s 1 CombinedPlaylistsNonReweightables minerva2p2h"%(dirname,name,stage))
    print "mv %s/%sSpecialSampleIncluded.root %s/%sSpecialSampleIncludedNonReweightables"%(dirname,name,dirname,name)
#    os.system("mv %s/%sSpecialSampleIncluded.root %s/%sSpecialSampleIncludedNonReweightables.root"%(dirname,name,dirname,name))
    



for name in names:
    stage = name.split("_")[0]
    print stage
    if(stage=="RecoilTemplates"):
        stage = "BackgroundTemplates"
    if(stage=="MigrationMatrix"):
        stage = "Migration"
    if(stage=="BlobQualityHists" or stage=="MichelQualityHistsImproved"):
        stage = "MuonEventSelection"
    print "$MY_CCQENU/make_hists/PlaylistAdder %s/%s %s 0 minerva1 minerva7 minerva9 minerva13"%(dirname,name,stage)
    os.system("$MY_CCQENU/make_hists/PlaylistAdder %s/%s %s 0 minerva1 minerva7 minerva9 minerva13"%(dirname,name,stage))


#sys.exit("Not adding 2p2h")
#add _CombinedPlaylists
for name in names:
    stage = name.split("_")[0]
    if(stage=="RecoilTemplates"):
        stage = "BackgroundTemplates"
    if(stage=="MigrationMatrix"):
        stage = "Migration"
    if(stage=="BlobQualityHists" or stage=="MichelQualityHistsImproved"):
        stage = "MuonEventSelection"
    os.system("$MY_CCQENU/make_hists/PlaylistAdder %s/%s %s 1 CombinedPlaylists minerva2p2h"%(dirname,name,stage))


