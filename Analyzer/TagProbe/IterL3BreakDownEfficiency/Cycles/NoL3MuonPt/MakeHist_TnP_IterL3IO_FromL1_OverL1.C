#include <TagProbe/MakeHist_TnP_IterL3_OverL1.h>

void MakeHist_TnP_IterL3IO_FromL1_OverL1()
{

  TString dataPath = "/data8/Users/jskim/MuonHLTNtuple/171218/merged.root";

  HistProducer* producer = new HistProducer();

  producer->IterL3Objs = {
"IterL3_FromL2_TK",
"IterL3IO_FromL1",
  };
  producer->L1MuonPtCut = 22.;
  producer->OffLineMuonPtCut = 29.;
  producer->IterL3MuonPtCut = 0.;
  producer->SetOutputFileName( "/data8/Users/jskim/CMSSW_9_2_14/src/TSNtuple/Analyzer/TagProbe/IterL3BreakDownEfficiency/Outputs/NoL3MuonPt/Output_IterL3IO_FromL1.root" );
  producer->AddDataPath(dataPath);
  producer->Produce();
}

