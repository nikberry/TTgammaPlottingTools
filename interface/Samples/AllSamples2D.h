/*                                                                                                                                                                                                                                                              
 * AllSamples2D.h
 *
 *  Created on: Oct 15, 2014
 *      Author: Nik
 */

#ifndef ALLSAMPLES2D_H_
#define ALLSAMPLES2D_H_

#include "Sample2D.h"
#include "TObject.h"

namespace std {

class AllSamples2D {
public:
        AllSamples2D(TString systematic, TString eSystematic);
        virtual ~AllSamples2D();

        Sample2D* mumu_data;
        Sample2D* ee_data;
        Sample2D* emu_data;
        Sample2D* ttgamma;
        Sample2D* ttbar;
        Sample2D* single_t;
        Sample2D* wjets;
        Sample2D* dyjets;
        Sample2D* vjets;
        Sample2D* diboson;
        Sample2D* qcd;
};

} /* namespace std */
#endif /* ALLSAMPLES2D_H_ */
