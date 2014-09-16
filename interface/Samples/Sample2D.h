/*                                                                                                                                                                                                                                                              
 * Sample2D.h
 *
 *  Created on: Jan 14, 2014
 *      Author: Nik
 */
#include "TString.h"
#include "TFile.h"
#include "TH2D.h"
#include <iostream>

#ifndef SAMPLE2D_H_
#define SAMPLE2D_H_

namespace std {

class Sample2D {
public:
        Sample2D();
        Sample2D(TString sample, Color_t fColor, Color_t lColor, TString systematic, TString eSystematic);
        virtual ~Sample2D();
        TFile* file;
        TH2D* histo;
        void SetHisto(TH2D* plot);
        void SetFillColor(Color_t fcolor); //pub or priv?
        Color_t GetFillColor();
        void SetLineColor(Color_t fcolor); //pub or priv?
        Color_t GetLineColor();
        Color_t fillColor;
        Color_t lineColor;
};

} /* namespace std */
#endif /* SAMPLE2D_H_ */
