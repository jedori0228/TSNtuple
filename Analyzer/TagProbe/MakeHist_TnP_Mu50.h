#include <TagProbe/TnPTool.h>

class TnPPairMu50: public TnPPair
{
public:
	TnPPairMu50( KPMuon tagCand, KPMuon probeCand ): TnPPair( tagCand, probeCand )
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
		// if( probe.IsHLTFilterMatched( ntuple, "hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07" ) )
		if( probe.IsMYHLTFilterMatched( ntuple, "hltL3fL1sMu22Or25L1f0L2f10QL3Filtered50Q" ) )
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

		TnPHistProducer* tnpHistMu50 = new TnPHistProducer();
		tnpHistMu50->SetPtThreshold( 52 ); // -- only probes above this pT cut will be filled in histograms -- //

		Int_t nEvent = chain->GetEntries();
		std::cout << "[Total event: " << nEvent << "]" << std::endl;

		// nEvent = 1000000;
		for(Int_t i_ev=0; i_ev<nEvent; i_ev++)
		{
			loadBar(i_ev+1, nEvent, 100, 100);

			ntuple->GetEvent( i_ev );

			vector< TnPPairMu50* > vec_tnpPairMu50;

			KPEvent event( ntuple );
			// printf("[%d event] nMuon = %d\n", i_ev, event.nMuon);
			for(Int_t i_mu=0; i_mu<event.nMuon; i_mu++)
			{
				KPMuon mu_ith( ntuple, i_mu );
				for(Int_t j_mu=i_mu+1; j_mu<event.nMuon; j_mu++) // -- starts from i_mu+1: no duplication -- //
				{
					KPMuon mu_jth( ntuple, j_mu );

					TnPPairMu50 *tnpPairMu50_ij = new TnPPairMu50( mu_ith, mu_jth );
					tnpPairMu50_ij->Validation( ntuple );
					if( tnpPairMu50_ij->isValid )
						vec_tnpPairMu50.push_back( tnpPairMu50_ij );

					TnPPairMu50 *tnpPairMu50_ji = new TnPPairMu50( mu_jth, mu_ith );
					tnpPairMu50_ji->Validation( ntuple );
					if( tnpPairMu50_ji->isValid )
						vec_tnpPairMu50.push_back( tnpPairMu50_ji );
				}
			}

			Double_t weight = event.IsRealData? 1.0 : event.GenEventWeight;

			for( const auto& tnpPair : vec_tnpPairMu50 )
				tnpHistMu50->Fill( tnpPair, weight );

			// // -- reduce memeory usage -- //
			// for( const auto& tnpPair : vec_tnpPairMu50 )
			// 	delete tnpPair;
			// vec_tnpPairMu50.clear();

		} // -- end of event iteration -- //

		// TString fileName_ith = this->fileName;
		// fileName_ith.ReplaceAll(".root", TString::Format("_v%02d.root", i_dataPath) );
		// TFile *f_Mu50 = TFile::Open(fileName_ith, "RECREATE");
		TFile *f_Mu50 = TFile::Open(this->fileName, "RECREATE");
		tnpHistMu50->Save( f_Mu50 );
		f_Mu50->Close();

		// -- reduce memeory usage -- //
		delete tnpHistMu50;
		// delete f_Mu50;

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