/*
 * Jets.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: philip
 */

#include "../../interface/Objects/Jets.h"

namespace std {

Jets::Jets() {
	// TODO Auto-generated constructor stub
	objName = "Jets";
}

Jets::~Jets() {
	// TODO Auto-generated destructor stub
}

void Jets::allPlots(AllSamples samples){

	//  Variable::Variable(TString name_temp, TString xTitle_temp, double minX_temp, double maxX_temp, int rebinFact_temp)
	Variable pt_all("all_jet_pT", "all jet p_{T}", 0, 300, 5);
	Variable phi_all("all_jet_phi", "all jet #phi", -3.4, 3.4, 5);
	Variable eta_all("all_jet_eta", "all jet #eta", -2.6, 2.6, 5);

	setSelectionAndChannel("TTbarDiLeptonAnalysis", "MuMu");

	savePlot(samples, pt_all);
	savePlot(samples, phi_all);
	savePlot(samples, eta_all);

	setChannel("EE");

	savePlot(samples, pt_all);
	savePlot(samples, phi_all);
	savePlot(samples, eta_all);

	setChannel("EMu");

	savePlot(samples, pt_all);
	savePlot(samples, phi_all);
	savePlot(samples, eta_all);

	pt_all.rebinFact *= 2;
	phi_all.rebinFact *= 2;
	eta_all.rebinFact *= 2;

	setSelectionAndChannel("TTbarPhotonAnalysis", "MuMu");

	savePlot(samples, pt_all);
	savePlot(samples, phi_all);
	savePlot(samples, eta_all);

	setChannel("EE");

	savePlot(samples, pt_all);
	savePlot(samples, phi_all);
	savePlot(samples, eta_all);

	setChannel("EMu");

	savePlot(samples, pt_all);
	savePlot(samples, phi_all);
	savePlot(samples, eta_all);

}

} /* namespace std */
