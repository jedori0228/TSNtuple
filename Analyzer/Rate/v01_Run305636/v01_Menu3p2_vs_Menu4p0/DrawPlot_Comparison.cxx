#include <Include/PlotTools.h>

class DrawingTool
{
public:
	SampleInfo *sampleInfo_Menu3p2;
	SampleInfo *sampleInfo_Menu4p0;
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
		TH2D* h_Menu3p2 = Get_Hist_2D( this->sampleInfo_Menu3p2->fileName, histInfo->name );
		h_Menu3p2->SetStats(kFALSE);
		h_Menu3p2->SetMarkerStyle(20);
		h_Menu3p2->SetMarkerSize(1);
		h_Menu3p2->SetMarkerColor(this->sampleInfo_Menu3p2->color);
		h_Menu3p2->SetLineColorAlpha( kWhite, 0 );

		TH2D* h_Menu4p0 = Get_Hist_2D( this->sampleInfo_Menu4p0->fileName, histInfo->name );
		h_Menu4p0->SetStats(kFALSE);
		h_Menu4p0->SetMarkerStyle(24);
		h_Menu4p0->SetMarkerSize(1);
		h_Menu4p0->SetMarkerColor(this->sampleInfo_Menu4p0->color);
		h_Menu4p0->SetLineColorAlpha( kWhite, 0 );

		TCanvas *c;
		TString CanvasName = histInfo->name;
		CanvasName.ReplaceAll("h2D_", "Local/c2D_");
		SetCanvas_Square( c, CanvasName );

		c->cd();
		h_Menu3p2->Draw("SCAT"); // -- scatter-plot -- //
		h_Menu4p0->Draw("SCATSAME");

		TLegend *legend;
		SetLegend( legend );
		legend->AddEntry( h_Menu3p2, this->sampleInfo_Menu3p2->fullName );
		legend->AddEntry( h_Menu4p0, this->sampleInfo_Menu4p0->fullName );
		legend->Draw();

		h_Menu3p2->SetXTitle( histInfo->titleX );
		h_Menu3p2->SetYTitle( histInfo->titleY );

		h_Menu3p2->GetXaxis()->SetTitleOffset(1.2);
		h_Menu3p2->GetYaxis()->SetTitleOffset(1.5);
		if( histInfo->hasXRange ) h_Menu3p2->GetXaxis()->SetRangeUser(histInfo->minX, histInfo->maxX);
		if( histInfo->hasYRange ) h_Menu3p2->GetYaxis()->SetRangeUser(histInfo->minY, histInfo->maxY);

		TLatex latex;
		Latex_Preliminary_NoDataInfo( latex );
		latex.DrawLatexNDC(0.75, 0.96, "#scale[0.8]{#font[42]{2017, 13 TeV}}");
		latex.DrawLatexNDC(0.16, 0.91, "#scale[0.6]{#font[62]{"+this->trigFullName+"}}");

		c->SaveAs(".pdf");		
		c->SaveAs(".png");
	}

	void Init()
	{
		// -- sample info -- //
		this->sampleInfo_Menu3p2 = new SampleInfo(1, "Menu3p2", "HLT menu v3.2");
		this->sampleInfo_Menu3p2->SetFileName( "../Local/v20171103_013001_MuonTriggerRate_Menu3p2_nDataset7/ROOTFile_MuonTriggerRate_"+this->trigFullName+".root" );
		this->sampleInfo_Menu3p2->SetColor( kBlack );

		this->sampleInfo_Menu4p0 = new SampleInfo(1, "Menu4p0", "HLT menu v4.0");
		this->sampleInfo_Menu4p0->SetFileName( "../Local/v20171102_084733_MuonTriggerRate_withoutFix_nDataSet8/ROOTFile_MuonTriggerRate_"+this->trigFullName+".root" );
		this->sampleInfo_Menu4p0->SetColor( kRed );

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