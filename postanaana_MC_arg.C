 #define postanaana_MC_arg_C

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>

#include "TAxis.h"
#include "TMath.h"
#include <TH3.h>
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"
	//#include "TLorentzVector.h"
#include "TGraphAsymmErrors.h"
#include "TF1.h"
#include <iostream>
#include <fstream>
	//user defiend
#include "utilities.h"
#include "cuts.h"
#include "params_arg.h"
#include "GetError.h"
#include "hggx_analysers.h"
#include "quicksave.C"
#include "CMSStyle.C"
#include "../src/SusyEvent.h"
#include "MCpoint.h"
using namespace std;
using namespace params;

typedef std::map<string,TH1F*> LabelHist;
typedef std::map<string,LabelHist> Label2Hist;
typedef std::map<string,TH1F**> LabelHistArr;
typedef std::map<string,LabelHistArr> Label2HistArr;

void LoadHistSet(TH1F** h, TFile* fin, string prefix);
void MakeHistSet(TH1F** h, string prefix);
void FixLastBin(TH1F** h);

void postanaana_MC_arg(string which_MC_to_use){
                ofstream firealarm;
                bool onfire = false;
                firealarm.open("tmpfirealarm.txt");
                firealarm << "postanaana_MC_arg is on FIRE"<<endl;
                firealarm.close();
	
	int debug = 2;
	if(debug>0) cout<<"postanaana_MC_arg is alive!"<<endl;
	CMSStyle();

	int nKinemVars = (bumpJEC == 0 &&  bumpBtagEff ==0)?nKinemVars_all: nKinemVars_limit;
	string *s_KinemVars = (bumpJEC == 0 &&  bumpBtagEff ==0)?s_KinemVars_all: s_KinemVars_limit;

	if(showTag) cout<<endl<<"WARNING!! showTag IS ON!"<<endl<<endl;
	else  cout<<endl<<"showTag IS OFF!"<<endl<<endl;

	string s_EventTopology_v1[nEventTopologies];
	s_EventTopology_v1[0]="";
	for (int iTopo=1; iTopo<nEventTopologies; iTopo++) {s_EventTopology_v1[iTopo] = string("_")+s_EventTopology[iTopo];}//{"","_1Jb","_3J"...
	string s_EventTopology_v2[nEventTopologies];
	s_EventTopology_v2[0]="";
	for (int iTopo=1; iTopo<nEventTopologies; iTopo++) {s_EventTopology_v2[iTopo] = string("_")+s_EventTopology[iTopo]+"_";} //{"","_1Jb_","_3J_"...

	//make some nice titles
	if(debug > 9) cout<<"attempting to make toplogy title list"<<endl;
	string s_EventTopology_v4[nEventTopologies]={
		"with no extra cuts",//NULL
		"with both pho in the barrel",//gbar2
	//	"with MET > 30",
		"with at least 1 lep and both pho in the barrel",//1lepgbar2
		"with exactly 1 lep and both pho in the barrel",//"1!lepgbar2",
		"with at least one electron and both pho in the barrel",//"1Elegbar2",
		"with at least one Muon and both pho in the barrel",//"1Mugbar2",
		"with at least two leptons and both pho in the barrel",//"2lepgbar2",
		"with exactly two same-flavor leptons that make a Z, and barrel photons",//"2!lepZgbar2",
		"with at least 3 leptons, and both pho in the barrel",//"3lepgbar2",
		"with 2 or 3 jets, exactly 2 M B-tags, no leptons, barrel photons, and 95<Mbb<155", //"23JbMM!gbar2Mbb0lep",
		"with at least 2 jets, exactly 2 M B-tags, no leptons, barrel photons, and 95<Mbb<155", //"2JbMM!gbar2Mbb0lep", //2
		"with 2 or 3 jets, exactly 2 M B-tags, <2 leptons, barrel photons, and 95<Mbb<155", //"23JbMM!gbar2Mbb0lep",
		"with at least 2 jets, B-tags 2!L with M, <2 leptons, barrel photons, and 95<Mbb<155", //"2JbML!gbar2Mbb0lep", //2
		"with at least 2 jets, exactly 2 M B-tags, <2 leptons, barrel photons, and 95<Mbb<155", //"2JbMM!gbar2Mbb01lep
		"with at least 2 jets, B-tags 2!L with T, <2 leptons, barrel photons, and 95<Mbb<155", //"2JbTL!gbar2Mbb01lep
		"with at least 2 jets, B-tags 2!M with T, <2 leptons, barrel photons, and 95<Mbb<155", //"2JbTM!gbar2Mbb01lep
		"with at least 2 light flavor jets, and both pho in the barrel", //2lJgbar2",
		"with at least 2 light flavor jets with 70<Mljlj<110, and both pho in the barrel",//"2lJewkMllgbar2",
		"with at 2 or 3 light flavor jets with 70<Mljlj<110, and both pho in the barrel",//"23lJewkMllgbar2", "2lJMWgbar2" "2lJMZgbar2" //4
		"with 2 Jets, B-tags:MM", //"2JbML"
		"with 2 Jets, B-tags:ML", //"2JbML"
		"with 2 Jets, B-tags:ML, and both pho in the barrel", //"2JbMLgbar2",
		"with 2 Jets, B-tags:MM, and both pho in the barrel", //"2JbMMgbar2",
		"with 2 Jets, B-tags 2!L with M, both pho in the barrel, and 95<Mbb<155", //"2JbML!Gbar2Mbb"
		"with 2 Jets, B-tags 2!L with M, both pho in the barrel, and !95<Mbb<155", //2JbML!Gbar2Mbb!
		"with 3 Jets, B-tags 3+L with M, both pho in the barrel", //3JbMLLGbar2
		"with 2 Jets, B-tags 2!L with 2M, both pho in the barrel, and 95<Mbb<155", //"2JbMM!Gbar2Mbb 
		"with 2 Jets, B-tags 2!L with 2M, both pho in the barrel, and !95<Mbb<155", //2JbMM!Gbar2Mbb!
		"with 3 Jets, B-tags 3+L with 2M, both pho in the barrel", //3JbMMLGbar2
		//"with 2 Jets, B-tags 2!L with M, both pho in the barrel, and 110<bestMjj<140", //"2JbML!gbar2bestOn",
		//"with 2 Jets, B-tags 2!L with M, both pho in the barrel, and !110<bestMjj<140", //"2JbML!gbar2bestOff",
		//"with 2 Jets, B-tags 2!L with 2M, both pho in the barrel, and 110<bestMjj<140", //"2JbMM!gbar2bestOn",
		//"with 2 Jets, B-tags 2!L with 2M, both pho in the barrel, and !110<bestMjj<140", //"2JbMM!gbar2bestOff", //4
		"with 2 Jets, B-tag T, with pho in the barrel, and 110<M(Tight B +1Jet)<140",//2JbT!gbar2ProbeMJJ
		"with at least 2 jets, exactly 2 L and <= 1 M B-tags, <2 leptons, barrel photons, and 95<Mbb<155", //"2JbMLextgbar2Mbb01lep"
		"with at least 2 jets, exactly 1 M and 1 L  B-tags, <2 leptons, barrel photons, and 95<Mbb<155", //"2JbMLmaxgbar2Mbb01lep"
		"with 2 or 3 jets, light flavor jets with 70<Mljlj<110, no leptons, and barrel photons",//"23Jb01MewkMll0lepgbar2", //for WH
		"with 2-5 jets, light flavor jets with 70<Mljlj<110, no leptons, and barrel photons",//"0lep25Jb01MewkMllgbar2",
		"with 2-3 jets, light flavor jets with 70<Mljlj<110, exaclty 1 lepton, and barrel pho",//1!lep23Jb01MewkMllgbar2,
		"with 2-3 jets, light flavor jets with !70<Mljlj<110, exaclty 1 lepton, and barrel pho",//"1!lep23Jb01M!ewkMllgbar2"
		"with 2 Jets, B-tags:M, 2 leptons, and both pho in the barrel",//"2JbM2lepgbar2",
		"with 2 Jets, B-tags 2!L with M, both pho in the barrel, and exactly one lepton", //"2JbML!1lepgbar2",

		"with 2 Jets, exactly 2 M B-tags, barrel phos, no lep, and 110<bestMjj<140",//"2JbMM!gbar2bestOn0lep"
		"with 4 Jets, exactly 2 M B-tags, barrel phos, no lep, EWK Mljlj, and !110<bestMjj<140", //"4JbMM!gbar2 MllEWK bestOff 0lep",
		"with 2 Jets, exactly 2 M B-tags, barrel phos, no lep, no Mjj on EWK, and !110<bestMjj<140",//"2JbMM!gbar2bothOff0lep"
		"with just barrel photons: no leptons or b-jets, and at most 1 light jet",//"01J0lep0Bgbar2"
		"with four pho and hgg in the barrel"};//4phogbar2





		/*"with 2 Jets, B-tags:ML",
		"with 2 Jets, B-tags:ML, and both pho in the barrel",
		"with 2 Jets, B-tags:ML, and MET>20",
		"with 2 Jets, B-tags:ML, and 1 pho in the barrel",
		"with 2 Jets, B-tags:ML, both pho in the barrel, and MET>20",
		"with 2 Jets, B-tags 2!L with M, both pho in the barrel, and 95<Mbb<155",
		"with 2 Jets, B-tags 2!L with M, both pho in the barrel, and !95<Mbb<155",
		"with 3 Jets, B-tags 3+L with M, both pho in the barrel",
		"with 4 Jets, B-tags 4+L with M, both pho in the barrel"
		"with 2 Jets, B-tags 2!L with M, and both pho in the barrel",
		"with 2 Jets, B-tags:TL, and both pho in the barrel",
		"with Tight Photons, 2 Jets, B-tags:ML, and both pho in the barrel",
		"with Tight Photons, 2 Jets, B-tags:TL, and both pho in the barrel",
		"with Medium Photons, 2 Jets, B-tags:ML, and both pho in the barrel",
		"with Medium Photons, 2 Jets, B-tags:TL, and both pho in the barrel",*/
			// "with 2 Jets, B-tags:TL, and MET>20",
			//  "with 2 Jets, B-tags:TL, 1 pho in the barrel, and MET>20",
			//"with 3 Jets, B-tags:M, and MET>20",
			//"with 3 Jets, B-tags:T, and MET>20",

			//"with 2 Jets, B-tags:ML, 1 pho in the barrel, jet dEta<1.5, and MET>20",
			//"with 2 Jets, B-tags:ML, both pho in the barrel, jet dEta<1.5, and MET>20",

			//"with 2 Jets that look higgs-like mass, and 1 pho in the barrel", //2JHjj
			//"with 2 Jets that look higgs-like mass, and 2 pho in the barrel", //2JHjj
			//"with 2 Jets that look higgs-like mass, 1 pho in the barrel, and jet dEta<1.5", //2JHjj
			//"with 2 Jets that look higgs-like mass, 2 pho in the barrel, and jet dEta<1.5", //2JHjj
			//"with 4 Jets, B-tags:M, 1 pho in the barrel, and MET>20",
			//"with 4 Jets, B-tags:M, 2 pho in the barrel, and MET>20",
			//"with 4 Jets, B-tags:T, 1 pho in the barrel, and MET>20",
			//"with 4 Jets, B-tags:T, 2 pho in the barrel, and MET>20",
			//"with 4 Jets, B-tags:TL, and MET>20",

			//"with 4 Jets, B-tags:ML, 1 pho in the barrel, and MET>20",
			//"with 4 Jets, B-tags:ML, 2 pho in the barrel, and MET>20",
			//"with 4 Jets, B-tags:LLLL, 1 pho in the barrel, and MET>20",
			//"with 4 Jets, B-tags:LLLL, 2 pho in the barrel, and MET>20",

			//"with 4 Jets, B-tags:T, and MET>20",

			//"with 8 Jets, and 1 pho in the barrel",
			//"with 8 Jets, and 2 pho in the barrel",

			//"with no leptons",
			//"with exactly one lepton",
			//"with at least one lepton",
			//"with at least two leptons",
			//"with at least three leptons",
			//"with at least one electron and muon",
			//"with a Z->ll",
			//"with a muon",
			//"with Tight Photons",
			//"with Tight Photons, 2 Jets, B-tags:ML, both pho in the barrel, and MET>20",
			//"with Tight Photons and a lepton",
			//"with Tight Photons and 2+ leptons",
			//"where both photons are tight"
		/*"with 2 Jets, B-tags 2L with M, both pho in the barrel, and 110<bestMjj<140",
		"with 2 Jets, B-tags 2L with M, both pho in the barrel, and !110<bestMjj<140",
		"with 2 Jets, B-tags 2L with T, both pho in the barrel, and 110<bestMjj<140",
		"with 2 Jets, B-tags 2L with T, both pho in the barrel, and !110<bestMjj<140"*/
	
        if(debug > 9) cout<<"success in making toplogy title list"<<endl;

        MCpoint* thisMCpoint = setupMCpoint(which_MC_to_use);
        cout<<endl<<"Reading from file "<<thisMCpoint->plotsroot_mc<<endl<<endl;
        TFile fin(thisMCpoint->plotsroot_mc.c_str());

	if(debug>1) cout<<"loaded fin"<<endl;

		//load all histogrmas
	TH1F* h_vtxZ = (TH1F*)fin.Get("vtxZ_unsliced");
	     if(debug>1) cout<<"loaded hist from fin"<<endl;
	TH1F* h_bsZ = (TH1F*)fin.Get("bsZ_unsliced");

	if(debug>2) cout<<"am4"<<endl;

	LabelHist lh_mGG_unsliced;
	Label2Hist lh_unsliced;
	Label2HistArr lha2;

	if(debug>2) cout<<"loading histograms for all topologies"<<endl;
		//load your histograms for all topologies. 
	for (int iTopo=0; iTopo<nEventTopologies; iTopo++) {
		if(debug>2) cout<<"topo "<<s_EventTopology[iTopo]<<endl;
		lh_mGG_unsliced[s_EventTopology[iTopo]] = (TH1F*)fin.Get((char*)(string("h_mGG")+s_EventTopology[iTopo]+"_unsliced").c_str());

		LabelHist tmpMapKinVar;
		for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++) {
			tmpMapKinVar[s_KinemVars[kKinVar]] = (TH1F*)fin.Get((char*)(string("h_")+s_KinemVars[kKinVar]+s_EventTopology[iTopo]+"_unsliced").c_str());
		}//end for every kinematic varriable.
		lh_unsliced[s_EventTopology[iTopo]] = tmpMapKinVar;
	}
	if(debug>2) cout<<"am6"<<endl;
	for (int iTopo=0; iTopo<nEventTopologies; iTopo++) {
		LabelHistArr tmpMapKinVar;
		if(debug>3) cout<<"topo "<<s_EventTopology[iTopo]<<endl;
		for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++) {
			if(debug>4) cout<<"kinvar"<<s_KinemVars[kKinVar]<<endl;
			TH1F ** temp = new TH1F*[nPhoMassAndBkgDists];
			if(debug>5) cout<<"try and load"<<endl;
			LoadHistSet(temp, &fin, s_KinemVars[kKinVar]+s_EventTopology[iTopo]);
			if(debug>5) cout<<"supposedly loaded, try and touch it"<<endl;
			FixLastBin(temp);
			if(debug>5) cout<<"worked"<<endl;
			tmpMapKinVar[s_KinemVars[kKinVar]] = temp;
		}
		lha2[s_EventTopology[iTopo]] = tmpMapKinVar;
	}
	
		//Get the integrals of the side bands. 
	if(debug>2) cout<<"am7"<<endl;
	TH1I *lsb_int = (TH1I*) fin.Get("lsb_int"); //this is fairly frightening. 
	TH1I *usb_int = (TH1I*) fin.Get("usb_int");
		//order: is the same as that in s_EventTopology.

	
	if(debug>0) cout<<"nocuts usb_int "<<usb_int->GetBinContent(0)<<" lsb_int "<< lsb_int->GetBinContent(0)<<endl;
	if(debug>1) cout<<"making fout"<<endl;
												  
	cout<<endl<<"Writing To File "<<thisMCpoint->plotsAndBackground_mc <<endl<<endl;
	TFile* fout = new TFile(thisMCpoint->plotsAndBackground_mc.c_str(),"RECREATE");
	ofstream logfile;
	logfile.open(thisMCpoint->logplotsAndBackground_mc.c_str());
		//TFile* fout = new TFile(plotsAndBackground_mc.c_str(),"RECREATE");
	fout->cd();
		//bounce some of these right back. 

	if(debug>1) cout<<"Try write to fout"<<endl;
	h_vtxZ->Write();
	if(debug>3) cout<<"Managed to write once."<<endl;
	if(debug>8) cout<<"Write bsZ unsliced"<<endl;
	h_bsZ->Write();


	for (int iTopo=0; iTopo<nEventTopologies; iTopo++) {
		if(debug>3) cout<<"Topo = "<<s_EventTopology[iTopo]<<endl;

		for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++) {
			PrettyHist(lh_unsliced[s_EventTopology[iTopo]][s_KinemVars[kKinVar]]);
			PrettyMarker(lh_unsliced[s_EventTopology[iTopo]][s_KinemVars[kKinVar]]);
			lh_unsliced[s_EventTopology[iTopo]][s_KinemVars[kKinVar]]->Write();
		}
			//this one is special, not in the loop
		PrettyHist(lh_mGG_unsliced[s_EventTopology[iTopo]]);
		PrettyMarker(lh_mGG_unsliced[s_EventTopology[iTopo]]);
		lh_mGG_unsliced[s_EventTopology[iTopo]]->Write();
	}

	if(debug>3) cout<<"done with that writing round."<<endl;
		//support 
//	int nEventTopologies = 5; //keep same order as lsb_int: 
		//0 = just photons
		//1 = 1 b-tag jet
		//2 = 3 jets
		//3 = 3 jets + a b-tag
		//4 = met cut
	float B_integral[nEventTopologies];
	float B_integral_error[nEventTopologies];
	float chi2[nEventTopologies];
	TF1* mgg_fit_curve[nEventTopologies];
//	TGraphAsymmErrors* g[nEventTopologies];
	TH1F* ha_diPhotonMass[nEventTopologies];

	for (int iTopo=0; iTopo<nEventTopologies; iTopo++) {
		ha_diPhotonMass[iTopo] = lh_mGG_unsliced[s_EventTopology[iTopo]];
		//printf("dipho %s mass integ %.0f\n",(char*)s_EventTopology[iTopo].c_str(),ha_diPhotonMass[iTopo]->Integral() );
		logfile<<Form("dipho %s mass integ %.0f\n",(char*)s_EventTopology[iTopo].c_str(),ha_diPhotonMass[iTopo]->Integral() );
	}

	if(debug>2) cout << "a"<<endl;


		//find all the background integrals and their errors.
	for (int iTopo=0; iTopo<nEventTopologies; iTopo++) {
		cout<<endl<<"    @@@@ Try to fit background for topology "<<s_EventTopology[iTopo]<<" @@@@"<<endl;
		fitmgg_simpler(ha_diPhotonMass[iTopo], 105.,160.,&(mgg_fit_curve[iTopo]),chi2[iTopo], B_integral[iTopo], B_integral_error[iTopo],s_EventTopology_v2[iTopo]);

		printf("B_integral %s     %f +- %f  Chi2 %f\n",(char*)s_EventTopology[iTopo].c_str(), B_integral[iTopo],B_integral_error[iTopo],chi2[iTopo]);
	}
	if(debug>1) printf("ana finished get_bkg_integral\n");
	
	for (int iTopo=0; iTopo<nEventTopologies; iTopo++) {
		for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++) {
			find_bkg_with_fit(lha2[s_EventTopology[iTopo]][s_KinemVars[kKinVar]],B_integral[iTopo], B_integral_error[iTopo], lsb_int->GetBinContent(iTopo), usb_int->GetBinContent(iTopo));//if the side bands have a 0, this'll spew warnings, but it's usually ok. 
		}
	}
	if(debug>1) printf("finished find_bkg_with_fit for all groups\n");

	
	fout->cd();
	if(debug>3) printf("Wrote the set of mgg fit curves\n");
	for (int iTopo=0; iTopo < nEventTopologies; iTopo++) mgg_fit_curve[iTopo]->Write();

	for (int i=0; i < nPhoMassAndBkgDists; i++){
		// {"lowSB","tag","upperSB","bkg","tag_subbkg","lowSB_scaled","upperSB_scaled","lsb_over_usb","tag_over_bkg"};
		//   0x       1      2x      3       4x          5                6                    7x           8
		if(i == 0 ||  //don't write unscaled lowSB, only scaled 
		i == 2 || //don't write unscaled upperSB, only scaled
		i == 4 || //don't write tag_subbkg 
		i == 7)  //don't write lsb_over_usb
		continue;

		for (int iTopo=0; iTopo<nEventTopologies; iTopo++){
			for (int kKinVar = 0; kKinVar<nKinemVars; kKinVar++){
				lha2[s_EventTopology[iTopo]][s_KinemVars[kKinVar]][i]->Write();
			}
		}
	}


	for (int iTopo=0; iTopo<nEventTopologies; iTopo++){
		TString title = "mgg"+s_EventTopology_v2[iTopo]+"TCanvas";
		TCanvas *mggCanv = new TCanvas(title.Data(),title.Data(),800, 800);
		mggCanv->cd();
		string mggTitle =string("Di-Photon mass spectra cuts ")+s_EventTopology_v4[iTopo]+";M^{#gamma #gamma} (GeV)";
		ha_diPhotonMass[iTopo]->SetTitle((char*)mggTitle.c_str());
		ha_diPhotonMass[iTopo]->Draw("EP");
		mgg_fit_curve[iTopo]->SetLineColor(kRed);
		mgg_fit_curve[iTopo]->SetLineWidth(5);
		mgg_fit_curve[iTopo]->Draw("same");
		mggCanv->Write();

		//print the data driven bkg
		printf("Data Driven Bkg %s %f\n",(char*)s_EventTopology[iTopo].c_str(),lha2[s_EventTopology[iTopo]]["MET"][3]->Integral() );
	}
	logfile.close();
	fout->cd();
	fout->Write();
	fout->Close();

	if(!onfire){
                ofstream firealarm2;
                firealarm2.open("tmpfirealarm.txt");
                firealarm2 << "postanaana_MC_arg is ok"<<endl;
                firealarm2.close();
	}
}//end Loop


void LoadHistSet(TH1F** h, TFile* fin, string prefix){
	string names[nPhoMassAndBkgDists];
	for (int i = 0; i<nPhoMassAndBkgDists; i++) {
		names[i] = "h";
		names[i]+= prefix+"_"+s_MassBkgDists[i];
	}
	//for (int i=0; i < nPhoMassAndBkgDists; i++){
	for (int i=0; i < 3; i++){
		//only load the histograms we don't make here. 
		// {"lowSB","tag","upperSB","bkg","tag_subbkg","lowSB_scaled","upperSB_scaled","lsb_over_usb","tag_over_bkg"};
		//   0       1      2        3x      4x          5x               6x                   7x           8x
		//cout<<"Load Hist Set i="<<i<<" prefix: "<<prefix<<endl;
		h[i] = (TH1F*) fin->Get((char*)names[i].c_str() );
		//cout<<"did it"<<endl;
	}
	//cout<<"attempt MakeHistSet"<<endl;
	MakeHistSet(h,prefix); //this fails.
	//cout<<"finished MakeHistSet"<<endl;
} //end LoadHistSet

void FixLastBin(TH1F** h){
	AddOverflow(h[0]);	
	AddOverflow(h[1]);	
	AddOverflow(h[2]);	
}


void MakeHistSet(TH1F** h, string prefix){
//called with            MakeHistSet(tmpMapKinVar[s_KinemVars[kKinVar]], s_KinemVars[kKinVar]+s_EventTopology[iTopo]);
	//makes the histograms not loaded by cloning those that were already loaded in the exact same way as done in SusyMainAna. 
        string names[nPhoMassAndBkgDists];
        string titles[nPhoMassAndBkgDists];
        string descriptions[nPhoMassAndBkgDists] = {"Lower Side Band",
                "in Higgs Tag Region","Upper Side Band","Background to Higgs Tag Region",
                "Background Subtracted Higgs Tag Region","Lower Side Band","Upper Side Band",
                "Lower to Upper sideband ratio","Tag to background ratio"};
        for (int i = 0; i<nPhoMassAndBkgDists; i++) {
                names[i] = "h";
                names[i]+= prefix+"_"+s_MassBkgDists[i];
                titles[i] = prefix+" "+descriptions[i];
        }
        for (int i=0; i < nPhoMassAndBkgDists; i++) {
		if(i<3) continue; //only do the ones not loaded already
                h[i] = (TH1F*) h[0]->Clone( RandomString(6) ); //blows up!!
		h[i]->Reset("M");
                NameHist(h[i],(char*)names[i].c_str(),(char*)titles[i].c_str());
        }
}//end MakeHistSet


