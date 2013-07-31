#ifndef _HGGX_ANALYSERS_H
#define _HGGX_ANALYSERS_H

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>
#include "TAxis.h"
#include "TMath.h"
#include "math.h"
#include <TH3.h>
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "PoissonError.h"
#include "TGraphAsymmErrors.h"
//#include "TGraphErrors.h"
#include "TGraph.h"
#include "TF1.h"
#include <iostream>
	//user defiend
#include "utilities.h"
#include "cuts.h"
#include "params_arg.h"
#include "GetError.h"//made obsolete by fitmgg_simple
#include "TMatrixTSym.h"
#include "TFitResult.h"
#include <map>

using namespace std;
using namespace params;

//void fitmgg(TH1F* hmgg, float lb, float ub, TGraphAsymmErrors** g, TF1** fitcurve, float& chi2, float ** fit_parameters, float ** fit_parameter_errors);
void fitmgg_simpler(TH1F* hmgg, Double_t lb, Double_t ub, TF1** fitcurve, float& chi2, float & B_integral, float & B_integral_error, TString type, bool preset_fitter = true);
void fitmgg_simple(TH1F* hmgg, float lb, float ub, TGraphAsymmErrors** g, TF1** fitcurve, float& chi2, float & B_integral, float & B_integral_error, TString type, bool preset_fitter = true);//obsolete, but maybe useful

void find_preset_params(TH1F* hmgg,int lb_bin,int higgslb_bin,int higgsub_bin, int ub_bin,float &param0,float &param1);
void find_preset_params_powerlaw(TH1F* hmgg,int lb_bin,int higgslb_bin,int higgsub_bin, int ub_bin,float &param0,float &param1);
bool check_statistics(TH1F* hmgg,int lb_bin,int higgslb_bin,int higgsub_bin, int ub_bin);
//***	
void nLep(TH1F** h, float B_integral, float B_integral_error, float lsb_int, float usb_int);
//***
void fitmgg(TH1F* hmgg, float lb, float ub, TGraphAsymmErrors** g, TF1** fitcurve, float& chi2, float * fit_parameters, float * covarianceMx, bool preset_fitter = true); //currently orphaned and unused
void find_bkg_with_fit(TH1F** h, float B_integral, float B_integral_error, float lsb_int, float usb_int); //the state of the art; but you can do better
void get_bkg_integral(float* fit_parameters, float* covarianceMx, float & B_integral, float & B_integral_error);//made obsolete by fitmgg_simple, orphaned, unused. 
float expo_integral(float * params);//made obsolete by fitmgg_simple orphaned, unsed.
void find_bkg(TH1F** h);//obsolete, but maybe still useful if the fit fails., orphaned, unused

	//fit functions
Double_t fpow(Double_t *x, Double_t *par);
Double_t flin(Double_t *x, Double_t *par);
Double_t fcon(Double_t *x, Double_t *par);
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	

Bool_t reject;//needed for communicaiton with fpow
Double_t fpow(Double_t *x, Double_t *par){
		//Fit function definition
		//if(x[0]>tag_lb && x[0]<tag_ub){
	if(reject && x[0]>=lsb_ub && x[0]<=usb_lb){
		TF1::RejectPoint();
		return 0;
	}
	return par[0]*pow(x[0],par[1]);
}
Double_t flin(Double_t *x, Double_t *par){
		//Fit function definition
		//if(x[0]>tag_lb && x[0]<tag_ub){
	if(reject && x[0]>=lsb_ub && x[0]<=usb_lb){
		TF1::RejectPoint();
		return 0;
	}
	return par[0]+x[0]*par[1];
}
Double_t fcon(Double_t *x, Double_t *par){
		//Fit function definition
		//if(x[0]>tag_lb && x[0]<tag_ub){
	if(reject && x[0]>=lsb_ub && x[0]<=usb_lb){
		TF1::RejectPoint();
		return 0;
	}
	return par[0];
}




void fitmgg_simpler(TH1F* hmgg, Double_t lb, Double_t ub, TF1** fitcurve, float& chi2, float & B_integral, float & B_integral_error, TString type, bool preset_fitter){
		//fit an power law to hmgg within (lb, ub), but excluding the tag region and buffers.
		//example call:
		//	TF1* mgg_fit_curve;
		//	float chi2, B_integral, B_integral_error;   //for return vals
		//  fitmgg_simpler(hdiPhoMass,105.,160.,&mgg_fit_curve,chi2, B_integral, B_integral_error);
		//  //and that's all, no need for the get_bkg_integral function at all!
	//cout << "in fitmgg_simple"<<endl;

	TString name = "mgg"+type+"fit";
	*fitcurve = new TF1(name,fpow,lb,ub,2);//the last 2 says 2params.

	int lb_bin = hmgg->GetXaxis()->FindBin(lb);
	int ub_bin = hmgg->GetXaxis()->FindBin(ub);
	int higgslb_bin = hmgg->GetXaxis()->FindBin(lsb_ub);
	int higgsub_bin = hmgg->GetXaxis()->FindBin(usb_lb);
	if( check_statistics(hmgg,lb_bin,higgslb_bin,higgsub_bin, ub_bin)){
		if( preset_fitter){
			/*prepare the fit result*/
			float param0, param1;
			find_preset_params_powerlaw(hmgg,lb_bin,higgslb_bin,higgsub_bin,ub_bin,param0,param1);
			printf("Presetting parameters to p0 = %f, p1 = %f \n",param0,param1);
			(*fitcurve)->SetParameter(0,param0);
			(*fitcurve)->SetParameter(1,param1);
		}


		reject = true;
		int status = hmgg->Fit(*fitcurve,"L","",lb,ub);
		printf("fit status: %i \n",status);
		TFitResultPtr fitresult = hmgg->Fit(*fitcurve,"SL","",lb,ub);
			//if this gives you trouble, look here: http://root.cern.ch/root/html/TGraph.html#TGraph:Fit@1


			//now force this to be a decreasing function. If it's not, try a simpler fit function.
		if(fitresult->GetParams()[1]>0.0){ //if exponent > 0 = rising exponential
			*fitcurve = new TF1(name,flin,lb,ub,2); //fit with a line
			cout << "The fit is obviously nonsense, try with a line"<<endl;
			status = hmgg->Fit(*fitcurve,"L","",lb,ub);
			printf("fit status: %i \n",status);
			fitresult = hmgg->Fit(*fitcurve,"SL","",lb,ub);
		}
		if(fitresult->GetParams()[1]>0.0){ //if linear slope > 0 = rising line, force the slope down to zero.
			*fitcurve = new TF1("mggfit0",fcon,lb,ub,1); //fit with a constant
			cout << "The fit is still obviously nonsense, try with a constant"<<endl;
			status = hmgg->Fit(*fitcurve,"L","",lb,ub);
			printf("fit status: %i \n",status);
			fitresult = hmgg->Fit(*fitcurve,"SL","",lb,ub);
		}

		(*fitcurve)->SetName(name.Data());
		TMatrixDSym cov = fitresult->GetCovarianceMatrix();


			///Mess with Chi2
		cout << fitresult->Chi2()<<endl;
			//get chi2 per degree of freedom.
		chi2 = (*fitcurve)->GetChisquare()/((float)((*fitcurve)->GetNDF() - 1));
			//	chi2 = res->Chi2()/((float)(npoints - 3)); // to retrieve the fit chi2
		printf("chi2 from fit: %f nDOF = %f chi2/ndof-1: %f\n",(*fitcurve)->GetChisquare(),(float)((*fitcurve)->GetNDF()) ,chi2);
		printf("chi2 from ResultPointer %f, nDOF = %f, chi2/ndof-1 %f\n",fitresult->Chi2(), (float)((*fitcurve)->GetNDF()), fitresult->Chi2()/((float)((*fitcurve)->GetNDF() - 1)));
			//could also do that with Int_t TF1::GetNumberFitPoints() const

			//Do Integrals. For help, see here: http://root.cern.ch/root/html/TF1.html#TF1:IntegralError
		reject = false;
		B_integral = (*fitcurve)->Integral(tag_lb,tag_ub);
		B_integral_error = (*fitcurve)->IntegralError(tag_lb,tag_ub,fitresult->GetParams(), cov.GetMatrixArray() );
		if(B_integral <0.0){ B_integral = 0; B_integral_error = 0;}
		reject = true;
		cout<<"integral: "<<B_integral<<" +- "<<B_integral_error<<endl;
		
	}
	else{
		cout<<"Warning! Too little statistics to do the fit. Setting tag integral to zero."<<endl;
		B_integral = 0.f;
		B_integral_error = 0.f;
		chi2 = 0.f;
		(*fitcurve)->SetParameter(0,0.0);
		(*fitcurve)->SetParameter(1,0.0);
	}
}//end fitmgg_simpler



void fitmgg(TH1F* hmgg, float lb, float ub, TGraphAsymmErrors** g, TF1** fitcurve, float& chi2, float * fit_parameters, float * covarianceMx, bool preset_fitter){
	//currently orphaned and unused.

	//fit an exponential to hmgg within (lb, ub), but excluding the tag region.
	//fit_parameters = new float[2];
	//fit_parameter_errors = new float[2];
	//example call:
	//	TF1* mgg_fit_curve;
	//	TGraphErrors* g;
	//	float chi2;
	//	float fit_parameters[2];
	//	float covarianceMx[3];
	//  fitmgg(hdiPhoMass,80.,160.,&g,&mgg_fit_curve,chi2,fit_parameters, covarianceMx);
	//  then you'd do
	//  float B_integral, B_integral_error;
	//	get_bkg_integral(fit_parameters, covarianceMx, B_integral, B_integral_error);

	bool debug = false;
	if(debug) cout << "in fitmgg"<<endl;
	fit_parameters[0] = 0.; 
	fit_parameters[1] = 0.;
	covarianceMx[0] = 0.;	
	covarianceMx[1] = 0.;
	covarianceMx[2] = 0.;
	if(debug) cout << "successfully touched the fit params"<<endl;
	
	int lb_bin, ub_bin, higgslb_bin, higgsub_bin;
	int npoints = 0;
	vector<float> xvals;
	vector<float> yvals;
	vector<float> xerr;
	vector<float> yerr;
	if(debug) cout << "d"<<endl;
	
	lb_bin = hmgg->GetXaxis()->FindBin(lb)+1;
	ub_bin = hmgg->GetXaxis()->FindBin(ub)-1;
	higgslb_bin = hmgg->GetXaxis()->FindBin(lsb_ub);
	higgsub_bin = hmgg->GetXaxis()->FindBin(usb_lb);//black out the buffer too. 
//	higgslb_bin = hmgg->GetXaxis()->FindBin(tag_lb);
//	higgsub_bin = hmgg->GetXaxis()->FindBin(tag_ub);

	if(debug) cout << "e"<<endl;
	
	for (int i=lb_bin; i<=ub_bin; i++) {
			//if (i >= higgslb_bin && i <= higgsub_bin) continue;
		if (i >= higgslb_bin && i < higgsub_bin) continue; //the right end is on a bin edge. incude it. 
		xvals.push_back(hmgg->GetXaxis()->GetBinCenter(i));
		float ytemp = hmgg->GetBinContent(i)/hmgg->GetBinWidth(i);
                if(ytemp < 0.00001 && ytemp > -0.00001) ytemp+= 0.00001;//force zero to be non zero so that the fitter won't ignore it.
                yvals.push_back(ytemp);
		//yvals.push_back(hmgg->GetBinContent(i));
		xerr.push_back(0.);
		yerr.push_back(hmgg->GetBinError(i));//xxx should be made poisson errors. 
		npoints++;
	}
	
	if(debug) cout << "f"<<endl;
		//do some immoral container conversions; take this oppertunity to impose poissson errors
	float fxvals[xvals.size()];
	float fyvals[yvals.size()];
	float fxerrU[xerr.size()];
	float fxerrL[xerr.size()];
	float fyerrU[yerr.size()];
	float fyerrL[yerr.size()];
	for (int i=0;i<(int)xvals.size();i++) {
		fxvals[i]=xvals[i];
		fyvals[i]=yvals[i];
		fxerrU[i]=xerr[i];
		fxerrL[i]=xerr[i];
		if(fyvals[i] >10){
			fyerrL[i]=yerr[i];
			fyerrU[i]=yerr[i];
		}
		else{
			fyerrL[i]=UncertaintyLow(fyvals[i]);
			fyerrU[i]=UncertaintyHi(fyvals[i]);
		}
	}
	if(debug) cout << "g"<<endl;
	*g = new TGraphAsymmErrors(xvals.size(),fxvals,fyvals,fxerrL,fxerrU,fyerrL,fyerrU);
	if(debug) cout << "h"<<endl;

		//do fit
	*fitcurve = new TF1("mggfit","[0]*x^[1]",lb,ub);
	//*fitcurve = new TF1("mggfit","expo",lb,ub);
	if(debug) cout << "i"<<endl;	
	
	if( preset_fitter){
		/*prepare the fit result*/
		float param0, param1;
		find_preset_params_powerlaw(hmgg,lb_bin,higgslb_bin,higgsub_bin,ub_bin,param0,param1);
		printf("Presetting parameters to p0 = %f, p1 = %f \n",param0,param1);
		(*fitcurve)->SetParameter(0,param0);
		(*fitcurve)->SetParameter(1,param1);
	}
		//form y = p0*x^p1
	int status = (*g)->Fit(*fitcurve,"","",lb,ub);
	printf("fit status: %i \n",status);
	TFitResultPtr fitresult = (*g)->Fit(*fitcurve,"SW","",lb,ub);

	//new
	//now force this to be a decreasing function. If it's not, try a simpler fit function. 
	if(fitresult->GetParams()[1]>0.0){ //if exponent > 0 = rising exponential 
		*fitcurve = new TF1("mggfit1","pol1",lb,ub); //fit with a line
		cout << "The fit is obviously nonsense, try with a line"<<endl;
		status = (*g)->Fit(*fitcurve,"","",lb,ub);
		printf("fit status: %i \n",status);
		fitresult = (*g)->Fit(*fitcurve,"SW","",lb,ub);
	}
	if(fitresult->GetParams()[1]>0.0){ //if linear slope > 0 = rising line, force the slope down to zero. 
		*fitcurve = new TF1("mggfit0","pol0",lb,ub); //fit with a constant
		cout << "The fit is still obviously nonsense, try with a constant"<<endl;
		status = (*g)->Fit(*fitcurve,"","",lb,ub);
		printf("fit status: %i \n",status);
		fitresult = (*g)->Fit(*fitcurve,"SW","",lb,ub);
	}
		//if this gives you trouble, look here:
		//http://root.cern.ch/root/html/TGraph.html#TGraph:Fit@1
	cout << fitresult->Chi2()<<endl;
	
	TMatrixDSym cov = fitresult->GetCovarianceMatrix(); 
	if(debug) cout << "attempt to access covarieance matrix elements"<<endl;
	covarianceMx[0] = cov[0][0];
	covarianceMx[1] = cov[0][1];
	covarianceMx[2] = cov[1][1];
	if(debug) cout << "That worked! "<< covarianceMx[0] <<endl;
	
	cout<<"Using TFitResultPtr and its integral function:"<<endl; 
		//TMatrixDSym cov = fitresult->GetCovarianceMatrix();
	double ie = (*fitcurve)->IntegralError(tag_lb,tag_ub,fitresult->GetParams(), cov.GetMatrixArray() );
	cout<<"** integral: "<<(*fitcurve)->Integral(tag_lb,tag_ub)<<" +- "<<ie<<endl;
	
		//get chi2 per degree of freedom. 
	chi2 = (*fitcurve)->GetChisquare()/((float)((*fitcurve)->GetNDF() - 1));
		//	chi2 = res->Chi2()/((float)(npoints - 3)); // to retrieve the fit chi2
		//printf("chi2 from fit: %f \n",chi2);
	if(debug) printf("chi2 from fit: %f from ResultPointer %f\n",chi2,fitresult->Chi2()/((float)((*fitcurve)->GetNDF() - 1)));
		//these come out exactly the same :) but it acts like npoints -3 is too big. 

	

		//could also do that with Int_t TF1::GetNumberFitPoints() const
		//or maybe TF1::GetNumberFreeParameters, but it should be the same thing (check)
	printf("npoints -- my count: %i GetNumberFitPoints %i, 	GetNumberFreeParameters %i GetNDF %i\n",
		   npoints, (*fitcurve)->GetNumberFitPoints(),	(*fitcurve)->GetNumberFreeParameters(), (*fitcurve)->GetNDF());
		//xxx big disagreement here
		//my measure: 47 GetNumberFitPoints 36, 	GetNumberFreeParameters 2 GetNDF 34
		//so indeed GetNDF = GetNumberFitPoints - GetNumberFreeParameters.
		//And I want to use GetNDF - 1. 
	
		//get params
	fit_parameters[0] = (*fitcurve)->GetParameter(0);
    if(debug) printf("filling param0 with %f \n",(*fitcurve)->GetParameter(0));
	fit_parameters[1] = (*fitcurve)->GetParameter(1);
	if(debug) printf("filling param1 with %f \n",(*fitcurve)->GetParameter(1));
//	fit_parameter_errors[0] = (*fitcurve)->GetParError(0);
//	fit_parameter_errors[1] = (*fitcurve)->GetParError(1);
//	printf("params set, exiting fitmgg func\n");
	
}//end fitmgg

	//obsolete and statistically bad. DO NOT USE!
void fitmgg_simple(TH1F* hmgg, float lb, float ub, TGraphAsymmErrors** g, TF1** fitcurve, float& chi2, float & B_integral, float & B_integral_error, TString type, bool preset_fitter){
		//fit an power law to hmgg within (lb, ub), but excluding the tag region. 
		//example call:
		//	TF1* mgg_fit_curve;
		//	TGraphAsymmErrors* g				    //for return 
		//	float chi2, B_integral, B_integral_error;   //for return vals
		//  fitmgg_simple(hdiPhoMass,80.,160.,&g,&mgg_fit_curve,chi2, B_integral, B_integral_error);
		//  //and that's all, no need for the get_bkg_integral function at all!
	bool debug = false;
	if(debug) cout << "in fitmgg_simple"<<endl;
	
	int lb_bin, ub_bin, higgslb_bin, higgsub_bin;
	int npoints = 0;
	vector<float> xvals;
	vector<float> yvals;
	vector<float> xerr;
	vector<float> yerr;
	if(debug) cout << "d"<<endl;
	
	lb_bin = hmgg->GetXaxis()->FindBin(lb)+1;
	ub_bin = hmgg->GetXaxis()->FindBin(ub)-1;
	higgslb_bin = hmgg->GetXaxis()->FindBin(lsb_ub);
	higgsub_bin = hmgg->GetXaxis()->FindBin(usb_lb);//this blacks out the buffer area and higgs tag area
	if(debug) cout << "e"<<endl;
	
	for (int i=lb_bin; i<=ub_bin; i++) {
			//if (i >= higgslb_bin && i <= higgsub_bin) continue;
		if (i >= higgslb_bin && i < higgsub_bin) continue; //the right end is on a bin edge. incude it. 
		xvals.push_back(hmgg->GetXaxis()->GetBinCenter(i));
		float ytemp = hmgg->GetBinContent(i)/hmgg->GetBinWidth(i); 
			//dividing by bin width converts from histogram to graph. else area is screwed up
		if(ytemp < 0.00001 && ytemp > -0.00001) ytemp+= 0.00001;//force zero to be non zero so that the fitter won't ignore it.
		yvals.push_back(ytemp); //yvals.push_back(hmgg->GetBinContent(i)/hmgg->GetBinWidth(i));
		xerr.push_back(0.);
		yerr.push_back(hmgg->GetBinError(i)/hmgg->GetBinWidth(i));//xxx should be made poisson errors.
		npoints++;
	}
	
	if(debug) cout << "f"<<endl;
		//do some immoral container conversions.Take this oppertunity to impose poisson errors
        float fxvals[xvals.size()];
        float fyvals[yvals.size()];
        float fxerrU[xerr.size()];
        float fxerrL[xerr.size()];
        float fyerrU[yerr.size()];
        float fyerrL[yerr.size()];
        for (int i=0;i<(int)xvals.size();i++) {
                fxvals[i]=xvals[i];
                fyvals[i]=yvals[i];
                fxerrU[i]=xerr[i];
                fxerrL[i]=xerr[i];
                if(fyvals[i] >10){
                        fyerrL[i]=yerr[i];
                        fyerrU[i]=yerr[i];
                }
                else{
                        fyerrL[i]=UncertaintyLow(fyvals[i]);
                        fyerrU[i]=UncertaintyHi(fyvals[i]);
                }
        }
	if(debug) cout << "g"<<endl;
	*g = new TGraphAsymmErrors(xvals.size(),fxvals,fyvals,fxerrL,fxerrU,fyerrL,fyerrU);
	if(debug) cout << "h"<<endl;
	
		//do fit
	TString name = "mgg";
	name += type;
	name += "fit";
	*fitcurve = new TF1(name,"[0]*x^[1]",lb,ub);
	//*fitcurve = new TF1(name,"expo",lb,ub);
	//*fitcurve = new TF1("mggfit","expo",lb,ub);
	if(debug) cout << "i"<<endl;	
	
	if( check_statistics(hmgg,lb_bin,higgslb_bin,higgsub_bin,ub_bin)){
		if( preset_fitter){
			/*prepare the fit result*/
			float param0, param1;
			find_preset_params_powerlaw(hmgg,lb_bin,higgslb_bin,higgsub_bin,ub_bin,param0,param1);
			printf("Presetting parameters to p0 = %f, p1 = %f \n",param0,param1);
			(*fitcurve)->SetParameter(0,param0);
			(*fitcurve)->SetParameter(1,param1);
		}
			//form y = p0*x^p1
		int status = (*g)->Fit(*fitcurve,"","",lb,ub);
		printf("fit status: %i \n",status);
		TFitResultPtr fitresult = (*g)->Fit(*fitcurve,"SW","",lb,ub);
			//if this gives you trouble, look here:
			//http://root.cern.ch/root/html/TGraph.html#TGraph:Fit@1

			//new
			//now force this to be a decreasing function. If it's not, try a simpler fit function. 
		if(fitresult->GetParams()[1]>0.0){ //if exponent > 0 = rising exponential 
			*fitcurve = new TF1("mggfit1","pol1",lb,ub); //fit with a line
			cout << "The fit is obviously nonsense, try with a line"<<endl;
			status = (*g)->Fit(*fitcurve,"","",lb,ub);
			printf("fit status: %i \n",status);
			fitresult = (*g)->Fit(*fitcurve,"SW","",lb,ub);
		}
		if(fitresult->GetParams()[1]>0.0){ //if linear slope > 0 = rising line, force the slope down to zero. 
			*fitcurve = new TF1("mggfit0","pol0",lb,ub); //fit with a constant
			cout << "The fit is still obviously nonsense, try with a constant"<<endl;
			status = (*g)->Fit(*fitcurve,"","",lb,ub);
			printf("fit status: %i \n",status);
			fitresult = (*g)->Fit(*fitcurve,"SW","",lb,ub);
		}
		(*fitcurve)->SetName(name.Data());
		cout << fitresult->Chi2()<<endl;

		if(debug) cout<<"Using TFitResultPtr and its integral function:"<<endl;
		TMatrixDSym cov = fitresult->GetCovarianceMatrix();
		B_integral = (*fitcurve)->Integral(tag_lb,tag_ub);
		B_integral_error = (*fitcurve)->IntegralError(tag_lb,tag_ub,fitresult->GetParams(), cov.GetMatrixArray() );
			//see here: http://root.cern.ch/root/html/TF1.html#TF1:IntegralError
		cout<<"integral: "<<B_integral<<" +- "<<B_integral_error<<endl;

			//get chi2 per degree of freedom.
		chi2 = (*fitcurve)->GetChisquare()/((float)((*fitcurve)->GetNDF() - 1));
			//	chi2 = res->Chi2()/((float)(npoints - 3)); // to retrieve the fit chi2
			//printf("chi2 from fit: %f \n",chi2);
		if(debug) printf("chi2 from fit: %f from ResultPointer %f\n",chi2,fitresult->Chi2()/((float)((*fitcurve)->GetNDF() - 1)));
			//these come out exactly the same :) but it acts like npoints -3 is too big.



			//could also do that with Int_t TF1::GetNumberFitPoints() const
			//or maybe TF1::GetNumberFreeParameters, but it should be the same thing (check)
		printf("npoints -- my count: %i GetNumberFitPoints %i, 	GetNumberFreeParameters %i GetNDF %i\n",
			   npoints, (*fitcurve)->GetNumberFitPoints(),	(*fitcurve)->GetNumberFreeParameters(), (*fitcurve)->GetNDF());
	}
	else{
		cout<<"Warning! Too little statistics to do the fit. Setting tag integral to zero."<<endl;
		cout<<"That should mean there's no events in either sideband"<<endl;
		B_integral = 0.f;
		B_integral_error = 0.f;
		chi2 = -1.f;
		(*fitcurve)->SetParameter(0,0.0);
		(*fitcurve)->SetParameter(1,0.0);
	}
		//xxx big disagreement here
		//my measure: 47 GetNumberFitPoints 36, 	GetNumberFreeParameters 2 GetNDF 34
		//so indeed GetNDF = GetNumberFitPoints - GetNumberFreeParameters.
		//And I want to use GetNDF - 1. 
}//end fitmgg_simple

void find_preset_params(TH1F* hmgg,int lb_bin,int higgslb_bin,int higgsub_bin, int ub_bin,float &param0,float &param1){
	//makes a guess at what the exponential fit parameters should be
	int npoints_l = 0;
	int npoints_u = 0;
	float avg_l = 0.;
	float avg_u = 0.;
	float avgX_l = 0.;
	float avgX_u = 0.;
	for (int i=lb_bin; i<higgslb_bin; i++) {
		avg_l += hmgg->GetBinContent(i);
		avgX_l += hmgg->GetXaxis()->GetBinCenter(i);
		npoints_l++;
	}
	avg_l /= ((float) npoints_l);
	avgX_l /= ((float) npoints_l);
	printf("avg_l %f, avgX_l %f\n",avg_l,avgX_l);
	for (int i=higgsub_bin+1; i<=ub_bin; i++) {
		avg_u += hmgg->GetBinContent(i); avgX_u += hmgg->GetXaxis()->GetBinCenter(i); npoints_u++; } avg_u /= ((float) npoints_u); avgX_u /= ((float) npoints_u);
	printf("avg_u %f, avgX_u %f\n",avg_u,avgX_u);

	if (avg_l > 0.f && avg_u > 0.f && avgX_u != avgX_l) {
		float l1 = log(avg_l);
		float l2 = log(avg_u);
		float det = 1./(avgX_u - avgX_l);
		param0 = det*(avgX_u*l1 - avgX_l*l2);
		param1 = det*(-l1 + l2);
	}
	else{
		param0 = 1.f;
		param1 = 0.f;
	}
}

void find_preset_params_powerlaw(TH1F* hmgg,int lb_bin,int higgslb_bin,int higgsub_bin, int ub_bin,float &param0,float &param1){
        //makes a guess at what the power law fit parameters should be
        int npoints_l = 0;
        int npoints_u = 0;
        float avg_l = 0.;
        float avg_u = 0.;
        float avgX_l = 0.;
        float avgX_u = 0.;

	if (avg_l<0.0001) avg_l = 0.1;
	if (avg_u<0.0001) avg_u = 0.1;

	//take averages of lower and upper side bands -> one point for upper, one point for lower
        for (int i=lb_bin; i<higgslb_bin; i++) {
                avg_l += hmgg->GetBinContent(i);
                avgX_l += hmgg->GetXaxis()->GetBinCenter(i);
                npoints_l++;
        }
        avg_l /= ((float) npoints_l);
        avgX_l /= ((float) npoints_l);
        printf("avg_l %f, avgX_l %f\n",avg_l,avgX_l);
        for (int i=higgsub_bin+1; i<=ub_bin; i++) {
                avg_u += hmgg->GetBinContent(i);
                avgX_u += hmgg->GetXaxis()->GetBinCenter(i);
                npoints_u++;
        }
        avg_u /= ((float) npoints_u);
        avgX_u /= ((float) npoints_u);
        printf("avg_u %f, avgX_u %f\n",avg_u,avgX_u);
	//averages made
	//you now have the average x and y of the lower and upper side bands, effectively two points.
	//draw a curve between them. 
        if (avgX_u != avgX_l) {
		
                param1 = (log(avg_l) - log(avg_u))/(log(avgX_l) - log(avgX_u));
                param0 = avg_l/pow(avgX_l, param1);
        }
        else{
        	printf("ERROR!! avgX_u == avgX_l !! INVESTIGATE!!\n"); 
                param0 = 1.f;
                param1 = 0.f;
        }
}

bool check_statistics(TH1F* hmgg,int lb_bin,int higgslb_bin,int higgsub_bin, int ub_bin){
		//if both side bands are empty, return false.
	bool USB_IS_OK = hmgg->Integral(lb_bin,higgslb_bin) > 0.0001f;
	bool LSB_IS_OK = hmgg->Integral(ub_bin,higgsub_bin) > 0.0001f;
	if ((!LSB_IS_OK) && (!USB_IS_OK) ) cout<<"Warning! Both sidebands are empty"<<endl;
	else if(!LSB_IS_OK)cout<<"Lower sideband is empty"<<endl;
	else if(!USB_IS_OK)cout<<"Upper sideband is empty"<<endl;
	return USB_IS_OK || LSB_IS_OK;
}

	//made obsolete by fitmgg_simple
void get_bkg_integral(float* fit_parameters, float* covarianceMx, float & B_integral, float & B_integral_error){
		//currently orphaned, not used 
		//fit_parameters = values of fit parameters. y = exp(fit_parameters[0] + fit_parameters[1]*mgg)
		//fit_parameter_errors are the fitter's uncertaintites in those fit_parameters.
		//B_integral is output; it's the integral of the background int the tag region
		//B_integral_error is output; it's the uncertainty in that integral from the uncertainty in the fit params. 
	float centralvals[4];
	centralvals[0] = fit_parameters[0];
	centralvals[1] = fit_parameters[1];
	centralvals[2] = tag_lb;
	centralvals[3] = tag_ub;
//  float uncertainties[4];
//	uncertainties[0] = fit_parameter_errors[0];
//	uncertainties[1] = fit_parameter_errors[1];
//	uncertainties[2] = 0.;
//	uncertainties[3] = 0.;
	//cout<<"C"<<endl;
	//bool zero_limited[4] = {false, false, false,false};
	//printf("withing get_bkg_integral: bint = %f, binterr = %f\n",B_integral,B_integral_error);	
	B_integral = expo_integral(centralvals);
	B_integral = expo_integral(centralvals);
	//cout<<"D"<<endl;
	//B_integral_error = GetError(expo_integral,4, centralvals, uncertainties,zero_limited); //replace me
	B_integral_error = GetError_2correlated(expo_integral, centralvals, covarianceMx, 4);
	//printf("withing get_bkg_integral: bint = %f, binterr = %f\n",B_integral,B_integral_error);	
	if(B_integral < 0.0){
		B_integral = 0;
		B_integral_error = 0;
	}
}


	//made obsolete by fitmgg_simple
float expo_integral(float * params){
		//currently orphaned, unused

		//	params[0] = p0;
		//	params[1] = p1;
		//	params[2] = x_low;
		//	params[3] = x_hi;
		//return TMath::Exp(p0)*p1*(TMath::Exp(-x_low/p1) - TMath::Exp(-x_hi/p1)); //but I expect p1 to be negative, so that's no good. 
		//	return TMath::Exp(p0)*p1*(TMath::Exp(x_low/p1) - TMath::Exp(x_hi/p1));
	//printf("0 %f 1 %f 2 %f 3 %f \n",params[0],params[1],params[2],params[3]);//xxx
	//if(params[1]<0.00001 && params[1]>-0.00001)return 0.f;
	//cout<<TMath::Exp(params[3]*params[1])<<endl;
	//cout<<TMath::Exp(params[2]*params[1])<<endl;
	//cout<<TMath::Exp(params[0])/params[1]<<endl;
	//cout<<(TMath::Exp(params[0])/params[1])*(TMath::Exp(params[3]*params[1]) - TMath::Exp(params[2]*params[1]))<<endl;

	return (TMath::Exp(params[0])/params[1])*(TMath::Exp(params[3]*params[1]) - TMath::Exp(params[2]*params[1]));
}

void find_bkg_with_fit(TH1F** h, float B_integral, float B_integral_error, float lsb_int, float usb_int){
		//Take In an array of TH1F's. 
		//calculate the background, from [0] and [2] and store it in [3]
	if (B_integral <=0.0 || lsb_int <= 0.0 || usb_int <= 0.0)
		printf("Warning: find_bkg_with_fit recieves B_integral = %.2f +- %.2f and lsb_int = %.2f, usb = %.2f %s\n",B_integral,B_integral_error,lsb_int,usb_int,h[3]->GetName());
//	else printf("         find_bkg_with_fit is ok\n");


		//Scale side bands and set error
	for (int ibin = 0; ibin <= h[5]->GetNbinsX()+1; ibin++) {
			//Scale them
		if(lsb_int>0) h[5]->SetBinContent(ibin,(h[0]->GetBinContent(ibin)*B_integral/lsb_int));
		else h[5]->SetBinContent(ibin,0.);
		if(usb_int>0)h[6]->SetBinContent(ibin,(h[2]->GetBinContent(ibin)*B_integral/usb_int));
		else h[6]->SetBinContent(ibin,0.);
		
			//SetErrors
		if(h[0]->GetBinContent(ibin) > 0 && lsb_int >0 && B_integral>0){
			h[5]->SetBinError(ibin, h[5]->GetBinContent(ibin)*sqrt(pow((h[0]->GetBinError(ibin)/h[0]->GetBinContent(ibin)),2) +
												  (1./lsb_int)+pow(B_integral_error/B_integral,2)));
//			printf("lsb bin %i bincontentfracerr %f lsbfracerr %f integral fractional error %f\n",ibin,(h[0]->GetBinError(ibin)/h[0]->GetBinContent(ibin)),sqrt(1./lsb_int),B_integral_error/B_integral);
		}
		else {
			h[5]->SetBinError(ibin,h[5]->GetBinContent(ibin));
//			printf("lsb bin %i something is zero bin content %f sideband %f integral %f\n",ibin,h[0]->GetBinContent(ibin),lsb_int,B_integral);
		}
						  
		if(h[2]->GetBinContent(ibin) > 0 && usb_int >0 && B_integral>0)
			h[6]->SetBinError(ibin, h[6]->GetBinContent(ibin)*sqrt(pow((h[2]->GetBinError(ibin)/h[2]->GetBinContent(ibin)),2) +
												  (1./usb_int)+pow(B_integral_error/B_integral,2)));
		else h[6]->SetBinError(ibin, h[6]->GetBinContent(ibin));
	}
	//h[5]->Sumw2(); h[6]->Sumw2();

	//find combined background
	h[3]->Add(h[5],h[6]);
	h[3]->Scale(0.5);//finish the average
	printf("for bin 2, Expecting bin error %f and get %f\n",sqrt(0.25*pow(h[5]->GetBinError(2),2)+ 0.25*pow(h[6]->GetBinError(2),2)) , h[3]->GetBinError(2) );//debug xxx
	for (int ibin = 0; ibin <= h[3]->GetNbinsX()+1; ibin++) { //make error for combined bkg. 
		h[3]->SetBinError(ibin,sqrt(pow(h[3]->GetBinError(ibin),2)+pow(0.5*(h[5]->GetBinContent(ibin) - h[6]->GetBinContent(ibin)),2))); //add systematic error

		if(fabs(h[3]->GetBinContent(ibin) )< 0.0001 ) h[3]->SetBinError(ibin, 0.5*B_integral/lsb_int ); //insert an uncertainty on zero = lsb has 1 and usb has 0. 
	}
	h[4]->Add(h[1],h[3],1.,-1.); //subtract the bkg.

		//you should check that these are producing something sensible for their errors.
	h[7] = (TH1F*)h[5]->Clone(h[7]->GetName());
	h[7]->Reset();
	h[7]->Divide(h[5],h[6]); //lsb_over_usb
//	printf("divide %f/%f = %f, outcome is %f\n",h[5]->GetBinContent(1),h[6]->GetBinContent(1),h[5]->GetBinContent(1)/h[6]->GetBinContent(1),h[7]->GetBinContent(1));
	h[8] = (TH1F*)h[1]->Clone(h[8]->GetName());
	h[8]->Reset();
	h[8]->Divide(h[1],h[3]);//tag_over_bkg
//	printf("divide %f/%f = %f, outcome is %f\n",h[1]->GetBinContent(1),h[3]->GetBinContent(1),h[1]->GetBinContent(1)/h[3]->GetBinContent(1),h[8]->GetBinContent(1));
	fixNAN(h[7]);
	fixNAN(h[8]);
}

void find_bkg(TH1F** h){
		//used in SusyMainAna for a dumb simple way of getting a dummy background

		//Take In an array of TH1F's.
		//calculate the background, from [0] and [2] and store it in [3]
		//this assumes the mgg dist is linear, so it will always guess low.
	for(int i=0;i<nPhoMassAndBkgDists;i++) h[i]->Sumw2();
	//for(int i=0;i<nPhoMassAndBkgDists;i++) cout<<"hist "<<i<<" nbins "<<h[i]->GetXaxis()->GetNbins()<<endl;
	//for(int i=0;i<nPhoMassAndBkgDists;i++){
		//TAxis* x = h[i]->GetXaxis();
		//cout<<"hist "<<i<<" goes from "<<x->GetBinLowEdge(x->GetFirst())<<" to "<<x->GetBinUpEdge(x->GetLast())<<endl;
	//}
	h[3]->Add(h[0],h[2],mHwidth/(lsb_ub-lsb_lb),mHwidth/(usb_ub-usb_lb));//apply weights to adjust for the difference in region width
	h[3]->Scale(0.5);//finish the average
	h[4]->Add(h[1],h[3],1.,-1.); //subtract the bkg.
		//string s_MassBkgDists[nPhoMassAndBkgDists] = {"0 lowSB","1 tag","2 upperSB","3 bkg","4 tag_subbkg","5 lowSB_scaled","6 upperSB_scaled","7 lsb_over_usb","8 tag_over_bkg"};
	h[5] = (TH1F*)h[0]->Clone(h[5]->GetName());
	h[5]->Scale(mHwidth/(lsb_ub-lsb_lb)); //lowSB_scaled
	h[6] = (TH1F*)h[1]->Clone(h[6]->GetName());
	h[6]->Scale(mHwidth/(usb_ub-usb_lb)); //upperSB_scaled
	h[7] = (TH1F*)h[5]->Clone(h[7]->GetName());
	h[7]->Divide(h[6]);//lsb_over_usb
	h[8] = (TH1F*)h[1]->Clone(h[8]->GetName());
	h[8]->Divide(h[3]);//tag_over_bkg

}//obsolete; end find_bkg

class KinematicVar{
	public:
	KinematicVar(){}
	//KinematicVar(string _tag):tag(_tag){}
	KinematicVar(string _tag, string _titles, string _xlabels,bool _useCustomBinning, int _nbins, float min = 0, float max = -1):tag(_tag),titles(_titles),xlabels(_xlabels),useCustomBinning(_useCustomBinning),nbins(_nbins),hmin(min),hmax(max){ 
		CustomBinning = new float[nbins+1];
	} 
	~KinematicVar(){}

	string tag;
	string titles;
	string xlabels;
	bool useCustomBinning;
	int nbins;
	float hmin;
	float hmax;
	float *CustomBinning; //this explodes. 
	void usearray(float* f);
	//void printarray();
};
void KinematicVar::usearray(float* f){
	for(int i = 0;i<=nbins;i++) CustomBinning[i] = f[i];
}
/*void KinematicVar::printarray(){
	printf("{");
	for(int i = 0;i<=nbins;i++) printf("%f, ",CustomBinning[i]);
	printf("}\n");
}*/

typedef std::map<string,KinematicVar*> LabelKinVars;

LabelKinVars setupKinematicVar(){
//will consider the list of kinematic variables in params_arg and 
//make a map from kinvars to *KinematicVar
	LabelKinVars allKinVars;
	//first compose an object for everything we've ever defined. 

	{ KinematicVar* temp = new KinematicVar("MET","Missing Transverse Energy","#slash{E}_{T} (GeV)",true,5);
	//KinematicVar* temp = new KinematicVar("MET","Missing Transverse Energy","#slash{E}_{T} (GeV)",false,6,0,150);
	float a[] = {0,20,30,40,60,140};
	temp->usearray(a);
	allKinVars["MET"] = temp; }

	{ KinematicVar* temp = new KinematicVar("ST","Scalar Sum of all Calorimeter Energy","#SigmaE_{E}_{T} (GeV)",true,4);
	// KinematicVar* temp = new KinematicVar("ST","Scalar Sum of all Calorimeter Energy","#SigmaE_{E}_{T} (GeV)",false,30,0,1500);
	float a[] = {0,250,350,550,1000};
	temp->usearray(a);
	allKinVars["ST"] = temp; }

	{ KinematicVar* temp = new KinematicVar("HT","Scalar Sum of all Hadronic Transverse Energy","#SigmaH_{T} (GeV)",true,5);
	 //KinematicVar* temp = new KinematicVar("HT","Scalar Sum of all Hadronic Transverse Energy","#SigmaH_{T} (GeV)",false,20,0,1000);
	float a[] = {0,150,250,350,500,1000};
	temp->usearray(a);
	allKinVars["HT"] = temp; }

	allKinVars["LHT"] = new KinematicVar("LHT","Scalar Sum of Light Hadronic Transverse Energy", "#SigmaH_{T} (GeV)", false, 3.f, 0.f, 300.f);

	{ KinematicVar* temp = new KinematicVar("Bt",  "Scalar Sum of all B-jet Transverse Energy", "#SigmaB_{T} (GeV)",true, 10);
        //allKinVars["Bt"] = new KinematicVar("Bt",  "Scalar Sum of all B-jet Transverse Energy", "#SigmaB_{T} (GeV)",true, 20, 0.f, 800.f);
	float a[] = {0,40,80,120,160,200,240,280,320,480,800};
	temp->usearray(a);
	allKinVars["Bt"] = temp; }
    
        { KinematicVar* temp = new KinematicVar("BTL",  "Scalar Sum of Exclusively Loose B-jet Transverse Energy", "#SigmaB_{T} (GeV)",true, 3);
        //allKinVars["BTL"] = new KinematicVar("BTL",  "Scalar Sum of Exclusively Loose B-jet Transverse Energy", "#SigmaB_{T} (GeV)",true, 20.f, 0.f, 800.f); 
	float a[] = {0,100,200,300};//, 6 bins
	temp->usearray(a);
        allKinVars["BTL"] = temp;}

	{ KinematicVar* temp = new KinematicVar("BTM",  "Scalar Sum of Exclusively Medium B-jet Transverse Energy", "#SigmaB_{T} (GeV)",true, 3);
        //allKinVars["BTM"] = new KinematicVar("BTM",  "Scalar Sum of Exclusively Medium B-jet Transverse Energy", "#SigmaB_{T} (GeV)",true, 20.f, 0.f, 800.f);
	float a[] = {0,100,200,300};// 6 bins
	temp->usearray(a);
        allKinVars["BTM"] = temp;}

	{ KinematicVar* temp = new KinematicVar("BTT",  "Scalar Sum of B-jeusively Tight Transverse Energy", "#SigmaB_{T} (GeV)",true, 3);
        //allKinVars["BTT"] = new KinematicVar("BTT",  "Scalar Sum of B-jeusively Tight Transverse Energy", "#SigmaB_{T} (GeV)",true, 20.f, 0.f, 800.f);
	float a[] = {0,100,200,300};// 3 bins
	temp->usearray(a);
        allKinVars["BTT"] = temp;}

	{ KinematicVar* temp = new KinematicVar("MHT",  "Missing Transverse Hadronic Energy", "#slashH_{T} (GeV)",true, 5);
        //allKinVars["MHT"] = new KinematicVar("MHT",  "Missing Transverse Hadronic Energy", "#slashH_{T} (GeV)",true, 20.f, 0.f, 250.f);
	float a[] = {0,40,80,120,160,260};//  
	temp->usearray(a);
        allKinVars["MHT"] = temp;}

	{ KinematicVar* temp = new KinematicVar("PtGG",  "Di-Photon Pt Sectrum", "P_{t}^{#gamma #gamma} (GeV)",true, 4);
        //allKinVars["PtGG"] = new KinematicVar("PtGG",  "Di-Photon Pt Sectrum", "P_{t}^{#gamma #gamma} (GeV)",true, 25., 0.f, 250.f);
//	float a[] = {0,10,20,30,40,50,60,70,80,90,120,150,180,210,240};// 14 bins
		float a[] = {0,30,60,90,120};
		temp->usearray(a);
        allKinVars["PtGG"] = temp;}

	allKinVars["LepT"] = new KinematicVar("LepT","Leptonic Transverse Energy", "Lep #sigmaE_{T} (GeV)", false, 20.f, 0.f, 150.f),

	allKinVars["LepPt"] = new KinematicVar("LepT","Lepton Transverse Energy", "Lepton E_{T} (GeV)", false, 20.f, 0.f, 150.f),

        allKinVars["phoPt0"] = new KinematicVar("phoPt0",  "", "P_{t}^{#gamma0} (GeV)",false, 4, 0.f, 144);

        allKinVars["phoPt1"] = new KinematicVar("phoPt1",  "", "P_{t}^{#gamma1} (GeV)",false, 4, 0.f, 88);
        
        allKinVars["PhiGG"] = new KinematicVar("PhiGG",  "Phi of the di-photon system", "#phi^{#gamma #gamma}",false, 18, 0.f, 6.2832);

        allKinVars["phoPhi"] = new KinematicVar("phoPhi",  "", "#phi^{#gamma}",false, 18, 0.f, 6.2832);

        allKinVars["phoPhi1"] = new KinematicVar("phoPhi1",  "", "#phi^{#gamma1}",false, 18, 0.f, 6.2832);

        allKinVars["EtaGG"] = new KinematicVar("EtaGG",  "Eta of the di-photon system", "#eta^{#gamma #gamma}",false, 26, -2.6, 2.6);

        allKinVars["phoEta"] = new KinematicVar("phoEta",  "", "#eta^{#gamma0}",false, 26, -2.6, 2.6);

        allKinVars["phoEta1"] = new KinematicVar("phoEta1",  "", "#eta^{#gamma1}",false, 26, -2.6, 2.6);

        allKinVars["phoEtaMax"] = new KinematicVar("phoEtaMax",  "Max Eta of the Two Photons", "Max #eta^{#gamma}",false, 13, 0.0, 2.6);

        allKinVars["phoEtaMin"] = new KinematicVar("phoEtaMin",  "Min Eta of the Two Photons", "Min #eta^{#gamma}",false, 13, 0.0, 2.6);

        allKinVars["phoDEta"] = new KinematicVar("phoDEta",  "", "#Delta #eta^{#gamma #gamma}",false, 13, 0.0f, 2.6);

        allKinVars["phoMinR9"] = new KinematicVar("phoMinR9",  "Min R9 of the Two Photons", "Min R9",false, 30, 0.4, 1.0);

        allKinVars["nJets"] = new KinematicVar("nJets",  "", "Number of Jets",false, 8, 0.f, 8);
        
        allKinVars["nBjets"] = new KinematicVar("nBjets",  "", "Number of B-jets",false, 5, 0.f, 5);

        allKinVars["Bness1"] = new KinematicVar("Bness1",  "", "Sum(sqrt(jet CSV))",false, 8, 0.f, 4);
        
        allKinVars["bestMjj"] = new KinematicVar("bestMjj",  "", "Closet dijet mass to M_{H}",false, 30, 0.f, 225);
        
        allKinVars["bestMbb"] = new KinematicVar("bestMbb",  "", "Closet di-B-jet mass to M_{H}",false, 30, 0.f, 225);
        
        allKinVars["allMjj"] = new KinematicVar("allMjj",  "", "All combinations of dijet mass",false, 30, 0.f, 225);
        
        allKinVars["allMbb"] = new KinematicVar("allMbb",  "", "All combinations of di-B-jet mass",false, 30, 0.f, 225);
        
        allKinVars["nLep"] = new KinematicVar("nLep",  "", "Number of Leptons",false, 6, 0.f, 6);
        
        allKinVars["nMu"] = new KinematicVar("nMu",  "", "Number of Muons",false, 5, 0.f, 5);

        allKinVars["nEle"] = new KinematicVar("nEle",  "", "Number of Electrons",false, 5, 0.f, 5);

        allKinVars["Mleplep"] = new KinematicVar("Mleplep",  "", "M_{dileptons}",false, 30, 0.f, 120);

        allKinVars["MTphoMET"] = new KinematicVar("MTphoMET",  "", "M_{t}^{#gamma0 MET} (GeV)",false, 30, 0.f, 300.f);

        allKinVars["MTpho1MET"] = new KinematicVar("MTpho1MET",  "", "M_{t}^{#gamma1 MET} (GeV)",false, 30, 0.f, 300.0);

        allKinVars["cosThetaStar"] = new KinematicVar("cosThetaStar",  "Cos of angle between the two Photons in their center of mass frame", "Cos(#theta*)",false, 10, 0.0f, 1.0);

        allKinVars["phoDPhi"] = new KinematicVar("phoDPhi",  "", "#Delta#phi(#gamma #gamma)",false, 12, 0.f, 3.1416);

        allKinVars["dPhiPhoMet"] = new KinematicVar("dPhiPhoMet",  "", "#Delta#phi(#gamma0, #slash{E}_{T})",false, 12, 0.f, 3.1416);

        allKinVars["dPhiPho1Met"] = new KinematicVar("dPhiPho1Met",  "", "#Delta#phi(#gamma1, #slash{E}_{T})",false, 12, 0.f, 3.1416);

        allKinVars["PitGG"] = new KinematicVar("PitGG",  "", "#Pi_{t}",false, 20, 0.f, 2.f);

        { KinematicVar* temp = new KinematicVar("jetPt",  "", "Jet P_{t} (GeV)",true, 9);
        //allKinVars["jetPt"] = new KinematicVar("jetPt",  "", "Jet P_{t} (GeV)",true, 16, 0.f, 240.f);
	float a[] = {0,30,45,60,75,90,120,150,195,240};// 9 bins //theres no need to rebin but this would be good. 
	temp->usearray(a);
        allKinVars["jetPt"] = temp;}
        
        allKinVars["jetPhi"] = new KinematicVar("jetPhi",  "", "Jet #phi",false, 10, 0.f, 6.2832);
        
        allKinVars["jetEta"] = new KinematicVar("jetEta",  "", "Jet #eta",false, 26, -2.6, 2.6);
        allKinVars["jetEtaMin"] = new KinematicVar("jetEtaMin",  "", "Min Jet #eta",false, 26, -2.6, 2.6);
        
        allKinVars["dPhiJetMet"] = new KinematicVar("dPhiJetMet",  "", "#Delta#phi(Jet #slash{E}_{t})",false, 12, 0.f, 3.1416);
        allKinVars["dPhiJet0Met"] = new KinematicVar("dPhiJet0Met",  "", "#Delta#phi(Jet0 #slash{E}_{t})",false, 12, 0.f, 3.14159);

        allKinVars["dPhiJet1Met"] = new KinematicVar("dPhiJet1Met",  "", "#Delta#phi(Jet1 #slash{E}_{t})",false, 12, 0.f, 3.14159);
        
        allKinVars["dijetDEta01"] = new KinematicVar("dijetDEta01",  "", "#Delta#eta^{J J}",false, 14, 0.0, 3.5);

        allKinVars["dijetEta01"] = new KinematicVar("dijetEta01",  "", "#eta^{J J}",false, 28, -3.5, 3.5);

        allKinVars["dijetDPhi01"] = new KinematicVar("dijetDPhi01",  "", "#Delta#phi(J0 J1)",false, 12, 0.f, 3.1416);

        allKinVars["dijetDR01"] = new KinematicVar("dijetDR01",  "", "dR^{J0 J1}",false, 25, 0.f, 5.0);

        allKinVars["dijetPt01"] = new KinematicVar("dijetPt01",  "", "P_{t}^{J J} (GeV)",false, 15, 0.f, 300.f);

        allKinVars["dijetM01"] = new KinematicVar("dijetM01",  "Mass of the leading two dijets", "M^{J J} (GeV)",false, 20, 0.f, 400.f);

        allKinVars["Mbb01"] = new KinematicVar("Mbb01",  "Mass of the leading bb System", "M^{b0 b1} (GeV)",false, 15, 0.f, 300.f);

        allKinVars["Mbb01gg01"] = new KinematicVar("Mbb01gg01",  "Mass of the leading bb and h->gg System", "M^{b0 b1 #gamma0 #gamma1} (GeV)",false, 15, 0.f, 600.0);

        allKinVars["MJJ01gg01"] = new KinematicVar("MJJ01gg01",  "Mass of the leading two jets and h->gg System", "M^{J0 J1 #gamma0 #gamma1} (GeV)",false, 15, 0.f, 600.0);

        allKinVars["MZllHgg"] = new KinematicVar("MZllHgg",  "Mass of Z-like dilepton and H like diphoton", "M^{lep lep #gamma0 #gamma1} (GeV)",false, 30, 0.f, 990.f);

        allKinVars["MTggMET"] = new KinematicVar("MTggMET",  "Transverse Mass di-photon system and MET", "M^{t}(#gamma0 #gamma1 + MET) (GeV)",false, 4, 0.f, 160.f);

        allKinVars["MTlepMET"] = new KinematicVar("MTlepMET",  "Mass of the leading bb and h->gg System", "M^{t}(lep,MET) (GeV)",false, 30, 0.f, 300.f);

        allKinVars["HGt"] = new KinematicVar("HGt",  "Hadronic and Photon01 Transverse Energy", "HG_{t} (GeV)",false, 30, 0.f, 300.f);

        allKinVars["HGt_prime"] = new KinematicVar("HGt_prime", "Hadronic and Photon01 Transverse Energy, from lep+MET", "HG'_^{t} (GeV)",false, 30, 0.f, 300.f);

        allKinVars["dPhiHG"] = new KinematicVar("dPhiHG",  "Delta Phi between gg and All Jets", "#Delta Phi(Jets,#gamma0 #gamma1) (GeV)",false, 12, 0.f, 3.1416f);

        allKinVars["dPhiHG_prime"] = new KinematicVar("dPhiHG_prime",  "Mass of the leding bb and h->gg System, from lep+MET", "#Delta Phi(Jets,#gamma0 #gamma1) (GeV)",false, 12, 0.f, 3.1416f);
        allKinVars["HLMGt"] = new KinematicVar("HLMGt",  "Transverse Energy of all Objects and MET", "Pt(all particles and met) (GeV)",false, 30, 0.f, 300.f);


	{ KinematicVar* temp = new KinematicVar("BPtGG",  "Bness-weighted Di-Photon Pt Sectrum", "P_{t}^{#gamma #gamma} (GeV)",true, 4);
			//allKinVars["PtGG"] = new KinematicVar("PtGG",  "Di-Photon Pt Sectrum", "P_{t}^{#gamma #gamma} (GeV)",true, 25., 0.f, 250.f);
			//	float a[] = {0,10,20,30,40,50,60,70,80,90,120,150,180,210,240};// 14 bins
		float a[] = {0,15,90,135,180};
		temp->usearray(a);
        allKinVars["BPtGG"] = temp;}

	{ KinematicVar* temp = new KinematicVar("BMET","Bness-weighted Missing Transverse Energy","#slash{E}_{T} (GeV)",true,5);
			//KinematicVar* temp = new KinematicVar("MET","Missing Transverse Energy","#slash{E}_{T} (GeV)",false,6,0,150);
		float a[] = {0,20,45,60,90,210};
		temp->usearray(a);
		allKinVars["BMET"] = temp; }

	{ KinematicVar* temp = new KinematicVar("BnBjets",  "B weighted nBjets (Sum of B-ness)", "#Sigma B(csv)",true,5);
			//KinematicVar* temp = new KinematicVar("HT","Scalar Sum of all Hadronic Transverse Energy","#SigmaH_{T} (GeV)",false,20,0,1000);
		float a[] = {0,0.91,1.61,2.31,3,4}; //0, M, ML, MML, LLLL
		temp->usearray(a);
		allKinVars["BnBjets"] = temp; }

	{ KinematicVar* temp = new KinematicVar("Bunjets",  "Bu weighted nJets (Sum of Beautifullness)", "#Sigma Bu(csv)",true,5);
			//KinematicVar* temp = new KinematicVar("HT","Scalar Sum of all Hadronic Transverse Energy","#SigmaH_{T} (GeV)",false,20,0,1000);
		float a[] = {0,0.96,1.62,2.29,3,4}; //0, M, ML, MML, LLLL
		temp->usearray(a);
		allKinVars["Bunjets"] = temp; }


	allKinVars["nLFjets"] = new KinematicVar("nLFjets",  "", "Number of light flavor Jets",false, 8, 0.f, 8);

	{ KinematicVar* temp = new KinematicVar("phoHness",  "Weighted Di-Photon Pt Sectrum", "Photon Higgs-likeness (GeV)",true, 4);
			//allKinVars["PtGG"] = new KinematicVar("PtGG",  "Di-Photon Pt Sectrum", "P_{t}^{#gamma #gamma} (GeV)",true, 25., 0.f, 250.f);
			//	float a[] = {0,10,20,30,40,50,60,70,80,90,120,150,180,210,240};// 14 bins
		float a[] = {0,30,60,90,120};
		temp->usearray(a);
        allKinVars["phoHness"] = temp;}


	{ KinematicVar* temp = new KinematicVar("BuHT","Scalar Sum of all Beautifulness Weighted Hadronic Transverse Energy","#Sigma Bu(csv) * #Sigma H_{T} (GeV)",true,5);
			//KinematicVar* temp = new KinematicVar("HT","Scalar Sum of all Hadronic Transverse Energy","#SigmaH_{T} (GeV)",false,20,0,1000);
		float a[] = {0,225,375,525,750,1500};
		temp->usearray(a);
		allKinVars["BuHT"] = temp; }


	{ KinematicVar* temp = new KinematicVar("BBt",  "Scalar Sum of all B-jet B-ness weighted Transverse Momentum", "#Sigma_{B} B(csv)*P_{T} (GeV)",true, 10);
			//allKinVars["Bt"] = new KinematicVar("Bt",  "Scalar Sum of all B-jet Transverse Energy", "#SigmaB_{T} (GeV)",true, 20, 0.f, 800.f);
		float a[] = {0,40,80,120,160,200,240,280,320,480,800};
		temp->usearray(a);
		allKinVars["BBt"] = temp; }

	{ KinematicVar* temp = new KinematicVar("BST","B-ness Weighted Scalar Sum of all Calorimeter Energy","#Sigma B(csv) * #Sigma E_{T} (GeV)",true,4);
			// KinematicVar* temp = new KinematicVar("ST","Scalar Sum of all Calorimeter Energy","#SigmaE_{E}_{T} (GeV)",false,30,0,1500);
		float a[] = {0,357,525,825,1500};
		temp->usearray(a);
		allKinVars["BST"] = temp; }





	//now trim it down to those you care about
	LabelKinVars retKinVars;
	for(int k=0;k<nKinemVars_all;k++){
		retKinVars[s_KinemVars_all[k]] = allKinVars[s_KinemVars_all[k]];
	}
	return retKinVars;
}//end setupKinematicVar

/*
class Topology{
	string topo;
	//something about whether it passes? or maybe the definition of the cut. 
	//this is tricky, putting it here makes it less generalizable. 
	string title; //for use in postanaana.C
}
*/

#endif
