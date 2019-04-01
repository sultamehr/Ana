import os,sys

#MuonSelection Configs
selection_samples = ["Signal","MichelSideBand","BlobSideBand","MicBlobSideBand"]
selection_multiplicity = ["0","1","2"]

#MigrationMatrix Configs
mig_multiplicity = ["0"]

#EffPurity Configs
eff_multiplicity = ["0"]


#playlists
playlists = ["minervame1A"]

#configurations
config ={}
config["default"]= ""
config["pion"]=" --piontune "
config["pionrpa"]= " --piontune --rpa "
config["pion2p2h"]= " --piontune --2p2h "
config["CV"]=" --piontune --2p2h --rpa "
config["CVResPionNieves"]=" --piontune --2p2h --rpa --resrpanieves "
config["CVResPionMINOS"]=" --piontune --2p2h --rpa --resrpaminos "


###############################
###############################
outdir = sys.argv[1]
if(outdir[-1:]=="/"):
    print "Removing trailing /"
    outdir = outdir.rstrip("/")


#if(os.path.isdir(outdir)):
#    sys.exit("This output directory exists. Use a new one.")
#submit MichelQualityHistsImproved
for key in config.keys():
#    if(key!="CV"):
#        continue
    print "I'm working on",key
    outdir_key = outdir
    if(key=="default"):
        outdir_key = outdir_key+"_default"
    elif(key=="pion"):
        outdir_key = outdir_key+"_piontune"
    elif(key=="pionrpa"):
        outdir_key = outdir_key+"_pion_rpa"
    elif(key=="pion2p2h"):
        outdir_key = outdir_key+"_pion_2p2h"
    elif(key=="CV"):
        outdir_key = outdir_key+"_CV"
    elif(key=="CVResPionNieves"):
        outdir_key = outdir_key+"_CV_RPA_Res_Nieves"
    elif(key=="CVResPionMINOS"):
        outdir_key = outdir_key+"_CV_RPA_Res_MINOS"
    else:
        print "Unknown configuration-%s. Quiting."%(key)
        sys.exit(1)
    for pl in playlists:
        cmd = "python SubmitPlaylistToGrid.py --outdir %s --stage %s --playlist %s --limitmc -1 %s"%(outdir_key,"IOptimalMichel",pl,config[key])
        print cmd
        os.system(cmd)
#submit BlobQualityHists
    for pl in playlists:
        cmd = "python SubmitPlaylistToGrid.py --outdir %s --stage %s --playlist %s --limitmc -1 %s"%(outdir_key,"BlobQualityHists",pl,config[key])
        print cmd
        os.system(cmd)
#Submit MuonSelection
    for sam in selection_samples:
        for mul in selection_multiplicity:
            for pl in playlists:
                cmd = "python SubmitPlaylistToGrid.py --outdir %s --stage %s --sample %s --playlist %s --multiplicity %s --limitmc -1 %s"%(outdir_key,"MuonSelectionHists",sam,pl,mul,config[key])
                print cmd
                os.system(cmd)

#Submit Efficiency
    for mul in eff_multiplicity:
        for pl in playlists:
            cmd = "python SubmitPlaylistToGrid.py --outdir %s --stage %s --playlist %s --multiplicity %s --limitmc -1 %s"%(outdir_key,"EffPurityHists",pl,mul,config[key])
            print cmd
            os.system(cmd)

#Submit Migration
    for mul in mig_multiplicity:
        for pl in playlists:
            cmd = "python SubmitPlaylistToGrid.py --outdir %s --stage %s --playlist %s --multiplicity %s --limitmc -1 %s"%(outdir_key,"MigrationMatrixHists",pl,mul,config[key])
            print cmd
            os.system(cmd)
