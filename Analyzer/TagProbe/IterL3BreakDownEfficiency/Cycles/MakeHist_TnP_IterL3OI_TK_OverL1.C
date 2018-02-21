#include <TagProbe/MakeHist_TnP_IterL3_OverL1.h>

void MakeHist_TnP_IterL3OI_TK_OverL1(TString infile, TString outfile)
{

  HistProducer* producer = new HistProducer();

  producer->IterL3Objs = {
"IterL3OI_TK",
  };
  producer->L1MuonPtCut = 22.;
  producer->OffLineMuonPtCut = 29.;
  producer->IterL3MuonPtCut = 0.;
  producer->SetOutputFileName(outfile);
  producer->AddDataPath(infile);
  producer->Produce();
}

