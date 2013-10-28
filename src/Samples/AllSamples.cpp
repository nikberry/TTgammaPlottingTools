/*
 * AllSamples.cpp
 *
 *  Created on: Oct 15, 2013
 *      Author: philip
 */

#include "../../interface/Samples/AllSamples.h"

namespace std {

AllSamples::AllSamples() {

	mumu_data = new Sample;
	Sample mumu_temp("DoubleMu", kBlack, kBlack);
	*mumu_data = mumu_temp;

	ee_data = new Sample;
	Sample ee_temp("DoubleElectron", kBlack, kBlack);
	*ee_data = ee_temp;

	emu_data = new Sample;
	Sample emu_temp("MuEG", kBlack, kBlack);
	*emu_data = emu_temp;

	ttgamma = new Sample;
	Sample ttgamma_temp("TTGamma", kAzure+8, kBlack);
	*ttgamma = ttgamma_temp;

	ttbar = new Sample;
	Sample ttbar_temp("TTJet", kRed, kBlack);
	*ttbar = ttbar_temp;

	single_t = new Sample;
	Sample single_t_temp("SingleTop", kMagenta, kBlack);
	*single_t = single_t_temp;

	wjets = new Sample;
	Sample wjets_temp("WJetsToLNu", kGreen-3, kBlack);
	*wjets = wjets_temp;

	zjets = new Sample;
	Sample zjets_temp("DYJetsToLL", kAzure-2, kBlack);
	*zjets = zjets_temp;

	diboson = new Sample;
	Sample diboson_temp("DiBoson", kGreen+3, kBlack);
	*diboson = diboson_temp;

	qcd = new Sample;
	Sample qcd_temp("QCD_All", kYellow, kBlack);
	*qcd = qcd_temp;
}

AllSamples::~AllSamples() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
