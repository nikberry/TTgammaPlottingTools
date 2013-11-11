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
	Variable jet1pt("jet1_pT", "p_{T}(leading jet)", 0., 400., 5);
	Variable jet1phi("jet1_phi", "#eta(leading jet)", -3., 3., 5);
	Variable jet1eta("jet1_eta", "#eta(leading jet)", -4., 4., 5);
//	Variable numberofbjets("N_BJets", "N(B-jets)", -1., 7., 1);
	Variable numberofjets("N_Jets", "N(Jets)", -1., 7., 1);

	setSelectionAndChannel("TTbarDiLeptonAnalysis", "MuMu");
	savePlot(samples, pt_all);
	savePlot(samples, phi_all);
	savePlot(samples, eta_all);
        savePlot(samples, jet1pt);
        savePlot(samples, jet1phi);
        savePlot(samples, jet1eta);
  //      savePlot(samples, numberofbjets);
        savePlot(samples, numberofjets);

	setChannel("EE");
	savePlot(samples, pt_all);
	savePlot(samples, phi_all);
	savePlot(samples, eta_all);
	savePlot(samples, jet1pt);
        savePlot(samples, jet1phi);
        savePlot(samples, jet1eta);
    //    savePlot(samples, numberofbjets);
        savePlot(samples, numberofjets);

	setChannel("EMu");
	savePlot(samples, pt_all);
	savePlot(samples, phi_all);
	savePlot(samples, eta_all);
        savePlot(samples, jet1pt);
        savePlot(samples, jet1phi);
        savePlot(samples, jet1eta);
   //     savePlot(samples, numberofbjets);
        savePlot(samples, numberofjets);

	pt_all.rebinFact *= 2;
	phi_all.rebinFact *= 2;
	eta_all.rebinFact *= 2;

	setSelectionAndChannel("TTbarPhotonAnalysis", "MuMu");
	savePlot(samples, pt_all);
	savePlot(samples, phi_all);
	savePlot(samples, eta_all);
        savePlot(samples, jet1pt);
        savePlot(samples, jet1phi);
        savePlot(samples, jet1eta);
     //   savePlot(samples, numberofbjets);
        savePlot(samples, numberofjets);

	setChannel("EE");
	savePlot(samples, pt_all);
	savePlot(samples, phi_all);
	savePlot(samples, eta_all);
        savePlot(samples, jet1pt);
        savePlot(samples, jet1phi);
        savePlot(samples, jet1eta);
  //      savePlot(samples, numberofbjets);
        savePlot(samples, numberofjets);

	setChannel("EMu");
	savePlot(samples, pt_all);
	savePlot(samples, phi_all);
	savePlot(samples, eta_all);
        savePlot(samples, jet1pt);
        savePlot(samples, jet1phi);
        savePlot(samples, jet1eta);
//        savePlot(samples, numberofbjets);
        savePlot(samples, numberofjets);
}

} /* namespace std */
