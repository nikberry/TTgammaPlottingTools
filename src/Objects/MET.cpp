/*
 * MET.cpp
 *
 *  Created on: Oct 11, 2013
 *      Author: philip
 */

#include "../../interface/Objects/MET.h"
#include "TCanvas.h"

namespace std {

MET::MET() {
	objName = "MET";
}

MET::~MET() {

}

void MET::allPlots(AllSamples samples){

	setMetType("patType1CorrectedPFMet");

//  Variable::Variable(TString name_temp, TString xTitle_temp, double minX_temp, double maxX_temp, int rebinFact_temp)
	Variable met;
	Variable met_sig("METsignificance", "E_{T}^{miss} significance", 0, 150, 2);
	Variable st("ST", "ST [GeV]", 0, 1500, 2);
//	Variable wpt("WPT", "p_{T}(W) [GeV]", 0, 300, 5);
//	Variable mt("MT", "m_{T}(W) [GeV]", 0, 300, 5);
	Variable met_phi("MET_phi", "E_{T}^{miss} #phi", -3.4, 3.4, 1);

	setSelectionAndChannel("TTbarDiLeptonAnalysis", "MuMu");
	savePlot(samples, met);
	savePlot(samples, met_sig);
	savePlot(samples, st);
//	savePlot(samples, wpt);
//	savePlot(samples, mt);
	savePlot(samples, met_phi);

	setChannel("EE");
	savePlot(samples, met);
	savePlot(samples, met_sig);
	savePlot(samples, st);
//	savePlot(samples, wpt);
//	savePlot(samples, mt);
	savePlot(samples, met_phi);

	setChannel("EMu");
	savePlot(samples, met);
	savePlot(samples, met_sig);
	savePlot(samples, st);
//	savePlot(samples, wpt);
//	savePlot(samples, mt);
	savePlot(samples, met_phi);

	met.rebinFact *= 2;
	met_sig.rebinFact *= 2;
	st.rebinFact *= 2;
//	wpt.rebinFact *= 2;
//	mt.rebinFact *= 2;
	met_phi.rebinFact *= 2;

	setSelectionAndChannel("TTbarPhotonAnalysis", "MuMu");
	savePlot(samples, met);
	savePlot(samples, met_sig);
	savePlot(samples, st);
//	savePlot(samples, wpt);
//	savePlot(samples, mt);
	savePlot(samples, met_phi);

	setChannel("EE");
	savePlot(samples, met);
	savePlot(samples, met_sig);
	savePlot(samples, st);
//	savePlot(samples, wpt);
//	savePlot(samples, mt);
	savePlot(samples, met_phi);

	setChannel("EMu");
	savePlot(samples, met);
	savePlot(samples, met_sig);
	savePlot(samples, st);
//	savePlot(samples, wpt);
//	savePlot(samples, mt);
	savePlot(samples, met_phi);


}

void MET::setMetType(TString metType){
	objName += "/"+metType;
}

} /* namespace std */


