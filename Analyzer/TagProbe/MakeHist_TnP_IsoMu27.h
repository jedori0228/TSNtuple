#include <TagProbe/TnPTool.h>

class TnPPairIsoMu27: public TnPPair
{
public:
	TnPPairIsoMu27( KPMuon tagCand, KPMuon probeCand ): TnPPair( tagCand, probeCand )
	{

	}

	// -- user-defined tag condition -- //
	Bool_t IsTag( KPMuon tagCand, NtupleHandle *ntuple )
	{
		// -- IsoMu27 final filter: hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07 -- //
		// -- Mu50 final filter: hltL3fL1sMu22Or25L1f0L2f10QL3Filtered50Q -- //
		Bool_t flag = kFALSE;

		// printf("[Tag] (Pt, Eta, IsTight, RelPFIso(dBeta)) = (%lf, %lf, %d, %lf)\n", tagCand.Pt, tagCand.Eta, tagCand.IsTight, tagCand.RelPFIso_dBeta);

		if( tagCand.IsHLTFilterMatched( ntuple, "hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07" ) &&
			tagCand.Pt > 29 &&
			fabs(tagCand.Eta) < 2.4 &&
			tagCand.IsTight && 
			tagCand.RelPFIso_dBeta < 0.15 )
			flag = kTRUE;

		// if( flag ) cout << "Tag is found" << endl;

		return flag;
	}

	// -- user-defined probe condition -- //
	Bool_t IsProbe( KPMuon probeCand, NtupleHandle *ntuple )
	{
		Bool_t flag = kFALSE;

		if( probeCand.IsTight && 
			probeCand.RelPFIso_dBeta < 0.15 )
			flag = kTRUE;

		// if( flag ) cout << "Probe is found" << endl;

		return flag;
	}

	// -- user-defined passing probe condition -- //
	Bool_t IsPassingProbe( KPMuon probe, NtupleHandle *ntuple )
	{
		Bool_t flag = kFALSE;
		if( probe.IsMYHLTFilterMatched( ntuple, "hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07" ) )
			flag = kTRUE;

		return flag;
	}
};

class HistProducer
{
public:
	TString fileName;
	vector<TString> vec_DataPath;
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

		TnPHistProducer* tnpHistIsoMu27 = new TnPHistProducer();
		tnpHistIsoMu27->SetPtThreshold( 29 ); // -- only probes above this pT cut will be filled in histograms -- //

		Int_t nEvent = chain->GetEntries();
		std::cout << "[Total event: " << nEvent << "]" << std::endl;

		// nEvent = 1000000;
		for(Int_t i_ev=0; i_ev<nEvent; i_ev++)
		{
			loadBar(i_ev+1, nEvent, 100, 100);

			ntuple->GetEvent( i_ev );

			vector< TnPPairIsoMu27* > vec_tnpPairIsoMu27;

			KPEvent event( ntuple );
			// printf("[%d event] nMuon = %d\n", i_ev, event.nMuon);
			for(Int_t i_mu=0; i_mu<event.nMuon; i_mu++)
			{
				KPMuon mu_ith( ntuple, i_mu );
				for(Int_t j_mu=i_mu+1; j_mu<event.nMuon; j_mu++) // -- starts from i_mu+1: no duplication -- //
				{
					KPMuon mu_jth( ntuple, j_mu );

					TnPPairIsoMu27 *tnpPairIsoMu27_ij = new TnPPairIsoMu27( mu_ith, mu_jth );
					tnpPairIsoMu27_ij->Validation( ntuple );
					if( tnpPairIsoMu27_ij->isValid )
						vec_tnpPairIsoMu27.push_back( tnpPairIsoMu27_ij );

					TnPPairIsoMu27 *tnpPairIsoMu27_ji = new TnPPairIsoMu27( mu_jth, mu_ith );
					tnpPairIsoMu27_ji->Validation( ntuple );
					if( tnpPairIsoMu27_ji->isValid )
						vec_tnpPairIsoMu27.push_back( tnpPairIsoMu27_ji );
				}
			}

			Double_t weight = event.IsRealData? 1.0 : event.GenEventWeight;

			for( const auto& tnpPair : vec_tnpPairIsoMu27 )
				tnpHistIsoMu27->Fill( tnpPair, weight );

			// // -- reduce memeory usage -- //
			// for( const auto& tnpPair : vec_tnpPairIsoMu27 )
			// 	delete tnpPair;
			// vec_tnpPairIsoMu27.clear();

		} // -- end of event iteration -- //

		// TString fileName_ith = this->fileName;
		// fileName_ith.ReplaceAll(".root", TString::Format("_v%02d.root", i_dataPath) );
		// TFile *f_IsoMu27 = TFile::Open(fileName_ith, "RECREATE");
		TFile *f_IsoMu27 = TFile::Open(this->fileName, "RECREATE");
		tnpHistIsoMu27->Save( f_IsoMu27 );
		f_IsoMu27->Close();

		// -- reduce memeory usage -- //
		delete tnpHistIsoMu27;
		// delete f_IsoMu27;

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