/*
 * Photons.h
 *
 *  Created on: Oct 28, 2013
 *      Author: philip
 */

#include "../../interface/Objects/Object.h"

#ifndef PHOTONS_H_
#define PHOTONS_H_

namespace std {

class Photons: public Object {
public:
	Photons();
	virtual ~Photons();
	void allPlots(AllSamples samples);
	void allPlots2D(AllSamples2D samples);
private:
	void setPhotonSel(TString photon_sel);
};

} /* namespace std */
#endif /* PHOTONS_H_ */
