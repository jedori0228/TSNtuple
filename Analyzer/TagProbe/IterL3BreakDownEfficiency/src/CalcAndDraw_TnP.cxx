#include "TnPTool.h"
#include "canvas_margin.h"
#include "mylib.h"

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

void make_ratio(TH1D *hist_num, TH1D *hist_den){

  for(int i=1; i<=hist_num->GetXaxis()->GetNbins(); i++){

    double y_num = hist_num->GetBinContent(i);
    double e_num = hist_num->GetBinError(i);
    double y_den = hist_den->GetBinContent(i);
    double e_den = hist_den->GetBinError(i);

    double y_new = 0.;
    double e_new = 0.;

    if(y_den!=0){
      y_new = y_num/y_den;
      e_new = e_num/y_den;
    }

    //cout << y_num << "/" << y_den << " : " << y_new << endl;

    hist_num->SetBinContent(i, y_new);
    hist_num->SetBinError(i, e_new);

  }

}

void empty_hist(TH1D *hist_num){

  for(int i=1; i<=hist_num->GetXaxis()->GetNbins(); i++){

    hist_num->SetBinContent(i, 0.);
    hist_num->SetBinError(i, 0.);

  }

}

void CalcAndDraw_TnP()
{

  gStyle->SetOptStat(0);
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+"/NoL3MuonPt/";
  TString plotpath = ENV_PLOT_PATH+"/Efficiencies/NoL3MuonPt/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  //==== Variables
  vector<TString> vars = {
    "Pt", "Eta", "Phi", "Vtx",
  };
  vector<TString> varsForKP = {
    "pt", "eta", "phi", "vtx",
  };
  vector<TString> xtitle = {
    "p_{T} (GeV)", "#eta", "#phi", "# of Verticies",
  };


  //==== Objects

  int index_ratio_den = 3;
  vector<TString> IterL3MuonObjs = {
    "L2_OverL1",
    "IterL3OI_TK",
    "IterL3_FromL2_TK",
    "L3_OverL1",
    "HLTFilterMatched_OverL1__hltL3fL1sMu22Or25L1f0L2f10QL3Filtered27Q",
    "HLTFilterMatched_OverL1__hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07",
  };
  vector<Color_t> colors = {
    kGreen,
    kRed,
    kOrange-1,
    kBlack,
    kRed+3,
    kBlue,
  };
  vector<TString> IterL3MuonObjs_alias = {
    "(L2) / L1",
    "(IterL3 OI) / L1",
    "(IterL3 FromL2) / L1",
    "(L3) / L1",
    "(HLTFilter : Mu27) / L1",
    "(HLTFilter : IsoMu27) / L1",
  };
  TFile *file_KP_2016 = new TFile(filepath+"/ROOTFile_EfficiencyGraphs_Data.root");
  TFile *file_KP_2016_2 = new TFile(filepath+"/ROOTFile_EfficiencyGraphs_Data_WithoutTK.root");
  vector<int> widths = {
    3,
    3,
    3,
    1,
    2,
    2,
  };

  TLegend *lg = new TLegend(0.25, 0.05, 0.9, 0.30);
  //lg->SetBorderSize(0);
  //lg->SetFillStyle(0);

  TGraphAsymmErrors *lggr_KP = (TGraphAsymmErrors *)file_KP_2016->Get("Data_IsoMu27_OR_IsoTkMu27_from_L1_IsoMu27_and_Tight2012_and_dBeta_015_pt");
  lggr_KP->SetMarkerSize(0);
  lggr_KP->SetLineColor(kBlue);
  lg->AddEntry(lggr_KP, "(HLTFilter : IsoMu27 OR IsoTkMu27) / L1 (2016)", "ple");

  TGraphAsymmErrors *lggr_KP2 = (TGraphAsymmErrors *)file_KP_2016_2->Get("Data_IsoMu27_from_L1_IsoMu27_and_Tight2012_and_dBeta_015_pt");
  lggr_KP2->SetMarkerSize(0);
  lggr_KP2->SetLineColor(kMagenta);
  lg->AddEntry(lggr_KP2, "(HLTFilter : IsoMu27) / L1 (2016)", "ple");

  for(unsigned int i=0; i<IterL3MuonObjs.size(); i++){
    int j = IterL3MuonObjs.size()-1-i;
    TH1D *histlg = new TH1D("histlg_"+IterL3MuonObjs.at(j), "", 1, 0., 1.);
    histlg->SetLineColor(colors.at(j));
    histlg->SetLineWidth(widths.at(j));
    if(IterL3MuonObjs.at(j).Contains("HLTFilterMatched")) histlg->SetLineStyle(3);
    lg->AddEntry(histlg, IterL3MuonObjs_alias.at(j), "ple");
  }

  for(unsigned int it_var=0; it_var<vars.size(); it_var++){

    TString var = vars.at(it_var);

    TCanvas *c1 = new TCanvas("c1", "", 600, 600);
    TPad *c1_up;
    TPad *c1_down;
    c1_up = new TPad("c1_up", "", 0, 0.25, 1, 1);
    c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);

    canvas_margin(c1, c1_up, c1_down);

    c1_up->Draw();
    c1_down->Draw();

    //==== Top Pad
    c1_up->cd();
    TH1D *dummy_top = NULL;

    vector<TH1D *> hists;
    for(unsigned int it_obj=0; it_obj<IterL3MuonObjs.size(); it_obj++){

      TString obj = IterL3MuonObjs.at(it_obj);

      DrawingTool *tool = new DrawingTool(filepath+"Output_"+obj+".root");
      cout << IterL3MuonObjs_alias.at(it_obj) << "\t";
      TH1Ext *histext = tool->GetEfficiencyHistogram(var);

      TH1D *hist = histext->h;
      hists.push_back(hist);

      if(it_obj==0){
        dummy_top = (TH1D *)hist->Clone();
        dummy_top->SetLineWidth(0);
        dummy_top->SetLineColor(0);
        dummy_top->SetMarkerSize(0);
        dummy_top->SetMarkerColor(0);
        dummy_top->Draw("hist");
        dummy_top->GetYaxis()->SetTitle("Efficiency");
        if(var=="pt") dummy_top->GetYaxis()->SetRangeUser(0., 1.01);
        else dummy_top->GetYaxis()->SetRangeUser(0.50, 1.01);
      }

      TGraphAsymmErrors *gr = hist_to_graph(hist);
      gr->SetLineWidth(widths.at(it_obj));
      if(obj.Contains("HLTFilterMatched")) gr->SetLineStyle(3);
      gr->Draw("psame");
      gr->SetLineColor(colors.at(it_obj));

    }

    //==== KP's 2016 HLT/L1 eff : IsoMu27_OR_IsoTkMu27
    TGraphAsymmErrors *gr_KP = (TGraphAsymmErrors *)file_KP_2016->Get("Data_IsoMu27_OR_IsoTkMu27_from_L1_IsoMu27_and_Tight2012_and_dBeta_015_"+varsForKP.at(it_var));
    TH1D *hist_KP = graph_to_hist(gr_KP);
    gr_KP->SetMarkerSize(0);
    gr_KP->SetLineColor(kBlue);
    gr_KP->Draw("psame");

    TGraphAsymmErrors *gr_KP2 = (TGraphAsymmErrors *)file_KP_2016_2->Get("Data_IsoMu27_from_L1_IsoMu27_and_Tight2012_and_dBeta_015_"+varsForKP.at(it_var));
    TH1D *hist_KP2 = graph_to_hist(gr_KP2);
    gr_KP2->SetMarkerSize(0);
    gr_KP2->SetLineColor(kMagenta);
    gr_KP2->Draw("psame");




/*
    cout << "####### TEST #########" << endl;
    for(int aa=1;aa<=hists.at(4)->GetXaxis()->GetNbins();aa++){
      cout << hists.at(4)->GetBinContent(aa) << "\t" << hists.at(5)->GetBinContent(aa) <<" : " << hists.at(4)->GetBinContent(aa)/hists.at(5)->GetBinContent(aa) << endl;
    }
    cout << "########################" << endl;
*/

    //==== Bottom Pad
    c1_down->cd();
    TH1D *dummy_bottom = (TH1D *)hists.at(index_ratio_den)->Clone();
    empty_hist(dummy_bottom);
    dummy_bottom->SetLineWidth(0);
    dummy_bottom->SetLineColor(0);
    dummy_bottom->SetMarkerSize(0);
    dummy_bottom->SetMarkerColor(0);
    dummy_bottom->Draw("hist");
    dummy_bottom->GetYaxis()->SetRangeUser(0.80, 1.05);
    hist_axis(dummy_top, dummy_bottom);
    dummy_bottom->GetXaxis()->SetTitle(xtitle.at(it_var));
    dummy_bottom->GetYaxis()->SetTitle("Rel. to (L3)/L1");

    TH1D *hist_den = (TH1D *)hists.at(index_ratio_den)->Clone();
    for(unsigned int it_hist=0; it_hist<hists.size(); it_hist++){
      TH1D *this_hist = hists.at(it_hist);
      make_ratio(this_hist,hist_den);

      TGraphAsymmErrors *gr = hist_to_graph(this_hist);
      gr->SetLineWidth(widths.at(it_hist));
      if(IterL3MuonObjs.at(it_hist).Contains("HLTFilterMatched")) gr->SetLineStyle(3);
      gr->Draw("psame");
      gr->SetLineColor(colors.at(it_hist));

    }

    //==== KP
    make_ratio(hist_KP,hist_den);
    TGraphAsymmErrors *ratio_gr_hist_KP = hist_to_graph(hist_KP);
    ratio_gr_hist_KP->SetMarkerSize(0);
    ratio_gr_hist_KP->SetLineColor(kBlue);
    ratio_gr_hist_KP->Draw("psame");

    make_ratio(hist_KP2,hist_den);
    TGraphAsymmErrors *ratio_gr_hist_KP2 = hist_to_graph(hist_KP2);
    ratio_gr_hist_KP2->SetMarkerSize(0);
    ratio_gr_hist_KP2->SetLineColor(kMagenta);
    hist_KP2->SetLineColor(kMagenta);
    ratio_gr_hist_KP2->Draw("psame");

    //==== Draw Legend
    c1_up->cd();
    lg->Draw();

    c1->cd();
    TLatex latex_CMSPriliminary, latex_Lumi;
    latex_CMSPriliminary.SetNDC();
    latex_Lumi.SetNDC();
    latex_CMSPriliminary.SetTextSize(0.035);
    latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
    latex_Lumi.SetTextSize(0.035);
    //latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");
    latex_Lumi.DrawLatex(0.55, 0.96, "2017 RunF 305832-305862");

    //==== Save
    c1->SaveAs(plotpath+"/"+var+".pdf");
    c1->SaveAs(plotpath+"/"+var+".png");
    c1->Close();
  
  }

}
