#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLorentzVector.h>
#include <TStopwatch.h>
#include <TTimeStamp.h>
#include <TString.h>
#include <TLegend.h>
#include <THStack.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TAttMarker.h>
#include <TF1.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TApplication.h>
#include <vector>
#include <TMath.h>
#include <TSystem.h>

#include <Include/NtupleHandle.h>
#include <Include/Object.h>

class MakeHistTool
{
public:
	vector< TString > vec_DataList;
	TFile *f_Output;

	TH1D* h_nVertices;

	void SetDataList( vector<TString> vec )
	{
		this->vec_DataList = _vec;
	}

	void SetOutput( TFile *f )
	{
		this->f_Output = f;
	}

	void Save()
	{
		this->f_Output->cd();
		this->h_nVertices->Write();
	}

	void MakeHist()
	{
		this->Init();

		TChain *chain = new TChain("ntupler/ntuple");
		for( const auto& DataPath : this->vec_DataPath )
		{
			if( debug ) cout << DataPath << endl;
			chain->Add( DataPath );
		}

		NtupleHandle *ntuple = new NtupleHandle( chain );
		ntuple->TurnOffBranches_All();
		// ntuple->TurnOnBranches_GenParticle();
		ntuple->TurnOnBranches_Event();
		ntuple->TurnOnBranches_HLT();
		// ntuple->TurnOnBranches_Muon();
		// ntuple->TurnOnBranches_HLTRerunObject();

		Bool_t Flag_IsMC = kFALSE;
		Int_t nEvent = chain->GetEntries();
		std::cout << "[Total event: " << nEvent << "]" << std::endl;
		// nEvent = 1000;
		for(Int_t i_ev=0; i_ev<nEvent; i_ev++)
		{
			loadBar(i_ev+1, nEvent, 100, 100);
			// if( debug ) cout << "1" << endl;

			ntuple->GetEvent( i_ev );
			if( debug ) printf("[%d event]\n", i_ev);
			KPEvent event( ntuple, Flag_IsMC );

			this->nVertices->Fill( event.nVertices );
		}
	}
private:
	void Init()
	{
		this->h_nVertices = new TH1D("h_nVertices", "", 100, 0, 100 );
	}

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

void MakeHist_nVertices()
{
	TString DataBasePath = gSystem->Getenv("KP_DATA_PATH");
	vector< TString > vec_Data = 
	{
		DataBasePath+"/92X/CRABOutputs/HLTReRunNtuple_v20170923_withFix_HLTPhysics1_Run2017Cv3/*.root",
		DataBasePath+"/92X/CRABOutputs/HLTReRunNtuple_v20170923_withFix_HLTPhysics2_Run2017Cv3/*.root",
		// DataBasePath+"/92X/CRABOutputs/HLTReRunNtuple_v20170923_withFix_HLTPhysics3_Run2017Cv3/*.root",
		DataBasePath+"/92X/CRABOutputs/HLTReRunNtuple_v20170923_withFix_HLTPhysics4_Run2017Cv3/*.root",
		DataBasePath+"/92X/CRABOutputs/HLTReRunNtuple_v20170923_withFix_HLTPhysics5_Run2017Cv3/*.root",
		DataBasePath+"/92X/CRABOutputs/HLTReRunNtuple_v20170923_withFix_HLTPhysics6_Run2017Cv3/*.root",
		DataBasePath+"/92X/CRABOutputs/HLTReRunNtuple_v20170923_withFix_HLTPhysics7_Run2017Cv3/*.root",
		DataBasePath+"/92X/CRABOutputs/HLTReRunNtuple_v20170923_withFix_HLTPhysics8_Run2017Cv3/*.root"
	};

	TFile *f_Output = TFile::Open("ROOTFile_MakeHist_nVertices.root", "RECREATE");

	MakeHistTool *tool = new MakeHistTool();
	tool->SetOutput( f_Output );
	tool->SetDataList( vec_Data );
	tool->Analyze();
	tool->Save();

	f_Output->Close();
}