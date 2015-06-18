/*
 * GlobalVariables.cpp
 *
 *  Created on: Oct 24, 2013
 *      Author: philip
 */

#include "../interface/GlobalVariables.h"

namespace std {

TString Globals::lumi = "19.7 fb^{-1}";

bool Globals::addRatioPlot = true;
bool Globals::addHashErrors= true;
bool Globals::addOverFlow = false;
bool Globals::doLogPlot = false;
bool Globals::isPreliminary = true;
bool Globals::splitTTbar = true;
} /* namespace std */
