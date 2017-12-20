import os

IterL3MuonObjs = [
    "IterL3OI_TK",
    #"IterL3OI_SA",
    #"IterL3OI_GL",
    "IterL3IO_L2Seeded_TK",
    #"IterL3IO_L2Seeded_SA",
    #"IterL3IO_L2Seeded_GL",
    "IterL3IO_FromL1",
    "IterL3_FromL2_TK",
    #"IterL3_FromL2_SA",
    #"IterL3_FromL2_GL",
]

counter = 0
for obj in IterL3MuonObjs:

  filename = 'MakeHist_TnP_'+obj+'_OverL1'
  out = open('Cycles/'+filename+'.C','w')

  outputfilepath = '/data8/Users/jskim/CMSSW_9_2_14/src/TSNtuple/Analyzer/TagProbe/IterL3BreakDownEfficiency/Outputs/Output_'+obj+'.root'

  print>>out,'''#include <TagProbe/MakeHist_TnP_IterL3_OverL1.h>

void {0}()
{{

  TString dataPath = "/data8/Users/jskim/MuonHLTNtuple/171218/merged.root";

  HistProducer* producer = new HistProducer();
'''.format(filename, obj, outputfilepath)

  out.write('  producer->iterl3objs = {\n')

  for a in range(0,counter+1):
    out.write('"'+IterL3MuonObjs[a]+'",\n')

  out.write('  };\n')


  print>>out,'''  producer->SetOutputFileName( "{2}" );
  producer->AddDataPath(dataPath);
  producer->Produce();
}}
'''.format(filename, obj, outputfilepath)

  out.close()

  counter = counter+1
