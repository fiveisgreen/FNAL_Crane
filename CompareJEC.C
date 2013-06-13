#include "CMSStyle.C"
#include "params_arg.h"
using namespace params;
using namespace std;

//Copy this into root

TFile * f = new TFile("LimitPackage_mst_210_mu_150_2JbMLm20gbar2_MET.root");
f->cd();
TCanvas *c = new TCanvas("asfd","asdf",800,800);
c->SetTopMargin(0.06);
c->SetBottomMargin(0.15);
PrettyHist(hMET2JbMLm20gbar2_MC);
hMET2JbMLm20gbar2_MC->Draw();
PrettyMarker(hMET2JbMLm20gbar2_MC);
hMET2JbMLm20gbar2_MC->Draw();
hMET2JbMLm20gbar2_MC->GetXaxis()->SetTitle("MET (GeV)");
hMET2JbMLm20gbar2_MC->Draw();
TLegend * l = new TLegend(0.54397,0.708791,0.743719,0.907967);
PrettyLegend(l);
l->AddEntry(hMET2JbMLm20gbar2_MC,"Unshifted");
PrettyHist(hMET2JbMLm20gbar2_JECUp,kRed);
hMET2JbMLm20gbar2_JECUp->Draw("same");
l->AddEntry(hMET2JbMLm20gbar2_JECUp,"JEC Up 1#sigma");
PrettyHist(hMET2JbMLm20gbar2_JECDown,kBlue);
l->AddEntry(hMET2JbMLm20gbar2_JECDown,"JEC Down 1#sigma");
hMET2JbMLm20gbar2_JECDown->Draw("same");
hMET2JbMLm20gbar2_MC->Draw("same");
l->Draw("same");
c->SaveAs("JECcomp_mst_210_mu_150.pdf");
c->SaveAs("JECcomp_mst_210_mu_150.jpg");


/*      TLatex * TEX_CMSPrelim = new TLatex(1.177136,0.953368,"CMS Preliminary 2013");
        PrettyLatex(TEX_CMSPrelim,0.03);
        TEX_CMSPrelim->Draw("same");

        TLatex * TEX_E_TeV = new TLatex(0.800251,0.953368,"#sqrt{s} = 8 TeV");
        PrettyLatex(TEX_E_TeV,0.03);
        TEX_E_TeV->Draw("same");

        TLatex * TEX_lumi_fb = new TLatex(0.621859,0.953368,Form("#intL dt = %.0f fb^{-1}",Integrated_Luminosity_Data));
        PrettyLatex(TEX_lumi_fb,0.03);
        TEX_lumi_fb->Draw("same");*/

