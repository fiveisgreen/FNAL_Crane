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
#include <sstream>
#include "TString.h"
#include <fstream>
#include "TF1.h"
#include "TLine.h"
	//#include "quicksave.C"
#include "CMSStyle.C"
#include "utilities.h"
#include "util.C"
#include "params_arg.h"
	//#include "params_arg.h"
#include<string.h>
#include<map>
#include "MCpoint.h"
#include <algorithm>    // std::sort
#include <vector>
#include "Interpolate.h"


using namespace std;
using namespace params;

struct limit{
	float Observed;
	float Expected2_5;
	float Expected16;
	float Expected50;
	float Expected84;
	float Expected97_5;
	string pointName;
	string topo;
	string kinvar;
	limit(){}
	~limit(){}
};

typedef std::map<string,float> Labeledflaot;
typedef std::map<string,int> Labeledint;
//typedef std::map<string,TFile*> TFileMap;
typedef std::map<string,limit*> LabelLim;
typedef std::map<string,LabelLim> Label2Lim;
typedef std::map<string,Label2Lim> Label3Lim;
typedef std::map<string,TH1F*> LableHist;
typedef std::map<string,TH2F*> LableHist2;



//void RetrieveLimit();
TString makeFileName(MCpoint* thispoint);
void suckinfile(Label2Lim* contianer, string pointName);
void suckinfile(Label2Lim* contianer, MCpoint* thispoint);
void suckinallfiles(int type, Label3Lim* allLims);
void printLimit(TString MassPoint, TString topo, TString kinvar, bool show_observed = false);
bool checkin(Label2Lim* contianer,TString topo, TString kinvar);
bool checkin(Label3Lim* contianers,TString MassPoint, TString topo, TString kinvar);
//void MakeLimitPlot(Labeledflaot& ObservedLimit);
void GetBestLim(TString MassPoint);
limit * GetBestLim(Label2Lim* contianer, TString MassPoint, bool announceIt=false);
void WhatCanExclude(TString MassPoint,int max = -1,bool sort = true);
bool betterlim(limit* a,limit* b);

TCanvas* MakeLimitPlot(TString topo, TString kinvar, bool showData=false, bool saveplot = true);
TCanvas* MakeLimitPlot(Label3Lim* allLims, TString topo, TString kinvar, bool showData=false, bool saveplot = true);

TCanvas* MakeXSecPlot(bool saveplot = true);

int suckinRawLogFile(MCpoint* thispoint,Labeledint & nPass);
TCanvas* MakeEffPlot(string topo, bool saveplot = true);
void MakeEffPlots(bool saveplot = true);



//TCanvas* MakeEfficiencyPlot(TString topo, TString kinvar, bool saveplot = true);
//TCanvas* MakeEfficiencyPlot(Label3Lim* allLims, TString topo, TString kinvar, bool saveplot = true);

//void SetupLimit();
void RetrieveLimit()
{
	//this just tests stuff
	cout<<"hello world"<<endl;
	Label3Lim * allLims = new Label3Lim();
	suckinallfiles(2, allLims);
		//itterate over it,
	for (Label3Lim::iterator it=allLims->begin(); it!=allLims->end(); ++it){
		std::cout << "** Caught limit file for "<<it->first << " kinvar-submap size: "<< it->second.size() <<endl;
		if (it->second.size() == 0) cout<<"     NOTE that it's empty!"<<endl;
	}
}//end RetrieveLimit
	//currently used to test out suckinallfiles, which seems to work fine. 

void suckinfile(Label2Lim* contianer, string pointName){
		//working!
	MCpoint* thispoint = setupMCpoint(pointName);
	suckinfile(contianer, thispoint);
}//works
void suckinfile(Label2Lim* contianer, MCpoint* thispoint){
	/*
	 open limit results from one mass point.

	 this is to use the compressed files.
	 infile has entries of the form
	   2JbMLm20
	   MET
	   5.0119
	   1.8288
	   2.5127
	   3.6719
	   5.5307
	   8.0620
	 these are produced in the order:
		for every kinvar
		  for every topo.
	 */
	bool debug = false;
	string filename = makeFileName(thispoint).Data();
	if(debug) printf("*************Reaching for file %s*********************\n",filename.data());
	ifstream infile;
	infile.open(filename.data(),ifstream::in);
	if(!infile.is_open()){
		printf("WARNING: FILE NOT FOUND %s \t\t(seen by suckinfile)\n",filename.data());
		return; //if file doesn't exist, return
	}
	bool keepgoing = true;
	do {

		limit *newlim = new limit();
		newlim->pointName = thispoint->pointName;
		keepgoing = keepgoing && infile>>newlim->topo;
//		if(debug) cout<<" topo: "<<newlim->topo<<endl;
		if(keepgoing){
			keepgoing = keepgoing && infile>>newlim->kinvar;//may have to strip this.
			if(debug) printf("suckingile finds entry for %s %s\n",newlim->topo.data(), newlim->kinvar.data());
		}
		if(keepgoing){
			keepgoing = keepgoing && infile>>newlim->Observed;//may have to strip this.
//			if(debug) cout<<" obs: "<<newlim->Observed<<endl;
		}
		if(keepgoing) keepgoing = keepgoing && infile>>newlim->Expected2_5;
		if(keepgoing) keepgoing = keepgoing && infile>>newlim->Expected16;
		if(keepgoing) keepgoing = keepgoing && infile>>newlim->Expected50;
		if(keepgoing) keepgoing = keepgoing && infile>>newlim->Expected84;
		if(keepgoing) keepgoing = keepgoing && infile>>newlim->Expected97_5;
		if (keepgoing) {
			if(debug) printf("found all materials, storing the limit\n");
			(*contianer)[newlim->kinvar][newlim->topo]=newlim;
		}
	} while (keepgoing);

		//ok, lets try counting how many things are in container.
//	cout<<"lets see what we inhaled and metabolized"<<endl;
//	for (Label2Lim::iterator it=contianer->begin(); it!=contianer->end(); ++it){
//		std::cout << it->first << endl; //it->second << '\n';
//		for (LabelLim::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
//			std::cout << "      "<<it2->first << endl; //we conclusively have constructed a map of maps with all the entries we expected to have.
//				//now lets try to access something, anything out of this.
//			cout<< it2->second->topo << " "<<it2->second->kinvar<<endl;
//
//		}
//	}
//
//	cout<<"test1"<<endl;
//	limit* thislim = (*contianer)["MET"]["NULL"];
//	cout<<"test2"<<endl;
//	printf("ok, try to get topo for NULL/MET %s\n", thislim->topo.data()); //pukes like crazy.
//	cout<<"test3"<<endl;

}//end suckinfiles

void suckinallfiles(int type, Label3Lim* allLims){
		//load all numbers from LimitResultBundle_*_reduced.txt from all files with MCpoint type = type
	std::vector<MCpoint*> vp = setupMCpoints();
	std::vector<MCpoint*>::iterator thispoint = vp.begin();
	while (thispoint != vp.end() ){
		if((*thispoint)->gettype()==type_to_run){
			Label2Lim * contianer = new Label2Lim();
			suckinfile(contianer,*thispoint);
			(*allLims)[(*thispoint)->pointName] = *contianer;
		}
		thispoint++;
	}//end while
}//end suckinallfile
	//seems to work 

void printLimit(TString MassPoint, TString topo, TString kinvar, bool show_observed){
		//print limits seen on one mass point.
		//working!
	MCpoint *thispoint = setupMCpoint(MassPoint.Data());
	Label2Lim* contianer = new Label2Lim();
	suckinfile(contianer,thispoint->pointName);
	if(!checkin(contianer,topo,kinvar)) return; //make sure it exists. 

	limit* thislim = (*contianer)[kinvar.Data()][topo.Data()];
	printf("Limits for %s, %s %s\n",thislim->pointName.data(),thislim->topo.data(),thislim->kinvar.data());

	if (show_observed)	printf("observed limit: %f\n",thislim->Observed);
	printf("Expected limit 2.5%%: %f\n",thislim->Expected2_5);
	printf("Expected limit 16%%: %f\n",thislim->Expected16);
	printf("Expected limit 50%%: %f\n",thislim->Expected50);
	printf("Expected limit 84%%: %f\n",thislim->Expected84);
	printf("Expected limit 97.5%%: %f\n",thislim->Expected97_5);
}//end printLimit
	//works.

TString makeFileName(MCpoint* thispoint){
	return thispoint->makeLimitResultBundleName().ReplaceAll(".txt","_reduced.txt");
}//works.

bool checkin(Label2Lim* contianer,TString topo, TString kinvar){
		//returns true if the container has an entry for [kinvar][topo], else false
	if((*contianer).count(kinvar.Data()) > 0){
		if((*contianer)[kinvar.Data()].count(topo.Data()) > 0)	return true;
		else{
			printf("Warning: Found entry in container for kinvar %s but not for topo %s\n",kinvar.Data(),topo.Data());
			return false;
		}
	}
	else{
		printf("Warning: Found no entry in container for kinvar %s for any topology\n",kinvar.Data());
		return false;
	}
}//end checkin for Label2Lim
bool checkin(Label3Lim* contianers,TString MassPoint, TString topo, TString kinvar){
		//returns true if the containers has an entry for [masspoint][kinvar][topo], else false
	if((*contianers).count(MassPoint.Data()) > 0){
		if ((*contianers)[MassPoint.Data()].count(kinvar.Data()) > 0) {
			if((*contianers)[MassPoint.Data()][kinvar.Data()].count(topo.Data()) > 0)	return true;
			else{
				printf("Warning: Found no entry for topo %s with MassPoint %s and kinvar %s\n",topo.Data(),MassPoint.Data(),kinvar.Data());
				return false;
			}
		}
		else{
			printf("Warning: Found no entry in container for %s with MassPoint %s with any topology\n",kinvar.Data(),MassPoint.Data());
			return false;
		}
	}//end if found mass point
	else{ //no mass point
		printf("Warning: Found no entry in containers for MassPoint %s\n",MassPoint.Data());
		return false;
	}
}//end checkin for Label3Lim

void GetBestLim(TString MassPoint){
		//return best expected limit
	Label2Lim * contianer = new Label2Lim();
	suckinfile(contianer,MassPoint.Data());
	GetBestLim(contianer, MassPoint,true);
}
limit * GetBestLim(Label2Lim* contianer, TString MassPoint, bool announceIt){
		//return best expected limit
	limit *bestlim = new limit();
	bestlim->Expected50 = 100000;
	if ((*contianer).empty()) {
		printf("WARNING! Trying to get best expected limit for empty container; Masspoint %s\n",MassPoint.Data());
		return bestlim;
	}
	for (Label2Lim::iterator it=contianer->begin(); it!=contianer->end(); ++it){
		for (LabelLim::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
			if(it2->second->Expected50 < bestlim->Expected50) bestlim = it2->second;
		}
	}//end fors
	if (announceIt) {
		printf("For Masspoint %s, The best Expected Limit is r < %f for %s, %s\n",MassPoint.Data(),bestlim->Expected50,bestlim->topo.data(),bestlim->kinvar.data());
	}
	return bestlim;
}

void WhatCanExclude(TString MassPoint,int max,bool sort){
		//prints a list of topos and kinvars that are expected to exclude this masspoint.
		//if sort, we get an ordered, numbered list of the top [max] performers.
		//if max < 0 or we're not sorting, we print them all. 
	Label2Lim * contianer = new Label2Lim();
	suckinfile(contianer,MassPoint.Data());
	if ((*contianer).empty()) {
		printf("WARNING! Trying to get best expected limit for empty container; Masspoint %s\n",MassPoint.Data());
		return;
	}

	vector<limit*> excLims;
	for (Label2Lim::iterator it=contianer->begin(); it!=contianer->end(); ++it){
		for (LabelLim::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
			if(it2->second->Expected50 < 1.0) excLims.push_back(it2->second);
		}
	}//end fors
	if (sort) {
		std::sort (excLims.begin(), excLims.end(), betterlim);
			//loop over the
		int i = 1;
		for (std::vector<limit*>::iterator it = excLims.begin() ; it != excLims.end(); ++it){
			if(max>0 && i>= max) break;
			printf("%i    Expected limit for %s %s, masspoint %s: %f\n",i,(*it)->topo.data(),(*it)->kinvar.data(),MassPoint.Data(),(*it)->Expected50);
			i++;
		}
	}
	else{
		for (std::vector<limit*>::iterator it = excLims.begin() ; it != excLims.end(); ++it){
			printf("Expected limit for %s %s, masspoint %s: %f\n",(*it)->topo.data(),(*it)->kinvar.data(),MassPoint.Data(),(*it)->Expected50);
		}
	}
}//end WhatCanExclude

bool betterlim(limit* a,limit* b){return a->Expected50 < b->Expected50;} //return true iff a is a stronger limit than b


/*
void MakeLimitPlot(Labeledflaot& ObservedLimit){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	gStyle->SetPadLeftMargin(0.15);
	TString option2D = "COL Z";


	std::vector<MCpoint*> points = setupMCpoints();
		//first count them
	int nMCpoints = 0;
	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
		if((*it)->type != 2) continue;
		nMCpoints++;
	}
	float Mstop[15] =   {185,210,235,260,285,310,335,360,385,410 ,460,510,1010,1510,2010};
	float Mhiggsino[21] = {150,175,225,250,275,300,325,375,425,475 ,525,575,625,675,725,825,925,1025,1125,1225 ,1525};

		//open a file
		//for every topo in the map
		//for every kinvar in the map


		//loop over all the mass points,
		//make six 2D plots
		//save those
		//format others into something presentable. 



}//end MakeLimitPlot
*/

TCanvas* MakeLimitPlot(TString topo, TString kinvar, bool showData,bool saveplot ){
	Label3Lim* allLims = new Label3Lim();
	return MakeLimitPlot(allLims, topo, kinvar, showData,saveplot);
}

TCanvas* MakeLimitPlot(Label3Lim* allLims, TString topo, TString kinvar, bool showData, bool saveplot){
	printf("hello world\n");
		//setup up general style
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	gStyle->SetPadLeftMargin(0.15);
	CMSStyle();
		//setup bins
//	const int nS = 15;
//	const int nH = 21;
//	float mSVals[nS] = {185,210,235,260,285,310,335,360,385,410,460,510,1010,1510,2010};//nominal mass points.
//	float mHVals[nH] = {150,175,225,250,275,300,325,375,425,475,525,575,625,675,725,825,925,1025,1125,1225 ,1525};
	const int nS = 11; //xBinning
	const int nH = 19;
	/*if(type_to_run == 2){
		nS = 12;
		nH = 11;
		float mSVals[nS] = {185,210,235,260,285,310,335,360,385,410,460,510};//nominal mass points.
		float mHVals[nH] = {150,175,200,225,250,275,300,325,375,425,475};
	}
	if(type_to_run >= 10){
		nS = 11;
		nH = 11;*/
//		float mSVals[nS] = {185,210,260,285,310,335,360,385,410,460,510,660,710};
//		float mHVals[nH] = {150,175,200,225,250,275,300,325,375,425,475,525,575,625,675};
	float mSBins[nS+1] = {187.5, 212.5, 237.5 ,262.5 ,287.5, 312.5, 337.5, 362.5,    375, 425, 475, 525};
	float mHBins[nH+1] = {130, 140, 160, 190, 210,    220, 230, 235,245, 255,     260, 270, 280, 285,295,     305, 310,320, 330,370};


	/*float* mSBins = new float[nS+1];
	float* mHBins = new float[nH+1];
	mSBins[0] = mSVals[0] - 12.5;
	mHBins[0] = mHVals[0] - 12.5;
	mSBins[nS] = mSVals[nS-1] + 25;//250;
	mHBins[nH] = mHVals[nH-1] + 25;//150;
	for(int i=1; i<nS; i++) mSBins[i] = 0.5*(mSVals[i-1]+mSVals[i]);
	for(int i=1; i<nH; i++) mHBins[i] = 0.5*(mHVals[i-1]+mHVals[i]);*/

		//Make the hists and canvas
	TString plotname = "Limits_"+topo+kinvar;
	const int nlimit = 7;
	TString limitname[nlimit] = {"limit", "exp", "exp_1L","exp_1H","exp_2L","exp_2H","xsec"};
	TString limitname2[nlimit] = {"observed", "exp", "exp_1L","exp_1H","exp_2L","exp_2H","xsec"};
	TH2D* h_limit[nlimit];
	TH2D* h_limit_cs[nlimit];
	h_limit[0] = new TH2D(limitname[0],limitname[0]+";Stop Mass (GeV);Higgsino Mass (GeV);Observed r-value",nS,mSBins,nH,mHBins);
	h_limit_cs[0] = new TH2D(limitname[0]+"_cs",limitname[0]+";Stop Mass (GeV);Higgsino Mass (GeV);Observed Excluded Cross Section (fb)",nS,mSBins,nH,mHBins);
	for(int i=1; i<nlimit; i++) {
		h_limit[i] = new TH2D(limitname[i],limitname[i]+";Stop Mass (GeV);Higgsino Mass (GeV);Expected r-value",nS,mSBins,nH,mHBins);
		h_limit_cs[i] = new TH2D(limitname[i]+"_cs",limitname[i]+";Stop Mass (GeV);Higgsino Mass (GeV);Expected Exclusion Cross Section (fb)",nS,mSBins,nH,mHBins);
	}

		//Fetch all data:
	suckinallfiles(2, allLims); //xxx this doesn't work right. allLimits comes back quite incomplete.
	std::vector<MCpoint*> points = setupMCpoints();
	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
		if((*it)->gettype() != type_to_run) continue;
		if ((*it)->Mstop > 510) continue;
		int temp =(*it)->Mstop;
		if((*it)->Mstop == 325 && (*it)->Mhiggsino == 315) continue; 
		if(temp == 375 || temp == 425) continue;
		if (!checkin(allLims,(*it)->pointName, topo, kinvar)) continue;
		limit *thislim = (*allLims)[(*it)->pointName][kinvar.Data()][topo.Data()];
/*O*/	h_limit[0]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Observed);
/*50*/	h_limit[1]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected50);
/*16%*/	h_limit[2]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected16);
/*84%*/	h_limit[3]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected84);
/*2.5%*/h_limit[4]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected2_5);
/*97.5*/h_limit[5]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected97_5);
		h_limit[6]->Fill((*it)->Mstop,(*it)->Mhiggsino,3.0/((*it)->cs*Integrated_Luminosity_Data)); //max possible r given cs and lumi

		/*O*/	h_limit_cs[0]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Observed * (*it)->cs_fb());
		/*50*/	h_limit_cs[1]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected50 * (*it)->cs_fb());
		/*16%*/	h_limit_cs[2]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected16 * (*it)->cs_fb());
		/*84%*/	h_limit_cs[3]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected84 * (*it)->cs_fb());
		/*2.5%*/h_limit_cs[4]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected2_5 * (*it)->cs_fb());
		/*97.5*/h_limit_cs[5]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected97_5 * (*it)->cs_fb());

	}
	//fill pot holes
		//interpolate collumns, keeping triangularity
	for (int i=0; i<7; i++) interpolate_Zywicki(h_limit[i]);
	for (int i=0; i<6; i++) interpolate_Zywicki(h_limit_cs[i]);

/*	for(int i= 0;i<7;i++){
		//this compensates for the missing points (385,275),(410,300),(460,325)
		//h_limit[i]->SetBinContent(9,4, h_limit[i]->GetBinContent(9,5));//fake pothol
		h_limit[i]->SetBinContent(9,6, h_limit[i]->GetBinContent(9,7));
		h_limit[i]->SetBinContent(10,7, h_limit[i]->GetBinContent(10,8));
		h_limit[i]->SetBinContent(11,8, h_limit[i]->GetBinContent(11,9));
	}*/

	h_limit[0]->SaveAs("probeExclusion.root");//xxx

	TGraph* curve[6];//6 ~= nlimit
	TH1F* legcurve[6];
	for (int i=0; i<6; i++) { //6 ~= nlimit
			//		curve[i] = getContour1(h_limit[i],"excl_curve_"+limitname2[i]+"_"+topo+"_"+kinvar);//dongwook's way; abandon this
			//curve[i] = getContourBarker(h_limit[i],"excl_curve_"+limitname2[i]+"_"+topo+"_"+kinvar);
		printf("try to get cure for %s\n",limitname2[i].Data());
		curve[i] = getContourBarker_fancy(h_limit[i],"excl_curve_"+limitname2[i]+"_"+topo+"_"+kinvar);
		printf("got curve\n");
//		printf("got limit\n");
		legcurve[i] = new TH1F("excl_curve_"+limitname2[i]+"_"+topo+"_"+kinvar,"asdf",1,0,1);//dummy histograms for use in legend
		legcurve[i]->SetMarkerStyle(0);
	}

		//	for(int i=0; i<nlimit; i++) fillPotHoles( h_limit[i] ) ; //this is bad magic


		///Save the r-value exclusion plots
	TCanvas* canv = new TCanvas(plotname.Data(),plotname.Data(),800,600);
	canv->SetTopMargin(0.06);
	canv->SetBottomMargin(0.15);
	canv->SetRightMargin(0.2);
	h_limit[0]->GetXaxis()->SetNdivisions(505);
	h_limit[0]->GetYaxis()->SetNdivisions(505);
	h_limit[0]->GetYaxis()->SetTitleOffset(1.2);
	h_limit[0]->GetZaxis()->SetTitleOffset(1.3);

	gStyle->SetPalette(1);
	h_limit[0]->SetMaximum(1.2);//main background color is observed
	h_limit[0]->SetMinimum(0);
	h_limit[0]->GetXaxis()->SetRangeUser(180,510);
	h_limit[0]->GetYaxis()->SetRangeUser(130,500);
	PrettyFonts(h_limit[0]);
	h_limit[0]->Draw("COL Z");
	if (showData) {
		PrettyGraph(curve[0],kBlack,5,1);
		PrettyHist(legcurve[0],kBlack,5,1);
		curve[0]->Draw("sameL");
	}
	PrettyGraph(curve[1],kBlue,3,7);
	PrettyHist(legcurve[1],kBlue,3,7);
	PrettyGraph(curve[2],kBlue,3,3);
	PrettyHist(legcurve[2],kBlue,3,3);
	PrettyGraph(curve[3],kBlue,3,3);
	PrettyHist(legcurve[3],kBlue,3,3);
	
	curve[1]->Draw("sameL");
	curve[2]->Draw("sameL");//1 sigma low
	curve[3]->Draw("sameL");//1sigma high.

	TLegend * leg = new TLegend(0.193467,0.793706,0.393216,0.924825);
	PrettyLegend(leg);
	leg->AddEntry(legcurve[1],"#sigma (Expected)");
	leg->AddEntry(legcurve[2],"#sigma (Expected #pm 1#sigma exp.)");
	if(showData )leg->AddEntry(legcurve[0],"#sigma (Observed)");
	leg->Draw("same");
		//the contour plot method--embaressingly easy to draw, but then you would have to cull the points.
//	TH2D* h_cont = (TH2D*) h_limit[0]->Clone("cont");
//	Double_t cont[1] = {1.0};
//	h_cont->SetContour(1, cont);
//	h_cont->Draw("same CONT2");

	canv->SetTopMargin(0.06);
	canv->SetBottomMargin(0.15);
	if (saveplot) { //replace this by sending RetrieveLimit and sending it to format_plot_combined::SaveCanvas.
		canv->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+".gif");
		canv->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+".pdf");
//		canv->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+".C");
	}

		///Save the cross section exclusion plots
	TCanvas* canv2 = new TCanvas((plotname+"_cs").Data(),(plotname+"_cs").Data(),800,600);
	canv2->SetTopMargin(0.06);
	canv2->SetBottomMargin(0.15);
	canv2->SetRightMargin(0.2);
	h_limit_cs[0]->GetXaxis()->SetNdivisions(505);
	h_limit_cs[0]->GetYaxis()->SetNdivisions(505);
	h_limit_cs[0]->GetYaxis()->SetTitleOffset(1.2);
	h_limit_cs[0]->GetZaxis()->SetTitleOffset(1.3);

	gStyle->SetPalette(1);
//	h_limit_cs[0]->SetMaximum(1.2);//main background color is observed
	h_limit_cs[0]->SetMinimum(0);
	h_limit_cs[0]->GetXaxis()->SetRangeUser(180,510);
	h_limit_cs[0]->GetYaxis()->SetRangeUser(130,500);
	PrettyFonts(h_limit_cs[0]);
	h_limit_cs[0]->Draw("COL Z");
	if (showData) {
		PrettyGraph(curve[0],kBlack,5,1);
		PrettyHist(legcurve[0],kBlack,5,1);
		curve[0]->Draw("sameL");
	}
	PrettyGraph(curve[1],kBlue,3,7);
	PrettyHist(legcurve[1],kBlue,3,7);
	PrettyGraph(curve[2],kBlue,3,3);
	PrettyHist(legcurve[2],kBlue,3,3);
	PrettyGraph(curve[3],kBlue,3,3);
	PrettyHist(legcurve[3],kBlue,3,3);

	curve[1]->Draw("sameL");
	curve[2]->Draw("sameL");//1 sigma low
	curve[3]->Draw("sameL");//1sigma high.

//	TLegend * leg = new TLegend(0.193467,0.793706,0.393216,0.924825);
//	PrettyLegend(leg);
//	leg->AddEntry(legcurve[1],"#sigma (Expected)");
//	leg->AddEntry(legcurve[2],"#sigma (Expected #pm 1#sigma exp.)");
//	if(showData )leg->AddEntry(legcurve[0],"#sigma (Observed)");
	leg->Draw("same");
		//the contour plot method--embaressingly easy to draw, but then you would have to cull the points.
		//	TH2D* h_cont = (TH2D*) h_limit_cs[0]->Clone("cont");
		//	Double_t cont[1] = {1.0};
		//	h_cont->SetContour(1, cont);
		//	h_cont->Draw("same CONT2");

	canv2->SetTopMargin(0.06);
	canv2->SetBottomMargin(0.15);
	if (saveplot) { //replace this by sending RetrieveLimit and sending it to format_plot_combined::SaveCanvas.
		canv2->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+"_cs.gif");
		canv2->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+"_cs.pdf");
	}
	return canv2;
}

TCanvas* MakeXSecPlot(bool saveplot ){
	printf("hello world\n");
		//setup up general style
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	gStyle->SetPadLeftMargin(0.15);
	CMSStyle();
		//setup bins
//	const int nS = 15;
//	const int nH = 21;
//	float mSVals[nS] = {185,210,235,260,285,310,335,360,385,410,460,510,1010,1510,2010};//nominal mass points.
//	float mHVals[nH] = {150,175,225,250,275,300,325,375,425,475,525,575,625,675,725,825,925,1025,1125,1225 ,1525};
	const int nS = 11; //xBinning
	const int nH = 19;
	/*if(type_to_run == 2){
		nS = 12;
		nH = 11;
		float mSVals[nS] = {185,210,235,260,285,310,335,360,385,410,460,510};//nominal mass points.
		float mHVals[nH] = {150,175,200,225,250,275,300,325,375,425,475};
	}
	if(type_to_run >= 10){
		nS = 11;
		nH = 11;*/
//		float mSVals[nS] = {185,210,260,285,310,335,360,385,410,460,510,660,710};
//		float mHVals[nH] = {150,175,200,225,250,275,300,325,375,425,475,525,575,625,675};
			//		float mSVals[nS] = {185,210,260,285,310,335,360,385,410,460,510,610,660,710,810,910,1010,1510,2010};
			//		float mHVals[nH] = {150,175,200,225,250,275,300,325,375,425,475,525,575,625,675,825,925,1025,1125,1225};
	//}
	float mSBins[nS+1] = {187.5, 212.5, 237.5 ,262.5 ,287.5, 312.5, 337.5, 362.5,    375, 425, 475, 525};
	float mHBins[nH+1] = {130, 140, 160, 190, 210,    220, 230, 235,245, 255,     260, 270, 280, 285,295,     305, 310,320, 330,370};


/*	float* mSBins = new float[nS+1];
	float* mHBins = new float[nH+1];
	mSBins[0] = mSVals[0] - 12.5;
	mHBins[0] = mHVals[0] - 12.5;
	mSBins[nS] = mSVals[nS-1] + 25;//250;
	mHBins[nH] = mHVals[nH-1] + 25;//150;
	for(int i=1; i<nS; i++) mSBins[i] = 0.5*(mSVals[i-1]+mSVals[i]);
	for(int i=1; i<nH; i++) mHBins[i] = 0.5*(mHVals[i-1]+mHVals[i]);*/
//Make the hists and canvas
	TString plotname = "XSec";
	TCanvas* canv = new TCanvas(plotname.Data(),plotname.Data(),800,600);
	canv->SetTopMargin(0.06);
	canv->SetBottomMargin(0.15);

	//const int nlimit = 7;
	//TString limitname[nlimit] = {"limit", "exp", "exp_1L","exp_1H","exp_2L","exp_2H","xsec"};
	//TString limitname2[nlimit] = {"observed", "exp", "exp_1L","exp_1H","exp_2L","exp_2H","xsec"};
	TH2F *h_xsec = new TH2F("h_xsec","Stop-Higgsino Cross Sections;Stop Mass (GeV);Higgsino Mass (GeV);Cross Section X Br (fb)",nS,mSBins,nH,mHBins);
        float bbaa_br = 2*0.561*0.00229;
        float wwaa_br = 2*0.231*0.00229;
        float zzaa_br = 2*0.0289*0.00229;
        float ttaa_br = 2*0.0615*0.00229;

		//Fetch all data:
	std::vector<MCpoint*> points = setupMCpoints();
	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
		int temp = (*it)->Mstop;
		int tempH = (*it)->Mhiggsino;
		//cout<<(*it)->Mstop<<endl;
		if(temp == 375 || temp == 425) continue;
		if((*it)->gettype() != type_to_run) continue;
		//if ((*it)->Mstop > 520) { //this segfaults
		//if (temp > 520) { continue; }
		//h_xsec->Fill((*it)->Mstop,(*it)->Mhiggsino,(*it)->cs_fb());
		float tempcs = (*it)->cs_fb();
		if(type_to_run%10 == 0) tempcs *= (bbaa_br+wwaa_br+zzaa_br+ttaa_br)/bbaa_br;
		if(type_to_run%10 == 1) tempcs *= (bbaa_br+wwaa_br+zzaa_br+ttaa_br)/wwaa_br;
		if(type_to_run%10 == 2) tempcs *= (bbaa_br+wwaa_br+zzaa_br+ttaa_br)/zzaa_br;
		if(type_to_run%10 == 3) tempcs *= (bbaa_br+wwaa_br+zzaa_br+ttaa_br)/ttaa_br;

		h_xsec->Fill(temp,tempH,tempcs);
	}

	interpolate_Zywicki(h_xsec);


	//fill in potholes
	/*for(int i= 0;i<7;i++){
		//this compensates for the missing points (385,275),(410,300),(460,325)
		//h_xsec->SetBinContent(9,4, h_xsec->GetBinContent(9,5));
		h_xsec->SetBinContent(9,6, h_xsec->GetBinContent(9,7));
		h_xsec->SetBinContent(10,7, h_xsec->GetBinContent(10,8));
		h_xsec->SetBinContent(11,8, h_xsec->GetBinContent(11,9));
	}*/

	canv->SetRightMargin(0.2);
	h_xsec->GetXaxis()->SetNdivisions(505);
	h_xsec->GetYaxis()->SetNdivisions(505);
	h_xsec->GetYaxis()->SetTitleOffset(1.2);
	h_xsec->GetZaxis()->SetTitleOffset(1.3);
	PrettyHist(h_xsec);
	h_xsec->GetXaxis()->SetRangeUser(180,510);
	h_xsec->GetYaxis()->SetRangeUser(130,500);



		//	h_limit[0]->SetTitle(title);
//	if(showData) h_limit[0]->Draw("COL Z");
//	Int_t mypalette[5] = {}

	gStyle->SetPalette(1);
	//h_xsec->SetMaximum(1.2);
	//h_xsec->SetMinimum(0);
	h_xsec->Draw("COL Z");

	if (saveplot) { 
		canv->SaveAs((plotsdir+"XSec.gif").c_str());
		canv->SaveAs((plotsdir+"XSec.pdf").c_str());
	}
		canv->SetLogz();
	if (saveplot) { 
		canv->SaveAs((plotsdir+"XSecLogZ.gif").c_str());
		canv->SaveAs((plotsdir+"XSecLogZ.pdf").c_str());
	}

	return canv;
	m(100);

}//end MakeXSecPlot
/////////////////////////////////////////////////
int suckinRawLogFile(MCpoint* thispoint,Labeledint & nPass){


	std::ifstream infile(thispoint->logplotsroot_mc.data());
	std::string line;
	int n2pho = -1;
	while (std::getline(infile, line)) {
		std::istringstream iss(line);
		std::size_t found = line.find("tag");
		std::size_t found2 = line.find("2 loose photons");

		if (found!=std::string::npos){ //if found it
			int thisnPass;
			string crap1;
			string crap2;
			string crap3;
			string crap4;
			string crap5;
			string name;

			if (!(iss >> thisnPass ))  {break;}
			if (!(iss >> crap1 >> crap2 >> crap3 >> crap4 >> crap5 >> name ) ) { break; }
			nPass[name] = thisnPass;
		}//end if found match
		else if (n2pho == -1 && found2!=std::string::npos){
			if (!(iss >> n2pho )) { break; }
		}
				
	}//end for every line
	return n2pho;
} //end suckinRawLogFile
				
TCanvas* MakeEffPlot(string topo, bool saveplot){
	printf("in MakeEffPlot\n");
		//setup up general style
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	gStyle->SetPadLeftMargin(0.15);
	CMSStyle();
		//setup bins
//	const int nS = 12;
//	const int nH = 11;
	const int nS = 11; //xBinning
	const int nH = 19;
	/*if(type_to_run == 2){
		nS = 12;
		nH = 11;
		float mSVals[nS] = {185,210,235,260,285,310,335,360,385,410,460,510};//nominal mass points.
		float mHVals[nH] = {150,175,200,225,250,275,300,325,375,425,475};
	}
	if(type_to_run >= 10){
		nS = 11;
		nH = 11;*/
//		float mSVals[nS] = {185,210,260,285,310,335,360,385,410,460,510,660,710};
//		float mHVals[nH] = {150,175,200,225,250,275,300,325,375,425,475,525,575,625,675};
//		float mSVals[nS] = {185,210,260,285,310,335,360,385,410,460,510,610,660,710,810,910,1010,1510,2010};
//		float mHVals[nH] = {150,175,200,225,250,275,300,325,375,425,475,525,575,625,675,825,925,1025,1125,1225};
	//}

	float mSBins[nS+1] = {187.5, 212.5, 237.5 ,262.5 ,287.5, 312.5, 337.5, 362.5,    375, 425, 475, 525};
	float mHBins[nH+1] = {130, 140, 160, 190, 210,    220, 230, 235,245, 255,     260, 270, 280, 285,295,     305, 310,320, 330,370};



/*	float* mSBins = new float[nS+1];
	float* mHBins = new float[nH+1];
	mSBins[0] = mSVals[0] - 12.5;
	mHBins[0] = mHVals[0] - 12.5;
	mSBins[nS] = mSVals[nS-1] + 25;//250;
	mHBins[nH] = mHVals[nH-1] + 25;//150;
	for(int i=1; i<nS; i++) mSBins[i] = 0.5*(mSVals[i-1]+mSVals[i]);
	for(int i=1; i<nH; i++) mHBins[i] = 0.5*(mHVals[i-1]+mHVals[i]);*/
//Make the hists and canvas
	TString plotname = Form("Eff_%s",topo.data());
	TCanvas* canv = new TCanvas(plotname.Data(),plotname.Data(),800,600);
	canv->SetTopMargin(0.06);
	canv->SetBottomMargin(0.15);

	//const int nlimit = 7;
	TH2F *h_eff = new TH2F(Form("h_eff_%s",topo.data()),"Stop-Higgsino Selection Efficiency;Stop Mass (GeV);Higgsino Mass (GeV);Efficiency (%)",nS,mSBins,nH,mHBins);

		//Fetch all data:
	std::vector<MCpoint*> points = setupMCpoints();
	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
		int temp = (*it)->Mstop;
		int tempH = (*it)->Mhiggsino;
		if((*it)->gettype() != type_to_run) continue;
		if (temp > 510) continue;
		if(temp == 375 || temp == 425) continue;
		Labeledint nPass;
		int n2pho = suckinRawLogFile(*it, nPass);
		h_eff->Fill(temp,tempH,100.0*((float)nPass[topo])/(0.00229*2.0*((float)(*it)->NGenPoints)));
	}
	interpolate_Zywicki(h_eff);


	canv->SetRightMargin(0.2);
	h_eff->GetXaxis()->SetNdivisions(505);
	h_eff->GetYaxis()->SetNdivisions(505);
	h_eff->GetYaxis()->SetTitleOffset(1.2);
	h_eff->GetZaxis()->SetTitleOffset(1.3);
	PrettyHist(h_eff);
	h_eff->GetXaxis()->SetRangeUser(180,510);
	h_eff->GetYaxis()->SetRangeUser(130,500);

	gStyle->SetPalette(1);
	//h_eff->SetMaximum(1.2);
	//h_eff->SetMinimum(0);
	h_eff->Draw("COL Z");

	if (saveplot) { 
		canv->SaveAs(Form("%sEff_%s.gif",plotsdir.data(),topo.data()));
		canv->SaveAs(Form("%sEff_%s.pdf",plotsdir.data(),topo.data()));
	}

	return canv;
}//end MakeEffPlot

void MakeEffPlots(bool saveplot){
	printf("in MakeEffPlots\n");
		//setup up general style
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	gStyle->SetPadLeftMargin(0.15);
	CMSStyle();
		//setup bins
	const int nS = 11; //xBinning
	const int nH = 19;
	/*if(type_to_run == 2){
		nS = 12;
		nH = 11;
		float mSVals[nS] = {185,210,235,260,285,310,335,360,385,410,460,510};//nominal mass points.
		float mHVals[nH] = {150,175,200,225,250,275,300,325,375,425,475};
	}
	if(type_to_run >= 10){
		nS = 11;
		nH = 11;*/
//		float mSVals[nS] = {185,210,260,285,310,335,360,385,410,460,510,660,710};
//		float mHVals[nH] = {150,175,200,225,250,275,300,325,375,425,475,525,575,625,675};
			//		float mSVals[nS] = {185,210,260,285,310,335,360,385,410,460,510,610,660,710,810,910,1010,1510,2010};
			//		float mHVals[nH] = {150,175,200,225,250,275,300,325,375,425,475,525,575,625,675,825,925,1025,1125,1225};
	//}
	float mSBins[nS+1] = {187.5, 212.5, 237.5 ,262.5 ,287.5, 312.5, 337.5, 362.5,    375, 425, 475, 525};
	float mHBins[nH+1] = {130, 140, 160, 190, 210,    220, 230, 235,245, 255,     260, 270, 280, 285,295,     305, 310,320, 330,370};


/*	float* mSBins = new float[nS+1];
	float* mHBins = new float[nH+1];
	mSBins[0] = mSVals[0] - 12.5;
	mHBins[0] = mHVals[0] - 12.5;
	mSBins[nS] = mSVals[nS-1] + 25;//250;
	mHBins[nH] = mHVals[nH-1] + 25;//150;
	for(int i=1; i<nS; i++) mSBins[i] = 0.5*(mSVals[i-1]+mSVals[i]);
	for(int i=1; i<nH; i++) mHBins[i] = 0.5*(mHVals[i-1]+mHVals[i]);*/

	LableHist2 h_eff;
	for (int iTopo = 0; iTopo<nEventTopologies_limit; iTopo++) {
		h_eff[s_EventTopology[iTopo]] = new TH2F(Form("h_eff_%s",s_EventTopology[iTopo].data()),"Stop-Higgsino Selection Efficiency;Stop Mass (GeV);Higgsino Mass (GeV);Efficiency (%)",nS,mSBins,nH,mHBins);
	}
		//Fetch all data:
	std::vector<MCpoint*> points = setupMCpoints();
	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
		int temp = (*it)->Mstop;
		int tempH = (*it)->Mhiggsino;
		if((*it)->gettype() != type_to_run) continue;
		if(temp == 375 || temp == 425) continue;
		if (temp > 510) continue;
		Labeledint nPass;
		int n2pho = suckinRawLogFile(*it, nPass);
		for (int iTopo = 0; iTopo<nEventTopologies_limit; iTopo++) {
			h_eff[s_EventTopology[iTopo]]->Fill(temp,tempH,100.0*((float)nPass[s_EventTopology[iTopo]])/(0.00229*2.0*((float)(*it)->NGenPoints)));
		}
	}
		//fill in the potholes.
	for (int iTopo = 0; iTopo<nEventTopologies_limit; iTopo++) {
		interpolate_Zywicki(h_eff[s_EventTopology[iTopo]]);
	}

	for (int iTopo = 0; iTopo<nEventTopologies_limit; iTopo++) {
			//Make the hists and canvas
		TString plotname = Form("Eff_%s",s_EventTopology[iTopo].data());
		TCanvas* canv = new TCanvas(plotname.Data(),plotname.Data(),800,600);
		canv->SetTopMargin(0.06);
		canv->SetBottomMargin(0.15);

		canv->SetRightMargin(0.2);
		h_eff[s_EventTopology[iTopo]]->GetXaxis()->SetNdivisions(505);
		h_eff[s_EventTopology[iTopo]]->GetYaxis()->SetNdivisions(505);
		h_eff[s_EventTopology[iTopo]]->GetYaxis()->SetTitleOffset(1.2);
		h_eff[s_EventTopology[iTopo]]->GetZaxis()->SetTitleOffset(1.3);
		PrettyHist(h_eff[s_EventTopology[iTopo]]);
		h_eff[s_EventTopology[iTopo]]->GetXaxis()->SetRangeUser(180,510);
		h_eff[s_EventTopology[iTopo]]->GetYaxis()->SetRangeUser(130,500);

		gStyle->SetPalette(1);
			//h_eff->SetMaximum(1.2);
			//h_eff->SetMinimum(0);
		h_eff[s_EventTopology[iTopo]]->Draw("COL Z");

		if (saveplot) {
			canv->SaveAs(Form("%sEff_%s.gif",plotsdir.data(),s_EventTopology[iTopo].data()));
			canv->SaveAs(Form("%sEff_%s.pdf",plotsdir.data(),s_EventTopology[iTopo].data()));
		}
	}//end for every topo

}//end MakeEffPlots
