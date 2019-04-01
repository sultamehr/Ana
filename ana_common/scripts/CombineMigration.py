import os,sys
directory = sys.argv[1]

playlists = ["minerva1","minerva7","minerva9","minerva13","minervanonreweightables","minerva2p2h"]
for pl in playlists:
#Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-0_
    cmd = "$MY_CCQENU/make_hists/CombineSamples %s/Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-0_%s.root %s/Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-0_pzmu_%s.root %s/Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-0_q2_%s.root %s/Migration_MakeFlux-1_ApplyFlux-1_Multiplicity-0_enu_%s.root"%(directory,pl,directory,pl,directory,pl,directory,pl)
    os.system(cmd)

