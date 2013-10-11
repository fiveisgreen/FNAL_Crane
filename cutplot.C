	//Here you take in a single TH1F* and return at TH1F* of it's integral.
#include <iostream>
#include "math.h"
#include "TMath.h"
#include "TAxis.h"
#include "TH1.h"

enum cutmode {left=0, right=1, doublesided=2, higgs=3};
void Sqrt(TH1F* hin);
TH1F* CutEffComp(TH1F* sig, TH1F* bkg, cutmode approach);
TH1F* MakeCutEffScan(TH1F* hin, cutmode approach);
	///////////////////////////////////////////////////////////////
TH1F* MakeCutEffScan(TH1F* hin, cutmode approach){
		//just do the integrals.
	float integ = hin->Integral();
	int nbinsx = hin->GetXaxis()->GetNbins();
	switch (approach) {
		case 0://start cutting from the left
		{
			TH1F* hout = (TH1F*) hin->Clone("hout");
			for (int ibin = 1; ibin<=nbinsx; ibin++) {
				hout->SetBinContent(ibin,hin->Integral(ibin,nbinsx)/integ);
			}
			return hout;
		}
		case 1://start cutting from the right
		{
			Double_t edgesin[nbinsx+3];
			cout<<"in case 1, nbinsx = "<<nbinsx<<endl;
			hin->GetXaxis()->GetLowEdge(edgesin); // this segfaults
			cout<<"1"<<endl;
			Double_t newedges[nbinsx+2];
			cout<<"2"<<endl;
			for (int i=0; i<nbinsx; i++) {
				newedges[i] = edgesin[i];
				cout<<"i="<<i<<"edgesin[i]="<<edgesin[i]<<endl;
			}
			newedges[nbinsx] = hin->GetXaxis()->GetXmax();
			cout<<"3"<<endl;
			newedges[nbinsx+1] = 2.0*newedges[nbinsx] - newedges[nbinsx-1];
			cout<<"4"<<endl;
			for (int i=0; i<nbinsx+2; i++) {
				cout<<"newedges["<<i<<"] = "<<newedges[i]<<endl;
			}
			TH1F* hout = new TH1F("hout","",nbinsx+1,newedges);//gives error, complains that they are not in order.
			cout<<"5"<<endl;
//			TH1F* hout = (TH1F*) hin->Clone("hout");
			cout<<"6"<<endl;
			hout->SetBinContent(1,0);
			for (int ibin = nbinsx; ibin>0; ibin--) {
				cout<<"ibin"<<ibin<<endl;
				hout->SetBinContent(ibin+1,hin->Integral(1,ibin)/integ);
			}
			cout<<"7"<<endl;
			return hout;
		}
		case 2://start cutting at the edges and work to the center.
		{
			cout<<"in case 2, nbinsx = "<<nbinsx<<endl;
			int centerbin = (nbinsx/2)+1;//they're integers so you get the floor
			bool odd = nbinsx%2;
			cout<<"centerbin = "<<centerbin<<endl;
			Double_t edgesin[nbinsx+3];
			hin->GetXaxis()->GetLowEdge(edgesin);
			Double_t newedges[centerbin+1-!odd];
			for (int i=0; i<centerbin-1; i++) {
				newedges[i] = edgesin[i+centerbin];
				cout<<"i="<<i<<" edgesin[i+centerbin]="<<edgesin[i+centerbin]<<endl;
			}
			newedges[centerbin-1-!odd] = hin->GetXaxis()->GetXmax();
			newedges[centerbin-!odd] = 2.0*newedges[centerbin-1-!odd] - newedges[centerbin-2-!odd];
			for (int i=0; i<=centerbin-!odd; i++) {
				cout<<"newedges["<<i<<"] = "<<newedges[i]<<endl;
			}
			TH1F* hout = new TH1F("hout","",centerbin-!odd, newedges);
			hout->SetBinContent(1,0);
			for (int ibin = 0; ibin < centerbin-!odd; ibin++){
				hout->SetBinContent(ibin+1,hin->Integral(centerbin - ibin,centerbin + ibin)/integ);
			}
			return hout;
		}
		case 3: //scan higgs window width
		{
			int centerbin = hin->GetXaxis()->FindBin(125.5);//mHiggs);
			int nbinsOut = centerbin < nbinsx/2?centerbin:nbinsx+1-centerbin;
			TH1F* hout = new TH1F("hout",";efficiency;signal window width (GeV)", nbinsOut ,hin->GetBinWidth(centerbin), ((float)2*nbinsOut+1)*hin->GetBinWidth(centerbin));
			if(centerbin == 0 || centerbin == nbinsx+1){
				cout<<"Error! Attempting to build higgs efficiency plots on a non-sensical distribution!"<<endl;
				return hout;
			}
			for (int ibin = 0; ibin<nbinsOut; ++ibin) {
				hout->SetBinContent(ibin+1,hin->Integral(centerbin-ibin,centerbin+ibin)/integ);
			}
			return hout;
		}
		default:
		{
			TH1F* hout = new TH1F("hout","", 1,0,1);
			cout<<"Error! Nonsense mode received!"<<endl;
			return hout;
		}
	}//end switch
}//end CutEff

TH1F* CutEffComp(TH1F* sig, TH1F* bkg, cutmode approach){
		//Make efficiency scans on the signal and background
		//Return a hist of cut_efficiency(signal) / sqrt[ cut_efficiency(bkg)]
		//as a function of cut value
		//modes:
		//   "left": scan cut starting at left end
		//   "right": scan cut starting at left end
		//   "doublesided": scan cut at edges symmetrically, use for eta cut scan
		//   "higgs": scan higgs mass window
	TH1F* signal_eff = MakeCutEffScan(sig,approach);
	signal_eff->SetName("signal_eff_ratio");
	TH1F* background_eff = MakeCutEffScan(bkg,approach);
	background_eff->SetName("background_eff");
	Sqrt(background_eff);
	signal_eff->Divide(background_eff);
	return signal_eff;
}//end CutEff

void Sqrt(TH1F* hin){
		//hin = sqrt(hin)
	for (int ibin=0; ibin<= hin->GetXaxis()->GetNbins(); ++ibin) {
		float rootbin = sqrt(hin->GetBinContent(ibin));
		hin->SetBinContent(ibin,rootbin);
		hin->SetBinError(ibin,0.5f*hin->GetBinError(ibin)/rootbin);
	}
}//end Sqrt

