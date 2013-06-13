#ifndef HGGX_ANALYSER_H
#define HGGX_ANALYSER_H

#include <iostream>
//#include "TRandom.h"
#include "TRandom2.h"
#include <math.h>
using namespace std;

/*
 These funcitons take a function pointer and throw randoms into that function to get the error in it's output.
 
 */

/*
 Recall, to make a function pointer: 
 Take a normally defined function
 double func(*double inarray);
 then make a pointer to it.
 double (*funcPtr)(*double) = &func;
 
 To pass the function pointer, just give the name without prefixes
 
*** Test Driver: ***
 double divide(double * A);
 void test(){
 double (*funcPtr)(double *) = &divide;
 double avg_vals[2] = {4.,3.};
 double stdevs[2] = {0.01, 0.015};
 bool zero_limited[2] = {false, false};
 double err_out = GetError(funcPtr, 2, avg_vals, stdevs, zero_limited);
 cout << "prediction " << divide(avg_vals)<<" +- "<<err_out<<endl;
 cout << "usual error estimation: "<< sqrt(divide(avg_vals)*(pow(stdevs[0]/avg_vals[0],2) + pow(stdevs[1]/avg_vals[1],2)))<<endl;
 }
 double divide(double *A){
 return A[0]*A[1];
 }
 */

double GetError(double (*functionPointer)(double *), int n_vars, double * avg_vals, double * stdevs, bool * zero_limited);
float GetError(float (*functionPointer)(float *), int n_vars, float * avg_vals, float * stdevs, bool * zero_limited);
float GetError_v2(float (*functionPointer)(float *), int n_vars, float * avg_vals, float * stdevs, bool * zero_limited, bool * in_use);
float GetError_2correlated(float (*functionPointer)(float *), float * avg_vals, float * covarianceMx, int n_vars = 2);
void GetError_2correlated_help(float* covarianceMx, float& ss1, float& ss2,float& cp,float& sp);

double GetError(double (*functionPointer)(double *), int n_vars, double * avg_vals, double * stdevs, bool * zero_limited){
	/*
	 We have a function f = *functionPointer that takes random n_vars q1, q2...qn
	 qi is a gaussian random varriable with average Qi and stdev si.
	 p = f(q1, q2, .. qn) and 
	 P = f(Q1, Q2, .. Qn)
	 we want the standard deviation of P. 

	 We'll be stupid about it and assume that the error bars are symmetric and that everything is gaussian. 
	 We compute stdev(p) stochastically. We're doing this because qi may be used multiple times and we seek 
	 to account for those corrolations. 
	 
	 if zero_limited[i] then we won't allow qi to fluctuate to negative values and ignore pseudo experiments that do. 
	 functionPointer must take a double array length n_vars
	 */


		//screen for user doing stupid shit
	for (int j_var=0; j_var<n_vars; j_var++) {
		if(avg_vals[j_var] < 0. && zero_limited[j_var]){
			cout<<"Error! GetError recieved negative average on a zero_limited number"<<endl;
			return 0.;
		}
		if (stdevs[j_var] < 0.){
			cout<<"Warning! GetError recieved negative standard deviation, setting it to it's absolute value"<<endl;
			stdevs[j_var] = fabs(stdevs[j_var]);
		}
	}//end for every varraible
	
	
	double P = (*functionPointer)(avg_vals);
	double sum_res = 0.;
	int N_iterations = 100000; // 0.1 million should be enough. So note that this is a slow function. 
	int N_for_average = N_iterations;
	TRandom2 *r = new TRandom2();
	double In_i[n_vars];
	for (int iter = 0; iter<N_iterations && N_iterations < 400000; iter++) {
		for (int j_var=0; j_var<n_vars; j_var++) {
			In_i[j_var] = r->Gaus(avg_vals[j_var], stdevs[j_var]);  
			if (zero_limited[j_var] && In_i[j_var] < 0.){ //this is a slow question that could be eliminated
				N_iterations++;
				continue;
			}
		}//end for every varraible
		sum_res += pow(P-(*functionPointer)(In_i),2);
	}//end for every itteration
	if (N_iterations > 399997 ) cout<<"WARNING! GetErrors itterations timeout."<<endl;
	return sqrt(sum_res/N_for_average);
}//end GetError


float GetError(float (*functionPointer)(float *), int n_vars, float * avg_vals, float * stdevs, bool * zero_limited){
	/*
	 We have a function f = *functionPointer that takes random n_vars q1, q2...qn
	 qi is a gaussian random varriable with average Qi and stdev si.
	 p = f(q1, q2, .. qn) and 
	 P = f(Q1, Q2, .. Qn)
	 we want the standard deviation of P. 
	 
	 We'll be stupid about it and assume that the error bars are symmetric and that everything is gaussian. 
	 We compute stdev(p) stochastically. We're doing this because qi may be used multiple times and we seek 
	 to account for those corrolations. 
	 
	 if zero_limited[i] then we won't allow qi to fluctuate to negative values and ignore pseudo experiments that do. 
	 functionPointer must take a float array length n_vars
	 */
	
	
		//screen for user doing stupid shit
	for (int j_var=0; j_var<n_vars; j_var++) {
		if(avg_vals[j_var] < 0. && zero_limited[j_var]){
			cout<<"Error! GetError recieved negative average on a zero_limited number"<<endl;
			return 0.;
		}
		if (stdevs[j_var] < 0.){
			cout<<"Warning! GetError recieved negative standard deviation, setting it to it's absolute value"<<endl;
			stdevs[j_var] = fabs(stdevs[j_var]);
		}
	}//end for every varraible
	
	
	float P = (*functionPointer)(avg_vals);
	float sum_res = 0.;
	int N_iterations = 100000; // 0.1 million should be enough. So note that this is a slow function. 
	int N_for_average = N_iterations;
	TRandom2 *r = new TRandom2();
	float In_i[n_vars];
	for (int iter = 0; iter<N_iterations && N_iterations < 400000; iter++) {
		for (int j_var=0; j_var<n_vars; j_var++) {
			In_i[j_var] = r->Gaus(avg_vals[j_var], stdevs[j_var]);  
			if (zero_limited[j_var] && In_i[j_var] < 0.){ //this is a slow question that could be eliminated
				N_iterations++;
				continue;
			}
		}//end for every varraible
		sum_res += pow(P-(*functionPointer)(In_i),2);
	}//end for every itteration
	if (N_iterations > 399997 ) cout<<"WARNING! GetErrors itterations timeout."<<endl;
	return sqrt(sum_res/N_for_average);
}//end GetError


	////ddddd
float GetError_v2(float (*functionPointer)(float *), int n_vars, float * avg_vals, float * stdevs, bool * zero_limited, bool * in_use){
	/*
	 Here, some of the unput varriables are not used, so we don't bother varrying them
	 We only varry the input var if in_use
	 
	 We have a function f = *functionPointer that takes random n_vars q1, q2...qn
	 qi is a gaussian random varriable with average Qi and stdev si.
	 p = f(q1, q2, .. qn) and 
	 P = f(Q1, Q2, .. Qn)
	 we want the standard deviation of P. 
	 
	 We'll be stupid about it and assume that the error bars are symmetric and that everything is gaussian. 
	 We compute stdev(p) stochastically. We're doing this because qi may be used multiple times and we seek 
	 to account for those corrolations. 
	 
	 if zero_limited[i] then we won't allow qi to fluctuate to negative values and ignore pseudo experiments that do. 
	 functionPointer must take a float array length n_vars
	 */
	
	
		//screen for user doing stupid shit
	for (int j_var=0; j_var<n_vars; j_var++) {
		if(avg_vals[j_var] < 0. && zero_limited[j_var]){
			cout<<"Error! GetError recieved negative average on a zero_limited number"<<endl;
			return 0.;
		}
		if (stdevs[j_var] < 0.){
			cout<<"Warning! GetError recieved negative standard deviation, setting it to it's absolute value"<<endl;
			stdevs[j_var] = fabs(stdevs[j_var]);
		}
	}//end for every varraible
	
	
	float P = (*functionPointer)(avg_vals);
	float sum_res = 0.;
	int N_iterations = 100000; // 0.1 million should be enough. So note that this is a slow function. 
	int N_for_average = N_iterations;
	TRandom2 *r = new TRandom2();
	float In_i[n_vars];
	for (int iter = 0; iter<N_iterations && N_iterations < 400000; iter++) {
		for (int j_var=0; j_var<n_vars; j_var++) {
			if (!in_use[j_var]) continue;
			In_i[j_var] = r->Gaus(avg_vals[j_var], stdevs[j_var]);  
			if (zero_limited[j_var] && In_i[j_var] < 0.){ //this is a slow question that could be eliminated
				N_iterations++;
				continue;
			}
		}//end for every varraible
		sum_res += pow(P-(*functionPointer)(In_i),2);
	}//end for every itteration
	if (N_iterations > 399997 ) cout<<"WARNING! GetErrors itterations timeout."<<endl;
	return sqrt(sum_res/N_for_average);
}//end GetError


	//ok, make this as general as possible. 
	//we make a function of the form 

	//version one: you take a func ptr of two params simply, n_vars is set to two. avg vals are set. 
float GetError_2correlated(float (*functionPointer)(float *), float * avg_vals, float * covarianceMx, int n_vars ){
	/*
	 We have a function f = *functionPointer that takes 2 random correlated gaussian varriables q1, q2, 
	 and n_vars-2 constants q3...qn
	 q1 and q2 are correlated gaussian random variables, as described by the covarienceMx elements. 
	 avg_vals must have length n_vars. covarianceMx has three elements: r11, r12, r22, in that order.
	 there is no stdev input because that's replaced by the covariance matrix.
	 
	 qi is a gaussian random varriable with average Qi and stdev si.
	 p = f(q1, q2, .. qn) and 
	 P = f(Q1, Q2, .. Qn)
	 this outputs the standard deviation of P. 
	 	 We compute stdev(p) stochastically. We're doing this because qi may be used multiple times and we seek 
	 to account for those corrolations. 	 
	 */
		
	
	float P = (*functionPointer)(avg_vals);
	float sum_res = 0.;
	int N_iterations = 100000; // 0.1 million should be enough.
	int N_for_average = N_iterations;
	TRandom2 *r = new TRandom2();
//	for (int iter = 0; iter<N_iterations && N_iterations < 400000; iter++) {
	
		//calculate parameter for the correlation
	float ss1,ss2, cp, sp;
	GetError_2correlated_help(covarianceMx, ss1, ss2, cp, sp);//prep vars for throwing randoms
		
	float alpha, beta;
	float In_i[n_vars];
	for (int j_var=2; j_var<n_vars; j_var++) In_i[j_var] = avg_vals[j_var];
	
	for (int iter = 0; iter<N_iterations; iter++) {
		alpha = r->Gaus(0,ss1);
		beta  = r->Gaus(0,ss2);
		In_i[0] = avg_vals[0] + alpha*cp + beta*sp;
		In_i[1] = avg_vals[1] - alpha*sp + beta*cp;
//			if (zero_limited[j_var] && In_i[j_var] < 0.){ //this is a slow question that could be eliminated
//				N_iterations++;
//				continue;
//			}
		sum_res += pow(P-(*functionPointer)(In_i),2);
	}//end for every itteration
//	if (N_iterations > 399997 ) cout<<"WARNING! GetErrors itterations timeout."<<endl;
	return sqrt(sum_res/N_for_average);
}


/*
 //the function from Yuri:
 void rpar(double p0, double p1, double r11, double r12, double r22, double &rp0, double &rp1, TRandom3 *r)
	//p0, p1 - pol1 parameters
	// r11, r12, r22 - covariance matrix from the fit
	// rp0, rp1 - output: randomly thrown parameters for pol1
	// r - random number generator factory
{
	
	
	double phi = -0.5*atan(2*r12/(r11-r12));
	double sp  = sin(phi);
	double cp  = cos(phi);
	double sp2 = sin(phi)*sin(phi);
	double cp2 = 1-sp2;
	
	double ss2 = (r11*sp2-r22*cp2)/(sp2*sp2-cp2*cp2);
	double ss1 = r11+r22-ss2;
	ss2 = sqrt(ss2);
	ss1 = sqrt(ss1);
	
	double alpha = r->Gaus(0,ss1);
	double beta  = r->Gaus(0,ss2);
	rp0 = p0 + alpha*cp + beta*sp;
	rp1 = p1 - alpha*sp + beta*cp;
}
//I reduced this to:
void rpar(double p0, double p1, double r11, double r12, double r22, double &rp0, double &rp1, TRandom2 *r)
 //p0, p1 - fit parameters
 // r11, r12, r22 - covariance matrix from the fit
 // rp0, rp1 - output: randomly thrown parameters for pol1
 // r - random number generator factory
 {
 double ss1,ss2, cp, sp;
 rpar1(p0, p1, r11, r12, r22, ss1, ss2, cp, sp);//this is kind of wasteful. 
 rpar2(p0, p1, ss1, ss2, cp, sp, &rp0, &rp1, r)
 }


void rpar1(double p0, double p1, double r11, double r12, double r22, double& ss1, double& ss2,double& cp,double& sp){
	double phi = -0.5*atan(2*r12/(r11-r12));
	double sp  = sin(phi);
	double cp  = cos(phi);
	double sp2 = sp*sp;
	double cp2 = 1.0-sp2;
	
	double ss2 = (r11*sp2-r22*cp2)/(sp2*sp2-cp2*cp2);
	double ss1 = sqrt(r11+r22-ss2);
	ss2 = sqrt(ss2);
}
 
void rpar2(double p0, double p1, double ss1, double ss2,double cp,double sp,double &rp0, double &rp1, TRandom2 *r){
	double alpha = r->Gaus(0,ss1);
	double beta  = r->Gaus(0,ss2);
	rp0 = p0 + alpha*cp + beta*sp;
	rp1 = p1 - alpha*sp + beta*cp;
}*/
void GetError_2correlated_help(float* covarianceMx, float& ss1, float& ss2,float& cp,float& sp){
	/*
	 preps varriables for throwing correlated random numbers.
	 */
	float r11 = covarianceMx[0];
	float r12 = covarianceMx[1];
	float r22 = covarianceMx[2];
	float phi = -0.5*atan(2*r12/(r11-r12));
	sp  = sin(phi);
	cp  = cos(phi);
	float sp2 = sp*sp;
	float cp2 = 1.0-sp2;
	
	ss2 = (r11*sp2-r22*cp2)/(sp2*sp2-cp2*cp2);
	ss1 = sqrt(r11+r22-ss2);
	ss2 = sqrt(ss2);
}

#endif

