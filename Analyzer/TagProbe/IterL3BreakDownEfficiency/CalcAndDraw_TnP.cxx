#include <TagProbe/TnPTool.h>

class DrawingTool
{
public:
	TnPEffTool *effTool;

	DrawingTool(TString filename)
	{
		this->effTool = new TnPEffTool( filename );
	}

	TH1Ext* GetEfficiencyHistogram( TString varName )
	{
		SampleInfo *sampleInfo = new SampleInfo( true, "IterL3OI_TK", "Iter L3 OI" );
		sampleInfo->SetColor( kBlack );

		TString titleX = this->GetTitleX( varName );
		HistInfo *histInfo = new HistInfo( "", titleX, "Efficiency");

		TH1D *hist_eff = this->effTool->CalcTnPEff_CutAndCount( varName );
		TH1Ext *histex_eff = new TH1Ext( sampleInfo, histInfo, hist_eff );

/*
		TCanvas *c; TPad *TopPad; TPad *BottomPad;
		TString canvasName = "c_"+varName;
		SetCanvas_Ratio( c, canvasName, TopPad, BottomPad, 0, 0 );
		c->cd();
		TopPad->cd();

		histex_eff->DrawAndSet( "EPSAME" );

		TLegend *legend;
		SetLegend( legend, 0.50, 0.80, 0.97, 0.95 );
		histex_eff->AddToLegend( legend );
		legend->Draw();

		TLatex latex;
		Latex_Preliminary_NoDataInfo( latex );
		latex.DrawLatexNDC( 0.77, 0.96, "#scale[0.8]{#font[42]{2017, 13 TeV}}" );
		latex.DrawLatexNDC( 0.16, 0.91, "#scale[0.6]{#font[42]{IsoMu27}}" );

		c->cd();
		BottomPad->cd();


		TF1 *f_line;
		DrawLine( f_line );

		c->SaveAs("test.pdf");
*/

    return histex_eff;
	}

	TString GetTitleX( TString  varName )
	{
		TString titleX = "";
		if( varName == "Pt" ) titleX = "Muon P_{T} (#mu) [GeV]";
		if( varName == "Eta" ) titleX = "#eta (#mu)";
		if( varName == "Phi" ) titleX = "#phi (#mu)";
		if( varName == "Vtx" ) titleX = "# vertex";

    return titleX;
	}

};

void CalcAndDraw_TnP()
{
/*
/data8/Users/jskim/CMSSW_9_2_14/src/TSNtuple/Analyzer/TagProbe/IterL3BreakDownEfficiency/Outputs
[jskim@cms2 Outputs]$ ls -1
Output_IterL3_FromL2_TK.root
Output_IterL3IO_FromL1.root
Output_IterL3IO_L2Seeded_TK.root
Output_IterL3OI_TK.root
*/

  TString filepath = "/data8/Users/jskim/CMSSW_9_2_14/src/TSNtuple/Analyzer/TagProbe/IterL3BreakDownEfficiency/Outputs/";

  DrawingTool* tool = new DrawingTool(filepath+"Output_IterL3_FromL2_TK.root");
  TH1Ext *histext = tool->GetEfficiencyHistogram("Pt");

  TCanvas *c1 = new TCanvas("c1", "", 600, 600);
  c1->cd();
  histext->DrawAndSet("hist");
  c1->SaveAs("test2.pdf");
  c1->Close();
  

}
