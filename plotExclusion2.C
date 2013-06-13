#include <iostream>
#include <map>
#include "TCanvas.h"
#include "TFile.h"
#include "TH2.h"
#include "TString.h"
#include "TGraphSmooth.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//char* cms = "#bf{CMS Internal}";
char* cms = "#bf{CMS Preliminary}";

int obsColor = kBlack;
int obsStyle = 1;
int obsWidth = 3;
int obs1Width = 1;

int expColor = kBlack;
int expStyle = 2;
int expWidth = 3;

int exp1Fill = kGreen;
int exp1Color = kGreen;
int exp1Style = 1;
int exp1Width = 0;

int exp2Fill = kYellow;
int exp2Color = kYellow;
int exp2Style = 1;
int exp2Width = 0;

TFile* f;
TCanvas* c;
TCanvas* c1;
Int_t color = 1;

double getXsec(int par1, int par2, double &xsecLO, double &k, double &relErr_m, double &relErr_p) {
        xsecLO = 0; k = 1; relErr_m = relErr_p = 0.3; // PWZ put in to run through reading of xsec files faster, but temp plots won't get madde
        return true;
	std::ifstream xsecifs("XSec.txt");
	int key1, key2;
	bool found = false;
	while (xsecifs >> key1 >> key2 >> xsecLO) {
		if(key1 == par1 && key2 == par2) {
			found = true;
			break;
		}
	}
	k = 1; relErr_m = relErr_p = 0;
	/*while (xsecifs >> key1 >> key2 >> xsecLO >> k >> relErr_m >> relErr_p) {
		if(key1 == par1 && key2 == par2) {
			found = true;
			break;
		}
		}*/
	xsecifs.close();
	if(!found) {
		cout << "[PT] Could not determine cross-section information for point (" << par1 << "," << par2 << ")" << endl;
	}
	return found;
}

// overlay	0: no; 1: theory cross-section; 2: 95% observed upper limit; 3: 95% expected upper limit
void plotExclusion2(int overlay = 0, TString filename = "limitResuts_PZ.root") {
	gROOT->SetBatch();
	c = new TCanvas("c","Contour",0,0,800,600);
	gROOT->SetBatch(kFALSE);
	f = new TFile(filename);
	
	c1 = new TCanvas("c1", "Contour List", (overlay == 0) ? 700 : 800, 500);
        //c1 = new TCanvas("c1", "Contour List", (overlay == 0) ? 700 : 800, 600); // PWZ experimented with range
	c1->SetTopMargin(0.1);
	c1->SetBottomMargin(0.15);
	c1->SetLeftMargin(0.13);
	c1->SetRightMargin((overlay == 0) ? 0.03 : 0.17);
	
	Int_t nbinsx	= (hObs->GetXaxis()->GetXmax() - (hObs->GetXaxis()->GetXmin())) / hObs->GetXaxis()->GetBinWidth(0);
	Double_t xlow	= hObs->GetXaxis()->GetXmin();
	Double_t xup	= hObs->GetXaxis()->GetXmax();
	Int_t nbinsy	= (hObs->GetYaxis()->GetXmax() - hObs->GetYaxis()->GetXmin()) / hObs->GetYaxis()->GetBinWidth(0);
	Double_t ylow	= hObs->GetYaxis()->GetXmin();
	//Double_t ylow   = hObs->GetYaxis()->GetXmin() + hObs->GetYaxis()->GetBinWidth(0) / 2; //PWZ says this gets rid of empty white space, also causes warnings
	Double_t yup	= hObs->GetYaxis()->GetXmax();
	TH2F *hOverlayTheory = new TH2F("frame", "", nbinsx, xlow, xup, nbinsy, ylow, yup);
	hOverlayTheory->GetXaxis()->SetTitle("m_{#tilde{t}} (GeV)");
	hOverlayTheory->GetXaxis()->SetTitleSize(0.06);
	hOverlayTheory->GetXaxis()->SetLabelSize(0.05);
	hOverlayTheory->GetXaxis()->SetTitleOffset(1);
	//hOverlayTheory->GetYaxis()->SetTitle("m_{#tilde{H}} (GeV)");
	hOverlayTheory->GetYaxis()->SetTitle("Br(#tilde{#chi}_{1}^{0} #rightarrow h + G)");
	//hOverlayTheory->GetYaxis()->SetTitle("Br");
	hOverlayTheory->GetYaxis()->SetTitleSize(0.04);
	hOverlayTheory->GetYaxis()->SetLabelSize(0.03);
	hOverlayTheory->GetYaxis()->SetTitleOffset(1);
	if(overlay != 0) {
		hOverlayTheory->GetZaxis()->SetTitleSize(0.06);
		hOverlayTheory->GetZaxis()->SetLabelSize(0.05);
		hOverlayTheory->GetZaxis()->SetTitleOffset(0.9);
		if(overlay == 1) {
			hOverlayTheory->GetZaxis()->SetTitle("#sigma_{theory} (fb)");
		}
		if(fabs(overlay) == 2) {
			hOverlayTheory->GetZaxis()->SetTitle("#sigma^{observed}_{95%} (fb)");
		}
		if(fabs(overlay) == 3) {
			hOverlayTheory->GetZaxis()->SetTitle("#sigma^{expected}_{95%} (fb)");
		}
	}
	gStyle->SetOptStat(0);
	double xsecLO, k, relErr_m, relErr_p;
	TH2F *hk = new TH2F("k", "k", nbinsx, xlow, xup, nbinsy, ylow, yup);
	TH2F *hObs1p = new TH2F("hObs1p", "hObs1p", nbinsx, xlow, xup, nbinsy, ylow, yup);
	TH2F *hObs1m = new TH2F("hObs1m", "hObs1m", nbinsx, xlow, xup, nbinsy, ylow, yup);
	for(int i = 1; i <= hObs->GetXaxis()->GetNbins(); i++) {
		for(int j = 1; j <= hObs->GetYaxis()->GetNbins(); j++) {
			double par1 = hObs->GetXaxis()->GetBinCenter(i);
			double par2 = hObs->GetYaxis()->GetBinCenter(j);
                        if(par1 < par2 || !getXsec(par1, par2, xsecLO, k, relErr_m, relErr_p)) {
			  continue;
			}
			hOverlayTheory->Fill(par1, par2, xsecLO * 1000);
			hObs1p->Fill(par1, par2, 1 / (1 + relErr_p));
			hObs1m->Fill(par1, par2, 1 / (1 - relErr_m));
			hk->Fill(par1, par2, k);
		}
	}
	hOverlayTheory->Multiply(hk);
	hObs->Divide(hk);
	hObs1p->Multiply(hObs);
	hObs1m->Multiply(hObs);
	hExp->Divide(hk);
	hExp1p->Divide(hk);
	hExp1m->Divide(hk);
	hExp2p->Divide(hk);
	hExp2m->Divide(hk);
	if(overlay != 0) {
		if(overlay == 1) {
			hOverlayTheory->Draw("COLZ");
			gPad->SetLogz(1);
		} else {
			TH2D* hOverlayObs = hOverlayTheory->Clone("hOverlayObs");
			hOverlayObs->Multiply(hObs);
			TH2D* hOverlayExp = hOverlayTheory->Clone("hOverlayExp");
			hOverlayExp->Multiply(hExp);
			Double_t minimum = min(hOverlayObs->GetMinimum(0), hOverlayExp->GetMinimum(0));
			Double_t maximum = max(hOverlayObs->GetMaximum(), hOverlayExp->GetMaximum());
			if(fabs(overlay) == 2) {
				hOverlayObs->SetMinimum(minimum);
				hOverlayObs->SetMaximum(maximum);
				hOverlayObs->Draw("COLZ");
			}
			if(fabs(overlay) == 3) {
				hOverlayExp->SetMinimum(minimum);
				hOverlayExp->SetMaximum(maximum);
				hOverlayExp->Draw("COLZ");
			}
			if(overlay < 0) {
				gPad->SetLogz(1);
			}
		}
	} else {
		hOverlayTheory->Reset();
		hOverlayTheory->Draw();
	}
	
	TLatex text;
	text.SetNDC(true);
	text.SetTextAlign(12);
	text.SetTextFont(42);
	text.SetTextSize(0.036);
	text.DrawLatex(0.11, 0.94, cms);
	text.DrawLatex(0.45, 0.94, "#bf{#sqrt{s} = 8 TeV, #int L dt = 19.5 fb^{-1}}");
	
	if(overlay == 0) {
		TLine *l = new TLine(200, 200, 700, 700); // PWZ says this is for diagonal
		l->Draw("same");
	}
	
	c1->SetGrid(1, 1);
	double m1 = 0;
	double m2 = 0;
	TGraph* obs = 0;
	TGraph* obs1p = 0;
	TGraph* obs1m = 0;
	TGraph* exp = 0;
	TGraph* exp1p = 0;
	TGraph* exp1m = 0;
	TGraph* exp2p = 0;
	TGraph* exp2m = 0;
	cout << "=== doing obs" << endl;	obs = plotCurve(hObs, obsColor, obsStyle, 0); // PWZ changed to 0 from 1, pick -1 for list of curves, and start from 0 to whatever 
	cout << "=== doing obs1p" << endl;	obs1p = plotCurve(hObs1p, obsColor, obsStyle, 0); // ""  PWZ commented out theory uncertainties for now
	cout << "=== doing obs1m" << endl;	obs1m = plotCurve(hObs1m, obsColor, obsStyle, 0); // ""
	cout << "=== doing exp" << endl;	exp = plotCurve(hExp, expColor, expStyle, 0); // PWZ changed to 0 from 1
	if(overlay == 0) {
		cout << "=== doing exp1p" << endl;	exp1p = plotCurve(hExp1p, exp1Fill, exp1Style, 0); // ""
		cout << "=== doing exp1m" << endl;	exp1m = plotCurve(hExp1m, exp1Fill, exp1Style, 0);
		cout << "=== doing exp2p" << endl;	exp2p = plotCurve(hExp2p, exp2Fill, exp2Style, 0);
		cout << "=== doing exp2m" << endl;	exp2m = plotCurve(hExp2m, exp2Fill, exp2Style, 0);
	}
	//return;
	c1->cd();
	
	double legx1, legx2, legy1, legy2;
	if(overlay == 0) {
		legx1 = 0.15; legx2 = 0.50; legy1 = 0.58; legy2 = 0.85;
	} else {
		legx1 = 0.15; legx2 = 0.47; legy1 = 0.68; legy2 = 0.86;
	}

	TLegend *legendName = new TLegend(0.22,0.28,0.48,0.43,"#bf{Natural Higgsino NLSP}","brNDC");
	legendName->SetTextColor(1);
	legendName->SetFillColor(10);
	legendName->SetBorderSize(0);
	legendName->SetTextSize(0.035);
	legendName->Draw("");

	//	TLegend *legend = new TLegend(legx1, legy1, legx2, legy2, "Strong and Weak Production, #tilde{#chi}_{1}^{#pm} 250 GeV","brNDC");
	//TLegend *legend = new TLegend(legx1, legy1, legx2, legy2, "Strong Production Only, #tilde{#chi}_{1}^{#pm} 250 GeV","brNDC");
	TLegend *legend = new TLegend(legx1, legy1, legx2, legy2, "#bf{#tilde{#chi}_{1}^{#pm} = 250 GeV, Strong and Weak Production}","brNDC");
	legend->SetTextColor(1);
	legend->SetFillColor(10);
	legend->SetBorderSize(0);
	legend->SetTextSize(0.036);
	
	if(exp2m != 0 && exp2p != 0) {
		TGraph* exp2 = new TGraph(*exp2m);
		Double_t x;
		Double_t y;
		//exp2->SetPoint(exp2->GetN(), 475, 0.0);
		//exp2->SetPoint(exp2->GetN(), 800, 0.0);
		//exp2->SetPoint(exp2->GetN(), 20, 10); //PWZ commented out to remove yellow underneath with no data, also you add this point to fill in gaps in yellow
		for(int i = exp2p->GetN() - 1; i >= 0; --i) {
			exp2p->GetPoint(i, x, y);
			exp2->SetPoint(exp2->GetN(), x, y);
		}
		exp2->GetPoint(0, x, y);
//		exp2->SetPoint(exp2->GetN(), x, y);
		exp2->SetPoint(exp2->GetN(), 300, 1);
		exp2->SetFillColor(exp2Fill + (overlay != 0));
		exp2->SetLineColor(exp2Color);
		exp2->SetLineWidth(exp2Width);
		exp2->SetLineStyle(exp2Style);
		if(overlay != 0) exp2->SetFillStyle(3008);

		/*for(int i = exp2->GetN() - 1; i >= 0; --i) { //PWZ added to remove points close to diagonal (obs line loops)
                  double x, y; // PWZ says turn this for loop off when first running to get correct contour, i.e. 0,1,2, etc.
		  exp2->GetPoint(i, x, y);
		  if(x > 750) {
		  exp2->RemovePoint(i);
		  continue;
		  }
   		  if(x - y < 51) { // PWZ says you have to alter this number because may be too large for particular model
	          exp2->RemovePoint(i);
		  continue;
		  }
		  }*/

		//exp2->Draw("LF");
	}
	
	if(exp1m != 0 && exp1p != 0) {
		TGraph* exp1 = new TGraph(*exp1m);
		Double_t x;
		Double_t y;
		exp1->SetPoint(exp1->GetN(), 800, 0);
		for(int i = exp1p->GetN() - 1; i >= 0; --i) {
			exp1p->GetPoint(i, x, y);
			exp1->SetPoint(exp1->GetN(), x, y);
		}
		exp1->GetPoint(0, x, y);
//		exp1->SetPoint(exp1->GetN(), x, y);
		exp1->SetFillColor(exp1Fill + (overlay != 0));
		exp1->SetLineColor(exp1Color);
		exp1->SetLineWidth(exp1Width);
		exp1->SetLineStyle(exp1Style);
		if(overlay != 0) exp1->SetFillStyle(3008);

		/*for(int i = exp1->GetN() - 1; i >= 0; --i) { //PWZ added to remove points close to diagonal (obs line loops)
                  double x, y; // PWZ says turn this for loop off when first running to get correct contour, i.e. 0,1,2, etc.
		  exp1->GetPoint(i, x, y);
		  if(x > 750) {
		  exp1->RemovePoint(i);
		  continue;
		  }
   		  if(x - y < 51 || y > 380 || y < 150) { // PWZ says you have to alter this number because may be too large for particular model
	          exp1->RemovePoint(i);
		  continue;
		  }
		  }*/

		exp1->Draw("LF");
	}
	
	if(obs != 0) {
		obs->SetName("Observed");
		obs->SetTitle("Observed");
		obs->SetLineStyle(obsStyle);
		obs->SetLineWidth(obsWidth);
		obs->SetLineColor(obsColor);
		obs->SetLineStyle(obsStyle);
		
		for(int i = obs->GetN() - 1; i >= 0; --i) { //PWZ added to remove points close to diagonal (obs line loops)
  		  double x, y; // PWZ says turn this for loop off when first running to get correct contour, i.e. 0,1,2, etc.
		  obs->GetPoint(i, x, y);
		  if(x > 750) {
		  obs->RemovePoint(i);
		  continue;
		  }
   		  if(x - y < 51 || y > 380) { // PWZ says you have to alter this number because may be too large for particular model
	          obs->RemovePoint(i);
		  continue;
		  }
		}

		obs->Draw("LX");
		legend->AddEntry(obs,"observed 95% CLs Limits","l");
	}
	
	if(obs1p != 0) {
		obs1p->SetName("Observed 1p");
		obs1p->SetTitle("Observed 1p");
		obs1p->SetLineStyle(obsStyle);
		obs1p->SetLineWidth(obs1Width);
		obs1p->SetLineColor(obsColor);
		obs1p->SetLineStyle(obsStyle);
		for(int i = obs1p->GetN() - 1; i >= 0; --i) { //PWZ added to remove points close to diagonal (obs line loops)
  		  double x, y; // PWZ says turn this for loop off when first running to get correct contour, i.e. 0,1,2, etc.
		  obs1p->GetPoint(i, x, y);
		  if(x > 750) {
		  obs1p->RemovePoint(i);
		  continue;
		  }
   		  if(x - y < 51 || y > 380) { // PWZ says you have to alter this number because may be too large for particular model
	          obs1p->RemovePoint(i);
		  continue;
		  }
		}

		obs1p->Draw("LX");
		legend->AddEntry(obs1p,"Theory uncertainty (NLO)","l");
	}
	
	if(obs1m != 0) {
		obs1m->SetName("Observed 1m0");
		obs1m->SetTitle("Observed 1m0");
		obs1m->SetLineStyle(obsStyle);
		obs1m->SetLineWidth(obs1Width);
		obs1m->SetLineColor(obsColor);
		obs1m->SetLineStyle(obsStyle);
		for(int i = obs1m->GetN() - 1; i >= 0; --i) { //PWZ added to remove points close to diagonal (obs line loops)
  		  double x, y; // PWZ says turn this for loop off when first running to get correct contour, i.e. 0,1,2, etc.
		  obs1m->GetPoint(i, x, y);
		  if(x > 750) {
		  obs1m->RemovePoint(i);
		  continue;
		  }
   		  if(x - y < 51 || y > 380) { // PWZ says you have to alter this number because may be too large for particular model
	          obs1m->RemovePoint(i);
		  continue;
		  }
		}
		//obs1m->SetPoint(exp1->GetN(), 750, 0.05);
		obs1m->Draw("LX");
	}
	
	if(exp != 0) {
		exp->SetName("Expected");
		exp->SetTitle("Expected");
		exp->SetLineColor(expColor);
		exp->SetLineStyle(expStyle);
		exp->SetLineWidth(expWidth);
		exp->SetMarkerStyle(8);
//		exp->SetLineColor(38);
		
		for(int i = exp->GetN() - 1; i >= 0; --i) { //PWZ added to remove points close to diagonal
                  double x, y;
                  exp->GetPoint(i, x, y);
                  if(x > 750) {
                  exp->RemovePoint(i);
		  continue;
                  }
                  if(x - y < 51 || y > 380) {
                  exp->RemovePoint(i);
		  continue;
                  }
		}
		
		exp->Draw("LX");
		legend->AddEntry(exp,"expected 95% CLs Limits","l");
	}
	
	if(exp1m != 0 && exp1p != 0) {
		legend->AddEntry(exp1, "expected #pm1#sigma","fl");
	}
	/*if(exp2m != 0 && exp2p != 0) {
	  legend->AddEntry(exp2, "expected #pm2#sigma","fl");
	  }*/
	legend->Draw();
}

TGraph* plotCurve(TH2* hist, int color, int style, int curve = -1, bool smooth = false, int marker = 0) { // PWZ set smooth to false
	TGraph2D* gObsR = new TGraph2D(hist);
	Float_t npx = (gObsR->GetXmax() - gObsR->GetXmin()) / hObs->GetXaxis()->GetBinWidth(0);
	Float_t npy = (gObsR->GetYmax() - gObsR->GetYmin()) / hObs->GetYaxis()->GetBinWidth(0);
	//cout << "Number of x bins: " << npx << "(" << gObsR->GetXmin() << " till " << gObsR->GetXmax() << ")" << endl;
	//cout << "Number of y bins: " << npy << "(" << gObsR->GetYmin() << " till " << gObsR->GetYmax() << ")" << endl;
	gObsR->SetNpx(npx);
	gObsR->SetNpy(npy);
	Double_t xup  = hObs->GetXaxis()->GetXmax() - hObs->GetXaxis()->GetBinWidth(0) / 2;
	Double_t xlow = hObs->GetXaxis()->GetXmin() + hObs->GetXaxis()->GetBinWidth(0) / 2;
	Double_t yup  = hObs->GetYaxis()->GetXmax() - hObs->GetYaxis()->GetBinWidth(0) / 2;
	Double_t ylow = hObs->GetYaxis()->GetXmin() + hObs->GetYaxis()->GetBinWidth(0) / 2;
	TH2D* hist2 = new TH2D(TString(string(hist->GetName())) + "_interpolated", "dummy", xup - xlow + 1, xlow, xup, yup - ylow + 10, ylow, yup); // PWZ had to change bin size for from +1 to +10 for fractional values of y (sliding br)
	hist2->SetDirectory(0);
	gObsR->SetHistogram(hist2);
	hist2 = gObsR->GetHistogram();
//	gPad->SetLogz(1);
//	gPad->SetGrid(1, 1);
//	hist->Draw("LEGO2 Z");
//	return;
	// 20120507 PT: Test with coNLSP showed that smoothing three times with k3a seems to give the least invasive, yet smoothest result
	//for(int i = 0; i < 3; i++) hist->Smooth(1, "k3a");
	
	Double_t contours[1];
	contours[0] = 1.0;
	contours[1] = 2.0;
	hist2->SetContour(1, contours);

	c->cd();
	hist2->Draw("CONT LIST");
	c->Update();
//	hist->Draw("LEGO2 Z");
//	c->Update();
	c1->cd();

	TObjArray *conts = (TObjArray*)gROOT->GetListOfSpecials()->FindObject("contours");
	TList* contLevel = NULL;
	TGraph* curv	 = NULL;
	TGraph* gc	   = NULL;

	Int_t nGraphs	= 0;
	Int_t TotalConts = 0;

	if (conts == NULL) {
		printf("*** No Contours Were Extracted!\n");
		TotalConts = 0;
		return;
	} else {
		TotalConts = conts->GetSize();
	}

	printf("TotalConts = %d\n", TotalConts);

	nGraphs = 0;

	Double_t z0;
	TLatex l;
	l.SetTextSize(0.03);
	char val[20];

	for(int i = 0; i < TotalConts && i < 1; i++){
		contLevel = (TList*)conts->At(i);
		z0 = contours[i];
		printf("Z-Level Passed in as:  Z = %f with %d contours\n", z0, contLevel->GetSize());
		if(contLevel->GetSize() > 1 && curve < 0) {
			cout << "\tWARNING: Several curves found: " << contLevel->GetSize() << ", please specify which one to use. Skipping this contour!" << endl;
			return;
		}
		
		// Get first graph from list on curves on this level
		curv = (TGraph*)contLevel->First();
		for(int j = 0; j < contLevel->GetSize(); j++){
			nGraphs++;
			if(curve > j) {
				curv = (TGraph*)contLevel->After(curv); // Get Next graph
				continue;
			}
			printf("\tGraph: %d  -- %d Elements\n", nGraphs,curv->GetN());
			//curv->RemovePoint(0);
			Double_t x1, y1, x2, y2;
			curv->GetPoint(curv->GetN()-1, x1, y1);
			curv->GetPoint(curv->GetN()-2, x2, y2);
			// x2 < 260: Cut off superfluous extension of exp2
			/*while(sqrt(x1*x1 + y1*y1) > sqrt(x2*x2 + y2*y2)) { // PWZ commented out because was only plotting 2sigma band, can also cause curve not to reach up to diagonal
				curv->RemovePoint(curv->GetN()-1);
				curv->GetPoint(curv->GetN()-1, x1, y1);
				curv->GetPoint(curv->GetN()-2, x2, y2);
				}*/
			cout << "Determined counter starting point to be (" << x1 << "," << y1 << ")" << endl;
			
	 // Draw clones of the graphs to avoid deletions in case the 1st
	 // pad is redrawn.
			gc = (TGraph*)curv->Clone();
			gc->SetLineColor(color);
			gc->SetMarkerColor(color);
			gc->SetLineStyle(style);
//			gc->Draw("cp"); return;
			
			gc->GetPoint(gc->GetN() - 1, x1, y1);
			TGraphSmooth *gs = new TGraphSmooth();
			if(smooth) {
				curv->GetPoint(curv->GetN() - 1, x1, y1);
//				gc = gs->SmoothLowess(curv, "", 0.2, 3, 30);
//				gc = gs->SmoothLowess(curv, "");
			} else {
				for(Int_t p = 0; p <= (gc->GetN() - 1) / 2; ++p) {
					Int_t foo = p;	// necessary because of some ROOT bug
					gc->GetPoint(foo, x1, y1);
					gc->GetPoint(gc->GetN() - 1 - foo, x2, y2);
					gc->SetPoint(foo, x2, y2);
					gc->SetPoint(gc->GetN() - 1 - foo, x1, y1);
				}
			}
//			gc->SetPoint(0, x1, y1);
			
			int getNold = gc->GetN();
			gc->GetPoint(gc->GetN() - 1, x1, y1);
			for(UInt_t k = 0; k < gc->GetN(); k += 1) {
				for(UInt_t m = 0; m < 12; m++) {
					if(k + m + 1 < gc->GetN()) {
						//gc->RemovePoint(k + m + 1);
					}
				}
			}
			gc->SetPoint(gc->GetN(), x1, y1);
			cout << "Reduced number of points: " << getNold << " --> " << gc->GetN() << endl;
/*			for(UInt_t k = 0; k < gc->GetN(); k += 1) {
				gc->GetPoint(k, x1, y1);
				cout << x1 << " " << y1 << endl;
			}
*/			TGraph* tmp = (TGraph*)gc->Clone();
			gc->SetLineColor(color);
			gc->SetLineStyle(style);
			//gc->Draw("LPX");
			return gc;
//		gc->Print();
//			l.DrawLatex(x0,y0,name);


//			sprintf(val,"%g",z0);
		}
	}
	c1->Update();
	printf("\tExtracted %d Contours and %d Graphs\n", TotalConts, nGraphs );
	color++;
	//delete hist2; // PWZ commented out
	return gc;
}
