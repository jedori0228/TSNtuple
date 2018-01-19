#include <TagProbe/MakeHist_TnP_L3_OverL1.h>

void MakeHist_TnP_L3_OverL1()
{

  TString dataPath = "/data8/Users/jskim/MuonHLTNtuple/171218/merged.root";

  HistProducer* producer = new HistProducer();

  producer->L1MuonPtCut = 22.;
  producer->OffLineMuonPtCut = 29.;
  producer->L3MuonPtCut = 27.;
  producer->SetOutputFileName( "/data8/Users/jskim/CMSSW_9_2_14/src/TSNtuple/Analyzer/TagProbe/IterL3BreakDownEfficiency/Outputs/Output_L3_OverL1.root" );
  producer->AddDataPath(dataPath);
  producer->Produce();
}

