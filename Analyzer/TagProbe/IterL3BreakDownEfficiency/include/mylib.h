TGraphAsymmErrors* hist_to_graph(TH1D* hist, bool YErrorZero=false){

  TH1::SetDefaultSumw2(true);

  int Nbins = hist->GetXaxis()->GetNbins();
  double x[Nbins], y[Nbins], xlow[Nbins], xup[Nbins], ylow[Nbins], yup[Nbins];
  TAxis *xaxis = hist->GetXaxis();
  for(Int_t i=0; i<Nbins; i++){
    x[i] = xaxis->GetBinCenter(i+1);
    y[i] = hist->GetBinContent(i+1);
    xlow[i] = xaxis->GetBinCenter(i+1)-xaxis->GetBinLowEdge(i+1);
    xup[i] = xaxis->GetBinUpEdge(i+1)-xaxis->GetBinCenter(i+1);
    ylow[i] = hist->GetBinError(i+1);
    yup[i] = hist->GetBinError(i+1);
    if(YErrorZero){
      ylow[i] = 0;
      yup[i] = 0;
    }
    //ylow[i] = 0;
    //yup[i] = 0;
    //cout << "x = " << x[i] << ", y = " << y[i] << ", x_low = " << xlow[i] << ", xup = " << xup[i] << ", ylow = " << ylow[i] << ", yup = " << yup[i] << endl;
  }
  TGraphAsymmErrors *out = new TGraphAsymmErrors(Nbins, x, y, xlow, xup, ylow, yup);
  out->SetTitle("");
  return out;

}

TGraphAsymmErrors* hist_to_graph(TH1D* hist, int n_skip_x_left){

  TH1::SetDefaultSumw2(true);

  int Nbins = hist->GetXaxis()->GetNbins()-n_skip_x_left;
  double x[Nbins], y[Nbins], xlow[Nbins], xup[Nbins], ylow[Nbins], yup[Nbins];
  TAxis *xaxis = hist->GetXaxis();
  for(Int_t i=1; i<=Nbins; i++){
    x[i-1] = xaxis->GetBinCenter(i+n_skip_x_left);
    y[i-1] = hist->GetBinContent(i+n_skip_x_left);
    xlow[i-1] = xaxis->GetBinCenter(i+n_skip_x_left)-xaxis->GetBinLowEdge(i+n_skip_x_left);
    xup[i-1] = xaxis->GetBinUpEdge(i+n_skip_x_left)-xaxis->GetBinCenter(i+n_skip_x_left);
    ylow[i-1] = hist->GetBinError(i+n_skip_x_left);
    yup[i-1] = hist->GetBinError(i+n_skip_x_left);
    //ylow[i-1] = 0;
    //yup[i-1] = 0;
    //cout << "x = " << x[i-1] << ", y = " << y[i-1] << ", x_low = " << xlow[i-1] << ", xup = " << xup[i-1] << ", ylow = " << ylow[i-1] << ", yup = " << yup[i-1] << endl;
  }
  TGraphAsymmErrors *out = new TGraphAsymmErrors(Nbins, x, y, xlow, xup, ylow, yup);
  out->SetTitle("");
  return out;

}

TGraphAsymmErrors* hist_to_graph(TH1D* hist, int n_skip_x_left, int n_x_shift, int i_x_shift){

  TH1::SetDefaultSumw2(true);

  int Nbins = hist->GetXaxis()->GetNbins()-n_skip_x_left;
  double x[Nbins], y[Nbins], xlow[Nbins], xup[Nbins], ylow[Nbins], yup[Nbins];
  TAxis *xaxis = hist->GetXaxis();
  for(Int_t i=1; i<=Nbins; i++){
    x[i-1] = xaxis->GetBinCenter(i+n_skip_x_left);
    y[i-1] = hist->GetBinContent(i+n_skip_x_left);
    xlow[i-1] = xaxis->GetBinCenter(i+n_skip_x_left)-xaxis->GetBinLowEdge(i+n_skip_x_left);
    xup[i-1] = xaxis->GetBinUpEdge(i+n_skip_x_left)-xaxis->GetBinCenter(i+n_skip_x_left);
    ylow[i-1] = hist->GetBinError(i+n_skip_x_left);
    yup[i-1] = hist->GetBinError(i+n_skip_x_left);

    double dx = (xaxis->GetBinUpEdge(i+n_skip_x_left)-xaxis->GetBinLowEdge(i+n_skip_x_left))/double(n_x_shift+1);
    x[i-1] = xaxis->GetBinLowEdge(i+n_skip_x_left) + double(i_x_shift+1) * dx;
    xlow[i-1] = double(i_x_shift+1) * dx;
    xup[i-1] = xaxis->GetBinUpEdge(i+n_skip_x_left)-x[i-1];

    //ylow[i-1] = 0;
    //yup[i-1] = 0;
    //cout << "x = " << x[i-1] << ", y = " << y[i-1] << ", x_low = " << xlow[i-1] << ", xup = " << xup[i-1] << ", ylow = " << ylow[i-1] << ", yup = " << yup[i-1] << endl;
  }
  TGraphAsymmErrors *out = new TGraphAsymmErrors(Nbins, x, y, xlow, xup, ylow, yup);
  out->SetTitle("");
  return out;

}


TGraphAsymmErrors* GraphSubtract(TGraphAsymmErrors *a, TGraphAsymmErrors *b, bool Rel){

  //==== do a-b

  int NX = a->GetN();
  TGraphAsymmErrors* gr_out = (TGraphAsymmErrors*)a->Clone();

  for(int i=0; i<NX; i++){

    double a_x, a_y, b_x, b_y;

    a->GetPoint(i, a_x, a_y);
    b->GetPoint(i, b_x, b_y);

    if(Rel==true){
      gr_out->SetPoint( i, a_x, (a_y-b_y)/b_y );
    }
    else{
      gr_out->SetPoint( i, a_x, a_y-b_y );
    }

  }

  return gr_out;

}

void RemoveLargeError(TGraphAsymmErrors *a){

  int NX = a->GetN();

  for(int i=0; i<NX; i++){

    double x, y, yerr_low, yerr_high;

    a->GetPoint(i, x, y);
    yerr_low  = a->GetErrorYlow(i);
    yerr_high = a->GetErrorYhigh(i);

    if(y+yerr_high==1.){
      a->SetPointEYhigh( i, yerr_low );
    }

  }

}

void ScaleGraph(TGraphAsymmErrors *a, double c){

  int NX = a->GetN();

  for(int i=0; i<NX; i++){

    double x, y, yerr_low, yerr_high;

    a->GetPoint(i, x, y);
    yerr_low  = a->GetErrorYlow(i);
    yerr_high = a->GetErrorYhigh(i);

    a->SetPoint(i, x, c*y);
    a->SetPointEYlow(i, c*yerr_low);
    a->SetPointEYhigh(i, c*yerr_high);

  }

}



double GetMaximum(TH1D* hist){

  TAxis *xaxis = hist->GetXaxis();

  double maxval(-1.);
  for(int i=1; i<=xaxis->GetNbins(); i++){
    if( hist->GetBinContent(i) + hist->GetBinError(i) > maxval ){
      maxval = hist->GetBinContent(i) + hist->GetBinError(i);
    }
  }

  return maxval;

}

double GetMaximum(TGraphAsymmErrors *a){

  int NX = a->GetN();

  double maxval(-9999.);
  for(int i=0; i<NX; i++){

    double x, y, yerr_low, yerr_high;

    a->GetPoint(i, x, y);
    yerr_low  = a->GetErrorYlow(i);
    yerr_high = a->GetErrorYhigh(i);

    if( y+yerr_high > maxval ){
      maxval = y+yerr_high;
    }

  }

  return maxval;

}

double GetYieldSystematics(TH1D *hist){

  int n_syst = hist->GetXaxis()->GetNbins();
  int n_source = (n_syst-1)/2;

  //==== Bin index
  //==== i=1 : central
  //==== i=2 : _MuonEn_up
  //==== i=3 : _MuonEn_down
  //==== -> n_syst = 3
  //==== -> n_source = (n_syst-1)/2 = (3-1)/2 = 1

  double y_central = hist->GetBinContent(1);

  double sum_syst = 0.;
  for(int i=1; i<=n_source; i++){
    double yield_up = hist->GetBinContent(i*2);
    double yield_down = hist->GetBinContent(i*2+1);

    double syst_up = fabs(yield_up-y_central);
    double syst_down = fabs(yield_down-y_central);

    sum_syst += 0.5*(syst_up*syst_up+syst_down*syst_down);

  }

  return sqrt(sum_syst);

}

TDirectory *MakeTemporaryDirectory(){

  gROOT->cd();
  TDirectory* tempDir = 0;
  int counter = 0;
  while (not tempDir) {
    // First, let's find a directory name that doesn't exist yet:
    std::stringstream dirname;
    dirname << "HNCommonLeptonFakes_%i" << counter;
    if (gROOT->GetDirectory((dirname.str()).c_str())) {
      ++counter;
      continue;
    }
    // Let's try to make this directory:
    tempDir = gROOT->mkdir((dirname.str()).c_str());

  }

  return tempDir;

}

TH1D *graph_to_hist(TGraph *gr){

  int Nbins = gr->GetN();
  double x[Nbins+1];

  double *gr_X = gr->GetX();
  double *gr_EXlow = gr->GetEXlow();
  double *gr_EXhigh = gr->GetEXhigh();
  double *gr_Y = gr->GetY();
  double *gr_EYlow = gr->GetEYlow();
  double *gr_EYhigh = gr->GetEYhigh();

  x[0] = gr_X[0]-gr_EXlow[0];

  for(int i=0; i<Nbins; i++){
    x[i+1] = gr_X[i]+gr_EXhigh[i];
    //cout << x[i+1] << endl;
  }

  TH1D *out = new TH1D(gr->GetName(), "", Nbins, x);
  for(int i=1; i<=Nbins; i++){
    out->SetBinContent(i, gr_Y[i-1]);
    out->GetBinError(i, min(gr_EYlow[i-1],gr_EYhigh[i-1]));
  }

  return out;
}




