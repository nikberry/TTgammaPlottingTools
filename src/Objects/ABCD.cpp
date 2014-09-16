/*
 * ABCD.cpp
 *
 *  Created on: May 21, 2014
 *      Author: Nik
 */

#include "../../interface/Objects/ABCD.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLatex.h"
#include "TLine.h"
#include <sstream>
#include <iomanip>
#include <math.h>
#include "TColor.h"

namespace std {

ABCD::ABCD() {
	objName = "";
	selection = "TTbarDiLeptonAnalysis";
	selection2 = "Ref selection";
	channel = "MuMu";
}

ABCD::~ABCD() {

}

void Object::ABCD(AllSamples samples, Variable variable){

        readHistos(samples, variable);
                                                                                                                                                                                                                                            
        TH2D* data = new TH2D;

        if(channel == "MuMu")
                data = samples.mumu_data->histo;
        else if(channel == "EE")
                data = samples.ee_data->histo;
        else if(channel == "EMu")
                data = samples.emu_data->histo;

        standardPlotABCD(data, samples, variable);


        delete data;
}

TH2D* ABCD::readHistogram(Sample sample, Variable variable) {

///	cout << "plot: " << selection+"/"+channel+"/"+selection2+"/"+objName+"/"+variable.name << endl;

	TH2D* plot = (TH2D*) sample.file->Get(selection+"/"+channel+"/"+selection2+"/"+objName+"/"+variable.name+"_1btag");
	TH2D* plot1 = (TH2D*) sample.file->Get(selection+"/"+channel+"/"+selection2+"/"+objName+"/"+variable.name+"_2btags");
	TH2D* plot2 = (TH2D*) sample.file->Get(selection+"/"+channel+"/"+selection2+"/"+objName+"/"+variable.name+"_3btags");
	TH2D* plot3 = (TH2D*) sample.file->Get(selection+"/"+channel+"/"+selection2+"/"+objName+"/"+variable.name+"_4orMoreBtags");

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

void ABCD::readHistos(AllSamples samples, Variable variable){

	TH2D* mumu_data = readHistogram(*samples.mumu_data, variable);
	TH2D* ee_data = readHistogram(*samples.ee_data, variable);
	TH2D* emu_data = readHistogram(*samples.emu_data, variable);

	TH2D* ttgamma = readHistogram(*samples.ttgamma, variable);
	TH2D* ttbar = readHistogram(*samples.ttbar, variable);
	TH2D* single_t = readHistogram(*samples.single_t, variable);
	TH2D* wjets = readHistogram(*samples.wjets, variable);
	TH2D* zjets = readHistogram(*samples.zjets, variable);
	TH2D* diboson = readHistogram(*samples.diboson, variable);
	TH2D* qcd = readHistogram(*samples.qcd, variable);

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

void ABCD::standardPlotABCD(TH2D* data, AllSamples samples, Variable variable){
        //Style
        TdrStyle style;
        style.setTDRStyle();

	//draw histos to files
        TCanvas *c1 = new TCanvas("Plot","Plot",900, 600);
	gStyle->SetPalette(1);
	set_plot_style();
	data->SetMarkerSize(5);
	data->Draw("colz");
	data->GetXaxis()->SetTitle("(#rho-corr) SCFR Charged Hadron Iso ");
	data->GetYaxis()->SetTitle("#sigma_{i#etai#eta}");
	
	cout << channel << endl;                                                                                                                                   
        cout << "Region && No. of events" << endl;  
	cout << "Mixed Region (A) " << "&& " << data->Integral(0, 26, 60, 150) << endl;                                                                                                                      
        cout << "Background Region (B) " << "&& " << data->Integral(26, 200, 60, 150) << endl; // Integral(Int_t binx1, Int_t binx2, Int_t biny1, Int_t biny2, Option_t* option = "")
        cout << "Signal Region (C) " << "&& " << data->Integral(0, 26, 0, 60) << endl; 
        cout << "Mixed Region (D) " << "&& " << data->Integral(26, 200, 0, 60) << endl;

	TLine* yline = new TLine(0, 0.012, 20, 0.012);
        	yline->SetLineWidth(2);
	TLine* xline = new TLine(2.6, 0, 2.6, 0.03);
                xline->SetLineWidth(2);

	xline->Draw("same");
	yline->Draw("same");

        TText* textChan = doChan(0.12,0.96);
        textChan->Draw();
        TText* textPrelim = doPrelim(0.58,0.96);
        textPrelim->Draw();

        if(Globals::doLogPlot){
                c1->SetLogy();
                c1->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/Log/"+variable.name+".png");
                c1->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/Log/"+variable.name+".pdf");
        }else{
                c1->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/"+variable.name+".png");
                c1->SaveAs("Plots/ControlPlots/"+selection+"/"+channel+"/"+objName+"/"+variable.name+".pdf");
        }

        delete c1;
        delete textChan;
        delete textPrelim;
}

void ABCD::set_plot_style() {
    const Int_t NRGBs = 5;
    const Int_t NCont = 255;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
}

TText* ABCD::doChan(double x_pos,double y_pos){

	  ostringstream stream;
	if(channel == "MuMu")
		stream  << "#mu#mu, #geq 2 jets, #geq 1 btags, #geq 1 #gamma";
	if(channel == "EE")
		stream  << "ee, #geq 2 jets, #geq 1 btagsi, #geq 1 #gamma";
	if(channel == "EMu")
		stream  << "e#mu, #geq 2 jets, #geq 1 btags, #geq 1 #gamma";				

	  TLatex* text = new TLatex(x_pos, y_pos, stream.str().c_str());
	  text->SetNDC(true);
	  text->SetTextFont(62);
	  text->SetTextSize(0.045);  // for thesis

	  return text;s
}

TText* ABCD::doPrelim(double x_pos,double y_pos){

	  ostringstream stream;
	  stream  << "CMS Preliminary \n #int #mathcal{L} #mathrm{d}t = "+Globals::lumi;

	  TLatex* text = new TLatex(x_pos, y_pos, stream.str().c_str());
	  text->SetNDC(true);
	  text->SetTextFont(62);
	  text->SetTextSize(0.045);  // for thesis

	  return text;
}

} /* namespace std */
