#include <TagProbe/MakeHist_TnP_HLTFilterMatched_AND_OverL1.h>

void MakeHist_TnP_HLTFilterMatched_OverL1__DiMuon_Mu8Leg(TString infile, TString outfile)
{

  HistProducer* producer = new HistProducer();

  producer->L1MuonPtCut = 5.;
  producer->L1MuonQual = 8;

  producer->L3MuonPtCut = 0.;

  producer->OffLineMuonPtCut = 19.;

  vector<TString> filtersAND = {
    "hltDiMuon178RelTrkIsoFiltered0p4",
    "hltL3fL1DoubleMu155fPreFiltered8",
  };

  producer->PassingProbeHLTFilter = filtersAND;
  producer->SetOutputFileName(outfile);
  producer->AddDataPath(infile);
  producer->Produce();

}

