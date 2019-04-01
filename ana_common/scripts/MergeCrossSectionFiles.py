import os,sys
import ROOT

#find all cross section files
files = os.popen("find %s -type f -name 'CrossSection_*'"%(sys.argv[1])).readlines()

prefixes = {}
for f in files:
    filename = os.path.basename(f.rstrip("\n"))
    prefix = filename.split(".root")[0]
    prefixes[prefix]=1

options = []
counter = 0
for p in prefixes.keys():
    print "Option %d"%(counter),p
    options.append(p)
    counter+=1
selected = int(raw_input("Which option do you want?\n"))

specificfiles = os.popen("find %s -type f -name '%s*'"%(sys.argv[1],options[selected])).readlines()

print "I will merge the following files into a file named %s.root"%(options[selected])
print specificfiles
for f in specificfiles: 
    print f.rstrip("\n")


raw_input("Ctrl-c if you don't like these files")

outputfile = ROOT.TFile("%s/%s.root"%(sys.argv[1],options[selected]),"RECREATE")

for f in specificfiles:
    tmpfile = ROOT.TFile(f.rstrip("\n"))
    mykeys = tmpfile.GetListOfKeys()
    outputfile.cd()
    for k in mykeys:
        keyname = k.GetName()
        myobj = tmpfile.Get(keyname)
        print "Writing",keyname,"from",f.rstrip("\n")
        myobj.Write()
