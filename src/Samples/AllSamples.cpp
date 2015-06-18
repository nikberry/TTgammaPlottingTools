/*
 * AllSamples.cpp
 *
 *  Created on: Oct 15, 2013
 *      Author: philip
 */

#include "../../interface/Samples/AllSamples.h"

namespace std {

AllSamples::AllSamples(TString systematic, TString eSystematic) {

	mumu_data = new Sample;
	Sample mumu_temp("DoubleMu", kBlack, kBlack, systematic, eSystematic);
	*mumu_data = mumu_temp;

	ee_data = new Sample;
	Sample ee_temp("DoubleElectron", kBlack, kBlack, systematic, eSystematic);
	*ee_data = ee_temp;

	emu_data = new Sample;
	Sample emu_temp("MuEG", kBlack, kBlack, systematic, eSystematic);
	*emu_data = emu_temp;

	combined_data = new Sample;
	Sample combined_temp("Combined", kBlack, kBlack, systematic, eSystematic);
	*combined_data = combined_temp;

/*	signal = new Sample;
        Sample signal_temp("TTGamma_2-to-7", kAzure+8, kBlack, systematic, eSystematic);
        *signal = signal_temp;

	ttgamma = new Sample;
	Sample ttgamma_temp("TTGamma_2-to-7", kAzure+8, kBlack, systematic, eSystematic);
	*ttgamma = ttgamma_temp;
*/
        signal = new Sample;                                                                                                                          
        Sample signal_temp("TTGamma", kAzure+8, kBlack, systematic, eSystematic);
        *signal = signal_temp;

	ttgamma = new Sample;
	Sample ttgamma_temp("TTGamma", kAzure+8, kBlack, systematic, eSystematic);
	*ttgamma = ttgamma_temp;

//	ttbar = new Sample;
//	Sample ttbar_temp("TTJet", kRed, kBlack, systematic, eSystematic);
//	*ttbar = ttbar_temp;

        ttbar = new Sample;
        Sample ttbar_temp("TTbar", kRed, kBlack, systematic, eSystematic);
        *ttbar = ttbar_temp; 

        ttbar0 = new Sample;
        Sample ttbar0_temp("TTJets_Hadronic", kRed+2, kBlack, systematic, eSystematic);
        *ttbar0 = ttbar0_temp; 

        ttbar1 = new Sample;
        Sample ttbar1_temp("TTJets_SemiLept", kRed+1, kBlack, systematic, eSystematic);
        *ttbar1 = ttbar1_temp; 

        ttbar2 = new Sample;
        Sample ttbar2_temp("TTJets_FullLept", kRed, kBlack, systematic, eSystematic);
        *ttbar2 = ttbar2_temp; 

	single_t = new Sample;
	Sample single_t_temp("SingleTop", kMagenta, kBlack, systematic, eSystematic);
	*single_t = single_t_temp;

	wjets = new Sample;
	Sample wjets_temp("WJetsToLNu", kGreen-3, kBlack, systematic, eSystematic);
	*wjets = wjets_temp;

	dyjets = new Sample;
	Sample dyjets_temp("DYJetsToLL", kAzure-2, kBlack, systematic, eSystematic);
	*dyjets = dyjets_temp;

        vjets = new Sample;
        Sample vjets_temp("VJets", kGreen-3, kBlack, systematic, eSystematic);
        *vjets = vjets_temp;

	diboson = new Sample;
	Sample diboson_temp("DiBoson", kGreen+3, kBlack, systematic, eSystematic);
	*diboson = diboson_temp;

	qcd = new Sample;
	Sample qcd_temp("QCD_All", kYellow, kBlack, systematic, eSystematic);
	*qcd = qcd_temp;
}

AllSamples::~AllSamples() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
