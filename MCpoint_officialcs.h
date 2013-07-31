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
	double cs_uncert; //in percent

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
	cs_uncert = -1;
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
	else if(type == -1){
			//     ___       __
			//    / _ \___ _/ /____ _
			//   / // / _ `/ __/ _ `/
			//  /____/\_,_/\__/\_,_/
			//
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
			//    ____  __   __  __   ____      ______              __ ___               _
			//   / __ \/ /__/ / / /  / __ \  __/_  __/__  ___  ____/ // (_)__ ____ ____ (_)__  ___
			//  / /_/ / / _  / / /__/ /_/ / (_-</ / / _ \/ _ \/___/ _  / / _ `/ _ `(_-</ / _ \/ _ \
			//  \____/_/\_,_/ /____/\____/ /___/_/  \___/ .__/   /_//_/_/\_, /\_, /___/_/_//_/\___/
			//                                         /_/              /___//___/

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
			//    ____  __   __  ____          _ __  _____
			//   / __ \/ /__/ / / __/_ _____  (_) / / ___/______ ____
			//  / /_/ / / _  / _\ \/ // / _ \/ / / / /__/ __/ _ `/ _ \
			//  \____/_/\_,_/ /___/\_,_/_//_/_/_/  \___/_/  \_,_/ .__/
			//                                                 /_/
		
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
			//     ______  ___   __ ___
			//    / __/  |/  /  / // (_)__ ____ ____
			//   _\ \/ /|_/ /  / _  / / _ `/ _ `(_-<
			//  /___/_/  /_/  /_//_/_/\_, /\_, /___/
			//                       /___//___/

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
	else if(type >= 10 && type < 20){ //new strong production
			//       ______              __ ___               _
			//    __/_  __/__  ___  ____/ // (_)__ ____ ____ (_)__  ___
			//   (_-</ / / _ \/ _ \/___/ _  / / _ `/ _ `(_-</ / _ \/ _ \
			//  /___/_/  \___/ .__/   /_//_/_/\_, /\_, /___/_/_//_/\___/
			//              /_/              /___//___/
		string typelable;
		string nicelable;
		int randSeed=0;
		if (type == 10){
			typelable = "bbaa";
			nicelable = "bb\\gamma\\gamma";
			randSeed=15;
		}//tree_StopHiggs_stop200_chargino150_15_hh_bbaa.root
		else if (type == 11){
			typelable = "wwaa";
			nicelable = "ww\\gamma\\gamma";
			randSeed=5;
		}//tree_StopHiggs_stop200_chargino150_5_hh_wwaa.root
		else if (type == 12){
			typelable = "zzaa";
			nicelable = "zz\\gamma\\gamma";
			randSeed=10;
		}//tree_StopHiggs_stop200_chargino150_10_hh_zzaa.root
		else{ //if (type == 13){
			typelable = "ttaa";
			nicelable = "tt\\gamma\\gamma";
			randSeed=13;
		}//tree_StopHiggs_stop200_chargino150_13_hh_ttaa.root

		filepath = Form("%stree_StopHiggs_stop%i_chargino%i_%i_hh_%s.root",filepath.data(),Mstop,Mhiggsino,randSeed,typelable.data());
		pointName = Form("st_%i_mu_%i_%s",Mstop,Mhiggsino,typelable.data());
		outroot_mc = Form("susyEvents_MC_st%i_ho%i_%s.root",Mstop,Mhiggsino,typelable.data());
		btageff_file = Form("b_tag_eff_st%i_ho%i_bbaa.root",Mstop,Mhiggsino);//always bbaa to keep statistics. 
		plotsroot_mc = Form("raw_plots_MC_st%i_ho%i_%s.root",Mstop,Mhiggsino,typelable.data());
		logplotsroot_mc = Form("raw_plots_MC_st%i_ho%i_%s.log",Mstop,Mhiggsino,typelable.data());
		plotsAndBackground_mc = Form("plotsWithBackground_MC_st%i_ho%i_%s.root",Mstop,Mhiggsino,typelable.data());
		logplotsAndBackground_mc = Form("plotsWithBackground_MC_st%i_ho%i_%s.log",Mstop,Mhiggsino,typelable.data());
		formatedplotsroot_mc= Form("formatted_plots_MC_st%i_ho%i_%s.root",Mstop,Mhiggsino,typelable.data());

		s_DataAndMcFiles =Form("mst_%i_mu_%i_%s",Mstop,Mhiggsino,typelable.data());
		s_DataAndMcFiles_v2 = Form("MC_mst_%i_mu_%i_%s",Mstop,Mhiggsino,typelable.data());
		s_DataAndMcFiles_v3 = "MC";
		s_DataAndMcFiles_v4 = Form("M_{sTop}=%i, M_{Higgsino}=%i",Mstop,Mhiggsino);
	}
	
	else if(type >= 20 && type < 30){ //new strong production
			//     ______        __           __ ___
			//    / __/ /__ ____/ /________  / // (_)__ ____ ____
			//   / _// / -_) __/ __/ __/ _ \/ _  / / _ `/ _ `(_-<
			//  /___/_/\__/\__/\__/_/  \___/_//_/_/\_, /\_, /___/
			//
		string typelable;
		string nicelable;
		cs_uncert = 5;//5%
		int randSeed=0;
		if (type == 20){  //tree_ElectroHiggs_chargino135_15_hh_bbaa.root
			typelable = "bbaa";
			nicelable = "bb\\gamma\\gamma";
			randSeed=15;
		}
		else if (type == 21){  //tree_ElectroHiggs_chargino150_5_hh_wwaa.root
			typelable = "wwaa";
			nicelable = "ww\\gamma\\gamma";
			randSeed=5;
		}
		else if (type == 22){  //tree_ElectroHiggs_chargino240_10_hh_zzaa.root
			typelable = "zzaa";
			nicelable = "zz\\gamma\\gamma";
			randSeed=10;
		}
		else{ //if (type == 23){  //tree_ElectroHiggs_chargino240_13_hh_ttaa.root
			typelable = "ttaa";
			nicelable = "tt\\gamma\\gamma";
			randSeed=13;
		}
		filepath = Form("%stree_ElectroHiggs_chargino%i_%i_hh_%s.root",filepath.data(),Mhiggsino,randSeed,typelable.data());
		pointName = Form("mu_%i_%s",Mhiggsino,typelable.data());
		outroot_mc = Form("susyEvents_MC_%s.root",pointName.data());//this will change.
		btageff_file = Form("b_tag_eff_mu_%i_bbaa.root",Mhiggsino); //always bbaa
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
	else{ //assume type 0	Stop-higgsion type
			//     ___      ___          ____
			//    / _ \___ / _/__ ___ __/ / /_
			//   / // / -_) _/ _ `/ // / / __/
			//  /____/\__/_/ \_,_/\_,_/_/\__/   ______              __ ___               _
			//   / __ \/ /__/ / / /  / __ \  __/_  __/__  ___  ____/ // (_)__ ____ ____ (_)__  ___
			//  / /_/ / / _  / / /__/ /_/ / (_-</ / / _ \/ _ \/___/ _  / / _ `/ _ `(_-</ / _ \/ _ \
			//  \____/_/\_,_/ /____/\____/ /___/_/  \___/ .__/   /_//_/_/\_, /\_, /___/_/_//_/\___/
			//                                         /_/              /___//___/
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
void printMCpoints();
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

		//     ____     _ __  _      __  __  __                       _
		//    /  _/__  (_) /_(_)__ _/ /  \ \/ /__ _  _____ ____ ___  (_)
		//   _/ // _ \/ / __/ / _ `/ /    \  / -_) |/ / _ `/ -_) _ \/ /
		//  /___/_//_/_/\__/_/\_,_/_/     /_/\__/|___/\_, /\__/_//_/_/
		//                                           /___/
	
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

		//    ____  __   __  __   ____      ______              __ ___               _
		//   / __ \/ /__/ / / /  / __ \  __/_  __/__  ___  ____/ // (_)__ ____ ____ (_)__  ___
		//  / /_/ / / _  / / /__/ /_/ / (_-</ / / _ \/ _ \/___/ _  / / _ `/ _ `(_-</ / _ \/ _ \
		//  \____/_/\_,_/ /____/\____/ /___/_/  \___/ .__/   /_//_/_/\_, /\_, /___/_/_//_/\___/
		//                                         /_/              /___//___/
	string type2filedir = "dcache:/pnfs/cms/WAX/resilient/lpcpjm/PrivateMC/FastSim/533p3_full/naturalHiggsinoNLSP_try4/SusyNtuple/cms533v3_v2/";
		//string type2filedir = "dcache:/pnfs/cms/WAX/resilient/lpcpjm/PrivateMC/FastSim/533p3_full/naturalHiggsinoNLSP_try4/SusyNtuple/cms533v1_v1/";
	int ngen = 1000000;
	MCpoints.push_back(new MCpoint(185,5050,150,443138,5.490900E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(185,5050,175,554992,5.496100E-10,2,type2filedir));

	MCpoints.push_back(new MCpoint(210,5050,150,354025,3.541100E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(210,5050,175,474309,3.547700E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(210,5050,200,570199,3.564800E-10,2,type2filedir));

	MCpoints.push_back(new MCpoint(235,5050,150,270220,2.299700E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(235,5050,175,387713,2.304700E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(235,5050,200,493440,2.316200E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(235,5050,225,578117,2.329800E-10,2,type2filedir));

	MCpoints.push_back(new MCpoint(260,5050,150,199989,1.514400E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(260,5050,175,304227,1.515400E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(260,5050,200,410061,1.517300E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(260,5050,225,503790,1.522400E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(260,5050,250,578579,1.524700E-10,2,type2filedir));

	MCpoints.push_back(new MCpoint(285,5050,150,157355,1.117200E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(285,5050,175,230270,1.006400E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(285,5050,200,326837,1.005900E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(285,5050,225,424092,1.010400E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(285,5050,250,507641,1.010800E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(285,5050,275,577679,1.015100E-10,2,type2filedir));

	MCpoints.push_back(new MCpoint(310,5050,150,158669,1.114100E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint(310,5050,175,170054,6.781000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(310,5050,200,252237,6.769000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(310,5050,225,343047,6.785000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(310,5050,250,431087,6.804000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(310,5050,275,509904,6.828000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(310,5050,300,575064,6.848000E-11,2,type2filedir));

	MCpoints.push_back(new MCpoint(335,5050,150,126632,8.548000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(335,5050,175,188737,7.603000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(335,5050,200,189411,4.595000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(335,5050,225,267964,4.611000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(335,5050,250,352529,4.627000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(335,5050,275,434645,4.637000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(335,5050,300,507500,4.648000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(335,5050,325,569324,4.660000E-11,2,type2filedir));

	MCpoints.push_back(new MCpoint(360,5050,150,97439,6.375000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(360,5050,175,154852,5.949000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(360,5050,200,211492,5.197000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(360,5050,225,204946,3.176300E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(360,5050,250,279389,3.177100E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(360,5050,275,359063,3.197400E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(360,5050,300,434246,3.186600E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(360,5050,325,503935,3.201300E-11,2,type2filedir));

	MCpoints.push_back(new MCpoint(385,5050,150,73291,4.672000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(385,5050,175,120794,4.463000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(385,5050,200,177876,4.155000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(385,5050,225,230992,3.609500E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(385,5050,250,216866,2.217900E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(385,5050,275,287578,2.2159E-11,2,type2filedir)); //pothole
		//385 5050 275    261 76385 5.889E-12 264 211193 1.627E-11
	MCpoints.push_back(new MCpoint(385,5050,300,360822,2.220600E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(385,5050,325,431618,2.219600E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(385,5050,375,556384,2.239200E-11,2,type2filedir));

	MCpoints.push_back(new MCpoint(410,5050,150,54347,3.422800E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(410,5050,175,93212,3.333300E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(410,5050,200,141430,3.160200E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(410,5050,225,196822,2.928200E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(410,5050,250,242846,2.508500E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(410,5050,275,224621,1.559000E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(410,5050,300,291037,1.5553E-11,2,type2filedir));//pothole
		//410 5050 300    261 81540 4.353E-12 264 209497 1.120E-11
	MCpoints.push_back(new MCpoint(410,5050,325,362130,1.567700E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(410,5050,375,492187,1.569700E-11,2,type2filedir));

	MCpoints.push_back(new MCpoint(460,5050,150,29968,1.828800E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(460,5050,175,52518,1.798100E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(460,5050,200,83617,1.750500E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(460,5050,225,124608,1.701900E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(460,5050,250,173193,1.623600E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(460,5050,275,223482,1.501100E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(460,5050,300,257910,1.253900E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint(460,5050,325,233511,7.94E-12,2,type2filedir));//pothole
		//460 5050 325    261 71445 2.431E-12 264 162066 5.509E-12
	MCpoints.push_back(new MCpoint(460,5050,375,356439,7.964000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(460,5050,425,477281,7.990000E-12,2,type2filedir));

	MCpoints.push_back(new MCpoint(510,5050,150,16458,9.977000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,175,29197,9.767000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,200,47923,9.670000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,225,73526,9.518000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,250,107450,9.321000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,275,147890,9.003000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,300,193976,8.590000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,325,239791,7.912000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,375,235742,4.184000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,425,348621,4.205000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(510,5050,475,462418,4.233000E-12,2,type2filedir));

	MCpoints.push_back(new MCpoint(610,5050,150,5303,3.137000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(610,5050,175,9538,3.129000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(610,5050,200,15900,3.117000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(610,5050,225,25165,3.090000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(610,5050,250,37546,3.050000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(610,5050,275,55006,3.020000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(610,5050,300,76691,2.964000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(610,5050,325,104067,2.906000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(610,5050,375,174737,2.756000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(610,5050,425,250859,2.397900E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(610,5050,475,230089,1.272900E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(610,5050,525,327968,1.275700E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(610,5050,575,428587,1.280900E-12,2,type2filedir));

	MCpoints.push_back(new MCpoint(660,5050,150,3100,1.849800E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(660,5050,175,5589,1.830900E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(660,5050,200,9290,1.824700E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(660,5050,225,14772,1.797000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(660,5050,250,22199,1.767200E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(660,5050,275,32615,1.757300E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(660,5050,300,46432,1.750900E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(660,5050,325,64420,1.727100E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(660,5050,375,113342,1.667200E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(660,5050,425,179865,1.569200E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(660,5050,475,248936,1.360300E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(660,5050,525,224446,7.247000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(660,5050,575,315236,7.269000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(660,5050,625,412770,7.287000E-13,2,type2filedir));

	MCpoints.push_back(new MCpoint(710,5050,150,1824,1.100600E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(710,5050,175,3209,1.058400E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(710,5050,200,5586,1.076400E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(710,5050,225,8665,1.052700E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(710,5050,250,13317,1.054600E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(710,5050,275,19244,1.031200E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(710,5050,300,28008,1.035000E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(710,5050,325,39293,1.027200E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(710,5050,375,71372,1.002200E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint(710,5050,425,119341,9.691000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(710,5050,475,183097,9.172000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(710,5050,525,246486,7.922000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(710,5050,575,218104,4.216000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(710,5050,625,303717,4.221000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(710,5050,675,397887,4.250000E-13,2,type2filedir));

	MCpoints.push_back(new MCpoint(810,5050,150,655,3.878000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(810,5050,175,1202,3.955000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(810,5050,200,2117,4.054000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(810,5050,225,3057,3.728000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(810,5050,250,4889,3.820000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(810,5050,275,7290,3.846000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(810,5050,300,10640,3.850000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(810,5050,325,14576,3.746000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(810,5050,375,27624,3.707000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(810,5050,425,47889,3.614000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(810,5050,475,79872,3.547000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(810,5050,525,124846,3.438000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(810,5050,575,182352,3.251000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(810,5050,625,236020,2.787000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(810,5050,675,204040,1.491900E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(810,5050,725,281923,1.496300E-13,2,type2filedir));

	MCpoints.push_back(new MCpoint(910,5050,150,273,1.535000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(910,5050,175,428,1.418300E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(910,5050,200,743,1.489600E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(910,5050,225,1174,1.397200E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(910,5050,250,1859,1.452800E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(910,5050,275,2664,1.422400E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(910,5050,300,4065,1.466000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(910,5050,325,5575,1.422300E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(910,5050,375,10630,1.411000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(910,5050,425,19062,1.393600E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(910,5050,475,32456,1.375100E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(910,5050,525,53002,1.347900E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(910,5050,575,82939,1.313900E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(910,5050,625,124743,1.278400E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(910,5050,675,175995,1.204600E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(910,5050,725,223114,1.032000E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint(910,5050,825,260364,5.566000E-14,2,type2filedir));

	MCpoints.push_back(new MCpoint(1010,5050,150,103,5.866000E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,175,152,5.656000E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,200,302,5.672000E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,225,452,5.414000E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,250,767,5.825000E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,275,1097,5.649000E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,300,1585,5.695000E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,325,2183,5.707000E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,375,4236,5.593000E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,425,7447,5.451000E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,475,13091,5.459000E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,525,21596,5.326000E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,575,35208,5.341000E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,625,54623,5.192000E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,675,83218,5.117000E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,725,120924,4.910000E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,825,209119,3.952000E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint(1010,5050,925,241679,2.136000E-14,2,type2filedir));

	MCpoints.push_back(new MCpoint(1510,5050,1025,20172,1.454600E-15,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,1125,44090,1.444400E-15,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,1225,94283,1.447400E-15,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,150,0,6.571000E-17,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,175,5,1.720800E-15,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,200,3,8.604000E-16,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,225,8,1.069400E-15,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,250,5,6.351000E-16,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,275,14,7.109000E-16,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,300,17,7.130000E-16,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,325,32,7.774000E-16,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,375,56,8.305000E-16,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,425,91,6.303000E-16,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,475,180,7.477000E-16,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,525,288,6.668000E-16,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,575,443,6.731000E-16,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,625,739,6.882000E-16,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,675,1168,6.532000E-16,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,725,1806,6.418000E-16,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,825,4011,6.115000E-16,2,type2filedir));
	MCpoints.push_back(new MCpoint(1510,5050,925,9487,6.106000E-16,2,type2filedir));

	MCpoints.push_back(new MCpoint(2010,5050,1025,250,1.776100E-17,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,1125,523,1.690500E-17,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,1225,1173,1.615000E-17,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,150,0,0.000000E+00,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,1525,12048,1.496300E-17,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,175,0,0.000000E+00,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,200,0,1.240000E-21,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,225,0,3.547009E-21,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,250,0,2.252940E-17,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,275,0,4.229239E-18,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,300,0,1.190000E-18,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,325,1,3.531000E-17,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,375,0,5.475000E-18,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,425,1,6.205000E-18,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,475,1,1.206400E-17,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,525,6,9.339000E-18,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,575,5,7.601000E-18,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,625,8,9.516000E-18,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,675,9,5.345000E-18,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,725,27,8.027000E-18,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,825,50,8.279000E-18,2,type2filedir));
	MCpoints.push_back(new MCpoint(2010,5050,925,119,7.914000E-18,2,type2filedir));

	string type3filedir = "/eos/uscms/store/user/abarker/MC/Sunil/";
	ngen = 5000;
	//br's last updated June 12, 2013
	float bbaa_br = 2*0.561*0.00229;
	float wwaa_br = 2*0.231*0.00229;
	float zzaa_br = 2*0.0289*0.00229;
	float ttaa_br = 2*0.0615*0.00229;
	float mb_per_pb = 1e-9;
//	float hZ_aaZ_br = 0.00229;
//	float hW_aaW_br = 0.00229;
		//see https://twiki.cern.ch/twiki/bin/viewauth/CMS/Electrohiggs for branching ratios.


		//    ____  __   __  ____          _ __  _____
		//   / __ \/ /__/ / / __/_ _____  (_) / / ___/______ ____
		//  / /_/ / / _  / _\ \/ // / _ \/ / / / /__/ __/ _ `/ _ \
		//  \____/_/\_,_/ /___/\_,_/_//_/_/_/  \___/_/  \_,_/ .__/
		//                                                 /_/
	
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

		//     ___       __
		//    / _ \___ _/ /____ _
		//   / // / _ `/ __/ _ `/
		//  /____/\_,_/\__/\_,_/
		//
	
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

		//       ______              __ ___               _
		//    __/_  __/__  ___  ____/ // (_)__ ____ ____ (_)__  ___
		//   (_-</ / / _ \/ _ \/___/ _  / / _ `/ _ `(_-</ / _ \/ _ \
		//  /___/_/  \___/ .__/   /_//_/_/\_, /\_, /___/_/_//_/\___/
		//              /_/              /___//___/

		//Cross sections are Prospino NLO

		//type 10 = bbaa    aa = gamma gamma
	string type10_Strongbbaa_filedir = "/eos/uscms/store/user/lpcpjm/PrivateMC/FastSim/533p3_full/ewkinoLHEs/StopHiggs/bbaa/SusyNtuple/cms533v1_v1/";
	int ngen_bbaa = 6000;
		//tree_StopHiggs_stop200_chargino150_15_hh_bbaa.root

	MCpoints.push_back(new MCpoint(200,-1,150,ngen_bbaa,18.5245*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.9147;
	MCpoints.push_back(new MCpoint(200,-1,175,ngen_bbaa,18.5245*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.9147;
	MCpoints.push_back(new MCpoint(225,-1,150,ngen_bbaa,9.90959*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.9662;
	MCpoints.push_back(new MCpoint(225,-1,175,ngen_bbaa,9.90959*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.9662;
	MCpoints.push_back(new MCpoint(225,-1,200,ngen_bbaa,9.90959*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.9662;
	MCpoints.push_back(new MCpoint(225,-1,215,ngen_bbaa,9.90959*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.9662;
	MCpoints.push_back(new MCpoint(250,-1,135,ngen_bbaa,5.57596*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,150,ngen_bbaa,5.57596*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,175,ngen_bbaa,5.57596*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,200,ngen_bbaa,5.57596*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,225,ngen_bbaa,5.57596*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,240,ngen_bbaa,5.57596*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(275,-1,135,ngen_bbaa,3.2781*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,150,ngen_bbaa,3.2781*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,175,ngen_bbaa,3.2781*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,200,ngen_bbaa,3.2781*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,225,ngen_bbaa,3.2781*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,250,ngen_bbaa,3.2781*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,265,ngen_bbaa,3.2781*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(300,-1,135,ngen_bbaa,1.99608*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,150,ngen_bbaa,1.99608*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,175,ngen_bbaa,1.99608*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,200,ngen_bbaa,1.99608*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,225,ngen_bbaa,1.99608*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,250,ngen_bbaa,1.99608*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,275,ngen_bbaa,1.99608*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,290,ngen_bbaa,1.99608*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(325,-1,135,ngen_bbaa,1.25277*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,150,ngen_bbaa,1.25277*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,175,ngen_bbaa,1.25277*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,200,ngen_bbaa,1.25277*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,225,ngen_bbaa,1.25277*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,250,ngen_bbaa,1.25277*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,275,ngen_bbaa,1.25277*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,300,ngen_bbaa,1.25277*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,315,ngen_bbaa,1.25277*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(350,-1,135,ngen_bbaa,0.807323*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,150,ngen_bbaa,0.807323*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,175,ngen_bbaa,0.807323*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,200,ngen_bbaa,0.807323*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,225,ngen_bbaa,0.807323*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,250,ngen_bbaa,0.807323*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,275,ngen_bbaa,0.807323*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,300,ngen_bbaa,0.807323*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(375,-1,135,ngen_bbaa,0.576882*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2712;
	MCpoints.push_back(new MCpoint(400,-1,135,ngen_bbaa,0.35683*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,150,ngen_bbaa,0.35683*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,200,ngen_bbaa,0.35683*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,250,ngen_bbaa,0.35683*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,300,ngen_bbaa,0.35683*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,350,ngen_bbaa,0.35683*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(425,-1,135,ngen_bbaa,0.243755*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.0504;
	MCpoints.push_back(new MCpoint(450,-1,150,ngen_bbaa,0.169668*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(450,-1,200,ngen_bbaa,0.169668*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(450,-1,250,ngen_bbaa,0.169668*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(450,-1,300,ngen_bbaa,0.169668*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(450,-1,350,ngen_bbaa,0.169668*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(500,-1,150,ngen_bbaa,0.0855847*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.9611;
	MCpoints.push_back(new MCpoint(500,-1,200,ngen_bbaa,0.0855847*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.9611;
	MCpoints.push_back(new MCpoint(500,-1,250,ngen_bbaa,0.0855847*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.9611;
	MCpoints.push_back(new MCpoint(500,-1,300,ngen_bbaa,0.0855847*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.9611;
	MCpoints.push_back(new MCpoint(500,-1,350,ngen_bbaa,0.0855847*bbaa_br*mb_per_pb,10,type10_Strongbbaa_filedir)); MCpoints.back()->cs_uncert=14.9611;

	
	string type11_Strongwwaa_filedir = "/eos/uscms/store/user/lpcpjm/PrivateMC/FastSim/533p3_full/ewkinoLHEs/StopHiggs/wwaa/SusyNtuple/cms533v1_v1/";
	int ngen_wwaa = 3000;
		//tree_StopHiggs_stop200_chargino150_5_hh_wwaa.root
	MCpoints.push_back(new MCpoint(200,-1,150,ngen_wwaa,18.5245*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.9147;
	MCpoints.push_back(new MCpoint(200,-1,175,ngen_wwaa,18.5245*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.9147;
	MCpoints.push_back(new MCpoint(225,-1,150,ngen_wwaa,9.90959*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.9662;
	MCpoints.push_back(new MCpoint(225,-1,175,ngen_wwaa,9.90959*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.9662;
	MCpoints.push_back(new MCpoint(225,-1,200,ngen_wwaa,9.90959*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.9662;
	MCpoints.push_back(new MCpoint(225,-1,215,ngen_wwaa,9.90959*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.9662;
	MCpoints.push_back(new MCpoint(250,-1,135,ngen_wwaa,5.57596*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,150,ngen_wwaa,5.57596*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,175,ngen_wwaa,5.57596*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,200,ngen_wwaa,5.57596*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,225,ngen_wwaa,5.57596*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,240,ngen_wwaa,5.57596*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(275,-1,135,ngen_wwaa,3.2781*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,150,ngen_wwaa,3.2781*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,175,ngen_wwaa,3.2781*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,200,ngen_wwaa,3.2781*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,225,ngen_wwaa,3.2781*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,250,ngen_wwaa,3.2781*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,265,ngen_wwaa,3.2781*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(300,-1,135,ngen_wwaa,1.99608*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,150,ngen_wwaa,1.99608*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,175,ngen_wwaa,1.99608*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,200,ngen_wwaa,1.99608*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,225,ngen_wwaa,1.99608*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,250,ngen_wwaa,1.99608*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,275,ngen_wwaa,1.99608*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,290,ngen_wwaa,1.99608*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(325,-1,135,ngen_wwaa,1.25277*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,150,ngen_wwaa,1.25277*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,175,ngen_wwaa,1.25277*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,200,ngen_wwaa,1.25277*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,225,ngen_wwaa,1.25277*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,250,ngen_wwaa,1.25277*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,275,ngen_wwaa,1.25277*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,300,ngen_wwaa,1.25277*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,315,ngen_wwaa,1.25277*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(350,-1,135,ngen_wwaa,0.807323*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,150,ngen_wwaa,0.807323*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,175,ngen_wwaa,0.807323*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,200,ngen_wwaa,0.807323*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,225,ngen_wwaa,0.807323*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,250,ngen_wwaa,0.807323*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,275,ngen_wwaa,0.807323*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,300,ngen_wwaa,0.807323*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(375,-1,135,ngen_wwaa,0.576882*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2712;
	MCpoints.push_back(new MCpoint(400,-1,135,ngen_wwaa,0.35683*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,150,ngen_wwaa,0.35683*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,200,ngen_wwaa,0.35683*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,250,ngen_wwaa,0.35683*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,300,ngen_wwaa,0.35683*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,350,ngen_wwaa,0.35683*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(425,-1,135,ngen_wwaa,0.243755*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.0504;
	MCpoints.push_back(new MCpoint(450,-1,150,ngen_wwaa,0.169668*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(450,-1,200,ngen_wwaa,0.169668*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(450,-1,250,ngen_wwaa,0.169668*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(450,-1,300,ngen_wwaa,0.169668*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(450,-1,350,ngen_wwaa,0.169668*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(500,-1,150,ngen_wwaa,0.0855847*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.9611;
	MCpoints.push_back(new MCpoint(500,-1,200,ngen_wwaa,0.0855847*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.9611;
	MCpoints.push_back(new MCpoint(500,-1,250,ngen_wwaa,0.0855847*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.9611;
	MCpoints.push_back(new MCpoint(500,-1,300,ngen_wwaa,0.0855847*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.9611;
	MCpoints.push_back(new MCpoint(500,-1,350,ngen_wwaa,0.0855847*wwaa_br*mb_per_pb,11,type11_Strongwwaa_filedir)); MCpoints.back()->cs_uncert=14.9611;

	string type12_Strongzzaa_filedir = "/eos/uscms/store/user/lpcpjm/PrivateMC/FastSim/533p3_full/ewkinoLHEs/StopHiggs/zzaa/SusyNtuple/cms533v1_v1/";
		//tree_StopHiggs_stop200_chargino150_10_hh_zzaa.root
	int ngen_zzaa = 300;
	MCpoints.push_back(new MCpoint(200,-1,150,ngen_zzaa,18.5245*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.9147;
	MCpoints.push_back(new MCpoint(200,-1,175,ngen_zzaa,18.5245*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.9147;
	MCpoints.push_back(new MCpoint(225,-1,150,ngen_zzaa,9.90959*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.9662;
	MCpoints.push_back(new MCpoint(225,-1,175,ngen_zzaa,9.90959*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.9662;
	MCpoints.push_back(new MCpoint(225,-1,200,ngen_zzaa,9.90959*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.9662;
	MCpoints.push_back(new MCpoint(225,-1,215,ngen_zzaa,9.90959*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.9662;
	MCpoints.push_back(new MCpoint(250,-1,135,ngen_zzaa,5.57596*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,150,ngen_zzaa,5.57596*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,175,ngen_zzaa,5.57596*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,200,ngen_zzaa,5.57596*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,225,ngen_zzaa,5.57596*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,240,ngen_zzaa,5.57596*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(275,-1,135,ngen_zzaa,3.2781*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,150,ngen_zzaa,3.2781*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,175,ngen_zzaa,3.2781*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,200,ngen_zzaa,3.2781*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,225,ngen_zzaa,3.2781*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,250,ngen_zzaa,3.2781*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,265,ngen_zzaa,3.2781*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(300,-1,135,ngen_zzaa,1.99608*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,150,ngen_zzaa,1.99608*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,175,ngen_zzaa,1.99608*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,200,ngen_zzaa,1.99608*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,225,ngen_zzaa,1.99608*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,250,ngen_zzaa,1.99608*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,275,ngen_zzaa,1.99608*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,290,ngen_zzaa,1.99608*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(325,-1,135,ngen_zzaa,1.25277*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,150,ngen_zzaa,1.25277*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,175,ngen_zzaa,1.25277*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,200,ngen_zzaa,1.25277*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,225,ngen_zzaa,1.25277*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,250,ngen_zzaa,1.25277*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,275,ngen_zzaa,1.25277*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,300,ngen_zzaa,1.25277*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,315,ngen_zzaa,1.25277*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(350,-1,135,ngen_zzaa,0.807323*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,150,ngen_zzaa,0.807323*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,175,ngen_zzaa,0.807323*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,200,ngen_zzaa,0.807323*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,225,ngen_zzaa,0.807323*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,250,ngen_zzaa,0.807323*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,275,ngen_zzaa,0.807323*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,300,ngen_zzaa,0.807323*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(375,-1,135,ngen_zzaa,0.576882*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2712;
	MCpoints.push_back(new MCpoint(400,-1,135,ngen_zzaa,0.35683*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,150,ngen_zzaa,0.35683*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,200,ngen_zzaa,0.35683*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,250,ngen_zzaa,0.35683*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,300,ngen_zzaa,0.35683*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,350,ngen_zzaa,0.35683*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(425,-1,135,ngen_zzaa,0.243755*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.0504;
	MCpoints.push_back(new MCpoint(450,-1,150,ngen_zzaa,0.169668*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(450,-1,200,ngen_zzaa,0.169668*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(450,-1,250,ngen_zzaa,0.169668*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(450,-1,300,ngen_zzaa,0.169668*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(450,-1,350,ngen_zzaa,0.169668*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(500,-1,150,ngen_zzaa,0.0855847*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.9611;
	MCpoints.push_back(new MCpoint(500,-1,200,ngen_zzaa,0.0855847*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.9611;
	MCpoints.push_back(new MCpoint(500,-1,250,ngen_zzaa,0.0855847*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.9611;
	MCpoints.push_back(new MCpoint(500,-1,300,ngen_zzaa,0.0855847*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.9611;
	MCpoints.push_back(new MCpoint(500,-1,350,ngen_zzaa,0.0855847*zzaa_br*mb_per_pb,12,type12_Strongzzaa_filedir)); MCpoints.back()->cs_uncert=14.9611;

	string type13_Strongttaa_filedir = "/eos/uscms/store/user/lpcpjm/PrivateMC/FastSim/533p3_full/ewkinoLHEs/StopHiggs/ttaa/SusyNtuple/cms533v1_v1/";
		//tree_StopHiggs_stop200_chargino150_13_hh_ttaa.root
	int ngen_ttaa = 600;
	MCpoints.push_back(new MCpoint(200,-1,150,ngen_ttaa,18.5245*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.9147;
	MCpoints.push_back(new MCpoint(200,-1,175,ngen_ttaa,18.5245*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.9147;
	MCpoints.push_back(new MCpoint(225,-1,150,ngen_ttaa,9.90959*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.9662;
	MCpoints.push_back(new MCpoint(225,-1,175,ngen_ttaa,9.90959*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.9662;
	MCpoints.push_back(new MCpoint(225,-1,200,ngen_ttaa,9.90959*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.9662;
	MCpoints.push_back(new MCpoint(225,-1,215,ngen_ttaa,9.90959*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.9662;
	MCpoints.push_back(new MCpoint(250,-1,135,ngen_ttaa,5.57596*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,150,ngen_ttaa,5.57596*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,175,ngen_ttaa,5.57596*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,200,ngen_ttaa,5.57596*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,225,ngen_ttaa,5.57596*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(250,-1,240,ngen_ttaa,5.57596*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.7529;
	MCpoints.push_back(new MCpoint(275,-1,135,ngen_ttaa,3.2781*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,150,ngen_ttaa,3.2781*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,175,ngen_ttaa,3.2781*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,200,ngen_ttaa,3.2781*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,225,ngen_ttaa,3.2781*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,250,ngen_ttaa,3.2781*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(275,-1,265,ngen_ttaa,3.2781*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.7341;
	MCpoints.push_back(new MCpoint(300,-1,135,ngen_ttaa,1.99608*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,150,ngen_ttaa,1.99608*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,175,ngen_ttaa,1.99608*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,200,ngen_ttaa,1.99608*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,225,ngen_ttaa,1.99608*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,250,ngen_ttaa,1.99608*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,275,ngen_ttaa,1.99608*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(300,-1,290,ngen_ttaa,1.99608*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.6905;
	MCpoints.push_back(new MCpoint(325,-1,135,ngen_ttaa,1.25277*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,150,ngen_ttaa,1.25277*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,175,ngen_ttaa,1.25277*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,200,ngen_ttaa,1.25277*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,225,ngen_ttaa,1.25277*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,250,ngen_ttaa,1.25277*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,275,ngen_ttaa,1.25277*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,300,ngen_ttaa,1.25277*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(325,-1,315,ngen_ttaa,1.25277*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2875;
	MCpoints.push_back(new MCpoint(350,-1,135,ngen_ttaa,0.807323*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,150,ngen_ttaa,0.807323*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,175,ngen_ttaa,0.807323*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,200,ngen_ttaa,0.807323*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,225,ngen_ttaa,0.807323*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,250,ngen_ttaa,0.807323*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,275,ngen_ttaa,0.807323*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(350,-1,300,ngen_ttaa,0.807323*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.3597;
	MCpoints.push_back(new MCpoint(375,-1,135,ngen_ttaa,0.576882*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2712;
	MCpoints.push_back(new MCpoint(400,-1,135,ngen_ttaa,0.35683*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,150,ngen_ttaa,0.35683*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,200,ngen_ttaa,0.35683*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,250,ngen_ttaa,0.35683*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,300,ngen_ttaa,0.35683*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(400,-1,350,ngen_ttaa,0.35683*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2848;
	MCpoints.push_back(new MCpoint(425,-1,135,ngen_ttaa,0.243755*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.0504;
	MCpoints.push_back(new MCpoint(450,-1,150,ngen_ttaa,0.169668*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(450,-1,200,ngen_ttaa,0.169668*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(450,-1,250,ngen_ttaa,0.169668*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(450,-1,300,ngen_ttaa,0.169668*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(450,-1,350,ngen_ttaa,0.169668*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.2368;
	MCpoints.push_back(new MCpoint(500,-1,150,ngen_ttaa,0.0855847*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.9611;
	MCpoints.push_back(new MCpoint(500,-1,200,ngen_ttaa,0.0855847*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.9611;
	MCpoints.push_back(new MCpoint(500,-1,250,ngen_ttaa,0.0855847*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.9611;
	MCpoints.push_back(new MCpoint(500,-1,300,ngen_ttaa,0.0855847*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.9611;
	MCpoints.push_back(new MCpoint(500,-1,350,ngen_ttaa,0.0855847*ttaa_br*mb_per_pb,13,type13_Strongttaa_filedir)); MCpoints.back()->cs_uncert=14.9611;


		//     ______        __           __ ___
		//    / __/ /__ ____/ /________  / // (_)__ ____ ____
		//   / _// / -_) __/ __/ __/ _ \/ _  / / _ `/ _ `(_-<
		//  /___/_/\__/\__/\__/_/  \___/_//_/_/\_, /\_, /___/
		//
		//These use Higgsino-like chargino. Cross sections are Prospino NLO

		//see https://twiki.cern.ch/twiki/bin/view/CMS/NaturalSUSYHiggsinoNLSP for electrohiggs branching ratios and cs
		//and see https://twiki.cern.ch/twiki/bin/viewauth/CMS/Electrohiggs for numbers of generated events.

		//pat: these cross sections are bogus!!! They're something like 10% low. 

	string type20_Weakbbaa_filedir = "/eos/uscms/store/user/lpcpjm/PrivateMC/FastSim/533p3_full/ewkinoLHEs/ElectroHiggs/bbaa/SusyNtuple/cms533v1_v1/";
		//tree_ElectroHiggs_chargino135_15_hh_bbaa.root
	float ngen_weak_bbaa = 12000;
	MCpoints.push_back(new MCpoint(-1,-1,135,ngen_weak_bbaa,1.819*bbaa_br*mb_per_pb,20,type20_Weakbbaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,150,ngen_weak_bbaa,1.2176*bbaa_br*mb_per_pb,20,type20_Weakbbaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,175,ngen_weak_bbaa,0.6682*bbaa_br*mb_per_pb,20,type20_Weakbbaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,200,ngen_weak_bbaa,0.3943*bbaa_br*mb_per_pb,20,type20_Weakbbaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,215,ngen_weak_bbaa,0.2942*bbaa_br*mb_per_pb,20,type20_Weakbbaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,225,ngen_weak_bbaa,0.2446*bbaa_br*mb_per_pb,20,type20_Weakbbaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,240,ngen_weak_bbaa,0.18694*bbaa_br*mb_per_pb,20,type20_Weakbbaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,250,ngen_weak_bbaa,0.1571*bbaa_br*mb_per_pb,20,type20_Weakbbaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,265,ngen_weak_bbaa,0.12241*bbaa_br*mb_per_pb,20,type20_Weakbbaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,275,ngen_weak_bbaa,0.1044*bbaa_br*mb_per_pb,20,type20_Weakbbaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,290,ngen_weak_bbaa,0.08318*bbaa_br*mb_per_pb,20,type20_Weakbbaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,300,ngen_weak_bbaa,0.071*bbaa_br*mb_per_pb,20,type20_Weakbbaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,315,ngen_weak_bbaa,0.05746*bbaa_br*mb_per_pb,20,type20_Weakbbaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,350,ngen_weak_bbaa,0.0353*bbaa_br*mb_per_pb,20,type20_Weakbbaa_filedir));

	string type21_Weakwwaa_filedir = "/eos/uscms/store/user/lpcpjm/PrivateMC/FastSim/533p3_full/ewkinoLHEs/ElectroHiggs/wwaa/SusyNtuple/cms533v1_v1/";
		//tree_ElectroHiggs_chargino150_5_hh_wwaa.root
	float ngen_weak_wwaa = 4600;
	MCpoints.push_back(new MCpoint(-1,-1,135,ngen_weak_wwaa,1.819*wwaa_br*mb_per_pb,21,type21_Weakwwaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,150,ngen_weak_wwaa,1.2176*wwaa_br*mb_per_pb,21,type21_Weakwwaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,175,ngen_weak_wwaa,0.6682*wwaa_br*mb_per_pb,21,type21_Weakwwaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,200,ngen_weak_wwaa,0.3943*wwaa_br*mb_per_pb,21,type21_Weakwwaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,215,ngen_weak_wwaa,0.2942*wwaa_br*mb_per_pb,21,type21_Weakwwaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,225,ngen_weak_wwaa,0.2446*wwaa_br*mb_per_pb,21,type21_Weakwwaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,240,ngen_weak_wwaa,0.18694*wwaa_br*mb_per_pb,21,type21_Weakwwaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,250,ngen_weak_wwaa,0.1571*wwaa_br*mb_per_pb,21,type21_Weakwwaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,265,ngen_weak_wwaa,0.12241*wwaa_br*mb_per_pb,21,type21_Weakwwaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,275,ngen_weak_wwaa,0.1044*wwaa_br*mb_per_pb,21,type21_Weakwwaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,290,ngen_weak_wwaa,0.08318*wwaa_br*mb_per_pb,21,type21_Weakwwaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,300,ngen_weak_wwaa,0.071*wwaa_br*mb_per_pb,21,type21_Weakwwaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,315,ngen_weak_wwaa,0.05746*wwaa_br*mb_per_pb,21,type21_Weakwwaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,350,ngen_weak_wwaa,0.0353*wwaa_br*mb_per_pb,21,type21_Weakwwaa_filedir));

	string type22_Weakzzaa_filedir = "/eos/uscms/store/user/lpcpjm/PrivateMC/FastSim/533p3_full/ewkinoLHEs/ElectroHiggs/zzaa/SusyNtuple/cms533v1_v1/";
		//tree_ElectroHiggs_chargino240_10_hh_zzaa.root
	float ngen_weak_zzaa = 600;
	MCpoints.push_back(new MCpoint(-1,-1,135,ngen_weak_zzaa,1.819*zzaa_br*mb_per_pb,22,type22_Weakzzaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,150,ngen_weak_zzaa,1.2176*zzaa_br*mb_per_pb,22,type22_Weakzzaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,175,ngen_weak_zzaa,0.6682*zzaa_br*mb_per_pb,22,type22_Weakzzaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,200,ngen_weak_zzaa,0.3943*zzaa_br*mb_per_pb,22,type22_Weakzzaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,215,ngen_weak_zzaa,0.2942*zzaa_br*mb_per_pb,22,type22_Weakzzaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,225,ngen_weak_zzaa,0.2446*zzaa_br*mb_per_pb,22,type22_Weakzzaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,240,ngen_weak_zzaa,0.18694*zzaa_br*mb_per_pb,22,type22_Weakzzaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,250,ngen_weak_zzaa,0.1571*zzaa_br*mb_per_pb,22,type22_Weakzzaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,265,ngen_weak_zzaa,0.12241*zzaa_br*mb_per_pb,22,type22_Weakzzaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,275,ngen_weak_zzaa,0.1044*zzaa_br*mb_per_pb,22,type22_Weakzzaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,290,ngen_weak_zzaa,0.08318*zzaa_br*mb_per_pb,22,type22_Weakzzaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,300,ngen_weak_zzaa,0.071*zzaa_br*mb_per_pb,22,type22_Weakzzaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,315,ngen_weak_zzaa,0.05746*zzaa_br*mb_per_pb,22,type22_Weakzzaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,350,ngen_weak_zzaa,0.0353*zzaa_br*mb_per_pb,22,type22_Weakzzaa_filedir));


	string type23_Weakttaa_filedir = "/eos/uscms/store/user/lpcpjm/PrivateMC/FastSim/533p3_full/ewkinoLHEs/ElectroHiggs/ttaa/SusyNtuple/cms533v1_v1/";
		//tree_ElectroHiggs_chargino240_13_hh_ttaa.root
	float ngen_weak_ttaa = 1200;
	MCpoints.push_back(new MCpoint(-1,-1,135,ngen_weak_ttaa,1.819*ttaa_br*mb_per_pb,23,type23_Weakttaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,150,ngen_weak_ttaa,1.2176*ttaa_br*mb_per_pb,23,type23_Weakttaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,175,ngen_weak_ttaa,0.6682*ttaa_br*mb_per_pb,23,type23_Weakttaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,200,ngen_weak_ttaa,0.3943*ttaa_br*mb_per_pb,23,type23_Weakttaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,215,ngen_weak_ttaa,0.2942*ttaa_br*mb_per_pb,23,type23_Weakttaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,225,ngen_weak_ttaa,0.2446*ttaa_br*mb_per_pb,23,type23_Weakttaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,240,ngen_weak_ttaa,0.18694*ttaa_br*mb_per_pb,23,type23_Weakttaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,250,ngen_weak_ttaa,0.1571*ttaa_br*mb_per_pb,23,type23_Weakttaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,265,ngen_weak_ttaa,0.12241*ttaa_br*mb_per_pb,23,type23_Weakttaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,275,ngen_weak_ttaa,0.1044*ttaa_br*mb_per_pb,23,type23_Weakttaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,290,ngen_weak_ttaa,0.08318*ttaa_br*mb_per_pb,23,type23_Weakttaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,300,ngen_weak_ttaa,0.071*ttaa_br*mb_per_pb,23,type23_Weakttaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,315,ngen_weak_ttaa,0.05746*ttaa_br*mb_per_pb,23,type23_Weakttaa_filedir));
	MCpoints.push_back(new MCpoint(-1,-1,350,ngen_weak_ttaa,0.0353*ttaa_br*mb_per_pb,23,type23_Weakttaa_filedir));


		//    ___ _        _           _    _                _____  _
		//   | __| |___ __| |_ _ _ ___| |_ (_)__ _ __ _ ___ |_  / || |
		//   | _|| / -_) _|  _| '_/ _ \ ' \| / _` / _` (_-<  / /| __ |
		//   |___|_\___\__|\__|_| \___/_||_|_\__, \__, /__/ /___|_||_|
		//                                   |___/|___/
		//coming someday
//	string type30_WeahHZ_hgg_filedir = "";
//	float ngen_weak_ttaa = 20000; //from Pat Zywicki, June 12, 2013,
		//but this is in conflict with what is listed on the EH twiki: https://twiki.cern.ch/twiki/bin/viewauth/CMS/Electrohiggs
//	MCpoints.push_back(new MCpoint(-1,-1,290,ngen_weak_ttaa,__insert_cs_here__*hZ_aaZ_br*mb_per_pb,30,type30_WeahHZ_hgg_filedir));
		//150-400 in steps of 25.
	
	

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

void printMCpoints(){
	std::vector<MCpoint*> MCpoints = setupMCpoints();
	printf("$M_{stop}$ & $M_{higgsino}$ & cross section (fb)\\\\ \n");
	printf("\\hline\n");
	for(int i=0; i<(int)MCpoints.size();i++){
		if(MCpoints[i]->type != 2) continue;
		printf("%i & %i & %.2E \\\\ \n",MCpoints[i]->Mstop,MCpoints[i]->Mhiggsino, MCpoints[i]->cs_fb());
	}
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

		//cout<<"setupMCpoint rx pointname "<<pointname<<endl;
	std::vector<MCpoint*> vp = setupMCpoints();//this segfaults!!
		//std::map<string, int> pmap = makemap(vp);
		//string s_pointname = pointname;
	bool foundit = false;
	std::vector<MCpoint*>::iterator it = vp.begin();
	MCpoint* thispoint = *it;// = vp[pmap[s_pointname]];//default nonsense value
	while (it != vp.end() ){
			//cout<<"comparing to "<<(*it)->pointName.c_str()<<endl;
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
	TString topo_fixed = topo.ReplaceAll('!','_');
	return "LimitCard_"+MCpointname+"_"+topo_fixed+"_"+kinvar+".txt";
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
		//	TString newname = MCpointname;
//	newname.ReplaceAll("_bbaa","");
//	newname.ReplaceAll("_zzaa","");
//	newname.ReplaceAll("_wwaa","");
//	newname.ReplaceAll("_ttaa","");
//	return "LimitResultBundle_"+newname+".txt";
}//Done writing? Yes. Debugged? No




#endif
