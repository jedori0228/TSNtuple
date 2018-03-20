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

  //cout << "[make_ratio] " << hist_num->GetName() << endl;

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

void CompareL3(int i=0)
{

  gStyle->SetOptStat(0);
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

/*
  TString filepath = ENV_FILE_PATH+"/";
  TString plotpath = ENV_PLOT_PATH+"/Efficiencies/180129_FromL1ExtendL1Seed_COMPARE/";
*/

  TString filepath = ENV_FILE_PATH+"/CMSSW_9_2_13/";
  TString plotpath = ENV_PLOT_PATH+"/Efficiencies/L3Comparison/";

  TString WhichObject = "L3_OverL1";
  if(i==1) WhichObject = "IterL3_FromL2_TK_OverL1";
  if(i==2) WhichObject = "IterL3OI_TK_OverL1";
  if(i==3) WhichObject = "L3_OverL1";
  if(i==4) WhichObject = "HLTFilterMatched_OverL1__hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07";

  plotpath += WhichObject+"/";

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

  vector<TString> IterL3MuonObjs = {

    "180302_v2018_oi_iofix_loose",
    "180302_v2018_oi_iofix_tight",
    "180227_HLT_IsoMu27_MasterTable100X",

    //"180221_IterL3v2018_NoChi2_OIFix_TrilpetLayerlistFix_NtuplerOriginal",
    //"180217_IterL3v2018_OIFix_TrilpetLayerlistFix_NtuplerOriginal",

    //"180214_IterL3_v2018_Ntuple_noID",
    //"180214_IterL3_v2018_Ntuple_withID",

    //"180216_IterL3_v2017_Ntuple_iterl3froml1_0triplet_2doublet_extendl1",  // == TkMu?
    //"180204_FromL1ExtendL1Seed_PixTrilpetFixL1L2",
    //"180204_FromL1ExtendL1Seed_PixTrilpetFix",
    //"180129_FromL1ExtendL1Seed",

    //"180216_IterL3_v2017_Ntuple_iterl3froml1_0triplet_2doublet",
    //"180204_PixTrilpetFixL1L2",
    //"180204_PixTrilpetFix",
    "CMSSW_9_2_13",
  };
  int index_ratio_den = IterL3MuonObjs.size()-1;

  vector<TString> IterL3MuonObjs_alias = {

    "IterL3 2018, cmssw 10x, Loose WP",
    "IterL3 2018, cmssw 10x, Tight WP",
    "IterL3 2018, cmssw 10x, Default",

    //"IterL3 2018, with ID (No Chi2), OI Fixed, trilplet layerlist Fixed",
    //"IterL3 2018, with ID, OI Fixed, trilplet layerlist Fixed",

    //"IterL3 2018, no ID",
    //"IterL3 2018, with ID",

    //"Use all L1, Fix L1 and L2 trilplet layerlist, Use Doublet",
    //"Use all L1, Fix L1 and L2 trilplet layerlist",
    //"Use all L1, Fix L1 trilplet layerlist",
    //"Use all L1, default pixel triplet",

    //"Use L1 not L2, Fix L1 and L2 pixel trilplet layerlist, Use Doublet",
    //"Use L1 not L2, Fix L1 and L2 pixel trilplet layerlist",
    //"Use L1 not L2, Fix L1 pixel trilplet layerlist",
    "Use L1 not L2, default pixel trilplet (default)",
  };
  vector<Color_t> colors = {

    kOrange,
    kRed,
    kBlue,

    //kBlue,
    //kBlue,

    //kViolet,
    //kViolet,

    //kBlue,
    //kOrange,
    //kBlue,
    //kBlack,

    //kOrange,
    //kRed,
    //kBlue,
    kBlack,
  };
  vector<int> widths = {

    2,
    2,
    2,

    //2,
    //2,

    //2,
    //2,

    //2,
    //2,
    //2,
    //2,

    //2,
    //2,
    //2,
    2,
  };
  vector<int> styles = {

    1,
    1,
    1,

    //3,
    //1,

    //3,
    //3,

    //1,
    //1,
    //3,
    //3,

    //1,
    //1,
    //1,
    1,
  };

  TFile *file_KP_2016 = new TFile(filepath+"/ROOTFile_EfficiencyGraphs_Data.root");
  TFile *file_KP_2016_2 = new TFile(filepath+"/ROOTFile_EfficiencyGraphs_Data_WithoutTK.root");

  TLegend *lg = new TLegend(0.25, 0.05, 0.9, 0.40);
  //lg->SetBorderSize(0);
  //lg->SetFillStyle(0);

/*
  TGraphAsymmErrors *lggr_KP = (TGraphAsymmErrors *)file_KP_2016->Get("Data_IsoMu27_OR_IsoTkMu27_from_L1_IsoMu27_and_Tight2012_and_dBeta_015_pt");
  lggr_KP->SetMarkerSize(0);
  lggr_KP->SetLineColor(kBlue);
  lg->AddEntry(lggr_KP, "(HLTFilter : IsoMu27 OR IsoTkMu27) / L1 (2016)", "ple");

  TGraphAsymmErrors *lggr_KP2 = (TGraphAsymmErrors *)file_KP_2016_2->Get("Data_IsoMu27_from_L1_IsoMu27_and_Tight2012_and_dBeta_015_pt");
  lggr_KP2->SetMarkerSize(0);
  lggr_KP2->SetLineColor(kMagenta);
  lg->AddEntry(lggr_KP2, "(HLTFilter : IsoMu27) / L1 (2016)", "ple");
*/

  for(unsigned int j=0; j<IterL3MuonObjs.size(); j++){
    TH1D *histlg = new TH1D("histlg_"+IterL3MuonObjs.at(j), "", 1, 0., 1.);
    histlg->SetLineColor(colors.at(j));
    histlg->SetLineWidth(widths.at(j));
    histlg->SetLineStyle(styles.at(j));
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
      TString thisfilepath = ENV_FILE_PATH+"/"+obj+"/";

      DrawingTool *tool = new DrawingTool(thisfilepath+"Output_"+WhichObject+".root");
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
        dummy_top->GetYaxis()->SetTitle("L3 / L1 Efficiency");
        if(i==4) dummy_top->GetYaxis()->SetTitle("IsoMu27 / L1 Efficiency");
        if(var=="pt") dummy_top->GetYaxis()->SetRangeUser(0., 1.01);
        else dummy_top->GetYaxis()->SetRangeUser(0.70, 1.01);
      }

      TGraphAsymmErrors *gr = hist_to_graph(hist);
      gr->SetLineWidth(widths.at(it_obj));
      gr->SetLineStyle(styles.at(it_obj));
      gr->Draw("psame");
      gr->SetLineColor(colors.at(it_obj));

    }

/*
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
*/

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
    dummy_bottom->GetYaxis()->SetRangeUser(0.98, 1.05);
    hist_axis(dummy_top, dummy_bottom);
    dummy_bottom->GetXaxis()->SetTitle(xtitle.at(it_var));
    dummy_bottom->GetYaxis()->SetTitle("Rel. to default");

    TH1D *hist_den = (TH1D *)hists.at(index_ratio_den)->Clone();
    for(unsigned int it_hist=0; it_hist<hists.size(); it_hist++){

      if(it_hist==index_ratio_den) continue;

      TH1D *this_hist = hists.at(it_hist);
      make_ratio(this_hist,hist_den);

      TGraphAsymmErrors *gr = hist_to_graph(this_hist);
      gr->SetLineWidth(widths.at(it_hist));
      gr->SetLineStyle(styles.at(it_hist));
      gr->Draw("psame");
      gr->SetLineColor(colors.at(it_hist));

    }
    double x_1[2], y_1[2];
    x_1[0] = 5000;  y_1[0] = 1;
    x_1[1] = -5000;  y_1[1] = 1;
    TGraph *g1 = new TGraph(2, x_1, y_1);
    g1->Draw("same");

/*
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
*/

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
