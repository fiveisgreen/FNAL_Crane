#define ana_job_2photon_2012b_PRv1_skim_cxx
	//#ifndef _CUTS_H // if not defined
	//#define _CUTS_H
#include "ana_job_2photon_2012b_PRv1_skim.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TAxis.h"
#include "TH1.h"
#include "TMath.h"
#include <TH3.h>
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TF1.h"
#include <iostream>
//#include "quicksave.C"
//#include "CMSStyle.C"
#include "utilities.h"
#include "cuts.h"
#include "params_arg.h"
#include "GetError.h"
using namespace std;
using namespace params;

void fitmgg(TH1F* hmgg, float lb, float ub, TGraphErrors* g, TF1* fitcurve, float& chi2, float * fit_parameters, float * fit_parameter_errors);
void get_bkg_integral(float* fit_parameters, float* fit_parameter_errors, float & B_integral, float & B_integral_error);
float expo_integral(float * params);
void find_bkg_with_fit(TH1F** h, float B_integral, float B_integral_error, float lsb_int, float usb_int);
void find_bkg(TH1F** h);//obsolete


void ana_job_2photon_2012b_PRv1_skim::Loop()
{
	//CMSStyle();
	if (fChain == 0) return;

	fChain->SetBranchStatus("*",0); //turns off all branches
	fChain->SetBranchStatus("rho",1);//turn them on one by one. 
	fChain->SetBranchStatus("nPU",1);
	fChain->SetBranchStatus("nPho",1);
	fChain->SetBranchStatus("phoE",1);
	fChain->SetBranchStatus("phoEt",1);
	fChain->SetBranchStatus("phoEta",1);
	fChain->SetBranchStatus("phoPhi",1);
	fChain->SetBranchStatus("phoR9",1);
	fChain->SetBranchStatus("phoTrkIsoHollowDR04",1);
	fChain->SetBranchStatus("phoEcalIsoDR04",1);
	fChain->SetBranchStatus("phoHcalIsoDR04",1);
	fChain->SetBranchStatus("phoTrkIsoHollowDR03",1);
	fChain->SetBranchStatus("phoEcalIsoDR03",1);
	fChain->SetBranchStatus("phoHcalIsoDR03",1);
	fChain->SetBranchStatus("phoHoverE",1);
	fChain->SetBranchStatus("phoSigmaIEtaIEta",1);
	fChain->SetBranchStatus("phoSCEta",1);
	fChain->SetBranchStatus("phohasPixelSeed",1);
	
	fChain->SetBranchStatus("nHLT",1);
	fChain->SetBranchStatus("HLT",1);
	fChain->SetBranchStatus("HLTIndex",1);
	fChain->SetBranchStatus("nVtx",1);
	fChain->SetBranchStatus("vtx",1);
	
	fChain->SetBranchStatus("run",1);
	fChain->SetBranchStatus("event",1);
	fChain->SetBranchStatus("lumis",1);
	
	 fChain->SetBranchStatus("MET",1);
	 fChain->SetBranchStatus("METPhi",1);
	 fChain->SetBranchStatus("METsumEt",1);
	 
	 fChain->SetBranchStatus("pfMET",1);
	 fChain->SetBranchStatus("pfMETPhi",1);
	 fChain->SetBranchStatus("pfMETsumEt",1);

	 fChain->SetBranchStatus("recoPfMET",1);
	 fChain->SetBranchStatus("recoPfMETPhi",1);
	 fChain->SetBranchStatus("recoPfMETsumEt",1);
	 fChain->SetBranchStatus("recoPfMETmEtSig",1);
	 fChain->SetBranchStatus("nJet",1);
	 fChain->SetBranchStatus("jetPt",1);   
	 fChain->SetBranchStatus("jetEta",1);   
	 fChain->SetBranchStatus("jetPhi",1);   
	 fChain->SetBranchStatus("jetEt",1);   
	 fChain->SetBranchStatus("jetArea",1);   
	 fChain->SetBranchStatus("jetMVAs",1);   
	fChain->SetBranchStatus("jetWPLevels",1);   
	
	fChain->SetBranchStatus("jetCombinedSecondaryVtxBJetTags",1);   
	fChain->SetBranchStatus("jetCombinedSecondaryVtxMVABJetTags",1);   
	fChain->SetBranchStatus("jetJetProbabilityBJetTags",1);   
	fChain->SetBranchStatus("jetJetBProbabilityBJetTags",1);   
	fChain->SetBranchStatus("jetTrackCountingHighPurBJetTags",1);
	fChain->SetBranchStatus("jetMVAs",1);
	fChain->SetBranchStatus("jetWPLevels",1);
	
	fChain->SetBranchStatus("nMu",1);
	fChain->SetBranchStatus("muTrg",1);   
	fChain->SetBranchStatus("muEta",1);   
	 fChain->SetBranchStatus("muPhi",1);   
	 fChain->SetBranchStatus("muCharge",1);   
	 fChain->SetBranchStatus("muPt",1);   
	 fChain->SetBranchStatus("muPz",1);   
	 fChain->SetBranchStatus("muIsoTrk",1);   
	 fChain->SetBranchStatus("muIsoCalo",1);   
	 fChain->SetBranchStatus("muIsoEcal",1);   
	 fChain->SetBranchStatus("muIsoHcal",1);   
	 
	 fChain->SetBranchStatus("nEle",1);
	 fChain->SetBranchStatus("eleCharge",1);   
	 fChain->SetBranchStatus("elePt",1);   
	 fChain->SetBranchStatus("eleEta",1);   
	 fChain->SetBranchStatus("elePhi",1);   
	 fChain->SetBranchStatus("eleSCEta",1);   
	 fChain->SetBranchStatus("eleSCPhi",1);   
	 fChain->SetBranchStatus("eleVtx",1);   
	 fChain->SetBranchStatus("eleHoverE",1);   
	 fChain->SetBranchStatus("eleEoverP",1);   
	 fChain->SetBranchStatus("elePin",1);   
	 fChain->SetBranchStatus("elePout",1);   
	 fChain->SetBranchStatus("eleSigmaIEtaIEta",1);   
	 fChain->SetBranchStatus("eleIsoTrkDR03",1);   
	 fChain->SetBranchStatus("eleIsoEcalDR03",1);   
	 fChain->SetBranchStatus("eleIsoHcalDR03",1);   
	 fChain->SetBranchStatus("eleIsoHcalSolidDR03",1);   
	 fChain->SetBranchStatus("eleIsoTrkDR04",1);   
	 fChain->SetBranchStatus("eleIsoEcalDR04",1);   
	 fChain->SetBranchStatus("eleIsoHcalDR04",1);   
	 fChain->SetBranchStatus("eleIsoHcalSolidDR04",1);   

	
	TFile * foutroot = new TFile(outroot.c_str(),"RECREATE");
	foutroot->cd();
	TTree * mytree =fChain->CloneTree(0);
	
	
	TH1F* hdiPhoMass = new TH1F("hdiPhoMass","Di Photon Mass Sectrum",PhoMassNBins,PhoMassMin,PhoMassMax);
	
	TH1F * hMET[nPhoMassAndBkgDists];
	for (int i=0; i < nPhoMassAndBkgDists; i++) hMET[i] = new TH1F(RandomString(6),"",METNBins,METMin,METMax);
	NameHist(hMET[0],"hMET_lowSB","MET Lower Side Band");
	NameHist(hMET[1],"hMET_tag","MET in Higgs Tag Region");
	NameHist(hMET[2],"hMET_upperSB","MET Upper Side Band");
	NameHist(hMET[3],"hMET_bkg","MET Background to Higgs Tag Region");
	NameHist(hMET[4],"hMET_tag_subbkg","MET Background Subtracted Higgs Tag Region");
	NameHist(hMET[5],"hMET_lowSB_scaled","Scaled MET Lower Side Band");
	NameHist(hMET[6],"hMET_upperSB_scaled","Scaled MET Upper Side Band");
	
	
	
		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% END Prepare Histograms 
	
		//cut flow
	int ncutflow = 20;
	Long64_t cutflow[ncutflow];
	for(int i=0;i<ncutflow;i++) cutflow[i]=0;
	TString  cutflow_lables[ncutflow];
	cutflow_lables[0] = "no cuts";
	cutflow_lables[1] = "have 2 photons";
	cutflow_lables[2] = "have tight lead photons";
	cutflow_lables[3] = "are in some region";
	cutflow_lables[4] = "are in tag region";
	cutflow_lables[5] = "are in sb region";
	cutflow_lables[6] = "are in usb region";
	cutflow_lables[7] = "are in lsb region";
	
	int lsb_int = 0;//integrals of the upper and lower side band. 
	int usb_int = 0;
	
	
		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% LOOP !
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<1000000;jentry++) {
			//for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		
		cutflow[0]++;//no cuts
		if(jentry%10000 ==0) cout<<"jentry "<<jentry<<endl;
		
		if (nPho < 2) continue; 
		cutflow[1]++;//have 2 photons
		
		bool photons_pass = true;
		for (int i=0; i<2; i++) {
			photons_pass &= is_tight_pho(	
			 phoEt[i],
			 phoSCEta[i],
			 phoTrkIsoHollowDR04[i],
			 phoEcalIsoDR04[i],
			 phoHcalIsoDR04[i],
			 phoHoverE[i],
			 phoSigmaIEtaIEta[i],
			 phohasPixelSeed[i],
			 rho25);
		}
		if (!photons_pass) continue;
		cutflow[2]++;//have tight lead photons
		
		TLorentzVector Pho[nPho];
		for (int i=0; i<2; i++) {
			Pho[i].SetPtEtaPhiM(phoEt[i],phoEta[i],phoPhi[i],0.f);
		}
		TLorentzVector gg = Pho[0]+Pho[1];
		float mgg = gg.M();
		hdiPhoMass->Fill(mgg);
		
		
			//Select tag and side band regions
		bool passmass = false;
		if (mgg > lsb_lb && mgg < lsb_ub) { // lower side band 
			passmass = true;
			cutflow[5]++;//are in sb region
			cutflow[7]++;//are in lsb region
			hMET[0]->Fill(pfMET);
			lsb_int++;
		}
		else if(mgg > tag_lb && mgg < tag_ub){ //tag region
			passmass = true;
			cutflow[4]++;//are in tag region
			hMET[1]->Fill(pfMET);
		}
		else if(mgg > usb_lb && mgg < usb_ub){ // upper side band
			passmass = true;
			cutflow[5]++;//are in sb region
			cutflow[6]++;//are in usb region
			hMET[2]->Fill(pfMET);
			usb_int++;
		}
		if (!passmass) continue;
		else cutflow[3]++;//are in some region
		
		mytree->Fill();
		
	}//end for all events
	mytree->Write();

	
		//support 
	float B_integral, B_integral_error;
	TF1* mgg_fit_curve;
	TGraphErrors* g;
	float chi2;
	float* fit_parameters;
	float* fit_parameter_errors;
	
	fitmgg(hdiPhoMass,80.,160.,g,mgg_fit_curve,chi2,fit_parameters, fit_parameter_errors);
	get_bkg_integral(fit_parameters, fit_parameter_errors, B_integral, B_integral_error);
	find_bkg_with_fit(hMET,B_integral, B_integral_error, lsb_int, usb_int);
	//	find_bkg(hMET);

	hdiPhoMass->Write();
	for (int i=0; i < nPhoMassAndBkgDists; i++) hMET[i]->Write();
	
	foutroot->Close();
	
		//repport
	for(int i=0; i<ncutflow;i++){
		cout << cutflow[i] << " " << cutflow_lables[i] << endl;
	}
	
}


void find_bkg(TH1F** h){
		//Take In an array of TH1F's. 
		//calculate the background, from [0] and [2] and store it in [3]
	for(int i=0;i<nPhoMassAndBkgDists;i++) h[i]->Sumw2();
	h[3]->Add(h[0],h[2],mHwidth/(lsb_ub-lsb_lb),mHwidth/(usb_ub-usb_lb));//apply weights to adjust for the difference in region width
	//h[3]->Add(h[0],h[2]);
	h[3]->Scale(0.5);//finish the average
	h[4]->Add(h[1],h[3],1.,-1.); //subtract the bkg. 
}//obsolete; end find_bkg

void fitmgg(TH1F* hmgg, float lb, float ub, TGraphErrors* g, TF1* fitcurve, float& chi2, float * fit_parameters, float * fit_parameter_errors){
		//fit an exponential to hmgg within (lb, ub), but excluding the tag region. 
	fit_parameters = new float[2];
	fit_parameter_errors = new float[2];
	fit_parameters[0] = 0.; fit_parameters[1] = 0.;
	fit_parameter_errors[0] = 0.;	fit_parameter_errors[1] = 0.;
	
	int lb_bin, ub_bin, higgslb_bin, higgsub_bin;
	int npoints = 0;
	vector<float> xvals;
	vector<float> yvals;
	vector<float> xerr;
	vector<float> yerr;
	
	lb_bin = hmgg->GetBin(lb)+1;
	ub_bin = hmgg->GetBin(ub)-1;
	higgslb_bin = hmgg->GetBin(tag_lb);
	higgsub_bin = hmgg->GetBin(tag_ub);
	
	for (int i=lb_bin; i<=ub_bin; i++) {
		if (i >= higgslb_bin && i <= higgsub_bin) continue;
		xvals.push_back(hmgg->GetXaxis()->GetBinCenter(i));
		yvals.push_back(hmgg->GetBinContent(i));
		xerr.push_back(0.);
		yerr.push_back(hmgg->GetBinError(i));
		npoints++;
	}
	
		//do some immoral container conversions.
	float fxvals[xvals.size()];
	float fyvals[yvals.size()];
	float fxerr[xerr.size()];
	float fyerr[yerr.size()];
	for (int i=0;i<xvals.size();i++) {
		fxvals[i]=xvals[i];
		fyvals[i]=yvals[i];
		fxerr[i]=xerr[i];
		fyerr[i]=yerr[i];
	}
	
	g = new TGraphErrors(xvals.size(),fxvals,fyvals,fxerr,fyerr);
	
		//do fit
	fitcurve = new TF1("mggfit","expo",lb,ub);
		//form y = exp(p0 + p1*x)
	int status = g->Fit(fitcurve);
	printf("fit status: %i \n",status);
		//		TFitResultPtr res = g->Fit(fitcurve,"S"); //this doesn't actually work >:[]
		//if this gives you trouble, look here:
		//http://root.cern.ch/root/html/TGraph.html#TGraph:Fit@1
	
		//TFitResultPtr r = h->Fit(myFunc,"S");
		//	TMatrixDSym cov = r->GetCovarianceMatrix();  //  to access the covariance matrix
	
		//get chi2 per degree of freedom. 
	chi2 = fitcurve->GetChisquare()/((float)(npoints - 3));
		//	chi2 = res->Chi2()/((float)(npoints - 3)); // to retrieve the fit chi2
	printf("chi2 from fit: %f \n",chi2);
		//	printf("chi2 from fit: %f from ResultPointer %f\n",chi2,res.Chi2()/((float)(npoints - 3)));

	

		//could also do that with Int_t TF1::GetNumberFitPoints() const
		//or maybe TF1::GetNumberFreeParameters, but it should be the same thing (check)
	printf("my measure: %i GetNumberFitPoints %i, 	GetNumberFreeParameters %i GetNDF %i\n",
		   npoints - 3, fitcurve->GetNumberFitPoints(),	fitcurve->GetNumberFreeParameters(), fitcurve->GetNDF());
	
		//get params
//	fit_parameters[0] = res.Value(0);
//	fit_parameters[1] = res.Value(1);
//	fit_parameter_errors[0] = res.Error(0);
//	fit_parameter_errors[1] = res.Error(1);
	fit_parameters[0] = fitcurve->GetParameter(0);
	fit_parameters[1] = fitcurve->GetParameter(1);
	fit_parameter_errors[0] = fitcurve->GetParError(0);
	fit_parameter_errors[1] = fitcurve->GetParError(1);
	
}

void get_bkg_integral(float* fit_parameters, float* fit_parameter_errors, float & B_integral, float & B_integral_error){
		//fit_parameters = values of fit parameters. y = exp(fit_parameters[0] + fit_parameters[1]*mgg)
		//fit_parameter_errors are the fitter's uncertaintites in those fit_parameters.
		//B_integral is output; it's the integral of the background int the tag region
		//B_integral_error is output; it's the uncertainty in that integral from the uncertainty in the fit params. 
	float centralvals[4];
	float uncertainties[4];
	centralvals[0] = fit_parameters[0];
	centralvals[1] = fit_parameters[1];
	centralvals[2] = tag_lb;
	centralvals[3] = tag_ub;
	uncertainties[0] = fit_parameter_errors[0];
	uncertainties[1] = fit_parameter_errors[1];
	uncertainties[2] = 0.;
	uncertainties[3] = 0.;
	bool zero_limited[4] = {false, false, false,false};
	
	B_integral = expo_integral(centralvals);
	B_integral_error = GetError(expo_integral,4, centralvals, uncertainties,zero_limited);
}

float expo_integral(float * params){
		//	params[0] = p0;
		//	params[1] = p1;
		//	params[2] = x_low;
		//	params[3] = x_hi;
		//return TMath::Exp(p0)*p1*(TMath::Exp(-x_low/p1) - TMath::Exp(-x_hi/p1)); //but I expect p1 to be negative, so that's no good. 
		//	return TMath::Exp(p0)*p1*(TMath::Exp(x_low/p1) - TMath::Exp(x_hi/p1));
	return TMath::Exp(params[0])*params[1]*(TMath::Exp(params[2]/params[1]) - TMath::Exp(params[3]/params[1]));
}
															  															  

void find_bkg_with_fit(TH1F** h, float B_integral, float B_integral_error, float lsb_int, float usb_int){
		//Take In an array of TH1F's. 
		//calculate the background, from [0] and [2] and store it in [3]
	for(int i=0;i<nPhoMassAndBkgDists;i++) h[i]->Sumw2();
	
		//Scale side bands and set error 
	for (int ibin = 0; ibin <= h[5]->GetNbinsX()+1; ibin++) {
			//Scale them
		h[5]->SetBinContent(ibin,(h[0]->GetBinContent(ibin)*B_integral/lsb_int));
		h[6]->SetBinContent(ibin,(h[2]->GetBinContent(ibin)*B_integral/usb_int));
			//SetErrors
		h[5]->SetBinError(ibin, h[5]->GetBinContent(ibin)*sqrt(pow((h[0]->GetBinError(ibin)/h[0]->GetBinContent(ibin)),2) +
														  (1./lsb_int)+pow(B_integral_error/B_integral,2)));
						  
		h[6]->SetBinError(ibin, h[6]->GetBinContent(ibin)*sqrt(pow((h[2]->GetBinError(ibin)/h[2]->GetBinContent(ibin)),2) +
														  (1./usb_int)+pow(B_integral_error/B_integral,2)));
	}
	
	h[3]->Add(h[5],h[6]);
	h[3]->Scale(0.5);//finish the average
	h[4]->Add(h[1],h[3],1.,-1.); //subtract the bkg. 
}

//#endif



