/*
 * getSample.cpp
 *
 *  Created on: Oct 14, 2013
 *      Author: philip
 */

#include "../../interface/Samples/Sample.h"


namespace std {

Sample::Sample() {

	file = new TFile;
	histo = new TH1D;
	fillColor = kRed;
	lineColor = kBlack;
}

Sample::Sample(TString sample, Color_t fColor, Color_t lColor, TString systematic, TString eSystematic) {
	cout << "Getting file: " << systematic +"/"+ sample + "_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root" << endl;
        file = new TFile ("/data1/TTGammaAnalysis/HistogramFiles/VersionZmasspm7LooseIso/"+ systematic +"/" + sample + "_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root");
	histo = new TH1D;
	fillColor = fColor;
	lineColor = lColor;
}

void Sample::SetHisto(TH1D* plot){
	histo = plot;
}

void Sample::SetFillColor(Color_t fColor){
	fillColor = fColor;
}

Color_t Sample::GetFillColor(){
	return fillColor;
}

void Sample::SetLineColor(Color_t lColor){
	lineColor = lColor;
}

Color_t Sample::GetLineColor(){
	return lineColor;
}

Sample::~Sample() {

}


} /* namespace std */
