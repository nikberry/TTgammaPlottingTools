/*
 * Fit.cpp
 *
 *  Created on: Dec 24, 2013
 *      Author: philip/Nik
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
#include "../../interface/Objects/Object.h"

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

	    double xi = par[0]*(top_fit->GetBinContent(i+1)/Nsignal) + par[1]*(bg_fit->GetBinContent(i+1)/Nvjets)
	    		+par[2]*(qcd_fit->GetBinContent(i+1)/Nqcd);


	    if(data_i !=0 && xi != 0){
	      lnL += log(TMath::Poisson(data_i, xi));
	    }

	  }

	  f = -2.0 * lnL;

	  //constraints
	   double nvjets_err =Nvjets*0.5;
	   double nqcd_err = Nqcd*2.;

//	cout << "nsig: " << Nsignal << " ,par0: " << par[0] << endl;
//	cout << "nvjets: " << Nvjets << " ,par1: " << par[1] << endl;
//	cout << "nqcd: " << Nqcd << " ,par2: " << par[2] << endl;

//	  f += ((par[2]-Nqcd)*(par[2]-Nqcd))/(nqcd_err*nqcd_err);
//	  f += ((par[1]-Nvjets)*(par[1]-Nvjets))/(nvjets_err*nvjets_err);

}

void fcn2(int& npar, double* deriv, double& f, double par[], int flag){

		TObjArray* fithistos =  static_cast<TObjArray*> (TVirtualFitter::GetFitter()->GetObjectFit());

		double lnL_AbsEta = 0.0;
		double lnL_M3 = 0.0;
		double lnL_Mlb = 0.0;

	    TH1D* data_AbsEta = static_cast<TH1D*>(fithistos->At(0));
	    TH1D* data_M3 = static_cast<TH1D*>(fithistos->At(01));
	    TH1D* data_Mlb = static_cast<TH1D*>(fithistos->At(2));
	    TH1D* top_fit_AbsEta = static_cast<TH1D*>(fithistos->At(3));
	    TH1D* top_fit_M3 = static_cast<TH1D*>(fithistos->At(4));
	    TH1D* top_fit_Mlb = static_cast<TH1D*>(fithistos->At(5));
	    TH1D* bg_fit_M3 = static_cast<TH1D*>(fithistos->At(6));
	    TH1D* bg_fit_AbsEta = static_cast<TH1D*>(fithistos->At(7));
	    TH1D* bg_fit_Mlb = static_cast<TH1D*>(fithistos->At(8));
	    TH1D* qcd_fit_AbsEta = static_cast<TH1D*>(fithistos->At(9));
	    TH1D* qcd_fit_M3 = static_cast<TH1D*>(fithistos->At(10));
	    TH1D* qcd_fit_Mlb = static_cast<TH1D*>(fithistos->At(11));

	    double Nsignal_M3 = top_fit_M3->Integral();
	    double Nvjets_M3 = bg_fit_M3->Integral();
	    double Nqcd_M3 = qcd_fit_M3->Integral();
	    double Nsignal_Mlb = top_fit_Mlb->Integral();
	    double Nvjets_Mlb = bg_fit_Mlb->Integral();
	    double Nqcd_Mlb = qcd_fit_Mlb->Integral();
	    double Nsignal_AbsEta = top_fit_AbsEta->Integral();
	    double Nvjets_AbsEta = bg_fit_AbsEta->Integral();
	    double Nqcd_AbsEta = qcd_fit_AbsEta->Integral();
	    

	  for (int i=0; i< data_M3->GetNbinsX(); i++){
	    //data_i is the observed number of events in each bin
	    int data_M3_i = data_M3->GetBinContent(i+1);
	    //xi is the expected number of events in each bin

	    double xi_M3 = par[0]*(top_fit_M3->GetBinContent(i+1)/Nsignal_M3) + par[1]*(bg_fit_M3->GetBinContent(i+1)/Nvjets_M3)
	    		+par[2]*(qcd_fit_M3->GetBinContent(i+1)/Nqcd_M3);


	    if(data_M3_i !=0 && xi_M3 != 0){
	      lnL_M3 += log(TMath::Poisson(data_M3_i, xi_M3));
	    }

	  }
	  
	  for (int i=0; i< data_Mlb->GetNbinsX(); i++){
	    //data_i is the observed number of events in each bin
	    int data_Mlb_i = data_Mlb->GetBinContent(i+1);
	    //xi is the expected number of events in each bin

	    double xi_Mlb = par[0]*(top_fit_Mlb->GetBinContent(i+1)/Nsignal_Mlb) + par[1]*(bg_fit_Mlb->GetBinContent(i+1)/Nvjets_Mlb)
	    		+par[2]*(qcd_fit_Mlb->GetBinContent(i+1)/Nqcd_Mlb);


	    if(data_Mlb_i !=0 && xi_Mlb != 0){
	      lnL_Mlb += log(TMath::Poisson(data_Mlb_i, xi_Mlb));
	    }

	  }
	  
	  for (int i=0; i< data_AbsEta->GetNbinsX(); i++){
	    //data_i is the observed number of events in each bin
	    int data_AbsEta_i = data_AbsEta->GetBinContent(i+1);
	    //xi is the expected number of events in each bin

	    double xi_AbsEta = par[0]*(top_fit_AbsEta->GetBinContent(i+1)/Nsignal_AbsEta) + par[1]*(bg_fit_AbsEta->GetBinContent(i+1)/Nvjets_AbsEta)
	    		+par[2]*(qcd_fit_AbsEta->GetBinContent(i+1)/Nqcd_AbsEta);


	    if(data_AbsEta_i !=0 && xi_AbsEta != 0){
	      lnL_AbsEta += log(TMath::Poisson(data_AbsEta_i, xi_AbsEta));
	    }

	  }
	  
	  
//	if(fit == "2Dfit")
//	  f = -2.0 * (lnL_M3 + lnL_Mlb);
//	if(fit == "3Dfit")  
	  f = -2.0 * (lnL_AbsEta + lnL_M3 + lnL_Mlb);
	  //constraints
//	   double nvjets_err =NvjetsMlb*0.5;
//	   double nqcd_err = NqcdMlb*2.;

//	cout << "nsig: " << Nsignal << " ,par0: " << par[0] << endl;
//	cout << "nvjets: " << Nvjets << " ,par1: " << par[1] << endl;
//	cout << "nqcd: " << Nqcd << " ,par2: " << par[2] << endl;

//	  f += ((par[2]-Nqcd)*(par[2]-Nqcd))/(nqcd_err*nqcd_err);
//	  f += ((par[1]-Nvjets)*(par[1]-Nvjets))/(nvjets_err*nvjets_err);

}

Fit::Fit(){
	
	objName = "Muon";
//        selection = "TTbar_plus_X_analysis/MuPlusJets/Ref selection/";
//      selection = "DiffVariablesAnalyser/MuPlusJets/";
        folder = "Fits";
 //       abseta = true;
//      m3 = true;
 //     mlb = true;



}

Fit::~Fit(){
}

void Fit::allFits(){


	Variable absEta("muon_AbsEta", "muon |#eta|", 0, 2.6, 10);
	Variable M3("M3", "M_{3}", 0, 1000, 5);
	Variable Mlb("invariant_mass_lepton_1bjet", "M_{lb}", 0, 400, 4);
	Variable SCCHIso("phoSCChIso", "", 0, 20, 2);	

	//fits only save standard plot if doFit 3rd arg is "central"

	vector<xSects> xSectVector;
	vector<AllSamples> sampVect;
//	vector<xSects> xSectVector3D;
	
	sampVect.push_back(AllSamples("central", ""));
	sampVect.push_back(AllSamples("JES_up", "_plusJES"));
	sampVect.push_back(AllSamples("JES_down", "_minusJES"));
	sampVect.push_back(AllSamples("JER_up", "_plusJER"));
	sampVect.push_back(AllSamples("JER_down", "_minusJER"));
	sampVect.push_back(AllSamples("PU_up", "_PU_72765mb"));
	sampVect.push_back(AllSamples("PU_down", "_PU_65835mb"));
	sampVect.push_back(AllSamples("BJet_up", "_plusBjet"));
	sampVect.push_back(AllSamples("BJet_down", "_minusBJet"));
	sampVect.push_back(AllSamples("LightJet_up", "_plusLightJet"));
	sampVect.push_back(AllSamples("LightJet_down", "_minusLightJet"));
	
	TString syst[11] = {"central", "JES_up", "JES_down", "JER_up", "JER_down", "PU_up", "PU_down", "BJet_up", "BJet_down", "LightJet_up", "LightJet_down"};
	TString syst2[11] = {"central", "JES up", "JES down", "JER up", "JER down", "PU up", "PU down", "BJet up", "BJet down", "LightJet up", "LightJet down"};
	

	for(unsigned int i = 0; i<11; i++){
		xSectVector.push_back(xSects(readAndFit(sampVect[i], absEta, syst[i]), readAndFit(sampVect[i], M3, syst[i]),
		readAndFit(sampVect[i], Mlb, syst[i])));
		cout <<  syst2[i] << ": " << xSectVector[i].getAbsEta() << "& " << xSectVector[i].getM3() << "& " << xSectVector[i].getMlb() << "\\\\" << endl;
// 		
// 		xSectVector3D.push_back(xSects(readAndFit2and3D(sampVect[i], absEta, syst[i]), readAndFit2and3D(sampVect[i], M3, syst[i]),
// 		readAndFit2and3D(sampVect[i], Mlb, syst[i])));
// 		cout <<  syst2[i] << ": " << xSectVector3D[i].getAbsEta() << "& " << xSectVector3D[i].getM3() << "& " << xSectVector3D[i].getMlb() << "\\\\" << endl;
// 		
		

	}
	
	
 			double errorUpAbsEta = pow(xSectVector[1].getAbsEta()-xSectVector[0].getAbsEta(),2) + pow(xSectVector[3].getAbsEta()-xSectVector[0].getAbsEta(),2) +
				pow(xSectVector[5].getAbsEta()-xSectVector[0].getAbsEta(),2) + pow(xSectVector[7].getAbsEta()-xSectVector[0].getAbsEta(),2) +
 				pow(xSectVector[9].getAbsEta()-xSectVector[0].getAbsEta(),2);
 			double errorDownAbsEta = pow(xSectVector[2].getAbsEta()-xSectVector[0].getAbsEta(),2) + pow(xSectVector[4].getAbsEta()-xSectVector[0].getAbsEta(),2) + 
				pow(xSectVector[6].getAbsEta()-xSectVector[0].getAbsEta(),2) + pow(xSectVector[8].getAbsEta()-xSectVector[0].getAbsEta(),2)
 				+ pow(xSectVector[10].getAbsEta()-xSectVector[0].getAbsEta(),2);
				
			 
			double errorUpM3 = pow(xSectVector[1].getM3()-xSectVector[0].getM3(),2) + pow(xSectVector[3].getM3()-xSectVector[0].getM3(),2) +
				pow(xSectVector[5].getM3()-xSectVector[0].getM3(),2) + pow(xSectVector[7].getM3()-xSectVector[0].getM3(),2) +
 				pow(xSectVector[9].getM3()-xSectVector[0].getM3(),2);
 			double errorDownM3 = pow(xSectVector[2].getM3()-xSectVector[0].getM3(),2) + pow(xSectVector[4].getM3()-xSectVector[0].getM3(),2) + 
				pow(xSectVector[6].getM3()-xSectVector[0].getM3(),2) + pow(xSectVector[8].getM3()-xSectVector[0].getM3(),2)
 				+ pow(xSectVector[10].getM3()-xSectVector[0].getM3(),2);
				
				
			double errorUpMlb = pow(xSectVector[1].getMlb()-xSectVector[0].getMlb(),2) + pow(xSectVector[3].getMlb()-xSectVector[0].getMlb(),2) +
				pow(xSectVector[5].getMlb()-xSectVector[0].getMlb(),2) + pow(xSectVector[7].getMlb()-xSectVector[0].getMlb(),2) +
 				pow(xSectVector[9].getMlb()-xSectVector[0].getMlb(),2);
 			double errorDownMlb = pow(xSectVector[2].getMlb()-xSectVector[0].getMlb(),2) + pow(xSectVector[4].getMlb()-xSectVector[0].getMlb(),2) + 
				pow(xSectVector[6].getMlb()-xSectVector[0].getMlb(),2) + pow(xSectVector[8].getMlb()-xSectVector[0].getMlb(),2)
 				+ pow(xSectVector[10].getMlb()-xSectVector[0].getMlb(),2);

	cout << "Syst. & \\sigma & syst.uncrt (\\%)  \\\\" << endl;
 	
	cout << "sigma(abseta) = " << xSectVector[0].getAbsEta() << " & \\pm" << (sqrt(errorUpAbsEta)+sqrt(errorDownAbsEta))/2 << endl;
	cout << "sigma(m3) = " << xSectVector[0].getM3() << " & \\pm" << (sqrt(errorUpM3)+sqrt(errorDownM3))/2 << endl;
	cout << "sigma(mlb) = " << xSectVector[0].getMlb() << " & \\pm" << (sqrt(errorUpMlb)+sqrt(errorDownMlb))/2 << endl;
	
	
//	double xsectoodee = readAndFit2and3D(samples, variable, syst_folder);
//	cout << "tooooooodeeeeeeeeeeeee" << xsectoodee << endl;

}

double Fit::readAndFit2and3D(AllSamples samples, Variable variable, TString syst_folder){
	
	readHistos(samples, variable);
	
	double xsect2d = do2and3DFit(samples, variable, syst_folder);
//	double xsect3d = do2and3DFit(samples, variable, syst_folder);

//	if(fit == "2Dfit")
		return xsect2d;
//	else if(fit == "3Dfit")
//		return xsect3d;
}

double Fit::readAndFit(AllSamples samples, Variable variable, TString syst_folder){

	//Put various samples here
	readHistos(samples, variable);
 
	double xsect = doFit(samples, variable, syst_folder);

	
	if(syst_folder == "central"){
	TH1D* data = samples.single_mu_data->histo;
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

double Fit::do2and3DFit(AllSamples samples, Variable variable, TString syst_folder){
	
	double Ntop_err, Nbg_err, Nqcd_err;
	double Ntop, Nttbar, Nsingle_t, Nbg, Nqcd, Ntotal;
 
	if(variable.name == "muon_AbsEta"){
	
		TH1D* dataAbsEta = samples.single_mu_data->histo;
		TH1D* vjetsAbsEta = samples.vjets->histo;
		TH1D* qcdAbsEta =  samples.qcd->histo;
		TH1D* signalAbsEta = samples.signal->histo;
		TH1D* ttbarAbsEta = samples.ttbar->histo;
		TH1D* single_tAbsEta = samples.single_t->histo;
		
		Muon QCDmuon;
		QCDmuon.setSelection("TTbar_plus_X_analysis/MuPlusJets/QCD non iso mu+jets ge3j");
		TH1D* qcd_data = QCDmuon.qcdHisto(samples, variable);
		qcd_data->SetFillColor(samples.qcd->fillColor);
		qcd_data->Scale(qcdAbsEta->Integral()/qcd_data->Integral());
	
	
		//set the parameters
		double Ntop_err, Nbg_err, Nqcd_err;

		double Ntop = signalAbsEta->IntegralAndError(0, signalAbsEta->GetNbinsX()+1, Ntop_err);
		double Nttbar = ttbarAbsEta->Integral();
		double Nsingle_t = single_tAbsEta->Integral();
		double Nbg  = vjetsAbsEta->IntegralAndError(0, signalAbsEta->GetNbinsX()+1, Nbg_err);
		double Nqcd = qcdAbsEta->IntegralAndError(0, signalAbsEta->GetNbinsX()+1, Nqcd_err);
	
		double Ntotal = dataAbsEta->Integral();

	} 
	
	if(variable.name == "M3"){
	
		TH1D* dataM3 = samples.single_mu_data->histo;
		TH1D* vjetsM3 = samples.vjets->histo;
		TH1D* qcdM3 =  samples.qcd->histo;
		TH1D* signalM3 = samples.signal->histo;
		TH1D* ttbarM3 = samples.ttbar->histo;
		TH1D* single_tM3 = samples.single_t->histo;
	
	
		//set the parameters
		double Ntop_err, Nbg_err, Nqcd_err;

		double Ntop = signalM3->IntegralAndError(0, signalM3->GetNbinsX()+1, Ntop_err);
		double Nttbar = ttbarM3->Integral();
		double Nsingle_t = single_tM3->Integral();
		double Nbg  = vjetsM3->IntegralAndError(0, signalM3->GetNbinsX()+1, Nbg_err);
		double Nqcd = qcdM3->IntegralAndError(0, signalM3->GetNbinsX()+1, Nqcd_err);
	
		double Ntotal = dataM3->Integral();

	}
	
	if(variable.name == "invariant_mass_lepton_1bjet"){
	
		TH1D* dataMlb = samples.single_mu_data->histo;
		TH1D* vjetsMlb = samples.vjets->histo;
		TH1D* qcdMlb =   samples.qcd->histo;
		TH1D* signalMlb = samples.signal->histo;
		TH1D* ttbarMlb = samples.ttbar->histo;
		TH1D* single_tMlb = samples.single_t->histo;
		
		//set the parameters
		double Ntop_err, Nbg_err, Nqcd_err;

		double Ntop = signalMlb->IntegralAndError(0, signalMlb->GetNbinsX()+1, Ntop_err);
		double Nttbar = ttbarMlb->Integral();
		double Nsingle_t = single_tMlb->Integral();
		double Nbg  = vjetsMlb->IntegralAndError(0, signalMlb->GetNbinsX()+1, Nbg_err);
		double Nqcd = qcdMlb->IntegralAndError(0, signalMlb->GetNbinsX()+1, Nqcd_err);
	
		double Ntotal = dataMlb->Integral();

	}
	
	TVirtualFitter* fitter = TVirtualFitter::Fitter(0,3);
	fitter->SetFCN(fcn2);

	Double_t arg(-1); // disable printout
	fitter->ExecuteCommand("SET PRINT",&arg,1);

	fitter->SetParameter(0,"Ntop", Ntop, Ntop_err,0,Ntotal);
	fitter->SetParameter(1,"Nbg" , Nbg,  Nbg_err,0,Ntotal);
	fitter->SetParameter(2,"Nqcd", Nqcd, Nqcd_err,0,Ntotal);
	
	TH1D* dataM3,*vjetsM3, *signalM3, *qcdM3;
	TH1D* dataMlb,*vjetsMlb, *signalMlb, *qcdMlb;
	TH1D* dataAbsEta, *vjetsAbsEta, *signalAbsEta, *qcd_data;
		
	TH1D* fit_histos[12] = {dataAbsEta, dataM3, dataMlb, signalAbsEta, signalM3, signalMlb, vjetsAbsEta, vjetsM3, vjetsMlb, qcd_data, qcdM3, qcdMlb};

	
	TObjArray fithists(0);
	for(int i =0; i<12; i++){
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

	  fitter->GetStats(amin, edm, errdef, nvpar, nparx);
	  

	  
	 // if(fit == "2Dfit")
//	  	double xsect2d = (results[0]-Nsingle_t)*245.8/Nttbar;
	//  if(fit == "3Dfit")
	  	double xsect3d = (results[0]-Nsingle_t)*245.8/Nttbar;
		cout << "dfgsdfgsdfgsfdgsdffgdsfg" << xsect3d << endl;
	   
//	  if(fit == "2Dfit") 
//	  	return xsect2d;
//	  if(fit == "3Dfit")
	  	return xsect3d;	
}


double Fit::doFit(AllSamples samples, Variable variable, TString syst_folder){
		
	
	////readHistos(samples, variable);
	////draw the templates used in the fit
	drawTemplates(samples, variable, syst_folder);
	
	TH1D* data = samples.single_mu_data->histo;
	TH1D* vjets = samples.vjets->histo;
	TH1D* qcd =   samples.qcd->histo;
	TH1D* signal = samples.signal->histo;
	TH1D* ttbar = samples.ttbar->histo;
	TH1D* single_t = samples.single_t->histo;

	Muon QCDmuon;
	QCDmuon.setSelection("TTbar_plus_X_analysis/MuPlusJets/QCD non iso mu+jets ge3j");
	TH1D* qcd_data = QCDmuon.qcdHisto(samples, variable);
	qcd_data->SetFillColor(samples.qcd->fillColor);
	qcd_data->Scale(qcd->Integral()/qcd_data->Integral());
	

	//set the parameters
	double Ntop_err, Nbg_err, Nqcd_err;

	double Ntop = signal->IntegralAndError(0, signal->GetNbinsX()+1, Ntop_err);
	double Nttbar = ttbar->Integral();
	double Nsingle_t = single_t->Integral();
	double Nbg  = vjets->IntegralAndError(0, signal->GetNbinsX()+1, Nbg_err);
	double Nqcd = qcd->IntegralAndError(0, signal->GetNbinsX()+1, Nqcd_err);
	
	double Ntotal = data->Integral();


	TVirtualFitter* fitter = TVirtualFitter::Fitter(0,3);
	fitter->SetFCN(fcn);

	Double_t arg(-1); // disable printout
	fitter->ExecuteCommand("SET PRINT",&arg,1);

	fitter->SetParameter(0,"Ntop", Ntop, Ntop_err,0,Ntotal);
	fitter->SetParameter(1,"Nbg" , Nbg,  Nbg_err,0,Ntotal);
	fitter->SetParameter(2,"Nqcd", Nqcd, Nqcd_err,0,Ntotal);

	TH1D* fit_histos[4] = {data, signal, vjets, qcd};//qcd_data

	
	
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

	  fitter->GetStats(amin, edm, errdef, nvpar, nparx);

	  //do the plotting bit
	  	signal->Scale(results[0]/Ntop);
		vjets->Scale(results[1]/Nbg);	
		
		if(variable.name == "muon_AbsEta")	
			qcd_data->Scale(results[2]/Nqcd);
		else 
			qcd->Scale(results[2]/Nqcd);
		
		TH1D* bkgd = (TH1D*) vjets->Clone("vjets");
		if(variable.name == "muon_AbsEta"){
			bkgd->Add(qcd_data);
		} else
			bkgd->Add(qcd);
		
		TCanvas *c3 = new TCanvas("Plot","Plot",900, 600);
		
		TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
			
			c3->cd();
			pad1->Draw();
			pad1->cd();
			
		  THStack* sum_fit = new THStack("sum fit","stacked histograms"); //used for stack plot
		  sum_fit->Add(bkgd); sum_fit->Add(signal);
		  sum_fit->Draw("hist");
		  data->Draw("E same");

		  sum_fit->GetXaxis()->SetLimits(variable.minX, variable.maxX);
		  sum_fit->GetXaxis()->SetTitle(variable.xTitle); sum_fit->GetXaxis()->SetTitleSize(0.05);
		  sum_fit->GetYaxis()->SetTitle("Number of Events");sum_fit->GetYaxis()->SetTitleSize(0.05);
//
//			TLegend* leg = legend(samples);
//			leg->Draw();

			TLegend *tleg;
			tleg = new TLegend(0.65,0.7,0.8,0.9);
			tleg->SetTextSize(0.04);
			tleg->SetBorderSize(0);
			tleg->SetFillColor(10);

			tleg->AddEntry(signal , "signal", "f");
			tleg->AddEntry(bkgd, "bkgd", "f");
	 		tleg->Draw("same");

		 	TText* textChan = doChan(0.12,0.96);
			textChan->Draw();
			TText* textPrelim = doPrelim(0.58,0.96);
			textPrelim->Draw();



		    c3->SaveAs("Plots/"+folder+"/"+objName+"/"+syst_folder+"/"+variable.name+"_fit.pdf");
		    c3->SaveAs("Plots/"+folder+"/"+objName+"/"+syst_folder+"/"+variable.name+"_fit.png");
		
		    delete c3;

		    double xsect = (results[0]-Nsingle_t)*245.8/Nttbar;

		    return xsect;
}

void Fit::drawTemplates(AllSamples samples, Variable variable, TString syst_folder){

	TH1D* signal = (TH1D*)samples.signal->histo->Clone("signal");
	TH1D* vjets = (TH1D*)samples.vjets->histo->Clone("vjets");
	TH1D* qcd = (TH1D*)samples.qcd->histo->Clone("qcd");

	Muon QCDmuon;
	QCDmuon.setSelection("TTbar_plus_X_analysis/MuPlusJets/QCD non iso mu+jets ge3j");
	TH1D* qcd_data = QCDmuon.qcdHisto(samples, variable);
	qcd_data->Scale(qcd->Integral()/qcd_data->Integral());

	TH1D* bkgd = (TH1D*)vjets->Clone("vjets");
	if(variable.name == "muon_AbsEta")
		bkgd->Add(qcd_data);
	else		
		bkgd->Add(qcd);

	normAndColor(signal, *samples.ttbar);
	normAndColor(vjets, *samples.vjets);
	normAndColor(qcd, *samples.qcd);
	normAndColor(qcd_data, *samples.qcd);
	normAndColor(bkgd, *samples.vjets);

	TCanvas *c1 = new TCanvas("Plot","Plot",900, 600);

	  signal->Draw();
	  bkgd->Draw("same");

	  signal->SetAxisRange(variable.minX, variable.maxX);
	  signal->GetXaxis()->SetTitle(variable.xTitle); signal->GetXaxis()->SetTitleSize(0.05);
	  signal->GetYaxis()->SetTitle("Normalised Events");signal->GetYaxis()->SetTitleSize(0.05);

	  	TLegend *tleg;
		tleg = new TLegend(0.65,0.7,0.8,0.9);
		tleg->SetTextSize(0.04);
		tleg->SetBorderSize(0);
		tleg->SetFillColor(10);

		tleg->AddEntry(signal , "signal", "l");
		tleg->AddEntry(bkgd, "bkgd", "l");
	 	tleg->Draw("same");

	 	TText* textChan = doChan(0.12,0.96);
		textChan->Draw();
		TText* textPrelim = doPrelim(0.58,0.96);
		textPrelim->Draw();

	  c1->SaveAs("Plots/"+folder+"/"+objName+"/"+syst_folder+"/"+variable.name+"_templates.pdf");
	  c1->SaveAs("Plots/"+folder+"/"+objName+"/"+syst_folder+"/"+variable.name+"_templates.png");

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

		cout << "plot: " << selection+objName+"/"+variable.name << endl;
		
		TH1D* plot = (TH1D*) sample.file->Get(selection+objName+"/"+variable.name+"_2btags");
		TH1D* plot2 = (TH1D*) sample.file->Get(selection+objName+"/"+variable.name+"_3btags");
		TH1D* plot3 = (TH1D*) sample.file->Get(selection+objName+"/"+variable.name+"_4orMoreBtags");

		TH1D* plot4 = (TH1D*) sample.file->Get(selection+objName+"/"+variable.name+"_0btag");
		TH1D* plot5 = (TH1D*) sample.file->Get(selection+objName+"/"+variable.name+"_1btag");

		plot->Add(plot2);
		plot->Add(plot3);

		if(btag == false){
			plot->Add(plot4);
			plot->Add(plot5);
		}


	plot->SetFillColor(sample.fillColor);
	plot->SetLineColor(sample.lineColor);

	if(Globals::addOverFlow)
		addOverFlow(plot, variable);

	plot->Rebin(variable.rebinFact);

	cout << "bins X: " << sample.name << " - " << plot->GetNbinsX() << endl;


	return plot;
}

TH1D* Fit::readHistogram2(Sample sample, Variable variable, bool btag) {


	cout << "plot: " << selection+variable.name << endl;

	TH1D* plot = (TH1D*) sample.file->Get(selection+variable.name);


	plot->SetFillColor(sample.fillColor);
	plot->SetLineColor(sample.lineColor);

	if(Globals::addOverFlow)
		addOverFlow(plot, variable);

	plot->Rebin(variable.rebinFact);

	cout << "bins X: " << sample.name << " - " << plot->GetNbinsX() << endl;


	return plot;
}

void Fit::readHistos(AllSamples samples, Variable variable){

 		//for abseta
 		if(variable.name == "muon_AbsEta"){
		setSelection("TTbar_plus_X_analysis/MuPlusJets/Ref selection/");

		TH1D* data = readHistogram(*samples.single_mu_data, variable, true);
		TH1D* vjets = readHistogram(*samples.vjets, variable, true);
		TH1D* qcd = readHistogram(*samples.qcd, variable, true);
		TH1D* ttbar = readHistogram(*samples.ttbar, variable, true);
		TH1D* single_t = readHistogram(*samples.single_t, variable, true);
		TH1D* signal = (TH1D*) ttbar->Clone("signal");
		signal->Add(single_t);

		samples.single_mu_data->SetHisto(data);
		samples.ttbar->SetHisto(ttbar);
		samples.single_t->SetHisto(single_t);
		samples.signal->SetHisto(signal);
		samples.vjets->SetHisto(vjets);
		samples.qcd->SetHisto(qcd);

		setSelection("TTbar_plus_X_analysis/MuPlusJets/QCD non iso mu+jets ge3j/");
		TH1D* data_ge4j = readHistogram(*samples.single_mu_data, variable, false);
		TH1D* ttbar_ge4j = readHistogram(*samples.ttbar, variable, false);
		TH1D* single_t_ge4j = readHistogram(*samples.single_t, variable, false);
		TH1D* signal_ge4j = (TH1D*) ttbar_ge4j->Clone("signal");
		signal_ge4j->Add(single_t_ge4j);
		TH1D* vjets_ge4j = readHistogram(*samples.vjets, variable, false);
		TH1D* qcd_ge4j = readHistogram(*samples.qcd, variable, false);

		samples.single_mu_data->SetHistoGe4j(data_ge4j);
		samples.ttbar->SetHistoGe4j(ttbar_ge4j);
		samples.single_t->SetHistoGe4j(single_t_ge4j);
		samples.signal->SetHistoGe4j(signal_ge4j);
		samples.vjets->SetHistoGe4j(vjets_ge4j);
		samples.qcd->SetHistoGe4j(qcd_ge4j);
		}


		if(variable.name == "M3" || variable.name == "invariant_mass_lepton_1bjet"){
		setSelection("DiffVariablesAnalyser/MuPlusJets/");

		TH1D* data = readHistogram2(*samples.single_mu_data, variable, false);
		TH1D* vjets = readHistogram2(*samples.vjets, variable, false);
		TH1D* qcd = readHistogram2(*samples.qcd, variable, false);
		TH1D* ttbar = readHistogram2(*samples.ttbar, variable, false);
		TH1D* single_t = readHistogram2(*samples.single_t, variable, false);
		TH1D* signal = (TH1D*) ttbar->Clone("signal");
		signal->Add(single_t);
		
		samples.single_mu_data->SetHisto(data);
		samples.ttbar->SetHisto(ttbar);
		samples.single_t->SetHisto(single_t);
		samples.signal->SetHisto(signal);
		samples.vjets->SetHisto(vjets);
		samples.qcd->SetHisto(qcd);
		}

	

}

THStack* Fit::buildStack(AllSamples samples, Variable variable){

	THStack *hs = new THStack("hs","test");

	hs->Add(samples.qcd->histo);
	hs->Add(samples.vjets->histo);
	hs->Add(samples.single_t->histo);
	hs->Add(samples.ttbar->histo);

	return hs;
}

TH1D* Fit::allMChisto(AllSamples samples, Variable variable){

	TH1D *allMC = (TH1D*)samples.ttbar->histo->Clone("ratio plot");

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
		c1->SaveAs("Plots/"+folder+"/"+objName+"/Log/"+variable.name+".png");
		c1->SaveAs("Plots/"+folder+"/"+objName+"/Log/"+variable.name+".pdf");
	}else{
		c1->SaveAs("Plots/"+folder+"/"+objName+"/"+variable.name+".png");
		c1->SaveAs("Plots/"+folder+"/"+objName+"/"+variable.name+".pdf");
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
		c2->SaveAs("Plots/"+folder+"/"+objName+"/Log/"+variable.name+"_ratio.png");
		c2->SaveAs("Plots/"+folder+"/"+objName+"/Log/"+variable.name+"_ratio.pdf");
	}else{
		c2->SaveAs("Plots/"+folder+"/"+objName+"/"+variable.name+"_ratio.png");
		c2->SaveAs("Plots/"+folder+"/"+objName+"/"+variable.name+"_ratio.pdf");
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
		tleg->AddEntry(samples.single_mu_data->histo , "2012 data", "lpe");
		tleg->AddEntry(samples.ttbar->histo , "t#bar{t}", "f");
//		tleg->AddEntry(samples.single_t->histo, "single top"      , "f");
		tleg->AddEntry(samples.vjets->histo , "v+jets", "f");
		tleg->AddEntry(samples.qcd->histo, "QCD"      , "f");

		return tleg;
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
