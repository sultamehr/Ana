import os,sys

inputdir = sys.argv[1]#All the way to the ANA!!
outdir = sys.argv[2]#where you want the files
OutputPrefix = sys.argv[3]#the prefix you want on your output files
mcdata = sys.argv[4]#is this mc or data

long_dir = os.popen("find %s -type d "%(inputdir)).readlines()

#find longest dir
max_length = 0
alldirs = []
for d in long_dir:
    myl = len(d.split("/"))
    if(myl>max_length):
        max_length = myl

#populate list
runs = []
for d in long_dir:
    myl = len(d.split("/"))
    if(myl==max_length):
        name = d.strip("\n")
        print name
        alldirs.append(d.strip("\n"))
        splitdir = name.split("/")
        print splitdir
        run = int(splitdir[-4]+splitdir[-3]+splitdir[-2]+splitdir[-1])
        runs.append(run)
print runs
runs = sorted(runs)
print runs

#now do hadds
if(mcdata.lower()=="mc"):
    for run in runs:
        cmd = "MergeFiles.exe -i %s/ -n %d -o %s -s %s -m 1 -a CCQENu -t CCQENu"%(inputdir.split("/grid")[0],run,outdir,OutputPrefix)
        print cmd
        os.system(cmd)
else:
    cmd = "MergeFiles.exe -i %s/ -n %d-%d -o %s -s %s -data -a CCQENu -t CCQENu"%(inputdir.split("/grid")[0],runs[0],runs[-1]+1,outdir,OutputPrefix)
    print cmd
    os.system(cmd)
    print cmd

    
