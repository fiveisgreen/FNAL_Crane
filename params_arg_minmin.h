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
string plotsAndBackground_data_lim = "plotsWithBackground_data_lim.root";
string logplotsAndBackground_data_lim = "plotsWithBackground_data_lim.log";
string integSyst_data_lim = "integral_systematics_data_lim.txt";
string formatedplotsroot_data= "formatted_plots_dataGLL12.root";
bool useMETFilter_data = true;
bool useMVAphoP = true;

//Photon Type
//only one of these is allowed to be true at a time, otherwise it takes the first true one.
bool useSusyLoose_EleVeto = false;//default
bool useSusyLoose_PixelVeto = true;
bool useSusyLoose_PixelSeedMatch = false;//really ele
bool useSusyLoose_PS_ElePho= false;//one ele, one pho baised on pixel seed
bool useSusyMedium_EleVeto = false;


//MC
bool useMETFilter_mc = false;
bool makeEventsList = false;
bool makeTMVAlist = false;
bool showTag = true; //this blinds out the tag region when false;
bool preliminary = false;
bool useElectroHiggs = true; //if false, throw out all the MC events without a stop in them. 

//Limit Setting
bool remake_Limit_packages = true;
bool remake_Limit_cards    = true;
bool useHybridNew    = false; //false = Asymptotic, ture = HybridNew

int type_to_run = 10;
//10 = bbaa strong
//11 = wwaa strong
//12 = zzaa strong
//13 = ttaa strong
//20 = bbaa weak
//21 = bbaa weak
//22 = bbaa weak
//23 = bbaa weak

long int probeevent = 10496;

string which_MC_to_use2 = "mst_235_mu_225";
//string which_MC_to_use2 = "st_400_mu_300"; //more modern. 

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
//string plotsdir = "plots_higgsino/";
string plotsdir = "plots_bbin/";

	///LISTS FOR INDEXING
const int nPhoMassAndBkgDists = 9;
string s_MassBkgDists[nPhoMassAndBkgDists] = {"lowSB","tag","upperSB","bkg","tag_subbkg","lowSB_scaled","upperSB_scaled","lsb_over_usb","tag_over_bkg"};
const int nEventTopologies = 4; // the number of types of cuts selected, like 1JB...
//const int nEventTopologies = 40; // the number of types of cuts selected, like 1JB...
string s_EventTopology[nEventTopologies] = { 
	"2JbMLgbar2","2JbML!Gbar2Mbb", "2JbML!Gbar2Mbb!","3JbMLLGbar2"};//3
	//"2JbMM!Gbar2Mbb", "2JbMM!Gbar2Mbb!","3JbMMLGbar2",//3
	//"2JbML!gbar2bestOn","2JbML!gbar2bestOff", "2JbMM!gbar2bestOn","2JbMM!gbar2bestOff", //4
	//"2JbT!gbar2ProbeMJJ",
	//"23Jb01MewkMll0lepgbar2", //for WH
	//"0lep25Jb01MewkMllgbar2", "1!lep23Jb01MewkMllgbar2","1!lep23Jb01M!ewkMllgbar2",  //for WWbins //3
	//"2JbM2lepgbar2", "2JbML!1lepgbar2", "2JbML!gbar2bestOn0lep",
	//"4JbML!gbar2ewkMllbestOff0lep", "2JbML!gbar2bothOff0lep",
	//"01J0lep0Bgbar2"}; //5

		//higgs + met only: 0lep, 0B's at most one other jet,

	
		//WH
//"WHbins" = "1!lepgbar2", "23Jb01MewkMll0lepgbar2"
		//ZH
//"ZHbins" = "2lepZgbar2", "23Jb01MewkMll0lepgbar2"
		//WW
//"WWbins" = "2lepgbar2", "1!lep23Jb01MewkMllgbar2","1!lep23Jb01M!ewkMllgbar2", "0lep25Jb01MewkMllgbar2"
		//ZZ
//"ZZbins" = "3lepgbar2", "2!lepZgbar2", "1!lep23Jb01M!ewkMllgbar2", "1!lep23Jb01MewkMllgbar2", "0lep25Jb01MewkMllgbar2"
		//stop-higgsino done right:
//"SHbins" = "2JbM2lepgbar2", "2JbML!1lepgbar2", "2JbML!gbar2bestOn0lep", "4JbML!gbar2ewkMllbestOff0lep", "2JbML!gbar2bothOff0lep","3JbMLLGbar2"
	//so bestMjj is not on the Mh and no Mll combos are on the M_EWK


//"NULL","2JbML","2JbMLgbar2", "2JbMLm20", "2JbMLgbar1", "2JbMLm20gbar2",
//"2JbML!Gbar2Mbb", "2JbML!Gbar2Mbb!","3JbMLLGbar2", "4JbMLLLGbar2","2JbML!Gbar2",
//"2JbTLgbar2","2JbMLgbar2Tpho", "2JbTLgbar2Tpho", "2JbMLgbar2Mpho", "2JbTLgbar2Mpho",
//"1lep", "2lep","2JbMLgbar2bestOn","2JbMLgbar2bestOff","2JbTLgbar2bestOn","2JbTLgbar2bestOff",
//"2JbTgbar2","2JbTMgbar2","2JbMMgbar2","2JbTTgbar2"};

//"NULL","gbar2",
//"1!lep","1lep","1ele1mu","2lep", "2lepZ","3lep", 
//"1!lepgbar2","1lepgbar2","1ele1mugbar2","2lepgbar2", "2lepZgbar2",
//"23JbML!gbar2Mbb0Lep", "2JbML!gbar2Mbb0Lep",
//"2ljets", "2ljetsEWK", "2ljetsW", "2ljetsZ",
//"2JbMLgbar2","2JbMMgbar2",

const int nEventTopologies_limit = 5; // the number of types of cuts selected, like 1JB...
string s_EventTopology_limit[nEventTopologies_limit] = {
	"2JbMLgbar2", "2JbML!Gbar2Mbb", "2JbML!Gbar2Mbb!","3JbMLLGbar2", "bbin3"};




		//build a channel to catch WW...
		//1lep





//	"NULL","2JbML","2JbMLgbar2", "2JbMLm20", "2JbMLgbar1", "2JbMLm20gbar2",
//	"2JbTLgbar2","2JbMLgbar2Tpho", "2JbTLgbar2Tpho", "2JbMLgbar2Mpho", "2JbTLgbar2Mpho",
//	"1lep", "2lep","bbin3","bbinMLbest","bbinTLbest",
//	"2JbTgbar2","2JbTMgbar2","2JbMMgbar2","2JbTTgbar2"};




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

const int nKinemVars_all = 6;	//always keep MET in the first position, it's special.
string s_KinemVars_all[nKinemVars_all] = {
"MET","ST","HT","MHT","PtGG",//5
"Bt"};//4


//BMet = sum_bness * MET
//BST =  sum_bness * ST
//BPtGG= sum_bness * PtGG
//BnBjets = sum(Bness)
//BunBjets = sum(beautifullness)
//BBt = sum(Bness*BjetEt)
//BuHT = sum(beautifullness*jetEt)
//phoSep = PtGG*(s/b phoDPhi)*(s/b phiEtaMax)*(s/b phiMinR9)


		//Will be used if either bumpBtagEff != 0 or bumpJEC != 0. 
		//list of kin vars to make limits on. These must be singly-filled per event and otherwise make sense.
const int nKinemVars_limit = 1;
string s_KinemVars_limit[nKinemVars_limit] = {"MET"};//4

		//news: nEle, nLFjets, and the bottom row. 
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

const float Integrated_Luminosity_Data = 19.499;//18.304;// 1/fb
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

float BR_haa = 0.00229;
float BR_hbb = 0.561;
float BR_hzz = 0.0289;
float BR_hww = 0.231;
float BR_htt = 0.0615;
float BR_bbaa = 2*0.561*0.00229;
float BR_wwaa = 2*0.231*0.00229;
float BR_zzaa = 2*0.0289*0.00229; 
float BR_ttaa = 2*0.0615*0.00229;

} //end namespace params
#endif

