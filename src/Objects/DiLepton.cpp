/*
 * DiLepton.cpp
 *
 *  Created on: Oct 28, 2013
 *      Author: philip
 */

#include "../../interface/Objects/DiLepton.h"

namespace std {

DiLepton::DiLepton() {
	// TODO Auto-generated constructor stub
	objName = "DiLepton";
}

DiLepton::~DiLepton() {
	// TODO Auto-generated destructor stub
}


void DiLepton::allPlots(AllSamples samples){

	//  Variable::Variable(TString name_temp, TString xTitle_temp, double minX_temp, double maxX_temp, int rebinFact_temp)
	Variable pt_lead("LeadLepton_Pt", "lead #mu p_{T}", 0, 300, 5);

	setSelectionAndChannel("TTbarDiLeptonAnalysis", "MuMu");
	savePlot(samples, pt_lead);

	setChannel("EE");
	savePlot(samples, pt_lead);

	setChannel("EMu");
	savePlot(samples, pt_lead);

	setSelectionAndChannel("TTbarPhotonAnalysis", "MuMu");
	savePlot(samples, pt_lead);

	setChannel("EE");
	savePlot(samples, pt_lead);

	setChannel("EMu");
	savePlot(samples, pt_lead);

}

} /* namespace std */
