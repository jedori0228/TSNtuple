#include <TagProbe/MakeHist_TnP_HLTFilterMatched_OverL1.h>

void MakeHist_TnP_HLTFilterMatched_OverL1()
{

  TString dataPath = "/data8/Users/jskim/MuonHLTNtuple/171218/merged.root";
//ntuple_153.root
//merged.root

  vector<TString> filtersToRun = {
    //"hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07",
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
    producer->SetOutputFileName( "/data8/Users/jskim/CMSSW_9_2_14/src/TSNtuple/Analyzer/TagProbe/IterL3BreakDownEfficiency/Outputs/NoL3MuonPt/Output_HLTFilterMatched_OverL1__"+this_filter+".root" );
    producer->AddDataPath(dataPath);
    producer->Produce();

  }
}

