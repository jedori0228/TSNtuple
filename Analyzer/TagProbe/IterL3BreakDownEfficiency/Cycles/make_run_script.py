import os

lines = open('ToRun.txt').readlines()

n_file = 5

infiledirs = [
#'180204_PixTrilpetFix',
#'180204_PixTrilpetFixL1L2',
#'180204_FromL1ExtendL1Seed_PixTrilpetFix',
#'180204_FromL1ExtendL1Seed_PixTrilpetFixL1L2',
#'180214_IterL3_v2018_Ntuple_withID',
#"180214_IterL3_v2018_Ntuple_noID",
#'180216_IterL3_v2017_Ntuple_iterl3froml1_0triplet_2doublet',
#'180216_IterL3_v2017_Ntuple_iterl3froml1_0triplet_2doublet_extendl1',
#'180217_IterL3v2018_OIFix_TrilpetLayerlistFix_NtuplerOriginal',
#'180221_IterL3v2018_NoChi2_OIFix_TrilpetLayerlistFix_NtuplerOriginal',
#'180227_HLT_IsoMu27_MasterTable100X_NoRecoAsOffline',
#'180227_HLT_IsoMu27_MasterTable100X',
#'180302_v2018_oi_iofix_loose',
#'180302_v2018_oi_iofix_tight',
#'180304_HLT_IsoMu27__HLT_Mu50_Default_ntupler',
#'180309_HLTConfig_dimuon_samewith2017_EphemeralHLTPhysics',
#'180309_HLTConfig_dimuon_sepa_seq2018_v04_EphemeralHLTPhysics',
'180320_Ntupler__HLTConfig_v01_Default',
'180320_Ntupler__HLTConfig_v01_Default__customizerForMuonReco2018',
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
      os.system('mkdir -p '+outfile+infiledir)
      print 'mkdir -p '+outfile+infiledir
      outfile += infiledir+"/Output_"+line+"_"+str(i)+".root"

      logfile = "logs/"+infiledir+"/log_MakeHist_TnP_"+line+"_"+str(i)+".log"
      os.system('mkdir -p logs/'+infiledir)

      cmd = 'root -l -b -q "'+cyclename+'.C(\\"'+infile+'\\",\\"'+outfile+'\\")"'
      cmd = cmd+' &> '+logfile
      print cmd
