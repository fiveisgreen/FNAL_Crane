	// -*- C++ -*-
	//
	// Package:    SusyNtuplizer
	// Class:      SusyEventAnalyzer.cc
	// 
/*
 
 Description: an analyzer for susy::Event
 
 Implementation:
 
 */
	//
	// Original Author:  Dongwook Jang
	// $Id: SusyEventAnalyzer.cc,v 1.12 2012/05/03 19:58:51 dwjang Exp $
	//

#define SusyEventAnalyzer_cxx

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#include <utility>

#include "SusyEventAnalyzer.h"
#include "SusyEventPrinter.h"

#include "../jec/JetMETObjects/interface/JetCorrectorParameters.h"
#include "../jec/JetMETObjects/interface/FactorizedJetCorrector.h"
	//my additions
#include "TAxis.h"
#include "TMath.h"
#include <TH3.h>
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include <iostream>
	//user defiend
#include "utilities.h"
#include "cuts.h"
#include "params_arg.h"
#include "GetError.h"
#include "hggx_analysers.h"
#include "quicksave.C"

using namespace std;
using namespace params;


template<typename T> bool EtGreater(const T* p1, const T* p2) {
	return (p1->momentum.Et() > p2->momentum.Et());
}


void SusyEventAnalyzer::InitializePerEvent() {
	
}


bool SusyEventAnalyzer::isSameObject(TLorentzVector& p1, TLorentzVector& p2) {
	
	float dEta = p1.Eta() - p2.Eta();
	float dPhi = TVector2::Phi_mpi_pi(p1.Phi() - p2.Phi());
	float dR = std::sqrt(dEta*dEta + dPhi*dPhi);
	if(dR < 0.5) return true;
	return false;
}//dR05 cut


float SusyEventAnalyzer::d0correction(TVector3& beamSpot, susy::Track& track) const {
	
	float d0 = track.d0() - beamSpot.X()*std::sin(track.phi()) + beamSpot.Y()*std::cos(track.phi());
	return d0;
}


bool SusyEventAnalyzer::PassTrigger(TString path) {
	bool pass = false;
	for(susy::TriggerMap::iterator it = event->hltMap.begin(); it != event->hltMap.end(); it++) {
		if(it->first.Contains(path) && (int(it->second.second)) ) {
			pass = true;
			break;
		}
	}
	return pass;
}


bool SusyEventAnalyzer::PassTriggers() {
	bool pass = false;
	for(std::vector<TString>::iterator it = hltNames.begin(); it != hltNames.end(); it++) {
		if(PassTrigger(*it)) {
			pass = true;
			break;
		}
	}
	return pass;
}



void SusyEventAnalyzer::Loop() {
	cout<<"hello world"<<endl;
	
	//hard code kluge
	Long64_t start_event = 0; //7680000;
	int start_num = 0;
	const int n_files = 100;
	char *filename_prefix = "SuperSkim_12ABC_";
        int increment = 20000000;
	//end hard code kluge

	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntries();
	if(processNEvents <= 0 || processNEvents > nentries) processNEvents = nentries;
	
	std::cout << "total events in files  : " << nentries << std::endl;
	std::cout << "events to be processed : " << processNEvents << std::endl; 
	
		//Initialize Counters	
	if(printLevel > 0) std::cout << "Initialize event counters." << std::endl;
	const int NCNT = 8;
	int nCnt[NCNT];
	for(int i=0; i<NCNT; i++) nCnt[i] = 0;
	
		//cut flow
	//int NCNT = 9;
	//Long64_t nCnt[NCNT];
	//for(int i=0;i<NCNT;i++) nCnt[i]=0;
	TString  nCnt_lables[NCNT];
	nCnt_lables[0] = "no cuts";
	nCnt_lables[1] = "pass HLT";
	nCnt_lables[2] = "have 2 loose photons";
	nCnt_lables[3] = "have 2 photons over pt thresh";
	//nCnt_lables[4] = "are in some region";
	nCnt_lables[4] = "are in tag region";
	nCnt_lables[5] = "are in sb region";
	nCnt_lables[6] = "are in usb region";
	nCnt_lables[7] = "are in lsb region";
	
	int lsb_int = 0;//integrals of the upper and lower side band. 
	int usb_int = 0;
	
	
	
	int nFiltered = 0;
        int num = 0;
        int label = start_num;
	cout<<"make filter file pointer"<<endl;
       	TFile* filterFile[n_files];//(Form("%s%i.root",filename_prefix,start_num),"RECREATE");
	cout<<"make filter tree pointer"<<endl;
       	TTree * filterTree[n_files];// =fChain->CloneTree(0);
	cout<<"done with that nonsense"<<endl;
	
	
		// open hist file and define histograms
//	TFile* fout = new TFile("hist_"+ds+".root","RECREATE");//xxx
	TFile* fout = new TFile(plotsroot.c_str(),"RECREATE");//xxx
	fout->cd();
	
	TH1F* h_vtxZ = new TH1F("vtxZ","Z position of the primary vertex;Z (cm);Events",100,-50.0,50.0);
	TH1F* h_bsZ = new TH1F("bsZ","Z position of the beam spot;Z (cm);Events",100,-50.0,50.0);
	TH1F* h_met = new TH1F("met","missing transverse energy;#slash{E}_{T} (GeV);Events",200,0.0,1000.0);
	TH1F* h_sumEt = new TH1F("sumEt","Scalar sum of all calorimeter energy;#sigmaE_{T} (GeV);Events",200,0.0,2000.0);
		
		//my histograms
	TH1F* hdiPhoMass = new TH1F("hdiPhoMass","Di Photon Mass Sectrum",PhoMassNBins,PhoMassMin,PhoMassMax);
	
	TH1F * hMET[nPhoMassAndBkgDists];
	for (int i=0; i < nPhoMassAndBkgDists; i++) hMET[i] = new TH1F(RandomString(6),"",METNBins,METMin,METMax);
	NameHist(hMET[0],"hMET_lowSB","MET Lower Side Band");
	NameHist(hMET[1],"hMET_tag","MET in Higgs Tag Region");
	NameHist(hMET[2],"hMET_upperSB","MET Upper Side Band");
	NameHist(hMET[3],"hMET_bkg","MET Background to Higgs Tag Region");
	NameHist(hMET[4],"hMET_tag_subbkg","MET Background Subtracted Higgs Tag Region");
	NameHist(hMET[5],"hMET_lowSB_scaled","Scaled MET Lower Side Band");
	NameHist(hMET[6],"hMET_upperSB_scaled","Scaled MET Upper Side Band");
	
        TH1F * hST[nPhoMassAndBkgDists];
        for (int i=0; i < nPhoMassAndBkgDists; i++) hST[i] = new TH1F(RandomString(6),"",STNBins,STMin,STMax);
        NameHist(hST[0],"hST_lowSB","MET Lower Side Band");
        NameHist(hST[1],"hST_tag","MET in Higgs Tag Region");
        NameHist(hST[2],"hST_upperSB","MET Upper Side Band");
        NameHist(hST[3],"hST_bkg","MET Background to Higgs Tag Region");
        NameHist(hST[4],"hST_tag_subbkg","MET Background Subtracted Higgs Tag Region");
        NameHist(hST[5],"hST_lowSB_scaled","Scaled MET Lower Side Band");
        NameHist(hST[6],"hST_upperSB_scaled","Scaled MET Upper Side Band");
	
	
	
		// to check duplicated events
	std::map<int, std::set<int> > allEvents;
	
		// start event looping
	Long64_t nbytes = 0, nb = 0;
	Long64_t jentry=start_event-1;
        while(jentry<=start_event+n_files*increment){ //added
		 jentry++;//added 
		 Long64_t ientry = LoadTree(jentry);
      		if (ientry < 0) break;
      		nb = fChain->GetEntry(jentry);   nbytes += nb;
        	if(nb <= 0) break;//added, main exit
        	if(num>=n_files) break;

        if(jentry == start_event){
		if(enableFilter) {
                cout<<"opening new file, num = "<<num<<" label = "<<label<<endl;
                cout<<"new file name: "<<Form("%s%i.root",filename_prefix,label)<<endl;
                filterFile[num] = new TFile(Form("%s%i.root",filename_prefix,label),"RECREATE");
                cout<<"cd to file"<<endl;
                filterFile[num]->cd();
                cout<<"re clone tree"<<endl;
		}
                //filterTree[num] =fChain->CloneTree(0);
                filterTree[num] = (TTree*) fChain->GetTree()->CloneTree(0);
                filterTree[num]->SetAutoSave();
                cout<<"wow, that all worked"<<endl;

        }
        else if((jentry-start_event)%increment ==0){
                cout<<"ttree break, consider writing file"<<endl;
		if(enableFilter) {
                filterFile[num]->cd();
                filterTree[num]->Write();
                cout <<"closing file"<<endl;
                filterFile[num]->Close();
		}
                num++;
                label++;
		if(enableFilter) {
                cout<<"opening new file, num = "<<num<<" label = "<<label<<endl;
                filterFile[num]= new TFile(Form("%s%i.root",filename_prefix,label),"RECREATE");
                cout<<"cd to file"<<endl;
                filterFile[num]->cd();
		}
                cout<<"re clone tree"<<endl;
                //filterTree[num] =fChain->CloneTree(0);
                filterTree[num] = (TTree*) fChain->GetTree()->CloneTree(0);
                filterTree[num]->SetAutoSave();
                cout<<"wow, that all worked"<<endl;
        }

	//for (Long64_t jentry=0; jentry < processNEvents; jentry++) {
		
		//Long64_t ientry = LoadTree(jentry);
		//if (ientry < 0) break;
		//nb = fChain->GetEntry(jentry);   nbytes += nb;
		
		
		//if(printLevel > 0 || (printInterval > 0 && (jentry >= printInterval && jentry%printInterval == 0)) ) {
		if(jentry >= printInterval && jentry%printInterval == 0) {
			std::cout << int(jentry) << " events processed with run="
			<< event->runNumber << ", event=" << event->eventNumber << std::endl;
		}
		
		
		InitializePerEvent();
		
		bool duplicateEvent = ! (allEvents[event->runNumber].insert(event->eventNumber)).second;
		if(event->isRealData && duplicateEvent) continue;
		
		nCnt[0]++; // total number of events

		std::vector<susy::Photon*>   tight_photons;
		std::vector<susy::CaloJet*>  caloJets;
		std::vector<susy::PFJet*>    pfJets;
		
		TVector3* primVtx = 0;
		if(event->vertices.size() > 0) primVtx = &(event->vertices[0].position);
		
		if(primVtx) h_vtxZ->Fill(primVtx->Z());
		h_bsZ->Fill(event->beamSpot.Z());
		
		std::map<TString, std::vector<susy::Photon> >::iterator phoMap = event->photons.find("photons");
		
		if(phoMap != event->photons.end()) {
			
			for(std::vector<susy::Photon>::iterator it = phoMap->second.begin();
				it != phoMap->second.end(); it++) {
				
					// fiducial cuts. Look for only barrel now
				if(it->momentum.Et() < phoEtThresh) continue;

				bool tightCut = is_tight_pho( //is_tight_pho(	
							 it->momentum.Et(),
							 it->caloPosition.Eta(), //not sure about this one. 
							 it->trkSumPtHollowConeDR04,
							 it->ecalRecHitSumEtConeDR04,
							 it->hcalTowerSumEtConeDR04(),
							 it->hadronicOverEm,
							 it->sigmaIetaIeta,
							 it->nPixelSeeds,
							 event->rho25);
				
				if(tightCut) {
					tight_photons.push_back(&*it);
				}
			}// for all photon
		}// else
		
		if (tight_photons.size()<2 ) continue; 
		//nCnt[1]++;//have 2 photons
		nCnt[2]++;

			// sort photons by Et
		std::sort(tight_photons.begin(),tight_photons.end(),EtGreater<susy::Photon>);
		if(tight_photons[0]->momentum.Et()<36. || tight_photons[1]->momentum.Et() < 22.) continue;
		nCnt[3]++;
		
		TLorentzVector Pho[tight_photons.size()];
		for (int i=0; i<2; i++) {
			Pho[i].SetPtEtaPhiM(tight_photons[i]->momentum.Et(),tight_photons[i]->momentum.Eta(),tight_photons[i]->momentum.Phi(),0.f);
		}

		TLorentzVector gg = Pho[0]+Pho[1];
		float mgg = gg.M();
		hdiPhoMass->Fill(mgg);
		
		if(printLevel > 0) std::cout << "Find caloJets in the event." << std::endl;
		
		std::map<TString,susy::CaloJetCollection>::iterator caloJets_it = event->caloJets.find("ak5");
		
		if(caloJets_it != event->caloJets.end()){
			
			susy::CaloJetCollection& jetColl = caloJets_it->second;
			
			for(std::vector<susy::CaloJet>::iterator it = jetColl.begin();
				it != jetColl.end(); it++) {
				
				std::map<TString,Float_t>::iterator s_it = it->jecScaleFactors.find("L2L3");
				if (s_it == it->jecScaleFactors.end()) {
					std::cout << "JEC is not available for this jet!!!" << std::endl;
					continue;
				}
				float scale = s_it->second;
				
				if(printLevel > 2) std::cout << "CaloJet stored (" << scale << ")" << std::endl;
				
				TLorentzVector corrP4 = scale * it->momentum;
				
				if(std::abs(corrP4.Eta()) > 3.0) continue;
				
				bool same = false;
				
				for(std::vector<susy::Photon*>::iterator m_it = tight_photons.begin();
					m_it != tight_photons.end(); m_it++){
					if(isSameObject(corrP4,(*m_it)->momentum)){
						same = true;
						break;
					}
				}
				if(same) continue;
				
				caloJets.push_back(&*it);
				
			}// for jet
		}// else
		
		std::sort(caloJets.begin(),caloJets.end(),EtGreater<susy::CaloJet>);
		
		
		if(printLevel > 0) std::cout << "Find pfJets in the event." << std::endl;
		
		std::map<TString,susy::PFJetCollection>::iterator pfJets_it = event->pfJets.find("ak5");
		if(pfJets_it == event->pfJets.end()){
			if(event->pfJets.size() > 0) std::cout << "JetCollection is not available!!!" << std::endl;
		}
		else {
			
			susy::PFJetCollection& jetColl = pfJets_it->second;
			
			for(std::vector<susy::PFJet>::iterator it = jetColl.begin();
				it != jetColl.end(); it++) {
				
				std::map<TString,Float_t>::iterator s_it = it->jecScaleFactors.find("L2L3");
				if (s_it == it->jecScaleFactors.end()) {
					std::cout << "JEC is not available for this jet!!!" << std::endl;
					continue;
				}
				float scale = s_it->second;
				
				if(printLevel > 2) std::cout << "PFJet stored (" << scale << ")" << std::endl;
				
				TLorentzVector corrP4 = scale * it->momentum;
				
				if(std::abs(corrP4.Eta()) > 3.0) continue;
				
				bool same = false;
				
				for(std::vector<susy::Photon*>::iterator m_it = tight_photons.begin();
					m_it != tight_photons.end(); m_it++){
					if(isSameObject(corrP4,(*m_it)->momentum)){
						same = true;
						break;
					}
				}
				if(same) continue;
				
				pfJets.push_back(&*it);
				
			}// for jet
		}// else
		
		std::sort(pfJets.begin(),pfJets.end(),EtGreater<susy::PFJet>);
		
		
		if(printLevel > 0) std::cout << "Select which met will be used in the event." << std::endl;
		
		std::map<TString, susy::MET>::iterator met_it = event->metMap.find("pfMet");
		if(met_it == event->metMap.end()) {
			std::cout << "MET map is not available!!!" << std::endl;
			continue;
		}
		susy::MET* met = &(met_it->second);
		
			//Select tag and side band regions
		bool passmass = false;
		if (mgg > lsb_lb && mgg < lsb_ub) { // lower side band 
			passmass = true;
			nCnt[5]++;//are in sb region
			nCnt[7]++;//are in lsb region
			hMET[0]->Fill(met->met());
			hST[0]->Fill(met->sumEt);
			lsb_int++;
		}
		else if(mgg > tag_lb && mgg < tag_ub){ //tag region
			passmass = true;
			nCnt[4]++;//are in tag region
			hMET[1]->Fill(met->met());
			hST[1]->Fill(met->sumEt);
			//cout<<"hit a tag. Met: "<<met->met()<<" St: "<<met->sumEt<<endl;
		}
		else if(mgg > usb_lb && mgg < usb_ub){ // upper side band
			passmass = true;
			nCnt[5]++;//are in sb region
			nCnt[6]++;//are in usb region
			hMET[2]->Fill(met->met());
			hST[2]->Fill(met->sumEt);
			usb_int++;
		}
		if (!passmass) continue;
		
		
		
		/*if(printLevel > 0) {
			std::cout << "------------------------------------------" << std::endl;
			std::cout << "              event summary" << std::endl;
			std::cout << "------------------------------------------" << std::endl;
//			std::cout << "loose_photons     : " << loose_photons.size() << std::endl;
			std::cout << "tight_photons     : " << tight_photons.size() << std::endl;
//			std::cout << "ele_photons       : " << ele_photons.size() << std::endl;
//			std::cout << "fake_photons      : " << fake_photons.size() << std::endl;
			std::cout << "caloJets          : " << caloJets.size() << std::endl;
			std::cout << "pfJets            : " << pfJets.size() << std::endl;
			std::cout << "------------------------------------------" << std::endl;
			std::cout << "met               : " << met->met() << std::endl;
			
			std::cout << "Apply event level cuts from now on..." << std::endl;
		} //print event summary
	        */	
			// filter conditions
		if(enableFilter) {
				nFiltered++;
				filterTree[num]->Fill();
		}// if(enableFilter)
		
		h_met->Fill(met->met());
		h_sumEt->Fill(met->sumEt);//st!!
		
	} // for every jentry
	
	
		// end of event loop and print summary
	/*std::cout << " ----------------- Job Summary ----------------- " << std::endl;
	std::cout << " Total events            : " << nCnt[0] << std::endl;
	//std::cout << " HLT passed              : " << nCnt[1] << " (" << nCnt[1]/float(nCnt[0]) << ") wrt total events" << std::endl;
	std::cout << " loose_photons > 0       : " << nCnt[2] << " (" << nCnt[2]/float(nCnt[0]) << ") wrt HLT" << std::endl;
	//std::cout << " gg events               : " << nCnt[3] << " (" << nCnt[3]/float(nCnt[1]) << ")" << std::endl;
	std::cout << " passed pt thresh: " << nCnt[3] << " (" << nCnt[3]/float(nCnt[0]) << ")" << std::endl;
//	std::cout << " ge events               : " << nCnt[4] << " (" << nCnt[4]/float(nCnt[1]) << ")" << std::endl;
//	std::cout << " ee events               : " << nCnt[5] << " (" << nCnt[5]/float(nCnt[1]) << ")" << std::endl;
//	std::cout << " gf events               : " << nCnt[6] << " (" << nCnt[6]/float(nCnt[1]) << ")" << std::endl;
//	std::cout << " ff events               : " << nCnt[7] << " (" << nCnt[7]/float(nCnt[1]) << ")" << std::endl;
//	std::cout << " met > 50 GeV            : " << nCnt[8] << " (" << nCnt[8]/float(nCnt[1]) << ")" << std::endl;
*/
	
	if(enableFilter) {
		std::cout << " --------------- Filtered events --------------- " << std::endl;
		std::cout << " filtered events         : " << nFiltered << " (" << nFiltered/float(nCnt[0]) << ")" << std::endl;
	}
	std::cout << " ----------------------------------------------- " << std::endl;
	
	
		//quick save the side band integrals. 
	float sideband_integrals[2] = {(float)lsb_int,(float)usb_int};
	TTree* t_sideband_integrals = Save(sideband_integrals,2,"sideband_integrals");
	fout->cd();
	t_sideband_integrals->Write();
	
		//support 
	find_bkg(hMET);	
	find_bkg(hST);	
	
	hdiPhoMass->Write();
//	gDirectory->Append(g);
//	g->Write();
//	gDirectory->Write();
//	mgg_fit_curve->Write();
	for (int i=0; i < nPhoMassAndBkgDists; i++) hMET[i]->Write();
	for (int i=0; i < nPhoMassAndBkgDists; i++) hST[i]->Write();
	

	for(int i=0; i<NCNT;i++){
		cout << nCnt[i] << " " << nCnt_lables[i] << endl;
	}
	
		
		// close the output file
	fout->cd();
	fout->Write();
	fout->Close();

	if(enableFilter) {
		printf("last time: cd\n");	
		filterFile[num]->cd();
		printf("write, %i\n",num);	
		filterTree[num]->Write();
		cout <<"closing file"<<endl;
		filterFile[num]->Close();
	}
	
}//end Loop





















