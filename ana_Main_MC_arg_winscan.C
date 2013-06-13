//#include "params_arg.h"
#include "TString.h"
using namespace std;
//using namespace params;

// Come back to this directory and do
// $ make
// $ root -b -q -l ana.C
// will produce hist_"physics"_"ds".root

void ana_Main_MC_arg_winscan(string which_MC_to_use, string MCFileLocation) {

	gSystem->Load("libSusyEvent.so");

	// Look ../jec/JetMETObjects/README
	gSystem->Load("../jec/lib/libJetMETObjects.so");

	// Printing utility for ntuple variables
	gROOT->LoadMacro("SusyEventPrinter.cc+");

	// Main analysis code
	gROOT->LoadMacro("SusyMainAna_MC_arg_windowscan.cc+");

	// chain of inputs
	TChain* chain = new TChain("susyTree");

	//////////////// MC files /////////////////
	//MCpoint* thisMCpoint = setupMCpoint(which_MC_to_use);
	chain->Add(MCFileLocation.data());
	//chain->Add(thisMCpoint->filepath.c_str());


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


	SusyMainAna_MC_arg_windowscan* sea = new SusyMainAna_MC_arg_windowscan(chain);

	// configuration parameters
	// any values given here will replace the default values
	sea->SetDataset("ttbar_relval");        // dataset name
	sea->SetPrintInterval(1e4);             // print frequency
	sea->SetPrintLevel(0);                  // print level for event contents
	sea->SetUseTrigger(false);
	sea->SetFilter(false);                  // filter events passing final cuts
	sea->SetProcessNEvents(-1);             // number of events to be processed

	TStopwatch ts;
	ts.Start();

	sea->Loop(which_MC_to_use);

	ts.Stop();
	std::cout << "RealTime : " << ts.RealTime()/60.0 << " minutes" << std::endl;
	std::cout << "CPUTime  : " << ts.CpuTime()/60.0 << " minutes" << std::endl;

}

