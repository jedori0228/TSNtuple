#include <TagProbe/MakeHist_TnP_HLTFilterMatched_OverL1.h>

void MakeHist_TnP_HLTFilterMatched_OverL1__hltL3fL1sMu22Or25L1f0L2f10QL3Filtered27Q(TString infile, TString outfile)
{

  vector<TString> filtersToRun = {
    "hltL3fL1sMu22Or25L1f0L2f10QL3Filtered27Q",
  };

  for(unsigned int i=0; i<filtersToRun.size(); i++){

    TString this_filter = filtersToRun.at(i);

    cout << "HLT Filter Name : " << this_filter << endl;

    HistProducer* producer = new HistProducer();

    producer->L1MuonPtCut = 22.;
    producer->OffLineMuonPtCut = 29.;
    producer->L3MuonPtCut = 0.;
    producer->PassingProbeHLTFilter = this_filter;
    producer->SetOutputFileName(outfile);
    producer->AddDataPath(infile);
    producer->Produce();

  }
}

