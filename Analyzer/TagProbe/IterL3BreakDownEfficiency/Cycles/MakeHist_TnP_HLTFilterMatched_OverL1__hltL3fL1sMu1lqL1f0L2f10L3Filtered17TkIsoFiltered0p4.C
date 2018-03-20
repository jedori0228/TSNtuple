#include <TagProbe/MakeHist_TnP_HLTFilterMatched_OverL1.h>

//==== Mu17
void MakeHist_TnP_HLTFilterMatched_OverL1__hltL3fL1sMu1lqL1f0L2f10L3Filtered17TkIsoFiltered0p4(TString infile, TString outfile)
{

  vector<TString> filtersToRun = {
    "hltL3fL1sMu1lqL1f0L2f10L3Filtered17TkIsoFiltered0p4",
  };

  for(unsigned int i=0; i<filtersToRun.size(); i++){

    TString this_filter = filtersToRun.at(i);

    cout << "HLT Filter Name : " << this_filter << endl;

    HistProducer* producer = new HistProducer();

    //==== L1 : L1_SingleMu10_lowQ
    //==== pt > 10 && quality >= 8
    producer->L1MuonPtCut = 10.;
    producer->L1MuonQual = 8; // Q >= 8
    producer->OffLineMuonPtCut = 19.;

    producer->L3MuonPtCut = 0.;
    producer->PassingProbeHLTFilter = this_filter;
    producer->SetOutputFileName(outfile);
    producer->AddDataPath(infile);
    producer->Produce();

  }
}

