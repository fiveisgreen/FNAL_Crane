#include "TAxis.h"
#include "TH1.h"
//#include "TMath.h"
#include <TH2.h>
//#include <TStyle.h>
//#include <TCanvas.h>
//#include "TFile.h"
//#include "TTree.h"
//#include "TVirtualFitter.h"
//#include "TLegend.h"
#include <iostream>
//#include <sstream>
//#include "TString.h"
//#include <fstream>
//#include "TF1.h"
//#include "TLine.h"
	//#include "quicksave.C"
//#include "CMSStyle.C"
#include "utilities.h"
//#include "util.C"
//#include "params_arg.h"
	//#include "params_arg.h"
//#include<string.h>
//#include<map>
//#include <algorithm>    // std::sort
//#include <vector>


using namespace std;
float bilinear_interpolate(float x1,float val1,float x2, float val2, float x_target);//wad
float bilinear_interpolate( float x1, float x2, float y1, float y2,
		float val11, float val12, float val21, float va22,
		float x_target,float y_target);
void interpolate_collumn(TH2F* hin, int col, int rowstart, int rowend); //wad
void interpolate_uneven_column(TH2F* hin, int col, int rowstart, int rowend);//wad
void interpolate_collumn_rowwise(TH2F* hin, int col, int rowstart, int rowend); //wad
TH2F* HistOr(TH2F* h1, TH2F* h2, float blankval, float tollorence);
void interpolate_Zywicki(TH2F* shittyhist,bool bigcol = true);
void interpolate_Zywicki(TH2D* shittyhist,bool bigcol = true);

	///////////TH2D///////////////
void interpolate_collumn(TH2D* hin, int col, int rowstart, int rowend); //wad
void interpolate_uneven_column(TH2D* hin, int col, int rowstart, int rowend);//wad
void interpolate_collumn_rowwise(TH2D* hin, int col, int rowstart, int rowend); //wad
TH2D* HistOr(TH2D* h1, TH2D* h2, float blankval, float tollorence);


// ##############################

float bilinear_interpolate(float x1,float val1,float x2, float val2, float x_target){
	return (x2-x_target)*val1/(x2-x1) + (x_target-x1)*val2/(x2-x1);
} 
float bilinear_interpolate( float x1, float x2, float y1, float y2,
		float val11, float val12, float val21, float val22,
		float x_target,float y_target){
	//take four points on the corners of a rectangle, bilinearly interpolate inside the rectangle. 
	return ((x2-x_target)*(y2-y_target)*val11 + (x_target-x1)*(y2-y_target)*val21 + (x2-x_target)*(y_target-y1)*val12 + (x_target-x1)*(y_target-y1)*val22)/((x2-x1)*(y2-y1));
} 
/*float bilinear_interpolate_center(float val11, float val12, float val21, float va22){
	//take four points on the edges of a rectangle and interpolate the point in the middle. 
	//this is just the average of the four points. 
	return 0.25*(val11+val12+val21+val22);
}*/

void interpolate_collumn(TH2F* hin, int col, int rowstart, int rowend){
	//assumes that alternating cells in the are occupied. 
	//go up the collumn, interpolating the blanks
	TAxis* y = hin->GetYaxis();
	for(int irow = rowstart; irow <= rowend; irow++){
		if(aeq(hin->GetBinContent(col,irow),0)){ //fixed
			hin->SetBinContent(col,irow, //fixed
							   bilinear_interpolate( y->GetBinCenter(irow-1),hin->GetBinContent(col,irow-1), y->GetBinCenter(irow+1), hin->GetBinContent(col,irow+1), y->GetBinCenter(irow) )); //fixed
		} 
	}
}
void interpolate_uneven_column(TH2F* hin, int col, int rowstart, int rowend){
	TAxis* y = hin->GetYaxis();
	//first we crawl up the column, looking for the first non-zero entry

	//then we crawl up to find the next non-zero entry. 
	//then you fill in all the rows inbetween and 
	int lowrow = rowstart;
	int hirow = rowstart+1;
	do{
		if(aeq(hin->GetBinContent(col,lowrow),0)){ //fixed
			lowrow++;
			continue;
		}
		//now on a non-zero entry
		hirow = lowrow+1;
		while(aeq(hin->GetBinContent(col,hirow),0) && hirow <= rowend) hirow++;//fixed
		if(hirow > rowend) break;
		//hirow is now on a no-zero entry. 
		for(int irow = lowrow+1; irow<hirow; irow++){
			hin->SetBinContent(col, irow,//fixed
						bilinear_interpolate( y->GetBinCenter(lowrow),hin->GetBinContent(col,lowrow), y->GetBinCenter(hirow), hin->GetBinContent(col,hirow), y->GetBinCenter(irow) ));
		}
		lowrow = hirow;	
	}while(lowrow<rowend);
}

void interpolate_collumn_rowwise(TH2F* hin, int col, int rowstart, int rowend){
	//assuming a blank column with filled columns on either side. 
	//interpolate from neighbors in rows. 
	TAxis* x = hin->GetYaxis();
	for(int irow = rowstart; irow <= rowend; irow++){
		hin->SetBinContent(col, irow,
						bilinear_interpolate( x->GetBinCenter(col-1),hin->GetBinContent(col-1,irow), x->GetBinCenter(col+1), hin->GetBinContent(col+1,irow), x->GetBinCenter(col) ));
	}
}

TH2F* HistOr(TH2F* h1, TH2F* h2, float blankval, float tollorence){
	//takes two partly interpolated histograms and takes the Or of them.
	//if they both have a value, give preference to h1
	//if they're not of the same dimension, return h1. 
	if(h1->GetXaxis()->GetNbins() != h2->GetXaxis()->GetNbins()  || 
	h1->GetYaxis()->GetNbins() != h2->GetYaxis()->GetNbins() ) return h1;
	TH2F* hout = (TH2F*) h1->Clone("hout");
	for(int i=0;i<=h1->GetXaxis()->GetNbins();i++){
		for(int j=0;j<=h1->GetYaxis()->GetNbins();j++){
			if( fabs(h1->GetBinContent(i,j) - blankval) < tollorence) hout->SetBinContent(i,j,h2->GetBinContent(i,j));
		}
	}
	return h1;
}

void interpolate_collumn(TH2D* hin, int col, int rowstart, int rowend){
		//assumes that alternating cells in the are occupied.
		//go up the collumn, interpolating the blanks
	TAxis* y = hin->GetYaxis();
	for(int irow = rowstart; irow <= rowend; irow++){
		if(aeq(hin->GetBinContent(col,irow),0)){ //fixed
			hin->SetBinContent(col,irow, //fixed
							   bilinear_interpolate( y->GetBinCenter(irow-1),hin->GetBinContent(col,irow-1), y->GetBinCenter(irow+1), hin->GetBinContent(col,irow+1), y->GetBinCenter(irow) )); //fixed
		}
	}
}
void interpolate_uneven_column(TH2D* hin, int col, int rowstart, int rowend){
	TAxis* y = hin->GetYaxis();
		//first we crawl up the column, looking for the first non-zero entry

		//then we crawl up to find the next non-zero entry.
		//then you fill in all the rows inbetween and
	int lowrow = rowstart;
	int hirow = rowstart+1;
	do{
		if(aeq(hin->GetBinContent(col,lowrow),0)){ //fixed
			lowrow++;
			continue;
		}
			//now on a non-zero entry
		hirow = lowrow+1;
		while(aeq(hin->GetBinContent(col,hirow),0) && hirow <= rowend) hirow++;//fixed
		if(hirow > rowend) break;
			//hirow is now on a no-zero entry.
		for(int irow = lowrow+1; irow<hirow; irow++){
			hin->SetBinContent(col, irow,//fixed
							   bilinear_interpolate( y->GetBinCenter(lowrow),hin->GetBinContent(col,lowrow), y->GetBinCenter(hirow), hin->GetBinContent(col,hirow), y->GetBinCenter(irow) ));
		}
		lowrow = hirow;
	}while(lowrow<rowend);
}

void interpolate_collumn_rowwise(TH2D* hin, int col, int rowstart, int rowend){
		//assuming a blank column with filled columns on either side.
		//interpolate from neighbors in rows.
	TAxis* x = hin->GetYaxis();
	for(int irow = rowstart; irow <= rowend; irow++){
		hin->SetBinContent(col, irow,
						   bilinear_interpolate( x->GetBinCenter(col-1),hin->GetBinContent(col-1,irow), x->GetBinCenter(col+1), hin->GetBinContent(col+1,irow), x->GetBinCenter(col) ));
	}
}

TH2D* HistOr(TH2D* h1, TH2D* h2, float blankval, float tollorence){
		//takes two partly interpolated histograms and takes the Or of them.
		//if they both have a value, give preference to h1
		//if they're not of the same dimension, return h1.
	if(h1->GetXaxis()->GetNbins() != h2->GetXaxis()->GetNbins()  ||
	   h1->GetYaxis()->GetNbins() != h2->GetYaxis()->GetNbins() ) return h1;
	TH2D* hout = (TH2D*) h1->Clone("hout");
	for(int i=0;i<=h1->GetXaxis()->GetNbins();i++){
		for(int j=0;j<=h1->GetYaxis()->GetNbins();j++){
			if( fabs(h1->GetBinContent(i,j) - blankval) < tollorence) hout->SetBinContent(i,j,h2->GetBinContent(i,j));
		}
	}
	return h1;
}


void interpolate_Zywicki(TH2D* shittyhist,bool bigcol){
	interpolate_Zywicki((TH2F* )shittyhist,bigcol);
}
void interpolate_Zywicki(TH2F* shittyhist,bool bigcol){
	//This assumes a histogram with the following binning: 
	//float mSBins[nS+1] = {187.5, 212.5, 237.5 ,262.5 ,287.5, 312.5, 337.5, 362.5,    375, 425, 475, 525}
	//float mHBins[nH+1] = {130, 140, 160, 190, 210,    220, 230, 235,245, 255,     260, 270, 280, 285,295,     305, 310,320, 330};
	//with points filled in according to the spotty-ass grid that PZ sent us. 

	//very spicific interpolation of 
	interpolate_uneven_column(shittyhist,    2, 2, 5);
	interpolate_uneven_column(shittyhist,    3, 1, 8);
	interpolate_uneven_column(shittyhist,    4, 1, 11);
	interpolate_uneven_column(shittyhist,    5, 1, 14);
	interpolate_uneven_column(shittyhist,    6, 1, 17);
	interpolate_uneven_column(shittyhist,    7, 1, 16);
	//skip 8
	interpolate_uneven_column(shittyhist,    9, 1, 19);
	interpolate_uneven_column(shittyhist,         10, 2, 19); //these are regular, so use a simpler algor. 
	interpolate_uneven_column(shittyhist,         11, 2, 19);
	//now do 8
	interpolate_collumn_rowwise(shittyhist, 8, 1, 15);
}
