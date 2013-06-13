	//A good fitting procedure from Yuri
#include <iostream>
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "params_arg.h"
#include "TFitResult.h"

using namespace std;
using namespace params;

Bool_t reject;

Double_t fpow(Double_t *x, Double_t *par)
{
  //if(x[0]>tag_lb && x[0]<tag_ub){
  if(reject && x[0]>=lsb_ub && x[0]<=usb_lb){
    TF1::RejectPoint();
    return 0;
  }
  return par[0]*pow(x[0],par[1]);

}

void fitpow2()
{
	TFile *ff = new TFile("Mgg_2JbMLm20gbar2.root");
	TH1F *h1 = (TH1F*) gDirectory->Get("h_mGG2JbMLm20gbar2_unsliced");
	TF1 *fitcurve = new TF1("fitcurve",fpow,105,160,2);
	reject = true;
	int status = h1->Fit(fitcurve,"L","",105,160);
	printf("fit status: %i \n",status);
	TFitResultPtr fitresult = h1->Fit(fitcurve,"SL","",105,160);
	printf("param0 %f param1 %f \n",fitresult->GetParams()[0],fitresult->GetParams()[1]);
	cout << fitresult->Chi2()<<endl;
	TMatrixDSym cov = fitresult->GetCovarianceMatrix();
	float chi2 = (fitcurve)->GetChisquare()/((float)((fitcurve)->GetNDF() - 1));
	reject = false;
	float B_integral = (fitcurve)->Integral(tag_lb,tag_ub);
	float B_integral_error = (fitcurve)->IntegralError(tag_lb,tag_ub,fitresult->GetParams(), cov.GetMatrixArray() );
	reject = true;
		//see here: http://root.cern.ch/root/html/TF1.html#TF1:IntegralError
	cout<<"integral: "<<B_integral<<" +- "<<B_integral_error<<endl;

		//get chi2 per degree of freedom.
	cout<<"Chi2 per dof "<<chi2<<endl;
	printf("param0 %f param1 %f \n",fitresult->GetParams()[0],fitresult->GetParams()[1]);

}
