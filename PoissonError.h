#ifndef POISSONERROR
#define POISSONERROR
#include <iostream>
//#include <vector>
//#include <map>
//#include <string>
//#include "TString.h"
//#include "TMath.h"
#include <cmath>

using namespace std;

	//Numbers taken from http://pdg.lbl.gov/2009/reviews/rpp2009-rev-statistics.pdf
	//page 26; Table 32.3
float UncertaintyLow(float n);
float UncertaintyHi(float n);
int round(float n);
float Upper95pctBound(int n);
float Lower95pctBound(int n);
float Upper1sigmaBound(int n);
float Lower1sigmaBound(int n);
float PoissonCDF(int n, float lambda);
float FindUpperPoissonLimit(int n, float u = 0.3173);
float FindLowerPoissonLimit(int n, float u = 0.6827);
float Gamma(float s);
float Zeta(float s, short nstop = 50);
int factorial(int n);




float UncertaintyLow(float n){
	return n-Lower1sigmaBound(round(n));
}
float UncertaintyHi(float n){
	return Upper1sigmaBound(round(n)) - n;
}

int round(float n){
	int N = floor(n);
	n -= (float) N;
	if(n >=0.5) return N+1;
	else return N;
}


float Upper95pctBound(int n){
	if (n<0) return 0.f;
	switch (n) {
		case 0:
			return 3.0;
		case 1:
			return 4.74;
		case 2:
			return 6.30;
		case 3:
			return 7.75;
		case 4:
			return 9.15;
		case 5:
			return 10.15;
		case 6:
			return 11.84;
		case 7:
			return 13.15;
		case 8:
			return 14.43;
		case 9:
			return 15.71;
		case 10:
			return 10.96;
		default:
			return sqrt(float(n));
	}
}//end Upper95pctBound

float Lower95pctBound(int n){
	if (n<0) return 0.f;
	switch (n) {
		case 0:
			return 0.f;
		case 1:
			return 0.051;
		case 2:
			return 0.355;
		case 3:
			return 0.818;
		case 4:
			return 1.37;
		case 5:
			return 1.97;
		case 6:
			return 2.61;
		case 7:
			return 3.29;
		case 8:
			return 3.98;
		case 9:
			return 4.70;
		case 10:
			return 5.43;
		default:
			return sqrt(float(n));
	}
}//end Lower95pctBound

float Upper1sigmaBound(int n){
	//I calculated these using a poisson cdf--probed until poissoncdf(n,mu) = 1-0.6827
	if (n<0) return 0.f;
	switch (n) {
		case 0:
			return 1.15; 
		case 1:
			return 2.36;
		case 2:
			return 3.52;
		case 3:
			return 4.66;
		case 4:
			return 5.77;
		case 5:
			return 6.88;
		case 6:
			return 7.97; 
		case 7:
			return 9.06;
		case 8:
			return 10.14;
		case 9:
			return 11.22; 
		case 10:
			return 12.30;
		default:
			return sqrt(float(n));
	}
}//end Upper95pctBound

float Lower1sigmaBound(int n){
	//I calculated these using a poisson cdf--probed until poissoncdf(n,mu) = 0.6827
	if (n<0) return 0.f;
/*	switch (n) {
		case 0:
			return 0.f;
		case 1:
			return 0.99;
		case 2:
			return 1.97; //wtf, really?
		case 3:
			return 2.84;
		case 4:
			return 3.72;
		case 5:
			return 4.61;
		case 6:
			return 5.52;
		case 7:
			return 6.43;
		case 8:
			return 7.34;
		case 9:
			return 8.26;
		case 10:
			return 9.19;
		default:
			return sqrt(float(n));
	}
*/
//I don't believe those, they look too high. So I'll use this kluge
	float N = ((float)n);
	return N - (N-Lower95pctBound(n))/2.0f;
}//end Lower95pctBound


float PoissonCDF(int n, float lambda){
	if(n>12) return 0;//protect it from int max value in factorial;
	float ret = 0.0f;
	for(int i=0;i<=n;i++) ret+= pow(lambda,i)/((float) factorial(i));
	return exp(-lambda)*ret;
}
float FindUpperPoissonLimit(int n, float u ){
	if(n>11) return sqrt((float)n);
	float mu = 0.01+((float) n);
	while(PoissonCDF(n,mu) > u && mu<30.0f) mu+=0.01f;	
	return mu;
}
float FindLowerPoissonLimit(int n, float u ){
	if(n==0) return 0;
	if(n>11) return sqrt((float)n);
	float mu = ((float) n) -0.01f;
	while(PoissonCDF(n,mu) < u && mu>0.0f) mu-=0.01f;	
	return mu;
}

/*float PoissonCDF_hard(int n, float lambda){
	return IncompleteGamma_U(n+1,lambda)/((float) factorial(n));	
}

float IncompleteGamma_U(float s, float z){
	//the Upper Incomplete Gamma Function
	if(s<0.00001 && s > 0.00001){
		float ret = -0.577216-log(z);
		for(short k=1;k<11;k++) ret += pow(-1,k)*pow(z,k)/((float) k*factorial(k));
		return ret;
	}
	return Gamma(s) - IncompleteGamma_L(s,z);
}
float IncompleteGamma_L(float s, float z){
		//the Lower Incomplete Gamma Function
	if(s>0){
		float ret = 0f;
		for(short k=0;k<11;k++) ret+= pow(-1,k)*pow(z,k)/((s+z)*factorial(k));
		ret *= pow(z,s);
		return ret;
	}
	else{
		float ret = 0f;
		for(short k=0;k<11;k++) ret+= pow(-1,k)*pow(z,k)/((s+z)*factorial(k)*Gamma(s));
		return ret;
	}
}//end UncompleteGamma_l
*/
float Gamma(float s){
	//if s<0 or >-2 this breaks down. 
	s--;
	float logG = -s*0.577216;//the Euler–Mascheroni constant
	for(float i=2.0f;i<50.0f;i++) logG += Zeta(i)*pow(-s,i)/i;
	return exp(logG);
}

float Zeta(float s, short nstop){
	//returns an approxomate Riemann zeta function for real s
	//20 is probably enough. 70 will push the series past the limit
	float ret = 0.0f;
	for(short i=1;i<nstop;i++) ret += 1.0f/pow((float)i,s);
	return ret;
}
int factorial(int n){
	//returns n! as long as n<=13, else it gives nonsense 
	if(n<=0) return 1;
	else return n*factorial(n-1);
}

#endif
