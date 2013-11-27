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
	Variable photon_eta("Photon_Eta", "Photon #eta", -3., 3., 10);
	Variable photon_abseta("Photon_AbsEta", "Photon |#eta|", 0., 3., 10);
	Variable photon_sigmaietaieta_barrel("Photon_sigma_ietaieta_barrel", "#sigmai#etai#eta(barrel)", 0., 0.1, 10);
	Variable photon_sigmaietaieta_endcap("Photon_sigma_ietaieta_endcap", "#sigmai#etai#eta(endcap)", 0., 0.1, 12);
	Variable photon_rhocorrchargediso_barrel("Photon_RhoCorrectedPFChargedHadronIso_barrel", "RhoCorrPFChargedHadronIso(barrel)", 0., 10., 2);
	Variable photon_rhocorrchargediso_endcap("Photon_RhoCorrectedPFChargedHadronIso_endcap", "RhoCorrPFChargedHadronIso(endcap)", 0., 10., 2);
	Variable photon_chargediso_barrel("Photon_PFChargedHadronIso_barrel", "PFChargedHadronIso(barrel)", 0., 10., 2);
	Variable photon_chargediso_endcap("Photon_PFChargedHadronIso_endcap", "PFChargedHadronIso(endcap)", 0., 10., 2);
	Variable photon_rhocorrneutraliso_barrel("Photon_RhoCorrectedPFNeutralHadronIso_barrel", "RhoCorrPFNeutralHadronIso(barrel)", 0., 10., 2);
	Variable photon_rhocorrneutraliso_endcap("Photon_RhoCorrectedPFNeutralHadronIso_endcap", "RhoCorrPFNeutralHadronIso(endcap)", 0., 10., 2);	
	Variable photon_neutraliso_barrel("Photon_PFNeutralHadronIso_barrel", "PFNeutralHadronIso(barrel)", 0., 10., 2);
	Variable photon_neutraliso_endcap("Photon_PFNeutralHadronIso_endcap", "PFNeutralHadronIso(endcap)", 0., 10., 2);   
	Variable photon_rhocorrphotoniso_barrel("Photon_RhoCorrectedPFPhotonIso_barrel", "RhoCorrPFPhotonIso(barrel)", 0., 10., 2);
	Variable photon_rhocorrphotoniso_endcap("Photon_RhoCorrectedPFPhotonIso_endcap", "RhoCorrPFPhotonIso(endcap)", 0., 10., 2);
	Variable photon_photoniso_barrel("Photon_PFPhotonIso_barrel", "PFPhotonIso(barrel)", 0., 10., 2);
	Variable photon_photoniso_endcap("Photon_PFPhotonIso_endcap", "PFPhotonIso(endcap)", 0., 10., 2);
	Variable photon_htowoe("Photon_HtowoE", "H/E", 0., 5., 2);
	Variable photon_numberofphotons("Number_Of_Photons", "N(#gamma)", -0.5, 6.5, 1);


	setSelectionAndChannel("TTbarDiLeptonAnalysis", "MuMu");
	setPhotonSel("AllPhotons");
	savePlot(samples, photon_pt);
	savePlot(samples, photon_eta);
	savePlot(samples, photon_abseta);
	savePlot(samples, photon_sigmaietaieta_barrel);
	savePlot(samples, photon_sigmaietaieta_endcap);
	savePlot(samples, photon_rhocorrchargediso_barrel);
	savePlot(samples, photon_rhocorrchargediso_endcap);
	savePlot(samples, photon_chargediso_barrel);
	savePlot(samples, photon_chargediso_endcap);
	savePlot(samples, photon_rhocorrneutraliso_barrel);
	savePlot(samples, photon_rhocorrneutraliso_endcap);
	savePlot(samples, photon_neutraliso_barrel);
	savePlot(samples, photon_neutraliso_endcap);
	savePlot(samples, photon_rhocorrphotoniso_barrel);
	savePlot(samples, photon_rhocorrphotoniso_endcap);
	savePlot(samples, photon_photoniso_barrel);
	savePlot(samples, photon_photoniso_endcap);
	savePlot(samples, photon_htowoe);
	savePlot(samples, photon_numberofphotons);
	
	photon_sigmaietaieta_endcap.rebinFact *= 2;
	
	setChannel("EE");
	savePlot(samples, photon_pt);
	savePlot(samples, photon_eta);
	savePlot(samples, photon_abseta);
	savePlot(samples, photon_sigmaietaieta_barrel);
	savePlot(samples, photon_sigmaietaieta_endcap);
	savePlot(samples, photon_rhocorrchargediso_barrel);
	savePlot(samples, photon_rhocorrchargediso_endcap);
	savePlot(samples, photon_chargediso_barrel);
	savePlot(samples, photon_chargediso_endcap);
	savePlot(samples, photon_rhocorrneutraliso_barrel);
	savePlot(samples, photon_rhocorrneutraliso_endcap);
	savePlot(samples, photon_neutraliso_barrel);
	savePlot(samples, photon_neutraliso_endcap);
	savePlot(samples, photon_rhocorrphotoniso_barrel);
	savePlot(samples, photon_rhocorrphotoniso_endcap);
	savePlot(samples, photon_photoniso_barrel);
	savePlot(samples, photon_photoniso_endcap);
	savePlot(samples, photon_htowoe);
	savePlot(samples, photon_numberofphotons);
	
	setChannel("EMu");
	savePlot(samples, photon_pt);
	savePlot(samples, photon_eta);
	savePlot(samples, photon_abseta);
	savePlot(samples, photon_sigmaietaieta_barrel);
	savePlot(samples, photon_sigmaietaieta_endcap);
	savePlot(samples, photon_rhocorrchargediso_barrel);
	savePlot(samples, photon_rhocorrchargediso_endcap);
	savePlot(samples, photon_chargediso_barrel);
	savePlot(samples, photon_chargediso_endcap);
	savePlot(samples, photon_rhocorrneutraliso_barrel);
	savePlot(samples, photon_rhocorrneutraliso_endcap);
	savePlot(samples, photon_neutraliso_barrel);
	savePlot(samples, photon_neutraliso_endcap);
	savePlot(samples, photon_rhocorrphotoniso_barrel);
	savePlot(samples, photon_rhocorrphotoniso_endcap);
	savePlot(samples, photon_photoniso_barrel);
	savePlot(samples, photon_photoniso_endcap);
	savePlot(samples, photon_htowoe);
	savePlot(samples, photon_numberofphotons);

	photon_pt.rebinFact *= 2;
	photon_eta.rebinFact *= 2;

	setSelectionAndChannel("TTbarPhotonAnalysis", "MuMu");
	setPhotonSel("SignalPhotons");
	savePlot(samples, photon_pt);
	savePlot(samples, photon_eta);
	savePlot(samples, photon_abseta);
        savePlot(samples, photon_sigmaietaieta_barrel);
        savePlot(samples, photon_sigmaietaieta_endcap);
        savePlot(samples, photon_rhocorrchargediso_barrel);
        savePlot(samples, photon_rhocorrchargediso_endcap);
	savePlot(samples, photon_chargediso_barrel);
	savePlot(samples, photon_chargediso_endcap);
	savePlot(samples, photon_rhocorrneutraliso_barrel);
	savePlot(samples, photon_rhocorrneutraliso_endcap);
	savePlot(samples, photon_neutraliso_barrel);
	savePlot(samples, photon_neutraliso_endcap);
	savePlot(samples, photon_rhocorrphotoniso_barrel);
	savePlot(samples, photon_rhocorrphotoniso_endcap);
	savePlot(samples, photon_photoniso_barrel);
	savePlot(samples, photon_photoniso_endcap);
	savePlot(samples, photon_htowoe);
        savePlot(samples, photon_numberofphotons);
	
	photon_abseta.rebinFact *= 2;
	photon_sigmaietaieta_barrel.rebinFact *= 2;
//	photon_sigmaietaieta_endcap.rebinFact *= 2;

	setChannel("EE");
	savePlot(samples, photon_pt);
	savePlot(samples, photon_eta);
        savePlot(samples, photon_abseta);
        savePlot(samples, photon_sigmaietaieta_barrel);
        savePlot(samples, photon_sigmaietaieta_endcap);
        savePlot(samples, photon_rhocorrchargediso_barrel);
        savePlot(samples, photon_rhocorrchargediso_endcap);
	savePlot(samples, photon_chargediso_barrel);
	savePlot(samples, photon_chargediso_endcap);
	savePlot(samples, photon_rhocorrneutraliso_barrel);
	savePlot(samples, photon_rhocorrneutraliso_endcap);
	savePlot(samples, photon_neutraliso_barrel);
	savePlot(samples, photon_neutraliso_endcap);
	savePlot(samples, photon_rhocorrphotoniso_barrel);
	savePlot(samples, photon_rhocorrphotoniso_endcap);
	savePlot(samples, photon_photoniso_barrel);
	savePlot(samples, photon_photoniso_endcap);
	savePlot(samples, photon_htowoe);
        savePlot(samples, photon_numberofphotons);

	setChannel("EMu");
	savePlot(samples, photon_pt);
	savePlot(samples, photon_eta);
        savePlot(samples, photon_abseta);
        savePlot(samples, photon_sigmaietaieta_barrel);
        savePlot(samples, photon_sigmaietaieta_endcap);
        savePlot(samples, photon_rhocorrchargediso_barrel);
        savePlot(samples, photon_rhocorrchargediso_endcap);
	savePlot(samples, photon_chargediso_barrel);
	savePlot(samples, photon_chargediso_endcap);
	savePlot(samples, photon_rhocorrneutraliso_barrel);
	savePlot(samples, photon_rhocorrneutraliso_endcap);
	savePlot(samples, photon_neutraliso_barrel);
	savePlot(samples, photon_neutraliso_endcap);
	savePlot(samples, photon_rhocorrphotoniso_barrel);
	savePlot(samples, photon_rhocorrphotoniso_endcap);
	savePlot(samples, photon_photoniso_barrel);
	savePlot(samples, photon_photoniso_endcap);
	savePlot(samples, photon_htowoe);
        savePlot(samples, photon_numberofphotons);

	setPhotonSel("NminusOnePhotons");
	setChannel("MuMu");
	savePlot(samples, photon_pt);
	savePlot(samples, photon_eta);
        savePlot(samples, photon_abseta);
        savePlot(samples, photon_sigmaietaieta_barrel);
        savePlot(samples, photon_sigmaietaieta_endcap);
        savePlot(samples, photon_rhocorrchargediso_barrel);
        savePlot(samples, photon_rhocorrchargediso_endcap);
	savePlot(samples, photon_chargediso_barrel);
	savePlot(samples, photon_chargediso_endcap);
	savePlot(samples, photon_rhocorrneutraliso_barrel);
	savePlot(samples, photon_rhocorrneutraliso_endcap);
	savePlot(samples, photon_neutraliso_barrel);
	savePlot(samples, photon_neutraliso_endcap);
	savePlot(samples, photon_rhocorrphotoniso_barrel);
	savePlot(samples, photon_rhocorrphotoniso_endcap);
	savePlot(samples, photon_photoniso_barrel);
	savePlot(samples, photon_photoniso_endcap);
	savePlot(samples, photon_htowoe);
//        savePlot(samples, photon_numberofphotons);

	setChannel("EE");
	savePlot(samples, photon_pt);
	savePlot(samples, photon_eta);
        savePlot(samples, photon_abseta);
        savePlot(samples, photon_sigmaietaieta_barrel);
        savePlot(samples, photon_sigmaietaieta_endcap);
        savePlot(samples, photon_rhocorrchargediso_barrel);
        savePlot(samples, photon_rhocorrchargediso_endcap);
	savePlot(samples, photon_chargediso_barrel);
	savePlot(samples, photon_chargediso_endcap);
	savePlot(samples, photon_rhocorrneutraliso_barrel);
	savePlot(samples, photon_rhocorrneutraliso_endcap);
	savePlot(samples, photon_neutraliso_barrel);
	savePlot(samples, photon_neutraliso_endcap);
	savePlot(samples, photon_rhocorrphotoniso_barrel);
	savePlot(samples, photon_rhocorrphotoniso_endcap);
	savePlot(samples, photon_photoniso_barrel);
	savePlot(samples, photon_photoniso_endcap);
	savePlot(samples, photon_htowoe);
//        savePlot(samples, photon_numberofphotons);

	setChannel("EMu");
	savePlot(samples, photon_pt);
	savePlot(samples, photon_eta);
        savePlot(samples, photon_abseta);
        savePlot(samples, photon_sigmaietaieta_barrel);
        savePlot(samples, photon_sigmaietaieta_endcap);
        savePlot(samples, photon_rhocorrchargediso_barrel);
        savePlot(samples, photon_rhocorrchargediso_endcap);
	savePlot(samples, photon_chargediso_barrel);
	savePlot(samples, photon_chargediso_endcap);
	savePlot(samples, photon_rhocorrneutraliso_barrel);
	savePlot(samples, photon_rhocorrneutraliso_endcap);
	savePlot(samples, photon_neutraliso_barrel);
	savePlot(samples, photon_neutraliso_endcap);
	savePlot(samples, photon_rhocorrphotoniso_barrel);
	savePlot(samples, photon_rhocorrphotoniso_endcap);
	savePlot(samples, photon_photoniso_barrel);
	savePlot(samples, photon_photoniso_endcap);
	savePlot(samples, photon_htowoe);
//        savePlot(samples, photon_numberofphotons);
}

void Photons::setPhotonSel(TString photon_sel){
	objName = "Photons/"+photon_sel;
}

} /* namespace std */
