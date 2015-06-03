/*
 * Fit.cpp
 *
 *  Created on: Dec 24, 2013
 *      Author: N.Berry
 */

#include "../../interface/Objects/Fit.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLatex.h"
#include "TLine.h"
#include "TObjArray.h"
#include "TVirtualFitter.h"
#include <sstream>
#include <iomanip>
#include <math.h>

#include "../../interface/Objects/Photons.h"

namespace std {


void fcn(int& npar, double* deriv, double& f, double par[], int flag){

		TObjArray* fithistos =  static_cast<TObjArray*> (TVirtualFitter::GetFitter()->GetObjectFit());

		double lnL = 0.0;

		TH1D* data = static_cast<TH1D*>(fithistos->At(0));
	    TH1D* top_fit = static_cast<TH1D*>(fithistos->At(1));
	    TH1D* bg_fit = static_cast<TH1D*>(fithistos->At(2));
	    TH1D* qcd_fit = static_cast<TH1D*>(fithistos->At(3));

	    double Nsignal = top_fit->Integral();
	    double Nvjets = bg_fit->Integral();
	    double Nqcd = qcd_fit->Integral();

	  for (int i=0; i< data->GetNbinsX(); i++){
	    //data_i is the observed number of events in each bin
	    int data_i = data->GetBinContent(i+1);
	    //xi is the expected number of events in each bin

	    double xi = par[0]*(top_fit->GetBinContent(i+1)/Nsignal) + par[1]*(bg_fit->GetBinContent(i+1)/Nvjets);


	    if(data_i !=0 && xi != 0){
	      lnL += log(TMath::Poisson(data_i, xi));
	    }

	  }

	  f = -2.0 * lnL;

	  //constraints
//	   double nvjets_err =Nvjets*0.5;
	   double nqcd_err = Nqcd*1.;
//	cout << "LL: " << lnL << endl;
//	cout << "nsig: " << Nsignal << " ,par0: " << par[0] << endl;
//	cout << "nvjets: " << Nvjets << " ,par1: " << par[1] << endl;
//	cout << "nqcd: " << Nqcd << " ,par2: " << par[2] << endl;

//	  f += ((par[2]-Nqcd)*(par[2]-Nqcd))/(nqcd_err*nqcd_err);
//	  f += ((par[1]-Nvjets)*(par[1]-Nvjets))/(nvjets_err*nvjets_err);

}

Fit::Fit() {
	channel = "EMu";
	selection = "TTbarPhotonAnalysis/"+channel+"/Ref selection/Photons/SignalPhotons/";
	folder = "Fits";
}

Fit::~Fit() {

}


void Fit::allFits(){
	Variable RandConeChIso("Photon_RandConeChIso_barrel", "Random Cone Isolation", -5, 20, 2);
	Variable SCFRChargedhadronIso("Photon_RhoCorrectedSCChIso_barrel", "(#rho-corr) SCFR Charge Hadron Isolation", -5, 20, 2);
	//fits only save standard plot if doFit 3rd arg is "central"

	std::vector<double> xsects;
	std::vector<TString> names;
	//could perhaps turn this into an iterator over all samples
	AllSamples samples("central", "");
	xsects.push_back(readAndFit(samples, RandConeChIso, "central"));
	names.push_back("central");

// 	AllSamples jesDown("JES_down", "_minusJES", "");
// 	xsects.push_back(readAndFit(jesDown, absEta, "JES_down"));
// 	names.push_back("JES_down");
// 
// 	AllSamples jesUp("JES_up", "_plusJES", "");
// 	xsects.push_back(readAndFit(jesUp, absEta, "JES_up"));
// 	names.push_back("JES_up");
// 
// 	AllSamples jerDown("JER_down", "_minusJER", "");
// 	xsects.push_back(readAndFit(jerDown, absEta, "JER_down"));
// 	names.push_back("JER_down");
// 
// 	AllSamples jerUp("JER_up", "_plusJER", "");
// 	xsects.push_back(readAndFit(jerUp, absEta, "JER_up"));
// 	names.push_back("JER_up");
// 
// 	AllSamples pudown("PU_down", "_PU_65835mb", "");
// 	xsects.push_back(readAndFit(pudown, absEta, "PU_down"));
// 	names.push_back("PU_down");
// 
// 	AllSamples puUp("PU_up", "_PU_72765mb", "");
// 	xsects.push_back(readAndFit(puUp, absEta, "PU_up"));
// 	names.push_back("PU_up");
// 
// 	AllSamples bjetDown("BJet_down", "_minusBJet", "");
// 	xsects.push_back(readAndFit(bjetDown, absEta, "BJet_down"));
// 	names.push_back("BJet_down");
// 
// 	AllSamples bjetUp("BJet_up", "_plusBjet", "");
// 	xsects.push_back(readAndFit(bjetUp, absEta, "BJet_up"));
// 	names.push_back("BJet_up");
// 
// 	AllSamples scaleDown("central", "", "_scaledown");
// 	xsects.push_back(readAndFit(scaleDown, absEta, "Scale_down"));
// 	names.push_back("Scale_down");
// 
// 	AllSamples scaleUp("central", "", "_scaleup");
// 	xsects.push_back(readAndFit(scaleUp, absEta, "Scale_up"));
// 	names.push_back("Scale_up");
// 
// 	AllSamples matchDown("central", "", "_matchingdown");
// 	xsects.push_back(readAndFit(matchDown, absEta, "Match_down"));
// 	names.push_back("Match_down");
// 
// 	AllSamples matchUp("central", "", "_matchingup");
// 	xsects.push_back(readAndFit(matchUp, absEta, "Scale_up"));
// 	names.push_back("Match_up");

//	AllSamples ljetUp("LightJet_up", "_plusLightJet");
//	xsects.push_back(readAndFit(ljetUp, absEta, "LightJet_up"));
//
//	AllSamples ljetDown("LightJet_down", "_minusLightJet");
//	xsects.push_back(readAndFit(ljetDown, absEta, "LightJet_down"));

//	double error_up = 0;
//	double error_down = 0;
//	for(unsigned int i = 1; i < xsects.size(); i++){
//
//		if(i > 0 && i%2 != 0)
//		cout << names.at(i) << " & " << xsects.at(i)-xsects.at(0) << " (" << 100*(xsects.at(i)-xsects.at(0))/xsects.at(0) << "\\%) ";
//		else if(i > 1 && i%2 == 0)
//		cout << " & " << xsects.at(i)-xsects.at(0) << " (" << 100*(xsects.at(i)-xsects.at(0))/xsects.at(0) << "\\%) \\\\" << endl;
//
//		if(i > 1 && xsects.at(i)-xsects.at(0) > 0.){
//			error_up += pow(xsects.at(i)-xsects.at(0),2);
//		}else{
//			error_down += pow(xsects.at(i)-xsects.at(0),2);
//		}
//
//	}
//	cout << "xsect = " << xsects.at(0) << " + " << sqrt(error_up) << " - " << sqrt(error_down) << endl;
	cout << "xsect = " << xsects[0] << endl;
}

double Fit::readAndFit(AllSamples samples, Variable variable, TString syst_folder){

	//Put various samples here
	readHistos(samples, variable);

	double xsect = doFit(samples, variable, syst_folder);

	if(syst_folder == "central"){
	TH1D* data = samples.emu_data->histo;
	THStack *hs = buildStack(samples, variable);

	standardPlot(data, hs, samples, variable);

	if(Globals::addRatioPlot){
		ratioPlot(data, hs, samples, variable);
	}

	delete data;
	delete hs;
	}

	return xsect;
}

double Fit::doFit(AllSamples samples, Variable variable, TString syst_folder){

	//readHistos(samples, variable);
	//draw the templates used in the fit
	drawTemplates(samples, variable, syst_folder);

	TH1D* data = samples.emu_data->histo;

//	if(syst_folder == "Scale_up" || syst_folder == "Scale_down" || syst_folder == "Match_up" || syst_folder == "Match_down"){
//		vjets = (TH1D*)samples.vjets->histo_ge4j->Clone("vjets");
//	}else{
	TH1D* vjets = samples.vjets->histo;
//	}
	TH1D* signal = samples.signal->histo;
	TH1D* wjets = samples.wjets->histo;
	TH1D* dyjets = samples.dyjets->histo;
	TH1D* qcd =   samples.qcd->histo;
	TH1D* diboson = samples.diboson->histo;
	TH1D* ttgamma = samples.ttgamma->histo;
	TH1D* ttbar = samples.ttbar->histo;
	TH1D* single_t = samples.single_t->histo;

//	Muon QCDmuon;
//	QCDmuon.setSelection("TTbar_plus_X_analysis/MuPlusJets/QCD non iso mu+jets ge3j");
//	TH1D* qcd_data = QCDmuon.qcdHisto(samples, variable);
//	qcd_data->SetFillColor(samples.qcd->fillColor);
//	qcd_data->Scale(qcd->Integral()/qcd_data->Integral());

	//set the parameters
	double Nttgamma_err, Nttbar_err, Ntop_err, Nsingle_t_err, Nbg_err, Nqcd_err, Nwjets_err, Ndyjets_err, Ndiboson_err;

	double Nttgamma = signal->IntegralAndError(0, ttgamma->GetNbinsX()+1, Nttgamma_err);
	double Ntop = signal->IntegralAndError(0, signal->GetNbinsX()+1, Ntop_err);
	double Nttbar = ttbar->IntegralAndError(0, ttbar->GetNbinsX()+1, Nttbar_err);
	double Nsingle_t = single_t->IntegralAndError(0, single_t->GetNbinsX()+1, Nsingle_t_err);
	double Nwjets  = wjets->IntegralAndError(0, wjets->GetNbinsX()+1, Nwjets_err);
	double Ndyjets  = dyjets->IntegralAndError(0, dyjets->GetNbinsX()+1, Ndyjets_err);
	double Ndiboson  = diboson->IntegralAndError(0, diboson->GetNbinsX()+1, Ndiboson_err);	
	double Nbg  = vjets->IntegralAndError(0, signal->GetNbinsX()+1, Nbg_err);
	double Nqcd = qcd->IntegralAndError(0, signal->GetNbinsX()+1, Nqcd_err);
	double Ntotal = data->Integral();

	TVirtualFitter* fitter = TVirtualFitter::Fitter(0,3);
	fitter->SetFCN(fcn);

	Double_t arg(1); // disable printout
	fitter->ExecuteCommand("SET PRINT",&arg,1);

	fitter->SetParameter(0,"Ntop", Ntop, Ntop_err,0,Ntotal);
	fitter->SetParameter(1,"Nbg" , Nbg,  Nbg_err,0,Ntotal);
	fitter->SetParameter(2,"Nqcd", Nqcd, Nqcd_err,0,Ntotal);

	TH1D* fit_histos[4] = {data, signal, vjets, qcd};
	TObjArray fithists(0);
	for(int i =0; i<4; i++){
		fithists.Add(fit_histos[i]);
	}

	//so that can use stuff in fcn
	fitter->SetObjectFit(&fithists);

	Double_t arglist[10];
	arglist[0] = 2;

//	fitter->FixParameter(2);
//	fitter->ExecuteCommand("CALL FCN", arglist, 1);
	fitter->ExecuteCommand("MIGRAD", arglist,0);
//	fitter->ExecuteCommand("MINOS", arglist, 0);

	 double results[] = { fitter->GetParameter(0), fitter->GetParameter(1),  fitter->GetParameter(2)};
	 double errors[] = { fitter->GetParError(0), fitter->GetParError(1), fitter->GetParError(2)};

	  double amin, edm, errdef;
	  int nvpar, nparx;

	  double Nwjets_ferr = ((fitter->GetParameter(1)/Nbg)*Nwjets)*sqrt(pow(fitter->GetParError(1)/fitter->GetParameter(1) ,2) + pow(Nbg_err/Nbg ,2) + pow(Nwjets_err/Nwjets ,2));
	  double Ndyjets_ferr = ((fitter->GetParameter(1)/Nbg)*Ndyjets)*sqrt(pow(fitter->GetParError(1)/fitter->GetParameter(1) ,2) + pow(Nbg_err/Nbg ,2) + pow(Ndyjets_err/Ndyjets ,2));

	  std::cout.setf(std::ios::fixed);
	  std::cout.precision(1);

	  cout << "N_vjets: " << Nbg << endl;
	  double totMC = Ntop + Nwjets + Ndyjets + Nqcd;
	  double totMC_err = sqrt(Ntop_err*Ntop_err+Nwjets_err*Nwjets_err+Ndyjets_err*Ndyjets_err+Nqcd_err*Nqcd_err);
	  double totFit = fitter->GetParameter(0) + fitter->GetParameter(1) + fitter->GetParameter(2);
	  double totFit_err = sqrt(fitter->GetParError(0)*fitter->GetParError(0) + fitter->GetParError(1)*fitter->GetParError(1) + fitter->GetParError(2)*fitter->GetParError(2));

	  cout << "MC estimation & " <<  Ntop << " $\\pm$ " << Ntop_err << " & " << Nwjets << " $\\pm$ " << Nwjets_err << " & " << Ndyjets << " $\\pm$ " << Ndyjets_err << " & " << Nqcd << " $\\pm$ " << Nqcd_err << " & " << totMC << " $\\pm$ " << totMC_err << endl;
	  cout << "Fit results & " << fitter->GetParameter(0)  << " $\\pm$ " << fitter->GetParError(0) << " & " << (fitter->GetParameter(1)/Nbg)*Nwjets << " $\\pm$ " << Nwjets_ferr << " & " << (fitter->GetParameter(1)/Nbg)*Ndyjets << " $\\pm$ " << Ndyjets_ferr << " & " << fitter->GetParameter(2) << " $\\pm$ " << fitter->GetParError(2) <<" & " << totFit << " $\\pm$ " << totFit_err << endl;

	  fitter->GetStats(amin, edm, errdef, nvpar, nparx);

	  //do the plotting bit
	  	signal->Scale(results[0]/Ntop);
		vjets->Scale(results[1]/Nbg);
		qcd->Scale(results[2]/Nqcd);

		TCanvas *c3 = new TCanvas("Plot","Plot",900, 600);

		  THStack* sum_fit = new THStack("sum fit","stacked histograms"); //used for stack plot
		  //sum_fit->Add(qcd);
		  sum_fit->Add(vjets);sum_fit->Add(signal);

		  sum_fit->Draw("hist");
		  data->Draw("E same");

		  sum_fit->GetXaxis()->SetLimits(variable.minX, variable.maxX);
		  sum_fit->GetXaxis()->SetTitle(variable.xTitle); sum_fit->GetXaxis()->SetTitleSize(0.05);
		  sum_fit->GetYaxis()->SetTitle("Number of Events");sum_fit->GetYaxis()->SetTitleSize(0.05);

			TLegend* leg = legend(samples);
			leg->Draw();

		 	TText* textChan = doChan(0.12,0.96);
			textChan->Draw();
			TText* textPrelim = doPrelim(0.58,0.96);
			textPrelim->Draw();

		 	c3->SaveAs("Plots/"+folder+"/TTbarPhotonAnalysis/"+channel+"/"+syst_folder+"/"+variable.name+"_fit.pdf");
		    c3->SaveAs("Plots/"+folder+"/TTbarPhotonAnalysis/"+channel+"/"+syst_folder+"/"+variable.name+"_fit.png");
		    delete c3;

//		TH1D* Nemu_presel;
//		double xsect;
//		double eff = Nemu_sig/Nemu_presel;
//		double xsect = ((Nemu_sig - Nemu_bkgd)/eff)/19700;
		    double xsect = (results[0]-Nsingle_t)*245.8/Nttbar;
// 		    double xsect_up =(results[0]+errors[0]-Nsingle_t)*245.8/Nttbar;
// 		    double xsect_down =(results[0]-errors[0]-Nsingle_t)*245.8/Nttbar;
// 
// 		    double xsect_up_singt =(results[0]-(Nsingle_t*0.7))*245.8/Nttbar;
// 		    double xsect_down_singt =(results[0]-Nsingle_t*1.3)*245.8/Nttbar;
// 
// 		    double xsect_up_qcd =(results[0]-Nsingle_t+results[2])*245.8/Nttbar;
// 		    double xsect_down_qcd =(results[0]-Nsingle_t-results[2])*245.8/Nttbar;

//		    cout << "cov: " << fitter->GetCovarianceMatrixElement(0, 1) << endl;
//		    cout << " check: " << results[0] << " pm " << errors[0] << endl;

// 		    //stat errors
// 		    cout << "xsect is: " << xsect << "+-" << xsect_up-xsect << " (" << 100*(xsect_up-xsect)/xsect << ")" << endl;
// 		    //single top
// 		    cout << "xsect is: " << xsect << "+-" << xsect_up_singt-xsect << " (" << 100*(xsect_up_singt-xsect)/xsect << ")" << endl;
// 		    //QCD
// 		    cout << "xsect is: " << xsect << "+-" << xsect_up_qcd+-xsect << " (" << 100*(xsect_up_qcd-xsect)/xsect << ")" << endl;


		    return xsect;
}


void Fit::drawTemplates(AllSamples samples, Variable variable, TString syst_folder){
	TH1D* signal = (TH1D*)samples.signal->histo->Clone("signal");
	TH1D* vjets;
// 	if(syst_folder == "Scale_up" || syst_folder == "Scale_down" || syst_folder == "Match_up" || syst_folder == "Match_down"){
// 		vjets = (TH1D*)samples.vjets->histo_ge4j->Clone("vjets");
// 	}else{
		vjets = (TH1D*)samples.vjets->histo->Clone("vjets");
		vjets->Rebin(6);
// 	}
	TH1D* qcd = (TH1D*)samples.qcd->histo->Clone("qcd");

// 	Muon QCDmuon;
// 	QCDmuon.setSelection("TTbar_plus_X_analysis/MuPlusJets/QCD non iso mu+jets ge3j");
// 	TH1D* qcd_data = QCDmuon.qcdHisto(samples, variable);

	normAndColor(signal, *samples.ttbar);
	normAndColor(vjets, *samples.vjets);
	normAndColor(qcd, *samples.qcd);
//	normAndColor(qcd_data, *samples.qcd);

	TCanvas *c1 = new TCanvas("Plot","Plot",900, 600);

	  signal->Draw("histo");
	  vjets->Draw("histo same");

// 	  if(Globals::qcdFromData)
// 		  qcd_data->Draw("same");
// 	  else
//		  qcd->Draw("same");

	  signal->SetAxisRange(variable.minX, variable.maxX);
	  signal->GetXaxis()->SetTitle(variable.xTitle); signal->GetXaxis()->SetTitleSize(0.05);
	  signal->GetYaxis()->SetTitle("Normalised Events");signal->GetYaxis()->SetTitleSize(0.05);

	  	TLegend *tleg;
		tleg = new TLegend(0.65,0.7,0.8,0.9);
		tleg->SetTextSize(0.04);
		tleg->SetBorderSize(0);
		tleg->SetFillColor(10);

		tleg->AddEntry(signal , "signal", "l");
		tleg->AddEntry(vjets , "v+jets", "l");
		tleg->AddEntry(qcd , "QCD", "l");
	 	tleg->Draw("same");

	 	TText* textChan = doChan(0.12,0.96);
		textChan->Draw();
		TText* textPrelim = doPrelim(0.58,0.96);
		textPrelim->Draw();

	  c1->SaveAs("Plots/"+folder+"/TTbarPhotonAnalysis/"+channel+"/"+syst_folder+"/"+variable.name+"_templates.pdf");
	  c1->SaveAs("Plots/"+folder+"/TTbarPhotonAnalysis/"+channel+"/"+syst_folder+"/"+variable.name+"_templates.png");

	  delete c1;
	  delete signal;
	  delete vjets;
	  delete qcd;

}

void Fit::normAndColor(TH1D* hist, Sample sample){

	hist->Scale(1./hist->Integral());
	hist->SetMarkerStyle(0);
	hist->SetLineWidth(2);
	hist->SetLineColor(sample.fillColor);
	hist->SetFillColor(kWhite);
}

TH1D* Fit::readHistogram(Sample sample, Variable variable, bool btag) {

	cout << "plot: " << selection+variable.name << endl;

	TH1D* plot = (TH1D*) sample.file->Get(selection+variable.name+"_1btag");
	TH1D* plot2 = (TH1D*) sample.file->Get(selection+variable.name+"_2btags");
	TH1D* plot3 = (TH1D*) sample.file->Get(selection+variable.name+"_3btags");
	TH1D* plot4 = (TH1D*) sample.file->Get(selection+variable.name+"_4orMoreBtags");

	plot->Add(plot2);
	plot->Add(plot3);
	plot->Add(plot4);

// 	if(btag == false){
// 		plot->Add(plot4);
// 		plot->Add(plot5);
// 	}

	plot->SetFillColor(sample.fillColor);
	plot->SetLineColor(sample.lineColor);

	if(Globals::addOverFlow)
		addOverFlow(plot, variable);

	plot->Rebin(variable.rebinFact);

//	cout << "bins X: " << sample.name << " - " << plot->GetNbinsX() << endl;


	return plot;
}

void Fit::addOverFlow(TH1D* overflow, Variable variable){

	if(variable.minX > -0.1){
		int bin = variable.maxX/overflow->GetBinWidth(1);
		double error;

		double overflow_val = overflow->IntegralAndError(bin, overflow->GetNbinsX()+1, error);

		overflow->SetBinContent(bin, overflow_val);
		overflow->SetBinError(bin, error);
	}
}


void Fit::readHistos(AllSamples samples, Variable variable){

	setSelection("TTbarPhotonAnalysis/"+channel+"/Ref selection/Photons/SignalPhotons/");
	TH1D* data = readHistogram(*samples.emu_data, variable, true);
	TH1D* vjets = readHistogram(*samples.vjets, variable, true);
	TH1D* wjets = readHistogram(*samples.wjets, variable, true);
	TH1D* diboson = readHistogram(*samples.diboson, variable, true);
	TH1D* dyjets = readHistogram(*samples.dyjets, variable, true);
	TH1D* qcd = readHistogram(*samples.qcd, variable, true);
	TH1D* ttgamma = readHistogram(*samples.ttgamma, variable, true);
	TH1D* ttbar = readHistogram(*samples.ttbar, variable, true);
	TH1D* single_t = readHistogram(*samples.single_t, variable, true);
	TH1D* signal = (TH1D*) ttgamma->Clone("signal"); //was ttbar
//	signal->Add(ttbar);
//	signal->Add(single_t);

	samples.emu_data->SetHisto(data);
	samples.ttbar->SetHisto(ttbar);
	samples.single_t->SetHisto(single_t);
	samples.signal->SetHisto(signal);
	samples.vjets->SetHisto(vjets);
	samples.wjets->SetHisto(wjets);
	samples.dyjets->SetHisto(dyjets);
	samples.diboson->SetHisto(diboson);
	samples.qcd->SetHisto(qcd);

// 	setSelection("TTbar_plus_X_analysis/MuPlusJets/QCD non iso mu+jets ge3j/");
// 	TH1D* data_ge4j = readHistogram(*samples.single_mu_data, variable, false);
// 	TH1D* ttbar_ge4j = readHistogram(*samples.ttbar, variable, false);
// 	TH1D* single_t_ge4j = readHistogram(*samples.single_t, variable, false);
// 	TH1D* signal_ge4j = (TH1D*) ttbar_ge4j->Clone("signal");
// 	signal_ge4j->Add(single_t_ge4j);
// 	TH1D* vjets_ge4j = readHistogram(*samples.vjets, variable, false);
// 	TH1D* qcd_ge4j = readHistogram(*samples.qcd, variable, false);
// 
// 	samples.single_mu_data->SetHistoGe4j(data_ge4j);
// 	samples.ttbar->SetHistoGe4j(ttbar_ge4j);
// 	samples.single_t->SetHistoGe4j(single_t_ge4j);
// 	samples.signal->SetHistoGe4j(signal_ge4j);
// 	samples.vjets->SetHistoGe4j(vjets_ge4j);
// 	samples.qcd->SetHistoGe4j(qcd_ge4j);

}

THStack* Fit::buildStack(AllSamples samples, Variable variable){

	THStack *hs = new THStack("hs","test");

	hs->Add(samples.qcd->histo);
	hs->Add(samples.vjets->histo);
	hs->Add(samples.single_t->histo);
	hs->Add(samples.ttbar->histo);
	hs->Add(samples.ttgamma->histo);

	return hs;
}

TH1D* Fit::allMChisto(AllSamples samples, Variable variable){

	TH1D *allMC = (TH1D*)samples.signal->histo->Clone("ratio plot");

	allMC->Add(samples.ttbar->histo);
	allMC->Add(samples.qcd->histo);
	allMC->Add(samples.vjets->histo);
	allMC->Add(samples.single_t->histo);

	return allMC;
}

void Fit::standardPlot(TH1D* data, THStack *hs, AllSamples samples, Variable variable){
	//Style
	TdrStyle style;
	style.setTDRStyle();

	//draw histos to files
	TCanvas *c1 = new TCanvas("Plot","Plot",900, 600);

	data->Draw();
	hs->Draw("hist");

	if(Globals::addHashErrors){
		TH1D* hashErrs = hashErrors(samples, variable);
		hashErrs->Draw("same e2");
	}

	data->Draw("E same");
	data->SetMarkerStyle(20);
	data->SetMarkerSize(0.5);

	hs->SetMaximum(data->GetBinContent(data->GetMaximumBin())*1.3);
	hs->GetXaxis()->SetLimits(variable.minX, variable.maxX);
	hs->GetXaxis()->SetTitle(variable.xTitle); hs->GetXaxis()->SetTitleSize(0.05);
	hs->GetYaxis()->SetTitle("Number of Events");hs->GetYaxis()->SetTitleSize(0.05);

	TLegend* leg = legend(samples);
	leg->Draw();

	TText* textChan = doChan(0.12,0.96);
	textChan->Draw();
	TText* textPrelim = doPrelim(0.58,0.96);
	textPrelim->Draw();

	if(Globals::doLogPlot){
		c1->SetLogy();
		c1->SaveAs("Plots/"+folder+"/TTbarPhotonAnalysis/"+channel+"/Log/"+variable.name+".png");
		c1->SaveAs("Plots/"+folder+"/TTbarPhotonAnalysis/"+channel+"/Log/"+variable.name+".pdf");
	}else{
		c1->SaveAs("Plots/"+folder+"/TTbarPhotonAnalysis/"+channel+"/"+variable.name+".png");
		c1->SaveAs("Plots/"+folder+"/TTbarPhotonAnalysis/"+channel+"/"+variable.name+".pdf");
	}

	delete c1;
	delete leg;
	delete textChan;
	delete textPrelim;
}

void Fit::ratioPlot(TH1D* data, THStack *hs, AllSamples samples, Variable variable){
	//draw histos with ratio plot
	float r = 0.3;
	float epsilon = 0.02;
	TCanvas *c2 = new TCanvas("Plot","Plot",635, 600);
	c2->SetFillColor(0);
	c2->SetFrameFillStyle(0);
	TPad *pad1 = new TPad("pad1","pad1",0,r-epsilon,1,1);
	pad1->SetBottomMargin(epsilon);
	c2->cd();
	pad1->Draw();
	pad1->cd();

	hs->Draw("hist");

	hs->SetMaximum(data->GetBinContent(data->GetMaximumBin())*1.3);
	hs->GetXaxis()->SetLimits(variable.minX, variable.maxX);
	hs->GetXaxis()->SetTitle(variable.xTitle); hs->GetXaxis()->SetTitleSize(0.05);
	hs->GetYaxis()->SetTitle("Number of Events");hs->GetYaxis()->SetTitleSize(0.05);

	if(Globals::addHashErrors){
		TH1D* hashErrs = hashErrors(samples, variable);
		hashErrs->Draw("same e2");
	}

	data->Draw("E same");
	//data->SetMarkerStyle(20);
	data->SetMarkerSize(0.5);

	TLegend* leg = legend(samples);
	leg->Draw();

	TText* textChan = doChan(0.12,0.96);
	textChan->Draw();
	TText* textPrelim = doPrelim(0.58,0.96);
	textPrelim->Draw();

	TPad *pad2 = new TPad("pad2","pad2",0,0,1,r*(1-epsilon));
	pad2->SetTopMargin(0);
	pad2->SetFrameFillStyle(4000);
	pad2->SetBottomMargin(0.4);
	c2->cd();
	pad2->Draw();
	pad2->cd();

	TH1D * allMC = allMChisto(samples, variable);
	TH1D * ratio = (TH1D*)data->Clone("ratio plot");
	ratio->Sumw2();
	ratio->SetStats(0);
	ratio->Divide(allMC);

	ratio->SetMaximum(2);
	ratio->SetMinimum(0.);

//	Will need to see if this works in other situations
	if(variable.minX < 0. && ratio->GetBinWidth(1)){
		ratio->SetAxisRange(variable.minX+ratio->GetBinWidth(1)/2, fabs(variable.minX+ratio->GetBinWidth(1)/2));
	}else{
		ratio->SetAxisRange(0, variable.maxX-ratio->GetBinWidth(1)/2);
	}

	ratio->SetLabelSize(0.1, "X");
	ratio->SetTitleOffset(0.5, "Y");
	ratio->SetTitleOffset(0.8, "X");
	ratio->GetYaxis()->SetTitle("data/MC");ratio->GetYaxis()->SetTitleSize(0.1);
	ratio->GetXaxis()->SetTitle(variable.xTitle);ratio->GetXaxis()->SetTitleSize(0.15);

	ratio->Draw("ep");

	TLine *line = new TLine(variable.minX,1,variable.maxX,1);
	line->Draw();

	pad1->cd();

	if(Globals::doLogPlot){
		pad1->SetLogy();
		c2->SaveAs("Plots/"+folder+"/"+channel+"/Log/"+variable.name+"_ratio.png");
		c2->SaveAs("Plots/"+folder+"/"+channel+"/Log/"+variable.name+"_ratio.pdf");
	}else{
		c2->SaveAs("Plots/"+folder+"/"+channel+"/"+variable.name+"_ratio.png");
		c2->SaveAs("Plots/"+folder+"/"+channel+"/"+variable.name+"_ratio.pdf");
	}

	delete c2;
	delete leg;
	delete textChan;
	delete textPrelim;
}

TH1D* Fit::hashErrors(AllSamples samples, Variable variable){
	TH1D * hashErrors = allMChisto(samples, variable);

	hashErrors->SetFillColor(kBlack);
	hashErrors->SetFillStyle(3354);
	hashErrors->SetMarkerSize(0.);
	hashErrors->SetStats(0);

	return hashErrors;
}

TLegend* Fit::legend(AllSamples samples){

		TLegend *tleg;
		tleg = new TLegend(0.75,0.75,0.85,0.9);
		tleg->SetTextSize(0.04);
		tleg->SetBorderSize(0);
		tleg->SetFillColor(10);
		tleg->AddEntry(samples.mumu_data->histo , "2012 data", "lpe");
		tleg->AddEntry(samples.ttgamma->histo, "t#bar{t}#gamma", "f"); 
		tleg->AddEntry(samples.ttbar->histo , "t#bar{t}", "f");
		tleg->AddEntry(samples.single_t->histo, "single top"      , "f");
//		tleg->AddEntry(samples.dyjets->histo, "Z+jets"      , "f");
//		tleg->AddEntry(samples.wjets->histo, "W+jets"      , "f");
//		tleg->AddEntry(samples.diboson->histo, "Diboson"      , "f");		
		tleg->AddEntry(samples.vjets->histo , "v+jets", "f");
		tleg->AddEntry(samples.qcd->histo, "QCD"      , "f");

		return tleg;
}

TText* Fit::doChan(double x_pos,double y_pos){

	  ostringstream stream;
	  stream  << "#mu, #geq 4 jets, #geq 2 btags";

	  TLatex* text = new TLatex(x_pos, y_pos, stream.str().c_str());
	  text->SetNDC(true);
	  text->SetTextFont(62);
	  text->SetTextSize(0.045);  // for thesis

	  return text;
}

TText* Fit::doPrelim(double x_pos,double y_pos){

	  ostringstream stream;
	  stream  << "CMS Preliminary, L = "+Globals::lumi;

	  TLatex* text = new TLatex(x_pos, y_pos, stream.str().c_str());
	  text->SetNDC(true);
	  text->SetTextFont(62);
	  text->SetTextSize(0.045);  // for thesis

	  return text;
}

void Fit::setSelection(TString sel_name){
	selection = sel_name;
}

} /* namespace std */
