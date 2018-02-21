#include <TagProbe/MakeHist_TnP_L2_OverL1.h>

void MakeHist_TnP_L2_OverL1(TString infile, TString outfile)
{

  HistProducer* producer = new HistProducer();

  producer->L1MuonPtCut = 22.;
  producer->OffLineMuonPtCut = 29.;
  producer->L2MuonPtCut = 0.;
  producer->SetOutputFileName(outfile);
  producer->AddDataPath(infile);
  producer->Produce();
}

