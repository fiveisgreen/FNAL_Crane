#include <TH1F.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TAxis.h"
#include "TMath.h"
#include "TFile.h"
#include "TLegend.h"
#include "TF1.h"
#include <iostream>
#include <fstream>
#include "utilities.h"
#include "CMSStyle.C"
#include "TFitResult.h"

//#ifndef __CINT__
//#include "RooGlobalFunc.h"
//#endif
//#include "RooRealVar.h"
//#include "RooDataSet.h"
//#include "RooGaussian.h"
//#include "RooPlot.h"

//using namespace RooFit ;
using namespace std;

Double_t CrystalBall(Double_t *x,Double_t *par);
Double_t mycrystal(Double_t *x,Double_t *par);
float addquad(float a, float b, float c);
float combine(float higgs, float full, float fast);


void combineSmearing(){
	TFile* fFullsim = TFile::Open("mcSmeraing_fullsim.root");
	TFile* fFastsim = TFile::Open("mcSmeraing_fastsim.root");
	TFile* fout = new TFile("combinedSmearing.root","RECREATE");

	//Load them all
	TH1F* smearing_eta0_lowr9_Full = (TH1F*)fFullsim->Get("smearing_eta0_lowr9"); smearing_eta0_lowr9_Full->SetName("smearing_eta0_lowr9_Full");
	TH1F* smearing_eta1_lowr9_Full = (TH1F*)fFullsim->Get("smearing_eta1_lowr9"); smearing_eta1_lowr9_Full->SetName("smearing_eta1_lowr9_Full");
	TH1F* smearing_eta2_lowr9_Full = (TH1F*)fFullsim->Get("smearing_eta2_lowr9"); smearing_eta2_lowr9_Full->SetName("smearing_eta2_lowr9_Full");
	TH1F* smearing_eta3_lowr9_Full = (TH1F*)fFullsim->Get("smearing_eta3_lowr9"); smearing_eta3_lowr9_Full->SetName("smearing_eta3_lowr9_Full");
	TH1F* smearing_eta0_hir9_Full = (TH1F*)fFullsim->Get("smearing_eta0_hir9"); smearing_eta0_hir9_Full->SetName("smearing_eta0_hir9_Full");
	TH1F* smearing_eta1_hir9_Full = (TH1F*)fFullsim->Get("smearing_eta1_hir9"); smearing_eta1_hir9_Full->SetName("smearing_eta1_hir9_Full");
	TH1F* smearing_eta2_hir9_Full = (TH1F*)fFullsim->Get("smearing_eta2_hir9"); smearing_eta2_hir9_Full->SetName("smearing_eta2_hir9_Full");
	TH1F* smearing_eta3_hir9_Full = (TH1F*)fFullsim->Get("smearing_eta3_hir9"); smearing_eta3_hir9_Full->SetName("smearing_eta3_hir9_Full");

	TH1F* smearing_eta0_lowr9_Fast = (TH1F*)fFastsim->Get("smearing_eta0_lowr9"); smearing_eta0_lowr9_Fast->SetName("smearing_eta0_lowr9_Fast");
	TH1F* smearing_eta1_lowr9_Fast = (TH1F*)fFastsim->Get("smearing_eta1_lowr9"); smearing_eta1_lowr9_Fast->SetName("smearing_eta1_lowr9_Fast");
	TH1F* smearing_eta2_lowr9_Fast = (TH1F*)fFastsim->Get("smearing_eta2_lowr9"); smearing_eta2_lowr9_Fast->SetName("smearing_eta2_lowr9_Fast");
	TH1F* smearing_eta3_lowr9_Fast = (TH1F*)fFastsim->Get("smearing_eta3_lowr9"); smearing_eta3_lowr9_Fast->SetName("smearing_eta3_lowr9_Fast");
	TH1F* smearing_eta0_hir9_Fast = (TH1F*)fFastsim->Get("smearing_eta0_hir9"); smearing_eta0_hir9_Fast->SetName("smearing_eta0_hir9_Fast");
	TH1F* smearing_eta1_hir9_Fast = (TH1F*)fFastsim->Get("smearing_eta1_hir9"); smearing_eta1_hir9_Fast->SetName("smearing_eta1_hir9_Fast");
	TH1F* smearing_eta2_hir9_Fast = (TH1F*)fFastsim->Get("smearing_eta2_hir9"); smearing_eta2_hir9_Fast->SetName("smearing_eta2_hir9_Fast");
	TH1F* smearing_eta3_hir9_Fast = (TH1F*)fFastsim->Get("smearing_eta3_hir9"); smearing_eta3_hir9_Fast->SetName("smearing_eta3_hir9_Fast");
	fout->cd();

	float sigmaFullsim[8];
	float sigmaFastsim[8];
	float higgsSmears[8];
	string lables[8] = { "smearing_eta0_lowr9", "smearing_eta1_lowr9", "smearing_eta2_lowr9", "smearing_eta3_lowr9", "smearing_eta0_hir9", "smearing_eta1_hir9", "smearing_eta2_hir9", "smearing_eta3_hir9"};


	//TF1* f = new TF1("fit1","TMath::Gaus(x,0,[1])*[0]",-0.2,0.2);
	TF1* f = new TF1("fit1","gaus",-0.10,0.10);
	TFitResultPtr res;

	cout<<"Do smearing_eta0_lowr9_Full"<<endl;
	f->SetRange(-0.02,0.02);
	TCanvas *tc_smearing_eta0_lowr9_Full = newTCanvas("tc_smearing_eta0_lowr9_Full","tc_smearing_eta0_lowr9_Full");
	f->SetParameters(smearing_eta0_lowr9_Full->Integral(),0,0.01);
	res=smearing_eta0_lowr9_Full->Fit(f,"SM","",-0.02,0.02);
	sigmaFullsim[0] = res->GetParams()[2];
	smearing_eta0_lowr9_Full->Draw();
	f->Draw("same");
	tc_smearing_eta0_lowr9_Full->Write();
	

	cout<<endl<<"Do smearing_eta1_lowr9_Full"<<endl;
	f->SetRange(-0.02,0.02);
	TCanvas *tc_smearing_eta1_lowr9_Full = newTCanvas("tc_smearing_eta1_lowr9_Full","tc_smearing_eta1_lowr9_Full");
	f->SetParameters(smearing_eta1_lowr9_Full->Integral(),0,0.01);
	res=smearing_eta1_lowr9_Full->Fit(f,"SM","",-0.02,0.02);
	sigmaFullsim[1] = res->GetParams()[2];
	smearing_eta1_lowr9_Full->Draw();
	f->Draw("same");
	tc_smearing_eta1_lowr9_Full->Write();

	cout<<endl<<"Do smearing_eta2_lowr9_Full"<<endl;
	f->SetRange(-0.05,0.05);
	TCanvas *tc_smearing_eta2_lowr9_Full = newTCanvas("tc_smearing_eta2_lowr9_Full","tc_smearing_eta2_lowr9_Full");
	f->SetParameters(smearing_eta2_lowr9_Full->Integral(),0,0.01);
	res=smearing_eta2_lowr9_Full->Fit(f,"SM","",-0.05,0.05);
	sigmaFullsim[2] = res->GetParams()[2];
	smearing_eta2_lowr9_Full->Draw();
	f->Draw("same");
	tc_smearing_eta2_lowr9_Full->Write();

	cout<<endl<<"Do smearing_eta3_lowr9_Full"<<endl;
	f->SetRange(-0.03,0.03);
	TCanvas *tc_smearing_eta3_lowr9_Full = newTCanvas("tc_smearing_eta3_lowr9_Full","tc_smearing_eta3_lowr9_Full");
	f->SetParameters(smearing_eta3_lowr9_Full->Integral(),0,0.01);
	res=smearing_eta3_lowr9_Full->Fit(f,"SM","",-0.03,0.03);
	sigmaFullsim[3] = res->GetParams()[2];
	smearing_eta3_lowr9_Full->Draw();
	f->Draw("same");
	tc_smearing_eta3_lowr9_Full->Write();

	cout<<endl<<"Do smearing_eta0_hir9_Full"<<endl;
	f->SetRange(-0.02,0.02);
	TCanvas *tc_smearing_eta0_hir9_Full = newTCanvas("tc_smearing_eta0_hir9_Full","tc_smearing_eta0_hir9_Full");
	f->SetParameters(smearing_eta0_hir9_Full->Integral(),0,0.01);
	res=smearing_eta0_hir9_Full->Fit(f,"SM","",-0.02,0.02);
	sigmaFullsim[4] = res->GetParams()[2];
	smearing_eta0_hir9_Full->Draw();
	f->Draw("same");
	tc_smearing_eta0_hir9_Full->Write();

	cout<<endl<<"Do smearing_eta1_hir9_Full"<<endl;
	f->SetRange(-0.02,0.02);
	TCanvas *tc_smearing_eta1_hir9_Full = newTCanvas("tc_smearing_eta1_hir9_Full","tc_smearing_eta1_hir9_Full");
	f->SetParameters(smearing_eta1_hir9_Full->Integral(),0,0.01);
	res=smearing_eta1_hir9_Full->Fit(f,"SM","",-0.02,0.02);
	sigmaFullsim[5] = res->GetParams()[2];
	smearing_eta1_hir9_Full->Draw();
	f->Draw("same");
	tc_smearing_eta1_hir9_Full->Write();

	cout<<endl<<"Do smearing_eta2_hir9_Full"<<endl;
	f->SetRange(-0.02,0.02);
	TCanvas *tc_smearing_eta2_hir9_Full = newTCanvas("tc_smearing_eta2_hir9_Full","tc_smearing_eta2_hir9_Full");
	f->SetParameters(smearing_eta2_hir9_Full->Integral(),0,0.01);
	res=smearing_eta2_hir9_Full->Fit(f,"SM","",-0.02,0.02);
	sigmaFullsim[6] = res->GetParams()[2];
	smearing_eta2_hir9_Full->Draw();
	f->Draw("same");
	tc_smearing_eta2_hir9_Full->Write();

	cout<<endl<<"Do smearing_eta3_hir9_Full"<<endl;
	f->SetRange(-0.03,0.03);
	TCanvas *tc_smearing_eta3_hir9_Full = newTCanvas("tc_smearing_eta3_hir9_Full","tc_smearing_eta3_hir9_Full");
	f->SetParameters(smearing_eta3_hir9_Full->Integral(),0,0.01);
	res=smearing_eta3_hir9_Full->Fit(f,"SM","",-0.03,0.03);
	sigmaFullsim[7] = res->GetParams()[2];
	smearing_eta3_hir9_Full->Draw();
	f->Draw("same");
	tc_smearing_eta3_hir9_Full->Write();
/////////////////////
	cout<<endl<<"***BEGIN FAST SIM***"<<endl;

	cout<<endl<<"Do smearing_eta0_lowr9_Fast"<<endl;
	f->SetRange(-0.02,0.02);
	TCanvas *tc_smearing_eta0_lowr9_Fast = newTCanvas("tc_smearing_eta0_lowr9_Fast","tc_smearing_eta0_lowr9_Fast");
	f->SetParameters(smearing_eta0_lowr9_Fast->Integral(),0,0.01);
	res=smearing_eta0_lowr9_Fast->Fit(f,"SM","",-0.02,0.02);
	sigmaFastsim[0] = res->GetParams()[2];
	smearing_eta0_lowr9_Fast->Draw();
	f->Draw("same");
	tc_smearing_eta0_lowr9_Fast->Write();

	cout<<endl<<"Do smearing_eta1_lowr9_Fast"<<endl;
	f->SetRange(-0.03,0.03);
	TCanvas *tc_smearing_eta1_lowr9_Fast = newTCanvas("tc_smearing_eta1_lowr9_Fast","tc_smearing_eta1_lowr9_Fast");
	f->SetParameters(smearing_eta1_lowr9_Fast->Integral(),0,0.01);
	res=smearing_eta1_lowr9_Fast->Fit(f,"SM","",-0.03,0.03);
	sigmaFastsim[1] = res->GetParams()[2];
	smearing_eta1_lowr9_Fast->Draw();
	f->Draw("same");
	tc_smearing_eta1_lowr9_Fast->Write();

	cout<<endl<<"Do smearing_eta2_lowr9_Fast"<<endl;
	f->SetRange(-0.05,0.05);
	TCanvas *tc_smearing_eta2_lowr9_Fast = newTCanvas("tc_smearing_eta2_lowr9_Fast","tc_smearing_eta2_lowr9_Fast");
	f->SetParameters(smearing_eta2_lowr9_Fast->Integral(),0,0.01);
	res=smearing_eta2_lowr9_Fast->Fit(f,"SM","",-0.05,0.05);
	sigmaFastsim[2] = res->GetParams()[2];
	smearing_eta2_lowr9_Fast->Draw();
	f->Draw("same");
	tc_smearing_eta2_lowr9_Fast->Write();

	cout<<endl<<"Do smearing_eta3_lowr9_Fast"<<endl;
	f->SetRange(-0.09,0.09);
	TCanvas *tc_smearing_eta3_lowr9_Fast = newTCanvas("tc_smearing_eta3_lowr9_Fast","tc_smearing_eta3_lowr9_Fast");
	f->SetParameters(smearing_eta3_lowr9_Fast->Integral(),0,0.01);
	res=smearing_eta3_lowr9_Fast->Fit(f,"SM","",-0.09,0.09);
	sigmaFastsim[3] = res->GetParams()[2];
	smearing_eta3_lowr9_Fast->Draw();
	f->Draw("same");
	tc_smearing_eta3_lowr9_Fast->Write();

	cout<<endl<<"Do smearing_eta0_hir9_Fast"<<endl;
	f->SetRange(-0.02,0.02);
	TCanvas *tc_smearing_eta0_hir9_Fast = newTCanvas("tc_smearing_eta0_hir9_Fast","tc_smearing_eta0_hir9_Fast");
	f->SetParameters(smearing_eta0_hir9_Fast->Integral(),0,0.01);
	res=smearing_eta0_hir9_Fast->Fit(f,"SM","",-0.02,0.02);
	sigmaFastsim[4] = res->GetParams()[2];
	smearing_eta0_hir9_Fast->Draw();
	f->Draw("same");
	tc_smearing_eta0_hir9_Fast->Write();

	cout<<endl<<"Do smearing_eta1_hir9_Fast"<<endl;
	f->SetRange(-0.03,0.03);
	TCanvas *tc_smearing_eta1_hir9_Fast = newTCanvas("tc_smearing_eta1_hir9_Fast","tc_smearing_eta1_hir9_Fast");
	f->SetParameters(smearing_eta1_hir9_Fast->Integral(),0,0.01);
	res=smearing_eta1_hir9_Fast->Fit(f,"SM","",-0.03,0.03);
	sigmaFastsim[5] = res->GetParams()[2];
	smearing_eta1_hir9_Fast->Draw();
	f->Draw("same");
	tc_smearing_eta1_hir9_Fast->Write();

	cout<<endl<<"Do smearing_eta2_hir9_Fast"<<endl;
	f->SetRange(-0.035,0.035);
	TCanvas *tc_smearing_eta2_hir9_Fast = newTCanvas("tc_smearing_eta2_hir9_Fast","tc_smearing_eta2_hir9_Fast");
	f->SetParameters(smearing_eta2_hir9_Fast->Integral(),0,0.01);
	res=smearing_eta2_hir9_Fast->Fit(f,"SM","",-0.035,0.035);
	sigmaFastsim[6] = res->GetParams()[2];
	smearing_eta2_hir9_Fast->Draw();
	f->Draw("same");
	tc_smearing_eta2_hir9_Fast->Write();

	cout<<endl<<"Do smearing_eta3_hir9_Fast"<<endl;
	f->SetRange(-0.05,0.05);
	TCanvas *tc_smearing_eta3_hir9_Fast = newTCanvas("tc_smearing_eta3_hir9_Fast","tc_smearing_eta3_hir9_Fast");
	f->SetParameters(smearing_eta3_hir9_Fast->Integral(),0,0.01);
	res=smearing_eta3_hir9_Fast->Fit(f,"SM","",-0.05,0.05);
	sigmaFastsim[7] = res->GetParams()[2];
	smearing_eta3_hir9_Fast->Draw();
	f->Draw("same");
	tc_smearing_eta3_hir9_Fast->Write();

	///////////////////////////////////
	cout<<endl<<endl<<endl;
	///////////////////////////////////
	higgsSmears[0] = addquad(0.0107,0.0006,0.0022);//eta0, low r9
	higgsSmears[1] = addquad(0.0194,0.0011,0.0059);//eta1, low r9
	higgsSmears[2] = addquad(0.0276,0.0013,0.0030);//eta2, low r9
	higgsSmears[3] = addquad(0.0371,0.0016,0.0052);//eta3, low r9
	higgsSmears[4] = addquad(0.0111,0.0007,0.0022);//eta0, hi r9
	higgsSmears[5] = addquad(0.0155,0.0040,0.0060);//eta1, hi r9
	higgsSmears[6] = addquad(0.0295,0.0025,0.0090);//eta2, hi r9
	higgsSmears[7] = addquad(0.0370,0.0011,0.0034);//eta3, hi r9
	/*TH1F* smearing_eta0_lowr9_Full = (TH1F*)fFullsim->Get("smearing_eta0_lowr9"); smearing_eta0_lowr9_Full->SetName("smearing_eta0_lowr9_Full");
	TH1F* smearing_eta1_lowr9_Full = (TH1F*)fFullsim->Get("smearing_eta1_lowr9"); smearing_eta1_lowr9_Full->SetName("smearing_eta1_lowr9_Full");
	TH1F* smearing_eta2_lowr9_Full = (TH1F*)fFullsim->Get("smearing_eta2_lowr9"); smearing_eta2_lowr9_Full->SetName("smearing_eta2_lowr9_Full");
	TH1F* smearing_eta3_lowr9_Full = (TH1F*)fFullsim->Get("smearing_eta3_lowr9"); smearing_eta3_lowr9_Full->SetName("smearing_eta3_lowr9_Full");
	TH1F* smearing_eta0_hir9_Full = (TH1F*)fFullsim->Get("smearing_eta0_hir9"); smearing_eta0_hir9_Full->SetName("smearing_eta0_hir9_Full");
	TH1F* smearing_eta1_hir9_Full = (TH1F*)fFullsim->Get("smearing_eta1_hir9"); smearing_eta1_hir9_Full->SetName("smearing_eta1_hir9_Full");
	TH1F* smearing_eta2_hir9_Full = (TH1F*)fFullsim->Get("smearing_eta2_hir9"); smearing_eta2_hir9_Full->SetName("smearing_eta2_hir9_Full");
	TH1F* smearing_eta3_hir9_Full = (TH1F*)fFullsim->Get("smearing_eta3_hir9"); smearing_eta3_hir9_Full->SetName("smearing_eta3_hir9_Full");*/
	float combined[8];

	for(int i = 0;i<8;i++){
		//cout<<"higgs "<<higgsSmears[i] <<" full "<<sigmaFullsim[i]<<" fast "<<sigmaFastsim[i]<<" conbined "<<1+combine(higgsSmears[i],sigmaFullsim[i],sigmaFastsim[i])<<endl;
		combined[i] = combine(higgsSmears[i],sigmaFullsim[i],sigmaFastsim[i]);
		printf("%s higgs %.4f full %.4f fast %.4f combined %.4f\n",lables[i].c_str(),higgsSmears[i],sigmaFullsim[i],sigmaFastsim[i],combined[i]);
	}
	///////////////////////////////////
	cout<<endl<<endl<<endl;
	///////////////////////////////////
	int i;
	printf("category             higgs (%) full (%) fast (%) combined (%)\n");
	i = 4; printf("%s\t%.2f\t%.2f\t%.2f\t%.2f\n",lables[i].data(),100.0*higgsSmears[i],100.0*sigmaFullsim[i],100.0*sigmaFastsim[i],100.0*combined[i]);
	i = 0; printf("%s\t%.2f\t%.2f\t%.2f\t%.2f\n",lables[i].data(),100.0*higgsSmears[i],100.0*sigmaFullsim[i],100.0*sigmaFastsim[i],100.0*combined[i]);
	i = 5; printf("%s\t%.2f\t%.2f\t%.2f\t%.2f\n",lables[i].data(),100.0*higgsSmears[i],100.0*sigmaFullsim[i],100.0*sigmaFastsim[i],100.0*combined[i]);
	i = 1; printf("%s\t%.2f\t%.2f\t%.2f\t%.2f\n",lables[i].data(),100.0*higgsSmears[i],100.0*sigmaFullsim[i],100.0*sigmaFastsim[i],100.0*combined[i]);
	i = 6; printf("%s\t%.2f\t%.2f\t%.2f\t%.2f\n",lables[i].data(),100.0*higgsSmears[i],100.0*sigmaFullsim[i],100.0*sigmaFastsim[i],100.0*combined[i]);
	i = 2; printf("%s\t%.2f\t%.2f\t%.2f\t%.2f\n",lables[i].data(),100.0*higgsSmears[i],100.0*sigmaFullsim[i],100.0*sigmaFastsim[i],100.0*combined[i]);
	i = 7; printf("%s\t%.2f\t%.2f\t%.2f\t%.2f\n",lables[i].data(),100.0*higgsSmears[i],100.0*sigmaFullsim[i],100.0*sigmaFastsim[i],100.0*combined[i]);
	i = 3; printf("%s\t%.2f\t%.2f\t%.2f\t%.2f\n",lables[i].data(),100.0*higgsSmears[i],100.0*sigmaFullsim[i],100.0*sigmaFastsim[i],100.0*combined[i]);

	///////////////////////////////////
	cout<<endl<<endl<<endl;
	///////////////////////////////////

cout<<" put this in cuts.h"<<endl<<endl;;

printf("       if(is_bar(eta)){\n");
printf("                if(eta < 1){\n");
printf("                        if(r9>0.94) sigma = %f;\n",combined[4]);
printf("                        else sigma = %f;\n",combined[0]);
printf("                }\n");
printf("                else{\n");
printf("                        if(r9>0.94) sigma = %f;\n",combined[5]);
printf("                        else sigma = %f;\n",combined[1]);
printf("                }\n");
printf("        }\n");
printf("        else{ //ec\n");
printf("                if(eta < 2){\n");
printf("                        if(r9>0.94) sigma = %f;\n",combined[6]);
printf("                        else sigma = %f;\n",combined[2]);
printf("                }\n");
printf("                else{\n");
printf("                        if(r9>0.94) sigma = %f;\n",combined[7]);
printf("                        else sigma = %f;\n",combined[3]);
printf("                }\n");
printf("        }\n");

	cout<<endl<<endl<<endl;
/*
	TH1F* smearing_eta0_lowr9_Full = (TH1F*)fFullsim->Get("smearing_eta0_lowr9"); smearing_eta0_lowr9_Full->SetName("smearing_eta0_lowr9_Full");
	TH1F* smearing_eta1_lowr9_Full = (TH1F*)fFullsim->Get("smearing_eta1_lowr9"); smearing_eta1_lowr9_Full->SetName("smearing_eta1_lowr9_Full");
	TH1F* smearing_eta2_lowr9_Full = (TH1F*)fFullsim->Get("smearing_eta2_lowr9"); smearing_eta2_lowr9_Full->SetName("smearing_eta2_lowr9_Full");
	TH1F* smearing_eta3_lowr9_Full = (TH1F*)fFullsim->Get("smearing_eta3_lowr9"); smearing_eta3_lowr9_Full->SetName("smearing_eta3_lowr9_Full");
	TH1F* smearing_eta0_hir9_Full = (TH1F*)fFullsim->Get("smearing_eta0_hir9"); smearing_eta0_hir9_Full->SetName("smearing_eta0_hir9_Full");
	TH1F* smearing_eta1_hir9_Full = (TH1F*)fFullsim->Get("smearing_eta1_hir9"); smearing_eta1_hir9_Full->SetName("smearing_eta1_hir9_Full");
	TH1F* smearing_eta2_hir9_Full = (TH1F*)fFullsim->Get("smearing_eta2_hir9"); smearing_eta2_hir9_Full->SetName("smearing_eta2_hir9_Full");
	TH1F* smearing_eta3_hir9_Full = (TH1F*)fFullsim->Get("smearing_eta3_hir9"); smearing_eta3_hir9_Full->SetName("smearing_eta3_hir9_Full");
*/

	fFullsim->Close();
	fFastsim->Close();
	fout->Close();
	cout<<"end all"<<endl;
}//end combineSmearing

Double_t CrystalBall(Double_t *x,Double_t *par) {
//Crystal ball function for signal, parameters are 0:alpha,1:n,2:mean,3:sigma,4:normalization;

  Double_t t = (x[0]-par[2])/par[3];
  if (par[0] < 0) t = -t;

  Double_t absAlpha = fabs((Double_t)par[0]);

  if (t >= -absAlpha) {
    return par[4]*exp(-0.5*t*t);
  }
  else {
    Double_t A =  TMath::Power(par[1]/absAlpha,par[1])*exp(-0.5*absAlpha*absAlpha);
    Double_t B= par[1]/absAlpha - absAlpha; 

    return par[4]*(A/TMath::Power(B - t, par[1]));
  }
}//end CrystalBall

Double_t mycrystal(Double_t *x,Double_t *par){
	//0:alpha, 1:n, 2: mean, 3: sigma 4: normalization
	//see here: http://en.wikipedia.org/wiki/Crystal_Ball_function
	Double_t t = (x[0]-par[2])/par[3];
	Double_t absAlpha = fabs((Double_t)par[0]);
	Double_t C = (par[1]/absAlpha)*(1.0/(par[1] -1))*exp(-0.5*absAlpha*absAlpha);
	Double_t D = sqrt(TMath::PiOver2())*TMath::Erf(absAlpha/TMath::Sqrt2());
	Double_t N = 1.0/(par[4]*(C+D));
	if (t >= -absAlpha) {
		return par[4]*N*exp(-0.5*t*t);
	}
	else {
		Double_t A =  TMath::Power(par[1]/absAlpha,par[1])*exp(-0.5*absAlpha*absAlpha);
		Double_t B= (par[1]/absAlpha) - absAlpha; 
		return par[4]*N*(A/TMath::Power(B - t, -par[1]));
	}
}//end mycrystal

float addquad(float a, float b, float c){
	return sqrt(a*a + b*b + c*c);
}
float combine(float higgs, float full, float fast){
	return sqrt(higgs*higgs + full*full - fast*fast);
}
