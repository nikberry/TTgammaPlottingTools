/*
 * AllSamples.h
 *
 *  Created on: Oct 15, 2013
 *      Author: philip
 */

#ifndef ALLSAMPLES_H_
#define ALLSAMPLES_H_

#include "Sample.h"

namespace std {

class AllSamples {
public:
	AllSamples();
	virtual ~AllSamples();

	Sample* mumu_data;
	Sample* ee_data;
	Sample* emu_data;
	Sample* ttgamma;
	Sample* ttbar;
	Sample* single_t;
	Sample* wjets;
	Sample* zjets;
	Sample* diboson;
	Sample* qcd;
};

} /* namespace std */
#endif /* ALLSAMPLES_H_ */
