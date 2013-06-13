#ifndef MCPOINT
#define MCPOINT
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "TString.h"
#include "params_arg.h"
using namespace std;
using namespace params;

TString makeLimitCardName_(TString MCpointname, TString topo, TString kinvar);//Done writing? Yes. Debugged? No
TString makeRootLimitPackageName_(TString MCpointname, TString topo, TString kinvar);//Done writing? Yes. Debugged? No
TString makeCombineBatchFileName_(TString MCpointname);//Done writing? Yes. Debugged? No
TString makeLimitResultName_(TString MCpointname, TString topo, TString kinvar);//Done writing? Yes. Debugged? No
TString makeLimitResultBundleName_(TString MCpointname);//Done writing? Yes. Debugged? No

class MCpoint{
public:
	MCpoint(int Mstop_, int Mgluino_, int Mhiggsino_, int NGenPoints_, double cs_,int type_=1,string filepath_=""):
	Mstop(Mstop_),Mgluino(Mgluino_),Mhiggsino(Mhiggsino_),NGenPoints(NGenPoints_),cs(cs_),filepath(filepath_) {
		setType(type_);
	}
	~MCpoint(){
		cout<<"running the destructor"<<endl;
	}
		//int index;//some linear index number.

	int Mstop;
	int Mgluino;
	int Mhiggsino;

	int NGenPoints;//always around 2,500,000
	double cs; //1.923E-11 in mbarns

	string pointName;//name used in the map.
	int processID; // a numeric name for use in passing it from the jdl file

	string outroot_mc;// = "susyEvents_MC_AB_1M_st250_ho200.root"; //skim of the events used in analysis form big ntuples
	string btageff_file;// = "b_tag_eff.root"; //The MC B-tag efficiency measured for this MC point.
	string plotsroot_mc;// = "raw_plots_MC_AB_1M_st250_ho200.root"; // raw plots from ana.C
	string logplotsroot_mc;// = "raw_plots_MC_AB_1M_st250_ho200.log";	//log file name 1
	string plotsAndBackground_mc;// = "plotsWithBackground_MC_1M_st250_ho200.root"; //output from postananan.C
	string logplotsAndBackground_mc;// = "plotsWithBackground_MC_1M_st250_ho200.log"; //output from postananan.C
	string formatedplotsroot_mc;//= "formatted_plots_MC_1M_st250_ho200.root"; //output from format_plots.C

	string filepath;//where the origional file actually sits. Need something external to set this.

	string s_DataAndMcFiles; //"mst_350_M3_5025_mu_225"
	string s_DataAndMcFiles_v2; //"MC_mst_350_M3_5025_mu_225"...}
	string s_DataAndMcFiles_v3; //"MC" (or "Data")
	string s_DataAndMcFiles_v4; //"M_{sTop}=650, M_{Higgsino}=275"

	float lumiscalefactor(float lumi_in_fb);
	float cs_fb();
	void setType(int type_);
	
	TString makeLimitCardName(TString topo, TString kinvar);//Returns name of Card File //Done writing? Yes. Debugged? No
//	friend TString makeLimitCardName(TString MCpointname, TString topo, TString kinvar);//Done writing? Yes. Debugged? No

	TString makeRootLimitPackageName(TString topo, TString kinvar);//Returns name of root histogram bundle for use in limit card//Done writing? Yes. Debugged? No
//	friend TString makeRootLimitPackageName(TString MCpointname, TString topo, TString kinvar);//Done writing? Yes. Debugged? No

	TString makeCombineBatchFileName();//return name of batch file that runs limit cards //Done writing? Yes. Debugged?
//	friend TString makeCombineBatchFileName(TString MCpointname);//Done writing? Yes. Debugged? No

	TString makeLimitResultName(TString topo, TString kinvar);//returns name for a single limit result file //Done writing? Yes. Debugged? No
//	friend TString makeLimitResultName(TString MCpointname, TString topo, TString kinvar);//Done writing? Yes. Debugged? No

	TString makeLimitResultBundleName();//returns name of a bundle of limit results //Done writing? Yes. Debugged? No
//	friend	TString makeLimitResultBundleName(TString MCpointname);//Done writing? Yes. Debugged? No
//	friend std::vector<MCpoint*> setupMCpoints();

	int gettype(){return type;}
	int type;
};

TString MCpoint::makeLimitCardName(TString topo, TString kinvar){return makeLimitCardName_(TString(pointName), topo,  kinvar);}//Done writing? Yes. Debugged? No
TString MCpoint::makeRootLimitPackageName(TString topo, TString kinvar){return makeRootLimitPackageName_(TString(pointName), topo, kinvar);}//Done writing? Yes. Debugged? No
TString MCpoint::makeCombineBatchFileName(){return makeCombineBatchFileName_(TString(pointName));}
TString MCpoint::makeLimitResultName(TString topo, TString kinvar){return makeLimitResultName_(TString(pointName),topo,kinvar);} //Done writing? Yes. Debugged? No
TString MCpoint::makeLimitResultBundleName(){return makeLimitResultBundleName_(TString(pointName)); }//Done writing? Yes. Debugged? No

void MCpoint::setType(int type_){
	type = type_;
	if(type == 1){	//higgino only type
		pointName = Form("ho_%i",Mhiggsino);
		outroot_mc = Form("susyEvents_MC_ho%i.root",Mhiggsino);
		btageff_file = Form("b_tag_eff_ho%i.root",Mhiggsino);
		plotsroot_mc = Form("raw_plots_MC_ho%i.root",Mhiggsino);
		logplotsroot_mc = Form("raw_plots_MC_ho%i.log",Mhiggsino);
		plotsAndBackground_mc = Form("plotsWithBackground_MC_ho%i.root",Mhiggsino);
		logplotsAndBackground_mc = Form("plotsWithBackground_MC_ho%i.log",Mhiggsino);
		formatedplotsroot_mc= Form("formatted_plots_MC_ho%i.root",Mhiggsino);

		s_DataAndMcFiles =Form("ho_%i",Mhiggsino);
		s_DataAndMcFiles_v2 = Form("MC_ho_%i",Mhiggsino);
		s_DataAndMcFiles_v3 = "MC";
		s_DataAndMcFiles_v4 = Form("M_{Higgsino}=%i",Mhiggsino);
	}
	else if(type == -1){		//I don't recommend using this; not without changing the naming convention entirely to get rid of "MC"..oh well, I guess I'm doing it anyway
		string Data = "Data";
		Mstop = 0;
		Mgluino = 0;
		Mhiggsino = 0;
		NGenPoints = 1;
		cs = -1;

		pointName = Data;
		outroot_mc = outroot_data;
		btageff_file = "";
		plotsroot_mc = plotsroot_data;
		string plotsroot_mc_copy(plotsroot_mc);
		size_t pos1 = plotsroot_mc_copy.find(".root");
		logplotsroot_mc = plotsroot_mc_copy.replace(pos1,std::string(".root").length(),".log");
		plotsAndBackground_mc = plotsAndBackground_data;
		string plotsAndBackground_data_copy(plotsAndBackground_data);
		size_t pos2 = plotsAndBackground_data_copy.find(".root");
		logplotsAndBackground_mc = plotsAndBackground_data_copy.replace(pos2,std::string(".root").length(),".log");
		formatedplotsroot_mc= formatedplotsroot_data;

		s_DataAndMcFiles = Data;
		s_DataAndMcFiles_v2 = Data;
		s_DataAndMcFiles_v3 = Data;
		s_DataAndMcFiles_v4 = Data;
	}
	else if(type == 2){
		//filepath = Form("%stree_naturalHiggsinoNLSPout_mst_%i_M3_%i_mu_%i.root",filepath.data(),Mstop,Mgluino,Mhiggsino);
		filepath = Form("%snaturalHiggsinoNLSPout_mst_%i_M3_%i_mu_%i.root",filepath.data(),Mstop,Mgluino,Mhiggsino);
			//tree_naturalHiggsinoNLSPout_mst_910_M3_5050_mu_150.root

			//same from here to end as type 0
		pointName = Form("mst_%i_mu_%i",Mstop,Mhiggsino);
		outroot_mc = Form("susyEvents_MC_st%i_ho%i.root",Mstop,Mhiggsino);
		btageff_file = Form("b_tag_eff_st%i_ho%i.root",Mstop,Mhiggsino);
		plotsroot_mc = Form("raw_plots_MC_st%i_ho%i.root",Mstop,Mhiggsino);
		logplotsroot_mc = Form("raw_plots_MC_st%i_ho%i.log",Mstop,Mhiggsino);
		plotsAndBackground_mc = Form("plotsWithBackground_MC_st%i_ho%i.root",Mstop,Mhiggsino);
		logplotsAndBackground_mc = Form("plotsWithBackground_MC_st%i_ho%i.log",Mstop,Mhiggsino);
		formatedplotsroot_mc= Form("formatted_plots_MC_st%i_ho%i.root",Mstop,Mhiggsino);

		s_DataAndMcFiles =Form("mst_%i_M3_%i_mu_%i",Mstop,Mgluino,Mhiggsino);
		s_DataAndMcFiles_v2 = Form("MC_mst_%i_M3_%i_mu_%i",Mstop,Mgluino,Mhiggsino);
		s_DataAndMcFiles_v3 = "MC";
		s_DataAndMcFiles_v4 = Form("M_{sTop}=%i, M_{Higgsino}=%i",Mstop,Mhiggsino);
	}
	else if(type == 3){ //sunil's stuff
			//MCpoints.push_back(new MCpoint(-1,-1,135,ngen, 0.131* bbaa_br,3,type3filedir));
			//MCpoints.back().pointName = "n2n1_135_8_hh_bbaa";

		outroot_mc = Form("susyEvents_MC_%s.root",pointName.data());//this will change.
		btageff_file = Form("b_tag_eff_%s.root",pointName.data());
		plotsroot_mc = Form("raw_plots_MC_%s.root",pointName.data());
		logplotsroot_mc = Form("raw_plots_MC_%s.log",pointName.data());
		plotsAndBackground_mc = Form("plotsWithBackground_MC_%s.root",pointName.data());
		logplotsAndBackground_mc = Form("plotsWithBackground_MC_%s.log",pointName.data());
		formatedplotsroot_mc= Form("formatted_plots_MC_%s.root",pointName.data());

		s_DataAndMcFiles = pointName.data();
		s_DataAndMcFiles_v2 = Form("MC_%s",pointName.data());
		s_DataAndMcFiles_v3 = "MC";
		s_DataAndMcFiles_v4 = Form("M_{Higgsino}=%i",Mhiggsino);
	}
	else if(type == 4){ //Higgs to GG fullsim MC
			//MCpoints.push_back(new MCpoint(-1,-1,-1,16048, 0.0448E-9,4,"/eos/uscms/store/user/abarker/MC/"));//need to recount events; this number is bull
			//MCpoints.back()->pointName = "GluGluToHToGG_quick"; MCpoints.back()->setType(4);

		outroot_mc = Form("susyEvents_MC_%s.root",pointName.data());//this will change.
		btageff_file = "b_tag_eff_for_higgs.root"; //just replace this with a constant. 
		plotsroot_mc = Form("raw_plots_MC_%s.root",pointName.data());
		logplotsroot_mc = Form("raw_plots_MC_%s.log",pointName.data());
		plotsAndBackground_mc = Form("plotsWithBackground_MC_%s.root",pointName.data());
		logplotsAndBackground_mc = Form("plotsWithBackground_MC_%s.log",pointName.data());
		formatedplotsroot_mc= Form("formatted_plots_MC_%s.root",pointName.data());

		s_DataAndMcFiles = pointName.data();
		s_DataAndMcFiles_v2 = Form("MC_%s",pointName.data());
		s_DataAndMcFiles_v3 = "MC";
		//s_DataAndMcFiles_v4 = Form("M_{Higgsino}=%i",Mhiggsino);
	}
	else{ //assume type 0	Stop-higgsion type
		type = 0;
		pointName = Form("mst_%i_mu_%i",Mstop,Mhiggsino);
		outroot_mc = Form("susyEvents_MC_st%i_ho%i.root",Mstop,Mhiggsino);
		btageff_file = Form("b_tag_eff_st%i_ho%i.root",Mstop,Mhiggsino);
		plotsroot_mc = Form("raw_plots_MC_st%i_ho%i.root",Mstop,Mhiggsino);
		logplotsroot_mc = Form("raw_plots_MC_st%i_ho%i.log",Mstop,Mhiggsino);
		plotsAndBackground_mc = Form("plotsWithBackground_MC_st%i_ho%i.root",Mstop,Mhiggsino);
		logplotsAndBackground_mc = Form("plotsWithBackground_MC_st%i_ho%i.log",Mstop,Mhiggsino);
		formatedplotsroot_mc= Form("formatted_plots_MC_st%i_ho%i.root",Mstop,Mhiggsino);

		s_DataAndMcFiles =Form("mst_%i_M3_%i_mu_%i",Mstop,Mgluino,Mhiggsino);
		s_DataAndMcFiles_v2 = Form("MC_mst_%i_M3_%i_mu_%i",Mstop,Mgluino,Mhiggsino);
		s_DataAndMcFiles_v3 = "MC";
		s_DataAndMcFiles_v4 = Form("M_{sTop}=%i, M_{Higgsino}=%i",Mstop,Mhiggsino);
	}
}//end setType

float MCpoint::lumiscalefactor(float lumi_in_fb){
	if(type == -1) return 1;//if data
	return (lumi_in_fb * cs_fb())/((float) NGenPoints);
}
float MCpoint::cs_fb(){
	return (float)(cs * 1E12);
}




std::map<string, int> makemap(std::vector<MCpoint*> MCpoints);
void printMCpoints(std::vector<MCpoint*> MCpoints);
std::vector<MCpoint*> setupMCpoints();
MCpoint * setupMCpoint(string pointname, string filepath="");

	///here you stop doing thing within the class and start doing things outside it




std::vector<MCpoint*> setupMCpoints(){
	std::vector<MCpoint*> MCpoints;

		//lumiscalemap["new_natural_mst_350_M3_5025_mu_225"] = (Integrated_Luminosity_Data * 517.0/*fb*/)/((float) 2500000/*events*/);
		//lumiscalemap["mst_250_M3_5025_mu_200"] = (Integrated_Luminosity_Data * 3311.0/*fb*/)/((float) 2500000/*events*/);
		//lumiscalemap["mst_250_M3_5025_mu_150"] = (Integrated_Luminosity_Data * 2000.0/*fb*/)/((float) 2500000/*events*/);
		//lumiscalemap["mst_350_M3_5025_mu_200"] = (Integrated_Luminosity_Data * 864.0/*fb*/)/((float) 2500000/*events*/);
		//lumiscalemap["ho_140"] = (Integrated_Luminosity_Data * 1833.0/*fb*/)/((float) 2500000/*events*/);
		//lumiscalemap["ho_200"] = (Integrated_Luminosity_Data * 463.0/*fb*/)/((float) 2500000/*events*/);

		//MCpoints.push_back(new MCpoint(350,5025,225,       2500000,      517.0E-12,   0, "/eos/uscms/store/user/abarker/MC/newNat350_225/MC_AB_2500k_NEWnaturalHiggsinoNLSPout_mst_350_M3_5025_mu_225.root"));//new_natural_mst_350_M3_5025_mu_225
	MCpoints.push_back(new MCpoint(350,5025,225,       2500000,      517.0E-12,   0, "/uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/susyEvents_newNatural.root"));
	MCpoints.push_back(new MCpoint(250,5025,200,       2500000,      3311.0E-12,  0,  "/eos/uscms/store/user/abarker/MC/st_250_ho_200/MC_AB_2500k_st_250_ho_200.root"));//mst_250_M3_5025_mu_200
	MCpoints.push_back(new MCpoint(250,5025,150,       2500000,      2000.0E-12,  0,  "/eos/uscms/store/user/abarker/MC/st_250_ho_150/MC_AB_2500k_st_250_ho_150.root"));//mst_250_M3_5025_mu_150
	MCpoints.push_back(new MCpoint(350,5025,200,       2500000,      864.0E-12,  0,  "/eos/uscms/store/user/abarker/MC/st_350_ho_200/MC_AB_2500k_mst_350_mu_200.root"));//mst_350_M3_5025_mu_200
	MCpoints.push_back(new MCpoint(0,0,140,       2500000,      1833.0E-12, 1, "/eos/uscms/store/user/abarker/MC/ho_140/MC_AB_2500k_ho_140.root"));//ho_140
	MCpoints.push_back(new MCpoint(0,0,200,       2500000,      463.0E-12,  1, "/eos/uscms/store/user/abarker/MC/ho_200/MC_AB_2500k_ho_200.root"));//ho_200
	/*
	 These files are also on DCache:
	 chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/MC/MC_AB_2500k_NEWnaturalHiggsinoNLSPout_mst_350_M3_5025_mu_225.root");
	 chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/MC/MC_AB_2500k_st_250_ho_150.root");
	 chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/MC/MC_AB_2500k_st_250_ho_200.root");
	 chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/MC/MC_AB_2500k_mst_350_mu_200.root");
	 chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/MC/MC_AB_2500k_ho_140.root");
	 chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/MC/MC_AB_2500k_ho_200.root");
	 */

	string type2filedir = "dcache:/pnfs/cms/WAX/resilient/lpcpjm/PrivateMC/FastSim/533p3_full/naturalHiggsinoNLSP_try4/SusyNtuple/cms533v3_v2/";

	//string type2filedir = "dcache:/pnfs/cms/WAX/resilient/lpcpjm/PrivateMC/FastSim/533p3_full/naturalHiggsinoNLSP_try4/SusyNtuple/cms533v1_v1/";
	int ngen = 1000000;
	MCpoints.push_back(new MCpoint(1010,5050,150,ngen,5.937E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,175,ngen,3.265E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,200,ngen,1.930E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,225,ngen,1.202E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,250,ngen,7.791E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,275,ngen,5.212E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,300,ngen,3.576E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,325,ngen,2.512E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,375,ngen,1.307E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,425,ngen,7.182E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,475,ngen,4.119E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,525,ngen,2.449E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,575,ngen,1.498E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,625,ngen,9.405E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,675,ngen,6.074E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,725,ngen,4.021E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,825,ngen,1.859E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,925,ngen,8.410E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,1025,ngen,7.224E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,1125,ngen,3.279E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,1225,ngen,1.537E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,150,ngen,5.960E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,175,ngen,3.278E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,200,ngen,1.936E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,225,ngen,1.205E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,250,ngen,7.811E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,275,ngen,5.223E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,300,ngen,3.589E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,325,ngen,2.522E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,375,ngen,1.309E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,425,ngen,7.170E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,475,ngen,4.091E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,525,ngen,2.412E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,575,ngen,1.455E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,625,ngen,8.966E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,675,ngen,5.618E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,725,ngen,3.564E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,825,ngen,1.486E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,925,ngen,6.386E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,1025,ngen,7.090E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,1125,ngen,3.136E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,1225,ngen,1.394E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,150,ngen,5.961E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,1525,ngen,1.217E-15,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,175,ngen,3.276E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,200,ngen,1.939E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,225,ngen,1.206E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,250,ngen,7.807E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,275,ngen,5.231E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,300,ngen,3.593E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,325,ngen,2.523E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,375,ngen,1.312E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,425,ngen,7.188E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,475,ngen,4.098E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,525,ngen,2.415E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,575,ngen,1.459E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,625,ngen,8.974E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,675,ngen,5.629E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,725,ngen,3.569E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,825,ngen,1.485E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,925,ngen,6.341E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(185,5050,150,ngen,1.123E-09,2,type2filedir));
	MCpoints.push_back(new MCpoint(185,5050,175,ngen,8.638E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(210,5050,150,ngen,9.297E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(210,5050,175,ngen,6.704E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(210,5050,200,ngen,5.423E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(235,5050,150,ngen,8.072E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(235,5050,175,ngen,5.472E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(235,5050,200,ngen,4.183E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(235,5050,225,ngen,3.488E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(260,5050,150,ngen,7.298E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(260,5050,175,ngen,4.686E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(260,5050,200,ngen,3.383E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(260,5050,225,ngen,2.684E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(260,5050,250,ngen,2.276E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(285,5050,150,ngen,6.923E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(285,5050,175,ngen,4.186E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(285,5050,200,ngen,2.880E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(285,5050,225,ngen,2.168E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(285,5050,250,ngen,1.764E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(285,5050,275,ngen,1.519E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(310,5050,150,ngen,6.929E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(310,5050,175,ngen,3.862E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(310,5050,200,ngen,2.553E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(310,5050,225,ngen,1.843E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(310,5050,250,ngen,1.434E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(310,5050,275,ngen,1.186E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(310,5050,300,ngen,1.031E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(335,5050,150,ngen,6.676E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(335,5050,175,ngen,3.957E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(335,5050,200,ngen,2.340E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(335,5050,225,ngen,1.631E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(335,5050,250,ngen,1.219E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(335,5050,275,ngen,9.683E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(335,5050,300,ngen,8.115E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(335,5050,325,ngen,7.102E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(360,5050,150,ngen,6.481E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(360,5050,175,ngen,3.793E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(360,5050,200,ngen,2.410E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(360,5050,225,ngen,1.490E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(360,5050,250,ngen,1.075E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(360,5050,275,ngen,8.257E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(360,5050,300,ngen,6.654E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(360,5050,325,ngen,5.637E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(385,5050,150,ngen,6.310E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(385,5050,175,ngen,3.656E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(385,5050,200,ngen,2.307E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(385,5050,225,ngen,1.535E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(385,5050,250,ngen,9.811E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(385,5050,300,ngen,5.698E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(385,5050,325,ngen,4.662E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(385,5050,375,ngen,3.509E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(410,5050,150,ngen,6.205E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(410,5050,175,ngen,3.546E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(410,5050,200,ngen,2.213E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(410,5050,225,ngen,1.468E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(410,5050,250,ngen,1.011E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(410,5050,275,ngen,6.641E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(410,5050,325,ngen,4.010E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(410,5050,375,ngen,2.839E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(460,5050,150,ngen,6.061E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(460,5050,175,ngen,3.404E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(460,5050,200,ngen,2.077E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(460,5050,225,ngen,1.349E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(460,5050,250,ngen,9.256E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(460,5050,275,ngen,6.601E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(460,5050,300,ngen,4.757E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(460,5050,375,ngen,2.067E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(460,5050,425,ngen,1.497E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,150,ngen,5.986E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,175,ngen,3.334E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,200,ngen,2.002E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,225,ngen,1.279E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,250,ngen,8.598E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,275,ngen,6.021E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,300,ngen,4.371E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,325,ngen,3.251E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,375,ngen,1.693E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,425,ngen,1.119E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,475,ngen,8.233E-12,2,type2filedir));


	string type3filedir = "/eos/uscms/store/user/abarker/MC/Sunil/";
	ngen = 5000;
	float bbaa_br = 2.0*5.61E-01*2.29E-03;
		//the branching ratios of interest: h - > bb = 5.61E-01; h - > aa = 2.29E-03, so BR(h->bbaa) = 2*5.61E-01*2.29E-03
	MCpoints.push_back(new MCpoint(-1,-1,135,ngen, (1498.8/131.0)*0.131E-9* bbaa_br,3,type3filedir));//scale to emulate the whole set
	MCpoints.back()->pointName = "n2n1_135_8_hh_bbaa"; MCpoints.back()->setType(3);
	MCpoints.push_back(new MCpoint(-1,-1,135,ngen, 0.383E-9* bbaa_br,3,type3filedir));
	MCpoints.back()->pointName = "x1px1m_135_8_hh_bbaa"; MCpoints.back()->setType(3);
	MCpoints.push_back(new MCpoint(-1,-1,135,ngen, 0.498E-9* bbaa_br,3,type3filedir));
	MCpoints.back()->pointName = "x1pn1_135_8_hh_bbaa"; MCpoints.back()->setType(3);
	MCpoints.push_back(new MCpoint(-1,-1,135,ngen, 0.259E-9* bbaa_br,3,type3filedir));
	MCpoints.back()->pointName = "x1mn1_135_8_hh_bbaa"; MCpoints.back()->setType(3);
	MCpoints.push_back(new MCpoint(-1,-1,135,ngen, 0.153E-9* bbaa_br,3,type3filedir));
	MCpoints.back()->pointName = "x1pn2_135_8_hh_bbaa"; MCpoints.back()->setType(3);
	MCpoints.push_back(new MCpoint(-1,-1,135,ngen, 0.0748E-9* bbaa_br,3,type3filedir));
	MCpoints.back()->pointName = "x1mn2_135_8_hh_bbaa"; MCpoints.back()->setType(3);

	MCpoints.push_back(new MCpoint(-1,-1,145,ngen, (1.1435/0.0992)*0.0992E-9* bbaa_br,3,type3filedir));//scale to emulate the whole set
	MCpoints.back()->pointName = "n2n1_145_8_hh_bbaa"; MCpoints.back()->setType(3);
	MCpoints.push_back(new MCpoint(-1,-1,145,ngen, 0.294E-9* bbaa_br,3,type3filedir));
	MCpoints.back()->pointName = "x1px1m_145_8_hh_bbaa"; MCpoints.back()->setType(3);
	MCpoints.push_back(new MCpoint(-1,-1,145,ngen, 0.382E-9* bbaa_br,3,type3filedir));
	MCpoints.back()->pointName = "x1pn1_145_8_hh_bbaa"; MCpoints.back()->setType(3);
	MCpoints.push_back(new MCpoint(-1,-1,145,ngen, 0.194E-9* bbaa_br,3,type3filedir));
	MCpoints.back()->pointName = "x1mn1_145_8_hh_bbaa"; MCpoints.back()->setType(3);
	MCpoints.push_back(new MCpoint(-1,-1,145,ngen, 0.118E-9* bbaa_br,3,type3filedir));
	MCpoints.back()->pointName = "x1pn2_145_8_hh_bbaa"; MCpoints.back()->setType(3);
	MCpoints.push_back(new MCpoint(-1,-1,145,ngen, 0.0563E-9* bbaa_br,3,type3filedir));
	MCpoints.back()->pointName = "x1mn2_145_8_hh_bbaa"; MCpoints.back()->setType(3);

	MCpoints.push_back(new MCpoint(-1,-1,155,ngen, (0.3635/0.0302)*0.0302E-9* bbaa_br,3,type3filedir));//scale to emulate the whole set
	MCpoints.back()->pointName = "n2n1_155_8_hh_bbaa"; MCpoints.back()->setType(3);
	MCpoints.push_back(new MCpoint(-1,-1,155,ngen, 0.0952E-9* bbaa_br,3,type3filedir));
	MCpoints.back()->pointName = "x1px1m_155_8_hh_bbaa"; MCpoints.back()->setType(3);
	MCpoints.push_back(new MCpoint(-1,-1,155,ngen, 0.125E-9* bbaa_br,3,type3filedir));
	MCpoints.back()->pointName = "x1pn1_155_8_hh_bbaa"; MCpoints.back()->setType(3);
	MCpoints.push_back(new MCpoint(-1,-1,155,ngen, 0.0579E-9* bbaa_br,3,type3filedir));
	MCpoints.back()->pointName = "x1mn1_155_8_hh_bbaa"; MCpoints.back()->setType(3);
	MCpoints.push_back(new MCpoint(-1,-1,155,ngen, 0.0385E-9* bbaa_br,3,type3filedir));
	MCpoints.back()->pointName = "x1pn2_155_8_hh_bbaa"; MCpoints.back()->setType(3);
	MCpoints.push_back(new MCpoint(-1,-1,155,ngen, 0.0167E-9* bbaa_br,3,type3filedir));
	MCpoints.back()->pointName = "x1mn2_155_8_hh_bbaa"; MCpoints.back()->setType(3);

	//higgs to gg fullsim
	MCpoints.push_back(new MCpoint(-1,-1,-1,7199, 0.0448E-9,4,"/eos/uscms/store/user/abarker/MC/"));
	MCpoints.back()->pointName = "GluGluToHToGG_quick"; MCpoints.back()->setType(4);
	MCpoints.back()->s_DataAndMcFiles_v4 = "gg #rightarrow h #rightarrow #gamma #gamma";

	MCpoints.push_back(new MCpoint(-1,-1,-1,10000, 0.0448E-9,4,"/eos/uscms/store/user/abarker/MC/"));
	MCpoints.back()->pointName = "GluGluToHToGG"; MCpoints.back()->setType(4);
	MCpoints.back()->s_DataAndMcFiles_v4 = "gg #rightarrow h #rightarrow #gamma #gamma";

	MCpoints.push_back(new MCpoint(-1,-1,-1,10000, 0.00357E-9,4,"/eos/uscms/store/user/abarker/MC/"));
	MCpoints.back()->pointName = "VBF_HToGG"; MCpoints.back()->setType(4);
	MCpoints.back()->s_DataAndMcFiles_v4 = "VBF h #rightarrow #gamma #gamma";

	MCpoints.push_back(new MCpoint(-1,-1,-1,10000, 0.0025E-9,4,"/eos/uscms/store/user/abarker/MC/")); 
	MCpoints.back()->pointName = "VH_HToGG"; MCpoints.back()->setType(4);
	MCpoints.back()->s_DataAndMcFiles_v4 = "Vh, h #rightarrow #gamma #gamma";


	/*Order:
	 n2n1
	 x1px1m
	 x1pn1
	 x1mn1
	 x1pn2
	 x1mn2
	 For higgsino mass 135:
	   nn  1  2  1.2672 0.131
	   nn  5  7  1.2820 0.383
	   nn  1  5  1.2871 0.498
	   nn  1  7  1.3012 0.259
	   nn  2  5  1.2484 0.153
	   nn  2  7  1.2660 0.0748
	 For higgsino mass 145:
	   nn  1  2  1.2601 0.0992
	   nn  5  7  1.2789 0.294
	   nn  1  5  1.2775 0.382
	   nn  1  7  1.2990 0.194
	   nn  2  5  1.2373 0.118
	   nn  2  7  1.2629 0.0563
	 For higgsino mass 155:
	   nn  1  2  1.2285 0.0302
	   nn  5  7  1.2605 0.0952
	   nn  1  5  1.2480 0.125
	   nn  1  7  1.2763 0.0579
	   nn  2  5  1.2156 0.0385
	   nn  2  7  1.2515 0.0167
	 */

		//These are from the before time when we had bugs in our MC Gen. Their crossections are fubar!!
	/*
	 //MCpoints.push_back(new MCpoint(1000,5025,125,       2499364,      16920188,   1.727E-09));
	 MCpoints.push_back(new MCpoint(1000,5025,175,       2499358,      17194360,   4.761E-10));
	 MCpoints.push_back(new MCpoint(1000,5025,225,       2499311,      17648647,   1.756E-10));
	 MCpoints.push_back(new MCpoint(1000,5025,375,       2499107,      20212366,   1.923E-11));
	 MCpoints.push_back(new MCpoint(1000,5025,525,       2499000,      27361729,   3.614E-12));
	 MCpoints.push_back(new MCpoint(1000,5025,575,       2498971,      31044448,   2.215E-12));
	 //MCpoints.push_back(new MCpoint(100,5025,125,       2481742,      86062365,   7.565E-09));     //largest cross section
	 MCpoints.push_back(new MCpoint(100,5025,175,       2474617,      98810609,   6.372E-09));
	 //MCpoints.push_back(new MCpoint(1500,5025,125,       2499414,      16896940,   1.729E-09));
	 MCpoints.push_back(new MCpoint(1500,5025,175,       2499373,      17154844,   4.767E-10));
	 MCpoints.push_back(new MCpoint(1500,5025,225,       2499268,      17542698,   1.757E-10));
	 MCpoints.push_back(new MCpoint(1500,5025,275,       2499289,      17931924,   7.647E-11));
	 MCpoints.push_back(new MCpoint(1500,5025,325,       2499241,      18436745,   3.698E-11));
	 MCpoints.push_back(new MCpoint(1500,5025,425,       2499149,      20576264,   1.055E-11));
	 MCpoints.push_back(new MCpoint(1500,5025,525,       2499058,      23477889,   3.553E-12));
	 //MCpoints.push_back(new MCpoint(150,5025,125,       2488655,      75534489,   4.248E-09));
	 MCpoints.push_back(new MCpoint(150,5025,175,       2478498,      98753644,   3.029E-09));
	 //MCpoints.push_back(new MCpoint(2000,5025,125,       2499360,      16883090,   1.729E-09));
	 MCpoints.push_back(new MCpoint(2000,5025,175,       2499368,      17139806,   4.773E-10));
	 MCpoints.push_back(new MCpoint(2000,5025,225,       2499272,      17511966,   1.760E-10));
	 MCpoints.push_back(new MCpoint(2000,5025,275,       2499271,      17917333,   7.660E-11));
	 MCpoints.push_back(new MCpoint(2000,5025,325,       2499243,      18410265,   3.701E-11));
	 MCpoints.push_back(new MCpoint(2000,5025,425,       2499184,      20528769,   1.057E-11));
	 MCpoints.push_back(new MCpoint(2000,5025,475,       2499135,      21888107,   6.039E-12));
	 MCpoints.push_back(new MCpoint(2000,5025,775,       2498892,      30689383,   3.381E-13));
	 MCpoints.push_back(new MCpoint(2000,5025,875,       2498742,      33557395,   1.426E-13));
	 MCpoints.push_back(new MCpoint(2000,5025,975,       2498703,      36434364,   6.161E-14));
	 //MCpoints.push_back(new MCpoint(200,5025,125,       2494491,      58023664,   2.760E-09));
	 MCpoints.push_back(new MCpoint(200,5025,175,       2484842,      90742426,   1.526E-09));
	 //MCpoints.push_back(new MCpoint(250,5025,125,       2497479,      41292840,   2.151E-09));
	 MCpoints.push_back(new MCpoint(250,5025,175,       2491606,      73629184,   9.166E-10));
	 //MCpoints.push_back(new MCpoint(300,5025,125,       2499006,      29459675,   1.957E-09));
	 MCpoints.push_back(new MCpoint(300,5025,175,       2495982,      54338860,   6.668E-10));
	 MCpoints.push_back(new MCpoint(300,5025,225,       2490335,      83750434,   3.704E-10));
	 //MCpoints.push_back(new MCpoint(350,5025,125,       2499239,      23673189,   1.835E-09));
	 MCpoints.push_back(new MCpoint(350,5025,175,       2498679,      37795810,   5.862E-10));
	 MCpoints.push_back(new MCpoint(350,5025,225,       2495051,      64018960,   2.644E-10));
	 MCpoints.push_back(new MCpoint(350,5025,275,       2489699,      91061781,   1.668E-10));
	 //MCpoints.push_back(new MCpoint(400,5025,125,       2499248,      20667535,   1.774E-09));
	 MCpoints.push_back(new MCpoint(400,5025,175,       2499119,      29132453,   5.314E-10));
	 MCpoints.push_back(new MCpoint(400,5025,225,       2498545,      44598225,   2.293E-10));
	 //MCpoints.push_back(new MCpoint(450,5025,125,       2499326,      19023857,   1.748E-09));
	 MCpoints.push_back(new MCpoint(450,5025,175,       2499167,      24121282,   5.036E-10));
	 MCpoints.push_back(new MCpoint(450,5025,225,       2498985,      34124867,   2.042E-10));
	 MCpoints.push_back(new MCpoint(450,5025,275,       2498368,      49993733,   1.037E-10));
	 MCpoints.push_back(new MCpoint(450,5025,325,       2493952,      76551830,   5.875E-11));
	 //MCpoints.push_back(new MCpoint(5000,5025,125,       2499368,      16851674,   1.732E-09));
	 MCpoints.push_back(new MCpoint(5000,5025,175,       2499373,      17125006,   4.778E-10));
	 MCpoints.push_back(new MCpoint(5000,5025,225,       2499308,      17509295,   1.761E-10));
	 MCpoints.push_back(new MCpoint(5000,5025,275,       2499289,      17876386,   7.670E-11));
	 MCpoints.push_back(new MCpoint(5000,5025,325,       2499253,      18365279,   3.710E-11));
	 MCpoints.push_back(new MCpoint(5000,5025,475,       2499146,      21820769,   6.053E-12));
	 MCpoints.push_back(new MCpoint(5000,5025,525,       2499075,      23269454,   3.573E-12));
	 MCpoints.push_back(new MCpoint(5000,5025,575,       2499080,      24729972,   2.160E-12));
	 MCpoints.push_back(new MCpoint(5000,5025,775,       2498963,      30563131,   3.395E-13));
	 MCpoints.push_back(new MCpoint(5000,5025,825,       2498988,      31962057,   2.199E-13));
	 MCpoints.push_back(new MCpoint(5000,5025,875,       2498886,      33421312,   1.432E-13));
	 //MCpoints.push_back(new MCpoint(500,5025,125,       2499279,      18106211,   1.735E-09));
	 MCpoints.push_back(new MCpoint(500,5025,175,       2499207,      21192071,   4.897E-10));
	 MCpoints.push_back(new MCpoint(500,5025,225,       2499175,      27544790,   1.904E-10));
	 //MCpoints.push_back(new MCpoint(550,5025,125,       2499358,      17642251,   1.728E-09));
	 MCpoints.push_back(new MCpoint(550,5025,175,       2499269,      19568246,   4.825E-10));
	 MCpoints.push_back(new MCpoint(550,5025,225,       2499184,      23585013,   1.833E-10));
	 MCpoints.push_back(new MCpoint(600,1525,175,       2499290,      18614580,   4.790E-10));
	 //MCpoints.push_back(new MCpoint(600,5025,125,       2499354,      17362209,   1.726E-09));
	 MCpoints.push_back(new MCpoint(600,5025,175,       2499320,      18584654,   4.793E-10));
	 MCpoints.push_back(new MCpoint(600,5025,225,       2499256,      21217587,   1.796E-10));
	 //MCpoints.push_back(new MCpoint(650,5025,125,       2499359,      17183098,   1.726E-09));
	 MCpoints.push_back(new MCpoint(650,5025,175,       2499291,      18055288,   4.773E-10));
	 MCpoints.push_back(new MCpoint(650,5025,225,       2499270,      19823269,   1.776E-10));
	 MCpoints.push_back(new MCpoint(650,5025,275,       2499189,      22861808,   7.873E-11));
	 //MCpoints.push_back(new MCpoint(700,5025,125,       2499373,      17073231,   1.725E-09));
	 MCpoints.push_back(new MCpoint(700,5025,175,       2499324,      17742969,   4.761E-10));
	 MCpoints.push_back(new MCpoint(700,5025,225,       2499244,      18972983,   1.764E-10));
	 MCpoints.push_back(new MCpoint(700,5025,275,       2499149,      21027373,   7.761E-11));
	 MCpoints.push_back(new MCpoint(700,5025,325,       2499142,      24466063,   3.832E-11));
	 //MCpoints.push_back(new MCpoint(750,5025,125,       2499367,      17023133,   1.725E-09));
	 MCpoints.push_back(new MCpoint(750,5025,175,       2499334,      17524868,   4.759E-10));
	 MCpoints.push_back(new MCpoint(750,5025,225,       2499188,      18446270,   1.760E-10));
	 MCpoints.push_back(new MCpoint(750,5025,275,       2499188,      19882754,   7.697E-11));
	 MCpoints.push_back(new MCpoint(750,5025,325,       2499177,      22268998,   3.767E-11));
	 MCpoints.push_back(new MCpoint(750,5025,375,       2499092,      26311225,   2.005E-11));
	 //MCpoints.push_back(new MCpoint(800,5025,125,       2499381,      16989206,   1.725E-09));
	 MCpoints.push_back(new MCpoint(800,5025,175,       2499294,      17401112,   4.758E-10));
	 MCpoints.push_back(new MCpoint(800,5025,225,       2499293,      18124818,   1.757E-10));
	 MCpoints.push_back(new MCpoint(800,5025,275,       2499225,      19181900,   7.668E-11));
	 MCpoints.push_back(new MCpoint(800,5025,325,       2499144,      20895246,   3.732E-11));
	 MCpoints.push_back(new MCpoint(800,5025,375,       2499084,      23847631,   1.969E-11));
	 MCpoints.push_back(new MCpoint(800,5025,425,       2498987,      28345861,   1.104E-11));
	 //MCpoints.push_back(new MCpoint(850,5025,125,       2499362,      16955742,   1.726E-09));
	 MCpoints.push_back(new MCpoint(850,5025,175,       2499258,      17316375,   4.760E-10));
	 MCpoints.push_back(new MCpoint(850,5025,225,       2499279,      17923593,   1.755E-10));
	 MCpoints.push_back(new MCpoint(850,5025,275,       2499203,      18733113,   7.652E-11));
	 MCpoints.push_back(new MCpoint(850,5025,325,       2499196,      20031441,   3.714E-11));
	 MCpoints.push_back(new MCpoint(850,5025,425,       2499051,      25653093,   1.082E-11));
	 MCpoints.push_back(new MCpoint(850,5025,525,       2498878,      36693358,   3.868E-12));
	 //MCpoints.push_back(new MCpoint(900,5025,125,       2499389,      16949209,   1.726E-09));
	 MCpoints.push_back(new MCpoint(900,5025,175,       2499289,      17275793,   4.756E-10));
	 MCpoints.push_back(new MCpoint(900,5025,225,       2499246,      17786135,   1.755E-10));
	 MCpoints.push_back(new MCpoint(900,5025,325,       2499191,      19497369,   3.703E-11));
	 MCpoints.push_back(new MCpoint(900,5025,475,       2498974,      27470358,   6.201E-12));
	 //MCpoints.push_back(new MCpoint(950,5025,125,       2499378,      16946691,   1.724E-09));
	 MCpoints.push_back(new MCpoint(950,5025,175,       2499345,      17226528,   4.762E-10));
	 */
		//for(std::vector<MCpoint*>::iterator it = MCpoints.begin();it!=MCpoints.end();it++)
		//it->filepath = Form("/eos/uscms/store/user/lpcpjm/PrivateMC/FastSim/533p3_full/naturalHiggsinoNLSP/SusyNtuple/cms533v1_v1/tree_naturalHiggsinoNLSPout_mst_%i_M3_%i_mu_%i.root", it->Mstop,it->Mgluino,it->Mhiggsino);
		//for(int i=0, i<(int)MCpoints.size();i++)
		//MCpoints[i]->filepath = Form("/eos/uscms/store/user/lpcpjm/PrivateMC/FastSim/533p3_full/naturalHiggsinoNLSP/SusyNtuple/cms533v1_v1/tree_naturalHiggsinoNLSPout_mst_%i_M3_%i_mu_%i.root",
		//MCpoints[i]->Mstop,MCpoints[i]->Mgluino,MCpoints[i]->Mhiggsino);

	//within in a type, assign an index number to each. 
	int i_processID = 0;
	std::vector<MCpoint*>::iterator it = MCpoints.begin();
	int thistype = (*it)->type;
	for(;it!=MCpoints.end();it++){
		int temptype = (*it)->type; //sometimes calling (*it)->type will segfault for no reason
		if(temptype == thistype){
//		if((*it)->type == thistype){
			(*it)->processID = i_processID++;
		}
		else{
			i_processID = 0;
			thistype = temptype;//used for cluster 
		}
	}

	return MCpoints;
}//end setup

void printMCpoints(std::vector<MCpoint*> MCpoints){
	for(int i=0; i<(int)MCpoints.size();i++) printf("MStop %i \t MHiggsino %i\n",MCpoints[i]->Mstop,MCpoints[i]->Mhiggsino);
}

std::map<string, int> makemap(std::vector<MCpoint*> MCpoints){
		//naming convension: mstop_mhiggino
		//We call the point by it's point name in params.h, then map it to this to get the right one.
	std::map<string,int> m;
	for(int i=0; i<(int)(MCpoints.size());i++){
		string temp = MCpoints[i]->pointName;
		m[temp] = i;
	}
		//m["350_225"] = 10;//the index is the array index in the vector MCpoints
		//...
	return m;
}
MCpoint * setupMCpoint(string pointname, string filepath){
		//returns a pointer to a fully setup MC point, ready to use.
		//you should add a check that the file exists.
	if(pointname.compare("Data") ==0 ){
		MCpoint *d = new MCpoint(1,1,1,1,1,1);
		d->setType(-1);
		if(filepath.compare("")!=0) d->filepath = filepath;
		return d;
	}
	std::vector<MCpoint*> vp = setupMCpoints();//this segfaults!!
		//std::map<string, int> pmap = makemap(vp);
		//string s_pointname = pointname;
	bool foundit = false;
	std::vector<MCpoint*>::iterator it = vp.begin();
	MCpoint* thispoint = *it;// = vp[pmap[s_pointname]];//default nonsense value
	while (it != vp.end() ){
		if((*it)->pointName.compare(pointname) == 0){ // they are the same
			foundit = true;
			thispoint = *it;
			it++;
		}
		else{
			vp.erase(it);	//delete and go to the next one.
		}
	}//end while
	if(!foundit) cout<<"WARNING !! DID NOT FIND MC POINT!! USING DEFAULT POINT"<<endl;
	if(filepath.compare("")!=0) thispoint->filepath = filepath; // its not ""
	return thispoint;
}//end setupMCpoint



TString makeLimitCardName_(TString MCpointname, TString topo, TString kinvar){
	//returns the name of the card file to be used for this Mass point, topo, and kinvar.
	return "LimitCard_"+MCpointname+"_"+topo+"_"+kinvar+".txt";
}//Done writing? Yes. Debugged? No

TString makeRootLimitPackageName_(TString MCpointname, TString topo, TString kinvar){
	//Returns name of root histogram bundle for use in limit card.
	//the root file will contian the main MC hist and all the various shape systematic histograms.
	return "LimitPackage_"+MCpointname+"_"+topo+"_"+kinvar+".root";
}//Done writing? Yes. Debugged? No

TString makeCombineBatchFileName_(TString MCpointname){
	//Returns the name of the batch file that will run all the CLs limit commands for one mass point
	//and pipe the results into the LimitResultBundle
	return "doLimits_"+MCpointname+".sh";
}//Done writing? Yes. Debugged? No

TString makeLimitResultName_(TString MCpointname, TString topo, TString kinvar){
	//This Returns the name of the text file contianing the results of a single limit setting--
	//so the results for one topo and kinvar for one mass point. If you use these there will be a lot per run
	//It's really meant to be for making one by hand.
	return "LimitResult_"+MCpointname+"_"+topo+"_"+kinvar+".txt";
}//Done writing? Yes. Debugged? No

TString makeLimitResultBundleName_(TString MCpointname){
	//Returns the name of the text file containing all the CLs limits for one MC point. This is the limit output of your condor job.
	return "LimitResultBundle_"+MCpointname+".txt";
}//Done writing? Yes. Debugged? No




#endif
