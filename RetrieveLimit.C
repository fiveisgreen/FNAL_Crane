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
#include "TLatex.h"

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

typedef std::map<string,float> Labeledfloat;
typedef std::map<string,int> Labeledint;
//typedef std::map<string,TFile*> TFileMap;
typedef std::map<string,limit*> LabelLim;
typedef std::map<string,LabelLim> Label2Lim;
typedef std::map<string,Label2Lim> Label3Lim;
typedef std::map<string,TH1F*> LableHist;
typedef std::map<string,TH2F*> LableHist2;

typedef std::map<int,MCpoint*> higgsinoMap;




//void RetrieveLimit();
TString makeFileName(MCpoint* thispoint);
void suckinfile(Label2Lim* contianer, string pointName);
void suckinfile(Label2Lim* contianer, MCpoint* thispoint);
void suckinallfiles(int type, Label3Lim* allLims);
void printLimit(TString MassPoint, TString topo, TString kinvar, bool show_observed = false);
bool checkin(Label2Lim* contianer,TString topo, TString kinvar);
bool checkin(Label3Lim* contianers,TString MassPoint, TString topo, TString kinvar);
//void MakeLimitPlot(Labeledfloat& ObservedLimit);
void GetBestLim(TString MassPoint);
limit * GetBestLim(Label2Lim* contianer, TString MassPoint, bool announceIt=false);
void WhatCanExclude(TString MassPoint,int max = -1,bool sort = true);
bool betterlim(limit* a,limit* b);

TCanvas* MakeBrazilianLimitPlot(TString topo, TString kinvar, bool showData = false, bool saveplot = true);
TCanvas* MakeBrazilianLimitPlot(Label3Lim* allLims, TString topo, TString kinvar, bool showData = false, bool saveplot = true);
TCanvas* MakeLimitPlot(TString topo, TString kinvar, bool showData=false, bool saveplot = true);
TCanvas* MakeLimitPlot(Label3Lim* allLims, TString topo, TString kinvar, bool showData=false, bool saveplot = true);

TCanvas* MakeXSecPlot(bool saveplot = true);

int suckinRawLogFile(MCpoint* thispoint,Labeledint & nPass);
TCanvas* MakeEffPlot(string topo, int which = 0, bool saveplot = true);
TCanvas* MakeEffPlotComb(string topo, bool saveplot = true);
void print2D(TH2F* h);
//void MakeEffPlots(bool saveplot = true);

void makeHiggsinoMap(std::vector<MCpoint*> points, higgsinoMap & map,int which);

//TCanvas* MakeEfficiencyPlot(TString topo, TString kinvar, bool saveplot = true);
//TCanvas* MakeEfficiencyPlot(Label3Lim* allLims, TString topo, TString kinvar, bool saveplot = true);

//void SetupLimit();
void RetrieveLimit()
{
	//this just tests stuff
	cout<<"hello world"<<endl;
	Label3Lim * allLims = new Label3Lim();
	suckinallfiles(10, allLims);
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
	cout<<"in suckinallfiles"<<endl;
	std::vector<MCpoint*> vp = setupMCpoints();
	std::vector<MCpoint*>::iterator thispoint = vp.begin();
	while (thispoint != vp.end() ){
		if((*thispoint)->gettype()==type){
			Label2Lim * contianer = new Label2Lim();
			suckinfile(contianer,*thispoint);
			cout<<"try ot segfault "<<(*thispoint)->pointName<<endl;
			(*allLims)[(*thispoint)->pointName] = *contianer;
			cout<<"still alive"<<endl;
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
	TString filename = thispoint->makeLimitResultBundleName();
	filename = filename.ReplaceAll(".txt","_reduced.txt");
//	filename = filename.ReplaceAll("_bbaa","");
//	filename = filename.ReplaceAll("_wwaa","");
//	filename = filename.ReplaceAll("_zzaa","");
//	filename = filename.ReplaceAll("_ttaa","");
	return filename;
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
		//supposed to returns true if the containers has an entry for [masspoint][kinvar][topo], else false

	if((*contianers).count(MassPoint.Data()) > 0){
		if (((*contianers)[MassPoint.Data()]).count(kinvar.Data()) > 0) {
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
void MakeLimitPlot(Labeledfloat& ObservedLimit){
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

TCanvas* MakeBrazilianLimitPlot(TString topo, TString kinvar, bool showData,bool saveplot ){
	Label3Lim* allLims = new Label3Lim();
	return MakeBrazilianLimitPlot(allLims, topo, kinvar, showData,saveplot);
}
TCanvas* MakeBrazilianLimitPlot(Label3Lim* allLims, TString topo, TString kinvar, bool showData, bool saveplot){
	printf("hello world\n");
		//setup up general style
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	gStyle->SetPadLeftMargin(0.15);
	CMSStyle();

        TLatex * TEX_CMSPrelim;
        if(preliminary) TEX_CMSPrelim = new TLatex(0.177136,0.935315,"CMS Preliminary, #sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = 19 fb^{-1}"); 
        else TEX_CMSPrelim = new TLatex(0.177136,0.935315,Form("CMS, #sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}",Integrated_Luminosity_Data));
        //TLatex * TEX_CMSPrelim = new TLatex(0.177136,0.935315,Form("CMS Preliminary, #sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}",Integrated_Luminosity_Data));
        PrettyLatex(TEX_CMSPrelim,0.05);
       // TLatex * TEX_E_TeV = new TLatex(0.700251,0.935315,"#sqrt{s} = 8 TeV");
	//TLatex * TEX_sqrtS_lumi_fb = new TLatex(0.551859,0.935315,"#sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = 19 fb^{-1}");
        //PrettyLatex(TEX_sqrtS_lumi_fb,0.05);
        //PrettyLatex(TEX_E_TeV,0.04);
        //TLatex * TEX_lumi_fb = new TLatex(0.551859,0.935315,"#scale[0.75]{#int}#it{L} d#it{t} = 19 fb^{-1}");
        //TLatex * TEX_lumi_fb = new TLatex(0.551859,0.935315,Form("#scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}",Integrated_Luminosity_Data));
        //TLatex * TEX_lumi_fb = new TLatex(0.551859,0.935315,Form("#intL dt = %.1f fb^{-1}",Integrated_Luminosity_Data));
	//text.DrawLatex(0.64, 0.94, "#bf{#sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = 19.5 fb^{-1}}");
        //PrettyLatex(TEX_lumi_fb,0.04);
	const int nH = 14;
	float mHVals[nH] = {135,150,175,200,215,225,240,250,265,275,290,300,315,350};
	float mHBins[nH+1];
	mHBins[0] = mHVals[0]-7.5;
	mHBins[nH] = mHVals[nH-1]+17.5;
	for(int i=1; i<nH; i++) mHBins[i] = 0.5*(mHVals[i-1]+mHVals[i]);

		//Make the hists and canvas
	TString plotname = "Limits_Mu_"+topo+kinvar;
	const int nlimit = 7;
	TString limitname[nlimit] = {"limit", "exp", "exp_1L","exp_1H","exp_2L","exp_2H","xsec"};
//	TString limitname2[nlimit] = {"observed", "exp", "exp_1L","exp_1H","exp_2L","exp_2H","xsec"};
	TH1F* h_limit[nlimit];
//	TH1D* h_limit_cs[nlimit];
	h_limit[0] = new TH1F(limitname[0],limitname[0]+";m_{#tilde{#chi}_{1}^{#pm}} (GeV);r-value",nH,mHBins);
	//h_limit[0] = new TH1F(limitname[0],limitname[0]+";Higgsino Mass (GeV);r-value",nH,mHBins);
//	h_limit_cs[0] = new TH1D(limitname[0]+"_cs",limitname[0]+";Higgsino Mass (GeV);Observed Excluded Cross Section (fb)",nH,mHBins);
	for(int i=1; i<nlimit; i++) {
		h_limit[i] = new TH1F(limitname[i],limitname[i]+";m_{#tilde{#chi}_{1}^{#pm}} (GeV);r-value",nH,mHBins);
		//h_limit[i] = new TH1F(limitname[i],limitname[i]+";Higgsino Mass (GeV);r-value",nH,mHBins);
//		h_limit_cs[i] = new TH2D(limitname[i]+"_cs",limitname[i]+";Higgsino Mass (GeV);Expected Exclusion Cross Section (fb)",nH,mHBins);
	}

		//Fetch all data:
	suckinallfiles(20, allLims);
	std::vector<MCpoint*> points = setupMCpoints();
	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
		if((*it)->gettype() != 20) continue;
//		if ((*it)->Mstop > 510) continue;
		if (!checkin(allLims,(*it)->pointName, topo, kinvar)) continue;
		limit *thislim = (*allLims)[(*it)->pointName][kinvar.Data()][topo.Data()];
		/*O*/	h_limit[0]->Fill((*it)->Mhiggsino,thislim->Observed);
		/*50*/	h_limit[1]->Fill((*it)->Mhiggsino,thislim->Expected50);
		/*16%*/	h_limit[2]->Fill((*it)->Mhiggsino,thislim->Expected16);
		/*84%*/	h_limit[3]->Fill((*it)->Mhiggsino,thislim->Expected84);
		/*2.5%*/h_limit[4]->Fill((*it)->Mhiggsino,thislim->Expected2_5);
		/*97.5*/h_limit[5]->Fill((*it)->Mhiggsino,thislim->Expected97_5);
		h_limit[6]->Fill((*it)->Mhiggsino,3.0/((*it)->cs*Integrated_Luminosity_Data)); //max possible r given cs and lumi
//		/*O*/	h_limit_cs[0]->Fill((*it)->Mhiggsino,thislim->Observed * (*it)->cs_fb());
//		/*50*/	h_limit_cs[1]->Fill((*it)->Mhiggsino,thislim->Expected50 * (*it)->cs_fb());
//		/*16%*/	h_limit_cs[2]->Fill((*it)->Mhiggsino,thislim->Expected16 * (*it)->cs_fb());
//		/*84%*/	h_limit_cs[3]->Fill((*it)->Mhiggsino,thislim->Expected84 * (*it)->cs_fb());
//		/*2.5%*/h_limit_cs[4]->Fill((*it)->Mhiggsino,thislim->Expected2_5 * (*it)->cs_fb());
//		/*97.5*/h_limit_cs[5]->Fill((*it)->Mhiggsino,thislim->Expected97_5 * (*it)->cs_fb());
		printf("Mu %i observed r = %f, expected r = %f\n",(*it)->Mhiggsino,thislim->Observed,thislim->Expected50);
		
	}

		///Save the r-value exclusion plots
	TCanvas* canv = new TCanvas(plotname.Data(),plotname.Data(),800,600);
	canv->SetTopMargin(0.10);
	canv->SetBottomMargin(0.15);
	canv->SetRightMargin(0.2);

	PrettyHist(h_limit[5],kYellow,0); //top of yellow
	PrettyFillColor(h_limit[5],kYellow);
	PrettyMarker(h_limit[5],kYellow);
	PrettyHist(h_limit[3],kGreen+2,0); //top of green
	PrettyFillColor(h_limit[3],kGreen+2);
	PrettyMarker(h_limit[3],kGreen+2);

	PrettyHist(h_limit[2],kYellow,0); //bottom of green
	PrettyFillColor(h_limit[2],kYellow);
	PrettyMarker(h_limit[2],kYellow);
	PrettyHist(h_limit[4],10,0);//bottom of yellow
	PrettyFillColor(h_limit[4],10);
	PrettyHist(h_limit[1],kBlack,3,kDashed);
	PrettyMarker(h_limit[1],0,0);
	PrettyHist(h_limit[0],kBlack,3);
	PrettyMarker(h_limit[0],0,0);

	h_limit[5]->GetXaxis()->SetNdivisions(505);
	h_limit[5]->GetYaxis()->SetNdivisions(505);
	//h_limit[5]->GetYaxis()->SetTitleOffset(1.2);
	//h_limit[5]->GetZaxis()->SetTitleOffset(1.1);
	TLine * oneline = new TLine(mHBins[0],1,mHBins[nH],1);
	oneline->SetLineColor(kRed+2);
	oneline->SetLineWidth(4);

	float min = TMath::Min(h_limit[4]->GetMinimum(),0.1);
	SetRange(h_limit[5],min);

	//
	float mu_cs_uncert = 15; //assume a flat 15%
	TH1F* theo_ub = (TH1F*)h_limit[0]->Clone("theo_ub");
	TH1F* theo_lb = (TH1F*)h_limit[0]->Clone("theo_lb");
	theo_ub->Scale(1.0/(1+0.01*mu_cs_uncert ));
	theo_lb->Scale(1.0/(1-0.01*mu_cs_uncert ));
	PrettyHist(theo_ub,kBlack,1);
	PrettyHist(theo_lb,kBlack,1);

	canv->SetLogy();
	h_limit[5]->Draw("C");
	h_limit[3]->Draw("Csame");
	h_limit[2]->Draw("Csame");
	h_limit[4]->Draw("Csame");
	h_limit[1]->Draw("Csame");
	if(showData ){
		 h_limit[0]->Draw("Csame");
		 theo_ub->Draw("Csame");
		 theo_lb->Draw("Csame");
	}
	oneline->Draw("same");

	TLegend * leg;
	if(showData) leg = new TLegend( 0.467337, 0.155594, 0.667085, 0.354895 );
	else leg = new TLegend(0.187186, 0.743007, 0.386935, 0.874126);

	PrettyLegend(leg);
	leg->AddEntry(h_limit[1],"Expected Limit");
	leg->AddEntry(h_limit[3],"1#sigma Expected Limit");
	leg->AddEntry(h_limit[5],"2#sigma Expected Limit");
	if(showData ){
		leg->AddEntry(h_limit[0],"Observed Limit");
		leg->AddEntry(theo_ub,"1#sigma Observed Limit");
	}
	leg->Draw("same");

	TEX_CMSPrelim->Draw("same");
	//TEX_E_TeV->Draw("same");
	//TEX_lumi_fb->Draw("same");
	//TEX_sqrtS_lumi_fb->Draw("same");

	canv->SetTopMargin(0.10);
	canv->SetBottomMargin(0.15);
	gPad->RedrawAxis();
	if (saveplot) { 
		canv->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+".gif");
		canv->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+".pdf");
		canv->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+".png");
		canv->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+".root");
		canv->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+".C");
	}

	return canv;
}//end MakeBrazilianLimitPlot

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

        TLatex * TEX_CMSPrelim;
        if(preliminary) TEX_CMSPrelim = new TLatex(0.177136,0.935315,Form("CMS Preliminary, #sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}",Integrated_Luminosity_Data));
	else TEX_CMSPrelim = new TLatex(0.177136,0.935315,Form("CMS, #sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}",Integrated_Luminosity_Data));
        //TLatex * TEX_CMSPrelim = new TLatex(0.177136,0.935315,"CMS Preliminary, #sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = 19 fb^{-1}"); 
        //TLatex * TEX_CMSPrelim = new TLatex(0.177136,0.935315,"CMS Preliminary"); 
        PrettyLatex(TEX_CMSPrelim,0.05);
        //TLatex * TEX_E_TeV = new TLatex(0.700251,0.935315,"#sqrt{s} = 8 TeV");
        //PrettyLatex(TEX_E_TeV,0.04);
//	TLatex * TEX_lumi_fb = new TLatex(0.551859,0.935315,Form("#intL dt = %.1f fb^{-1}",Integrated_Luminosity_Data));
	//TLatex * TEX_lumi_fb = new TLatex(0.551859,0.935315,Form("#scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}",Integrated_Luminosity_Data));
        //TLatex * TEX_lumi_fb = new TLatex(0.551859,0.935315,"#scale[0.75]{#int}#it{L} d#it{t} = 19 fb^{-1}");
        //PrettyLatex(TEX_lumi_fb,0.04);
        //TLatex * TEX_sqrtS_lumi_fb2 = new TLatex(0.551859,0.935315,"#sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = 19 fb^{-1}");
        //PrettyLatex(TEX_sqrtS_lumi_fb2,0.06);
		//setup bins
//	const int nS = 15;
//	const int nH = 21;
//	float mSVals[nS] = {185,210,235,260,285,310,335,360,385,410,460,510,1010,1510,2010};//nominal mass points.
//	float mHVals[nH] = {150,175,225,250,275,300,325,375,425,475,525,575,625,675,725,825,925,1025,1125,1225 ,1525};
	const int nS = 11; //xBinning
	const int nH = 20;
	/*if(type_to_run == 2){
		nS = 12;
		nH = 11;
		float mSVals[nS] = {185,210,235,260,285,310,335,360,385,410,460,510};//nominal mass points.
		float mHVals[nH] = {150,175,200,225,250,275,300,325,375,425,475};
	}
	if(type_to_run >= 10)
		nS = 11;
		nH = 11;*/
//		float mSVals[nS] = {185,210,260,285,310,335,360,385,410,460,510,660,710};
//		float mHVals[nH] = {150,175,200,225,250,275,300,325,375,425,475,525,575,625,675};
	float mSBins[nS+1] = {187.5, 212.5, 237.5 ,262.5 ,287.5, 312.5, 337.5, 362.5,    375, 425, 475, 525};
	float mHBins[nH+1] = {130, 140, 160, 190, 210,    220, 230, 235,245, 255,     260, 270, 280, 285,295,     305, 310,320, 330,370,505};


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
	h_limit[0] = new TH2D(limitname[0],limitname[0]+";m_{#tilde t} (GeV);m_{#tilde{#chi}_{1}^{#pm}} (GeV);Observed r-value",nS,mSBins,nH,mHBins);
	h_limit_cs[0] = new TH2D(limitname[0]+"_cs",limitname[0]+";m_{#tilde t} (GeV);m_{#tilde{#chi}_{1}^{#pm}} (GeV);Observed Excluded Cross Section (pb)",nS,mSBins,nH,mHBins);
	for(int i=1; i<nlimit; i++) {
		h_limit[i] = new TH2D(limitname[i],limitname[i]+";m_{#tilde t} (GeV);m_{#tilde{#chi}_{1}^{#pm}} (GeV);Expected r-value",nS,mSBins,nH,mHBins);
		h_limit_cs[i] = new TH2D(limitname[i]+"_cs",limitname[i]+";m_{#tilde t} (GeV);m_{#tilde{#chi}_{1}^{#pm}} (GeV);Expected Exclusion Cross Section (pb)",nS,mSBins,nH,mHBins);
	}

	float divby = 1;
	if(type_to_run == 10 || type_to_run == 20) divby = 2*0.561*0.0022;
	if(type_to_run == 11 || type_to_run == 21) divby = 2*0.231*0.00229;
	if(type_to_run == 12 || type_to_run == 22) divby = 2*0.0289*0.00229;
	if(type_to_run == 13 || type_to_run == 23) divby = 2*0.0615*0.00229;


		//Fetch all data:
	suckinallfiles(10, allLims);//type = 10
	std::vector<MCpoint*> points = setupMCpoints();
	higgsinoMap map;
	makeHiggsinoMap(points,map,type_to_run);
	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
		if((*it)->gettype() != type_to_run) continue;
		if ((*it)->Mstop > 510) continue;
		int temp =(*it)->Mstop;
		if((*it)->Mstop == 325 && (*it)->Mhiggsino == 315) continue; 
		if(temp == 375 || temp == 425) continue;
		if (!checkin(allLims,(*it)->pointName, topo, kinvar)) continue;

		int tempH = (*it)->Mhiggsino;
		float mu_cs = map[tempH]->cs_fb();
		/*float mu_cs = 0;
                for(std::vector<MCpoint*>::iterator it_mu = points.begin();it_mu != points.end();it_mu++){
                        if((*it_mu)->gettype() != type_to_run + 10 || (*it_mu)->Mhiggsino != tempH) continue;
                        mu_cs = (*it_mu)->cs_fb();
                        break;
                }*/

		limit *thislim = (*allLims)[(*it)->pointName][kinvar.Data()][topo.Data()];
/*O*/	h_limit[0]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Observed);
/*50*/	h_limit[1]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected50);
/*16%*/	h_limit[2]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected16);
/*84%*/	h_limit[3]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected84);
/*2.5%*/h_limit[4]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected2_5);
/*97.5*/h_limit[5]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected97_5);
		h_limit[6]->Fill((*it)->Mstop,(*it)->Mhiggsino,3.0/(((*it)->cs + mu_cs) * Integrated_Luminosity_Data)); //max possible r given cs and lumi

//		mu_cs /= divby;
		//float stop_cs_fb = (*it)->cs_fb()/divby;
		float total_cs_fb = (mu_cs + (*it)->cs_fb() ) / divby;
		

		/*O*/	h_limit_cs[0]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Observed * total_cs_fb/1000.0);
		/*50*/	h_limit_cs[1]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected50 * total_cs_fb/1000.0);
		/*16%*/	h_limit_cs[2]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected16 * total_cs_fb/1000.0);
		/*84%*/	h_limit_cs[3]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected84 * total_cs_fb/1000.0);
		/*2.5%*/h_limit_cs[4]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected2_5 * total_cs_fb/1000.0);
		/*97.5*/h_limit_cs[5]->Fill((*it)->Mstop,(*it)->Mhiggsino,thislim->Expected97_5 * total_cs_fb/1000.0);

	}

	TH2D* theo_ub = (TH2D*) h_limit[0]->Clone();
	TH2D* theo_lb = (TH2D*) h_limit[0]->Clone();
	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
		if((*it)->gettype() != type_to_run) continue;
		if ((*it)->Mstop > 510) continue;
		int temp =(*it)->Mstop;
		if((*it)->Mstop == 325 && (*it)->Mhiggsino == 315) continue; 
		if(temp == 375 || temp == 425) continue;
	
                int tempH = (*it)->Mhiggsino;
		float mu_cs = map[tempH]->cs_fb();
		//float mu_cs = 0;
                float mu_cs_uncert = 15; //assume a flat 15%
                /*for(std::vector<MCpoint*>::iterator it_mu = points.begin();it_mu != points.end();it_mu++){
                        if((*it_mu)->gettype() != type_to_run + 10 || (*it_mu)->Mhiggsino != tempH) continue;
			mu_cs = (*it_mu)->cs_fb();
                        //mu_cs_uncert = (*it_mu)->cs_uncert;
                        break;
                }*/
		float total_cs_uncert = sqrt(pow(mu_cs*mu_cs_uncert,2) + pow( (*it)->cs_fb() * (*it)->cs_uncert,2))/(mu_cs+(*it)->cs_fb());//the uncertainty in the cross section in %

		int x = theo_ub->GetXaxis()->FindBin((*it)->Mstop);
		int y = theo_ub->GetYaxis()->FindBin((*it)->Mhiggsino);
		//theo_ub->SetBinContent(x,y, theo_ub->GetBinContent(x,y)*(1.0/(1+0.01*(*it)->cs_uncert))); //needs to change to include uncert in higgsino cs.
		//theo_lb->SetBinContent(x,y, theo_lb->GetBinContent(x,y)*(1.0/(1-0.01*(*it)->cs_uncert))); 
		theo_ub->SetBinContent(x,y, theo_ub->GetBinContent(x,y)*(1.0/(1+0.01*total_cs_uncert ))); 
		theo_lb->SetBinContent(x,y, theo_lb->GetBinContent(x,y)*(1.0/(1-0.01*total_cs_uncert ))); 
	///xxx
	}
	//fill pot holes
		//interpolate collumns, keeping triangularity
	for (int i=0; i<7; i++) interpolate_Zywicki(h_limit[i]);
	for (int i=0; i<6; i++) interpolate_Zywicki(h_limit_cs[i]);
	interpolate_Zywicki(theo_ub);
	interpolate_Zywicki(theo_lb);

/*	for(int i= 0;i<7;i++){
		//this compensates for the missing points (385,275),(410,300),(460,325)
		//h_limit[i]->SetBinContent(10,4, h_limit[i]->GetBinContent(9,5));//fake pothol
		h_limit[i]->SetBinContent(9,6, h_limit[i]->GetBinContent(9,7));
		h_limit[i]->SetBinContent(10,7, h_limit[i]->GetBinContent(10,8));
		h_limit[i]->SetBinContent(11,8, h_limit[i]->GetBinContent(11,9));
	}*/

	TGraph* curve[6];//6 ~= nlimit
		//0: observed
		//1: expected mean
		//2: expected, 1 sigma low 
		//3: expected, 1 sigma hi
		//4: expected, 2 sigma low 
		//5: expected, 2 sigma hi
	TH1F* legcurve[6];
	for (int i=0; i<6; i++) { //6 ~= nlimit
			//		curve[i] = getContour1(h_limit[i],"excl_curve_"+limitname2[i]+"_"+topo+"_"+kinvar);//dongwook's way; abandon this
			//curve[i] = getContourBarker(h_limit[i],"excl_curve_"+limitname2[i]+"_"+topo+"_"+kinvar);
		printf("try to get cure for %s\n",limitname2[i].Data());
		curve[i] = getContourBarker_fancy(h_limit[i],"excl_curve_"+limitname2[i]+"_"+topo+"_"+kinvar);
		printf("got curve\n");
//		printf("got limit\n");
		legcurve[i] = new TH1F("lexcl_curve_"+limitname2[i]+"_"+topo+"_"+kinvar,"asdf",1,0,1);//dummy histograms for use in legend
		legcurve[i]->SetMarkerStyle(0);
	}
	TGraph* curve_obs_ub;
	TGraph* curve_obs_lb;
	TH1F* legcurve_obs_ub;
	TH1F* legcurve_obs_lb;
	printf("try to get cure for observed_ub\n");
	curve_obs_ub = getContourBarker_fancy(theo_ub,"excl_curve_obs_ub_"+topo+"_"+kinvar);
	printf("got curve\n");
	legcurve_obs_ub = new TH1F("lexcl_curve_obs_ub_"+topo+"_"+kinvar,"asdf",1,0,1);//dummy histograms for use in legend
	legcurve_obs_ub->SetMarkerStyle(0);

	printf("try to get cure for observed_lb\n");
	curve_obs_lb = getContourBarker_fancy(theo_lb,"excl_curve_obs_lb_"+topo+"_"+kinvar);
	printf("got curve\n");
	legcurve_obs_lb = new TH1F("lexcl_curve_obs_lb_"+topo+"_"+kinvar,"asdf",1,0,1);//dummy histograms for use in legend
	legcurve_obs_lb->SetMarkerStyle(0);

		//	for(int i=0; i<nlimit; i++) fillPotHoles( h_limit[i] ) ; //this is bad magic


		///Save the r-value exclusion plots
	TCanvas* canv = new TCanvas(plotname.Data(),plotname.Data(),800,600);
	canv->SetTopMargin(0.10);
	canv->SetBottomMargin(0.15);
	canv->SetRightMargin(0.2);
	h_limit[0]->GetXaxis()->SetNdivisions(505);
	h_limit[0]->GetYaxis()->SetNdivisions(505);
	//h_limit[0]->GetYaxis()->SetTitleOffset(1.2);
	//h_limit[0]->GetZaxis()->SetTitleOffset(1.1);

	gStyle->SetPalette(1);
	h_limit[0]->SetMaximum(1.2);//main background color is observed
	h_limit[0]->SetMinimum(0);
	h_limit[0]->GetXaxis()->SetRangeUser(180,510);
	h_limit[0]->GetYaxis()->SetRangeUser(140,500);
	PrettyFonts(h_limit[0]);
	h_limit[0]->Draw("COL Z");
	PrettyGraph(curve_obs_ub,kBlack,3,7);
	PrettyHist(legcurve_obs_ub,kBlack,3,7);
	PrettyGraph(curve_obs_lb,kBlack,3,7);
	PrettyHist(legcurve_obs_lb,kBlack,3,7);
	if (showData) {
		PrettyGraph(curve[0],kBlack,5,1);
		PrettyHist(legcurve[0],kBlack,5,1);
		curve[0]->Draw("sameL");
		curve_obs_lb->Draw("sameL");
		curve_obs_ub->Draw("sameL");
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

        //TLine* al = new TLine(190, 190, 505, 505); //for some reason this doesn't display, oh well, it looks ugly anyway. 
	//al->SetLineColor(kBlack);
        //al->Draw("same");


        TLegend *leg= new TLegend( 0.182161, 0.606643, 0.513819,0.84265,"#splitline{#bf{Natural Higgsino NLSP (GMSB)}}{#bf{Br(#tilde{#chi}_{1}^{0} #rightarrow h#tilde{G}) = 1, Strong and Weak Production}}","brNDC");
	leg->SetLineColor(0); //these did not eliminate the line
	leg->SetLineStyle(0);
	leg->SetLineWidth(0);
        leg->SetTextColor(1);
        leg->SetFillColor(10);
        leg->SetBorderSize(0);
        leg->SetTextSize(0.036);
        TH1F* Blank2 = new TH1F("b","",1,0,1);
        Blank2->SetLineColor(kWhite);
        Blank2->SetMarkerColor(kWhite);
        Blank2->SetMarkerSize(0);
        leg->AddEntry(Blank2,"","");//prev. had option "l", which probably is making the ugly white line. 
	if(showData )leg->AddEntry(legcurve[0],"observed 95% CLs Limits","l");
	if(showData )leg->AddEntry(legcurve_obs_lb,"theory uncertainty (NLO+NLL)","l");
	leg->AddEntry(legcurve[1],"expected 95% CLs Limits","l");
	leg->AddEntry(legcurve[2],"expected #pm1#sigma_{experimental}","l");
        leg->Draw("same");
	/*
		//old nice colz legend
	   TLegend * leg = new TLegend( 0.18593 , 0.68007, 0.295226, 0.882867 );
	   PrettyLegend(leg,0.043);
	   leg->SetLineColor(0);
	   leg->SetLineStyle(0);
	   leg->SetLineWidth(0);
	   leg->AddEntry(legcurve[1],"#sigma (Expected)");
	   leg->AddEntry(legcurve[2],"#sigma (Expected #pm 1#sigma exp.)");
	   if(showData )leg->AddEntry(legcurve[0],"#sigma (Observed)");
	   if(showData )leg->AddEntry(legcurve_obs_lb,"#sigma (Observed #pm 1#sigma theory)");
	   leg->Draw("same");
*/
        //al->Draw("same");
	TEX_CMSPrelim->Draw("same");
        TLatex text2;
        text2.SetNDC(true);
        text2.SetTextAlign(12);
        text2.SetTextFont(42);
        text2.SetTextSize(0.05);
        text2.DrawLatex(0.135678,0.0437063,"m_{#tilde{#chi}_{1}^{0}} = m_{#tilde{#chi}_{1}^{#pm}} #font[122]{-} 5 GeV, m_{#tilde{#chi}_{2}^{0}} = m_{#tilde{#chi}_{1}^{#pm}} + 5 GeV");//xxx consider changing this to x = 0.123116

	//TEX_E_TeV->Draw("same");
	//TLatex * TEX_sqrtS_lumi_fb3 = new TLatex(0.551859,0.935315,"#sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = 19 fb^{-1}");
        //PrettyLatex(TEX_sqrtS_lumi_fb3,0.06);
	//TEX_sqrtS_lumi_fb3->Draw("same");
	//TEX_lumi_fb->Draw("same");
		//the contour plot method--embaressingly easy to draw, but then you would have to cull the points.
//	TH2D* h_cont = (TH2D*) h_limit[0]->Clone("cont");
//	Double_t cont[1] = {1.0};
//	h_cont->SetContour(1, cont);
//	h_cont->Draw("same CONT2");

	canv->SetTopMargin(0.10);
	canv->SetBottomMargin(0.15);
        //al->Draw("same");
        gPad->RedrawAxis();
	if (saveplot) { //replace this by sending RetrieveLimit and sending it to format_plot_combined::SaveCanvas.
		canv->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+".gif");
		canv->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+".pdf");
		canv->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+".png");
		canv->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+".root");
		canv->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+".C");
	}

		///Save the cross section exclusion plots
	TCanvas* canv2 = new TCanvas((plotname+"_cs").Data(),(plotname+"_cs").Data(),800,600);
	canv2->SetTopMargin(0.10);
	canv2->SetBottomMargin(0.15);
	canv2->SetRightMargin(0.2);
	h_limit_cs[0]->GetXaxis()->SetNdivisions(505);
	h_limit_cs[0]->GetYaxis()->SetNdivisions(505);
	//h_limit_cs[0]->GetYaxis()->SetTitleOffset(1.2);
	//h_limit_cs[0]->GetZaxis()->SetTitleOffset(1.1);

	gStyle->SetPalette(1);
//	h_limit_cs[0]->SetMaximum(1.2);//main background color is observed
	h_limit_cs[0]->SetMinimum(0);
	h_limit_cs[0]->GetXaxis()->SetRangeUser(180,510);
	h_limit_cs[0]->GetYaxis()->SetRangeUser(140,500);
	//h_limit_cs[0]->GetZaxis()->SetRangeUser(0,3.5);
	h_limit_cs[0]->GetZaxis()->SetRangeUser(0,3.5);
	PrettyFonts(h_limit_cs[0]);
	h_limit_cs[0]->Draw("COL Z");
	if (showData) {
		PrettyGraph(curve[0],kBlack,5,1);
		PrettyHist(legcurve[0],kBlack,5,1);
		curve[0]->Draw("sameL");
                curve_obs_lb->Draw("sameL");
                curve_obs_ub->Draw("sameL");
	}
	PrettyGraph(curve[1],kRed+1,3,7);
	PrettyHist(legcurve[1],kRed+1,3,7);
	PrettyGraph(curve[2],kRed+1,3,3);
	PrettyHist(legcurve[2],kRed+1,3,3);
	PrettyGraph(curve[3],kRed+1,3,3);
	PrettyHist(legcurve[3],kRed+1,3,3);

	curve[1]->Draw("sameL");
	curve[2]->Draw("sameL");//1 sigma low
	curve[3]->Draw("sameL");//1sigma high.

//	TLegend * leg = new TLegend(0.193467,0.793706,0.393216,0.924825);
//	PrettyLegend(leg);
//	leg->AddEntry(legcurve[1],"#sigma (Expected)");
//	leg->AddEntry(legcurve[2],"#sigma (Expected #pm 1#sigma exp.)");
//	if(showData )leg->AddEntry(legcurve[0],"#sigma (Observed)");
	leg->Draw("same");
	TEX_CMSPrelim->Draw("same");
        text2.DrawLatex(0.0150754,0.0402098,"m_{#tilde{#chi}_{1}^{0}} = m_{#tilde{#chi}_{1}^{#pm}} #font[122]{-} 5 GeV, m_{#tilde{#chi}_{2}^{0}} = m_{#tilde{#chi}_{1}^{#pm}} + 5 GeV");
	//TEX_E_TeV->Draw("same");
	//TEX_lumi_fb->Draw("same");
	//TEX_sqrtS_lumi_fb2->Draw("same");
		//the contour plot method--embaressingly easy to draw, but then you would have to cull the points.
		//	TH2D* h_cont = (TH2D*) h_limit_cs[0]->Clone("cont");
		//	Double_t cont[1] = {1.0};
		//	h_cont->SetContour(1, cont);
		//	h_cont->Draw("same CONT2");

	canv2->SetTopMargin(0.10);
	canv2->SetBottomMargin(0.15);
	if (saveplot) { //replace this by sending RetrieveLimit and sending it to format_plot_combined::SaveCanvas.
		canv2->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+"_cs.gif");
		canv2->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+"_cs.pdf");
		canv2->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+"_cs.png");
		canv2->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+"_cs.C");
		canv2->SaveAs(plotsdir+"Excl_"+topo+"_"+kinvar+"_cs.root");
	}


        printf("opening file LimitCurves_%s_%s.root\n",topo.Data(),kinvar.Data());
        TFile* fcurves = new TFile(Form("LimitCurves_%s_%s.root",topo.Data(),kinvar.Data()),"RECREATE");
        fcurves->cd();
        printf("cd\n");

        for (int i=0; i<6; i++) { //6 ~= nlimit
                        //              curve[i] = getContour1(h_limit[i],"excl_curve_"+limitname2[i]+"_"+topo+"_"+kinvar);//dongwook's way; abandon this
                        //curve[i] = getContourBarker(h_limit[i],"excl_curve_"+limitname2[i]+"_"+topo+"_"+kinvar);
                printf("try to get cure for %s\n",limitname2[i].Data());
                curve[i] = getContourBarker_fancy(h_limit[i],"excl_curve_"+limitname2[i]+"_"+topo+"_"+kinvar);
                printf("try to write to it\n");
                curve[i]->Write();
                printf("got curve\n");
        }       

//     __  ___     __         _____                   ___  __     __     ___  __     __    
//    /  |/  /__ _/ /_____   / ___/______ ___ ___    / _ )/ /__  / /    / _ \/ /__  / /____
//   / /|_/ / _ `/  '_/ -_) / (_ / __/ -_) -_) _ \  / _  / / _ \/ _ \  / ___/ / _ \/ __(_-<
//  /_/  /_/\_,_/_/\_\\__/  \___/_/  \__/\__/_//_/ /____/_/\___/_.__/ /_/  /_/\___/\__/___/
//                                                                                         
//Make Green Blob Plots

	bool makestupidaxis = true;
	TCanvas* greenblob = new TCanvas("greenblob", "Contour List", makestupidaxis?800:725, 500);
	greenblob->cd();
	TH2F* blank = new TH2F("blank",";m_{#tilde t} (GeV);m_{#tilde{#chi}_{1}^{#pm}} (GeV)",50,195,makestupidaxis?805:505,50,135,makestupidaxis?750:505);
	PrettyHist(blank);
	greenblob->SetTopMargin(0.10);
	blank->GetXaxis()->SetTitleSize(0.06);
	blank->GetXaxis()->SetLabelSize(0.05);
	blank->GetXaxis()->SetTitleOffset(1);
	blank->GetYaxis()->SetTitleSize(0.06);
	blank->GetYaxis()->SetLabelSize(0.05);
	blank->GetYaxis()->SetTitleOffset(1);
	blank->Draw();
		//0: observed
		//1: expected mean
		//2: expected, 1 sigma low 
		//3: expected, 1 sigma hi
		//4: expected, 2 sigma low 
		//5: expected, 2 sigma hi

	//TGraph* curve[6];
	PrettyGraph(curve[0],1,3,1);
	PrettyGraph(curve_obs_ub,1,1,1);
	PrettyGraph(curve_obs_lb,1,1,1);
	
	PrettyGraph(curve[1],1,3,2);
	PrettyGraph(curve[2],kGreen,0,1);
	PrettyGraph(curve[3],kGreen,0,1);
	PrettyGraph(curve[4],kYellow,0,1);
	PrettyGraph(curve[5],kYellow,0,1);
	TGraph * blob = makeband_0guard(curve[2], curve[3],kGreen);
	PrettyGraph(blob,kGreen,0,1);

	//curve[3]->SetFillStyle(0);
	blob->SetFillStyle(1001);
	//curve[3]->SetFillColor(kGreen);
	//curve[3]->Draw("F");
	blob->Draw("Fsame");
	//curve[2]->SetFillStyle(0);
	//curve[2]->SetFillColor(kWhite);
	//curve[2]->Draw("Fsame");
	curve[1]->Draw("Lsame");
	curve_obs_ub->Draw("Lsame");
	curve_obs_lb->Draw("Lsame");
	curve[0]->Draw("Lsame");
	

	//double legx1, legx2, legy1, legy2;
	//legx1 = 0.15; legx2 = 0.50; legy1 = 0.63; legy2 = 0.85;
	//legx1 = 0.15; legx2 = 0.53; legy1 = 0.63; legy2 = 0.85;
	TLegend *legend = new TLegend(0.197236, 0.596154, 0.576633, 0.816434,"#splitline{#bf{Natural Higgsino NLSP (GMSB)}}{#bf{Br(#tilde{#chi}_{1}^{0} #rightarrow h#tilde{G}) = 1, Strong and Weak Production}}","brNDC");
	//TLegend *legend = new TLegend(0.188442, 0.684322, 0.567839, 0.904661, "#splitline{#bf{Natural Higgsino NLSP (GMSB)}}{Br(#tilde{#chi}_{1}^{0} #rightarrow h#tilde{G}) = 1, Strong and Weak Production}","brNDC");
   legend->SetLineColor(0); //these did not eliminate the line
   legend->SetLineStyle(0);
   legend->SetLineWidth(0);

	legend->SetTextColor(1);
	legend->SetFillColor(10);
	legend->SetBorderSize(0);
	legend->SetTextSize(0.036);
	TH1F* Blank = new TH1F("b","",1,0,1);
	//TColor *transp = new TColor(kWhite, 1, 1, 1, "", 0);//fully transparent 
	Blank->SetLineColor(kWhite);
        Blank->SetMarkerColor(kWhite);
        Blank->SetMarkerSize(0);
	//observed
	legend->AddEntry(Blank,"","");
	legend->AddEntry(curve[0],"observed 95% CLs Limits","l");
	legend->AddEntry(curve_obs_ub,"Theory uncertainty (NLO+NLL)","l");
	legend->AddEntry(curve[1],"expected 95% CLs Limits","l");
	legend->AddEntry(blob, "expected #pm1#sigma_{experimental}","fl");

	legend->Draw("same");
	TLatex text;
	text.SetNDC(true);
	text.SetTextAlign(12);
	text.SetTextFont(42);
	text.SetTextSize(0.04);
	//text.DrawLatex(0.13, 0.94, "#bf{CMS}");
	//text.DrawLatex(0.64, 0.94, "#bf{#sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = 19.5 fb^{-1}}");
	
	text.SetTextSize(0.05);
	text.DrawLatex(0.123116,0.065,"m_{#tilde{#chi}_{1}^{0}} = m_{#tilde{#chi}_{1}^{#pm}} #font[122]{-} 5 GeV, m_{#tilde{#chi}_{2}^{0}} = m_{#tilde{#chi}_{1}^{#pm}} + 5 GeV");
	TEX_CMSPrelim->Draw("same");
	//TLatex * TEX_sqrtS_lumi_fb = new TLatex(0.758794,0.935315,"#sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = 19 fb^{-1}");
	//TLatex * TEX_sqrtS_lumi_fb = new TLatex(0.758794,0.935315,Form("#sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}",Integrated_Luminosity_Data));
	//TEX_sqrtS_lumi_fb->Draw("same");
	//TLatex * TEX_sqrtS_lumi_fb = new TLatex(0.551859,0.935315,"#sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = 19 fb^{-1}");
        //PrettyLatex(TEX_sqrtS_lumi_fb,0.04);
	//TEX_E_TeV->Draw("same");
	//TEX_lumi_fb->Draw("same");
        //PrettyLatex(TEX_sqrtS_lumi_fb,0.05);
	//TEX_sqrtS_lumi_fb->Draw("same");
	
	
	
	TLine* l;
	l = new TLine(200, 200, makestupidaxis?750:505, makestupidaxis?750:505);
	l->Draw("same");
	gPad->RedrawAxis();

	greenblob->SaveAs(plotsdir+"ExclBlob_"+topo+"_"+kinvar+".gif");
	greenblob->SaveAs(plotsdir+"ExclBlob_"+topo+"_"+kinvar+".C");
	greenblob->SaveAs(plotsdir+"ExclBlob_"+topo+"_"+kinvar+".pdf");
	greenblob->SaveAs(plotsdir+"ExclBlob_"+topo+"_"+kinvar+".png");
	greenblob->SaveAs(plotsdir+"ExclBlob_"+topo+"_"+kinvar+".root");


/////////////////////// END MAKE GREEN BLOB PLOTS ///////////////////////////
        printf("go close it\n");
        fcurves->Close();
        printf("closed it\n");

	return canv2;
}//MakeLimitPlot

TCanvas* MakeXSecPlot(bool saveplot ){
	printf("hello world\n");
		//setup up general style
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	gStyle->SetPadLeftMargin(0.15);
	CMSStyle();

	TLatex * TEX_CMSPrelim;
	if(preliminary) TEX_CMSPrelim = new TLatex(0.177136,0.935315,"CMS Simulation Preliminary, #sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = 19 fb^{-1}"); 
        else TEX_CMSPrelim = new TLatex(0.177136,0.935315,Form("CMS, #sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}",Integrated_Luminosity_Data));
        //TLatex * TEX_CMSPrelim = new TLatex(0.177136,0.935315,Form("CMS Preliminary, #sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}",Integrated_Luminosity_Data));
        PrettyLatex(TEX_CMSPrelim,0.05);
        //TLatex * TEX_E_TeV = new TLatex(0.700251,0.935315,"#sqrt{s} = 8 TeV");
        //PrettyLatex(TEX_E_TeV,0.03);
	//TLatex * TEX_lumi_fb = new TLatex(0.551859,0.935315,Form("#intL dt = %.1f fb^{-1}",Integrated_Luminosity_Data));
	//TLatex * TEX_lumi_fb = new TLatex(0.551859,0.935315,Form("#scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}",Integrated_Luminosity_Data));
        //TLatex * TEX_lumi_fb = new TLatex(0.551859,0.935315,"#scale[0.75]{#int}#it{L} d#it{t} = 19 fb^{-1}");
        //PrettyLatex(TEX_lumi_fb,0.04);

	//TLatex * TEX_sqrtS_lumi_fb = new TLatex(0.551859,0.935315,"#sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = 19 fb^{-1}");
        //PrettyLatex(TEX_sqrtS_lumi_fb,0.05);
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
	canv->SetTopMargin(0.10);
	canv->SetBottomMargin(0.15);

	//const int nlimit = 7;
	//TString limitname[nlimit] = {"limit", "exp", "exp_1L","exp_1H","exp_2L","exp_2H","xsec"};
	//TString limitname2[nlimit] = {"observed", "exp", "exp_1L","exp_1H","exp_2L","exp_2H","xsec"};
	TH2F *h_xsec = new TH2F("h_xsec","Stop-Higgsino Cross Sections;m_{#tilde t} (GeV);m_{#tilde{#chi}_{1}^{#pm}} (GeV);Cross Section x br[H#rightarrow #gamma #gamma] (fb)",nS,mSBins,nH,mHBins);
	//TH2F *h_xsec = new TH2F("h_xsec","Stop-Higgsino Cross Sections;Stop Mass (GeV);Higgsino Mass (GeV);Cross Section x br[H#rightarrow #gamma #gamma] (fb)",nS,mSBins,nH,mHBins);
	TH2F *h_xsec_stop = new TH2F("h_xsec_stop","Stop Cross Sections Fraction;m_{#tilde t} (GeV);m_{#tilde{#chi}_{1}^{#pm}} (GeV);Stop Cross Section Fraction",nS,mSBins,nH,mHBins);
	//TH2F *h_xsec_stop = new TH2F("h_xsec_stop","Stop Cross Sections Fraction;Stop Mass (GeV);Higgsino Mass (GeV);Stop Cross Section Fraction",nS,mSBins,nH,mHBins);


        float bbaa_br = 2*0.561*0.00229;
        float wwaa_br = 2*0.231*0.00229;
        float zzaa_br = 2*0.0289*0.00229;
        float ttaa_br = 2*0.0615*0.00229;
	float hgg_br = 0.00229;

		//Fetch all data:
	std::vector<MCpoint*> points = setupMCpoints();
	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
		int temp = (*it)->Mstop;
		int tempH = (*it)->Mhiggsino;
		//cout<<(*it)->Mstop<<endl;
		if(temp == 375 || temp == 425) continue;
		if((*it)->gettype() != type_to_run) continue;

		float mu_cs = 0;	
		for(std::vector<MCpoint*>::iterator it_mu = points.begin();it_mu != points.end();it_mu++){
			if((*it_mu)->gettype() != type_to_run + 10 || (*it_mu)->Mhiggsino != tempH) continue;
			mu_cs = (*it_mu)->cs_fb();
			break;
		}
		mu_cs *= hgg_br / bbaa_br;
		//if((*it)->gettype() != type_to_run) continue;
		//if((*it)->gettype() != type_to_run) continue;
		//if ((*it)->Mstop > 520) { //this segfaults
		//if (temp > 520) { continue; }
		//h_xsec->Fill((*it)->Mstop,(*it)->Mhiggsino,(*it)->cs_fb());
		float tempcs = (*it)->cs_fb();
		if((*it)->gettype() == 10 || (*it)->gettype() == 20) 	  tempcs *= hgg_br / bbaa_br; 
		else if((*it)->gettype() == 11 || (*it)->gettype() == 21) tempcs *= hgg_br / wwaa_br; 
		else if((*it)->gettype() == 12 || (*it)->gettype() == 22) tempcs *= hgg_br / zzaa_br; 
		else if((*it)->gettype() == 13 || (*it)->gettype() == 23) tempcs *= hgg_br / ttaa_br; 
		h_xsec->Fill(temp,tempH,tempcs+mu_cs);
		h_xsec_stop->Fill(temp,tempH,tempcs/(tempcs+mu_cs));
	}
	cout<<"ok, what the heck is up with the frac plot?"<<endl;
	print2D(h_xsec_stop);

	interpolate_Zywicki(h_xsec,false);
	interpolate_Zywicki(h_xsec_stop,false);
	cout<<"does interpolation do anything bad? "<<endl;
	print2D(h_xsec_stop);


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
	//h_xsec->GetYaxis()->SetTitleOffset(0.8);
	//h_xsec->GetXaxis()->SetTitleOffset(0.8);
	//h_xsec->GetZaxis()->SetTitleOffset(1.1);
	PrettyHist(h_xsec);
	h_xsec->GetZaxis()->SetTitleSize(0.07);
	h_xsec->GetXaxis()->SetRangeUser(180,510);
	h_xsec->GetYaxis()->SetRangeUser(140,500);
	h_xsec->GetZaxis()->SetRangeUser(0,35);



		//	h_limit[0]->SetTitle(title);
//	if(showData) h_limit[0]->Draw("COL Z");
//	Int_t mypalette[5] = {}

	gStyle->SetPalette(1);
	//h_xsec->SetMaximum(1.2);
	//h_xsec->SetMinimum(0);
	h_xsec->Draw("COL Z");
	TEX_CMSPrelim->Draw("same");
	//TEX_E_TeV->Draw("same");
	//TEX_lumi_fb->Draw("same");
	//TEX_sqrtS_lumi_fb->Draw("same");

	if (saveplot) { 
		canv->SaveAs((plotsdir+"XSec.gif").c_str());
		canv->SaveAs((plotsdir+"XSec.pdf").c_str());
		canv->SaveAs((plotsdir+"XSec.png").c_str());
		canv->SaveAs((plotsdir+"XSec.C").c_str());
		canv->SaveAs((plotsdir+"XSec.root").c_str());
	}
		canv->SetLogz();
	h_xsec->GetZaxis()->SetRangeUser(0.1,50);
	if (saveplot) { 
		canv->SaveAs((plotsdir+"XSecLogZ.gif").c_str());
		canv->SaveAs((plotsdir+"XSecLogZ.pdf").c_str());
		canv->SaveAs((plotsdir+"XSecLogZ.png").c_str());
		canv->SaveAs((plotsdir+"XSecLogZ.C").c_str());
		canv->SaveAs((plotsdir+"XSecLogZ.root").c_str());
	}

        TCanvas* canvT = new TCanvas((plotname+"_stopfrac").Data(),(plotname+"_stopfrac").Data(),800,600);
	canvT->cd();
        canvT->SetTopMargin(0.10);
        canvT->SetBottomMargin(0.15);
	canvT->SetRightMargin(0.2);
        h_xsec_stop->GetXaxis()->SetNdivisions(505);
        h_xsec_stop->GetYaxis()->SetNdivisions(505);
        //h_xsec_stop->GetYaxis()->SetTitleOffset(1.2);
        //h_xsec_stop->GetZaxis()->SetTitleOffset(1.1);
        PrettyHist(h_xsec_stop);
	h_xsec_stop->GetZaxis()->SetTitleSize(0.07);
        h_xsec_stop->GetXaxis()->SetRangeUser(180,510);
        h_xsec_stop->GetYaxis()->SetRangeUser(140,500);
        h_xsec_stop->GetZaxis()->SetRangeUser(0,1);
	h_xsec_stop->Draw("COL Z");
	TEX_CMSPrelim->Draw("same");
	//TEX_sqrtS_lumi_fb->Draw("same");
	if (saveplot) { 
		canvT->SaveAs((plotsdir+"XSec_stopfrac.gif").c_str());
		canvT->SaveAs((plotsdir+"XSec_stopfrac.pdf").c_str());
		canvT->SaveAs((plotsdir+"XSec_stopfrac.png").c_str());
		canvT->SaveAs((plotsdir+"XSec_stopfrac.C").c_str());
		canvT->SaveAs((plotsdir+"XSec_stopfrac.root").c_str());
	}

	return canv;
	m(100);

}//end MakeXSecPlot
/////////////////////////////////////////////////
int suckinRawLogFile(MCpoint* thispoint,Labeledint & nPass){

	cout<<"in suckinRawLogFile, reaching for file "<<thispoint->logplotsroot_mc<<endl;
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
				
TCanvas* MakeEffPlot(string topo,int which, bool saveplot){

	int printLevel = 2;
	if(printLevel >=1) printf("in MakeEffPlot\n");
		//setup up general style
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	gStyle->SetPadLeftMargin(0.15);
	CMSStyle();
	if(printLevel>=4) cout<<"boo1"<<endl;

        TLatex * TEX_CMSPrelim;
	if(printLevel>=4) cout<<"boo1.1"<<endl;
	if(preliminary){ 
		TEX_CMSPrelim = new TLatex(0.177136,0.935315,"CMS Simulation Preliminary, #sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = 19 fb^{-1}");
		if(printLevel>=4) cout<<"boo1.2"<<endl;
	}
        else{
		TEX_CMSPrelim = new TLatex(0.177136,0.935315,Form("CMS, #sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}",Integrated_Luminosity_Data));
		if(printLevel>=4) cout<<"boo1.3"<<endl;
	}
        //TLatex * TEX_CMSPrelim = new TLatex(0.177136,0.935315,Form("CMS Preliminary, #sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}",Integrated_Luminosity_Data));
		if(printLevel>=4) cout<<"boo1.4"<<endl;
        PrettyLatex(TEX_CMSPrelim,0.05);
	if(printLevel>=4) cout<<"boo2"<<endl;
        //TLatex * TEX_E_TeV = new TLatex(0.700251,0.935315,"#sqrt{s} = 8 TeV");
        //PrettyLatex(TEX_E_TeV,0.04);
        //TLatex * TEX_lumi_fb = new TLatex(0.551859,0.935315,Form("#intL dt = %.1f fb^{-1}",Integrated_Luminosity_Data));
	//TLatex * TEX_lumi_fb = new TLatex(0.551859,0.935315,Form("#scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}",Integrated_Luminosity_Data));
        //TLatex * TEX_lumi_fb = new TLatex(0.551859,0.935315,"#scale[0.75]{#int}#it{L} d#it{t} = 19 fb^{-1}");
        //PrettyLatex(TEX_lumi_fb,0.04);
        //TLatex * TEX_sqrtS_lumi_fb = new TLatex(0.551859,0.935315,"#sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = 19 fb^{-1}");
        //PrettyLatex(TEX_sqrtS_lumi_fb,0.05);
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
	canv->SetTopMargin(0.10);
	canv->SetBottomMargin(0.15);

	if(printLevel>=4) cout<<"boo3"<<endl;
	//const int nlimit = 7;
	TH2F *h_eff = new TH2F(Form("h_eff_%s",topo.data()),"Stop-Higgsino Selection Efficiency;m_{#tilde t} (GeV);m_{#tilde{#chi}_{1}^{#pm}} (GeV);Efficiency (%)",nS,mSBins,nH,mHBins);
	//TH2F *h_eff = new TH2F(Form("h_eff_%s",topo.data()),"Stop-Higgsino Selection Efficiency;Stop Mass (GeV);Higgsino Mass (GeV);Efficiency (%)",nS,mSBins,nH,mHBins);

		//Fetch all data:
	std::vector<MCpoint*> points = setupMCpoints();
	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
		if((*it)->gettype() != which) continue;
		int temp = (*it)->Mstop;
		int tempH = (*it)->Mhiggsino;
		if (temp > 510) continue;
		if(temp == 375 || temp == 425) continue;
		if(temp == 450 && tempH == 200) continue;
		Labeledint nPass;
//		int n2pho = suckinRawLogFile(*it, nPass);
		
		if(printLevel>=3) cout<<"loading raw file from stop "<<temp<<" higgsino "<<tempH<<endl;
		suckinRawLogFile(*it, nPass);
		if(printLevel>=3) cout<<"succeeded"<<endl;
		h_eff->Fill(temp,tempH,100.0*((float)nPass[topo])/((float)(*it)->NGenPoints));
		//h_eff->Fill(temp,tempH,100.0*((float)nPass[topo])/(0.00229*2.0*((float)(*it)->NGenPoints)));
	}

	interpolate_Zywicki(h_eff,false);

	canv->SetRightMargin(0.2);
	h_eff->GetXaxis()->SetNdivisions(505);
	h_eff->GetYaxis()->SetNdivisions(505);
	//h_eff->GetYaxis()->SetTitleOffset(1.2);
	//h_eff->GetZaxis()->SetTitleOffset(1.1);
	PrettyHist(h_eff);
	h_eff->GetXaxis()->SetRangeUser(180,510);
	h_eff->GetYaxis()->SetRangeUser(140,500);

	gStyle->SetPalette(1);
	//h_eff->SetMaximum(1.2);
	//h_eff->SetMinimum(0);
	h_eff->Draw("COL Z");
	TEX_CMSPrelim->Draw("same");
	//TEX_E_TeV->Draw("same");
	//TEX_lumi_fb->Draw("same");
	//TEX_sqrtS_lumi_fb->Draw("same");
	
	string which_str;
	switch (which){
		case 10: which_str = "bbaa";
			break;
		case 11: which_str = "wwaa";
			break;
		case 12: which_str = "zzaa";
			break;
		case 13: which_str = "ttaa";
			break;
		case 20: which_str = "bbaa_mu";
			break;
		case 21: which_str = "wwaa_mu";
			break;
		case 22: which_str = "zzaa_mu";
			break;
		case 23: which_str = "ttaa_mu";
			break;
		default: which_str = "bbaa";
			 break;
	}//end switch

	if (saveplot) { 
		canv->SaveAs(Form("%sEff_%s_%s.gif",plotsdir.data(),topo.data(),which_str.data()));
		canv->SaveAs(Form("%sEff_%s_%s.pdf",plotsdir.data(),topo.data(),which_str.data()));
		canv->SaveAs(Form("%sEff_%s_%s.png",plotsdir.data(),topo.data(),which_str.data()));
		canv->SaveAs(Form("%sEff_%s_%s.root",plotsdir.data(),topo.data(),which_str.data()));
		canv->SaveAs(Form("%sEff_%s_%s.C",plotsdir.data(),topo.data(),which_str.data()));
	}

	return canv;
}//end MakeEffPlot

TCanvas* MakeEffPlotComb(string topo, bool saveplot){
	printf("in MakeEffPlotComb\n");
		//setup up general style
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	gStyle->SetPadLeftMargin(0.15);
	CMSStyle();

        TLatex * TEX_CMSPrelim;
        if(preliminary) TEX_CMSPrelim = new TLatex(0.177136,0.935315,"CMS Simulation Preliminary, #sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = 19 fb^{-1}");
        else  TEX_CMSPrelim = new TLatex(0.177136,0.935315,Form("CMS, #sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}",Integrated_Luminosity_Data));
        //TLatex * TEX_CMSPrelim = new TLatex(0.177136,0.935315,Form("CMS Preliminary, #sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}",Integrated_Luminosity_Data));
        PrettyLatex(TEX_CMSPrelim,0.05);
        //TLatex * TEX_E_TeV = new TLatex(0.700251,0.935315,"#sqrt{s} = 8 TeV");
        //PrettyLatex(TEX_E_TeV,0.04);
        //TLatex * TEX_lumi_fb = new TLatex(0.551859,0.935315,Form("#intL dt = %.1f fb^{-1}",Integrated_Luminosity_Data));
	//TLatex * TEX_lumi_fb = new TLatex(0.551859,0.935315,Form("#scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}",Integrated_Luminosity_Data));
        //TLatex * TEX_lumi_fb = new TLatex(0.551859,0.935315,"#scale[0.75]{#int}#it{L} d#it{t} = 19 fb^{-1}");
        //PrettyLatex(TEX_lumi_fb,0.04);
	//TLatex * TEX_sqrtS_lumi_fb = new TLatex(0.551859,0.935315,"#sqrt{s} = 8 TeV, #scale[0.75]{#int}#it{L} d#it{t} = 19 fb^{-1}");
        //PrettyLatex(TEX_sqrtS_lumi_fb,0.05);
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
	canv->SetTopMargin(0.10);
	canv->SetBottomMargin(0.15);

	//const int nlimit = 7;
	TH2F *h_eff = new TH2F(Form("h_eff_%s",topo.data()),"Stop-Higgsino Selection Efficiency;m_{#tilde t} (GeV);m_{#tilde{#chi}_{1}^{#pm}} (GeV);Efficiency (%)",nS,mSBins,nH,mHBins);
	TH2F *h_eff_wwaa = new TH2F(Form("h_eff_wwaa_%s",topo.data()),"Stop-Higgsino Selection Efficiency;m_{#tilde t} (GeV);m_{#tilde{#chi}_{1}^{#pm}} (GeV);Efficiency (%)",nS,mSBins,nH,mHBins);
	TH2F *h_eff_zzaa = new TH2F(Form("h_eff_zzaa_%s",topo.data()),"Stop-Higgsino Selection Efficiency;m_{#tilde t} (GeV);m_{#tilde{#chi}_{1}^{#pm}} (GeV);Efficiency (%)",nS,mSBins,nH,mHBins);
	TH2F *h_eff_ttaa = new TH2F(Form("h_eff_ttaa_%s",topo.data()),"Stop-Higgsino Selection Efficiency;m_{#tilde t} (GeV);m_{#tilde{#chi}_{1}^{#pm}} (GeV);Efficiency (%)",nS,mSBins,nH,mHBins);

	TH2F *h_eff_bbaa_mu = new TH2F(Form("h_eff_bbaa_mu_%s",topo.data()),"Higgsino Selection Efficiency;m_{#tilde t} (GeV);m_{#tilde{#chi}_{1}^{#pm}} (GeV);Efficiency (%)",nS,mSBins,nH,mHBins);
	TH2F *h_eff_wwaa_mu = new TH2F(Form("h_eff_wwaa_mu_%s",topo.data()),"Higgsino Selection Efficiency;m_{#tilde t} (GeV);m_{#tilde{#chi}_{1}^{#pm}} (GeV);Efficiency (%)",nS,mSBins,nH,mHBins);
	TH2F *h_eff_zzaa_mu = new TH2F(Form("h_eff_zzaa_mu_%s",topo.data()),"Higgsino Selection Efficiency;m_{#tilde t} (GeV);m_{#tilde{#chi}_{1}^{#pm}} (GeV);Efficiency (%)",nS,mSBins,nH,mHBins);
	TH2F *h_eff_ttaa_mu = new TH2F(Form("h_eff_ttaa_mu_%s",topo.data()),"Higgsino Selection Efficiency;m_{#tilde t} (GeV);m_{#tilde{#chi}_{1}^{#pm}} (GeV);Efficiency (%)",nS,mSBins,nH,mHBins);
	//TH2F *h_eff_ttaa_mu = new TH2F(Form("h_eff_ttaa_mu_%s",topo.data()),"Higgsino Selection Efficiency;Stop Mass (GeV);Higgsino Mass (GeV);Efficiency (%)",nS,mSBins,nH,mHBins);

		//Fetch all data:
	std::vector<MCpoint*> points = setupMCpoints();
        higgsinoMap map_bbaa;
        higgsinoMap map_wwaa;
        higgsinoMap map_zzaa;
        higgsinoMap map_ttaa;
        makeHiggsinoMap(points,map_bbaa,10);
        makeHiggsinoMap(points,map_wwaa,11);
        makeHiggsinoMap(points,map_zzaa,12);
        makeHiggsinoMap(points,map_ttaa,13);

	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
		if((*it)->gettype() != type_to_run) continue;
		int temp = (*it)->Mstop;
		int tempH = (*it)->Mhiggsino;
		if (temp > 510) continue;
		if(temp == 375 || temp == 425) continue;
		if(temp == 450 && tempH == 200) continue;
		//if(temp == 325 && tempH == 175) continue;
		Labeledint nPass;
//		int n2pho = suckinRawLogFile(*it, nPass);
		suckinRawLogFile(*it, nPass);
		h_eff->Fill(temp,tempH,100.0*((float)nPass[topo])/((float)(*it)->NGenPoints));
	}
	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
		if((*it)->gettype() != type_to_run+1) continue;
		int temp = (*it)->Mstop;
		int tempH = (*it)->Mhiggsino;
		if (temp > 510) continue;
		if(temp == 375 || temp == 425) continue;
		if(temp == 450 && tempH == 200) continue;
		//if(temp == 325 && tempH == 175) continue;
		Labeledint nPass;
//		int n2pho = suckinRawLogFile(*it, nPass);
		suckinRawLogFile(*it, nPass);
		h_eff_wwaa->Fill(temp,tempH,100.0*((float)nPass[topo])/((float)(*it)->NGenPoints));
	}
	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
		if((*it)->gettype() != type_to_run+2) continue;
		int temp = (*it)->Mstop;
		int tempH = (*it)->Mhiggsino;
		if (temp > 510) continue;
		if(temp == 375 || temp == 425) continue;
		if(temp == 450 && tempH == 200) continue;
		//if(temp == 325 && tempH == 175) continue;
		Labeledint nPass;
//		int n2pho = suckinRawLogFile(*it, nPass);
		suckinRawLogFile(*it, nPass);
		h_eff_zzaa->Fill(temp,tempH,100.0*((float)nPass[topo])/((float)(*it)->NGenPoints));
	}
	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
		if((*it)->gettype() != type_to_run+3) continue;
		int temp = (*it)->Mstop;
		int tempH = (*it)->Mhiggsino;
		if (temp > 510) continue;
		if(temp == 375 || temp == 425) continue;
		if(temp == 450 && tempH == 200) continue;
		//if(temp == 325 && tempH == 175) continue;
		Labeledint nPass;
//		int n2pho = suckinRawLogFile(*it, nPass);
		suckinRawLogFile(*it, nPass);
		h_eff_ttaa->Fill(temp,tempH,100.0*((float)nPass[topo])/((float)(*it)->NGenPoints));
	}


	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
		if((*it)->gettype() != type_to_run) continue;
		int temp = (*it)->Mstop;
		int tempH = (*it)->Mhiggsino;
		if (temp > 510) continue;
		if(temp == 375 || temp == 425) continue;
		if(temp == 450 && tempH == 200) continue;
		//if(temp == 325 && tempH == 175) continue;
		Labeledint nPass;
		MCpoint* mu = map_bbaa[tempH];
		suckinRawLogFile(mu, nPass);
		h_eff_bbaa_mu->Fill(temp,tempH,100.0*((float)nPass[topo])/((float)mu->NGenPoints));
	}
	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
		if((*it)->gettype() != type_to_run+1) continue;
		int temp = (*it)->Mstop;
		int tempH = (*it)->Mhiggsino;
		if (temp > 510) continue;
		if(temp == 375 || temp == 425) continue;
		if(temp == 450 && tempH == 200) continue;
		//if(temp == 325 && tempH == 175) continue;
		Labeledint nPass;
		MCpoint* mu = map_wwaa[tempH];
		suckinRawLogFile(mu, nPass);
		h_eff_wwaa_mu->Fill(temp,tempH,100.0*((float)nPass[topo])/((float)mu->NGenPoints));
	}
	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
		if((*it)->gettype() != type_to_run+2) continue;
		int temp = (*it)->Mstop;
		int tempH = (*it)->Mhiggsino;
		if (temp > 510) continue;
		if(temp == 375 || temp == 425) continue;
		if(temp == 450 && tempH == 200) continue;
		//if(temp == 325 && tempH == 175) continue;
		Labeledint nPass;
		MCpoint* mu = map_zzaa[tempH];
		suckinRawLogFile(mu, nPass);
		h_eff_zzaa_mu->Fill(temp,tempH,100.0*((float)nPass[topo])/((float)mu->NGenPoints));
	}
	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
		if((*it)->gettype() != type_to_run+3) continue;
		int temp = (*it)->Mstop;
		int tempH = (*it)->Mhiggsino;
		if (temp > 510) continue;
		if(temp == 375 || temp == 425) continue;
		if(temp == 450 && tempH == 200) continue;
		//if(temp == 325 && tempH == 175) continue;
		Labeledint nPass;
		MCpoint* mu = map_ttaa[tempH];
		suckinRawLogFile(mu, nPass);
		h_eff_ttaa_mu->Fill(temp,tempH,100.0*((float)nPass[topo])/((float)mu->NGenPoints));
	}


	cout<<" DOING TOPO "<<topo<<endl;
	printf(" ** tops **\n");
	printf("\nbbaa\n");
	print2D(h_eff);
	printf("\nwwaa\n");
	print2D(h_eff_wwaa);
	printf("\nzzaa\n");
	print2D(h_eff_zzaa);
	printf("\nttaa\n");
	print2D(h_eff_ttaa);

	printf("\n ** higgsinos **\n");
	printf("\nbbaa\n");
	print2D(h_eff_bbaa_mu);
	printf("\nwwaa\n");
	print2D(h_eff_wwaa_mu);
	printf("\nzzaa\n");
	print2D(h_eff_zzaa_mu);
	printf("\nttaa\n");
	print2D(h_eff_ttaa_mu);


	float bb_br = 0.561;
        float ww_br = 0.231;
        float zz_br = 0.0289;
        float tt_br = 0.0615;
	h_eff->Scale(bb_br);
	h_eff->Add(h_eff_wwaa,ww_br);
	h_eff->Add(h_eff_zzaa,zz_br);
	h_eff->Add(h_eff_ttaa,tt_br);
	h_eff->Scale(1.0/(bb_br+ww_br+zz_br+tt_br));

	printf(" ** tops combined **\n");
	print2D(h_eff);
	TH2F* h_eff_tops = (TH2F*)h_eff->Clone("tops");

	h_eff_bbaa_mu->Scale(bb_br);
	h_eff_bbaa_mu->Add(h_eff_wwaa_mu,ww_br);
	h_eff_bbaa_mu->Add(h_eff_zzaa_mu,zz_br);
	h_eff_bbaa_mu->Add(h_eff_ttaa_mu,tt_br);
	h_eff_bbaa_mu->Scale(1.0/(bb_br+ww_br+zz_br+tt_br));
	
	printf("\n ** higgsinos combined**\n");
	print2D(h_eff_bbaa_mu);

	float topcs[3][3];
	float mucs[3][3];
	//now weight by cross sections. 
        for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
                if((*it)->gettype() != type_to_run) continue;
                int temp = (*it)->Mstop;
                int tempH = (*it)->Mhiggsino;
                if (temp > 510) continue;
                if(temp == 375 || temp == 425) continue;
		if(temp == 450 && tempH == 200) continue;
		//if(temp == 325 && tempH == 175) continue;

		float stop_cs = (*it)->cs_fb();	
		float mu_cs = 0;
                for(std::vector<MCpoint*>::iterator it_mu = points.begin();it_mu != points.end();it_mu++){
                        if((*it_mu)->gettype() != type_to_run + 10 || (*it_mu)->Mhiggsino != tempH) continue;
                        mu_cs = (*it_mu)->cs_fb();
                        break;
                }
		//now have both cross sections. 

		if(temp == 500 && tempH==350){ topcs[0][2] = stop_cs; mucs[0][2] = mu_cs;}
		if(temp == 350 && tempH==250){ topcs[1][1] = stop_cs; mucs[1][1] = mu_cs;}
		if(temp == 500 && tempH==250){ topcs[1][2] = stop_cs; mucs[1][2] = mu_cs;}
		if(temp == 200 && tempH==150){ topcs[2][0] = stop_cs; mucs[2][0] = mu_cs;}
		if(temp == 350 && tempH==150){ topcs[2][1] = stop_cs; mucs[2][1] = mu_cs;}
		if(temp == 500 && tempH==150){ topcs[2][2] = stop_cs; mucs[2][2] = mu_cs;}

		//weight by xsec 
                int xbin = h_eff->GetXaxis()->FindBin((*it)->Mstop);
                int ybin = h_eff->GetYaxis()->FindBin((*it)->Mhiggsino);
	
		h_eff->SetBinContent(xbin,ybin, (stop_cs*h_eff->GetBinContent(xbin,ybin) + mu_cs*h_eff_bbaa_mu->GetBinContent(xbin,ybin))/(stop_cs+mu_cs));
        }

	//now your finished cs map for this topo is in h_eff
	printf("stop xsec\n");

	printf("350|                    %4.2f\n",topcs[0][2]);
	printf("250|          %4.2f      %4.2f\n",topcs[1][1],topcs[1][2]);
	printf("150|%4.2f      %4.2f      %4.2f\n",topcs[2][0],topcs[2][1],topcs[2][2]);
	printf("----------------------------\n");
	printf("   | 200       350       500\n");

	printf("higgsino xsec\n");
	printf("350|                    %4.2f\n",mucs[0][2]);
	printf("250|          %4.2f      %4.2f\n",mucs[1][1],mucs[1][2]);
	printf("150|%4.2f      %4.2f      %4.2f\n",mucs[2][0],mucs[2][1],mucs[2][2]);
	printf("----------------------------\n");
	printf("   | 200       350       500\n");
	

	printf(" ** net **\n");
	print2D(h_eff);

	interpolate_Zywicki(h_eff,false);
	interpolate_Zywicki(h_eff_tops,false);
	//TH2F* h_eff_topsdiv = (TH2F*)h_eff->Clone("topsdiv");

	canv->SetRightMargin(0.2);
	h_eff->GetXaxis()->SetNdivisions(506);
	h_eff->GetYaxis()->SetNdivisions(505);
	//h_eff->GetYaxis()->SetTitleOffset(1.2);
	//h_eff->GetZaxis()->SetTitleOffset(1.1);
	PrettyHist(h_eff);
	h_eff->GetXaxis()->SetRangeUser(180,510);
	h_eff->GetYaxis()->SetRangeUser(140,500);

	h_eff_tops->GetXaxis()->SetNdivisions(506);
	h_eff_tops->GetYaxis()->SetNdivisions(505);
	//h_eff_tops->GetYaxis()->SetTitleOffset(1.2);
	//h_eff_tops->GetZaxis()->SetTitleOffset(1.1);
	PrettyHist(h_eff_tops);
	h_eff_tops->GetXaxis()->SetRangeUser(180,510);
	h_eff_tops->GetYaxis()->SetRangeUser(140,500);

	gStyle->SetPalette(1);
	//h_eff->SetMaximum(1.2);
	//h_eff->SetMinimum(0);
	h_eff->Draw("COL Z");
	TEX_CMSPrelim->Draw("same");
	//TEX_sqrtS_lumi_fb->Draw("same");
	//TEX_E_TeV->Draw("same");
	//TEX_lumi_fb->Draw("same");

	if (saveplot) { 
		canv->SaveAs(Form("%sEff_%s_comb.gif",plotsdir.data(),topo.data()));
		canv->SaveAs(Form("%sEff_%s_comb.pdf",plotsdir.data(),topo.data()));
		canv->SaveAs(Form("%sEff_%s_comb.png",plotsdir.data(),topo.data()));
		canv->SaveAs(Form("%sEff_%s_comb.root",plotsdir.data(),topo.data()));
		canv->SaveAs(Form("%sEff_%s_comb.C",plotsdir.data(),topo.data()));
	}

	
	TCanvas* canvT = new TCanvas(plotname.Data(),plotname.Data(),800,600);
	canvT->SetTopMargin(0.10);
	canvT->SetBottomMargin(0.15);
	canvT->SetRightMargin(0.2);
	h_eff_tops->Draw("COL Z");
	TEX_CMSPrelim->Draw("same");
	//TEX_sqrtS_lumi_fb->Draw("same");
	//TEX_E_TeV->Draw("same");
	//TEX_lumi_fb->Draw("same");

	if (saveplot) { 
		canvT->SaveAs(Form("%sEff_%s_comb_stoponly.gif",plotsdir.data(),topo.data()));
		canvT->SaveAs(Form("%sEff_%s_comb_stoponly.pdf",plotsdir.data(),topo.data()));
		canvT->SaveAs(Form("%sEff_%s_comb_stoponly.png",plotsdir.data(),topo.data()));
		canvT->SaveAs(Form("%sEff_%s_comb_stoponly.root",plotsdir.data(),topo.data()));
		canvT->SaveAs(Form("%sEff_%s_comb_stoponly.C",plotsdir.data(),topo.data()));
	}
	return canv;
}//end MakeEffPlotComb

/*
//I'm commenting this out b/c I don't understand what it does and am to lazy to figure it out
//Also it's not updated to use higgsino 

void MakeEffPlots(bool saveplot){
	printf("in MakeEffPlots\n");
		//setup up general style
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	gStyle->SetPadLeftMargin(0.15);
	CMSStyle();

        TLatex * TEX_CMSPrelim = new TLatex(0.177136,0.935315,"CMS Simulation Preliminary");
        PrettyLatex(TEX_CMSPrelim,0.03);
        TLatex * TEX_E_TeV = new TLatex(0.700251,0.935315,"#sqrt{s} = 8 TeV");
        PrettyLatex(TEX_E_TeV,0.03);
        TLatex * TEX_lumi_fb = new TLatex(0.551859,0.935315,Form("#intL dt = %.1f fb^{-1}",Integrated_Luminosity_Data));
        PrettyLatex(TEX_lumi_fb,0.03);
		//setup bins
	const int nS = 11; //xBinning
	const int nH = 19;

	float mSBins[nS+1] = {187.5, 212.5, 237.5 ,262.5 ,287.5, 312.5, 337.5, 362.5,    375, 425, 475, 525};
	float mHBins[nH+1] = {130, 140, 160, 190, 210,    220, 230, 235,245, 255,     260, 270, 280, 285,295,     305, 310,320, 330,370};

	LableHist2 h_eff;
	//allocate histograms
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
		suckinRawLogFile(*it, nPass);

		//Labeledint nPass_mu;
//				int n2pho = suckinRawLogFile(*it, nPass);
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
		canv->SetTopMargin(0.10);
		canv->SetBottomMargin(0.15);

		canv->SetRightMargin(0.2);
		h_eff[s_EventTopology[iTopo]]->GetXaxis()->SetNdivisions(505);
		h_eff[s_EventTopology[iTopo]]->GetYaxis()->SetNdivisions(505);
		h_eff[s_EventTopology[iTopo]]->GetYaxis()->SetTitleOffset(1.2);
		h_eff[s_EventTopology[iTopo]]->GetZaxis()->SetTitleOffset(1.1);
		PrettyHist(h_eff[s_EventTopology[iTopo]]);
		h_eff[s_EventTopology[iTopo]]->GetXaxis()->SetRangeUser(180,510);
		h_eff[s_EventTopology[iTopo]]->GetYaxis()->SetRangeUser(140,500);

		gStyle->SetPalette(1);
			//h_eff->SetMaximum(1.2);
			//h_eff->SetMinimum(0);
		h_eff[s_EventTopology[iTopo]]->Draw("COL Z");
                TEX_CMSPrelim->Draw("same");
		TEX_E_TeV->Draw("same");
		TEX_lumi_fb->Draw("same");

		if (saveplot) {
			canv->SaveAs(Form("%sEff_%s.gif",plotsdir.data(),s_EventTopology[iTopo].data()));
			canv->SaveAs(Form("%sEff_%s.pdf",plotsdir.data(),s_EventTopology[iTopo].data()));
			canv->SaveAs(Form("%sEff_%s.png",plotsdir.data(),s_EventTopology[iTopo].data()));
		}
	}//end for every topo

}//end MakeEffPlots*/

void makeHiggsinoMap(std::vector<MCpoint*> points, higgsinoMap & map,int which){
        for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
                if((*it)->gettype() != which) continue;

                for(std::vector<MCpoint*>::iterator it_mu = points.begin();it_mu != points.end();it_mu++){
                        if((*it_mu)->gettype() != which+10 || (*it_mu)->Mhiggsino != (*it)->Mhiggsino) continue;
                        map[(*it)->Mhiggsino] = (*it_mu);
                        break;
                }
        }//end for every stop point
}//end makeHiggsinoMap

void print2D(TH2F* h){
	printf("350|                    %4.2f\n",h->GetBinContent(11,19) );
	printf("250|          %4.2f      %4.2f\n",h->GetBinContent(6,9),h->GetBinContent(11,9) );
	printf("150|%4.2f      %4.2f      %4.2f\n",h->GetBinContent(1,2), h->GetBinContent(6,2)  , h->GetBinContent(11,2) );
	printf("----------------------------\n");
	printf("   | 200       350       500\n");
}
