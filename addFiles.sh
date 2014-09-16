#!/bin/bash

echo "*********adding DY root files in folder $1**********"
hadd $1DYJetsToLL_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root $1DYJetsToLL*_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root
echo "*********adding QCD root files in folder $1**********"
hadd $1QCD_All_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root $1QCD*_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root
echo "*********adding SingleTop root files in folder $1**********"
hadd $1SingleTop_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root $1*tW-channel_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root
echo "*********adding DiBoson root files in folder $1**********"
hadd $1DiBoson_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root $1*ToAnything_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root
echo "*********adding Diboson, DYJets, and WJets to make VJets root files in folder $1**********"
hadd $1VJets_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root  $1DiBoson_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root $1DYJetsToLL_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root $1WJetsToLNu_19584pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root

