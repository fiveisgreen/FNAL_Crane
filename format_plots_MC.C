#include "TFractionFitter.h"
#include "TAxis.h"
#include "TH1.h"
#include "TMath.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TFile.h"
#include "TTree.h"
#include "TVirtualFitter.h"
#include "TLegend.h"
#include <iostream>
#include "TF1.h"
#include "TLine.h"
	//#include "quicksave.C"
#include "CMSStyle.C"
#include "utilities.h"
#include "params_arg.h"
#include<string.h>
#include<map>
using namespace std;
using namespace params;
TLegend* makeL1(float f1=0.652548,float f2=0.663899,float f3=0.852528,float f4=0.864219);
TLegend* makeL2(float f1=0.651267,float f2=0.660256,float f3=0.851246,float f4=0.860577);
void Arrange1(TCanvas* c, TH1F** h, TLegend* l1, TLegend* l2);
void diphoMassPlot(TH1F* hdiPhoMass, TCanvas* canv, TF1* fitcurve);
void LoadHistSet(TH1F** h, TFile* fin, TString prefix);





void format_plots_MC(){
	cout<<"hello world"<<endl;
	CMSStyle();
	TFile fin(plotsAndBackground_mc.c_str());
	fin.cd();
	

	
	TH1F* h_mGG_unsliced = (TH1F*)fin.Get("h_mGG_unsliced");
	TH1F* h_mGG_1Jb_unsliced = (TH1F*)fin.Get("h_mGG_1Jb_unsliced");
	TH1F* h_mGG_3J_unsliced = (TH1F*)fin.Get("h_mGG_3J_unsliced");
	TH1F* h_mGG_3Jb_unsliced = (TH1F*)fin.Get("h_mGG_3Jb_unsliced");
	TH1F* h_mGG_metCut_unsliced = (TH1F*)fin.Get("h_mGG_metCut_unsliced");
	
	h_mGG_unsliced->SetName("h_mGG_unsliced");
	TH1F * hMET[nPhoMassAndBkgDists];
	LoadHistSet(hMET, &fin, "MET");
	TH1F * hST[nPhoMassAndBkgDists];
	LoadHistSet(hST, &fin, "ST");
	TH1F * hPtGG[nPhoMassAndBkgDists];
	LoadHistSet(hPtGG,&fin,"PtGG");
	TH1F * hHT[nPhoMassAndBkgDists];
	LoadHistSet(hHT,&fin,"HT");
	TH1F * hMHT[nPhoMassAndBkgDists];
	LoadHistSet(hMHT,&fin,"MHT");
		//require 1+ jets that b-tags
	TH1F * hMET_1Jb[nPhoMassAndBkgDists];
	LoadHistSet(hMET_1Jb,&fin,"MET_1Jb");
	TH1F * hST_1Jb[nPhoMassAndBkgDists];
	LoadHistSet(hST_1Jb,&fin,"ST_1Jb");
	TH1F * hPtGG_1Jb[nPhoMassAndBkgDists];
	LoadHistSet(hPtGG_1Jb,&fin,"PtGG_1Jb");
	TH1F * hHT_1Jb[nPhoMassAndBkgDists];
	LoadHistSet(hHT_1Jb,&fin,"HT_1Jb");
	TH1F * hMHT_1Jb[nPhoMassAndBkgDists];
	LoadHistSet(hMHT_1Jb,&fin,"MHT_1Jb");
		//require three+ jets 
	TH1F * hMET_3J[nPhoMassAndBkgDists];
	LoadHistSet(hMET_3J,&fin,"MET_3J");
	TH1F * hST_3J[nPhoMassAndBkgDists];
	LoadHistSet(hST_3J,&fin,"ST_3J");
	TH1F * hPtGG_3J[nPhoMassAndBkgDists];
	LoadHistSet(hPtGG_3J,&fin,"PtGG_3J");
	TH1F * hHT_3J[nPhoMassAndBkgDists];
	LoadHistSet(hHT_3J,&fin,"HT_3J");
	TH1F * hMHT_3J[nPhoMassAndBkgDists];
	LoadHistSet(hMHT_3J,&fin,"MHT_3J");
		//req 3+ jets and a b-tag
	TH1F * hMET_3Jb[nPhoMassAndBkgDists];
	LoadHistSet(hMET_3Jb,&fin,"MET_3Jb");
	TH1F * hST_3Jb[nPhoMassAndBkgDists];
	LoadHistSet(hST_3Jb,&fin,"ST_3Jb");
	TH1F * hPtGG_3Jb[nPhoMassAndBkgDists];
	LoadHistSet(hPtGG_3Jb,&fin,"PtGG_3Jb");
	TH1F * hHT_3Jb[nPhoMassAndBkgDists];
	LoadHistSet(hHT_3Jb,&fin,"HT_3Jb");
	TH1F * hMHT_3Jb[nPhoMassAndBkgDists];
	LoadHistSet(hMHT_3Jb,&fin,"MHT_3Jb");
		//require a met>20
	TH1F * hST_metCut[nPhoMassAndBkgDists];
	LoadHistSet(hST_metCut,&fin,"ST_metCut");
	TH1F * hPtGG_metCut[nPhoMassAndBkgDists];
	LoadHistSet(hPtGG_metCut,&fin,"PtGG_metCut");
	TH1F * hHT_metCut[nPhoMassAndBkgDists];
	LoadHistSet(hHT_metCut,&fin,"HT_metCut");
	TH1F * hMHT_metCut[nPhoMassAndBkgDists];
	LoadHistSet(hMHT_metCut,&fin,"MHT_metCut");
	
		//load the fit curves. 
	int nEventTopologies = 5;
	TF1* mgg_fit_curve[nEventTopologies];
	mgg_fit_curve[0] = (TF1*)fin.Get("mggfit");
	mgg_fit_curve[1] = (TF1*)fin.Get("mgg_1Jb_fit");
	mgg_fit_curve[2] = (TF1*)fin.Get("mgg_3J_fit");
	mgg_fit_curve[3] = (TF1*)fin.Get("mgg_3Jb_fit");
	mgg_fit_curve[4] = (TF1*)fin.Get("mgg_metCut_fit");
	
	
		//plot the Two background curves and the estimate between them and the center curve
		//put the subtracted spectrum belown it. 
		//Make some of this into fuctions; you'll use them several times.  
		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	TFile* fplots = new TFile(formatedplotsroot_mc.c_str(),"RECREATE");
	fplots->cd();

		//if there is a src folder, make it. 
	
		//diphoton mass plots
	TCanvas *c_mGG_unsliced = newTCanvas("c_mGG_unsliced");
	diphoMassPlot(h_mGG_unsliced, c_mGG_unsliced, mgg_fit_curve[0]);
	c_mGG_unsliced->Write();
	
	TCanvas *c_mGG_1Jb_unsliced = newTCanvas("c_mGG_1Jb_unsliced");
	diphoMassPlot(h_mGG_1Jb_unsliced, c_mGG_1Jb_unsliced, mgg_fit_curve[1]);
	c_mGG_1Jb_unsliced->Write();
	
	TCanvas *c_mGG_3J_unsliced = newTCanvas("c_mGG_3J_unsliced");
	diphoMassPlot(h_mGG_3J_unsliced, c_mGG_3J_unsliced, mgg_fit_curve[2]);
	c_mGG_3J_unsliced->Write();

	TCanvas *c_mGG_3Jb_unsliced = newTCanvas("c_mGG_3Jb_unsliced");
	diphoMassPlot(h_mGG_3Jb_unsliced, c_mGG_3Jb_unsliced, mgg_fit_curve[3]);
	c_mGG_3Jb_unsliced->Write();
	
	TCanvas *c_mGG_metCut_unsliced = newTCanvas("c_mGG_metCut_unsliced");
	diphoMassPlot(h_mGG_metCut_unsliced, c_mGG_metCut_unsliced, mgg_fit_curve[4]);
	c_mGG_metCut_unsliced->Write();
	
	
		// %%%%%%%%%%%%%%%%%%%%%%%% Kinematics and backgrounds %%%%%%%%%%%%%%%%%
		// nothing extra:
	TCanvas *cMET = newTCanvas("cMET");
	Arrange1(cMET,hMET,makeL1(),makeL2());
	cMET->Write();
	
	TCanvas *cST = newTCanvas("cST");
	Arrange1(cST,hST,makeL1(),makeL2());
	cST->Write();

	TCanvas *cPtGG = newTCanvas("cPtGG");
	Arrange1(cPtGG,hPtGG,makeL1(),makeL2());
	cPtGG->Write();
	
	TCanvas *cHT = newTCanvas("cHT");
	Arrange1(cHT,hHT,makeL1(),makeL2());
	cHT->Write();
	
	TCanvas *cMHT = newTCanvas("cMHT");
	Arrange1(cMHT,hMHT,makeL1(),makeL2());
	cMHT->Write();
	
		//1Jb
	TCanvas *cMET_1Jb = newTCanvas("cMET_1Jb");
	Arrange1(cMET_1Jb,hMET_1Jb,makeL1(),makeL2());
	cMET_1Jb->Write();
	
	TCanvas *cST_1Jb = newTCanvas("cST_1Jb");
	Arrange1(cST_1Jb,hST_1Jb,makeL1(),makeL2());
	cST_1Jb->Write();
	
	TCanvas *cPtGG_1Jb = newTCanvas("cPtGG_1Jb");
	Arrange1(cPtGG_1Jb,hPtGG_1Jb,makeL1(),makeL2());
	cPtGG_1Jb->Write();
	
	TCanvas *cHT_1Jb = newTCanvas("cHT_1Jb");
	Arrange1(cHT_1Jb,hHT_1Jb,makeL1(),makeL2());
	cHT_1Jb->Write();
	
	TCanvas *cMHT_1Jb = newTCanvas("cMHT_1Jb");
	Arrange1(cMHT_1Jb,hMHT_1Jb,makeL1(),makeL2());
	cMHT_1Jb->Write();
	
		//require three+ jets 
	TCanvas *cMET_3J = newTCanvas("cMET_3J");
	Arrange1(cMET_3J,hMET_3J,makeL1(),makeL2());
	cMET_3J->Write();
	
	TCanvas *cST_3J = newTCanvas("cST_3J");
	Arrange1(cST_3J,hST_3J,makeL1(),makeL2());
	cST_3J->Write();
	
	TCanvas *cPtGG_3J = newTCanvas("cPtGG_3J");
	Arrange1(cPtGG_3J,hPtGG_3J,makeL1(),makeL2());
	cPtGG_3J->Write();
	
	TCanvas *cHT_3J = newTCanvas("cHT_3J");
	Arrange1(cHT_3J,hHT_3J,makeL1(),makeL2());
	cHT_3J->Write();
	
	TCanvas *cMHT_3J = newTCanvas("cMHT_3J");
	Arrange1(cMHT_3J,hMHT_3J,makeL1(),makeL2());
	cMHT_3J->Write();
	
		//req 3+ jets and a b-tag
	TCanvas *cMET_3Jb = newTCanvas("cMET_3Jb");
	Arrange1(cMET_3Jb,hMET_3Jb,makeL1(),makeL2());
	cMET_3Jb->Write();
	
	TCanvas *cST_3Jb = newTCanvas("cST_3Jb");
	Arrange1(cST_3Jb,hST_3Jb,makeL1(),makeL2());
	cST_3Jb->Write();
	
	TCanvas *cPtGG_3Jb = newTCanvas("cPtGG_3Jb");
	Arrange1(cPtGG_3Jb,hPtGG_3Jb,makeL1(),makeL2());
	cPtGG_3Jb->Write();
	
	TCanvas *cHT_3Jb = newTCanvas("cHT_3Jb");
	Arrange1(cHT_3Jb,hHT_3Jb,makeL1(),makeL2());
	cHT_3Jb->Write();
	
	TCanvas *cMHT_3Jb = newTCanvas("cMHT_3Jb");
	Arrange1(cMHT_3Jb,hMHT_3Jb,makeL1(),makeL2());
	cMHT_3Jb->Write();

		//require a met>20
	TCanvas *cST_metCut = newTCanvas("cST_metCut");
	Arrange1(cST_metCut,hST_metCut,makeL1(),makeL2());
	cST_metCut->Write();
	
	TCanvas *cPtGG_metCut = newTCanvas("cPtGG_metCut");
	Arrange1(cPtGG_metCut,hPtGG_metCut,makeL1(),makeL2());
	cPtGG_metCut->Write();
	
	TCanvas *cHT_metCut = newTCanvas("cHT_metCut");
	Arrange1(cHT_metCut,hHT_metCut,makeL1(),makeL2());
	cHT_metCut->Write();
	
	TCanvas *cMHT_metCut = newTCanvas("cMHT_metCut");
	Arrange1(cMHT_metCut,hMHT_metCut,makeL1(),makeL2());
	cMHT_metCut->Write();
	
	
	
		//plot the Two background curves and the estimate between them and the center curve
		//put the subtracted spectrum belown it. 
		//Make some of this into fuctions; you'll use them several times.  
	

	
	
	fplots->Close();
	fin.Close();
}//end format plots

void diphoMassPlot(TH1F* hdiPhoMass, TCanvas* canv, TF1* fitcurve){
	canv->cd();
	PrettyHist(hdiPhoMass);
	float ymax = 0.5*hdiPhoMass->GetMaximum();
	hdiPhoMass->Draw();
	TLine *L_tag_ub = new TLine(tag_ub,0.,tag_ub,ymax);
	TLine *L_tag_lb = new TLine(tag_lb,0.,tag_lb,ymax);
	L_tag_ub->SetLineColor(4);
	L_tag_lb->SetLineColor(4);
	TLine *L_usb_lb = new TLine(usb_lb,0.,usb_lb,ymax);
	TLine *L_usb_ub = new TLine(usb_ub,0.,usb_ub,ymax);
	L_usb_lb->SetLineColor(2);
	L_usb_ub->SetLineColor(2);
	TLine *L_lsb_lb = new TLine(lsb_lb,0.,lsb_lb,ymax);
	TLine *L_lsb_ub = new TLine(lsb_ub,0.,lsb_ub,ymax);
	L_lsb_lb->SetLineColor(2);
	L_lsb_ub->SetLineColor(2);
	L_tag_ub->Draw("same");
	L_tag_lb->Draw("same");
	L_usb_lb->Draw("same");
	L_usb_ub->Draw("same");
	L_lsb_lb->Draw("same");
	L_lsb_ub->Draw("same");
	fitcurve->Draw("same");
}


	//make the legends for Arrange1, allow the option of changing the position. 
TLegend* makeL1(float f1,float f2,float f3,float f4){
		//TLegend* makeL1(float f1=0.652548,float f2=0.663899,float f3=0.852528,float f4=0.864219){
	TLegend * l1 = new TLegend(f1, f2, f3, f4);
	PrettyLegend(l1);
	return l1;
}
TLegend* makeL2(float f1,float f2,float f3,float f4){
		//TLegend* makeL2(float f1=0.651267,float f2=0.660256,float f3=0.851246,float f4=0.860577){
	TLegend * l2 = new TLegend(f1, f2, f3, f4); 
	PrettyLegend(l2);

	return l2;
}
void Arrange1(TCanvas* c, TH1F** h, TLegend* l1, TLegend* l2){
	c->Divide(1,2);
	c->cd(1);
	PrettyHist(h[5],4);
	PrettyHist(h[1]);
	PrettyHist(h[6],kGreen);
	PrettyHist(h[3],2);
	PrettyHist(h[4]);
	PrettyMarker(h[5],4);
	PrettyMarker(h[1]);
	PrettyMarker(h[6],kGreen);
	PrettyMarker(h[3],2);
	PrettyMarker(h[4]);
//	h[5]->Scale(mHwidth/(lsb_ub-lsb_lb));//lsb scaled
//	h[6]->Scale(mHwidth/(usb_ub-usb_lb));//usb scaled
	SameRange(h[5],h[6],h[1]);
	h[5]->Draw("ep");
	h[6]->Draw("epsame");
//	h[3]->Draw("epsame");//bkg
	h[1]->Draw("epsame");//tag
	c->cd(2);
	h[4]->Draw("ep");//bkg subtracted tag
	
	c->cd(1);
	l1->AddEntry(h[1],"tag region");
		//	l1->AddEntry(hMET[3],"Background");
	l1->AddEntry(h[5],"Low M sideband");
	l1->AddEntry(h[6],"Hi M sideband");		
	l1->Draw("same");
	c->cd(2);
	l2->AddEntry(h[4],"bkg subtracted tag");
	l2->Draw("same");	
}


void LoadHistSet(TH1F** h, TFile* fin, TString prefix){
	TString names[7];
	for (int i = 0; i<7; i++) {
		names[i] = "h";
		names[i]+= prefix;
	}
	names[0]+="_lowSB";
	names[1]+="_tag";  
	names[2]+="_upperSB";      
	names[3]+="_bkg";          
	names[4]+="_tag_subbkg";   
	names[5]+="_lowSB_scaled"; 
	names[6]+="_upperSB_scaled";
	
	for (int i=0; i < nPhoMassAndBkgDists; i++) h[i] = (TH1F*) fin->Get(names[i]);
}
