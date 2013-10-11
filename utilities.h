#ifndef _UTILITIES_H // if not defined
#define _UTILITIES_H

#include <iostream>
#include "math.h"
#include "TMath.h"
#include "TRandom2.h"
#include "TString.h"
#include "TH2.h"
#include <vector>
#include <fstream>
#include "TStopwatch.h"
#include "TLorentzVector.h"
#include <sys/stat.h>  //needed for fileExists
#include "TGraph.h"
using namespace std;

bool aeq(float A, float B, int scale=5);
bool strCmp(string a, string b); //a == b

bool is_real(float x);
void NameHist(TH1F* h, string rootname, string title);
TString RandomString(int length);
float dPhi(float phi1, float phi2);
float dPhi(TLorentzVector A, TLorentzVector B);
float phi_0_2pi(float phi);
float phi_negpi_pi(float phi);
float dR(TLorentzVector A, TLorentzVector B);
float Mt(TLorentzVector x);
float ThetaStar(TLorentzVector & a,TLorentzVector & b);
//float slowThetaStar(TLorentzVector a,TLorentzVector b);
void fixNAN(TH1F* h,float nonsenceval=-1.0, float nonsenceerr = 0);
void AddOverflow(TH1F* h);
bool histisempty(TH1F* h);
void printHist(TH1F* h);
bool fileExists(std::string fname);
void m(int i);
TGraph* makeband(TGraph* A, TGraph* B, int color);
TGraph* makeband_0guard(TGraph* A, TGraph* B, int color);
void Sqrt(TH1F* hin);

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void m(int i){ cout<<"mark "<<i<<endl; }

	//aproxomately equals function
	//test if A and B are within 10^-scale of each other
bool aeq(float A, float B, int scale ){
	if(A>(B-pow(10,-1*scale)) && A<(B+pow(10,-1*scale))) return true;
	else return false;
}

bool strCmp(string a, string b){
        //returns true if strings match; a == b
        return a.compare(b) == 0 && b.compare(a) == 0;
}

bool is_real(float x){
	if(TMath::IsNaN(x)) return false;
	return TMath::Finite(x);
}

bool histisempty(TH1F* h){
	bool empty = true;
	for(int i=1;i<=h->GetNbinsX();i++) empty &= aeq(0.0f,h->GetBinContent(i));
	return empty;
}

void printHist(TH1F* h){
	printf("integral %i\n",(int)h->Integral());
	TAxis *x = h->GetXaxis();
	printf("bin    Range                    val+- Error\n");
	printf("underflow bin                  %f +- %f\n", h->GetBinContent(0),h->GetBinError(0));
	for(int i=1;i<=h->GetNbinsX();i++){
		printf("bin %i %f-%f        %f +- %f\n",i,x->GetBinLowEdge(i),x->GetBinUpEdge(i), h->GetBinContent(i),h->GetBinError(i));
	} 
	int j = h->GetNbinsX()+1;
	printf("overflow bin                   %f +- %f\n", h->GetBinContent(j),h->GetBinError(j));
}

void NameHist(TH1F* h, string rootname, string title){
	h->SetName(rootname.c_str());
	h->SetTitle(title.c_str());
}

TString RandomString(int length){
 //returns a TString of (length) random upper and lower case letters 
 //TString f = RandomString(12) // f = JxcDLbEaRpAR
 //good for random titles. 
	TString randstring("");
	static TRandom2 * r = new TRandom2();
	while (length > 0) {
		length--;
		int j = r->Integer(52); //25ns per call
		if (j<26) j += 65;//A
		else j += 71;
		randstring.Append((char)j);
	}
	return randstring;
} // end RandomString

float dPhi(float phi1, float phi2){
	float dphi = fabs(phi1 - phi2);
	if (dphi > 3.14159265359) return 6.28318530718 - dphi;
	return dphi;
}
float dPhi(TLorentzVector A, TLorentzVector B){ return dPhi(A.Phi(),B.Phi()); }
float dR(TLorentzVector A, TLorentzVector B){
	float dphi = dPhi(A.Phi(),B.Phi());
	float dEta = fabs(A.Eta() - B.Eta());
	return sqrt(dphi*dphi  +  dEta*dEta);
}
float phi_0_2pi(float phi){ //forces phi to be on 0..2pi
	if(phi >= 0) return phi;
	else return 6.28318530718 + phi;
}
float phi_negpi_pi(float phi){ //forces phi to be on 0..2pi
	if(phi >= 3.14159265359) return phi - 6.28318530718;
	else return phi;
}

float Mt(TLorentzVector x){return sqrt(x.E()*x.E() - x.Perp2());}
	//sqrt(E^2 - Pt^2)

float ThetaStar(TLorentzVector & a,TLorentzVector & b){
                        //calculate cos(theta*), the angle between the two vectors  in their center of mass frame.

                TLorentzVector A(a); //copy A so we dont' spoil the origional
                TLorentzVector sum = a + b;
		TVector3 xhat(1,0,0);//x_hat unit vector
                TVector3 axis = (sum.Vect().Cross(xhat)).Unit(); //get rot axis by which to rotate sum to x-axis
                A.Rotate(sum.Angle(xhat),axis); //Rotate the sum to lie along the x-axis
                A.Boost(-sum.Beta(),0,0); //boost along the x-axis to move to CM frame
                return fabs(A.Vect() * xhat)/A.Vect().Mag(); //get cos(theta) w.r.t. x-axis/boost direction.
}//end 

/*float slowThetaStar(TLorentzVector a,TLorentzVector b){
                        //calculate cos(theta*), the angle between the two vectors  in their center of mass frame.
			//I keep this comment because the derrivaiton is a little clearer
                TLorentzVector A(a);
                TLorentzVector B(b);
                TLorentzVector sum = a + b;

                TVector3 v3sum = sum.Vect();//get the spacial vector.                
		TVector3 xhat(1,0,0);//x_hat unit vector
                TVector3 axis = (v3sum.Cross(xhat)).Unit();
                double theta = sum.Angle(xhat);
                printf("sum before: E %.1f P %.1f Px %.1f Py %.1f Pz %.1f\n",sum.E(),sum.P(),sum.Px(),sum.Py(),sum.Pz());
                printf("axis: x %.2f y %.2f z %.2f theta %.2f \n",axis.Px(),axis.Py(),axis.Pz(),theta);
                sum.Rotate(theta,axis); //rotate so that sum is parallel with the x-axis. This makes the boost 1D
                A.Rotate(theta,axis);
                B.Rotate(theta,axis);
		printf("sum afterR: E %.1f P %.1f Px %.1f Py %.1f Pz %.1f\n",sum.E(),sum.P(),sum.Px(),sum.Py(),sum.Pz());
                double beta = sum.Beta();
                sum.Boost(-beta,0,0);
                A.Boost(-beta,0,0);
                B.Boost(-beta,0,0);
                //these are now in the center of mass frame. and the boost is along xhat
                //A and B are identically back to back. So it doesn't matter which one we choose. 
//              printf("sum afterB: E %.1f P %.1f Px %.1f Py %.1f Pz %.1f\n",sum.E(),sum.P(),sum.Px(),sum.Py(),sum.Pz());
                TVector3 Aprime = A.Vect().Unit();
                //TVector3 p1prime = B.Vect().Unit();
                //printf("p0prime: x %.2f y %.2f z %.2f \n",p0prime.Px(),p0prime.Py(),p0prime.Pz());
                return fabs(Aprime * xhat/Aprime.Mag());
}//end */

void fixNAN(TH1F* h,float nonsenceval, float nonsenceerr){
	for(int i=0;i<= h->GetNbinsX(); i++){
		if(TMath::IsNaN(h->GetBinContent(i)) || !TMath::Finite(h->GetBinContent(i)) ||
		   TMath::IsNaN(h->GetBinError(i)) || !TMath::Finite(h->GetBinError(i))){
			h->SetBinContent(i,nonsenceval);
			h->SetBinContent(i,nonsenceerr);
		}//end if something is wrong with it.
	}//end for.
}//end fixNAN

void AddOverflow(TH1F* h){
		//merges the overflow bin and the last bin.
	int nb = h->GetNbinsX();
	float lastbin = h->GetBinContent(nb);
	float overflow = h->GetBinContent(nb+1);
	float lbErr = h->GetBinError(nb);
	float ofError = h->GetBinError(nb+1);

	h->SetBinContent(nb,lastbin+overflow);
	h->SetBinError(nb,sqrt(lbErr*lbErr + ofError+ofError)  );
	h->SetBinContent(nb+1,0.0);
	h->SetBinError(nb+1,0.0);
}

class probe{
/*
This gives a quick cout function for probing lines and also gives time measurements to understand code efficiency. 
Define a probe at the start. 
p("message to print to terminal");//simplified cout, adds time stamp 
put a ppush before a loop or block to start a new coutner. the string becomes it's name and gets printed
ppop to remove a counter
pall prints the last n counters defined along with your message. just neglect n to print all. 
*/
public:
	probe(string s = "begin probe");
	void p(string s);
	void ppush(string s, bool silent = false);
	void ppop(bool silent = false);
	void pall(string s,int n=-1);
private:
	std::vector<TStopwatch*> vts;
	std::vector<string> vs;
	double tinstant;
};
probe::probe(string s){
	vts.push_back(new TStopwatch());
	vs.push_back(s);
	vts[0]->Start();
	tinstant = vts[0]->RealTime();
	vts[0]->Continue();
}
void probe::p(string s){
		//prints your message s and tells the time since the last push or the start. 
	printf("%s %.3f ms\n",s.c_str(),(vts.back()->RealTime() - tinstant)*1000.0);
	vts.back()->Continue();
}
void probe::ppush(string s, bool silent){
		//make a new timer, add it to the list, start it, give it a name s, print s unless silent
	if(!silent) p(Form("start %s",s.c_str()));
	vs.push_back(s);
	vts.push_back(new TStopwatch());
	vts.back()->Start();
}

void probe::ppop(bool silent){
		//removes the last timer and tell how long it ran (unless silent)
	if(!silent) p(Form("finished %s",vs.back().c_str()));
	vs.pop_back();
	vts.pop_back();
}
void probe::pall(string s,int n){
		//print s and print the last n timers. 
	int nst = (int)vts.size();
	printf("%s\n",s.c_str());
	if (n == -1 || n >= nst) {
		n = nst;
	}
		std::vector<TStopwatch*>::reverse_iterator vit = vts.rbegin();
		std::vector<string>::reverse_iterator sit = vs.rbegin();
		while (vit != vts.rend()-(nst-n)) {
			printf("probe %s took %.3f ms\n",(*sit).c_str(),((*vit)->RealTime()-tinstant)*1000.0);
			vit++; sit++;
		}
		for(std::vector<TStopwatch*>::reverse_iterator it = vts.rbegin(); it != vts.rend()-(nst-n); ++it) (*it)->Continue();
}//end pall

bool fileExists(std::string filename){
		//returns true if a file exists
		//if file doesn't exist, runs in 0.72 microseconds
		//if file exists and is 500MB, runs in 0.93 microseconds
    struct stat buf;
    return stat(filename.c_str(), &buf) != -1;

		/*alternatively could do
			ifstream infile(filename.data());
			return (bool) infile;
		//requires 2.36 microseconds if the file doesn't exist
		//requires 17.4 microseconds for a 500MB file */
}

TGraph* makeband(TGraph* A, TGraph* B, int color){
		//Takes two TGraphs, presumably parallel..
		//makes a third TGraph that is a loop connecting the end of one to the start of the other
		//it closes the loop so you can plot it as a band. 
	int nA = A->GetN();
	int nB = B->GetN();
	int npoints = nA + nB + 1;
	Double_t x[npoints];
	Double_t y[npoints];
	for (int i = 0; i<nA; i++) {
		Double_t tmpx, tmpy;
		A->GetPoint(i,tmpx,tmpy);
		x[i]=tmpx;
		y[i]=tmpy;
		cout<<"A: x="<<tmpx<<" y="<<tmpy<<endl;
	}
	for (int i = 0; i<nB; i++) {
		Double_t tmpx, tmpy;
		B->GetPoint(nB-1-i,tmpx,tmpy);
		x[i+nA]=tmpx;
		y[i+nA]=tmpy;
		cout<<"B: x="<<tmpx<<" y="<<tmpy<<endl;
	}
	
	cout<<"EndPoint: x="<<x[0]<<" y="<<y[0]<<endl;
	x[npoints-1]=x[0];
	y[npoints-1]=y[0];
	TGraph* out = new TGraph(npoints,x,y);
	out->SetFillColor(color);
	return out;
}//end makeband
TGraph* makeband_0guard(TGraph* A, TGraph* B, int color){
		//Takes two TGraphs, presumably parallel..
		//makes a third TGraph that is a loop connecting the end of one to the start of the other
		//it closes the loop so you can plot it as a band. 
	int nA = 0;
	int nB = 0;
	for (int i = 0; i<A->GetN(); i++) {
		Double_t tmpx, tmpy;
		A->GetPoint(i,tmpx,tmpy);
		if(tmpx!=0 && tmpy!=0) nA++;
	}
	for (int i = 0; i<B->GetN(); i++) {
		Double_t tmpx, tmpy;
		B->GetPoint(i,tmpx,tmpy);
		if(tmpx!=0 && tmpy!=0) nB++;
	}
	int npoints = nA + nB + 1;
	Double_t x[npoints];
	Double_t y[npoints];
	for (int i = 0; i<nA; i++) {
		Double_t tmpx, tmpy;
		A->GetPoint(i,tmpx,tmpy);
		x[i]=tmpx;
		y[i]=tmpy;
		cout<<"i="<<i<<" A: x="<<tmpx<<" y="<<tmpy<<endl;
	}
	for (int i = 0; i<nB; i++) {
		Double_t tmpx, tmpy;
		B->GetPoint(nB-1-i,tmpx,tmpy);
		x[i+nA]=tmpx;
		y[i+nA]=tmpy;
		cout<<"i="<<i+nA<<" B: x="<<tmpx<<" y="<<tmpy<<endl;
	}
	
	cout<<"i="<<npoints-1<<" EndPoint: x="<<x[0]<<" y="<<y[0]<<endl;
	x[npoints-1]=x[0];
	y[npoints-1]=y[0];
	TGraph* out = new TGraph(npoints,x,y);
	out->SetFillColor(color);
	return out;
}//end makeband

void Sqrt(TH1F* hin){
	//hin = sqrt(hin)
	for (int ibin=0; ibin<= hin->GetXaxis()->GetNbins(); ++ibin) {
		float rootbin = sqrt(hin->GetBinContent(ibin));
		hin->SetBinContent(ibin,rootbin);
		hin->SetBinError(ibin,0.5f*hin->GetBinError(ibin)/rootbin);
	}
}//end Sqrt

#endif
