#include "TFile.h"
#include "TH1.h"
#include "TObject.h"
#include "TString.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLegend.h"
#include "THStack.h"
#include <string.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "TROOT.h"

TH2D* getSample(TString sample, double weight, TString Variable, TString channel, TString type, TString Systematic);
//TH1D* getQCD(TString Obj, TString Variable, int RebinFact);
//TText* doPrelim(float x, float y, TString nbtags);

TH2D* getSample(TString sample, double weight, TString Variable, TString channel, TString type, TString Systematic){
	TString dir = "/data1/TTGammaAnalysis/HistogramFiles/Version14LooseBtag/"+ Systematic +"/";

	TString syst = "";

	if(Systematic == "BJet_down")
		syst = "_minusBJet";
	else if(Systematic == "BJet_up")
		syst = "_plusBjet";
	else if(Systematic == "JES_down")
		syst = "_minusJES";
	else if(Systematic == "JES_up")
		syst = "_plusJES";
	else if(Systematic == "LightJet_up")
		syst = "_plusLightJet";	
	else if(Systematic == "LightJet_down")
		syst = "_minusLightJet";							
	else if(Systematic == "PU_down")
		syst = "_PU_65835mb";
	else if(Systematic == "PU_up")
		syst = "_PU_72765mb";
	else	
		syst = "";

	TFile* file = new TFile(dir + sample + "_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon"+syst+".root");
	//TDirectoryFile* folder = (TDirectoryFile*) file->Get("TTbarPlusMetAnalysis/QCD No Iso/Muon/");

	cout << "file: " << dir + sample + "_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon"+syst+".root" << endl;
	cout << "folder: " << "TTbarPhotonAnalysis/"+channel+"/Ref selection/Photons/"+type+"/" << endl;
	
	
	TH2D* plot; 
	TH2D* plot2;
	TH2D* plot3;
	TH2D* plot4;

	plot = (TH2D*) file->Get("TTbarPhotonAnalysis/"+channel+"/Ref selection/Photons/"+type+"/"+Variable+"_1btag");
	plot2 = (TH2D*) file->Get("TTbarPhotonAnalysis/"+channel+"/Ref selection/Photons/"+type+"/"+Variable+"_2btags");
	plot3 = (TH2D*) file->Get("TTbarPhotonAnalysis/"+channel+"/Ref selection/Photons/"+type+"/"+Variable+"_3btags");
	plot4 = (TH2D*) file->Get("TTbarPhotonAnalysis/"+channel+"/Ref selection/Photons/"+type+"/"+Variable+"_4orMoreBtags");

	plot->Add(plot2);
	plot->Add(plot3);
	plot->Add(plot4);

//        if(sample == "TTJet" || sample == "TTJet_SemiLept"|| sample == "TTJet_POWHEG"|| sample == "TTJet_MCNLO"|| sample == "TTJetPTRW"){
//	plot->SetFillColor(kRed+1);
 //       plot->SetLineColor(kRed+1);
//	}else if(sample == "TTJet_FullLept"){
//	plot->SetFillColor(kRed+2);
//       plot->SetLineColor(kRed+2);	
//	}else if(sample == "TTJet_Hadronic"){
//	plot->SetFillColor(kRed+3);
 //       plot->SetLineColor(kRed+3);
//	}else if(sample == "WJetsToLNu" || sample == "W1Jet" || sample == "W2Jets"|| sample == "W3Jets"|| sample == "W4Jets"|| sample == "VJets"){
//	plot->SetLineColor(kGreen-3);	  
//  	plot->SetFillColor(kGreen-3);
//	}else if(sample == "DYJetsToLL" || sample == "DY1JetsToLL" || sample == "DY2JetsToLL" || sample == "DY3JetsToLL" || sample == "DY4JetsToLL"){
//	plot->SetFillColor(kAzure-2);
//	plot->SetLineColor(kAzure-2);
//	}else if(sample == "QCD_Pt_20_MuEnrichedPt_15" || sample == "QCD_Pt-15to20_MuEnrichedPt5" || sample=="QCD_Pt-15to20_MuEnrichedPt5" || sample =="QCD_Pt-20to30_MuEnrichedPt5" || sample ==    "QCD_Pt-30to50_MuEnrichedPt5" || sample ==    "QCD_Pt-50to80_MuEnrichedPt5" || sample ==    "QCD_Pt-80to120_MuEnrichedPt5" || sample ==   "QCD_Pt-120to170_MuEnrichedPt5" || sample ==  "QCD_Pt-170to300_MuEnrichedPt5" || sample ==  "QCD_Pt-300to470_MuEnrichedPt5" || sample ==  "QCD_Pt-470to600_MuEnrichedPt5" || sample ==  "QCD_Pt-800to1000_MuEnrichedPt5" || sample =="QCD_Pt-1000_MuEnrichedPt5" 	 ){
//	plot->SetFillColor(kYellow);
//	plot->SetLineColor(kYellow);
//	}else if(sample == "T_t-channel" || sample == "T_tW-channel" || sample == "T_s-channel" || sample == "Tbar_t-channel" || sample == "Tbar_tW-channel" || sample == "Tbar_s-channel"){
//	plot->SetFillColor(kMagenta);
//	plot->SetLineColor(kMagenta);
//	}else if(sample == "SingleMu"){
//	plot->SetLineColor(kBlack);	  
//	}

	//plot->Scale(weight);
//	plot->Rebin(rebinFact);

	plot->SetDirectory(gROOT);
	file->Close();

	return plot;

}


//always data
// TH1D* getQCD(TString Obj, TString Variable, int rebinFact){
// 	TString dir = "rootFilesV4/central/";
// 	TFile* file = new TFile(dir + "SingleMu_19584pb_PFElectron_PFMuon_PF2PATJets_PFMET.root");
// 	//TDirectoryFile* folder = (TDirectoryFile*) file->Get("TTbarPlusMetAnalysis/QCD No Iso/Muon/");
// 
// 	TH1D* plot = (TH1D*) file->Get("TTbar_plus_X_analysis/MuPlusJets/QCD non iso mu+jets ge4j/"+Obj+Variable+"0btag");
// 
// 	plot->SetFillColor(kYellow);
// 	plot->SetLineColor(kYellow);
//     	
// 	plot->Scale(1/plot->Integral());
// 	plot->Rebin(rebinFact);
// 
// 	plot->SetDirectory(gROOT);
// 	file->Close();
// 
// 	return plot;
// 
// }
// 

 TText* doPrelimABCD(float x, float y)
{
   std::ostringstream stream;
   stream  << "A              B/n C             D";  

   TLatex* textABCD = new TLatex(x, y, stream.str().c_str());
   //text->SetTextAlign(33);  //left
   //text->SetTextAlign(22);  //center
   //text->SetTextAlign(11);  //right
   text->SetNDC(true);
   text->SetTextFont(62);
   text->SetTextSize(0.1);  // for thesis

   return textABCD;
 }

 TText* doPrelim(float x, float y)
{
   std::ostringstream stream;
   stream  << "#mu#mu, #geq 2 jets, #geq 1 b-jet, #geq 1 #gamma                   CMS Preliminary, L = 19.6 fb^{-1}";   
 
   TLatex* text = new TLatex(x, y, stream.str().c_str());
   //text->SetTextAlign(33);  //left
   //text->SetTextAlign(22);  //center
   //text->SetTextAlign(11);  //right
   text->SetNDC(true);
   text->SetTextFont(62);
   text->SetTextSize(0.045);  // for thesis
 
   return text;
 }
