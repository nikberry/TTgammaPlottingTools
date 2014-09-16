/*
 * ABCD.h
 *
 *  Created on: May 21, 2014
 *      Author: Nik
 */

#include "TString.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1D.h"
#include "THStack.h"
#include "TLegend.h"
#include "TText.h"

#include <iostream>

#include "../../interface/GlobalVariables.h"
#include "../../interface/Samples/AllSamples.h"
#include "../../interface/Variables/Variable.h"
#include "../../interface/Variables/Variable2D.h"
#include "../../interface/ABCDs/TdrStyle.h"

#ifndef ABCD_H_
#define ABCD_H_

namespace std {

class ABCD {
public:
	ABCD();
	virtual ~ABCD();
	void allPlotsABCD(AllSamples samples);
protected:
	TString objName;
	TString selection;
	TString selection2;
	TString channel;
//	void setSelectionAndChannel(TString sel_name, TString sel_name2, TString chan);
//	void setSelectionAndChannel(TString sel_name, TString chan);
//	void setChannel(TString chan);
//	TLegend* legend(AllSamples samples);
	TText* doPrelim(double x_pos,double y_pos);
	TText* doChan(double x_pos,double y_pos);
	TH1D* readHistogram(Sample sample, Variable variable);
	void readHistos(AllSamples samples, Variable variable);
//	THStack* buildStack(AllSamples samples, Variable variable);
//	TH1D* allMChisto(AllSamples samples, Variable variable);
//	TH1D* hashErrors(AllSamples samples, Variable variable);
//	void addOverFlow(TH1D* overflow, Variable variable);
//	void standardPlot(TH1D* data, THStack *hs, AllSamples samples, Variable variable);
//	void standardPlotSignalComparison(TH1D* data, AllSamples samples, Variable variable);
	void standardPlotABCD(TH1D* data, AllSamples samples, Variable variable);
//        void standardPlotABCDAllChannels(TH1D* data, AllSamples samples, Variable variable);
//	void ratioPlot(TH1D* data, THStack *hs, AllSamples samples, Variable variable);
//	void ratioPlotSignalComparison(TH1D* data, AllSamples samples, Variable variable);
//	void SignalComparison(AllSamples samples, Variable variable);
	void ABCD(AllSamples samples, Variable variable);
	void ABCDAllChannels(AllSamples samples, Variable variable);
	void set_plot_style(); 
//	void savePlot(AllSamples samples, Variable variable);
//	void rebinMethod(double rebinning);
};

} /* namespace std */
#endif /* ABCD_H_ */
