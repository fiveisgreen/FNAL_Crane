	// -*- C++ -*-
#define SusyEventAnalyzer_shruti_cxx

	//            ||
	//         _.-''-._
	//        (O_.--._O)
	//        //      \\            ______  ______          ___       __   __   _______
	//       //        \\          /      ||   _  \        /   \     |  \ |  | |   ____|
	//      //          \\        |  ,----'|  |_)  |      /  ^  \    |   \|  | |  |__
	//  .-.//            \\.-.    |  |     |      /      /  /_\  \   |  . `  | |   __|
	//  |O)/              \(O|    |  `----.|  |\  \----./  _____  \  |  |\   | |  |____
	//  | `-.            .-` |     \______|| _| `._____/__/     \__\ |__| \__| |_______|
	//   \  |            |  /
	//    \ |            | /
	//     \|            |/
	//      `            `
	// Written by Anthony Barker, 2013

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#include <utility>

#include "SusyEventAnalyzer_shruti.h"
#include "SusyEventPrinter.h"

#include "../jec/JetMETObjects/interface/JetCorrectorParameters.h"
#include "../jec/JetMETObjects/interface/FactorizedJetCorrector.h"
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
#include <string.h>
	//user defiend
#include "utilities.h"
#include "cuts.h"
#include "params_arg.h"
	//#include "GetError.h"
#include "hggx_analysers.h"
#include "quicksave.C"
#include "CMSStyle.C"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "hggx_analysers.h"

using namespace std;
using namespace params;


template<typename T> bool EtGreater(const T* p1, const T* p2) {
	return (p1->momentum.Et() > p2->momentum.Et());
}
template<typename T> bool EtGreaterpho(const T* p1, const T* p2) {
	if(useMVAphoP) return ((p1->MVAregEnergyAndErr.first / p1->momentum.E())*p1->momentum).Et() > ((p2->MVAregEnergyAndErr.first / p2->momentum.E())*p2->momentum).Et();
	else return p1->momentum.Et() > p2->momentum.Et();
}


void SusyEventAnalyzer_shruti::InitializePerEvent() {

}


bool SusyEventAnalyzer_shruti::isSameObject(TLorentzVector& p1, TLorentzVector& p2) {

	float dEta = p1.Eta() - p2.Eta();
	float dPhi = TVector2::Phi_mpi_pi(p1.Phi() - p2.Phi());
	return std::sqrt(dEta*dEta + dPhi*dPhi) <= 0.6 || fabs(dPhi) <= 0.05; //dMorse as of April2013
		//return std::sqrt(dEta*dEta + dPhi*dPhi) < 0.5;
}//dR05 cut


float SusyEventAnalyzer_shruti::d0correction(TVector3& beamSpot, susy::Track& track) const {

	return track.d0() - beamSpot.X()*std::sin(track.phi()) + beamSpot.Y()*std::cos(track.phi());
}


bool SusyEventAnalyzer_shruti::PassTrigger(TString path) {
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


bool SusyEventAnalyzer_shruti::PassTriggers() {
	bool pass = false;
	for(std::vector<TString>::iterator it = hltNames.begin(); it != hltNames.end(); it++) {
		if(PassTrigger(*it)) {
			pass = true;
			break;
		}
	}
	return pass;
}

typedef std::map<string,int> nameint;
typedef std::map<string,float> namefloat;
typedef std::map<string,bool> namebool;
typedef std::map<string,string> labels;

typedef std::map<string,TH1F*> LabelHist;
typedef std::map<string,LabelHist> Label2Hist;
typedef std::map<string,TH1F**> LabelHistArr;
typedef std::map<string,LabelHistArr> Label2HistArr;

void addCounter(nameint & C, vector<string> & V, string Label){
	C[Label]=0;
	V.push_back(Label);
}

void remove_duplicate_photons(std::vector<susy::Photon*> & photons,bool keep_hardest_matched_photon=true){
	/*
	 This takes a pt-sorted vector of Photon*. It looks through all pairs of photons, for dR matches (dR<0.6 or dPhi < 0.05)
	 If it finds a match and keep_hardest_matched_photon, it keeps the hardest one and deletes the others from the vector.
	 If it finds a match and !keep_hardest_matched_photon, it deletes all photons involved int the match. David Morse and I do the former.
	 */

	if (photons.size()<2) return;
	std::vector<susy::Photon*>::iterator i_p1 = photons.begin(); int I_p1 = 0;
		//cout<<"enter remove_duplicate_photons. Size = "<<photons.size()<<endl;
		//cout<<"photon end: "<<*photons.end()<<" i_p1+1: "<<*(i_p1+1)<<endl;
	int size = photons.size();
	while(I_p1+1 < size){
			//while(i_p1+1 != photons.end()){
		bool match_found = false;
			//cout<<"phoA. i="<<I_p1<<" "<<*i_p1<<endl;
		TLorentzVector p1 = (useMVAphoP?(*i_p1)->MVAregEnergyAndErr.first / (*i_p1)->momentum.E():1.0)*(*i_p1)->momentum;
			//TLorentzVector p1 = useMVAphoP?(*i_p1)->MVAcorrMomentum:(*i_p1)->momentum;
			//TLorentzVector p1 = (*i_p1)->momentum;
		std::vector<susy::Photon*>::iterator i_p2 = i_p1+1; int I_p2 = I_p1+1;
		while(I_p2 < size){ //increments to the terminator, then does not terminate.
				//while(i_p2 != photons.end()){ //increments to the terminator, then does not terminate.
				//cout<<"phoB, i= "<<I_p2<<" "<<*i_p2<<endl;
				//TLorentzVector p2 = (*i_p2)->momentum;
			TLorentzVector p2 = (useMVAphoP?(*i_p2)->MVAregEnergyAndErr.first / (*i_p2)->momentum.E():1.0)*(*i_p2)->momentum;
				//TLorentzVector p2 = useMVAphoP?(*i_p2)->MVAcorrMomentum:(*i_p2)->momentum;
				//cout<<"rem4"<<endl;
			if (dR(p1,p2)<0.6 || dPhi(p1,p2) < 0.05 ) {
				std::vector<susy::Photon*>::iterator temp = i_p2+1;
				i_p2 = photons.erase(i_p2);//this is supposed to return the next element but does not.
					//cout<<"found match phoB new address: "<<*i_p2<<endl;
				i_p2 = temp;
					//cout<<"after =temp, address: "<<*i_p2<<endl;
				size--;
				match_found = true;
				if(I_p2 == (int) photons.size()-1) break;
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

void SusyEventAnalyzer_shruti::Loop() {
	ofstream firealarm;
	bool onfire = false;
	firealarm.open("tmpfirealarm.txt");
	firealarm << "SusyEventAnalyzer_shruti_MC_arg is on FIRE"<<endl;
	firealarm.close();
		///////////////////////////////////////////////////////
	printLevel = 0;
	int nKinemVars = nKinemVars_all;
	string *s_KinemVars = s_KinemVars_all;


	string s_forTopo[nEventTopologies];
		//s_forTopo[0]="";
	for (int iTopo=0; iTopo<nEventTopologies; iTopo++){ //xxx may have to change this line back.
		s_forTopo[iTopo]=string(" for ")+s_EventTopology[iTopo];
	}


	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntries();
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
	addCounter(Counters,Counter_order,"have 2 loose photons");
	if(useSusyLoose_PS_ElePho) addCounter(Counters,Counter_order,"have 1 ele, 1 pho candidat");
		//addCounter(Counters,Counter_order,"have 2 tight photons");
		//addCounter(Counters,Counter_order,"have 2 tight photons passing dR cuts");
	addCounter(Counters,Counter_order,"pass a primary vertex reqirement");
	addCounter(Counters,Counter_order,"has met map");
	addCounter(Counters,Counter_order,"number filtered");
		//no extra cuts.
	for (int iTopo=0; iTopo<nEventTopologies; iTopo++) {
		addCounter(Counters,Counter_order,string("are in tag region")+s_forTopo[iTopo]);
		addCounter(Counters,Counter_order,string("are in sb region")+s_forTopo[iTopo]);
		addCounter(Counters,Counter_order,string("are in usb region")+s_forTopo[iTopo]);
		addCounter(Counters,Counter_order,string("are in lsb region")+s_forTopo[iTopo]);
	}

	TH1I *lsb_int = new TH1I("lsb_int","lower side band integrals",nEventTopologies,0,nEventTopologies);
	TH1I *usb_int = new TH1I("usb_int","lower side band integrals",nEventTopologies,0,nEventTopologies);
		//order:keeps the order of the s_EventTopology array in params.

	int nFiltered = 0;
	TTree* filterTree = 0;
	cout << "enableFilter is set to "<<enableFilter<<endl;
	if (enableFilter){
		enableFilter = false;
		cout << "setting it to false"<<endl;
	}

	ofstream eventlist;
	if(makeEventsList) eventlist.open ("trip_eventlist_SusyMain.txt");
	ofstream tmvaOut;
	if(makeTMVAlist) tmvaOut.open ("tmva_bkg_data.txt");
	ofstream specialevents;
	specialevents.open ("special_events_in_data.txt");

		//Set the first line to be the var names:
		//format:
		//TotEt/F:dPhi/F:METdPhiLead/F:METdPhiTrail/F:AlphaT/F:PhotonLessHT/F:DiEMPt/F:InvarMass/F:Met/F:MR/F
		//if(makeTMVAlist) tmvaOut<<"MET/F:ST/F:HT/F:Bt/F:MHT/F:PtGG/F:EtaGG/F:phoPt0/F:phoPt1/F:phoEta0/F:phoEta1/F:phoEtaMax/F:phoEtaMin/F:nJets/I:nBjets/I:bestMjj/F:nLep/I:nMu/I:nEle/I:Mleplep/F:MTpho0MET/F:MTpho1MET/F:cosThetaStar/F:phoDPhi/F:dPhiPho0Met/F:dPhiPho1Met/F:dijetDEta01/F:dijetEta01/F:dijetDPhi01/F:dijetM01/F:dijetPt01/F:dPhiJet0Met/F:dPhiJet1Met/F"<<endl;
	if(makeTMVAlist) tmvaOut<<"phoPt0/F"<<endl;

		// open hist file and define histograms
		//cout <<endl<< "Writing to Plots File "<< plotsroot_data<<endl<<endl;
		//TFile* fout = new TFile(plotsroot_data.c_str(),"RECREATE");
		//fout->cd();
	ofstream logfile;
	logfile.open("shruti.log");



	TH1F* h_vtxZ_unsliced = new TH1F("vtxZ_unsliced","Z position of the primary vertex;Z (cm);Events",100,-50.0,50.0);
	TH1F* h_bsZ_unsliced = new TH1F("bsZ_unsliced","Z position of the beam spot;Z (cm);Events",100,-50.0,50.0);

		//nameint nbins;
		//namefloat hmin;
		//namefloat hmax;
		//labels xlabels;
		//labels titles;
	printf("Setup Kinematic Vars\n");
	LabelKinVars KinVars = setupKinematicVar(); //setup all the binning and histogram info printf("worked!\n");


	namebool topoCut;
	for (int iTopo = 0; iTopo<nEventTopologies; iTopo++) topoCut[s_EventTopology[iTopo]] = false;

		//no extra selection.
	LabelHist lh_mGG_unsliced;

	Label2Hist lh_unsliced;
	Label2HistArr lha2;


		//make all the unsliced plots.
	for (int iTopo = 0; iTopo<nEventTopologies; iTopo++) {
		lh_mGG_unsliced[s_EventTopology[iTopo]] = new TH1F(
														   (char*)(string("h_mGG")+s_EventTopology[iTopo]+"_unsliced").c_str(),
														   (char*)(string("Di Photon Mass Sectrum")+s_forTopo[iTopo]+";M^{#gamma #gamma} (GeV)").c_str(),
														   PhoMassNBins,PhoMassMin,PhoMassMax);

		LabelHist tmpMapKinVar;
		for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++) {

			if(KinVars[s_KinemVars[kKinVar]]->useCustomBinning){

				tmpMapKinVar[s_KinemVars[kKinVar]] = new TH1F(
															  (char*)(string("h_")+s_KinemVars[kKinVar]+s_EventTopology[iTopo]+"_unsliced").c_str(),
															  (char*)(KinVars[s_KinemVars[kKinVar]]->titles+s_forTopo[iTopo]+";"+KinVars[s_KinemVars[kKinVar]]->xlabels).c_str(),
															  KinVars[s_KinemVars[kKinVar]]->nbins,
															  KinVars[s_KinemVars[kKinVar]]->CustomBinning);
			}
			else{
				tmpMapKinVar[s_KinemVars[kKinVar]] = new TH1F(
															  (char*)(string("h_")+s_KinemVars[kKinVar]+s_EventTopology[iTopo]+"_unsliced").c_str(),
															  (char*)(KinVars[s_KinemVars[kKinVar]]->titles+s_forTopo[iTopo]+";"+KinVars[s_KinemVars[kKinVar]]->xlabels).c_str(),
															  KinVars[s_KinemVars[kKinVar]]->nbins,
															  KinVars[s_KinemVars[kKinVar]]->hmin,
															  KinVars[s_KinemVars[kKinVar]]->hmax);
			}

				//tmpMapKinVar[s_KinemVars[kKinVar]] = new TH1F(
				//(char*)(string("h_")+s_KinemVars[kKinVar]+s_EventTopology[iTopo]+"_unsliced").c_str(),
				//(char*)(titles[s_KinemVars[kKinVar]]+s_forTopo[iTopo]+";"+xlabels[s_KinemVars[kKinVar]]).c_str(),
				//nbins[s_KinemVars[kKinVar]],
				//hmin[s_KinemVars[kKinVar]],
				//hmax[s_KinemVars[kKinVar]]);
		}//end for every kinematic varriable.
		lh_unsliced[s_EventTopology[iTopo]] = tmpMapKinVar;
	}//end for every topology

	if(printLevel>4) printf("done making unsliced plots, make collections\n");
		//make the collections.
	for (int iTopo = 0; iTopo<nEventTopologies; iTopo++) {
		LabelHistArr tmpMapKinVar;
		for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++) {

			tmpMapKinVar[s_KinemVars[kKinVar]] = new TH1F*[nPhoMassAndBkgDists];

			if(KinVars[s_KinemVars[kKinVar]]->useCustomBinning){
				MakeHistSet(tmpMapKinVar[s_KinemVars[kKinVar]],
							s_KinemVars[kKinVar]+s_EventTopology[iTopo],
							KinVars[s_KinemVars[kKinVar]]->nbins,
							KinVars[s_KinemVars[kKinVar]]->CustomBinning);
			}
			else{
				MakeHistSet(tmpMapKinVar[s_KinemVars[kKinVar]],
							s_KinemVars[kKinVar]+s_EventTopology[iTopo],
							KinVars[s_KinemVars[kKinVar]]->nbins,
							KinVars[s_KinemVars[kKinVar]]->hmin,
							KinVars[s_KinemVars[kKinVar]]->hmax);
			}
				//MakeHistSet(tmpMapKinVar[s_KinemVars[kKinVar]],
				//s_KinemVars[kKinVar]+s_EventTopology[iTopo],
				//nbins[s_KinemVars[kKinVar]],
				//hmin[s_KinemVars[kKinVar]],
				//hmax[s_KinemVars[kKinVar]]);
		}//end for every kinvar
		lha2[s_EventTopology[iTopo]] = tmpMapKinVar;
	}//end for every Topo,
	if(printLevel>4) printf("done making collections, make selvars\n");
		//end make create histograms

		//plots of things I cut on.
		//////////////////////////////////////////////////////////////
		///////////////////// OBJECT SELECTION VARS /////////////////

		//PHOTONS
	TH1F* pho_Et_0 = new TH1F("pho_Et_0","Leading Photon Pt;E_{t}^{#gamma}",200,0.,200.);
	TH1F* pho_Et_1 = new TH1F("pho_Et_1","Subleading Photon Pt;E_{t}^{#gamma}",200,0.,200.);
	TH1F* pho_Et_2 = new TH1F("pho_Et_2","Sub-sub-leading Photon Pt;E_{t}^{#gamma}",200,0.,200.);

	TH1F* selvar_pho_nPho = new TH1F("selvar_pho_nPho","number of tight photons;n photons", 10,0.,10.);
	TH1F* selvar_pho_Et = new TH1F("selvar_pho_Et","selvar_pho_Et;E_{t}^{#gamma}", 200,0.,200);
	TH1F* selvar_pho_Eta= new TH1F("selvar_pho_Eta","selvar_pho_Eta;#gamma #eta", 100,-2.5,2.5);
	TH1F* selvar_pho_Phi= new TH1F("selvar_pho_Phi","selvar_pho_Phi;#gamma #phi", 60,0.,3.15);
	TH1F* selvar_pho_TrkIsoDR04= new TH1F("selvar_pho_TrkIsoDR04","selvar_pho_TrkIsoDR04;TrackIsoDR04", 32,-1.,7.);
	TH1F* selvar_pho_EcalIsoDR04= new TH1F("selvar_pho_EcalIsoDR04","selvar_pho_EcalIsoDR04;EcalIsoDR04", 34,-2.,15.);
	TH1F* selvar_pho_HcalIsoDR04= new TH1F("selvar_pho_HcalIsoDR04","selvar_pho_HcalIsoDR04;HCalIsoDR04", 32,-1.,7.);
	TH1F* selvar_pho_TrkIsoDR03= new TH1F("selvar_pho_TrkIsoDR03","selvar_pho_TrkIsoDR03;TrackIsoDR03", 32,-1.,7.);
	TH1F* selvar_pho_EcalIsoDR03= new TH1F("selvar_pho_EcalIsoDR03","selvar_pho_EcalIsoDR03;EcalIsoDR03", 34,-2.,15.);
	TH1F* selvar_pho_HcalIsoDR03= new TH1F("selvar_pho_HcalIsoDR03","selvar_pho_HcalIsoDR03;HcalIsoDR03", 32,-1.,7.);
	TH1F* selvar_pho_HE= new TH1F("selvar_pho_HE","selvar_pho_HE;H/E", 110,-0.01,0.1);
	TH1F* selvar_pho_R9= new TH1F("selvar_pho_R9","selvar_pho_R9;R9", 150,-0.1,1.4);
	TH1F* selvar_pho_sinin_bar= new TH1F("selvar_pho_sinin_bar","selvar_pho_sinin_bar;#sigma_{i #eta i #eta}", 140,0.,0.014);
	TH1F* selvar_pho_sipip_bar= new TH1F("selvar_pho_sipip_bar","selvar_pho_sipip_bar;#sigma_{i #phi i #phi}", 0,0.,0.);
	TH1F* selvar_pho_sinin_ec= new TH1F("selvar_pho_sinin_ec","selvar_pho_sinin_ec;#sigma_{i #eta i #eta}", 130,0.025,0.038);
	TH1F* selvar_pho_sipip_ec= new TH1F("selvar_pho_sipip_ec","selvar_pho_sipip_ec;#sigma_{i #phi i #phi}", 0,0.,0.);
	TH1F* selvar_pho_nPixelSeeds= new TH1F("selvar_pho_nPixelSeeds","selvar_pho_nPixelSeeds;n pixel seeds", 11,-1.,10.);
	TH1F* selvar_pho_rho= new TH1F("selvar_pho_rho","selvar_pho_rho;rho25", 80,0.,40.);
	TH1F* selvar_pho_PFcargedHadIso= new TH1F("selvar_pho_PFcargedHadIso","selvar_pho_PFcargedHadIso;PFcargedHadIso", 32,-1.,7.);
	TH1F* selvar_pho_PFneutralHadIso= new TH1F("selvar_pho_PFneutralHadIso","selvar_pho_PFneutralHadIso;PFneutralHadIso", 32,-1.,7.);
	TH1F* selvar_pho_PFphoIso= new TH1F("selvar_pho_PFphoIso","selvar_pho_PFphoIso;PFphoIso", 34,-1.,15.);
	TH1F* selvar_pho_ChargeSafeEleVeto = new TH1F("selvar_pho_ChargeSafeEleVeto","ChargeSafeEleVeto",2,0.,2.);
	/*	TH2F* selvar_pho_TrkIso04_v_rho[7];
	 TH2F* selvar_pho_ECalIso04_v_rho[7];
	 TH2F* selvar_pho_ECalIso04_v_rho[7];
	 TH2F* selvar_pho_TrkIso03_v_rho[7];
	 TH2F* selvar_pho_ECalIso03_v_rho[7];
	 TH2F* selvar_pho_ECalIso03_v_rho[7];
	 TString regions[7] = {"<1", "1 - 1.479", "1.479 - 2", "2 - 2.2", "2.2 - 2.3", "2.3 - 2.4", ">2.4"};
	 for (int i=0; i<7; i++) {
	 selvar_pho_TrkIso04_v_rho[i] = new TH1F("selvar_pho_TrkIso04_v_rho_"+i,"photon TrkIso04_v_rho for eta "+regions[i],140,-5.,30.,60,0.,30.);
	 selvar_pho_ECalIso04_v_rho[7]= new TH1F("selvar_pho_TrkIso04_v_rho_"+i,"photon TrkIso04_v_rho for eta "+regions[i],140,-5.,30.,60,0.,30.);
	 selvar_pho_ECalIso04_v_rho[7]= new TH1F("selvar_pho_TrkIso04_v_rho_"+i,"photon TrkIso04_v_rho for eta "+regions[i],140,-5.,30.,60,0.,30.);
	 selvar_pho_TrkIso03_v_rho[7]= new TH1F("selvar_pho_TrkIso04_v_rho_"+i,"photon TrkIso04_v_rho for eta "+regions[i],140,-5.,30.,60,0.,30.);
	 selvar_pho_ECalIso03_v_rho[7]= new TH1F("selvar_pho_TrkIso04_v_rho_"+i,"photon TrkIso04_v_rho for eta "+regions[i],140,-5.,30.,60,0.,30.);
	 selvar_pho_ECalIso03_v_rho[7]= new TH1F("selvar_pho_TrkIso04_v_rho_"+i,"photon TrkIso04_v_rho for eta "+regions[i],140,-5.,30.,60,0.,30.);
	 }*/

		//ELECTRONS
	TH1F* selvar_ele_nele = new TH1F("selvar_ele_nele","selvar_ele_nele;n ele", 10,0.,10.);
	TH1F* selvar_ele_Et = new TH1F("selvar_ele_Et","selvar_ele_Et;electron E_{t}", 200,0.,200);
	TH1F* selvar_ele_Eta= new TH1F("selvar_ele_Eta","selvar_ele_Eta;ele #eta", 100,-2.5,2.5);
	TH1F* selvar_ele_Phi= new TH1F("selvar_ele_Phi","selvar_ele_Phi;ele #phi", 60,0.,3.15);
	TH1F* selvar_ele_relIso = new TH1F("selvar_ele_relIso","selvar_ele_relIso;ele relIso", 105,-0.1,2.);
		//	TH1F* selvar_ele_passMVAPreselect = new TH1F("selvar_ele_passMVAPreselect","selvar_ele_passMVAPreselect", 2,0.,2.);
		//	TH1F* selvar_ele_isPF = new TH1F("selvar_ele_isPF","selvar_ele_isPF", 2,0.,2.);
		//	TH1F* selvar_ele_d0 = new TH1F("selvar_ele_d0","selvar_ele_d0", 200,0.,20);
		//	TH1F* selvar_ele_dz_pVtxZ = new TH1F("selvar_ele_dz_pVtxZ","selvar_ele_dz_pVtxZ", 80,0.,20.);

		//MUONS
	TH1F* selvar_mu_nmu = new TH1F("selvar_mu_nmu","selvar_mu_nmu;n muons", 10,0.,10.);
	TH1F* selvar_mu_Et = new TH1F("selvar_mu_Et","selvar_mu_Et;muon E_{t}", 200,0.,200);
	TH1F* selvar_mu_Eta= new TH1F("selvar_mu_Eta","selvar_mu_Eta;muon #eta", 100,-2.5,2.5);
	TH1F* selvar_mu_Phi= new TH1F("selvar_mu_Phi","selvar_mu_Phi;muon #phi", 60,0.,3.15);
	TH1F* selvar_mu_relIso = new TH1F("selvar_mu_relIso","selvar_mu_relIso;mu relIso", 140,-5.,30.);
	TH1F* selvars_mu_emEnergy= new TH1F("selvars_mu_emEnergy","selvars_mu_emEnergy;mu emEnergy", 140,-5.,30.);
	TH1F* selvars_mu_hadEnergy= new TH1F("selvars_mu_hadEnergy","selvars_mu_hadEnergy;mu hadEnergy", 140,-5.,30.);
	TH1F* selvar_mu_d0 = new TH1F("selvar_mu_d0","selvar_mu_d0;mu d0", 200,0.,20);
	TH1F* selvar_mu_dz_pVtxZ = new TH1F("selvar_mu_dz_pVtxZ","mu dz-pVtxZ;mu dz-pVtxZ", 80,0.,20.);
	TH1F* selvars_mu_dZ= new TH1F("selvars_mu_dZ","selvars_mu_dZ;mu dZ", 200,0.,20);
	TH1F* selvars_mu_chi2OverNdof = new TH1F("selvars_mu_chi2OverNdof","selvars_mu_chi2OverNdof;mu chi2OverNdof", 200,0.,20);
	TH1F* selvars_mu_nValidTrackerHits= new TH1F("selvars_mu_nValidTrackerHits","selvars_mu_nValidTrackerHits;mu nValidTrackerHits", 40,0.,40);
	TH1F* selvars_mu_combinedTrackIndex= new TH1F("selvars_mu_combinedTrackIndex","selvars_mu_combinedTrackIndex;mu combinedTrackIndex", 40,0.,40);
	TH1F* selvars_mu_numberOfValidPixelHits= new TH1F("selvars_mu_numberOfValidPixelHits","selvars_mu_numberOfValidPixelHits;mu_numberOfValidPixelHits", 40,0.,40);
	TH1F* selvars_mu_numberOfValidMuonHits= new TH1F("selvars_mu_numberOfValidMuonHits","selvars_mu_numberOfValidMuonHits;mu_numberOfValidMuonHits", 40,0.,40);

	TH1F* selvars_mu_isGlobalMuon= new TH1F("selvars_mu_isGlobalMuon","selvars_mu_isGlobalMuon;isGlobalMuon", 2,0.,2.);
	TH1F* selvars_mu_isPFMuon= new TH1F("selvars_mu_isPFMuon","selvars_mu_isPFMuon;isPFMuon", 2,0.,2.);


		//JETS
	TH1F* selvar_jet_njet = new TH1F("selvar_jet_njet","selvar_jet_njet;n jets", 15,0.,15.);
	TH1F* selvar_jet_Et = new TH1F("selvar_jet_Et","selvar_jet_Et; jet E_{t}", 250,0.,250);
	TH1F* selvar_jet_Eta= new TH1F("selvar_jet_Eta","selvar_jet_Eta; jet #eta", 100,-2.5,2.5);
	TH1F* selvar_jet_Phi= new TH1F("selvar_jet_Phi","selvar_jet_Phi; jet #phi", 60,0.,3.15);

	TH1F* selvars_jet_nConstituents= new TH1F("selvars_jet_nConstituents","selvars_jet_nConstituents;jet_nConstituents", 41,-2.,80.);
	TH1F* selvars_jet_NeutralHadFrac= new TH1F("selvars_jet_NeutralHadFrac","selvars_jet_NeutralHadFrac;jet_NeutralHadFrac", 100,0.,1.);
	TH1F* selvars_jet_NeutralEMFrac= new TH1F("selvars_jet_NeutralEMFrac","selvars_jet_NeutralEMFrac;jet_NeutralEMFrac", 100,0.,1.);
	TH1F* selvars_jet_ChargedHadFrac= new TH1F("selvars_jet_ChargedHadFrac","selvars_jet_ChargedHadFrac;jet_ChargedHadFrac", 100,0.,1.);
	TH1F* selvars_jet_ChargedEMFrac= new TH1F("selvars_jet_ChargedEMFrac","selvars_jet_ChargedEMFrac;jet_ChargedEMFrac", 100,0.,1.);
	TH1F* selvars_jet_chargedHadMult= new TH1F("selvars_jet_chargedHadMult","selvars_jet_chargedHadMult;jet_chargedHadMult", 60,0.,60.);
		//	TH1F* selvars_jet_dR_ele_min= new TH1F("selvar_jet_Phi","selvar_jet_Phi", 60,0.,3.);
		//	TH1F* selvars_jet_dR_mu_min= new TH1F("selvar_jet_Phi","selvar_jet_Phi", 60,0.,3.);

		//VERTEX
	TH1F* selvar_vtx_nVtx = new TH1F("selvar_vtx_nVtx","selvar_vtx_nVtx;N vertecies",40,0.,40.);
	TH1F* selvar_vtx_isFake= new TH1F("selvar_vtx_isFake","selvar_vtx_isFake; vertex isFake flag",2,0,2);
	TH1F* selvar_vtx_ndof= new TH1F("selvar_vtx_ndof","selvar_vtx_ndof; vertex ndof",40,0.,40.);
	TH1F* selvar_vtx_chi2= new TH1F("selvar_vtx_chi2","selvar_vtx_chi2;vtx_chi2",200,0.,20);
	TH1F* selvar_vtx_trackSize= new TH1F("selvar_vtx_trackSize","selvar_vtx_trackSize;vtx_trackSize",80,0,80.);
	TH1F* selvar_vtx_rho= new TH1F("selvar_vtx_rho","selvar_vtx_rho;vtx_rho",100,0.,1.);
	TH1F* selvar_vtx_Zpos=new TH1F("selvar_vtx_Zpos","selvar_vtx_Zpos;vtx_Zpos",72,0.,72.);
		//B-TAG
	TH1F* selvar_btag_nbtag= new TH1F("selvar_btag_nbtag","selvar_btag_nbtag;N b-tags",10,0.,10.);
	TH1F* selvar_btag_csv= new TH1F("selvar_btag_csv","selvar_btag_csv;jet CSV",120,0.,1.2);

	if(printLevel>4) printf("now do the trigger\n");

	const int Nnonr9Triggers = 9;
	const int Nr9Triggers = 4;
		//const int NT = Nnonr9Triggers+Nr9Triggers;
		//bool passHLTs[NT];
	TString dmason_triggers[4] = {  //not using these.
		"HLT_Photon36_CaloId10_Iso50_Photon22_CaloId10_Iso50", //Yutaro's study:
		"HLT_Photon36_CaloId10_Iso50_Photon22_R9Id85",
		"HLT_Photon36_R9Id85_Photon22_CaloId10_Iso50",
		"HLT_Photon36_R9Id85_Photon22_R9Id85"};

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
		"HLT_Photon36_R9Id85_OR_CaloId10_Iso50_Photon22_R9Id85_OR_CaloId10_Iso50"}; //include this too

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

	cout<<"opening the file"<<endl;
	TFile f("forshruti.root","RECREATE");

	cout<<"opening "<<endl;
	f.cd();
	TH1F* mvaCor_plot = new TH1F("mva","MVA Corrected E;E (GeV)",100,0,100);
	TH1F* normal_plot = new TH1F("normal","Uncorrected E;E( GeV)",100,0,100);
	TH1F* mvaCor_plot_unsliced = new TH1F("mva_unsliced","MVA Corrected E;E (GeV)",100,0,100);
	TH1F* normal_plot_unsliced = new TH1F("normal_unsliced","Uncorrected E;E( GeV)",100,0,100);

		// start event looping
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry < processNEvents; jentry++) {
			//for (Long64_t jentry=0; jentry < 500; jentry++){  //master loop



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
			//continue;xxx
		}

		if(printLevel > 0 && event->eventNumber == ((unsigned int)probeevent)) cout<<"probe is at point A"<<endl;

		if(printLevel > 0) std::cout << "Apply good run list." << std::endl;
		//if(event->isRealData && useJSON && !isInJson(event->runNumber,event->luminosityBlockNumber)) continue;
		if(printLevel > 0 && event->eventNumber == ((unsigned int)probeevent)) cout<<"probe passes JSON"<<endl;
		Counters["pass Json"]++; // total number of events that pass Json

			//Print(*event);  // uncomment this to print all ntuple variables


		if(printLevel > 1) cout << "Check duplicated events for data only." << endl;

		if(event->isRealData){
			bool duplicateEvent = ! (allEvents[event->runNumber].insert(event->eventNumber)).second;
			if(duplicateEvent){
				cout<<"Duplicate Event! Run "<<event->runNumber<<" Event "<<event->eventNumber<<endl;
				//continue;
			}
		}
		if(printLevel > 0 && event->eventNumber == ((unsigned int)probeevent)) cout<<"probe passes Duplicate Filter"<<endl;
		Counters["pass duplicate check"]++;

			//		if(printLevel > 0) Print(*event); // uncomment this to print all ntuple variables

		if(printLevel > 0) std::cout << "Apply trigger selection in the event." << std::endl;

		bool pass_non_r9id_trigger = false;
		bool pass_r9id_trigger = false;
		bool pass_dmason_trigger = false;
		bool passHLT = false;


		for (int i=0; i<5 && !pass_non_r9id_trigger; i++) {
			pass_dmason_trigger |= PassTrigger(dmason_triggers[i]);
		}
		/*for (int i=0; i<Nnonr9Triggers && !pass_non_r9id_trigger; i++) {
		 pass_non_r9id_trigger |= PassTrigger(nonR9triggers[i]);
		 }
		 if(!pass_non_r9id_trigger){
		 for (int i=0; i<Nr9Triggers && !pass_r9id_trigger; i++) {
		 pass_r9id_trigger |= PassTrigger(R9triggers[i]);
		 }
		 }*/
		passHLT = pass_dmason_trigger;//pass_r9id_trigger || pass_non_r9id_trigger;
		//if(!passHLT) continue;
			//if(useTrigger && !passHLT) continue;
			//if(event->isRealData && useTrigger && !passHLT) continue;
		if(printLevel > 0 && event->eventNumber == ((unsigned int)probeevent)) cout<<"probe passes HLT"<<endl;
		Counters["pass HLT"]++;


		//if(useMETFilter_data && event->isRealData && !event->passMetFilters()) continue; //don't use the met filter for MC, nothing passes.
		if(printLevel > 0 && event->eventNumber == ((unsigned int)probeevent)) cout<<"probe passes MetFilter"<<endl;
		Counters["pass MET Filter"]++;


		if(printLevel > 0) std::cout << "Setup object vectors." << std::endl;

		float myST = 0.0;
		float myPhotonST = 0.0;
		float myLeptonST = 0.0;
		TLorentzVector vMET,vH,vL,vPho;//Have gg for diphotons


		std::vector<susy::Photon*>   loose_photons; // loose objects have all standard cuts except for isolation
		std::vector<susy::Photon*>   tight_susy11_photons; // tight objects hava isolation cuts applied on top of loose objects
		std::vector<susy::Photon*>   tight_susy11Star_photons; // tight objects hava isolation cuts applied on top of loose objects
		std::vector<susy::Photon*>   medium_susy12_photons; // tight objects hava isolation cuts applied on top of loose objects
		std::vector<susy::Photon*>   loose_susy12_photons; // tight objects hava isolation cuts applied on top of loose objects
		std::vector<susy::Photon*>   loose_susy12_photons_pixelSeedVeto; //like susy photons, but using pixel seeds instead.
		std::vector<susy::Photon*>   loose_susy12_photons_pixelSeedReq; //Electrons that fake photons
		std::vector<susy::Photon*>   loose_susy12_photons_NeglectpixelSeed; //Electrons that fake photons
		std::vector<susy::Photon*>   tight_VG11_photons;
		std::vector<susy::Photon*>*  p_photonVector;
			//std::vector<susy::Photon*>* p_photonVector = &tight_susy11_photons;
			//use as (*p_photonVector)

		std::vector<susy::PFJet*>    pfJets;
		std::vector<susy::PFJet*>    pfBJetsTight;
		std::vector<susy::PFJet*>    pfBJetsMedium;
		std::vector<susy::PFJet*>    pfBJetsLoose;
		std::vector<susy::Vertex*>   good_vtx;
			//		std::vector<susy::Muon*>     ra3_muons;
		std::vector<susy::Muon*>     Muons;//DM's collection
		std::vector<susy::PFJet*>    ra3_pfjets;
		std::vector<susy::Electron*>   pfEles;
			//		std::vector<susy::Photon*>   tap_electrons;
			//std::vector<susy::Track*>    tap_tracks;
			//std::vector<susy::PFJet*>    ra3_pfjets_noid;
			//std::vector<susy::PFJet*>    ra3_pfjets_noclean;
			//std::vector<susy::Photon*>   r9_photons;
			//std::vector<susy::Photon*>   rho_photons;
			//std::vector<MyEMObject> myEMObject_sorted;
			//std::vector<MyEMObject> myEMObject; // applied all DR condition
			//std::vector<susy::Photon*>   ele_photons; 			// same as tight except for nPixelSeeds > 0
			//std::vector<susy::Photon*>   fake_photons; 			// same as tight except for reversing either trackIso or sigmaIetaIeta
			//std::vector<susy::CaloJet*>  caloJets;


			/////////////////////////////////////////////////////////////////
			//////////////////////////// PHOTONS ////////////////////////////
			/////////////////////////////////////////////////////////////////
			//    ____  _           _
			//   |  _ \| |__   ___ | |_ ___  _ __  ___
			//   | |_) | '_ \ / _ \| __/ _ \| '_ \/ __|
			//   |  __/| | | | (_) | || (_) | | | \__ \
			//   |_|   |_| |_|\___/ \__\___/|_| |_|___/
			//


		int phoi = 0;
		if(printLevel > 0) std::cout << "Find loose and tight photons in the event." << std::endl;
		std::map<TString, std::vector<susy::Photon> >::iterator phoMap = event->photons.find("photons");
		if(phoMap != event->photons.end()) {
			for(std::vector<susy::Photon>::iterator it = phoMap->second.begin(); it != phoMap->second.end(); it++) {
				float MVAcor = it->MVAregEnergyAndErr.first/it->momentum.E();

                        mvaCor_plot_unsliced->Fill(it->MVAregEnergyAndErr.first);
                        normal_plot_unsliced->Fill(it->momentum.E());

			if(jentry<50){
				printf("%i %i %i: pho %i\t Et %.2f\t Eta  %.2f\t E %f\t MVA_E %f\t MVA_E_err %f\n",
						event->runNumber,event->luminosityBlockNumber,event->eventNumber,
						phoi,
						it->momentum.Et(),
						it->caloPosition.Eta(),
						it->momentum.E(),
						it->MVAregEnergyAndErr.first,
						it->MVAregEnergyAndErr.second	);
			}
			phoi++;
//run lumi event photon pt , eta, mva uncorr energy and mva corr energy

				/*bool tightSusy11Cut = is_tight_combIso_BFrancis(
				 //useMVAphoP?it-> MVAcorrMomentum.Et():it->momentum.Et(),//it->momentum.Et(),
				 ((useMVAphoP?MVAcor:1.0)*it->momentum).Et(),
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
				 bool loose11Cut = is_vloose_pho(
				 //useMVAphoP?it-> MVAcorrMomentum.Et():it->momentum.Et(),//it->momentum.Et(),
				 ((useMVAphoP?MVAcor:1.0)*it->momentum).Et(),
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

				 bool tightVG11Cut = is_tight_ManiTripathi(
				 //useMVAphoP?it-> MVAcorrMomentum.Et():it->momentum.Et(),//it->momentum.Et(),
				 ((useMVAphoP?MVAcor:1.0)*it->momentum).Et(),
				 it->caloPosition.Eta(),
				 it->trkSumPtHollowConeDR04,
				 it->ecalRecHitSumEtConeDR04,
				 it->hcalTowerSumEtConeDR04(),
				 it->hadronicOverEm,
				 it->sigmaIetaIeta,
				 it->sigmaIphiIphi,
				 it->r9,
				 it->nPixelSeeds,
				 event->rho25);

				 bool istight2012Cut = is_tight_2012(
				 //useMVAphoP?it-> MVAcorrMomentum.Et():it->momentum.Et(),//it->momentum.Et(),
				 ((useMVAphoP?MVAcor:1.0)*it->momentum).Et(),
				 it->caloPosition.Eta(),
				 it->chargedHadronIso,
				 it->neutralHadronIso,
				 it->photonIso,
				 it->hadTowOverEm,  //single tower, same cut though
				 it->sigmaIetaIeta,
				 it->sigmaIphiIphi,
				 it->passelectronveto, //replaces pixel seed veto
				 event->rho25);*/

				bool ismedium2012Cut = is_medium_2012(
													  //useMVAphoP?it-> MVAcorrMomentum.Et():it->momentum.Et(),//it->momentum.Et(),
													  ((useMVAphoP?MVAcor:1.0)*it->momentum).Et(),
													  it->caloPosition.Eta(),
													  it->chargedHadronIso,
													  it->neutralHadronIso,
													  it->photonIso,
													  it->hadTowOverEm,  //single tower, same cut though
													  it->sigmaIetaIeta,
													  it->sigmaIphiIphi,
													  it->passelectronveto, //replaces pixel seed veto
													  event->rho25);

				bool isloose2012Cut = is_loose_2012(
													//useMVAphoP?it-> MVAcorrMomentum.Et():it->momentum.Et(),//it->momentum.Et(),
													((useMVAphoP?MVAcor:1.0)*it->momentum).Et(),
													it->caloPosition.Eta(),
													it->chargedHadronIso,
													it->neutralHadronIso,
													it->photonIso,
													it->hadTowOverEm,  //single tower, same cut though
													it->sigmaIetaIeta,
													it->sigmaIphiIphi,
													it->passelectronveto, //replaces pixel seed veto
													event->rho25);

				bool isloose2012_pixelSeedVeto = is_loose_2012_PixelSeedVeto(
																			 ((useMVAphoP?MVAcor:1.0)*it->momentum).Et(),
																			 it->caloPosition.Eta(),
																			 it->chargedHadronIso,
																			 it->neutralHadronIso,
																			 it->photonIso,
																			 it->hadTowOverEm,  //single tower, same cut though
																			 it->sigmaIetaIeta,
																			 it->sigmaIphiIphi,
																			 it->nPixelSeeds,
																			 event->rho25);

				bool isloose2012_pixelSeedReq = is_loose_2012_PixelSeedReq(
																		   ((useMVAphoP?MVAcor:1.0)*it->momentum).Et(),
																		   it->caloPosition.Eta(),
																		   it->chargedHadronIso,
																		   it->neutralHadronIso,
																		   it->photonIso,
																		   it->hadTowOverEm,  //single tower, same cut though
																		   it->sigmaIetaIeta,
																		   it->sigmaIphiIphi,
																		   it->nPixelSeeds,
																		   event->rho25);

					//if((useMVAphoP?it-> MVAcorrMomentum.Et():it->momentum.Et()) < phoEtThresh1){ //if(it->momentum.Et() < phoEtThresh1){
				if( ((useMVAphoP?MVAcor:1.0)*it->momentum).Et() < phoEtThresh1){ //if(it->momentum.Et() < phoEtThresh1){
					selvar_pho_HE->Fill(it->hadronicOverEm);
					if(fabs(it->caloPosition.Eta())<1.4442) {
						selvar_pho_sinin_bar->Fill(it->sigmaIetaIeta);
						selvar_pho_sipip_bar->Fill(it->sigmaIphiIphi);
					}
					else if(fabs(it->caloPosition.Eta())>1.56 && fabs(it->caloPosition.Eta())<2.5) {
						selvar_pho_sinin_ec->Fill(it->sigmaIetaIeta);
						selvar_pho_sipip_ec->Fill(it->sigmaIphiIphi);
					}
					selvar_pho_nPixelSeeds->Fill(it->nPixelSeeds);
					selvar_pho_R9->Fill(it->r9);
				}//fill selvars
				selvar_pho_ChargeSafeEleVeto->Fill(it->passelectronveto?1:0);


					//if(loose11Cut) { loose_photons.push_back(&*it); }
				if(isloose2012Cut) {
						//if((useMVAphoP?it-> MVAcorrMomentum.Et():it->momentum.Et()) < phoEtThresh1){
					if( ((useMVAphoP?it->MVAregEnergyAndErr.first / it->momentum.E():1.0)*it->momentum).Et() < phoEtThresh1){ // if(it->momentum.Et() < phoEtThresh1){
						selvar_pho_TrkIsoDR04->Fill(it->trkSumPtHollowConeDR04);
						selvar_pho_EcalIsoDR04->Fill(it->ecalRecHitSumEtConeDR04);
						selvar_pho_HcalIsoDR04->Fill(it->hcalTowerSumEtConeDR04());
						selvar_pho_TrkIsoDR03->Fill(it->trkSumPtHollowConeDR04);
						selvar_pho_EcalIsoDR03->Fill(it->ecalRecHitSumEtConeDR04);
						selvar_pho_HcalIsoDR03->Fill(it->hcalTowerSumEtConeDR03());
						selvar_pho_PFcargedHadIso->Fill(it->chargedHadronIso);
						selvar_pho_PFneutralHadIso->Fill(it->neutralHadronIso);
						selvar_pho_PFphoIso->Fill(it->photonIso);
						selvar_pho_rho->Fill(event->rho25);
					}
				}
					//if(tightSusy11Cut) { tight_susy11_photons.push_back(&*it); }
					//if (tightVG11Cut) { tight_VG11_photons.push_back(&*it); }
				if(isloose2012Cut){
					loose_susy12_photons.push_back(&*it);
				}
				if(isloose2012_pixelSeedVeto){
					loose_susy12_photons_pixelSeedVeto.push_back(&*it);
				}
				if(isloose2012_pixelSeedReq){
					loose_susy12_photons_pixelSeedReq.push_back(&*it);
				}
				if(isloose2012_pixelSeedReq || isloose2012_pixelSeedVeto){
					loose_susy12_photons_NeglectpixelSeed.push_back(&*it);
				}

				if(ismedium2012Cut){
					medium_susy12_photons.push_back(&*it);
				}

			}// for all photon
		}// else
			// sort photons by Et
			// std::sort(loose_photons.begin(),loose_photons.end(),EtGreaterpho<susy::Photon>);
			//std::sort(tight_susy11_photons.begin(),tight_susy11_photons.end(),EtGreaterpho<susy::Photon>);
			//std::sort(loose_photons.begin(),loose_photons.end(),EtGreaterpho<susy::Photon>);
			//std::sort(tight_VG11_photons.begin(),tight_VG11_photons.end(),EtGreaterpho<susy::Photon>);
		std::sort(medium_susy12_photons.begin(),medium_susy12_photons.end(),EtGreaterpho<susy::Photon>);
		std::sort(loose_susy12_photons.begin(),loose_susy12_photons.end(),EtGreaterpho<susy::Photon>);
		std::sort(loose_susy12_photons_pixelSeedVeto.begin(),loose_susy12_photons_pixelSeedVeto.end(),EtGreaterpho<susy::Photon>);
		std::sort(loose_susy12_photons_pixelSeedReq.begin(),loose_susy12_photons_pixelSeedReq.end(),EtGreaterpho<susy::Photon>);
		std::sort(loose_susy12_photons_NeglectpixelSeed.begin(),loose_susy12_photons_NeglectpixelSeed.end(),EtGreaterpho<susy::Photon>);
		if(printLevel > 50) cout<<"e"<<endl;
			//remove_duplicate_photons(tight_susy11_photons);
			//remove_duplicate_photons(tight_VG11_photons);
			//remove_duplicate_photons(loose_photons);

		remove_duplicate_photons(loose_susy12_photons);
		remove_duplicate_photons(loose_susy12_photons_pixelSeedVeto);
		remove_duplicate_photons(loose_susy12_photons_pixelSeedReq);
		remove_duplicate_photons(loose_susy12_photons_NeglectpixelSeed);
		if(printLevel > 50) cout<<"f"<<endl;
		remove_duplicate_photons(medium_susy12_photons);
		if(printLevel > 50) cout<<"g"<<endl;

			//////////////////////////////////////////////////////////////////////////////
			//////////////////////// Set Which Kind of Photon You Use ////////////////////
			//////////////////////////////////////////////////////////////////////////////
			//use as (*p_photonVector)
		if(useSusyLoose_EleVeto) p_photonVector = &loose_susy12_photons;		//PhoPho with ele veto
		else if(useSusyLoose_PixelVeto) p_photonVector = &loose_susy12_photons_pixelSeedVeto; //PhoPho with pixel veto
		else if(useSusyLoose_PixelSeedMatch) p_photonVector = &loose_susy12_photons_pixelSeedReq; //EleEle
		else if(useSusyLoose_PS_ElePho) p_photonVector = &loose_susy12_photons_NeglectpixelSeed; //Ele+Pho
		else if(useSusyMedium_EleVeto) p_photonVector = &medium_susy12_photons; //Medium pho
		else p_photonVector = &loose_susy12_photons;		//default is Loose w/ ele veto
			//////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////
		if(printLevel > 10) cout<<"set pho pointer"<<endl;

			//	I want to set this after all the removing and sorting is done in case some of
			//	that messes with the address of the start of the vector.


			//fill photon dists.
		if ((*p_photonVector).size()>=2 ){
			float MVAcor0 = (*p_photonVector)[0]->MVAregEnergyAndErr.first/(*p_photonVector)[0]->momentum.E();
			float Et0 =  ((useMVAphoP?MVAcor0:1.0)*(*p_photonVector)[0]->momentum).Et();
				//float Et0 = useMVAphoP?(*p_photonVector)[0]->MVAcorrMomentum.Et():(*p_photonVector)[0]->momentum.Et();
			pho_Et_0->Fill(Et0);//look at pho0 with no pt cut. // pho_Et_0->Fill((*p_photonVector)[0]->momentum.Et());//look at pho0 with no pt cut.
			if (Et0 >= phoEtThresh0){ // if ((*p_photonVector)[0]->momentum.Et() >= phoEtThresh0){
					//float Et1 = useMVAphoP?(*p_photonVector)[1]->MVAcorrMomentum.Et():(*p_photonVector)[1]->momentum.Et();
				float MVAcor1 = (*p_photonVector)[1]->MVAregEnergyAndErr.first/(*p_photonVector)[1]->momentum.E();
				float Et1 =  ((useMVAphoP?MVAcor1:1.0)*(*p_photonVector)[1]->momentum).Et();
				pho_Et_1->Fill(Et1); //pho_Et_1->Fill((*p_photonVector)[1]->momentum.Et());
				if ((*p_photonVector).size()>2 && Et1 >= phoEtThresh1) //if ((*p_photonVector).size()>2 && (*p_photonVector)[1]->momentum.Et() >= phoEtThresh1)
						//float MVAcor2 = (*p_photonVector)[2]->MVAregEnergyAndErr.first/(*p_photonVector)[2]->momentum.E();
					pho_Et_2->Fill( ((useMVAphoP?(*p_photonVector)[2]->MVAregEnergyAndErr.first/(*p_photonVector)[2]->momentum.E():1.0)*(*p_photonVector)[2]->momentum).Et() ); //pho_Et_2->Fill((*p_photonVector)[2]->momentum.Et());
					//pho_Et_2->Fill( useMVAphoP?(*p_photonVector)[2]->MVAcorrMomentum.Et():(*p_photonVector)[2]->momentum.Et() );
			}
		}
		selvar_pho_nPho->Fill((*p_photonVector).size());
		for(std::vector<susy::Photon*>::iterator it = (*p_photonVector).begin(); it != (*p_photonVector).end(); it++) {
			float Eti = ((useMVAphoP?(*it)->MVAregEnergyAndErr.first / (*it)->momentum.E():1.0)*(*it)->momentum).Et();
				//float Eti = (useMVAphoP?(*it)-> MVAcorrMomentum.Et():(*it)->momentum.Et());
			if(Eti < phoEtThresh1){//if((*it)->momentum.Et() < phoEtThresh1){
				selvar_pho_Et->Fill(Eti);//selvar_pho_Et->Fill((*it)->momentum.Et());
				selvar_pho_Eta ->Fill((*it)->caloPosition.Eta());
				selvar_pho_Phi->Fill(fabs((*it)->caloPosition.Phi()));
			}
		}

			//probe the event
		if(printLevel > 0 && event->eventNumber == ((unsigned int)probeevent)){
			printf("probe: nPho_tight %li nPho_loose %li\n",(*p_photonVector).size(),loose_susy12_photons.size());
			if(event->eventNumber == ((unsigned int)probeevent) && loose_susy12_photons.size() >= 2)
				printf("tight: phoEt[0] %f, phoEt[1] %f phoEta[0] %.2f, phoEta[1] %.2f\n",
					   ((useMVAphoP?loose_susy12_photons[0]->MVAregEnergyAndErr.first / loose_susy12_photons[0]->momentum.E():1.0)*loose_susy12_photons[0]->momentum).Et(),
					   ((useMVAphoP?loose_susy12_photons[1]->MVAregEnergyAndErr.first / loose_susy12_photons[1]->momentum.E():1.0)*loose_susy12_photons[1]->momentum).Et(),
					   loose_susy12_photons[0]->momentum.Eta(),
					   loose_susy12_photons[1]->momentum.Eta() );
			/* useMVAphoP?loose_susy12_photons[0]->MVAcorrMomentum.Et():loose_susy12_photons[0]->momentum.Et(),
			 useMVAphoP?loose_susy12_photons[1]->MVAcorrMomentum.Et():loose_susy12_photons[1]->momentum.Et(),
			 useMVAphoP?loose_susy12_photons[0]->MVAcorrMomentum.Eta():loose_susy12_photons[0]->momentum.Eta(),
			 useMVAphoP?loose_susy12_photons[1]->MVAcorrMomentum.Eta():loose_susy12_photons[1]->momentum.Eta() );*/
			if(event->eventNumber == ((unsigned int)probeevent) && (*p_photonVector).size() >= 2)
				printf("tight: phoEt[0] %f, phoEt[1] %f phoEta[0] %.2f, phoEta[1] %.2f\n",
					   ((useMVAphoP?(*p_photonVector)[0]->MVAregEnergyAndErr.first / (*p_photonVector)[0]->momentum.E():1.0)*(*p_photonVector)[0]->momentum).Et(),
					   ((useMVAphoP?(*p_photonVector)[1]->MVAregEnergyAndErr.first / (*p_photonVector)[1]->momentum.E():1.0)*(*p_photonVector)[1]->momentum).Et(),
					   (*p_photonVector)[0]->momentum.Eta(),
					   (*p_photonVector)[1]->momentum.Eta()  );
			/* useMVAphoP?(*p_photonVector)[0]->MVAcorrMomentum.Et():(*p_photonVector)[0]->momentum.Et(),
			 useMVAphoP?(*p_photonVector)[1]->MVAcorrMomentum.Et():(*p_photonVector)[1]->momentum.Et(),
			 useMVAphoP?(*p_photonVector)[0]->MVAcorrMomentum.Eta():(*p_photonVector)[0]->momentum.Eta(),
			 useMVAphoP?(*p_photonVector)[1]->MVAcorrMomentum.Eta():(*p_photonVector)[1]->momentum.Eta()  );*/
			printf("I see thresholds: %f, %f\n",phoEtThresh0,phoEtThresh1);
		}

			//////////////////make two photon cuts.///////////////////////
			//if (loose_susy12_photons.size()<2 ||
			//(((useMVAphoP?loose_susy12_photons[0]->MVAregEnergyAndErr.first / loose_susy12_photons[0]->momentum.E():1.0)*loose_susy12_photons[0]->momentum).Et()) < phoEtThresh0 ||
			//(((useMVAphoP?loose_susy12_photons[1]->MVAregEnergyAndErr.first / loose_susy12_photons[1]->momentum.E():1.0)*loose_susy12_photons[1]->momentum).Et()) < phoEtThresh1) continue;

			//(useMVAphoP?loose_susy12_photons[0]->MVAcorrMomentum.Et():loose_susy12_photons[0]->momentum.Et()) < phoEtThresh0 ||
			//(useMVAphoP?loose_susy12_photons[1]->MVAcorrMomentum.Et():loose_susy12_photons[1]->momentum.Et()) < phoEtThresh1) continue;//firing all of the time.

			//	If we're doing ele-pho, Require one to have ps and the other not to.
		if(useSusyLoose_PS_ElePho){
			if(((*p_photonVector)[0]->nPixelSeeds == 0 && (*p_photonVector)[1]->nPixelSeeds == 0 ) ||
			   ((*p_photonVector)[0]->nPixelSeeds > 0 && (*p_photonVector)[1]->nPixelSeeds > 0 ) ||
			   (*p_photonVector)[0]->nPixelSeeds < 0 || (*p_photonVector)[1]->nPixelSeeds < 0  ) continue; //xyxyx
			Counters["have 1 ele, 1 pho candidate"]++;
		}

		if ((*p_photonVector).size()<2 ||
			(((useMVAphoP?(*p_photonVector)[0]->MVAregEnergyAndErr.first / (*p_photonVector)[0]->momentum.E():1.0)*(*p_photonVector)[0]->momentum).Et()) < phoEtThresh0 ||
			(((useMVAphoP?(*p_photonVector)[1]->MVAregEnergyAndErr.first / (*p_photonVector)[1]->momentum.E():1.0)*(*p_photonVector)[1]->momentum).Et()) < phoEtThresh1 ||
			isSameObject((*p_photonVector)[0]->momentum,(*p_photonVector)[1]->momentum) ) continue;
			//(useMVAphoP?(*p_photonVector)[0]->MVAcorrMomentum.Et():(*p_photonVector)[0]->momentum.Et()) < phoEtThresh0 ||
			//(useMVAphoP?(*p_photonVector)[1]->MVAcorrMomentum.Et():(*p_photonVector)[1]->momentum.Et()) < phoEtThresh1) continue;
		Counters["have 2 loose photons"]++;
		if(printLevel > 0 && event->eventNumber == ((unsigned int)probeevent)) cout<<"probe passes Two Loose Photons"<<endl;
			//Counters["have 2 tight photons"]++;

		TLorentzVector p0, p1, gg;
		p0 = (useMVAphoP?(*p_photonVector)[0]->MVAregEnergyAndErr.first / (*p_photonVector)[0]->momentum.E():1.0)*(*p_photonVector)[0]->momentum;
		p1 = (useMVAphoP?(*p_photonVector)[1]->MVAregEnergyAndErr.first / (*p_photonVector)[1]->momentum.E():1.0)*(*p_photonVector)[1]->momentum;
			//p0 = useMVAphoP?(*p_photonVector)[0]->MVAcorrMomentum:(*p_photonVector)[0]->momentum;
			//p1 = useMVAphoP?(*p_photonVector)[1]->MVAcorrMomentum:(*p_photonVector)[1]->momentum;
		gg = p0+p1;
		float mgg = gg.M();//mass is fine
		float ptgg = gg.Pt();//pt is fine
		float mtgg = sqrt(gg.E()*gg.E() - gg.Perp2());

			//		int ipho = 0;//loop over the first four photons.
			//		for(std::vector<susy::Photon*>::iterator it = loose_photons.begin();it != loose_photons.end() && ipho<2; it++)
		for(std::vector<susy::Photon*>::iterator it = (*p_photonVector).begin(); it != (*p_photonVector).end(); it++) {
			vPho +=      (useMVAphoP?(*it)->MVAregEnergyAndErr.first / (*it)->momentum.E():1.0)*(*it)->momentum;
			myPhotonST+= ((useMVAphoP?(*it)->MVAregEnergyAndErr.first / (*it)->momentum.E():1.0)*(*it)->momentum).Et();
				//vPho +=      useMVAphoP?(*it)->MVAcorrMomentum:(*it)->momentum;
				//myPhotonST+= useMVAphoP?(*it)->MVAcorrMomentum.Et():(*it)->momentum.Et();
				//			ipho++;
		}

			/////////////////////////////////////////////////////////////////
			//////////////////////// FIND THE PRIMARY VERTEX ////////////////
			/////////////////////////////////////////////////////////////////
			//    ____       _                             __     __        _
			//   |  _ \ _ __(_)_ __ ___   __ _ _ __ _   _  \ \   / /__ _ __| |_ _____  __
			//   | |_) | '__| | '_ ` _ \ / _` | '__| | | |  \ \ / / _ \ '__| __/ _ \ \/ /
			//   |  __/| |  | | | | | | | (_| | |  | |_| |   \ V /  __/ |  | ||  __/>  <
			//   |_|   |_|  |_|_| |_| |_|\__,_|_|   \__, |    \_/ \___|_|   \__\___/_/\_\
			//                                      |___/

		if(printLevel > 0) std::cout << "Find primary vertex in the event." << std::endl;
			//		TVector3* primVtx = &(event->vertices[0].position);
		TVector3* primVtx = 0;
		if(event->vertices.size() > 0) primVtx = &(event->vertices[0].position);
		if(primVtx) h_vtxZ_unsliced->Fill(primVtx->Z());
		h_bsZ_unsliced->Fill(event->beamSpot.Z());

		for(std::vector<susy::Vertex>::iterator it = event->vertices.begin(); it != event->vertices.end(); it++) {
			if(ok_vtx(it)) good_vtx.push_back(&*it);

			selvar_vtx_isFake->Fill(it->isFake());
			selvar_vtx_ndof->Fill(it->ndof);
			selvar_vtx_chi2->Fill(it->chi2);
			selvar_vtx_trackSize->Fill(it->tracksSize);
			selvar_vtx_rho->Fill(std::sqrt((it->position.X())*(it->position.X()) + (it->position.Y())*(it->position.Y())));
			selvar_vtx_Zpos->Fill(std::fabs(it->position.Z()));

		}
		int nPVertex = good_vtx.size();
		selvar_vtx_nVtx->Fill(nPVertex);
		if(nPVertex<1){
			if(printLevel > 1) cout<<"No Good Vertex!!!!  Run: "<<event->runNumber<<"  Event: "<<event->eventNumber<<endl;
			continue;
		}
		if(printLevel > 0 && event->eventNumber == ((unsigned int)probeevent)) cout<<"pass Vertex"<<endl;
		Counters["pass a primary vertex reqirement"]++;

			/////////////////////////////////////////////////////////////////
			//////////////////////// FIND MUONS  ////////////////////////////
			/////////////////////////////////////////////////////////////////
			//    __  __
			//   |  \/  |_   _  ___  _ __  ___
			//   | |\/| | | | |/ _ \| '_ \/ __|
			//   | |  | | |_| | (_) | | | \__ \
			//   |_|  |_|\__,_|\___/|_| |_|___/
			//
			//may need primVtx->Z()
			//float myMuSumEt = 0;
		if(printLevel > 1) cout << "Find Muons in the event." << endl;
			//susy::MuonCollection muonC = event->muons["muidGlobalMuonPromptTight"];//xxx
			//muonCollectionTags
			//for(std::vector<susy::Muon>::iterator it_Mu = muonC.begin(); it_Mu != muonC.end(); it_Mu++)
			////for(std::vector<susy::Muon>::iterator it_Mu = event->muons.begin(); it_Mu != event->muons.end(); it_Mu++)

		std::map<TString, std::vector<susy::Muon> >::iterator muMap = event->muons.find("muons");
			//std::map<TString, std::vector<susy::Muon> >::iterator muMap = event->muons.find("muidGlobalMuonPromptTight");
			//this is probably not the right thing to look for..ask.
			//in the ntuplizer, the keys are in muonCollectionTags_.
		if(muMap != event->muons.end()) {
				//loop over muons collection
			for(std::vector<susy::Muon>::iterator it_Mu= muMap->second.begin(); it_Mu!= muMap->second.end(); it_Mu++) {


				/*for(std::vector<susy::Muon>::iterator it_Mu = event->muonv.begin(); it_Mu != event->muonv.end(); it_Mu++)
				 std::map<TString,UChar_t>::iterator idPair = it_Mu->idPairs.find("muidGlobalMuonPromptTight");
				 if(idPair == it_Mu->idPairs.end()) continue;
				 if(int(idPair->second) == 0) continue;
				 */

				bool same_pho_object = false;
				for(std::vector<susy::Photon*>::iterator p_it = (*p_photonVector).begin(); p_it != (*p_photonVector).end(); p_it++) {
					same_pho_object |= isSameObject(it_Mu->momentum,(*p_it)->momentum);//dR indep of e scale
						//same_pho_object |= isSameObject(it_Mu->momentum,useMVAphoP?(*p_it)->MVAcorrMomentum:(*p_it)->momentum);
				}
				if(same_pho_object) continue;//forbid mu that are pho.

				if(printLevel > 1) cout<<"looping over muon collection"<<endl;

				susy::Track& innerTrack = event->tracks[it_Mu->trackIndex];
				if(ok_muon_DMoris(it_Mu,innerTrack)){
					Muons.push_back(&*it_Mu);
					myLeptonST += (it_Mu)->momentum.Et();
						//myMuSumET += (it_Mu)->momentum.Et();
					vL += (it_Mu)->momentum;
				}
				selvar_mu_Et->Fill(it_Mu->momentum.Pt());
				selvar_mu_Eta->Fill(it_Mu->momentum.Eta());
				selvar_mu_Phi->Fill(fabs(it_Mu->momentum.Phi()));
					//	float combIsoPF=( it_Mu->sumChargedHadronPt04 + std::max(0.,it_Mu->sumNeutralHadronEt04+it_Mu->sumPhotonEt04-0.5*it_Mu->sumPUPt04) );
					//			selvar_mu_relIso->Fill(combIsoPF / it_Mu->momentum.Pt());
				selvar_mu_relIso->Fill(	((it_Mu->ecalIsoR03 + it_Mu->hcalIsoR03 + it_Mu->trackIsoR03)/(it_Mu->momentum.Pt() )));
				selvars_mu_emEnergy->Fill(it_Mu->emEnergy);
				selvars_mu_hadEnergy->Fill(it_Mu->hadEnergy);
				selvar_mu_d0->Fill(innerTrack.d0());
				selvar_mu_dz_pVtxZ->Fill(fabs(event->tracks[it_Mu->trackIndex].vertex.Z() - primVtx->Z()));
				selvars_mu_dZ->Fill(innerTrack.dz());
				selvars_mu_chi2OverNdof->Fill(innerTrack.normChi2());
				selvars_mu_nValidTrackerHits->Fill(it_Mu->nValidTrackerHits);
				selvars_mu_combinedTrackIndex->Fill(it_Mu->combinedTrackIndex);
				selvars_mu_numberOfValidPixelHits->Fill(innerTrack.numberOfValidPixelHits);
				selvars_mu_numberOfValidMuonHits ->Fill(it_Mu->nValidMuonHits);
				selvars_mu_isGlobalMuon->Fill(it_Mu->isGlobalMuon());
				selvars_mu_isPFMuon->Fill(it_Mu->isPFMuon());

			}//end it_Mu muon loop
		}
			//sort Muons by Pt
		std::sort(Muons.begin(), Muons.end(), EtGreater<susy::Muon>);
		if(printLevel>1)cout<<"Muons size= "<<Muons.size()<<endl;

		selvar_mu_nmu->Fill(Muons.size());
		float Mleplep = -1;
		if(Muons.size() >=2) Mleplep = (Muons[0]->momentum + Muons[1]->momentum).M();


			/////////////////////////////////////////////////////////////////
			//////////////////////// FIND pfElectrons  //////////////////////
			/////////////////////////////////////////////////////////////////
			//    _____ _           _
			//   | ____| | ___  ___| |_ _ __ ___  _ __  ___
			//   |  _| | |/ _ \/ __| __| '__/ _ \| '_ \/ __|
			//   | |___| |  __/ (__| |_| | | (_) | | | \__ \
			//   |_____|_|\___|\___|\__|_|  \___/|_| |_|___/
			//
			//float myEleSumEt = 0;
		std::map<TString, std::vector<susy::Electron> >::iterator eleMap = event->electrons.find("gsfElectrons");
		if(eleMap != event->electrons.end()) {
				//loop over electron collection
			for(std::vector<susy::Electron>::iterator it_Ele = eleMap->second.begin(); it_Ele != eleMap->second.end(); it_Ele++) {
				if(printLevel > 1) cout<<"looping over electron collection"<<endl;

				bool same_pho_object = false;
				for(std::vector<susy::Photon*>::iterator p_it = (*p_photonVector).begin(); p_it != (*p_photonVector).end(); p_it++) {
					float t_dEta = it_Ele->momentum.Eta() - (*p_it)->momentum.Eta();
						//float t_dEta = it_Ele->momentum.Eta() - (useMVAphoP?(*p_it)->MVAcorrMomentum.Eta():(*p_it)->momentum.Eta());
						//float t_dEta = it_Ele->momentum.Eta() - (*p_it)->momentum.Eta();
					float t_dPhi = TVector2::Phi_mpi_pi(it_Ele->momentum.Phi() - (*p_it)->momentum.Phi());
						//float t_dPhi = TVector2::Phi_mpi_pi(it_Ele->momentum.Phi() - (useMVAphoP?(*p_it)->MVAcorrMomentum.Phi():(*p_it)->momentum.Phi()) );
						//float t_dPhi = TVector2::Phi_mpi_pi(it_Ele->momentum.Phi() - (*p_it)->momentum.Phi());
					float t_dR = std::sqrt(t_dEta*t_dEta + t_dPhi*t_dPhi);
						//same_pho_object |= isSameObject(it_Ele->momentum,(*p_it)->momentum);//dR05 cut
						//same_pho_object |= (t_dR < 0.1 && !(*p_it)->passelectronveto);
						//if it's a photon here it's already passed the passelectronveto so that'd never fire
					same_pho_object |= t_dR < 0.1;


				}
				if(same_pho_object) continue;//forbid ele that are pho.


				float relIso=(it_Ele->chargedHadronIso + it_Ele->neutralHadronIso + it_Ele->photonIso)/it_Ele->momentum.Pt();
				selvar_ele_Et->Fill(it_Ele->momentum.Pt());
				selvar_ele_Eta->Fill(it_Ele->momentum.Eta());
				selvar_ele_Phi->Fill(fabs(it_Ele->momentum.Phi()));
				selvar_ele_relIso->Fill(relIso);

				if(ok_ele(it_Ele)){
					pfEles.push_back(&*it_Ele);
					myLeptonST += (it_Ele)->momentum.Et();
						//myEleSumEt += (it_Ele)->momentum.Et();
					vL += (it_Ele)->momentum;
				}
			}//end it_Ele electron loop
			std::sort(pfEles.begin(), pfEles.end(), EtGreater<susy::Electron>); //sort pfEles by Pt
			if(printLevel>1)cout<<"pfEles size= "<<pfEles.size()<<endl;
		}//end eleMap
		selvar_ele_nele->Fill(pfEles.size());
		if(Muons.size()<2 && pfEles.size() >=2){
			Mleplep = (pfEles[0]->momentum + pfEles[1]->momentum).M();
		}

			/////////////////////////////////////////////////////////////////
			//////////////////////// FIND JETS  /////////////////////////////
			/////////////////////////////////////////////////////////////////
			//        _      _
			//       | | ___| |_ ___
			//    _  | |/ _ \ __/ __|
			//   | |_| |  __/ |_\__ \
			//    \___/ \___|\__|___/
			//
		float HT_all = 0;
		float LHT_all = 0;//non-B hadronic scalar sum
		float BT_all = 0;
		float Bness1 = 0;
			//float SumCSV = 0;
		float BT[3] = {0,0,0};//L,M,T
		float MHT_all = 0;
		float MHT_x_all =0;
		float MHT_y_all =0;

		if(printLevel > 3) std::cout << "Find pfJets in the event." << std::endl;

		std::map<TString,susy::PFJetCollection>::iterator pfJets_it = event->pfJets.find("ak5");
		if(pfJets_it != event->pfJets.end()){

			susy::PFJetCollection& jetColl = pfJets_it->second;

			for(std::vector<susy::PFJet>::iterator it = jetColl.begin();it != jetColl.end(); it++) {

				std::map<TString,Float_t>::iterator s_it = it->jecScaleFactors.find("L1FastL2L3");
				if (s_it == it->jecScaleFactors.end()) {
					std::cout << "JEC is not available for this jet!!!" << std::endl;
					continue;
				}
				float scale = s_it->second;
				TLorentzVector corrP4 = scale * it->momentum;
				selvar_jet_Et   ->Fill(corrP4.Pt());
				selvar_jet_Eta  ->Fill(corrP4.Phi());
				selvar_jet_Phi  ->Fill(std::fabs(corrP4.Phi()));

				if(corrP4.Pt() < 30) continue;
				if(std::fabs(corrP4.Eta()) > 2.6) continue; //AN_11_409

				float uncorrE = it->momentum.E();
				float NeutralHadronFraction = (it->neutralHadronEnergy)/uncorrE;
				float NeutralEMFraction =(it->neutralEmEnergy)/uncorrE;
				float ChargedHadronFraction = (it->chargedHadronEnergy)/uncorrE;
				float ChargedEMFraction = (it->chargedEmEnergy)/uncorrE;

				selvars_jet_nConstituents->Fill(it->nConstituents);
				selvars_jet_NeutralHadFrac ->Fill(NeutralHadronFraction);
				selvars_jet_NeutralEMFrac  ->Fill(NeutralEMFraction);
				selvars_jet_ChargedHadFrac ->Fill(ChargedHadronFraction);
				selvars_jet_ChargedEMFrac  ->Fill(ChargedEMFraction);
				selvars_jet_chargedHadMult ->Fill(it->chargedHadronMultiplicity);
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

					///Anti-select tight photons
				bool same_pho_object = false; //exclude the two photons you use for analysis.
					//				int np=0;
				for(std::vector<susy::Photon*>::iterator p_it = (*p_photonVector).begin(); p_it != (*p_photonVector).end(); p_it++) {
						//					if (np >=2) break;
						//same_pho_object |= isSameObject(corrP4,useMVAphoP?(*p_it)->MVAcorrMomentum:(*p_it)->momentum );
					same_pho_object |= isSameObject(corrP4,(*p_it)->momentum);
						//					np++;
				}

				bool same_emobject = false;
				for(std::vector<susy::Electron*>::iterator m_it = pfEles.begin(); m_it != pfEles.end(); m_it++) {
					same_emobject |= isSameObject(corrP4,(*m_it)->momentum);
				}

				bool same_muon = false;
				for(std::vector<susy::Muon*>::iterator m_it = Muons.begin(); m_it != Muons.end(); m_it++){
					same_muon |= isSameObject(corrP4,(*m_it)->momentum);
				}

				if((!same_emobject) && (!same_muon) && (!same_pho_object)){
					ra3_pfjets.push_back(&*it);
					vH += corrP4;
					HT_all += corrP4.Pt();
					MHT_x_all -= corrP4.Px();
					MHT_y_all -= corrP4.Py();
						//SumCSV+=it->bTagDiscriminators[5];
					Bness1+=pow(it->bTagDiscriminators[5],0.20);//could also use 0.25
					if(it->bTagDiscriminators[5] > 0.244) BT_all += corrP4.Pt();//if CSVL, add to BT, this is the first and only time it's filled
					else LHT_all += corrP4.Pt(); //light flavor tagged

					if(it->bTagDiscriminators[5] > 0.898) BT[2] += corrP4.Pt();//BT_tight
					else if(it->bTagDiscriminators[5] > 0.679) BT[1] += corrP4.Pt();//BT_medium
					else if(it->bTagDiscriminators[5] > 0.244) BT[0] += corrP4.Pt();//BT_loose
				}

			}// pfjet
		}//if
		selvar_jet_njet->Fill(ra3_pfjets.size());
		std::sort(ra3_pfjets.begin(),ra3_pfjets.end(),EtGreater<susy::PFJet>);
		MHT_all = std::sqrt(MHT_x_all*MHT_x_all + MHT_y_all*MHT_y_all);


			/////////////////////////////////////////////////////////////////
			//////////////////////// FIND B-JETS  ///////////////////////////
			/////////////////////////////////////////////////////////////////
			//    ____            _      _
			//   | __ )          | | ___| |_ ___
			//   |  _ \ _____ _  | |/ _ \ __/ __|
			//   | |_) |_____| |_| |  __/ |_\__ \
			//   |____/       \___/ \___|\__|___/
			//
		for(std::vector<susy::PFJet*>::iterator it = ra3_pfjets.begin();	it != ra3_pfjets.end(); it++) { //error
			if((*it)->bTagDiscriminators[5] > 0.898) pfBJetsTight.push_back(*it);//CSV medium working point
			if((*it)->bTagDiscriminators[5] > 0.679) pfBJetsMedium.push_back(*it);//CSV medium working point
			if((*it)->bTagDiscriminators[5] > 0.244) pfBJetsLoose.push_back(*it);//CSV loose working point
				//https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagPerformanceOP#B_tagging_Operating_Points_for_5
			selvar_btag_csv->Fill((*it)->bTagDiscriminators[5]);
		}
		selvar_btag_nbtag->Fill(pfBJetsMedium.size());

		if(printLevel > 4) std::cout << "Try to calculate bestMjj." << std::endl;
		float bestMjj = -1;
		int tempsize_1 = ra3_pfjets.size();
		if(tempsize_1 >=2){
				//for(std::vector<susy::PFJet*>::iterator it = ra3_pfjets.begin(); it+1 != ra3_pfjets.end(); it++)
				//for(std::vector<susy::PFJet*>::iterator it2 = ra3_pfjets.begin()+1;        it != ra3_pfjets.end(); it++)
			for(int i=0;i<tempsize_1-1;i++){
				for(int j=i+1; j<tempsize_1;j++){
					float mmm = (ra3_pfjets[i]->momentum+ra3_pfjets[j]->momentum).M();
					if(fabs(mmm-mHiggs) < fabs(bestMjj-mHiggs)) bestMjj = mmm;
				}
			}
		}
		if(printLevel > 4) std::cout << "Try to calculate bestMbj." << std::endl;
		float bestMbb = -1;
		/*if(pfBJetsLoose.size() >=2){
		 for(std::vector<susy::PFJet*>::iterator it = pfBJetsLoose.begin(); it+1 != pfBJetsLoose.end(); it++) {
		 for(std::vector<susy::PFJet*>::iterator it2 = pfBJetsLoose.begin()+1; it != pfBJetsLoose.end(); it++) {
		 if(fabs(((*it)->momentum+(*it2)->momentum).M()-mHiggs) < fabs(bestMbb-mHiggs)) bestMbb = ((*it)->momentum+(*it2)->momentum).M();
		 }
		 }
		 } */
		tempsize_1= pfBJetsLoose.size();
		if(tempsize_1 >=2){
			for(int i=0;i<tempsize_1-1;i++){
				for(int j=i+1; j<tempsize_1;j++){
					float mmm = (pfBJetsLoose[i]->momentum+pfBJetsLoose[j]->momentum).M();
					if(fabs((pfBJetsLoose[i]->momentum+pfBJetsLoose[j]->momentum).M()-mHiggs) < fabs(bestMbb-mHiggs)) bestMbb = (pfBJetsLoose[i]->momentum+pfBJetsLoose[j]->momentum).M();
					if(mmm<10) printf("info: see low mbb mass=%f, nJ=%i, E1 %.2f E2 %.2f dphi %f \n",mmm,tempsize_1,pfBJetsLoose[i]->momentum.E(),pfBJetsLoose[j]->momentum.E(),pfBJetsLoose[i]->momentum.Phi()-pfBJetsLoose[j]->momentum.Phi());
				}
			}
		}


			//////////////////////// GET MET  ///////////////////////////
		if(printLevel > 3) std::cout << "Select which met will be used in the event." << std::endl;
		std::map<TString, susy::MET>::iterator met_it = event->metMap.find("pfMet");
		if(met_it == event->metMap.end()) {
			std::cout << "MET map is not available!!!" << std::endl;
			continue;
		}
		susy::MET* pfmet = &(met_it->second);
		bool spillguts = false;
		if(printLevel > 3 && event->eventNumber == ((unsigned int)probeevent)){
			cout<<"pass Met Map"<<endl;
			spillguts = true;
			printf("Running JEC_MET on the probe event\n");
		}
			//float metX = MHT_x_all - vPho.X() - vL.X();
			//float metY = MHT_y_all - vPho.Y() - vL.Y();
		float metX,metY;
		float corrmet = JEC_MET(pfmet,ra3_pfjets,metX,metY,spillguts);
		corrmet = PhoEC_MET(corrmet,*p_photonVector,metX,metY,spillguts);
			//float metPhi = TMath::ATan(metY/metX); // This looks just plain wrong.
			//float metPhi = TMath::ATan(metY/metX); // This looks just plain wrong. xxx
		float metPhi = TMath::ATan(metY/metX);
		Counters["has met map"]++;
		if(printLevel > 3 && event->eventNumber == ((unsigned int)probeevent)) cout<<"probe: corrmet "<<corrmet<<" uncorrmet "<< pfmet->met() <<endl;

		myST = HT_all + myPhotonST + corrmet;// + myLeptonST;
		vMET.SetPtEtaPhiM(corrmet,0,metPhi,0);

		if(printLevel > 3) std::cout << "boo1" << std::endl;

			//                   __    __        __          __    __        __          __    __
			//                  (//    \\)    __(//   __    (//    \\)    __(//   __    (//    \\)
			//                  /"      / __  \\)"    \\)_  /"      / __  \\)"    \\)_  /"      / __
			//                '|-..__..-''\_''-.\__..-''  '|-..__..-''\_''-.\__..-''  '|-..__..-''\
			//                (\\  \_    _(\\      _/     (\\  \_    _(\\      _/     (\\  \_    //)
			//                 ""  (\\  //)""     //)      ""  (\\  //)""     //)      ""  (\\   ""
			//                      ""  ""        ""            ""  ""        ""            ""
			//////////////////////////////////////////////////////////////////////
			//////////////////////// READY FOR PHYSICS ///////////////////////////
			//////////////////////////////////////////////////////////////////////


		for(std::vector<susy::Photon*>::iterator it = (*p_photonVector).begin(); it != (*p_photonVector).end(); it++) {
			mvaCor_plot->Fill((*it)->MVAregEnergyAndErr.first);
			normal_plot->Fill((*it)->momentum.E());
		}

	}//end for every event.
	normal_plot->Write();
	mvaCor_plot->Write();
	normal_plot_unsliced->Write();
	mvaCor_plot_unsliced->Write();

	f.Close();
	cout<<"iclosed "<<endl;
	cout<<"total events "<<nentries<<endl;


		// end of event loop and print summary
}


bool SusyEventAnalyzer_shruti::ok_vtx(std::vector<susy::Vertex>::iterator it){
	float vtx_rho = std::sqrt((it->position.X())*(it->position.X()) + (it->position.Y())*(it->position.Y()));
	if(it->isFake() || //it->chi2 == 0.f) || (it->tracksSize == 0) ||  //this disagrees with D.Morris. DM: Vtx_it->isFake() ||
	   (it->ndof <= 4.f) ||
	   (std::fabs(it->position.Z()) >= 24.f) || //vtx absZ > 24
	   (vtx_rho >= 2.f)) return false;
	return true;
}//end ok_vtx

void SusyEventAnalyzer_shruti::MakeHistSet(TH1F** h, string prefix, int nbins, float lower, float upper){
	string names[nPhoMassAndBkgDists];
	string titles[nPhoMassAndBkgDists];
	string descriptions[nPhoMassAndBkgDists] = {"Lower Side Band",
		"in Higgs Tag Region","Upper Side Band","Background to Higgs Tag Region",
		"Background Subtracted Higgs Tag Region","Lower Side Band","Upper Side Band",
		"Lower to Upper sideband ratio","Tag to background ratio"};
	for (int i = 0; i<nPhoMassAndBkgDists; i++) {
		names[i] = "h";
		names[i]+= prefix+"_"+s_MassBkgDists[i];
		titles[i] = prefix+" "+descriptions[i];
	}
	for (int i=0; i < nPhoMassAndBkgDists; i++) {
		h[i] = new TH1F(RandomString(6),"",nbins,lower,upper);
		NameHist(h[i],(char*)names[i].c_str(),(char*)titles[i].c_str());
	}
}// end MakeHistSet

void SusyEventAnalyzer_shruti::MakeHistSet(TH1F** h, string prefix, int nbins, float*  bins){
	string names[nPhoMassAndBkgDists];
	string titles[nPhoMassAndBkgDists];
	string descriptions[nPhoMassAndBkgDists] = {"Lower Side Band",
		"in Higgs Tag Region","Upper Side Band","Background to Higgs Tag Region",
		"Background Subtracted Higgs Tag Region","Lower Side Band","Upper Side Band",
		"Lower to Upper sideband ratio","Tag to background ratio"};
	for (int i = 0; i<nPhoMassAndBkgDists; i++) {
		names[i] = "h";
		names[i]+= prefix+"_"+s_MassBkgDists[i];
		titles[i] = prefix+" "+descriptions[i];
	}
	for (int i=0; i < nPhoMassAndBkgDists; i++) {
		h[i] = new TH1F(RandomString(6),"",nbins,bins);
		NameHist(h[i],(char*)names[i].c_str(),(char*)titles[i].c_str());
	}
}// end MakeHistSet

	//Photon Energy Corrections
float SusyEventAnalyzer_shruti::PhoEC_MET(float oldcorrmet,std::vector<susy::Photon*> photons, float &corrX, float &corrY, bool Debug_noisily){
		//add adjust MET for Photon Energy corrections
	if(!useMVAphoP) return oldcorrmet; //if we choose to not correct photons, just return.

	float corr_px = 0;
	float corr_py = 0;
	float uncorr_px = 0;
	float uncorr_py = 0;
	if(Debug_noisily) printf("Entering PhoEC_MET. JECmet = %.3f\n",oldcorrmet);
	if(Debug_noisily) printf("npho: %li\n",photons.size());
	for(std::vector<susy::Photon*>::iterator p_it = photons.begin(); p_it != photons.end(); p_it++) {
			//for(std::vector<susy::PFJet*>::iterator m_it = ra3_pfjets.begin();
			//       m_it != ra3_pfjets.end(); m_it++) {

		if(Debug_noisily) printf("PhoEt: %.2f\n", (*p_it)->momentum.Et());
		corr_px += ((useMVAphoP?(*p_it)->MVAregEnergyAndErr.first / (*p_it)->momentum.E():1.0)*(*p_it)->momentum).Px();
		corr_py += ((useMVAphoP?(*p_it)->MVAregEnergyAndErr.first / (*p_it)->momentum.E():1.0)*(*p_it)->momentum).Py();
			//corr_px += (*p_it)->MVAcorrMomentum.Px();
			//corr_py += (*p_it)->MVAcorrMomentum.Py();
		uncorr_px += (*p_it)->momentum.Px();
		uncorr_py += (*p_it)->momentum.Py();
		if(Debug_noisily) printf("corr_px %.2f y %.2f uncorr_px %.2f y %.2f\n",corr_px,corr_py,uncorr_px,uncorr_py);
	}

	float dx = corr_px - uncorr_px;
	float dy = corr_py - uncorr_py;
	corrX -= dx;
	corrY -= dy;
		//float corrmet = std::sqrt((met_x - corrmet_x)*(met_x - corrmet_x) + (met_y - corrmet_y)*(met_y - corrmet_y));
	float corrmet = std::sqrt(corrX*corrX + corrY*corrY);
	if(Debug_noisily) printf("In Total dx %.2f dy %.2f UCmet_x%.2f UCmet_y %.2f corrmet %.3f\n",dx,dy,corrX+dx,corrY+dy,corrmet);
	return corrmet;
}//end PhoEC_MET

float SusyEventAnalyzer_shruti::JEC_MET(susy::MET* pfmet,std::vector<susy::PFJet*> ra3_pfjets,float &corrX, float &corrY, bool Debug_noisily){
		//add adjust MET for JEC.
	float corr_px = 0;
	float corr_py = 0;
	float uncorr_px = 0;
	float uncorr_py = 0;
	if(Debug_noisily) printf("Entering JEC_MET. UCmet = %.3f\n",pfmet->met());
	if(Debug_noisily) printf("njets: %li\n",ra3_pfjets.size());
	for(std::vector<susy::PFJet*>::iterator m_it = ra3_pfjets.begin();
		m_it != ra3_pfjets.end(); m_it++) {

		std::map<TString,Float_t>::iterator s_it = (*m_it)->jecScaleFactors.find("L1FastL2L3");
		if (s_it == (*m_it)->jecScaleFactors.end()) {
			std::cout << "JEC is not available for this jet!!!" << std::endl;
			continue;
		}

		std::map<TString,Float_t>::iterator s_it_v1 = (*m_it)->jecScaleFactors.find("L2L3");
		if (s_it_v1 == (*m_it)->jecScaleFactors.end()) {
			std::cout << "JEC is not available for this jet!!!" << std::endl;
			continue;
		}

		float scale = s_it->second;
		float scale_v1 = s_it_v1->second;
		float scale_l1fastl2l3_minus_l1fast = 1.0+(scale - scale/scale_v1);
		if(Debug_noisily) printf("scale %f scale_v1 %f scale_l1fastl2l3_minus_l1fast %f \n",scale,scale_v1,scale_l1fastl2l3_minus_l1fast);
		if(Debug_noisily) printf("JetEt: %.2f\n", (*m_it)->momentum.Et());

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
	corrX = met_x - corrmet_x;
	corrY = met_y - corrmet_y;
	float corrmet = std::sqrt((met_x - corrmet_x)*(met_x - corrmet_x) + (met_y - corrmet_y)*(met_y - corrmet_y));
	if(Debug_noisily) printf("In Total corrmet_x %.2f y %.2f met_x%.2f y %.2f corrmet %.3f\n",corrmet_x,corrmet_y,met_x,met_y,corrmet);
	return corrmet;
}//end JEC_MET


	//use this one!
bool SusyEventAnalyzer_shruti::ok_ele(std::vector<susy::Electron>::iterator it_Ele){ //Dave Moris
	if(!it_Ele->isPF() and !it_Ele->passingMvaPreselection()) return false;
	float Iso=it_Ele->chargedHadronIso + it_Ele->neutralHadronIso + it_Ele->photonIso;
	float pt=it_Ele->momentum.Pt();
	if(it_Ele->momentum.Eta()>2.6) return false;
	if(pt<15) return false;
	if(Iso/pt>0.2) return false;
	return true;
}

bool SusyEventAnalyzer_shruti::ok_ele_AN_11_409(std::vector<susy::Electron>::iterator it_Ele, susy::Track& innerTrack, float pVtx_Z){
		//if(!it_Ele->isPF() and !it_Ele->passingMvaPreselection()) return false;
	float pt=it_Ele->momentum.Pt();
	if(pt<10) return false;
		//      float Iso= it_Ele->ecalIsoR03 + it_Ele->hcalIsoR03 + it_Ele->trackIsoR03;
	float Iso= it_Ele->dr03TkSumPt+ it_Ele->dr03EcalRecHitSumEt+ it_Ele->dr03HcalDepth1TowerSumEt+ it_Ele->dr03HcalDepth2TowerSumEt;
	float eleSCEta = it_Ele->momentum.Eta(); // this is probably wrong
	if(eleSCEta>2.5 || (eleSCEta > 1.4442 && eleSCEta < 1.566)) return false;
	if(Iso/pt>=0.2) return false; //RelIso
	float d0 = innerTrack.d0(); //no! d0 of the pv!
	float dZ = innerTrack.dz(); //no! dZ of the pv!
	if(std::fabs(d0) >= 0.2) return false;    //require |d0 (beam spot)| < 0.02
	if(std::fabs(dZ - pVtx_Z) >= 1) return false;     //|ele.vertex.Z - pVtx_Z | < 1cm
		//require number of lost hits <= 1, I don't k
//	now how to implement this!!!!!!! xxx
	return true;
}



	//use this one!
bool SusyEventAnalyzer_shruti::ok_muon_DMoris(std::vector<susy::Muon>::iterator it_Mu,susy::Track& innerTrack){
	if(!it_Mu->isGlobalMuon()) return false; //Brian Francis agrees
	if(!it_Mu->isPFMuon()) return false; //Brian Francis agrees

	float pt = it_Mu->momentum.Pt();
		//      float combIso=(it_Mu->ecalIsoR03 + it_Mu->hcalIsoR03 + it_Mu->trackIsoR03);
	float combIsoPF=( it_Mu->sumChargedHadronPt04 + std::max(0.,it_Mu->sumNeutralHadronEt04+it_Mu->sumPhotonEt04-0.5*it_Mu->sumPUPt04) );
		//      float relIso = combIso/pt;
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
}//end ok_muon_DMoris



bool SusyEventAnalyzer_shruti::ok_muon_AN_11_409(std::vector<susy::Muon>::iterator it,susy::Track& combinedTrack, float pVtx_Z){ //probably inner track instead
		//get combinedTrack using       susy::Track& combinedTrack = event->tracks[it->combinedTrackIndex];
		//I don't see where
	if(!it->isGlobalMuon()) return false;
	if(!it->isPFMuon()) return false;
		//      std::map<TString,UChar_t>::iterator idPair = it->idPairs.find("muidGlobalMuonPromptTight");
	if (
		//(idPair == it->idPairs.end()) ||
		//(int(idPair->second) == 0) ||
		(std::fabs(it->momentum.Eta()) > 2.4) || //dm: >2.6
		(it->momentum.Pt() < 10) ||
		(it->nValidTrackerHits < 11) ||
		(it->combinedTrackIndex < 0) ||
		((it->ecalIsoR03 + it->hcalIsoR03 + it->trackIsoR03)/(it->momentum.Pt()) >= 0.15) || //relIso > 0.15
		//(it->emEnergy > 4.0) ||
		//      (it->hadEnergy > 6.0)
		fabs(combinedTrack.vertex.Z() - pVtx_Z) >= 1.0 //1 cm //Brain Francis and Dave Moris don't use this.
		) return false;
	float normChi2 = combinedTrack.chi2 / combinedTrack.ndof;
	float d0 = std::abs(d0correction(event->beamSpot,combinedTrack));

		//      if(normChi2 >= 10.f || d0 >= 0.2 ) return false;
	if(d0 >= 0.2 ) return false; //assuming that sais d0 < 0.02cm.
	else return true;
}//end ok_muon_AN_11_409

bool SusyEventAnalyzer_shruti::ok_muon(std::vector<susy::Muon>::iterator it){ //Yu Feng
		//      std::map<TString,UChar_t>::iterator idPair = it->idPairs.find("muidGlobalMuonPromptTight");
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

