/*
 * CutFlow.cpp
 *
 *  Created on: Oct 26, 2013
 *      Author: philip
 */

#include "../../interface/Objects/CutFlow.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLatex.h"
#include "TLine.h"
#include <sstream>
#include <iomanip>
#include <math.h>

namespace std {

CutFlow::CutFlow() {
	// TODO Auto-generated constructor stub
	objName = "CutFlow";
	selection = "EventCount";
	channel = "MuMu";

}

CutFlow::~CutFlow() {
	// TODO Auto-generated destructor stub
}

void CutFlow::allPlots(AllSamples samples){

//  Variable::Variable(TString name_temp, TString xTitle_temp, double minX_temp, double maxX_temp, int rebinFact_temp)
	Variable mumu_sel("TTbarMuMuRefSelection", "selection step", -1.5, 8.5, 1);
	saveCutFlowPlot(samples, mumu_sel);

	setSelectionAndChannel("EventCount", "EE");

	Variable ee_sel("TTbarEERefSelection", "selection step", -1.5, 8.5, 1);
	saveCutFlowPlot(samples, ee_sel);

	setSelectionAndChannel("EventCount", "EMu");

	Variable emu_sel("TTbarEMuRefSelection", "selection step", -1.5, 6.5, 1);
	saveCutFlowPlot(samples, emu_sel);

}

void CutFlow::saveCutFlowPlot(AllSamples samples, Variable variable){

	readCutFlowHistos(samples, variable);

	TH1D* data = new TH1D;

	if(channel == "MuMu")
		data = samples.mumu_data->histo;
	else if(channel == "EE")
		data = samples.ee_data->histo;
	else if(channel == "EMu")
		data = samples.emu_data->histo;

	THStack *hs = buildStack(samples, variable);

	standardCutFlowPlot(data, hs, samples, variable);

	if(Globals::addRatioPlot){
		ratioCutFlowPlot(data, hs, samples, variable);
	}

	writeTable(samples, variable);

	delete data;
	delete hs;
}

TH1D* CutFlow::readCutFlowHistogram(Sample sample, Variable variable) {

	cout << "plot: " << selection+"/"+variable.name << endl;

	TH1D* plot = (TH1D*) sample.file->Get(selection+"/"+variable.name);

	plot->SetFillColor(sample.fillColor);
	plot->SetLineColor(sample.lineColor);

	return plot;
}

void CutFlow::readCutFlowHistos(AllSamples samples, Variable variable){

	TH1D* mumu_data = readCutFlowHistogram(*samples.mumu_data, variable);
	TH1D* ee_data = readCutFlowHistogram(*samples.ee_data, variable);
	TH1D* emu_data = readCutFlowHistogram(*samples.emu_data, variable);

	TH1D* ttgamma = readCutFlowHistogram(*samples.ttgamma, variable);
	TH1D* ttbar = readCutFlowHistogram(*samples.ttbar, variable);
	TH1D* single_t = readCutFlowHistogram(*samples.single_t, variable);
	TH1D* wjets = readCutFlowHistogram(*samples.wjets, variable);
	TH1D* zjets = readCutFlowHistogram(*samples.zjets, variable);
	TH1D* diboson = readCutFlowHistogram(*samples.diboson, variable);
	TH1D* qcd = readCutFlowHistogram(*samples.qcd, variable);

	samples.mumu_data->SetHisto(mumu_data);
	samples.ee_data->SetHisto(ee_data);
	samples.emu_data->SetHisto(emu_data);

	samples.ttgamma->SetHisto(ttgamma);
	samples.ttbar->SetHisto(ttbar);
	samples.single_t->SetHisto(single_t);
	samples.wjets->SetHisto(wjets);
	samples.zjets->SetHisto(zjets);
	samples.diboson->SetHisto(diboson);
	samples.qcd->SetHisto(qcd);
}

THStack* CutFlow::buildStack(AllSamples samples, Variable variable){

	THStack *hs = new THStack("hs","test");

	hs->Add(samples.qcd->histo);
	hs->Add(samples.wjets->histo);
	hs->Add(samples.diboson->histo);
	hs->Add(samples.zjets->histo);
	hs->Add(samples.single_t->histo);
	hs->Add(samples.ttbar->histo);
	hs->Add(samples.ttgamma->histo);

	return hs;
}

TH1D* CutFlow::allMChisto(AllSamples samples, Variable variable){

	TH1D *allMC = (TH1D*)samples.ttbar->histo->Clone("all mc");

	allMC->Add(samples.ttgamma->histo);
	allMC->Add(samples.qcd->histo);
	allMC->Add(samples.diboson->histo);
	allMC->Add(samples.zjets->histo);
	allMC->Add(samples.wjets->histo);
	allMC->Add(samples.single_t->histo);

	return allMC;
}

void CutFlow::standardCutFlowPlot(TH1D* data, THStack *hs, AllSamples samples, Variable variable){
	//Style
	TdrStyle style;
	style.setTDRStyle();

	//draw histos to files
	TCanvas *c1 = new TCanvas("Plot","Plot",900, 600);

	data->Draw();
	hs->Draw("hist");

	setBinLabels(hs, data);

	if(Globals::addHashErrors){
		TH1D* hashErrs = hashErrors(samples, variable);
		hashErrs->Draw("same e2");
	}

	data->Draw("E same");
	data->SetMarkerStyle(20);
	data->SetMarkerSize(0.5);

	hs->SetMaximum(data->GetBinContent(data->GetMaximumBin())*1.3);
//	hs->SetMinimum(1.);
	hs->GetXaxis()->SetLimits(variable.minX, variable.maxX);
	hs->GetXaxis()->SetTitle(variable.xTitle); hs->GetXaxis()->SetTitleSize(0.05);
	hs->GetYaxis()->SetTitle("Number of Events");hs->GetYaxis()->SetTitleSize(0.05);

	TLegend* leg = legend(samples);
	leg->Draw();

	TText* textChan = doChan(0.12,0.96);
	textChan->Draw();
	TText* textPrelim = doPrelim(0.58,0.96);
	textPrelim->Draw();

	c1->SetLogy();
	c1->SaveAs("Plots/ControlPlots/"+objName+"/Log/"+variable.name+".png");
	c1->SaveAs("Plots/ControlPlots/"+objName+"/Log/"+variable.name+".pdf");

	delete c1;
	delete leg;
	delete textChan;
	delete textPrelim;
}

void CutFlow::ratioCutFlowPlot(TH1D* data, THStack *hs, AllSamples samples, Variable variable){
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

	cout << "ratio bins: " << ratio->GetNbinsX() << endl;
	cout << "all mc bins: " << allMC->GetNbinsX() << endl;

	ratio->Divide(allMC);

	ratio->SetMaximum(2);
	ratio->SetMinimum(0.);

	setBinLabels(hs, ratio);

//	Will need to see if this works in other situations

	ratio->SetLabelSize(0.1, "X");
	ratio->SetTitleOffset(0.5, "Y");
	ratio->SetTitleOffset(0.8, "X");
	ratio->GetYaxis()->SetTitle("data/MC");ratio->GetYaxis()->SetTitleSize(0.1);
	ratio->GetXaxis()->SetTitle(variable.xTitle);ratio->GetXaxis()->SetTitleSize(0.15);

	ratio->Draw("ep");

	TLine *line = new TLine(variable.minX,1,variable.maxX,1);
	line->Draw();

	pad1->cd();

	pad1->SetLogy();
	c2->SaveAs("Plots/ControlPlots/"+objName+"/Log/"+variable.name+"_ratio.png");
	c2->SaveAs("Plots/ControlPlots/"+objName+"/Log/"+variable.name+"_ratio.pdf");

	delete c2;
	delete leg;
	delete textChan;
	delete textPrelim;
}

TH1D* CutFlow::hashErrors(AllSamples samples, Variable variable){
	TH1D * hashErrors = allMChisto(samples, variable);

	hashErrors->SetFillColor(kBlack);
	hashErrors->SetFillStyle(3354);
	hashErrors->SetMarkerSize(0.);
	hashErrors->SetStats(0);

	return hashErrors;
}

TLegend* CutFlow::legend(AllSamples samples){

		TLegend *tleg;
		tleg = new TLegend(0.65,0.60,0.85,0.9);
		tleg->SetTextSize(0.04);
		tleg->SetBorderSize(0);
		tleg->SetFillColor(10);
		tleg->AddEntry(samples.mumu_data->histo , "2012 data", "lpe");
		tleg->AddEntry(samples.ttgamma->histo , "t#bar{t}+#gamma", "f");
		tleg->AddEntry(samples.ttbar->histo , "t#bar{t}", "f");
		tleg->AddEntry(samples.single_t->histo, "Single Top"      , "f");
		tleg->AddEntry(samples.zjets->histo , "Z+Jets", "f");
		tleg->AddEntry(samples.diboson->histo , "WW/ZZ/WZ", "f");
		tleg->AddEntry(samples.wjets->histo , "W+Jets", "f");
		tleg->AddEntry(samples.qcd->histo, "QCD"      , "f");

		return tleg;
}

void CutFlow::writeTable(AllSamples samples, Variable variable){
    std::cout.setf(std::ios::fixed);
    std::cout.precision(0);

    TH1D * allMC = allMChisto(samples, variable);

	if(channel == "MuMu" || channel == "EE"){
		TString step[10] = {"Skim" ,"Cleaning and HLT","Di-lepton Sel", "m(Z) veto", "$\\geq$ 1 jet", "$\\geq$ 2 jets", "$\\slash{E_{T}}$ cut", "$\\geq$ 1 CSV b-tag", "$\\geq$ 1 Good Photon" , "1 Good Photon"};
		//TString step[11] = { "Skim" ,"Cleaning and HLT","Di-lepton Sel", "#geq 1 jets", "#geq 2 jets", "#geq1 CSV b-tag", "#geq1 Good Photon", "1 Good Photon"};
		cout << " & $t\\bar{t}+\\gamma$ & $t\\bar{t}$ & w+jets & z+jets & diboson & single-t & qcd & all MC & data" << endl;

		for(int i = 0; i < samples.ttbar->histo->GetNbinsX(); i++){
			cout << step[i] << " & " << samples.ttgamma->histo->GetBinContent(i+1) << " $\\pm$ " << samples.ttgamma->histo->GetBinError(i+1)
					<< " & " << samples.ttbar->histo->GetBinContent(i+1) << " $\\pm$ " << samples.ttbar->histo->GetBinError(i+1)
					<< " & " << samples.wjets->histo->GetBinContent(i+1) << " $\\pm$ " << samples.wjets->histo->GetBinError(i+1)
					<< " & " << samples.zjets->histo->GetBinContent(i+1) << " $\\pm$ " << samples.zjets->histo->GetBinError(i+1)
					<< " & " << samples.diboson->histo->GetBinContent(i+1) << " $\\pm$ " << samples.diboson->histo->GetBinError(i+1)
					<< " & " << samples.single_t->histo->GetBinContent(i+1) << " $\\pm$ " << samples.single_t->histo->GetBinError(i+1)
					<< " & " << samples.qcd->histo->GetBinContent(i+1) << " $\\pm$ " << samples.qcd->histo->GetBinError(i+1)
					<< " & " << allMC->GetBinContent(i+1) << " $\\pm$ " << allMC->GetBinError(i+1);
			if(channel == "MuMu")
				cout << " & " << samples.mumu_data->histo->GetBinContent(i+1) << " $\\pm$ " << samples.mumu_data->histo->GetBinError(i+1)  << endl;
			else if(channel == "EE")
				cout << " & " << samples.ee_data->histo->GetBinContent(i+1) << " $\\pm$ " << samples.ee_data->histo->GetBinError(i+1)  << endl;
			else if(channel == "EE")
				cout << " & " << samples.emu_data->histo->GetBinContent(i+1) << " $\\pm$ " << samples.emu_data->histo->GetBinError(i+1)  << endl;

		}
	}else{
		TString step[8] = {"Skim" ,"Cleaning and HLT","Di-lepton Sel", "$\\geq$ 1 jet", "$\\geq$ 2 jets", "$\\geq$ 1 CSV b-tag", "$\\geq$ 1 Good Photon" , "1 Good Photon"};
		//TString step[11] = { "Skim" ,"Cleaning and HLT","Di-lepton Sel", "#geq 1 jets", "#geq 2 jets", "#geq1 CSV b-tag", "#geq1 Good Photon", "1 Good Photon"};
		cout << " & $t\\bar{t}+\\gamma$ & $t\\bar{t}$ & w+jets & z+jets & diboson & single-t & qcd & all MC & data" << endl;

		for(int i = 0; i < samples.ttbar->histo->GetNbinsX(); i++){
			cout << step[i] << " & " << samples.ttgamma->histo->GetBinContent(i+1) << " $\\pm$ " << samples.ttgamma->histo->GetBinError(i+1)
					<< " & " << samples.ttbar->histo->GetBinContent(i+1) << " $\\pm$ " << samples.ttbar->histo->GetBinError(i+1)
					<< " & " << samples.wjets->histo->GetBinContent(i+1) << " $\\pm$ " << samples.wjets->histo->GetBinError(i+1)
					<< " & " << samples.zjets->histo->GetBinContent(i+1) << " $\\pm$ " << samples.zjets->histo->GetBinError(i+1)
					<< " & " << samples.diboson->histo->GetBinContent(i+1) << " $\\pm$ " << samples.diboson->histo->GetBinError(i+1)
					<< " & " << samples.single_t->histo->GetBinContent(i+1) << " $\\pm$ " << samples.single_t->histo->GetBinError(i+1)
					<< " & " << samples.qcd->histo->GetBinContent(i+1) << " $\\pm$ " << samples.qcd->histo->GetBinError(i+1)
					<< " & " << allMC->GetBinContent(i+1) << " $\\pm$ " << allMC->GetBinError(i+1);
			if(channel == "MuMu")
				cout << " & " << samples.mumu_data->histo->GetBinContent(i+1) << " $\\pm$ " << samples.mumu_data->histo->GetBinError(i+1)  << endl;
			else if(channel == "EE")
				cout << " & " << samples.ee_data->histo->GetBinContent(i+1) << " $\\pm$ " << samples.ee_data->histo->GetBinError(i+1)  << endl;
			else if(channel == "EMu")
				cout << " & " << samples.emu_data->histo->GetBinContent(i+1) << " $\\pm$ " << samples.emu_data->histo->GetBinError(i+1)  << endl;

		}
	}

}

TText* CutFlow::doChan(double x_pos,double y_pos){

	  ostringstream stream;
	  stream  << "#mu, #geq 4 jets, #geq 2 btags";

	  TLatex* text = new TLatex(x_pos, y_pos, stream.str().c_str());
	  text->SetNDC(true);
	  text->SetTextFont(62);
	  text->SetTextSize(0.045);  // for thesis

	  return text;
}

TText* CutFlow::doPrelim(double x_pos,double y_pos){

	  ostringstream stream;
	  stream  << "CMS Preliminary, L = "+Globals::lumi;

	  TLatex* text = new TLatex(x_pos, y_pos, stream.str().c_str());
	  text->SetNDC(true);
	  text->SetTextFont(62);
	  text->SetTextSize(0.045);  // for thesis

	  return text;
}

void CutFlow::setSelectionAndChannel(TString sel_name, TString chan){
	selection = sel_name;
	channel = chan;
}

void CutFlow::setBinLabels(THStack* hs, TH1D* data){

	if(channel == "MuMu" || channel == "EE"){
		TString step[10] = {"Skim" ,"Cleaning and HLT","Di-lepton Sel", "m(Z) veto", "#geq 1 jet", "#geq 2 jets", "#slash{E_{T}} cut", "#geq1 CSV b-tag", "#geq1 Good Photon" , "1 Good Photon"};
		for(int i =0; i<data->GetNbinsX(); i++){
			hs->GetXaxis()->SetBinLabel(i+1, step[i]);
			data->GetXaxis()->SetBinLabel(i+1, step[i]);
		}
	}else{
		TString step[8] = {"Skim" ,"Cleaning and HLT","Di-lepton Sel", "#geq 1 jet", "#geq 2 jets", "#geq1 CSV b-tag", "#geq1 Good Photon" , "1 Good Photon"};
		for(int i =0; i<data->GetNbinsX(); i++){
			hs->GetXaxis()->SetBinLabel(i+1, step[i]);
			data->GetXaxis()->SetBinLabel(i+1, step[i]);
		}
	}
}

} /* namespace std */
