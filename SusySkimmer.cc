/*
WARNING!! YOU DON'T WANT TO USE THIS. IF YOU'RE LOOKING FOR A SKIMMER, GO USE SusyMainAna.cc and turn on the filter
pay attention to lines such as if ( !(Med12phoM01>100) ) continue;
*/

#define SusySkimmer_cxx

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#include <utility>

#include "SusySkimmer.h"
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

using namespace std;
using namespace params;


template<typename T> bool EtGreater(const T* p1, const T* p2) {
	return (p1->momentum.Et() > p2->momentum.Et());
}


void SusySkimmer::InitializePerEvent() {

}


bool SusySkimmer::isSameObject(TLorentzVector& p1, TLorentzVector& p2) {

	float dEta = p1.Eta() - p2.Eta();
	float dPhi = TVector2::Phi_mpi_pi(p1.Phi() - p2.Phi());
	float dR = std::sqrt(dEta*dEta + dPhi*dPhi);
	if(dR < 0.5) return true;
	return false;
}//dR05 cut


float SusySkimmer::d0correction(TVector3& beamSpot, susy::Track& track) const {

	float d0 = track.d0() - beamSpot.X()*std::sin(track.phi()) + beamSpot.Y()*std::cos(track.phi());
	return d0;
}

	//float SusySkimmer::d0correction_(TVector3& beamSpot, susy::Track& track){
	//	float d0 = track.d0() - beamSpot.X()*std::sin(track.phi()) + beamSpot.Y()*std::cos(track.phi());
	//	return d0;
	//}



bool SusySkimmer::PassTrigger(TString path) {
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


bool SusySkimmer::isfarFromPhotons(TLorentzVector& lep, std::vector<susy::Photon*> & photons){
	bool isFar = true;
	for(std::vector<susy::Photon*>::iterator it = photons.begin(); it != photons.end(); it++) {
		TLorentzVector ltmp = (*it)->momentum;
		isFar &= ! SusySkimmer::isSameObject(lep,ltmp);
	}
	return isFar;
}


bool SusySkimmer::PassTriggers() {
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

typedef std::map<string,TH1F*> LabelHist;
	//typedef std::map<string,LabelHist> Label2Hist;

typedef std::map<string,TH1F**> LabelHistArr;
	//typedef std::map<string,LabelHistArr> Label2HistArr;

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
        //cout<<"enter remove_duplicate_photons. Size = "<<photons.size()<<endl;
        //cout<<"photon end: "<<*photons.end()<<" i_p1+1: "<<*(i_p1+1)<<endl;
        int size = photons.size();
        while(I_p1+1 < size){
        //while(i_p1+1 != photons.end()){
                bool match_found = false;
                //cout<<"phoA. i="<<I_p1<<" "<<*i_p1<<endl;
                TLorentzVector p1 = (*i_p1)->momentum;
                std::vector<susy::Photon*>::iterator i_p2 = i_p1+1; int I_p2 = I_p1+1;
                while(I_p2 < size){ //increments to the terminator, then does not terminate.
                //while(i_p2 != photons.end()){ //increments to the terminator, then does not terminate.
                        //cout<<"phoB, i= "<<I_p2<<" "<<*i_p2<<endl;
                        TLorentzVector p2 = (*i_p2)->momentum;
                        //cout<<"rem4"<<endl;
                        if (dR(p1,p2)<0.6 || dPhi(p1,p2) < 0.05 ) {
                                std::vector<susy::Photon*>::iterator temp = i_p2+1;
                                i_p2 = photons.erase(i_p2);//this is supposed to return the next element but does not.
                                //cout<<"found match phoB new address: "<<*i_p2<<endl; 
                                i_p2 = temp;
                                //cout<<"after =temp, address: "<<*i_p2<<endl;
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

void SusySkimmer::Loop() {

//	string s_forTopo[nEventTopologies];
//	s_forTopo[0]="";
//	for (int iTopo=1; iTopo<nEventTopologies; iTopo++){
//		s_forTopo[iTopo]=string("for ")+s_EventTopology[iTopo];
//	}

	cout<<"hello world"<<endl;
	printLevel = 0;
	if (fChain == 0) return;

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
		//	for (int iTopo=0; iTopo<nEventTopologies; iTopo++) {
		//		addCounter(Counters,Counter_order,string("are in tag region")+s_forTopo[iTopo]);
		//		addCounter(Counters,Counter_order,string("are in sb region")+s_forTopo[iTopo]);
		//		addCounter(Counters,Counter_order,string("are in usb region")+s_forTopo[iTopo]);
		//		addCounter(Counters,Counter_order,string("are in lsb region")+s_forTopo[iTopo]);
		//	}

		//	TH1I *lsb_int = new TH1I("lsb_int","lower side band integrals",nEventTopologies,0,nEventTopologies);
		//	TH1I *usb_int = new TH1I("usb_int","lower side band integrals",nEventTopologies,0,nEventTopologies);
		//order:
		//keeps the order of the s_EventTopology array in params.

		//	int nFiltered = 0;
		//	TTree* filterTree = 0;
		//	cout << "enableFilter is set to "<<enableFilter<<endl;
		//	if (enableFilter){
		//		enableFilter = false;
		//		cout << "setting it to false"<<endl;
		//	}

		//	if(enableFilter) {
		//		cout << "Making Filter File"<<endl;
		//		TFile* filterFile = new TFile(outroot_data.c_str(),"RECREATE");
		//		filterTree = (TTree*) fChain->GetTree()->CloneTree(0);
		//		filterTree->SetAutoSave();
		//	}
	cout<<"trying to open flatsikim file"<<endl;
	//TFile flatskim("diphoFlatSkim_20k_MC.root","RECREATE");
	TFile flatskim("diphoFlatSkim_MC_350_225.root","RECREATE");
	flatskim.cd();
	TTree* flatskimtree = new TTree("flatskim","");
	cout<<"opened flatsikim file"<<endl;
	
	ofstream eventlist;
        eventlist.open ("ntuplized_trip_eventlist.txt");//everything passing the ntuplizer. 
	ofstream eventlist2;
        eventlist2.open ("ntuplized_passingTrip_eventlist.txt");//passing the ntuplizer and also passing the cuts in this context. 

	Int_t     run;
    ULong_t   evnt;
    Int_t     lumi;


		//Photon Varriables
	Int_t nPho;
	Float_t phoE[4];
	Float_t phoPt[4];
	Float_t phoEta[4];
	Float_t phoSCEta[4];
	Float_t phoPhi[4];
	Float_t phoHE[4];
	Float_t phoR9[4];
	Float_t phoSinin[4];
	Float_t phoSipip[4];
	Int_t phoNPixelSeed[4];
	Int_t rho;
	Float_t phoTIso04[4];
	Float_t phoEIso04[4];
	Float_t phoHIso04[4];
	Float_t phoTIso03[4];
	Float_t phoEIso03[4];
	Float_t phoHIso03[4];
	Float_t phoPFchargedHad[4];
	Float_t phoPFneutralHad[4];
	Float_t phoPFphoIso[4];
	Float_t phoSusySumIso[4];//save sum iso vars,
	Float_t phoTIso04_corr[4];//save rho corrected iso vars for vg11
	Float_t phoEIso04_corr[4];
	Float_t phoHIso04_corr[4];
	Float_t phoTIso03_corr[4];//save rho corrected iso vars for as used in SUS-12-018
	Float_t phoEIso03_corr[4];
	Float_t phoHIso03_corr[4];
	Int_t phoisTight_sus[4];
	Int_t phoisTight_Med12[4];
	Int_t phoisBar[4];
	Int_t phoisEC[4];
	Float_t phoM01;
	Float_t phoM02;
	Float_t phoM12;
	Float_t phoPt01;
	Float_t phoPt02;
	Float_t phoPt12;
		//save a conversion bit

		//Medium 2012 photon lists.
		//Photon Varriables
	Int_t nMed12pho;
	Float_t Med12phoE[4];
	Float_t Med12phoPt[4];
	Float_t Med12phoEta[4];
	Float_t Med12phoSCEta[4];
	Float_t Med12phoPhi[4];
	Float_t Med12phoHE[4];
	Float_t Med12phoR9[4];
	Float_t Med12phoSinin[4];
	Float_t Med12phoSipip[4];
	Int_t Med12phoNPixelSeed[4];
//	Int_t rho;
	Float_t Med12phoTIso04[4];
	Float_t Med12phoEIso04[4];
	Float_t Med12phoHIso04[4];
	Float_t Med12phoTIso03[4];
	Float_t Med12phoEIso03[4];
	Float_t Med12phoHIso03[4];
	Float_t Med12phoPFchargedHad[4];
	Float_t Med12phoPFneutralHad[4];
	Float_t Med12phoPFphoIso[4];
	Float_t Med12phoSusySumIso[4];//save sum iso vars,
	Float_t Med12phoTIso04_corr[4];//save rho corrected iso vars for vg11
	Float_t Med12phoEIso04_corr[4];
	Float_t Med12phoHIso04_corr[4];
	Float_t Med12phoTIso03_corr[4];//save rho corrected iso vars for as used in SUS-12-018
	Float_t Med12phoEIso03_corr[4];
	Float_t Med12phoHIso03_corr[4];
	Int_t Med12phoisTight_sus[4];
	Int_t Med12phoisBar[4];
	Int_t Med12phoisEC[4];
	Float_t Med12phoM01;
	Float_t Med12phoM02;
	Float_t Med12phoM12;
	Float_t Med12phoPt01;
	Float_t Med12phoPt02;
	Float_t Med12phoPt12;

		//SusyStar Photons
	Int_t nsusPho;
	Float_t susphoE[4];
	Float_t susphoPt[4];
	Float_t susphoEta[4];
	Float_t susphoSCEta[4];
	Float_t susphoPhi[4];
	Float_t susphoHE[4];
	Float_t susphoR9[4];
	Float_t susphoSinin[4];
	Float_t susphoSipip[4];
	Int_t susphoNPixelSeed[4];
	Float_t susphoTIso04[4];
	Float_t susphoEIso04[4];
	Float_t susphoHIso04[4];
	Float_t susphoTIso03[4];
	Float_t susphoEIso03[4];
	Float_t susphoHIso03[4];
	Float_t susphoPFchargedHad[4];
	Float_t susphoPFneutralHad[4];
	Float_t susphoPFphoIso[4];
	Float_t susphoSusySumIso[4];//save sum iso vars,
	Float_t susphoTIso04_corr[4];//save rho corrected iso vars for VG11
	Float_t susphoEIso04_corr[4];
	Float_t susphoHIso04_corr[4];
	Float_t susphoTIso03_corr[4];//save rho corrected iso vars for as used in SUS-12-018
	Float_t susphoEIso03_corr[4];
	Float_t susphoHIso03_corr[4];
		//Int_t susphoisTight_sus[4];
	Int_t susphoisTight_Med12[4];
	Int_t susphoisBar[4];
	Int_t susphoisEC[4];
	Float_t susphoM01;
	Float_t susphoM02;
	Float_t susphoM12;
	Float_t susphoPt01;
	Float_t susphoPt02;
	Float_t susphoPt12;


		//ele vars
	Int_t nEle;
	Float_t eleE[4];
	Float_t elePt[4];
	Float_t eleEta[4];
//	Float_t eleSCEta[4];
	Float_t elePhi[4];
	Float_t eleSumPFIso[4];
	Float_t eleSumIsoDR03[4];
	Float_t eleMt[4];
	Float_t eleM01;
		//	Float_t eleM02;
		//	Float_t eleM12;

		//muon vars
	Int_t nMu;
	Float_t muE[4];
	Float_t muPt[4];
	Float_t muEta[4];
	Float_t muPhi[4];
	Float_t muSumPFIso[4];
	Float_t muSumIsoDR03[4];
	Float_t muMt[4];
	Float_t muM01;
		//	Float_t muM02;
		//	Float_t muM12;

		//jet vars
	Int_t nJet;
	Float_t jetPt[4];
	Float_t jetE[4];
	Float_t jetEta[4];
	Float_t jetPhi[4];
		//	Float_t jetEnScale[4];

	Float_t jetM01;
	Float_t jetM02;
	Float_t jetM03;
	Float_t jetM12;
	Float_t jetM13;
	Float_t jetM23;
	Float_t HT;
	Float_t csv[4];
	Int_t nbtags;
		//MET
	Float_t met;
	Float_t metPhi;
	Float_t MHT;
	Float_t ST;

	cout<<"branches declared"<<endl;

	flatskimtree->Branch("run",&run,"run/I");
	flatskimtree->Branch("evnt",&evnt,"evnt/l");
	flatskimtree->Branch("lumi",&lumi,"lumi/I");
	
	flatskimtree->Branch("nPho",&nPho,"nPho/I");
	flatskimtree->Branch("phoE",phoE,"phoE[4]/F");
	flatskimtree->Branch("phoPt",phoPt,"phoPt[4]/F");
	flatskimtree->Branch("phoEta",phoEta,"phoEta[4]/F");
	flatskimtree->Branch("phoSCEta",phoSCEta,"phoSCEta[4]/F");
	flatskimtree->Branch("phoPhi",phoPhi,"phoPhi[4]/F");
	flatskimtree->Branch("phoHE",phoHE,"phoHE[4]/F");
	flatskimtree->Branch("phoR9",phoR9,"phoR9[4]/F");
	flatskimtree->Branch("phoSinin",phoSinin,"phoSinin[4]/F");
	flatskimtree->Branch("phoSipip",phoSipip,"phoSipip[4]/F");
	flatskimtree->Branch("phoNPixelSeed",phoNPixelSeed,"phoNPixelSeed[4]/I");
	flatskimtree->Branch("rho",&rho,"rho/I");
	flatskimtree->Branch("phoTIso04",phoTIso04,"phoTIso04[4]/F");
	flatskimtree->Branch("phoEIso04",phoEIso04,"phoEIso04[4]/F");
	flatskimtree->Branch("phoHIso04",phoHIso04,"phoHIso04[4]/F");
	flatskimtree->Branch("phoTIso03",phoTIso03,"phoTIso03[4]/F");
	flatskimtree->Branch("phoEIso03",phoEIso03,"phoEIso03[4]/F");
	flatskimtree->Branch("phoHIso03",phoHIso03,"phoHIso03[4]/F");
	flatskimtree->Branch("phoPFchargedHad",phoPFchargedHad,"phoPFchargedHad[4]/F");
	flatskimtree->Branch("phoPFneutralHad",phoPFneutralHad,"phoPFneutralHad[4]/F");
	flatskimtree->Branch("phoPFphoIso",phoPFphoIso,"phoPFphoIso[4]/F");
	flatskimtree->Branch("phoSusySumIso",phoSusySumIso,"phoSusySumIso[4]/F");
	flatskimtree->Branch("phoTIso04_corr",phoTIso04_corr,"phoTIso04_corr[4]/F");
	flatskimtree->Branch("phoEIso04_corr",phoEIso04_corr,"phoEIso04_corr[4]/F");
	flatskimtree->Branch("phoHIso04_corr",phoHIso04_corr,"phoHIso04_corr[4]/F");
	flatskimtree->Branch("phoTIso03_corr",phoTIso03_corr,"phoTIso03_corr[4]/F");
	flatskimtree->Branch("phoEIso03_corr",phoEIso03_corr,"phoEIso03_corr[4]/F");
	flatskimtree->Branch("phoHIso03_corr",phoHIso03_corr,"phoHIso03_corr[4]/F");
	flatskimtree->Branch("phoisTight_sus",&phoisTight_sus,"phoisTight_sus[4]/I");
	flatskimtree->Branch("phoisTight_Med12",&phoisTight_Med12,"phoisTight_Med12[4]/I");
	flatskimtree->Branch("phoisBar",&phoisBar,"phoisBar[4]/I");
	flatskimtree->Branch("phoisEC",&phoisEC,"phoisEC[4]/I");
	flatskimtree->Branch("phoM01",&phoM01,"phoM01/F");
	flatskimtree->Branch("phoM02",&phoM02,"phoM02/F");
	flatskimtree->Branch("phoM12",&phoM12,"phoM12/F");
	flatskimtree->Branch("phoPt01",&phoPt01,"phoPt01/F");
	flatskimtree->Branch("phoPt02",&phoPt02,"phoPt02/F");
	flatskimtree->Branch("phoPt12",&phoPt12,"phoPt12/F");
		//med12 photons
	flatskimtree->Branch("nMed12pho",&nMed12pho,"nMed12pho/I");
	flatskimtree->Branch("Med12phoE",Med12phoE,"Med12phoE[4]/F");
	flatskimtree->Branch("Med12phoPt",Med12phoPt,"Med12phoPt[4]/F");
	flatskimtree->Branch("Med12phoEta",Med12phoEta,"Med12phoEta[4]/F");
	flatskimtree->Branch("Med12phoSCEta",Med12phoSCEta,"Med12phoSCEta[4]/F");
	flatskimtree->Branch("Med12phoPhi",Med12phoPhi,"Med12phoPhi[4]/F");
	flatskimtree->Branch("Med12phoHE",Med12phoHE,"Med12phoHE[4]/F");
	flatskimtree->Branch("Med12phoR9",Med12phoR9,"Med12phoR9[4]/F");
	flatskimtree->Branch("Med12phoSinin",Med12phoSinin,"Med12phoSinin[4]/F");
	flatskimtree->Branch("Med12phoSipip",Med12phoSipip,"Med12phoSipip[4]/F");
	flatskimtree->Branch("Med12phoNPixelSeed",Med12phoNPixelSeed,"Med12phoNPixelSeed[4]/I");
	flatskimtree->Branch("Med12phoTIso04",Med12phoTIso04,"Med12phoTIso04[4]/F");
	flatskimtree->Branch("Med12phoEIso04",Med12phoEIso04,"Med12phoEIso04[4]/F");
	flatskimtree->Branch("Med12phoHIso04",Med12phoHIso04,"Med12phoHIso04[4]/F");
	flatskimtree->Branch("Med12phoTIso03",Med12phoTIso03,"Med12phoTIso03[4]/F");
	flatskimtree->Branch("Med12phoEIso03",Med12phoEIso03,"Med12phoEIso03[4]/F");
	flatskimtree->Branch("Med12phoHIso03",Med12phoHIso03,"Med12phoHIso03[4]/F");
	flatskimtree->Branch("Med12phoPFchargedHad",Med12phoPFchargedHad,"Med12phoPFchargedHad[4]/F");
	flatskimtree->Branch("Med12phoPFneutralHad",Med12phoPFneutralHad,"Med12phoPFneutralHad[4]/F");
	flatskimtree->Branch("Med12phoPFphoIso",Med12phoPFphoIso,"Med12phoPFphoIso[4]/F");
	flatskimtree->Branch("Med12phoSusySumIso",Med12phoSusySumIso,"Med12phoSusySumIso[4]/F");
	flatskimtree->Branch("Med12phoTIso04_corr",Med12phoTIso04_corr,"Med12phoTIso04_corr[4]/F");
	flatskimtree->Branch("Med12phoEIso04_corr",Med12phoEIso04_corr,"Med12phoEIso04_corr[4]/F");
	flatskimtree->Branch("Med12phoHIso04_corr",Med12phoHIso04_corr,"Med12phoHIso04_corr[4]/F");
	flatskimtree->Branch("Med12phoTIso03_corr",Med12phoTIso03_corr,"Med12phoTIso03_corr[4]/F");
	flatskimtree->Branch("Med12phoEIso03_corr",Med12phoEIso03_corr,"Med12phoEIso03_corr[4]/F");
	flatskimtree->Branch("Med12phoHIso03_corr",Med12phoHIso03_corr,"Med12phoHIso03_corr[4]/F");
	flatskimtree->Branch("Med12phoisTight_sus",&Med12phoisTight_sus,"Med12phoisTight_sus[4]/I");
//	flatskimtree->Branch("Med12phoisTight_Med12",&Med12phoisTight_Med12,"Med12phoisTight_Med12[4]/I");
	flatskimtree->Branch("Med12phoisBar",&Med12phoisBar,"Med12phoisBar[4]/I");
	flatskimtree->Branch("Med12phoisEC",&Med12phoisEC,"Med12phoisEC[4]/I");
	flatskimtree->Branch("Med12phoM01",&Med12phoM01,"Med12phoM01/F");
	flatskimtree->Branch("Med12phoM02",&Med12phoM02,"Med12phoM02/F");
	flatskimtree->Branch("Med12phoM12",&Med12phoM12,"Med12phoM12/F");
	flatskimtree->Branch("Med12phoPt01",&Med12phoPt01,"Med12phoPt01/F");
	flatskimtree->Branch("Med12phoPt02",&Med12phoPt02,"Med12phoPt02/F");
	flatskimtree->Branch("Med12phoPt12",&Med12phoPt12,"Med12phoPt12/F");
		//SusyStarPhotons
	flatskimtree->Branch("nsusPho",&nsusPho,"nsusPho/I");
	flatskimtree->Branch("susphoE",susphoE,"susphoE[4]/F");
	flatskimtree->Branch("susphoPt",susphoPt,"susphoPt[4]/F");
	flatskimtree->Branch("susphoEta",susphoEta,"susphoEta[4]/F");
	flatskimtree->Branch("susphoSCEta",susphoSCEta,"susphoSCEta[4]/F");
	flatskimtree->Branch("susphoPhi",susphoPhi,"susphoPhi[4]/F");
	flatskimtree->Branch("susphoHE",susphoHE,"susphoHE[4]/F");
	flatskimtree->Branch("susphoR9",susphoR9,"susphoR9[4]/F");
	flatskimtree->Branch("susphoSinin",susphoSinin,"susphoSinin[4]/F");
	flatskimtree->Branch("susphoSipip",susphoSipip,"susphoSipip[4]/F");
	flatskimtree->Branch("susphoNPixelSeed",susphoNPixelSeed,"susphoNPixelSeed[4]/I");
	flatskimtree->Branch("susphoTIso04",susphoTIso04,"susphoTIso04[4]/F");
	flatskimtree->Branch("susphoEIso04",susphoEIso04,"susphoEIso04[4]/F");
	flatskimtree->Branch("susphoHIso04",susphoHIso04,"susphoHIso04[4]/F");
	flatskimtree->Branch("susphoTIso03",susphoTIso03,"susphoTIso03[4]/F");
	flatskimtree->Branch("susphoEIso03",susphoEIso03,"susphoEIso03[4]/F");
	flatskimtree->Branch("susphoHIso03",susphoHIso03,"susphoHIso03[4]/F");
	flatskimtree->Branch("susphoPFchargedHad",susphoPFchargedHad,"susphoPFchargedHad[4]/F");
	flatskimtree->Branch("susphoPFneutralHad",susphoPFneutralHad,"susphoPFneutralHad[4]/F");
	flatskimtree->Branch("susphoPFphoIso",susphoPFphoIso,"susphoPFphoIso[4]/F");
	flatskimtree->Branch("susphoSusySumIso",susphoSusySumIso,"susphoSusySumIso[4]/F");
	flatskimtree->Branch("susphoTIso04_corr",susphoTIso04_corr,"susphoTIso04_corr[4]/F");
	flatskimtree->Branch("susphoEIso04_corr",susphoEIso04_corr,"susphoEIso04_corr[4]/F");
	flatskimtree->Branch("susphoHIso04_corr",susphoHIso04_corr,"susphoHIso04_corr[4]/F");
	flatskimtree->Branch("susphoTIso03_corr",susphoTIso03_corr,"susphoTIso03_corr[4]/F");
	flatskimtree->Branch("susphoEIso03_corr",susphoEIso03_corr,"susphoEIso03_corr[4]/F");
	flatskimtree->Branch("susphoHIso03_corr",susphoHIso03_corr,"susphoHIso03_corr[4]/F");
		//flatskimtree->Branch("Med12phoisTight_sus",&Med12phoisTight_sus,"Med12phoisTight_sus[4]/I");
	flatskimtree->Branch("susphoisTight_Med12",&susphoisTight_Med12,"susphoisTight_Med12[4]/I");
	flatskimtree->Branch("susphoisBar",&susphoisBar,"susphoisBar[4]/I");
	flatskimtree->Branch("susphoisEC",&susphoisEC,"susphoisEC[4]/I");
	flatskimtree->Branch("susphoM01",&susphoM01,"susphoM01/F");
	flatskimtree->Branch("susphoM02",&susphoM02,"susphoM02/F");
	flatskimtree->Branch("susphoM12",&susphoM12,"susphoM12/F");
	flatskimtree->Branch("susphoPt01",&susphoPt01,"susphoPt01/F");
	flatskimtree->Branch("susphoPt02",&susphoPt02,"susphoPt02/F");
	flatskimtree->Branch("susphoPt12",&susphoPt12,"susphoPt12/F");

	flatskimtree->Branch("nEle",&nEle,"nEle/I");
	flatskimtree->Branch("eleE",eleE,"eleE[4]/F");
	flatskimtree->Branch("elePt",elePt,"elePt[4]/F");
	flatskimtree->Branch("eleEta",eleEta,"eleEta[4]/F");
	flatskimtree->Branch("elePhi",elePhi,"elePhi[4]/F");
	flatskimtree->Branch("eleSumPFIso",eleSumPFIso,"eleSumPFIso[4]/F");
	flatskimtree->Branch("eleSumIsoDR03",eleSumIsoDR03,"eleSumIsoDR03[4]/F");
	flatskimtree->Branch("eleMt",eleMt,"eleMt[4]/F");
	flatskimtree->Branch("eleM01",&eleM01,"eleM01/F");
	flatskimtree->Branch("nMu",&nMu,"nMu/I");
	flatskimtree->Branch("muE",muE,"muE[4]/F");
	flatskimtree->Branch("muPt",muPt,"muPt[4]/F");
	flatskimtree->Branch("muEta",muEta,"muEta[4]/F");
	flatskimtree->Branch("muPhi",muPhi,"muPhi[4]/F");
	flatskimtree->Branch("muSumPFIso",muSumPFIso,"muSumPFIso[4]/F");
	flatskimtree->Branch("muSumIsoDR03",muSumIsoDR03,"muSumIsoDR03[4]/F");
	flatskimtree->Branch("muMt",muMt,"muMt[4]/F");
	flatskimtree->Branch("muM01",&muM01,"muM01/F");
	flatskimtree->Branch("nJet",&nJet,"nJet/I");
	flatskimtree->Branch("jetPt",jetPt,"jetPt[4]/F");
	flatskimtree->Branch("jetE",jetE,"jetE[4]/F");
	flatskimtree->Branch("jetEta",jetEta,"jetEta[4]/F");
	flatskimtree->Branch("jetPhi",jetPhi,"jetPhi[4]/F");
	flatskimtree->Branch("jetM01",&jetM01,"jetM01/F");
	flatskimtree->Branch("jetM02",&jetM02,"jetM02/F");
	flatskimtree->Branch("jetM03",&jetM03,"jetM03/F");
	flatskimtree->Branch("jetM12",&jetM12,"jetM12/F");
	flatskimtree->Branch("jetM13",&jetM13,"jetM13/F");
	flatskimtree->Branch("jetM23",&jetM23,"jetM23/F");
	flatskimtree->Branch("HT",&HT,"HT/F");
	flatskimtree->Branch("csv",csv,"csv[4]/F");
	flatskimtree->Branch("nbtags",&nbtags,"nbtags/I");
	flatskimtree->Branch("met",&met,"met/F");
	flatskimtree->Branch("metPhi",&metPhi,"metPhi/F");
	flatskimtree->Branch("MHT",&MHT,"MHT/F");
	flatskimtree->Branch("ST",&ST,"ST/F");
		//Make store varriables.
		//Int_t Is_fake_pv[32];
		//mytree->Branch("b_Is_fake_pv", Is_fake_pv, "Is_fake_pv[32]/I");

		//	TBranch        *b_jetTrg;
		//	Int_t           jetTrg[52][14];
		//	fChain->SetBranchAddress("jetTrg", jetTrg, &b_jetTrg);


		// open hist file and define histograms
		//	TFile* fout = new TFile(plotsroot_data.c_str(),"RECREATE");
		//	fout->cd();
		//<td> int n_ff;</td>
		//	<td> TBranch  *b_n_ff;</td>
		//	<td> tNFF->SetBranchAddress("N_FF", &n_ff, &b_n_ff);</td>


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
	for (Long64_t jentry=0; jentry < processNEvents; jentry++) {
		//for (Long64_t jentry=0; jentry < 500; jentry++) { //master loop

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

		run = event->runNumber;
		evnt = event->eventNumber;
		lumi = event->luminosityBlockNumber;

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

		float myST = 0.0;
		float myPhotonST = 0.0;
		float myLeptonST = 0.0;

		std::vector<susy::Photon*>   loose_photons; // loose objects have all standard cuts except for isolation
		std::vector<susy::Photon*>   tight_susy11_photons; // tight objects hava isolation cuts applied on top of loose objects
		std::vector<susy::Photon*>   tight_susy11Star_photons; // tight objects hava isolation cuts applied on top of loose objects
		std::vector<susy::Photon*>   medium_susy12_photons; // tight objects hava isolation cuts applied on top of loose objects
		std::vector<susy::Photon*>   loose_susy12_photons; // tight objects hava isolation cuts applied on top of loose objects
		//std::vector<susy::Photon*>   tight_VG11_photons;
		//std::vector<susy::Photon*>*  p_photonVector;
		//std::vector<susy::Photon*>* p_photonVector = &tight_susy11_photons;
		//use as (*p_photonVector)
	
		std::vector<susy::PFJet*>    pfJets;
		std::vector<susy::PFJet*>    pfBJets;
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
			for(std::vector<susy::Photon>::iterator it = phoMap->second.begin();
				it != phoMap->second.end(); it++) {
				bool looseCut = is_vloose_pho(
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

				/*bool is_tightEg11_photons = is_tight_ManiTripathi(
				  it->momentum.Et(),
				  it->caloPosition.Eta(),
				  it->trkSumPtHollowConeDR04,
				  it->ecalRecHitSumEtConeDR04,
				  it->hcalTowerSumEtConeDR04(),
				  it->hadronicOverEm,
				  it->sigmaIetaIeta,
				  it->sigmaIphiIphi,
				  it->r9,
				  it->nPixelSeeds,
				  event->rho25);*/

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
                                                event->rho25);

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

				if(is_tightSusy_photons) { tight_susy11_photons.push_back(&*it); }
				if(is_tightStar_photons){ tight_susy11Star_photons.push_back(&*it); }
				//if(is_tightEg11_photons) { tightEg11_photons.push_back(&*it); }
				if(isloose2012Cut){ loose_susy12_photons.push_back(&*it); }
				if(ismedium2012Cut){ medium_susy12_photons.push_back(&*it);      }
				if(looseCut) { loose_photons.push_back(&*it); }
			}// for all photon
		} //end if pho map
		else continue; //else there are no photons
		std::sort(loose_photons.begin(),loose_photons.end(),EtGreater<susy::Photon>);
		remove_duplicate_photons(loose_photons);

		nPho = (int)loose_susy12_photons.size();
		if (((int)loose_photons.size())<2){
			cout<<"WARNING, less than two loose Photons, how is this possible?"<<endl;
			continue;
		}
		Counters["pass two loose photons"]++;
			//apply the Et threshold.
		if (loose_photons[0]->momentum.Et() < phoEtThresh0 || loose_photons[1]->momentum.Et() < phoEtThresh1) {
			continue;
		}
		Counters["pass 2 loose pho over thresh"]++;


		std::sort(tight_susy11_photons.begin(),tight_susy11_photons.end(),EtGreater<susy::Photon>);
		remove_duplicate_photons(tight_susy11_photons);

		std::sort(tight_susy11Star_photons.begin(),tight_susy11Star_photons.end(),EtGreater<susy::Photon>);
		remove_duplicate_photons(tight_susy11Star_photons);

		//std::sort(tightEg11_photons.begin(),tightEg11_photons.end(),EtGreater<susy::Photon>);
		//remove_duplicate_photons(tightEg11_photons);

		std::sort(medium_susy12_photons.begin(),medium_susy12_photons.end(),EtGreater<susy::Photon>);
		remove_duplicate_photons(medium_susy12_photons);   

		std::sort(loose_susy12_photons.begin(),loose_susy12_photons.end(),EtGreater<susy::Photon>); 
		remove_duplicate_photons(loose_susy12_photons);

		rho=event->rho25;

		for (int i=0; i<4; i++) {
			phoE[i]=-999.0;
			phoPt[i]=-999.0;
			phoEta[i]=-999.0;
			phoSCEta[i]=-999.0;
			phoPhi[i]=-999.0;
			phoHE[i]=-999.0;
			phoR9[i]=-999.0;
			phoSinin[i]=-999.0;
			phoSipip[i]=-999.0;
			phoNPixelSeed[i]=-999;
			phoTIso04[i]=-999.0;
			phoEIso04[i]=-999.0;
			phoHIso04[i]=-999.0;
			phoTIso03[i]=-999.0;
			phoEIso03[i]=-999.0;
			phoHIso03[i]=-999.0;
			phoPFchargedHad[i]=-999.0;
			phoPFneutralHad[i]=-999.0;
			phoPFphoIso[i]=-999.0;
			phoSusySumIso[i]=-999.0;//save sum iso vars,
			phoTIso04_corr[i]=-999.0;//save rho corrected iso vars for vg11
			phoEIso04_corr[i]=-999.0;
			phoHIso04_corr[i]=-999.0;
			phoTIso03_corr[i]=-999.0;//save rho corrected iso vars for as used in SUS-12-018
			phoEIso03_corr[i]=-999.0;
			phoHIso03_corr[i]=-999.0;
			phoisTight_sus[i]=-999;
			phoisTight_Med12[i]=-999;
			phoisBar[i]=-999;
			phoisEC[i]=-999;

				//Med12pho
			nMed12pho = -999;
			Med12phoE[i]=-999.0;
			Med12phoPt[i]=-999.0;
			Med12phoEta[i]=-999.0;
			Med12phoSCEta[i]=-999.0;
			Med12phoPhi[i]=-999.0;
			Med12phoHE[i]=-999.0;
			Med12phoR9[i]=-999.0;
			Med12phoSinin[i]=-999.0;
			Med12phoSipip[i]=-999.0;
			Med12phoNPixelSeed[i]=-999;
			Med12phoTIso04[i]=-999.0;
			Med12phoEIso04[i]=-999.0;
			Med12phoHIso04[i]=-999.0;
			Med12phoTIso03[i]=-999.0;
			Med12phoEIso03[i]=-999.0;
			Med12phoHIso03[i]=-999.0;
			Med12phoPFchargedHad[i]=-999.0;
			Med12phoPFneutralHad[i]=-999.0;
			Med12phoPFphoIso[i]=-999.0;
			Med12phoSusySumIso[i]=-999.0;//save sum iso vars,
			Med12phoTIso04_corr[i]=-999.0;//save rho corrected iso vars for vg11
			Med12phoEIso04_corr[i]=-999.0;
			Med12phoHIso04_corr[i]=-999.0;
			Med12phoTIso03_corr[i]=-999.0;//save rho corrected iso vars for as used in SUS-12-018
			Med12phoEIso03_corr[i]=-999.0;
			Med12phoHIso03_corr[i]=-999.0;
			Med12phoisTight_sus[i]=-999;
			Med12phoM01 = -999.0;
			Med12phoM02 = -999.0;
			Med12phoM12 = -999.0;
			Med12phoPt01 = -999.0;
			Med12phoPt02 = -999.0;
			Med12phoPt12 = -999.0;
			Med12phoisBar[i]=-999;
			Med12phoisEC[i]=-999;

			
				//susypho
			nsusPho = -999;
			susphoE[i]=-999.0;
			susphoPt[i]=-999.0;
			susphoEta[i]=-999.0;
			susphoSCEta[i]=-999.0;
			susphoPhi[i]=-999.0;
			susphoHE[i]=-999.0;
			susphoR9[i]=-999.0;
			susphoSinin[i]=-999.0;
			susphoSipip[i]=-999.0;
			susphoNPixelSeed[i]=-999;
			susphoTIso04[i]=-999.0;
			susphoEIso04[i]=-999.0;
			susphoHIso04[i]=-999.0;
			susphoTIso03[i]=-999.0;
			susphoEIso03[i]=-999.0;
			susphoHIso03[i]=-999.0;
			susphoPFchargedHad[i]=-999.0;
			susphoPFneutralHad[i]=-999.0;
			susphoPFphoIso[i]=-999.0;
			susphoSusySumIso[i]=-999.0;//save sum iso vars,
			susphoTIso04_corr[i]=-999.0;//save rho corrected iso vars for vg11
			susphoEIso04_corr[i]=-999.0;
			susphoHIso04_corr[i]=-999.0;
			susphoTIso03_corr[i]=-999.0;//save rho corrected iso vars for as used in SUS-12-018
			susphoEIso03_corr[i]=-999.0;
			susphoHIso03_corr[i]=-999.0;
			susphoisTight_Med12[i]=-999;
			susphoM01 = -999.0;
			susphoM02 = -999.0;
			susphoM12 = -999.0;
			susphoPt01 = -999.0;
			susphoPt02 = -999.0;
			susphoPt12 = -999.0;
			susphoisBar[i]=-999;
			susphoisEC[i]=-999;


			eleE[i]=-999.0;
			elePt[i]=-999.0;
			eleEta[i]=-999.0;
//			eleSCEta[i]=-999.0;
			elePhi[i]=-999.0;
			eleSumPFIso[i]=-999.0;
			eleSumIsoDR03[i]=-999.0;
			eleMt[i]=-999.0;
			muE[i]=-999.0;
			muPt[i]=-999.0;
			muEta[i]=-999.0;
			muPhi[i]=-999.0;
			muSumPFIso[i]=-999.0;
			muSumIsoDR03[i]=-999.0;
			muMt[i]=-999.0;
			jetPt[i]=-999.0;
			jetE[i]=-999.0;
			jetEta[i]=-999.0;
			jetPhi[i]=-999.0;
			csv[i]=-999.0;
			nEle = 0;
			nMu = 0;
			nJet = 0;
		}
		cout<<"L"<<endl;
			///////////////////////////////////////////////////////
			/////////////////FILL Loose Photons////////////////////
			///////////////////////////////////////////////////////
		if (nPho>=2 && loose_susy12_photons[0]->momentum.Et() > phoEtThresh0 && loose_susy12_photons[1]->momentum.Et() > phoEtThresh1) {
		int ipho = 0;//loop over the first four photons.
		for(std::vector<susy::Photon*>::iterator it = loose_susy12_photons.begin();it != loose_susy12_photons.end() && ipho<4; it++) {

			//bool is_tightSusy_photons = is_tight_susyStar(
			/*bool is_tightSusy_photons = is_tight_combIso_BFrancis(
								   (*it)->momentum.Et(),
								   (*it)->caloPosition.Eta(),
								   (*it)->trkSumPtHollowConeDR03,
								   (*it)->ecalRecHitSumEtConeDR03,
								   (*it)->hcalTowerSumEtConeDR03(),
								   (*it)->hadronicOverEm,
								   (*it)->sigmaIetaIeta,
								   (*it)->sigmaIphiIphi,
								   (*it)->r9,
								   (*it)->nPixelSeeds,
								   event->rho25);*/

			bool is_tightStar_photons = is_tight_susyStar(
                                                                   (*it)->momentum.Et(),
                                                                   (*it)->caloPosition.Eta(),
                                                                   (*it)->trkSumPtHollowConeDR03,
                                                                   (*it)->ecalRecHitSumEtConeDR03,
                                                                   (*it)->hcalTowerSumEtConeDR03(),
                                                                   (*it)->hadronicOverEm,
                                                                   (*it)->sigmaIetaIeta,
                                                                   (*it)->sigmaIphiIphi,
                                                                   (*it)->r9,
                                                                   (*it)->nPixelSeeds,
                                                                   event->rho25);

			/*bool is_tightEg11_photons = is_tight_ManiTripathi(
									(*it)->momentum.Et(),
									(*it)->caloPosition.Eta(),
									(*it)->trkSumPtHollowConeDR04,
									(*it)->ecalRecHitSumEtConeDR04,
									(*it)->hcalTowerSumEtConeDR04(),
									(*it)->hadronicOverEm,
									(*it)->sigmaIetaIeta,
									(*it)->sigmaIphiIphi,
									(*it)->r9,
									(*it)->nPixelSeeds,
									event->rho25);*/
			bool ismedium2012Cut = is_medium_2012(
                                                (*it)->momentum.Et(),
                                                (*it)->caloPosition.Eta(),
                                                (*it)->chargedHadronIso,
                                                (*it)->neutralHadronIso,
                                                (*it)->photonIso,
                                                (*it)->hadTowOverEm,  //single tower, same cut though
                                                (*it)->sigmaIetaIeta,
                                                (*it)->sigmaIphiIphi,
                                                (*it)->passelectronveto, //replaces pixel seed veto
                                                event->rho25);

			phoisTight_sus[ipho] = is_tightStar_photons? 1:0;
			phoisTight_Med12[ipho] = ismedium2012Cut? 1:0;
			bool isbar = is_bar((*it)->caloPosition.Eta());
			bool isec = is_ec((*it)->caloPosition.Eta());
			phoisBar[ipho] = isbar? 1:0;
			phoisEC[ipho] = isec? 1:0;

			phoE[ipho]=(*it)->momentum.E();
			phoPt[ipho]=(*it)->momentum.Pt();
			phoEta[ipho]=(*it)->momentum.Eta();
			phoSCEta[ipho]=(*it)->caloPosition.Eta();
			phoPhi[ipho]=(*it)->momentum.Phi();
			phoHE[ipho]=(*it)->hadronicOverEm;
			phoR9[ipho]=(*it)->r9;
			phoSinin[ipho]=(*it)->sigmaIetaIeta;
			phoSipip[ipho]=(*it)->sigmaIphiIphi;
			phoNPixelSeed[ipho]=(*it)->nPixelSeeds;

			phoTIso04[ipho]=(*it)->trkSumPtHollowConeDR04;
			phoEIso04[ipho]=(*it)->ecalRecHitSumEtConeDR04;
			phoHIso04[ipho]=(*it)->hcalTowerSumEtConeDR04();

			phoTIso03[ipho]=(*it)->trkSumPtHollowConeDR04;
			phoEIso03[ipho]=(*it)->ecalRecHitSumEtConeDR03;
			phoHIso03[ipho]=(*it)->hcalTowerSumEtConeDR03();
			phoPFchargedHad[ipho]= (*it)->chargedHadronIso;
			phoPFneutralHad[ipho]= (*it)->neutralHadronIso;
			phoPFphoIso[ipho]= (*it)->photonIso;

			if (isbar||isec) {  
				phoSusySumIso[ipho]=(phoTIso03[ipho] - 0.009*rho) +
				(phoEIso03[ipho] - 0.080*rho) +
				(phoHIso03[ipho] - 0.021*rho);
			}
			else  phoSusySumIso[ipho] = 999.0;

			if (isbar) {
				phoTIso04_corr[ipho]=phoTIso04[ipho] - 0.001*phoPt[ipho] - 0.0167*rho;
				phoEIso04_corr[ipho]=phoEIso04[ipho] - 0.006*phoPt[ipho] - 0.183*rho;
				phoHIso04_corr[ipho]=phoHIso04[ipho] - 0.0025*phoPt[ipho] - 0.062*rho;
			}
			else if(isec){
				phoTIso04_corr[ipho]=phoTIso04[ipho] - 0.001*phoPt[ipho] - 0.032*rho;
				phoEIso04_corr[ipho]=phoEIso04[ipho] - 0.006*phoPt[ipho] - 0.090*rho;
				phoHIso04_corr[ipho]=phoHIso04[ipho] - 0.0025*phoPt[ipho] - 0.180*rho;
			}


			if(isbar){ //this is kind of messed up. This is not the 2012 way of doing iso.
				phoTIso03_corr[ipho]=phoTIso03[ipho] - 0.001*phoPt[ipho] - 0.0167*rho;
				phoEIso03_corr[ipho]=phoEIso03[ipho] - 0.006*phoPt[ipho] - 0.183*rho;
				phoHIso03_corr[ipho]=phoHIso03[ipho] - 0.0025*phoPt[ipho] - 0.062*rho;
			}
			else if(isec){
				phoTIso03_corr[ipho]=phoTIso03[ipho] - 0.001*phoPt[ipho] - 0.032*rho;
				phoEIso03_corr[ipho]=phoEIso03[ipho] - 0.006*phoPt[ipho] - 0.090*rho;
				phoHIso03_corr[ipho]=phoHIso03[ipho] - 0.0025*phoPt[ipho] - 0.180*rho;
			}

			cout<<"L"<<ipho<<endl;
			ipho++;
		}//end for leading four loose photon candidates.
		cout<<"Lz"<<endl;



			//we have two photons
		TLorentzVector p0,p1;
		p0 = loose_susy12_photons[0]->momentum;
		p1 = loose_susy12_photons[1]->momentum;//segfaults.
		phoM01 = -999.0;
		phoM02 = -999.0;
		phoM12 = -999.0;
		phoM01 = (p0+p1).M();
		phoPt01 = (p0+p1).Pt();
		if (nPho > 2) { //then we have a third photon.
			TLorentzVector p2 = loose_susy12_photons[2]->momentum;
			phoM02 = (p0+p2).M();
			phoPt02 = (p0+p2).Pt();

			phoM12 = (p2+p1).M();
			phoPt12 = (p2+p1).Pt();
		}
		}//end if two loose_susy12_photons

		cout<<"M"<<endl;

			///////////////////////////////////////////////////////
			/////////////////FILL MED12 Photons////////////////////
			///////////////////////////////////////////////////////

		nMed12pho = (int)medium_susy12_photons.size();

			//apply the Et threshold.
		if (nMed12pho>=2 && medium_susy12_photons[0]->momentum.Et() > phoEtThresh0 && medium_susy12_photons[1]->momentum.Et() > phoEtThresh1) {
			int iMed12pho = 0;//loop over the first four photons.
			for(std::vector<susy::Photon*>::iterator it = medium_susy12_photons.begin();it != medium_susy12_photons.end() && iMed12pho<4; it++) {

					//bool is_tightSusy_photons = is_tight_susyStar(
				/*bool is_tightSusy_photons = is_tight_combIso_BFrancis(
											  (*it)->momentum.Et(),
											  (*it)->caloPosition.Eta(),
											  (*it)->trkSumPtHollowConeDR03,
											  (*it)->ecalRecHitSumEtConeDR03,
											  (*it)->hcalTowerSumEtConeDR03(),
											  (*it)->hadronicOverEm,
											  (*it)->sigmaIetaIeta,
											  (*it)->sigmaIphiIphi,
											  (*it)->r9,
											  (*it)->nPixelSeeds,
											  event->rho25);*/

				bool is_tightStar_photons = is_tight_susyStar(
										  (*it)->momentum.Et(),
										  (*it)->caloPosition.Eta(),
										  (*it)->trkSumPtHollowConeDR03,
										  (*it)->ecalRecHitSumEtConeDR03,
										  (*it)->hcalTowerSumEtConeDR03(),
										  (*it)->hadronicOverEm,
										  (*it)->sigmaIetaIeta,
										  (*it)->sigmaIphiIphi,
										  (*it)->r9,
										  (*it)->nPixelSeeds,
										  event->rho25);

				Med12phoisTight_sus[iMed12pho] = is_tightStar_photons? 1:0;
				bool isbar = is_bar((*it)->caloPosition.Eta());
				bool isec = is_ec((*it)->caloPosition.Eta());
				Med12phoisBar[iMed12pho] = isbar? 1:0;
				Med12phoisEC[iMed12pho] = isec? 1:0;

				Med12phoE[iMed12pho]=(*it)->momentum.E();
				Med12phoPt[iMed12pho]=(*it)->momentum.Pt();
				Med12phoEta[iMed12pho]=(*it)->momentum.Eta();
				Med12phoSCEta[iMed12pho]=(*it)->caloPosition.Eta();
				Med12phoPhi[iMed12pho]=(*it)->momentum.Phi();
				Med12phoHE[iMed12pho]=(*it)->hadronicOverEm;
				Med12phoR9[iMed12pho]=(*it)->r9;
				Med12phoSinin[iMed12pho]=(*it)->sigmaIetaIeta;
				Med12phoSipip[iMed12pho]=(*it)->sigmaIphiIphi;
				Med12phoNPixelSeed[iMed12pho]=(*it)->nPixelSeeds;

				Med12phoTIso04[iMed12pho]=(*it)->trkSumPtHollowConeDR04;
				Med12phoEIso04[iMed12pho]=(*it)->ecalRecHitSumEtConeDR04;
				Med12phoHIso04[iMed12pho]=(*it)->hcalTowerSumEtConeDR04();

				Med12phoTIso03[iMed12pho]=(*it)->trkSumPtHollowConeDR04;
				Med12phoEIso03[iMed12pho]=(*it)->ecalRecHitSumEtConeDR03;
				Med12phoHIso03[iMed12pho]=(*it)->hcalTowerSumEtConeDR03();
				Med12phoPFchargedHad[iMed12pho]= (*it)->chargedHadronIso;
				Med12phoPFneutralHad[iMed12pho]= (*it)->neutralHadronIso;
				Med12phoPFphoIso[iMed12pho]= (*it)->photonIso;

				if (isbar||isec) {
					Med12phoSusySumIso[iMed12pho]=(Med12phoTIso03[iMed12pho] - 0.009*rho) +
					(Med12phoEIso03[iMed12pho] - 0.080*rho) +
					(Med12phoHIso03[iMed12pho] - 0.021*rho);
				}
				else  Med12phoSusySumIso[iMed12pho] = 999.0;

				if (isbar) {
					Med12phoTIso04_corr[iMed12pho]=Med12phoTIso04[iMed12pho] - 0.001*Med12phoPt[iMed12pho] - 0.0167*rho;
					Med12phoEIso04_corr[iMed12pho]=Med12phoEIso04[iMed12pho] - 0.006*Med12phoPt[iMed12pho] - 0.183*rho;
					Med12phoHIso04_corr[iMed12pho]=Med12phoHIso04[iMed12pho] - 0.0025*Med12phoPt[iMed12pho] - 0.062*rho;
				}
				else if(isec){
					Med12phoTIso04_corr[iMed12pho]=Med12phoTIso04[iMed12pho] - 0.001*Med12phoPt[iMed12pho] - 0.032*rho;
					Med12phoEIso04_corr[iMed12pho]=Med12phoEIso04[iMed12pho] - 0.006*Med12phoPt[iMed12pho] - 0.090*rho;
					Med12phoHIso04_corr[iMed12pho]=Med12phoHIso04[iMed12pho] - 0.0025*Med12phoPt[iMed12pho] - 0.180*rho;
				}


				if(isbar){ //this is kind of messed up. This is not the 2012 way of doing iso.
					Med12phoTIso03_corr[iMed12pho]=Med12phoTIso03[iMed12pho] - 0.001*Med12phoPt[iMed12pho] - 0.0167*rho;
					Med12phoEIso03_corr[iMed12pho]=Med12phoEIso03[iMed12pho] - 0.006*Med12phoPt[iMed12pho] - 0.183*rho;
					Med12phoHIso03_corr[iMed12pho]=Med12phoHIso03[iMed12pho] - 0.0025*Med12phoPt[iMed12pho] - 0.062*rho;
				}
				else if(isec){
					Med12phoTIso03_corr[iMed12pho]=Med12phoTIso03[iMed12pho] - 0.001*Med12phoPt[iMed12pho] - 0.032*rho;
					Med12phoEIso03_corr[iMed12pho]=Med12phoEIso03[iMed12pho] - 0.006*Med12phoPt[iMed12pho] - 0.090*rho;
					Med12phoHIso03_corr[iMed12pho]=Med12phoHIso03[iMed12pho] - 0.0025*Med12phoPt[iMed12pho] - 0.180*rho;
				}

				iMed12pho++;
			}//end for leading four tight MED12 photon candidates.
			cout<<"O"<<endl;
				//we have two photons
			Med12phoM01 = -999.0;
			Med12phoM02 = -999.0;
			Med12phoM12 = -999.0;
			Med12phoPt01 = -999.0;
			Med12phoPt02 = -999.0;
			Med12phoPt12 = -999.0;
			if (nMed12pho >=2) {
				cout<<"nMed12pho>=2"<<endl;
				TLorentzVector MedPho0,MedPho1;
				MedPho0 = medium_susy12_photons[0]->momentum;
				MedPho1 = medium_susy12_photons[1]->momentum;
				cout<<"accessed first two phos"<<endl;
				Med12phoM01 = (MedPho0+MedPho1).M();
				Med12phoPt01 = (MedPho0+MedPho1).Pt();
				if (nMed12pho > 2) { //then we have a third photon.
					cout<<"Try to access third"<<endl;
					TLorentzVector MedPho2 = medium_susy12_photons[2]->momentum;
					cout<<"accessed third phos"<<endl;
					Med12phoM02 = (MedPho0+MedPho2).M();
					Med12phoPt02 = (MedPho0+MedPho2).Pt();
					
					Med12phoM12 = (MedPho2+MedPho1).M();
					Med12phoPt12 = (MedPho2+MedPho1).Pt();
				}
		}

		}

		cout<<"S"<<endl;

			///////////////////////////////////////////////////////
			/////////////////FILL Susy* Photons////////////////////
			///////////////////////////////////////////////////////

		nsusPho = (int)tight_susy11Star_photons.size();

			//apply the Et threshold.
		if (nsusPho && tight_susy11Star_photons[0]->momentum.Et() > phoEtThresh0 && tight_susy11Star_photons[1]->momentum.Et() > phoEtThresh1) {
			int isuspho = 0;//loop over the first four photons.
			for(std::vector<susy::Photon*>::iterator it = medium_susy12_photons.begin();it != medium_susy12_photons.end() && isuspho<4; it++) {

					//bool is_tightSusy_photons = is_tight_susyStar(
				bool is_med12_photon =  is_medium_2012(
                                                (*it)->momentum.Et(),
                                                (*it)->caloPosition.Eta(),
                                                (*it)->chargedHadronIso,
                                                (*it)->neutralHadronIso,
                                                (*it)->photonIso,
                                                (*it)->hadTowOverEm,  //single tower, same cut though
                                                (*it)->sigmaIetaIeta,
                                                (*it)->sigmaIphiIphi,
                                                (*it)->passelectronveto, //replaces pixel seed veto
                                                event->rho25);

				/*is_tight_ManiTripathi(
									  (*it)->momentum.Et(),
									  (*it)->caloPosition.Eta(),
									  (*it)->trkSumPtHollowConeDR03,
									  (*it)->ecalRecHitSumEtConeDR03,
									  (*it)->hcalTowerSumEtConeDR03(),
									  (*it)->hadronicOverEm,
									  (*it)->sigmaIetaIeta,
									  (*it)->sigmaIphiIphi,
									  (*it)->r9,
									  (*it)->nPixelSeeds,
									  event->rho25);*/

				susphoisTight_Med12[isuspho] = is_med12_photon? 1:0;
				bool isbar = is_bar((*it)->caloPosition.Eta());
				bool isec = is_ec((*it)->caloPosition.Eta());
				susphoisBar[isuspho] = isbar? 1:0;
				susphoisEC[isuspho] = isec? 1:0;

				susphoE[isuspho]=(*it)->momentum.E();
				susphoPt[isuspho]=(*it)->momentum.Pt();
				susphoEta[isuspho]=(*it)->momentum.Eta();
				susphoSCEta[isuspho]=(*it)->caloPosition.Eta();
				susphoPhi[isuspho]=(*it)->momentum.Phi();
				susphoHE[isuspho]=(*it)->hadronicOverEm;
				susphoR9[isuspho]=(*it)->r9;
				susphoSinin[isuspho]=(*it)->sigmaIetaIeta;
				susphoSipip[isuspho]=(*it)->sigmaIphiIphi;
				susphoNPixelSeed[isuspho]=(*it)->nPixelSeeds;

				susphoTIso04[isuspho]=(*it)->trkSumPtHollowConeDR04;
				susphoEIso04[isuspho]=(*it)->ecalRecHitSumEtConeDR04;
				susphoHIso04[isuspho]=(*it)->hcalTowerSumEtConeDR04();

				susphoTIso03[isuspho]=(*it)->trkSumPtHollowConeDR04;
				susphoEIso03[isuspho]=(*it)->ecalRecHitSumEtConeDR03;
				susphoHIso03[isuspho]=(*it)->hcalTowerSumEtConeDR03();
				susphoPFchargedHad[isuspho]= (*it)->chargedHadronIso;
				susphoPFneutralHad[isuspho]= (*it)->neutralHadronIso;
				susphoPFphoIso[isuspho]= (*it)->photonIso;

				if (isbar||isec) {
					susphoSusySumIso[isuspho]=(susphoTIso03[isuspho] - 0.009*rho) +
					(susphoEIso03[isuspho] - 0.080*rho) +
					(susphoHIso03[isuspho] - 0.021*rho);
				}
				else  susphoSusySumIso[isuspho] = 999.0;

				if (isbar) {
					susphoTIso04_corr[isuspho]=susphoTIso04[isuspho] - 0.001*susphoPt[isuspho] - 0.0167*rho;
					susphoEIso04_corr[isuspho]=susphoEIso04[isuspho] - 0.006*susphoPt[isuspho] - 0.183*rho;
					susphoHIso04_corr[isuspho]=susphoHIso04[isuspho] - 0.0025*susphoPt[isuspho] - 0.062*rho;
				}
				else if(isec){
					susphoTIso04_corr[isuspho]=susphoTIso04[isuspho] - 0.001*susphoPt[isuspho] - 0.032*rho;
					susphoEIso04_corr[isuspho]=susphoEIso04[isuspho] - 0.006*susphoPt[isuspho] - 0.090*rho;
					susphoHIso04_corr[isuspho]=susphoHIso04[isuspho] - 0.0025*susphoPt[isuspho] - 0.180*rho;
				}


				if(isbar){ //this is kind of messed up. This is not the 2012 way of doing iso.
					susphoTIso03_corr[isuspho]=susphoTIso03[isuspho] - 0.001*susphoPt[isuspho] - 0.0167*rho;
					susphoEIso03_corr[isuspho]=susphoEIso03[isuspho] - 0.006*susphoPt[isuspho] - 0.183*rho;
					susphoHIso03_corr[isuspho]=susphoHIso03[isuspho] - 0.0025*susphoPt[isuspho] - 0.062*rho;
				}
				else if(isec){
					susphoTIso03_corr[isuspho]=susphoTIso03[isuspho] - 0.001*susphoPt[isuspho] - 0.032*rho;
					susphoEIso03_corr[isuspho]=susphoEIso03[isuspho] - 0.006*susphoPt[isuspho] - 0.090*rho;
					susphoHIso03_corr[isuspho]=susphoHIso03[isuspho] - 0.0025*susphoPt[isuspho] - 0.180*rho;
				}

				isuspho++;
			}//end for leading four tight susy* photon candidates.
			cout<<"O"<<endl;
				//we have two photons
			susphoM01 = -999.0;
			susphoM02 = -999.0;
			susphoM12 = -999.0;
			susphoPt01 = -999.0;
			susphoPt02 = -999.0;
			susphoPt12 = -999.0;
			if (nsusPho >=2) {
				cout<<"nsuspho>=2"<<endl;
				TLorentzVector susp0,susp1;
				susp0 = tight_susy11Star_photons[0]->momentum;
				susp1 = tight_susy11Star_photons[1]->momentum;
				cout<<"accessed first two phos"<<endl;
				susphoM01 = (susp0+susp1).M();
				susphoPt01 = (susp0+susp1).Pt();
				if (nsusPho > 2) { //then we have a third photon.
					cout<<"Try to access third"<<endl;
					TLorentzVector susp2 = tight_susy11Star_photons[2]->momentum;
					cout<<"accessed third phos"<<endl;
					susphoM02 = (susp0+susp2).M();
					susphoPt02 = (susp0+susp2).Pt();

					susphoM12 = (susp2+susp1).M();
					susphoPt12 = (susp2+susp1).Pt();
				}
			}
			
		}//end if
		if(event->eventNumber == ((unsigned int)probeevent)) cout<<"probe got to end of photon loop"<<endl;



			/////////////////////////do MT cut ////////////////////////////////
		//if (!(phoM01>100 || phoM02 > 100 || phoM12 > 100 ) &&
			//!(Med12phoM01>100 || Med12phoM02 > 100 || Med12phoM12 > 100 ) ) continue;
		if ( !(Med12phoM01>100) ) continue;
		Counters["pass phoM 100 cuts"]++;

		//for(std::vector<susy::Photon*>::iterator it = tightSusy_photons.begin();it != tightSusy_photons.end(); it++) {
		for(std::vector<susy::Photon*>::iterator it = medium_susy12_photons.begin();it != medium_susy12_photons.end(); it++) {
			myPhotonST+= (*it)->momentum.Et();
//			ipho++;
		}

			/////////////////////////////////////////////////////////////////
			//////////////////////// FIND THE PRIMARY VERTEX ////////////////
			/////////////////////////////////////////////////////////////////

		if(printLevel > 0) std::cout << "Find primary vertex in the event." << std::endl;
			//		TVector3* primVtx = &(event->vertices[0].position);
		TVector3* primVtx = 0;
		if(event->vertices.size() > 0) primVtx = &(event->vertices[0].position);
			//		if(primVtx) h_vtxZ_unsliced->Fill(primVtx->Z());
			//		h_bsZ_unsliced->Fill(event->beamSpot.Z());

		for(std::vector<susy::Vertex>::iterator it = event->vertices.begin(); it != event->vertices.end(); it++) {
			if(ok_vtx(it)) good_vtx.push_back(&*it);
		}
		int nPVertex = good_vtx.size();
			//		selvar_vtx_nVtx->Fill(nPVertex);
		if(nPVertex<1){
			if(printLevel > 1) cout<<"No Good Vertex!!!!  Run: "<<event->runNumber<<"  Event: "<<event->eventNumber<<endl;
			continue;
		}		
		if(event->eventNumber == ((unsigned int)probeevent)) cout<<"pass Vertex"<<endl;
		Counters["pass a primary vertex reqirement"]++;
		
			/////////////////////////////////////////////////////////////////
			//////////////////////// FIND MUONS  ////////////////////////////
			/////////////////////////////////////////////////////////////////
			//may need primVtx->Z()

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
			   isfarFromPhotons(it_Mu->momentum, medium_susy12_photons)
			   ){
				 Muons.push_back(&*it_Mu);
				 myLeptonST += (it_Mu)->momentum.Et();
			}	
				//if(ok_muon_AN_11_409(it_Mu,innerTrack, primVtx->Z()) Muons.push_back(&*it_Mu);
				//innerTrack is not the same as the combined track. Fix it!! //xxx

			/*			selvar_mu_Et->Fill(it_Mu->momentum.Pt());
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
			 selvars_mu_isPFMuon->Fill(it_Mu->isPFMuon());*/

		}}//end it_Mu muon loop
			//sort Muons by Pt
		std::sort(Muons.begin(), Muons.end(), EtGreater<susy::Muon>);
		if(printLevel>1)cout<<"Muons size= "<<Muons.size()<<endl;
		nMu = (int)Muons.size();
		int m=0;
		TLorentzVector m0;
		muM01 = -999.0;
		for(std::vector<susy::Muon*>::iterator it_Mu = Muons.begin(); it_Mu != Muons.end() && m<4; it_Mu++) {
			muE[m]=(*it_Mu)->momentum.E();
			muPt[m]=(*it_Mu)->momentum.Pt();
			muEta[m]=(*it_Mu)->momentum.Eta();
			muPhi[m]=(*it_Mu)->momentum.Phi();
			muSumPFIso[m]= (*it_Mu)->sumChargedHadronPt04 + std::max(0.,(*it_Mu)->sumNeutralHadronEt04+(*it_Mu)->sumPhotonEt04-0.5*(*it_Mu)->sumPUPt04);
			muSumIsoDR03[m]= (*it_Mu)->ecalIsoR03 + (*it_Mu)->hcalIsoR03 + (*it_Mu)->trackIsoR03;
			muMt[m]=Mt((*it_Mu)->momentum);

			if (m==0) m0 = (*it_Mu)->momentum;
			else if(m==1) muM01 = ((*it_Mu)->momentum + m0).M();
			m++;
		}


			//		selvar_mu_nmu->Fill(Muons.size());

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
		eleM01 = -999.0;
		if(eleMap != event->electrons.end()) {
				//loop over electron collection
			for(std::vector<susy::Electron>::iterator it_Ele = eleMap->second.begin(); it_Ele != eleMap->second.end(); it_Ele++) {
				if(printLevel > 1) cout<<"looping over electron collection"<<endl;

				float relIso=(it_Ele->chargedHadronIso + it_Ele->neutralHadronIso + it_Ele->photonIso)/it_Ele->momentum.Pt();
					//				selvar_ele_Et->Fill(it_Ele->momentum.Pt());
					//				selvar_ele_Eta->Fill(it_Ele->momentum.Eta());
					//				selvar_ele_Phi->Fill(fabs(it_Ele->momentum.Phi()));
					//				selvar_ele_relIso->Fill(relIso);
					//				selvar_ele_passMVAPreselect->Fill();
					//				selvar_ele_isPF->Fill();
					//				selvar_ele_d0->Fill();
					//				selvar_ele_dz_pVtxZ->Fill();

				if(ok_ele(it_Ele) &&
				   isfarFromPhotons(it_Ele->momentum, medium_susy12_photons)){
					pfEles.push_back(&*it_Ele);
					myLeptonST += (it_Ele)->momentum.Et();
				   }
					//				susy::Track& innerTrack = event->tracks[it_Ele->trackIndex];
					//				if(ok_ele_AN_11_409(it_Ele, innerTrack, primVtx->Z())) pfEles.push_back(&*it_Ele);

			}//end it_Ele electron loop
			std::sort(pfEles.begin(), pfEles.end(), EtGreater<susy::Electron>); //sort pfEles by Pt
			if(printLevel>1)cout<<"pfEles size= "<<pfEles.size()<<endl;


			nEle = (int)pfEles.size();
			int ie=0;
			TLorentzVector ele0;
			for(std::vector<susy::Electron*>::iterator it_Ele = pfEles.begin(); it_Ele != pfEles.end() && m<4; it_Ele++) {
				eleE[ie]=(*it_Ele)->momentum.E();
				elePt[ie]=(*it_Ele)->momentum.Pt();
				eleEta[ie]=(*it_Ele)->momentum.Eta();
				elePhi[ie]=(*it_Ele)->momentum.Phi();
//				eleSCEta[ie] = (*it_Ele)->caloPosition.Eta();
					//				eleSumPFIso[ie]= (*it_Ele)->sumChargedHadronPt04 + std::max(0.,(*it_Ele)->sumNeutralHadronEt04+(*it_Ele)->sumPhotonEt04-0.5*(*it_Ele)->sumPUPt04);
					//				eleSumIsoDR03[ie]= (*it_Ele)->ecalIsoR03 + (*it_Ele)->hcalIsoR03 + (*it_Ele)->trackIsoR03;
				eleSumPFIso[ie]=(*it_Ele)->chargedHadronIso + (*it_Ele)->neutralHadronIso + (*it_Ele)->photonIso;
				eleSumIsoDR03[ie]=(*it_Ele)->dr03TkSumPt+ (*it_Ele)->dr03EcalRecHitSumEt+ (*it_Ele)->dr03HcalDepth1TowerSumEt+ (*it_Ele)->dr03HcalDepth2TowerSumEt;
				eleMt[ie]=Mt((*it_Ele)->momentum);

				if (ie==0) ele0 = (*it_Ele)->momentum;
				else if(ie==1) eleM01 = ((*it_Ele)->momentum + ele0).M();
				ie++;
			}




		}//end eleMap

			//		selvar_ele_nele->Fill(pfEles.size());

			//import
		float HT_all = 0;
		float MHT_all = 0;
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
					//				selvar_jet_Et   ->Fill(corrP4.Pt());
					//				selvar_jet_Eta  ->Fill(corrP4.Phi());
					//				selvar_jet_Phi  ->Fill(std::fabs(corrP4.Phi()));

				if(corrP4.Pt() < 30) continue;
				if(std::fabs(corrP4.Eta()) > 2.6) continue; //AN_11_409
								
				float uncorrE = it->momentum.E();
				float NeutralHadronFraction = (it->neutralHadronEnergy)/uncorrE;
				float NeutralEMFraction =(it->neutralEmEnergy)/uncorrE;
				float ChargedHadronFraction = (it->chargedHadronEnergy)/uncorrE;
				float ChargedEMFraction = (it->chargedEmEnergy)/uncorrE;

					//				selvars_jet_nConstituents->Fill(it->nConstituents);
					//				selvars_jet_NeutralHadFrac ->Fill(NeutralHadronFraction);
					//				selvars_jet_NeutralEMFrac  ->Fill(NeutralEMFraction);
					//				selvars_jet_ChargedHadFrac ->Fill(ChargedHadronFraction);
					//				selvars_jet_ChargedEMFrac  ->Fill(ChargedEMFraction);
					//				selvars_jet_chargedHadMult ->Fill(it->chargedHadronMultiplicity);
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

					//ra3_pfjets_noclean.push_back(&*it);
				
				if(event->eventNumber == ((unsigned int)probeevent)){
					printf("PFjet Pt %.1f Eta %.2f Phi %.2f\n",corrP4.Pt(),corrP4.Eta(),corrP4.Phi());
				}	

				bool same_pho_object = false; //exclude the two photons you use for analysis. 
//				int np=0;
				for(std::vector<susy::Photon*>::iterator p_it = medium_susy12_photons.begin(); p_it != medium_susy12_photons.end(); p_it++) {
					if(event->eventNumber == ((unsigned int)probeevent)){
						printf("      Photon Pt %.1f Eta %.2f Phi %.2f\n",(*p_it)->momentum.Pt(),(*p_it)->momentum.Eta(),(*p_it)->momentum.Phi());
						cout<<"      object match: "<<isSameObject(corrP4,(*p_it)->momentum)<<endl;
					}
//					if (np >=2) break;
					same_pho_object |= isSameObject(corrP4,(*p_it)->momentum);
//					np++;
				}
				
				bool same_emobject = false;
				for(std::vector<susy::Electron*>::iterator m_it = pfEles.begin(); m_it != pfEles.end(); m_it++) { 
					if(event->eventNumber == ((unsigned int)probeevent)){
 						printf("      Ele Pt %.1f Eta %.2f Phi %.2f\n",(*m_it)->momentum.Pt(),(*m_it)->momentum.Eta(),(*m_it)->momentum.Phi());
						cout<<"      object match: "<<isSameObject(corrP4,(*m_it)->momentum)<<endl;
					}
					same_emobject |= isSameObject(corrP4,(*m_it)->momentum);
				}

				bool same_muon = false;
				for(std::vector<susy::Muon*>::iterator m_it = Muons.begin(); m_it != Muons.end(); m_it++){
					if(event->eventNumber == ((unsigned int)probeevent)){
						printf("      Muon Pt %.1f Eta %.2f Phi %.2f\n",(*m_it)->momentum.Pt(),(*m_it)->momentum.Eta(),(*m_it)->momentum.Phi());
						cout<<"      object match: "<<isSameObject(corrP4,(*m_it)->momentum)<<endl;
					}
					same_muon |= isSameObject(corrP4,(*m_it)->momentum);
				}
					//				selvars_jet_dR_mu_min      ->Fill();

				if(!same_emobject && !same_muon && !same_pho_object){
					ra3_pfjets.push_back(&*it);
					HT_all += corrP4.Pt();
					MHT_x_all -= corrP4.Px();
					MHT_y_all -= corrP4.Py();	
				}
				
			}// pfjet
		}//if
			//		selvar_jet_njet->Fill(ra3_pfjets.size());
		std::sort(ra3_pfjets.begin(),ra3_pfjets.end(),EtGreater<susy::PFJet>);
		nJet = (int)ra3_pfjets.size();
		HT = HT_all;
		MHT_all = std::sqrt(MHT_x_all*MHT_x_all + MHT_y_all*MHT_y_all);
		MHT = MHT_all;



			//now select b-tags.
		int j=0;
		for(std::vector<susy::PFJet*>::iterator it = ra3_pfjets.begin();	it != ra3_pfjets.end(); it++) { //error
			if((*it)->bTagDiscriminators[5] > 0.679) pfBJets.push_back(*it);//CSV medium working point
				//https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagPerformanceOP#B_tagging_Operating_Points_for_5
				//			selvar_btag_csv->Fill((*it)->bTagDiscriminators[5]);
			if(j<4){
				jetPt[j] = (*it)->momentum.Pt();
				jetE[j]= (*it)->momentum.E();
				jetEta[j]= (*it)->momentum.Eta();
				jetPhi[j]= (*it)->momentum.Phi();
				csv[j] = (*it)->bTagDiscriminators[5];
			}
			j++;
		}
		nbtags = (int)pfBJets.size();

		jetM01=-999.0;
		jetM02=-999.0;
		jetM03=-999.0;
		jetM12=-999.0;
		jetM13=-999.0;
		jetM23=-999.0;
		TLorentzVector j0,j1;
		if (nJet>=2) {
			j0 = ra3_pfjets[0]->momentum;
			j1 = ra3_pfjets[1]->momentum;
			jetM01 = (j0+j1).M();
			if (nJet>=3) {
				TLorentzVector j2 = ra3_pfjets[2]->momentum;
				jetM02 = (j0+j2).M();
				jetM12 = (j2+j1).M();

				if (nJet>=4) {
					TLorentzVector j3 = ra3_pfjets[3]->momentum;
					jetM03 = (j0+j3).M();
					jetM13 = (j1+j3).M();
					jetM23 = (j2+j3).M();
				}
			}
		}//end if two jets.




			//////////////////////// GET MET  ///////////////////////////
		if(printLevel > 0) std::cout << "Select which met will be used in the event." << std::endl;
		std::map<TString, susy::MET>::iterator met_it = event->metMap.find("pfMet");
		if(met_it == event->metMap.end()) {
			std::cout << "MET map is not availabel!!!" << std::endl;
			continue;
		}
		susy::MET* pfmet = &(met_it->second);
		bool spillguts = false;
		if(event->eventNumber == ((unsigned int)probeevent)) spillguts = true;
		float corrmet = JEC_MET(pfmet,ra3_pfjets,spillguts);
		metPhi = TMath::ATan(MHT_y_all/MHT_x_all);
		Counters["has met map"]++;

		myST = HT_all + myPhotonST + corrmet + myLeptonST;
		met = corrmet;
		if(met<30){
			 cout<<endl<<"WARNING!! MET < 30 met = "<<met<<" uc pfMET="<<pfmet->met()<<endl;
			cout<<"list "<<event->runNumber<<" "<<event->luminosityBlockNumber<<" "<<event->eventNumber<<endl;
		}
		ST = myST;
		flatskimtree->Fill();
		if(event->eventNumber == ((unsigned int)probeevent)) cout<<"probe: corrmet "<<corrmet<<" uncorrmet "<< pfmet->met() <<endl;
		eventlist<<event->runNumber<<" "<<event->luminosityBlockNumber<<" "<<event->eventNumber<<endl;

		if(met <= 30) printf("info: fail met cut\n");
		if(!(Med12phoM01 > 105 && Med12phoM01 < 156)) printf( "info: fail window\n");
		if(!(medium_susy12_photons[0]->momentum.Pt()>Med12phoM01/3.0)) printf("info: fail pt0\n");
		if(!(medium_susy12_photons[1]->momentum.Pt()>Med12phoM01/4.0)) printf("info: fail pt1\n");
		if(!(Med12phoPt01/Med12phoM01 > 0.6)) printf( "info: fail PIt cut\n");
		if(is_ec(medium_susy12_photons[0]->momentum.Eta()) && is_ec(medium_susy12_photons[1]->momentum.Eta())) printf("info: ee\n");

		if(met > 30.0 && 
		   Med12phoM01 > 105 && Med12phoM01 < 156 && 
		   medium_susy12_photons[0]->momentum.Pt()>Med12phoM01/3.0 &&
		   medium_susy12_photons[1]->momentum.Pt()>Med12phoM01/4.0 &&
		   Med12phoPt01/Med12phoM01 > 0.6 &&
		   !(is_ec(medium_susy12_photons[0]->momentum.Eta()) && is_ec(medium_susy12_photons[1]->momentum.Eta()) )){
			eventlist2<<event->runNumber<<" "<<event->luminosityBlockNumber<<" "<<event->eventNumber<<endl;
			if(event->eventNumber == ((unsigned int)probeevent)) cout<<"Filling eventlist2 because it live in the plot"<<endl;
		}
		if(event->eventNumber == ((unsigned int)probeevent)){
                        TLorentzVector gg_trip =        medium_susy12_photons[0]->momentum + medium_susy12_photons[1]->momentum;
                        float mgg_trip = gg_trip.M();
                        float pigg_trip = gg_trip.Pt()/mgg_trip;
			cout<<endl<<"*** Probe Event ***"<<endl;

			cout<<"run "<< event->runNumber <<" lumi "<< event->luminosityBlockNumber << " event "<< event->eventNumber <<endl;
			printf("phoPt[0] %.2f Eta %.2f Phi %.2f\n", medium_susy12_photons[0]->momentum.Pt(), medium_susy12_photons[0]->momentum.Eta(), medium_susy12_photons[0]->momentum.Phi() );
			printf("phoPt[1] %.2f Eta %.2f Phi %.2f\n", medium_susy12_photons[1]->momentum.Pt(), medium_susy12_photons[1]->momentum.Eta(), medium_susy12_photons[1]->momentum.Phi() );
			printf("met %f phi %.2f\n",corrmet,pigg_trip);
		}
	} // for every jentry
			///AT THIS POINT WE DECLARE THE EVENT PHYSICS-GOOD

			//	for( nameint::iterator i=Counters.begin(); i!=Counters.end(); ++i){
			//		cout << (*i).second << " " << (*i).first << endl;
			//	}
		for (int i=0; i<int(Counter_order.size()); i++) {
			cout <<  Counters[Counter_order[i]] << " " << Counter_order[i] << endl;
		}


			// close the output file
		flatskim.cd();
		flatskimtree->Write();
		flatskim.Close();
		eventlist.close();
		eventlist2.close();
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


	bool SusySkimmer::ok_muon(std::vector<susy::Muon>::iterator it){ //Yu Feng
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

	bool SusySkimmer::ok_muon_AN_11_409(std::vector<susy::Muon>::iterator it,susy::Track& combinedTrack, float pVtx_Z){ //probably inner track instead
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
		float normChi2 = combinedTrack.chi2 / combinedTrack.ndof;
		float d0 = std::abs(d0correction(event->beamSpot,combinedTrack));

			//	if(normChi2 >= 10.f || d0 >= 0.2 ) return false;
		if(d0 >= 0.2 ) return false; //assuming that sais d0 < 0.02cm.
		else return true;
	}

		//use this one!
	bool SusySkimmer::ok_muon_DMoris(std::vector<susy::Muon>::iterator it_Mu,susy::Track& innerTrack){
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
	bool SusySkimmer::ok_ele(std::vector<susy::Electron>::iterator it_Ele){	//Dave Moris
		if(!it_Ele->isPF() and !it_Ele->passingMvaPreselection()) return false;
		float Iso=it_Ele->chargedHadronIso + it_Ele->neutralHadronIso + it_Ele->photonIso;
		float pt=it_Ele->momentum.Pt();
		if(it_Ele->momentum.Eta()>2.6) return false;
		if(pt<15) return false;
		if(Iso/pt>0.2) return false;
		return true;
	}

	bool SusySkimmer::ok_ele_AN_11_409(std::vector<susy::Electron>::iterator it_Ele, susy::Track& innerTrack, float pVtx_Z){
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
	float SusySkimmer::JEC_MET(susy::MET* pfmet,std::vector<susy::PFJet*> ra3_pfjets,bool Debug_noisily){
			//add adjust MET for JEC. 
		float corr_px = 0;
		float corr_py = 0;
		float uncorr_px = 0;
		float uncorr_py = 0;
		if(Debug_noisily) printf("Entering JEC_MET. UCmet = %.3f\n",pfmet->met());
		if(Debug_noisily) printf("njets: %i\n",(int)ra3_pfjets.size());
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

	bool SusySkimmer::ok_vtx(std::vector<susy::Vertex>::iterator it){
		float vtx_rho = std::sqrt((it->position.X())*(it->position.X()) + (it->position.Y())*(it->position.Y()));
		if(it->isFake() || //it->chi2 == 0.f) || (it->tracksSize == 0) ||  //this disagrees with D.Morris. DM: Vtx_it->isFake() ||
		   (it->ndof <= 4.f) ||
		   (std::fabs(it->position.Z()) >= 24.f) || //vtx absZ > 24
		   (vtx_rho >= 2.f)) return false;
		return true;
	}

	void SusySkimmer::MakeHistSet(TH1F** h, TString prefix, int nbins, float lower, float upper){
		TString names[7];
		TString titles[7];
		for (int i = 0; i<7; i++) {
			names[i] = "h";
			names[i]+= prefix;
			titles[i] = prefix;
		}
		names[0]+="_lowSB";        titles[0] += " Lower Side Band";
		names[1]+="_tag";          titles[1] += " in Higgs Tag Region";
		names[2]+="_upperSB";      titles[2] += " Upper Side Band";
		names[3]+="_bkg";          titles[3] += " Background to Higgs Tag Region";
		names[4]+="_tag_subbkg";   titles[4] += " Background Subtracted Higgs Tag Region";
		names[5]+="_lowSB_scaled"; titles[5] += " Lower Side Band";
		names[6]+="_upperSB_scaled";titles[6] += " Upper Side Band";
		
		for (int i=0; i < nPhoMassAndBkgDists; i++) h[i] = new TH1F(RandomString(6),"",nbins,lower,upper);
		for (int i = 0; i<7; i++) NameHist(h[i],names[i].Data(),titles[i].Data());
			//	NameHist(h[0],"h"+prefix+"_lowSB",prefix + " Lower Side Band");
			//	NameHist(h[1],"h"+prefix+"_tag",prefix + " in Higgs Tag Region");
			//	NameHist(h[2],"h"+prefix+"_upperSB",prefix + " Upper Side Band");
			//	NameHist(h[3],"h"+prefix+"_bkg",prefix + " Background to Higgs Tag Region");
			//	NameHist(h[4],"h"+prefix+"_tag_subbkg",prefix + " Background Subtracted Higgs Tag Region");
			//	NameHist(h[5],"h"+prefix+"_lowSB_scaled",prefix + " Lower Side Band");
			//	NameHist(h[6],"h"+prefix+"_upperSB_scaled",prefix + " Upper Side Band");
	}
	
	
	
	
