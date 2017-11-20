#include <TagProbe/TnPTool.h>

class DrawingTool
{
	TnPEffTool *effTool_noFix;
	TnPEffTool *effTool_PixelMiti;

	DrawingTool()
	{
		TString fileName_noFix = "";
		this->effTool_noFix = new TnPEffTool( fileName_noFix );

		TString fileName_PixelMiti = "";
		this->effTool_PixelMiti = new TnPEffTool( fileName_PixelMiti );
	}

	void ComparisonPlot_All()
	{
		this->ComparisonPlot( "Pt" );
		this->ComparisonPlot( "Eta" );
		this->ComparisonPlot( "Phi" );
		this->ComparisonPlot( "Vtx" );
	}

private:
	void ComparisonPlot( TString varName )
	{
		SampleInfo *sampleInfo_noFix = new SampleInfo( 1, "noFix", "Menu v4.0" );
		sampleInfo_noFix->SetColor( kBlack );

		SampleInfo *sampleInfo_PixelMiti = new SampleInfo( 1, "PixelMiti", "Menu v4.0 + Pixel mitigation" );
		sampleInfo_PixelMiti->SetColor( kRed );

		TString titleX = this->GetTitleX( varName );
		HistInfo *histInfo = new HistInfo( "", titleX, "Efficiency");

		TH1D* h_noFix = this->effTool_noFix->CalcTnPEff_CutAndCount( varName );
		TH1Ext *hext_noFix = new TH1Ext( sampleInfo_noFix, histInfo, h_noFix );

		TH1D* h_PixelMiti = this->effTool_PixelMiti->CalcTnPEff_CutAndCount( varName );
		TH1Ext *hext_PixelMiti = new TH1Ext( sampleInfo_PixelMiti, histInfo, h_PixelMiti );
		hext_PixelMiti->CalcRatio_DEN( hext_noFix->h );

		TCanvas *c; TPad *TopPad; TPad *BottomPad;
		TString canvasName = "c_noFix_vs_PixelMitigation_"+varName;
		SetCanvas_Ratio( c, canvasName, TopPad, BottomPad, 0, 0 );
		c->cd();
		TopPad->cd();

		hext_noFix->DrawAndSet( "EPSAME" );
		hext_PixelMiti->DrawAndSet( "EPSAME" );

		TLegend *legend;
		SetLegend( legend, 0.50, 0.80, 0.97, 0.95 );
		hext_noFix->AddToLegend( legend );
		hext_PixelMiti->AddToLegend( legend );
		legend->Draw();

		TLatex latex;
		Latex_Preliminary_NoDataInfo( latex );
		latex.DrawLatexNDC( 0.77, 0.96, "#scale[0.8]{#font[42]{2017, 13 TeV}}" );
		latex.DrawLatexNDC( 0.16, 0.91, "#scale[0.6]{#font[42]{IsoMu27}}" );

		c->cd();
		BottomPad->cd();

		hext_PixelMiti->DrawRatioAndSet( "EPSAME", "Red/Black", 0.9, 1.1 );

		TF1 *f_line;
		DrawLine( f_line );

		c->SaveAs(".pdf");
	}

	TString GetTitleX( TString  varName )
	{
		TString titleX = "";
		if( varName == "Pt" ) titleX = "Muon P_{T} (#mu) [GeV]";
		if( varName == "Eta" ) titleX = "#eta (#mu)";
		if( varName == "Phi" ) titleX = "#phi (#mu)";
		if( varName == "Vtx" ) titleX = "# vertex";
	}

};

void CalcAndDraw_TnP()
{
	DrawingTool* tool = new DrawingTool();
	tool->ComparisonPlot_All();	
}