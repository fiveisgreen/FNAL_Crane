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
string outroot_data = "/eos/uscms/store/user/abarker/SusyEvents_skim_data_A.root"; //skim of the events used in analysis form big ntuples
//string outroot_data = "SusyEvents_forTMVA_data.root"; //skim of the events used in analysis form big ntuples
string plotsroot_data= "raw_plots_data_GLL12ABC.root"; // raw plots from ana.C
string plotsAndBackground_data = "plotsWithBackground_dataGLL12.root";
string logplotsAndBackground_data = "plotsWithBackground_dataGLL12.log";
string formatedplotsroot_data= "formatted_plots_dataGLL12.root";
bool useMETFilter_data = true;
bool useMVAphoP = false;


//MC
bool useMETFilter_mc = false;
bool makeEventsList = false;
bool makeTMVAlist = false;
bool showTag = true; //this blinds out the tag region when false;
bool useElectroHiggs = true; //if false, throw out all the MC events without a stop in them. 

long int probeevent = 10496;

//string which_MC_to_use = "mst_250_mu_200";
//string which_MC_to_use ="mst_250_mu_150";
//string which_MC_to_use ="mst_350_mu_200";
//string which_MC_to_use ="ho_140";
//string which_MC_to_use ="ho_200";
string which_MC_to_use2 = "mst_250_mu_200";

/*string outroot_mc = "susyEvents_MC_mst_250_M3_5025_mu_150.root"; //skim of the events used in analysis
string plotsroot_mc = "raw_plots_MC_mst_250_M3_5025_mu_150.root"; // raw plots from ana.C
string plotsAndBackground_mc = "plotsWithBackground_MC_mst_250_M3_5025_mu_150.root"; //output from postananan.C
string formatedplotsroot_mc= "formatted_plots_MC_mst_250_M3_5025_mu_150.root"; //output from format_plots.C*/

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
const int nEventTopologies = 1;//29; // the number of types of cuts selected, like 1JB...
string s_EventTopology[nEventTopologies] = {"2JbMLm20gbar2"}; 
/*"NULL","2JbMLm20", "2JbMLm20gbar1", "2JbMLm20gbar2", "2JbTLm20", 
"2JbTLm20gbar1", "2JbTLm20gbar2", "3JbMm20", "3JbTm20", "4JbMm20gbar1", 
"4JbMm20gbar2", "4JbTm20gbar1", "4JbTm20gbar2", "4JbTLm20","4JbMLm20gbar2",
"1lep","2lep","3lep","1Ele1Mu","2lepZ","1Mu",
"Tpho","2JbMLm20gbar2Tpho","1lepTpho","2lepTpho", "2JbML!m20Gbar2Mbb", "2JbML!m20Gbar2Mbb!", 
"3JbMLLm20Gbar2", "4JbMLLLm20Gbar2"};*/


//naming convention: gbar1 gbar2, jdn15
//base states: 1bar, 2bar, 1barjetdeta<1.5
//make your setup nimbler now. 


const int nKinemVars_all = 1;//53;		//always keep MET in the first position, it's special.
string s_KinemVars_all[nKinemVars_all] = {"MET"};
/*"MET","ST","HT","MHT","PtGG",
"phoPt0","phoPt1","phoPhi","phoEta","phoEtaMax",
"phoEtaMin","nJets","nLep","nMu","nEle",
"nBjets","MTphoMET","cosThetaStar","phoDPhi","phoDEta",
"dPhiPhoMet","jetPt","jetEta","jetPhi","phoMinR9",
"dijetDPhi01","dijetDEta01","dijetM01","dijetPt01","dPhiJetMet", //suggest killing dijetDEta01..., consolodate it. 
"Bt","bestMjj","bestMbb","allMjj","allMbb",
"Mbb01","Mbb01gg01",
"MJJ01gg01","Mleplep", "MZllHgg","MTggMET","MTlepMET",
"HGt","HGt_prime","dPhiHG","dPhiHG_prime","HLMGt",
"jetEtaMin",
"LHT","BTL","BTM","BTT","LepT"};*/

		//Will be used if either bumpBtagEff != 0 or bumpJEC != 0. 
		//list of kin vars to make limits on. These must be singly-filled per event and otherwise make sense.
	const int nKinemVars_limit = 1;
string s_KinemVars_limit[nKinemVars_limit] = {"MET"};
/*"MET","ST","HT","MHT","PtGG", 
"phoPt0","phoPt1","phoEtaMax", 
"phoEtaMin","nJets","nLep","nMu","nEle", 
"nBjets","cosThetaStar","phoDPhi","phoDEta","phoMinR9", 
"dijetDPhi01","dijetDEta01","dijetM01","dijetPt01", 
"Bt","bestMjj","bestMbb", "Mbb01","Mbb01gg01", 
"MJJ01gg01","Mleplep", "MZllHgg","MTggMET","MTlepMET", 
"dPhiHG","dPhiHG_prime", "jetEtaMin",
"LHT","BTL","BTM","BTT","LepT"};*/





float mHiggs = 125.5f; //higgs mass. 
float mHwidth = 11.f; 
//11 is the broades it's allowed to be
//float l_tag_sb_gap = 2.0f;//lower sideband gap
//float u_tag_sb_gap = 2.0f;//upper sideband gap
float l_sidebandwidth = 15.f;//lower sideband width
float u_sidebandwidth = 30.f;//upper sideband width
float tag_ub = mHiggs + 0.5*mHwidth;
float tag_lb = mHiggs - 0.5*mHwidth;
float usb_lb = 105;//tag_ub+u_tag_sb_gap;//upper side band lower bound
float usb_ub = 120;//usb_lb+u_sidebandwidth;
float lsb_ub = 131;//tag_lb-l_tag_sb_gap;
float lsb_lb = 161;//lsb_ub-l_sidebandwidth;

	//                                mHiggs
	// | sidebandwidth | tag_sb_gap | mHwidth | tag_sb_gap | sidebandwidth | 
	//lsb_lb         lsb_ub       tag_lb    tag_ub        usb_lb        usb_ub

//you should no longer need these
//int nMCGenerated = 1000000;
//float crossSection = 447.4; //fb
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

