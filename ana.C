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

void ana(TString ds="relval", TString physics="ttbar") {

  gSystem->Load("libSusyEvent.so");

  // Look ../jec/JetMETObjects/README
  gSystem->Load("../jec/lib/libJetMETObjects.so");

  // Printing utility for ntuple variables
  gROOT->LoadMacro("SusyEventPrinter.cc+");

  // Main analysis code
  gROOT->LoadMacro("SusyEventAnalyzer_shruti.cc+");

  // chain of inputs
  TChain* chain = new TChain("susyTree");
  chain->Add("../susyEvents_Shruti.root");
  //chain->Add("dcap:///pnfs/cms/WAX/resilient/lpcpjm/SusyNtuples/cms423v2_v1/Run2011A-May10ReReco-v1/Photon/susyEvent_1_1_dLs.root");

  SusyEventAnalyzer_shruti* sea = new SusyEventAnalyzer_shruti(chain);

  // configuration parameters
  // any values given here will replace the default values
  sea->SetDataset(physics+"_"+ds);        // dataset name
  sea->SetPrintInterval(1e4);             // print frequency
  sea->SetPrintLevel(10);                  // print level for event contents
  sea->SetUseTrigger(true);
  //sea->AddHltName("HLT_Photon36_CaloIdL_Photon22_CaloIdL");  // add HLT trigger path name
  //sea->AddHltName("HLT_Photon32_CaloIdL_Photon26_CaloIdL");  // add HLT trigger path name
  sea->SetFilter(false);                  // filter events passing final cuts
  sea->SetProcessNEvents(-1);             // number of events to be processed

  // as an example -- add your favorite Json here.  More than one can be "Include"ed
  //sea->IncludeAJson("Cert_190456-199429_8TeV_PromptReco_Collisions12_JSON.txt");
  //sea->IncludeAJson("Cert_190456-202016_8TeV_PromptReco_Collisions12_JSON.txt");
  //sea->IncludeAJson("Cert_190456-203853_8TeV_PromptReco_Collisions12_JSON.txt");
  sea->IncludeAJson("Cert_190456-208686_8TeV_PromptReco_Collisions12_JSON.txt"); //DeC 14 Json
  //sea->IncludeAJson("anotherJSON.txt");

  TStopwatch ts;

  ts.Start();

  sea->Loop();

  ts.Stop();

  std::cout << "RealTime : " << ts.RealTime()/60.0 << " minutes" << std::endl;
  std::cout << "CPUTime  : " << ts.CpuTime()/60.0 << " minutes" << std::endl;

}
