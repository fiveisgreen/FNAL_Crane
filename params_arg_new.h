#ifndef _PARAMS_H // if not defined
#define _PARAMS_H

#include <iostream>
//#include "MCpoint.h"
//#include "math.h"
//#include "TMath.h"
//#include "TH2.h"
using namespace std; 

namespace params{
//data
string outroot_data = "SusyEvents_skim_2JbML.root"; //skim of the events used in analysis form big ntuples
//string outroot_data = "SusyEvents_forTMVA_data.root"; //skim of the events used in analysis form big ntuples
string plotsroot_data= "raw_plots_data_GLL12ABC.root"; // raw plots from ana.C
string logplotsroot_data= "raw_plots_data_GLL12ABC.log"; // raw plots from ana.C
string plotsAndBackground_data = "plotsWithBackground_dataGLL12.root";
string logplotsAndBackground_data = "plotsWithBackground_dataGLL12.log";
string formatedplotsroot_data= "formatted_plots_dataGLL12.root";
bool useMETFilter_data = true;
bool useMVAphoP = true;

//Photon Type
//only one of these is allowed to be true at a time, otherwise it takes the first true one.
bool useSusyLoose_EleVeto = false;//default
bool useSusyLoose_PixelVeto = false;
bool useSusyLoose_PixelSeedMatch = true;//really ele
bool useSusyMedium_EleVeto = false;


//MC
bool useMETFilter_mc = false;
bool makeEventsList = false;
bool makeTMVAlist = false;
bool showTag = true; //this blinds out the tag region when false;
bool useElectroHiggs = false; //if false, throw out all the MC events without a stop in them. 

long int probeevent = 10496;

string which_MC_to_use2 = "mst_235_mu_225";

string which_higgsMC_to_use2 = "GluGluToHToGG";
//string which_higgsMC_to_use2 = "GluGluToHToGG_quick"; //shorter version of GluGluToHToGG
//string which_higgsMC_to_use2 = "VBF_HToGG";
//string which_higgsMC_to_use2 = "VH_HToGG";

//shift jet energy corrections and all up/down by one sigma. 
int bumpJEC = 0;//is allowed to be +- 1 and 0	//assuems 2% uncertainty.  
int bumpBtagEff = 0;//is allowed to be +- 1 and 0 
//string btageff_file = "b_tag_eff.root";//control given over to MCpoint

//Data+MC
string formatedplotsroot_combined= "formatted_plots_dataMC.root"; //output from format_plots.C
string plotsdir = "plots_bbin/";

	///LISTS FOR INDEXING
const int nPhoMassAndBkgDists = 9;
string s_MassBkgDists[nPhoMassAndBkgDists] = {"lowSB","tag","upperSB","bkg","tag_subbkg","lowSB_scaled","upperSB_scaled","lsb_over_usb","tag_over_bkg"};
const int nEventTopologies = 26; // the number of types of cuts selected, like 1JB...
string s_EventTopology[nEventTopologies] = { 
"NULL","2JbML","2JbMLgbar2", "2JbMLm20", "2JbMLgbar1", "2JbMLm20gbar2",
"2JbML!Gbar2Mbb", "2JbML!Gbar2Mbb!","3JbMLLGbar2", "4JbMLLLGbar2","2JbML!Gbar2",
"2JbTLgbar2","2JbMLgbar2Tpho", "2JbTLgbar2Tpho", "2JbMLgbar2Mpho", "2JbTLgbar2Mpho",
"1lep", "2lep","2JbMLgbar2bestOn","2JbMLgbar2bestOff","2JbTLgbar2bestOn","2JbTLgbar2bestOff",
"2JbTgbar2","2JbTMgbar2","2JbMMgbar2","2JbTTgbar2"};

const int nEventTopologies_limit = 20; // the number of types of cuts selected, like 1JB...
string s_EventTopology_limit[nEventTopologies_limit] = {
	"NULL","2JbML","2JbMLgbar2", "2JbMLm20", "2JbMLgbar1", "2JbMLm20gbar2",
	"2JbTLgbar2","2JbMLgbar2Tpho", "2JbTLgbar2Tpho", "2JbMLgbar2Mpho", "2JbTLgbar2Mpho",
	"1lep", "2lep","bbin3","bbinMLbest","bbinTLbest",
	"2JbTgbar2","2JbTMgbar2","2JbMMgbar2","2JbTTgbar2"};



/*
"NULL","2JbML","2JbMLgbar2", "2JbMLm20", "2JbMLm20gbar1", "2JbMLm20gbar2",
"2JbML!m20Gbar2Mbb", "2JbML!m20Gbar2Mbb!","3JbMLLm20Gbar2", "4JbMLLLm20Gbar2","2JbML!m20Gbar2",
"2JbTLm20gbar2","2JbMLm20gbar2Tpho", "2JbTLm20gbar2Tpho", "2JbMLm20gbar2Mpho", "2JbTLm20gbar2Mpho"};
*/


/*"NULL",        		 "2JbMLm20",	"2JbMLm20gbar1", "2JbMLm20gbar2",	//"2JbMLm20gbar1jdn15",	
//"2JbMLm20gbar2n15",	 "2JHjjgbar1",	 "2JHjjgbar2",	 "2JHjjgbar1jdn15",	 "2JHjjgbar2jdn15",
"4JbMLm20gbar1",	"4JbMLm20gbar2",  "4JbMm20gbar1","4JbMm20gbar2", 	"4JbLLLLm20gbar1",	
"4JbLLLLm20gbar2",	 "2JbTLm20",	"4JbTm20",	"4JbTLm20",	 	"8Jgbar1",	
"8Jgbar2",	 	"0!lep",        "1!lep",        "1lep",			"1Ele1Mu",	
"3lep",		 	"2lep",         "2lepZ",        "1Mu",			"2Tphos"};*/


/*
string s_EventTopology[nEventTopologies] = { 
"NULL",         "2Jm20",        "3Jm20",        "3JbMm20",      "3JbLm20",
"4Jm20",        "metCut",       "4JbLLLLm20",   "2JbMLm20", 	"4JbMLm20",
"4JbMLLm20",    "4JbMLLLm20",   "4JbMm20", 	"8J",	 	"1Mu", 
"0!lep",        "1!lep",        "1lep",		"1ele1mu",	"3lep",
"2lep",         "2lepZ",        "2JHjj",        "2JHbM",       "2JbM",
"2JbML", 	"2Tphos"};
*/

const int nKinemVars_all = 54;		//always keep MET in the first position, it's special.
string s_KinemVars_all[nKinemVars_all] = {
"MET","ST","HT","MHT","PtGG",
"phoPt0","phoPt1","phoPhi","phoEta","phoEtaMax",
"phoEtaMin","nJets","nLep","nMu","nEle",
"nBjets","MTphoMET","cosThetaStar","phoDPhi","phoDEta",
"dPhiPhoMet","jetPt","jetEta","jetPhi","phoMinR9",
"dijetDPhi01","dijetDEta01","dijetM01","dijetPt01","dPhiJetMet", //suggest killing dijetDEta01..., consolodate it. 
"Bt","bestMjj","bestMbb","allMjj","allMbb",
"Mbb01","Mbb01gg01",
"MJJ01gg01","Mleplep", "MZllHgg","MTggMET","MTlepMET",
"HGt","HGt_prime","dPhiHG","dPhiHG_prime","HLMGt",
"jetEtaMin","Bness1",
"LHT","BTL","BTM","BTT","LepT"};

		//Will be used if either bumpBtagEff != 0 or bumpJEC != 0. 
		//list of kin vars to make limits on. These must be singly-filled per event and otherwise make sense.
const int nKinemVars_limit = 41;
string s_KinemVars_limit[nKinemVars_limit] = {
"MET","ST","HT","MHT","PtGG", 
"phoPt0","phoPt1","phoEtaMax", 
"phoEtaMin","nJets","nLep","nMu","nEle", 
"nBjets","cosThetaStar","phoDPhi","phoDEta","phoMinR9", 
"dijetDPhi01","dijetDEta01","dijetM01","dijetPt01", 
"Bt","bestMjj","bestMbb", "Mbb01","Mbb01gg01", 
"MJJ01gg01","Mleplep", "MZllHgg","MTggMET","MTlepMET", 
"dPhiHG","dPhiHG_prime", "jetEtaMin","Bness1",
"LHT","BTL","BTM","BTT","LepT"};


/*
Useless varriables that I'm tired of having in front of me: 
MTphoMET and dPhiPhoMET -- just let there be a cominatoric bkg. 
diJet eta01 
*/

//MTlepMET, use all permutations instead of leading lepton.  
//create allMjj nad allMbb

//"dijetDPhi01"
/*{
"MET","ST","HT","MHT","PtGG",
"PhiGG","EtaGG","phoPt0","phoPt1","phoPhi0",
"phoPhi1","phoEta0","phoEta1","phoEtaMax","phoEtaMin",
"phoDR", "nJets","nLep","nMu","nEle",
"nBjets","MTpho0MET","MTpho1MET","cosThetaStar","phoDPhi",
"dPhiPho0Met","dPhiPho1Met", "PitGG","jetPt","jetEta",
"jetPhi","dPhiJetMet","dijetDPhi01","dijetDR01","dijetDEta01",
"dijetEta01","dijetM01","dijetPt01","dPhiJet0Met","dPhiJet1Met",
"Bt","bestMjj","bestMbb","Mbb01","Mbb01gg01",
"MJJ01gg01","Mleplep", "MZllHgg","MTggMET","MTlepMET",
"HGt","HGt_prime","dPhiHG","dPhiHG_prime","HLMGt"};*/





float mHiggs = 125.5f; //higgs mass. 
float mHwidth = 11.f; //width of the tag region 5 gives 80%, 7 is probably too broad, but brings it up to 86
float l_tag_sb_gap = 2.0f;//lower sideband gap
float u_tag_sb_gap = 2.0f;//upper sideband gap
float l_sidebandwidth = 15.f;//lower sideband width
float u_sidebandwidth = 30.f;//upper sideband width
float tag_ub = mHiggs + 0.5*mHwidth;
float tag_lb = mHiggs - 0.5*mHwidth;
float usb_lb = tag_ub+u_tag_sb_gap;//upper side band lower bound
float usb_ub = usb_lb+u_sidebandwidth;
float lsb_ub = tag_lb-l_tag_sb_gap;
float lsb_lb = lsb_ub-l_sidebandwidth;

	//                                mHiggs
	// | sidebandwidth | tag_sb_gap | mHwidth | tag_sb_gap | sidebandwidth | 
	//lsb_lb         lsb_ub       tag_lb    tag_ub        usb_lb        usb_ub

const float Integrated_Luminosity_Data = 18.304;// 1/fb
//float lumiscale = (integLumi*crossSection)/((float)nMCGenerated);
/*
 st 350 h0 150: cross section is 447.4 fb
 st 250 h0 150: cross section is 2.059D-09 mb = 2059 fb
 st 250 h0 200: cross section is 1.443D-09 mb = 1443 fb
 h0 200: cross section is 2.990D-10 mb  = 299.0 fb
 ho140: cross section is 1.195D-09 mb = 1195 fb
 */

int PhoMassNBins = 130;
float PhoMassMin = 50.0f;
float PhoMassMax = 180.0f;

} //end namespace params
#endif

