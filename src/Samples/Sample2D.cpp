/*                                                                                                                                                                                                                                                              
 * Sample2D.cpp
 *
 *  Created on: Jan, 2014
 *      Author: Nik 
 */

#include "../../interface/Samples/Sample2D.h"


namespace std {

Sample2D::Sample2D() {

        file = new TFile;
        histo = new TH2D;
        fillColor = kRed;
        lineColor = kBlack;
}

Sample2D::Sample2D(TString sample, Color_t fColor, Color_t lColor, TString systematic, TString eSystematic) {
        cout << "Getting file: " << systematic +"/"+ sample + "_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root" << endl;
        file = new TFile ("/data1/TTGammaAnalysis/HistogramFiles/Version14/"+ systematic +"/" + sample + "_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root");
        histo = new TH2D;
        fillColor = fColor;
        lineColor = lColor;
}

void Sample2D::SetHisto(TH2D* plot){
        histo = plot;
}

void Sample2D::SetFillColor(Color_t fColor){
        fillColor = fColor;
}

Color_t Sample2D::GetFillColor(){
        return fillColor;
}

void Sample2D::SetLineColor(Color_t lColor){
        lineColor = lColor;
}

Color_t Sample2D::GetLineColor(){
        return lineColor;
}

Sample2D::~Sample2D() {

}


} /* namespace std */
