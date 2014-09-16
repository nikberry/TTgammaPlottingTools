#include "TFile.h"
#include "TH1.h"
#include "TH1D.h"
#include "TObject.h"
#include "TString.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLegend.h"
#include "THStack.h"
#include <string.h>
#include <iostream>
#include <sstream>
#include <iomanip>

void SignalComparison(){

gStyle->SetOptStat(0);
//TFile* ttgamma = TFile::Open("");

TFile* dataMuMu = new TFile("/data1/TTGammaAnalysis/HistogramFiles/Version14/central/DoubleMu_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root");
TFile* dataEE = new TFile("/data1/TTGammaAnalysis/HistogramFiles/Version14/central/DoubleElectron_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root");
TFile* dataEMu = new TFile("/data1/TTGammaAnalysis/HistogramFiles/Version14/central/MuEG_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root");
TFile* ttgamma = new TFile("/data1/TTGammaAnalysis/HistogramFiles/Version14/central/TTGamma_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root");


TH1D* dataRandConeIsoMuMu0 = (TH1D*)dataMuMu->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_0btag");
TH1D* dataRandConeIsoMuMu1 = (TH1D*)dataMuMu->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_1btag");
TH1D* dataRandConeIsoMuMu2 = (TH1D*)dataMuMu->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_2btags");
TH1D* dataRandConeIsoMuMu3 = (TH1D*)dataMuMu->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_3btags");
TH1D* dataRandConeIsoMuMu4 = (TH1D*)dataMuMu->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_4orMoreBtags");

TH1D* dataRandConeIsoEE0 = (TH1D*)dataEE->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_0btag");
TH1D* dataRandConeIsoEE1 = (TH1D*)dataEE->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_1btag");
TH1D* dataRandConeIsoEE2 = (TH1D*)dataEE->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_2btags");
TH1D* dataRandConeIsoEE3 = (TH1D*)dataEE->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_3btags");
TH1D* dataRandConeIsoEE4 = (TH1D*)dataEE->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_4orMoreBtags");

TH1D* dataRandConeIsoEMu0 = (TH1D*)dataEMu->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_0btag");
TH1D* dataRandConeIsoEMu1 = (TH1D*)dataEMu->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_1btag");
TH1D* dataRandConeIsoEMu2 = (TH1D*)dataEMu->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_2btags");
TH1D* dataRandConeIsoEMu3 = (TH1D*)dataEMu->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_3btags");
TH1D* dataRandConeIsoEMu4 = (TH1D*)dataEMu->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_4orMoreBtags");

//ttgamma
TH1D* ttgammaRandConeIsoMuMu0 = (TH1D*)ttgamma->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_0btag");
TH1D* ttgammaRandConeIsoMuMu1 = (TH1D*)ttgamma->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_1btag");
TH1D* ttgammaRandConeIsoMuMu2 = (TH1D*)ttgamma->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_2btags");
TH1D* ttgammaRandConeIsoMuMu3 = (TH1D*)ttgamma->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_3btags");
TH1D* ttgammaRandConeIsoMuMu4 = (TH1D*)ttgamma->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_4orMoreBtags");

TH1D* ttgammaRandConeIsoEE0 = (TH1D*)ttgamma->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_0btag");
TH1D* ttgammaRandConeIsoEE1 = (TH1D*)ttgamma->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_1btag");
TH1D* ttgammaRandConeIsoEE2 = (TH1D*)ttgamma->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_2btags");
TH1D* ttgammaRandConeIsoEE3 = (TH1D*)ttgamma->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_3btags");
TH1D* ttgammaRandConeIsoEE4 = (TH1D*)ttgamma->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_4orMoreBtags");

TH1D* ttgammaRandConeIsoEMu0 = (TH1D*)ttgamma->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_0btag");
TH1D* ttgammaRandConeIsoEMu1 = (TH1D*)ttgamma->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_1btag");
TH1D* ttgammaRandConeIsoEMu2 = (TH1D*)ttgamma->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_2btags");
TH1D* ttgammaRandConeIsoEMu3 = (TH1D*)ttgamma->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_3btags");
TH1D* ttgammaRandConeIsoEMu4 = (TH1D*)ttgamma->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_4orMoreBtags");

//DY
TH1D* MCRandConeIsoMuMu0 = (TH1D*)MC->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_0btag");
TH1D* MCRandConeIsoMuMu1 = (TH1D*)MC->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_1btag");
TH1D* MCRandConeIsoMuMu2 = (TH1D*)MC->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_2btags");
TH1D* MCRandConeIsoMuMu3 = (TH1D*)MC->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_3btags");
TH1D* MCRandConeIsoMuMu4 = (TH1D*)MC->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_4orMoreBtags");

TH1D* MCRandConeIsoEE0 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_0btag");
TH1D* MCRandConeIsoEE1 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_1btag");
TH1D* MCRandConeIsoEE2 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_2btags");
TH1D* MCRandConeIsoEE3 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_3btags");
TH1D* MCRandConeIsoEE4 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_4orMoreBtags");

TH1D* MCRandConeIsoEMu0 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_0btag");
TH1D* MCRandConeIsoEMu1 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_1btag");
TH1D* MCRandConeIsoEMu2 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_2btags");
TH1D* MCRandConeIsoEMu3 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_3btags");
TH1D* MCRandConeIsoEMu4 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_4orMoreBtags");

//WJets
TH1D* MCRandConeIsoMuMu0 = (TH1D*)MC->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_0btag");
TH1D* MCRandConeIsoMuMu1 = (TH1D*)MC->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_1btag");
TH1D* MCRandConeIsoMuMu2 = (TH1D*)MC->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_2btags");
TH1D* MCRandConeIsoMuMu3 = (TH1D*)MC->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_3btags");
TH1D* MCRandConeIsoMuMu4 = (TH1D*)MC->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_4orMoreBtags");

TH1D* MCRandConeIsoEE0 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_0btag");
TH1D* MCRandConeIsoEE1 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_1btag");
TH1D* MCRandConeIsoEE2 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_2btags");
TH1D* MCRandConeIsoEE3 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_3btags");
TH1D* MCRandConeIsoEE4 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_4orMoreBtags");

TH1D* MCRandConeIsoEMu0 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_0btag");
TH1D* MCRandConeIsoEMu1 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_1btag");
TH1D* MCRandConeIsoEMu2 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_2btags");
TH1D* MCRandConeIsoEMu3 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_3btags");
TH1D* MCRandConeIsoEMu4 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_4orMoreBtags");

//SingleTop
TH1D* MCRandConeIsoMuMu0 = (TH1D*)MC->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_0btag");
TH1D* MCRandConeIsoMuMu1 = (TH1D*)MC->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_1btag");
TH1D* MCRandConeIsoMuMu2 = (TH1D*)MC->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_2btags");
TH1D* MCRandConeIsoMuMu3 = (TH1D*)MC->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_3btags");
TH1D* MCRandConeIsoMuMu4 = (TH1D*)MC->Get("TTbarPhotonAnalysis/MuMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_4orMoreBtags");

TH1D* MCRandConeIsoEE0 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_0btag");
TH1D* MCRandConeIsoEE1 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_1btag");
TH1D* MCRandConeIsoEE2 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_2btags");
TH1D* MCRandConeIsoEE3 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_3btags");
TH1D* MCRandConeIsoEE4 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EE/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_4orMoreBtags");

TH1D* MCRandConeIsoEMu0 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_0btag");
TH1D* MCRandConeIsoEMu1 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_1btag");
TH1D* MCRandConeIsoEMu2 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_2btags");
TH1D* MCRandConeIsoEMu3 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_3btags");
TH1D* MCRandConeIsoEMu4 = (TH1D*)MC->Get("TTbarPhotonAnalysis/EMu/Ref selection/Photons/SignalPhotons/Photon_RandConeChIso_4orMoreBtags");





dataRandConeIsoMuMu0->Add(dataRandConeIsoMuMu1);
dataRandConeIsoMuMu0->Add(dataRandConeIsoMuMu2);
dataRandConeIsoMuMu0->Add(dataRandConeIsoMuMu3);
dataRandConeIsoMuMu0->Add(dataRandConeIsoMuMu4);
dataRandConeIsoMuMu0->SetLineColor(kBlue);
dataRandConeIsoMuMu0->GetXaxis()->SetTitle("#mu#mu");
//dataRandConeIsoMuMu0->Scale(1/dataRandConeIsoMuMu0->Integral());
cout << "data MuMu: " << dataRandConeIsoMuMu0->Integral() << endl;

dataRandConeIsoEE0->Add(dataRandConeIsoEE1);
dataRandConeIsoEE0->Add(dataRandConeIsoEE2);
dataRandConeIsoEE0->Add(dataRandConeIsoEE3);
dataRandConeIsoEE0->Add(dataRandConeIsoEE4);
dataRandConeIsoEE0->SetLineColor(kBlue);
dataRandConeIsoEE0->GetXaxis()->SetTitle("e^+e^-");
cout << "data EE: " << dataRandConeIsoEE0->Integral() << endl;

dataRandConeIsoEMu0->Add(dataRandConeIsoEMu1);
dataRandConeIsoEMu0->Add(dataRandConeIsoEMu2);
dataRandConeIsoEMu0->Add(dataRandConeIsoEMu3);
dataRandConeIsoEMu0->Add(dataRandConeIsoEMu4);
dataRandConeIsoEMu0->SetLineColor(kBlue);
dataRandConeIsoEMu0->GetXaxis()->SetTitle("e#mu");
cout << "data EMu: " << dataRandConeIsoEMu0->Integral() << endl;

MCRandConeIsoMuMu0->Add(MCRandConeIsoMuMu1);
MCRandConeIsoMuMu0->Add(MCRandConeIsoMuMu2);
MCRandConeIsoMuMu0->Add(MCRandConeIsoMuMu3);
MCRandConeIsoMuMu0->Add(MCRandConeIsoMuMu4);
MCRandConeIsoMuMu0->SetLineColor(kGreen);
MCRandConeIsoMuMu0->GetXaxis()->SetTitle("#mu#mu");
cout << "MC MuMu: " << MCRandConeIsoMuMu0->Integral() << endl;

MCRandConeIsoEE0->Add(MCRandConeIsoEE1);
MCRandConeIsoEE0->Add(MCRandConeIsoEE2);
MCRandConeIsoEE0->Add(MCRandConeIsoEE3);
MCRandConeIsoEE0->Add(MCRandConeIsoEE4);
MCRandConeIsoEE0->SetLineColor(kGreen);
MCRandConeIsoEE0->GetXaxis()->SetTitle("e^[+]e^{-}");
cout << "MC EE: " << MCRandConeIsoEE0->Integral() << endl;

MCRandConeIsoEMu0->Add(MCRandConeIsoEMu1);
MCRandConeIsoEMu0->Add(MCRandConeIsoEMu2);
MCRandConeIsoEMu0->Add(MCRandConeIsoEMu3);
MCRandConeIsoEMu0->Add(MCRandConeIsoEMu4);
MCRandConeIsoEMu0->SetLineColor(kGreen);
MCRandConeIsoEMu0->GetXaxis()->SetTitle("e#mu");
cout << "MC EMu: " << MCRandConeIsoEMu0->Integral() << endl;

TCanvas* c1 = new TCanvas("c1");

//c1->SetLogy();
dataRandConeIsoMuMu0->Draw();
MCRandConeIsoMuMu0->Draw("same");

	TLegend *tleg;
        tleg = new TLegend(0.7,0.65,0.85,0.9);
        tleg->SetTextSize(0.04);
        tleg->SetBorderSize(0);
        tleg->SetFillColor(10);
        tleg->AddEntry( dataRandConeIsoMuMu0, "Data", "lpe");
        tleg->AddEntry( MCRandConeIsoMuMu0, "MC truth", "lpe");
	
tleg->Draw("same");

c1->SaveAs("Plots/SignalComparison/MuMu_signal.pdf");
c1->SaveAs("Plots/SignalComparison/MuMu_signal.png");

TCanvas* c2 = new TCanvas("c2");

dataRandConeIsoEE0->Draw();
MCRandConeIsoEE0->Draw("same");

	TLegend *tleg;
        tleg = new TLegend(0.7,0.65,0.85,0.9);
        tleg->SetTextSize(0.04);
        tleg->SetBorderSize(0);
        tleg->SetFillColor(10);
        tleg->AddEntry( dataRandConeIsoEE0, "Data", "lpe");
        tleg->AddEntry( MCRandConeIsoEE0, "MC truth", "lpe");
	
tleg->Draw("same");

c2->SaveAs("Plots/SignalComparison/EE_signal.pdf");
c2->SaveAs("Plots/SignalComparison/EE_signal.png");

TCanvas* c3 = new TCanvas("c3");

dataRandConeIsoEMu0->Draw();
MCRandConeIsoEMu0->Draw("same");

	TLegend *tleg;
        tleg = new TLegend(0.7,0.65,0.85,0.9);
        tleg->SetTextSize(0.04);
        tleg->SetBorderSize(0);
        tleg->SetFillColor(10);
        tleg->AddEntry( dataRandConeIsoEMu0, "Data", "lpe");
        tleg->AddEntry( MCRandConeIsoEMu0, "MC truth", "lpe");
	
tleg->Draw("same");

c3->SaveAs("Plots/SignalComparison/EMu_signal.pdf");
c3->SaveAs("Plots/SignalComparison/EMu_signal.png");

TCanvas* c4 = new TCanvas("c4");

c4->SetLogy();
dataRandConeIsoMuMu0->Draw();
MCRandConeIsoMuMu0->Draw("same");

	TLegend *tleg;
        tleg = new TLegend(0.7,0.65,0.85,0.9);
        tleg->SetTextSize(0.04);
        tleg->SetBorderSize(0);
        tleg->SetFillColor(10);
        tleg->AddEntry( dataRandConeIsoMuMu0, "Data", "lpe");
        tleg->AddEntry( MCRandConeIsoMuMu0, "MC truth", "lpe");
	
tleg->Draw("same");

c4->SaveAs("Plots/SignalComparison/Log/MuMu_signal.pdf");
c4->SaveAs("Plots/SignalComparison/Log/MuMu_signal.png");

TCanvas* c5 = new TCanvas("c5");

c5->SetLogy();
dataRandConeIsoEE0->Draw();
MCRandConeIsoEE0->Draw("same");

	TLegend *tleg;
        tleg = new TLegend(0.7,0.65,0.85,0.9);
        tleg->SetTextSize(0.04);
        tleg->SetBorderSize(0);
        tleg->SetFillColor(10);
        tleg->AddEntry( dataRandConeIsoEE0, "Data", "lpe");
        tleg->AddEntry( MCRandConeIsoEE0, "MC truth", "lpe");
	
tleg->Draw("same");

c5->SaveAs("Plots/SignalComparison/Log/EE_signal.pdf");
c5->SaveAs("Plots/SignalComparison/Log/EE_signal.png");

TCanvas* c6 = new TCanvas("c6");

c6->SetLogy();
dataRandConeIsoEMu0->Draw();
MCRandConeIsoEMu0->Draw("same");

	TLegend *tleg;
        tleg = new TLegend(0.7,0.65,0.85,0.9);
        tleg->SetTextSize(0.04);
        tleg->SetBorderSize(0);
        tleg->SetFillColor(10);
        tleg->AddEntry( dataRandConeIsoEMu0, "Data", "lpe");
        tleg->AddEntry( MCRandConeIsoEMu0, "MC truth", "lpe");
	
tleg->Draw("same");

c6->SaveAs("Plots/SignalComparison/Log/EMu_signal.pdf");
c6->SaveAs("Plots/SignalComparison/Log/EMu_signal.png");

}
