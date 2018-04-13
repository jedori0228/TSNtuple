#include <TagProbe/TnPTool_JPsi.h>

class MyTnPPair: public TnPPair
{
public:
	MyTnPPair( KPMuon tagCand, KPMuon probeCand ): TnPPair( tagCand, probeCand )
	{

    //==== Pt cuts For Probe
    OffLineMuonPtCut = 29; // Pt cut for probe (OffLine Muon) : use 29 GeV, to compare with IsoMu27 filtered muons
    L1MuonPtCut = 22; // Pt cut for L1Muon, which will be matched to probe
    L1MuonQual = 12;
    //==== Pt cuts For Passing Probe
    L3MuonPtCut = 27; // Pt cut for L3Muon, which will be matched to passing probe, use 27 GeV, because they will be filtered by IsoMu27
	}

  double OffLineMuonPtCut;
  double L1MuonPtCut;
  double L1MuonQual;
  double L3MuonPtCut;
  TString PassingProbeHLTFilter;


	// -- user-defined tag condition -- //
	Bool_t IsTag( KPMuon tagCand, NtupleHandle *ntuple )
	{
		// -- IsoMu27 final filter: hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07 -- //
		// -- Mu50 final filter: hltL3fL1sMu22Or25L1f0L2f10QL3Filtered50Q -- //
		Bool_t flag = kFALSE;

		// printf("[Tag] (Pt, Eta, IsTight, RelPFIso(dBeta)) = (%lf, %lf, %d, %lf)\n", tagCand.Pt, tagCand.Eta, tagCand.IsTight, tagCand.RelPFIso_dBeta);

		if( tagCand.IsMYHLTFilterMatched( ntuple, "hltL3fLMu7p5TrackL3Filtered7p5" ) && tagCand.IsSoft )
			flag = kTRUE;

		// if( flag ) cout << "Tag is found" << endl;

		return flag;
	}

	// -- user-defined probe condition -- //
	Bool_t IsProbe( KPMuon probeCand, NtupleHandle *ntuple )
	{
		Bool_t flag = kFALSE;
		if( probeCand.IsMYHLTFilterMatched( ntuple, "hltMu7p5Track2JpsiTrackMassFiltered")
        && !probeCand.IsMYHLTFilterMatched( ntuple, "hltL3fLMu7p5TrackL3Filtered7p5") && probeCand.IsSoft )
			flag = kTRUE;

		// if( flag ) cout << "Probe is found" << endl;

		return flag;
	}

	// -- user-defined passing probe condition -- //
	Bool_t IsPassingProbe( KPMuon probe, NtupleHandle *ntuple )
	{
		Bool_t flag = kFALSE;
		if( probe.IsMYHLTFilterMatched( ntuple, "hltL3fL1sMu3L1f0L2f0L3Filtered3" ) ) // Filter already has L3Muonpt>27
			flag = kTRUE;

		return flag;
	}
};

class HistProducer
{
public:
	TString fileName;
	vector<TString> vec_DataPath;
  double OffLineMuonPtCut;
  double L1MuonPtCut;
  double L1MuonQual;
  double L3MuonPtCut;
  TString PassingProbeHLTFilter;


	HistProducer()
	{

	}

	void SetOutputFileName( TString _fileName )
	{
		this->fileName = _fileName;
	}

	void AddDataPath( TString value )
	{
		printf("[AddDataPath] %s\n", value.Data());
		vec_DataPath.push_back( value );
	}

	// void Produce()
	// {
	// 	Int_t nDataPath = this->vec_DataPath.size();
	// 	for(Int_t i=0; i<nDataPath; i++)
	// 		this->Produce( this->vec_DataPath[i], i );
	// }

	// void Produce( TString dataPath, Int_t i_dataPath )
	void Produce()
	{
		// printf( "[Produce] dataPath (%02d-th) = %s\n", i_dataPath, dataPath.Data() );

		TChain *chain = new TChain("ntupler/ntuple");
		for(const auto& dataPath : vec_DataPath )
			chain->Add(dataPath);
		// chain->Add(dataPath);

		NtupleHandle *ntuple = new NtupleHandle( chain );
		// ntuple->TurnOffBranches_All();

		TnPHistProducer* tnpHist = new TnPHistProducer();
		tnpHist->SetPtThreshold( OffLineMuonPtCut ); // -- only probes above this pT cut will be filled in histograms -- // // FIXME Pt cut?

		Int_t nEvent = chain->GetEntries();
		std::cout << "[Total event: " << nEvent << "]" << std::endl;

		// nEvent = 1000000;
		for(Int_t i_ev=0; i_ev<nEvent; i_ev++)
		{
//if(i_ev==6919) continue;
//cout << i_ev << endl;

			loadBar(i_ev+1, nEvent, 100, 100);

			ntuple->GetEvent( i_ev );

			vector< MyTnPPair* > vec_myTnpPair;

			KPEvent event( ntuple );
			// printf("[%d event] nMuon = %d\n", i_ev, event.nMuon);

			for(Int_t i_mu=0; i_mu<event.nMuon; i_mu++)
			{
//cout << "  i_mu = " << i_mu;
				KPMuon mu_ith( ntuple, i_mu );
//cout << ", mu_ith made, i_mu+1 = " << i_mu+1 << ", event.nMuon = " << event.nMuon << ", vec_myTnpPair.size() = " << vec_myTnpPair.size() << endl;
				for(Int_t j_mu=i_mu+1; j_mu<event.nMuon; j_mu++) // -- starts from i_mu+1: no duplication -- //
				{

//cout << "    j_mu = " << j_mu;
					KPMuon mu_jth( ntuple, j_mu );
//cout << ", mu_jth made";
					MyTnPPair *myTnpPair_ij = new MyTnPPair( mu_ith, mu_jth );

          //==== pt cuts
          myTnpPair_ij->OffLineMuonPtCut = OffLineMuonPtCut;
          myTnpPair_ij->L1MuonPtCut = L1MuonPtCut;
          myTnpPair_ij->L1MuonQual = L1MuonQual;
          myTnpPair_ij->L3MuonPtCut = L3MuonPtCut;
          myTnpPair_ij->PassingProbeHLTFilter = PassingProbeHLTFilter;
          //==== validation
					myTnpPair_ij->Validation( ntuple );

					if( myTnpPair_ij->isValid )
						vec_myTnpPair.push_back( myTnpPair_ij );

					MyTnPPair *myTnpPair_ji = new MyTnPPair( mu_jth, mu_ith );
          //==== pt cuts
          myTnpPair_ji->OffLineMuonPtCut = OffLineMuonPtCut;
          myTnpPair_ji->L1MuonPtCut = L1MuonPtCut;
          myTnpPair_ji->L1MuonQual = L1MuonQual;
          myTnpPair_ji->L3MuonPtCut = L3MuonPtCut;
          myTnpPair_ji->PassingProbeHLTFilter = PassingProbeHLTFilter;
          //==== validation
					myTnpPair_ji->Validation( ntuple );
					if( myTnpPair_ji->isValid )
						vec_myTnpPair.push_back( myTnpPair_ji );

//cout << " --> Validated" << endl;
				}
			}

			Double_t weight = event.IsRealData? 1.0 : event.GenEventWeight;

			for( const auto& tnpPair : vec_myTnpPair )
				tnpHist->Fill( tnpPair, weight );

//cout << "--> Done" << endl;

			// // -- reduce memeory usage -- //
			// for( const auto& tnpPair : vec_myTnpPair )
			// 	delete tnpPair;
			// vec_myTnpPair.clear();

		} // -- end of event iteration -- //

		// TString fileName_ith = this->fileName;
		// fileName_ith.ReplaceAll(".root", TString::Format("_v%02d.root", i_dataPath) );
		// TFile *f_output = TFile::Open(fileName_ith, "RECREATE");

    cout << "Output Filename = " << this->fileName << endl;
		TFile *f_output = TFile::Open(this->fileName, "RECREATE");
		tnpHist->Save( f_output );
		f_output->Close();

		// -- reduce memeory usage -- //
		delete tnpHist;
		// delete f_output;

		cout << "finished" << endl;
	}

private:
	static inline void loadBar(int x, int n, int r, int w)
	{
	    // Only update r times.
	    if( x == n )
	    	cout << endl;

	    if ( x % (n/r +1) != 0 ) return;

	 
	    // Calculuate the ratio of complete-to-incomplete.
	    float ratio = x/(float)n;
	    int   c     = ratio * w;
	 
	    // Show the percentage complete.
	    printf("%3d%% [", (int)(ratio*100) );
	 
	    // Show the load bar.
	    for (int x=0; x<c; x++) cout << "=";
	 
	    for (int x=c; x<w; x++) cout << " ";
	 
	    // ANSI Control codes to go back to the
	    // previous line and clear it.
		cout << "]\r" << flush;
	}
};
