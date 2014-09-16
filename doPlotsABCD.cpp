#include "TFile.h"
#include "TH2.h"
#include "TObject.h"
#include "TString.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLegend.h"
#include "THStack.h"
#include "TLine.h"
#include <string.h>
#include <iostream>
#include <sstream>
#include <iomanip>
//#include "tdrstyle.C"
#include "getSamples.cpp"


void doPlotsABCD();

TString Variable = "RhoCorrectedSCFRChIso_v._Sigma_ietaieta_barrel";
TString Systematic = "central";
TString type = "SignalPhotons";
TText* doPrelim(float x, float y);

void doPlotsABCD() {

gStyle->SetOptStat(0);
gStyle->SetPalette(1);
set_plot_style();
gROOT->SetBatch();

//data
TH2D* dataMuMu = getSample("DoubleMu", 1., Variable, "MuMu", type, Systematic);
TH2D* dataEE = getSample("DoubleElectron", 1., Variable, "EE", type, Systematic);
TH2D* dataEMu = getSample("MuEG", 1., Variable, "EMu", type, Systematic);

TH2D* combined = (TH2D*)dataMuMu->Clone("combined"); 
combined->Add(dataEE);
combined->Add(dataEMu);

//mc - MuMu
TH2D* ttgammaMuMu = getSample("TTGamma", 1, Variable, "MuMu", type, Systematic);
TH2D* ttjetMuMu = getSample("TTJet", 1, Variable, "MuMu", type, Systematic);
TH2D* wjetsMuMu = getSample("WJetsToLNu", 1, Variable, "MuMu", type, Systematic);
TH2D* dyjetsMuMu = getSample("DYJetsToLL", 1, Variable, "MuMu", type, Systematic);
TH2D* singletopMuMu = getSample("SingleTop", 1, Variable, "MuMu", type, Systematic);
TH2D* dibosonMuMu = getSample("DiBoson", 1, Variable, "MuMu", type, Systematic);
TH2D* qcdMuMu = getSample("QCD_All", 1, Variable, "MuMu", type, Systematic);

TH2D* mcMuMu = (TH2D*)ttgammaMuMu->Clone("mcMuMu"); 
mcMuMu->Add(ttjetMuMu);
mcMuMu->Add(wjetsMuMu);
mcMuMu->Add(dyjetsMuMu);
mcMuMu->Add(singletopMuMu);
mcMuMu->Add(dibosonMuMu);
mcMuMu->Add(qcdMuMu);


//mc - ee
TH2D* ttgammaEE = getSample("TTGamma", 1, Variable, "EE", type, Systematic);
TH2D* ttjetEE = getSample("TTJet", 1, Variable, "EE", type, Systematic);
TH2D* wjetsEE = getSample("WJetsToLNu", 1, Variable, "EE", type, Systematic);
TH2D* dyjetsEE = getSample("DYJetsToLL", 1, Variable, "EE", type, Systematic);
TH2D* singletopEE = getSample("SingleTop", 1, Variable, "EE", type, Systematic);
TH2D* dibosonEE = getSample("DiBoson", 1, Variable, "EE", type, Systematic);
TH2D* qcdEE = getSample("QCD_All", 1, Variable, "EE", type, Systematic);

TH2D* mcEE = (TH2D*)ttgammaEE->Clone("mcEE"); 
mcEE->Add(ttjetEE);
mcEE->Add(wjetsEE);
mcEE->Add(dyjetsEE);
mcEE->Add(singletopEE);
mcEE->Add(dibosonEE);
mcEE->Add(qcdEE);

//mc - emu
TH2D* ttgammaEMu = getSample("TTGamma", 1, Variable, "EMu", type, Systematic);
TH2D* ttjetEMu = getSample("TTJet", 1, Variable, "EMu", type, Systematic);
TH2D* wjetsEMu = getSample("WJetsToLNu", 1, Variable, "EMu", type, Systematic);
TH2D* dyjetsEMu = getSample("DYJetsToLL", 1, Variable, "EMu", type, Systematic);
TH2D* singletopEMu = getSample("SingleTop", 1, Variable, "EMu", type, Systematic);
TH2D* dibosonEMu = getSample("DiBoson", 1, Variable, "EMu", type, Systematic);
TH2D* qcdEMu = getSample("QCD_All", 1, Variable, "EMu", type, Systematic);

TH2D* mcEMu = (TH2D*)ttgammaEMu->Clone("mcEMu"); 
mcEMu->Add(ttjetEMu);
mcEMu->Add(wjetsEMu);
mcEMu->Add(dyjetsEMu);
mcEMu->Add(singletopEMu);
mcEMu->Add(dibosonEMu);
mcEMu->Add(qcdEMu);

TH2D* mcALL = (TH2D*)mcMuMu->Clone("mcALL");
mcALL->Add(mcEE);
mcALL->Add(mcEMu);

TCanvas* c1 = new TCanvas("c1");

	mcMuMu->Draw("colz");
	mcMuMu->SetTitle("");
        mcMuMu->GetXaxis()->SetTitle("(#rho-corr) SCFR Charged Hadron Iso ");
        mcMuMu->GetYaxis()->SetTitle("#sigma_{i#etai#eta}");

	
	double A = mcMuMu->Integral(0, 26, 80, 150);
	double B = mcMuMu->Integral(26, 200, 80, 150);
	double C = mcMuMu->Integral(0, 26, 0, 80);
	double D = mcMuMu->Integral(26, 200, 0, 80);
	
        cout << "mcMuMu" << endl;
        cout << "Region && No. of events" << endl;
        cout << "Mixed Region (A) " << "& " << A << endl;
        cout << "Background Region (B) " << "& " << B << endl; // Integral(Int_t binx1, Int_t binx2, Int_t biny1, Int_t biny2, Option_t* option = "")
        cout << "Signal Region (C) " << "& " << C << endl;
        cout << "Mixed Region (D) " << "& " << D << endl;
	cout << "Number of events: " << mcMuMu->Integral() <<  endl;


	double errorA = sqrt(A);
	double errorB = sqrt(B);
	double errorC = sqrt(C);
	double errorD = sqrt(D);

	double background = (A*D)/C;
	double signalABCD = (A*D)/B;

	double efficiency = C/8700;

	double signal = C;
	double trueSignal = signal - signalABCD;

	double x = pow((1/A), 2) + pow((1/B), 2) + pow((1/D), 2); 
	double errquad = pow(x, 0.5)*signalABCD; 
	double error = pow(C + pow(B, 2), 0.5);


        cout << "Solved for Background: " << background << " Solved for Signal: " << signalABCD << endl;  
	
	double xsect = (trueSignal/efficiency)/19700;
	
	cout << "X-section: " << xsect << " pb^-1" << " \\pm " << error << " (stat.)" <<  endl;
	cout << "Number of signal events: " << trueSignal << " \\pm " << error << endl;

        TLine* yline = new TLine(0, 0.012, 20, 0.012);
                yline->SetLineWidth(2);
        TLine* xline = new TLine(2.6, 0, 2.6, 0.03);
                xline->SetLineWidth(2);
		
	TText* text = doPrelim(0.1,0.91);
	text->Draw("same");
	
        xline->Draw("same");
        yline->Draw("same");

c1->SaveAs("Plots/ABCD/MuMu/SignalPhotons/RhoCorrectedSCFRChIso_v._Sigma_ietaieta_mc_barrel.pdf");
c1->SaveAs("Plots/ABCD/MuMu/SignalPhotons/RhoCorrectedSCFRChIso_v._Sigma_ietaieta_mc_barrel.png");

TCanvas* c2 = new TCanvas("c2");

	mcEE->Draw("colz");
	mcEE->SetTitle("");
        mcEE->GetXaxis()->SetTitle("(#rho-corr) SCFR Charged Hadron Iso ");
        mcEE->GetYaxis()->SetTitle("#sigma_{i#etai#eta}");

	
	double A = mcEE->Integral(0, 26, 80, 150);
	double B = mcEE->Integral(26, 200, 80, 150);
	double C = mcEE->Integral(0, 26, 0, 80);
	double D = mcEE->Integral(26, 200, 0, 80);
	
        cout << "mcEE" << endl;
        cout << "Region && No. of events" << endl;
        cout << "Mixed Region (A) " << "& " << A << endl;
        cout << "Background Region (B) " << "& " << B << endl; // Integral(Int_t binx1, Int_t binx2, Int_t biny1, Int_t biny2, Option_t* option = "")
        cout << "Signal Region (C) " << "& " << C << endl;
        cout << "Mixed Region (D) " << "& " << D << endl;
	cout << "Number of events: " << mcEE->Integral() <<  endl;


	double errorA = sqrt(A);
	double errorB = sqrt(B);
	double errorC = sqrt(C);
	double errorD = sqrt(D);

	double background = (A*D)/C;
	double signalABCD = (A*D)/B;

	double efficiency = C/9587;

	double signal = C;
	double trueSignal = signal - signalABCD;

	double x = pow((1/A), 2) + pow((1/B), 2) + pow((1/D), 2); 
	double errquad = pow(x, 0.5)*signalABCD; 
	double error = pow(C + pow(B, 2), 0.5);


        cout << "Solved for Background: " << background << " Solved for Signal: " << signalABCD << endl;  
	
	double xsect = (trueSignal/efficiency)/19700;
	
	cout << "X-section: " << xsect << " pb^-1" << " \\pm " << error << " (stat.)" <<  endl;
	cout << "Number of signal events: " << trueSignal << " \\pm " << error << endl;

        TLine* yline = new TLine(0, 0.012, 20, 0.012);
                yline->SetLineWidth(2);
        TLine* xline = new TLine(2.6, 0, 2.6, 0.03);
                xline->SetLineWidth(2);
		
	TText* text = doPrelim(0.1,0.91);
	text->Draw("same");
	
        xline->Draw("same");
        yline->Draw("same");

c2->SaveAs("Plots/ABCD/EE/SignalPhotons/RhoCorrectedSCFRChIso_v._Sigma_ietaieta_mc_barrel.pdf");
c2->SaveAs("Plots/ABCD/EE/SignalPhotons/RhoCorrectedSCFRChIso_v._Sigma_ietaieta_mc_barrel.png");

TCanvas* c3 = new TCanvas("c3");

	mcEMu->Draw("colz");
	mcEMu->SetTitle("");
        mcEMu->GetXaxis()->SetTitle("(#rho-corr) SCFR Charged Hadron Iso ");
        mcEMu->GetYaxis()->SetTitle("#sigma_{i#etai#eta}");

	
	double A = mcEMu->Integral(0, 26, 80, 150);
	double B = mcEMu->Integral(26, 200, 80, 150);
	double C = mcEMu->Integral(0, 26, 0, 80);
	double D = mcEMu->Integral(26, 200, 0, 80);
	
        cout << "mcEMu" << endl;
        cout << "Region && No. of events" << endl;
        cout << "Mixed Region (A) " << "& " << A << endl;
        cout << "Background Region (B) " << "& " << B << endl; // Integral(Int_t binx1, Int_t binx2, Int_t biny1, Int_t biny2, Option_t* option = "")
        cout << "Signal Region (C) " << "& " << C << endl;
        cout << "Mixed Region (D) " << "& " << D << endl;
	cout << "Number of events: " << mcEMu->Integral() <<  endl;


	double errorA = sqrt(A);
	double errorB = sqrt(B);
	double errorC = sqrt(C);
	double errorD = sqrt(D);

	double background = (A*D)/C;
	double signalABCD = (A*D)/B;

	double efficiency = C/35164;

	double signal = C;
	double trueSignal = signal - signalABCD;

	double x = pow((1/A), 2) + pow((1/B), 2) + pow((1/D), 2); 
	double errquad = pow(x, 0.5)*signalABCD; 
	double error = pow(C + pow(B, 2), 0.5);


        cout << "Solved for Background: " << background << " Solved for Signal: " << signalABCD << endl;  
	
	double xsect = (trueSignal/efficiency)/19700;
	
	cout << "X-section: " << xsect << " pb^-1" << " \\pm " << error << " (stat.)" <<  endl;
	cout << "Number of signal events: " << trueSignal << " \\pm " << error << endl;

        TLine* yline = new TLine(0, 0.012, 20, 0.012);
                yline->SetLineWidth(2);
        TLine* xline = new TLine(2.6, 0, 2.6, 0.03);
                xline->SetLineWidth(2);
		
	TText* text = doPrelim(0.1,0.91);
	text->Draw("same");
	
        xline->Draw("same");
        yline->Draw("same");

c3->SaveAs("Plots/ABCD/EMu/SignalPhotons/RhoCorrectedSCFRChIso_v._Sigma_ietaieta_mc_barrel.pdf");
c3->SaveAs("Plots/ABCD/EMu/SignalPhotons/RhoCorrectedSCFRChIso_v._Sigma_ietaieta_mc_barrel.png");

TCanvas* c4 = new TCanvas("c4");

	mcALL->Draw("colz");
	mcALL->SetTitle("");
        mcALL->GetXaxis()->SetTitle("(#rho-corr) SCFR Charged Hadron Iso ");
        mcALL->GetYaxis()->SetTitle("#sigma_{i#etai#eta}");

	
	double A = mcALL->Integral(0, 26, 80, 150);
	double B = mcALL->Integral(26, 200, 80, 150);
	double C = mcALL->Integral(0, 26, 0, 80);
	double D = mcALL->Integral(26, 200, 0, 80);
	
        cout << "mcALL" << endl;
        cout << "Region && No. of events" << endl;
        cout << "Mixed Region (A) " << "& " << A << endl;
        cout << "Background Region (B) " << "& " << B << endl; // Integral(Int_t binx1, Int_t binx2, Int_t biny1, Int_t biny2, Option_t* option = "")
        cout << "Signal Region (C) " << "& " << C << endl;
        cout << "Mixed Region (D) " << "& " << D << endl;
	cout << "Number of events: " << mcALL->Integral() <<  endl;


	double errorA = sqrt(A);
	double errorB = sqrt(B);
	double errorC = sqrt(C);
	double errorD = sqrt(D);

	double background = (A*D)/C;
	double signalABCD = (A*D)/B;

	double efficiency = C/53451;

	double signal = C;
	double trueSignal = signal - signalABCD;

	double x = pow((1/A), 2) + pow((1/B), 2) + pow((1/D), 2); 
	double errquad = pow(x, 0.5)*signalABCD; 
	double error = pow(C + pow(B, 2), 0.5);


        cout << "Solved for Background: " << background << " Solved for Signal: " << signalABCD << endl;  
	
	double xsect = (trueSignal/efficiency)/19700;
	
	cout << "X-section: " << xsect << " pb^-1" << " \\pm " << error << " (stat.)" <<  endl;
	cout << "Number of signal events: " << trueSignal << " \\pm " << error << endl;

        TLine* yline = new TLine(0, 0.012, 20, 0.012);
                yline->SetLineWidth(2);
        TLine* xline = new TLine(2.6, 0, 2.6, 0.03);
                xline->SetLineWidth(2);
		
	TText* text = doPrelim(0.1,0.91);
	text->Draw("same");
	
        xline->Draw("same");
        yline->Draw("same");

c4->SaveAs("Plots/ABCD/Combined/SignalPhotons/RhoCorrectedSCFRChIso_v._Sigma_ietaieta_mc_barrel.pdf");
c4->SaveAs("Plots/ABCD/Combined/SignalPhotons/RhoCorrectedSCFRChIso_v._Sigma_ietaieta_mc_barrel.png");


TCanvas* c7 = new TCanvas("c7");

//c1->SetLogy();
	combined->Draw("colz");
	combined->SetTitle("");
        combined->GetXaxis()->SetTitle("(#rho-corr) SCFR Charged Hadron Iso ");
        combined->GetYaxis()->SetTitle("#sigma_{i#etai#eta}");


	double A = combined->Integral(0, 26, 80, 150);
	double B = combined->Integral(26, 200, 80, 150);
	double C = combined->Integral(0, 26, 0, 80);
	double D = combined->Integral(26, 200, 0, 80);
	
        cout << "Combined" << endl;
        cout << "Region && No. of events" << endl;
        cout << "Mixed Region (A) " << "& " << A << endl;
        cout << "Background Region (B) " << "& " << B << endl; // Integral(Int_t binx1, Int_t binx2, Int_t biny1, Int_t biny2, Option_t* option = "")
        cout << "Signal Region (C) " << "& " << C << endl;
        cout << "Mixed Region (D) " << "& " << D << endl;
	cout << "Number of events: " << combined->Integral() <<  endl;


	double errorA = sqrt(A);
	double errorB = sqrt(B);
	double errorC = sqrt(C);
	double errorD = sqrt(D);

	double background = (A*D)/C;
	double signalABCD = (A*D)/B;

	double efficiency = C/50305;
	
	double signal = C;
	double trueSignal = signal - signalABCD;

	double x = pow((1/A), 2) + pow((1/B), 2) + pow((1/D), 2); 
	double errquad = pow(x, 0.5)*signalABCD; 
	double error = pow(C + pow(B, 2), 0.5);


        cout << "Solved for Background: " << background << " Solved for Signal: " << signalABCD << endl;  
	
	double xsect = (trueSignal/efficiency)/19700;
	double ratio = xsect/245;
	
	cout << "X-section: " << xsect << " pb^-1" << " \\pm " << error << " (stat.)" <<  endl;
	cout << "Ratio = " << ratio << endl;

	cout << "Number of signal events: " << trueSignal << " \\pm " << error << endl;

        TLine* yline = new TLine(0, 0.012, 20, 0.012);
                yline->SetLineWidth(2);
        TLine* xline = new TLine(2.6, 0, 2.6, 0.03);
                xline->SetLineWidth(2);
		
	TText* text = doPrelim(0.1,0.91);
	text->Draw("same");
	
        xline->Draw("same");
        yline->Draw("same");

c7->SaveAs("Plots/ABCD/Combined/SignalPhotons/RhoCorrectedSCFRChIso_v._Sigma_ietaieta_data_barrel.pdf");
c7->SaveAs("Plots/ABCD/Combined/SignalPhotons/RhoCorrectedSCFRChIso_v._Sigma_ietaieta_data_barrel.png");

TCanvas* c8 = new TCanvas("c8");

//c1->SetLogy();
	dataMuMu->Draw("colz");
	dataMuMu->SetTitle("");
        dataMuMu->GetXaxis()->SetTitle("(#rho-corr) SCFR Charged Hadron Iso ");
        dataMuMu->GetYaxis()->SetTitle("#sigma_{i#etai#eta}");


	double A = dataMuMu->Integral(0, 26, 80, 150);
	double B = dataMuMu->Integral(26, 200, 80, 150);
	double C = dataMuMu->Integral(0, 26, 0, 80);
	double D = dataMuMu->Integral(26, 200, 0, 80);
	
        cout << "dataMuMu" << endl;
        cout << "Region && No. of events" << endl;
        cout << "Mixed Region (A) " << "& " << A << endl;
        cout << "Background Region (B) " << "& " << B << endl; // Integral(Int_t binx1, Int_t binx2, Int_t biny1, Int_t biny2, Option_t* option = "")
        cout << "Signal Region (C) " << "& " << C << endl;
        cout << "Mixed Region (D) " << "& " << D << endl;
	cout << "Number of events: " << dataMuMu->Integral() <<  endl;


	double errorA = sqrt(A);
	double errorB = sqrt(B);
	double errorC = sqrt(C);
	double errorD = sqrt(D);

	double background = (A*D)/C;
	double signalABCD = (A*D)/B;

	double efficiency = C/50305;
	
	double signal = C;
	double trueSignal = signal - signalABCD;

	double x = pow((1/A), 2) + pow((1/B), 2) + pow((1/D), 2); 
	double errquad = pow(x, 0.5)*signalABCD; 
	double error = pow(C + pow(B, 2), 0.5);


        cout << "Solved for Background: " << background << " Solved for Signal: " << signalABCD << endl;  
	
	double xsect = (trueSignal/efficiency)/19700;
	double ratio = xsect/245;
	
	cout << "X-section: " << xsect << " pb^-1" << " \\pm " << error << " (stat.)" <<  endl;
	cout << "Ratio = " << ratio << endl;

	cout << "Number of signal events: " << trueSignal << " \\pm " << error << endl;

        TLine* yline = new TLine(0, 0.012, 20, 0.012);
                yline->SetLineWidth(2);
        TLine* xline = new TLine(2.6, 0, 2.6, 0.03);
                xline->SetLineWidth(2);
		
	TText* text = doPrelim(0.1,0.91);
	text->Draw("same");
	
        xline->Draw("same");
        yline->Draw("same");

c8->SaveAs("Plots/ABCD/MuMu/SignalPhotons/RhoCorrectedSCFRChIso_v._Sigma_ietaieta_data_barrel.pdf");
c8->SaveAs("Plots/ABCD/MuMu/SignalPhotons/RhoCorrectedSCFRChIso_v._Sigma_ietaieta_data_barrel.png");

TCanvas* c9 = new TCanvas("c9");

//c1->SetLogy();
	dataEE->Draw("colz");
	dataEE->SetTitle("");
        dataEE->GetXaxis()->SetTitle("(#rho-corr) SCFR Charged Hadron Iso ");
        dataEE->GetYaxis()->SetTitle("#sigma_{i#etai#eta}");


	double A = dataEE->Integral(0, 26, 80, 150);
	double B = dataEE->Integral(26, 200, 80, 150);
	double C = dataEE->Integral(0, 26, 0, 80);
	double D = dataEE->Integral(26, 200, 0, 80);
	
        cout << "dataEE" << endl;
        cout << "Region && No. of events" << endl;
        cout << "Mixed Region (A) " << "& " << A << endl;
        cout << "Background Region (B) " << "& " << B << endl; // Integral(Int_t binx1, Int_t binx2, Int_t biny1, Int_t biny2, Option_t* option = "")
        cout << "Signal Region (C) " << "& " << C << endl;
        cout << "Mixed Region (D) " << "& " << D << endl;
	cout << "Number of events: " << dataEE->Integral() <<  endl;


	double errorA = sqrt(A);
	double errorB = sqrt(B);
	double errorC = sqrt(C);
	double errorD = sqrt(D);

	double background = (A*D)/C;
	double signalABCD = (A*D)/B;

	double efficiency = C/50305;
	
	double signal = C;
	double trueSignal = signal - signalABCD;

	double x = pow((1/A), 2) + pow((1/B), 2) + pow((1/D), 2); 
	double errquad = pow(x, 0.5)*signalABCD; 
	double error = pow(C + pow(B, 2), 0.5);


        cout << "Solved for Background: " << background << " Solved for Signal: " << signalABCD << endl;  
	
	double xsect = (trueSignal/efficiency)/19700;
	double ratio = xsect/245;
	
	cout << "X-section: " << xsect << " pb^-1" << " \\pm " << error << " (stat.)" <<  endl;
	cout << "Ratio = " << ratio << endl;

	cout << "Number of signal events: " << trueSignal << " \\pm " << error << endl;

        TLine* yline = new TLine(0, 0.012, 20, 0.012);
                yline->SetLineWidth(2);
        TLine* xline = new TLine(2.6, 0, 2.6, 0.03);
                xline->SetLineWidth(2);
		
	TText* text = doPrelim(0.1,0.91);
	text->Draw("same");
	
        xline->Draw("same");
        yline->Draw("same");

c9->SaveAs("Plots/ABCD/EE/SignalPhotons/RhoCorrectedSCFRChIso_v._Sigma_ietaieta_data_barrel.pdf");
c9->SaveAs("Plots/ABCD/EE/SignalPhotons/RhoCorrectedSCFRChIso_v._Sigma_ietaieta_data_barrel.png");

TCanvas* c8 = new TCanvas("c8");

//c1->SetLogy();
	dataEMu->Draw("colz");
	dataEMu->SetTitle("");
        dataEMu->GetXaxis()->SetTitle("(#rho-corr) SCFR Charged Hadron Iso ");
        dataEMu->GetYaxis()->SetTitle("#sigma_{i#etai#eta}");


	double A = dataEMu->Integral(0, 26, 80, 150);
	double B = dataEMu->Integral(26, 200, 80, 150);
	double C = dataEMu->Integral(0, 26, 0, 80);
	double D = dataEMu->Integral(26, 200, 0, 80);
	
        cout << "dataEMu" << endl;
        cout << "Region && No. of events" << endl;
        cout << "Mixed Region (A) " << "& " << A << endl;
        cout << "Background Region (B) " << "& " << B << endl; // Integral(Int_t binx1, Int_t binx2, Int_t biny1, Int_t biny2, Option_t* option = "")
        cout << "Signal Region (C) " << "& " << C << endl;
        cout << "Mixed Region (D) " << "& " << D << endl;
	cout << "Number of events: " << dataEMu->Integral() <<  endl;


	double errorA = sqrt(A);
	double errorB = sqrt(B);
	double errorC = sqrt(C);
	double errorD = sqrt(D);

	double background = (A*D)/C;
	double signalABCD = (A*D)/B;

	double efficiency = C/50305;
	
	double signal = C;
	double trueSignal = signal - signalABCD;

	double x = pow((1/A), 2) + pow((1/B), 2) + pow((1/D), 2); 
	double errquad = pow(x, 0.5)*signalABCD; 
	double error = pow(C + pow(B, 2), 0.5);


        cout << "Solved for Background: " << background << " Solved for Signal: " << signalABCD << endl;  
	
	double xsect = (trueSignal/efficiency)/19700;
	double ratio = xsect/245;
	
	cout << "X-section: " << xsect << " pb^-1" << " \\pm " << error << " (stat.)" <<  endl;
	cout << "Ratio = " << ratio << endl;

	cout << "Number of signal events: " << trueSignal << " \\pm " << error << endl;

        TLine* yline = new TLine(0, 0.012, 20, 0.012);
                yline->SetLineWidth(2);
        TLine* xline = new TLine(2.6, 0, 2.6, 0.03);
                xline->SetLineWidth(2);
		
	TText* text = doPrelim(0.1,0.91);
	text->Draw("same");
	
        xline->Draw("same");
        yline->Draw("same");

c7->SaveAs("Plots/ABCD/EMu/SignalPhotons/RhoCorrectedSCFRChIso_v._Sigma_ietaieta_data_barrel.pdf");
c7->SaveAs("Plots/ABCD/EMu/SignalPhotons/RhoCorrectedSCFRChIso_v._Sigma_ietaieta_data_barrel.png");
}

void set_plot_style() {
    const Int_t NRGBs = 5;
    const Int_t NCont = 255;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
}
