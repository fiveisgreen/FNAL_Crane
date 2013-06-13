//#include "params.h"
#include "TString.h"
#include "MCpoint.h"
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

void ana_MC_BTagEff(TString ds="relval", TString physics="ttbar") {
{
  gSystem->Load("libSusyEvent.so");

  // Look ../jec/JetMETObjects/README
  gSystem->Load("../jec/lib/libJetMETObjects.so");

  // Printing utility for ntuple variables
  gROOT->LoadMacro("SusyEventPrinter.cc+");

  // Main analysis code
  gROOT->LoadMacro("SusyAna_MC_BTagEff.cc+"); //this line causes everything to segfault at the end.

  // chain of inputs
  TChain* chain = new TChain("susyTree");

//////////////// MC files /////////////////
  MCpoint* thisMCpoint = setupMCpoint(which_MC_to_use2); 
cout<<"try to add "<<thisMCpoint->filepath.c_str()<<endl;
  chain->Add(thisMCpoint->filepath.c_str()); 
//int which_MC_to_use=0; //already set
/*if(which_MC_to_use==0){
   chain->Add("MC/susyEvents_MC_AB_1M_st350_ho200.root");
}
else if(which_MC_to_use==1){
   chain->Add("MC/susyEvents_MC_AB_1M_st250_ho200.root");
}
else if(which_MC_to_use==2){
   chain->Add("MC/susyEvents_MC_AB_1M_st250_ho150.root");
}
else if(which_MC_to_use==3){
   chain->Add("MC/susyEvents_MC_AB_1M_ho140.root");
}
else if(which_MC_to_use==4){
   chain->Add("MC/susyEvents_MC_AB_1M_ho200.root");
}
*/


   //chain->Add("../susyEvents_AB_1M_ho200_v2.root");
   //chain->Add("../susyEvents_newNatural.root");
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


  SusyAna_MC_BTagEff* sea = new SusyAna_MC_BTagEff(chain);

  // configuration parameters
  // any values given here will replace the default values
  sea->SetDataset(physics+"_"+ds);        // dataset name
  sea->SetPrintInterval(1e4);             // print frequency
  sea->SetPrintLevel(0);                  // print level for event contents
  sea->SetUseTrigger(false);
/*
  sea->AddHltName("HLT_Photon36_CaloIdL_Photon22_CaloIdL");  // add HLT trigger path name 
  sea->AddHltName("HLT_Photon32_CaloIdL_Photon26_CaloIdL");  // add HLT trigger path name
  sea->AddHltName("HLT_Photon26_R9Id85_Photon18_R9Id85_Mass60");
  sea->AddHltName("HLT_Photon26_R9Id85_Photon18_CaloId10_Iso50_Mass60");
  sea->AddHltName("HLT_Photon26_CaloId10_Iso50_Photon18_R9Id85_Mass60");
  sea->AddHltName("HLT_Photon26_CaloId10_Iso50_Photon18_CaloId10_Iso50_Mass60");
  sea->AddHltName("HLT_Photon26_R9Id85_OR_CaloId10_Iso50_Photon18_R9Id85_OR_CaloId10_Iso50_Mass60");
  sea->AddHltName("HLT_Photon26_R9Id85_OR_CaloId10_Iso50_Photon18_R9Id85_OR_CaloId10_Iso50_Mass70");
  sea->AddHltName("HLT_Photon36_R9Id85_Photon22_R9Id85");
  sea->AddHltName("HLT_Photon36_R9Id85_Photon22_CaloId10_Iso50");
  sea->AddHltName("HLT_Photon36_CaloId10_Iso50_Photon22_R9Id85");
  sea->AddHltName("HLT_Photon36_CaloId10_Iso50_Photon22_CaloId10_Iso50");
  sea->AddHltName("HLT_Photon36_R9Id85_OR_CaloId10_Iso50_Photon22_R9Id85_OR_CaloId10_Iso50");
*/
  sea->SetFilter(true);                  // filter events passing final cuts
  sea->SetProcessNEvents(-1);             // number of events to be processed

  // as an example -- add your favorite Json here.  More than one can be "Include"ed
  //  sea->IncludeAJson("Cert_161079-161352_7TeV_PromptReco_Collisions11_JSON_noESpbl_v2.txt");
  //sea->IncludeAJson("anotherJSON.txt");

  TStopwatch ts;

  ts.Start();

  sea->Loop();

  ts.Stop();

  std::cout << "RealTime : " << ts.RealTime()/60.0 << " minutes" << std::endl;
  std::cout << "CPUTime  : " << ts.CpuTime()/60.0 << " minutes" << std::endl;
	}
  std::cout << "super end"<<std::endl;
	

}
