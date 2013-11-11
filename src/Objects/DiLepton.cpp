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
	Variable pt_lead("LeadLepton_Pt", "lead lepton p_{T}", 0, 300, 5);
	Variable pt_second("SecondLepton_Pt", "second lepton p_{T}", 0, 300, 5); 
        Variable eta_lead("LeadLepton_Eta", "lead lepton #eta", -3, 3, 5);
        Variable eta_second("SecondLepton_Eta", "second lepton #eta", -3, 3, 5);
	Variable abseta_lead("LeadLepton_AbsEta", "lead lepton |#eta|", 0, 3, 5);
        Variable abseta_second("SecondLepton_AbsEta", "second lepton |#eta|", 0, 3, 5);
        Variable phi_lead("LeadLepton_Phi", "lead lepton #phi", -4, 4, 5);
        Variable phi_second("SecondLepton_Phi", "second lepton #phi", -4, 4, 5);
	Variable dileptonmass("diLepton_Mass", "M_{ll}", 0, 400, 5);

	setSelectionAndChannel("TTbarDiLeptonAnalysis", "MuMu");
	savePlot(samples, pt_lead);
        savePlot(samples, pt_second);
        savePlot(samples, eta_lead);
        savePlot(samples, eta_second);
	savePlot(samples, abseta_lead);
        savePlot(samples, abseta_second);
        savePlot(samples, phi_lead);
        savePlot(samples, phi_second);
        savePlot(samples, dileptonmass);
	
	setChannel("EE");
	savePlot(samples, pt_lead);
        savePlot(samples, pt_second);
        savePlot(samples, eta_lead);
        savePlot(samples, eta_second);
        savePlot(samples, abseta_lead);
        savePlot(samples, abseta_second);
        savePlot(samples, phi_lead);
        savePlot(samples, phi_second);
        savePlot(samples, dileptonmass);

	setChannel("EMu");
	savePlot(samples, pt_lead);
        savePlot(samples, pt_second);
        savePlot(samples, eta_lead);
        savePlot(samples, eta_second);
        savePlot(samples, abseta_lead);
        savePlot(samples, abseta_second);
        savePlot(samples, phi_lead);
        savePlot(samples, phi_second);
        savePlot(samples, dileptonmass);

	setSelectionAndChannel("TTbarPhotonAnalysis", "MuMu");
	savePlot(samples, pt_lead);
        savePlot(samples, pt_second);
        savePlot(samples, eta_lead);
        savePlot(samples, eta_second);
        savePlot(samples, abseta_lead);
        savePlot(samples, abseta_second);
        savePlot(samples, phi_lead);
        savePlot(samples, phi_second);
        savePlot(samples, dileptonmass);

	setChannel("EE");
	savePlot(samples, pt_lead);
        savePlot(samples, pt_second);
        savePlot(samples, eta_lead);
        savePlot(samples, eta_second);
        savePlot(samples, abseta_lead);
        savePlot(samples, abseta_second);
        savePlot(samples, phi_lead);
        savePlot(samples, phi_second);
        savePlot(samples, dileptonmass);

	setChannel("EMu");
	savePlot(samples, pt_lead);
        savePlot(samples, pt_second);
        savePlot(samples, eta_lead);
        savePlot(samples, eta_second);
        savePlot(samples, abseta_lead);
        savePlot(samples, abseta_second);
        savePlot(samples, phi_lead);
        savePlot(samples, phi_second);
        savePlot(samples, dileptonmass);
}

} /* namespace std */
