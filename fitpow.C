	//A good fitting procedure from Yuri
#include <iostream>
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "params_arg.h"
#include "TFitResult.h"

using namespace std;

Bool_t reject;

Double_t fpow(Double_t *x, Double_t *par)
{
  if(reject && x[0]>122 && x[0]<129){
    TF1::RejectPoint();
    return 0;
  }
  return par[0]*pow(x[0],par[1]);

}

void fitpow()
{
  TFile *ff = new TFile("Mgg_2JbMLm20gbar2.root");
  TH1F *h1 = (TH1F*) gDirectory->Get("h_mGG2JbMLm20gbar2_unsliced");
  TF1 *fp = new TF1("fp",fpow,100,180,2);
  reject = true;
  h1->Fit(fp,"L","",105,160);

}
