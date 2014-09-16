/*                                                                                                                                                                                                                                                                       
 * Variable2D.h
 *
 *  Created on: April 30, 2014
 *      Author: N.Berry 
 */

#include "TString.h"

#ifndef VARIABLE2D_H_
#define VARIABLE2D_H_

namespace std {

class Variable2D {
public:
        Variable2D();
        Variable2D(TString name_temp, TString XTitle_temp, TString YTitle_temp, double minX, double maxX, int rebinFact_temp, double minY_temp, double maxY_temp);
        virtual ~Variable2D();
        TString name;
        TString XTitle;
	TString YTitle;
        double minX;
        double maxX;
        int rebinFact;
	double minY;
	double maxY;
//	int rebinFactY;
	
};

} /* namespace std */
#endif /* VARIABLE2D_H_ */
