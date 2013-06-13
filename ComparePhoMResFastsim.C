#include "CMSStyle.C"
void ComparePhoMResFastsim(){
TFile* file0 = new TFile("PhoEc/raw_plots_MC_st235_ho225.root");
TFile* file1 = new TFile("noPhoEC/raw_plots_MC_st235_ho225.root");
TH1F* cor = (TH1F*)file0->Get("h_mGGNULL_unsliced");
TH1F* uncor = (TH1F*)file1->Get("h_mGGNULL_unsliced");
//cor->Scale(1.0/((float)cor->Integral()));
//uncor->Scale(1.0/((float)uncor->Integral()));
PrettyHist(cor);
PrettyHist(uncor,2);
RaiseRangeRoof(cor);
RaiseRangeRoof(uncor);
SameRange(cor,uncor);
cor->GetXaxis()->SetRangeUser(100,150);
uncor->GetXaxis()->SetRangeUser(100,150);
cor->SetTitle("Mass Resolution Comparison in M_{stop}= 235 M_{h0} = 225");
TLegend* l = new TLegend(0.599138,0.675847,0.798851,0.872881);
PrettyLegend(l);
l->AddEntry(uncor,"Uncorrected");
l->AddEntry(cor,"MVA regressed E^{#gamma}");
cor->Draw();
uncor->Draw("same");
cor->Draw("same");
l->Draw("same");

}
