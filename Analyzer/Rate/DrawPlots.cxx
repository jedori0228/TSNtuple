#include <Include/PlotTools.h>

class DrawingTool
{
public:
	TString FileName;
	TString TriggerTag;

	TH2D* h2D_Lumi_Rate;

	DrawingTool( TString _FileName, TString _TriggerTag )
	{
		this->Init();

		this->FileName = _FileName;
		this->TriggerTag = _TriggerTag;
		this->Get_Histogram();
	}

	void Draw_All()
	{
		this->Draw_Lumi_Rate();
	}

private:
	void Get_Histogram()
	{
		TString HistName_Lumi_Rate = "h2D_Lumi_Rate_"+this->TriggerTag;
		this->h2D_Lumi_Rate = Get_Hist_2D( FileName, HistName_Lumi_Rate );
	}

	void Draw_Lumi_Rate()
	{
		TString CanvasName = "Local/c_Lumi_Rate_"+this->TriggerTag;
		TCanvas *c;
		SetCanvas_Square( c, CanvasName );

		c->cd();
		this->h2D_Lumi_Rate->Draw("SCAT"); // -- scatter-plot -- //

		this->h2D_Lumi_Rate->SetStats(kFALSE);
		this->h2D_Lumi_Rate->SetXTitle("Inst. Lumi. [10^{30} cm^{-2}s^{-1}]");
		this->h2D_Lumi_Rate->SetYTitle( "Rate [Hz]");
		this->h2D_Lumi_Rate->SetMarkerStyle(20);
		this->h2D_Lumi_Rate->SetMarkerColor(kBlue);
		this->h2D_Lumi_Rate->SetMarkerSize(0.5);
		this->h2D_Lumi_Rate->GetXaxis()->SetTitleOffset(1.2);
		this->h2D_Lumi_Rate->GetYaxis()->SetTitleOffset(1.5);
		this->h2D_Lumi_Rate->GetXaxis()->SetRangeUser(5000, 15000);
		this->h2D_Lumi_Rate->GetYaxis()->SetRangeUser(0, 20);

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
	}

};

void DrawPlots( TString FileName, TString TriggerTag )
{
	DrawingTool* tool = new DrawingTool( FileName, TriggerTag );
	tool->Draw_All();
}