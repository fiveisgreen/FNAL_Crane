void ana_firstskim(TString label="") {
  gSystem->Load("libSusyEvent.so");
  gSystem->Load("../jec/lib/libJetMETObjects.so");
  gROOT->LoadMacro("SusyEventPrinter.cc+");
  gROOT->LoadMacro("SusyAna_firstskim_Loose.cc+");
  TChain* chain = new TChain("susyTree");
  chain->Add("/pnfs/cms/WAX/resilient/bfrancis/SusyNtuples/cms533v1/PromptReco_recover/Run2012C-v1/Events_1_1_XP7.root");
  chain->Add("/pnfs/cms/WAX/resilient/bfrancis/SusyNtuples/cms533v1/PromptReco_recover/Run2012C-v1/Events_7_1_R7f.root");
  chain->Add("/pnfs/cms/WAX/resilient/bfrancis/SusyNtuples/cms533v1/PromptReco_recover/Run2012C-v1/Events_5_1_BdI.root");
  chain->Add("/pnfs/cms/WAX/resilient/bfrancis/SusyNtuples/cms533v1/PromptReco_recover/Run2012C-v1/Events_6_1_xbw.root");
  chain->Add("/pnfs/cms/WAX/resilient/bfrancis/SusyNtuples/cms533v1/PromptReco_recover/Run2012C-v1/Events_4_1_rnl.root");
  chain->Add("/pnfs/cms/WAX/resilient/bfrancis/SusyNtuples/cms533v1/PromptReco_recover/Run2012C-v1/Events_2_1_e5d.root");
  chain->Add("/pnfs/cms/WAX/resilient/bfrancis/SusyNtuples/cms533v1/PromptReco_recover/Run2012C-v1/Events_9_1_ss0.root");
  chain->Add("/pnfs/cms/WAX/resilient/bfrancis/SusyNtuples/cms533v1/PromptReco_recover/Run2012C-v1/Events_10_1_KCH.root");
  chain->Add("/pnfs/cms/WAX/resilient/bfrancis/SusyNtuples/cms533v1/PromptReco_recover/Run2012C-v1/Events_11_1_Ztp.root");
  chain->Add("/pnfs/cms/WAX/resilient/bfrancis/SusyNtuples/cms533v1/PromptReco_recover/Run2012C-v1/Events_8_1_7Cv.root");
  SusyAna_firstskim_Loose* sea = new SusyAna_firstskim_Loose(chain);
  sea->SetDataset("asdf");
  sea->SetPrintInterval(1e4);             // print frequency
  sea->SetPrintLevel(0);                  // print level for event contents
  sea->SetUseTrigger(true);
  sea->SetFilter(true);                  // filter events passing final cuts
  sea->SetProcessNEvents(-1);             // number of events to be processed
  sea->label = label;
  sea->IncludeAJson("Cert_190456-208686_8TeV_Collisions12_Abarker_Combined_JSON.txt");//combined 2012 json
  TStopwatch ts;
  ts.Start();
  sea->Loop();
  ts.Stop();
  std::cout << "RealTime : " << ts.RealTime()/60.0 << " minutes" << std::endl;
  std::cout << "CPUTime  : " << ts.CpuTime()/60.0 << " minutes" << std::endl;
}
