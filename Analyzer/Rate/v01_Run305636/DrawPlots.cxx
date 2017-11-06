#include <Include/PlotTools.h>

class DrawingTool
{
public:
	TString FileName;
	TString TriggerTag;

	TH2D* h2D_Lumi_Rate;
	TH2D* h2D_Lumi_Rate_Scaled2e34;

	TH2D* h2D_PU_Rate;
	TH2D* h2D_PU_Rate_Scaled2e34;

	DrawingTool( TString _FileName, TString _TriggerTag )
	{
		this->Init();

		this->FileName = _FileName;
		this->TriggerTag = _TriggerTag;
		this->Get_Histogram();
	}

	void Draw_All()
	{
		this->Draw_Lumi_Rate( this->h2D_Lumi_Rate );
		this->Draw_Lumi_Rate( this->h2D_Lumi_Rate_Scaled2e34 );

		this->Draw_PU_Rate( this->h2D_PU_Rate );
		this->Draw_PU_Rate( this->h2D_PU_Rate_Scaled2e34 );
	}

private:
	void Get_Histogram()
	{
		this->h2D_Lumi_Rate = Get_Hist_2D( FileName, "h2D_Lumi_Rate_UnPS_"+this->TriggerTag );
		this->h2D_Lumi_Rate_Scaled2e34 = Get_Hist_2D( FileName, "h2D_Lumi_Rate_UnPS_Scaled2e34_"+this->TriggerTag);

		this->h2D_PU_Rate = Get_Hist_2D( FileName, "h2D_PU_Rate_UnPS_"+this->TriggerTag );
		this->h2D_PU_Rate_Scaled2e34 = Get_Hist_2D( FileName, "h2D_PU_Rate_UnPS_Scaled2e34_"+this->TriggerTag);
	}

	void Draw_Lumi_Rate( TH2D* h_Lumi_Rate )
	{
		TString HistName = h_Lumi_Rate->GetName();
		TString CanvasName = "Local/"+HistName;
		CanvasName.ReplaceAll("h2D", "c");
		TCanvas *c;
		SetCanvas_Square( c, CanvasName );

		c->cd();
		h_Lumi_Rate->Draw("SCAT"); // -- scatter-plot -- //

		h_Lumi_Rate->SetStats(kFALSE);
		h_Lumi_Rate->SetXTitle("Inst. Lumi. [10^{30} cm^{-2}s^{-1}]");
		h_Lumi_Rate->SetYTitle( "Rate [Hz]");
		h_Lumi_Rate->SetMarkerStyle(20);
		h_Lumi_Rate->SetMarkerColor(kBlue);
		h_Lumi_Rate->SetMarkerSize(0.5);
		h_Lumi_Rate->GetXaxis()->SetTitleOffset(1.2);
		h_Lumi_Rate->GetYaxis()->SetTitleOffset(1.5);
		h_Lumi_Rate->GetXaxis()->SetRangeUser(1000, 20000);
		h_Lumi_Rate->GetYaxis()->SetRangeUser(0, 300);

		TLatex latex;
		Latex_Preliminary_NoDataInfo( latex );
		latex.DrawLatexNDC(0.76, 0.96, "#scale[0.8]{#font[42]{2017, 13 TeV}}");
		latex.DrawLatexNDC(0.16, 0.91, "#scale[0.6]{#font[62]{"+this->TriggerTag+"}}");

		c->SaveAs(".pdf");
	}

	void Draw_PU_Rate( TH2D* h_PU_Rate )
	{
		TString HistName = h_PU_Rate->GetName();
		TString CanvasName = "Local/"+HistName;
		CanvasName.ReplaceAll("h2D", "c");
		TCanvas *c;
		SetCanvas_Square( c, CanvasName );

		c->cd();
		h_PU_Rate->Draw("SCAT"); // -- scatter-plot -- //

		h_PU_Rate->SetStats(kFALSE);
		h_PU_Rate->SetXTitle("Pileup");
		h_PU_Rate->SetYTitle( "Rate [Hz]");
		h_PU_Rate->SetMarkerStyle(20);
		h_PU_Rate->SetMarkerColor(kBlue);
		h_PU_Rate->SetMarkerSize(0.5);
		h_PU_Rate->GetXaxis()->SetTitleOffset(1.2);
		h_PU_Rate->GetYaxis()->SetTitleOffset(1.5);
		h_PU_Rate->GetXaxis()->SetRangeUser(0, 100);
		h_PU_Rate->GetYaxis()->SetRangeUser(0, 300);

		TLatex latex;
		Latex_Preliminary_NoDataInfo( latex );
		latex.DrawLatexNDC(0.76, 0.96, "#scale[0.8]{#font[42]{2017, 13 TeV}}");
		latex.DrawLatexNDC(0.16, 0.91, "#scale[0.6]{#font[62]{"+this->TriggerTag+"}}");

		c->SaveAs(".pdf");
	}

private:
	void Init()
	{
		this->h2D_Lumi_Rate = NULL;
		this->h2D_Lumi_Rate_Scaled2e34 = NULL;

		this->h2D_PU_Rate = NULL;
		this->h2D_PU_Rate_Scaled2e34 = NULL;
	}

};

void DrawPlots( TString FileName, TString TriggerTag )
{
	DrawingTool* tool = new DrawingTool( FileName, TriggerTag );
	tool->Draw_All();
}