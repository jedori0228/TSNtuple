#include <TagProbe/MakeHist_TnP_HLTFilterMatched_OverL1.h>

//==== Mu8
void MakeHist_TnP_HLTFilterMatched_OverL1__hltL3fL1sMu5L1f0L2f5L3Filtered8TkIsoFiltered0p4(TString infile, TString outfile)
{

  vector<TString> filtersToRun = {
    "hltL3fL1sMu5L1f0L2f5L3Filtered8TkIsoFiltered0p4",
  };

  for(unsigned int i=0; i<filtersToRun.size(); i++){

    TString this_filter = filtersToRun.at(i);

    cout << "HLT Filter Name : " << this_filter << endl;

    HistProducer* producer = new HistProducer();

    //==== L1 : SingleMu3
    //==== pt > 3 && quality == 12
    producer->L1MuonPtCut = 3.;
    producer->L1MuonQual = 12; // Q == 12
    producer->OffLineMuonPtCut = 10.;

    producer->L3MuonPtCut = 0.;
    producer->PassingProbeHLTFilter = this_filter;
    producer->SetOutputFileName(outfile);
    producer->AddDataPath(infile);
    producer->Produce();

  }
}

