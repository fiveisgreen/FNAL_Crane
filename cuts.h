#ifndef _CUTS_H // if not defined
#define _CUTS_H

#include <iostream>
#include "math.h"
#include "TMath.h"
#include "TH2.h"
#include "../src/SusyEvent.h"
#include "TRandom.h"
using namespace std; 

bool is_ec(float eta);
bool is_bar(float eta);

float phoEtThresh0 = 40.;
float phoEtThresh1 = 25.;

float higgsness(float PtGG, float phoDphi, float phoMinR9, float phoEtaMax);
float Bness(float csv);
float Beauty(float csv);

	//Vgamma tight ID from 2011
bool is_tight_pho(float pt,
				  float eta,
				  float TrkIsoHollowDR04,
				  float EcalIsoDR04,
				  float HcalIsoDR04,
				  float HoverE,
				  float sigma_IetaIeta,
				  float sigmaIphiIphi,
				  float r9,
				  int hasPixelSeed,
				  float rho25);

bool is_tight_phoR9(float pt,
				  float eta,
				  float TrkIsoHollowDR04,
				  float EcalIsoDR04,
				  float HcalIsoDR04,
				  float HoverE,
				  float sigma_IetaIeta,
				  float sigmaIphiIphi,
				  float r9,
				  int hasPixelSeed,
				  float rho25);


	//pixel seed veto, H/E, and sinin only, for your skim.
bool is_vloose_pho(float pt,
				   float eta,
				   float TrkIsoHollowDR04,
				   float EcalIsoDR04,
				   float HcalIsoDR04,
				   float HoverE,
				   float sigma_IetaIeta,
				   float sigmaIphiIphi,
				   float r9,
				   int hasPixelSeed,
				   float rho25);

bool is_vloose_pho( std::vector<susy::Photon>::iterator it);
bool is_vvloose_pho( std::vector<susy::Photon>::iterator it);
bool is_vloose_if_vvloose_pho( std::vector<susy::Photon>::iterator it);

	//used in SUS-12-018 and AN-2011-515
bool is_tight_combIso( float pt,
					  float eta,
					  float TrkIsoHollowDR03,
					  float EcalIsoDR03,
					  float HcalIsoDR03,
					  float HoverE,
					  float sigma_IetaIeta,
					  float sigmaIphiIphi,
					  float r9,
					  int hasPixelSeed,
					  float rho25);

bool is_tight_combIso_BFrancis(float pt,
							   float eta,
							   float TrkIsoHollowDR03,
							   float EcalIsoDR03,
							   float HcalIsoDR03,
							   float HoverE,
							   float sigma_IetaIeta,
							   float sigmaIphiIphi,
							   float r9,
							   int hasPixelSeed,
							   float rho25);//cannonical susy photon ID
bool is_tight_susyStar(float pt,
                                                           float eta,
                                                           float TrkIsoHollowDR03,
                                                           float EcalIsoDR03,
                                                           float HcalIsoDR03,
                                                           float HoverE,
                                                           float sigma_IetaIeta,
                                                           float sigmaIphiIphi,
                                                           float r9,
                                                           int hasPixelSeed,
                                                           float rho25);

bool is_tight_ManiTripathi(
						   float pt,
						   float eta,
						   float TrkIsoHollowDR04,
						   float EcalIsoDR04,
						   float HcalIsoDR04,
						   float HoverE,
						   float sigma_IetaIeta,
						   float sigmaIphiIphi,
						   float r9,
						   int hasPixelSeed,
						   float rho25);
	
bool is_tight_2012(float pt,
				   float eta,
				   float PFchargedHadIso,
				   float PFneutralHadIso,
				   float PFphoIso,
				   float HoverE,  //single tower, same cut though
				   float sigma_IetaIeta,
				   float sigmaIphiIphi,
				   bool ChargeSafeEleVeto,
				   float rho25);
bool is_medium_2012(float pt,
					float eta,
					float PFchargedHadIso,
					float PFneutralHadIso,
					float PFphoIso,
					float HoverE,  //single tower, same cut though
					float sigma_IetaIeta,
					float sigmaIphiIphi,
					bool ChargeSafeEleVeto,
					float rho25);
bool is_loose_2012(float pt,
				   float eta,
				   float PFchargedHadIso,
				   float PFneutralHadIso,
				   float PFphoIso,
				   float HoverE,  //single tower, same cut though
				   float sigma_IetaIeta,
				   float sigmaIphiIphi,
				   bool ChargeSafeEleVeto,
				   float rho25);
bool is_loose_2012_PixelSeedVeto(float pt,
		float eta,
		float PFchargedHadIso,
		float PFneutralHadIso,
		float PFphoIso,
		float HoverE,  //single tower, same cut though
		float sigma_IetaIeta,
		float sigmaIphiIphi,
		int nPixelSeeds, //int!!
		float rho25);
bool is_loose_2012_PixelSeedReq(float pt,
		float eta,
		float PFchargedHadIso,
		float PFneutralHadIso,
		float PFphoIso,
		float HoverE,  //single tower, same cut though
		float sigma_IetaIeta,
		float sigmaIphiIphi,
		int nPixelSeeds, //int!!
		float rho25);
bool is_loose_2012_neglectPixelSeed(float pt,
		float eta,
		float PFchargedHadIso,
		float PFneutralHadIso,
		float PFphoIso,
		float HoverE,  //single tower, same cut though
		float sigma_IetaIeta,
		float sigmaIphiIphi,
		int nPixelSeeds, //int!!
		float rho25);

//for skimming, a looser version of is_loose_2012, neglects mention of pixel seed
bool is_skimmerPho_2012(float pt,
                                   float eta,
                                   float PFchargedHadIso,
                                   float PFneutralHadIso,
                                   float PFphoIso,
                                   float HoverE,  //single tower, same cut though
                                   float sigma_IetaIeta,
                                   float rho25);


bool is_superskimmer_pho(float pt,
		float eta,
		float PFchargedHadIso,
		float PFneutralHadIso,
		float PFphoIso,
		float HoverE,  //single tower, same cut though
		float sigma_IetaIeta,
		float sigmaIphiIphi,
		float rho25);

float max(float a, double b);
float MCsmear(float eta, float r9,TRandom* r);
float MCsmear_fullsim(float eta, float r9,TRandom* r);

// end prototyping

	//info on getting varriables
// bool passelectronveto = !ConversionTools::hasMatchedPromptElectron(ph->superCluster(), hElectrons, hConversions, beamspot.position());
// For 52X: use rho = double_kt6PFJets_rho_RECO

bool is_tight_pho( float pt, //differs from is_tight_ManiTripathi in the R9 cut. 
		  float eta,
		  float TrkIsoHollowDR04,
		  float EcalIsoDR04,
		  float HcalIsoDR04,
		  float HoverE,
		  float sigma_IetaIeta,
		  float sigmaIphiIphi,
		  float r9,
		  int hasPixelSeed,
		  float rho25){
	if(
	   HoverE   <0.05 &&
	   hasPixelSeed == 0 &&
	   sigma_IetaIeta > 0.001 &&
	   sigmaIphiIphi > 0.001 &&
	   ((is_bar(eta) && 
		 //		 r9 < 0.98 && //used in AN-2011/289
		 TrkIsoHollowDR04  < 2.0+0.001*pt + 0.0167*rho25 &&
		 EcalIsoDR04  < 4.2+0.006*pt + 0.183*rho25 &&
		 HcalIsoDR04  < 2.2+0.0025*pt + 0.062*rho25 &&		 
		 sigma_IetaIeta< 0.011
		 ) || (
			   is_ec(eta) && 
//		       r9 < 0.98 &&
			   TrkIsoHollowDR04  < 2.0+0.001*pt + 0.032*rho25 &&
			   EcalIsoDR04  < 4.2+0.006*pt + 0.090*rho25 &&
			   HcalIsoDR04  < 2.2+0.0025*pt + 0.180*rho25 &&		
			   sigma_IetaIeta<0.030
			   )
		)
	   
	   )return true;
	else return false;
}

bool is_tight_phoR9( float pt,
				  float eta,
				  float TrkIsoHollowDR04,
				  float EcalIsoDR04,
				  float HcalIsoDR04,
				  float HoverE,
				  float sigma_IetaIeta,
				  float sigmaIphiIphi,
				  float r9,
				  int hasPixelSeed,
				  float rho25){
	if(
	   HoverE   <0.05 &&
	   hasPixelSeed == 0 &&
	   r9 > 0.94 &&
	   sigma_IetaIeta > 0.001 &&
	   sigmaIphiIphi > 0.001 &&
	   ((is_bar(eta) &&
		 //		 r9 < 0.98 && //used in AN-2011/289
		 TrkIsoHollowDR04  < 2.0+0.001*pt + 0.0167*rho25 &&
		 EcalIsoDR04  < 4.2+0.006*pt + 0.183*rho25 &&
		 HcalIsoDR04  < 2.2+0.0025*pt + 0.062*rho25 &&
		 sigma_IetaIeta< 0.011
		 ) || (
			   is_ec(eta) &&
			   //		       r9 < 0.98 &&
			   TrkIsoHollowDR04  < 2.0+0.001*pt + 0.032*rho25 &&
			   EcalIsoDR04  < 4.2+0.006*pt + 0.090*rho25 &&
			   HcalIsoDR04  < 2.2+0.0025*pt + 0.180*rho25 &&
			   sigma_IetaIeta<0.030
			   )
		)

	   )return true;
	else return false;
}



bool is_vloose_pho( float pt,
                  float eta,
                  float TrkIsoHollowDR04,
                  float EcalIsoDR04,
                  float HcalIsoDR04,
                  float HoverE,
                  float sigma_IetaIeta,
				  float sigmaIphiIphi,
				  float r9,
                  int hasPixelSeed,
                  float rho25){
        if(
           HoverE   <0.05 &&
           hasPixelSeed == 0 &&
		   r9 < 1.0 &&
		   sigma_IetaIeta > 0.001 &&
		   sigmaIphiIphi > 0.001 &&
           ((is_bar(eta) &&
                 //TrkIsoHollowDR04  < 2.0+0.001*pt + 0.0167*rho25 &&
                 //EcalIsoDR04  < 4.2+0.006*pt + 0.183*rho25 &&
                 //HcalIsoDR04  < 2.2+0.0025*pt + 0.062*rho25 &&
                 sigma_IetaIeta< 0.011
                 ) || (
                           is_ec(eta) &&
                           //TrkIsoHollowDR04  < 2.0+0.001*pt + 0.032*rho25 &&
                           //EcalIsoDR04  < 4.2+0.006*pt + 0.090*rho25 &&
                           //HcalIsoDR04  < 2.2+0.0025*pt + 0.180*rho25 &&
                           sigma_IetaIeta<0.030
                           )
                )

           )return true;
        else return false;
}

bool is_vvloose_pho( std::vector<susy::Photon>::iterator it){
        float eta = it->caloPosition.Eta();
        return (it->hadTowOverEm < 0.05 || it->hadronicOverEm < 0.05 ) &&
            (it->passelectronveto || it->nPixelSeeds == 0 ) && 
	    ((is_bar(eta) && it->sigmaIetaIeta < 0.014) ||
	     ( is_ec(eta) && it->sigmaIetaIeta < 0.035));
}
bool is_vloose_pho( std::vector<susy::Photon>::iterator it){
	float eta = it->caloPosition.Eta();
        return (it->hadTowOverEm < 0.05 || it->hadronicOverEm < 0.05 ) &&
            (it->passelectronveto || it->nPixelSeeds == 0 ) && 
	    ((is_bar(eta) && it->sigmaIetaIeta < 0.011) ||
	     ( is_ec(eta) && it->sigmaIetaIeta < 0.030));
}
bool is_vloose_if_vvloose_pho( std::vector<susy::Photon>::iterator it){
	//assuming the photon passes is_vvloose_pho, does it pass is_vloose_pho?
	float eta = it->caloPosition.Eta();
        return ((is_bar(eta) && it->sigmaIetaIeta < 0.011) ||
	     ( is_ec(eta) && it->sigmaIetaIeta < 0.030));
}

bool is_tight_combIso( float pt,
				  float eta,
				  float TrkIsoHollowDR03,
				  float EcalIsoDR03,
				  float HcalIsoDR03,
				  float HoverE,
				  float sigma_IetaIeta,
				  float sigmaIphiIphi,
				  float r9,
				  int hasPixelSeed,
				  float rho25){
		//used in SUS-12-018 and AN-2011-515, I think. I'm using the Aeff from 2011
	if(
	   HoverE   <0.05 &&
	   hasPixelSeed == 0 &&
	   sigma_IetaIeta > 0.001 &&
	   sigmaIphiIphi > 0.001 &&
	   ((is_bar(eta) && 
		 r9<1.0 &&
		 ((TrkIsoHollowDR03 - 0.001*pt - 0.0167*rho25) +
		 (EcalIsoDR03  - 0.006*pt - 0.183*rho25) +
		  (HcalIsoDR03  - 0.0025*pt - 0.062*rho25)) < 6.0 &&
		 sigma_IetaIeta< 0.011
		 ) || (
			   is_ec(eta) && 
			   r9<=1.0 &&
			   ((TrkIsoHollowDR03 - 0.001*pt - 0.032*rho25)+
				(EcalIsoDR03 - 0.006*pt - 0.090*rho25)+
				(HcalIsoDR03  - 0.0025*pt - 0.180*rho25)) < 6.0 &&
			   sigma_IetaIeta<0.030
			   )
		)
	   
	   )return true;
	else return false;
}

bool is_tight_combIso_BFrancis(float pt,
							   float eta,
							   float TrkIsoHollowDR03,
							   float EcalIsoDR03,
							   float HcalIsoDR03,
							   float HoverE,
							   float sigma_IetaIeta,
							   float sigmaIphiIphi,
							   float r9,
							   int hasPixelSeed,
							   float rho25){
	/*Brian Francis: I have for ICHEP:
	  gamma.ecalRecHitSumEtConeDR03 - 0.080*rho25 +
	 gamma.hcalTowerSumEtConeDR03() - 0.021*rho25 +
	 gamma.trkSumPtHollowConeDR03 - 0.009*rho25
	 < 6.0
	 He and the rest of Susy don't use the end caps.
	 */
	if(
	   HoverE   <0.05 &&
	   hasPixelSeed == 0 &&
	   sigma_IetaIeta > 0.001 &&
	   sigmaIphiIphi > 0.001 &&
	   is_bar(eta) && 
		 r9<1.0 &&
		 ((TrkIsoHollowDR03 - 0.009*rho25) +
		  (EcalIsoDR03      - 0.080*rho25) +
		  (HcalIsoDR03      - 0.021*rho25)) < 6.0 &&
		 sigma_IetaIeta< 0.011
	   )return true;
	else return false;
}
bool is_tight_susyStar(float pt,
                                                           float eta,
                                                           float TrkIsoHollowDR03,
                                                           float EcalIsoDR03,
                                                           float HcalIsoDR03,
                                                           float HoverE,
                                                           float sigma_IetaIeta,
                                                           float sigmaIphiIphi,
                                                           float r9,
                                                           int hasPixelSeed,
                                                           float rho25){
        /*Just like the main susy selection, but with the end cap defined using the same iso as everything else.  */
        if(
           HoverE   <0.05 &&
           hasPixelSeed == 0 &&
           sigma_IetaIeta > 0.001 &&
           sigmaIphiIphi > 0.001 &&
           r9<1.0 &&
	   ((TrkIsoHollowDR03 - 0.009*rho25) +
              (EcalIsoDR03      - 0.080*rho25) +
	      (HcalIsoDR03      - 0.021*rho25)) < 6.0 &&
           ((is_bar(eta) && sigma_IetaIeta< 0.011) || 
           (is_ec(eta)  && sigma_IetaIeta< 0.030))
           )return true;
        else return false;
}

bool is_tight_ManiTripathi( float pt,
					  float eta,
					  float TrkIsoHollowDR04,
					  float EcalIsoDR04,
					  float HcalIsoDR04,
					  float HoverE,
					  float sigma_IetaIeta,
					  float sigmaIphiIphi,
					  float r9,
					  int hasPixelSeed,
					  float rho25){
		//from Mani Tripathy, basically 2011 EGamma selection. 
	if(
	   HoverE   <0.05 &&
	   hasPixelSeed == 0 &&
	   sigma_IetaIeta > 0.001 && // not in mani's selection, but I'm keeping it anyway. 
	   sigmaIphiIphi > 0.001 && // not in mani's selection, but I'm keeping it anyway. 
	   r9<1.0 &&
	   ((is_bar(eta) && 
		 TrkIsoHollowDR04  < 2.0+0.001*pt + 0.0167*rho25 &&
		 EcalIsoDR04  < 4.2+0.006*pt + 0.183*rho25 &&
		 HcalIsoDR04  < 2.2+0.0025*pt + 0.062*rho25 &&		 
		 sigma_IetaIeta< 0.011
		 ) || (
			   is_ec(eta) && 
			   TrkIsoHollowDR04  < 2.0+0.001*pt + 0.032*rho25 &&
			   EcalIsoDR04  < 4.2+0.006*pt + 0.090*rho25 &&
			   HcalIsoDR04  < 2.2+0.0025*pt + 0.180*rho25 &&		
			   sigma_IetaIeta<0.030
			   )
		)
	   )return true;
	else return false;
}

bool is_bar(float eta){
	if (fabs(eta)<1.4442)      return true;
	else return false;
}
bool is_ec(float eta){
	if (fabs(eta)>1.566 && fabs(eta)<2.5) return true;
	else return false;
}

	//for 2012 analysis, see here: https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedPhotonID2012#Effective_Areas_for_rho_correcti
	//correct rho using PFIso_corrected = max(PFIso - rho*EA, 0.)
	//For 52X: use rho = double_kt6PFJets_rho_RECO
float EA_charged_hadron(float SCEta){
	SCEta = fabs(SCEta);
	if (SCEta < 1.0) return 0.012;
	else if(SCEta < 1.479) return 0.010;
	else if(SCEta < 2.0) return 0.014;
	else if(SCEta < 2.2) return 0.012;
	else if(SCEta < 2.3) return 0.016;
	else if(SCEta < 2.4) return 0.020;
	else /*if(SCEta > 2.4)*/ return 0.012;
}
float EA_neutral_hadron(float SCEta){
	SCEta = fabs(SCEta);
	if (SCEta < 1.0) return 0.030;
	else if(SCEta < 1.479) return 0.057;
	else if(SCEta < 2.0) return 0.039;
	else if(SCEta < 2.2) return 0.015;
	else if(SCEta < 2.3) return 0.024;
	else if(SCEta < 2.4) return 0.039;
	else /*if(SCEta > 2.4)*/ return 0.072;
}
float EA_photon(float SCEta){
	SCEta = fabs(SCEta);
	if (SCEta < 1.0) return 0.148;
	else if(SCEta < 1.479) return 0.130;
	else if(SCEta < 2.0) return 0.112;
	else if(SCEta < 2.2) return 0.216;
	else if(SCEta < 2.3) return 0.262;
	else if(SCEta < 2.4) return 0.260;
	else /*if(SCEta > 2.4)*/ return 0.266;
}

bool is_tight_2012(float pt,
				   float eta,
				   float PFchargedHadIso,
				   float PFneutralHadIso,
				   float PFphoIso,
				   float HoverE,  //single tower, same cut though
				   float sigma_IetaIeta,
				   float sigmaIphiIphi,
				   bool ChargeSafeEleVeto,
				   float rho25){
		//claimed to be 70% efficint in the barrel, 65% in the ec
		//source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonID2012
	PFchargedHadIso = max(PFchargedHadIso - rho25*EA_charged_hadron(eta),0.);
	PFneutralHadIso = max(PFneutralHadIso - rho25*EA_neutral_hadron(eta),0.);
	PFphoIso = max(PFphoIso - rho25*EA_photon(eta),0.);
	if( HoverE   <0.05 &&
	   sigma_IetaIeta > 0.001 &&
	   sigmaIphiIphi > 0.001 &&
	   (ChargeSafeEleVeto) &&
	   ((is_bar(eta) && 
		 PFchargedHadIso  < 0.7 &&
		 PFneutralHadIso  < 0.4+0.04*pt &&
		 PFphoIso  < 0.5+0.005*pt &&
		 sigma_IetaIeta< 0.011
		 ) || (
			   is_ec(eta) && 
			   PFchargedHadIso  < 0.5 &&
			   PFneutralHadIso  < 1.5+0.04*pt &&
			   PFphoIso  < 1.0+0.005*pt &&		 
			   sigma_IetaIeta<0.031
			   )
		))return true;
	else return false;
}

bool is_medium_2012(float pt,
				   float eta,
				   float PFchargedHadIso,
				   float PFneutralHadIso,
				   float PFphoIso,
				   float HoverE,  //single tower, same cut though
				   float sigma_IetaIeta,
					float sigmaIphiIphi,
				   bool ChargeSafeEleVeto,
				   float rho25){
		//claimed to be 80% efficint in the barrel, 75% in the ec
		//source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonID2012
	PFchargedHadIso = max(PFchargedHadIso - rho25*EA_charged_hadron(eta),0.);
	PFneutralHadIso = max(PFneutralHadIso - rho25*EA_neutral_hadron(eta),0.);
	PFphoIso = max(PFphoIso - rho25*EA_photon(eta),0.);
	if( HoverE   <0.05 &&
	   sigma_IetaIeta > 0.001 &&
	   sigmaIphiIphi > 0.001 &&
	   (ChargeSafeEleVeto) &&
	   ((is_bar(eta) && 
		 PFchargedHadIso  < 1.5 &&
		 PFneutralHadIso  < 1.0+0.04*pt &&
		 PFphoIso  < 0.7+0.005*pt &&
		 sigma_IetaIeta< 0.011
		 ) || (
			   is_ec(eta) && 
			   PFchargedHadIso  < 1.2 &&
			   PFneutralHadIso  < 1.5+0.04*pt &&
			   PFphoIso  < 1.0+0.005*pt &&		 
			   sigma_IetaIeta<0.033
			   )
		))return true;
	else return false;
}
bool is_loose_2012(float pt,
				   float eta,
				   float PFchargedHadIso,
				   float PFneutralHadIso,
				   float PFphoIso,
				   float HoverE,  //single tower, same cut though
				   float sigma_IetaIeta,
				   float sigmaIphiIphi,
				   bool ChargeSafeEleVeto,
				   float rho25){
		//claimed to be 90% efficint in the barrel, 85% in the ec
		//source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonID2012
	//if(PFchargedHadIso< 0.001 && PFneutralHadIso < 0.001 && PFphoIso < 0.001 && 
	   //PFchargedHadIso>-0.001 && PFneutralHadIso >-0.001 && PFphoIso >-0.001) printf("akk, it didn't take\n");
	//else printf("ok\n");

	PFchargedHadIso = max(PFchargedHadIso - rho25*EA_charged_hadron(eta),0.);
	PFneutralHadIso = max(PFneutralHadIso - rho25*EA_neutral_hadron(eta),0.);
	PFphoIso = max(PFphoIso - rho25*EA_photon(eta),0.);
	if( HoverE   <0.05 &&
	   sigma_IetaIeta > 0.001 &&
	   sigmaIphiIphi > 0.001 &&
	   (ChargeSafeEleVeto) &&
	   ((is_bar(eta) && 
		 PFchargedHadIso  < 2.6 &&
		 PFneutralHadIso  < 3.5+0.04*pt &&
		 PFphoIso  < 1.3+0.005*pt &&
		 sigma_IetaIeta< 0.012
		 ) || (
			   is_ec(eta) && 
			   PFchargedHadIso  < 2.3 &&
			   PFneutralHadIso  < 2.9+0.04*pt &&
			   //PFphoIso  < 1.0+0.005*pt &&	//yes really, no PhoIsoCut..
			   sigma_IetaIeta<0.034
			   )
		))return true;
	else{
		 return false;
	}
}

bool is_loose_2012_PixelSeedVeto(float pt,
				   float eta,
				   float PFchargedHadIso,
				   float PFneutralHadIso,
				   float PFphoIso,
				   float HoverE,  //single tower, same cut though
				   float sigma_IetaIeta,
				   float sigmaIphiIphi,
				   int nPixelSeeds,
				   float rho25){
		//Just like loose_2012 but replace the conversion safe electron veto with a pixel seed veto.
	
	PFchargedHadIso = max(PFchargedHadIso - rho25*EA_charged_hadron(eta),0.);
	PFneutralHadIso = max(PFneutralHadIso - rho25*EA_neutral_hadron(eta),0.);
	PFphoIso = max(PFphoIso - rho25*EA_photon(eta),0.);
	if( HoverE   <0.05 &&
	   nPixelSeeds == 0 &&
	   sigma_IetaIeta > 0.001 &&
	   sigmaIphiIphi > 0.001 &&
	   ((is_bar(eta) &&
		 PFchargedHadIso  < 2.6 &&
		 PFneutralHadIso  < 3.5+0.04*pt &&
		 PFphoIso  < 1.3+0.005*pt &&
		 sigma_IetaIeta< 0.012
		 ) || (
			   is_ec(eta) &&
			   PFchargedHadIso  < 2.3 &&
			   PFneutralHadIso  < 2.9+0.04*pt &&
			   //yes really, no PhoIsoCut..
			   sigma_IetaIeta<0.034
			   )
		))return true;
	else{
		return false;
	}
}

bool is_loose_2012_PixelSeedReq(float pt,
								 float eta,
								 float PFchargedHadIso,
								 float PFneutralHadIso,
								 float PFphoIso,
								 float HoverE,  //single tower, same cut though
								 float sigma_IetaIeta,
								 float sigmaIphiIphi,
								 int nPixelSeeds,
								 float rho25){
		//This is to identify Electrons
		//Just like loose_2012 but neglects the conversion safe electron veto and Requires a pixel seed, so invert the pixel seed requirement

	PFchargedHadIso = max(PFchargedHadIso - rho25*EA_charged_hadron(eta),0.);
	PFneutralHadIso = max(PFneutralHadIso - rho25*EA_neutral_hadron(eta),0.);
	PFphoIso = max(PFphoIso - rho25*EA_photon(eta),0.);
	if( HoverE   <0.05 &&
	   nPixelSeeds > 0 && //select ele!!
	   sigma_IetaIeta > 0.001 &&
	   sigmaIphiIphi > 0.001 &&
	   ((is_bar(eta) &&
		 PFchargedHadIso  < 2.6 &&
		 PFneutralHadIso  < 3.5+0.04*pt &&
		 PFphoIso  < 1.3+0.005*pt &&
		 sigma_IetaIeta< 0.012
		 ) || (
			   is_ec(eta) &&
			   PFchargedHadIso  < 2.3 &&
			   PFneutralHadIso  < 2.9+0.04*pt &&
			   //yes really, no PhoIsoCut..
			   sigma_IetaIeta<0.034
			   )
		))return true;
	else{
		return false;
	}
}

bool is_loose_2012_neglectPixelSeed(float pt,
								 float eta,
								 float PFchargedHadIso,
								 float PFneutralHadIso,
								 float PFphoIso,
								 float HoverE,  //single tower, same cut though
								 float sigma_IetaIeta,
								 float sigmaIphiIphi,
								 int nPixelSeeds,
								 float rho25){
		//This is to identify Electrons
		//Just like loose_2012 but neglects the seed requirement entirely.

	PFchargedHadIso = max(PFchargedHadIso - rho25*EA_charged_hadron(eta),0.);
	PFneutralHadIso = max(PFneutralHadIso - rho25*EA_neutral_hadron(eta),0.);
	PFphoIso = max(PFphoIso - rho25*EA_photon(eta),0.);
	if( HoverE   <0.05 &&
	   //nPixelSeeds > 0 && //select ele!!
	   sigma_IetaIeta > 0.001 &&
	   sigmaIphiIphi > 0.001 &&
	   ((is_bar(eta) &&
		 PFchargedHadIso  < 2.6 &&
		 PFneutralHadIso  < 3.5+0.04*pt &&
		 PFphoIso  < 1.3+0.005*pt &&
		 sigma_IetaIeta< 0.012
		 ) || (
			   is_ec(eta) &&
			   PFchargedHadIso  < 2.3 &&
			   PFneutralHadIso  < 2.9+0.04*pt &&
			   //yes really, no PhoIsoCut..
			   sigma_IetaIeta<0.034
			   )
		))return true;
	else{
		return false;
	}
}

bool is_skimmerPho_2012(float pt,
                                   float eta,
                                   float PFchargedHadIso,
                                   float PFneutralHadIso,
                                   float PFphoIso,
                                   float HoverE,  //single tower, same cut though
                                   float sigma_IetaIeta,
                                   float rho25){
	//This is a loosened up version of is_Loose_2012 for use in skimming
	//in particular it has no electron veto or pixel veto

        PFchargedHadIso = max(PFchargedHadIso - rho25*EA_charged_hadron(eta),0.);
        PFneutralHadIso = max(PFneutralHadIso - rho25*EA_neutral_hadron(eta),0.);
        PFphoIso = max(PFphoIso - rho25*EA_photon(eta),0.);
        if( HoverE   <0.10 &&
           //sigma_IetaIeta > 0.001 &&
           //sigmaIphiIphi > 0.001 &&
           //(ChargeSafeEleVeto) &&
           ((is_bar(eta) &&
                 PFchargedHadIso  < 3 && //2.6 &&
                 PFneutralHadIso  < 4+0.06*pt && // 3.5+0.04*pt &&
                 PFphoIso  < 1.6+0.007*pt && // 1.3+0.005*pt &&
                 sigma_IetaIeta< 0.014 // 0.012
                 ) || (
                           is_ec(eta) &&
                           PFchargedHadIso  < 3.0 && // < 2.3 &&
                           PFneutralHadIso  < 3.5+0.06*pt && // < 2.9+0.04*pt &&
                           sigma_IetaIeta<0.038 //sigma_IetaIeta<0.034
                           )
                ))return true;
        else{
                 return false;
        }
}

bool is_superskimmer_pho(float pt,
		float eta,
		float PFchargedHadIso,
		float PFneutralHadIso,
		float PFphoIso,
		float HoverE,  //single tower, same cut though
		float sigma_IetaIeta,
		float sigmaIphiIphi,
		float rho25){
		//This is to identify Electrons
		//Just like loose_2012 but neglects the seed requirement entirely.
		//We also multiply the pt scalings by w to make sure they don't interfere
		//with photon energy scale corrections.
		//so with this we skim out the cuts up to loose, but neglect pv/ele veto
		//and allow ourselves enough leeway to mess with 
		//the photon energy scales without interference
	PFchargedHadIso = max(PFchargedHadIso - rho25*EA_charged_hadron(eta),0.);
	PFneutralHadIso = max(PFneutralHadIso - rho25*EA_neutral_hadron(eta),0.);
	PFphoIso = max(PFphoIso - rho25*EA_photon(eta),0.);
	float w = 2;
	if( HoverE   <0.05 &&
	   //nPixelSeeds > 0 && //select ele!!
	   sigma_IetaIeta > 0.001 &&
	   sigmaIphiIphi > 0.001 &&
	   ((is_bar(eta) &&
		 PFchargedHadIso  < 2.6 &&
		 PFneutralHadIso  < 3.5+w*0.04*pt &&
		 PFphoIso  < 1.3+w*0.005*pt &&
		 sigma_IetaIeta< 0.012
		 ) || (
			   is_ec(eta) &&
			   PFchargedHadIso  < 2.3 &&
			   PFneutralHadIso  < 2.9+w*0.04*pt &&
			   //yes really, no PhoIsoCut..
			   sigma_IetaIeta<0.034
			   )
		))return true;
	else{
		return false;
	}
}//end is_superskimmer_pho

float max(float a, double b){
	if(a >= (float)b) return a;
	return (float)b;
}
float MCsmear(float eta, float r9,TRandom* r){
	//returns a random value for the MCsmearing scale factor. 
	//these values come out of combineSmearing.C and are done with mst_185_mhiggsino_150 on fast sim and fullsim. 
	//you need to give it a TRandom* so that you don't generate the same seed every time it's called 
	//setup with TRandom *r = new TRandom();
	float sigma;
	eta = fabs(eta);
	////////////////////////this block is generated automatically by combineSmearing.C

	if(is_bar(eta)){
		if(eta < 1){
			if(r9>0.94) sigma = 0.009213;
			else sigma = 0.010046;
		}
		else{
			if(r9>0.94) sigma = 0.016318;
			else sigma = 0.017477;
		}
	}
	else{ //ec
		if(eta < 2){
			if(r9>0.94) sigma = 0.029787;
			else sigma = 0.029989;
		}
		else{
			if(r9>0.94) sigma = 0.034883;
			else sigma = 0.024528;
		}
	}

//////////////////////
	//TRandom r;
	return r->Gaus(1,sigma);
}
float MCsmear_fullsim(float eta, float r9,TRandom* r){

	//returns a random value for the MCsmearing scale factor. 
	//These are the smearing factors from the higgs analysis and are to be used only on Fullsim
	//you need to give it a TRandom* so that you don't generate the same seed every time it's called 
	//setup with TRandom *r = new TRandom();
	float sigma;
	eta = fabs(eta);

	if(is_bar(eta)){
		if(eta < 1){
			if(r9>0.94) sigma = 0.0113;
			else sigma = 0.0109;
		}
		else{
			if(r9>0.94) sigma = 0.0171;
			else sigma = 0.0203;
		}
	}
	else{ //ec
		if(eta < 2){
			if(r9>0.94) sigma = 0.0309;
			else sigma = 0.0278;
		}
		else{
			if(r9>0.94) sigma = 0.0372;
			else sigma = 0.0375;
		}
	}

	return r->Gaus(1,sigma);
}//end MCsmear_fullsim

float higgsness(float PtGG, float phoDphi, float phoMinR9, float phoEtaMax){
	float sb_phi = 0.25;
	if(phoDphi < 1.8) sb_phi = 1.0;
	else if(phoDphi < 2.6) sb_phi = 0.429;
	else if(phoDphi < 2.9) sb_phi = 0.444;
	else sb_phi = 0.25;

	float sb_eta = 0.05;
	if(phoDphi < 1.0f) sb_eta = 1.0;
	else if(phoDphi < 1.4442f) sb_eta = 0.667;
	else if(phoDphi < 2.0f) sb_eta = 0.136;
	else sb_phi = 0.05;

	float sb_r9;
	if(phoEtaMax > 0.92) sb_r9 = 1;
	else sb_phi = sb_r9 = exp(2*(sb_phi-0.9));

	return PtGG*sb_r9*sb_eta*sb_phi;
}
float Bness(float csv){
	if(csv < 0.244) return 0;
	return pow(csv,0.222);
}
float Beauty(float csv){
	return sin(1.57079635*pow(csv,0.5435));
}


#endif
