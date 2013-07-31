
	//
	//                                              _
	//                                           _/|X|\
	//                                         _/  |X| \
	//                                       _/    |X|  \
	//                                     _/      |X|   \
	//                                   _/        |X|    \
	//                                 _/          |X|     \
	//                               _/            |X|      \
	//                             _/              |X|       \
	//   _________________________/________________|X|________\_____[][][]
	//  /_\/_\/_\/_\/_\/_\/_\/_\/_\/_\/_\/_\/_\/_\/MM|_\/_\/_\/_\/_\[][][]
	//              | |                        /  |\/|              [][][]
	//              | |                       |'  |/\|              [][][]
	//              | |                       |___|\/|              [][][]
	//              | |                           |\/|
	//              | |                           |/\|
	//              | |                           |\/|
	//              | |                           |/\|
	//              | |                           |\/|
	//              (o)                           |/\|
	//               J                            |\/|
	//           ,__/_\__,                        |/\|
	//           |H(gg)+X|                        |\/|
	//           '-------'                        |/\|
	//                                            |\/|
	//                                            |/\|
	//                                            |\/|
	//                                            |/\|
	//            ______ .______         ___      .__   __.  _______
	//           /      ||   _  \       /   \     |  \ |  | |   ____|
	//          |  ,----'|  |_)  |     /  ^  \    |   \|  | |  |__
	//          |  |     |      /     /  /_\  \   |  . `  | |   __|
	//          |  `----.|  |\  \---./  _____  \  |  |\   | |  |____
	//           \______|| _| `.____/__/     \__\ |__| \__| |_______|
	// 
	//          Anthony Barker, 2013

#include "TFractionFitter.h"
#include "TAxis.h"
#include "TH1.h"
#include "TMath.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TFile.h"
#include "TTree.h"
#include "TVirtualFitter.h"
#include "TLegend.h"
#include <iostream>
#include "TF1.h"
#include "TLine.h"
	//#include "quicksave.C"
#include "CMSStyle.C"
#include "utilities.h"
#include "params_arg.h"
	//#include "params_minimal.h"

	//#include "params_reduced.h"
	//#include "params_arg.h"
#include<string.h>
#include<map>
#include "MCpoint.h"
#include "RetrieveLimit.C"
#include "TPaveText.h"
#include "TLatex.h"
#include "TColor.h"

using namespace std;
using namespace params;
TLegend* makeL1(float f1=0.652548,float f2=0.663899,float f3=0.852528,float f4=0.864219);
TLegend* makeL1_v2(float f1=0.19598,float f2=0.721154,float f3=0.395729,float f4=0.92033);
TLegend* makeL2(float f1=0.651267,float f2=0.660256,float f3=0.851246,float f4=0.860577);
void BkgDemo_Diplot(TCanvas* c, TH1F** h, TLegend* l1, TLegend* l2); //orphaned
	//void diphoMassPlot(TH1F* hdiPhoMass, TCanvas* canv, TF1* fitcurve);
	//void LoadHistSet(TH1F** h, TFile* fin, TString prefix);
void SaveCanvas(TCanvas * c, string fileNameAndDir, string FileTypes =  "crootpdfjpggifpngeps");
bool KinvarIsLimit(string kinvar);
//bool TopoIsLimit(string Topo);

typedef std::map<string,TH1F*> LableHist;
typedef std::map<string,LableHist> Lable2Hist;
	//typedef map<string,Lable2Hist> Lable3Hist;

typedef std::map<string,TH1F**> LableHistArr;
typedef std::map<string,LableHistArr> Lable2HistArr;
typedef std::map<string,Lable2HistArr> Lable3HistArr;

typedef std::map<string,float> Labledflaot;
typedef std::map<string,TFile*>   TFileMap;
typedef std::map<string,TFileMap> TFileMap2;

void format_plots_higgsino(){
	cout<<"hello world"<<endl;
	int nKinemVars = nKinemVars_all;
	string *s_KinemVars = s_KinemVars_all; //use all unless otherwise stated.
	CMSStyle();

		///////////////////////////// Switcehs //////////////////////////////////////
	int printlevel = 3;

	bool saveImages = true;
	bool writeRootFile = true;
	string savewhat = "ggifpdf";//ggifpdfeps
//	string savewhat = "ggifpdfepsjpgpng";//ggifpdfeps
	bool divideOutBinWidths = true;
	float nominalBinWidth = 10;//GeV, for those measured in GeV
	bool DrawLimits = true; //switch this off it it segfaults

		//which plots to produce
	bool makeDesignLinPlots = 0;
	bool makeDesignLogPlots = 0;

	bool makeSigcompFullLinPlots = 0;
	bool makeSigcompFullLogPlots = 0;
	bool makeSigComp1 = 0;
	bool makeSigComp1log = 0;

	bool makeBkgSubPlots = false; //keep this false
	bool makeTagToBkgRatPlots = false;//keep false
	bool makeNormPlots = false;//keep false
	bool makeExclusionPlots = 0;
	bool makeExclusionPlotsMinimal = 1;
	bool makeXSecPlot = 0;
	bool makeEffPlots = 0;
	bool makeDesignSummary = 0;

		///////////////////////////// File Work ///////////////////////////////////////
	/*Debug*/ if(printlevel > 0) cout << "Start File work" << endl;

		///INPUT FILES
		//const int nDataAndMcFiles = 3;
		//const int nDataAndMcFiles = 5;
	const int nDataAndMcFiles = 4;
	string Data = "Data";

	const int nchannels = 4;
	string channel[nchannels] = {"bbaa","wwaa","zzaa","ttaa"};

	MCpoint* MCpoints[nDataAndMcFiles][nchannels];//the 0th is going to be the data.
	/*
	 MCpoint is going to have the following structure: 
	 [0][0]  = data
	 [1][0] = st_###_mu_###_bbaa, [1][1] = st_###_mu_###_wwaa, [1][2] = st_###_mu_###_zzaa, [1][3] = st_###_mu_###_ttaa
	 [2][0] = st_###_mu_###_bbaa, [2][1] = st_###_mu_###_wwaa, [2][2] = st_###_mu_###_zzaa, [2][3] = st_###_mu_###_ttaa
	 ...
	 Then just promise to never call MCpoint[0][>0].
	 I don't fill the rest of the first row with pointers to data for fear that some bug may multiply the data by nDataAndMcFiles
	 */

		//	string indexNames[nDataAndMcFiles] = {Data,"st_200_mu_150_bbaa", "st_225_mu_215_bbaa",  "st_250_mu_150_bbaa"};
	string indexNames[nDataAndMcFiles] = {Data,"mu_135", "mu_250",  "mu_350"};
	//string indexNames[nDataAndMcFiles] = {Data,"st_200_mu_150", "st_225_mu_215",  "st_250_mu_150"};


		//setup MC points and acouple associated strings. 
//	string s_DataAndMcFiles[nDataAndMcFiles][nchannels];
//	string s_DataAndMcFiles_v4[nDataAndMcFiles][nchannels];
	for(int i=0;i<nDataAndMcFiles;i++){
		if(i==0){//do data
			printf("asking for %s\n",(indexNames[i]).data());
			MCpoints[i][0] = setupMCpoint(indexNames[i],"");
//			s_DataAndMcFiles[i][0] = MCpoints[i][0]->s_DataAndMcFiles;
//			s_DataAndMcFiles_v4[i][0] = MCpoints[i][0]->s_DataAndMcFiles_v4;
			continue;
		}
			//do MC
		for(int j=0;j<nchannels;j++){
			printf("asking for MCpoint %s\n",(indexNames[i]+"_"+channel[j]).data());
			MCpoints[i][j] = setupMCpoint(indexNames[i]+"_"+channel[j],"");
//			s_DataAndMcFiles[i][j] = MCpoints[i][j]->s_DataAndMcFiles;
//			s_DataAndMcFiles_v4[i][j] = MCpoints[i][j]->s_DataAndMcFiles_v4;
		}
	}

		///Fetch Limit Results
	Label2Lim* LimitContainers[nDataAndMcFiles-1];
	for (int i = 0; i<nDataAndMcFiles-1; i++) LimitContainers[i] = new Label2Lim();
		//	Label2Lim** LimitContainers = new Label2Lim[nDataAndMcFiles-1];//that's a pointer/array to a list of pointers.
	if (DrawLimits) {
		cout<<"Reach For Limit Files: Marko"<<endl;
		for (int i=1;i<nDataAndMcFiles;i++){
			cout<<"i "<<i<<endl;
			suckinfile(LimitContainers[i-1],(indexNames[i]+"_bbaa").data()); //index name indexes the mass point.
		}
		cout<<"Polo: Got all limit files"<<endl;
	}


		///Output File
	cout<<"try to make formatplots combined file"<<endl;
	TFile* fplots = new TFile(formatedplotsroot_combined.c_str(),"RECREATE");
	cout<<"that worked"<<endl;

	TFileMap2 PostAnaAnaFiles;//[point][channel]
	/*
	 Structure: 
	 [Data]:[Data]
	 [st_200_mu_150]:["bbaa","wwaa","zzaa","ttaa"]
	 [st_250_mu_150]:["bbaa","wwaa","zzaa","ttaa"]
	 ...
	 */
//	TFileMap MainAnaFiles;
	cout<<endl<<"Reading in data file "<<plotsAndBackground_data<<endl<<endl;

	cout<<"open post ana files"<<endl;
	for(int i=0;i<nDataAndMcFiles;i++){
		TFileMap temp;
		if (i==0) {
			cout<<"Try to open "<<MCpoints[0][0]->plotsAndBackground_mc.c_str()<<endl;
			temp[Data] = new TFile(MCpoints[0][0]->plotsAndBackground_mc.c_str());
		}
		else{
			for (int jchan=0; jchan<nchannels; jchan++) {
				cout<<"Try to open "<<MCpoints[i][jchan]->plotsAndBackground_mc.c_str()<<endl;
				temp[channel[jchan]]= new TFile(MCpoints[i][jchan]->plotsAndBackground_mc.c_str());
			}
		}
		PostAnaAnaFiles[indexNames[i]] = temp;
	}
/*	cout<<"that worked, now try main ana files"<<endl;
	for(int i=0;i<nDataAndMcFiles;i++){
		cout<<"Try to open "<<MCpoints[i]->plotsroot_mc.c_str()<<endl;
		MainAnaFiles[indexNames[i]] = new TFile(MCpoints[i]->plotsroot_mc.c_str());
	}*/
	cout<<endl<<"Writing finished plots to file "<<plotsroot_data<<endl<<endl;

		///////////////////////////// Other Lists ///////////////////////////////////////

		/////////////// FOR INDEXING, USE THESE /////////////////////////
		///	string s_MassBkgDists[nPhoMassAndBkgDists]={lowSB,tag,upperSB,bkg,tag_subbkg,lowSB_scaled,upperSB_scaled};
		/// string s_EventTopology[nEventTopologies]={"","1Jb","3J","3Jb","metCut"};
		/// string s_KinemVars[nKinemVars]={"MET","ST","PtGG","HT","MHT"};
		/// string s_DataAndMcFiles[nDataAndMcFiles]={Data,"MC_mst_350_M3_5025_mu_225"...}
		/////////////////////////////////////////////////////////////////
	/*Debug*/ if(printlevel > 4) cout << "Make Other Lists" << endl;
		//	const int nEventTopologies = 5; // the number of types of cuts selected, like 1JB...
		//string s_EventTopology[nEventTopologies] = {"","1Jb","3J","3Jb","metCut"};//** FOR INEDEXING
	string s_EventTopology_v2[nEventTopologies];//{"","_1Jb","_3J","_3Jb","_metCut"};
	string s_EventTopology_v3[nEventTopologies];//{"","_1Jb_","_3J_","_3Jb_","_metCut_"};
		//s_EventTopology_v2[0]=s_EventTopology[0];
		//s_EventTopology_v3[0]=s_EventTopology[0];
		//for (int i=1; i<nEventTopologies; i++) {
	for (int i=0; i<nEventTopologies; i++) {
		s_EventTopology_v2[i] = string("_")+s_EventTopology[i];
		s_EventTopology_v3[i] = string("_")+s_EventTopology[i]+"_";
		/*Debug*/ if(printlevel > 4) cout<<"making v2 "<<s_EventTopology_v2[i]<<" v3 "<<s_EventTopology_v3[i]<<endl;
	}

		//const int nPhoMassAndBkgDists //lsb, tag, usb...
		///	string s_MassBkgDists[] = {"lowSB","tag","upperSB","bkg","tag_subbkg","lowSB_scaled","upperSB_scaled"};
		///	string s_MassBkgDists_v2[] = {"_lowSB","_tag","_upperSB","_bkg","_tag_subbkg","_lowSB_scaled","_upperSB_scaled"};
	string s_MassBkgDists_v2[nPhoMassAndBkgDists-2];
	int iMassDist = 1;
	for (int i=0; i<nPhoMassAndBkgDists-3; i++) {
		if(iMassDist == 2 || iMassDist == 4) iMassDist++;
		s_MassBkgDists_v2[i]=string("_")+s_MassBkgDists[iMassDist];
		iMassDist++;
	}

//	string s_DataAndMcFiles_v2[nDataAndMcFiles];
//	string s_DataAndMcFiles_v3[nDataAndMcFiles];
//	for(int i=0;i<nDataAndMcFiles;i++) s_DataAndMcFiles_v2[i] = MCpoints[i]->s_DataAndMcFiles_v2;
//	for(int i=0;i<nDataAndMcFiles;i++) s_DataAndMcFiles_v3[i] = MCpoints[i]->s_DataAndMcFiles_v3;

		///////////////////////////// Color Scheme //////////////////////////////////////
	int dataColor = kBlack;
	int dgBkgBoxColor = kRed;
	int dgBkgThatchColor = kRed;
	int usbColor = kGreen;
	int lsbColor = kCyan;

	int tag_bkgColor = kRed+2;
	int TagToBkgRatColor = kMagenta+2;

	int tempMCcolors[6]={kMagenta+2,kGreen+2,kBlue+2,kOrange+2,kCyan+2,kRed+2};//first six colors
	int nMCcolor = nDataAndMcFiles-1>6?nDataAndMcFiles-1:6;
	int MCcolors[nMCcolor];
	for (int i=0; i<nMCcolor; i++) MCcolors[i] = i<6?tempMCcolors[i]:i;// if more than six--which there never will be, autofill'em.

		///////////////////////////// STANDARD MARKINGS ///////////////////////////////////////
	TLatex * TEX_CMSPrelim = new TLatex(0.177136,0.953368,"CMS Preliminary 2013");
	PrettyLatex(TEX_CMSPrelim,0.03);
	TLatex * TEX_E_TeV = new TLatex(0.800251,0.953368,"#sqrt{s} = 8 TeV");
	PrettyLatex(TEX_E_TeV,0.03);
	TLatex * TEX_lumi_fb = new TLatex(0.621859,0.953368,Form("#intL dt = %.0f fb^{-1}",Integrated_Luminosity_Data));
	PrettyLatex(TEX_lumi_fb,0.03);
		////////////////////////////////////////////////////////////////////
		///////////////////////////////Load h_mGG/////////////////////////////////////
/*	if(printlevel > 0) cout << "Load h_mGG" << endl;
		//load mGG_unsliced histograms from all files.
	Lable2Hist h_mGG_unsliced;
	for (int jFile=0; jFile<nDataAndMcFiles; jFile++) { //loop over all files
		LableHist tmp; // this is the collection of histograms, indexed by topology name
		if(printlevel > 2) cout << "first loop, jFile = "<<jFile << endl;
		for (int iTop = 0; iTop<nEventTopologies; iTop++) {
			if(printlevel > 4) cout << "second loop, iTop = "<<iTop <<endl;
			string instring = string("h_mGG") +s_EventTopology[iTop] + "_unsliced";
			if(printlevel > 4) cout << "loading "<<instring<< " from file " << indexNames[jFile] << " for topology "<<s_EventTopology[iTop] <<endl;
			tmp[s_EventTopology[iTop]] = (TH1F*)PostAnaAnaFiles[indexNames[jFile]]->Get(instring.c_str());
			if(printlevel > 4) cout << "succeeded"<<endl;

				//fix the root names
			string newname = instring+"_"+s_DataAndMcFiles[jFile];
			if(printlevel > 4) cout << "resetting name to "<<newname<<" for topology "<<s_EventTopology[iTop]<<endl;


			tmp[s_EventTopology[iTop]]->SetName((newname).c_str());
			if(printlevel > 4) cout << "succeeded"<<endl;
		}
		if(printlevel > 2) cout << "Attempting to write tmp to h_mGG_unsliced with tag "<<s_DataAndMcFiles[jFile] << endl;
		h_mGG_unsliced[indexNames[jFile]] = tmp;
		if(printlevel > 2) cout << "succeeded"<<endl;
	}
*/
		////////////////////////////// MAKE EXCLUSION PLOTS //////////////////////////////////////

	if(makeExclusionPlots){
		Label3Lim* allLims = new Label3Lim();
//		for (int iTop=0; iTop<nEventTopologies; iTop++) {
//			for (int kKinVar=0; kKinVar<nKinemVars_limit; kKinVar++) {
//				TCanvas * canv = MakeLimitPlot(allLims, s_EventTopology[iTop], s_KinemVars_limit[kKinVar], showTag,true);
				//if(saveImages)SaveCanvas(canv,plotsdir+"Exclusion_"+s_EventTopology[iTop]+"_"+s_KinemVars_limit[kKinVar],savewhat);//done somewhere else
//			} //end kKinvar
//		}//end for itopo
		for (int kKinVar=0; kKinVar<nKinemVars_limit; kKinVar++) {
			//TCanvas* canv4 = MakeLimitPlot(allLims, "bbin4", s_KinemVars_limit[kKinVar], showTag,true);
			//canv4->SetTopMargin(0.06);
			//canv4->SetBottomMargin(0.15);
			//if(saveImages)SaveCanvas(canv4,plotsdir+"Exclusion_bbin4_"+s_KinemVars_limit[kKinVar],savewhat);
			TCanvas* canv3 = MakeLimitPlot(allLims, "bbin3", s_KinemVars_limit[kKinVar], showTag,true);
			canv3->SetTopMargin(0.06);
			canv3->SetBottomMargin(0.15);

			MakeLimitPlot(allLims, "bbinMLbest", s_KinemVars_limit[kKinVar], showTag,true);
			MakeLimitPlot(allLims, "bbinTLbest", s_KinemVars_limit[kKinVar], showTag,true);
//			if(saveImages)SaveCanvas(canv3,plotsdir+"Exclusion_bbin3_"+s_KinemVars_limit[kKinVar],savewhat);
		} //end kKinvar
	}//endif 
	if(makeExclusionPlotsMinimal){
		//Label3Lim* allLims = new Label3Lim();
		//TCanvas* canv4 = MakeLimitPlot(allLims, "bbin4", "MET", showTag,true);
		//canv4->SetTopMargin(0.06);
		//canv4->SetBottomMargin(0.15);
		//if(saveImages)SaveCanvas(canv4,plotsdir+"Exclusion_bbin4_MET",savewhat);
		printf("***** going to make limit plots now**** \n");
		MakeLimitPlot("bbin3", "MET", showTag,true); //this saves the plot for you
		MakeLimitPlot("2JbMLgbar2", "MET", showTag,true); //this saves the plot for you
		printf("***** done makeing limit plots now**** \n");

		for (int iTop=0; iTop<nEventTopologies_limit; iTop++) {
		MakeBrazilianLimitPlot(s_EventTopology_limit[iTop],"MET",false,true);
		}
	}
	if(makeXSecPlot){
		MakeXSecPlot(saveImages);
	}
	if(makeEffPlots){
		MakeEffPlots();
		//MakeEffPlot("NULL");
		//MakeEffPlot("2JbMLgbar2");
	}

		////////////////////////////// Load Kin Var Plots //////////////////////////////////////
	/*Debug*/ if(printlevel > 0) cout << "Load Kin Var Plots" << endl;
	Lable3HistArr KinVarHistMap; //[file][kinVar][topo]
	for (int jFile=0; jFile<nDataAndMcFiles; jFile++) {

		/*Debug*/ if(printlevel >2) cout << "first loop, jFile = "<<jFile <<endl;
		Lable2HistArr tmpMapTopo;
		for (int iTop = 0; iTop<nEventTopologies; iTop++) {
			/*Debug*/ if(printlevel >4) cout << "second loop, iTop = "<<iTop <<endl;

			LableHistArr tmpMapKinVar;
			for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++) {
				/*Debug*/ if(printlevel >6) cout << "third loop, kKinVar = "<<kKinVar <<endl;

					//there is no MET dist for metCut, so don't try to load it.
				if (s_EventTopology[iTop].compare("metCut") == 0 && strCmp(s_KinemVars[kKinVar],"MET") ) continue;

				TH1F** tmpHistArray = new TH1F*[nPhoMassAndBkgDists];
				if (jFile == 0) {
						//LoadHistSet(hMET, &fin, "MET");
					for (int lMassDist=0; lMassDist < nPhoMassAndBkgDists; lMassDist++){
						/*Debug*/ if(printlevel >8) cout << "forth loop, lMassDist = "<<lMassDist <<endl;
						string instring = string("h")+s_KinemVars[kKinVar]+s_EventTopology[iTop]+"_"+s_MassBkgDists[lMassDist];
						if(lMassDist == 0 || lMassDist == 2 || lMassDist == 4){
							string newname = instring+"_"+MCpoints[jFile][0]->s_DataAndMcFiles;
							/*Debug*/ if(printlevel >8) cout << "Making dummy histogram "<<newname<<" for tmpHistArray["<<lMassDist<<"]"<<endl;
								//clone a good histogram
							string instring_dummy = string("h")+s_KinemVars[kKinVar]+s_EventTopology[iTop]+"_"+s_MassBkgDists[1];
							/*Debug*/ if(printlevel >8) cout << "attempting to clone "<<instring_dummy << "from  "<<indexNames[jFile] <<endl;
							TH1F* temp = (TH1F*) PostAnaAnaFiles[indexNames[jFile]][Data]->Get( instring_dummy.c_str() );
							/*Debug*/ if(printlevel >8) cout << "rename hist "<<newname <<endl;
							tmpHistArray[lMassDist] = (TH1F*) temp->Clone((newname).c_str());
							tmpHistArray[lMassDist]->Reset();
								//tmpHistArray[lMassDist]->SetName((newname).c_str()); //this segfaults!! for hMETNULL_lowSB_mst_185_M3_5050_mu_150
							/*Debug*/ if(printlevel >8) cout << "success" <<endl;
							tmpHistArray[lMassDist]->SetTitle("dummy hist");
						}
						else{
							/*Debug*/ if(printlevel >8) cout << "Load hist "<<instring<< " from file "<< indexNames[jFile] << " into tmpHistArray["<<lMassDist<<"]"<<endl;

							tmpHistArray[lMassDist] = (TH1F*) PostAnaAnaFiles[indexNames[jFile]][Data]->Get( instring.c_str() );
								//fix the root name
							string newname = instring+"_"+MCpoints[jFile][0]->s_DataAndMcFiles;
							/*Debug*/ if(printlevel >8) cout << "rename hist "<<newname <<endl;
							tmpHistArray[lMassDist]->SetName((newname).c_str()); //this segfaults!! for hMETNULL_lowSB_mst_185_M3_5050_mu_150
							/*Debug*/ if(printlevel >8) cout << "success" <<endl;
							string newtitle;
							if(s_KinemVars[kKinVar].compare("Phi") >=0 ||
							   s_KinemVars[kKinVar].compare("Eta") >=0 ||
							   s_KinemVars[kKinVar][0] == 'n' ||
							   strCmp(s_KinemVars[kKinVar],"cosThetaStar") ||
							   strCmp(s_KinemVars[kKinVar],"SumRootCSV")){
								newtitle = string(";")+s_KinemVars[kKinVar];
							}
							else{
								newtitle = string(";")+s_KinemVars[kKinVar]+" (GeV)";
								if(divideOutBinWidths && (lMassDist<4 || lMassDist == 5 || lMassDist == 6)){
									DivideOutBinWidths(tmpHistArray[lMassDist],nominalBinWidth);
									newtitle = newtitle + Form(";Events per %.0f GeV",nominalBinWidth);
								}
							}
							tmpHistArray[lMassDist]->SetTitle((char*)newtitle.c_str());
						}
					}//end for every Mass Dist
					/*Debug*/ if(printlevel >6) cout << "load hist array into tmpMapKinVar for "<< s_KinemVars[kKinVar] <<endl;
				}
				else{
						//else you're on MC and you only care about the tag region.
					int lMassDist = 1;
					string instring = string("h")+s_KinemVars[kKinVar]+s_EventTopology[iTop]+"_"+s_MassBkgDists[lMassDist];
						/////////////////////
					for (int ichan = 0; ichan < nchannels; ichan++) {
						/*Debug*/ if(printlevel >8) cout << "Load and scale hist "<<instring<< " from file "<< indexNames[jFile]<<"_"<<channel[ichan] << " into tmpHistArray["<<lMassDist<<"]"<<endl;

						printf("check summation %s %s %s\n",s_KinemVars[kKinVar].data(),s_EventTopology[iTop].data(),s_MassBkgDists[lMassDist].data());
						if (ichan == 0) {
							TH1F* temp = (TH1F*) PostAnaAnaFiles[indexNames[jFile]][channel[ichan]]->Get( instring.c_str() );
							temp->Scale(MCpoints[jFile][ichan]->lumiscalefactor(Integrated_Luminosity_Data) );
							tmpHistArray[lMassDist] = temp;
							cout<<"integral"<<ichan<<" "<<tmpHistArray[lMassDist]->Integral()<<endl;
						}
						else{
							TH1F* temp = (TH1F*) PostAnaAnaFiles[indexNames[jFile]][channel[ichan]]->Get( instring.c_str() ); 
							temp->Scale(MCpoints[jFile][ichan]->lumiscalefactor(Integrated_Luminosity_Data) );
							tmpHistArray[lMassDist]->Add(temp);
							cout<<"integral"<<ichan<<" "<<tmpHistArray[lMassDist]->Integral()<<endl;
						}
					}//end for each channel
						//so all histograms come in from here summed and loaded.

						//fix the root name
					string newname = instring+"_"+indexNames[jFile]; //MCpoints[jFile][0]->s_DataAndMcFiles;
					/*Debug*/ if(printlevel >8) cout << "rename hist "<<newname <<endl;
					tmpHistArray[lMassDist]->SetName((newname).c_str()); //this segfaults!! for hMETNULL_lowSB_mst_185_M3_5050_mu_150
					/*Debug*/ if(printlevel >8) cout << "success" <<endl;
					string newtitle;
					if(s_KinemVars[kKinVar].compare("Phi") >=0 ||
					   s_KinemVars[kKinVar].compare("Eta") >=0 ||
					   s_KinemVars[kKinVar][0] == 'n' ||
					   strCmp(s_KinemVars[kKinVar],"cosThetaStar") ||
					   strCmp(s_KinemVars[kKinVar],"SumRootCSV")){
						newtitle = string(";")+s_KinemVars[kKinVar];
					}
					else{
						newtitle = string(";")+s_KinemVars[kKinVar]+" (GeV)";
						if(divideOutBinWidths && (lMassDist<4 || lMassDist == 5 || lMassDist == 6)){
							DivideOutBinWidths(tmpHistArray[lMassDist],nominalBinWidth);
							newtitle = newtitle + Form(";Events per %.0f GeV",nominalBinWidth);
						}
					}
					tmpHistArray[lMassDist]->SetTitle((char*)newtitle.c_str());

				}//if MC
				tmpMapKinVar[s_KinemVars[kKinVar]] = tmpHistArray;

			}//End for each kinematic varraible
			/*Debug*/ if(printlevel >4) cout << "load hist array into tmpMapTopo for "<< s_EventTopology[iTop] <<endl;
			tmpMapTopo[s_EventTopology[iTop]] = tmpMapKinVar;

		}//end for each topology
		/*Debug*/ if(printlevel >2) cout << "load hist array into KinVarHistMap for "<< indexNames[jFile] <<endl;
		KinVarHistMap[indexNames[jFile]] = tmpMapTopo;
	}//end for each file

	/*Debug*/ if(printlevel >2){
		cout << "***KinVarHistMap should now be loaded, but did it work?***"<<endl;
			//cout << "Data 1Jb MHT tag name:" <<KinVarHistMap["Data"]["1Jb"]["MHT"][1]->GetName()<<endl;
			//cout << "Data 3Jb MHT tag name:" <<KinVarHistMap["Data"]["3Jb"]["MHT"][1]->GetName()<<endl;
			//cout << "Data 1Jb ST tag name:" <<KinVarHistMap["Data"]["1Jb"]["ST"][1]->GetName()<<endl;
			//cout << "Data 1Jb MHT sb name:" <<KinVarHistMap["Data"]["1Jb"]["MHT"][5]->GetName()<<endl;
			//cout << "mst_350_M3_5025_mu_225 1Jb MHT tag name:" <<KinVarHistMap["mst_350_M3_5025_mu_225"]["1Jb"]["MHT"][1]->GetName()<<endl;
			//cout << "mst_350_mu_200 2JbMLm20gbar2 MHT tag name:" <<KinVarHistMap["mst_350_mu_200"]["2JbMLm20gbar2"]["MHT"][1]->GetName()<<
			//cout << "new nat mst_100_M3_5025_mu_175 1Jb MHT tag name:" <<KinVarHistMap["new_natural_mst_350_M3_5025_mu_225"]["2Jm20"]["MHT"][1]->GetName()<<
			//KinVarHistMap["mst_350_mu_200"]["2JbMLm20gbar2"]["MHT"][1]->Integral()<<endl;
			//KinVarHistMap["new_natural_mst_350_M3_5025_mu_225"]["2Jm20"]["MHT"][1]->Integral()<<endl;
			//cout<<"yes it did"<<endl;
		cout<<"skipping this check"<<endl;
	}


		////////////////////////////////////////////////////////////////////
	/*Debug*/ if(printlevel > 0) cout << "Load the Fit Curves" << endl;
		//load the fit curves for the data.
	TF1* mgg_fit_curve[nEventTopologies];
	for (int iTop=0; iTop<nEventTopologies; iTop++) {
		/*Debug*/ if(printlevel > 1) cout << "first loop, iTop = "<<iTop <<endl;
		string instring = string("mgg") + s_EventTopology_v3[iTop] + "fit";
		if(printlevel > 1)cout<<"format_plots_higgsino curve fitting sees s_EventTopology_v3 as "<<s_EventTopology_v3[iTop]<<endl;
		/*Debug*/ if(printlevel > 1) cout << "instring = "<<instring <<endl;
		mgg_fit_curve[iTop] = (TF1*)PostAnaAnaFiles[Data][Data]->Get(instring.c_str());
		/*Debug*/ if(printlevel > 1) cout << "supposidly loaded it, try it "<<endl;
		/*Debug*/ if(printlevel > 1) cout << mgg_fit_curve[iTop]->GetProb() <<endl;
	}


		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	/*Debug*/ if(printlevel > 0) cout << "Start Building Plots" << endl;

	fplots->cd();

		///Make background subtracted plots.
	if(showTag && makeBkgSubPlots){
		for (int iTop = 0; iTop<nEventTopologies; iTop++) {
			for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++) {
				if (s_EventTopology[iTop].compare("metCut")==0 && s_KinemVars[kKinVar].compare("MET")==0 ) continue;
				TH1F** h =KinVarHistMap[Data][s_EventTopology[iTop]][s_KinemVars[kKinVar]];
					//linear only. Data only.
				string canvName = string("BkgSub_")+s_KinemVars[kKinVar]+s_EventTopology_v2[iTop];
				TCanvas* tempCanv = newTCanvas(canvName.data() );
				tempCanv->SetTopMargin(0.06);
				tempCanv->SetBottomMargin(0.15);
//				TCanvas* tempCanv = newTCanvas((char*)canvName.c_str());

				tempCanv->cd();
				PrettyHist(h[4],tag_bkgColor);//tag-bkg.
				PrettyMarker(h[4],tag_bkgColor);
					//				RaiseRangeRoof(h[4]);
				playNiceWithLegend(h[4],0.30,0.0);


				if(h[4]->GetMinimum() < 0 && h[4]->GetMaximum() > 0){
					if(-h[4]->GetMinimum() > 2*h[4]->GetMaximum()) h[4]->SetMaximum(-0.5*h[4]->GetMinimum());
					if(h[4]->GetMaximum() > -2*h[4]->GetMinimum()) h[4]->SetMinimum(-0.5*h[4]->GetMaximum());
				}

				TLegend* l1=makeL1_v2(0.443467,0.869171,0.643216,0.914508);
				PrettyLegend(l1);
				l1->SetTextSize(0.03067876);
				l1->AddEntry(h[4],"Background Subtracted");
				h[4]->GetYaxis()->SetRangeUser(0.,3.);
				h[4]->Draw("ep");
				l1->Draw("same");
				TEX_CMSPrelim->Draw("same");
				TEX_E_TeV->Draw("same");
				TEX_lumi_fb->Draw("same");
				TAxis* x = h[4]->GetXaxis();
				TLine *OneLine = new TLine(x->GetXmin(),0.0,x->GetXmax(),0.0);
				OneLine->SetLineColor(kBlack);
				OneLine->SetLineWidth(2);
				OneLine->SetLineStyle(7);//dashed.
				OneLine->Draw("same");
				if(writeRootFile) tempCanv->Write();
				if(saveImages)SaveCanvas(tempCanv,plotsdir+tempCanv->GetName(),savewhat);
			}//end for
		}//end for
	}//end if

		///Make the Design Wall ////////////////////
	if(makeDesignSummary){

			//make a good looking color gradient
		const int NRGBs = 10, NCont = 48;
			//				     dkPrpl  dkBlu  blu   cyan   grass    lY     Y     O     R     pink
		Double_t stops[NRGBs] = { 0.00,   0.04,  0.16, 0.28, 0.40,   0.54, 0.59,  0.68, 0.76, 0.88};
		Double_t red[NRGBs]   = { 0.2813, 0.00,  0.00, 0.00, 0.4492 , 1.00,  1.00,0.9102, 1.00, 1.00};
		Double_t green[NRGBs] = { 0.1172, 0.00,  0.00, 1.00, 0.9492 , 0.9727,1.00,0.5703, 0.00, 0.00};
		Double_t blue[NRGBs]  = { 0.3125, 0.379, 1.00, 1.00, 0.1719 , 0.3828,0.00,0.1484, 0.00, 1.00};



		TH2F* DesignWalls[nDataAndMcFiles-1];//do not make this for data!!
		for (int jFile=1; jFile<nDataAndMcFiles; jFile++) {
//			DesignWalls[jFile-1] = new TH2F(Form("DesignWallLin_%s",MCpoints[jFile][0]->s_DataAndMcFiles.data() ),Form("Expected 50% 1/r-Values for %s;Topology;Kinematic Variable",MCpoints[jFile]->s_DataAndMcFiles.data()),nEventTopologies_limit,0,nEventTopologies_limit,nKinemVars_limit,0,nKinemVars_limit);
			DesignWalls[jFile-1] = new TH2F(Form("DesignWallLin_%s",indexNames[jFile].data() ),Form("Expected 50% 1/r-Values for %s;Topology;Kinematic Variable",indexNames[jFile].data()),nEventTopologies_limit,0,nEventTopologies_limit,nKinemVars_limit,0,nKinemVars_limit);
				//set text labels
			for (int iTopo = 0; iTopo<nEventTopologies_limit; iTopo++) {
				DesignWalls[jFile-1]->GetXaxis()->SetBinLabel(iTopo+1,s_EventTopology_limit[iTopo].data());
			}
			for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {
				DesignWalls[jFile-1]->GetYaxis()->SetBinLabel(kKinVar+1,s_KinemVars_limit[kKinVar].data());
			}

				//fill it up
			float maxlim = 0;
			for (int iTop = 0; iTop<nEventTopologies_limit; iTop++) {
				for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++) {

					if( checkin(LimitContainers[jFile-1],s_EventTopology_limit[iTop],s_KinemVars_limit[kKinVar])){   //there's 1 LimitContainers for every MC, no data
						float lim = 1.0/(*(LimitContainers[jFile-1]))[s_KinemVars_limit[kKinVar]][s_EventTopology_limit[iTop]]->Expected50;
						DesignWalls[jFile-1]->SetBinContent(iTop+1,kKinVar+1, lim);

						if(lim > maxlim) maxlim = lim;

					}
					else {
						DesignWalls[jFile-1]->SetBinContent(iTop+1,kKinVar+1,-1);
					}

				}//end for kKinvar
			}//end for each topology

			maxlim = 0.1*floor(10*maxlim) + 0.1;

			PrettyHist(DesignWalls[jFile-1]);
			TCanvas * canv = new TCanvas(Form("c_DesignSummaryLin_%s",indexNames[jFile].data() ),Form("Expected 50% 1/r -Values for %s;Topology",indexNames[jFile].data()),149,473,1000,700);
//			TCanvas * canv = new TCanvas(Form("c_DesignSummaryLin_%s",MCpoints[jFile]->s_DataAndMcFiles.data() ),Form("Expected 50% 1/r -Values for %s;Topology",MCpoints[jFile]->s_DataAndMcFiles.data()),149,473,1000,700);
			gStyle->SetPaintTextFormat("3.2f");
//			gStyle->SetPalette(1);
			gStyle->SetNumberContours(NCont);
//			gStyle->CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
			TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
			canv->Range(-4.24581,-6.654991,18.01117,40.42032);
			canv->SetLeftMargin(0.1907631);
			canv->SetRightMargin(0.11);
			canv->SetTopMargin(0.02);
			canv->SetBottomMargin(0.141369);
			canv->SetFrameBorderMode(0);
			DesignWalls[jFile-1]->GetXaxis()->SetLabelSize(0.043);
			DesignWalls[jFile-1]->GetYaxis()->SetLabelSize(0.043);
			DesignWalls[jFile-1]->GetXaxis()->SetTickLength(0.02);
			DesignWalls[jFile-1]->GetXaxis()->SetTitleOffset(1.15);
			DesignWalls[jFile-1]->GetYaxis()->SetTickLength(0.02);
			DesignWalls[jFile-1]->GetYaxis()->SetTitleOffset(1.7);
			DesignWalls[jFile-1]->SetMarkerSize(0.85);
			DesignWalls[jFile-1]->GetZaxis()->SetRangeUser(0,maxlim);
			DesignWalls[jFile-1]->DrawCopy("colz");
			DesignWalls[jFile-1]->DrawCopy("textsame");
			if(writeRootFile) canv->Write();
			if(saveImages)SaveCanvas(canv,plotsdir+canv->GetName(),savewhat);
		}//end for every MC file; end DesignWall
	}//end if makeDesignSummary



		///Make Design Plots--plot The combined bkg and all the MC.
	TH1F * box = new TH1F("box","asdf",1,0,1);
	box->SetMarkerColor(dgBkgBoxColor);
	box->SetMarkerStyle(25);
	box->SetMarkerSize(2);
	box->SetLineColor(0);
	for (int iTop = 0; iTop<nEventTopologies; iTop++) {
		for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++) {
			if (s_EventTopology[iTop].compare("metCut")==0 && s_KinemVars[kKinVar].compare("MET")==0 ) continue;

			string canvName = string("Design_")+s_KinemVars[kKinVar]+s_EventTopology_v2[iTop];
			string canvName2 = string("Designlog_")+s_KinemVars[kKinVar]+s_EventTopology_v2[iTop];
			TCanvas* tempCanv = newTCanvas(canvName.data(),canvName.data());
			tempCanv->SetTopMargin(0.06);
			tempCanv->SetBottomMargin(0.15);
			TCanvas* tempCanv2 = newTCanvas(canvName2.data(),canvName2.data());
			tempCanv2->SetTopMargin(0.06);
			tempCanv2->SetBottomMargin(0.15);

				//make an array of the signal dists in the tag region.
			TH1F* MC_hists[nDataAndMcFiles-1];
			int iter = 0;
			for (int jFile = 0; jFile < nDataAndMcFiles; jFile++) { //for each file
				if (indexNames[jFile].compare(Data) == 0 ) continue; // skip the data file, so really for each MC file
				MC_hists[iter] = KinVarHistMap[indexNames[jFile]][s_EventTopology[iTop]][s_KinemVars[kKinVar]][1];
				if(printlevel > 2) cout << "jFile = "<<jFile<<" MC_histe " <<KinVarHistMap[indexNames[jFile]][s_EventTopology[iTop]][s_KinemVars[kKinVar]][1]->GetName()<<" integral:"<<KinVarHistMap[indexNames[jFile]][s_EventTopology[iTop]][s_KinemVars[kKinVar]][1]->Integral()<<endl;

				iter++;
			}
				//pull out the limit files.
			limit* theseLimits[nDataAndMcFiles-1];
			TPaveText *textlims = new TPaveText(0.748744,0.722798,0.899497,0.874352,"BLNDC");//Design Plots //Limit
			bool allthere = true;
			if(DrawLimits && KinvarIsLimit(s_KinemVars[kKinVar]) ){
				for (int i=0; i<nDataAndMcFiles-1; i++) allthere &= checkin(LimitContainers[i],s_EventTopology[iTop],s_KinemVars[kKinVar]);
				if(allthere){
					for (int i=0; i<nDataAndMcFiles-1; i++) theseLimits[i] = (*(LimitContainers[i]))[s_KinemVars[kKinVar]][s_EventTopology[iTop]];
					PrettyText(textlims,0.033); //Limit
					textlims->AddText("Expected Limits"); //Limit
					for (int i=0; i<nDataAndMcFiles-1; i++){
						if (checkin(LimitContainers[i],s_EventTopology[iTop],s_KinemVars[kKinVar])) {
							textlims->AddText(Form("r < %.2f",theseLimits[i]->Expected50)); //Limit
						}
						else textlims->AddText("   "); //Limit
					}
				}//end if all there
				else printf("warning: checkin for designlog repports incomplete limits\n");
			}
			


				///MAKE LINEAR ARRANGE3 PLOTS///
			TH1F** h =KinVarHistMap[Data][s_EventTopology[iTop]][s_KinemVars[kKinVar]];
			tempCanv->cd();
			TLegend* l1=makeL1_v2();

			PrettyHist(h[3],dgBkgBoxColor);
			PrettyHist(h[5],lsbColor);
			PrettyHist(h[1],dataColor);
			PrettyHist(h[6],usbColor);
			PrettyBlock2(h[5],lsbColor,3354,2);//PrettyMarker(h[5],kBlue,4);
			PrettyBlock2(h[6],usbColor,3345,2);//PrettyMarker(h[6],kGreen,4);

			h[3]->SetFillStyle(0);//open rectangle
			h[3]->SetLineColor(kRed);
			h[3]->SetLineWidth(4);

			if (s_KinemVars[kKinVar].compare("HT") == 0) {
				h[3]->GetXaxis()->SetLabelSize(0.04);
			}

				//PrettyBlock2(h[3],kRed,4050);
				//				PrettyBlock2(h[3],kRed,3345,2);
				//PrettyBlock(h[3],kRed,string("transparent"));//PrettyMarker(h[3],kRed);
			for (int i=0; i<nDataAndMcFiles-1; i++) { //there should be nDataAndMcFiles -1 MC files
				PrettyHist(MC_hists[i],MCcolors[i]);//xyxy
				PrettyMarker(MC_hists[i],MCcolors[i]);
				playNiceWithLegend(MC_hists[i],0.30,0.0);
			}
			h[3]->SetMinimum(0.0);
			float linmax = h[3]->GetMaximum();
			float linmin = h[3]->GetMinimum();
				//			RaiseRangeRoof(h[5],1.25);
				//			RaiseRangeRoof(h[6],1.25);
				//			RaiseRangeRoof(h[3],1.25);
			playNiceWithLegend(h[3],0.30,0.0);
			playNiceWithLegend(h[6],0.30,0.0);
			playNiceWithLegend(h[5],0.30,0.0);
				//			for (int i=0; i<nDataAndMcFiles-1; i++) SameRange(h[3],MC_hists[i]);
			for (int i=0; i<nDataAndMcFiles-1; i++){
				playNiceWithLegend(MC_hists[i],0.30,0.0);
				SameRange(h[3],MC_hists[i]);//WARNING--pattern is normal, huge on upper side.
			}

			SameRange(h[3],h[5],h[6]);
			h[3]->Draw("e2p");
			for (int i=0; i<nDataAndMcFiles-1; i++) MC_hists[i]->Draw("same");
			h[5]->Draw("e2psame");
			h[6]->Draw("e2psame");
			h[3]->Draw("e2psame");
			l1->AddEntry(box,"Data Driven Background");//h[3]
			l1->AddEntry(h[5],"LSB Bkg Estimate");
			l1->AddEntry(h[6],"USB Bkg Estimate");

			for (int i=0; i<nDataAndMcFiles-1; i++){
				string lablestring = string("MC Signal: ")+MCpoints[i+1][0]->s_DataAndMcFiles_v4;
				l1->AddEntry(MC_hists[i],lablestring.c_str());
			}
			l1->Draw("same");
			if(DrawLimits && allthere) textlims->Draw("same"); //Limit
			TEX_CMSPrelim->Draw("same");
			TEX_E_TeV->Draw("same");
			TEX_lumi_fb->Draw("same");

			if(makeDesignLinPlots){
				if(writeRootFile) tempCanv->Write();
				if(saveImages)SaveCanvas(tempCanv,plotsdir+tempCanv->GetName(),savewhat);
			}
				///END MAKE LINEAR PLOTS///

                ///MAKE LOG PLTOS///
			TLegend* l2 = makeL1_v2();
			tempCanv2->cd();
			PrettyHist(h[3],dgBkgBoxColor);

			if (s_KinemVars[kKinVar].compare("HT") == 0) {
				h[3]->GetXaxis()->SetLabelSize(0.04);}


				//PrettyBlock2(h[3],kRed,3345,2);
			h[3]->SetFillStyle(0);//open rectangle
			h[3]->SetLineColor(dgBkgBoxColor);
			h[3]->SetLineWidth(4);
			PrettyBlock2(h[5],kCyan-7,3354,2);//PrettyMarker(h[5],kBlue,4);
			PrettyBlock2(h[6],kGreen-7,3345,2);//PrettyMarker(h[6],kGreen,4);


			for (int i=0; i<nDataAndMcFiles-1; i++) { //there should be nDataAndMcFiles -1 MC files
				PrettyHist(MC_hists[i],MCcolors[i]);
				PrettyMarker(MC_hists[i],MCcolors[i]);
				playNiceWithLegendLog(MC_hists[i],0.30,0.05);
			}
				//h[3]->SetMaximum(TMath::Max(100.,h[3]->GetMaximum()));
				//			h[3]->SetMaximum(TMath::Max(100.,50*h[3]->GetMaximum()));
				//			h[3]->SetMinimum(0.5);
			playNiceWithLegendLog(h[3],0.30,0.05);
			playNiceWithLegendLog(h[6],0.30,0.05);
			playNiceWithLegendLog(h[5],0.30,0.05);
			for (int i=0; i<nDataAndMcFiles-1; i++){
				playNiceWithLegendLog(MC_hists[i],0.30,0.05);
				SameRange(h[3],MC_hists[i]);//WARNING//now we get huge, reasonable.

			}
			SameRange(h[3],h[5],h[6]);
			h[3]->SetMinimum(0.05);
			tempCanv2->SetLogy();
			h[3]->Draw("e2p");
			h[5]->Draw("e2psame");
			h[6]->Draw("e2psame");
				//	cout << "final MC integral "<<MC_hists[0]->Integral()<<endl;
			for (int i=0; i<nDataAndMcFiles-1; i++) MC_hists[i]->Draw("same");//e1psame
			h[3]->Draw("e2psame");
				//l2->AddEntry(h[3],"Data Driven Background");
			l2->AddEntry(box,"Data Driven Background");//h[3]
			l2->AddEntry(h[5],"LSB Bkg Estimate");
			l2->AddEntry(h[6],"USB Bkg Estimate");
			for (int i=0; i<nDataAndMcFiles-1; i++){
				string lablestring2 = string("MC Signal: ")+MCpoints[i+1][0]->s_DataAndMcFiles_v4;
				l2->AddEntry(MC_hists[i],lablestring2.c_str());
			}
			l2->Draw("same");
			if(DrawLimits&&allthere) textlims->Draw("same"); //Limit
			TEX_CMSPrelim->Draw("same");
			TEX_E_TeV->Draw("same");
			TEX_lumi_fb->Draw("same");
			if(makeDesignLogPlots){
				if(writeRootFile) tempCanv2->Write();
				if(saveImages)SaveCanvas(tempCanv2,plotsdir+tempCanv2->GetName(),savewhat);
			}
			h[3]->SetMaximum(linmax);
			h[3]->SetMinimum(linmin);
		}//edn for each kinematic varriable
	}//end for each topology

		///SigCompFull: Make Full Final Plot--plot the tag, combined bkg, all the MC, then on a lower subplot make the sig/bkg.
	if(showTag && (makeSigcompFullLinPlots || makeSigcompFullLogPlots)){
		for (int iTop = 0; iTop<nEventTopologies; iTop++) {
			for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++) {
				if (s_EventTopology[iTop].compare("metCut")==0 && s_KinemVars[kKinVar].compare("MET")==0 ) continue;

				string canvName = string("SigCompFull_")+s_KinemVars[kKinVar]+s_EventTopology_v2[iTop];
				string canvName2 = string("SigCompFulllog_")+s_KinemVars[kKinVar]+s_EventTopology_v2[iTop];
				TCanvas* tempCanv = newTCanvas(canvName.data());
				tempCanv->SetTopMargin(0.06);
				tempCanv->SetBottomMargin(0.15);
				TCanvas* tempCanv2 = newTCanvas(canvName2.data());
				tempCanv2->SetTopMargin(0.06);
				tempCanv2->SetBottomMargin(0.15);

				TPad *p1lin = new TPad("p1lin","",0.,0.32,1.,1.);
				TPad *p1log = new TPad("p1log","",0.,0.32,1.,1.);
				TPad *p2lin = new TPad("p2lin","",0.,0.145,1.,0.32);//just reuse p2lin for the log plot.
				p1lin->SetBottomMargin(0);
				p1log->SetBottomMargin(0);
				p2lin->SetTopMargin(0);

					//make an array of the signal dists in the tag region.
				TH1F* MC_hists[nDataAndMcFiles-1];
				int iter = 0;
				for (int jFile = 0; jFile < nDataAndMcFiles; jFile++) { //for each file
					if (indexNames[jFile].compare(Data) == 0 ) continue; // skip the data file, so really for each MC file
					MC_hists[iter] = KinVarHistMap[indexNames[jFile]][s_EventTopology[iTop]][s_KinemVars[kKinVar]][1];
					if(printlevel>2)cout << "jFile = "<<jFile<<" MC_hist " <<KinVarHistMap[indexNames[jFile]][s_EventTopology[iTop]][s_KinemVars[kKinVar]][1]->GetName()<<" integral:"<<KinVarHistMap[indexNames[jFile]][s_EventTopology[iTop]][s_KinemVars[kKinVar]][1]->Integral()<<endl;

					iter++;
				}

					//pull out the limit files.
				limit* theseLimits[nDataAndMcFiles-1];
				TPaveText *textlims = new TPaveText(0.625628,0.702835,0.776382,0.881896,"BLNDC");//SigCompFull //Limit
				bool allthere = true;
				if(DrawLimits && KinvarIsLimit(s_KinemVars[kKinVar]) ){
					for (int i=0; i<nDataAndMcFiles-1; i++) allthere &= checkin(LimitContainers[i],s_EventTopology[iTop],s_KinemVars[kKinVar]);
					if(allthere){
						for (int i=0; i<nDataAndMcFiles-1; i++) theseLimits[i] = (*(LimitContainers[i]))[s_KinemVars[kKinVar]][s_EventTopology[iTop]];
						PrettyText(textlims,0.033); //Limit
						textlims->AddText("Observed Limits");
						for (int i=0; i<nDataAndMcFiles-1; i++){
							if (checkin(LimitContainers[i],s_EventTopology[iTop],s_KinemVars[kKinVar])) {
								textlims->AddText(Form("r < %.2f",theseLimits[i]->Observed)); //Limit
							}
							else textlims->AddText("   "); //Limit
						}
					}//end if all there
				}

					///MAKE LINEAR ARRANGE3 PLOTS///
				TH1F** h =KinVarHistMap[Data][s_EventTopology[iTop]][s_KinemVars[kKinVar]];
					//				tempCanv->cd();
				p1lin->cd();
				TLegend* l1=makeL1_v2( 0.201005,0.6889313,0.4007538,0.9198473);
				PrettyHist(h[3],dgBkgThatchColor);//bkg
				PrettyHist(h[1],dataColor);//tag

				if (s_KinemVars[kKinVar].compare("HT") == 0) {
					h[3]->GetXaxis()->SetLabelSize(0.04);
					h[8]->GetXaxis()->SetLabelSize(0.04);}

					//PrettyBlock2(h[3],kRed,4050);
				PrettyBlock2(h[3],kRed,3345,2);
					//PrettyBlock(h[3],kRed,string("transparent"));//PrettyMarker(h[3],kRed);
				PrettyMarker(h[1],kBlack,kFullCircle,1.3);


				for (int i=0; i<nDataAndMcFiles-1; i++) { //there should be nDataAndMcFiles -1 MC files
					PrettyHist(MC_hists[i],MCcolors[i]);
					PrettyMarker(MC_hists[i],MCcolors[i]);
				}
				h[3]->SetMinimum(0.0);
				float linmax = h[3]->GetMaximum();
				float linmin = h[3]->GetMinimum();
					//				RaiseRangeRoof(h[3],1.15);
					//				RaiseRangeRoof(h[1],1.15);
				playNiceWithLegend(h[3],0.30,0.0);
				playNiceWithLegend(h[1],0.30,0.0);
				playNiceWithLegend(h[5],0.30,0.0);
				playNiceWithLegend(h[6],0.30,0.0);

				for (int i=0; i<nDataAndMcFiles-1; i++){
					playNiceWithLegend(MC_hists[i],0.30,0.0);
					SameRange(h[3],MC_hists[i]);//WARNING--pattern is normal, huge on upper side.
					playNiceWithLegend(MC_hists[i],0.30,0.0);  
				}

				//SameRange(h[3],h[1]);
				SameRange(h[3],h[5],h[6]);

				h[3]->Draw("e2p");
				if(showTag) h[1]->Draw("e1psame");//tag


				for (int i=0; i<nDataAndMcFiles-1; i++) MC_hists[i]->Draw("same");
				h[3]->Draw("e2psame");
				h[1]->Draw("e1psame");
				l1->AddEntry(h[1],"Higgs Mass Region");
				l1->AddEntry(h[3],"Data Driven Background");
				for (int i=0; i<nDataAndMcFiles-1; i++){
					string lablestring = string("MC Signal: ")+MCpoints[i+1][0]->s_DataAndMcFiles_v4;
					l1->AddEntry(MC_hists[i],lablestring.c_str());
				}
				l1->Draw("same");
				if(DrawLimits&&allthere) textlims->Draw("same"); //Limit
				TEX_CMSPrelim->Draw("same");
				TEX_E_TeV->Draw("same");
				TEX_lumi_fb->Draw("same");
				p2lin->cd();
				PrettyHist(h[8],TagToBkgRatColor);
				PrettyMarker(h[8],TagToBkgRatColor);
				TAxis * xx = h[8]->GetXaxis();
				TAxis * y = h[8]->GetYaxis();
				float fontsize = 0.25;
				float fontsizeY = 0.10;
				xx->SetTitleSize(fontsize);
				y->SetTitleSize(fontsizeY);
				xx->SetLabelSize(fontsize);
				y->SetLabelSize(fontsizeY);

				h[8]->GetYaxis()->SetRangeUser(0.,3.);
				h[8]->Draw("e1p");
				TAxis* x = h[7]->GetXaxis();
				TLine *OneLine = new TLine(x->GetXmin(),1.0,x->GetXmax(),1.0);
				OneLine->SetLineColor(kBlack);
				OneLine->SetLineWidth(2);
				OneLine->SetLineStyle(7);//dashed.
				OneLine->Draw("same");
				h[8]->Draw("e1psame");

				TLegend* l6 = makeL1_v2( 0.548995, 0.72909, 0.748744, 0.928942);
				l6->SetTextSize(fontsize*0.8);
				l6->AddEntry(h[8],"Tag to Background Ratio");
				l6->Draw("same");

				tempCanv->cd();
				p1lin->Draw();
				p2lin->Draw();
				if(makeSigcompFullLinPlots){
					if(writeRootFile) tempCanv->Write();
					if(saveImages)SaveCanvas(tempCanv,plotsdir+tempCanv->GetName(),savewhat);
				}
					///END MAKE LINEAR PLOTS///

					///MAKE LOG PLTOS///
				TLegend* l2 = makeL1_v2(0.201005,0.6889313,0.4007538,0.9198473);
					//				tempCanv2->cd();
				p1log->cd();
				PrettyHist(h[3],dgBkgThatchColor);//bkg
				PrettyHist(h[1],dataColor);//tag

				if (s_KinemVars[kKinVar].compare("HT") == 0) {
					h[3]->GetXaxis()->SetLabelSize(0.04);}

					//PrettyBlock2(h[3],kRed,4050);
				PrettyBlock2(h[3],kRed,3345,2);
					//PrettyBlock(h[3],kRed,string("transparent"));//PrettyMarker(h[3],kRed);
				PrettyMarker(h[1],kBlack,kFullCircle,1.3);
				for (int i=0; i<nDataAndMcFiles-1; i++) { //there should be nDataAndMcFiles -1 MC files
					PrettyHist(MC_hists[i],MCcolors[i]);
					PrettyMarker(MC_hists[i],MCcolors[i]);
					playNiceWithLegendLog(MC_hists[i],0.30,0.05);
				}
					//				h[3]->SetMaximum(TMath::Max(100.,h[3]->GetMaximum()));
					//				h[3]->SetMinimum(0.05);
					//				h[1]->SetMinimum(0.05);
				playNiceWithLegendLog(h[1],0.3,0.05);
				playNiceWithLegendLog(h[3],0.3,0.05);
				playNiceWithLegendLog(h[6],0.3,0.05);
				playNiceWithLegendLog(h[5],0.3,0.05);
				for (int i=0; i<nDataAndMcFiles-1; i++){ 
					playNiceWithLegendLog(MC_hists[i],0.30,0.05);  
					SameRange(h[3],MC_hists[i]);//WARNING//now we get huge, reasonable.  
				}
				SameRange(h[3],h[1],h[5]);
					//tempCanv2->SetLogy();
				h[3]->SetMinimum(0.05); 
				p1log->SetLogy();
				h[3]->Draw("e2p");
				h[1]->Draw("e1psame");//tag
					//	cout << "final MC integral "<<MC_hists[0]->Integral()<<endl;
				for (int i=0; i<nDataAndMcFiles-1; i++) MC_hists[i]->Draw("same");
				h[3]->Draw("e2psame");
				h[1]->Draw("e1psame");
				if(showTag) h[1]->Draw("e1psame");
				l2->AddEntry(h[1],"Higgs Mass Region");
				l2->AddEntry(h[3],"Data Driven Background");
				for (int i=0; i<nDataAndMcFiles-1; i++){
					string lablestring2 = string("MC Signal: ")+MCpoints[i+1][0]->s_DataAndMcFiles_v4;
					l2->AddEntry(MC_hists[i],lablestring2.c_str());
				}
				l2->Draw("same");
				if(DrawLimits&&allthere) textlims->Draw("same");//Limit
				TEX_CMSPrelim->Draw("same");
				TEX_E_TeV->Draw("same");
				TEX_lumi_fb->Draw("same");
				tempCanv2->cd();
				p1log->Draw();
				p2lin->Draw();
				if (makeSigcompFullLogPlots) {
					if(writeRootFile) tempCanv2->Write();
					if(saveImages)SaveCanvas(tempCanv2,plotsdir+tempCanv2->GetName(),savewhat);
				}
				h[3]->SetMaximum(linmax);
				h[3]->SetMinimum(linmin);
				h[1]->SetMaximum(linmax);
				h[1]->SetMinimum(linmin);
			}//edn for each kinematic varriable
		}//end for each topology
	}//end if show tag.



		///SigComp1: Final Plot Upper--plot the tag, combined bkg, all the MC, but not the ratio S/B ratio.
	if(showTag && (makeSigComp1 || makeSigComp1log)){
		for (int iTop = 0; iTop<nEventTopologies; iTop++) {
			for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++) {
				if (s_EventTopology[iTop].compare("metCut")==0 && s_KinemVars[kKinVar].compare("MET")==0 ) continue;

				string canvName = string("SigComp1_")+s_KinemVars[kKinVar]+s_EventTopology_v2[iTop];
				string canvName2 = string("SigComp1log_")+s_KinemVars[kKinVar]+s_EventTopology_v2[iTop];
				TCanvas* tempCanv = newTCanvas(canvName.data());
				tempCanv->SetTopMargin(0.06);
				tempCanv->SetBottomMargin(0.15);
				TCanvas* tempCanv2 = newTCanvas(canvName2.data());
				tempCanv2->SetTopMargin(0.06);
				tempCanv2->SetBottomMargin(0.15);

					//make an array of the signal dists in the tag region.
				TH1F* MC_hists[nDataAndMcFiles-1];
				int iter = 0;
				for (int jFile = 0; jFile < nDataAndMcFiles; jFile++) { //for each file
					if (indexNames[jFile].compare(Data) == 0 ) continue; // skip the data file, so really for each MC file
					MC_hists[iter] = KinVarHistMap[indexNames[jFile]][s_EventTopology[iTop]][s_KinemVars[kKinVar]][1];

					iter++;
				}
					//pull out the limit files.
				limit* theseLimits[nDataAndMcFiles-1];
				TPaveText *textlims = new TPaveText(0.751256,0.755181,0.90201,0.90544,"BLNDC");//Design Plots //Limit

				bool allthere = true;
				if(DrawLimits && KinvarIsLimit(s_KinemVars[kKinVar]) ){
					for (int i=0; i<nDataAndMcFiles-1; i++) allthere &= checkin(LimitContainers[i],s_EventTopology[iTop],s_KinemVars[kKinVar]);
					if(allthere){
						for (int i=0; i<nDataAndMcFiles-1; i++) theseLimits[i] = (*(LimitContainers[i]))[s_KinemVars[kKinVar]][s_EventTopology[iTop]];
						PrettyText(textlims,0.033); //Limit
						textlims->AddText("Observed Limits");
						for (int i=0; i<nDataAndMcFiles-1; i++){
							if (checkin(LimitContainers[i],s_EventTopology[iTop],s_KinemVars[kKinVar])) {
								textlims->AddText(Form("r < %f",theseLimits[i]->Observed));
							}
							else textlims->AddText("   "); //Limit
						}
					}//end if all there
				}

					///MAKE LINEAR ARRANGE3 PLOTS///
				TH1F** h =KinVarHistMap[Data][s_EventTopology[iTop]][s_KinemVars[kKinVar]];
				tempCanv->cd();
				TLegend* l1=makeL1_v2( 0.1997487,0.742228,0.3404523,0.9235751);

				PrettyHist(h[3],dgBkgThatchColor);//bkg
				PrettyHist(h[1],dataColor);//tag

				if (s_KinemVars[kKinVar].compare("HT") == 0) {
					h[3]->GetXaxis()->SetLabelSize(0.04);}

					//PrettyBlock2(h[3],kRed,4050);
				PrettyBlock2(h[3],kRed,3345,2);
					//PrettyBlock(h[3],kRed,string("transparent"));//PrettyMarker(h[3],kRed);
				PrettyMarker(h[1],kBlack,kFullCircle,1.3);

				for (int i=0; i<nDataAndMcFiles-1; i++) { //there should be nDataAndMcFiles -1 MC files
					PrettyHist(MC_hists[i],MCcolors[i]);
					PrettyMarker(MC_hists[i],MCcolors[i]);
					playNiceWithLegend(MC_hists[i],0.30,0.0);
				}
				h[3]->SetMinimum(0.0);
				float linmax = h[3]->GetMaximum();
				float linmin = h[3]->GetMinimum();

					//				RaiseRangeRoof(h[3],1.15);
					//				RaiseRangeRoof(h[1],1.15);
					//				cout<<"Try to play nice "<<	h[1]->GetMaximum()<<" "<<h[3]->GetMaximum()<<endl;
				playNiceWithLegend(h[1],0.30,0.0);
				playNiceWithLegend(h[3],0.30,0.0);
				playNiceWithLegend(h[5],0.30,0.0);
				playNiceWithLegend(h[6],0.30,0.0);
				for (int i=0; i<nDataAndMcFiles-1; i++){
					playNiceWithLegend(MC_hists[i],0.30,0.0);
					SameRange(h[3],MC_hists[i]);
				}
				SameRange(h[3],h[1]);
					//				cout<<"After attempt "<<h[1]->GetMaximum()<<" "<<h[3]->GetMaximum()<<endl;

				h[3]->Draw("e2p");
				if(showTag) h[1]->Draw("e1psame");//tag
					//already done
				for (int i=0; i<nDataAndMcFiles-1; i++) MC_hists[i]->Draw("same");
				h[3]->Draw("e2psame");
				h[1]->Draw("e1psame");
				l1->AddEntry(h[1],"Higgs Mass Region");
				l1->AddEntry(h[3],"Data Driven Background");
				for (int i=0; i<nDataAndMcFiles-1; i++){
					string lablestring = string("MC Signal: ")+MCpoints[i+1][0]->s_DataAndMcFiles_v4;
					l1->AddEntry(MC_hists[i],lablestring.c_str());
				}
				l1->Draw("same");
				if(DrawLimits&&allthere) textlims->Draw("same"); //Limit
				TEX_CMSPrelim->Draw("same");
				TEX_E_TeV->Draw("same");
				TEX_lumi_fb->Draw("same");

				if(makeSigComp1){
					if(writeRootFile) tempCanv->Write();
					if(saveImages)SaveCanvas(tempCanv,plotsdir+tempCanv->GetName(),savewhat);
				}
					///END MAKE LINEAR PLOTS///

					///MAKE LOG PLTOS///
					//TLegend* l2 = makeL1_v2();
				TLegend* l2 = makeL1_v2( 0.190955,0.756477,0.390704,0.92487); //0.414573, 0.819948, 0.614322, 0.92228);
				tempCanv2->cd();
				PrettyHist(h[3],dgBkgThatchColor);//bkg
				PrettyHist(h[1],dataColor);//tag

				if (s_KinemVars[kKinVar].compare("HT") == 0) {
					h[5]->GetXaxis()->SetLabelSize(0.04);}
				PrettyBlock2(h[3],kRed,3345,2);
					//PrettyBlock2(h[3],kRed,4050);
					//PrettyBlock(h[3],kRed,string("transparent"));//PrettyMarker(h[3],kRed);
				PrettyMarker(h[1],kBlack,kFullCircle,1.3);
				for (int i=0; i<nDataAndMcFiles-1; i++) { //there should be nDataAndMcFiles -1 MC files
					PrettyHist(MC_hists[i],MCcolors[i]);
					PrettyMarker(MC_hists[i],MCcolors[i]);
					playNiceWithLegendLog(MC_hists[i],0.30,0.05);
				}
					//				h[3]->SetMaximum(TMath::Max(100.,h[3]->GetMaximum()));
					//				h[3]->SetMinimum(0.05);
					//				h[1]->SetMinimum(0.05);
				playNiceWithLegendLog(h[1],0.3,0.05);
				playNiceWithLegendLog(h[3],0.3,0.05);
				playNiceWithLegendLog(h[6],0.3,0.05);
				playNiceWithLegendLog(h[5],0.3,0.05);
				for (int i=0; i<nDataAndMcFiles-1; i++){
					playNiceWithLegendLog(MC_hists[i],0.30,0.05); 
					SameRange(h[3],MC_hists[i]);
				}
				SameRange(h[1],h[3],h[5]);
				h[3]->SetMinimum(0.05);  
				tempCanv2->SetLogy();
				h[3]->Draw("e2p");
				h[1]->Draw("e1psame");//tag
					//	cout << "final MC integral "<<MC_hists[0]->Integral()<<endl;
				for (int i=0; i<nDataAndMcFiles-1; i++) MC_hists[i]->Draw("same");
				h[3]->Draw("e2psame");
				h[1]->Draw("e1psame");
				if(showTag) h[1]->Draw("e1psame");
				l2->AddEntry(h[1],"Higgs Mass Region");
				l2->AddEntry(h[3],"Data Driven Background");
				for (int i=0; i<nDataAndMcFiles-1; i++){
					string lablestring2 = string("MC Signal: ")+MCpoints[i+1][0]->s_DataAndMcFiles_v4;
					l2->AddEntry(MC_hists[i],lablestring2.c_str());
				}
				l2->Draw("same");
				if(DrawLimits&&allthere) textlims->Draw("same");//Limit
				TEX_CMSPrelim->Draw("same");
				TEX_E_TeV->Draw("same");
				TEX_lumi_fb->Draw("same");
				if(makeSigComp1log){
					if(writeRootFile) tempCanv2->Write();
					if(saveImages)SaveCanvas(tempCanv2,plotsdir+tempCanv2->GetName(),savewhat);
				}
				h[3]->SetMaximum(linmax);
				h[3]->SetMinimum(linmin);
				h[1]->SetMaximum(linmax);
				h[1]->SetMinimum(linmin);
			}//edn for each kinematic varriable
		}//end for each topology
	}//end if show tag.


		///Tag-Signal to Avg background Ratio. Plot the ratio of the two and nothing else.
	if(showTag && makeTagToBkgRatPlots){
		for (int iTop = 0; iTop<nEventTopologies; iTop++) {
			for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++) {
				if (s_EventTopology[iTop].compare("metCut")==0 && s_KinemVars[kKinVar].compare("MET")==0 ) continue;
				string canvName = string("TagToBkgRat_")+s_KinemVars[kKinVar]+s_EventTopology_v2[iTop];
				TCanvas* tempCanv = newTCanvas(canvName.data());
				tempCanv->SetTopMargin(0.06);
				tempCanv->SetBottomMargin(0.15);
				TH1F** h = KinVarHistMap[Data][s_EventTopology[iTop]][s_KinemVars[kKinVar]];
				tempCanv->cd();
				PrettyHist(h[8],TagToBkgRatColor);

				if (s_KinemVars[kKinVar].compare("HT") == 0) {
					h[8]->GetXaxis()->SetLabelSize(0.04);}

				PrettyMarker(h[8],kMagenta+2);
				h[8]->GetYaxis()->SetRangeUser(0.,5.);
				h[8]->Draw("e1p");
				TAxis* xaxis = h[7]->GetXaxis();
				TLine *OneLine = new TLine(xaxis->GetXmin(),1.0,xaxis->GetXmax(),1.0);
				OneLine->SetLineColor(kBlack);
				OneLine->SetLineWidth(2);
				OneLine->SetLineStyle(7);//dashed.
				OneLine->Draw("same");
				h[8]->Draw("e1psame");
				TLegend* l1 = makeL1_v2();
				l1->AddEntry(h[8],"Tag to Background Ratio");
				l1->Draw("same");
				TEX_CMSPrelim->Draw("same");
				TEX_E_TeV->Draw("same");
				TEX_lumi_fb->Draw("same");
				if(writeRootFile) tempCanv->Write();
				if(saveImages)SaveCanvas(tempCanv,plotsdir+tempCanv->GetName(),savewhat);//save as all types
			}//edn for each kinematic varriable
		}//end for each topology
	}//end if show tag.

		///Make Unit Norm Plots--plot The combined bkg and all the MC. Make sure this goes last!!
	if(makeNormPlots){
		for (int iTop = 0; iTop<nEventTopologies; iTop++) {
			for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++) {
				if (s_EventTopology[iTop].compare("metCut")==0 && s_KinemVars[kKinVar].compare("MET")==0 ) continue;

				string canvName = string("Norm_")+s_KinemVars[kKinVar]+s_EventTopology_v2[iTop];
					//			string canvName2 = string("Designlog_")+s_KinemVars[kKinVar]+s_EventTopology_v2[iTop];
				TCanvas* tempCanv = newTCanvas(canvName.data());
				tempCanv->SetTopMargin(0.06);
				tempCanv->SetBottomMargin(0.15);
					//			TCanvas* tempCanv2 = newTCanvas((char*)canvName2.c_str());


					//make an array of the signal dists in the tag region.
				TH1F* MC_hists[nDataAndMcFiles-1];

				int iter = 0;
				for (int jFile = 0; jFile < nDataAndMcFiles; jFile++) { //for each file
					if (indexNames[jFile].compare(Data) == 0 ) continue; // skip the data file, so really for each MC file
					MC_hists[iter] = KinVarHistMap[indexNames[jFile]][s_EventTopology[iTop]][s_KinemVars[kKinVar]][1];

					iter++;
				}


					///MAKE LINEAR ARRANGE3 PLOTS///
				TH1F** h =KinVarHistMap[Data][s_EventTopology[iTop]][s_KinemVars[kKinVar]];
				tempCanv->cd();
				TLegend* l1=makeL1_v2();

				float datanorm = h[3]->Integral();
				if (datanorm == 0 ) datanorm = 1;
				h[3]->Scale(1.0/datanorm);
				h[5]->Scale(1.0/datanorm);
				h[6]->Scale(1.0/datanorm);

				PrettyHist(h[3],dgBkgBoxColor);
				PrettyHist(h[5],lsbColor);
				PrettyHist(h[1],dataColor);
				PrettyHist(h[6],usbColor);
				PrettyBlock2(h[5],lsbColor,3354,2);//PrettyMarker(h[5],kBlue,4);
				PrettyBlock2(h[6],usbColor,3345,2);//PrettyMarker(h[6],kGreen,4);

				h[3]->SetFillStyle(0);//open rectangle
				h[3]->SetLineColor(dgBkgBoxColor);
				h[3]->SetLineWidth(4);

				if (s_KinemVars[kKinVar].compare("HT") == 0) {
					h[3]->GetXaxis()->SetLabelSize(0.04);}

					//PrettyBlock2(h[3],kRed,4050);
					//			PrettyBlock2(h[3],kRed,3345,2);
					//PrettyBlock(h[3],kRed,string("transparent"));//PrettyMarker(h[3],kRed);
				for (int i=0; i<nDataAndMcFiles-1; i++) { //there should be nDataAndMcFiles -1 MC files
					PrettyHist(MC_hists[i],MCcolors[i]);
					PrettyMarker(MC_hists[i],MCcolors[i]);
				}
				h[3]->SetMinimum(0.0);
				float linmax = h[3]->GetMaximum();
				float linmin = h[3]->GetMinimum();
					//			RaiseRangeRoof(h[3],1.25);
					//			RaiseRangeRoof(h[5],1.25);
					//			RaiseRangeRoof(h[6],1.25);
				playNiceWithLegend(h[3],0.30,0.0);
				playNiceWithLegend(h[6],0.30,0.0);
				playNiceWithLegend(h[5],0.30,0.0);
				SameRange(h[3],h[5],h[6]);
				for (int i=0; i<nDataAndMcFiles-1; i++){
					UnitNorm(MC_hists[i]);//->Scale(1.0/MC_hists[i]->Integral()); //set to unit norm
					playNiceWithLegend(MC_hists[i],0.30,0.0);
					SameRange(h[3],MC_hists[i]);
				}
				h[3]->Draw("e2p");

				for (int i=0; i<nDataAndMcFiles-1; i++) MC_hists[i]->Draw("same");
				h[5]->Draw("e2psame");
				h[6]->Draw("e2psame");
				h[3]->Draw("e2psame");
				l1->AddEntry(box,"Data Driven Background");//h[3]
				l1->AddEntry(h[5],"LSB Bkg Estimate");
				l1->AddEntry(h[6],"USB Bkg Estimate");

				for (int i=0; i<nDataAndMcFiles-1; i++){
					string lablestring = string("MC Signal: ")+MCpoints[i+1][0]->s_DataAndMcFiles_v4;
					l1->AddEntry(MC_hists[i],lablestring.c_str());
				}
				l1->Draw("same");
				TEX_CMSPrelim->Draw("same");
				TEX_E_TeV->Draw("same");
				TEX_lumi_fb->Draw("same");

				if(writeRootFile) tempCanv->Write();
				if(saveImages)SaveCanvas(tempCanv,plotsdir+tempCanv->GetName(),savewhat);
					///END MAKE LINEAR PLOTS///
				h[3]->SetMaximum(linmax);
				h[3]->SetMinimum(linmin);
				h[1]->SetMaximum(linmax);
				h[1]->SetMinimum(linmin);
			}//edn for each kinematic varriable
		}//end for each topology
	}//end if makeNormPlots

		///END MAKE PLOTS
	/*Debug*/ if(printlevel > 0) cout << "Close Files" << endl;
	printf("Closing output root file\n");
	fplots->Close();

	printf("Closing PostAnaAna files\n");
		//itterate over the map. close everything.
	for(int i=1;i<nDataAndMcFiles;i++) printf(".");
	printf("\n");
	PostAnaAnaFiles[Data][Data]->Close();
	for(int i=1;i<nDataAndMcFiles;i++){
		for (int jchan=0; jchan<nchannels; jchan++) {
			PostAnaAnaFiles[indexNames[i]][channel[jchan]]->Close();
		}
		printf(".");
		fflush(stdout);
	}
	printf("\n");

/*	printf("Closing raw files\n");
	iii=0;
	for( TFileMap::iterator i=MainAnaFiles.begin(); i!=MainAnaFiles.end(); ++i){
		if(iii%5==0) printf(".");
		i++;
	}
	printf(".\n");
	iii=0;
	for( TFileMap::iterator i=MainAnaFiles.begin(); i!=MainAnaFiles.end(); ++i){
		(*i).second->Close();
		if(iii%5==0) printf(".");
		fflush(stdout);
		iii++;
	}
	printf(".\n");*/


}//end format plots

void diphoMassPlot(TH1F* hdiPhoMass, TCanvas* canv, TF1* fitcurve){
	canv->SetTopMargin(0.06);
	canv->SetBottomMargin(0.15);
	TLatex * TEX_CMSPrelim = new TLatex(0.177136,0.953368,"CMS Preliminary 2013");
	PrettyLatex(TEX_CMSPrelim,0.03);
	TLatex * TEX_E_TeV = new TLatex(0.800251,0.953368,"#sqrt{s} = 8 TeV");
	PrettyLatex(TEX_E_TeV,0.03);
	TLatex * TEX_lumi_fb = new TLatex(0.621859,0.953368,Form("#intL dt = %.0f fb^{-1}",Integrated_Luminosity_Data));
	PrettyLatex(TEX_lumi_fb,0.03);
	canv->cd();
	PrettyHist(hdiPhoMass);
	float ymax = 0.5*hdiPhoMass->GetMaximum();
	hdiPhoMass->Draw();
	TLine *L_tag_ub = new TLine(tag_ub,0.,tag_ub,ymax);
	TLine *L_tag_lb = new TLine(tag_lb,0.,tag_lb,ymax);
	L_tag_ub->SetLineColor(4);
	L_tag_lb->SetLineColor(4);
	TLine *L_usb_lb = new TLine(usb_lb,0.,usb_lb,ymax);
	TLine *L_usb_ub = new TLine(usb_ub,0.,usb_ub,ymax);
	L_usb_lb->SetLineColor(2);
	L_usb_ub->SetLineColor(2);
	TLine *L_lsb_lb = new TLine(lsb_lb,0.,lsb_lb,ymax);
	TLine *L_lsb_ub = new TLine(lsb_ub,0.,lsb_ub,ymax);
	L_lsb_lb->SetLineColor(2);
	L_lsb_ub->SetLineColor(2);
	L_tag_ub->Draw("same");
	L_tag_lb->Draw("same");
	L_usb_lb->Draw("same");
	L_usb_ub->Draw("same");
	L_lsb_lb->Draw("same");
	L_lsb_ub->Draw("same");
	fitcurve->Draw("same");
	TEX_CMSPrelim->Draw("same");
	TEX_E_TeV->Draw("same");
	TEX_lumi_fb->Draw("same");
}


	//make the legends for BkgDemo_Diplot, allow the option of changing the position.
TLegend* makeL1(float f1,float f2,float f3,float f4){
		//TLegend* makeL1(float f1=0.652548,float f2=0.663899,float f3=0.852528,float f4=0.864219){
	TLegend * l1 = new TLegend(f1, f2, f3, f4);
	PrettyLegend(l1);
	l1->SetTextSize(0.03067876);
	return l1;
}
TLegend* makeL1_v2(float f1,float f2,float f3,float f4){ return makeL1(f1, f2, f3, f4); }
TLegend* makeL2(float f1,float f2,float f3,float f4){
		//TLegend* makeL2(float f1=0.651267,float f2=0.660256,float f3=0.851246,float f4=0.860577){
	TLegend * l2 = new TLegend(f1, f2, f3, f4);
	PrettyLegend(l2);
	l2->SetTextSize(0.03067876);
	return l2;
}

	//orphaned
void BkgDemo_Diplot(TCanvas* c, TH1F** h, TLegend* l1, TLegend* l2){ ////orphaned

		//Make a split canvas, comparison of methods and tag above, bkg subtracted tag below
		//	printf("\nDo BkgDemo_Diplot for canvas %s\n",c->GetName());
		//	printf("integrals stage1: tag %f usb %f lsb %f\n",h[1]->Integral(),h[5]->Integral(),h[6]->Integral());
	c->SetTopMargin(0.06);
	c->SetBottomMargin(0.15);
	string sp1 = string(c->GetName())+"_p1";
	string sp2 = string(c->GetName())+"_p2";
	TPad *p1 = new TPad((char*)sp1.c_str(),"",0.,0.3,1.,1.);
	p1->SetBottomMargin(0);
	p1->cd();
	//	c->Divide(1,2);
	//	c->cd(1);
	PrettyHist(h[5],kCyan-7);
	PrettyHist(h[1]);//kblack
	PrettyHist(h[6],kGreen-7);
	PrettyHist(h[3],kRed);//red
	PrettyHist(h[7],kTeal);
	//h[6] kMagenta+2
	PrettyMarker(h[5],kCyan-7,4);
	PrettyMarker(h[1],kFullCircle,1.3);
	PrettyMarker(h[6],kGreen-7);
	//PrettyBlock2(h[3],kRed,4050);
	PrettyBlock2(h[3],kRed,3345,2);
	//PrettyBlock(h[3],kRed,string("transparent"));//PrettyMarker(h[3],kRed);
	PrettyMarker(h[7],kTeal);
	//	h[5]->Scale(mHwidth/sidebandwidth);//lsb scaled
	//	h[6]->Scale(mHwidth/sidebandwidth);//usb scaled
	//	printf("integrals stage2: tag %f usb %f lsb %f\n",h[1]->Integral(),h[5]->Integral(),h[6]->Integral());
	//	printf("ranges maximi before setrange tag %f lsb %f, usb %f\n",h[1]->GetMaximum(),h[5]->GetMaximum(),h[6]->GetMaximum());
	SameRange(h[5],h[6],h[1]);
	//	printf("integrals stage3: tag %f usb %f lsb %f\n",h[1]->Integral(),h[5]->Integral(),h[6]->Integral());
	//	printf("ranges maximi before after tag %f lsb %f usb %f\n",h[1]->GetMaximum(),h[5]->GetMaximum(),h[6]->GetMaximum());
	h[6]->Draw("e1p");
	h[5]->Draw("e1psame");
	//	h[3]->Draw("e2psame");//bkg
	if(showTag) h[1]->Draw("e1psame");//tag
	TPad *p2 = new TPad((char*)sp2.c_str(),"",0.,0.125,1.,0.3);
	p2->SetTopMargin(0);
	p2->cd();
	//	c->cd(2);
	h[7]->Draw("e1p");//bkg subtracted tag

	p1->cd();
	//  c->cd(1);
	if(showTag) l1->AddEntry(h[1],"Higgs Mass Region");
	l1->AddEntry(h[5],"Low M sideband");
	l1->AddEntry(h[6],"Lower Mass Sideband");
	l1->Draw("same");
	p2->cd();
	//c->cd(2);
	l2->AddEntry(h[7],"Left/Right Sideband Ratio");
	l2->Draw("same");
	c->cd();
	p1->Draw();
	p2->Draw();
}//orphaned

void SaveCanvas(TCanvas * c, string fileNameAndDir, string FileTypes){
	/*
	 Supply a canvas, a name you'd like the file to have (possibly prefixed by a directory),
	 and a string containing the names of file extensons.  The default is to save as .C, .root, .pdf, .jpg, .gif, .png, and .eps
	 The filetype string is case insensitive.

	 For example
	 SaveCanvas(myCanvas, "plots/mycanvas")
	 saves canvas in dir plots as mycanvas.C, mycanvas.root, mycanvas.jpg
	 all types are saved.
	 SaveCanvas(myCanvas, "mycanvas","jpgif")
	 saves the canvas as mycanvas.jpg and mycanvas.gif
	 */

	TString TFileTypes = FileTypes;
	TFileTypes.ToLower();
	string lc_types = TFileTypes.Data();
	if(lc_types.find("c")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".C").c_str());
	if(lc_types.find("root")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".root").c_str());
	if(lc_types.find("pdf")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".pdf").c_str());
	if(lc_types.find("jpg")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".jpg").c_str());
	if(lc_types.find("gif")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".gif").c_str());
	if(lc_types.find("png")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".png").c_str());
	if(lc_types.find("eps")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".eps").c_str());
}


/*void LoadHistSet(TH1F** h, TFile* fin, TString prefix){
 TString names[7];
 for (int i = 0; i<7; i++) {
 names[i] = "h";
 names[i]+= prefix;
 }
 names[0]+="_lowSB";
 names[1]+="_tag";
 names[2]+="_upperSB";
 names[3]+="_bkg";
 names[4]+="_tag_subbkg";
 names[5]+="_lowSB_scaled";
 names[6]+="_upperSB_scaled";
 
 for (int i=0; i < nPhoMassAndBkgDists; i++) h[i] = (TH1F*) fin->Get(names[i]);
 }*/

bool KinvarIsLimit(string kinvar){
		//	true iff kinvar is in s_KinemVars_limit.
	for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++)
		if( kinvar.compare(s_KinemVars_limit[kKinVar]) == 0) //I think this is a "contains and starts at 0, not equality"
			if( s_KinemVars_limit[kKinVar].compare(kinvar) == 0)
				return true;

	return false;
}//end KinvarIsLimit

/*bool TopoIsLimit(string Topo){
		//	true iff Topo is in s_EventTopology_limit.
	for (int iTopo = 0; iTopo<nEventTopologies_limit; iTopo++)
		if( Topo.compare(s_EventTopology_limit[iTopo]) == 0) //I think this is a "contains and starts at 0, not equality"
			if( s_EventTopology_limit[iTopo].compare(Topo) == 0)
				return true;

	return false;
}//end TopoIsLimit*/

