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

#define nMaxLumiBlock 5000
#define LumiBlockTime 23.31

// -- HLT_Physics_part[0-7]_v7 -- //
// -- 7.5e33: 320
// -- 1.0e34: 400
// -- 1.2e34: 500
// -- 1.4e34: 580
// -- 1.6e34: 580

vector<Int_t> vec_Prescale_Run301567 = {400, 320};
vector<Double_t> vec_LS_Run301567 = {20, 267, 99999};

vector<Int_t> vec_Prescale_Run301627 = {400, 320, 400, 320};
vector<Double_t> vec_LS_Run301627 = {45, 63, 82, 264, 99999};

vector<Int_t> vec_Prescale_Run301664 = {320, 400, 320};
vector<Double_t> vec_LS_Run301664 = {27, 49, 203, 99999};

vector<Int_t> vec_Prescale_Run301665 = {320};
vector<Double_t> vec_LS_Run301665 = {1, 99999};

vector<Int_t> vec_Prescale_Run301694 = {580, 580};
vector<Double_t> vec_LS_Run301694 = {27, 64, 99999};

vector<Int_t> vec_Prescale_Run301912 = {320};
vector<Double_t> vec_LS_Run301912 = {43, 99999};

vector<Int_t> vec_Prescale_Run301913 = {320};
vector<Double_t> vec_LS_Run301913 = {1, 99999};

vector<Int_t> vec_Prescale_Run301914 = {320};
vector<Double_t> vec_LS_Run301914 = {1, 99999};

vector<Int_t> vec_Prescale_Run301941 = {580, 320};
vector<Double_t> vec_LS_Run301941 = {11, 32, 99999};

vector<Int_t> vec_Prescale_Run301959 = {400, 320, 0};
vector<Double_t> vec_LS_Run301959 = {23, 433, 1061, 99999};

Int_t Find_PrescaleValue( Int_t RunNum, Int_t LumiBlockNum )
{
	vector<Int_t> vec_Prescale;
	vector<Double_t> vec_LS;
	if( RunNum == 301567 )
	{
		vec_Prescale = vec_Prescale_Run301567;
		vec_LS = vec_LS_Run301567;
	}
	else if( RunNum == 301627 )
	{
		vec_Prescale = vec_Prescale_Run301627;
		vec_LS = vec_LS_Run301627;
	}
	else if( RunNum == 301664 )
	{
		vec_Prescale = vec_Prescale_Run301664;
		vec_LS = vec_LS_Run301664;
	}
	else if( RunNum == 301665 )
	{
		vec_Prescale = vec_Prescale_Run301665;
		vec_LS = vec_LS_Run301665;
	}
	else if( RunNum == 301694 )
	{
		vec_Prescale = vec_Prescale_Run301694;
		vec_LS = vec_LS_Run301694;
	}
	else if( RunNum == 301912 )
	{
		vec_Prescale = vec_Prescale_Run301912;
		vec_LS = vec_LS_Run301912;
	}
	else if( RunNum == 301913 )
	{
		vec_Prescale = vec_Prescale_Run301913;
		vec_LS = vec_LS_Run301913;
	}
	else if( RunNum == 301914 )
	{
		vec_Prescale = vec_Prescale_Run301914;
		vec_LS = vec_LS_Run301914;
	}
	else if( RunNum == 301941 )
	{
		vec_Prescale = vec_Prescale_Run301941;
		vec_LS = vec_LS_Run301941;
	}
	else if( RunNum == 301959 )
	{
		vec_Prescale = vec_Prescale_Run301959;
		vec_LS = vec_LS_Run301959;
	}

	// -- find pre-scale value -- //
	Double_t Prescale = 0;

	Int_t nBin = (Int_t)vec_Prescale.size();
	for(Int_t i=0; i<nBin; i++)
	{
		Double_t LowerEdge = vec_LS[i];
		Double_t UpperEdge = vec_LS[i+1];

		if( LumiBlockNum >= LowerEdge && LumiBlockNum < UpperEdge )
		{
			Prescale = vec_Prescale[i];
			break;
		}
	}

	// printf("[Run = %d, LS = %d] -> Prescale = %.0lf\n", RunNum, LumiBlockNum, Prescale);

	return Prescale;
}


// Int_t Find_PrescaleValue( Double_t InstLumi )
// {
// 	Int_t Prescale = 0;
// 	UInt_t nBin = (Int_t)vec_Prescale.size();

// 	if( InstLumi > vec_LumiEdge[nBin] ) // -- extrapolation to higher lumi. -- //
// 		Prescale = vec_Prescale[nBin-1];
// 	else
// 	{
// 		for(UInt_t i=0; i<nBin; i++)
// 		{
// 			Double_t LowerEdge = vec_LumiEdge[i];
// 			Double_t UpperEdge = vec_LumiEdge[i+1];

// 			if( InstLumi > LowerEdge && InstLumi < UpperEdge )
// 			{
// 				Prescale = vec_Prescale[i];
// 				break;
// 			}
// 		}
// 	}

// 	// printf("[Inst.Lumi = %lf] -> Prescale = %.0lf\n", InstLumi, Prescale);

// 	return Prescale;
// }

class LumiBlockInfo
{
public:
	Int_t LumiBlockNum;

	Int_t nEvent;
	Int_t nFiredEvent;

	Int_t nEvent_UnPS;
	Int_t nFiredEvent_UnPS;
	
	Double_t nFiredEvent_UnPS_Scaled2e34;
	
	Double_t Sum_InstLumi;
	Double_t Mean_InstLumi;
	Double_t Sum_nVertices;
	Double_t Mean_nVertices;

	Double_t Rate;
	Double_t Rate_UnPS;
	Double_t Rate_UnPS_Scaled2e34;

	LumiBlockInfo( Int_t _Num )
	{
		this->LumiBlockNum = _Num;
		this->Init();
	}

	void Fill( KPEvent &event, TString TriggerTag )
	{
		Double_t Prescale = Find_PrescaleValue( event.RunNum, event.LumiBlockNum );

		this->nEvent += 1;
		this->nEvent_UnPS += Prescale;

		this->Sum_InstLumi = Sum_InstLumi + event.InstLumi;
		this->Sum_nVertices = Sum_nVertices + event.nVertices;

		if( std::find(event.vec_FiredTrigger->begin(), event.vec_FiredTrigger->end(), TriggerTag) != event.vec_FiredTrigger->end() ) // -- if trigger is fired -- //
		{
			this->nFiredEvent += 1;
			this->nFiredEvent_UnPS += Prescale;
		}
	}

	void Calc_Rate()
	{
		if( this->nEvent == 0 )
		{
			this->Mean_InstLumi = 0;
			this->Mean_nVertices = 0;
			this->Rate = 0;
			this->Rate_UnPS = 0;
			this->Rate_UnPS_Scaled2e34 = 0;
		}
		else
		{
			this->Mean_InstLumi = this->Sum_InstLumi / this->nEvent; // -- divided by total # events, not only # fired events! -- //
			this->Mean_nVertices = this->Sum_nVertices / this->nEvent;
			this->Rate = this->nFiredEvent / LumiBlockTime; // -- unit: Hz -- //
			this->Rate_UnPS = this->nFiredEvent_UnPS / LumiBlockTime;

			Double_t SF_Lumi = 20000.0 / this->Mean_InstLumi;
			this->nFiredEvent_UnPS_Scaled2e34 = this->nFiredEvent_UnPS * SF_Lumi;
			this->Rate_UnPS_Scaled2e34 = this->nFiredEvent_UnPS_Scaled2e34 / LumiBlockTime;

			// printf("[%d lumi-block] (# fired events, # fired rate, un-prescaled # rate, scaled to 2e34 rate) = (%d, %lf, %lf, %lf)\n",
			// 	this->LumiBlockNum, this->nFiredEvent, this->Rate, this->Rate_UnPS, this->Rate_UnPS_Scaled2e34);
		}

	}

private:
	void Init()
	{
		this->nEvent = 0;
		this->nFiredEvent = 0;

		this->nEvent_UnPS = 0;
		this->nFiredEvent_UnPS = 0;

		this->nFiredEvent_UnPS_Scaled2e34 = 0;

		this->Sum_InstLumi = 0;
		this->Mean_InstLumi = 0;
		this->Sum_nVertices = 0;
		this->Mean_nVertices = 0;

		this->Rate = 0;
		this->Rate_UnPS = 0;
		this->Rate_UnPS_Scaled2e34 = 0;
	}
};

class RunInfo
{
public:
	Int_t RunNum;
	vector< LumiBlockInfo* > vec_LumiBlockInfo;

	RunInfo( Int_t _RunNum )
	{
		this->Init();
		this->RunNum = _RunNum;
	}

	void Fill( KPEvent &event, TString TriggerTag )
	{
		Int_t LumiBlockNum = event.LumiBlockNum;
		vec_LumiBlockInfo[LumiBlockNum]->Fill( event, TriggerTag );
	}

	void CalcRate_EachLumiBlock()
	{
		for( auto& Info : this->vec_LumiBlockInfo )
			Info->Calc_Rate();
	}

private:
	void Init()
	{
		this->RunNum = 0;
		// -- 0-th content: dummy (to have consistent between vector index and exact lumi-block number) -- //
		for(Int_t i=0; i<nMaxLumiBlock+1; i++)
		{
			LumiBlockInfo* Info = new LumiBlockInfo( i );
			vec_LumiBlockInfo.push_back( Info );
		}
	}
};

class RunHistContainer
{
public:
	TString Tag;

	vector<TH1D*> vec_Hist;
	TH1D* h_LumiBlock_vs_nEvent;
	TH1D* h_LumiBlock_vs_nFiredEvent;
	TH1D* h_LumiBlock_vs_InstLumiMean;
	TH1D* h_LumiBlock_vs_nVerticesMean;
	TH1D* h_LumiBlock_vs_Rate;

	TH1D* h_LumiBlock_vs_nFiredEvent_UnPS;
	TH1D* h_LumiBlock_vs_Rate_UnPS;

	TH1D* h_LumiBlock_vs_nFiredEvent_UnPS_Scaled2e34;
	TH1D* h_LumiBlock_vs_Rate_UnPS_Scaled2e34;

	// -- just 1 bin -- //
	TH1D* h_TotalRate;
	TH1D* h_TotalRate_UnPS;
	TH1D* h_TotalRate_UnPS_Scaled2e34;

	Int_t nFiredEvent;
	Int_t nFiredEvent_UnPS;
	Double_t nFiredEvent_UnPS_Scaled2e34;
	Int_t nLumiBlock;
	Double_t TotalRate;
	Double_t TotalRate_UnPS;
	Double_t TotalRate_UnPS_Scaled2e34;

	RunHistContainer( TString _Tag )
	{
		this->Tag = _Tag;
		this->Init();
	}

	void Fill( LumiBlockInfo* Info )
	{
		Int_t LumiBlockNum = Info->LumiBlockNum; // -- same with bin number -- //

		this->h_LumiBlock_vs_nEvent->SetBinContent(LumiBlockNum, Info->nEvent );
		this->h_LumiBlock_vs_nEvent->SetBinError(LumiBlockNum, sqrt(Info->nEvent) );

		this->h_LumiBlock_vs_nFiredEvent->SetBinContent(LumiBlockNum, Info->nFiredEvent );
		this->h_LumiBlock_vs_nFiredEvent->SetBinError(LumiBlockNum, sqrt(Info->nFiredEvent) );

		this->h_LumiBlock_vs_InstLumiMean->SetBinContent(LumiBlockNum, Info->Mean_InstLumi );
		this->h_LumiBlock_vs_InstLumiMean->SetBinError(LumiBlockNum, 0 );

		this->h_LumiBlock_vs_nVerticesMean->SetBinContent(LumiBlockNum, Info->Mean_nVertices );
		this->h_LumiBlock_vs_nVerticesMean->SetBinError(LumiBlockNum, 0 );

		this->h_LumiBlock_vs_Rate->SetBinContent(LumiBlockNum, Info->Rate );
		this->h_LumiBlock_vs_Rate->SetBinError(LumiBlockNum, Info->Rate * (1.0 / sqrt(Info->nFiredEvent)) );

		// -- un-prescaled -- //
		this->h_LumiBlock_vs_nFiredEvent_UnPS->SetBinContent(LumiBlockNum, Info->nFiredEvent_UnPS );
		this->h_LumiBlock_vs_nFiredEvent_UnPS->SetBinError(LumiBlockNum, 0);

		this->h_LumiBlock_vs_Rate_UnPS->SetBinContent(LumiBlockNum, Info->Rate_UnPS );
		this->h_LumiBlock_vs_Rate_UnPS->SetBinError(LumiBlockNum, 0);

		// -- scaled to 2e34 -- //
		this->h_LumiBlock_vs_nFiredEvent_UnPS_Scaled2e34->SetBinContent(LumiBlockNum, Info->nFiredEvent_UnPS_Scaled2e34 );
		this->h_LumiBlock_vs_nFiredEvent_UnPS_Scaled2e34->SetBinError(LumiBlockNum, 0);

		this->h_LumiBlock_vs_Rate_UnPS_Scaled2e34->SetBinContent(LumiBlockNum, Info->Rate_UnPS_Scaled2e34 );
		this->h_LumiBlock_vs_Rate_UnPS_Scaled2e34->SetBinError(LumiBlockNum, 0);

		this->nFiredEvent += Info->nFiredEvent;
		this->nFiredEvent_UnPS += Info->nFiredEvent_UnPS;
		this->nFiredEvent_UnPS_Scaled2e34 += Info->nFiredEvent_UnPS_Scaled2e34;
		this->nLumiBlock += 1;
	}

	void Save( TFile *f_output )
	{
		// -- fill histogram for total rate -- //
		if( this->nLumiBlock == 0 )
		{
			this->TotalRate = 0;
			this->TotalRate_UnPS = 0;
			this->TotalRate_UnPS_Scaled2e34 = 0;
		}
		else
		{
			this->TotalRate = this->nFiredEvent / (this->nLumiBlock * LumiBlockTime);
			this->TotalRate_UnPS = this->nFiredEvent_UnPS / (this->nLumiBlock * LumiBlockTime);
			this->TotalRate_UnPS_Scaled2e34 = this->nFiredEvent_UnPS_Scaled2e34 / (this->nLumiBlock * LumiBlockTime);
		}

		this->h_TotalRate->SetBinContent(1, this->TotalRate);
		this->h_TotalRate->SetBinError(1, 0);

		this->h_TotalRate_UnPS->SetBinContent(1, this->TotalRate_UnPS);
		this->h_TotalRate_UnPS->SetBinError(1, 0);

		this->h_TotalRate_UnPS_Scaled2e34->SetBinContent(1, this->TotalRate_UnPS_Scaled2e34);
		this->h_TotalRate_UnPS_Scaled2e34->SetBinError(1, 0);

		f_output->cd();
		for( const auto& h : this->vec_Hist )
			h->Write();
	}
private:
	void Init()
	{
		this->h_LumiBlock_vs_nEvent = new TH1D("h_LumiBlock_vs_nEvent_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
		this->vec_Hist.push_back( this->h_LumiBlock_vs_nEvent );

		this->h_LumiBlock_vs_nFiredEvent = new TH1D("h_LumiBlock_vs_nFiredEvent_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
		this->vec_Hist.push_back( this->h_LumiBlock_vs_nFiredEvent );

		this->h_LumiBlock_vs_InstLumiMean = new TH1D("h_LumiBlock_vs_InstLumiMean_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
		this->vec_Hist.push_back( this->h_LumiBlock_vs_InstLumiMean );

		this->h_LumiBlock_vs_nVerticesMean = new TH1D("h_LumiBlock_vs_nVerticesMean_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
		this->vec_Hist.push_back( this->h_LumiBlock_vs_nVerticesMean );

		this->h_LumiBlock_vs_Rate = new TH1D("h_LumiBlock_vs_Rate_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
		this->vec_Hist.push_back( this->h_LumiBlock_vs_Rate );

		this->h_LumiBlock_vs_nFiredEvent_UnPS = new TH1D("h_LumiBlock_vs_nFiredEvent_UnPS_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
		this->vec_Hist.push_back( this->h_LumiBlock_vs_nFiredEvent_UnPS );

		this->h_LumiBlock_vs_Rate_UnPS = new TH1D("h_LumiBlock_vs_Rate_UnPS_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
		this->vec_Hist.push_back( this->h_LumiBlock_vs_Rate_UnPS );

		this->h_LumiBlock_vs_nFiredEvent_UnPS_Scaled2e34 = new TH1D("h_LumiBlock_vs_nFiredEvent_UnPS_Scaled2e34_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
		this->vec_Hist.push_back( this->h_LumiBlock_vs_nFiredEvent_UnPS_Scaled2e34 );

		this->h_LumiBlock_vs_Rate_UnPS_Scaled2e34 = new TH1D("h_LumiBlock_vs_Rate_UnPS_Scaled2e34_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
		this->vec_Hist.push_back( this->h_LumiBlock_vs_Rate_UnPS_Scaled2e34 );


		this->h_TotalRate = new TH1D("h_TotalRate_"+this->Tag, "", 1, 0, 1);
		this->vec_Hist.push_back( this->h_TotalRate );

		this->h_TotalRate_UnPS = new TH1D("h_TotalRate_UnPS_"+this->Tag, "", 1, 0, 1);
		this->vec_Hist.push_back( this->h_TotalRate_UnPS );

		this->h_TotalRate_UnPS_Scaled2e34 = new TH1D("h_TotalRate_UnPS_Scaled2e34_"+this->Tag, "", 1, 0, 1);
		this->vec_Hist.push_back( this->h_TotalRate_UnPS_Scaled2e34 );

		this->nFiredEvent = 0;
		this->nFiredEvent_UnPS = 0;
		this->nFiredEvent_UnPS_Scaled2e34 = 0;
		this->nLumiBlock = 0;
		this->TotalRate = 0;
		this->TotalRate_UnPS = 0;
		this->TotalRate_UnPS_Scaled2e34 = 0;
	}
};

class RateHistContainer
{
public:
	TString Tag;

	vector<TH1D*> vec_Hist;
	TH1D* h_TotalRate;
	TH1D* h_TotalRate_UnPS;
	TH1D* h_TotalRate_UnPS_Scaled2e34;

	Int_t nFiredEvent;
	Double_t nFiredEvent_UnPS;
	Double_t nFiredEvent_UnPS_Scaled2e34;

	Int_t nLumiBlock;
	Double_t TotalRate;
	Double_t TotalRate_UnPS;
	Double_t TotalRate_UnPS_Scaled2e34;

	vector<TH2D*> vec_2DHist;
	TH2D* h2D_Lumi_Rate;
	TH2D* h2D_Lumi_Rate_UnPS;
	TH2D* h2D_Lumi_Rate_UnPS_Scaled2e34;

	TH2D* h2D_nVertices_Rate;
	TH2D* h2D_nVertices_Rate_UnPS;
	TH2D* h2D_nVertices_Rate_UnPS_Scaled2e34;

	RateHistContainer( TString _Tag )
	{
		this->Tag = _Tag;
		this->Init();
	}

	void Fill( LumiBlockInfo *Info )
	{
		this->nFiredEvent += Info->nFiredEvent;
		this->nFiredEvent_UnPS += Info->nFiredEvent_UnPS;
		this->nFiredEvent_UnPS_Scaled2e34 += Info->nFiredEvent_UnPS_Scaled2e34;
		this->nLumiBlock += 1;

		this->h2D_Lumi_Rate->Fill( Info->Mean_InstLumi, Info->Rate );
		this->h2D_Lumi_Rate_UnPS->Fill( Info->Mean_InstLumi, Info->Rate_UnPS );
		this->h2D_Lumi_Rate_UnPS_Scaled2e34->Fill( Info->Mean_InstLumi, Info->Rate_UnPS_Scaled2e34 );

		this->h2D_nVertices_Rate->Fill( Info->Mean_nVertices, Info->Rate );
		this->h2D_nVertices_Rate_UnPS->Fill( Info->Mean_nVertices, Info->Rate_UnPS );
		this->h2D_nVertices_Rate_UnPS_Scaled2e34->Fill( Info->Mean_nVertices, Info->Rate_UnPS_Scaled2e34 );
	}

	void Save( TFile *f_output )
	{
		// -- fill histogram for total rate -- //
		if( this->nLumiBlock == 0 )
		{
			this->TotalRate = 0;
			this->TotalRate_UnPS = 0;
			this->TotalRate_UnPS_Scaled2e34 = 0;
		}
		else
		{
			this->TotalRate = this->nFiredEvent / (this->nLumiBlock * LumiBlockTime);
			this->TotalRate_UnPS = this->nFiredEvent_UnPS / (this->nLumiBlock * LumiBlockTime);
			this->TotalRate_UnPS_Scaled2e34 = this->nFiredEvent_UnPS_Scaled2e34 / (this->nLumiBlock * LumiBlockTime);
		}


		this->h_TotalRate->SetBinContent(1, this->TotalRate);
		this->h_TotalRate->SetBinError(1, 0);

		this->h_TotalRate_UnPS->SetBinContent(1, this->TotalRate_UnPS);
		this->h_TotalRate_UnPS->SetBinError(1, 0);

		this->h_TotalRate_UnPS_Scaled2e34->SetBinContent(1, this->TotalRate_UnPS_Scaled2e34);
		this->h_TotalRate_UnPS_Scaled2e34->SetBinError(1, 0);

		f_output->cd();
		for( const auto* h : this->vec_Hist )
			h->Write();

		for( const auto& h_2D : this->vec_2DHist )
			h_2D->Write();
	}
private:
	void Init()
	{
		this->h_TotalRate = new TH1D("h_TotalRate_"+this->Tag, "", 1, 0, 1 );
		this->vec_Hist.push_back( this->h_TotalRate );

		this->h_TotalRate_UnPS = new TH1D("h_TotalRate_UnPS_"+this->Tag, "", 1, 0, 1 );
		this->vec_Hist.push_back( this->h_TotalRate_UnPS );

		this->h_TotalRate_UnPS_Scaled2e34 = new TH1D("h_TotalRate_UnPS_Scaled2e34_"+this->Tag, "", 1, 0, 1 );
		this->vec_Hist.push_back( this->h_TotalRate_UnPS_Scaled2e34 );

		this->h2D_Lumi_Rate = new TH2D("h2D_Lumi_Rate_"+this->Tag, "", 2000, 1000 ,20000, 200, 0, 200 );
		this->vec_2DHist.push_back( this->h2D_Lumi_Rate );

		this->h2D_Lumi_Rate_UnPS = new TH2D("h2D_Lumi_Rate_UnPS_"+this->Tag, "", 2000, 1000 ,20000, 200, 0, 200 );
		this->vec_2DHist.push_back( this->h2D_Lumi_Rate_UnPS );

		this->h2D_Lumi_Rate_UnPS_Scaled2e34 = new TH2D("h2D_Lumi_Rate_UnPS_Scaled2e34_"+this->Tag, "", 2000, 1000 ,20000, 200, 0, 200 );
		this->vec_2DHist.push_back( this->h2D_Lumi_Rate_UnPS_Scaled2e34 );

		this->h2D_nVertices_Rate = new TH2D("h2D_nVertices_Rate_"+this->Tag, "", 100, 0, 100, 100, 0, 100 );
		this->vec_2DHist.push_back( this->h2D_nVertices_Rate );

		this->h2D_nVertices_Rate_UnPS = new TH2D("h2D_nVertices_Rate_UnPS_"+this->Tag, "", 100, 0, 100, 100, 0, 100 );
		this->vec_2DHist.push_back( this->h2D_nVertices_Rate_UnPS );

		this->h2D_nVertices_Rate_UnPS_Scaled2e34 = new TH2D("h2D_nVertices_Rate_UnPS_Scaled2e34_"+this->Tag, "", 100, 0, 100, 100, 0, 100 );
		this->vec_2DHist.push_back( this->h2D_nVertices_Rate_UnPS_Scaled2e34 );

		this->nFiredEvent = 0;
		this->nFiredEvent_UnPS = 0;
		this->nFiredEvent_UnPS_Scaled2e34 = 0;
		this->nLumiBlock = 0;
	}
};

class TriggerRateTool
{
public:
	vector<TString> vec_DataPath;
	vector<Int_t> vec_RunNumList;
	vector< RunHistContainer* > vec_RunHist;
	TString TriggerTag; // -- exact trigger expression -- //
	TString TriggerName;

	Bool_t debug;

	TFile *f_output;

	TriggerRateTool()
	{
		this->debug = kFALSE;
		this->TriggerTag = "";
		this->TriggerName = "";
		this->f_output = NULL;
	}

	void Set_DataList( vector<TString> _vec )
	{
		this->vec_DataPath = _vec;
	}

	void Set_RunNumList( vector<Int_t> _vec )
	{
		this->vec_RunNumList = _vec;

		// -- histogram for each run -- //
		cout << "Run list" << endl;
		Int_t nRun = (Int_t)this->vec_RunNumList.size();
		for(Int_t i=0; i<nRun; i++)
		{
			Int_t RunNum = vec_RunNumList[i];
			cout << RunNum << endl;

			TString Tag = TString::Format("Run%d", RunNum);
			RunHistContainer* Hist = new RunHistContainer( Tag );
			this->vec_RunHist.push_back( Hist );
		}
	}

	void Set_Trigger( TString _TriggerTag )
	{
		this->TriggerTag = _TriggerTag;
	}

	void Set_Output( TFile *_f_output )
	{
		this->f_output = _f_output;
	}

	void Analyze()
	{
		if( TriggerTag == "" || 
			this->f_output == NULL || 
			this->vec_DataPath.size() == 0 || 
			this->vec_RunNumList.size() == 0 )
		{
			cout << "Setup is not done accordingly!" << endl;
			return;
		}

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

		// -- initialize RunInfo -- //
		vector< RunInfo* > vec_RunInfo;
		Int_t nRun = (Int_t)this->vec_RunNumList.size();
		for(Int_t i=0; i<nRun; i++)
		{
			RunInfo* Info = new RunInfo( vec_RunNumList[i] );
			vec_RunInfo.push_back( Info );
		}

		RateHistContainer* RateHist = new RateHistContainer( TriggerTag );

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

			if( debug ) printf("(run, lumi, event) = (%d, %d, %llu)\n", event.RunNum, event.LumiBlockNum, event.EventNum );

			for(Int_t i=0; i<nRun; i++)
			{
				if( this->vec_RunNumList[i] == event.RunNum )
				{
					if( debug ) cout << "Find corresponding run number: " << this->vec_RunNumList[i] << endl;
					vec_RunInfo[i]->Fill( event, TriggerTag );
					break;
				}
			}

			if( debug ) cout << endl;
		} // -- end of event iteration -- //

		// -- fill histograms -- //
		for(Int_t i=0; i<nRun; i++)
		{
			vec_RunInfo[i]->CalcRate_EachLumiBlock();
			
			for( auto& LumiBlockInfo : vec_RunInfo[i]->vec_LumiBlockInfo )
			{
				// -- only for meaningful lumi-block -- //
				if( LumiBlockInfo->nEvent > 0 )
				{
					if( debug )
						printf("[Run=%d, LumiBlock=%d] (nEvent, nFiredEvent, Rate, Rate_UnPS, Rate_UnPS_Scaled2e34) = (%d, %d, %lf, %lf, %lf)\n",
							vec_RunInfo[i]->RunNum, LumiBlockInfo->LumiBlockNum, LumiBlockInfo->nEvent, LumiBlockInfo->nFiredEvent, LumiBlockInfo->Rate, LumiBlockInfo->Rate_UnPS, LumiBlockInfo->Rate_UnPS_Scaled2e34);

					// -- fill histogram for each run -- //
					vec_RunHist[i]->Fill( LumiBlockInfo );

					// -- fill histogram accumulated for all runs -- //
					RateHist->Fill( LumiBlockInfo );
				}
			} // -- iteration over all lumi-block in a run -- //

		} // -- iteration over all runs -- //

		this->f_output->cd();
		RateHist->Save( f_output );
		for(const auto& RunHist : vec_RunHist )
			RunHist->Save( f_output );

		// -- total run rates are calculated after save! -- //
		for( const auto& RunHist : vec_RunHist )
		{
			Double_t RunRate = RunHist->TotalRate;
			Double_t RunRate_UnPS = RunHist->TotalRate_UnPS;
			Double_t RunRate_UnPS_Scaled2e34 = RunHist->TotalRate_UnPS_Scaled2e34;
			printf("[%s] (run rate, un-prescaled run rate, un-prescaled run rate scaled w.r.t 2e34) = (%lf, %lf, %lf)\n",
				RunHist->Tag.Data(), RunRate, RunRate_UnPS, RunRate_UnPS_Scaled2e34);
		}

		Double_t TotalRate = RateHist->TotalRate;
		Double_t TotalRate_UnPS = RateHist->TotalRate_UnPS;
		Double_t TotalRate_UnPS_Scaled2e34 = RateHist->TotalRate_UnPS_Scaled2e34;
		printf("[Total] (rate, un-prescaled rate, un-prescaled rate scaled w.r.t 2e34) = (%lf, %lf, %lf)\n", TotalRate, TotalRate_UnPS, TotalRate_UnPS_Scaled2e34);

		cout << "finished" << endl;
	}

private:
	void Init()
	{

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