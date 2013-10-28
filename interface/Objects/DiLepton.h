/*
 * DiLepton.h
 *
 *  Created on: Oct 28, 2013
 *      Author: philip
 */

#include "../../interface/Objects/Object.h"

#ifndef DILEPTON_H_
#define DILEPTON_H_

namespace std {

class DiLepton: public Object  {
public:
	DiLepton();
	virtual ~DiLepton();
	void allPlots(AllSamples samples);
private:
	void setSelectionChannelAndObj(TString sel_name, TString chan1, TString chan2);
};

} /* namespace std */
#endif /* DILEPTON_H_ */
