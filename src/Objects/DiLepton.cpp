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

	setSelectionChannelAndObj("TTbarDiLeptonAnalysis", "MuMu", "DiLepton");
	savePlot(samples, pt_lead);

}


void DiLepton::setSelectionChannelAndObj(TString sel_name, TString chan1, TString chan2){
	selection = sel_name;
	channel = chan1;
	objName = chan2;
}

} /* namespace std */
