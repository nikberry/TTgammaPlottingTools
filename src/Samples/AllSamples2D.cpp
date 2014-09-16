/*
 * AllSamples.cpp
 *
 *  Created on: Jan 15, 2014
 *      Author: Nik
 */

#include "../../interface/Samples/AllSamples2D.h"
                                                                                                                                                                                                                                                                
namespace std {

AllSamples2D::AllSamples2D(TString systematic, TString eSystematic) {

        mumu_data = new Sample2D;
        Sample2D mumu_temp("DoubleMu", kBlack, kBlack, systematic, eSystematic);
        *mumu_data = mumu_temp;

        ee_data = new Sample2D;
        Sample2D ee_temp("DoubleElectron", kBlack, kBlack, systematic, eSystematic);
        *ee_data = ee_temp;

        emu_data = new Sample2D;
        Sample2D emu_temp("MuEG", kBlack, kBlack, systematic, eSystematic);
        *emu_data = emu_temp;

        ttgamma = new Sample2D;
        Sample2D ttgamma_temp("TTGamma", kAzure+8, kBlack, systematic, eSystematic);
        *ttgamma = ttgamma_temp;

        ttbar = new Sample2D;
        Sample2D ttbar_temp("TTJet", kRed, kBlack, systematic, eSystematic);
        *ttbar = ttbar_temp;

        single_t = new Sample2D;
        Sample2D single_t_temp("SingleTop", kMagenta, kBlack, systematic, eSystematic);
        *single_t = single_t_temp;

        wjets = new Sample2D;
        Sample2D wjets_temp("WJetsToLNu", kGreen-3, kBlack, systematic, eSystematic);
        *wjets = wjets_temp;

        dyjets = new Sample2D;
        Sample2D dyjets_temp("DYJetsToLL", kAzure-2, kBlack, systematic, eSystematic);
        *dyjets = dyjets_temp;

        vjets = new Sample2D;
        Sample2D vjets_temp("VJets", kGreen-3, kBlack, systematic, eSystematic);
        *vjets = vjets_temp;

        diboson = new Sample2D;
        Sample2D diboson_temp("DiBoson", kGreen+3, kBlack, systematic, eSystematic);
        *diboson = diboson_temp;

        qcd = new Sample2D;
        Sample2D qcd_temp("QCD_All", kYellow, kBlack, systematic, eSystematic);
        *qcd = qcd_temp;
}

AllSamples2D::~AllSamples2D() {
        // TODO Auto-generated destructor stub
}

} /* namespace std */
