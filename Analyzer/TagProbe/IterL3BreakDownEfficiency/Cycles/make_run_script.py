import os

lines = open('ToRun.txt').readlines()

n_file = 3

infiledirs = [
'180204_PixTrilpetFix',
'180204_PixTrilpetFixL1L2',
'180204_FromL1ExtendL1Seed_PixTrilpetFix',
'180204_FromL1ExtendL1Seed_PixTrilpetFixL1L2',
]

for infiledir in infiledirs:

  for line in lines:
    line = line.strip('\n')

    if "#" in line:
      continue

    cyclename = 'MakeHist_TnP_'+line

    for i in range(1,n_file+1):
      infile = "/data8/Users/jskim/MuonHLTNtuple/"+infiledir+"/merge_"+str(i)+".root"

      outfile = "/data8/Users/jskim/CMSSW_9_2_13/src/TSNtuple/Analyzer/TagProbe/IterL3BreakDownEfficiency/Outputs/"
      outfile += infiledir+"/Output_"+line+"_"+str(i)+".root"

      logfile = "logs/"+infiledir+"/log_MakeHist_TnP_"+line+"_"+str(i)+".log"
      os.system('mkdir -p logs/'+infiledir)

      cmd = 'root -l -b -q "'+cyclename+'.C(\\"'+infile+'\\",\\"'+outfile+'\\")"'
      cmd = cmd+' &> '+logfile
      print cmd
