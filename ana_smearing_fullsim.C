#include "params_arg.h"
//#include "TString.h"
#include "MCpoint.h"
using namespace std;
using namespace params;
// Original Author:  Dongwook Jang
// $Id: ana.C,v 1.8 2011/11/01 22:14:51 dwjang Exp $
//
// Jet energy correction is possible at ntuple level.
// $ cd ../jec/JetMETObjects
// $ make
// This will create a shared library in jec/lib
// which is included below as libJetMETObjects.so
//
// Come back to this directory and do
// $ make
// $ root -b -q -l ana.C
// will produce hist_"physics"_"ds".root

void ana_smearing_fullsim(TString ds="relval", TString physics="ttbar") {

	gSystem->Load("libSusyEvent.so");

	// Look ../jec/JetMETObjects/README
	gSystem->Load("../jec/lib/libJetMETObjects.so");

	// Printing utility for ntuple variables
	gROOT->LoadMacro("SusyEventPrinter.cc+");

	// Main analysis code
	gROOT->LoadMacro("SusyAna_smearing_fullsim.cc+");

	// chain of inputs
	TChain* chain = new TChain("susyTree");

	//////////////// MC files /////////////////
	//cout<<"I survive this long1 "<< which_higgsMC_to_use2<< endl;
	//MCpoint* thisMCpoint = setupMCpoint(which_higgsMC_to_use2);
	cout<<"I survive this long2"<<endl;

        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_1.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_100001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_10001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_110001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_130001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_150001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_160001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_180001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_190001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_200001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_20001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_210001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_220001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_230001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_240001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_250001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_260001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_270001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_280001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_300001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_30001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_310001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_320001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_330001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_340001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_350001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_360001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_380001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_390001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_400001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_410001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_420001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_430001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_440001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_450001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_460001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_470001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_480001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_500001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_50001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_510001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_520001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_530001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_550001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_560001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_570001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_580001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_590001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_60001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_610001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_620001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_630001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_640001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_650001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_660001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_670001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_680001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_690001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_700001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_70001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_710001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_720001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_730001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_740001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_750001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_760001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_770001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_780001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_790001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_800001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_80001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_830001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_840001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_850001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_860001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_870001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_880001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_890001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_900001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_90001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_910001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_920001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_950001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_960001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_970001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_980001.root");
        chain->Add("/eos/uscms/store/user/lpcpjm/PrivateMC/FullSim/NaturalHiggsinoNLSPFullsim/tree/tree_185_5050_150_990001.root");

	cout<<"I survive this long"<<endl;


	//chain->Add("../susyEvents_AB_1M_ho200_v2.root");
	//chain->Add("../susyEvents_newNatural.root"); //last used!!
	//chain->Add("/eos/uscms/store/user/abarker/MC/newNat350_225/MC_AB_2500k_NEWnaturalHiggsinoNLSPout_mst_350_M3_5025_mu_225.root");//same thing as ../susyEvents_newNatural.root
	//chain->Add("/eos/uscms/store/user/abarker/MC/st_250_ho_150/MC_AB_2500k_st_250_ho_150.root");
	//chain->Add("/eos/uscms/store/user/abarker/MC/st_250_ho_200/MC_AB_2500k_st_250_ho_200.root");
	//chain->Add("/eos/uscms/store/user/abarker/MC/st_350_ho_200/MC_AB_2500k_mst_350_mu_200.root");
	//chain->Add("/eos/uscms/store/user/abarker/MC/ho_140/MC_AB_2500k_ho_140.root");
	//chain->Add("/eos/uscms/store/user/abarker/MC/ho_200/MC_AB_2500k_ho_200.root");


	//chain->Add("../susyEvents_newNatural.root");
	//chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/MC/MC_AB_2500k_NEWnaturalHiggsinoNLSPout_mst_350_M3_5025_mu_225.root");

	//chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/MC/MC_AB_2500k_st_250_ho_150.root");
	//chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/MC/MC_AB_2500k_st_250_ho_200.root");
	//chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/MC/MC_AB_2500k_mst_350_mu_200.root");
	//chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/MC/MC_AB_2500k_ho_140.root");
	//chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/MC/MC_AB_2500k_ho_200.root");



	SusyAna_smearing_fullsim* sea = new SusyAna_smearing_fullsim(chain);

	// configuration parameters
	// any values given here will replace the default values
	sea->SetDataset(physics+"_"+ds);        // dataset name
	sea->SetPrintInterval(1e4);             // print frequency
	sea->SetPrintLevel(0);                  // print level for event contents
	sea->SetUseTrigger(false);
	sea->SetFilter(false);                  // filter events passing final cuts
	sea->SetProcessNEvents(-1);             // number of events to be processed

	TStopwatch ts;

	ts.Start();

	sea->Loop();

	ts.Stop();

	std::cout << "RealTime : " << ts.RealTime()/60.0 << " minutes" << std::endl;
	std::cout << "CPUTime  : " << ts.CpuTime()/60.0 << " minutes" << std::endl;

	cout<<"super end"<<endl;
}

