/*
 * Object.h
 *
 *  Created on: Oct 18, 2013
 *      Author: philip
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
#include "../../interface/Objects/TdrStyle.h"

#ifndef OBJECT_H_
#define OBJECT_H_

namespace std {

class Object {
public:
	Object();
	virtual ~Object();
	void allPlots(AllSamples samples);
protected:
	TString objName;
	TString selection;
	TString selection2;
	TString channel;
	void setSelectionAndChannel(TString sel_name, TString sel_name2, TString chan);
	void setSelectionAndChannel(TString sel_name, TString chan);
	void setChannel(TString chan);
	TLegend* legend(AllSamples samples);
	TText* doPrelim(double x_pos,double y_pos);
	TText* doChan(double x_pos,double y_pos);
	TH1D* readHistogram(Sample sample, Variable variable);
	void readHistos(AllSamples samples, Variable variable);
	THStack* buildStack(AllSamples samples, Variable variable);
	TH1D* allMChisto(AllSamples samples, Variable variable);
	TH1D* hashErrors(AllSamples samples, Variable variable);
	void addOverFlow(TH1D* overflow, Variable variable);
	void standardPlot(TH1D* data, THStack *hs, AllSamples samples, Variable variable);
	void ratioPlot(TH1D* data, THStack *hs, AllSamples samples, Variable variable);
	void savePlot(AllSamples samples, Variable variable);
//	void rebinMethod(double rebinning);
};

} /* namespace std */
#endif /* OBJECT_H_ */
