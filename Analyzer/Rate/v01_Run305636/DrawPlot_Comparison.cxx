#include <Include/PlotTools.h>

class DrawingTool
{
public:
	SampleInfo *sampleInfo_noFix;
	SampleInfo *sampleInfo_withFix;
	vector< HistInfo* > vec_HistInfo;

	TString trigFullName;

	DrawingTool()
	{

	}

	DrawingTool( TString _trigFullName ): DrawingTool()
	{
		this->trigFullName = _trigFullName;
		this->Init();
	}

	void DrawAll()
	{
		for( const auto & histInfo : vec_HistInfo )
		{
			this->Draw( histInfo );
		}
	}
private:
	void Draw( HistInfo* histInfo )
	{
		TH2Ext* h_noFix = new TH2Ext( this->sampleInfo_noFix, histInfo );
		TH2Ext* h_withFix = new TH2Ext( this->sampleInfo_withFix, histInfo );

		TCanvas *c;
		TString CanvasName = histInfo->name;
		CanvasName.ReplaceAll("h2D_", "Local/c2D_");
		SetCanvas_Square( c, CanvasName );

		c->cd();
		h_noFix->DrawAndSet("SCAT"); // -- scatter-plot -- //
		h_withFix->DrawAndSet("SCATSAME");
		h_withFix->h->SetMarkerStyle( 24 );

		TLegend *legend;
		SetLegend( legend );
		h_noFix->AddToLegend( legend );
		h_withFix->AddToLegend( legend );
		legend->Draw();

		TLatex latex;
		Latex_Preliminary_NoDataInfo( latex );
		latex.DrawLatexNDC(0.75, 0.96, "#scale[0.8]{#font[42]{2017, 13 TeV}}");
		latex.DrawLatexNDC(0.16, 0.91, "#scale[0.6]{#font[62]{"+this->trigFullName+"}}");

		c->SaveAs(".pdf");		
		c->SaveAs(".png");


		// TH2D* h_noFix = Get_Hist_2D( this->sampleInfo_noFix->fileName, histInfo->name );
		// h_noFix->SetStats(kFALSE);
		// h_noFix->SetMarkerStyle(20);
		// h_noFix->SetMarkerSize(1);
		// h_noFix->SetMarkerColor(this->sampleInfo_noFix->color);
		// h_noFix->SetLineColorAlpha( kWhite, 0 );

		// TH2D* h_withFix = Get_Hist_2D( this->sampleInfo_withFix->fileName, histInfo->name );
		// h_withFix->SetStats(kFALSE);
		// h_withFix->SetMarkerStyle(24);
		// h_withFix->SetMarkerSize(1);
		// h_withFix->SetMarkerColor(this->sampleInfo_withFix->color);
		// h_withFix->SetLineColorAlpha( kWhite, 0 );

		// TCanvas *c;
		// TString CanvasName = histInfo->name;
		// CanvasName.ReplaceAll("h2D_", "Local/c2D_");
		// SetCanvas_Square( c, CanvasName );

		// c->cd();
		// h_noFix->Draw("SCAT"); // -- scatter-plot -- //
		// h_withFix->Draw("SCATSAME");

		// TLegend *legend;
		// SetLegend( legend );
		// legend->AddEntry( h_noFix, this->sampleInfo_noFix->fullName );
		// legend->AddEntry( h_withFix, this->sampleInfo_withFix->fullName );
		// legend->Draw();

		// h_noFix->SetXTitle( histInfo->titleX );
		// h_noFix->SetYTitle( histInfo->titleY );

		// h_noFix->GetXaxis()->SetTitleOffset(1.2);
		// h_noFix->GetYaxis()->SetTitleOffset(1.5);
		// if( histInfo->hasXRange ) h_noFix->GetXaxis()->SetRangeUser(histInfo->minX, histInfo->maxX);
		// if( histInfo->hasYRange ) h_noFix->GetYaxis()->SetRangeUser(histInfo->minY, histInfo->maxY);

		// TLatex latex;
		// Latex_Preliminary_NoDataInfo( latex );
		// latex.DrawLatexNDC(0.75, 0.96, "#scale[0.8]{#font[42]{2017, 13 TeV}}");
		// latex.DrawLatexNDC(0.16, 0.91, "#scale[0.6]{#font[62]{"+this->trigFullName+"}}");

		// c->SaveAs(".pdf");		
		// c->SaveAs(".png");
	}

	void Init()
	{
		// -- sample info -- //
		this->sampleInfo_noFix = new SampleInfo(1, "Before", "Before update");
		this->sampleInfo_noFix->SetFileName( "./Local/v20171102_084733_MuonTriggerRate_withoutFix_nDataSet8/ROOTFile_MuonTriggerRate_"+this->trigFullName+".root" );
		this->sampleInfo_noFix->SetColor( kBlack );

		this->sampleInfo_withFix = new SampleInfo(1, "After", "After update");
		this->sampleInfo_withFix->SetFileName( "./Local/v20171103_012749_MuonTriggerRate_withFix_nDataset8/ROOTFile_MuonTriggerRate_"+this->trigFullName+".root" );
		this->sampleInfo_withFix->SetColor( kRed );

		// -- hist info -- //
		HistInfo* histInfo_PUvsRate = new HistInfo("h2D_PU_Rate_UnPS_"+this->trigFullName, "Pileup", "Rate [Hz]");
		histInfo_PUvsRate->SetXRange(0, 80);
		histInfo_PUvsRate->SetYRange(0, 350);
		this->vec_HistInfo.push_back( histInfo_PUvsRate );

		HistInfo* histInfo_LumivsRate = new HistInfo("h2D_Lumi_Rate_UnPS_"+this->trigFullName, "Inst. Lumi. [10^{30} cm^{-2}s^{-1}]", "Rate [Hz]");
		histInfo_LumivsRate->SetXRange(1000, 20000);
		histInfo_LumivsRate->SetYRange(0, 350);
		this->vec_HistInfo.push_back( histInfo_LumivsRate );
	}

};

void DrawPlot_Comparison( TString trig )
{
	DrawingTool *tool = new DrawingTool( trig );
	tool->DrawAll();
}