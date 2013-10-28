/*
 * Object.cpp
 *
 *  Created on: Oct 18, 2013
 *      Author: philip
 */

#include "../../interface/Objects/Object.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLatex.h"
#include "TLine.h"
#include <sstream>
#include <iomanip>
#include <math.h>

namespace std {

Object::Object() {
	objName = "";
	selection = "TTbarDiLeptonAnalysis";
	selection2 = "Ref selection";
	channel = "MuMu";
}

Object::~Object() {

}

void Object::savePlot(AllSamples samples, Variable variable){

	readHistos(samples, variable);

	TH1D* data = new TH1D;

	if(channel == "MuMu")
		data = samples.mumu_data->histo;
	else if(channel == "EE")
		data = samples.ee_data->histo;
	else if(channel == "EMu")
		data = samples.emu_data->histo;

	THStack *hs = buildStack(samples, variable);

	standardPlot(data, hs, samples, variable);

	if(Globals::addRatioPlot){
		ratioPlot(data, hs, samples, variable);
	}

	delete data;
	delete hs;
}

TH1D* Object::readHistogram(Sample sample, Variable variable) {

	cout << "plot: " << selection+"/"+channel+"/"+selection2+"/"+objName+"/"+variable.name << endl;

	TH1D* plot = (TH1D*) sample.file->Get(selection+"/"+channel+"/"+selection2+"/"+objName+"/"+variable.name+"_1btag");
	TH1D* plot1 = (TH1D*) sample.file->Get(selection+"/"+channel+"/"+selection2+"/"+objName+"/"+variable.name+"_2btags");
	TH1D* plot2 = (TH1D*) sample.file->Get(selection+"/"+channel+"/"+selection2+"/"+objName+"/"+variable.name+"_3btags");
	TH1D* plot3 = (TH1D*) sample.file->Get(selection+"/"+channel+"/"+selection2+"/"+objName+"/"+variable.name+"_4orMoreBtags");

	plot->Add(plot1);
	plot->Add(plot2);
	plot->Add(plot3);

	plot->SetFillColor(sample.fillColor);
	plot->SetLineColor(sample.lineColor);

	if(Globals::addOverFlow)
		addOverFlow(plot, variable);

	plot->Rebin(variable.rebinFact);

	return plot;
}

void Object::addOverFlow(TH1D* overflow, Variable variable){

	if(variable.minX > -0.1){
		int bin = variable.maxX/overflow->GetBinWidth(1);
		double error;

		double overflow_val = overflow->IntegralAndError(bin, overflow->GetNbinsX()+1, error);

		overflow->SetBinContent(bin, overflow_val);
		overflow->SetBinError(bin, error);
	}
}


void Object::readHistos(AllSamples samples, Variable variable){

	TH1D* mumu_data = readHistogram(*samples.mumu_data, variable);
	TH1D* ee_data = readHistogram(*samples.ee_data, variable);
	TH1D* emu_data = readHistogram(*samples.emu_data, variable);

	TH1D* ttgamma = readHistogram(*samples.ttgamma, variable);
	TH1D* ttbar = readHistogram(*samples.ttbar, variable);
	TH1D* single_t = readHistogram(*samples.single_t, variable);
	TH1D* wjets = readHistogram(*samples.wjets, variable);
	TH1D* zjets = readHistogram(*samples.zjets, variable);
	TH1D* diboson = readHistogram(*samples.diboson, variable);
	TH1D* qcd = readHistogram(*samples.qcd, variable);

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

THStack* Object::buildStack(AllSamples samples, Variable variable){

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

TH1D* Object::allMChisto(AllSamples samples, Variable variable){

	TH1D *allMC = (TH1D*)samples.ttbar->histo->Clone("ratio plot");
	allMC->Add(samples.ttgamma->histo);
	allMC->Add(samples.qcd->histo);
	allMC->Add(samples.diboson->histo);
	allMC->Add(samples.zjets->histo);
	allMC->Add(samples.wjets->histo);
	allMC->Add(samples.single_t->histo);

	return allMC;
}

void Object::standardPlot(TH1D* data, THStack *hs, AllSamples samples, Variable variable){
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

	cout << "saving plot shit" << endl;

	if(Globals::doLogPlot){
		c1->SetLogy();
		c1->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/Log/"+variable.name+".png");
		c1->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/Log/"+variable.name+".pdf");
	}else{
		c1->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/"+variable.name+".png");
		c1->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/"+variable.name+".pdf");
	}

	delete c1;
	delete leg;
	delete textChan;
	delete textPrelim;
}

void Object::ratioPlot(TH1D* data, THStack *hs, AllSamples samples, Variable variable){
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
		c2->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/Log/"+variable.name+"_ratio.png");
		c2->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/Log/"+variable.name+"_ratio.pdf");
	}else{
		c2->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/"+variable.name+"_ratio.png");
		c2->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/"+variable.name+"_ratio.pdf");
	}

	delete c2;
	delete leg;
	delete textChan;
	delete textPrelim;
}

TH1D* Object::hashErrors(AllSamples samples, Variable variable){
	TH1D * hashErrors = allMChisto(samples, variable);

	hashErrors->SetFillColor(kBlack);
	hashErrors->SetFillStyle(3354);
	hashErrors->SetMarkerSize(0.);
	hashErrors->SetStats(0);

	return hashErrors;
}

TLegend* Object::legend(AllSamples samples){

		TLegend *tleg;
		tleg = new TLegend(0.7,0.65,0.85,0.9);
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

TText* Object::doChan(double x_pos,double y_pos){

	  ostringstream stream;
	  stream  << "#mu, #geq 4 jets, #geq 2 btags";

	  TLatex* text = new TLatex(x_pos, y_pos, stream.str().c_str());
	  text->SetNDC(true);
	  text->SetTextFont(62);
	  text->SetTextSize(0.045);  // for thesis

	  return text;
}

TText* Object::doPrelim(double x_pos,double y_pos){

	  ostringstream stream;
	  stream  << "CMS Preliminary, L = "+Globals::lumi;

	  TLatex* text = new TLatex(x_pos, y_pos, stream.str().c_str());
	  text->SetNDC(true);
	  text->SetTextFont(62);
	  text->SetTextSize(0.045);  // for thesis

	  return text;
}

void Object::setSelectionAndChannel(TString sel_name, TString sel_name2, TString chan){
	selection = sel_name;
	selection2 = sel_name2;
	channel = chan;
}

void Object::setSelectionAndChannel(TString sel_name, TString chan){
	selection = sel_name;
	channel = chan;
}

void Object::setChannel(TString chan){
	channel = chan;
}

} /* namespace std */
