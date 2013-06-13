// -*- C++ -*-
//
// Package:    SusyNtuplizer
// Class:      SusyAna_MC_BTagEff_test.cc
//
/*

Description: an analyzer for susy::Event

Implementation:

 */
//
// Original Author:  Dongwook Jang
// $Id: SusyAna_MC_BTagEff_test.cc,v 1.12 2012/05/03 19:58:51 dwjang Exp $
//

#define SusyAna_MC_BTagEff_test_cxx

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#include <utility>

#include "SusyAna_MC_BTagEff_test.h"
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
#include <fstream>
//user defiend
#include "utilities.h"
#include "cuts.h"
#include "params_arg.h"
#include "GetError.h"
#include "hggx_analysers.h"
#include "quicksave.C"
#include "CMSStyle.C"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "MCpoint2.C"

using namespace std;
using namespace params;


template<typename T> bool EtGreater(const T* p1, const T* p2) {
	return (p1->momentum.Et() > p2->momentum.Et());
}


void SusyAna_MC_BTagEff_test::InitializePerEvent() {

}


bool SusyAna_MC_BTagEff_test::isSameObject(TLorentzVector& p1, TLorentzVector& p2) {

	float dEta = p1.Eta() - p2.Eta();
	float dPhi = TVector2::Phi_mpi_pi(p1.Phi() - p2.Phi());
	float dR = std::sqrt(dEta*dEta + dPhi*dPhi);
	if(dR < 0.5) return true;
	return false;
}//dR05 cut


float SusyAna_MC_BTagEff_test::d0correction(TVector3& beamSpot, susy::Track& track) const {

	float d0 = track.d0() - beamSpot.X()*std::sin(track.phi()) + beamSpot.Y()*std::cos(track.phi());
	return d0;
}

//float SusyAna_MC_BTagEff_test::d0correction_(TVector3& beamSpot, susy::Track& track){
//	float d0 = track.d0() - beamSpot.X()*std::sin(track.phi()) + beamSpot.Y()*std::cos(track.phi());
//	return d0;
//}



bool SusyAna_MC_BTagEff_test::PassTrigger(TString path) {
	//Does not have to be an exact name. the trigger name must contain "path". So you can ignore the trigger version.
	bool pass = false;
	for(susy::TriggerMap::iterator it = event->hltMap.begin(); it != event->hltMap.end(); it++) {
		if(it->first.Contains(path) && (int(it->second.second)) ) {
			pass = true;
			break;
		}
	}
	return pass;
}


bool SusyAna_MC_BTagEff_test::isfarFromPhotons(TLorentzVector& lep, std::vector<susy::Photon*> & photons){
	bool isFar = true;
	for(std::vector<susy::Photon*>::iterator it = photons.begin(); it != photons.end(); it++) {
		TLorentzVector ltmp = (*it)->momentum;
		isFar &= ! SusyAna_MC_BTagEff_test::isSameObject(lep,ltmp);
	}
	return isFar;
}


bool SusyAna_MC_BTagEff_test::PassTriggers() {
	bool pass = false;
	for(std::vector<TString>::iterator it = hltNames.begin(); it != hltNames.end(); it++) {
		if(PassTrigger(*it)) {
			pass = true;
			break;
		}
	}
	return pass;
}

typedef std::map<string, int> nameint;

void addCounter(nameint & C, vector<string> & V, string label){
	C[label]=0;
	V.push_back(label);
}

void remove_duplicate_photons(std::vector<susy::Photon*> & photons,bool keep_hardest_matched_photon=true){
	/*
	   This takes a pt-sorted vector of Photon*. It looks through all pairs of photons, for dR matches (dR<0.6 or dPhi < 0.05)
	   If it finds a match and keep_hardest_matched_photon, it keeps the hardest one and deletes the others from the vector. 
	   If it finds a match and !keep_hardest_matched_photon, it deletes all photons involved int the match. David Morse and I do the former.
	 */

	if (photons.size()<2) return;
	std::vector<susy::Photon*>::iterator i_p1 = photons.begin(); int I_p1 = 0;
	int size = photons.size();
	while(I_p1+1 < size){
		bool match_found = false;
		TLorentzVector p1 = (*i_p1)->momentum;
		std::vector<susy::Photon*>::iterator i_p2 = i_p1+1; int I_p2 = I_p1+1;
		while(I_p2 < size){ //increments to the terminator, then does not terminate.
			TLorentzVector p2 = (*i_p2)->momentum;
			if (dR(p1,p2)<0.6 || dPhi(p1,p2) < 0.05 ) {
				std::vector<susy::Photon*>::iterator temp = i_p2+1;
				i_p2 = photons.erase(i_p2);//this is supposed to return the next element but does not.
				i_p2 = temp;
				size--;
				match_found = true;
				if(I_p2 == (int)photons.size()-1) break;
			}
			else{ i_p2++; I_p2++;}
		}//end while2
		if (match_found && !keep_hardest_matched_photon) {
			i_p1 = photons.erase(i_p1);
		}
		else {i_p1++; I_p1++;}
		}//end while
	}//end remove_duplicate_photons

	void PrintPhotonTriggers(susy::Event* event){
		for(susy::TriggerMap::iterator it = event->hltMap.begin(); it != event->hltMap.end(); it++) {
			if (it->first.Contains("Photon")) {
				std::cout << "\t" << it->first << "(prescale=" << it->second.first << ", fire=" << int(it->second.second) << ")" << std::endl;
			}
		}
	}

	void SusyAna_MC_BTagEff_test::Loop() {

		cout<<"hello world"<<endl;
		printLevel = 0;
		if (fChain == 0) return;
		//probe p = probe();
		//p.p("probe");

		Long64_t nentries = fChain->GetEntries();
		std::cout << "k " << nentries << std::endl;
		if(processNEvents <= 0 || processNEvents > nentries) processNEvents = nentries;

		std::cout << "total events in files  : " << nentries << std::endl;
		std::cout << "events to be processed : " << processNEvents << std::endl;

		//Initialize Counters
		if(printLevel > 0) std::cout << "Initialize event counters." << std::endl;
		vector <string> Counter_order;
		nameint Counters;
		addCounter(Counters,Counter_order,"no cuts");
		addCounter(Counters,Counter_order,"pass Json");
		addCounter(Counters,Counter_order,"pass duplicate check");
		addCounter(Counters,Counter_order,"pass HLT");
		addCounter(Counters,Counter_order,"pass MET Filter");
		addCounter(Counters,Counter_order,"pass two loose photons");
		addCounter(Counters,Counter_order,"pass 2 loose pho over thresh");
		addCounter(Counters,Counter_order,"pass phoM 100 cuts");

		addCounter(Counters,Counter_order,"have 2 tight photons");
		//addCounter(Counters,Counter_order,"have 2 tight photons passing dR cuts");
		addCounter(Counters,Counter_order,"pass a primary vertex reqirement");
		addCounter(Counters,Counter_order,"has met map");
		addCounter(Counters,Counter_order,"number filtered");
		//no extra cuts.

		//	int nFiltered = 0;
		//	TTree* filterTree = 0;
		//	cout << "enableFilter is set to "<<enableFilter<<endl;
		//	if (enableFilter){
		//		enableFilter = false;
		//		cout << "setting it to false"<<endl;
		//	}

		//	if(enableFilter) {
		//		cout << "Making Filter File"<<endl;
		
		MCpoint2* thisMCpoint = setupMCpoint(which_MC_to_use2);
		TFile* b_tag_eff_file = new TFile(thisMCpoint->btageff_file.c_str(),"RECREATE");
		//TFile* b_tag_eff_file = new TFile("foobar.root","RECREATE");

		int nbins = 16;
		float ptmin[] = {20, 30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 600, 800};
		//float ptmax[] = {30, 40, 50, 60, 70, 80,100, 120, 160, 210, 260, 320, 400, 500, 600, 800};
		TH1F* bjetEffDen = new TH1F("bjetEffDen","denominator",nbins,ptmin);
		TH1F* bjetEff_CSVLNum = new TH1F("bjetEff_CSVLNum","CSVL Numerator;Pt",nbins,ptmin);
		TH1F* bjetEff_CSVMNum = new TH1F("bjetEff_CSVMNum","CSVM Numerator;Pt",nbins,ptmin);
		TH1F* bjetEff_CSVTNum = new TH1F("bjetEff_CSVTNum","CSVT Numerator;Pt",nbins,ptmin);

		TH1F* nbjets_dist = new TH1F("nbjets","Number of B-jets;n b-jets",8,0,8);

		TH1F* bjetEff_CSVL = new TH1F("bjetEff_CSVL","CSVL Efficiency;Pt;Efficiency",nbins,ptmin);
		TH1F* bjetEff_CSVM = new TH1F("bjetEff_CSVM","CSVM Efficiency;Pt;Efficiency",nbins,ptmin);
		TH1F* bjetEff_CSVT = new TH1F("bjetEff_CSVT","CSVT Efficiency;Pt;Efficiency",nbins,ptmin);

		TH1F* bMistagDen = new TH1F("bMistagDen","denominator",nbins,ptmin);
		TH1F* bMistag_CSVLNum = new TH1F("bMistag_CSVLNum","CSVL Numerator;Pt",nbins,ptmin);
		TH1F* bMistag_CSVMNum = new TH1F("bMistag_CSVMNum","CSVM Numerator;Pt",nbins,ptmin);
		TH1F* bMistag_CSVTNum = new TH1F("bMistag_CSVTNum","CSVT Numerator;Pt",nbins,ptmin);

		TH1F* nMistagsL_dist = new TH1F("nMistagsL","Number of CSVL mistags per event;n jets",8,0,8);
		TH1F* nMistagsM_dist = new TH1F("nMistagsM","Number of CSVM mistags per event;n jets",8,0,8);
		TH1F* nMistagsT_dist = new TH1F("nMistagsT","Number of CSVT mistags per event;n jets",8,0,8);

		TH1F* bMistag_CSVL = new TH1F("bMistag_CSVL","CSVL Mistag Rate;Pt;Efficiency",nbins,ptmin);
		TH1F* bMistag_CSVM = new TH1F("bMistag_CSVM ","CSVM Mistag Rate;Pt;Efficiency",nbins,ptmin);
		TH1F* bMistag_CSVT = new TH1F("bMistag_CSVT ","CSVT Mistag Rate;Pt;Efficiency",nbins,ptmin);

		ofstream eventlist;
		eventlist.open ("beff_eventlist.txt");//everything passing the ntuplizer. 
		//ofstream eventlist2;
		//eventlist2.open ("ntuplized_passingTrip_eventlist.txt");//passing the ntuplizer and also passing the cuts in this context. 


		//plots of things I cut on.
		cout<<"start on trigger"<<endl;

		const int Nnonr9Triggers = 9;
		const int Nr9Triggers = 4;
		//const int NT = Nnonr9Triggers+Nr9Triggers;
		//bool passHLTs[NT];
		/*TString dmason_triggers[4] = {  //not using these.
		  "HLT_Photon36_CaloId10_Iso50_Photon22_CaloId10_Iso50",
		  "HLT_Photon36_CaloId10_Iso50_Photon22_R9Id85",
		  "HLT_Photon36_R9Id85_Photon22_CaloId10_Iso50", 
		  "HLT_Photon36_R9Id85_Photon22_R9Id85"};*/

		TString R9triggers[Nr9Triggers] = {
			"HLT_Photon36_CaloId10_Iso50_Photon22_CaloId10_Iso50", //dmason
			"HLT_Photon36_CaloIdL_Photon22_CaloIdL",
			"HLT_Photon32_CaloIdL_Photon26_CaloIdL",
			"HLT_Photon26_CaloId10_Iso50_Photon18_CaloId10_Iso50_Mass60"};
		TString nonR9triggers[Nnonr9Triggers] = {
			"HLT_Photon36_R9Id85_Photon22_R9Id85", //dmason
			"HLT_Photon36_R9Id85_Photon22_CaloId10_Iso50", //dmason
			"HLT_Photon36_CaloId10_Iso50_Photon22_R9Id85", //dmason
			"HLT_Photon26_R9Id85_OR_CaloId10_Iso50_Photon18_R9Id85_OR_CaloId10_Iso50_Mass60",
			"HLT_Photon26_R9Id85_OR_CaloId10_Iso50_Photon18_R9Id85_OR_CaloId10_Iso50_Mass70",
			"HLT_Photon26_R9Id85_Photon18_R9Id85_Mass60",
			"HLT_Photon26_R9Id85_Photon18_CaloId10_Iso50_Mass60",
			"HLT_Photon26_CaloId10_Iso50_Photon18_R9Id85_Mass60",
			"HLT_Photon36_R9Id85_OR_CaloId10_Iso50_Photon22_R9Id85_OR_CaloId10_Iso50"};

		if(!useTrigger&&event->isRealData){
			useTrigger = true;
			cout<< endl<<"By some black magic, useTrigger is false, setting it to true"<<endl; 
		}

		if (!useTrigger) cout << endl << endl << "WARNING!! NOT USING THE TRIGGER!!!"<<endl<<endl<<endl;
		else cout << endl << "TRIGGER ON"<<endl<<endl;

		if (!useJSON) cout << endl << endl << "WARNING!! NOT USING THE JSON FILE!!!"<<endl<<endl<<endl;
		else cout << endl << "USING JSON"<<endl<<endl;
		// to check duplicated events
		std::map<int, std::set<int> > allEvents;

		// start event looping
		Long64_t nbytes = 0, nb = 0;
		//for (Long64_t jentry=0; jentry < processNEvents; jentry++) {
		for (Long64_t jentry=0; jentry < 500; jentry++) { //master loop
			if(jentry > 10001) break;//limit this to the first 10k entries.

			if(printLevel > 0) std::cout << "Get the tree contents." << std::endl;
			Long64_t ientry = LoadTree(jentry);
			if (ientry < 0) break;
			Counters["no cuts"]++;
			nb = fChain->GetEntry(jentry);   nbytes += nb;


			if(printLevel > -1 && (printInterval > 0 && (jentry >= printInterval && jentry%printInterval == 0)) ) {
				std::cout << int(jentry) << " events processed with run="
					<< event->runNumber << ", event=" << event->eventNumber << std::endl;

				//every 100 print intervals, print the trigger list. It should always on the first event. 
				//if (jentry%(printInterval*100) == 0)  PrintPhotonTriggers(event); 

			}//end if millionth event. 
			if(printLevel > 0) std::cout << "Initialize any global variables to be reset per event." << std::endl;

			InitializePerEvent();

			if(event->runNumber<0){
				if(printLevel > 0) std::cout << "Warning: run number less than zero" << std::endl;
				continue;
			}		

			if(event->eventNumber == ((unsigned int)probeevent)) cout<<"probe is at point A"<<endl;

			if(printLevel > 0) std::cout << "Apply good run list." << std::endl;
			if(event->isRealData && useJSON && !isInJson(event->runNumber,event->luminosityBlockNumber)) continue;
			if(event->eventNumber == ((unsigned int)probeevent)) cout<<"probe passes JSON"<<endl;
			Counters["pass Json"]++; // total number of events that pass Json

			//Print(*event);  // uncomment this to print all ntuple variables


			if(printLevel > 1) cout << "Check duplicated events for data only." << endl;

			if(event->isRealData){
				bool duplicateEvent = ! (allEvents[event->runNumber].insert(event->eventNumber)).second;
				if(duplicateEvent){
					cout<<"Duplicate Event! Run "<<event->runNumber<<" Event "<<event->eventNumber<<endl;
					continue;
				}
			}
			if(event->eventNumber == ((unsigned int)probeevent)) cout<<"probe passes Duplicate Filter"<<endl;
			Counters["pass duplicate check"]++;

			//		if(printLevel > 0) Print(*event); // uncomment this to print all ntuple variables

			if(printLevel > 0) std::cout << "Apply trigger selection in the event." << std::endl;		

			bool pass_non_r9id_trigger = false;
			bool pass_r9id_trigger = false;
			bool passHLT = false;

			for (int i=0; i<Nnonr9Triggers; i++) {
				pass_non_r9id_trigger |= PassTrigger(nonR9triggers[i]);
			}
			for (int i=0; i<Nr9Triggers; i++) {
				pass_r9id_trigger |= PassTrigger(R9triggers[i]);
			}
			passHLT = pass_r9id_trigger || pass_non_r9id_trigger;

			if(event->isRealData && useTrigger && !passHLT) continue;
			if(event->eventNumber == ((unsigned int)probeevent)) cout<<"probe passes HLT"<<endl;
			Counters["pass HLT"]++;

			//Print(event->hltMap);cout << endl << endl;

			if(useMETFilter_data && event->isRealData && !event->passMetFilters()) continue; //don't use the met filter for MC, nothing passes.
			if(event->eventNumber == ((unsigned int)probeevent)) cout<<"probe passes MetFilter"<<endl;
			Counters["pass MET Filter"]++;


			if(printLevel > 0) std::cout << "Setup object vectors." << std::endl;

			//float myST = 0.0;
			//float myPhotonST = 0.0;
			float myLeptonST = 0.0;

			std::vector<susy::Photon*>   loose_photons; // loose objects have all standard cuts except for isolation
			//std::vector<susy::Photon*>   tight_susy11_photons; // tight objects hava isolation cuts applied on top of loose objects
			//std::vector<susy::Photon*>   tight_susy11Star_photons; // tight objects hava isolation cuts applied on top of loose objects
			//std::vector<susy::Photon*>   medium_susy12_photons; // tight objects hava isolation cuts applied on top of loose objects
			std::vector<susy::Photon*>   loose_susy12_photons; // tight objects hava isolation cuts applied on top of loose objects
			//std::vector<susy::Photon*>   tight_VG11_photons;
			//std::vector<susy::Photon*>*  p_photonVector;
			//std::vector<susy::Photon*>* p_photonVector = &tight_susy11_photons;
			//use as (*p_photonVector)

			std::vector<susy::PFJet*>    pfJets;
			std::vector<susy::PFJet*>    pfBJets;
		std::vector<susy::PFJet*>    pfBJetsLoose;
		std::vector<susy::PFJet*>    pfBJetsMedium;
		std::vector<susy::PFJet*>    pfBJetsTight;

			std::vector<susy::Vertex*>   good_vtx;
			std::vector<susy::Muon*>     ra3_muons;
			std::vector<susy::Muon*>     Muons;//DM's collection
			std::vector<susy::PFJet*>    ra3_pfjets;
			std::vector<susy::Electron*>   pfEles;

			/////////////////////////////////////////////////////////////////
			//////////////////////////// PHOTONS ////////////////////////////
			/////////////////////////////////////////////////////////////////

			if(printLevel > 0) std::cout << "Find loose and tight photons in the event." << std::endl;
			std::map<TString, std::vector<susy::Photon> >::iterator phoMap = event->photons.find("photons");
			if(phoMap != event->photons.end()) {
				int j = 0;
				for(std::vector<susy::Photon>::iterator it = phoMap->second.begin();
						it != phoMap->second.end(); it++) {
					/*bool looseCut = is_vloose_pho(
							it->momentum.Et(),
							it->caloPosition.Eta(),
							it->trkSumPtHollowConeDR03,
							it->ecalRecHitSumEtConeDR03,
							it->hcalTowerSumEtConeDR03(),
							it->hadronicOverEm,
							it->sigmaIetaIeta,
							it->sigmaIphiIphi,
							it->r9,
							it->nPixelSeeds,
							event->rho25);

					bool is_tightSusy_photons = is_tight_combIso_BFrancis(
							it->momentum.Et(),
							it->caloPosition.Eta(),
							it->trkSumPtHollowConeDR03,
							it->ecalRecHitSumEtConeDR03,
							it->hcalTowerSumEtConeDR03(),
							it->hadronicOverEm,
							it->sigmaIetaIeta,
							it->sigmaIphiIphi,
							it->r9,
							it->nPixelSeeds,
							event->rho25);
					bool is_tightStar_photons = is_tight_susyStar(
							it->momentum.Et(),
							it->caloPosition.Eta(),
							it->trkSumPtHollowConeDR03,
							it->ecalRecHitSumEtConeDR03,
							it->hcalTowerSumEtConeDR03(),
							it->hadronicOverEm,
							it->sigmaIetaIeta,
							it->sigmaIphiIphi,
							it->r9,
							it->nPixelSeeds,
							event->rho25);

					bool ismedium2012Cut = is_medium_2012(
							it->momentum.Et(),
							it->caloPosition.Eta(),
							it->chargedHadronIso,
							it->neutralHadronIso,
							it->photonIso,
							it->hadTowOverEm,  //single tower, same cut though
							it->sigmaIetaIeta,
							it->sigmaIphiIphi,
							it->passelectronveto, //replaces pixel seed veto
							event->rho25);*/

					bool isloose2012Cut = is_loose_2012(
							it->momentum.Et(),
							it->caloPosition.Eta(),
							it->chargedHadronIso,
							it->neutralHadronIso,
							it->photonIso,
							it->hadTowOverEm,  //single tower, same cut though
							it->sigmaIetaIeta,
							it->sigmaIphiIphi,
							it->passelectronveto, //replaces pixel seed veto
							event->rho25);
			//it's failing the ele veto 100% of the time. 
					//p.p(Form("I'm in the photon for loop and the bool is %i",isloose2012Cut));//ok, there are frequently two photons. 
		//printf("Et %f Eta %f ChadIso %f nHadIso %f phoIso %f\n",it->momentum.Et(),it->caloPosition.Eta(),it->chargedHadronIso,it->neutralHadronIso,it->photonIso);
		//printf("he %f sieie %f sipip %f pass eleveto %i rho %f\n",it->hadTowOverEm,it->sigmaIetaIeta,it->sigmaIphiIphi,it->passelectronveto,event->rho25);

					//if(is_tightSusy_photons) { tight_susy11_photons.push_back(&*it); }
					//if(is_tightStar_photons){ tight_susy11Star_photons.push_back(&*it); }
					//if(is_tightEg11_photons) { tightEg11_photons.push_back(&*it); }
					//if(ismedium2012Cut){ medium_susy12_photons.push_back(&*it);      }
					//if(looseCut) { loose_photons.push_back(&*it); }
					if(isloose2012Cut){ loose_susy12_photons.push_back(&*it); }
					j++;
				}// for all photon
			} //end if pho map
			else {
				continue; //else there are no photons
			}
			std::sort(loose_susy12_photons.begin(),loose_susy12_photons.end(),EtGreater<susy::Photon>);
			remove_duplicate_photons(loose_susy12_photons);

			if (((int)loose_susy12_photons.size())<2){ continue; }

			Counters["pass two loose photons"]++;
			
			if (loose_susy12_photons[0]->momentum.Et() < phoEtThresh0 || loose_susy12_photons[1]->momentum.Et() < phoEtThresh1) {
				continue;
			}
			Counters["pass 2 loose pho over thresh"]++;


			std::sort(loose_susy12_photons.begin(),loose_susy12_photons.end(),EtGreater<susy::Photon>); 
			remove_duplicate_photons(loose_susy12_photons);


			/////////////////////////////////////////////////////////////////
			//////////////////////// FIND THE PRIMARY VERTEX ////////////////
			/////////////////////////////////////////////////////////////////

			if(printLevel > 0) std::cout << "Find primary vertex in the event." << std::endl;
			//TVector3* primVtx = 0;
			//if(event->vertices.size() > 0) primVtx = &(event->vertices[0].position);

			for(std::vector<susy::Vertex>::iterator it = event->vertices.begin(); it != event->vertices.end(); it++) {
				if(ok_vtx(it)) good_vtx.push_back(&*it);
			}
			int nPVertex = good_vtx.size();
			if(nPVertex<1){
				if(printLevel > 1) cout<<"No Good Vertex!!!!  Run: "<<event->runNumber<<"  Event: "<<event->eventNumber<<endl;
				continue;
			}		
			if(event->eventNumber == ((unsigned int)probeevent)) cout<<"pass Vertex"<<endl;
			Counters["pass a primary vertex reqirement"]++;


			/////////////////////////////////////////////////////////////////
			//////////////////////// FIND MUONS  ////////////////////////////
			/////////////////////////////////////////////////////////////////

			if(printLevel > 1) cout << "Find Muons in the event." << endl;
			std::map<TString, std::vector<susy::Muon> >::iterator muMap = event->muons.find("muons");
			if(muMap != event->muons.end()) {
				for(std::vector<susy::Muon>::iterator it_Mu= muMap->second.begin(); it_Mu!= muMap->second.end(); it_Mu++) {


					//////////////////////

					/*if(printLevel > 1) cout << "Find Muons in the event." << endl;
					  for(std::vector<susy::Muon>::iterator it_Mu = event->muons.begin(); it_Mu != event->muons.end(); it_Mu++) {
					  std::map<TString,UChar_t>::iterator idPair = it_Mu->idPairs.find("muidGlobalMuonPromptTight");
					  if(idPair == it_Mu->idPairs.end()) continue;
					  if(int(idPair->second) == 0) continue;
					 */	

					if(printLevel > 1) cout<<"looping over muon collection"<<endl;

					susy::Track& innerTrack = event->tracks[it_Mu->trackIndex];
					if(ok_muon_DMoris(it_Mu,innerTrack) &&
							isfarFromPhotons(it_Mu->momentum, loose_susy12_photons)
					  ){
						Muons.push_back(&*it_Mu);
						myLeptonST += (it_Mu)->momentum.Et();
					}	

				}}//end it_Mu muon loop
				//sort Muons by Pt
				std::sort(Muons.begin(), Muons.end(), EtGreater<susy::Muon>);
				if(printLevel>1)cout<<"Muons size= "<<Muons.size()<<endl;


				//Find Muons Yueh-Feng's way
				/*
				   for(std::vector<susy::Muon>::iterator it = event->muons.begin();
				   it != event->muons.end(); it++) {
				   if(ok_muon(it)) ra3_muons.push_back(&*it);
				   }//muon
				   std::sort(ra3_muons.begin(),ra3_muons.end(),EtGreater<susy::Muon>);
				 */

				/////////////////////////////////////////////////////////////////
				//////////////////////// FIND pfElectrons  //////////////////////
				/////////////////////////////////////////////////////////////////
				std::map<TString, std::vector<susy::Electron> >::iterator eleMap = event->electrons.find("gsfElectrons");
				if(eleMap != event->electrons.end()) {
					//loop over electron collection
					for(std::vector<susy::Electron>::iterator it_Ele = eleMap->second.begin(); it_Ele != eleMap->second.end(); it_Ele++) {
						if(printLevel > 1) cout<<"looping over electron collection"<<endl;

						//float relIso=(it_Ele->chargedHadronIso + it_Ele->neutralHadronIso + it_Ele->photonIso)/it_Ele->momentum.Pt();

						if(ok_ele(it_Ele) &&
								isfarFromPhotons(it_Ele->momentum, loose_susy12_photons)){
							pfEles.push_back(&*it_Ele);
							myLeptonST += (it_Ele)->momentum.Et();
						}

					}//end it_Ele electron loop
					std::sort(pfEles.begin(), pfEles.end(), EtGreater<susy::Electron>); //sort pfEles by Pt
					if(printLevel>1)cout<<"pfEles size= "<<pfEles.size()<<endl;



				}//end eleMap

				//import
				float HT_all = 0;
				//float MHT_all = 0;
				float MHT_x_all =0;
				float MHT_y_all =0;

				if(printLevel > 0) std::cout << "Find pfJets in the event." << std::endl;

				std::map<TString,susy::PFJetCollection>::iterator pfJets_it = event->pfJets.find("ak5");
				if(pfJets_it != event->pfJets.end()){

					susy::PFJetCollection& jetColl = pfJets_it->second;

					for(std::vector<susy::PFJet>::iterator it = jetColl.begin();it != jetColl.end(); it++) {

						std::map<TString,Float_t>::iterator s_it = it->jecScaleFactors.find("L1FastL2L3");
						if (s_it == it->jecScaleFactors.end()) {
							std::cout << "JEC is not abailable for this jet!!!" << std::endl;
							continue;
						}
						float scale = s_it->second;
						TLorentzVector corrP4 = scale * it->momentum;

						if(corrP4.Pt() < 30) continue;
						if(std::fabs(corrP4.Eta()) > 2.6) continue; //AN_11_409

						float uncorrE = it->momentum.E();
						float NeutralHadronFraction = (it->neutralHadronEnergy)/uncorrE;
						float NeutralEMFraction =(it->neutralEmEnergy)/uncorrE;
						float ChargedHadronFraction = (it->chargedHadronEnergy)/uncorrE;
						float ChargedEMFraction = (it->chargedEmEnergy)/uncorrE;

						if(std::fabs(corrP4.Eta()) < 2.4){      //AN_11_409 selection
							if((int(it->nConstituents) <= 1) ||
									(NeutralHadronFraction > 0.99) ||
									(NeutralEMFraction > 0.99) ||
									(ChargedHadronFraction <= 0) ||
									(ChargedEMFraction > 0.99) ||
									(int(it->chargedHadronMultiplicity) <= 0)) continue;
						}
						else {  //eta in 2.4-2.6. We the jet misses the tracker but hits HCAL, so ignore charged criteria.
							if((int(it->nConstituents) <= 1) ||
									(NeutralHadronFraction > 0.99) ||
									(NeutralEMFraction > 0.99) ) continue;
						}

						if(event->eventNumber == ((unsigned int)probeevent)){
							printf("PFjet Pt %.1f Eta %.2f Phi %.2f\n",corrP4.Pt(),corrP4.Eta(),corrP4.Phi());
						}	


						//Make sure the jet is not a photon
						bool same_pho_object = false; //exclude the two photons you use for analysis. 
						for(std::vector<susy::Photon*>::iterator p_it = loose_susy12_photons.begin(); p_it != loose_susy12_photons.end(); p_it++) {
							if(event->eventNumber == ((unsigned int)probeevent)){
								printf("      Photon Pt %.1f Eta %.2f Phi %.2f\n",(*p_it)->momentum.Pt(),(*p_it)->momentum.Eta(),(*p_it)->momentum.Phi());
								cout<<"      object match: "<<isSameObject(corrP4,(*p_it)->momentum)<<endl;
							}
							same_pho_object |= isSameObject(corrP4,(*p_it)->momentum);
						}


						//Make sure the jet is not an electron
						bool same_emobject = false;
						for(std::vector<susy::Electron*>::iterator m_it = pfEles.begin(); m_it != pfEles.end(); m_it++) { 
							if(event->eventNumber == ((unsigned int)probeevent)){
								printf("      Ele Pt %.1f Eta %.2f Phi %.2f\n",(*m_it)->momentum.Pt(),(*m_it)->momentum.Eta(),(*m_it)->momentum.Phi());
								cout<<"      object match: "<<isSameObject(corrP4,(*m_it)->momentum)<<endl;
							}
							same_emobject |= isSameObject(corrP4,(*m_it)->momentum);
						}



						//Make sure the jet is not an muon
						bool same_muon = false;
						for(std::vector<susy::Muon*>::iterator m_it = Muons.begin(); m_it != Muons.end(); m_it++){
							if(event->eventNumber == ((unsigned int)probeevent)){
								printf("      Muon Pt %.1f Eta %.2f Phi %.2f\n",(*m_it)->momentum.Pt(),(*m_it)->momentum.Eta(),(*m_it)->momentum.Phi());
								cout<<"      object match: "<<isSameObject(corrP4,(*m_it)->momentum)<<endl;
							}
							same_muon |= isSameObject(corrP4,(*m_it)->momentum);
						}



						if(!same_emobject && !same_muon && !same_pho_object){
							ra3_pfjets.push_back(&*it);
							HT_all += corrP4.Pt();
							MHT_x_all -= corrP4.Px();
							MHT_y_all -= corrP4.Py();	
						}

					}// pfjet
				}//if

				std::sort(ra3_pfjets.begin(),ra3_pfjets.end(),EtGreater<susy::PFJet>);
				//MHT_all = std::sqrt(MHT_x_all*MHT_x_all + MHT_y_all*MHT_y_all);



                         /////////////////////////////////////////////////////////////////
                          //////////////////////// FIND B-JETS  ///////////////////////////
                          /////////////////////////////////////////////////////////////////
				for(std::vector<susy::PFJet*>::iterator it = ra3_pfjets.begin();	it != ra3_pfjets.end(); it++) { 
					if((*it)->bTagDiscriminators[5] > 0.898) pfBJetsTight.push_back(*it);//CSV medium working point
					if((*it)->bTagDiscriminators[5] > 0.679) pfBJetsMedium.push_back(*it);//CSV medium working point
					if((*it)->bTagDiscriminators[5] > 0.244) pfBJetsLoose.push_back(*it);//CSV loose working point
				}
				
				//////////////////////// GET MET  ///////////////////////////
				if(printLevel > 0) std::cout << "Select which met will be used in the event." << std::endl;
				std::map<TString, susy::MET>::iterator met_it = event->metMap.find("pfMet");
				if(met_it == event->metMap.end()) {
					std::cout << "MET map is not availabel!!!" << std::endl;
					continue;
				}
				Counters["has met map"]++;

				susy::MET* pfmet = &(met_it->second);
				bool spillguts = false;
				if(event->eventNumber == ((unsigned int)probeevent)) spillguts = true;
				float corrmet = JEC_MET(pfmet,ra3_pfjets,spillguts);
				//metPhi = TMath::ATan(MHT_y_all/MHT_x_all);

				//myST = HT_all + myPhotonST + corrmet + myLeptonST;
				//met = corrmet;
				/*if(corrmet<30){
					cout<<endl<<"WARNING!! MET < 30 met = "<<corrmet<<" uc pfMET="<<pfmet->met()<<endl;
					cout<<"list "<<event->runNumber<<" "<<event->luminosityBlockNumber<<" "<<event->eventNumber<<endl;
				}*/


				//Get the denominators: look at all reco jets, categorize as MC b-jets and non-b's. 
				int ib = 0;//count how many MC true b-jets there are. 
				for(std::vector<susy::PFJet*>::iterator itj = ra3_pfjets.begin();	itj != ra3_pfjets.end(); itj++) { 
					bool isB = false; 
					for(std::vector<susy::Particle>::iterator it = event->genParticles.begin(); !isB && it != event->genParticles.end(); it++) {
						isB |= abs(it->pdgId) == 5 && (*itj)->momentum.DeltaR(it->momentum)<0.5;
					}
					if(isB){
						bjetEffDen->Fill((*itj)->momentum.Pt());
						ib++;
					}
					else bMistagDen->Fill((*itj)->momentum.Pt());
				}
				nbjets_dist->Fill(ib);

				int im = 0;
				for(std::vector<susy::PFJet*>::iterator itb = pfBJetsTight.begin();	itb != pfBJetsTight.end(); itb++) {
					bool isB = false; 
					for(std::vector<susy::Particle>::iterator it = event->genParticles.begin();!isB &&	it != event->genParticles.end(); it++) {
						isB |= abs(it->pdgId) == 5 && (*itb)->momentum.DeltaR(it->momentum)<0.5;
					}
					if(isB) bjetEff_CSVTNum->Fill((*itb)->momentum.Pt());
					else {
						bMistag_CSVTNum->Fill((*itb)->momentum.Pt());
						im++;
					}
				}
				nMistagsT_dist->Fill(im);
				im = 0;
				for(std::vector<susy::PFJet*>::iterator itb = pfBJetsMedium.begin();	itb != pfBJetsMedium.end(); itb++) {
					bool isB = false; 
					for(std::vector<susy::Particle>::iterator it = event->genParticles.begin();!isB && it != event->genParticles.end(); it++) {
						isB |= abs(it->pdgId) == 5 && (*itb)->momentum.DeltaR(it->momentum)<0.5;
					}
					if(isB) bjetEff_CSVMNum->Fill((*itb)->momentum.Pt());
					else{
						bMistag_CSVMNum->Fill((*itb)->momentum.Pt());
						im++;
					}
				}
				nMistagsM_dist->Fill(im);
				im = 0;
				for(std::vector<susy::PFJet*>::iterator itb = pfBJetsLoose.begin();	itb != pfBJetsLoose.end(); itb++) {
					bool isB = false; 
					for(std::vector<susy::Particle>::iterator it = event->genParticles.begin(); !isB && it != event->genParticles.end(); it++) {
						isB |= abs(it->pdgId) == 5 && (*itb)->momentum.DeltaR(it->momentum)<0.5;
					}
					if(isB) bjetEff_CSVLNum->Fill((*itb)->momentum.Pt());
					else{
						bMistag_CSVLNum->Fill((*itb)->momentum.Pt());
						im++;
					}
				}
				nMistagsL_dist->Fill(im);


				//END LOOKING AT MC TRUTH


				//flatskimtree->Fill();
				if(event->eventNumber == ((unsigned int)probeevent)) cout<<"probe: corrmet "<<corrmet<<" uncorrmet "<< pfmet->met() <<endl;
				
				eventlist<<event->runNumber<<" "<<event->luminosityBlockNumber<<" "<<event->eventNumber<<endl;
				


				if(event->eventNumber == ((unsigned int)probeevent)){//probe
					TLorentzVector gg_trip =        loose_susy12_photons[0]->momentum + loose_susy12_photons[1]->momentum;
					float mgg_trip = gg_trip.M();
					float pigg_trip = gg_trip.Pt()/mgg_trip;
					cout<<endl<<"*** Probe Event ***"<<endl;

					cout<<"run "<< event->runNumber <<" lumi "<< event->luminosityBlockNumber << " event "<< event->eventNumber <<endl;
					printf("phoPt[0] %.2f Eta %.2f Phi %.2f\n", loose_susy12_photons[0]->momentum.Pt(), loose_susy12_photons[0]->momentum.Eta(), loose_susy12_photons[0]->momentum.Phi() );
					printf("phoPt[1] %.2f Eta %.2f Phi %.2f\n", loose_susy12_photons[1]->momentum.Pt(), loose_susy12_photons[1]->momentum.Eta(), loose_susy12_photons[1]->momentum.Phi() );
					printf("met %f phi %.2f\n",corrmet,pigg_trip);
				}//end probe
			} // for every jentry
			///AT THIS POINT WE DECLARE THE EVENT PHYSICS-GOOD

			for (int i=0; i<int(Counter_order.size()); i++) {
				cout <<  Counters[Counter_order[i]] << " " << Counter_order[i] << endl;
			}

			bjetEffDen->Sumw2();
			bjetEff_CSVLNum->Sumw2();
			bjetEff_CSVMNum->Sumw2();
			bjetEff_CSVTNum->Sumw2();
			bjetEff_CSVL->Divide(bjetEff_CSVLNum,bjetEffDen);
			bjetEff_CSVM->Divide(bjetEff_CSVMNum,bjetEffDen);
			bjetEff_CSVT->Divide(bjetEff_CSVTNum,bjetEffDen);
			bjetEff_CSVL->Sumw2();
			bjetEff_CSVM->Sumw2();
			bjetEff_CSVT->Sumw2();

			bMistagDen->Sumw2(); 
			bMistag_CSVLNum->Sumw2(); 
			bMistag_CSVMNum->Sumw2(); 
			bMistag_CSVTNum->Sumw2(); 
			bMistag_CSVL->Divide(bMistag_CSVLNum,bMistagDen);
			bMistag_CSVM->Divide(bMistag_CSVMNum,bMistagDen);
			bMistag_CSVT->Divide(bMistag_CSVTNum,bMistagDen);
			bMistag_CSVL->Sumw2(); 
			bMistag_CSVM->Sumw2(); 
			bMistag_CSVT->Sumw2(); 

			b_tag_eff_file->cd();
			bjetEff_CSVL->Write();
			bjetEff_CSVM->Write();
			bjetEff_CSVT->Write();
			nbjets_dist->Write();
			bMistag_CSVL->Write();
			bMistag_CSVM->Write();
			bMistag_CSVT->Write();
			nMistagsL_dist->Write(); 
			nMistagsM_dist->Write();
			nMistagsT_dist->Write(); 
			b_tag_eff_file->Close();

			eventlist.close();
			// close the output file
			//flatskim.cd();
			//flatskimtree->Write();
			//flatskim.Close();
			//eventlist2.close();


			//	fout->cd();
			//	fout->Write();
			//	fout->Close();
			//
			//	if(enableFilter) {
			//		filterTree->GetCurrentFile()->cd();
			//		filterTree->GetCurrentFile()->Write();
			//		filterTree->GetCurrentFile()->Close();
			//	}//end if filter enabled

		}//end Loop


		bool SusyAna_MC_BTagEff_test::ok_muon(std::vector<susy::Muon>::iterator it){ //Yu Feng
			//	std::map<TString,UChar_t>::iterator idPair = it->idPairs.find("muidGlobalMuonPromptTight");
			if (//(idPair == it->idPairs.end()) ||
					//(int(idPair->second) == 0) || that belongs in the loop
					(std::fabs(it->momentum.Eta()) > 2.1) || //dm: >2.6
					(it->momentum.Pt() < 20) || //dm: 15
					(it->nValidTrackerHits < 11) ||
					(it->combinedTrackIndex < 0) ||
					((it->ecalIsoR03 + it->hcalIsoR03 + it->trackIsoR03)/(it->momentum.Pt()) > 0.1) || //relIso > 0.1
					(it->emEnergy > 4.0) ||
					(it->hadEnergy > 6.0)) return false;

			susy::Track& combinedTrack = event->tracks[it->combinedTrackIndex];
			float normChi2 = combinedTrack.chi2 / combinedTrack.ndof;
			float d0 = std::abs(d0correction(event->beamSpot,combinedTrack));

			if(normChi2 >= 10.f || d0 >= 0.2 ) return false;
			else return true;
		}

		bool SusyAna_MC_BTagEff_test::ok_muon_AN_11_409(std::vector<susy::Muon>::iterator it,susy::Track& combinedTrack, float pVtx_Z){ //probably inner track instead
			//get combinedTrack using 	susy::Track& combinedTrack = event->tracks[it->combinedTrackIndex];
			//I don't see where
			if(!it->isGlobalMuon()) return false;
			if(!it->isPFMuon()) return false;
			//	std::map<TString,UChar_t>::iterator idPair = it->idPairs.find("muidGlobalMuonPromptTight");
			if (
					//(idPair == it->idPairs.end()) ||
					//(int(idPair->second) == 0) ||
					(std::fabs(it->momentum.Eta()) > 2.4) || //dm: >2.6
					(it->momentum.Pt() < 10) ||
					(it->nValidTrackerHits < 11) ||
					(it->combinedTrackIndex < 0) ||
					((it->ecalIsoR03 + it->hcalIsoR03 + it->trackIsoR03)/(it->momentum.Pt()) >= 0.15) || //relIso > 0.15
					//(it->emEnergy > 4.0) ||
					//	(it->hadEnergy > 6.0)
					fabs(combinedTrack.vertex.Z() - pVtx_Z) >= 1.0 //1 cm //Brain Francis and Dave Moris don't use this.
			   ) return false;
			//float normChi2 = combinedTrack.chi2 / combinedTrack.ndof;
			float d0 = std::abs(d0correction(event->beamSpot,combinedTrack));

			//	if(normChi2 >= 10.f || d0 >= 0.2 ) return false;
			if(d0 >= 0.2 ) return false; //assuming that sais d0 < 0.02cm.
			else return true;
		}

		//use this one!
		bool SusyAna_MC_BTagEff_test::ok_muon_DMoris(std::vector<susy::Muon>::iterator it_Mu,susy::Track& innerTrack){
			if(!it_Mu->isGlobalMuon()) return false; //Brian Francis agrees
			if(!it_Mu->isPFMuon()) return false; //Brian Francis agrees

			float pt = it_Mu->momentum.Pt();
			//	float combIso=(it_Mu->ecalIsoR03 + it_Mu->hcalIsoR03 + it_Mu->trackIsoR03);
			float combIsoPF=( it_Mu->sumChargedHadronPt04 + std::max(0.,it_Mu->sumNeutralHadronEt04+it_Mu->sumPhotonEt04-0.5*it_Mu->sumPUPt04) );
			//	float relIso = combIso/pt;
			float relIsoPF = combIsoPF/pt;
			float eta = fabs(it_Mu->momentum.Eta());
			float numberOfValidPixelHits = innerTrack.numberOfValidPixelHits;
			float d0 = innerTrack.d0();
			float dZ = innerTrack.dz();
			float numberOfValidTrackerHits = it_Mu->nValidTrackerHits;
			float numberOfValidMuonHits = it_Mu->nValidMuonHits;
			float chi2OverNdof = innerTrack.normChi2();

			if(pt < 15) return false; //Brian Francis agrees
			if(eta > 2.6) return false;  // the TDR says the muon system ends at |eta| < 2.4
			if(chi2OverNdof > 10)return false;
			if(numberOfValidMuonHits<=0)return false; //Brian Francis agrees
			if(std::fabs(d0) > 0.2) return false; //Brian Francis agrees
			if(std::fabs(dZ) > 0.5) return false; //Brian Francis agrees
			if(numberOfValidPixelHits<=0)return false; //Brian Francis agrees
			if(numberOfValidTrackerHits<11)return false;
			if(relIsoPF > 0.2) return false; //Brian Francis agrees
			//Also consider
			//if((int)mu_it->trackIndex >= (int)event->tracks.size()) return false;

			return true;
			//DMoris: don't have trackerlayerswithmeasurement or numberofmatchedstations
			//id from https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId
		}

		//use this one!
		bool SusyAna_MC_BTagEff_test::ok_ele(std::vector<susy::Electron>::iterator it_Ele){	//Dave Moris
			if(!it_Ele->isPF() and !it_Ele->passingMvaPreselection()) return false;
			float Iso=it_Ele->chargedHadronIso + it_Ele->neutralHadronIso + it_Ele->photonIso;
			float pt=it_Ele->momentum.Pt();
			if(it_Ele->momentum.Eta()>2.6) return false;
			if(pt<15) return false;
			if(Iso/pt>0.2) return false;
			return true;
		}

		bool SusyAna_MC_BTagEff_test::ok_ele_AN_11_409(std::vector<susy::Electron>::iterator it_Ele, susy::Track& innerTrack, float pVtx_Z){
			//if(!it_Ele->isPF() and !it_Ele->passingMvaPreselection()) return false;
			float pt=it_Ele->momentum.Pt();
			if(pt<10) return false;
			//	float Iso= it_Ele->ecalIsoR03 + it_Ele->hcalIsoR03 + it_Ele->trackIsoR03;
			float Iso= it_Ele->dr03TkSumPt+ it_Ele->dr03EcalRecHitSumEt+ it_Ele->dr03HcalDepth1TowerSumEt+ it_Ele->dr03HcalDepth2TowerSumEt;
			float eleSCEta = it_Ele->momentum.Eta(); // this is probably wrong
			if(eleSCEta>2.5 || (eleSCEta > 1.4442 && eleSCEta < 1.566)) return false;
			if(Iso/pt>=0.2) return false; //RelIso
			float d0 = innerTrack.d0(); //no! d0 of the pv!
			float dZ = innerTrack.dz(); //no! dZ of the pv!
			if(std::fabs(d0) >= 0.2) return false;	  //require |d0 (beam spot)| < 0.02
			if(std::fabs(dZ - pVtx_Z) >= 1) return false; 	  //|ele.vertex.Z - pVtx_Z | < 1cm
			//require number of lost hits <= 1, I don't know how to implement this!!!!!!! xxx
			return true;
		}


		//Jet Energy Corrections
		float SusyAna_MC_BTagEff_test::JEC_MET(susy::MET* pfmet,std::vector<susy::PFJet*> ra3_pfjets,bool Debug_noisily){
			//add adjust MET for JEC. 
			float corr_px = 0;
			float corr_py = 0;
			float uncorr_px = 0;
			float uncorr_py = 0;
			if(Debug_noisily) printf("Entering JEC_MET. UCmet = %.3f\n",pfmet->met());
			if(Debug_noisily) printf("njets: %i\n",(int)ra3_pfjets.size());
		//printf("attempt jec uc\n");

		//JetCorrectorParametersCollection JetCorParColl;
		//FactorizedJetCorrector *JetCorrector;
		//JetCorrectorParameters *ResJetPar = new JetCorrectorParameters("YYYY_L2L3Residual_AK5PF.txt"); 

		//edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
		/*ESHandle<JetCorrectorParametersCollection> JetCorParColl;
		JetCorrectorParametersCollection JetCorParColl;
		iSetup.get<JetCorrectionsRecord>().get("AK5PF",JetCorParColl); 
		JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"];
		JetCorrectionUncertainty *jecUnc = new JetCorrectionUncertainty(JetCorPar);
*/

		//printf("end attempt jec uc\n");
			for(std::vector<susy::PFJet*>::iterator m_it = ra3_pfjets.begin();
					m_it != ra3_pfjets.end(); m_it++) {

				std::map<TString,Float_t>::iterator s_it = (*m_it)->jecScaleFactors.find("L1FastL2L3");
				if (s_it == (*m_it)->jecScaleFactors.end()) {
					std::cout << "JEC is not availabel for this jet!!!" << std::endl;
					continue;
				}

				std::map<TString,Float_t>::iterator s_it_v1 = (*m_it)->jecScaleFactors.find("L2L3");
				if (s_it_v1 == (*m_it)->jecScaleFactors.end()) {
					std::cout << "JEC is not availabel for this jet!!!" << std::endl;
					continue;
				}

				float scale = s_it->second;
				float scale_v1 = s_it_v1->second;
				float scale_l1fastl2l3_minus_l1fast = 1+(scale - scale/scale_v1);
				if(Debug_noisily) printf("scale %f scale_v1 %f scale_l1fastl2l3_minus_l1fast %f \n",scale,scale_v1,scale_l1fastl2l3_minus_l1fast);
				if(Debug_noisily) printf("JetEt: %.2f\n", (*m_it)->momentum.Pt());

				TLorentzVector corrP4 = scale_l1fastl2l3_minus_l1fast *( (*m_it)->momentum );
				corr_px += corrP4.Px();
				corr_py += corrP4.Py();
				uncorr_px += (*m_it)->momentum.Px();
				uncorr_py += (*m_it)->momentum.Py();
				if(Debug_noisily) printf("corr_px %.2f y %.2f uncorr_px %.2f y %.2f\n",corr_px,corr_py,uncorr_px,uncorr_py);
			}

			float corrmet_x = corr_px - uncorr_px;
			float corrmet_y = corr_py - uncorr_py;
			float met_x = pfmet->metX();
			float met_y = pfmet->metY();
			float corrmet = std::sqrt((met_x - corrmet_x)*(met_x - corrmet_x) + (met_y - corrmet_y)*(met_y - corrmet_y));
			if(Debug_noisily) printf("In Total corrmet_x %.2f y %.2f met_x%.2f y %.2f corrmet %.3f\n",corrmet_x,corrmet_y,met_x,met_y,corrmet);
			return corrmet;
		}

		bool SusyAna_MC_BTagEff_test::ok_vtx(std::vector<susy::Vertex>::iterator it){
			float vtx_rho = std::sqrt((it->position.X())*(it->position.X()) + (it->position.Y())*(it->position.Y()));
			if(it->isFake() || //it->chi2 == 0.f) || (it->tracksSize == 0) ||  //this disagrees with D.Morris. DM: Vtx_it->isFake() ||
				(it->ndof <= 4.f) ||
					(std::fabs(it->position.Z()) >= 24.f) || //vtx absZ > 24
					(vtx_rho >= 2.f)) return false;
			return true;
		}





