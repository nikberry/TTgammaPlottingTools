/*
 * Variable2D.cpp
 *
 *  Created on: April 30, 2014
 *      Author: Nik 
 */

#include "../../interface/Variables/Variable2D.h"

namespace std {

Variable2D::Variable2D() {
        name = "MET";
        XTitle = "E_{T}^{miss}";
        minX = 0.;
        maxX = 300;
        rebinFact = 2;
	YTitle = "Crap";
	minY = 0;
	maxY = 0;
//	rebinFactY = 2;
}

Variable2D::Variable2D(TString name_temp, TString XTitle_temp, TString YTitle_temp, double minX_temp, double maxX_temp, int rebinFact_temp, double minY_temp, double maxY_temp ) { 
        name = name_temp;
        XTitle = XTitle_temp;
	YTitle - YTitle_temp;
        minX = minX_temp;
        maxX = maxX_temp;
        rebinFact = rebinFact_temp;
	minY = minY_temp;
	maxY = maxY_temp;
//	rebinFactY = rebinFactY_temp;
}

Variable2D::~Variable2D() {
        // TODO Auto-generated destructor stub
}

} /* namespace std */
