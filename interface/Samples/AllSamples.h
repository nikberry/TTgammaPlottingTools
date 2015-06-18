/*
 * AllSamples.h
 *
 *  Created on: Oct 15, 2013
 *      Author: philip
 */

#ifndef ALLSAMPLES_H_
#define ALLSAMPLES_H_

#include "Sample.h"
#include "TObject.h"

namespace std {

class AllSamples {
public:
	AllSamples(TString systematic, TString eSystematic);
	virtual ~AllSamples();

	Sample* mumu_data;
	Sample* ee_data;
	Sample* emu_data;
	Sample* combined_data;
	Sample* signal;
	Sample* ttgamma;
	Sample* ttbar;
	Sample* ttbar0;
	Sample* ttbar1;
	Sample* ttbar2;
	Sample* single_t;
	Sample* wjets;
	Sample* dyjets;
	Sample* vjets;
	Sample* diboson;
	Sample* qcd;
};

} /* namespace std */
#endif /* ALLSAMPLES_H_ */
