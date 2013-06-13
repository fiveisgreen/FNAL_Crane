#include "CMSStyle.C"
#include "TFile.h"
void ComparePhoMResFullsim(){
	TFile* file0 = new TFile("PhoEc/raw_plots_MC_GluGluToHToGG_quick.root");
	TFile* file1 = new TFile("noPhoEC/raw_plots_MC_GluGluToHToGG_quick.root");
	TH1F* cor = (TH1F*)file0->Get("h_mGGNULL_unsliced");
	TH1F* uncor = (TH1F*)file1->Get("h_mGGNULL_unsliced");
	PrettyHist(cor);
	PrettyHist(uncor,2);
	RaiseRangeRoof(cor);
	RaiseRangeRoof(uncor);
	SameRange(cor,uncor);
	cor->GetXaxis()->SetRangeUser(100,150);
	uncor->GetXaxis()->SetRangeUser(100,150);
	cor->SetTitle("Mass Resolution Comparison in gg#rightarrowH#rightarrow#gamma#gamma Full-Sim");
	TLegend* l = new TLegend(0.599138,0.675847,0.798851,0.872881);
	PrettyLegend(l);
	l->AddEntry(uncor,"Uncorrected");
	l->AddEntry(cor,"MVA regressed P_{t}^{#gamma}");
	cor->Draw();
	uncor->Draw("same");
	cor->Draw("same");
	l->Draw("same");
}
