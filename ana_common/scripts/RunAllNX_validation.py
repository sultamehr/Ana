import os,sys

#MuonSelection Configs
selection_samples = ["Signal","MichelSideBand","BlobSideBand","MicBlobSideBand"]
selection_multiplicity = ["0","1","2"]

#MigrationMatrix Configs
mig_multiplicity = ["0"]

#EffPurity Configs
eff_multiplicity = ["0"]


#playlists
playlists = ["minervame1A","minervame1F","minervame1L"]
#playlists = ["minervame1A","minervame1B","minervame1C","minervame1D","minervame1E","minervame1F","minervame1G","minervame1L","minervame1A2p2h","minervame1B2p2h","minervame1C2p2h","minervame1D2p2h","minervame1E2p2h","minervame1F2p2h","minervame1G2p2h","minervame1L2p2h"]


###############################
###############################
outdir = sys.argv[1]

if(os.path.isdir(outdir)):
    sys.exit("This output directory exists. Use a new one.")

#submit MichelQualityHistsImproved
for pl in playlists:
    cmd = "python SubmitPlaylistToGrid.py --outdir %s --stage %s --playlist %s --limitmc -1"%(outdir,"MichelQualityHistsImproved",pl)
    print cmd
    os.system(cmd)

##submit BlobQualityHists
#for pl in playlists:
#    cmd = "python SubmitPlaylistToGrid.py --outdir %s --stage %s --playlist %s --limitmc -1"%(outdir,"BlobQualityHists",pl)
#    print cmd
#    os.system(cmd)

#Submit ProtonSelectionHists
for sam in selection_samples:
        for pl in playlists:
            cmd = "python SubmitPlaylistToGrid.py --outdir %s --stage %s --sample %s --playlist %s --multiplicity 2 --limitmc -1"%(outdir,"ProtonSelectionHists",sam,pl)
            print cmd
            os.system(cmd)

#Submit MuonSelection
for sam in selection_samples:
    for mul in selection_multiplicity:
        for pl in playlists:
            cmd = "python SubmitPlaylistToGrid.py --outdir %s --stage %s --sample %s --playlist %s --multiplicity %s --limitmc -1"%(outdir,"MuonSelectionHists",sam,pl,mul)
            print cmd
            os.system(cmd)

#Submit Efficiency
for mul in eff_multiplicity:
    for pl in playlists:
        cmd = "python SubmitPlaylistToGrid.py --outdir %s --stage %s --playlist %s --multiplicity %s --limitmc -1"%(outdir,"EffPurityHists",pl,mul)
        print cmd
        os.system(cmd)

#Submit Migration
for mul in mig_multiplicity:
    for pl in playlists:
        cmd = "python SubmitPlaylistToGrid.py --outdir %s --stage %s --playlist %s --multiplicity %s --limitmc -1"%(outdir,"MigrationMatrixHists",pl,mul)
        print cmd
        os.system(cmd)
