/*
 * Photons.cpp
 *
 *  Created on: Oct 28, 2013
 *      Author: philip
 */

#include "../../interface/Objects/Photons.h"

namespace std {

Photons::Photons() {
	// TODO Auto-generated constructor stub
	objName = "Photons";
}

Photons::~Photons() {
	// TODO Auto-generated destructor stub
}

void Photons::allPlots(AllSamples samples){

	Variable photon_pt("Photon_ET", "Photon E_{T} [GeV]", 0, 150, 2);
	Variable photon_eta("Photon_Eta", "Photon #eta", -3., 3., 2);

	setPhotonSel("AllPhotons");
	setSelectionAndChannel("TTbarDiLeptonAnalysis", "MuMu");
	savePlot(samples, photon_pt);
	savePlot(samples, photon_eta);
	setChannel("EE");
	savePlot(samples, photon_pt);
	savePlot(samples, photon_eta);
	setChannel("EMu");
	savePlot(samples, photon_pt);
	savePlot(samples, photon_eta);

	photon_pt.rebinFact *= 2;
	photon_eta.rebinFact *= 2;

	setSelectionAndChannel("TTbarPhotonAnalysis", "MuMu");
	setPhotonSel("SignalPhotons");
	savePlot(samples, photon_pt);
	savePlot(samples, photon_eta);
	setChannel("EE");
	savePlot(samples, photon_pt);
	savePlot(samples, photon_eta);
	setChannel("EMu");
	savePlot(samples, photon_pt);
	savePlot(samples, photon_eta);

	setPhotonSel("NminusOnePhotons");
	savePlot(samples, photon_pt);
	savePlot(samples, photon_eta);
	setChannel("EE");
	savePlot(samples, photon_pt);
	savePlot(samples, photon_eta);
	setChannel("EMu");
	savePlot(samples, photon_pt);
	savePlot(samples, photon_eta);
}

void Photons::setPhotonSel(TString photon_sel){
	objName = "Photons/"+photon_sel;
}

} /* namespace std */
