#include "CMSStyle.C"
#include "params_arg.h"
//#include "TMatrixT.h"
#include "TMatrixD.h"
#include <iostream>
#include "TFile.h"
#include <TH1F.h>
#include "TAxis.h"
#include <TStyle.h>
#include <TCanvas.h>
#include "TLegend.h"
using namespace params;
using namespace std;

	//     ______        __                  _____          __           __
	//    / __/ /__ ____/ /________  ___    / ___/__  ___  / /____ ___  / /_
	//   / _// / -_) __/ __/ __/ _ \/ _ \  / /__/ _ \/ _ \/ __/ -_) _ \/ __/
	//  /___/_/\__/\__/\__/_/__\___/_//_/ _\___/\___/_//_/\__/\__/_//_/\__/
	//                    / __/_ __ ___  / /__  _______ ____
	//                   / _/ \ \ // _ \/ / _ \/ __/ -_) __/
	//                  /___//_\_\/ .__/_/\___/_/  \__/_/
	//                           /_/


	//////////////////////////////
void EleContent4();
void makeMetDist(TH1F* bkg, TH1F* gg, TH1F* eg,TH1F* ee, short whichshift);
void makePtDist( TH1F* bkg, TH1F* gg, TH1F* eg,TH1F* ee, short whichshift);
float GetEleBkg(float gg, float eg, float ee, float geff, float eeff, float efg, float gfe,bool checkmath = false);
void Whichshift(short whichshift, short& shift_efg, short& shift_gfe, short& shift_eeff, short& shift_geff, short& shift_gg, short& shift_eg, short& shift_ee);
inline float Efg(float pt);
float phoEff(float pt);
float phoEff_UC(float pt);
	//////////////////////////////

void EleContent4(){
	CMSStyle();
	TFile* Fpvpv =  TFile::Open("plotsWithBackground_dataGLL12_PVPV_195fb.root");
	TFile* Felepho= TFile::Open("plotsWithBackground_dataGLL12_elepho_195fb.root");
	TFile* Feleele1=TFile::Open("plotsWithBackground_dataGLL12_eleele1_195fb.root");
	TFile* Feleele2=TFile::Open("plotsWithBackground_dataGLL12_eleele2_195fb.root");
	TFile* Feleele3=TFile::Open("plotsWithBackground_dataGLL12_eleele3_195fb.root");
	TFile* Feleele4=TFile::Open("plotsWithBackground_dataGLL12_eleele4_195fb.root");

	TH1F* h_pvpv_pt =     (TH1F*)Fpvpv->Get("hphoPt02JbMLgbar2_bkg");
	TH1F* h_elepho_pt = (TH1F*)Felepho->Get("hphoPt02JbMLgbar2_tag");
	TH1F* h_eleele_pt =(TH1F*)Feleele1->Get("hphoPt02JbMLgbar2_tag");
	h_eleele_pt->Add(  (TH1F*)Feleele2->Get("hphoPt02JbMLgbar2_tag"));
	h_eleele_pt->Add(  (TH1F*)Feleele3->Get("hphoPt02JbMLgbar2_tag"));
	h_eleele_pt->Add(  (TH1F*)Feleele4->Get("hphoPt02JbMLgbar2_tag"));

	TH1F* h_pvpv_met =      (TH1F*)Fpvpv->Get("hMET2JbMLgbar2_bkg");
	TH1F* h_elepho_met =  (TH1F*)Felepho->Get("hMET2JbMLgbar2_tag");
	TH1F* h_eleele_met = (TH1F*)Feleele1->Get("hMET2JbMLgbar2_tag");
		cout<<"ele integral 1 "<<h_eleele_met->Integral()<<endl;
	h_eleele_met->Add(   (TH1F*)Feleele2->Get("hMET2JbMLgbar2_tag"));
		cout<<"ele integral 2 "<<h_eleele_met->Integral()<<endl;
	h_eleele_met->Add(   (TH1F*)Feleele3->Get("hMET2JbMLgbar2_tag"));
		cout<<"ele integral 3 "<<h_eleele_met->Integral()<<endl;
	h_eleele_met->Add(   (TH1F*)Feleele4->Get("hMET2JbMLgbar2_tag"));
		cout<<"ele integral 4 "<<h_eleele_met->Integral()<<endl;

		///Make some histograms
	TH1F* h_elebkg_met[129];
	TH1F* h_elebkg_pt[129];
		//the first 128 are shifts, the 129th is the central value.
		//There are seven uncertainties that you wiggle: 
		//n pho pho 
		//n ele pho
		//n ele ele
		//photon efficiency
		//electron efficiency
		//photon to electron fake rate
		//electorn to photon fake rate
		//129 = 2^7 + 1
	for (short i=0; i<129; i++) {
		h_elebkg_met[i] = (TH1F*)h_pvpv_met->Clone(Form("elebkgmet%i",i));
		h_elebkg_met[i]->Reset();
		h_elebkg_pt[i] = (TH1F*)h_pvpv_pt->Clone(Form("elebkgpt%i",i));
		h_elebkg_pt[i]->Reset();
	}

		///do all the hard work
	for (short whichshift=0; whichshift<129; whichshift++) {
		makeMetDist(h_elebkg_met[whichshift],h_pvpv_met,h_elepho_met,h_eleele_met,whichshift);
		makePtDist(h_elebkg_pt[whichshift],h_pvpv_pt,h_elepho_pt,h_eleele_pt,whichshift);
	}//end for met

		///turn that into uncertainties
	for (short ibin=1; ibin <= h_elebkg_met[128]->GetXaxis()->GetNbins(); ibin++){
		float residual_sum = 0;
		for (short i=0; i<128; i++) {
			residual_sum += pow(h_elebkg_met[i]->GetBinContent(ibin) - h_elebkg_met[128]->GetBinContent(ibin),2);
		}
		h_elebkg_met[128]->SetBinError(ibin, sqrt(residual_sum/128.0));
	}
		//make uc for MET
	for (short ibin=1; ibin<=h_elebkg_pt[128]->GetXaxis()->GetNbins(); ibin++) {
		float residual_sum = 0;
		for (short i=0; i<128; i++) {
			residual_sum += pow(h_elebkg_pt[i]->GetBinContent(ibin) - h_elebkg_pt[128]->GetBinContent(ibin),2);
		}
		h_elebkg_pt[128]->SetBinError(ibin, sqrt(residual_sum/128.0));
	}

	TFile* fout = new TFile("elecontent.root","RECREATE");
	fout->cd();
	h_elebkg_pt[128]->SetTitle("Electron Background to 2JbMLgbar2;Pt (GeV)");
	SetRange(h_elebkg_pt[128]);
	h_elebkg_pt[128]->Write();
	h_elebkg_met[128]->SetTitle("Electron Background to 2JbMLgbar2;MET (GeV)");
	h_elebkg_met[128]->Write();
	
		///////////
	TCanvas * cMETmain = newTCanvas("cMETmain","cMETmain");
	cMETmain->cd();
	PrettyHist(h_pvpv_met);
	PrettyHist(h_elebkg_met[128],kRed);
	SetRange(h_pvpv_met);
	h_pvpv_met->SetTitle(";MET (GeV); # Events");
	h_pvpv_met->Draw("ep");
	RaiseRangeRoof(h_pvpv_met);
	h_elebkg_met[128]->SetTitle(";MET (GeV); # Events");
	h_elebkg_met[128]->Draw("epsame");
	TLegend * ll = new TLegend(0.432161, 0.708791, 0.63191, 0.907967);
	PrettyLegend(ll);
	ll->AddEntry(h_pvpv_met,"Data Driven Background");
	ll->AddEntry(h_elebkg_met[128],"Electron Background");
	ll->Draw("same");
	cMETmain->Write();
//	cMETmain->SaveAs("EleBkg_met_main.pdf");
//	cMETmain->SaveAs("EleBkg_met_main.gif");

		///////////
	TCanvas * cPTmain = newTCanvas("cPTmain","cPTmain");
	cPTmain->cd();
	PrettyHist(h_pvpv_pt);
	PrettyHist(h_elebkg_pt[128],kRed);
	h_pvpv_pt->SetTitle(";P_{t} (GeV);# Events");
	h_pvpv_pt->Draw("ep");
	SetRange(h_pvpv_pt);
	RaiseRangeRoof(h_pvpv_pt,1.8);
	h_elebkg_pt[128]->SetTitle(";P_{t} (GeV);# Events");
	h_elebkg_pt[128]->Draw("epsame");
	ll->Draw("same");
	cPTmain->Write();
//	cPTmain->SaveAs("EleBkg_pt_main.pdf");
//	cPTmain->SaveAs("EleBkg_pt_main.gif");
		///////////
	TCanvas * cMETsyst = newTCanvas("cMETsyst","cMETsyst");
	cMETsyst->cd();
	PrettyHist(h_elebkg_met[128],kRed);
	SetRange(h_elebkg_met[128]);
	RaiseRangeRoof(h_elebkg_met[128],2.4);
	h_elebkg_met[128]->Draw("ep");
	for (short i=0; i<128; i++) h_elebkg_met[i]->Draw("same");
	h_elebkg_met[128]->Draw("epsame");
	TLegend * l = new TLegend( 0.463568,0.800824,0.663317,0.925824 );
	PrettyLegend(l);
	l->AddEntry(h_elebkg_met[128],"Electron Background");
	l->AddEntry(h_elebkg_met[0],"Bkg estimate variations");
	l->Draw("same");
	cMETsyst->Write();
//	cMETsyst->SaveAs("EleBkg_met_syst.pdf");
//	cMETsyst->SaveAs("EleBkg_met_syst.gif");

		///////////
	TCanvas * cPTsyst = newTCanvas("cPTsyst","cPTsyst");
	cPTsyst->cd();
	PrettyHist(h_elebkg_pt[128],kRed);
	SetRange(h_elebkg_pt[128]);
	RaiseRangeRoof(h_elebkg_pt[128],1.5);
	h_elebkg_pt[128]->Draw("ep");
	RaiseRangeRoof(h_elebkg_pt[128]);
	for (short i=0; i<128; i++) h_elebkg_pt[i]->Draw("same");
	h_elebkg_pt[128]->Draw("epsame");
	l->Draw("same");
	cPTsyst->Write();
//	cPTsyst->SaveAs("EleBkg_pt_syst.pdf");
//	cPTsyst->SaveAs("EleBkg_pt_syst.gif");

	fout->Close();
	Fpvpv->Close();
	Felepho->Close();
	Feleele1->Close();
	Feleele2->Close();
	Feleele3->Close();
	Feleele4->Close();
}

void makeMetDist(TH1F* bkg, TH1F* gg, TH1F* eg,TH1F* ee, short whichshift){

	short shift_efg, shift_gfe, shift_eeff, shift_geff, shift_gg, shift_eg, shift_ee;

	Whichshift(whichshift, shift_efg, shift_gfe, shift_eeff, shift_geff, shift_gg, shift_eg, shift_ee);

	for (short i=1; i<=bkg->GetXaxis()->GetNbins(); i++) {
		if(whichshift==128) printf("MET dist bin = %i\n",i);
		bkg->SetBinContent(i,GetEleBkg(
									   gg->GetBinContent(i) + shift_gg*gg->GetBinError(i),
									   eg->GetBinContent(i) + shift_eg*eg->GetBinError(i),
									   ee->GetBinContent(i) + shift_ee*ee->GetBinError(i),
									   0.875 + shift_geff*0.025,//from Poter and Andrew Askew
									   0.875 + shift_eeff*0.05,//assumed to match pho; made up
									   0.0200 + shift_efg*0.00021, //from Yutaro
									   0.11 + shift_gfe*0.05, //made up
									   whichshift==128) );
	}
}//end for met

void makePtDist(TH1F* bkg, TH1F* gg, TH1F* eg,TH1F* ee, short whichshift){

	short shift_efg, shift_gfe, shift_eeff, shift_geff, shift_gg, shift_eg, shift_ee;

	Whichshift(whichshift, shift_efg, shift_gfe, shift_eeff, shift_geff, shift_gg, shift_eg, shift_ee);

	for (short i=1; i<=bkg->GetXaxis()->GetNbins(); i++) {
		if(whichshift==128) printf("Pt dist bin=%i\n",i);
		float x = bkg->GetXaxis()->GetBinCenter(i);
		bkg->SetBinContent(i,GetEleBkg(
									   gg->GetBinContent(i) + shift_gg*gg->GetBinError(i),
									   eg->GetBinContent(i) + shift_eg*eg->GetBinError(i),
									   ee->GetBinContent(i) + shift_ee*ee->GetBinError(i),
									   phoEff(x) + shift_geff*phoEff_UC(x), //from Poter and Andrew
									   phoEff(x) + 2*shift_eeff*phoEff_UC(x), //assume it matches the photon, but more uncertain
									   Efg(x) + shift_efg*0.0012,//from linear fit
									   0.11 + shift_gfe*0.05, //made up
									   whichshift==128));
	}
}//end for Pt

float GetEleBkg(float gg, float eg, float ee, float geff, float eeff, float efg, float gfe,	bool checkmath){
		//takes the numbers of pho+pho (gg), pho+ele (eg), and ele+ele
		//then takes photon efficiency (geff), electonr efficiency (eeff),
		//electron faking photon probablility (efg) and the photon faking electon probablity (gfe)
		//and returns the electron content of gg

	efg *= geff*eeff;//necessary to undo the normalization that Yutaro applied. 
	gfe *= geff*eeff;

	TMatrixD obs(3,1);//collumn vector
	obs[0][0] = gg;
	obs[1][0] = eg;
	obs[2][0] = ee;

	if(checkmath){
		printf("\nObs\n");
		printf("%5.3f\n%5.3f\n%5.3f\n",obs[0][0],obs[1][0],obs[2][0]);
	}

	TMatrixD eff(3,3);
	/*gg->PP*/ eff[0][0] = geff*geff; /*gg->PE*/ eff[0][1] = 2*geff*gfe;          /*gg->EE*/ eff[0][2] = gfe*gfe;
	/*eg->PP*/ eff[1][0] = geff*efg;  /*eg->PE*/ eff[1][1] = geff*eeff + efg+gfe; /*eg->EE*/ eff[1][2] = eeff*gfe;
	/*ee->PP*/ eff[2][0] = efg*efg;   /*ee->PE*/ eff[2][1] = 2*eeff*efg;          /*ee->EE*/ eff[2][2] = eeff*eeff;
	if(checkmath){
		printf("\nEff\n");
		printf("%5.3f %5.3f %5.3f\n", eff[0][0], eff[0][1], eff[0][2]);
		printf("%5.3f %5.3f %5.3f\n", eff[1][0], eff[1][1], eff[1][2]);
		printf("%5.3f %5.3f %5.3f\n", eff[2][0], eff[2][1], eff[2][2]);
	}
//	Double_t det1;
	eff.InvertFast();//InvertFast is claimed to give an order of magnitude speed improvment over Invert
		//http://root.cern.ch/root/html/tutorials/matrix/invertMatrix.C.html

	if(checkmath){
		printf("\nInverse\n");
		printf("%5.3f %5.3f %5.3f\n", eff[0][0], eff[0][1], eff[0][2]);
		printf("%5.3f %5.3f %5.3f\n", eff[1][0], eff[1][1], eff[1][2]);
		printf("%5.3f %5.3f %5.3f\n", eff[2][0], eff[2][1], eff[2][2]);
	}
//	TMatrixD acutal = inverse*obs;
	TMatrixD acutal = eff*obs;
	if(checkmath){
		printf("\nActual\n");
		printf("%5.3f\n%5.3f\n%5.3f\n",acutal[0][0],acutal[1][0],acutal[2][0]);
		printf("\nBkg %f, of which we predict %f is ele\n",gg,acutal[1][0]*geff*efg + acutal[2][0]*efg*efg);
	}
	return acutal[1][0]*geff*efg + acutal[2][0]*efg*efg;
}//end GetEleBkg

void Whichshift(short whichshift, short& shift_efg, short& shift_gfe, short& shift_eeff, short& shift_geff, short& shift_gg, short& shift_eg, short& shift_ee){
		//0-31 set these to +- 1 in binary sequence.
		//whichshift == 128 sets them all to zero = does main.
	if(whichshift >= 128){
		shift_efg = shift_gfe = shift_eeff = shift_geff = shift_gg = shift_eg = shift_ee = 0;
		return;
	}
		//access the individual bits of whichshift so as to count in binary order. 
	shift_efg = (whichshift & 1) >> 0?1:-1;
	shift_gfe = (whichshift & 2) >> 1?1:-1;
	shift_eeff =(whichshift & 4) >> 2?1:-1;
	shift_geff =(whichshift & 8) >> 3?1:-1;
	shift_gg = (whichshift & 16) >> 4?1:-1;
	shift_eg = (whichshift & 32) >> 5?1:-1;
	shift_ee = (whichshift & 64) >> 6?1:-1;
}

inline float Efg(float pt){return 0.0280688 - 0.000184919*pt;}
	//linear fit to Yutaro's f(e->g)(Pt)
	//acurate to within 0.0012
	//unbinned, use 0.0200 +- 0.00021

float phoEff(float pt){
	//the falt value is 0.87.5% +- 2.5%
	//that is, eff_Loose * eff_PV/eff_EV = 0.92 * 0.78/0.82 = 0.875 = Loose_PV efficiency. 
	//with uncertainty 
	//(0.92*0.78/0.82)*sqrt((0.02/0.92)^2+(0.01/0.82)^2+(0.01/0.78)^2) = 0.0245
	//the 0.82 and 0.78 are pulled off Andrew's PV plots, giving us a w conversion between PV and EV
	//the rest are off of Poter's official performance plots. 
	float w = 0.78/0.82;
	if(pt < 30) return w*0.905;
	else if(pt < 40) return w*0.92;
	else if(pt < 50) return w*0.93;
	else return w*0.94;
}

float phoEff_UC(float pt){
	//return the uncertiainty in phoEff(pt);
	float c = pow(0.02/0.82,2) + pow(0.02/0.78,2);
	if(pt < 30) return sqrt(pow(0.005/0.905,2)+c)*phoEff(pt);
	else if(pt < 40) return sqrt(pow(0.005/0.92,2)+c)*phoEff(pt);
	else if(pt < 50) return sqrt(pow(0.010/0.93,2)+c)*phoEff(pt);
	else return sqrt(pow(0.010/0.94,2)+c)*phoEff(pt);
}

/*      TLatex * TEX_CMSPrelim = new TLatex(1.177136,0.953368,"CMS Preliminary 2013");
 PrettyLatex(TEX_CMSPrelim,0.03);
 TEX_CMSPrelim->Draw("same");

 TLatex * TEX_E_TeV = new TLatex(0.800251,0.953368,"#sqrt{s} = 8 TeV");
 PrettyLatex(TEX_E_TeV,0.03);
 TEX_E_TeV->Draw("same");

 TLatex * TEX_lumi_fb = new TLatex(0.621859,0.953368,Form("#intL dt = %.0f fb^{-1}",Integrated_Luminosity_Data));
 PrettyLatex(TEX_lumi_fb,0.03);
 TEX_lumi_fb->Draw("same");*/

