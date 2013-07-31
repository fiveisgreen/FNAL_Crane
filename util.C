#include "TGraph.h"
#include "TAxis.h"
#include "TH1.h"
#include "TMath.h"
#include <cmath>
#include <TH2.h>
#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include "TString.h"
#include <string.h>

using namespace std;

void fillPotHoles(TH2D *h);
void fixBadCells(TH2D* h);
void RemovePoints(TGraph* g);
void RemoveOffOrderedPoints(TGraph* g);
void PrintPoints(TGraph* g);
void Print2DHist(TH2D* h);
TGraph* getContour0(TH2D* h, TString name);
TGraph* getContour1(TH2D* h, TString name);
TGraph* getContourBarker(TH2D* h, TString name);
TGraph* makeBandGraph(TGraph* g1, TGraph* g2);
TH1D* TH1FtoD(TH1F* f);
TH2D* TH2FtoD(TH2F* f);
int mod(int x, int m);
void printregion(TH2D* h, int i, int j);

void fillPotHoles(TH2D *h) {

		// fill cells which have empty value
		//this is badly behaved!!!


	int nbinsX = h->GetXaxis()->GetNbins();
	int nbinsY = h->GetYaxis()->GetNbins();

	double epsilon = 1e-10;

		//if any cells are NAN, re-value them as zero. 
	for(int ix=1; ix <= nbinsX; ix++) {
		for(int iy=1; iy <= nbinsY; iy++) {
			double val = h->GetBinContent(ix,iy);
			if(TMath::IsNaN(val)) h->SetBinContent(ix,iy,0); // checking for NAN
		}
	}


	for(int ix=1; ix <= nbinsX; ix++) {
		for(int iy=1; iy <= nbinsY; iy++) {
			double val = h->GetBinContent(ix,iy);
			if(fabs(val) > epsilon) continue;
			int ncnt = 0;
			double sum = 0;
			double sumErr = 0;
			double up    = h->GetBinContent(ix,iy+1);
			if(fabs(up) > epsilon && iy < nbinsY){
				sum += up;
				sumErr += h->GetBinError(ix,iy+1)*h->GetBinError(ix,iy+1);
				ncnt++;
			}
			double down  = h->GetBinContent(ix,iy-1);
			if(fabs(down) > epsilon && iy > 1){
				sum += down;
				sumErr += h->GetBinError(ix,iy-1)*h->GetBinError(ix,iy-1);
				ncnt++;
			}
			double left  = h->GetBinContent(ix-1,iy);
			if(fabs(left) > epsilon && ix > 1){
				sum += left;
				sumErr += h->GetBinError(ix-1,iy)*h->GetBinError(ix-1,iy);
				ncnt++;
			}
			double right = h->GetBinContent(ix+1,iy);
			if(fabs(right) > epsilon && ix < nbinsX){
				sum += right;
				sumErr += h->GetBinError(ix+1,iy)*h->GetBinError(ix+1,iy);
				ncnt++;
			}
			if(ncnt > 0) {
				h->SetBinContent(ix,iy,sum/ncnt);
				h->SetBinError(ix,iy,std::sqrt(sumErr)/ncnt);
			}
		} // for iy
	} // for ix

}


void fixBadCells(TH2D* h) {

		// fix bad cells which have wrong sign compared to 4 surrounding cells.
		// then assign average value from 4 cells

	int nbinsX = h->GetXaxis()->GetNbins();
	int nbinsY = h->GetYaxis()->GetNbins();

	double epsilon = 0;

	for(int ix=1; ix <= nbinsX; ix++) {
		for(int iy=1; iy <= nbinsY; iy++) {
			double val = h->GetBinContent(ix,iy);
			if(val < epsilon) {
				int ncnt = 0;
				double up    = h->GetBinContent(ix,iy+1);
				if(up > epsilon) ncnt++;
				double down  = h->GetBinContent(ix,iy-1);
				if(down > epsilon) ncnt++;
				double left  = h->GetBinContent(ix-1,iy);
				if(left > epsilon) ncnt++;
				double right = h->GetBinContent(ix+1,iy);
				if(right > epsilon) ncnt++;
				if(ncnt == 4){
					val = (up+down+left+right)/ncnt;
					h->SetBinContent(ix,iy,val);
					up    = h->GetBinError(ix,iy+1);
					down  = h->GetBinError(ix,iy-1);
					left  = h->GetBinError(ix-1,iy);
					right = h->GetBinError(ix+1,iy);
					val = std::sqrt(up*up + down*down + left*left + right*right)/ncnt;
					h->SetBinError(ix,iy,val);
				}
			}
			else {
				int ncnt = 0;
				double up    = h->GetBinContent(ix,iy+1);
				if(up < epsilon) ncnt++;
				double down  = h->GetBinContent(ix,iy-1);
				if(down < epsilon) ncnt++;
				double left  = h->GetBinContent(ix-1,iy);
				if(left < epsilon) ncnt++;
				double right = h->GetBinContent(ix+1,iy);
				if(right < epsilon) ncnt++;
				if(ncnt == 4){
					val = (up+down+left+right)/ncnt;
					h->SetBinContent(ix,iy,val);
					up    = h->GetBinError(ix,iy+1);
					down  = h->GetBinError(ix,iy-1);
					left  = h->GetBinError(ix-1,iy);
					right = h->GetBinError(ix+1,iy);
					val = std::sqrt(up*up + down*down + left*left + right*right)/ncnt;
					h->SetBinError(ix,iy,val);
				}
			}
		} // for iy
	} // for ix
}


void RemovePoints(TGraph* g) {
	int N = g->GetN();
	int last = -1;
	for(int i=0; i<N; i++) {
		double x,y;
		g->GetPoint(i,x,y);
			//    if(abs(x-y) < 0.1) last = i;
		if(x > 900) {
			last = i+1;
			break;
		}
	}
	for(int i=N-1; i>=last; i--) g->RemovePoint(i);
}


void RemoveOffOrderedPoints(TGraph* g) {
	int i=g->GetN();
	while(i >= 1){
		double x,y;
		double xpre, ypre;
		g->GetPoint(i,x,y);
		g->GetPoint(i-1,xpre,ypre);
		if(x < xpre) g->RemovePoint(i);
		i--;
	}

}


void PrintPoints(TGraph* g) {
	int N = g->GetN();
	for(int i=0; i<N; i++) {
		double x,y;
		g->GetPoint(i,x,y);
		std::cout << "x, y = " << x << ", " << y << std::endl;
	}
}


void Print2DHist(TH2D* h) {

	int nbinsX = h->GetXaxis()->GetNbins();
	int nbinsY = h->GetYaxis()->GetNbins();

//	double epsilon = 1e-20;

	for(int ix=1; ix <= nbinsX; ix++) {
		for(int iy=1; iy <= nbinsY; iy++) {
			double val = h->GetBinContent(ix,iy);
			std::cout << "(" << ix << "," << iy << ") = " << val << std::endl;
		}
	}

}


TGraph* getContour0(TH2D* h, TString name) {
		//This looks through h and makes an exclusion contour based on where the bins cross zero.
		//in the upper-right triangular halfspace it tries to find a zero-crossing for every row
		//(origin corner should have bin content > 0)
		//in the lower-left triangular halfspace it tries to find a zero-crossing for every collumn, starting with the
		//last collumn where a crossing was found in the ur halfspace.
		//It stores and returns the results as a TGraph with root-name name.
		//At most 100 zero crossings are allowed. Less is fine. 

	TGraph* graph = new TGraph(100); //graph of 100 points; better have less than 100 rows in the graph. 
	graph->SetName(name);
	int ip = 0;
	int nx = h->GetXaxis()->GetNbins();
	int ny = h->GetYaxis()->GetNbins();

		//for the upper-left triangular halfspace, search each row look for where the collumn corsses over. 
		// for y>x
	int ix = -1;
	for(int j=ny;true; j--) {  //Start at the far end of j
		int k = -1;//error value, occurs if no bins on the jth row have cells < 0
		for(int i=2; i<nx-1; i++) { //not allowed to set the limit in the first collumn.
			if(h->GetBinContent(i,j) < 0) {
				std::cout << "i,j,z : " << i << ", " << j << ", " << h->GetBinContent(i,j) << std::endl;
				k = i;
				break;
			}
		}// for i
			//By here, we've identified which collumn for row j has a negative bin and stored that in k
		if(k<0) continue; //if no cells in this row have negative entries, continue
		double y = h->GetYaxis()->GetBinCenter(j);
		double x1 = h->GetXaxis()->GetBinCenter(k-1);
		double x2 = h->GetXaxis()->GetBinCenter(k);
		double z1 = h->GetBinContent(k-1,j);
		double z2 = h->GetBinContent(k,j);
		double x = x1 + (x2-x1)*fabs(z1)/fabs(z2-z1); //linearly calculate a point between the two bins where the lim should be.
			//we see the bin value cross zero, so the limit is somewhere between the two bin centers. Have a guess at where it is = x.
		std::cout << "y, x1, x2, z1, z2, x : " << y << ", " << x1 << ", " << x2 << ", " << x << ", " << z1 << ", " << z2 << std::endl;
		graph->SetPoint(ip++,x,y); //Add this point to the graph.

			//restrict results to the upper-left triangular halfspace
		if(h->GetYaxis()->GetBinCenter(j) < h->GetXaxis()->GetBinCenter(k)) { //if found the point in the lower-right triangular halfspace, break
			ix = k; //ix becomes the bin number of the last point found, particularly the one that went over the triangular line.
			break; //we're not rejecting the point, just not looking for any more.
		}
	}// for j

	if(ix < 0) std::cout << "Something wrong...." << std::endl;

			//for the upper-left triangular halfspace, search each collumn look for where the row corsses over;
		    //starting on the row where the last corss over point was found.
		//do the same thing as the last loop but with x and y transposed. 
		// for y<x
	for(int i=ix; i<=nx; i++) {
		int k = -1;
		for(int j=2; j<ny-1; j++) {
			if(h->GetBinContent(i,j) < 0) {
				k = j;
				break;
			}
		}// for j
		if(k<0) continue;
		double x = h->GetXaxis()->GetBinCenter(i);
		double y1 = h->GetYaxis()->GetBinCenter(k-1);
		double y2 = h->GetYaxis()->GetBinCenter(k);
		double z1 = h->GetBinContent(i,k-1);
		double z2 = h->GetBinContent(i,k);
		double y = y1 + (y2-y1)*fabs(z1)/fabs(z2-z1);
		std::cout << "x, y1, y2, z1, z2, y : " << x << ", " << y1 << ", " << y2 << ", " << y << ", " << z1 << ", " << z2 << std::endl;
		graph->SetPoint(ip++,x,y);
	}// for i

		//remove the last point with x<=1 GeV (or whatever the unitis of the hist are in). 
	ip = graph->GetN()-1;
	while(1) {
		double x, y;
		graph->GetPoint(ip,x,y);
		if(x>1) break;
		else graph->RemovePoint(ip);
		ip--;
	}

	return graph;
}//end getContour0

TGraph* getContour1(TH2D* h, TString name) {
		//This looks through h and makes an exclusion contour based on where the bins cross zero.
		//in the upper-right triangular halfspace it tries to find a 1-crossing for every row
		//(origin corner should have bin content > 1)
		//in the lower-left triangular halfspace it tries to find a 1-crossing for every collumn, starting with the
		//last collumn where a crossing was found in the ur halfspace.
		//It stores and returns the results as a TGraph with root-name name.
		//At most 100 zero crossings are allowed. Less is fine.


/*This is crazy. What I'd like this damn thing to do is to start at j=1, 
 find the point. stick a point there. Skip holes. 
 next row. find it... 
*/
	std::cout<<"enter getContour"<<endl;
	TGraph* graph = new TGraph(100); //graph of 100 points; better have less than 100 rows in the graph.
	graph->SetName(name);
	int ip = 0;
	int nx = h->GetXaxis()->GetNbins();
	int ny = h->GetYaxis()->GetNbins();

		//for the upper-left triangular halfspace, search each row look for where the collumn corsses over.
		// for y>x
	std::cout<<"Try Loop 1"<<endl;
	int ix = 1;
/*	for(int j=ny;j>=0; j--) {  //Start at the far end of j
		int k = -1;//error value, occurs if no bins on the jth row have cells < 0
		for(int i=2; i<nx-1; i++) { //not allowed to set the limit in the first collumn.
			if(h->GetBinContent(i,j) > 1 && h->GetBinContent(i,j) > 0.000001) {
				std::cout << "i,j,z : " << i << ", " << j << ", " << h->GetBinContent(i,j) << std::endl;
				k = i;
				break;
			}
		}// for i
			//By here, we've identified which collumn for row j has a negative bin and stored that in k
		if(k<0) continue; //if no cells in this row have negative entries, continue
		double y = h->GetYaxis()->GetBinCenter(j);
		double x1 = h->GetXaxis()->GetBinCenter(k-1);
		double x2 = h->GetXaxis()->GetBinCenter(k);
		double z1 = h->GetBinContent(k-1,j);
		double z2 = h->GetBinContent(k,j);
		double x = x1 + (x2-x1)*fabs(z2)/fabs(z2+z1); //linearly calculate a point between the two bins where the lim should be.
			//we see the bin value cross zero, so the limit is somewhere between the two bin centers. Have a guess at where it is = x.
		std::cout << "y, x1, x2, z1, z2, x : " << y << ", " << x1 << ", " << x2 << ", " << x << ", " << z1 << ", " << z2 << std::endl;
		graph->SetPoint(ip++,x,y); //Add this point to the graph.

			//restrict results to the upper-left triangular halfspace
		if(h->GetYaxis()->GetBinCenter(j) < h->GetXaxis()->GetBinCenter(k)) { //if found the point in the lower-right triangular halfspace, break
			ix = k; //ix becomes the bin number of the last point found, particularly the one that went over the triangular line.
			break; //we're not rejecting the point, just not looking for any more.
		}
	}// for j
	std::cout<<"Done loop1, try loop2"<<endl;
 */
	std::cout<<"try loop2"<<endl;

//	if(ix < 0) std::cout << "Something wrong...." << std::endl;

		//for the upper-left triangular halfspace, search each collumn look for where the row corsses over;
		//starting on the row where the last corss over point was found.
		//do the same thing as the last loop but with x and y transposed.
		// for y<x
	for(int i=ix; i<=nx; i++) {
		int k = -1;
		for(int j=2; j<ny-1; j++) {
			if(h->GetBinContent(i,j) > 1 && h->GetBinContent(i,j) > 0.000001) {
				k = j;
				break;
			}
		}// for j
		if(k<0) continue;
		double x = h->GetXaxis()->GetBinCenter(i);
		double y1 = h->GetYaxis()->GetBinCenter(k-1);
		double y2 = h->GetYaxis()->GetBinCenter(k);
		double z1 = h->GetBinContent(i,k-1);
		double z2 = h->GetBinContent(i,k);
		double y = y1 + (y2-y1)*fabs(z2)/fabs(z2+z1);
		std::cout << "x, y1, y2, z1, z2, y : " << x << ", " << y1 << ", " << y2 << ", " << y << ", " << z1 << ", " << z2 << std::endl;
		graph->SetPoint(ip++,x,y);
	}// for i
	std::cout<<"Done Loop 2"<<endl;


		//remove the last point with x<=1 GeV (or whatever the unitis of the hist are in).
	ip = graph->GetN()-1;
	int n = ip;
	while(n>=0) {
		double x, y;
		graph->GetPoint(ip,x,y);
		if(x>1) break;
		else graph->RemovePoint(ip);
		ip--;
		n--;
	}
	return graph;
}//end getContour1

TGraph* getContourBarker(TH2D* h, TString name) {
		//move along diagonals, starting in the upper left corner, mark transitions from <1 to >1 clockwise

	bool debug = false;
	if(debug) printf("enter getContour\n");

	TGraph* graph = new TGraph(100); //graph of 100 points; better have less than 100 rows in the graph.
	graph->SetName(name);

	int ip = 0;//ith point in the TGraph to fill.

		//number of x and y bins
	int nx = h->GetXaxis()->GetNbins();
	int ny = h->GetYaxis()->GetNbins();
	if(debug) printf( "nx %i ny %i\n",nx,ny);

		//starting point of the (first) diagonal
	int ist = 1;
	int jst = ny-1;

	double Xlast = 1; //x-value (not bin) of the last point we find. preset to 1

	while (ist<=nx) { //for every diagonal, strictly speaking, while not the last diagonal. 

		if(debug) printf( "ist %i jst %i\n",ist,jst);

		int i = ist;//x,y bin of cell to be examined.
		int j = jst;
		while (i<=nx && j<=ny) { //while not at end of diagonal
			float thisbin = h->GetBinContent(i,j);
			if(thisbin < 0.00001){
				if(debug) printf( "i %i j %i nothing to see here\n",i,j);
				i++; j++;
				continue;
			}//if the bin is empty, go on up the diagonal
			if(thisbin > 1){ //if it's over, go to the next diagonal.
				if(debug) printf("went over, go to next diag\n");
				break;
			}
			if(debug){
				printf("see valid bin i %i j %i\n",i,j);
				printf("%.1f\t%.1f\t%.1f\n",h->GetBinContent(i-1,j+1),h->GetBinContent(i,j+1),h->GetBinContent(i+1,j+1));
				printf("%.1f\t%.1f\t%.1f    %.1f  %.1f\n",h->GetBinContent(i-1,j),h->GetBinContent(i,j),h->GetBinContent(i+1,j),  h->GetXaxis()->GetBinCenter(i),h->GetYaxis()->GetBinCenter(j));
				printf("%.1f\t%.1f\t%.1f\n",h->GetBinContent(i-1,j-1),h->GetBinContent(i,j-1),h->GetBinContent(i+1,j-1));
			}
				//if there's a transisition to the left, mark it;
			if(h->GetBinContent(i-1,j)>1){
				/*
				 i+1,x1   i,x2
				 ____________
				 | z1* |  z2  | j, y
				 |_____|______|
				 
				 z1* > z2
				 */
				if(debug) printf("I see transition left\n");
				double y = h->GetYaxis()->GetBinCenter(j);
				double x1 = h->GetXaxis()->GetBinCenter(i-1);
				double x2 = h->GetXaxis()->GetBinCenter(i);
				double z1 = h->GetBinContent(i-1,j);
				double z2 = h->GetBinContent(i,j);
				double x = x1 + (x2-x1)*z2/(z2+z1); //linearly calculate a point between the two bins where the lim should be.
					//we see the bin value cross zero, so the limit is somewhere between the two bin centers. Have a guess at where it is = x.
				if(debug) printf("x %.2f, y %.2f z1-z2: %.2f-%.2f\n",x,y,z1,z2);
				graph->SetPoint(ip++,x,y); //Add this point to the graph.
				Xlast = x; //save x in case this is the last point
			}
				//if there's a transisition to the above, mark it;
			if(h->GetBinContent(i,j+1)>1){// there's a transition above
				/*
				   i,x
				  _____
				 | z1* | j+1, y1
				 |_____|
				 | z2  | j, y2
				 |_____|

				 z1* > z2
				 */
				if(debug) printf("I see transition above\n");
				double x = h->GetXaxis()->GetBinCenter(i);
				double y1 = h->GetYaxis()->GetBinCenter(j+1);
				double y2 = h->GetYaxis()->GetBinCenter(j);
				double z1 = h->GetBinContent(i,j+1);
				double z2 = h->GetBinContent(i,j);
				double y = y2 + (y1-y2)*z1/(z2+z1);
				if(debug) printf("x %.2f, y %.2f z1-z2: %.2f-%.2f\n",x,y,z1,z2);
				graph->SetPoint(ip++,x,y);
				Xlast = x;//save x in case this is the last point
			}
			if(h->GetBinContent(i+1,j)>1){ //there's a transition to the right
				{ //this is necessary
					/*
					  i,x2   i+1,x1
					  ____________
					 | z2  |  z1* | j, y
					 |_____|______|

					 z1* > z2
					 */
					if(debug) printf("I see transition right\n");
					double y = h->GetYaxis()->GetBinCenter(j);
					double x1 = h->GetXaxis()->GetBinCenter(i+1);
					double x2 = h->GetXaxis()->GetBinCenter(i);
					double z1 = h->GetBinContent(i+1,j);
					double z2 = h->GetBinContent(i,j);
					double x = x2 + (x1-x2)*z1/(z2+z1); //linearly calculate a point between the two bins where the lim should be.
						//we see the bin value cross zero, so the limit is somewhere between the two bin centers. Have a guess at where it is = x.
					if(debug) printf("x %.2f, y %.2f z1-z2: %.2f-%.2f\n",x,y,z1,z2);
					graph->SetPoint(ip++,x,y); //Add this point to the graph.
					Xlast = x; //save x in case this is the last point
				}
					//if there's also a transition below
				if(h->GetBinContent(i,j-1)>1){
					/*
					   i,x
					  _____
					 | z2  | j, y2
					 |_____|
					 | z1* | j-1, y1
					 |_____|

					 z1* > z2
					 */
					if(debug) printf("I see transition below\n");
					double x = h->GetXaxis()->GetBinCenter(i);
					double y1 = h->GetYaxis()->GetBinCenter(j-1);
					double y2 = h->GetYaxis()->GetBinCenter(j);
					double z1 = h->GetBinContent(i,j-1);
					double z2 = h->GetBinContent(i,j);
					double y = y1 + (y2-y1)*z2/(z2+z1);
					if(debug) printf("x %.2f, y %.2f z1-z2: %.2f-%.2f\n",x,y,z1,z2);
					graph->SetPoint(ip++,x,y);//Add this point to the graph.
					Xlast = x; //save x in case this is the last point
				}
			}//end there's a transition to the right

			i++; j++; //increment up diagonal
		}//end for every cell on diagonal

			//increment the diagonal
			//if starting point is on y-axis, decrement jst[art], if starting point is on the x-axis, increment xst[art]
		if(jst>1) jst--; //j stops at 1
		else ist++;
	}//end for every diagonal,

	graph->SetPoint(ip++,Xlast,-1); //put on a termination point directly below the last point found. This makes it prettier. 

	return graph;
}//end getContourBarker




	///////////////Prep for getContourBarker_fancy //////////////////
int mod(int x, int m){
	return x>=0?x%m:mod(x+m,m);
}

class cell{
public:
	int i;
	int j;
	cell(int _i, int _j):i(_i),j(_j){}
	cell(){}
	cell(cell& c):i(c.i),j(c.j){}
	~cell(){}
	cell& operator=(cell& c);
	bool operator==(cell& c);

	bool is_over(TH2D* h);
	bool is_under(TH2D* h);
	bool is_blank(TH2D* h);
	bool is_stair(TH2D* h);
	bool is_bottom(TH2D* h);
	bool is_rightEdge(TH2D* h);
	cell* shift(int octdir);
};
bool cell::is_over(TH2D* h){return h->GetBinContent(i,j)>1;}
bool cell::is_under(TH2D* h){return h->GetBinContent(i,j)<=1;}
bool cell::is_blank(TH2D* h){return h->GetBinContent(i,j) < 0.00001;}
bool cell::is_stair(TH2D* h){
		//if this and every other cell above it are zero, it's a staircase cell.
	for (int jj = j+1; jj<=h->GetYaxis()->GetNbins(); jj++) {
		if( h->GetBinContent(i,jj) > 0.00001 )return false;
	}
	return true;
}
bool cell::is_bottom(TH2D* h){
		//if this and every other cell above it are zero, it's a staircase cell.
	for (int jj = j-1; jj>0; jj--) {
		if( h->GetBinContent(i,jj) > 0.00001 )return false;
	}
	return true;
}
bool cell::is_rightEdge(TH2D* h){
		//if this and every other cell above it are zero, it's a staircase cell.
	for (int ii = i+1; ii<=h->GetXaxis()->GetNbins(); ii++) {
		if( h->GetBinContent(ii,j) > 0.00001 )return false;
	}
	return true;
}
cell& cell::operator=(cell& c){
	i = c.i;
	j = c.j;
	return *this;
}
bool cell::operator==(cell& c){
	return i == c.i && j ==c.j;
}
cell* cell::shift(int octdir){
/*
 7 0 1
 6 * 2
 5 4 3
 */
	switch(octdir){
		case 0: //up
			return new cell(i,j+1);
			break;
		case 1:
			return new cell(i+1,j+1);
			break;
		case 2: //right
			return new cell(i+1,j);
			break;
		case 3:
			return new cell(i+1,j-1);
			break;
		case 4://down
			return new cell(i,j-1);
			break;
		case 5:
			return new cell(i-1,j-1);
			break;
		case 6: //left
			return new cell(i-1,j);
			break;
		case 7:
			return new cell(i-1,j+1);
			break;
		default:
			return this;
	}
}//end shift

class overcell: public cell{
public:
//      overcells are cells with r > 1
//	overcell & operator=(overcell & cel);
	overcell(int _i, int _j):cell(_i,_j){}
	overcell():cell(){}
	overcell(cell c):cell(c){}
	~overcell(){}
	bool has_transition(TH2D* h, int dir);
};//end overcell
bool overcell::has_transition(TH2D* h, int dir){
		//this must be an over cell, look for cells around it that are under
		//dir is 0..3, 0 is up, 1 is right; clockwise. 
	if (!is_over(h)) return false;
    int Iunder, Junder; //the i,j of the adjacent cell in that direction
	switch (dir) {
		case 0: //up
			Iunder = i;
			Junder = j+1;
			break;
		case 1: //right
			Iunder = i+1;
			Junder = j;
			break;
		case 2: //down
			Iunder = i;
			Junder = j-1;
			break;
		case 3: //left
			Iunder = i-1;
			Junder = j;
			break;
		default:
			return false;
	}//end switch
		//Don't transition to blanks on the bottom
	if(Junder <= 3 && Iunder > Junder && h->GetBinContent(Iunder,Junder) < 0.00001) return false; 
		//the edges of the screen are not allowed transitions.
	if (Junder<=0 || Junder > h->GetYaxis()->GetNbins() || Iunder<=0 || Iunder > h->GetXaxis()->GetNbins() ) return false;
	return h->GetBinContent(Iunder,Junder) <= 1.0;
//	return h->GetBinContent(Iunder,Junder) <= 1.0 &&
//	!(Junder<=0 || Junder > h->GetYaxis()->GetNbins() || Iunder<=0 || Iunder > h->GetXaxis()->GetNbins() );

//	int Iunder = i + dir%2*((-1)**(dir>>1)); //this implements the same thing as the above switch statement.
//	int Junder = j + (dir+1)%2*((-1)**((dir+1)>>1));
//	return h->GetBinContent(i,j)>1.0 &&  h->GetBinContent(Iunder,Junder) <= 1.0 &&
//	!(Junder<=0 || Junder > h->GetYaxis->GetNbins() || Iunder<=0 || Iunder > h->GetXaxis->GetNbins() );
}//end if has transition.

class transitionpoint{
public:
	double x;
	double y;
	overcell cel;
	int dir;//0-3;
		//0 = up, 1 = right, 2 = down, 3 = left
	/* 	  0
	     3*1
	      2    	  */
	transitionpoint(){}
	transitionpoint(overcell& c, int _dir): cel(c),dir(_dir){}
	transitionpoint(overcell& c, int _dir, TH2D* h): cel(c),dir(_dir){	makeXY(h);}
	~transitionpoint(){}
	void makeXY(TH2D* h);
	bool operator==(transitionpoint& t);
	transitionpoint* Adjacent();
	transitionpoint* Corner();
};
void transitionpoint::makeXY(TH2D* h){
		//assumes you're on an over cell
		//fills x and y with sensible values somewhere between cell centers.
/*
 I don't like these formulas. What we should really do is take the two points, project a line through them and find where it crosses 1. 
 Then we get 
 X = ((x1-x2)*1 - (x1*z2 - x2*z1))/(z1 - z2)
      (fails if z1 == z2)
 then check that X is between x1 and x2
 but then that will have some hardship with the bin asymetry.
 
 */

	double gamma = 1.0;

	switch (dir) {
		case 0: //transition above
			/*
			 i,x
			 ______
			 | z1  | j+1, y1
			 |_____|
			 | z2* | j, y2
			 |_____|

			 z1 < z2*
			 */
			x = h->GetXaxis()->GetBinCenter(cel.i);
			if (h->GetBinContent(cel.i,cel.j+1)<0.00001) y =h->GetYaxis()->GetBinUpEdge(cel.j);
			else{
				double y1 = h->GetYaxis()->GetBinCenter(cel.j+1);
				double y2 = h->GetYaxis()->GetBinCenter(cel.j);
				double z1 = h->GetBinContent(cel.i,cel.j+1);
				double z2 = h->GetBinContent(cel.i,cel.j);
//				y = y2 + (y1-y2)*z2/(z2+z1);
				if (fabs(z1 - z2)< 0.001){
					y = h->GetYaxis()->GetBinUpEdge(cel.j);
					printf("WARNING: makeXY is trying to make a transition with equal bins\n");
				}
				else y = ((y1-y2)*gamma - (y1*z2 - y2*z1))/(z1-z2); //main method. find where it crosss 1
				if (y>y1 || y<y2){
					printf("WARNING: linear method gives nonsense, going with interpolation method. Y1 %f Y2 %f Y %f\n",y1,y2,y);
					y = y2 + (y1-y2)*z2/(z2+z1);
				}

//				if(z1 == z2) y =
//				else y =
			}
			break;
		case 1: //transition right
			/*
			 i,x2   i+1,x1
			 ____________
			 | z2* |  z1  | j, y
			 |_____|______|

			 z1 < z2*
			 */
			y = h->GetYaxis()->GetBinCenter(cel.j);
			if (h->GetBinContent(cel.i+1,cel.j)<0.00001) x =h->GetXaxis()->GetBinUpEdge(cel.i);
			else{
				double x1 = h->GetXaxis()->GetBinCenter(cel.i+1);
				double x2 = h->GetXaxis()->GetBinCenter(cel.i);
				double z1 = h->GetBinContent(cel.i+1,cel.j);
				double z2 = h->GetBinContent(cel.i,cel.j);
//				x = x2 + (x1-x2)*z2/(z2+z1); //linearly calculate a point between the two bins where the lim should be.
				if (fabs(z1 - z2)< 0.001){
					x = h->GetXaxis()->GetBinUpEdge(cel.i);
					printf("WARNING: makeXY is trying to make a transition with equal bins\n");
				}
				else x = ((x1-x2)*gamma - (x1*z2 - x2*z1))/(z1-z2); //main method. find where it crosss 1
				if (x<x2 || x>x1){
					printf("WARNING: linear method gives nonsense, going with interpolation method. X2 %f X1 %f X %f\n",x2,x1,x);
					x = x2 + (x1-x2)*z2/(z2+z1);
				}

			}
			break;
		case 2: //transition below
			/*
			 i,x
			 _____
			 | z2* | j, y2
			 |_____|
			 | z1  | j-1, y1
			 |_____|

			 z1 < z2*
			 */
			x = h->GetXaxis()->GetBinCenter(cel.i);
			if (h->GetBinContent(cel.i,cel.j-1)<0.00001) y =h->GetYaxis()->GetBinLowEdge(cel.j);
			else{
				double y1 = h->GetYaxis()->GetBinCenter(cel.j-1);
				double y2 = h->GetYaxis()->GetBinCenter(cel.j);
				double z1 = h->GetBinContent(cel.i,cel.j-1);
				double z2 = h->GetBinContent(cel.i,cel.j);
//				y = y1 + (y2-y1)*z1/(z2+z1);
				if (fabs(z1 - z2)< 0.001){
					y = h->GetYaxis()->GetBinLowEdge(cel.j);
					printf("WARNING: makeXY is trying to make a transition with equal bins\n");
				}
				else y = ((y1-y2)*gamma - (y1*z2 - y2*z1))/(z1-z2); //main method. find where it crosss 1
				if (y<y1 || y>y2){
					printf("WARNING: linear method gives nonsense, going with interpolation method. Y1 %f Y2 %f Y %f\n",y1,y2,y);
					y = y1 + (y2-y1)*z1/(z2+z1);
				}
			}
			break;
		case 3: //transition left
			/*
			 i+1,x1   i,x2
			 ____________
			 | z1  |  z2* | j, y
			 |_____|______|

			 z1 < z2*
			 */
			y = h->GetYaxis()->GetBinCenter(cel.j);
			if (h->GetBinContent(cel.i-1,cel.j)<0.00001) x =h->GetXaxis()->GetBinLowEdge(cel.i);
			else{
				double x1 = h->GetXaxis()->GetBinCenter(cel.i-1);
				double x2 = h->GetXaxis()->GetBinCenter(cel.i);
				double z1 = h->GetBinContent(cel.i-1,cel.j);
				double z2 = h->GetBinContent(cel.i,cel.j);
//				x = x1 + (x2-x1)*z1/(z2+z1);//linearly calculate a point between the two bins where the lim should be.

				if (fabs(z1 - z2)< 0.001){
					x = h->GetXaxis()->GetBinLowEdge(cel.i);
					printf("WARNING: makeXY is trying to make a transition with equal bins\n");
				}
				else x = ((x1-x2)*gamma - (x1*z2 - x2*z1))/(z1-z2); //main method. find where it crosss 1
				if (x<x1 || x>x2){
					printf("WARNING: linear method gives nonsense, going with interpolation method. X1 %f X2 %f X %f\n",x1,x2,x);
					x = x1 + (x2-x1)*z1/(z2+z1);
				}
			}
			break;
		default:
			x=-1;
			y=-1;
			break;
	}//end switch

} //end makeXY
bool transitionpoint::operator==(transitionpoint& t){
	return dir == t.dir && cel == t.cel;
}
transitionpoint* transitionpoint::Adjacent(){
		//return a transition point with the same direction as this one, but for the cell on the left (ccw)
		//recall that shift uses 0-7 dirirection and transition uses a 0-4 direction
	return new transitionpoint( (overcell&) *cel.shift( 2*mod((dir-1),4)), dir);
}
transitionpoint * transitionpoint::Corner(){
		//returns a transition point on the diagonal, one 8-spot ccw from where it's poitning, and with a new 4-dir one spot cw
	return new transitionpoint( (overcell&) *cel.shift( mod(dir*2 -1,8) ), mod(dir+1,4) );
}


void printregion(TH2D* h, int i, int j){
	printf("%.1f\t%.1f\t%.1f\n",h->GetBinContent(i-1,j+1),h->GetBinContent(i,j+1),h->GetBinContent(i+1,j+1));
	printf("%.1f\t%.1f\t%.1f    %.1f  %.1f\n",h->GetBinContent(i-1,j),h->GetBinContent(i,j),h->GetBinContent(i+1,j),  h->GetXaxis()->GetBinCenter(i),h->GetYaxis()->GetBinCenter(j));
	printf("%.1f\t%.1f\t%.1f\n",h->GetBinContent(i-1,j-1),h->GetBinContent(i,j-1),h->GetBinContent(i+1,j-1));
}

TGraph* getContourBarker_fancy(TH2D* h, TString name) {
		//move along diagonals, starting in the upper left corner, mark transitions from <1 to >1 clockwise

	bool debug = false;
	if(debug) printf("enter getContour\n");

		//number of x and y bins
	int nx = h->GetXaxis()->GetNbins();
	int ny = h->GetYaxis()->GetNbins();

//	double Xlast = 1; //x-value (not bin) of the last point we find. preset to 1
		//Get the seed.
		//finding the seed
		//go row by row from the top,
		//idetify first row that doesn't start with a red cell
		//then go inwards, the first blue cell with a up or right transition is your blue cell. This is the blue seed.
		//the first {up,left} red cell is the red seed and it's transition is the seed transition.
	overcell overseed;
	overseed.i = 0;
	overseed.j = 0;
	transitionpoint seedtransition;
	bool goon = true;
	for (int j = ny; goon && j>0; j--) {
		for (int i = 1; i<= nx; i++) {
			cell *thiscell = new cell(i,j);
//			if(debug) printf("i %i j %i\n",thiscell->i,thiscell->j);
			if (thiscell->is_blank(h) ){
//				printf("hit continue\n");
				continue;
			}
			else if (thiscell->is_over(h)) break;
			else if (thiscell->is_under(h)){
//				printf("I see under\n");
				if( thiscell->shift(0)->is_over(h)){//found underseed and overseed is above
//					underseed = thiscell;
					if(debug)printf("got a seed 1\n");
					overseed = (overcell&) * (thiscell->shift(0));
					seedtransition.cel = overseed;
					seedtransition.dir = 2;
					goon = false;
					break;
				}
				else if(thiscell->shift(2)->is_over(h)){//found underseed and overseed is on right
//					underseed = thiscell;
					if(debug) printf("got a seed 2\n");
					overseed = (overcell&) *(thiscell->shift(2));
					seedtransition.cel = overseed;
					seedtransition.dir = 3;
					goon = false;
					break;
				}//end if found underseed
					//otherwise, we didn't find the seed, but it's got to be in this row; probably the next itteration.
			}// end if found an undercell
		}//end for i
	}// end for j

	if(true) printf("I ought to have the seed now. i %i j %i, x %.1f, y%.1f\n",overseed.i,overseed.j, seedtransition.x, seedtransition.y);
	//if(debug) printf("I ought to have the seed now. i %i j %i, x %.1f, y%.1f\n",overseed.i,overseed.j, seedtransition.x, seedtransition.y);

		//save the seed transition to a list of transitions
	std::vector<transitionpoint*> foundpoints;
	seedtransition.makeXY(h);
	transitionpoint* thispoint = &seedtransition;
	foundpoints.push_back(thispoint);
	bool is_seed = true;
		//loop to find new transition points.
	bool lastpoint = false;
	int maxpoints = 100;//infinite loop protection.
	do{ //for every overcell on the boundary
		thispoint->makeXY(h);
		if(debug) printf("On Point: i %i, j %i, dir %i x %.1f y %.1f\t\t\t%i %i\n",thispoint->cel.i,thispoint->cel.j,thispoint->dir,
			   thispoint->x,thispoint->y,thispoint->cel.i,thispoint->cel.j);
		if(debug) printregion(h, thispoint->cel.i, thispoint->cel.j);
		
			//now I look around the rest of the red cell, going ccw, asking if I have transitions there that are not
			//on the list of found transitions.
			//If I find a new one, I move to it, add it to the list of found transitions.
		int basedir = thispoint->dir;//needed to keep basedir(ection) const under each rotation iteration.
		for(int rot = 0; rot<4; rot++){ //ccw rotations
			if(is_seed && (mod(basedir-rot,4) == 0  || mod(basedir-rot,4) == 3 )){
				//printf("this is the seed, so we reject rot %i\n",rot);
				continue;
			}

			bool transition_decision =thispoint->cel.has_transition(h,mod(basedir-rot,4)  );
//			if(thispoint->cel.has_transition(h,mod(basedir-rot,4)  )){
			if(debug) printf("dir %i rot %i decision %i\n",mod(basedir-rot,4),rot, transition_decision);
			if(transition_decision){
				transitionpoint*  newpoint = new transitionpoint(thispoint->cel,mod(basedir-rot,4 ) );
				if(debug) printf("         Keep it\n");
				newpoint->makeXY(h);
					///check that newpoint isn't already on the list
//				bool already_used = false;
//				for (std::vector<transitionpoint*>::iterator it = foundpoints.begin() ; it != foundpoints.end(); ++it){
//					if (newpoint == *it )already_used = true;
//				}
//				if (already_used) continue;
					//I'm not sure if the above is nonsense. 
				foundpoints.push_back(newpoint);
				thispoint = newpoint;
			}
			else break;	//if I do not find on, I discontinue circulating the red cell and start looking for a new overcell.
		}//end for
		is_seed = false;
//		if(debug) printf("done with rotations, go to next point\n");

		transitionpoint* adjacent = thispoint->Adjacent();
		transitionpoint* corner = thispoint->Corner();

		if (adjacent->cel.has_transition(h,adjacent->dir) )	thispoint = adjacent;
		else if(corner->cel.has_transition(h,corner->dir)) 	thispoint = corner;
		else lastpoint = true;
			//start looking for a new overcell.
			//I turn ccw from the last found transition and interogate that cell, ask it if it has a transition in the same dir.
			//if it does, move to that cell and transition
			//if not, ask the cell clock-wise diagonal from it and ask the transition in the cw direction.
			//if that works, move to that cell.
			//if niether of those work, terminate.
	}while(!lastpoint && --maxpoints  > 0 );
	if(debug) printf("out of the do loop\n");

			//make the found points into a graph.
	TGraph* graph = new TGraph(100); //graph of 100 points; better have less than 100 rows in the graph.
	graph->SetName(name);
	int ip = 0;//ith point in the TGraph to fill.
	for (std::vector<transitionpoint*>::iterator it = foundpoints.begin() ; it != foundpoints.end(); ++it){
		(*it)->makeXY(h);
		graph->SetPoint(ip++,(*it)->x,(*it)->y);
	}
//	printf("done filling the graph points\n");
		//fix up the last point
//	transitionpoint* last =*foundpoints.end();
//	std::vector<transitionpoint*>::iterator it = foundpoints.end();
//	printf("i, of list: %i\n",(int) foundpoints.size());
//	transitionpoint* last = *it;
	if(debug) printf("tack on last point\n");
	if(foundpoints.size() > 0){
		transitionpoint* last = foundpoints.back();
			//	printf("j, last j=%i\n",last->cel.j); //ok, it's segfaulting when it reaches for this.
		//if( last->cel.j > 1 ) graph->SetPoint(ip++,h->GetXaxis()->GetBinUpEdge(nx),last->y); //put on a termination point directly below the last point found. This makes it prettier.
		//else graph->SetPoint(ip++,last->x,-1);
		if( last->cel.is_bottom(h) ) graph->SetPoint(ip++,last->x,-1); //if on the bottom, set the point below the bottom
		else if( last->cel.is_rightEdge(h) ) graph->SetPoint(ip++,h->GetXaxis()->GetBinUpEdge(nx),last->y); //put on a termination point directly below the last point found. This makes it prettier.
	}
	if(debug) printf("End tack\n");
//	printf("done messing with the last point. \n");
	return graph;
}//enf getContourBarker_fancy



	///////////////////////end getContourBarker_fancy section ///////////////////

TGraph* makeBandGraph(TGraph* g1, TGraph* g2) {

	int n1 = g1->GetN();
	int n2 = g2->GetN();

	TGraph* graph = new TGraph(n1+n2);

	for(int i=0; i<n1; i++){
		double x,y;
		g1->GetPoint(i,x,y);
		graph->SetPoint(i,x,y);
	}
	for(int i=0; i<n2; i++){
		double x,y;
		g2->GetPoint(n2-1-i,x,y);
		graph->SetPoint(n1+i,x,y);
	}

	return graph;
}

TH1D* TH1FtoD(TH1F* f){
		//converts a TH1F to a TH1D
	TAxis * x =f->GetXaxis();
	int nbins = x->GetNbins();
	TString s(f->GetName());
	s+="_d";
	TH1D* d = new TH1D(s.Data(),f->GetTitle(), nbins,x->GetXmin(),x->GetXmax());
	for (int i=0; i<= nbins+1; ++i){
		d->SetBinContent(i,(double) f->GetBinContent(i));
		d->SetBinError(i,(double) f->GetBinError(i));
	}
	return d;
}

TH2D* TH2FtoD(TH2F* f){
		//converts a TH1F to a TH1D
	TAxis * x =f->GetXaxis();
	int nbinsX = x->GetNbins();
	TAxis * y =f->GetYaxis();
	int nbinsY = y->GetNbins();
	TString s(f->GetName());
	s+="_d";
	TH2D* d = new TH2D(s.Data(),f->GetTitle(), nbinsX,x->GetXmin(),x->GetXmax(),nbinsY,y->GetXmin(),y->GetXmax());
	for (int i=0; i<= nbinsX+1; ++i){
		for (int j=0; j<= nbinsY+1; ++j){
		d->SetBinContent(i,j,(double) f->GetBinContent(i,j));
		d->SetBinError(i,j,(double) f->GetBinError(i,j));
		}
	}
	return d;
}
