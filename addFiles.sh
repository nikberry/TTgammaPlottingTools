#!/bin/bash

echo "*********adding DY root files in folder $1**********"
hadd $1DYJetsToLL_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root $1DYJetsToLL*_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root
echo "*********adding QCD root files in folder $1**********"
hadd $1QCD_All_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root $1QCD*_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root
echo "*********adding SingleTop root files in folder $1**********"
hadd $1SingleTop_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root $1T*_*-channel_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root
echo "*********adding DiBoson root files in folder $1**********"
hadd $1DiBoson_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root $1*ToAnything_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root
echo "*********adding Diboson, DYJets, and WJets to make VJets root files in folder $1**********"
hadd $1VJets_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root  $1DiBoson_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root $1DYJetsToLL_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root $1WJetsToLNu_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root
echo "*********adding data to make Combined root file in folder**********"
hadd $1Combined_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root $1Double*_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root $1MuEG_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root
echo "*********adding TTJets separate to make TTbar root file in folder**********"
hadd $1TTbar_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root $1TTJets_FullLept_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root $1TTJets_SemiLept_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root $1TTJets_Hadronic_19700pb_PFElectron_PFMuon_PF2PATJets_patType1CorrectedPFMet_Photon.root

