import os

IterL3MuonObjs = [
  ["IterL3OI_TK"],
  ["IterL3OI_TK", "IterL3IO_L2Seeded_TK"],
  ["IterL3_FromL2_TK"],
  ["IterL3_FromL2_TK", "IterL3IO_FromL1"]
]

IterL3MuonObjsAlias = [
  "IterL3OI_TK",
  "IterL3IO_L2Seeded_TK",
  "IterL3_FromL2_TK",
  "IterL3IO_FromL1",
]

counter = 0
for obj in IterL3MuonObjs:

  objname = IterL3MuonObjsAlias[counter]
  filename = 'MakeHist_TnP_'+objname+'_OverL1'
  out = open('Cycles/NoL3MuonPt/'+filename+'.C','w')

  outputfilepath = '/data8/Users/jskim/CMSSW_9_2_14/src/TSNtuple/Analyzer/TagProbe/IterL3BreakDownEfficiency/Outputs/NoL3MuonPt/Output_'+objname+'.root'

  print>>out,'''#include <TagProbe/MakeHist_TnP_IterL3_OverL1.h>

void {0}()
{{

  TString dataPath = "/data8/Users/jskim/MuonHLTNtuple/171218/merged.root";

  HistProducer* producer = new HistProducer();
'''.format(filename, objname, outputfilepath)

  out.write('  producer->IterL3Objs = {\n')

  for a in range(0,len(obj)):
    out.write('"'+obj[a]+'",\n')
  out.write('  };\n')

  print>>out,'''  producer->L1MuonPtCut = 22.;
  producer->OffLineMuonPtCut = 29.;
  producer->IterL3MuonPtCut = 0.;
  producer->SetOutputFileName( "{2}" );
  producer->AddDataPath(dataPath);
  producer->Produce();
}}
'''.format(filename, objname, outputfilepath)

  out.close()

  counter = counter+1
