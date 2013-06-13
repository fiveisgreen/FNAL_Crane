#include "params_arg.h"
#include "TString.h"
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

void ana_test(TString ds="relval", TString physics="ttbar") {
/*
  gSystem->Load("libSusyEvent.so");
  gSystem->Load("../jec/lib/libJetMETObjects.so");
  gROOT->LoadMacro("SusyEventPrinter.cc+");
  // Main analysis code
  gROOT->LoadMacro("SusyMainAna_MC.cc+");
  // chain of inputs
  TChain* chain = new TChain("susyTree");
//////////////// MC files /////////////////
   chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/MC/MC_AB_2500k_mst_350_mu_200.root");


  SusyMainAna_MC* sea = new SusyMainAna_MC(chain);

  // configuration parameters
  // any values given here will replace the default values
  sea->SetDataset(physics+"_"+ds);        // dataset name
  sea->SetPrintInterval(1e4);             // print frequency
  sea->SetPrintLevel(0);                  // print level for event contents
  sea->SetUseTrigger(false);
  sea->SetFilter(true);                  // filter events passing final cuts
  sea->SetProcessNEvents(-1);             // number of events to be processed
*/

  TStopwatch ts;

  ts.Start();

//  sea->Loop();
  cout<<"wooooooork!!!"<<endl;

  ts.Stop();

  std::cout << "RealTime : " << ts.RealTime()/60.0 << " minutes" << std::endl;
  std::cout << "CPUTime  : " << ts.CpuTime()/60.0 << " minutes" << std::endl;

}
