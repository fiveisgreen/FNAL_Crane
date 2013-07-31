	// -*- C++ -*-
	//
	// Package:    SusyNtuplizer
	// Class:      SusyAna_superskim_Loose.cc
	// 
/*
 
 Description: an analyzer for susy::Event
 
 Implementation:
 
 */
	//
	// Original Author:  Dongwook Jang
	// $Id: SusyAna_superskim_Loose.cc,v 1.12 2012/05/03 19:58:51 dwjang Exp $
	//

#define SusyAna_superskim_Loose_cxx

//#include <TH2.h>
//#include <TStyle.h>
//#include <TCanvas.h>
//#include <TH1F.h>

#include <map>
//#include <set>
//#include <cmath>
#include <algorithm>
#include <utility>

#include "SusyAna_superskim_Loose.h"
#include "SusyEventPrinter.h"

#include "../jec/JetMETObjects/interface/JetCorrectorParameters.h"
#include "../jec/JetMETObjects/interface/FactorizedJetCorrector.h"
	//my additions
//#include "TAxis.h"
//#include "TMath.h"
//#include <TH3.h>
#include "TFile.h"
#include "TTree.h"
//#include "TLegend.h"
#include "TLorentzVector.h"
//#include "TGraphErrors.h"
//#include "TF1.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "TString.h"
	//user defiend
//#include "utilities.h"
#include "cuts.h"
//#include "params_arg.h"
//#include "GetError.h"
//#include "hggx_analysers.h"
//#include "quicksave.C"

using namespace std;
//using namespace params;


template<typename T> bool EtGreater(const T* p1, const T* p2) {
	return (p1->momentum.Et() > p2->momentum.Et());
}


void SusyAna_superskim_Loose::InitializePerEvent() {
	
}


bool SusyAna_superskim_Loose::isSameObject(TLorentzVector& p1, TLorentzVector& p2) {
	
	float dEta = p1.Eta() - p2.Eta();
	float dPhi = TVector2::Phi_mpi_pi(p1.Phi() - p2.Phi());
	return std::sqrt(dEta*dEta + dPhi*dPhi) <= 0.6 || fabs(dPhi) <= 0.05; //dMorse as of April2013
	//return std::sqrt(dEta*dEta + dPhi*dPhi) < 0.5;
}//dR05 cut


float SusyAna_superskim_Loose::d0correction(TVector3& beamSpot, susy::Track& track) const {
	
	float d0 = track.d0() - beamSpot.X()*std::sin(track.phi()) + beamSpot.Y()*std::cos(track.phi());
	return d0;
}


bool SusyAna_superskim_Loose::PassTrigger(TString path) {
	bool pass = false;
	for(susy::TriggerMap::iterator it = event->hltMap.begin(); it != event->hltMap.end(); it++) {
		if(it->first.Contains(path) && (int(it->second.second)) ) {
			pass = true;
			break;
		}
	}
	return pass;
}


bool SusyAna_superskim_Loose::PassTriggers() {
	bool pass = false;
	for(std::vector<TString>::iterator it = hltNames.begin(); it != hltNames.end(); it++) {
		if(PassTrigger(*it)) {
			pass = true;
			break;
		}
	}
	return pass;
}
//void MoveFileToDcache(char* filename, char* thisDir, char* dCacheDir, bool deleteOrigionalFile = false);
bool MoveFileToDcache(char* filename, char* thisDir, char* dCacheDir, bool deleteOrigionalFile = true){
/*	This copies a local file to dCache. It returns true iff the copy worked. 
	If the copy worked and deleteOrigionalFile, the origional file is deleted; otherwise it is not. 
	This requires: #include <stdio.h> and #include <stdlib.h>
        Example: 
	filename = "SuperSkim53X_data12A_1.root";
	thisDir = "/uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/" //must end in slash and be a full path.
	dCacheDir = "abarker/SusyLooseSkim_53X_2012/" //must end in slash and should start with abarker
	if deleteOrigionalFile, the file at filename is deleted after copying */
        char* command = Form("srmcp \"file:////////%s%s\" \"srm://cmssrm.fnal.gov:8443/resilient/%s%s\"",thisDir,filename,dCacheDir,filename);
        //char* command = Form("srmcp \"file://///////uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/%s\" \"srm://cmssrm.fnal.gov:8443/resilient/abarker/SusyLooseSkim_53X_2012/%s\"",filename,filename);
	cout<<"Running dCache Copy Command:"<<endl;
        cout<<command<<endl;
        //should come out like: 
	//srmcp "file://///////uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/SuperSkim53X_data12A_1.root" "srm://cmssrm.fnal.gov:8443/resilient/abarker/SusyLooseSkim_53X_2012/SuperSkim53X_data12A_1.root"%
        int status = system( command);
	bool bstatus = status ==0;
	if(deleteOrigionalFile && bstatus){
		cout<<endl<<"*** Deleting "<<filename<<" ***"<<endl<<endl;
		 system( Form("rm %s",filename));
	}
	return bstatus;
}//MoveFileToDcache

int TestDcache(char* thisDir, char* dCacheDir){
/*      This tests the DCache write process by attempting to copy a local file to dCache. 
	If it fails, it will announce the reason for the failure. 
	Exit codes: 
	0 = everything works. 
	1 = cannot find the local directory
	2 = cannot find the dCache directory
	3 = copy failed

        This requires: #include <stdio.h> and #include <stdlib.h>
        Example: 
        thisDir = "/uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/" //must end in slash and be a full path.
        dCacheDir = "abarker/SusyLooseSkim_53X_2012/" //must end in slash and should start with abarker
        */
	char* filename = "testDcache.txt";
	bool b1 = 0==system(Form("ls %s. > %s",thisDir,filename));//test local dir path
	if(!b1){
		printf("\n\nWARNING! CANNOT FIND LOCAL DIRECTORY\n%s\n\n\n",thisDir);
		return 1;
	}
	bool b2 = 0==system(Form("ls /pnfs/cms/WAX/resilient/%s > %s",dCacheDir,filename));
	if(!b2){
		printf("\n\nWARNING! CANNOT FIND DCACHE DIRECTORY\n%s%s\n\n\n","/pnfs/cms/WAX/resilient/",dCacheDir);
		return 2;
	}
	system(Form("rm /pnfs/cms/WAX/resilient/%s%s",dCacheDir,filename));
        char* command = Form("srmcp \"file:////////%s%s\" \"srm://cmssrm.fnal.gov:8443/resilient/%s%s\"",thisDir,filename,dCacheDir,filename);
        //char* command = Form("srmcp \"file://///////uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/%s\" \"srm://cmssrm.fnal.go v:8443/resilient/abarker/SusyLooseSkim_53X_2012/%s\"",filename,filename);
        cout<<"Running test dCache Copy Command:"<<endl;
        cout<<command<<endl;
        //should come out like: 
        //srmcp "file://///////uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/testDcache.txt" "srm://cmssrm.fnal.go v:8443/resilient/abarker/SusyLooseSkim_53X_2012/testDcache.txt"%
        bool b3 = 0== system(command);
	if(!b3){
		printf("\n\nWARNING! COPY TO DCACHE FAILED\n%s\n\n\n",command);
		return 3;
	}
	system( Form("rm %s",filename));//delete the test file
	return 0;
}//MoveFileToDcache
void wtfDcache(char* file){ //complain that the move to dcache failed 
	cout<<endl<<endl<<" ******************************************************"<<endl;
	cout<<"***************** WARNING!!! *************************"<<endl;
	cout<<"***********COPY TO DCACHE FAILED!! *******************"<<endl;
	cout<<"***** FILE "<<file<<" *****"<<endl; cout<<"******************************************************"<<endl<<endl<<endl;
}

void SusyAna_superskim_Loose::Loop() {
	cout<<"hello world"<<endl;
	
	//hard code kluge
        //Long64_t start_event = 0;
        //int start_num = 0;//label number
        //int start_num = 0;//label number
	//const int n_files = 100;
	char *filename_prefix = "ReSkim53X_data_";
        //int increment = 200000;
	//char *outfilename = plotsroot.c_str();
	//char *outfilename = "firstskim53X_plots.root";
	//end hard code kluge
        //char* thisDir = "/uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/"; //must end in slash and be a full path.
	//char* dCacheDir = "abarker/SusyLooseSkim_53X_2012/"; //must end in slash and should start with abarker
	/*if( TestDcache( thisDir, dCacheDir) != 0){
		cout<<"Write attempt to dCache failed, TERMINATING!"<<endl;
		exit;
		_Exit;
		float f = 0.0/0.0;//force the program down
	}*/

	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntries();
	if(processNEvents <= 0 || processNEvents > nentries) processNEvents = nentries;
	
	std::cout << "total events in files  : " << nentries << std::endl;
	std::cout << "events to be processed : " << processNEvents << std::endl; 
	
		//Initialize Counters	
	if(printLevel > 0) std::cout << "Initialize event counters." << std::endl;
	const int NCNT = 5;
	int nCnt[NCNT];
	for(int i=0; i<NCNT; i++) nCnt[i] = 0;
	
		//cut flow
	TString  nCnt_lables[NCNT];
	nCnt_lables[0] = "no cuts";
	nCnt_lables[1] = "pass json";
	nCnt_lables[2] = "pass met filter";
	nCnt_lables[3] = "have 2 vvloose photons";
	nCnt_lables[4] = "pass mass req";
	
	
	int nFiltered = 0;
        int num = 0;
        //int label = start_num;
	cout<<"make filter file pointer"<<endl;
       	TFile* filterFile;//(Form("%s%i.root",filename_prefix,start_num),"RECREATE");
	filterFile = new TFile(Form("%s%s.root",filename_prefix,label.Data()),"RECREATE");
	filterFile->cd();
	cout<<"make filter tree pointer"<<endl;
       	TTree * filterTree = (TTree*) fChain->GetTree()->CloneTree(0);
	cout<<"done with that"<<endl;
	
	
		// open hist file and define histograms
//	TFile* fout = new TFile("hist_"+ds+".root","RECREATE");//xxx
	//TFile* fout = new TFile(outfilename,"RECREATE");//xxx
	//fout->cd();
/*	
	TH1F* h_vtxZ = new TH1F("vtxZ","Z position of the primary vertex;Z (cm);Events",100,-50.0,50.0);
	TH1F* h_bsZ = new TH1F("bsZ","Z position of the beam spot;Z (cm);Events",100,-50.0,50.0);
	TH1F* h_met = new TH1F("met","missing transverse energy;#slash{E}_{T} (GeV);Events",200,0.0,1000.0);
	TH1F* h_sumEt = new TH1F("sumEt","Scalar sum of all calorimeter energy;#sigmaE_{T} (GeV);Events",200,0.0,2000.0);
*/		
		//my histograms
	//TH1F* hdiPhoMass = new TH1F("hdiPhoMass","Di Photon Mass Sectrum",PhoMassNBins,PhoMassMin,PhoMassMax);
		// to check duplicated events
	//std::map<int, std::set<int> > allEvents;
	
		// start event looping
	Long64_t nbytes = 0, nb = 0;
	/*Long64_t jentry=0;
        while(jentry<=start_event+n_files*increment){ //added
		 jentry++;//added 
		//cout<<"load tree "<<jentry<<endl;
		 Long64_t ientry = LoadTree(jentry);
		//cout<<"GetEntry"<<endl;
      		if (ientry < 0){
		//if(LoadTree(jentry) < 0){ //load tree and ask if terminate. 
			cout<<"break1"<<endl;
			 break;
		}
      		nb = fChain->GetEntry(jentry);   nbytes += nb;
		//cout<<"got Entry"<<endl;
        	if(nb <= 0){
      		//if( fChain->GetEntry(jentry) <= 0){ //getEntry, ask if terminate. 
			cout<<endl<<"Read Error Detected, quit. jentry="<<jentry<<endl<<endl;
			cout<<"break2"<<endl;
			break;//added, main exit
		}

        if(jentry == start_event){
		//if(enableFilter) {
			cout<<"opening new file, num = "<<num<<" label = "<<label<<endl;
			cout<<"new file name: "<<Form("%s%i.root",filename_prefix,label)<<endl;
			filterFile[num] = new TFile(Form("%s%i.root",filename_prefix,label),"RECREATE");
			filterFile[num]->cd();
			//cout<<"re clone tree"<<endl;
		//}
                //filterTree[num] =fChain->CloneTree(0);
                filterTree[num] = (TTree*) fChain->GetTree()->CloneTree(0);
                //filterTree[num]->SetAutoSave();
                cout<<"File creation worked"<<endl;

        }
        else if((jentry-start_event)%increment ==0){
                cout<<"ttree break, consider writing file"<<endl;
		//if(enableFilter) {
			filterFile[num]->cd();
			filterTree[num]->Write();
			cout <<"closing file"<<endl;
			filterFile[num]->Close();
                num++;
		if(num>=n_files){
                        cout<<"break3"<<endl;
                         break;
                }
                label++;
		cout<<"opening new file, num = "<<num<<" label = "<<label<<endl;
		filterFile[num]= new TFile(Form("%s%i.root",filename_prefix,label),"RECREATE");
		filterFile[num]->cd();
                filterTree[num] = (TTree*) fChain->GetTree()->CloneTree(0);
                //filterTree[num]->SetAutoSave();
                cout<<"File swap worked"<<endl;
        }*/

	for (Long64_t jentry=0; jentry < processNEvents; jentry++) {
		
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		
		if(jentry%printInterval == 0) {
			std::cout << int(jentry) << " events processed with run="
			<< event->runNumber << ", event=" << event->eventNumber << std::endl;
		}
		
		InitializePerEvent();
		
		nCnt[0]++; // total number of events

		if(!isInJson(event->runNumber,event->luminosityBlockNumber)) continue;
		nCnt[1]++; // total number of events
		if(!event->passMetFilters()) continue;
		nCnt[2]++; // total number of events



		TString dmason_triggers[5] = {  
                "HLT_Photon36_CaloId10_Iso50_Photon22_CaloId10_Iso50", //Yutaro's study:
                "HLT_Photon36_CaloId10_Iso50_Photon22_R9Id85",
                "HLT_Photon36_R9Id85_Photon22_CaloId10_Iso50",
                "HLT_Photon36_R9Id85_Photon22_R9Id85",
		"HLT_Photon36_R9Id85_OR_CaloId10_Iso50_Photon22_R9Id85_OR_CaloId10_Iso50"}; //include this too
                bool passHLT = false;


                for (int i=0; i<5 && !passHLT; i++) {
                        passHLT |= PassTrigger(dmason_triggers[i]);
                }
                if(!passHLT) continue;




		std::vector<susy::Photon*>   vloose_photons;// (pixel veto || cs ele veto) && (H/E || stH/E) 
		std::vector<susy::Photon*>   electronish_photons;// (pixel veto || cs ele veto) && (H/E || stH/E) 
		std::map<TString, std::vector<susy::Photon> >::iterator phoMap = event->photons.find("photons");
		
		if(phoMap != event->photons.end()) {
			for(std::vector<susy::Photon>::iterator it = phoMap->second.begin(); it != phoMap->second.end(); it++) {
					// fiducial cuts. Look for only barrel now
				if(it->momentum.Et() < phoEtThresh1) continue;

				//if( it->hadTowOverEm < 0.05 || it->hadronicOverEm < 0.05  ){
				       //if((is_bar(eta) && it->sigmaIetaIeta < 0.014) ||
						       //( is_ec(eta) && it->sigmaIetaIeta < 0.035)) vloose_photons.push_back(&*it);
			       //}//end if h/e and pixel seed

				if(is_superskimmer_pho( it->momentum.Et(),
							it->caloPosition.Eta(),
							it->chargedHadronIso,
							it->neutralHadronIso,
							it->photonIso,
							it->hadTowOverEm,
							it->sigmaIetaIeta,
							it->sigmaIphiIphi,
							event->rho25) &&
						//(it->nPixelSeeds != 0 || !it->passelectronveto) //is ele. 
						(it->nPixelSeeds == 0 || it->passelectronveto) //is photon. 
				  ) vloose_photons.push_back(&*it);

				/*if(is_superskimmer_pho( it->momentum.Et(),
							it->caloPosition.Eta(),
							it->chargedHadronIso,
							it->neutralHadronIso,
							it->photonIso,
							it->hadTowOverEm,
							it->sigmaIetaIeta,
							it->sigmaIphiIphi,
							event->rho25) &&
						(it->nPixelSeeds != 0 || !it->passelectronveto) //is electron
				  ) electronish_photons.push_back(&*it);*/

			}// for all photon
		}// else
		
		if (vloose_photons.size()<2 ) continue; 
		nCnt[3]++;//have 2 photons

			// sort photons by Et
		std::sort(vloose_photons.begin(),vloose_photons.end(),EtGreater<susy::Photon>);
		if(vloose_photons[0]->momentum.Et()<(phoEtThresh0-5) || vloose_photons[1]->momentum.Et() < (phoEtThresh1-5)) continue;

		bool ok_photons = false;
		std::sort(vloose_photons.begin(),vloose_photons.end(),EtGreater<susy::Photon>);
		//keep the event if there are two vloose photons, with Pt over 36, 22 threshold and 80<mgg
		std::vector<susy::Photon*>::iterator i_p1 = vloose_photons.begin(); //int I_p1 = 0;
		std::vector<susy::Photon*>::iterator i_p2;
		while(i_p1 != vloose_photons.end()-1 && !ok_photons){
			if((*i_p1)->momentum.Et()<phoEtThresh0-5) break;
			i_p2 = i_p1+1;
			while(i_p2 != vloose_photons.end() && !ok_photons){
				if((*i_p2)->momentum.Et()<phoEtThresh1-5) break;
				float m = ((*i_p1)->momentum + (*i_p2)->momentum).M();
				if(m>70.0){
					ok_photons = true;
					//hdiPhoMass->Fill(m);
					nCnt[4]++;
				}
				i_p2++;
			}//end while2
			i_p1++;
		}//end while
		//end accept vloose photon block

			// filter conditions
		if(ok_photons) {
			nFiltered++;
			filterTree->Fill();
		}// if(enableFilter)
	} // for every jentry
	
	
	//if(enableFilter) {
	std::cout << " --------------- Filtered events --------------- " << std::endl;
	std::cout << " filtered events         : " << nFiltered << " (" << nFiltered/float(nCnt[0]) << ")" << std::endl;
	//}
	std::cout << " ----------------------------------------------- " << std::endl;
	
	
		//quick save the side band integrals. 
	//float sideband_integrals[2] = {(float)lsb_int,(float)usb_int};
	//TTree* t_sideband_integrals = Save(sideband_integrals,2,"sideband_integrals");
	//fout->cd();
	//t_sideband_integrals->Write();
	
		//support 
//	find_bkg(hMET);	
//	find_bkg(hST);	
//	find_bkg(hPtGG);	
	
	//hdiPhoMass->Write();
//	gDirectory->Append(g);
//	g->Write();
//	gDirectory->Write();
//	mgg_fit_curve->Write();
//	for (int i=0; i < nPhoMassAndBkgDists; i++) hMET[i]->Write();
//	for (int i=0; i < nPhoMassAndBkgDists; i++) hST[i]->Write();
//	for (int i=0; i < nPhoMassAndBkgDists; i++) hPtGG[i]->Write();
	

	for(int i=0; i<NCNT;i++){
		cout << nCnt[i] << " " << nCnt_lables[i] << endl;
	}
	
		
		// close the output file
	//fout->cd();
	//fout->Write();
	//fout->Close();

	//if(enableFilter) {
		printf("last time: cd\n");	
		filterFile->cd();
		printf("write, %i\n",num);	
		filterTree->Write();
		cout <<"closing last file"<<endl;
		filterFile->Close();
		//bool itWorked = MoveFileToDcache(Form("%s%i.root",filename_prefix,label), thisDir, dCacheDir, false);
		//if(!itWorked) wtfDcache(Form("%s%i.root",filename_prefix,label));//complain
	//}
	
}//end Loop





















