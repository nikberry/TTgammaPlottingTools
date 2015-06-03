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
#include "TColor.h"
namespace std {

Object::Object() {
	objName = "";
	selection = "TTbarDiLeptonAnalysis";
	selection2 = "Ref selection";
	channel = "MuMu";
}

Object::~Object() {

}

void Object::SignalComparison(AllSamples samples, Variable variable){

        readHistos(samples, variable);
                                                                                                                                                                                                                                            
        TH1D* data = new TH1D;

        if(channel == "MuMu")
                data = samples.mumu_data->histo;
        else if(channel == "EE")
                data = samples.ee_data->histo;
        else if(channel == "EMu")
                data = samples.emu_data->histo;

        standardPlotSignalComparison(data, samples, variable);

        if(Globals::addRatioPlot){
                ratioPlotSignalComparison(data, samples, variable);
        }

        delete data;
}

void Object::savePlot2D(AllSamples2D samples, Variable2D variable){

        readHistos2D(samples, variable);

        TH2D* data = new TH2D;

        if(channel == "MuMu")
                data = samples.mumu_data->histo;
        else if(channel == "EE")
                data = samples.ee_data->histo;
        else if(channel == "EMu")
                data = samples.emu_data->histo;

       standardPlot2D(data,  samples, variable);


        delete data;


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

///	cout << "plot: " << selection+"/"+channel+"/"+selection2+"/"+objName+"/"+variable.name << endl;

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


// Unfinished
// 	double rebinning;
// 	if(((int)(plot->Integral()) % 2 == 0) && (int)(plot->GetNbinsX()) % 2 == 0)
// 		rebinning = (double)(plot->Integral()) / (double)(plot->GetNbinsX());
// 	if(((int)(plot->Integral()) % 2 != 0) && (int)((plot->GetNbinsX() % 2 != 0)))
// 		rebinning = (double)(plot->Integral()) / (double)(plot->GetNbinsX());
// 	if(((int)(plot->Integral()) % 2 == 0) && (int)((plot->GetNbinsX() % 2 != 0)))	
// 		rebinning = (double)(plot->Integral()) / (double)(plot->GetNbinsX()+1);
// 	if(((int)(plot->Integral()) % 2 != 0) && (int)(plot->GetNbinsX() % 2 == 0))	
// 		rebinning = plot->Integral()+1 / plot->GetNbinsX();	
// 		
	
	plot->Rebin(variable.rebinFact);
//	plot->SetBinsLength(rebinning);

	return plot;
}

TH2D* Object::readHistogram2D(Sample2D sample, Variable2D variable) {

///     cout << "plot: " << selection+"/"+channel+"/"+selection2+"/"+objName+"/"+variable.name << endl;

        TH2D* plot = (TH2D*) sample.file->Get(selection+"/"+channel+"/"+selection2+"/"+objName+"/"+variable.name+"_1btag");
        TH2D* plot1 = (TH2D*) sample.file->Get(selection+"/"+channel+"/"+selection2+"/"+objName+"/"+variable.name+"_2btags");
        TH2D* plot2 = (TH2D*) sample.file->Get(selection+"/"+channel+"/"+selection2+"/"+objName+"/"+variable.name+"_3btags");
        TH2D* plot3 = (TH2D*) sample.file->Get(selection+"/"+channel+"/"+selection2+"/"+objName+"/"+variable.name+"_4orMoreBtags");

        plot->Add(plot1);
        plot->Add(plot2);
        plot->Add(plot3);

//        plot->SetFillColor(sample.fillColor);
//        plot->SetLineColor(sample.lineColor);

//        if(Globals::addOverFlow)
//                addOverFlow(plot, variable);


// Unfinished
//      double rebinning;
//      if(((int)(plot->Integral()) % 2 == 0) && (int)(plot->GetNbinsX()) % 2 == 0)
//              rebinning = (double)(plot->Integral()) / (double)(plot->GetNbinsX());
//      if(((int)(plot->Integral()) % 2 != 0) && (int)((plot->GetNbinsX() % 2 != 0)))
//              rebinning = (double)(plot->Integral()) / (double)(plot->GetNbinsX());
//      if(((int)(plot->Integral()) % 2 == 0) && (int)((plot->GetNbinsX() % 2 != 0)))   
//              rebinning = (double)(plot->Integral()) / (double)(plot->GetNbinsX()+1);
//      if(((int)(plot->Integral()) % 2 != 0) && (int)(plot->GetNbinsX() % 2 == 0))     
//              rebinning = plot->Integral()+1 / plot->GetNbinsX();     
//              

        plot->Rebin(variable.rebinFact);
//      plot->SetBinsLength(rebinning);

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
	TH1D* dyjets = readHistogram(*samples.dyjets, variable);
	TH1D* diboson = readHistogram(*samples.diboson, variable);
	TH1D* qcd = readHistogram(*samples.qcd, variable);

	samples.mumu_data->SetHisto(mumu_data);
	samples.ee_data->SetHisto(ee_data);
	samples.emu_data->SetHisto(emu_data);

	samples.ttgamma->SetHisto(ttgamma);
	samples.ttbar->SetHisto(ttbar);
	samples.single_t->SetHisto(single_t);
	samples.wjets->SetHisto(wjets);
	samples.dyjets->SetHisto(dyjets);
	samples.diboson->SetHisto(diboson);
	samples.qcd->SetHisto(qcd);
}

void Object::readHistos2D(AllSamples2D samples, Variable2D variable){

        TH2D* mumu_data = readHistogram2D(*samples.mumu_data, variable);
        TH2D* ee_data = readHistogram2D(*samples.ee_data, variable);
        TH2D* emu_data = readHistogram2D(*samples.emu_data, variable);

        TH2D* ttgamma = readHistogram2D(*samples.ttgamma, variable);
        TH2D* ttbar = readHistogram2D(*samples.ttbar, variable);
        TH2D* single_t = readHistogram2D(*samples.single_t, variable);
        TH2D* wjets = readHistogram2D(*samples.wjets, variable);
        TH2D* dyjets = readHistogram2D(*samples.dyjets, variable);
        TH2D* diboson = readHistogram2D(*samples.diboson, variable);
        TH2D* qcd = readHistogram2D(*samples.qcd, variable);

        samples.mumu_data->SetHisto(mumu_data);
        samples.ee_data->SetHisto(ee_data);
        samples.emu_data->SetHisto(emu_data);

        samples.ttgamma->SetHisto(ttgamma);
        samples.ttbar->SetHisto(ttbar);
        samples.single_t->SetHisto(single_t);
        samples.wjets->SetHisto(wjets);
        samples.dyjets->SetHisto(dyjets);
        samples.diboson->SetHisto(diboson);
        samples.qcd->SetHisto(qcd);
}

THStack* Object::buildStack(AllSamples samples, Variable variable){

	THStack *hs = new THStack("hs","test");

	hs->Add(samples.qcd->histo);
	hs->Add(samples.wjets->histo);
	hs->Add(samples.diboson->histo);
	hs->Add(samples.dyjets->histo);
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
	allMC->Add(samples.dyjets->histo);
	allMC->Add(samples.wjets->histo);
	allMC->Add(samples.single_t->histo);

	return allMC;
}

TH2D* Object::allMChisto2D(AllSamples2D samples, Variable2D variable){

        TH2D *allMC2D = (TH2D*)samples.ttbar->histo->Clone("ratio plot");
        allMC2D->Add(samples.ttgamma->histo);
        allMC2D->Add(samples.qcd->histo);
        allMC2D->Add(samples.diboson->histo);
        allMC2D->Add(samples.dyjets->histo);
        allMC2D->Add(samples.wjets->histo);
        allMC2D->Add(samples.single_t->histo);

        return allMC2D;
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

	hs->SetMaximum(data->GetBinContent(data->GetMaximumBin())*1.4);
	hs->GetXaxis()->SetLimits(variable.minX, variable.maxX);
	hs->GetXaxis()->SetTitle(variable.xTitle); hs->GetXaxis()->SetTitleSize(0.05);
	hs->GetYaxis()->SetTitle("Number of Events");hs->GetYaxis()->SetTitleSize(0.05);

	TLegend* leg = legend(samples);
	leg->Draw();

	TText* textChan = doChan(0.12,0.96);
	textChan->Draw();
	TText* textPrelim = doPrelim(0.58,0.96);
	textPrelim->Draw();

        if(Globals::isPreliminary){                                                                                                                     
                TText* textPreliminary = doPreliminary(0.16, 0.85);
                textPreliminary->Draw();
        }

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

void Object::standardPlotSignalComparison(TH1D* data, AllSamples samples, Variable variable){
        //Style
        TdrStyle style;
        style.setTDRStyle();
	
	TH1D * allMC = allMChisto(samples, variable);
        allMC->SetMarkerStyle(20);
	allMC->SetLineColor(kGreen); 
	allMC->SetMarkerColor(kGreen);
	//draw histos to files
        TCanvas *c1 = new TCanvas("Plot","Plot",900, 600);
        float max = allMC->GetMaximum();
        max = TMath::Max(allMC->GetMaximum(),data->GetMaximum());
        allMC->SetMaximum(max*1.3);
        data->Draw();
        allMC->Draw("same");
                                                                                                                                                                                                                                            
//        if(Globals::addHashErrors){
//                TH1D* hashErrs = hashErrors(samples, variable);
//                hashErrs->Draw("same e2");
//        }

        data->Draw("E same");
        data->SetMarkerStyle(20);
        data->SetMarkerSize(0.5);
	data->SetLineColor(kBlue);
	data->SetMarkerColor(kBlue);

        allMC->SetMaximum(data->GetBinContent(data->GetMaximumBin())*1.3);
        allMC->GetXaxis()->SetLimits(variable.minX, variable.maxX);
        allMC->GetXaxis()->SetTitle(variable.xTitle); allMC->GetXaxis()->SetTitleSize(0.05);
        allMC->GetYaxis()->SetTitle("Number of Events");allMC->GetYaxis()->SetTitleSize(0.05);

	TLegend *tleg;
        tleg = new TLegend(0.7,0.65,0.85,0.9);
        tleg->SetTextSize(0.04);
        tleg->SetBorderSize(0);
        tleg->SetFillColor(10);
        tleg->AddEntry( data, "Data", "lpe");
        tleg->AddEntry( allMC, "MC truth", "lpe");

	tleg->Draw("same");

        TText* textChan = doChan(0.12,0.96);
        textChan->Draw();
        TText* textPrelim = doPrelim(0.58,0.96);
        textPrelim->Draw();

        if(Globals::doLogPlot){
                c1->SetLogy();
                c1->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/Log/"+variable.name+"_Signal.png");
                c1->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/Log/"+variable.name+"_Signal.pdf");
        }else{
                c1->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/"+variable.name+"_Signal.png");
                c1->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/"+variable.name+"_Signal.pdf");
        }

        delete c1;
        delete tleg;
        delete textChan;
        delete textPrelim;
}

void Object::standardPlot2D(TH2D* data, AllSamples2D samples, Variable2D variable){
        //Style
        TdrStyle style;
        style.setTDRStyle();

        //draw histos to files
        TCanvas *c1 = new TCanvas("Plot","Plot",900, 600);

	TH2D* allMC2D = allMChisto2D(samples, variable);
	allMC2D->Draw();
        //data->Draw();
        //data->SetMarkerStyle(20);
        //data->SetMarkerSize(0.5);

        TText* textChan = doChan(0.12,0.96);
        textChan->Draw();
        TText* textPrelim = doPrelim(0.58,0.96);
        textPrelim->Draw();

        c1->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/"+variable.name+".png");
        c1->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/"+variable.name+".pdf");

        delete c1;
        delete textChan;
        delete textPrelim;
}

void Object::set_plot_style() {
    const Int_t NRGBs = 5;
    const Int_t NCont = 255;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
}

void Object::ratioPlot(TH1D* data, THStack *hs, AllSamples samples, Variable variable){
	//draw histos with ratio plot
	float r = 0.3;
	float epsilon = 0.02;
	TCanvas *c2 = new TCanvas("Plot","Plot",635, 600);
	c2->SetFillColor(0);
	c2->SetFrameFillStyle(0);
	//TPad *pad1 = new TPad("pad1","pad1",0,r-epsilon,1,1);
	TPad *pad1 = new TPad("pad1","pad1",0,0.27,1,0.97);
	pad1->SetTopMargin(0.090);//0.062
	pad1->SetBottomMargin(0.03);//epsilon
	c2->cd();
	pad1->Draw();
	pad1->cd();

	hs->Draw("hist");

	hs->SetMaximum(data->GetBinContent(data->GetMaximumBin())*1.3);
	hs->GetXaxis()->SetLimits(variable.minX, variable.maxX);
	hs->GetXaxis()->SetTitle(variable.xTitle); hs->GetXaxis()->SetTitleSize(0.05);
	hs->GetYaxis()->SetTitle("Number of Events");hs->GetYaxis()->SetTitleSize(0.05);
	hs->GetXaxis()->SetLabelOffset(999);
	hs->GetXaxis()->SetLabelSize(0);

	if(Globals::addHashErrors){
		TH1D* hashErrs = hashErrors(samples, variable);
		hashErrs->Draw("same e2");
	}

	data->Draw("E same");
	//data->SetMarkerStyle(20);
	data->SetMarkerSize(0.5);

	TLegend* leg = legend(samples);
	leg->Draw();

/*	TText* textChan = doChan(0.12,0.94);
	textChan->Draw();
	TText* textPrelim = doPrelim(0.58,0.94);
	textPrelim->Draw();*/

	TText* textChan = doChan(0.12,0.92);
	textChan->Draw();
	TText* textPrelim = doPrelim(0.58,0.92);
	textPrelim->Draw();

	if(Globals::isPreliminary){
		TText* textPreliminary = doPreliminary(0.16, 0.82);
		textPreliminary->Draw();
	}

//	TPad *pad2 = new TPad("pad2","pad2",0,0,1,r*(1-epsilon));
        TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.26);
	pad2->SetTopMargin(0.04);
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

	ratio->SetMaximum(2.);
	ratio->SetMinimum(0.);//0.


//	Will need to see if this works in other situations - au moment il ne fonctionne pas pour des valeurs soin de zero.
	if(variable.minX < 0. && ratio->GetBinWidth(1)){
		ratio->SetAxisRange(variable.minX+ratio->GetBinWidth(1)/2, fabs(variable.maxX+ratio->GetBinWidth(1)/2));
	}else{
		ratio->SetAxisRange(0, variable.maxX-ratio->GetBinWidth(1)/2);
	}



	ratio->SetLabelSize(0.1, "X");
	ratio->SetTitleOffset(0.5, "Y");
	ratio->SetTitleOffset(0.8, "X");
	ratio->GetYaxis()->SetTitle("data/MC");ratio->GetYaxis()->SetTitleSize(0.12);
	ratio->GetXaxis()->SetTitle(variable.xTitle);ratio->GetXaxis()->SetTitleSize(0.15);
	ratio->GetYaxis()->SetNdivisions(4);
	ratio->GetYaxis()->SetLabelSize(0.08);
	ratio->SetMarkerSize(0.);
	ratio->Draw("ep");
	
	if(Globals::addHashErrors){
		TH1D* ratioHashErrs = ratioHashErrors(samples, variable);
		ratioHashErrs->Draw("same e2");
	}



	TLine *line = new TLine(variable.minX,1,variable.maxX,1); //1, 1
			line->SetLineStyle(7);
			line->SetLineColor(kCyan+3);
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

void Object::ratioPlotSignalComparison(TH1D* data,  AllSamples samples, Variable variable){
	//draw histos with ratio plot
	float r = 0.3;
	float epsilon = 0.02;
	TCanvas *c2 = new TCanvas("Plot","Plot",635, 600);
	c2->SetFillColor(0);
	c2->SetFrameFillStyle(0);
//	TPad *pad1 = new TPad("pad1","pad1",0,r-epsilon,1,1);
	TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
	pad1->SetBottomMargin(0.3); //epsilon
	c2->cd();
	pad1->Draw();
	pad1->cd();

	TH1D * allMC = allMChisto(samples, variable);
	allMC->SetLineColor(kGreen);	
	allMC->SetMarkerColor(kGreen);
	allMC->Draw();

	allMC->SetMaximum(data->GetBinContent(data->GetMaximumBin())*1.3);
	allMC->GetXaxis()->SetLimits(variable.minX, variable.maxX);
	allMC->GetXaxis()->SetTitle(variable.xTitle); allMC->GetXaxis()->SetTitleSize(0.05);
	allMC->GetYaxis()->SetTitle("Number of Events");allMC->GetYaxis()->SetTitleSize(0.05);

//	if(Globals::addHashErrors){
//		TH1D* hashErrs = hashErrors(samples, variable);
//		hashErrs->Draw("same e2");
//	}
	data->Draw("E same");
	//data->SetMarkerStyle(20);
	data->SetLineColor(kBlue);
	data->SetMarkerColor(kBlue);
	data->SetMarkerSize(0.5);

        TLegend *tleg;
        tleg = new TLegend(0.7,0.65,0.85,0.9);
        tleg->SetTextSize(0.04);
        tleg->SetBorderSize(0);
        tleg->SetFillColor(10);
        tleg->AddEntry( data, "Data", "lpe");
        tleg->AddEntry( allMC, "MC truth", "lpe");

	tleg->Draw();

	TText* textChan = doChan(0.12,0.96);
	textChan->Draw();
	TText* textPrelim = doPrelim(0.58,0.96);
	textPrelim->Draw();

//	TPad *pad2 = new TPad("pad2","pad2",0,0,1,r*(1-epsilon));
	TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.28);
	pad2->SetTopMargin(0);
	pad2->SetFrameFillStyle(4000);
	pad2->SetBottomMargin(0.6);//0.4
	c2->cd();
	pad2->Draw();
	pad2->cd();

	TH1D * ratio = (TH1D*)data->Clone("ratio plot");
	ratio->Sumw2();
	ratio->SetStats(0);
	ratio->Divide(allMC);

	ratio->SetMaximum(2);
	ratio->SetMinimum(0.);

//	Will need to see if this works in other situations - au moment il ne fonctionne pas pour des valeurs soin de zero.
	if(variable.minX < 0. && ratio->GetBinWidth(1)){
		ratio->SetAxisRange(variable.minX+ratio->GetBinWidth(1)/2, fabs(variable.maxX+ratio->GetBinWidth(1)/2));
	}else{
		ratio->SetAxisRange(0, variable.maxX-ratio->GetBinWidth(1)/2);
	}

	ratio->SetLabelSize(0.1, "X");
	ratio->SetTitleOffset(0.5, "Y");
	ratio->SetTitleOffset(0.8, "X");
	ratio->GetYaxis()->SetTitle("data/MC");ratio->GetYaxis()->SetTitleSize(0.1);
	ratio->GetXaxis()->SetTitle(variable.xTitle);ratio->GetXaxis()->SetTitleSize(0.15);
	ratio->SetMarkerSize(0.);
	ratio->Draw("ep");

	TLine *line = new TLine(variable.minX,1,variable.maxX,1);
	line->Draw();

	pad1->cd();

	if(Globals::doLogPlot){
		pad1->SetLogy();
		c2->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/Log/"+variable.name+"_Signal_ratio.png");
		c2->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/Log/"+variable.name+"_Signal_ratio.pdf");
	}else{
		c2->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/"+variable.name+"_Signal__ratio.png");
		c2->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/"+variable.name+"_Signal_ratio.pdf");
	}

	delete c2;
	delete tleg;
	delete textChan;
	delete textPrelim;
}

TH1D* Object::ratioHashErrors(AllSamples samples, Variable variable){
	TH1D * hashErrors = allMChisto(samples, variable);
	hashErrors->Divide(hashErrors);

	hashErrors->SetFillColor(kRed);
	hashErrors->SetFillStyle(3354);
	hashErrors->SetMarkerSize(0.);
	hashErrors->SetStats(0);

	return hashErrors;
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
		tleg = new TLegend(0.70,0.48,0.90,0.88);
		tleg->SetTextSize(0.04);
		tleg->SetBorderSize(0);
		tleg->SetFillColor(10);
		tleg->AddEntry(samples.mumu_data->histo , "2012 data", "lpe");
		tleg->AddEntry(samples.ttgamma->histo , "t#bar{t}+#gamma", "f");
		tleg->AddEntry(samples.ttbar->histo , "t#bar{t}", "f");
		tleg->AddEntry(samples.single_t->histo, "Single Top"      , "f");
		tleg->AddEntry(samples.dyjets->histo , "Z+Jets", "f");
		tleg->AddEntry(samples.diboson->histo , "WW/ZZ/WZ", "f");
		tleg->AddEntry(samples.wjets->histo , "W+Jets", "f");
		tleg->AddEntry(samples.qcd->histo, "QCD"      , "f");

		return tleg;
}

TText* Object::doChan(double x_pos,double y_pos){

	  ostringstream stream;
	if(channel == "MuMu")
		stream  << "#mu#mu, #geq 2 jets, #geq 1 btag, #geq 1 #gamma";
	if(channel == "EE")
		stream  << "#e^{+}#e^{-}, #geq 2 jets, #geq 1 btag #geq 1 #gamma";
	if(channel == "EMu")
		stream  << "e#mu, #geq 2 jets, #geq 1 btag, #geq 1 #gamma";				

	  TLatex* text = new TLatex(x_pos, y_pos, stream.str().c_str());
	  text->SetNDC(true);
	  text->SetTextFont(62);
	  text->SetTextSize(0.045);  // for thesis

	  return text;
}

TText* Object::doPrelim(double x_pos,double y_pos){

	  ostringstream stream;
	  stream  << "           #sqrt{s}=8 TeV,  #intLdt="+Globals::lumi;

	  TLatex* text = new TLatex(x_pos, y_pos, stream.str().c_str());
	  text->SetNDC(true);
	  text->SetTextFont(62);
	  text->SetTextSize(0.045);  // for thesis

	  return text;
}

TText* Object::doPreliminary(double x_pos,double y_pos){

          ostringstream stream;
          stream  << "CMS Preliminary";                                                                             

          TLatex* text = new TLatex(x_pos, y_pos, stream.str().c_str());
          text->SetNDC(true);
          text->SetTextFont(62);
          text->SetTextSize(0.05);  // for thesis

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

/*void Object::rebinMethod(double rebinning){

	TH1D* plot;
	double rebinning;
	rebinning = plot->Integral() / plot->GetNbinsX();
	
	cout << plot->Integral() << endl;
	
 	if(variable.minX < 0)
 		double range = -variable.minX + variable.maxX;
 	else
 		double range = variable.maxX;
}*/

} /* namespace std */
