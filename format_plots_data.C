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
//#include "params_arg.h"
#include<string.h>
#include<map>
using namespace std;
using namespace params;
TLegend* makeL1(float f1=0.652548,float f2=0.663899,float f3=0.852528,float f4=0.864219);
TLegend* makeL1_v2(float f1=0.19598,float f2=0.721154,float f3=0.395729,float f4=0.92033);
TLegend* makeL2(float f1=0.651267,float f2=0.660256,float f3=0.851246,float f4=0.860577);
void BkgDemo_Diplot(TCanvas* c, TH1F** h, TLegend* l1, TLegend* l2);
void diphoMassPlot(TH1F* hdiPhoMass, TCanvas* canv, TF1* fitcurve);
//void LoadHistSet(TH1F** h, TFile* fin, TString prefix);
void SaveCanvas(TCanvas * c, string fileNameAndDir, string FileTypes =  "crootpdfjpggifpngeps");


typedef std::map<string,TH1F*> LableHist;
typedef std::map<string,LableHist> Lable2Hist;
	//typedef map<string,Lable2Hist> Lable3Hist;

typedef std::map<string,TH1F**> LableHistArr;
typedef std::map<string,LableHistArr> Lable2HistArr;
typedef std::map<string,Lable2HistArr> Lable3HistArr;

typedef std::map<string,float> Labledflaot;


typedef std::map<string,TFile*> TFileMap;

void format_plots_data(){
	cout<<"hello world"<<endl;
	CMSStyle();
	
		///////////////////////////// Switcehs //////////////////////////////////////

        int nKinemVars = nKinemVars_all;
	string *s_KinemVars = s_KinemVars_all;


	int printlevel = 1;
	bool saveImages = true;
	
		///////////////////////////// File Work ///////////////////////////////////////
	/*Debug*/ if(printlevel > 0) cout << "Start File work" << endl;

		///INPUT FILES
	const int nDataAndMcFiles = 1;
	string Data = "Data";
	string s_DataAndMcFiles[nDataAndMcFiles]    = {Data};//** FOR INEDEXING
	string s_DataAndMcFiles_v4[nDataAndMcFiles] = {Data};

		///Output File
	TFile* fplots = new TFile(formatedplotsroot_data.c_str(),"RECREATE");

	TFileMap PostAnaAnaFiles;
	TFileMap MainAnaFiles;
	cout<<endl<<"Reading in data file "<<plotsAndBackground_data<<endl<<endl;
	PostAnaAnaFiles[Data] = new TFile(plotsAndBackground_data.c_str());
	MainAnaFiles[Data]    = new TFile(plotsroot_data.c_str());
	
//	PostAnaAnaFiles["st350ho200"] = new TFile(plotsAndBackground_mc.c_str());
//	MainAnaFiles["st350ho200"]    = new TFile(plotsroot_mc.c_str());

	cout<<endl<<"Writing finished plots to file "<<plotsroot_data<<endl<<endl;

		///////////////////////////// Other Lists ///////////////////////////////////////	
	/*Debug*/ if(printlevel > 0) cout << "Make Other Lists" << endl;


	
		/////////////// FOR INDEXING, USE THESE /////////////////////////
		///	string s_MassBkgDists[nPhoMassAndBkgDists]={lowSB,tag,upperSB,bkg,tag_subbkg,lowSB_scaled,upperSB_scaled};
		/// string s_EventTopology[nEventTopologies]={"","1Jb","3J","3Jb","metCut"};
		/// string s_KinemVars[nKinemVars]={"MET","ST","PtGG","HT","MHT"};
		/// string s_DataAndMcFiles[nDataAndMcFiles]={Data,"MC_st350ho200"...}
		/////////////////////////////////////////////////////////////////



		//	const int nEventTopologies = 5; // the number of types of cuts selected, like 1JB...
		//string s_EventTopology[nEventTopologies] = {"","1Jb","3J","3Jb","metCut"};//** FOR INEDEXING
	string s_EventTopology_v2[nEventTopologies];//{"","_1Jb","_3J","_3Jb","_metCut"};
	string s_EventTopology_v3[nEventTopologies];//{"","_1Jb_","_3J_","_3Jb_","_metCut_"};
	//s_EventTopology_v2[0]=s_EventTopology[0];
	//s_EventTopology_v3[0]=s_EventTopology[0];
	for (int i=0; i<nEventTopologies; i++) {
		s_EventTopology_v2[i] = string("_")+s_EventTopology[i];
		s_EventTopology_v3[i] = string("_")+s_EventTopology[i]+"_";
	}

	//const int nPhoMassAndBkgDists //lsb, tag, usb...
	//	string s_MassBkgDists[] = {"lowSB","tag","upperSB","bkg","tag_subbkg","lowSB_scaled","upperSB_scaled"};
	//	string s_MassBkgDists_v2[] = {"_lowSB","_tag","_upperSB","_bkg","_tag_subbkg","_lowSB_scaled","_upperSB_scaled"};
	string s_MassBkgDists_v2[nPhoMassAndBkgDists];
	for (int i=0; i<nPhoMassAndBkgDists; i++) {s_MassBkgDists_v2[i]=string("_")+s_MassBkgDists[i];}

	string s_DataAndMcFiles_v2[nDataAndMcFiles];
	string s_DataAndMcFiles_v3[nDataAndMcFiles];
	s_DataAndMcFiles_v2[0]=Data;//{Data,"MC_st350ho200"...}
	s_DataAndMcFiles_v3[0]=Data;//{Data,"MC","MC","MC"...}
	for (int i=1; i<nDataAndMcFiles; i++) {s_DataAndMcFiles_v3[i]=string("MC_")+s_DataAndMcFiles[i];}
	for (int i=1; i<nDataAndMcFiles; i++) {s_DataAndMcFiles_v3[i]=string("MC");}

		///////////////////////////// LUMI SCALES ///////////////////////////////////////
	/*Debug*/ if(printlevel > 0) cout << "Set Lumi Scales" << endl;
	Labledflaot lumiscalemap;
	lumiscalemap[Data] = 1.;
	const float Integrated_Luminosity_Data = 5.725; /*fb^-1*/
	lumiscalemap["st350ho200"] = (Integrated_Luminosity_Data * 447.4 /*fb*/)/((float) 1000000 /*events*/);


		//////////////////////////////////////////////////////////////////////////////
		///////////////////////////////Load h_mGG/////////////////////////////////////
	/*Debug*/ if(printlevel > 0) cout << "Load h_mGG" << endl;
		//load mGG_unsliced histograms from all files. 
	Lable2Hist h_mGG_unsliced;
	for (int jFile=0; jFile<nDataAndMcFiles; jFile++) { //loop over all files
		LableHist tmp; // this is the collection of histograms, indexed by topology name
		/*Debug*/ if(printlevel > 2) cout << "first loop, jFile = "<<jFile << endl;
		for (int iTop = 0; iTop<nEventTopologies; iTop++) {
			/*Debug*/ if(printlevel > 4) cout << "second loop, iTop = "<<iTop <<endl;
			string instring = string("h_mGG") +s_EventTopology[iTop] + "_unsliced";
			/*Debug*/ if(printlevel > 4) cout << "loading "<<instring<< " from file " << s_DataAndMcFiles[jFile] << " for topology "<<s_EventTopology[iTop] <<endl;
			tmp[s_EventTopology[iTop]] = (TH1F*)PostAnaAnaFiles[s_DataAndMcFiles[jFile]]->Get(instring.c_str());
			/*Debug*/ if(printlevel > 4) cout << "succeeded"<<endl;
			
				//fix the root names
			string newname = instring+"_"+s_DataAndMcFiles[jFile];
			/*Debug*/ if(printlevel > 4) cout << "resetting name to "<<newname<<" for topology "<<s_EventTopology[iTop]<<endl;
//			/*Debug*/ if(printlevel > 6) cout << tmp[s_EventTopology[iTop]]->Integral()<<endl;
			
			tmp[s_EventTopology[iTop]]->SetName((newname).c_str());
			/*Debug*/ if(printlevel > 4) cout << "succeeded"<<endl;
		}
		/*Debug*/ if(printlevel > 2) cout << "Attempting to write tmp to h_mGG_unsliced with tag "<<s_DataAndMcFiles[jFile] << endl;
		h_mGG_unsliced[s_DataAndMcFiles[jFile]] = tmp;
		/*Debug*/ if(printlevel > 2) cout << "succeeded"<<endl;
	}
//	TH1F* h_mGG_unsliced = (TH1F*)fin.Get("h_mGG_unsliced");
//	TH1F* h_mGG_1Jb_unsliced = (TH1F*)fin.Get("h_mGG_1Jb_unsliced");
	
		////////////////////////////// Load Kin Var Plots //////////////////////////////////////
	/*Debug*/ if(printlevel > 0) cout << "Load Kin Var Plots" << endl;
	Lable3HistArr KinVarHistMap;
	for (int jFile=0; jFile<nDataAndMcFiles; jFile++) {
		
		/*Debug*/ if(printlevel >2) cout << "first loop, jFile = "<<jFile <<endl;	
		Lable2HistArr tmpMapTopo;
		for (int iTop = 0; iTop<nEventTopologies; iTop++) {
			/*Debug*/ if(printlevel >4) cout << "second loop, iTop = "<<iTop <<endl;
			
			LableHistArr tmpMapKinVar;
			for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++) {
				/*Debug*/ if(printlevel >6) cout << "third loop, kKinVar = "<<kKinVar <<endl;
				
					//there is no MET dist for metCut, so don't try to load it. 
				if (s_EventTopology[iTop].compare("metCut") == 0 && s_KinemVars[kKinVar].compare("MET") == 0) continue;
				if (iTop == 2 && kKinVar==0) {cout << endl<<endl<<" ***** ERROR!! your attempt to skip metCut|MET failed"<<endl<<endl; 	}
				
				TH1F** tmpHistArray = new TH1F*[nPhoMassAndBkgDists];
					//LoadHistSet(hMET, &fin, "MET");
				for (int lMassDist=0; lMassDist < nPhoMassAndBkgDists; lMassDist++){
					/*Debug*/ if(printlevel >8) cout << "forth loop, lMassDist = "<<lMassDist <<" out of "<<nPhoMassAndBkgDists<<endl;
					string instring = string("h")+s_KinemVars[kKinVar]+s_EventTopology[iTop]+"_"+s_MassBkgDists[lMassDist];
					/*Debug*/ if(printlevel >8) cout << "Load hist "<<instring<< " from file "<< s_DataAndMcFiles[jFile] << " into tmpHistArray["<<lMassDist<<"]"<<endl;

					tmpHistArray[lMassDist] = (TH1F*) PostAnaAnaFiles[s_DataAndMcFiles[jFile]]->Get( instring.c_str() );
						//fix the root name
					string newname = instring+"_"+s_DataAndMcFiles[jFile];
					/*Debug*/ if(printlevel >8) cout << "rename hist "<<newname <<endl;
					tmpHistArray[lMassDist]->SetName((newname).c_str());
					/*Debug*/ if(printlevel >8) cout << "success" <<endl;
					string newtitle = string(";")+s_KinemVars[kKinVar]+" (GeV)";
					tmpHistArray[lMassDist]->SetTitle((char*)newtitle.c_str());
				}//end for every Mass Dist
				/*Debug*/ if(printlevel >6) cout << "load hist array into tmpMapKinVar for "<< s_KinemVars[kKinVar] <<endl;
				tmpMapKinVar[s_KinemVars[kKinVar]] = tmpHistArray;
								
			}//End for each kinematic varraible
			/*Debug*/ if(printlevel >4) cout << "load hist array into tmpMapTopo for "<< s_EventTopology[iTop] <<endl;
			tmpMapTopo[s_EventTopology[iTop]] = tmpMapKinVar;
			
		}//end for each topology
		/*Debug*/ if(printlevel >2) cout << "load hist array into KinVarHistMap for "<< s_DataAndMcFiles[jFile] <<endl;
		KinVarHistMap[s_DataAndMcFiles[jFile]] = tmpMapTopo;
	}//end for each file

	/*Debug*/ if(printlevel >2){
		cout << "***KinVarHistMap should now be loaded, but did it work?***"<<endl;
		//cout << "Data 1Jb MHT tag name:" <<KinVarHistMap["Data"]["1Jb"]["MHT"][1]->GetName()<<endl;
		//cout << "Data 3Jb MHT tag name:" <<KinVarHistMap["Data"]["3Jb"]["MHT"][1]->GetName()<<endl;
		//cout << "Data 1Jb ST tag name:" <<KinVarHistMap["Data"]["1Jb"]["ST"][1]->GetName()<<endl;
		//cout << "Data 1Jb MHT sb name:" <<KinVarHistMap["Data"]["1Jb"]["MHT"][5]->GetName()<<endl;
		cout << "Data MHT L/R bin 0:" <<KinVarHistMap["Data"]["NULL"]["MHT"][7]->GetBinContent(1)<<endl;
		cout << "Data HT L/R bin 0:" <<KinVarHistMap["Data"]["NULL"]["HT"][7]->GetBinContent(1)<<endl;
		cout << "Data ST L/R bin 0:" <<KinVarHistMap["Data"]["NULL"]["ST"][7]->GetBinContent(1)<<endl;
		cout << "***If this is printing, then the answer is probably Yes ***"<<endl;
	}

	
//	h_mGG_unsliced->SetName("h_mGG_unsliced");
/*	TH1F * hMET[nPhoMassAndBkgDists];
	LoadHistSet(hMET, &fin, "MET");

	TH1F * hST_1Jb[nPhoMassAndBkgDists];
	LoadHistSet(hST_1Jb,&fin,"ST_1Jb");
	*/
	
		////////////////////////////////////////////////////////////////////
		/*Debug*/ if(printlevel > 0) cout << "Load the Fit Curves" << endl;
		//load the fit curves for the data. 
	TF1* mgg_fit_curve[nEventTopologies];
	for (int iTop=0; iTop<nEventTopologies; iTop++) {
		/*Debug*/ if(printlevel > 1) cout << "first loop, iTop = "<<iTop <<endl;
		string instring = string("mgg") + s_EventTopology_v3[iTop] + "fit";
		/*Debug*/ if(printlevel > 1) cout << "instring = "<<instring <<endl;//mggNULLfit, am I naming it wrong? 
		mgg_fit_curve[iTop] = (TF1*)PostAnaAnaFiles[Data]->Get(instring.c_str());
		/*Debug*/ if(printlevel > 1) cout << "supposidly loaded it, try it "<<endl;
		/*Debug*/ if(printlevel > 1) cout << mgg_fit_curve[iTop]->GetProb() <<endl;//seg faults the first time it's exectuted. 
		
/*	mgg_fit_curve[0] = (TF1*)fin.Get("mggfit");
	mgg_fit_curve[1] = (TF1*)fin.Get("mgg_1Jb_fit");
	mgg_fit_curve[2] = (TF1*)fin.Get("mgg_3J_fit");
	mgg_fit_curve[3] = (TF1*)fin.Get("mgg_3Jb_fit");
	mgg_fit_curve[4] = (TF1*)fin.Get("mgg_metCut_fit");*/
	}
	
	
		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		/*Debug*/ if(printlevel > 0) cout << "Start Building Plots" << endl;

	fplots->cd();

		//if there is not a plots folder, make it. 
	
		/*Debug*/ if(printlevel > 0) cout << "Build mass plots" << endl;
	
		//diphoton mass plots, one for each data plot, for each topology. 
	for (int iTop = 0; iTop<nEventTopologies; iTop++) {
		/*Debug*/ if(printlevel > 1) cout << "first loop, iTop = "<<iTop <<endl;
		string canvName = string("c_mgg")+s_EventTopology_v2[iTop]+"_unsliced";
		/*Debug*/ if(printlevel > 1) cout << "made tempCanv with name "<<canvName  <<endl;
		TCanvas* tempCanv = newTCanvas((char*)canvName.c_str()); //char*error
		/*Debug*/ if(printlevel > 1) cout << "Enter the merky deptsh of diphoMassPlot"<<endl;
		diphoMassPlot(h_mGG_unsliced[Data][s_EventTopology[iTop]],tempCanv,mgg_fit_curve[iTop]);
		/*Debug*/ if(printlevel > 1) cout << "fin dinphoMass plot, try to write to fplots" <<endl;
		tempCanv->Write();
		if(saveImages) SaveCanvas(tempCanv,plotsdir+tempCanv->GetName(),"ggifpdfjpgepspng");//save as all types
		//if(saveImages) SaveCanvas(tempCanv,plotsdir+tempCanv->GetName(),"ggifpdfeps");//save as all types
	}	
	
		// %%%%%%%%%%%%%%%%%%%%%%%% Kinematics and backgrounds %%%%%%%%%%%%%%%%%
	/*Debug*/ if(printlevel > 0) cout << "Build Kin Var plots type 1" << endl;
		//Arrangement 1
        TH1F * box = new TH1F("box","asdf",1,0,1);
        box->SetMarkerColor(kRed);
        box->SetMarkerStyle(25);
        box->SetMarkerSize(2);
        box->SetLineColor(0);
		///Demonstrate background. Plot two side bands with their ratio as a sub-plot. include a switchable Tag.
	for (int iTop = 0; iTop<nEventTopologies; iTop++){
		for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++){
			/*Debug*/ if(printlevel >2) cout << "iTop="<<iTop<<" kKinVar="<<kKinVar<<endl;
			if (s_EventTopology[iTop].compare("metCut")==0 && s_KinemVars[kKinVar].compare("MET")==0 ){
				/*Debug*/ if(printlevel >2) cout << "skipping met plot for met cut"<<endl;
				continue;
			}
			string canvName = string("BkgFull_")+s_KinemVars[kKinVar]+s_EventTopology_v2[iTop];
			/*Debug*/ if(printlevel >6) {TH1F** h = KinVarHistMap[Data][s_EventTopology[iTop]][s_KinemVars[kKinVar]];
			/*Debug*/ if(printlevel >6) printf("Scan1 Ratio bin1 for %s %s  = %f\n",s_EventTopology[iTop].c_str(),s_KinemVars[kKinVar].c_str(),h[7]->GetBinContent(1));}
			TCanvas* tempCanv = newTCanvas((char*)canvName.c_str());
			BkgDemo_Diplot(tempCanv,
					 KinVarHistMap[Data][s_EventTopology[iTop]][s_KinemVars[kKinVar]],
						   makeL1(0.2072864,0.7203704,0.4070352,0.9203704),
						   makeL2(0.51005,0.706436,0.708543,0.902669));
			//tempCanv->Write();
			//if(saveImages)SaveCanvas(tempCanv,plotsdir+tempCanv->GetName(),"ggif");//save as all types
			//if(saveImages)SaveCanvas(tempCanv,plotsdir+tempCanv->GetName(),"ggifpdfeps");//save as all types
		}//edn for each kinematic varriable
	}//end for each topology


		///Demostrate background-upper. Plot the two side bands together, but ignore the ratio. (Arr2)
	for (int iTop = 0; iTop<nEventTopologies; iTop++) {		
		for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++) {
			if (s_EventTopology[iTop].compare("metCut")==0 && s_KinemVars[kKinVar].compare("MET")==0 ) continue;
			string canvName = string("Bkg1_")+s_KinemVars[kKinVar]+s_EventTopology_v2[iTop];
			string canvNamelog = string("Bkg1Log_")+s_KinemVars[kKinVar]+s_EventTopology_v2[iTop];
			TCanvas* tempCanv = newTCanvas((char*)canvName.c_str());
			TCanvas* tempCanvlog = newTCanvas((char*)canvNamelog.c_str());
			tempCanvlog->SetTopMargin(0.06);
                        tempCanvlog->SetBottomMargin(0.15);

			TH1F** h = KinVarHistMap[Data][s_EventTopology[iTop]][s_KinemVars[kKinVar]];
			tempCanv->cd();
			//RaiseRangeRoof(h[5],1.25);
			//RaiseRangeRoof(h[1],1.25);
			//RaiseRangeRoof(h[6],1.25);
			PrettyHist(h[5],kBlue);
			PrettyHist(h[1],1);
			PrettyHist(h[6],kGreen);
			PrettyHist(h[3],kRed);

//			string cname = tempCanv->GetName();
//			if(cname.find("_HT")!=string::npos)//if found "_HT" in the name
//				h[5]->GetXaxis()->SetLabelSize(0.04);
				//SPECIAL
			if (s_KinemVars[kKinVar].compare("HT") == 0) {
				h[5]->GetXaxis()->SetLabelSize(0.04);}

			PrettyBlock2(h[5],kBlue,3354,2);//PrettyMarker(h[5],kBlue,4);
			//PrettyBlock(h[5],kBlue,string("//thatch"));//PrettyMarker(h[5],kBlue,4);
			PrettyMarker(h[1]);
			PrettyBlock2(h[6],kGreen,3345,2);//PrettyMarker(h[6],kGreen,4);
			h[3]->SetFillStyle(0);//open rectangle
                        h[3]->SetLineColor(kRed);
                        h[3]->SetLineWidth(4);
			//PrettyBlock(h[6],kGreen,string("\\thatch"));//PrettyMarker(h[6],kGreen,4);
			playNiceWithLegend(h[3],0.30,0.0);
                        playNiceWithLegend(h[6],0.30,0.0);
                        playNiceWithLegend(h[5],0.30,0.0);
                        playNiceWithLegend(h[1],0.30,0.0);
			h[6]->SetMinimum(0.0);
			SameRange(h[1],h[3]);
			SameRange(h[5],h[6],h[1]);
			SameRange(h[1],h[3]);
			h[5]->Draw("e2p");
			h[6]->Draw("e2psame");
			h[3]->Draw("e2psame");
			//if(showTag) h[1]->Draw("e1psame");//tag
			TLegend* l1 = makeL1_v2(0.443467,0.720207,0.643216,0.919689);
			if(showTag) l1->AddEntry(h[1],"Higgs Mass Region");
			l1->AddEntry(h[5],"Lower Mass Sideband");
			l1->AddEntry(h[6],"Upper Mass Sideband");
			l1->AddEntry(box,"Data Driven Background");//h[3
			l1->Draw("same");
			tempCanv->Write();
			if(saveImages)SaveCanvas(tempCanv,plotsdir+tempCanv->GetName(),"ggif");//save as all types
			//if(saveImages)SaveCanvas(tempCanv,plotsdir+tempCanv->GetName(),"ggifpdfeps");//save as all types

			tempCanvlog->cd();
			h[5]->SetMinimum(0.05);
                        tempCanvlog->SetLogy();
			h[5]->Draw("e2p");
			h[6]->Draw("e2psame");
			h[3]->Draw("e2psame");
			l1->Draw("same");
			if(saveImages)SaveCanvas(tempCanvlog,plotsdir+tempCanvlog->GetName(),"ggif");//save as all types
			
		}//edn for each kinematic varriable
	}//end for each topology

		///Demostrate background--Ratio. Plot the ratio of the two side bands, and nothing else. 
	for (int iTop = 0; iTop<nEventTopologies; iTop++) {
		for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++) {
			/*Debug*/ if(printlevel >6) cout << "Data MHT L/R bin 0:" <<KinVarHistMap["Data"]["NULL"]["MHT"][7]->GetBinContent(1)<<endl;
			if (s_EventTopology[iTop].compare("metCut")==0 && s_KinemVars[kKinVar].compare("MET")==0 ) continue;
			string canvName = string("BkgRat_")+s_KinemVars[kKinVar]+s_EventTopology_v2[iTop];
			TCanvas* tempCanv = newTCanvas((char*)canvName.c_str());
			TH1F** h = KinVarHistMap[Data][s_EventTopology[iTop]][s_KinemVars[kKinVar]];
			/*Debug*/ if(printlevel >6)	printf("Scan2 Ratio bin1 for %s %s  = %f\n",s_EventTopology[iTop].c_str(),s_KinemVars[kKinVar].c_str(),h[7]->GetBinContent(1));
			tempCanv->cd();
			PrettyHist(h[7],kTeal);
			h[7]->GetYaxis()->SetRangeUser(0.,2.);
			if (s_KinemVars[kKinVar].compare("HT") == 0) {
				h[7]->GetXaxis()->SetLabelSize(0.04);}

			PrettyMarker(h[7],kTeal);
			h[7]->Draw("e1p");
			TAxis* xaxis = h[7]->GetXaxis();
			TLine *OneLine = new TLine(xaxis->GetXmin(),1.0,xaxis->GetXmax(),1.0);
			OneLine->SetLineColor(kBlack);
			OneLine->SetLineWidth(2);
			OneLine->SetLineStyle(7);//dashed.
			OneLine->Draw("same");
			h[7]->Draw("e1psame");
			TLegend* l1 = makeL1_v2(0.330402,0.836788,0.530151,0.919689);
			l1->AddEntry(h[7],"Lower/Upper Sideband Ratio");
			l1->Draw("same");
			
			tempCanv->Write();
			if(saveImages)SaveCanvas(tempCanv,plotsdir+tempCanv->GetName(),"ggif");//save as all types
			//if(saveImages)SaveCanvas(tempCanv,plotsdir+tempCanv->GetName(),"ggifpdfeps");//save as all types
		}//edn for each kinematic varriable
	}//end for each topology

		///END MAKE PLOTS
	/*Debug*/ if(printlevel > 0) cout << "Close Files" << endl;
	fplots->Close(); 
		//itterate over the map. close everything. 
	for( TFileMap::iterator i=PostAnaAnaFiles.begin(); i!=PostAnaAnaFiles.end(); ++i){
		(*i).second->Close();
	}
	for( TFileMap::iterator i=MainAnaFiles.begin(); i!=MainAnaFiles.end(); ++i){
		(*i).second->Close();
	}


}//end format plots

void diphoMassPlot(TH1F* hdiPhoMass, TCanvas* canv, TF1* fitcurve){
	canv->cd();
	PrettyHist(hdiPhoMass);
	float ymax = 0.75*hdiPhoMass->GetMaximum();
	hdiPhoMass->Draw();
	TLine *L_tag_ub = new TLine(tag_ub,0.,tag_ub,ymax);
	TLine *L_tag_lb = new TLine(tag_lb,0.,tag_lb,ymax);
	L_tag_ub->SetLineColor(4);
	L_tag_lb->SetLineColor(4);
	L_tag_ub->SetLineWidth(2);
	L_tag_lb->SetLineWidth(2);
	TLine *L_usb_lb = new TLine(usb_lb,0.,usb_lb,ymax);
	TLine *L_usb_ub = new TLine(usb_ub,0.,usb_ub,ymax);
	L_usb_lb->SetLineColor(2);
	L_usb_ub->SetLineColor(2);
	L_usb_lb->SetLineWidth(2);
	L_usb_ub->SetLineWidth(2);
	TLine *L_lsb_lb = new TLine(lsb_lb,0.,lsb_lb,ymax);
	TLine *L_lsb_ub = new TLine(lsb_ub,0.,lsb_ub,ymax);
	L_lsb_lb->SetLineColor(2);
	L_lsb_ub->SetLineColor(2);
	L_lsb_lb->SetLineWidth(2);
	L_lsb_ub->SetLineWidth(2);
	L_tag_ub->Draw("same");
	L_tag_lb->Draw("same");
	L_usb_lb->Draw("same");
	L_usb_ub->Draw("same");
	L_lsb_lb->Draw("same");
	L_lsb_ub->Draw("same");
	fitcurve->SetLineWidth(7);
	fitcurve->SetLineColor(kGreen+2);
	fitcurve->Draw("same");
}


	//make the legends for BkgDemo_Diplot, allow the option of changing the position. 
TLegend* makeL1(float f1,float f2,float f3,float f4){
		//TLegend* makeL1(float f1=0.652548,float f2=0.663899,float f3=0.852528,float f4=0.864219){
	TLegend * l1 = new TLegend(f1, f2, f3, f4);
	PrettyLegend(l1);
	return l1;
}
TLegend* makeL1_v2(float f1,float f2,float f3,float f4){ return makeL1(f1, f2, f3, f4); }
TLegend* makeL2(float f1,float f2,float f3,float f4){
		//TLegend* makeL2(float f1=0.651267,float f2=0.660256,float f3=0.851246,float f4=0.860577){
	TLegend * l2 = new TLegend(f1, f2, f3, f4); 
	PrettyLegend(l2);

	return l2;
}
void BkgDemo_Diplot(TCanvas* c, TH1F** h, TLegend* l1, TLegend* l2){
		//Make a split canvas, comparison of methods and tag above, bkg subtracted tag below
//	printf("\nDo BkgDemo_Diplot for canvas %s\n",c->GetName());
//	printf("integrals stage1: tag %f usb %f lsb %f\n",h[1]->Integral(),h[5]->Integral(),h[6]->Integral());
    string sp1 = string(c->GetName())+"_p1";
    string sp2 = string(c->GetName())+"_p2";
    TPad *p1 = new TPad((char*)sp1.c_str(),"",0.,0.3,1.,1.);
    p1->SetBottomMargin(0);
    p1->cd();
//	c->Divide(1,2);
//	c->cd(1);
	PrettyHist(h[3],kRed);
	PrettyHist(h[5],kBlue);
	PrettyHist(h[1]);
	PrettyHist(h[6],kGreen);
	//PrettyHist(h[3],kRed);
	PrettyHist(h[7],kTeal);
PrettyBlock2(h[5],kBlue,3354,2);
	//PrettyBlock(h[5],kBlue,string("//thatch"));//PrettyMarker(h[5],kBlue,4);
	PrettyMarker(h[1]);
PrettyBlock2(h[6],kGreen,3345,2);
	//PrettyBlock(h[6],kGreen,string("\\thatch"));//PrettyMarker(h[6],kGreen,4);
	//PrettyMarker(h[3],kRed);
	PrettyMarker(h[7],kTeal);
//	h[5]->Scale(mHwidth/sidebandwidth);//lsb scaled
//	h[6]->Scale(mHwidth/sidebandwidth);//usb scaled
//	printf("integrals stage2: tag %f usb %f lsb %f\n",h[1]->Integral(),h[5]->Integral(),h[6]->Integral());
//	printf("ranges maximi before setrange tag %f lsb %f, usb %f\n",h[1]->GetMaximum(),h[5]->GetMaximum(),h[6]->GetMaximum());
//	printf("integrals stage3: tag %f usb %f lsb %f\n",h[1]->Integral(),h[5]->Integral(),h[6]->Integral());
//	printf("ranges maximi before after tag %f lsb %f usb %f\n",h[1]->GetMaximum(),h[5]->GetMaximum(),h[6]->GetMaximum());
	h[3]->SetFillStyle(0);//open rectangle
	h[3]->SetLineColor(kRed);
	h[3]->SetLineWidth(4);

	h[6]->SetMinimum(0.0);
	//float linmax = h[6]->GetMaximum();
	//float linmin = h[6]->GetMinimum();
	playNiceWithLegend(h[6],0.30,0.0);
	playNiceWithLegend(h[3],0.30,0.0);
	playNiceWithLegend(h[5],0.30,0.0);
	playNiceWithLegend(h[1],0.30,0.0);
	SameRange(h[3],h[1]);
	SameRange(h[3],h[5],h[6]);
	SameRange(h[3],h[1]);
	h[3]->Draw("e2p");
	h[5]->Draw("e2psame");
	h[6]->Draw("e2psame");
	h[3]->Draw("e2psame");
	//if(showTag) h[1]->Draw("e1psame");//tag
	TPad *p2 = new TPad((char*)sp2.c_str(),"",0.,0.125,1.,0.3);
    p2->SetTopMargin(0);
    p2->cd();
//	c->cd(2);
	TAxis * x = h[7]->GetXaxis();
	TAxis * y = h[7]->GetYaxis();
	float fontsize = 0.25;
	float fontsizeY = 0.10;
	x->SetTitleSize(fontsize);
	y->SetTitleSize(fontsizeY);
	x->SetLabelSize(fontsize);
	y->SetLabelSize(fontsizeY);

	h[7]->GetYaxis()->SetRangeUser(0.,2.);
	h[7]->Draw("e1p");
	TLine *OneLine = new TLine(x->GetXmin(),1.0,x->GetXmax(),1.0);
	OneLine->SetLineColor(kBlack);
	OneLine->SetLineWidth(2);
	OneLine->SetLineStyle(7);//dashed.
	OneLine->Draw("same");
	h[7]->Draw("e1psame");
	
	p1->cd();
//  c->cd(1);
	if(showTag) l1->AddEntry(h[1],"Higgs Mass Region");
        TH1F * box = new TH1F("box","asdf",1,0,1);
        box->SetMarkerColor(kRed);
        box->SetMarkerStyle(25);
        box->SetMarkerSize(2);
        box->SetLineColor(0);
	l1->AddEntry(box,"Data Driven Background");
	l1->AddEntry(h[5],"Lower Mass Sideband");
	l1->AddEntry(h[6], "Upper Mass Sideband");
	l1->Draw("same");
	p2->cd();
		//c->cd(2);
	l2->SetTextSize(fontsize*0.8);
	l2->AddEntry(h[7],"Lower/Upper Sideband Ratio");
	l2->Draw("same");
    c->cd();
	p1->Draw();
	p2->Draw();
}

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
