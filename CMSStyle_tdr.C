#ifndef CMSSTYLE_C // if not defined
#define CMSSTYLE_C

#include "TStyle.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TH1.h"
#include "TROOT.h"
#include <TCanvas.h>
#include "TLegend.h"
#include "utilities.h"
#include "TPaveText.h"
#include "TLatex.h"
	//##########################################################################
	// Initialization code executed at the start of a ROOT session.
	//
	// File: $Id: CMSStyle.C,v 1.1 2010/08/20 00:20:34 iraklis Exp $
	//##########################################################################

	//#include <iostream>
	//using namespace std;


void CMSStyle();
void PrettyLegend(TLegend* leg, float fontSize = 0.05);
void PrettyText(TPaveText* text, float fontSize = 0.05);
void PrettyLatex(TLatex* text, float fontSize = 0.03814);
void PrettyHist(TH1F* h, int color = 1, int width = 3, int linestyle = 0);
void PrettyHist(TH2F* h, int color = 1, int width = 3, int linestyle = 0);
void PrettyGraph(TGraph* h, int color, int width, int linestyle );

void PrettyMarker(TH1F* h, int color = 1, int markerstyle = 20, float markersize = 1.2f);
void PrettyMarker(TH2F* h, int color = 1, int markerstyle = 20, float markersize = 1.2f);
void PrettyFonts(TH1F* h);
void PrettyFonts(TH1D* h);
void PrettyFonts(TH2F* h);
void PrettyFonts(TH2D* h);

void PrettyFillColor(TH1F* h, int color);
void PrettyBlock2(TH1* hist, int color=4, int style=1001, int width=1);
void PrettyBlock(TH1* hist, int color=4, string option="//thatch");

TLegend* newTLegend();
void UnitNorm(TH1F* hist);
void MatchArea(TH1F* toScale, TH1F* toMatch);
void SameRange(TH1F* hist1, TH1F* hist2);
void SetRange(TH1F* hist, float _min = 0.0f, float _max = -1.15);
float RaiseRangeRoof(TH1F* hist, float mult=1.2);
float highestErrorBar(TH1F *h);
float lowestErrorBar(TH1F *h);
void playNiceWithLegend(TH1F* h, float legendFraction, float h_min=-1.0f, float h_max=-1.0f);
void playNiceWithLegendLog(TH1F* h, float legendFraction, float h_min=-1.0f, float h_max=-1.0f);

void DrawSame(TH1F* h0, TH1F* h1, char* ops="");
void DrawSame(TH1F* h0, TH1F* h1, TH1F* h2, char* ops="");
void DrawSame(TH1F* h0, TH1F* h1, TH1F* h2, TH1F* h3, char* ops="");
void DrawSame(TH1F* h0, TH1F* h1, TH1F* h2, TH1F* h3,TH1F* h4, char* ops="");
void DrawSame(TH1F* h0, TH1F* h1, TH1F* h2, TH1F* h3,TH1F* h4,TH1F* h5, char* ops="");
TCanvas * newTCanvas(char* rootname, char* title = ""); //makes an 800x800 TCanvas and cd's into it.
TCanvas * newTCanvas(string rootname, string title = "");

void CMSStyle(){
		// use the 'plain' style for plots (white backgrounds, etc)
		//  cout << "...using style 'Plain'" << endl;
	gROOT->SetStyle("Plain");

		// Create the 'CMS' style for approved plots. Note that this style may need
		// some fine tuning in your macro depending on what you are plotting, e.g.
		//
		//  gStyle->SetMarkerSize(0.75);  // use smaller markers in a histogram with many bins
		//  gStyle->SetTitleOffset(0.65,"y");  // bring y axis label closer to narrow values

	TStyle *cmsStyle= new TStyle("CMS","CMS approved plots style");

		// use plain black on white colors
	cmsStyle->SetFrameBorderMode(0);
	cmsStyle->SetCanvasBorderMode(0);
	cmsStyle->SetPadBorderMode(0);
	cmsStyle->SetPadColor(0);
	cmsStyle->SetCanvasColor(kWhite);
	cmsStyle->SetTitleColor(1);
//	cmsStyle->SetStatColor(0);
	cmsStyle->SetStatColor(kWhite);
	cmsStyle->SetFrameFillColor(0);
	cmsStyle->SetCanvasDefH(600); //Height of canvas
	cmsStyle->SetCanvasDefW(600); //Width of canvas
	cmsStyle->SetCanvasDefX(0);   //POsition on screen
	cmsStyle->SetCanvasDefY(0);

	cmsStyle->SetFrameBorderSize(1);
	cmsStyle->SetFrameFillStyle(0);
	cmsStyle->SetFrameLineColor(1);
	cmsStyle->SetFrameLineStyle(1);
	cmsStyle->SetFrameLineWidth(1);


		// set the paper & margin sizes
//	cmsStyle->SetPaperSize(20,26);
	cmsStyle->SetPaperSize(20.,20.);
//	cmsStyle->SetPadTopMargin(0.05);
//	cmsStyle->SetPadRightMargin(0.05);
//	cmsStyle->SetPadBottomMargin(0.17);
//	cmsStyle->SetPadLeftMargin(0.17);

	cmsStyle->SetPadTopMargin(0.05);
	cmsStyle->SetPadBottomMargin(0.13);
	cmsStyle->SetPadLeftMargin(0.16);
	cmsStyle->SetPadRightMargin(0.02);

	cmsStyle->SetPadBorderMode(0);
	cmsStyle->SetPadColor(kWhite);
	cmsStyle->SetPadGridX(false);
	cmsStyle->SetPadGridY(false);
	cmsStyle->SetGridColor(0);
	cmsStyle->SetGridStyle(3);
	cmsStyle->SetGridWidth(1);


		// use large Times-Roman fonts
	cmsStyle->SetTextFont(42); //was 132
	cmsStyle->SetTextSize(0.08);
	cmsStyle->SetLabelFont(42,"x"); //was 132
	cmsStyle->SetLabelFont(42,"y"); //was 132
	cmsStyle->SetLabelFont(42,"z"); //was 132
	cmsStyle->SetLabelSize(0.05,"x");
	cmsStyle->SetTitleSize(0.05,"x"); //was 0.06
	cmsStyle->SetLabelSize(0.05,"y");
	cmsStyle->SetTitleSize(0.05,"y"); //was 0.06
	cmsStyle->SetLabelSize(0.05,"z");
	cmsStyle->SetTitleSize(0.05,"z"); //was 0.06

		// use bold lines and markers
//	cmsStyle->SetMarkerStyle(8);
	cmsStyle->SetMarkerStyle(20);
	cmsStyle->SetErrorX(0.);
	cmsStyle->SetEndErrorSize(2);

//	cmsStyle->SetHistLineWidth(1.85);
	cmsStyle->SetHistLineWidth(1);
	cmsStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

		// do not display any of the standard histogram decorations
//	cmsStyle->SetOptTitle(1);
//	cmsStyle->SetOptStat(1);
	cmsStyle->SetOptFit(1);
	cmsStyle->SetOptTitle(0);
	cmsStyle->SetOptStat(0);

		//For the fit/function:
//	cmsStyle->SetOptFit(1);
	cmsStyle->SetFitFormat("5.4g");
	cmsStyle->SetFuncColor(2);
	cmsStyle->SetFuncStyle(1);
	cmsStyle->SetFuncWidth(1);

		//For the date:
	cmsStyle->SetOptDate(0);

		// For the statistics box:
	cmsStyle->SetOptFile(0);
	cmsStyle->SetOptStat(0);
	cmsStyle->SetStatFont(42);
	cmsStyle->SetStatFontSize(0.025);
	cmsStyle->SetStatTextColor(1);
	cmsStyle->SetStatFormat("6.4g");
	cmsStyle->SetStatBorderSize(1);
	cmsStyle->SetStatH(0.1);
	cmsStyle->SetStatW(0.15);



		// put tick marks on top and RHS of plots
	cmsStyle->SetPadTickX(1);
	cmsStyle->SetPadTickY(1);
	cmsStyle->SetAxisColor(1, "XYZ");
	cmsStyle->SetStripDecimals(kTRUE);
	cmsStyle->SetTickLength(0.03, "XYZ");
	cmsStyle->SetNdivisions(510, "XYZ");

		// For the Global title:
	cmsStyle->SetOptTitle(0);
	cmsStyle->SetTitleFont(42);
	cmsStyle->SetTitleTextColor(1);
	cmsStyle->SetTitleFillColor(10);
	cmsStyle->SetTitleFontSize(0.05);

		// For the axis titles:
	cmsStyle->SetTitleColor(1, "XYZ");
	cmsStyle->SetTitleFont(42, "XYZ");
	cmsStyle->SetTitleSize(0.06, "XYZ");
	cmsStyle->SetTitleXOffset(0.9);
	cmsStyle->SetTitleYOffset(1.25);

		// For the axis labels:
	cmsStyle->SetLabelColor(1, "XYZ");
	cmsStyle->SetLabelFont(42, "XYZ");
	cmsStyle->SetLabelOffset(0.007, "XYZ");
	cmsStyle->SetLabelSize(0.05, "XYZ");



		//  cout << endl << "    For approved plots use: gROOT->SetStyle(\"CMS\");"
		//       << endl << "  To add a CMS label use: CMSLabel();"
		//       << endl << endl;

		// restore the plain style
	gROOT->SetStyle("Plain");
	gROOT->SetStyle("CMS");
	return ;
}

void PrettyLegend(TLegend* leg, float fontSize){
		//default fontSize = 0.05;
	leg->SetTextFont(42); //was 132
	leg->SetFillColor(0);
	leg->SetBorderSize(0);
	leg->SetTextSize(fontSize);
}

void PrettyText(TPaveText* text, float fontSize){
		//default fontSize = 0.05;
		//	text->SetNDC();
	text->SetTextFont(42); //was 132
	text->SetFillColor(0);
	text->SetBorderSize(0);
	text->SetTextSize(fontSize);
		//	textlims->SetShadowColor(0); //if need to kill the ugly shadow.
}
void PrettyLatex(TLatex* text, float fontSize){
	text->SetNDC();
	text->SetTextFont(42); //was 132
	text->SetTextSize(fontSize);
	text->SetLineWidth(2);
}

void PrettyHist(TH1F* h, int color, int width, int linestyle ){
		//defaults: PrettyHist(TH1F* h, int color = 1, int width = 3, int linestyle = 0){
	h->SetLineColor(color);
	h->SetLineWidth(width);
	h->SetLineStyle(linestyle);
	h->SetStats(0);
	PrettyFonts(h);
	h->GetXaxis()->SetLabelSize(0.05); //was 0.043
	h->GetYaxis()->SetLabelSize(0.05); //was 0.043
}
void PrettyHist(TH2F* h, int color, int width, int linestyle ){
		//defaults: PrettyHist(TH1F* h, int color = 1, int width = 3, int linestyle = 0){
	h->SetLineColor(color);
	h->SetLineWidth(width);
	h->SetLineStyle(linestyle);
	h->SetStats(0);
	PrettyFonts(h);
	h->GetXaxis()->SetLabelSize(0.05); //was 0.043
	h->GetYaxis()->SetLabelSize(0.05); //was 0.043
	h->GetZaxis()->SetLabelSize(0.05); //was 0.043
}
void PrettyGraph(TGraph* h, int color, int width, int linestyle ){
                //defaults: PrettyHist(TH1F* h, int color = 1, int width = 3, int linestyle = 0){
        h->SetLineColor(color);
        h->SetLineWidth(width);
        h->SetLineStyle(linestyle);
}

	///Can I do this?
	//Descriptive constants for line Styles.
static const int sSolid = 1;
static const int sdashed = 2;
static const int sDashed = 7;
static const int sdotted = 3;
static const int sdotdash = 4;
static const int sdotDash = 5;
static const int sbigDash = 9;
static const int bigdotDash = 10;

void PrettyFonts(TH1F* h){
	TAxis * x = h->GetXaxis();
	TAxis * y = h->GetYaxis();
	x->SetTitleFont(42); //was 132
	y->SetTitleFont(42); //was 132
	x->SetTitleSize(0.06);
	x->SetTitleOffset(1.05); //make the Title a little further from the axis
	y->SetTitleOffset(1.05);
	y->SetTitleSize(0.06);
	x->SetLabelFont(42); //was 132
	y->SetLabelFont(42); //was 132
	x->SetLabelSize(0.05); //was 0.06
	y->SetLabelSize(0.05); //was 0.06
}
void PrettyFonts(TH1D* h){
	TAxis * x = h->GetXaxis();
	TAxis * y = h->GetYaxis();
	x->SetTitleFont(42); //was 132
	y->SetTitleFont(42); //was 132
	x->SetTitleSize(0.06);
	x->SetTitleOffset(1.05); //make the Title a little further from the axis
	y->SetTitleOffset(1.05);
	y->SetTitleSize(0.06);
	x->SetLabelFont(42); //was 132
	y->SetLabelFont(42); //was 132
	x->SetLabelSize(0.05); //was 0.06
	y->SetLabelSize(0.05); //was 0.06
}
void PrettyFonts(TH2F* h){
	TAxis * x = h->GetXaxis();
	TAxis * y = h->GetYaxis();
	TAxis * z = h->GetZaxis();
	x->SetTitleFont(42); //was 132
	y->SetTitleFont(42); //was 132
	z->SetTitleFont(42); //was 132
	x->SetTitleSize(0.06);
	x->SetTitleOffset(1.05); //make the Title a little further from the axis
	y->SetTitleOffset(1.05);
	y->SetTitleSize(0.06);
	x->SetLabelFont(42); //was 132
	y->SetLabelFont(42); //was 132
	z->SetLabelFont(42); //was 132
	x->SetLabelSize(0.05); //was 0.06
	y->SetLabelSize(0.05); //was 0.06
	z->SetLabelSize(0.05); //was 0.06
}
void PrettyFonts(TH2D* h){
	TAxis * x = h->GetXaxis();
	TAxis * y = h->GetYaxis();
	TAxis * z = h->GetZaxis();
	x->SetTitleFont(42); //was 132
	y->SetTitleFont(42); //was 132
	z->SetTitleFont(42); //was 132
	x->SetTitleSize(0.06);
	x->SetTitleOffset(1.05); //make the Title a little further from the axis
	y->SetTitleOffset(1.05);
	y->SetTitleSize(0.06);
	x->SetLabelFont(42); //was 132
	y->SetLabelFont(42); //was 132
	z->SetLabelFont(42); //was 132
	x->SetLabelSize(0.05); //was 0.06
	y->SetLabelSize(0.05); //was 0.06
	z->SetLabelSize(0.05); //was 0.06
}

void PrettyFillColor(TH1F* h, int color){
	h->SetLineColor(color);
	h->SetFillColor(color);
	h->SetFillStyle(1001);
}

void PrettyBlock2(TH1* hist, int color, int style, int width){
		//These are meant for hist markers where the uncertainty range is a filled rectangle for each point and no marker
		//recommend the Draw("E2") option.
		//http://root.cern.ch/root/html/TAttFill.html
	hist->SetFillColor(color);
	hist->SetMarkerColor(color);
	hist->SetFillStyle(style);
	hist->SetMarkerSize(0); //totally sufficient for turning off the marker.
	gStyle->SetHatchesLineWidth(width);
}

void PrettyBlock(TH1* hist, int color, string option){
		//These are meant for hist markers where the uncertainty range is a filled rectangle for each point and no marker
		//recommend the Draw("E2") option.
		//http://root.cern.ch/root/html/TAttFill.html
		//Give it a string and it'll give you your working point.
	std::map<string,int> optionMap;
	optionMap["solid"] = 0;
	optionMap[""] = 0;//also solid
	optionMap["\\thatch"] =1;//bold wide thatch \ way
	optionMap["//thatch"] = 2;//bold wide thatch / way
	optionMap["transparent"] = 3;//half transparent
		//for finer thatching, try 3004(/), 3005(\)

	hist->SetFillColor(color);
	hist->SetMarkerColor(color);
	hist->SetMarkerSize(0); //totally sufficient for turning off the marker.
	switch( optionMap[option]){
		case 0: //solid
			hist->SetFillStyle(1001);
			gStyle->SetHatchesLineWidth(1);
		case 1: //  "\thatch"
			hist->SetFillStyle(3345);
			gStyle->SetHatchesLineWidth(2);
		case 2: //  "/thatch"
			hist->SetFillStyle(3354);
			gStyle->SetHatchesLineWidth(2);
		case 3: //  transparent
			hist->SetFillStyle(4050);//half transparent, half visible
			gStyle->SetHatchesLineWidth(1);
	}//end switch
}



void PrettyMarker(TH1F* h, int color, int markerstyle, float markersize){
	h->SetMarkerColor(color);
	h->SetMarkerSize(markersize);
	h->SetMarkerStyle(markerstyle);
}
void PrettyMarker(TH2F* h, int color, int markerstyle, float markersize){
	h->SetMarkerColor(color);
	h->SetMarkerSize(markersize);
	h->SetMarkerStyle(markerstyle);
}
/*
 Marker Styles:
 Marker number         Marker shape          Marker name
 1                    dot                  kDot
 2                    +                    kPlus
 3                    *                    kStar
 4                    o                    kCircle
 5                    x                    kMultiply
 6                    small scalable dot   kFullDotSmall
 7                    medium scalable dot  kFullDotMedium
 8                    large scalable dot   kFullDotLarge
 9 -->19              dot
 20                    full circle          kFullCircle
 21                    full square          kFullSquare
 22                    full triangle up     kFullTriangleUp
 23                    full triangle down   kFullTriangleDown
 24                    open circle          kOpenCircle
 25                    open square          kOpenSquare
 26                    open triangle up     kOpenTriangleUp
 27                    open diamond         kOpenDiamond
 28                    open cross           kOpenCross
 29                    open star            kOpenStar
 30                    full star            kFullStar
 http://physics.lunet.edu/docs/root/TAttMarker.html
 */


TLegend* newTLegend(){
		//makes a pretty TLegend with an unremarkable initial position. Use in place of "new TLegend(..." when you're lazy.
	TLegend* leg = 	new TLegend(0.75,0.60,.95,.80);
	PrettyLegend(leg);
	return leg;
}
void UnitNorm(TH1F* hist){ //makes hist have unit norm
	float norm = hist->Integral();
	if(norm >0.00001) hist->Scale(1.f/norm);
	else printf("WARNING: trying to take unit norm of an empty histogram\n");
}
void MatchArea(TH1F* toScale, TH1F* toMatch){
		//makes the area of toScale the same as toMatch
	float normM = toMatch->Integral();
	float normS = toScale->Integral();
	toScale->Scale(normM/normS);
}
void SetRange(TH1F* hist, float _min, float _max){
//void SetRange(TH1F* hist, float min = 0.0f, float Max = -1.15);
		//set histogram range. Max = -1.15 -> Max is 115% highest bin.
	if(_max < -1 && _max > -1.2) _max = 1.15*hist->GetMaximum();
	hist->SetMaximum(_max);
	hist->SetMinimum(_min);
}
void SameRange(TH1F* hist1, TH1F* hist2){
		//sets makes the range of both histograms accomodate either histogram.
	float _max = TMath::Max(hist1->GetMaximum(),hist2->GetMaximum());
	float _min = TMath::Min(hist1->GetMinimum(),hist2->GetMinimum());
	hist1->SetMaximum(_max);
	hist1->SetMinimum(_min);
	hist2->SetMaximum(_max);
	hist2->SetMinimum(_min);
}
void SameRange(TH1F* hist1, TH1F* hist2, TH1F* hist3){
		//sets makes the range of both histograms accomodate either histogram.
	float _max = TMath::Max((float)hist1->GetMaximum(),(float)hist2->GetMaximum());
	_max = TMath::Max((float)_max,(float)hist3->GetMaximum());
	float _min = TMath::Min((float)hist1->GetMinimum(),(float)hist2->GetMinimum());
	_min = TMath::Min((float)_min,(float)hist3->GetMinimum());
	hist1->SetMaximum(_max);
	hist1->SetMinimum(_min);
	hist2->SetMaximum(_max);
	hist2->SetMinimum(_min);
	hist3->SetMaximum(_max);
	hist3->SetMinimum(_min);
}
float RaiseRangeRoof(TH1F* hist, float mult){
		//takes the existing max range and multiplies it by mult. Default is 1.2
		//returns what the new max is set to.
	float newmax = hist->GetMaximum()*mult;
	hist->SetMaximum(newmax);
	return newmax;
}
float highestErrorBar(TH1F *h){
	float ret = h->GetBinContent(1);
	for(int i=1;i<=h->GetNbinsX();i++){
		float temp = h->GetBinContent(i)+h->GetBinError(i);
		ret = (float)TMath::Max((Float_t)ret,(Float_t)temp);
	}
	return ret;
}
float lowestErrorBar(TH1F *h){
	float ret = h->GetBinContent(1);
	for(int i=1;i<=h->GetNbinsX();i++){
		ret = (float)TMath::Min((double)ret,h->GetBinContent(i)-h->GetBinError(i));
	}
	return ret;
}
void playNiceWithLegend(TH1F* h, float legendFraction, float h_min, float h_max){
		//legendFraction is the proportion of the plot space on top reserved for the legend.
		//h_max and h_min are the usual bounds on the hist; by default they subsume the widest error bars.
		//IF WORKING WITH MULTIPLE HISTS, FOLLOW THIS WITH A SameRange COMMAND
	if(aeq(h_max,-1.0f)) h_max = highestErrorBar(h);
	if(aeq(h_min,-1.0f)) h_min = lowestErrorBar(h);
	if(legendFraction <0.0f || legendFraction>=1.0f){
		SetRange(h,h_min,h_max);
		return;
	}
	float newmax = (h_max - legendFraction*h_min)/(1.0f-legendFraction);
	SetRange(h,h_min,newmax);
}
void playNiceWithLegendLog(TH1F* h, float legendFraction, float h_min, float h_max){
		//legendFraction is the proportion of the plot space on top reserved for the legend.
		//h_max and h_min are the usual bounds on the hist; by default they subsume the widest error bars.
		//IF WORKING WITH MULTIPLE HISTS, FOLLOW THIS WITH A SameRange COMMAND
	if(aeq(h_max, -1.0f)) h_max = highestErrorBar(h);
	if(aeq(h_min, -1.0f)) h_min = lowestErrorBar(h);
	if(h_max <=0.0f) return;
	if(legendFraction <0.0f || legendFraction>=1.0f){
		SetRange(h,h_min,h_max);
		return;
	}
	float newmax = TMath::Exp((TMath::Log(h_max) - legendFraction*TMath::Log(h_min))/(1.0f-legendFraction));
	SetRange(h,h_min,newmax);
}



void DrawSame(TH1F* h0, TH1F* h1, char* ops){
	std::string same = "same";
	h0->Draw(ops);
	h1->Draw((same+ops).c_str());
}
void DrawSame(TH1F* h0, TH1F* h1, TH1F* h2, char* ops){
	std::string same = "same";
	h0->Draw(ops);
	h1->Draw((same+ops).c_str());
	h2->Draw((same+ops).c_str());
}

void DrawSame(TH1F* h0, TH1F* h1, TH1F* h2, TH1F* h3, char* ops){
	std::string same = "same";
	h0->Draw(ops);
	h1->Draw((same+ops).c_str());
	h2->Draw((same+ops).c_str());
	h3->Draw((same+ops).c_str());
}
void DrawSame(TH1F* h0, TH1F* h1, TH1F* h2, TH1F* h3,TH1F* h4, char* ops){
	std::string same = "same";
	h0->Draw(ops);
	h1->Draw((same+ops).c_str());
	h2->Draw((same+ops).c_str());
	h3->Draw((same+ops).c_str());
	h4->Draw((same+ops).c_str());
}
void DrawSame(TH1F* h0, TH1F* h1, TH1F* h2, TH1F* h3,TH1F* h4,TH1F* h5, char* ops){
	std::string same = "same";
	h0->Draw(ops);
	h1->Draw((same+ops).c_str());
	h2->Draw((same+ops).c_str());
	h3->Draw((same+ops).c_str());
	h4->Draw((same+ops).c_str());
	h5->Draw((same+ops).c_str());
}



TCanvas * newTCanvas(char* rootname, char* title){
	TCanvas * canv =new TCanvas( rootname, title, 800, 800);
	canv->SetTopMargin(0.06);
	canv->SetBottomMargin(0.15);
	canv->cd();
	return canv;
}
TCanvas * newTCanvas(string rootname, string title){
	TCanvas * canv =new TCanvas( rootname.data(), title.data(), 800, 800);
	canv->SetTopMargin(0.06);
	canv->SetBottomMargin(0.15);
	canv->cd();
	return canv;
}

void DivideOutBinWidths(TH1F* h, float w){
//scale all bins to be nEvents per W[x_units] rather than nEvents per binWidth[x_units]
	for(short i=1;i<=h->GetXaxis()->GetNbins();i++){
		float scale = w/(h->GetXaxis()->GetBinWidth(i));
		float err = scale*h->GetBinError(i);
		h->SetBinContent(i,scale*h->GetBinContent(i));
		h->SetBinError(i,err);
	}
}//end DivideOutBinWidths

#endif


