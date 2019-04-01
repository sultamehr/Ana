import os,sys
#script to audit output of grid jobs
#will check the grid for jobs as well and report back any not showing up in either place
#MuonSelection Configs
selection_samples = ["Signal","MichelSideBand","BlobSideBand","MicBlobSideBand"]
selection_multiplicity = ["1","2"]

#MigrationMatrix Configs
mig_multiplicity = ["0"]

#EffPurity Configs
eff_multiplicity = ["0"]


#playlists
#playlists = ["minerva1","minerva7","minerva9","minerva2p2h","minervanonreweightables","minerva13"]#minerva13 at the end of the list as you can do a lot with new files as long as you have minerva1,7,9,2p2h
playlists = ["minervame1A","minervame1B","minervame1C","minervame1D","minervame1E","minervame1F","minervame1G","minervame1L","minervame1M","minervame1N","minervame1O","minervame1P"]
status = [[],[],[]]#three blocks for muon sel,eff,migrat
for p in playlists:
    status[0].append(True)
    status[1].append(True)
    status[2].append(True)
#playlists = ["minervame1P"]
###############################
###############################
outdir = sys.argv[1]

files = os.popen("ls %s/"%(outdir)).readlines()

#Submit MuonSelection
for sam in selection_samples:
    for mul in selection_multiplicity:
        for i,pl in enumerate(playlists):
            prefixfn = "MuonEventSelection_MakeFlux-1_Multiplicity-%s_Sample-%s_%s"%(mul,sam,pl)
            found_root = prefixfn+".root\n" in files
            found_log =  prefixfn+".log\n" in files
            if found_log and not found_root:
                print "Only found the log file for:",prefixfn
                status[0][i]=False
            if not found_log and not found_root:
                print "No log or root file for:",prefixfn
                status[0][i]=False

#Submit Efficiency
for mul in eff_multiplicity:
    for i,pl in enumerate(playlists):
        prefixfn = "EffPurity_MakeFlux-1_%s"%(pl)
        found_root = prefixfn+".root\n" in files
        found_log =  prefixfn+".log\n" in files
        if found_log and not found_root:
            print "Only found the log file for:",prefixfn
            status[1][i]=False
        if not found_log and not found_root:
            print "No log or root file for:",prefixfn
            status[1][i]=False


#Submit Migration
for mul in eff_multiplicity:
    for i,pl in enumerate(playlists):
        for en in ["pzmu","q2","enu","pzptreco"]:
            prefixfn = "Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-0_%s_%s"%(en,pl)
            found_root = prefixfn+".root\n" in files
            found_log =  prefixfn+".log\n" in files
            if found_log and not found_root:
                print "Only found the log file for:",prefixfn
                status[2][i]=False
            if not found_log and not found_root:
                print "No log or root file for:",prefixfn
                status[2][i]=False

print "Overall Status"
for i,p in enumerate(playlists):
    if status[0][i] and status[1][i] and status[2][i]:#all stages there
        print p,"is good"
    else:
        print p,"is bad"
    




#Submit Proton Study
#for pl in playlists:
#    prefixfn = "ProtonEfficiencyStudy_%s"%(pl)
#    found_root = prefixfn+".root\n" in files
#    found_log =  prefixfn+".log\n" in files
#    if found_log and not found_root:
#        print "Only found the log file for:",prefixfn
#        if not found_log and not found_root:
#            print "No log or root file for:",prefixfn
