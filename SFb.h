#ifndef _SLB_H // if not defined
#define _SLB_H

#include <iostream>
//#include "math.h"
//#include "TMath.h"
//#include "TH2.h"
using namespace std;

// The numbers come from here: 
// https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagPOG#2012_Data_and_MC_Moriond13_presc
// They are scale factors for the MC b-tag efficiency. 

//*****************************//
float ptMin[] = {20, 30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 600};
float ptMax[] = {30, 40, 50, 60, 70, 80,100, 120, 160, 210, 260, 320, 400, 500, 600, 800};
float SFb_error_CSVL[] = {
	0.0484285,
	0.0126178,
	0.0120027,
	0.0141137,
	0.0145441,
	0.0131145,
	0.0168479,
	0.0160836,
	0.0126209,
	0.0136017,
	0.019182,
	0.0198805,
	0.0386531,
	0.0392831,
	0.0481008,
	0.0474291 };
float SFb_error_CSVM[] = {
	0.0554504,
	0.0209663,
	0.0207019,
	0.0230073,
	0.0208719,
	0.0200453,
	0.0264232,
	0.0240102,
	0.0229375,
	0.0184615,
	0.0216242,
	0.0248119,
	0.0465748,
	0.0474666,
	0.0718173,
	0.0717567 };
float SFb_error_CSVT[] = {
	0.0567059,
	0.0266907,
	0.0263491,
	0.0342831,
	0.0303327,
	0.024608,
	0.0333786,
	0.0317642,
	0.031102,
	0.0295603,
	0.0474663,
	0.0503182,
	0.0580424,
	0.0575776,
	0.0769779,
	0.0898199 };

int getBin(float Pt); 
float getSFbCSVL(float Pt,bool useTTbar = false);
float getSFbErrorCSVL(float Pt,bool useTTbar = false);
float getSFbCSVM(float Pt,bool useTTbar = false);
float getSFbErrorCSVM(float Pt,bool useTTbar = false);
float getSFbCSVT(float Pt,bool useTTbar = false);
float getSFbErrorCSVT(float Pt,bool useTTbar = false);
float screanBtagEff(int which, float beff);


//*********************************//
int getBin(float Pt){
	for(int i = 0; i< 16; i++){
		if(Pt >= ptMin[i] && Pt < ptMax[i]) return i;
	}
	return -1;
}

float getSFbCSVL(float Pt,bool useTTbar){
// Tagger: CSVL within 20 < pt < 800 GeV, abs(eta) < 2.4, 
	if(useTTbar) return 1.008;
	return 0.981149*((1.+(-0.000713295*Pt))/(1.+(-0.000703264*Pt)));
}

float getSFbErrorCSVL(float Pt,bool useTTbar){
	if(useTTbar) return 0.023;
	if(Pt < 20.0) return 0.05;
	else if(Pt > 800.0) return 0.05;
	return SFb_error_CSVL[getBin(Pt)];
}//end getSFbErrorCSVL
 
float getSFbCSVM(float Pt,bool useTTbar){
 //Tagger: CSVM within 20 < pt < 800 GeV, abs(eta) < 2.4, 
	if(useTTbar) return 0.963;
	return 0.726981*((1.+(0.253238*Pt))/(1.+(0.188389*Pt)));
}
float getSFbErrorCSVM(float Pt,bool useTTbar){
	if(useTTbar) return 0.020;
        if(Pt < 20.0) return 0.06;
        else if(Pt > 800.0) return 0.08;
        return SFb_error_CSVM[getBin(Pt)];
}//end getSFbErrorCSVL
 
float getSFbCSVT(float Pt,bool useTTbar){
	if(useTTbar) return 0.947;
	// Tagger: CSVT within 20 < pt < 800 GeV, abs(eta) < 2.4, 
	return 0.869965*((1.+(0.0335062*Pt))/(1.+(0.0304598*Pt)));
}
float getSFbErrorCSVT(float Pt,bool useTTbar){
	if(useTTbar) return 0.025;
        if(Pt < 20.0) return 0.06;
        else if(Pt > 800.0) return 0.09;
        return SFb_error_CSVT[getBin(Pt)];
}//end getSFbErrorCSVL


float screanBtagEff(int which, float beff){
	//check that the b-tag efficiency isn't 0, meaning that it wasn't filled in the histogram. 
	//return something sensible all the time. 
	//which indicates the CSV level 0 = L; 2 = T
	if(beff > 0.00001) return beff;
	else if(which == 0) return 0.8;	//CSVL
	else if(which == 1) return 0.6;	//CSVM
	else if(which == 2) return 0.5;	//CSVT
	else return 1.0;
}//end screanBtagEff
 
/* Tagger: TCHPT within 20 < pt < 800 GeV, abs(eta) < 2.4,
 SFb = 0.305208*((1.+(0.595166*Pt))/(1.+(0.186968*Pt)));
 SFb_error[] = {
 0.0725549,
 0.0275189,
 0.0279695,
 0.028065,
 0.0270752,
 0.0254934,
 0.0262087,
 0.0230919,
 0.0294829,
 0.0226487,
 0.0272755,
 0.0303747,
 0.051223,
 0.0542895,
 0.0589887,
 0.0584216 };
 
 Tagger: JPL within 20 < pt < 800 GeV, abs(eta) < 2.4, 
 SFb = 0.977721*((1.+(-1.02685e-06*Pt))/(1.+(-2.56586e-07*Pt)));
 SFb_error[] = {
 0.0456879,
 0.0229755,
 0.0229115,
 0.0219184,
 0.0222935,
 0.0189195,
 0.0237255,
 0.0236069,
 0.0159177,
 0.0196792,
 0.0168556,
 0.0168882,
 0.0348084,
 0.0355933,
 0.0476836,
 0.0500367 };
 
 Tagger: JPM within 20 < pt < 800 GeV, abs(eta) < 2.4, 
 SFb = 0.87887*((1.+(0.0393348*Pt))/(1.+(0.0354499*Pt)));
 SFb_error[] = {
 0.0584144,
 0.0304763,
 0.0311788,
 0.0339226,
 0.0343223,
 0.0303401,
 0.0329372,
 0.0339472,
 0.0368516,
 0.0319189,
 0.0354756,
 0.0347098,
 0.0408868,
 0.0415471,
 0.0567743,
 0.0605397 };
 
 Tagger: JPT within 20 < pt < 800 GeV, abs(eta) < 2.4, 
 SFb = 0.802097*((1.+(0.013219*Pt))/(1.+(0.0107842*Pt)));
 SFb_error[] = {
 0.0673183,
 0.0368276,
 0.037958,
 0.0418136,
 0.0463115,
 0.0409334,
 0.0436405,
 0.0419725,
 0.0451182,
 0.0394386,
 0.0423327,
 0.0393015,
 0.0499883,
 0.0509444,
 0.0780023,
 0.0856582 };
*/

/********** END Muon + Jet Results *******************/

/*********TTBAR RESULTS***********/
//------
//Tagger: CSV, abs(eta)<2.4, Pt = discriminator value,0.15<Pt<0.95
//Functional form:
/*SFb = 0.607239*Pt*Pt*Pt*Pt+-1.49984*Pt*Pt*Pt+1.3473*Pt*Pt+-0.599888*Pt+1.09396
SFb uncertainty = 0.02
//SFc = SFb 
SFc uncertainty = 0.02
 
//Working Points: 
CSV_L =  1.008 +/- 0.023
CSV_M =  0.963 +/- 0.020
CSV_T =  0.947 +/- 0.025

//------
//Tagger: JP, abs(eta)<2.4, Pt = discriminator value,0.15<Pt<1
//Functional form:
SFb = 1.02065*Pt*Pt*Pt*Pt+-2.55246*Pt*Pt*Pt+1.95819*Pt*Pt+-0.655278*Pt+1.06174
SFb uncertainty = 0.02
//SFc = SFb 
SFc uncertainty = 0.02
 
//Working Points: 
JP_L =  0.970 +/- 0.017
JP_M =  0.968 +/- 0.018
JP_T =  0.902 +/- 0.027
 
//------
//Tagger: TCHP, abs(eta)<2.4, Pt = discriminator value,1.2<Pt<8.5
//Functional form:
SFb = -0.000439434*Pt*Pt*Pt*Pt+0.00982901*Pt*Pt*Pt+-0.0758301*Pt*Pt+0.235126*Pt+0.664076
SFb uncertainty = 0.03
//SFc = SFb 
SFc uncertainty = 0.03
 
//Working Points:
TCHP_T =  0.911 +/- 0.027
*/
/*********END TTBAR RESULTS***********/
#endif

