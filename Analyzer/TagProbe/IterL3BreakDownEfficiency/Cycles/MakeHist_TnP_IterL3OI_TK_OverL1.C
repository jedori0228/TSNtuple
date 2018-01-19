#include <TagProbe/MakeHist_TnP_IterL3_OverL1.h>

void MakeHist_TnP_IterL3OI_TK_OverL1()
{

  TString dataPath = "/data8/Users/jskim/MuonHLTNtuple/171218/merged.root";

  HistProducer* producer = new HistProducer();

  producer->IterL3Objs = {
"IterL3OI_TK",
  };
  producer->L1MuonPtCut = 22.;
  producer->OffLineMuonPtCut = 29.;
  producer->IterL3MuonPtCut = 27.;
  producer->SetOutputFileName( "/data8/Users/jskim/CMSSW_9_2_14/src/TSNtuple/Analyzer/TagProbe/IterL3BreakDownEfficiency/Outputs/Output_IterL3OI_TK.root" );
  producer->AddDataPath(dataPath);
  producer->Produce();
}

