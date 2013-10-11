//#include "TFractionFitter.h"
#include "TAxis.h"
#include "TH1.h"
#include "TMath.h"
//#include <TH2.h>
#include <TStyle.h>
//#include <TCanvas.h>
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"
//#include "TVirtualFitter.h"
//#include "TLegend.h"
#include <iostream>
//#include <ios>
#include <fstream>
#include <sstream>
//#include "TF1.h"
//#include "TLine.h"
//#include "quicksave.C"
//#include "CMSStyle.C"
#include "utilities.h"
#include "params_arg.h"
//#include "params_arg.h"
	//#include "params_arg.h"
//#include "TString.h"
#include<string.h>
#include<map>
#include "MCpoint.h"
#include <stdio.h>
#include <stdlib.h>
#include "RetrieveLimit.C"

using namespace std;
using namespace params;

	//check to see which of these you're still using. 
typedef std::map<string,TH1F*> LableHist;
typedef std::map<string,float> Labeledfloat;
//typedef std::map<string,LableHist> Lable2Hist;
//typedef map<string,Lable2Hist> Lable3Hist;
typedef std::map<string,TH1F**> LableHistArr;
//typedef std::map<string,LableHistArr> Lable2HistArr;
//typedef std::map<string,Lable2HistArr> Lable3HistArr;
typedef std::map<string,float> Labledfloat;
typedef std::map<string,TFile*> TFileMap;

void SetupLimit(string which_MC_to_use="");//no reliance
void SetupLimitsForOnePlot(TString MCname, TString topo, TString kinvar);//originator
void SetupLimitsForOnePlot(MCpoint * thisMCpoint, TString topo, TString kinvar,Labeledfloat & integ_systs); //takes
void SetupLimitsForOneMassPoint(TString MCname);//originator
void SetupLimitsForOneMassPoint(MCpoint * thisMCpoint, Labeledfloat & integ_systs); //add bbins here //takes
void SetupLimitsForOnePlot_bbin(TFile * files[],MCpoint* thisMCpoint, TString channels[],short nchannels, TString kinvar, TString CombinedTopoName,float f_integ_systs[]);//takes

	//new guys
void SetupSummedLimitsForStrongGrid(); //do Everything, originator, higgino'd
void SetupSummedLimitsForWeakGrid();  //do Everything, originator
void SetupSummedLimitsForStrongGrid(TString topo); //originator //slow as mollasis in january
void SetupSummedLimitsForWeakGrid(TString topo); //originator
void SetupSummedLimitsOneMassPoint(MCpoint* points[], int nMCpoints,TString topo, Labeledfloat & integ_systs); //takes
void SetupSummedLimitsOneMassPoint(MCpoint* points[], int nMCpoints, Labeledfloat & integ_systs); //This is Much faster!!, takes

void SetupSummedLimitsOnePlot(TString mcpoint_pefix, TString topo, TString kinvar);//
void SetupSummedLimitsOnePlot(TFile* files[][6],MCpoint* points[], int nMCpoints,TString topo, TString kinvar, Labeledfloat & integ_systs);//takes
void SetupSummedLimitsOnePlot_bbin(TFile* files[][6],MCpoint* points[], int nMCpoints, TString channels[],short nchannels, TString kinvar, TString CombinedTopoName,float f_integ_systs[]);//takes


void loadhist(TH1F** histout, TFile* PostAnaAnaFile, string basename,string suffix,int type = 1);//Done writing? Yes. Debugged? No
bool loadhistSafely(TH1F** histout, TFile* PostAnaAnaFile, string basename,string suffix,int type = 1);

	//bbin2: 2 cut categories of some kind
	//bbin3: 3 cut categories of some kind
	//bbin4: 4 cut categories of some kind

void makeLimitSettingMachinery(TH1F** CardHistSet, MCpoint * thisMCpoint, TString basename, TString topo, float f_integ_systs, TString kinvar, bool appendCombineCommand = true);
void makeLimitSettingMachinery_bbin2(TH1F** CardHistSet1, TH1F** CardHistSet2, MCpoint * thisMCpoint, TString* channels, TString topo,float f_integ_systs[2], TString kinvar, bool appendCombineCommand);
void makeLimitSettingMachinery_bbin3(TH1F** CardHistSet1, TH1F** CardHistSet2, TH1F** CardHistSet3, MCpoint * thisMCpoint, TString* channels, TString topo, float f_integ_systs[3], TString kinvar, bool appendCombineCommand);
void makeLimitSettingMachinery_bbin4(TH1F** CardHistSet1, TH1F** CardHistSet2, TH1F** CardHistSet3, TH1F** CardHistSet4, MCpoint * thisMCpoint, TString* channels, TString topo, float f_integ_systs[4], TString kinvar, bool appendCombineCommand);
void makeLimitSettingMachinery_bbinN(short nchannels, TH1F* CardHistSet[][7], MCpoint * thisMCpoint, TString* channels, TString topo, float f_integ_systs[], TString kinvar, bool appendCombineCommand);



void repackage_Systematics(TH1F** CardHistSet,TString rootfilename);
void repackage_Systematics_bbin2(TH1F** CardHistSet1, TH1F** CardHistSet2, TString rootfilename);
void repackage_Systematics_bbin3(TH1F** CardHistSet1, TH1F** CardHistSet2, TH1F** CardHistSet3, TString rootfilename);
void repackage_Systematics_bbin4(TH1F** CardHistSet1, TH1F** CardHistSet2, TH1F** CardHistSet3, TH1F** CardHistSet4, TString rootfilename);
void repackage_Systematics_bbinN(short nchannels, TH1F* CardHistSet[][7], TString rootfilename);


void makeCard_Systematics(TH1F** CardHistSet, MCpoint* thisMCpoint, TString basename, TString topo, TString kinvar, float f_integ_systs);
void makeCard_Systematics_bbin2( TH1F** CardHistSet1,TH1F**  CardHistSet2, MCpoint* thisMCpoint, TString* channels, TString topo,TString kinvar, float f_integ_systs[2]);
void makeCard_Systematics_bbin3( TH1F** CardHistSet1,TH1F**  CardHistSet2, TH1F** CardHistSet3, MCpoint* thisMCpoint, TString* channels, TString topo,TString kinvar,float f_integ_systs[3]);
void makeCard_Systematics_bbin4( TH1F** CardHistSet1,TH1F**  CardHistSet2, TH1F** CardHistSet3, TH1F** CardHistSet4, MCpoint* thisMCpoint, TString* channels, TString topo,TString kinvar, float f_integ_systs[4]);
void makeCard_Systematics_bbinN(short nchannels, TH1F* CardHistSet[][7], MCpoint* thisMCpoint, TString* channels, TString topo,TString kinvar, float f_integ_systs[]);

TString TackBeforeRoot(TString main, TString tack);

void suckinIntegralSystematics( Labeledfloat & integ_systs);

//New machiens for running full toys
void SetupAllToys(string topo, string kinvar, int n_r_guesses=30, int ntoys = 3000, int fork = 8);

int SetupToys(float r_low, float r_high, int n_r_guesses, string cardfile, string bashfilename, string collection_file, int seed_start = 1, int ntoys = 3000, int fork = 8);
void DoHadd(string collection_file, string ouptutfilename, int n_r_guesses_expected = 30);
void DoHaddGlom(string collection_file, string ouptutfilename, int n_r_guesses_expected = 30);
void DoHadd_file(string collection_file, string ouptutfilename, int n_r_guesses_expected = 30);
void RunOnToys(string toysrootfilename, string cardfilename, string runfilename, string resultsfile);
	////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////


void SetupLimit(string which_MC_to_use)
{
		//main
	cout<<"hello world"<<endl;
//	SetupLimitsForOnePlot("mst_350_mu_200","NULL","MET");//for debug purposes only; kill before doing this for real.
//	SetupLimitsForOneMassPoint("mst_350_mu_200");//for debug purposes only; kill before doing this for real.
	
	//Labledfloat integ_systs;
	//suckinIntegralSystematics(integ_systs);
	//SetupLimitsForOneMassPoint(which_MC_to_use,integ_systs);//runtime command
	SetupLimitsForOneMassPoint(which_MC_to_use);//runtime command
}

void SetupLimitsForOnePlot(TString MCname, TString topo, TString kinvar){
		//this is something we might use from the command line.
	MCpoint * thisMCpoint = setupMCpoint(MCname.Data(), "");//this is bulky, so we're seperating it out from the rest of SetupLimitsForOnePlot.
	Labledfloat integ_systs;
        suckinIntegralSystematics(integ_systs);
	SetupLimitsForOnePlot(thisMCpoint, topo, kinvar,integ_systs);
} //Done writing? Yes. Debugged? No
//void SetupLimitsForOnePlot(MCpoint * thisMCpoint, TString topo, TString kinvar){
void SetupLimitsForOnePlot(MCpoint * thisMCpoint, TString topo, TString kinvar,Labeledfloat & integ_systs){
		//make machinery for one point, one topo, one kinvar, the point is to make you really nimble.
		//THIS IS THE FRONT DOOR, RUNS EVERYTHING ELSE.

	string data = "Data";
	MCpoint * datapoint = setupMCpoint(data, "");//this is efficient.
	int printlevel = 10;

		/// LUMI SCALES
	float lumiscale = thisMCpoint->lumiscalefactor(Integrated_Luminosity_Data);


		///open all files
	if(printlevel>2) cout<<"trying to open "<<datapoint->plotsAndBackground_mc<<endl;
	TFile * PostAnaAnaFiles_data = new TFile(datapoint->plotsAndBackground_mc.c_str());
	TFile * PostAnaAnaFiles_mc = new TFile(thisMCpoint->plotsAndBackground_mc.c_str());
	if(printlevel>2) cout<<"trying to open "<<TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"JECUp")<<endl;
	TFile * PostAnaAnaFiles_mc_JECUp       = new TFile(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"JECUp").Data());
	if(printlevel>2) cout<<"trying to open "<<TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"JECDown")<<endl;
	TFile * PostAnaAnaFiles_mc_JECDown     = new TFile(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"JECDown").Data());
	if(printlevel>2) cout<<"trying to open "<<TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"BtagEffUp")<<endl;
	TFile * PostAnaAnaFiles_mc_BtagEffUp   = new TFile(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"BtagEffUp").Data());
	if(printlevel>2) cout<<"trying to open "<<TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"BtagEffDown")<<endl;
	TFile * PostAnaAnaFiles_mc_BtagEffDown = new TFile(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"BtagEffDown").Data());

		///load all the plots for this kinvar and this topo.
	if( !(
		  fileExists(datapoint->plotsAndBackground_mc.c_str()) &&
		  fileExists(thisMCpoint->plotsAndBackground_mc.c_str()) &&
		  fileExists(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"JECUp").Data()) &&
		  fileExists(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"JECDown").Data()) &&
		  fileExists(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"BtagEffUp").Data()) &&
		  fileExists(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"BtagEffDown").Data()) )){
        printf("ERROR!! Some of the input files are missing completely!\n");
		if (!fileExists(datapoint->plotsAndBackground_mc.c_str()) ) printf("%s is missing.\n",datapoint->plotsAndBackground_mc.c_str() );
		if (!fileExists(thisMCpoint->plotsAndBackground_mc.c_str()) ) printf("%s is missing.\n",thisMCpoint->plotsAndBackground_mc.c_str());
		if (!fileExists(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"JECUp").Data()) ) printf("%s is missing.\n",TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"JECUp").Data() );
		if (!fileExists(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"JECDown").Data()) ) printf("%s is missing.\n",TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"JECDown").Data() );
		if (!fileExists(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"BtagEffUp").Data()) ) printf("%s is missing.\n",TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"BtagEffUp").Data() );
		if (!fileExists(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"BtagEffDown").Data()) ) printf("%s is missing.\n",TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"BtagEffDown").Data() );
		printf("Exiting SetupLimits (from SetupLimitsForOnePlot)!!\n");
        return;
	}


	TH1F* CardHistSet[7];
		//{Data_tag,  Data_bkg,	MC , MC_JECUp,  MC_JECDown, MC_BtagEffUp,	MC_BtagEffDown}
		//{ 0      ,  1       , 2  , 3       ,  4         , 5           ,   6             }

	if(printlevel>2) cout<<"loading hists"<<endl;
	string basename = string("h")+kinvar.Data()+topo.Data()+"_";
	//root names are basename+suffix
	bool got_them_all = true;
	got_them_all &= loadhistSafely(& CardHistSet[0], PostAnaAnaFiles_data, basename,data,1);
	got_them_all &= loadhistSafely(& CardHistSet[1], PostAnaAnaFiles_data, basename,"Bkg",3);
	got_them_all &= loadhistSafely(& CardHistSet[2], PostAnaAnaFiles_mc, basename,"MC",1);
	got_them_all &= loadhistSafely(& CardHistSet[3], PostAnaAnaFiles_mc_JECUp, basename,"JECUp",1);
	got_them_all &= loadhistSafely(& CardHistSet[4], PostAnaAnaFiles_mc_JECDown, basename,"JECDown",1);
	got_them_all &= loadhistSafely(& CardHistSet[5], PostAnaAnaFiles_mc_BtagEffUp, basename,"BtagEffUp",1);
	got_them_all &= loadhistSafely(& CardHistSet[6], PostAnaAnaFiles_mc_BtagEffDown, basename,"BtagEffDown",1);
	if (!got_them_all) {
		cout<<endl<<"MAJOR ERROR!! Could not find histograms for topo "<<topo<<" kinvar "<<kinvar<<endl;
		cout<<"    Check consistency among the params files. "<<endl;
		cout<<"    Now Forcing a Controled Exit!!"<<endl<<endl;
		return;
	}


		///Scale by Lumiscale
	if(printlevel>2) cout<<"scaling histogramms by factor "<<lumiscale<<endl;
	for(int j=2;j<=6;j++){
		CardHistSet[j]->Scale(lumiscale); //2-6 are the MC hists.
	}

	/*Debug*/ if(printlevel > 3) cout<<"Setting up machinery for "<<thisMCpoint->pointName<<" topo "<<topo<<" kinvar "<<kinvar<<endl;
	makeLimitSettingMachinery(CardHistSet, thisMCpoint, basename, topo, integ_systs[topo.Data()], kinvar, false);



		////close all files. 
	PostAnaAnaFiles_mc->Close();
	PostAnaAnaFiles_mc_JECUp->Close();
	PostAnaAnaFiles_mc_JECDown->Close();
	PostAnaAnaFiles_mc_BtagEffUp->Close();
	PostAnaAnaFiles_mc_BtagEffDown->Close();
	PostAnaAnaFiles_data->Close();
}//end SetupLimitsForOnePlot  //Done writing? Yes. Debugged? No

	///SetupLimitsForAllMCPoints makes the machines for all MC points, but for 1! topo and kinvar.
	///This is archaic, and abandoned
	///It does a whole lot of file IO and has to have ALL those files availabe.

void SetupLimitsForOneMassPoint(TString MCname){
		//this is something we might use from the command line.
	MCpoint * thisMCpoint = setupMCpoint(MCname.Data(), "");//this is bulky, so we're seperating it out from the rest of SetupLimitsForOnePlot.
	Labledfloat integ_systs;
        suckinIntegralSystematics(integ_systs);

	SetupLimitsForOneMassPoint(thisMCpoint,integ_systs);
}//end SetupLimitsForOneMassPoint
//void SetupLimitsForOneMassPoint(MCpoint * thisMCpoint){
void SetupLimitsForOneMassPoint(MCpoint * thisMCpoint, Labeledfloat & integ_systs){
		//make machinery for one mass point, for every topo and kinvar.
		//This does the file opening more efficiently than calling SetupLimitsForOnePlot a bunch of times.
		//THIS IS THE FRONT DOOR, RUNS EVERYTHING ELSE.
	string data = "Data";
	MCpoint * datapoint = setupMCpoint(data, "");//this is efficient.
	int printlevel = 10;
	/*Debug*/ if(printlevel > 3) cout<<"Setting up machinery for "<<thisMCpoint->pointName<<endl;
		/// LUMI SCALES
	float lumiscale = thisMCpoint->lumiscalefactor(Integrated_Luminosity_Data);

		///open all files
	TFile * PostAnaAnaFiles_data = new TFile(datapoint->plotsAndBackground_mc.c_str());
	TFile * PostAnaAnaFiles_mc = new TFile(thisMCpoint->plotsAndBackground_mc.c_str());
	TFile * PostAnaAnaFiles_mc_JECUp       = new TFile(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"JECUp").Data());
	TFile * PostAnaAnaFiles_mc_JECDown     = new TFile(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"JECDown").Data());
	TFile * PostAnaAnaFiles_mc_BtagEffUp   = new TFile(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"BtagEffUp").Data());
	TFile * PostAnaAnaFiles_mc_BtagEffDown = new TFile(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"BtagEffDown").Data());

	TFile * files[6] = {PostAnaAnaFiles_data,PostAnaAnaFiles_mc,
		    PostAnaAnaFiles_mc_JECUp,PostAnaAnaFiles_mc_JECDown,
		PostAnaAnaFiles_mc_BtagEffUp,PostAnaAnaFiles_mc_BtagEffDown};//new

	if( !( fileExists(datapoint->plotsAndBackground_mc.c_str()) &&
				fileExists(thisMCpoint->plotsAndBackground_mc.c_str()) &&
				fileExists(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"JECUp").Data()) &&
				fileExists(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"JECDown").Data()) &&
				fileExists(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"BtagEffUp").Data()) &&
				fileExists(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"BtagEffDown").Data()) )){
		printf("ERROR!! Some of the input files are missing completely!\n");
		if (!fileExists(datapoint->plotsAndBackground_mc.c_str()) ) printf("%s is missing.\n",datapoint->plotsAndBackground_mc.c_str() );
		if (!fileExists(thisMCpoint->plotsAndBackground_mc.c_str()) ) printf("%s is missing.\n",thisMCpoint->plotsAndBackground_mc.c_str());
		if (!fileExists(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"JECUp").Data()) ) printf("%s is missing.\n",TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"JECUp").Data() );
		if (!fileExists(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"JECDown").Data()) ) printf("%s is missing.\n",TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"JECDown").Data() );
		if (!fileExists(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"BtagEffUp").Data()) ) printf("%s is missing.\n",TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"BtagEffUp").Data() );
		if (!fileExists(TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"BtagEffDown").Data()) ) printf("%s is missing.\n",TackBeforeRoot(thisMCpoint->plotsAndBackground_mc,"BtagEffDown").Data() );
		printf("Exiting SetupLimits!! (from SetupLimitsForOneMassPoint) \n");
		return;
	}

	//for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++) {
		//TString kinvar = s_KinemVars[kKinVar];
	for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
		TString kinvar = s_KinemVars_limit[kKinVar];
		for (int iTop = 0; iTop<nEventTopologies; iTop++) {
			TString topo =s_EventTopology[iTop];

			//exclude the b-binnings.
			if(topo.CompareTo("2JbML!Gbar2Mbb!") == 0 || 
			   topo.CompareTo("3JbMLLGbar2") == 0 || 
			   topo.CompareTo("4JbMLLLGbar2") == 0 ||
			   topo.CompareTo("2JbMLgbar2bestOn") == 0 ||
			   topo.CompareTo("2JbMLgbar2bestOff") == 0 ||
			   topo.CompareTo("2JbTLgbar2bestOn") == 0 ||
			   topo.CompareTo("2JbTLgbar2bestOff") == 0 ||
			   topo.CompareTo("2JbM2lepgbar2") == 0 ||
			   topo.CompareTo("2JbML!1lepgbar2") == 0 ||
			   topo.CompareTo("2JbML!gbar2bestOn0lep") == 0 ||
			   topo.CompareTo("4JbML!gbar2ewkMllbestOff0lep") == 0 ||
			   topo.CompareTo("2JbML!gbar2bothOff0lep") == 0 ||
			   topo.CompareTo("3JbMLLgbar2") == 0 ||
			   topo.CompareTo("1!lep23Jb01M!ewkMllgbar2") == 0
			   ) continue;


				///load all the plots for this kinvar and this topo.
			TH1F* CardHistSet[7];
				//{Data_tag,  Data_bkg,	MC , MC_JECUp,  MC_JECDown, MC_BtagEffUp,	MC_BtagEffDown}
				//{ 0      ,  1       , 2  , 3       ,  4         , 5           ,   6             }
			string basename = string("h")+kinvar.Data()+topo.Data()+"_";
				//root names are basename+suffix
			bool got_them_all = true;
			got_them_all &= loadhistSafely(& CardHistSet[0], PostAnaAnaFiles_data, basename,data,1);
			got_them_all &= loadhistSafely(& CardHistSet[1], PostAnaAnaFiles_data, basename,"Bkg",3);
			got_them_all &= loadhistSafely(& CardHistSet[2], PostAnaAnaFiles_mc, basename,"MC",1);
			got_them_all &= loadhistSafely(& CardHistSet[3], PostAnaAnaFiles_mc_JECUp, basename,"JECUp",1);
			got_them_all &= loadhistSafely(& CardHistSet[4], PostAnaAnaFiles_mc_JECDown, basename,"JECDown",1);
			got_them_all &= loadhistSafely(& CardHistSet[5], PostAnaAnaFiles_mc_BtagEffUp, basename,"BtagEffUp",1);
			got_them_all &= loadhistSafely(& CardHistSet[6], PostAnaAnaFiles_mc_BtagEffDown, basename,"BtagEffDown",1);
			if (!got_them_all) {
				cout<<endl<<"MAJOR ERROR!! Could not find histograms for topo "<<topo<<" kinvar "<<kinvar<<endl;
				cout<<"    Check consistency among the params files. "<<endl;
				cout<<"    Continuing without it!!"<<endl<<endl;
				continue;
			}

				///Scale by Lumiscale
			if(printlevel>3) cout<<"scaling histogramms by factor "<<lumiscale<<endl;
			for(short j=2;j<=6;j++){
				CardHistSet[j]->Scale(lumiscale); //2-6 are the MC hists.
			}

			/*Debug*/ if(printlevel > 3) cout<<"Setting up machinery for topo "<<topo<<" kinvar "<<kinvar<<endl;
			makeLimitSettingMachinery(CardHistSet, thisMCpoint, basename, topo, integ_systs[topo.Data()], kinvar, true);
		}//end for every topo

		///Make Limit setting machines for b-binning
/*		TH1F* CardHistSet_2bMH[7];
		TH1F* CardHistSet_2bMnotH[7];
		TH1F* CardHistSet_3b[7];
		TH1F* CardHistSet_4b[7];
		//{Data_tag,  Data_bkg, MC , MC_JECUp,  MC_JECDown, MC_BtagEffUp,       MC_BtagEffDown}
		//{ 0      ,  1       , 2  , 3       ,  4         , 5           ,   6             }
		if(printlevel > 3) cout<<"loading topo 2JbML!Gbar2Mbb "<<kinvar<<endl;
		string basename = string("h")+kinvar.Data()+"2JbML!Gbar2Mbb"+"_"; //root names are basename+suffix
		bool got_them_all = true;
		got_them_all &= loadhistSafely(& CardHistSet_2bMH[0], PostAnaAnaFiles_data, basename,data,1);
		got_them_all &= loadhistSafely(& CardHistSet_2bMH[1], PostAnaAnaFiles_data, basename,"Bkg",3);
		got_them_all &= loadhistSafely(& CardHistSet_2bMH[2], PostAnaAnaFiles_mc, basename,"MC",1);
		got_them_all &= loadhistSafely(& CardHistSet_2bMH[3], PostAnaAnaFiles_mc_JECUp, basename,"JECUp",1);
		got_them_all &= loadhistSafely(& CardHistSet_2bMH[4], PostAnaAnaFiles_mc_JECDown, basename,"JECDown",1);
		got_them_all &= loadhistSafely(& CardHistSet_2bMH[5], PostAnaAnaFiles_mc_BtagEffUp, basename,"BtagEffUp",1);
		got_them_all &= loadhistSafely(& CardHistSet_2bMH[6], PostAnaAnaFiles_mc_BtagEffDown, basename,"BtagEffDown",1);
		if (!got_them_all) {
			cout<<endl<<"MAJOR ERROR!! Could not find histograms for topo 2JbML!Gbar2Mbb kinvar "<<kinvar<<endl;
			cout<<"    Check consistency among the params files. "<<endl;
			cout<<"    Continuing without it!!"<<endl<<endl;
			continue;
		}
		if(printlevel > 3) cout<<"loading topo 2JbML!Gbar2Mbb!"<<kinvar<<endl;
		basename = string("h")+kinvar.Data()+"2JbML!Gbar2Mbb!"+"_"; //root names are basename+suffix
		got_them_all = true;
		got_them_all &= loadhistSafely(& CardHistSet_2bMnotH[0], PostAnaAnaFiles_data, basename,data,1);
		got_them_all &= loadhistSafely(& CardHistSet_2bMnotH[1], PostAnaAnaFiles_data, basename,"Bkg",3);
		got_them_all &= loadhistSafely(& CardHistSet_2bMnotH[2], PostAnaAnaFiles_mc, basename,"MC",1);
		got_them_all &= loadhistSafely(& CardHistSet_2bMnotH[3], PostAnaAnaFiles_mc_JECUp, basename,"JECUp",1);
		got_them_all &= loadhistSafely(& CardHistSet_2bMnotH[4], PostAnaAnaFiles_mc_JECDown, basename,"JECDown",1);
		got_them_all &= loadhistSafely(& CardHistSet_2bMnotH[5], PostAnaAnaFiles_mc_BtagEffUp, basename,"BtagEffUp",1);
		got_them_all &= loadhistSafely(& CardHistSet_2bMnotH[6], PostAnaAnaFiles_mc_BtagEffDown, basename,"BtagEffDown",1);
		if (!got_them_all) {
			cout<<endl<<"MAJOR ERROR!! Could not find histograms for topo 2JbML!Gbar2Mbb! kinvar "<<kinvar<<endl;
			cout<<"    Check consistency among the params files. "<<endl;
			cout<<"    Continuing without it!!"<<endl<<endl;
			continue;
		}
		if(printlevel > 3) cout<<"loading topo 3JbMLLGbar2"<<kinvar<<endl;
		basename = string("h")+kinvar.Data()+"3JbMLLGbar2"+"_"; //root names are basename+suffix
		got_them_all = true;
		got_them_all &= loadhistSafely(& CardHistSet_3b[0], PostAnaAnaFiles_data, basename,data,1);
		got_them_all &= loadhistSafely(& CardHistSet_3b[1], PostAnaAnaFiles_data, basename,"Bkg",3);
		got_them_all &= loadhistSafely(& CardHistSet_3b[2], PostAnaAnaFiles_mc, basename,"MC",1);
		got_them_all &= loadhistSafely(& CardHistSet_3b[3], PostAnaAnaFiles_mc_JECUp, basename,"JECUp",1);
		got_them_all &= loadhistSafely(& CardHistSet_3b[4], PostAnaAnaFiles_mc_JECDown, basename,"JECDown",1);
		got_them_all &= loadhistSafely(& CardHistSet_3b[5], PostAnaAnaFiles_mc_BtagEffUp, basename,"BtagEffUp",1);
		got_them_all &= loadhistSafely(& CardHistSet_3b[6], PostAnaAnaFiles_mc_BtagEffDown, basename,"BtagEffDown",1);
		if (!got_them_all) {
			cout<<endl<<"MAJOR ERROR!! Could not find histograms for topo 3JbMLLGbar2 kinvar "<<kinvar<<endl;
			cout<<"    Check consistency among the params files. "<<endl;
			cout<<"    Continuing without it!!"<<endl<<endl;
			continue;
		}
		if(printlevel > 3) cout<<"loading topo 4JbMLLLGbar2"<<kinvar<<endl;
		basename = string("h")+kinvar.Data()+"4JbMLLLGbar2"+"_"; //root names are basename+suffix
		got_them_all = true;
		got_them_all &= loadhistSafely(& CardHistSet_4b[0], PostAnaAnaFiles_data, basename,data,1);
		got_them_all &= loadhistSafely(& CardHistSet_4b[1], PostAnaAnaFiles_data, basename,"Bkg",3);
		got_them_all &= loadhistSafely(& CardHistSet_4b[2], PostAnaAnaFiles_mc, basename,"MC",1);
		got_them_all &= loadhistSafely(& CardHistSet_4b[3], PostAnaAnaFiles_mc_JECUp, basename,"JECUp",1);
		got_them_all &= loadhistSafely(& CardHistSet_4b[4], PostAnaAnaFiles_mc_JECDown, basename,"JECDown",1);
		got_them_all &= loadhistSafely(& CardHistSet_4b[5], PostAnaAnaFiles_mc_BtagEffUp, basename,"BtagEffUp",1);
		got_them_all &= loadhistSafely(& CardHistSet_4b[6], PostAnaAnaFiles_mc_BtagEffDown, basename,"BtagEffDown",1);
		if (!got_them_all) {
			cout<<endl<<"MAJOR ERROR!! Could not find histograms for topo 4JbMLLLGbar2 kinvar "<<kinvar<<endl;
			cout<<"    Check consistency among the params files. "<<endl;
			cout<<"    Continuing without it!!"<<endl<<endl;
			continue;
		}
		///Scale by Lumiscale
		if(printlevel>3) cout<<"scaling histogramms by factor "<<lumiscale<<endl;
		for(int j=2;j<=6;j++){
			CardHistSet_2bMH[j]->Scale(lumiscale); //2-6 are the MC hists.
			CardHistSet_2bMnotH[j]->Scale(lumiscale); //2-6 are the MC hists.
			CardHistSet_3b[j]->Scale(lumiscale); //2-6 are the MC hists.
			CardHistSet_4b[j]->Scale(lumiscale); //2-6 are the MC hists.
		}
		TString channels[4];
		channels[0] = "2JbML!Gbar2Mbb";
		channels[1] = "2JbML!Gbar2Mbb!";
		channels[2] = "3JbMLLGbar2";
		channels[3] = "4JbMLLLGbar2";
		if(printlevel > 3) cout<<"Setting up machinery for b-bins kinvar "<<kinvar<<endl;
		//spicific to one particluar thing. 
		basename = string("h")+kinvar.Data()+"bbin_";
		cout<<"Setting up machinery for b-bins kinvar "<<kinvar<<endl;

		makeLimitSettingMachinery_bbin3(CardHistSet_2bMH,CardHistSet_2bMnotH,CardHistSet_3b,thisMCpoint, channels, "bbin3", kinvar, true);
*/
		{
			TString channels[3];
			channels[0] = "2JbML!Gbar2Mbb";
			channels[1] = "2JbML!Gbar2Mbb!";
			channels[2] = "3JbMLLGbar2";
			float f_integ_systs[3];
			f_integ_systs[0]=integ_systs["2JbML!Gbar2Mbb"];
			f_integ_systs[1]=integ_systs["2JbML!Gbar2Mbb!"];
			f_integ_systs[2]=integ_systs["3JbMLLGbar2"];
			SetupLimitsForOnePlot_bbin(files,thisMCpoint,channels,3,kinvar,"bbin3",f_integ_systs);
		}
		{
			TString channels[3];
			channels[0] = "2JbMM!Gbar2Mbb";
			channels[1] = "2JbMM!Gbar2Mbb!";
			channels[2] = "3JbMMLGbar2";
			float f_integ_systs[3];
			f_integ_systs[0]=integ_systs["2JbMM!Gbar2Mbb"];
			f_integ_systs[1]=integ_systs["2JbMM!Gbar2Mbb!"];
			f_integ_systs[2]=integ_systs["3JbMMLGbar2"];
			SetupLimitsForOnePlot_bbin(files,thisMCpoint,channels,3,kinvar,"bbin3MM",f_integ_systs);
		}
		{
			TString channels[3];
			channels[0] = "2JbML!gbar2Mbb01lep";
			channels[1] = "2JbT!gbar2ProbeMJJ";
			channels[2] = "0lep25Jb01MewkMllgbar2";
			float f_integ_systs[3];
			f_integ_systs[0]=integ_systs["2JbML!gbar2Mbb01lep"];
			f_integ_systs[1]=integ_systs["2JbT!gbar2ProbeMJJ"];
			f_integ_systs[2]=integ_systs["0lep25Jb01MewkMllgbar2"];
			SetupLimitsForOnePlot_bbin(files,thisMCpoint,channels,3,kinvar,"EHbin3",f_integ_systs);
		}
		{
			TString channels[3];
			channels[0] = "2JbML!gbar2bestOn";
			channels[1] = "2JbML!gbar2bestOff";
			channels[2] = "3JbMLLGbar2";
			float f_integ_systs[3];
			f_integ_systs[0]=integ_systs["2JbML!gbar2bestOn"];
			f_integ_systs[1]=integ_systs["2JbML!gbar2bestOff"];
			f_integ_systs[2]=integ_systs["3JbMLLGbar2"];
			SetupLimitsForOnePlot_bbin(files,thisMCpoint,channels,3,kinvar,"bbin3MLbest",f_integ_systs);
		}
		{
			TString channels[3];
			channels[0] = "2JbMM!gbar2bestOn";
			channels[1] = "2JbMM!gbar2bestOff";
			channels[2] = "3JbMMLGbar2";
			float f_integ_systs[3];
			f_integ_systs[0]=integ_systs["2JbMM!gbar2bestOn"];
			f_integ_systs[1]=integ_systs["2JbMM!gbar2bestOff"];
			f_integ_systs[2]=integ_systs["3JbMMLGbar2"];
			SetupLimitsForOnePlot_bbin(files,thisMCpoint,channels,3,kinvar,"bbin3MMbest",f_integ_systs);
		}
		{
			TString channels[2];
			channels[0] = "1!lepgbar2";
			channels[1] = "23Jb01MewkMll0lepgbar2";
			float f_integ_systs[2];
			f_integ_systs[0]=integ_systs["1!lepgbar2"];
			f_integ_systs[1]=integ_systs["23Jb01MewkMll0lepgbar2"];
			SetupLimitsForOnePlot_bbin(files,thisMCpoint,channels,2,kinvar,"WHbins",f_integ_systs);
		}
		{
			TString channels[2];
			channels[0] = "2!lepZgbar2";
			channels[1] = "23Jb01MewkMll0lepgbar2";
			float f_integ_systs[2];
			f_integ_systs[0]=integ_systs["2!lepZgbar2"];
			f_integ_systs[1]=integ_systs["23Jb01MewkMll0lepgbar2"];
			SetupLimitsForOnePlot_bbin(files,thisMCpoint,channels,2,kinvar,"ZHbins",f_integ_systs);
		}
		{
			TString channels[4];
			channels[0] = "2lepgbar2";
			channels[1] = "1!lep23Jb01M!ewkMllgbar2";
			channels[2] = "1!lep23Jb01MewkMllgbar2";
			channels[3] = "0lep25Jb01MewkMllgbar2";
			float f_integ_systs[4];
			f_integ_systs[0]=integ_systs["2lepgbar2"];
			f_integ_systs[1]=integ_systs["1!lep23Jb01M!ewkMllgbar2"];
			f_integ_systs[2]=integ_systs["1!lep23Jb01MewkMllgbar2"];
			f_integ_systs[3]=integ_systs["0lep25Jb01MewkMllgbar2"];
			SetupLimitsForOnePlot_bbin(files,thisMCpoint,channels,4,kinvar,"WWbins",f_integ_systs);
		}
		{
			TString channels[5];
			channels[0] = "3lepgbar2";
			channels[1] = "2!lepZgbar2";
			channels[2] = "1!lep23Jb01M!ewkMllgbar2";
			channels[3] = "1!lep23Jb01MewkMllgbar2";
			channels[4] = "0lep25Jb01MewkMllgbar2";
			float f_integ_systs[5];
			f_integ_systs[0]=integ_systs["3lepgbar2"];
			f_integ_systs[1]=integ_systs["2!lepZgbar2"];
			f_integ_systs[2]=integ_systs["1!lep23Jb01M!ewkMllgbar2"];
			f_integ_systs[3]=integ_systs["1!lep23Jb01MewkMllgbar2"];
			f_integ_systs[4]=integ_systs["0lep25Jb01MewkMllgbar2"];
			SetupLimitsForOnePlot_bbin(files,thisMCpoint,channels,5,kinvar,"ZZbins",f_integ_systs);
		}
		{
			TString channels[6];
			channels[0] = "2JbM2lepgbar2";
			channels[1] = "2JbML!1lepgbar2";
			channels[2] = "2JbML!gbar2bestOn0lep";
			channels[3] = "4JbML!gbar2ewkMllbestOff0lep";
			channels[4] = "2JbML!gbar2bothOff0lep";
			channels[5] = "3JbMLLGbar2";
			float f_integ_systs[6];
			f_integ_systs[0]=integ_systs["2JbM2lepgbar2"];
			f_integ_systs[1]=integ_systs["2JbML!1lepgbar2"];
			f_integ_systs[2]=integ_systs["2JbML!gbar2bestOn0lep"];
			f_integ_systs[3]=integ_systs["4JbML!gbar2ewkMllbestOff0lep"];
			f_integ_systs[4]=integ_systs["2JbML!gbar2bothOff0lep"];
			f_integ_systs[5]=integ_systs["3JbMLLGbar2"];
			SetupLimitsForOnePlot_bbin(files,thisMCpoint,channels,6,kinvar,"SHbins",f_integ_systs);
		}

//		printf("go do bbinTLbest\n");
//		TString channels_TLbest[2];
//		channels_TLbest[0] = "2JbTLgbar2bestOn";
//		channels_TLbest[1] = "2JbTLgbar2bestOff";
//		SetupLimitsForOnePlot_bbin(files,thisMCpoint,channels_TLbest,2,kinvar,"bbinTLbest");

//		printf("go do bbinMLbest\n");
//		TString channels_MLbest[2];
//		channels_MLbest[0] = "2JbMLgbar2bestOn";
//		channels_MLbest[1] = "2JbMLgbar2bestOff";
//		SetupLimitsForOnePlot_bbin(files,thisMCpoint,channels_MLbest,2,kinvar,"bbinMLbest");
	
	}//end for every kinvar

		////close all files.
	PostAnaAnaFiles_mc->Close();
	PostAnaAnaFiles_mc_JECUp->Close();
	PostAnaAnaFiles_mc_JECDown->Close();
	PostAnaAnaFiles_mc_BtagEffUp->Close();
	PostAnaAnaFiles_mc_BtagEffDown->Close();
	PostAnaAnaFiles_data->Close();
}//end SetupLimitsForOneMassPoint


void SetupLimitsForOnePlot_bbin(TFile * files[],MCpoint* thisMCpoint, TString channels[],short nchannels, TString kinvar, TString CombinedTopoName, float f_integ_systs[]){
		//files is expected to be an array of OPEN files that will be closed later. Use only via other functions.
		//nchannels is allowed to be 1-4, in the case of 1, use CombinedTopoName = topo and you shoud get the same result as not bbining.
	
	if(nchannels <1){
		printf("Error! You gave SetupLimitsForOnePlot_bbin a useless number of bins! Terminating! Fix it in SetupLimit\n");
		return;
	}
	printf("I'm in SetupLimitsForOnePlot_bbin\n");
    short printlevel = 4;
	string data = "Data";
		///Make Limit setting machines for b-binning
	TH1F* CardHistSet_bin[nchannels][7];

		//{Data_tag,  Data_bkg, MC , MC_JECUp,  MC_JECDown, MC_BtagEffUp,       MC_BtagEffDown}
		//{ 0      ,  1       , 2  , 3       ,  4         , 5           ,   6             }
	/*Debug*/ if(printlevel > 3) cout<<"loading topo "<<channels[0].Data()<<" "<<kinvar<<endl;
	string basename = string("h")+kinvar.Data()+channels[0].Data()+"_"; //root names are basename+suffix
	bool got_them_all = true;
	got_them_all &= loadhistSafely(& CardHistSet_bin[0][0], files[0], basename,data,1);
	got_them_all &= loadhistSafely(& CardHistSet_bin[0][1], files[0], basename,"Bkg",3);
	got_them_all &= loadhistSafely(& CardHistSet_bin[0][2], files[1], basename,"MC",1);
	got_them_all &= loadhistSafely(& CardHistSet_bin[0][3], files[2], basename,"JECUp",1);
	got_them_all &= loadhistSafely(& CardHistSet_bin[0][4], files[3], basename,"JECDown",1);
	got_them_all &= loadhistSafely(& CardHistSet_bin[0][5], files[4], basename,"BtagEffUp",1);
	got_them_all &= loadhistSafely(& CardHistSet_bin[0][6], files[5], basename,"BtagEffDown",1);
	if (!got_them_all) {
		cout<<endl<<"MAJOR ERROR!! Could not find histograms for topo "<<channels[0].Data()<<" kinvar "<<kinvar<<endl;
		cout<<"    Check consistency among the params files. "<<endl;
		cout<<"    Continuing without it!!"<<endl<<endl;
		return;
	}
	if(nchannels >=2){
		/*Debug*/ if(printlevel > 3) cout<<"loading topo "<<channels[1].Data()<<" "<<kinvar<<endl;
		basename = string("h")+kinvar.Data()+channels[1].Data()+"_"; //root names are basename+suffix
		got_them_all = true;
		got_them_all &= loadhistSafely(& CardHistSet_bin[1][0], files[0], basename,data,1);
		got_them_all &= loadhistSafely(& CardHistSet_bin[1][1], files[0], basename,"Bkg",3);
		got_them_all &= loadhistSafely(& CardHistSet_bin[1][2], files[1], basename,"MC",1);
		got_them_all &= loadhistSafely(& CardHistSet_bin[1][3], files[2], basename,"JECUp",1);
		got_them_all &= loadhistSafely(& CardHistSet_bin[1][4], files[3], basename,"JECDown",1);
		got_them_all &= loadhistSafely(& CardHistSet_bin[1][5], files[4], basename,"BtagEffUp",1);
		got_them_all &= loadhistSafely(& CardHistSet_bin[1][6], files[5], basename,"BtagEffDown",1);
		if (!got_them_all) {
			cout<<endl<<"MAJOR ERROR!! Could not find histograms for topo "<<channels[1].Data()<<" kinvar "<<kinvar<<endl;
			cout<<"    Check consistency among the params files. "<<endl;
			cout<<"    Continuing without it!!"<<endl<<endl;
			return;
		}
	}
	if(nchannels >=3){
		/*Debug*/ if(printlevel > 3) cout<<"loading topo "<<channels[2].Data()<<" "<<kinvar<<endl;
		basename = string("h")+kinvar.Data()+channels[2].Data()+"_"; //root names are basename+suffix
		got_them_all = true;
		got_them_all &= loadhistSafely(& CardHistSet_bin[2][0], files[0], basename,data,1);
		got_them_all &= loadhistSafely(& CardHistSet_bin[2][1], files[0], basename,"Bkg",3);
		got_them_all &= loadhistSafely(& CardHistSet_bin[2][2], files[1], basename,"MC",1);
		got_them_all &= loadhistSafely(& CardHistSet_bin[2][3], files[2], basename,"JECUp",1);
		got_them_all &= loadhistSafely(& CardHistSet_bin[2][4], files[3], basename,"JECDown",1);
		got_them_all &= loadhistSafely(& CardHistSet_bin[2][5], files[4], basename,"BtagEffUp",1);
		got_them_all &= loadhistSafely(& CardHistSet_bin[2][6], files[5], basename,"BtagEffDown",1);
		if (!got_them_all) {
			cout<<endl<<"MAJOR ERROR!! Could not find histograms for topo "<<channels[2].Data()<<" kinvar "<<kinvar<<endl;
			cout<<"    Check consistency among the params files. "<<endl;
			cout<<"    Continuing without it!!"<<endl<<endl;
			return;
		}
	}
	if(nchannels >=4){
		/*Debug*/ if(printlevel > 3) cout<<"loading topo "<<channels[3].Data()<<" "<<kinvar<<endl;
		basename = string("h")+kinvar.Data()+channels[3].Data()+"_"; //root names are basename+suffix
		got_them_all = true;
		got_them_all &= loadhistSafely(& CardHistSet_bin[3][0], files[0], basename,data,1);
		got_them_all &= loadhistSafely(& CardHistSet_bin[3][1], files[0], basename,"Bkg",3);
		got_them_all &= loadhistSafely(& CardHistSet_bin[3][2], files[1], basename,"MC",1);
		got_them_all &= loadhistSafely(& CardHistSet_bin[3][3], files[2], basename,"JECUp",1);
		got_them_all &= loadhistSafely(& CardHistSet_bin[3][4], files[3], basename,"JECDown",1);
		got_them_all &= loadhistSafely(& CardHistSet_bin[3][5], files[4], basename,"BtagEffUp",1);
		got_them_all &= loadhistSafely(& CardHistSet_bin[3][6], files[5], basename,"BtagEffDown",1);
		if (!got_them_all) {
			cout<<endl<<"MAJOR ERROR!! Could not find histograms for topo "<<channels[3].Data()<<" kinvar "<<kinvar<<endl;
			cout<<"    Check consistency among the params files. "<<endl;
			cout<<"    Continuing without it!!"<<endl<<endl;
			return;
		}
	}
	if(nchannels >4){
		for (short ibin = 4; ibin<nchannels; ibin++) {
			/*Debug*/ if(printlevel > 3) cout<<"loading topo "<<channels[ibin].Data()<<" "<<kinvar<<endl;
			basename = string("h")+kinvar.Data()+channels[ibin].Data()+"_"; //root names are basename+suffix
			got_them_all = true;
			got_them_all &= loadhistSafely(& CardHistSet_bin[ibin][0], files[0], basename,data,1);
			got_them_all &= loadhistSafely(& CardHistSet_bin[ibin][1], files[0], basename,"Bkg",3);
			got_them_all &= loadhistSafely(& CardHistSet_bin[ibin][2], files[1], basename,"MC",1);
			got_them_all &= loadhistSafely(& CardHistSet_bin[ibin][3], files[2], basename,"JECUp",1);
			got_them_all &= loadhistSafely(& CardHistSet_bin[ibin][4], files[3], basename,"JECDown",1);
			got_them_all &= loadhistSafely(& CardHistSet_bin[ibin][5], files[4], basename,"BtagEffUp",1);
			got_them_all &= loadhistSafely(& CardHistSet_bin[ibin][6], files[5], basename,"BtagEffDown",1);
			if (!got_them_all) {
				cout<<endl<<"MAJOR ERROR!! Could not find histograms for topo "<<channels[ibin].Data()<<" kinvar "<<kinvar<<endl;
				cout<<"    Check consistency among the params files. "<<endl;
				cout<<"    Continuing without it!!"<<endl<<endl;
				return;
			}
		}//end for
	}

		///Scale by Lumiscale
	float lumiscale = thisMCpoint->lumiscalefactor(Integrated_Luminosity_Data);
	if(printlevel>3) cout<<"scaling histogramms by factor "<<lumiscale<<endl;
	for(short j=2;j<=6;j++){
		for (short ibin = 0; ibin<nchannels; ibin++) {
			CardHistSet_bin[ibin][j]->Scale(lumiscale); //2-6 are the MC hists.
		}
//		CardHistSet_bin[0][j]->Scale(lumiscale); //2-6 are the MC hists.
//		if(nchannels >=2)CardHistSet_bin[1][j]->Scale(lumiscale); //2-6 are the MC hists.
//		if(nchannels >=3)CardHistSet_bin[2][j]->Scale(lumiscale); //2-6 are the MC hists.
//		if(nchannels >=4)CardHistSet_bin[3][j]->Scale(lumiscale); //2-6 are the MC hists.
	}
	if(printlevel > 3) cout<<"Setting up machinery for "<<CombinedTopoName<<" kinvar "<<kinvar<<endl;
		//spicific to one particluar thing.
	switch(nchannels){
		case 1:
			basename = string("h")+kinvar.Data()+CombinedTopoName.Data()+"_"; //assumes topo = CombinedTopoName
			makeLimitSettingMachinery(CardHistSet_bin[0], thisMCpoint, basename, CombinedTopoName, f_integ_systs[0], kinvar, true);
			break;

		case 2:
			makeLimitSettingMachinery_bbin2(CardHistSet_bin[0],CardHistSet_bin[1],thisMCpoint, channels, CombinedTopoName, f_integ_systs, kinvar, true);
			break;
		case 3:
			makeLimitSettingMachinery_bbin3(CardHistSet_bin[0],CardHistSet_bin[1],CardHistSet_bin[2],thisMCpoint, channels, CombinedTopoName, f_integ_systs, kinvar, true);
			break;
		case 4:
			makeLimitSettingMachinery_bbin4(CardHistSet_bin[0],CardHistSet_bin[1],CardHistSet_bin[2],CardHistSet_bin[3], thisMCpoint, channels, CombinedTopoName, f_integ_systs, kinvar, true);
			break;
		default:
			makeLimitSettingMachinery_bbinN(nchannels, CardHistSet_bin, thisMCpoint, channels, CombinedTopoName,f_integ_systs, kinvar, true);
			break;
	}//end switch
}//end SetupLimitsForOnePlot_bbin


void loadhist(TH1F** histout, TFile* PostAnaAnaFile, string basename,string suffix,int type){
	
		//histout is the hist you loaded in.
		//type is the type for s_MassBkgDists[1]. 1 = tag. 3 = bkg
		//suffix is what you'll tack onto the name
		//we set the root name to basename+suffix
	string instring = basename+s_MassBkgDists[type];
	TH1F* temp = (TH1F*) PostAnaAnaFile->Get( instring.c_str() );
			//fix the root name
	string newname = basename+suffix; //string newname = instring+"_"+suffix;
		//	MC_tag->SetName((newname).c_str());
	cout<<"Check recieved "<<newname<<" from hist, which in the file is called: "<<instring<<endl;
	cout<<temp->Integral();
	cout<<" Yup, I got it"<<endl;

	(*histout) = new TH1F(*temp);
	(*histout)->SetName(newname.data());
	string newtitle = string(";")+basename.data()+" (GeV)";//bad news charlie
	(*histout)->SetTitle((char*)newtitle.c_str());

}//end loadhist  //Done writing? Yes. Debugged? No

bool loadhistSafely(TH1F** histout, TFile* PostAnaAnaFile, string basename,string suffix,int type){

		//histout is the hist you loaded in.
		//type is the type for s_MassBkgDists[1]. 1 = tag. 3 = bkg
		//suffix is what you'll tack onto the name
		//we set the root name to basename+suffix
	string instring = basename+s_MassBkgDists[type];
	string newname = basename+suffix; //string newname = instring+"_"+suffix;

	TH1F* temp = 0;
	temp = (TH1F*) PostAnaAnaFile->GetObjectChecked( instring.c_str(), "TH1F");
		//	PostAnaAnaFile->GetObjectChecked( instring.c_str(), temp);
	if(!temp){
		cout<<"ERROR!! FAILED TO FIND "<<newname<<" ,which in the file is called: "<<instring<<endl;
		return false;
	}
		//fix the root name
	(*histout) = new TH1F(*temp);
	(*histout)->SetName(newname.data());
	string newtitle = string(";")+basename.data()+" (GeV)";//bad news charlie
	(*histout)->SetTitle((char*)newtitle.c_str());
	return true;
}//end loadhist  //Done writing? Yes. Debugged? No

//void makeLimitSettingMachinery(TH1F** CardHistSet, MCpoint * thisMCpoint, TString basename, TString topo, TString kinvar, bool appendCombineCommand){
void makeLimitSettingMachinery(TH1F** CardHistSet, MCpoint * thisMCpoint, TString basename, TString topo, float f_integ_systs, TString kinvar, bool appendCombineCommand){
		///This Sets up all hte machinery needed to run the point:
		///it makes the card file, a root file bundeling the MC points, and an entry in the bash script. 


		//package the MC hist and the MC systematic hists into one root file
	if(remake_Limit_packages) repackage_Systematics(CardHistSet, thisMCpoint->makeRootLimitPackageName(topo,kinvar) );//done

		//make the card file. 
	TString cardfilename = thisMCpoint->makeLimitCardName(topo,kinvar);
	if(remake_Limit_cards) makeCard_Systematics( CardHistSet , thisMCpoint, basename, topo, kinvar,f_integ_systs);//done

		//make an entry in the batch file that does the combined limits.
	if (appendCombineCommand) {
		ofstream CombineBatchFile;
		//CombineBatchFile.open(thisMCpoint->makeCombineBatchFileName());//open for appending
		CombineBatchFile.open(thisMCpoint->makeCombineBatchFileName(),ios_base::app);//open for appending
		TString toposhash = topo;
		toposhash = toposhash.ReplaceAll('!',"\\!");
		CombineBatchFile<<"echo \"************* DO COMBINE FOR "<<toposhash<<" "<<kinvar<<" **************\"  >> "<<thisMCpoint->makeLimitResultBundleName()<<endl;
                if(useHybridNew) CombineBatchFile<<"combine -M HybridNew --frequentist --testStat LHC "<<cardfilename<<" -H ProfileLikelihood --fork 8 >& temp"<<endl;
		else CombineBatchFile<<"combine -M Asymptotic "<<cardfilename<<" >& temp"<<endl;
		CombineBatchFile<<"cat temp >> "<<thisMCpoint->makeLimitResultBundleName()<<endl;
		CombineBatchFile<<"rm temp"<<endl;
		CombineBatchFile.close();
	}
	else{
		cout<<"Hey, code monkey: Run This!"<<endl;
                if(useHybridNew) cout<<"combine -M HybridNew --frequentist --testStat LHC "<<cardfilename<<" -H ProfileLikelihood --fork 8  >> "<<thisMCpoint->makeLimitResultName(topo, kinvar)<<endl;
		else cout<<"combine -M Asymptotic "<<cardfilename<<" >> "<<thisMCpoint->makeLimitResultName(topo, kinvar)<<endl;
	}

}//end new makeLimitSettingMachinery  //Done writing? Yes. Debugged? No

//void makeLimitSettingMachinery_bbin4(TH1F** CardHistSet1, TH1F** CardHistSet2, TH1F** CardHistSet3, TH1F** CardHistSet4, MCpoint * thisMCpoint, TString* channels, TString topo, TString kinvar, bool appendCombineCommand){
void makeLimitSettingMachinery_bbin4(TH1F** CardHistSet1, TH1F** CardHistSet2, TH1F** CardHistSet3, TH1F** CardHistSet4, MCpoint * thisMCpoint, TString* channels, TString topo, float f_integ_systs[4], TString kinvar, bool appendCombineCommand){
	cout<<"makeLimitSettingMachinery for bbin4"<<endl;
                ///This Sets up all hte machinery needed to run the b-binning set for this point:
                ///it makes the card file, a root file bundeling the MC points, and an entry in the bash script. 

                //package the MC hist and the MC systematic hists into one root file
        if(remake_Limit_packages) repackage_Systematics_bbin4(CardHistSet1, CardHistSet2, CardHistSet3, CardHistSet4, thisMCpoint->makeRootLimitPackageName(topo,kinvar) );//done

                //make the card file. 
        TString cardfilename = thisMCpoint->makeLimitCardName(topo,kinvar);
        if(remake_Limit_cards) makeCard_Systematics_bbin4( CardHistSet1, CardHistSet2, CardHistSet3, CardHistSet4, thisMCpoint, channels, topo, kinvar,f_integ_systs);//done

                //make an entry in the batch file that does the combined limits.
        if (appendCombineCommand) {
                ofstream CombineBatchFile;
                //CombineBatchFile.open(thisMCpoint->makeCombineBatchFileName());//open for appending
                CombineBatchFile.open(thisMCpoint->makeCombineBatchFileName(),ios_base::app);//open for appending
			TString toposhash = topo;
			toposhash = toposhash.ReplaceAll('!',"\\!");
                CombineBatchFile<<"echo \"************* DO COMBINE FOR "<<toposhash<<" "<<kinvar<<" **************\"  >> "<<thisMCpoint->makeLimitResultBundleName()<<endl;
                if(useHybridNew) CombineBatchFile<<"combine -M HybridNew --frequentist --testStat LHC "<<cardfilename<<" -H ProfileLikelihood --fork 8 >& temp"<<endl;
		else CombineBatchFile<<"combine -M Asymptotic "<<cardfilename<<" >& temp"<<endl;
                CombineBatchFile<<"cat temp >> "<<thisMCpoint->makeLimitResultBundleName()<<endl;
                CombineBatchFile<<"rm temp"<<endl;
                CombineBatchFile.close();
        }
        else{
                cout<<"Hey, code monkey: Run This!"<<endl;
                if(useHybridNew) cout<<"combine -M HybridNew --frequentist --testStat LHC "<<cardfilename<<" -H ProfileLikelihood --fork 8  >> "<<thisMCpoint->makeLimitResultName(topo, kinvar)<<endl;
		else cout<<"combine -M Asymptotic "<<cardfilename<<" >> "<<thisMCpoint->makeLimitResultName(topo, kinvar)<<endl;
        }

}//end makeLimitSettingMachinery_bbin4

//void makeLimitSettingMachinery_bbin3(TH1F** CardHistSet1, TH1F** CardHistSet2, TH1F** CardHistSet3, MCpoint * thisMCpoint, TString* channels, TString topo, TString kinvar, bool appendCombineCommand){
void makeLimitSettingMachinery_bbin3(TH1F** CardHistSet1, TH1F** CardHistSet2, TH1F** CardHistSet3, MCpoint * thisMCpoint, TString* channels, TString topo, float f_integ_systs[3], TString kinvar, bool appendCombineCommand){
	cout<<"makeLimitSettingMachinery for bbin3"<<endl;
                ///This Sets up all hte machinery needed to run the b-binning set for this point:
                ///it makes the card file, a root file bundeling the MC points, and an entry in the bash script. 

                //package the MC hist and the MC systematic hists into one root file
        if(remake_Limit_packages) repackage_Systematics_bbin3(CardHistSet1, CardHistSet2, CardHistSet3, thisMCpoint->makeRootLimitPackageName(topo,kinvar) );//done

                //make the card file. 
        TString cardfilename = thisMCpoint->makeLimitCardName(topo,kinvar);
        if(remake_Limit_cards) makeCard_Systematics_bbin3( CardHistSet1, CardHistSet2, CardHistSet3, thisMCpoint, channels, topo, kinvar,f_integ_systs);//done

                //make an entry in the batch file that does the combined limits.
        if (appendCombineCommand) {
                ofstream CombineBatchFile;
                //CombineBatchFile.open(thisMCpoint->makeCombineBatchFileName());//open for appending
                CombineBatchFile.open(thisMCpoint->makeCombineBatchFileName(),ios_base::app);//open for appending
			TString toposhash = topo;
			toposhash = toposhash.ReplaceAll('!',"\\!");
                CombineBatchFile<<"echo \"************* DO COMBINE FOR "<<toposhash<<" "<<kinvar<<" **************\"  >> "<<thisMCpoint->makeLimitResultBundleName()<<endl;
                if(useHybridNew) CombineBatchFile<<"combine -M HybridNew --frequentist --testStat LHC "<<cardfilename<<" -H ProfileLikelihood --fork 8 >& temp"<<endl;
		else CombineBatchFile<<"combine -M Asymptotic "<<cardfilename<<" >& temp"<<endl;
                CombineBatchFile<<"cat temp >> "<<thisMCpoint->makeLimitResultBundleName()<<endl;
                CombineBatchFile<<"rm temp"<<endl;
                CombineBatchFile.close();
        }
        else{
                cout<<"Hey, code monkey: Run This!"<<endl;
                if(useHybridNew) cout<<"combine -M HybridNew --frequentist --testStat LHC "<<cardfilename<<" -H ProfileLikelihood --fork 8  >> "<<thisMCpoint->makeLimitResultName(topo, kinvar)<<endl;
		else cout<<"combine -M Asymptotic "<<cardfilename<<" >> "<<thisMCpoint->makeLimitResultName(topo, kinvar)<<endl;
        }

}//end makeLimitSettingMachinery_bbin3

//void makeLimitSettingMachinery_bbin2(TH1F** CardHistSet1, TH1F** CardHistSet2, MCpoint * thisMCpoint, TString* channels, TString topo, TString kinvar, bool appendCombineCommand){
void makeLimitSettingMachinery_bbin2(TH1F** CardHistSet1, TH1F** CardHistSet2, MCpoint * thisMCpoint, TString* channels, TString topo,float f_integ_systs[2], TString kinvar, bool appendCombineCommand){
	cout<<"makeLimitSettingMachinery for bbin3"<<endl;
		///This Sets up all hte machinery needed to run the b-binning set for this point:
		///it makes the card file, a root file bundeling the MC points, and an entry in the bash script.

		//package the MC hist and the MC systematic hists into one root file
	if(remake_Limit_packages) repackage_Systematics_bbin2(CardHistSet1, CardHistSet2, thisMCpoint->makeRootLimitPackageName(topo,kinvar) );//done

		//make the card file.
	TString cardfilename = thisMCpoint->makeLimitCardName(topo,kinvar);
	if(remake_Limit_cards) makeCard_Systematics_bbin2( CardHistSet1, CardHistSet2, thisMCpoint, channels, topo, kinvar,f_integ_systs);//done

		//make an entry in the batch file that does the combined limits.
	if (appendCombineCommand) {
		ofstream CombineBatchFile;
			//CombineBatchFile.open(thisMCpoint->makeCombineBatchFileName());//open for appending
		CombineBatchFile.open(thisMCpoint->makeCombineBatchFileName(),ios_base::app);//open for appending
		TString toposhash = topo;
		toposhash = toposhash.ReplaceAll('!',"\\!");
		CombineBatchFile<<"echo \"************* DO COMBINE FOR "<<toposhash<<" "<<kinvar<<" **************\"  >> "<<thisMCpoint->makeLimitResultBundleName()<<endl;
                if(useHybridNew) CombineBatchFile<<"combine -M HybridNew --frequentist --testStat LHC "<<cardfilename<<" -H ProfileLikelihood --fork 8 >& temp"<<endl;
		else CombineBatchFile<<"combine -M Asymptotic "<<cardfilename<<" >& temp"<<endl;
		CombineBatchFile<<"cat temp >> "<<thisMCpoint->makeLimitResultBundleName()<<endl;
		CombineBatchFile<<"rm temp"<<endl;
		CombineBatchFile.close();
	}
	else{
		cout<<"Hey, code monkey: Run This!"<<endl;
                if(useHybridNew) cout<<"combine -M HybridNew --frequentist --testStat LHC "<<cardfilename<<" -H ProfileLikelihood --fork 8  >> "<<thisMCpoint->makeLimitResultName(topo, kinvar)<<endl;
		else cout<<"combine -M Asymptotic "<<cardfilename<<" >> "<<thisMCpoint->makeLimitResultName(topo, kinvar)<<endl;
	}

}//end makeLimitSettingMachinery_bbin2

//void makeLimitSettingMachinery_bbinN(short nchannels, TH1F* CardHistSet[][7], MCpoint * thisMCpoint, TString* channels, TString topo, TString kinvar, bool appendCombineCommand){
void makeLimitSettingMachinery_bbinN(short nchannels, TH1F* CardHistSet[][7], MCpoint * thisMCpoint, TString* channels, TString topo, float f_integ_systs[], TString kinvar, bool appendCombineCommand){

	cout<<"makeLimitSettingMachinery for bbinN, N="<<nchannels<<endl;
		///This Sets up all hte machinery needed to run the b-binning set for this point:
		///it makes the card file, a root file bundeling the MC points, and an entry in the bash script.

		//package the MC hist and the MC systematic hists into one root file
	if(remake_Limit_packages) repackage_Systematics_bbinN(nchannels, CardHistSet, thisMCpoint->makeRootLimitPackageName(topo,kinvar) );

		//make the card file.
	TString cardfilename = thisMCpoint->makeLimitCardName(topo,kinvar);
	if(remake_Limit_cards) makeCard_Systematics_bbinN(nchannels, CardHistSet, thisMCpoint, channels, topo, kinvar,f_integ_systs);

		//make an entry in the batch file that does the combined limits.
	if (appendCombineCommand) {
		ofstream CombineBatchFile;
			//CombineBatchFile.open(thisMCpoint->makeCombineBatchFileName());//open for appending
		CombineBatchFile.open(thisMCpoint->makeCombineBatchFileName(),ios_base::app);//open for appending
		TString toposhash = topo;
		toposhash = toposhash.ReplaceAll('!',"\\!");
		CombineBatchFile<<"echo \"************* DO COMBINE FOR "<<toposhash<<" "<<kinvar<<" **************\"  >> "<<thisMCpoint->makeLimitResultBundleName()<<endl;
                if(useHybridNew) CombineBatchFile<<"combine -M HybridNew --frequentist --testStat LHC "<<cardfilename<<" -H ProfileLikelihood --fork 8 >& temp"<<endl;
		else CombineBatchFile<<"combine -M Asymptotic "<<cardfilename<<" >& temp"<<endl;
		CombineBatchFile<<"cat temp >> "<<thisMCpoint->makeLimitResultBundleName()<<endl;
		CombineBatchFile<<"rm temp"<<endl;
		CombineBatchFile.close();
	}
	else{
		cout<<"Hey, code monkey: Run This!"<<endl;
                if(useHybridNew) cout<<"combine -M HybridNew --frequentist --testStat LHC "<<cardfilename<<" -H ProfileLikelihood --fork 8  >> "<<thisMCpoint->makeLimitResultName(topo, kinvar)<<endl;
		else cout<<"combine -M Asymptotic "<<cardfilename<<" >> "<<thisMCpoint->makeLimitResultName(topo, kinvar)<<endl;
	}

}//end makeLimitSettingMachinery_bbinN

void repackage_Systematics(TH1F** CardHistSet,TString rootfilename){
		//This writes the main MC hist and it's four systematics histograms to one file.
		//It does not include data or bkg. Those will be in a seperate file--the origional postAnaAna output file.

		//CardHistSet:
		//{Data_tag,  Data_bkg,	MC , MC_JECUp,  MC_JECDown, MC_BtagEffUp,	MC_BtagEffDown}
		//{ 0      ,  1       , 2  , 3       ,  4         , 5           ,   6             }
	TFile *f = new TFile(rootfilename,"RECREATE"); f->cd();
	CardHistSet[2]->Write();
	CardHistSet[3]->Write();
	CardHistSet[4]->Write();
	CardHistSet[5]->Write();
	CardHistSet[6]->Write();
	f->Close();
}//end repackage_Systematics 

void repackage_Systematics_bbin4(TH1F** CardHistSet1, TH1F** CardHistSet2, TH1F** CardHistSet3, TH1F** CardHistSet4, TString rootfilename){
	cout<<"make package for bbin4"<<endl;
	TFile *f = new TFile(rootfilename,"RECREATE"); f->cd();
	CardHistSet1[2]->Write();
	CardHistSet1[3]->Write();
	CardHistSet1[4]->Write();
	CardHistSet1[5]->Write();
	CardHistSet1[6]->Write();

	CardHistSet2[2]->Write();
	CardHistSet2[3]->Write();
	CardHistSet2[4]->Write();
	CardHistSet2[5]->Write();
	CardHistSet2[6]->Write();

	CardHistSet3[2]->Write();
	CardHistSet3[3]->Write();
	CardHistSet3[4]->Write();
	CardHistSet3[5]->Write();
	CardHistSet3[6]->Write();

	CardHistSet4[2]->Write();
	CardHistSet4[3]->Write();
	CardHistSet4[4]->Write();
	CardHistSet4[5]->Write();
	CardHistSet4[6]->Write();
	f->Close();
}//end repackage_Systematics_bbin4

void repackage_Systematics_bbin3(TH1F** CardHistSet1, TH1F** CardHistSet2, TH1F** CardHistSet3, TString rootfilename){
	cout<<"make package for bbin3"<<endl;
	TFile *f = new TFile(rootfilename,"RECREATE"); f->cd();
	CardHistSet1[2]->Write();
	CardHistSet1[3]->Write();
	CardHistSet1[4]->Write();
	CardHistSet1[5]->Write();
	CardHistSet1[6]->Write();

	CardHistSet2[2]->Write();
	CardHistSet2[3]->Write();
	CardHistSet2[4]->Write();
	CardHistSet2[5]->Write();
	CardHistSet2[6]->Write();

	CardHistSet3[2]->Write();
	CardHistSet3[3]->Write();
	CardHistSet3[4]->Write();
	CardHistSet3[5]->Write();
	CardHistSet3[6]->Write();
	f->Close();
}//end repackage_Systematics_bbin3

void repackage_Systematics_bbin2(TH1F** CardHistSet1, TH1F** CardHistSet2, TString rootfilename){
	cout<<"make package for bbin2"<<endl;
	TFile *f = new TFile(rootfilename,"RECREATE"); f->cd();
	CardHistSet1[2]->Write();
	CardHistSet1[3]->Write();
	CardHistSet1[4]->Write();
	CardHistSet1[5]->Write();
	CardHistSet1[6]->Write();

	CardHistSet2[2]->Write();
	CardHistSet2[3]->Write();
	CardHistSet2[4]->Write();
	CardHistSet2[5]->Write();
	CardHistSet2[6]->Write();
	f->Close();
}//end repackage_Systematics_bbin2

void repackage_Systematics_bbinN(short nchannels, TH1F* CardHistSet[][7], TString rootfilename){
	cout<<"make package for bbinN, N="<<nchannels<<endl;
	TFile *f = new TFile(rootfilename,"RECREATE"); f->cd();
	for (short ibin=0; ibin<nchannels; ibin++) {
		CardHistSet[ibin][2]->Write();
		CardHistSet[ibin][3]->Write();
		CardHistSet[ibin][4]->Write();
		CardHistSet[ibin][5]->Write();
		CardHistSet[ibin][6]->Write();
	}
	f->Close();
}//repackage_Systematics_bbinN

void makeCard_Systematics(TH1F** CardHistSet, MCpoint * thisMCpoint, TString basename, TString topo, TString kinvar,float f_integ_systs){
		//CardHistSet:
		//{Data_tag,  Data_bkg,	MC , MC_JECUp,  MC_JECDown, MC_BtagEffUp,	MC_BtagEffDown}
		//{ 0      ,  1       , 2  , 3       ,  4         , 5           ,   6             }
		//assumes all MC histograms are already scaled correctly to their lumiscale
	float dataIntegral = CardHistSet[0]->Integral();
	float bkgIntegral = CardHistSet[1]->Integral();
	float signalIntegral = CardHistSet[2]->Integral();
	//int nbins = CardHistSet[0]->GetNbinsX();//NBins in data
	MCpoint * datapoint = setupMCpoint("Data", "");//Fetch the data MCpoint for use in getting the plotsAndBkg file name

		//open some card file with some appropriate name.
	ofstream card;
	card.open(thisMCpoint->makeLimitCardName(topo,kinvar).Data());
		//	card<<"imax "<<1<<endl; //Is this either the number of data hist's or the number of bins. Idk. which.
	card<<"imax "<<1<<endl; //This is the number of channels = 1. I.E. decay modes. This is NOT the number of bins.
	card<<"jmax "<<1<<endl; //The number of backgrounds, not the number of bkg's + signals
	card<<"kmax *"<<endl; //The numbr of paracitic paramaters at the bottom, this can be left as *
	card<<"------------"<<endl;
		//references to the root files
	card<<"shapes data_obs * "<<datapoint->plotsAndBackground_mc.c_str()<<" "<<basename<<s_MassBkgDists[1]<<endl;
	card<<"shapes Bkg * "<<datapoint->plotsAndBackground_mc.c_str()<<" "<<basename<<s_MassBkgDists[3]<<endl;
	card<<"shapes MC * "<<thisMCpoint->makeRootLimitPackageName(topo, kinvar)<<" "<<basename<<"$PROCESS "<<basename<<"$SYSTEMATIC"<<endl;
	card<<"------------"<<endl;
	card<<"bin "<<topo<<endl;
	card<<"observation "<<dataIntegral<<endl;
	card<<"------------"<<endl;
	card<<"# now we list the expected events for signal and all backgrounds in that bin"<<endl;
	card<<"# the second 'process' line must have a positive number for backgrounds, and 0 for signal"<<endl;
	card<<"# then we list the independent sources of uncertainties, and give their effect (syst. error)"<<endl;
	card<<"# on each process and bin"<<endl;
	card<<"bin       "<<topo<<"    "<<topo<<endl;
	card<<"process MC     Bkg"<<endl;
	card<<"process  0          1"<<endl;
	card<<"rate     "<<signalIntegral<<"        "<<bkgIntegral<<endl;
	card<<"------------"<<endl;
	card<<"integ    lnN   -   "<<f_integ_systs<<endl;
	card<<"lumi    lnN   1.044    -   "<< endl;
	card<<"hlt    lnN   1.001    -   "<< endl;
	card<<"phoEff    lnN   1.01    -   "<< endl;
	card<<"JEC    shape   1    -   "<< endl;
	card<<"BtagEff shape   1    -   "<< endl;
	card.close();

	/*
	 # Simple counting experiment, with one signal and a few background processes
	 # Simplified version of the 35/pb H->WW analysis for mH = 160 GeV
	 imax 1  number of channels      = 1, number of data histograms.
	 jmax 1  number of backgrounds  //try it as the actual number of backgrounds where signals are not backgrounds. if that doesn't work try 1+nbackground
	 kmax *  number of nuisance parameters (sources of systematical uncertainties)
	 ------------
	 shapes * * therootfile.root $process
	 shapes data_obs * [data_postanaana file] histname_tag
	 shapes bkg * [data_postanaana file] histname_bkg
	 shapes sig * [MC_repackaged_file] [basename_]MC [basename_]$Systematic[Up/Down]
	 ------------
	 # we have just one channel, in which we observe 0 events
	 bin topo
	 observation 123
	 ------------
	 # now we list the expected events for signal and all backgrounds in that bin
	 # the second 'process' line must have a positive number for backgrounds, and 0 for signal
	 # then we list the independent sources of uncertainties, and give their effect (syst. error)
	 # on each process and bin
	 bin              topo     topo
	 process         signal    bkg
	 process          0        1
	 rate           1.47       0.63
	 ------------
	 lumi    lnN    1.11    -   lumi affects both signal and gg->WW (mc-driven). lnN = lognormal
	 JEC     shape
	 BTagEff shape
	 */

}//end makeCard_Systematics //Done writing? Yes. Debugged? No

void makeCard_Systematics_bbin4( TH1F** CardHistSet1,TH1F**  CardHistSet2, TH1F** CardHistSet3, TH1F** CardHistSet4, MCpoint* thisMCpoint, TString* channels, TString topo,TString kinvar,float f_integ_systs[4]){
                //CardHistSet:
                //{Data_tag,  Data_bkg, MC , MC_JECUp,  MC_JECDown, MC_BtagEffUp,       MC_BtagEffDown}
                //{ 0      ,  1       , 2  , 3       ,  4         , 5           ,   6             }
                //assumes all MC histograms are already scaled correctly to their lumiscale
	cout<<"makeCard for bbin4 "<<topo<<" "<<kinvar<<endl;
        float dataIntegral[4]; 
        float bkgIntegral[4]; 
        float signalIntegral[4];
        dataIntegral[0] = CardHistSet1[0]->Integral();
        bkgIntegral[0] = CardHistSet1[1]->Integral();
        signalIntegral[0] = CardHistSet1[2]->Integral();
        dataIntegral[1] = CardHistSet2[0]->Integral();
        bkgIntegral[1] = CardHistSet2[1]->Integral();
        signalIntegral[1] = CardHistSet2[2]->Integral();
        dataIntegral[2] = CardHistSet3[0]->Integral();
        bkgIntegral[2] = CardHistSet3[1]->Integral();
        signalIntegral[2] = CardHistSet3[2]->Integral();
        dataIntegral[3] = CardHistSet4[0]->Integral();
        bkgIntegral[3] = CardHistSet4[1]->Integral();
        signalIntegral[3] = CardHistSet4[2]->Integral();
        //int nbins = CardHistSet[0]->GetNbinsX();//NBins in data
        MCpoint * datapoint = setupMCpoint("Data", "");//Fetch the data MCpoint for use in getting the plotsAndBkg file name

                //open some card file with some appropriate name.
        ofstream card;
        card.open(thisMCpoint->makeLimitCardName(topo,kinvar).Data());
                //      card<<"imax "<<1<<endl; //Is this either the number of data hist's or the number of bins. Idk. which.
        card<<"imax "<<4<<endl; //This is the number of channels = 1. I.E. decay modes. This is NOT the number of bins.
        card<<"jmax "<<1<<endl; //The number of backgrounds, not the number of bkg's + signals
        card<<"kmax *"<<endl; //The numbr of paracitic paramaters at the bottom, this can be left as *
        card<<"------------"<<endl;
                //references to the root files
        card<<"shapes data_obs bin1 "<<datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[0]<<"_"<<s_MassBkgDists[1]<<endl; 
        card<<"shapes data_obs bin2 "<<datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[1]<<"_"<<s_MassBkgDists[1]<<endl; 
        card<<"shapes data_obs bin3 "<<datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[2]<<"_"<<s_MassBkgDists[1]<<endl; 
        card<<"shapes data_obs bin4 "<<datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[3]<<"_"<<s_MassBkgDists[1]<<endl; 

        card<<"shapes Bkg bin1 "<<     datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[0]<<"_"<<s_MassBkgDists[3]<<endl; 
        card<<"shapes Bkg bin2 "<<     datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[1]<<"_"<<s_MassBkgDists[3]<<endl; 
        card<<"shapes Bkg bin3 "<<     datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[2]<<"_"<<s_MassBkgDists[3]<<endl; 
        card<<"shapes Bkg bin4 "<<     datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[3]<<"_"<<s_MassBkgDists[3]<<endl; 

        card<<"shapes MC bin1 "<<thisMCpoint->makeRootLimitPackageName(topo, kinvar)<<" h"<<kinvar.Data()<<channels[0]<<"_$PROCESS h"<<kinvar.Data()<<channels[0]<<"_$SYSTEMATIC"<<endl; 
        card<<"shapes MC bin2 "<<thisMCpoint->makeRootLimitPackageName(topo, kinvar)<<" h"<<kinvar.Data()<<channels[1]<<"_$PROCESS h"<<kinvar.Data()<<channels[1]<<"_$SYSTEMATIC"<<endl; 
        card<<"shapes MC bin3 "<<thisMCpoint->makeRootLimitPackageName(topo, kinvar)<<" h"<<kinvar.Data()<<channels[2]<<"_$PROCESS h"<<kinvar.Data()<<channels[2]<<"_$SYSTEMATIC"<<endl; 
        card<<"shapes MC bin4 "<<thisMCpoint->makeRootLimitPackageName(topo, kinvar)<<" h"<<kinvar.Data()<<channels[3]<<"_$PROCESS h"<<kinvar.Data()<<channels[3]<<"_$SYSTEMATIC"<<endl; 
        card<<"------------"<<endl;
        //card<<"bin "<<channels[0]<<" "<<channels[1]<<" "<<channels[2]<<" "<<channels[3]<<endl;
        card<<"bin    bin1   bin2   bin3   bin4"<<endl;
        card<<"observation "<<dataIntegral[0]<<" "<<dataIntegral[1]<<" "<<dataIntegral[2]<<" "<<dataIntegral[3]<<endl;
        card<<"------------"<<endl;
        card<<"# now we list the expected events for signal and all backgrounds in that bin"<<endl;
        card<<"# the second 'process' line must have a positive number for backgrounds, and 0 for signal"<<endl;
        card<<"# then we list the independent sources of uncertainties, and give their effect (syst. error)"<<endl;
        card<<"# on each process and bin"<<endl;
        card<<"bin     bin1   bin1    bin2   bin2    bin3   bin3    bin4   bin4"<<endl;
        card<<"process MC     Bkg     MC     Bkg     MC     Bkg     MC     Bkg"<<endl;
        card<<"process  0      1      0       1      0       1      0       1"<<endl;
        card<<"rate     "<<signalIntegral[0]<<" "<<bkgIntegral[0]<<" "<<signalIntegral[1]<<" "<<bkgIntegral[1]<<" "<<signalIntegral[2]<<" "<<bkgIntegral[2]<<" "<<signalIntegral[3]<<" "<<bkgIntegral[3]<<endl;
        card<<"------------"<<endl;
        card<<"integ    lnN   -   "<<f_integ_systs[0]<<"  -  "<<f_integ_systs[1]<<"  -  "<<f_integ_systs[2]<<"  -  "<<f_integ_systs[3]<<endl;
        card<<"lumi    lnN   1.044    -   1.044    -  1.044    -  1.044    -  "<< endl;
        card<<"hlt    lnN   1.001    -   1.001    -  1.001    -  1.001    -  "<< endl;
	card<<"phoEff    lnN   1.01    -   1.01    -   1.01    -   1.01    -   "<< endl;
        card<<"JEC    shape   1    -   1    -   1    -   1    -   "<< endl;
        card<<"BtagEff shape   1    -   1    -   1    -   1    -   "<< endl;
        card.close();
}//end makeCard_Systematics_bbin4

void makeCard_Systematics_bbin3( TH1F** CardHistSet1,TH1F**  CardHistSet2, TH1F** CardHistSet3, MCpoint* thisMCpoint, TString* channels, TString topo,TString kinvar,float f_integ_systs[3]){
                //CardHistSet:
                //{Data_tag,  Data_bkg, MC , MC_JECUp,  MC_JECDown, MC_BtagEffUp,       MC_BtagEffDown}
                //{ 0      ,  1       , 2  , 3       ,  4         , 5           ,   6             }
                //assumes all MC histograms are already scaled correctly to their lumiscale
	cout<<"makeCard for bbin3 "<<topo<<" "<<kinvar<<endl;
        float dataIntegral[3]; 
        float bkgIntegral[3]; 
        float signalIntegral[3];
        dataIntegral[0] = CardHistSet1[0]->Integral();
        bkgIntegral[0] = CardHistSet1[1]->Integral();
        signalIntegral[0] = CardHistSet1[2]->Integral();
        dataIntegral[1] = CardHistSet2[0]->Integral();
        bkgIntegral[1] = CardHistSet2[1]->Integral();
        signalIntegral[1] = CardHistSet2[2]->Integral();
        dataIntegral[2] = CardHistSet3[0]->Integral();
        bkgIntegral[2] = CardHistSet3[1]->Integral();
        signalIntegral[2] = CardHistSet3[2]->Integral();
        //int nbins = CardHistSet[0]->GetNbinsX();//NBins in data
        MCpoint * datapoint = setupMCpoint("Data", "");//Fetch the data MCpoint for use in getting the plotsAndBkg file name

                //open some card file with some appropriate name.
        ofstream card;
        card.open(thisMCpoint->makeLimitCardName(topo,kinvar).Data());
                //      card<<"imax "<<1<<endl; //Is this either the number of data hist's or the number of bins. Idk. which.
        card<<"imax "<<3<<endl; //This is the number of channels = 1. I.E. decay modes. This is NOT the number of bins.
        card<<"jmax "<<1<<endl; //The number of backgrounds, not the number of bkg's + signals
        card<<"kmax *"<<endl; //The numbr of paracitic paramaters at the bottom, this can be left as *
        card<<"------------"<<endl;
                //references to the root files
        //card<<"shapes data_obs * "<<datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<"$CHANNEL_"<<s_MassBkgDists[1]<<endl; 
        //card<<"shapes Bkg * "<<     datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<"$CHANNEL_"<<s_MassBkgDists[3]<<endl; 
        //card<<"shapes MC * "<<thisMCpoint->makeRootLimitPackageName(topo, kinvar)<<" h"<<kinvar.Data()<<"$CHANNEL_$PROCESS h"<<kinvar.Data()<<"$CHANNEL_$SYSTEMATIC"<<endl; 
        card<<"shapes data_obs bin1 "<<datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[0]<<"_"<<s_MassBkgDists[1]<<endl; 
        card<<"shapes data_obs bin2 "<<datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[1]<<"_"<<s_MassBkgDists[1]<<endl; 
        card<<"shapes data_obs bin3 "<<datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[2]<<"_"<<s_MassBkgDists[1]<<endl; 
        card<<"shapes Bkg bin1 "<<     datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[0]<<"_"<<s_MassBkgDists[3]<<endl; 
        card<<"shapes Bkg bin2 "<<     datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[1]<<"_"<<s_MassBkgDists[3]<<endl; 
        card<<"shapes Bkg bin3 "<<     datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[2]<<"_"<<s_MassBkgDists[3]<<endl; 
        card<<"shapes MC bin1 "<<thisMCpoint->makeRootLimitPackageName(topo, kinvar)<<" h"<<kinvar.Data()<<channels[0]<<"_$PROCESS h"<<kinvar.Data()<<channels[0]<<"_$SYSTEMATIC"<<endl; 
        card<<"shapes MC bin2 "<<thisMCpoint->makeRootLimitPackageName(topo, kinvar)<<" h"<<kinvar.Data()<<channels[1]<<"_$PROCESS h"<<kinvar.Data()<<channels[1]<<"_$SYSTEMATIC"<<endl; 
        card<<"shapes MC bin3 "<<thisMCpoint->makeRootLimitPackageName(topo, kinvar)<<" h"<<kinvar.Data()<<channels[2]<<"_$PROCESS h"<<kinvar.Data()<<channels[2]<<"_$SYSTEMATIC"<<endl; 
        card<<"------------"<<endl;
        //card<<"bin "<<channels[0]<<" "<<channels[1]<<" "<<channels[2]<<endl;
        card<<"bin    bin1   bin2   bin3"<<endl;
        card<<"observation "<<dataIntegral[0]<<" "<<dataIntegral[1]<<" "<<dataIntegral[2]<<endl;
        card<<"------------"<<endl;
        card<<"# now we list the expected events for signal and all backgrounds in that bin"<<endl;
        card<<"# the second 'process' line must have a positive number for backgrounds, and 0 for signal"<<endl;
        card<<"# then we list the independent sources of uncertainties, and give their effect (syst. error)"<<endl;
        card<<"# on each process and bin"<<endl;
        //card<<"bin       "<<channels[0]<<" "<<channels[0]<<" "<<channels[1]<<" "<<channels[1]<<" "<<channels[2]<<" "<<channels[2]<<endl;
        card<<"bin     bin1   bin1    bin2   bin2    bin3   bin3"<<endl;
        card<<"process MC     Bkg     MC     Bkg     MC     Bkg"<<endl;
        card<<"process  0      1      0       1      0       1 "<<endl;
        card<<"rate     "<<signalIntegral[0]<<" "<<bkgIntegral[0]<<" "<<signalIntegral[1]<<" "<<bkgIntegral[1]<<" "<<signalIntegral[2]<<" "<<bkgIntegral[2]<<endl;
        card<<"------------"<<endl;
        card<<"integ    lnN   -   "<<f_integ_systs[0]<<"  -  "<<f_integ_systs[1]<<"  -  "<<f_integ_systs[2]<<endl;
        card<<"lumi    lnN   1.044    -   1.044    -  1.044    - "<< endl;
        card<<"hlt    lnN   1.001    -   1.001    -  1.001    - "<< endl;
	card<<"phoEff  lnN   1.01    -   1.01    -    1.01    - "<< endl;
        card<<"JEC    shape   1    -   1    -   1    -   "<< endl;
        card<<"BtagEff shape   1    -   1    -   1    -  "<< endl;
        card.close();
}//end makeCard_Systematics_bbin3

void makeCard_Systematics_bbin2( TH1F** CardHistSet1,TH1F**  CardHistSet2, MCpoint* thisMCpoint, TString* channels, TString topo,TString kinvar,float f_integ_systs[2]){
		//CardHistSet:
		//{Data_tag,  Data_bkg, MC , MC_JECUp,  MC_JECDown, MC_BtagEffUp,       MC_BtagEffDown}
		//{ 0      ,  1       , 2  , 3       ,  4         , 5           ,   6             }
		//assumes all MC histograms are already scaled correctly to their lumiscale
	cout<<"makeCard for bbin2 "<<topo<<" "<<kinvar<<endl;
	float dataIntegral[2];
	float bkgIntegral[2];
	float signalIntegral[2];
	dataIntegral[0] = CardHistSet1[0]->Integral();
	bkgIntegral[0] = CardHistSet1[1]->Integral();
	signalIntegral[0] = CardHistSet1[2]->Integral();
	dataIntegral[1] = CardHistSet2[0]->Integral();
	bkgIntegral[1] = CardHistSet2[1]->Integral();
	signalIntegral[1] = CardHistSet2[2]->Integral();
        //int nbins = CardHistSet[0]->GetNbinsX();//NBins in data
	MCpoint * datapoint = setupMCpoint("Data", "");//Fetch the data MCpoint for use in getting the plotsAndBkg file name

		//open some card file with some appropriate name.
	ofstream card;
	card.open(thisMCpoint->makeLimitCardName(topo,kinvar).Data());
		//      card<<"imax "<<1<<endl; //Is this either the number of data hist's or the number of bins. Idk. which.
	card<<"imax "<<2<<endl; //This is the number of channels = 1. I.E. decay modes. This is NOT the number of bins.
	card<<"jmax "<<1<<endl; //The number of backgrounds, not the number of bkg's + signals
	card<<"kmax *"<<endl; //The numbr of paracitic paramaters at the bottom, this can be left as *
	card<<"------------"<<endl;
		//references to the root files
        //card<<"shapes data_obs * "<<datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<"$CHANNEL_"<<s_MassBkgDists[1]<<endl;
        //card<<"shapes Bkg * "<<     datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<"$CHANNEL_"<<s_MassBkgDists[3]<<endl;
        //card<<"shapes MC * "<<thisMCpoint->makeRootLimitPackageName(topo, kinvar)<<" h"<<kinvar.Data()<<"$CHANNEL_$PROCESS h"<<kinvar.Data()<<"$CHANNEL_$SYSTEMATIC"<<endl;
	card<<"shapes data_obs bin1 "<<datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[0]<<"_"<<s_MassBkgDists[1]<<endl;
	card<<"shapes data_obs bin2 "<<datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[1]<<"_"<<s_MassBkgDists[1]<<endl;
	card<<"shapes Bkg bin1 "<<     datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[0]<<"_"<<s_MassBkgDists[3]<<endl;
	card<<"shapes Bkg bin2 "<<     datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[1]<<"_"<<s_MassBkgDists[3]<<endl;
	card<<"shapes MC bin1 "<<thisMCpoint->makeRootLimitPackageName(topo, kinvar)<<" h"<<kinvar.Data()<<channels[0]<<"_$PROCESS h"<<kinvar.Data()<<channels[0]<<"_$SYSTEMATIC"<<endl;
	card<<"shapes MC bin2 "<<thisMCpoint->makeRootLimitPackageName(topo, kinvar)<<" h"<<kinvar.Data()<<channels[1]<<"_$PROCESS h"<<kinvar.Data()<<channels[1]<<"_$SYSTEMATIC"<<endl;
	card<<"------------"<<endl;
        //card<<"bin "<<channels[0]<<" "<<channels[1]<<" "<<channels[2]<<endl;
	card<<"bin    bin1   bin2"<<endl;
	card<<"observation "<<dataIntegral[0]<<" "<<dataIntegral[1]<<endl;
	card<<"------------"<<endl;
	card<<"# now we list the expected events for signal and all backgrounds in that bin"<<endl;
	card<<"# the second 'process' line must have a positive number for backgrounds, and 0 for signal"<<endl;
	card<<"# then we list the independent sources of uncertainties, and give their effect (syst. error)"<<endl;
	card<<"# on each process and bin"<<endl;
        //card<<"bin       "<<channels[0]<<" "<<channels[0]<<" "<<channels[1]<<" "<<channels[1]<<" "<<channels[2]<<" "<<channels[2]<<endl;
	card<<"bin     bin1   bin1    bin2   bin2"<<endl;
	card<<"process MC     Bkg     MC     Bkg"<<endl;
	card<<"process  0      1      0       1"<<endl;
	card<<"rate     "<<signalIntegral[0]<<" "<<bkgIntegral[0]<<" "<<signalIntegral[1]<<" "<<bkgIntegral[1]<<endl;
	card<<"------------"<<endl;
	card<<"integ    lnN   -   "<<f_integ_systs[0]<<"  -  "<<f_integ_systs[1]<<endl;
	card<<"lumi    lnN   1.044    -   1.044    - "<< endl;
	card<<"hlt    lnN   1.001    -   1.001    - "<< endl;
	card<<"phoEff    lnN   1.01    -   1.01    - "<< endl;
	card<<"JEC    shape   1    -   1    - "<< endl;
	card<<"BtagEff shape   1    -   1    - "<< endl;
	card.close();
}//end makeCard_Systematics_bbin2

void makeCard_Systematics_bbinN(short nchannels, TH1F* CardHistSet[][7], MCpoint* thisMCpoint, TString* channels, TString topo,TString kinvar,float f_integ_systs[]){
		//CardHistSet:
		//{Data_tag,  Data_bkg, MC , MC_JECUp,  MC_JECDown, MC_BtagEffUp,       MC_BtagEffDown}
		//{ 0      ,  1       , 2  , 3       ,  4         , 5           ,   6             }
		//assumes all MC histograms are already scaled correctly to their lumiscale
	cout<<"makeCard for bbinN, N="<<nchannels<<" "<<topo<<" "<<kinvar<<endl;
	float dataIntegral[nchannels];
	float bkgIntegral[nchannels];
	float signalIntegral[nchannels];
	for (short ibin=0; ibin<nchannels; ibin++) dataIntegral[ibin] = CardHistSet[ibin][0]->Integral();
	for (short ibin=0; ibin<nchannels; ibin++) bkgIntegral[ibin] = CardHistSet[ibin][1]->Integral();
	for (short ibin=0; ibin<nchannels; ibin++) signalIntegral[ibin] = CardHistSet[ibin][2]->Integral();
        //int nbins = CardHistSet[0]->GetNbinsX();//NBins in data
	MCpoint * datapoint = setupMCpoint("Data", "");//Fetch the data MCpoint for use in getting the plotsAndBkg file name

		//open some card file with some appropriate name.
	ofstream card;
	card.open(thisMCpoint->makeLimitCardName(topo,kinvar).Data());
		//      card<<"imax "<<1<<endl; //Is this either the number of data hist's or the number of bins. Idk. which.
	card<<"imax "<<nchannels<<endl; //This is the number of channels = 1. I.E. decay modes. This is NOT the number of bins.
	card<<"jmax "<<1<<endl; //The number of backgrounds, not the number of bkg's + signals
	card<<"kmax *"<<endl; //The numbr of paracitic paramaters at the bottom, this can be left as *
	card<<"------------"<<endl;
		//references to the root files
        //card<<"shapes data_obs * "<<datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<"$CHANNEL_"<<s_MassBkgDists[1]<<endl;
        //card<<"shapes Bkg * "<<     datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<"$CHANNEL_"<<s_MassBkgDists[3]<<endl;
        //card<<"shapes MC * "<<thisMCpoint->makeRootLimitPackageName(topo, kinvar)<<" h"<<kinvar.Data()<<"$CHANNEL_$PROCESS h"<<kinvar.Data()<<"$CHANNEL_$SYSTEMATIC"<<endl;
	for (short ibin=0; ibin<nchannels; ibin++) card<<"shapes data_obs bin"<<ibin+1<<" "<<datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[ibin]<<"_"<<s_MassBkgDists[1]<<endl;
	for (short ibin=0; ibin<nchannels; ibin++) card<<"shapes Bkg bin"<<ibin+1<<" "<<datapoint->plotsAndBackground_mc.c_str()<<" h"<<kinvar.Data()<<channels[ibin]<<"_"<<s_MassBkgDists[3]<<endl;
	for (short ibin=0; ibin<nchannels; ibin++) card<<"shapes MC bin"<<ibin+1<<" "<<thisMCpoint->makeRootLimitPackageName(topo, kinvar)<<" h"<<kinvar.Data()<<channels[ibin]<<"_$PROCESS h"<<kinvar.Data()<<channels[ibin]<<"_$SYSTEMATIC"<<endl;
	card<<"------------"<<endl;
        //card<<"bin "<<channels[0]<<" "<<channels[1]<<" "<<channels[2]<<endl;
	card<<"bin"; for (short ibin=0; ibin<nchannels; ibin++){card<<"    bin"<<ibin+1;} card<<endl;//	card<<"bin    bin1   bin2"<<endl;
	card<<"observation"; for (short ibin=0; ibin<nchannels; ibin++){card<<"  "<<dataIntegral[ibin];} card<<endl;//card<<"observation "<<dataIntegral[0]<<" "<<dataIntegral[1]<<endl;
	card<<"------------"<<endl;
	card<<"# now we list the expected events for signal and all backgrounds in that bin"<<endl;
	card<<"# the second 'process' line must have a positive number for backgrounds, and 0 for signal"<<endl;
	card<<"# then we list the independent sources of uncertainties, and give their effect (syst. error)"<<endl;
	card<<"# on each process and bin"<<endl;
	card<<"bin"; for (short ibin=0; ibin<nchannels; ibin++){card<<"    bin"<<ibin+1<<"    bin"<<ibin+1;} card<<endl;//card<<"bin     bin1   bin1    bin2   bin2"<<endl;
	card<<"process"; for (short ibin=0; ibin<nchannels; ibin++){card<<"    MC    Bkg";} card<<endl;//card<<"process MC     Bkg     MC     Bkg"<<endl;
	card<<"process"; for (short ibin=0; ibin<nchannels; ibin++){card<<"     0     1 ";} card<<endl;//card<<"process  0      1      0       1"<<endl;
	card<<"rate     "; for (short ibin=0; ibin<nchannels; ibin++){card<<signalIntegral[ibin]<<" "<<bkgIntegral[ibin]<<" ";} card<<endl;//	card<<"rate     "<<signalIntegral[0]<<" "<<bkgIntegral[0]<<" "<<signalIntegral[1]<<" "<<bkgIntegral[1]<<endl;
	card<<"------------"<<endl;
	card<<"integ    lnN"; for (short ibin=0; ibin<nchannels; ibin++){card<<"   -   "<<f_integ_systs[ibin];} card<<endl;//	card<<"lumi    lnN   1.044    -   1.044    - "<< endl;
	card<<"lumi    lnN"; for (short ibin=0; ibin<nchannels; ibin++){card<<"   1.044    -";} card<<endl;//	card<<"lumi    lnN   1.044    -   1.044    - "<< endl;
	card<<"hlt    lnN"; for (short ibin=0; ibin<nchannels; ibin++){card<<"   1.001    -";} card<<endl;//	card<<"hlt    lnN   1.001    -   1.001    - "<< endl;
	card<<"phoEff    lnN"; for (short ibin=0; ibin<nchannels; ibin++){card<<"   1.01    -";} card<<endl;//card<<"phoEff   lnN   1.01    -   1.01    - "<< endl;
	card<<"JEC    shape"; for (short ibin=0; ibin<nchannels; ibin++){card<<"   1    -";} card<<endl;//card<<"JEC    shape   1    -   1    - "<< endl;
	card<<"BtagEff shape"; for (short ibin=0; ibin<nchannels; ibin++){card<<"   1    -";} card<<endl;//	card<<"BtagEff shape   1    -   1    - "<< endl;
	card.close();
}//end makeCard_Systematics_bbinN


	//obsolete, but working
/*void makeCard(TH1F* data, TH1F* bkg, TH1F* MC, TString MCpointname, TString topo, TString kinvar){
 float dataIntegral = data->Integral();
 float bkgIntegral = bkg->Integral();
 float signalIntegral = MC->Integral();//assumes you already hit it with the lumiscale.
 TString cardfilename = makeLimitCardName(MCpointname,topo,kinvar);
 int nbins = data->GetNbinsX();

 //open some card file with some appropriate name.
 ofstream card;
 card.open(cardfilename);
 //	card<<"imax "<<1<<endl; //Is this either the number of data hist's or the number of bins. Idk. which.
 card<<"imax "<<1<<endl; //This is the number of channels = 1. I.E. decay modes. This is NOT the number of bins.
 card<<"jmax "<<1<<endl; //The number of backgrounds, not the number of bkg's + signals
 card<<"kmax *"<<endl; //The numbr of paracitic paramaters at the bottom, this can be left as *
 card<<"------------"<<endl;
 //references to the root files
 card<<"shapes * * "<<makeRootLimitPackageName(MCpointname, topo, kinvar)<<" $PROCESS $PROCESS_$SYSTEMATIC"<<endl;
 card<<"------------"<<endl;
 card<<"bin 1"<<endl;
 card<<"observation "<<dataIntegral<<endl;
 card<<"------------"<<endl;
 card<<"# now we list the expected events for signal and all backgrounds in that bin"<<endl;
 card<<"# the second 'process' line must have a positive number for backgrounds, and 0 for signal"<<endl;
 card<<"# then we list the independent sources of uncertainties, and give their effect (syst. error)"<<endl;
 card<<"# on each process and bin"<<endl;
 card<<"bin       1        1"<<endl;
 card<<"process MCsig     ddBkg"<<endl;
 card<<"process  0          1"<<endl;
 card<<"rate     "<<signalIntegral<<"        "<<bkgIntegral<<endl;
 card<<"------------"<<endl;
 card<<"lumi    lnN   1.11    -   "<< endl;
 //card<<"JEC shape  1  - "<<endl;
 //card<<"BtagEff shape  1  - "<<endl;
 card.close();
 }//makeCard
 */


TString TackBeforeRoot(TString main, TString tack){
	TString mantissa = main.ReplaceAll(".root",5,"",0);
	mantissa+= tack;
	mantissa+=".root";
	return mantissa;
}//Done writing? Yes. Debugged? No

	//Run all topologies on the whole grid.
	//To run these, you need all the returned files from the grid, includeing the JEC and BTag files.

//void SetupSummedLimitsForStrongGrid(){
	//DO NOT USE THIS, IT'S ABSURDLY SLOW!!
//	for (int iTop = 0; iTop<nEventTopologies_limit; iTop++) {
//		SetupSummedLimitsForStrongGrid(s_EventTopology_limit[iTop]);
//	}
//}
	//Run all topologies on the whole grid
//void SetupSummedLimitsForWeakGrid(){
	//DO NOT USE THIS, IT'S ABSURDLY SLOW!!
//	for (int iTop = 0; iTop<nEventTopologies_limit; iTop++) {
//		SetupSummedLimitsForWeakGrid(s_EventTopology_limit[iTop]);
//	}
//}

void SetupSummedLimitsForStrongGrid(){
		//for every mass point
		//    for every topo
		//        for every kinvar: setup
	std::vector<MCpoint*> Points = setupMCpoints();
	std::vector<MCpoint*> bbaa;
	std::vector<MCpoint*> wwaa;
	std::vector<MCpoint*> zzaa;
	std::vector<MCpoint*> ttaa;
	std::vector<MCpoint*> bbaa_mu;
	std::vector<MCpoint*> wwaa_mu;
	std::vector<MCpoint*> zzaa_mu;
	std::vector<MCpoint*> ttaa_mu;
	for(std::vector<MCpoint*>::iterator it = Points.begin();it != Points.end();it++){
		if((*it)->type < 10 || (*it)->type >= 20) continue;
		else if((*it)->type == 10) bbaa.push_back(*it);
		else if((*it)->type == 11) wwaa.push_back(*it);
		else if((*it)->type == 12) zzaa.push_back(*it);
		else if((*it)->type == 13) ttaa.push_back(*it);
		else if((*it)->type == 20) bbaa_mu.push_back(*it);
		else if((*it)->type == 21) wwaa_mu.push_back(*it);
		else if((*it)->type == 22) zzaa_mu.push_back(*it);
		else if((*it)->type == 23) ttaa_mu.push_back(*it);
	}
        Labledfloat integ_systs;
        suckinIntegralSystematics(integ_systs);
	for(std::vector<MCpoint*>::iterator it = bbaa.begin();it != bbaa.end();it++){
		MCpoint* points[8];
		points[0] = *it;
		int found_them_all = 1;
		bool gotit = false;
		for(std::vector<MCpoint*>::iterator it2 = wwaa.begin();(!gotit) && it2 != wwaa.end();it2++){ //find the matching point in wwaa
			if ((*it2)->Mstop == (*it)->Mstop && (*it2)->Mhiggsino == (*it)->Mhiggsino ) {
				points[1] = *it2;
				found_them_all++;
				gotit = true;
				break;
			}
		}
		gotit = false;
		for(std::vector<MCpoint*>::iterator it2 = zzaa.begin();(!gotit) && it2 != zzaa.end();it2++){ //find the matching point in zzaa
			if ((*it2)->Mstop == (*it)->Mstop && (*it2)->Mhiggsino == (*it)->Mhiggsino ) {
				points[2] = *it2;
				found_them_all++;
				gotit = true;
				break;
			}
		}
		gotit = false;
		for(std::vector<MCpoint*>::iterator it2 = zzaa.begin();(!gotit) && it2 != zzaa.end();it2++){ //find the matching point in ttaa
			if ((*it2)->Mstop == (*it)->Mstop && (*it2)->Mhiggsino == (*it)->Mhiggsino ) {
				points[3] = *it2;
				found_them_all++;
				gotit = true;
				break;
			}
		}

                for(std::vector<MCpoint*>::iterator it2 = bbaa_mu.begin();it2 != bbaa_mu.end();it2++){ //find the matching point in bbaa_mu
                        if ((*it2)->Mhiggsino == (*it)->Mhiggsino ) {
                                points[4] = *it2;
                                found_them_all++;
                                break;
                        }
                }
                for(std::vector<MCpoint*>::iterator it2 = wwaa_mu.begin();it2 != wwaa_mu.end();it2++){ //find the matching point in wwaa_mu
                        if ((*it2)->Mhiggsino == (*it)->Mhiggsino ) {
                                points[5] = *it2;
                                found_them_all++;
                                break;
                        }
                }
                for(std::vector<MCpoint*>::iterator it2 = zzaa_mu.begin();it2 != zzaa_mu.end();it2++){ //find the matching point in zzaa_mu
                        if ((*it2)->Mhiggsino == (*it)->Mhiggsino ) {
                                points[6] = *it2;
                                found_them_all++;
                                break;
                        }
                }
                for(std::vector<MCpoint*>::iterator it2 = ttaa_mu.begin();it2 != ttaa_mu.end();it2++){ //find the matching point in ttaa_mu
                        if ((*it2)->Mhiggsino == (*it)->Mhiggsino ) {
                                points[7] = *it2;
                                found_them_all++;
                                break;
                        }
                }




		if (found_them_all != 8) { //make sure you found them all.
			printf("Error! Can't find all the categories for Mst = %i Mh = %i\n",(*it)->Mstop,(*it)->Mhiggsino);
			printf("Not Generating the card files for this point!!\n");
			continue;
		}
		printf("Setup for st_%i_mu_%i\n",(*it)->Mstop,(*it)->Mhiggsino);
		SetupSummedLimitsOneMassPoint(points, 8 , integ_systs);
	}//end for all MC points
}//SetupSummedLimitsForStrongGrid

void SetupSummedLimitsForWeakGrid(){
		//for every mass point
		//    for every topo
		//        for every kinvar: setup
	std::vector<MCpoint*> Points = setupMCpoints();
	std::vector<MCpoint*> bbaa;
	std::vector<MCpoint*> wwaa;
	std::vector<MCpoint*> zzaa;
	std::vector<MCpoint*> ttaa;
	for(std::vector<MCpoint*>::iterator it = Points.begin();it != Points.end();it++){
		if((*it)->type < 20 || (*it)->type >= 30) continue;
		else if((*it)->type == 20) bbaa.push_back(*it);
		else if((*it)->type == 21) wwaa.push_back(*it);
		else if((*it)->type == 22) zzaa.push_back(*it);
		else if((*it)->type == 23) ttaa.push_back(*it);
	}
	Labledfloat integ_systs;
        suckinIntegralSystematics(integ_systs);

	for(std::vector<MCpoint*>::iterator it = bbaa.begin();it != bbaa.end();it++){
		MCpoint* points[4];
		points[0] = *it;
		int found_them_all = 1;
		bool gotit = false;
		for(std::vector<MCpoint*>::iterator it2 = wwaa.begin();(!gotit) && it2 != wwaa.end();it2++){ //find the matching point in wwaa
			if ( (*it2)->Mhiggsino == (*it)->Mhiggsino ) {
				points[1] = *it2;
				found_them_all++;
				gotit = true;
				break;
			}
		}
		gotit = false;
		for(std::vector<MCpoint*>::iterator it2 = zzaa.begin();(!gotit) && it2 != zzaa.end();it2++){ //find the matching point in zzaa
			if ( (*it2)->Mhiggsino == (*it)->Mhiggsino ) {
				points[2] = *it2;
				found_them_all++;
				gotit = true;
				break;
			}
		}
		gotit = false;
		for(std::vector<MCpoint*>::iterator it2 = zzaa.begin();(!gotit) && it2 != zzaa.end();it2++){ //find the matching point in ttaa
			if ( (*it2)->Mhiggsino == (*it)->Mhiggsino ) {
				points[3] = *it2;
				found_them_all++;
				gotit = true;
				break;
			}
		}
		if (found_them_all != 4) { //make sure you found them all.
			printf("Error! Can't find all the categories for Mst = %i Mh = %i\n",(*it)->Mstop,(*it)->Mhiggsino);
			printf("Not Generating the card files for this point!!\n");
			continue;
		}
		printf("Setup for mu_%i\n",(*it)->Mhiggsino);
		SetupSummedLimitsOneMassPoint(points, 4 ,integ_systs);
	}//end for all MC points
}//SetupSummedLimitsForWeakGrid



	//To run these, you need all the returned files from the grid, includeing the JEC and BTag files.
	//for manual use only, this is pretty slow
void SetupSummedLimitsForStrongGrid(TString topo){
	std::vector<MCpoint*> Points = setupMCpoints();
	std::vector<MCpoint*> bbaa;
	std::vector<MCpoint*> wwaa;
	std::vector<MCpoint*> zzaa;
	std::vector<MCpoint*> ttaa;
	std::vector<MCpoint*> bbaa_mu;
	std::vector<MCpoint*> wwaa_mu;
	std::vector<MCpoint*> zzaa_mu;
	std::vector<MCpoint*> ttaa_mu;
	for(std::vector<MCpoint*>::iterator it = Points.begin();it != Points.end();it++){
		if((*it)->type < 10 ) continue;
		if((*it)->type == 10) bbaa.push_back(*it);
		if((*it)->type == 11) wwaa.push_back(*it);
		if((*it)->type == 12) zzaa.push_back(*it);
		if((*it)->type == 13) ttaa.push_back(*it);
		if((*it)->type == 20) bbaa_mu.push_back(*it);
		if((*it)->type == 21) wwaa_mu.push_back(*it);
		if((*it)->type == 22) zzaa_mu.push_back(*it);
		if((*it)->type == 23) ttaa_mu.push_back(*it);
	}
        Labledfloat integ_systs;
        suckinIntegralSystematics(integ_systs);
	for(std::vector<MCpoint*>::iterator it = bbaa.begin();it != bbaa.end();it++){
		MCpoint* points[8];
		points[0] = *it;
		int found_them_all = 1;
		for(std::vector<MCpoint*>::iterator it2 = wwaa.begin();it2 != wwaa.end();it2++){ //find the matching point in wwaa
			if ((*it2)->Mstop == (*it)->Mstop && (*it2)->Mhiggsino == (*it)->Mhiggsino ) {
				points[1] = *it2;
				found_them_all++;
				break;
			}
		}
		for(std::vector<MCpoint*>::iterator it2 = zzaa.begin();it2 != zzaa.end();it2++){ //find the matching point in zzaa
			if ((*it2)->Mstop == (*it)->Mstop && (*it2)->Mhiggsino == (*it)->Mhiggsino ) {
				points[2] = *it2;
				found_them_all++;
				break;
			}
		}
		for(std::vector<MCpoint*>::iterator it2 = zzaa.begin();it2 != zzaa.end();it2++){ //find the matching point in ttaa
			if ((*it2)->Mstop == (*it)->Mstop && (*it2)->Mhiggsino == (*it)->Mhiggsino ) {
				points[3] = *it2;
				found_them_all++;
				break;
			}
		}


		bool foundit = false;
		for(std::vector<MCpoint*>::iterator it2 = bbaa_mu.begin();it2 != bbaa_mu.end();it2++){ //find the matching point in bbaa_mu
			if ((*it2)->Mhiggsino == (*it)->Mhiggsino ) {
				points[4] = *it2;
				found_them_all++;
				foundit = true;
				break;
			}
		}
		if(!foundit) printf("can't find higgsino point for bbaa\n");
		foundit = false;
		for(std::vector<MCpoint*>::iterator it2 = wwaa_mu.begin();it2 != wwaa_mu.end();it2++){ //find the matching point in wwaa_mu
			if ((*it2)->Mhiggsino == (*it)->Mhiggsino ) {
				points[5] = *it2;
				found_them_all++;
				foundit = true;
				break;
			}
		}
		if(!foundit) printf("can't find higgsino point for wwaa\n");
		foundit = false;
		for(std::vector<MCpoint*>::iterator it2 = zzaa_mu.begin();it2 != zzaa_mu.end();it2++){ //find the matching point in zzaa_mu
			if ((*it2)->Mhiggsino == (*it)->Mhiggsino ) {
				points[6] = *it2;
				found_them_all++;
				foundit = true;
				break;
			}
		}
		if(!foundit) printf("can't find higgsino point for zzaa\n");
		foundit = false;
		for(std::vector<MCpoint*>::iterator it2 = ttaa_mu.begin();it2 != ttaa_mu.end();it2++){ //find the matching point in ttaa_mu
			if ((*it2)->Mhiggsino == (*it)->Mhiggsino ) {
				points[7] = *it2;
				found_them_all++;
				foundit = true;
				break;
			}
		}
		if(!foundit) printf("can't find higgsino point for ttaa\n");
		foundit = false;


		if (found_them_all != 8) { //make sure you found them all. 
			printf("Error! Can't find all the categories for Mst = %i Mh = %i\n",(*it)->Mstop,(*it)->Mhiggsino);
			printf("Not Generating the card files for this point!!\n");
			continue;
		}
		printf("Setup %s for st_%i_mu_%i\n",topo.Data(),(*it)->Mstop,(*it)->Mhiggsino);
		SetupSummedLimitsOneMassPoint(points, 8 ,topo,integ_systs);
	}//end for all MC points
}//SetupSummedLimitsForStrongGrid

	//To run these, you need all the returned files from the grid, includeing the JEC and BTag files.
	//for manual use only, this is pretty slow
void SetupSummedLimitsForWeakGrid(TString topo){
	std::vector<MCpoint*> Points = setupMCpoints();
	std::vector<MCpoint*> bbaa;
	std::vector<MCpoint*> wwaa;
	std::vector<MCpoint*> zzaa;
	std::vector<MCpoint*> ttaa;
	for(std::vector<MCpoint*>::iterator it = Points.begin();it != Points.end();it++){
		if((*it)->type < 20 || (*it)->type >= 30) continue;
		if((*it)->type == 20) bbaa.push_back(*it);
		if((*it)->type == 21) wwaa.push_back(*it);
		if((*it)->type == 22) zzaa.push_back(*it);
		if((*it)->type == 23) ttaa.push_back(*it);
	}
	Labledfloat integ_systs;
        suckinIntegralSystematics(integ_systs);
	for(std::vector<MCpoint*>::iterator it = bbaa.begin();it != bbaa.end();it++){
		MCpoint* points[4];
		points[0] = *it;
		int found_them_all = 1;
		for(std::vector<MCpoint*>::iterator it2 = wwaa.begin();it2 != wwaa.end();it2++){ //find the matching point in wwaa
			if ( (*it2)->Mhiggsino == (*it)->Mhiggsino ) {
				points[1] = *it2;
				found_them_all++;
				break;
			}
		}
		for(std::vector<MCpoint*>::iterator it2 = zzaa.begin();it2 != zzaa.end();it2++){ //find the matching point in zzaa
			if ( (*it2)->Mhiggsino == (*it)->Mhiggsino ) {
				points[2] = *it2;
				found_them_all++;
				break;
			}
		}
		for(std::vector<MCpoint*>::iterator it2 = zzaa.begin();it2 != zzaa.end();it2++){ //find the matching point in ttaa
			if ( (*it2)->Mhiggsino == (*it)->Mhiggsino ) {
				points[3] = *it2;
				found_them_all++;
				break;
			}
		}
		if (found_them_all != 4) { //make sure you found them all.
			printf("Error! Can't find all the categories for Mst = %i Mh = %i\n",(*it)->Mstop,(*it)->Mhiggsino);
			printf("Not Generating the card files for this point!!\n");
			continue;
		}
		printf("Setup %s for mu_%i\n",topo.Data(),(*it)->Mhiggsino);
		SetupSummedLimitsOneMassPoint(points, 4 ,topo,integ_systs);
	}//end for all MC points
}//SetupSummedLimitsForWeakGrid

//void SetupSummedLimitsOneMassPoint(MCpoint* points[], int nMCpoints,TString topo){
void SetupSummedLimitsOneMassPoint(MCpoint* points[], int nMCpoints,TString topo, Labeledfloat & integ_systs){ 
	string data = "Data";
	bool metonly = true;
	MCpoint * datapoint = setupMCpoint(data, "");//this is efficient.

	TFile* files[nMCpoints][6];
	for (int i =0; i<nMCpoints; i++) {
		files[i][0] = new TFile(datapoint->plotsAndBackground_mc.c_str());
		files[i][1] = new TFile(points[i]->plotsAndBackground_mc.c_str());
		files[i][2] = new TFile(TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECUp").Data());
		files[i][3] = new TFile(TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECDown").Data());
		files[i][4] = new TFile(TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffUp").Data());
		files[i][5] = new TFile(TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffDown").Data());

		if( !( fileExists(datapoint->plotsAndBackground_mc.c_str()) &&
			  fileExists(points[i]->plotsAndBackground_mc.c_str()) &&
			  fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECUp").Data()) &&
			  fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECDown").Data()) &&
			  fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffUp").Data()) &&
			  fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffDown").Data()) )){
			printf("ERROR!! Some of the input files are missing completely!\n");
			if (!fileExists(datapoint->plotsAndBackground_mc.c_str()) ) printf("%s is missing.\n",datapoint->plotsAndBackground_mc.c_str() );
			if (!fileExists(points[i]->plotsAndBackground_mc.c_str()) ) printf("%s is missing.\n",points[i]->plotsAndBackground_mc.c_str());
			if (!fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECUp").Data()) ) printf("%s is missing.\n",TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECUp").Data() );
			if (!fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECDown").Data()) ) printf("%s is missing.\n",TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECDown").Data() );
			if (!fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffUp").Data()) ) printf("%s is missing.\n",TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffUp").Data() );
			if (!fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffDown").Data()) ) printf("%s is missing.\n",TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffDown").Data() );
			printf("Exiting SetupLimits!! (From SetupSummedLimitsOneMassPoint) \n");
			return;
		}
	}
	
	if(topo.CompareTo("bbin3")==0){
		for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
			TString kinvar = s_KinemVars_limit[kKinVar];
			if(metonly && kinvar.CompareTo("MET") != 0) continue;
			TString channels[3] = {"2JbML!Gbar2Mbb", "2JbML!Gbar2Mbb!","3JbMLLGbar2"};
                        float f_integ_systs[3];
                        f_integ_systs[0]=integ_systs["2JbML!Gbar2Mbb"];
                        f_integ_systs[1]=integ_systs["2JbML!Gbar2Mbb!"];
                        f_integ_systs[2]=integ_systs["3JbMLLGbar2"];
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,3, s_KinemVars_limit[kKinVar],"bbin3",f_integ_systs);
		}
	}
	else if(topo.CompareTo("bbin3MM")==0){
		TString channels[3];
		channels[0] = "2JbMM!Gbar2Mbb";
		channels[1] = "2JbMM!Gbar2Mbb!";
		channels[2] = "3JbMMLGbar2";
                        float f_integ_systs[3];
                        f_integ_systs[0]=integ_systs["2JbMM!Gbar2Mbb"];
                        f_integ_systs[1]=integ_systs["2JbMM!Gbar2Mbb!"];
                        f_integ_systs[2]=integ_systs["3JbMMLGbar2"];

		for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
			TString kinvar = s_KinemVars_limit[kKinVar];
			if(metonly && kinvar.CompareTo("MET") != 0) continue;
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,3, s_KinemVars_limit[kKinVar],"bbin3MM",f_integ_systs);
		}
	}
	else if(topo.CompareTo("EHbin3")==0){
		TString channels[3];
		channels[0] = "2JbML!gbar2Mbb01lep";
		channels[1] = "2JbT!gbar2ProbeMJJ";
		channels[2] = "0lep25Jb01MewkMllgbar2";
                        float f_integ_systs[3];
                        f_integ_systs[0]=integ_systs["2JbML!gbar2Mbb01lep"];
                        f_integ_systs[1]=integ_systs["2JbT!gbar2ProbeMJJ"];
                        f_integ_systs[2]=integ_systs["0lep25Jb01MewkMllgbar2"];

		for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
			TString kinvar = s_KinemVars_limit[kKinVar];
			if(metonly && kinvar.CompareTo("MET") != 0) continue;
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,3, s_KinemVars_limit[kKinVar],"EHbin3",f_integ_systs);
		}
	}
	else if(topo.CompareTo("bbin3MLbest")==0){
		TString channels[3];
		channels[0] = "2JbML!gbar2bestOn";
		channels[1] = "2JbML!gbar2bestOff";
		channels[2] = "3JbMLLGbar2";
                        float f_integ_systs[3];
                        f_integ_systs[0]=integ_systs["2JbML!gbar2bestOn"];
                        f_integ_systs[1]=integ_systs["2JbML!gbar2bestOff"];
                        f_integ_systs[2]=integ_systs["3JbMLLGbar2"];

		for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
			TString kinvar = s_KinemVars_limit[kKinVar];
			if(metonly && kinvar.CompareTo("MET") != 0) continue;
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,3, s_KinemVars_limit[kKinVar],"bbin3MLbest",f_integ_systs);
		}
	}
	else if(topo.CompareTo("bbin3MMbest")==0){
		TString channels[3];
		channels[0] = "2JbMM!gbar2bestOn";
		channels[1] = "2JbMM!gbar2bestOff";
		channels[2] = "3JbMMLGbar2";
                        float f_integ_systs[3];
                        f_integ_systs[0]=integ_systs["2JbMM!gbar2bestOn"];
                        f_integ_systs[1]=integ_systs["2JbMM!gbar2bestOff"];
                        f_integ_systs[2]=integ_systs["3JbMMLGbar2"];

		for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
			TString kinvar = s_KinemVars_limit[kKinVar];
			if(metonly && kinvar.CompareTo("MET") != 0) continue;
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,3, s_KinemVars_limit[kKinVar],"bbin3MMbest",f_integ_systs);
		}
	}
	else if(topo.CompareTo("WHbins")==0){
		TString channels[2];
		channels[0] = "1!lepgbar2";
		channels[1] = "23Jb01MewkMll0lepgbar2";
                        float f_integ_systs[2];
                        f_integ_systs[0]=integ_systs["1!lepgbar2"];
                        f_integ_systs[1]=integ_systs["23Jb01MewkMll0lepgbar2"];

		for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
			TString kinvar = s_KinemVars_limit[kKinVar];
			if(metonly && kinvar.CompareTo("MET") != 0) continue;
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,2, s_KinemVars_limit[kKinVar],"WHbins",f_integ_systs);
		}
	}
	else if(topo.CompareTo("ZHbins")==0){
		TString channels[2];
		channels[0] = "2!lepZgbar2";
		channels[1] = "23Jb01MewkMll0lepgbar2";
                        float f_integ_systs[2];
                        f_integ_systs[0]=integ_systs["2!lepZgbar2"];
                        f_integ_systs[1]=integ_systs["23Jb01MewkMll0lepgbar2"];

		for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
			TString kinvar = s_KinemVars_limit[kKinVar];
			if(metonly && kinvar.CompareTo("MET") != 0) continue;
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,2, s_KinemVars_limit[kKinVar],"ZHbins",f_integ_systs);
		}
	}
	else if(topo.CompareTo("WWbins")==0){
		TString channels[4];
		channels[0] = "2lepgbar2";
		channels[1] = "1!lep23Jb01M!ewkMllgbar2";
		channels[2] = "1!lep23Jb01MewkMllgbar2";
		channels[3] = "0lep25Jb01MewkMllgbar2";
                        float f_integ_systs[4];
                        f_integ_systs[0]=integ_systs["2lepgbar2"];
                        f_integ_systs[1]=integ_systs["1!lep23Jb01M!ewkMllgbar2"];
                        f_integ_systs[2]=integ_systs["1!lep23Jb01MewkMllgbar2"];
                        f_integ_systs[3]=integ_systs["0lep25Jb01MewkMllgbar2"];

		for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
			TString kinvar = s_KinemVars_limit[kKinVar];
			if(metonly && kinvar.CompareTo("MET") != 0) continue;
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,4, s_KinemVars_limit[kKinVar],"WWbins",f_integ_systs);
		}
	}
	else if(topo.CompareTo("ZZbins")==0){
		TString channels[5];
		channels[0] = "3lepgbar2";
		channels[1] = "2!lepZgbar2";
		channels[2] = "1!lep23Jb01M!ewkMllgbar2";
		channels[3] = "1!lep23Jb01MewkMllgbar2";
		channels[4] = "0lep25Jb01MewkMllgbar2";
                        float f_integ_systs[5];
                        f_integ_systs[0]=integ_systs["3lepgbar2"];
                        f_integ_systs[1]=integ_systs["2!lepZgbar2"];
                        f_integ_systs[2]=integ_systs["1!lep23Jb01M!ewkMllgbar2"];
                        f_integ_systs[3]=integ_systs["1!lep23Jb01MewkMllgbar2"];
                        f_integ_systs[4]=integ_systs["0lep25Jb01MewkMllgbar2"];
		for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
			TString kinvar = s_KinemVars_limit[kKinVar];
			if(metonly && kinvar.CompareTo("MET") != 0) continue;
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,5, s_KinemVars_limit[kKinVar],"ZZbins",f_integ_systs);
		}
	}
	else if(topo.CompareTo("SHbins")==0){
		TString channels[6];
		channels[0] = "2JbM2lepgbar2";
		channels[1] = "2JbML!1lepgbar2";
		channels[2] = "2JbML!gbar2bestOn0lep";
		channels[3] = "4JbML!gbar2ewkMllbestOff0lep";
		channels[4] = "2JbML!gbar2bothOff0lep";
		channels[5] = "3JbMLLGbar2";
                        float f_integ_systs[6];
                        f_integ_systs[0]=integ_systs["2JbM2lepgbar2"];
                        f_integ_systs[1]=integ_systs["2JbML!1lepgbar2"];
                        f_integ_systs[2]=integ_systs["2JbML!gbar2bestOn0lep"];
                        f_integ_systs[3]=integ_systs["4JbML!gbar2ewkMllbestOff0lep"];
                        f_integ_systs[4]=integ_systs["2JbML!gbar2bothOff0lep"];
                        f_integ_systs[5]=integ_systs["3JbMLLGbar2"];

		for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
			TString kinvar = s_KinemVars_limit[kKinVar];
			if(metonly && kinvar.CompareTo("MET") != 0) continue;
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,6, s_KinemVars_limit[kKinVar],"SHbins",f_integ_systs);
		}
	}
	else{
		for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
			TString kinvar = s_KinemVars_limit[kKinVar];
			if(metonly && kinvar.CompareTo("MET") != 0) continue;
			SetupSummedLimitsOnePlot(files, points, nMCpoints,topo, s_KinemVars_limit[kKinVar],integ_systs);
		}
	}
		//close the files.
	for (int i =0; i<nMCpoints; i++) {
		for (int j =0; j<6; j++) {
		files[i][j]->Close();
		}
	}
}//SetupSummedLimitsOneMassPoint

//void SetupSummedLimitsOneMassPoint(MCpoint* points[], int nMCpoints){
void SetupSummedLimitsOneMassPoint(MCpoint* points[], int nMCpoints, Labeledfloat & integ_systs){
		//this does every topo, every kinvar for a mass point. this should be an order of magnitude faster.
		//it only opens the files once per mass point. 

	string data = "Data";
	bool metonly = true;
	MCpoint * datapoint = setupMCpoint(data, "");//this is efficient.

	TFile* files[nMCpoints][6];
	for (int i =0; i<nMCpoints; i++) {
		files[i][0] = new TFile(datapoint->plotsAndBackground_mc.c_str());
		files[i][1] = new TFile(points[i]->plotsAndBackground_mc.c_str());
		files[i][2] = new TFile(TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECUp").Data());
		files[i][3] = new TFile(TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECDown").Data());
		files[i][4] = new TFile(TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffUp").Data());
		files[i][5] = new TFile(TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffDown").Data());

		if( !( fileExists(datapoint->plotsAndBackground_mc.c_str()) &&
			  fileExists(points[i]->plotsAndBackground_mc.c_str()) &&
			  fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECUp").Data()) &&
			  fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECDown").Data()) &&
			  fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffUp").Data()) &&
			  fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffDown").Data()) )){
			printf("ERROR!! Some of the input files are missing completely!\n");
			if (!fileExists(datapoint->plotsAndBackground_mc.c_str()) ) printf("%s is missing.\n",datapoint->plotsAndBackground_mc.c_str() );
			if (!fileExists(points[i]->plotsAndBackground_mc.c_str()) ) printf("%s is missing.\n",points[i]->plotsAndBackground_mc.c_str());
			if (!fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECUp").Data()) ) printf("%s is missing.\n",TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECUp").Data() );
			if (!fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECDown").Data()) ) printf("%s is missing.\n",TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECDown").Data() );
			if (!fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffUp").Data()) ) printf("%s is missing.\n",TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffUp").Data() );
			if (!fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffDown").Data()) ) printf("%s is missing.\n",TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffDown").Data() );
			printf("Exiting SetupLimits!! (From SetupSummedLimitsOneMassPoint) \n");
			return;
		}
	}//for every MC point

	for (int iTop = 0; iTop<nEventTopologies_limit; iTop++) {
		TString topo = s_EventTopology_limit[iTop];
		
		if(topo.CompareTo("bbin3")==0){
			TString channels[3] = {"2JbML!Gbar2Mbb", "2JbML!Gbar2Mbb!","3JbMLLGbar2"};
                        float f_integ_systs[3];
                        f_integ_systs[0]=integ_systs["2JbML!Gbar2Mbb"];
                        f_integ_systs[1]=integ_systs["2JbML!Gbar2Mbb!"];
                        f_integ_systs[2]=integ_systs["3JbMLLGbar2"];

			for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
				if(metonly && kKinVar !=0 ) continue; //just do MET
				SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,3, s_KinemVars_limit[kKinVar],"bbin3",f_integ_systs);
			}
		}
		else if(topo.CompareTo("bbin3MM")==0){
			TString channels[3];
			channels[0] = "2JbMM!Gbar2Mbb";
			channels[1] = "2JbMM!Gbar2Mbb!";
			channels[2] = "3JbMMLGbar2";
                        float f_integ_systs[3];
                        f_integ_systs[0]=integ_systs["2JbMM!Gbar2Mbb"];
                        f_integ_systs[1]=integ_systs["2JbMM!Gbar2Mbb!"];
                        f_integ_systs[2]=integ_systs["3JbMMLGbar2"];
			for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
				if(metonly && kKinVar !=0 ) continue; //just do MET
				SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,3, s_KinemVars_limit[kKinVar],"bbin3MM",f_integ_systs);
			}
		}
		else if(topo.CompareTo("EHbin3")==0){
			TString channels[3];
			channels[0] = "2JbML!gbar2Mbb01lep";
			channels[1] = "2JbT!gbar2ProbeMJJ";
			channels[2] = "0lep25Jb01MewkMllgbar2";
                        float f_integ_systs[3];
                        f_integ_systs[0]=integ_systs["2JbML!gbar2Mbb01lep"];
                        f_integ_systs[1]=integ_systs["2JbT!gbar2ProbeMJJ"];
                        f_integ_systs[2]=integ_systs["0lep25Jb01MewkMllgbar2"];
			for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
				if(metonly && kKinVar !=0 ) continue; //just do MET
				SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,3, s_KinemVars_limit[kKinVar],"EHbin3",f_integ_systs);
			}
		}
		else if(topo.CompareTo("bbin3MLbest")==0){
			TString channels[3];
			channels[0] = "2JbML!gbar2bestOn";
			channels[1] = "2JbML!gbar2bestOff";
			channels[2] = "3JbMLLGbar2";
                        float f_integ_systs[3];
                        f_integ_systs[0]=integ_systs["2JbML!gbar2bestOn"];
                        f_integ_systs[1]=integ_systs["2JbML!gbar2bestOff"];
                        f_integ_systs[2]=integ_systs["3JbMLLGbar2"];
			for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
				if(metonly && kKinVar !=0 ) continue; //just do MET
				SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,3, s_KinemVars_limit[kKinVar],"bbin3MLbest",f_integ_systs);
			}
		}
		else if(topo.CompareTo("bbin3MMbest")==0){
			TString channels[3];
			channels[0] = "2JbMM!gbar2bestOn";
			channels[1] = "2JbMM!gbar2bestOff";
			channels[2] = "3JbMMLGbar2";
                        float f_integ_systs[3];
                        f_integ_systs[0]=integ_systs["2JbMM!gbar2bestOn"];
                        f_integ_systs[1]=integ_systs["2JbMM!gbar2bestOff"];
                        f_integ_systs[2]=integ_systs["3JbMMLGbar2"];
			for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
				if(metonly && kKinVar !=0 ) continue; //just do MET
				SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,3, s_KinemVars_limit[kKinVar],"bbin3MMbest",f_integ_systs);
			}
		}
		else if(topo.CompareTo("WHbins")==0){
			TString channels[2];
			channels[0] = "1!lepgbar2";
			channels[1] = "23Jb01MewkMll0lepgbar2";
                        float f_integ_systs[2];
                        f_integ_systs[0]=integ_systs["1!lepgbar2"];
                        f_integ_systs[1]=integ_systs["23Jb01MewkMll0lepgbar2"];
			for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
				if(metonly && kKinVar !=0 ) continue; //just do MET
				SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,2, s_KinemVars_limit[kKinVar],"WHbins",f_integ_systs);
			}
		}
		else if(topo.CompareTo("ZHbins")==0){
			TString channels[2];
			channels[0] = "2!lepZgbar2"; 
			channels[1] = "23Jb01MewkMll0lepgbar2";
                        float f_integ_systs[2];
                        f_integ_systs[0]=integ_systs["2!lepZgbar2"];
                        f_integ_systs[1]=integ_systs["23Jb01MewkMll0lepgbar2"];
			for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
				if(metonly && kKinVar !=0 ) continue; //just do MET
				SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,2, s_KinemVars_limit[kKinVar],"ZHbins",f_integ_systs);
			}
		}
		else if(topo.CompareTo("WWbins")==0){
			TString channels[4];
			channels[0] = "2lepgbar2";
			channels[1] = "1!lep23Jb01M!ewkMllgbar2";
			channels[2] = "1!lep23Jb01MewkMllgbar2";
			channels[3] = "0lep25Jb01MewkMllgbar2";
                        float f_integ_systs[4];
                        f_integ_systs[0]=integ_systs["2lepgbar2"];
                        f_integ_systs[1]=integ_systs["1!lep23Jb01M!ewkMllgbar2"];
                        f_integ_systs[2]=integ_systs["1!lep23Jb01MewkMllgbar2"];
                        f_integ_systs[3]=integ_systs["0lep25Jb01MewkMllgbar2"];
			for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
				if(metonly && kKinVar !=0 ) continue; //just do MET
				SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,4, s_KinemVars_limit[kKinVar],"WWbins",f_integ_systs);
			}
		}
		else if(topo.CompareTo("ZZbins")==0){
			TString channels[5];
			channels[0] = "3lepgbar2";
			channels[1] = "2!lepZgbar2";
			channels[2] = "1!lep23Jb01M!ewkMllgbar2";
			channels[3] = "1!lep23Jb01MewkMllgbar2";
			channels[4] = "0lep25Jb01MewkMllgbar2";
                        float f_integ_systs[5];
                        f_integ_systs[0]=integ_systs["3lepgbar2"];
                        f_integ_systs[1]=integ_systs["2!lepZgbar2"];
                        f_integ_systs[2]=integ_systs["1!lep23Jb01M!ewkMllgbar2"];
                        f_integ_systs[3]=integ_systs["1!lep23Jb01MewkMllgbar2"];
                        f_integ_systs[4]=integ_systs["0lep25Jb01MewkMllgbar2"];
			for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
				if(metonly && kKinVar !=0 ) continue; //just do MET
				SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,5, s_KinemVars_limit[kKinVar],"ZZbins",f_integ_systs);
			}
		}
		else if(topo.CompareTo("SHbins")==0){
			TString channels[6];
			channels[0] = "2JbM2lepgbar2";
			channels[1] = "2JbML!1lepgbar2";
			channels[2] = "2JbML!gbar2bestOn0lep";
			channels[3] = "4JbML!gbar2ewkMllbestOff0lep";
			channels[4] = "2JbML!gbar2bothOff0lep";
			channels[5] = "3JbMLLGbar2";
                        float f_integ_systs[6];
                        f_integ_systs[0]=integ_systs["2JbM2lepgbar2"];
                        f_integ_systs[1]=integ_systs["2JbML!1lepgbar2"];
                        f_integ_systs[2]=integ_systs["2JbML!gbar2bestOn0lep"];
                        f_integ_systs[3]=integ_systs["4JbML!gbar2ewkMllbestOff0lep"];
                        f_integ_systs[4]=integ_systs["2JbML!gbar2bothOff0lep"];
                        f_integ_systs[5]=integ_systs["3JbMLLGbar2"];
			for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
				if(metonly && kKinVar !=0 ) continue; //just do MET
				SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,6, s_KinemVars_limit[kKinVar],"SHbins",f_integ_systs);
			}
		}
		else{
			for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
				if(metonly && kKinVar !=0 ) continue; //just do MET
				SetupSummedLimitsOnePlot(files, points, nMCpoints,topo, s_KinemVars_limit[kKinVar],integ_systs);
			}
		}
	}//end for every topo.
	
		//close the files.
	printf("start closing\n");
	for (int i =0; i<nMCpoints; i++) {
		for (int j =0; j<6; j++) {
			files[i][j]->Close();
		}
	}
	printf("fin closing\n");
}//SetupSummedLimitsOneMassPoint



void SetupSummedLimitsOnePlot(TString mcpoint_pefix, TString topo, TString kinvar){
	//usage:  SetupSummedLimitsOnePlot("st_300_mu_290","bbin3","MET")

	std::vector<MCpoint*> Points = setupMCpoints();

	string data = "Data";
        MCpoint * datapoint = setupMCpoint(data, "");//this is efficient.

	const int nMCpoints = 8;
	MCpoint* points[nMCpoints];
        points[0] = setupMCpoint((mcpoint_pefix+"_bbaa").Data(), "");
        points[1] = setupMCpoint((mcpoint_pefix+"_wwaa").Data(), "");
        points[2] = setupMCpoint((mcpoint_pefix+"_zzaa").Data(), "");
        points[3] = setupMCpoint((mcpoint_pefix+"_ttaa").Data(), "");

	int found_them_all = 0;
	for(std::vector<MCpoint*>::iterator it2 = Points.begin(); it2 != Points.end();it2++){ //find the matching point in wwaa
		if ((*it2)->type == points[0]->type + 10 && (*it2)->Mhiggsino == (points[0])->Mhiggsino ) {
			//if type is the same and Mhiggsino is hte same, 
			points[4] = *it2;
			found_them_all++;
		}
		if ((*it2)->type == points[1]->type + 10 && (*it2)->Mhiggsino == (points[1])->Mhiggsino ) {
			//if type is the same and Mhiggsino is hte same, 
			points[5] = *it2;
			found_them_all++;
		}
		if ((*it2)->type == points[2]->type + 10 && (*it2)->Mhiggsino == (points[2])->Mhiggsino ) {
			//if type is the same and Mhiggsino is hte same, 
			points[6] = *it2;
			found_them_all++;
		}
		if ((*it2)->type == points[3]->type + 10 && (*it2)->Mhiggsino == (points[3])->Mhiggsino ) {
			//if type is the same and Mhiggsino is hte same, 
			points[7] = *it2;
			found_them_all++;
		}
	}//look for the compliments
	if(found_them_all != 4){
		printf("ERROR! I didn't find all the higgsino MC points!!\n");
		return;
	}

	//setup and load in the integral syst's
        Labledfloat integ_systs;
        suckinIntegralSystematics(integ_systs);


	TFile* files[nMCpoints][6];
	for (int i =0; i<nMCpoints; i++) {
		files[i][0] = new TFile(datapoint->plotsAndBackground_mc.c_str());
		files[i][1] = new TFile(points[i]->plotsAndBackground_mc.c_str());
		files[i][2] = new TFile(TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECUp").Data());
		files[i][3] = new TFile(TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECDown").Data());
		files[i][4] = new TFile(TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffUp").Data());
		files[i][5] = new TFile(TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffDown").Data());

		if( !( fileExists(datapoint->plotsAndBackground_mc.c_str()) &&
					fileExists(points[i]->plotsAndBackground_mc.c_str()) &&
					fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECUp").Data()) &&
					fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECDown").Data()) &&
					fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffUp").Data()) &&
					fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffDown").Data()) )){
			printf("ERROR!! Some of the input files are missing completely!\n");
			if (!fileExists(datapoint->plotsAndBackground_mc.c_str()) ) printf("%s is missing.\n",datapoint->plotsAndBackground_mc.c_str() );
			if (!fileExists(points[i]->plotsAndBackground_mc.c_str()) ) printf("%s is missing.\n",points[i]->plotsAndBackground_mc.c_str());
			if (!fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECUp").Data()) ) printf("%s is missing.\n",TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECUp").Data() );
			if (!fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECDown").Data()) ) printf("%s is missing.\n",TackBeforeRoot(points[i]->plotsAndBackground_mc,"JECDown").Data() );
			if (!fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffUp").Data()) ) printf("%s is missing.\n",TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffUp").Data() );
			if (!fileExists(TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffDown").Data()) ) printf("%s is missing.\n",TackBeforeRoot(points[i]->plotsAndBackground_mc,"BtagEffDown").Data() );
			printf("Exiting SetupLimits!! (From SetupSummedLimitsOneMassPoint) \n");
			//return;
		}
	}//for every MC point

	//things I need here: 
	//files, points, nMCpoints, 

                if(topo.CompareTo("bbin3")==0){
                        TString channels[3] = {"2JbML!Gbar2Mbb", "2JbML!Gbar2Mbb!","3JbMLLGbar2"};
                        float f_integ_systs[3];
                        f_integ_systs[0]=integ_systs["2JbML!Gbar2Mbb"];
                        f_integ_systs[1]=integ_systs["2JbML!Gbar2Mbb!"];
                        f_integ_systs[2]=integ_systs["3JbMLLGbar2"];

			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,3, kinvar,"bbin3",f_integ_systs);
                }
                else if(topo.CompareTo("bbin3MM")==0){
                        TString channels[3];
                        channels[0] = "2JbMM!Gbar2Mbb";
                        channels[1] = "2JbMM!Gbar2Mbb!";
                        channels[2] = "3JbMMLGbar2";
                        float f_integ_systs[3];
                        f_integ_systs[0]=integ_systs["2JbMM!Gbar2Mbb"];
                        f_integ_systs[1]=integ_systs["2JbMM!Gbar2Mbb!"];
                        f_integ_systs[2]=integ_systs["3JbMMLGbar2"];
                                
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,3, kinvar,"bbin3MM",f_integ_systs);
                }
                else if(topo.CompareTo("EHbin3")==0){
                        TString channels[3];
                        channels[0] = "2JbML!gbar2Mbb01lep";
                        channels[1] = "2JbT!gbar2ProbeMJJ";
                        channels[2] = "0lep25Jb01MewkMllgbar2";
                        float f_integ_systs[3];
                        f_integ_systs[0]=integ_systs["2JbML!gbar2Mbb01lep"];
                        f_integ_systs[1]=integ_systs["2JbT!gbar2ProbeMJJ"];
                        f_integ_systs[2]=integ_systs["0lep25Jb01MewkMllgbar2"];
                                
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,3, kinvar,"EHbin3",f_integ_systs);
                }
                else if(topo.CompareTo("bbin3MLbest")==0){
                        TString channels[3];
                        channels[0] = "2JbML!gbar2bestOn";
                        channels[1] = "2JbML!gbar2bestOff";
                        channels[2] = "3JbMLLGbar2";
                        float f_integ_systs[3];
                        f_integ_systs[0]=integ_systs["2JbML!gbar2bestOn"];
                        f_integ_systs[1]=integ_systs["2JbML!gbar2bestOff"];
                        f_integ_systs[2]=integ_systs["3JbMLLGbar2"];
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,3, kinvar ,"bbin3MLbest",f_integ_systs);
                }
                else if(topo.CompareTo("bbin3MMbest")==0){
                        TString channels[3];
                        channels[0] = "2JbMM!gbar2bestOn";
                        channels[1] = "2JbMM!gbar2bestOff";
                        channels[2] = "3JbMMLGbar2";
                        float f_integ_systs[3];
                        f_integ_systs[0]=integ_systs["2JbMM!gbar2bestOn"];
                        f_integ_systs[1]=integ_systs["2JbMM!gbar2bestOff"];
                        f_integ_systs[2]=integ_systs["3JbMMLGbar2"];
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,3, kinvar,"bbin3MMbest",f_integ_systs);
                }
                else if(topo.CompareTo("WHbins")==0){
                        TString channels[2];
                        channels[0] = "1!lepgbar2";
                        channels[1] = "23Jb01MewkMll0lepgbar2";
                        float f_integ_systs[2];
                        f_integ_systs[0]=integ_systs["1!lepgbar2"];
                        f_integ_systs[1]=integ_systs["23Jb01MewkMll0lepgbar2"];
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,2, kinvar ,"WHbins",f_integ_systs);
                }
                else if(topo.CompareTo("ZHbins")==0){
                        TString channels[2];
                        channels[0] = "2!lepZgbar2";
                        channels[1] = "23Jb01MewkMll0lepgbar2";
                        float f_integ_systs[2];
                        f_integ_systs[0]=integ_systs["2!lepZgbar2"];
                        f_integ_systs[1]=integ_systs["23Jb01MewkMll0lepgbar2"];
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,2, kinvar ,"ZHbins",f_integ_systs);
                }
                else if(topo.CompareTo("WWbins")==0){
                        TString channels[4];
                        channels[0] = "2lepgbar2";
                        channels[1] = "1!lep23Jb01M!ewkMllgbar2";
                        channels[2] = "1!lep23Jb01MewkMllgbar2";
                        channels[3] = "0lep25Jb01MewkMllgbar2";
                        float f_integ_systs[4];
                        f_integ_systs[0]=integ_systs["2lepgbar2"];
                        f_integ_systs[1]=integ_systs["1!lep23Jb01M!ewkMllgbar2"];
                        f_integ_systs[2]=integ_systs["1!lep23Jb01MewkMllgbar2"];
                        f_integ_systs[3]=integ_systs["0lep25Jb01MewkMllgbar2"];
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,4, kinvar,"WWbins",f_integ_systs);
                }
                else if(topo.CompareTo("ZZbins")==0){
                        TString channels[5];
                        channels[0] = "3lepgbar2";
                        channels[1] = "2!lepZgbar2";
                        channels[2] = "1!lep23Jb01M!ewkMllgbar2";
                        channels[3] = "1!lep23Jb01MewkMllgbar2";
                        channels[4] = "0lep25Jb01MewkMllgbar2";
                        float f_integ_systs[5];
                        f_integ_systs[0]=integ_systs["3lepgbar2"];
                        f_integ_systs[1]=integ_systs["2!lepZgbar2"];
                        f_integ_systs[2]=integ_systs["1!lep23Jb01M!ewkMllgbar2"];
                        f_integ_systs[3]=integ_systs["1!lep23Jb01MewkMllgbar2"];
                        f_integ_systs[4]=integ_systs["0lep25Jb01MewkMllgbar2"];
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,5, kinvar,"ZZbins",f_integ_systs);
                }
                else if(topo.CompareTo("SHbins")==0){
                        TString channels[6];
                        channels[0] = "2JbM2lepgbar2";
                        channels[1] = "2JbML!1lepgbar2";
                        channels[2] = "2JbML!gbar2bestOn0lep";
                        channels[3] = "4JbML!gbar2ewkMllbestOff0lep";
                        channels[4] = "2JbML!gbar2bothOff0lep";
                        channels[5] = "3JbMLLGbar2";
                        float f_integ_systs[6];
                        f_integ_systs[0]=integ_systs["2JbM2lepgbar2"];
                        f_integ_systs[1]=integ_systs["2JbML!1lepgbar2"];
                        f_integ_systs[2]=integ_systs["2JbML!gbar2bestOn0lep"];
                        f_integ_systs[3]=integ_systs["4JbML!gbar2ewkMllbestOff0lep"];
                        f_integ_systs[4]=integ_systs["2JbML!gbar2bothOff0lep"];
                        f_integ_systs[5]=integ_systs["3JbMLLGbar2"];
			SetupSummedLimitsOnePlot_bbin(files, points, nMCpoints,channels,6, kinvar,"SHbins",f_integ_systs);
                }
                else{
			SetupSummedLimitsOnePlot(files, points, nMCpoints,topo, kinvar,integ_systs);
                }
}//end SetupSummedLimitsOnePlot


//void SetupSummedLimitsOnePlot(TFile* files[][6],MCpoint* points[], int nMCpoints,TString topo, TString kinvar){
void SetupSummedLimitsOnePlot(TFile* files[][6],MCpoint* points[], int nMCpoints,TString topo, TString kinvar, Labeledfloat & integ_systs){
	string data = "Data";
	TH1F* CardHistSet[7];
	TH1F* CardHistSets[nMCpoints][7];

	string basename = string("h")+kinvar.Data()+topo.Data()+"_";
	bool got_them_all = true;
	for (int i =0; i<nMCpoints; i++) {
		got_them_all &= loadhistSafely(& CardHistSets[i][0], files[i][0], basename,data,1);
		got_them_all &= loadhistSafely(& CardHistSets[i][1], files[i][0], basename,"Bkg",3);
		got_them_all &= loadhistSafely(& CardHistSets[i][2], files[i][1], basename,"MC",1);
		got_them_all &= loadhistSafely(& CardHistSets[i][3], files[i][2], basename,"JECUp",1);
		got_them_all &= loadhistSafely(& CardHistSets[i][4], files[i][3], basename,"JECDown",1);
		got_them_all &= loadhistSafely(& CardHistSets[i][5], files[i][4], basename,"BtagEffUp",1);
		got_them_all &= loadhistSafely(& CardHistSets[i][6], files[i][5], basename,"BtagEffDown",1);
	}
	if (!got_them_all) {
		cout<<endl<<"MAJOR ERROR!! Could not find histograms for topo "<<topo<<" kinvar "<<kinvar<<endl;
		cout<<"    Check consistency among the params files. "<<endl;
		cout<<"    Continuing without it!!"<<endl<<endl;
		return;
	}
		//Scale the MC hists and add them all up. 
	for(short j=2;j<=6;j++){ //2-6 are the MC hists.
		for (int i =0; i<nMCpoints; i++) {
			CardHistSets[i][j]->Scale(points[i]->lumiscalefactor(Integrated_Luminosity_Data));
		}
		CardHistSet[j]=CardHistSets[0][j];
		for (int i =1; i<nMCpoints; i++) {
			CardHistSet[j]->Add(CardHistSets[i][j]);
		}
	}
	CardHistSet[0]=CardHistSets[0][0];//transfer data simply
	CardHistSet[1]=CardHistSets[0][1];//transfer data simply

	makeLimitSettingMachinery(CardHistSet, points[0], basename, topo, integ_systs[topo.Data()], kinvar, true);
}//SetupSummedLimitsOnePlot

//void SetupSummedLimitsOnePlot_bbin(TFile* files[][6],MCpoint* points[], int nMCpoints, TString channels[],short nchannels, TString kinvar, TString CombinedTopoName){
void SetupSummedLimitsOnePlot_bbin(TFile* files[][6],MCpoint* points[], int nMCpoints, TString channels[],short nchannels, TString kinvar, TString CombinedTopoName,float f_integ_systs[]){
	string data = "Data";
	TH1F* CardHistSet[nchannels][7];
	TH1F* CardHistSets[nMCpoints][nchannels][7];

	for (int k=0; k<nchannels; k++) {
		string basename = string("h")+kinvar.Data()+channels[k].Data()+"_";
		bool got_them_all = true;
		for (int i =0; i<nMCpoints; i++) {
			got_them_all &= loadhistSafely(& CardHistSets[i][k][0], files[i][0], basename,data,1);
			got_them_all &= loadhistSafely(& CardHistSets[i][k][1], files[i][0], basename,"Bkg",3);
			got_them_all &= loadhistSafely(& CardHistSets[i][k][2], files[i][1], basename,"MC",1);
			got_them_all &= loadhistSafely(& CardHistSets[i][k][3], files[i][2], basename,"JECUp",1);
			got_them_all &= loadhistSafely(& CardHistSets[i][k][4], files[i][3], basename,"JECDown",1);
			got_them_all &= loadhistSafely(& CardHistSets[i][k][5], files[i][4], basename,"BtagEffUp",1);
			got_them_all &= loadhistSafely(& CardHistSets[i][k][6], files[i][5], basename,"BtagEffDown",1);
		}
		if (!got_them_all) {
			cout<<endl<<"MAJOR ERROR!! Could not find histograms for topo "<<channels[k].Data()<<" kinvar "<<kinvar<<endl;
			cout<<"    Check consistency among the params files. "<<endl;
			cout<<"    Continuing without it!!"<<endl<<endl;
			return;
		}
	}
		//Scale the MC hists and add them all up.
	for(short j=2;j<=6;j++){ //2-6 are the MC hists.
		for (short k=0; k<nchannels; k++) {
			for (int i =0; i<nMCpoints; i++) {
				CardHistSets[i][k][j]->Scale(points[i]->lumiscalefactor(Integrated_Luminosity_Data));
			}
			CardHistSet[k][j]=CardHistSets[0][k][j];
			for (int i =1; i<nMCpoints; i++) {
				CardHistSet[k][j]->Add(CardHistSets[i][k][j]);
			}
		}
	}
	for (short k=0; k<nchannels; k++) {
		CardHistSet[k][0]=CardHistSets[0][k][0];//transfer data simply
		CardHistSet[k][1]=CardHistSets[0][k][1];//transfer data simply
	}

	makeLimitSettingMachinery_bbinN(nchannels, CardHistSet, points[0], channels, CombinedTopoName,f_integ_systs, kinvar, true);
}//SetupSummedLimitsOnePlot_bbin

void suckinIntegralSystematics( Labeledfloat & integ_systs){
        std::ifstream infile(integSyst_data_lim.c_str());
        std::string line;
        while (std::getline(infile, line)) {
                std::istringstream iss(line);
                string name;
                string s_integ_syst;
		
                if (!(iss >> name >> s_integ_syst) ) { break; }
		TString ts_integ_syst = s_integ_syst;
                integ_systs[name]=ts_integ_syst.Atof();
        }//end for every line
	infile.close();
	printf("sucked in integSyst_data_lim\n");
	printf("found integ syst for 2JbMLgbar2: %f\n",integ_systs["2JbMLgbar2"]);
	printf("found integ syst for 2JbML!Gbar2Mbb: %f\n",integ_systs["2JbML!Gbar2Mbb"]);
} // end suckinIntegralSystematics

void SetupAllToys(string topo, string kinvar, int n_r_guesses, int ntoys, int fork){
//void SetupAllToys(string topo, string kinvar, int n_r_guesses=30, int ntoys = 3000, int fork = 8){
                //Fetch all Asymptotic data:

	//of course, this assumes that the Asymptotici structure has already made the limit packages 
	//and combined them into something called bbaa that is really the four stop channels plus the four electrohiggs channels. 
	cout<<"star setup toys"<<endl;
	Label3Lim* allLims = new Label3Lim();
        suckinallfiles(10, allLims); //this segfaults. 

	int seed = 1;
        std::vector<MCpoint*> points = setupMCpoints();
        for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
                if((*it)->gettype() != 10) continue;
//              if ((*it)->Mstop > 510) continue;
                if (!checkin(allLims,(*it)->pointName, topo, kinvar)) continue;
                limit *thislim = (*allLims)[(*it)->pointName][kinvar.data()][topo.data()];

		//you then calculate a search region. 
		float r_min = thislim->Expected2_5;
		float r_max = thislim->Expected97_5; //check that you got the order right. 
		float diff = r_max - r_min;
		//make sure the observed isn't close to the boundary
		if(thislim->Observed < r_min + 0.2*diff) r_min = thislim->Observed - 0.2*diff;
		if(thislim->Observed > r_max - 0.2*diff) r_max = thislim->Observed + 0.2*diff;
		
	
		//construct names for the bashfilename and collection_file
		string bashfilename = Form("doToys_%s_%s_%s.sh",(*it)->pointName.data(),topo.data(),kinvar.data());
		string collection_file = Form("toyslog_%s_%s_%s.txt",(*it)->pointName.data(),topo.data(),kinvar.data());
		//setup the toys
		seed = SetupToys(r_min, r_max, n_r_guesses, 
				(*it)->makeLimitCardName(topo,kinvar).Data(),
				bashfilename, collection_file, seed, ntoys, fork);
	
	}//end for every MC point
}//end SetupAllToys

int SetupToys(float r_low, float r_high, int n_r_guesses, string cardfile, string bashfilename, string collection_file, int seed_start, int ntoys, int fork){
//int SetupToys(float r_low, float r_high, int n_r_guesses, string cardfile, string bashfilename, string collection_file, int seed_start = 1, int ntoys = 3000, int fork = 8){

	//You take a range r_low to r_high of r-value guesses that you'll get from Asymptotic and split it into n_r_guesses within that range
	//n_r_guesses is typically 30-100. I like 30.
	//You then make one command that throws toys for every n_r_guesses. 
	//You put each of those commands into a bash script "bashfile" that will run the set. 
	//each command dumps it's output into a text file collection_file 

	//you can set the random seed to seed_start, which is the first random seed you use. SetupToys then increments this for every guess. 
	//SetupToys returns seed_start + n_r_guesses, which you can use as the start seed the next time you run SetupToys. 
	//So the first time you run this, use seed_start = 1, then take the retval
	//from SetupToys as your next seed. This way you continuiously increment the seed.

	//You can set the number of toys. The rutgers group is using a bunch, like 3k. 
	//The speed of the combine command is a very slowly growing function of the nubmer of toys. 
	//100 -> 3k toys only increaces the run time from 6 sec to 7 sec. 

	//fork determins how many processors you run over. I like 8 on 3day storage, but probably use 1 if you're on in a crab env. 
	if(r_high <= r_low){ 
		cout<<"Error! SetupToys recieves r_high <= r_low. r_low = "<<r_low<<" r_high = "<<r_high<<". Exiting!!"<<endl;
		return seed_start + n_r_guesses;
	}
	if(ntoys <= 0){
		cout<<"Error! SetupToys recieves ntoys <= 0! ntoys = "<<ntoys<<". Exiting!!"<<endl;
		return seed_start + n_r_guesses;
	}
	cout<<"Making stuff to run toys for card file "<<cardfile<<endl;
	float increment = (r_high - r_low)/((float) n_r_guesses);
	
	ofstream bashfile;
	bashfile.open(bashfilename.data(),ios_base::out);//open for writing
	bashfile<<"echo \"************* THROW TOYS FOR "<<cardfile<<" ************\""<<endl;
	for(int i = 0; i<n_r_guesses; i++){
		float r_guess = r_low + increment *((float)i);

		bashfile<<"echo \"************* THROW TOYS FOR r="<<r_guess<<" ************\""<<endl;
                
//                bashfile<<"combine -M HybridNew --frequentist --testStat LHC "<<cardfile<<" -H ProfileLikelihood --fork 8 >& temp"<<endl;
 		if(fork >1) bashfile<<"combine "<<cardfile<<" -M HybridNew --freq --clsAcc 0 -T "<<ntoys<<" -s "<< seed_start+i << " --singlePoint "<< r_guess <<" --saveToys --saveHybridResult --fork "<< fork <<" >& temp2"<<endl;
 		else        bashfile<<"combine "<<cardfile<<" -M HybridNew --freq --clsAcc 0 -T "<<ntoys<<" -s "<< seed_start+i << " --singlePoint "<< r_guess <<" --saveToys --saveHybridResult >& temp2"<<endl;
                bashfile<<"cat temp2 >> "<< collection_file <<endl;
                bashfile<<"rm temp2"<<endl;
	
	}
	bashfile.close();
	return seed_start + n_r_guesses;
}//end SetupToys

void HaddAndRunAll_file(string topo, string kinvar, int n_r_guesses_expected = 30){
       std::vector<MCpoint*> points = setupMCpoints();
       for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
	       if((*it)->gettype() != 10) continue;

	       string ouptutfilename  = Form("ToysCombined_%s_%s_%s.root",(*it)->pointName.data(),topo.data(),kinvar.data());
	       string collection_file = Form("toyslog_%s_%s_%s.txt",(*it)->pointName.data(),topo.data(),kinvar.data());
                //setup the toys
                //seed = SetupToys(r_min, r_max, n_r_guesses,
                                //(*it)->makeLimitCardName(topo,kinvar).Data(),
                                //bashfilename, collection_file, seed, ntoys, fork);
		
	       printf("\n\nDo Hadd for %s %s %s,   Searching through %s\n",(*it)->pointName.data(),topo.data(),kinvar.data(),collection_file.data());
	       DoHadd_file(collection_file, ouptutfilename, n_r_guesses_expected);
       }//end for every MC point.

       for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
	       if((*it)->gettype() != 10) continue;

	       string ouptutfilename  = Form("ToysCombined_%s_%s_%s.root",(*it)->pointName.data(),topo.data(),kinvar.data());
	       string collection_file = Form("toyslog_%s_%s_%s.txt",(*it)->pointName.data(),topo.data(),kinvar.data());
	       string runfilename = Form("doLimits_freq_%s_%s_%s.txt",(*it)->pointName.data(),topo.data(),kinvar.data());
	       string resultsfile = Form("LimitResult_freq_%s_%s_%s.txt",(*it)->pointName.data(),topo.data(),kinvar.data());
		
                //setup the toys
                //seed = SetupToys(r_min, r_max, n_r_guesses,
                                //(*it)->makeLimitCardName(topo,kinvar).Data(),
                                //bashfilename, collection_file, seed, ntoys, fork);
		
	       printf("Make Run Scripts for %s %s %s\n",(*it)->pointName.data(),topo.data(),kinvar.data());
	       RunOnToys(ouptutfilename, (*it)->makeLimitCardName(topo,kinvar).Data(),
			       runfilename, resultsfile);
       }//end for every MC point.
}//HaddAndRunAll

void HaddAndRunAll(string topo, string kinvar, int n_r_guesses_expected = 30){
       std::vector<MCpoint*> points = setupMCpoints();
       for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
	       if((*it)->gettype() != 10) continue;

	       string ouptutfilename  = Form("ToysCombined_%s_%s_%s.root",(*it)->pointName.data(),topo.data(),kinvar.data());
	       string collection_file = Form("toyslog_%s_%s_%s.txt",(*it)->pointName.data(),topo.data(),kinvar.data());
                //setup the toys
                //seed = SetupToys(r_min, r_max, n_r_guesses,
                                //(*it)->makeLimitCardName(topo,kinvar).Data(),
                                //bashfilename, collection_file, seed, ntoys, fork);
		
	       printf("\n\nDo Hadd for %s %s %s,   Searching through %s\n",(*it)->pointName.data(),topo.data(),kinvar.data(),collection_file.data());
	       DoHadd(collection_file, ouptutfilename, n_r_guesses_expected);
       }//end for every MC point.

       for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
	       if((*it)->gettype() != 10) continue;

	       string ouptutfilename  = Form("ToysCombined_%s_%s_%s.root",(*it)->pointName.data(),topo.data(),kinvar.data());
	       string collection_file = Form("toyslog_%s_%s_%s.txt",(*it)->pointName.data(),topo.data(),kinvar.data());
	       string runfilename = Form("doLimits_freq_%s_%s_%s.txt",(*it)->pointName.data(),topo.data(),kinvar.data());
	       string resultsfile = Form("LimitResult_freq_%s_%s_%s.txt",(*it)->pointName.data(),topo.data(),kinvar.data());
		
                //setup the toys
                //seed = SetupToys(r_min, r_max, n_r_guesses,
                                //(*it)->makeLimitCardName(topo,kinvar).Data(),
                                //bashfilename, collection_file, seed, ntoys, fork);
		
	       printf("Make Run Scripts for %s %s %s\n",(*it)->pointName.data(),topo.data(),kinvar.data());
	       RunOnToys(ouptutfilename, (*it)->makeLimitCardName(topo,kinvar).Data(),
			       runfilename, resultsfile);
       }//end for every MC point.
}//HaddAndRunAll

void DoHadd(string collection_file, string ouptutfilename, int n_r_guesses_expected){
	//Take in the results of toy throwing (the collection file made in SetupToys)
	//identify what the output files were
	//hadd them together and put the result in outputfilename
	//check that you got them all by specifying in n_r_guesses_expected the number you were expectind 

	TString haddcommand = "hadd -f -k "+ouptutfilename;
	//-f option forces it, makes the output file
	//-k makes it skip files with errors.
	
	//go along through collection_file
	ifstream infile;
        infile.open(collection_file.data(),ifstream::in);
        if(!infile.is_open()){
                printf("ERROR!: FILE NOT FOUND %s \t\t(seen by suckinfile)\n",collection_file.data());
                return; 
        }
	std::string line;
	int n_found = 0;
	while (std::getline(infile, line) && n_found < n_r_guesses_expected){
		//line format: 
		//Hybrid result saved as HypoTestResult_mh120_r0.2788_630311758 in higgsCombineTest.HybridNew.mH120.1.root
		std::istringstream iss(line);
                std::size_t found = line.find("higgsCombineTest");
                //std::size_t found2 = line.find("root");
		if (found!=std::string::npos){
			string crap1;
                        string crap2;
                        string crap3;
                        string crap4;
                        string crap5;
                        string crap6;
                        string thefilename;
                        if (!(iss >> crap1 >> crap2 >> crap3 >> crap4 >> crap5 >> crap6 >> thefilename ) ) { break; }

			//for debugging
			//cout<<crap1<<" "<<crap2<<" "<<crap3<<" "<<crap4<<" "<<crap5<<" "<<crap6<<" "<<thefilename<<endl;
			cout<<"adding "<<thefilename<<endl;

			haddcommand += " "+thefilename;

			n_found++;
		}//end if
	}//end while
	if(n_found != n_r_guesses_expected && n_r_guesses_expected >0) cout<<"Warning! I only found "<<n_found<<" files!, expected "<<n_r_guesses_expected<<endl;

	//when you're done
	cout<<"do hadd command now:"<<endl;
	system( haddcommand.Data());
}//end DoHadd
void DoHaddGlom(string collection_file, string ouptutfilename, int n_r_guesses_expected){
	//Take in the results of toy throwing (the collection file made in SetupToys)
	//identify what the output files were
	//hadd them together and put the result in outputfilename
	//check that you got them all by specifying in n_r_guesses_expected the number you were expectind 
	ofstream runfile;
	runfile.open(Form("doHaddFor_%s",ouptutfilename.data()) ,ios_base::out);

	TString haddprefix = "hadd -f -k ";
	//-f option forces it, makes the output file
	//-k makes it skip files with errors.
	TString tempfile = "tempball.root";
	
	runfile<<"rm "<<ouptutfilename<<endl;
	runfile<<"rm "<<tempfile<<endl;
	//go along through collection_file
	ifstream infile;
        infile.open(collection_file.data(),ifstream::in);
        if(!infile.is_open()){
                printf("ERROR!: FILE NOT FOUND %s \t\t(seen by suckinfile)\n",collection_file.data());
                return; 
        }
	bool first = true;
	bool second = false;
	std::string line;
	int n_found = 0;
	TString firstline;
		
	while (std::getline(infile, line) && n_found < n_r_guesses_expected){
		//line format: 
		//Hybrid result saved as HypoTestResult_mh120_r0.2788_630311758 in higgsCombineTest.HybridNew.mH120.1.root
		std::istringstream iss(line);
                std::size_t found = line.find("higgsCombineTest");
                //std::size_t found2 = line.find("root");
		if (found!=std::string::npos){
			string crap1;
                        string crap2;
                        string crap3;
                        string crap4;
                        string crap5;
                        string crap6;
                        string thefilename;
                        if (!(iss >> crap1 >> crap2 >> crap3 >> crap4 >> crap5 >> crap6 >> thefilename ) ) { break; }

			//for debugging
			//cout<<crap1<<" "<<crap2<<" "<<crap3<<" "<<crap4<<" "<<crap5<<" "<<crap6<<" "<<thefilename<<endl;
			cout<<"adding "<<thefilename<<endl;

			if(first){
				firstline = haddprefix + ouptutfilename + " "+thefilename;
				first = false;
				second = true;
			}
			else if(second){
				firstline += " "+thefilename;
				second = false;
				runfile<<firstline<<endl;
			}
			else{
				runfile<<haddprefix+tempfile+" "+ouptutfilename+" "+thefilename<<endl;
				runfile<<"mv "+tempfile+" "+ouptutfilename<<endl;
			}

			n_found++;
		}//end if
	}//end while
	if(n_found != n_r_guesses_expected && n_r_guesses_expected >0) cout<<"Warning! I only found "<<n_found<<" files!, expected "<<n_r_guesses_expected<<endl;

	runfile.close(); 
	printf("produced doHaddFor_%s\n",ouptutfilename.data());

}//end DoHaddGlom

void DoHadd_file(string collection_file, string ouptutfilename, int n_r_guesses_expected){
	//Take in the results of toy throwing (the collection file made in SetupToys)
	//identify what the output files were
	//hadd them together and put the result in outputfilename
	//check that you got them all by specifying in n_r_guesses_expected the number you were expectind 

	TString haddcommand = "hadd -f -k "+ouptutfilename;
	//-f option forces it, makes the output file
	//-k makes it skip files with errors.
	
	//go along through collection_file
	ifstream infile;
        infile.open(collection_file.data(),ifstream::in);
        if(!infile.is_open()){
                printf("ERROR!: FILE NOT FOUND %s \t\t(seen by suckinfile)\n",collection_file.data());
                return; 
        }
	std::string line;
	int n_found = 0;
	while (std::getline(infile, line) && n_found < n_r_guesses_expected){
		//line format: 
		//Hybrid result saved as HypoTestResult_mh120_r0.2788_630311758 in higgsCombineTest.HybridNew.mH120.1.root
		std::istringstream iss(line);
                std::size_t found = line.find("higgsCombineTest");
                //std::size_t found2 = line.find("root");
		if (found!=std::string::npos){
			string crap1;
                        string crap2;
                        string crap3;
                        string crap4;
                        string crap5;
                        string crap6;
                        string thefilename;
                        if (!(iss >> crap1 >> crap2 >> crap3 >> crap4 >> crap5 >> crap6 >> thefilename ) ) { break; }

			//for debugging
			//cout<<crap1<<" "<<crap2<<" "<<crap3<<" "<<crap4<<" "<<crap5<<" "<<crap6<<" "<<thefilename<<endl;
			cout<<"adding "<<thefilename<<endl;

			haddcommand += " "+thefilename;

			n_found++;
		}//end if
	}//end while
	if(n_found != n_r_guesses_expected && n_r_guesses_expected >0) cout<<"Warning! I only found "<<n_found<<" files!, expected "<<n_r_guesses_expected<<endl;

	if(n_found > 0) system(Form("echo \"%s\" >> haddall.sh",haddcommand.Data()));
}//end DoHadd

void RunOnToys(string toysrootfilename, string cardfilename, string runfilename, string resultsfile){
		//ideally here you'd 
	//here you're not going to be that ambitionus. You'll form the commands, make a .sh script runfilename to run them, 
	//and collect the output in resultsfile

	//consider makeing a version of this that popens them and parses the files immediately and just gives you back numbers. 
	
		TString obs_cmd = "combine "+cardfilename+" -M HybridNew --freq --grid="+toysrootfilename;
		TString exp_vlow_cmd = "combine "+cardfilename+" -M HybridNew --freq --grid="+toysrootfilename+" --expectedFromGrid 0.025";
		TString exp_low_cmd = "combine "+cardfilename+" -M HybridNew --freq --grid="+toysrootfilename+" --expectedFromGrid 0.16";
		TString exp_avg_cmd = "combine "+cardfilename+" -M HybridNew --freq --grid="+toysrootfilename+" --expectedFromGrid 0.50";
		TString exp_hi_cmd  = "combine "+cardfilename+" -M HybridNew --freq --grid="+toysrootfilename+" --expectedFromGrid 0.84";
		TString exp_vhi_cmd  = "combine "+cardfilename+" -M HybridNew --freq --grid="+toysrootfilename+" --expectedFromGrid 0.975";

		ofstream runfile;
		runfile.open(runfilename.data() ,ios_base::out);//open for writing

                runfile<<"rm temp3"<<endl;

		runfile<<obs_cmd<<" >& temp3"<<endl;
                runfile<<"cat temp3 > "<< resultsfile <<endl;
                runfile<<"rm temp3"<<endl;

		runfile<<exp_vlow_cmd<<" >& temp3"<<endl;
                runfile<<"cat temp3 >> "<< resultsfile <<endl;
                runfile<<"rm temp3"<<endl;

		runfile<<exp_low_cmd<<" >& temp3"<<endl;
                runfile<<"cat temp3 >> "<< resultsfile <<endl;
                runfile<<"rm temp3"<<endl;

		runfile<<exp_avg_cmd<<" >& temp3"<<endl;
                runfile<<"cat temp3 >> "<< resultsfile <<endl;
                runfile<<"rm temp3"<<endl;

		runfile<<exp_hi_cmd<<" >& temp3"<<endl;
                runfile<<"cat temp3 >> "<< resultsfile <<endl;
                runfile<<"rm temp3"<<endl;

		runfile<<exp_vhi_cmd<<" >& temp3"<<endl;
                runfile<<"cat temp3 >> "<< resultsfile <<endl;
                runfile<<"rm temp3"<<endl;

		runfile.close();
}//end RunOnToys

/*void RunOnToysNow(string toysrootfilename, string cardfilename, string runfilename, string resultsfile){
		//ideally here you'd 
	//here you're not going to be that ambitionus. You'll form the commands, make a .sh script runfilename to run them, 
	//and collect the output in resultsfile

	//consider makeing a version of this that popens them and parses the files immediately and just gives you back numbers. 
	
		TString obs_cmd = "combine "+cardfilename+" -M HybridNew --freq --grid="+toysrootfilename;
		TString exp_low_cmd = "combine "+cardfilename+" -M HybridNew --freq --grid="+toysrootfilename+" --expectedFromGrid 0.16";
		TString exp_avg_cmd = "combine "+cardfilename+" -M HybridNew --freq --grid="+toysrootfilename+" --expectedFromGrid 0.50";
		TString exp_hi_cmd  = "combine "+cardfilename+" -M HybridNew --freq --grid="+toysrootfilename+" --expectedFromGrid 0.84";

		FILE* obsfile; 
		int status;
		char path[PATH_MAX];
		obsfile = popen(obs_cmd.Data(), "r");
		if (obsfile == NULL){
			cout<<"There was a problem with popen on obs_cmd"<<endl;
			return;
		}
		while (fgets(path, PATH_MAX, obsfile) != NULL)
			printf("%s", path);
			//here, figure out all the things. 

		status = pclose(obsfile);
		if (status == -1) {
			cout<<"popen status repports failure on obs_cmd"<<endl;
			return;
		}
		//handle error

}//end RunOnToysNow*/
