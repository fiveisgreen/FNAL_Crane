#include "TString.h"
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

void ana_superskim_data(TString ds="relval", TString physics="ttbar") {

  gSystem->Load("libSusyEvent.so");

  // Look ../jec/JetMETObjects/README
  gSystem->Load("../jec/lib/libJetMETObjects.so");

  // Printing utility for ntuple variables
  gROOT->LoadMacro("SusyEventPrinter.cc+");

  // Main analysis code
  gROOT->LoadMacro("SusyMainAna_superskim.cc+");

  // chain of inputs
  TChain* chain = new TChain("susyTree");
  //chain->Add("Susyskim2.root");

//////////////// controls //////////////////
bool useA = false;// /eos/uscms/store/user/lpcpjm/SusyNtuples/cms525v3_jec2012/Run2012A-PromptReco-v1/Photon/Runs190456-193621/
bool useB = false;// /eos/uscms/store/user/lpcpjm/SusyNtuples/cms525v3_jec2012/Run2012B-PromptReco-v1/DoublePhoton/Runs193834-195937/
bool useC1 = false;// /eos/uscms/store/user/lpcpjm/SusyNtuples/cms525v3_jec2012/Run2012C-PromptReco-v1/DoublePhoton/Runs198022-198903/
bool useC2 = false;// /eos/uscms/store/user/lpcpjm/SusyNtuples/cms525v3_jec2012/Run2012C-PromptReco-v2/DoublePhoton/Runs198941-199103/
bool useD1 = true;
bool useD2 = false;
//sea->IncludeAJson("Cert_190456-199429_8TeV_PromptReco_Collisions12_JSON.txt");
bool useSkim = false; //use just the medium skin. 

//using Cert_190456-202016_8TeV_PromptReco_Collisions12_JSON.txt

bool useMC = false;


//////////////// data /////////////////



if(useMC){
//chain->Add("Susysignal_1030evt.root");
//chain->Add("../susyEvents_bydmason.root");
useA = false;
useB = false;
useC1 = false;
useC2 = false;
useD2 = false;
useD2 = false;
useSkim = false;
}

if(useSkim){
//chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012/Susyskim53X_12ABC_mediumphotons.root");
chain->Add("/eos/uscms/store/user/abarker/SusyEvents_skim_data_A2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyEvents_skim_data_A3.root");
chain->Add("/eos/uscms/store/user/abarker/SusyEvents_skim_data_B.root");
chain->Add("/eos/uscms/store/user/abarker/SusyEvents_skim_data_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyEvents_skim_data_C1.root");
}

if(useA){ //get rid of file 36 
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_0.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_1.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_10.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_11.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_12.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_13.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_14.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_15.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_16.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_17.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_18.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_19.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_2.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_20.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_21.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_22.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_23.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_24.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_25.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_26.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_27.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_28.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_29.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_3.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_30.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_31.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_32.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_33.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_34.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_35.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_36.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_37.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_38.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_39.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_4.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_40.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_41.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_42.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_43.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_44.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_45.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_46.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_47.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_48.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_49.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_5.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_50.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_51.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_52.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_53.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_54.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_55.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_56.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_57.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_58.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_59.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_6.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_60.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_61.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_62.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_63.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_64.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_65.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_66.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_67.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_7.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_8.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12A_9.root");

}

if(useB){//don't use file 37 or 79
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_0.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_1.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_10.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_100.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_101.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_102.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_103.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_104.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_105.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_106.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_107.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_108.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_109.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_11.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_110.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_111.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_112.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_113.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_114.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_115.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_116.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_117.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_118.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_119.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_12.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_120.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_121.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_122.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_123.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_124.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_125.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_126.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_127.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_13.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_14.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_15.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_16.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_17.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_18.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_19.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_2.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_20.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_21.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_22.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_23.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_24.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_25.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_26.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_27.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_28.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_29.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_3.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_32.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_33.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_34.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_35.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_36.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_37.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_38.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_39.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_4.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_40.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_41.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_42.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_43.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_44.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_45.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_46.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_47.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_48.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_49.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_5.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_50.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_51.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_52.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_53.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_54.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_55.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_56.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_57.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_58.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_59.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_6.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_60.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_61.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_62.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_63.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_64.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_65.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_66.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_67.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_68.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_69.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_7.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_70.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_71.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_72.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_73.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_74.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_75.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_76.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_77.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_78.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_79.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_8.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_80.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_81.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_82.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_83.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_84.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_85.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_86.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_87.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_88.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_89.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_9.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_90.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_91.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_92.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_93.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_94.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_95.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_96.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_97.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_98.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12B_99.root");

}


if(useC1){
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C1_0.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C1_1.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C1_10.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C1_11.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C1_12.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C1_13.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C1_2.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C1_3.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C1_4.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C1_5.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C1_6.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C1_7.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C1_8.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C1_9.root");

}

if(useC2){
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_0.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_1.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_10.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_100.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_101.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_102.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_103.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_104.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_105.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_106.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_107.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_108.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_109.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_11.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_110.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_111.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_112.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_113.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_114.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_115.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_116.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_117.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_118.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_119.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_12.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_120.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_121.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_122.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_123.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_124.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_125.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_126.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_127.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_128.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_129.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_13.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_130.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_131.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_132.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_133.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_134.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_135.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_136.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_137.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_138.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_139.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_14.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_140.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_141.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_142.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_143.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_144.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_145.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_146.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_147.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_148.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_149.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_15.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_150.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_151.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_152.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_153.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_154.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_155.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_156.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_157.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_158.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_159.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_16.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_160.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_161.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_162.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_163.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_164.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_165.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_166.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_167.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_168.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_169.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_17.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_170.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_171.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_172.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_173.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_174.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_175.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_176.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_177.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_178.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_179.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_18.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_180.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_181.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_182.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_183.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_184.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_185.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_186.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_187.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_188.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_189.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_19.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_190.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_191.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_192.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_193.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_194.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_195.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_196.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_2.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_20.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_21.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_22.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_23.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_24.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_25.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_26.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_27.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_28.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_29.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_3.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_30.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_31.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_32.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_33.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_34.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_35.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_36.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_37.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_38.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_39.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_4.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_40.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_41.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_42.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_43.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_44.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_45.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_46.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_47.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_48.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_49.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_5.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_50.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_51.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_52.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_53.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_54.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_55.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_56.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_57.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_58.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_59.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_6.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_60.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_61.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_62.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_63.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_64.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_65.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_66.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_67.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_68.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_69.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_7.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_70.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_71.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_72.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_73.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_74.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_75.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_76.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_77.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_78.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_79.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_8.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_80.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_81.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_82.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_83.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_84.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_85.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_86.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_87.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_88.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_89.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_9.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_90.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_91.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_92.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_93.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_94.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_95.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_96.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_97.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_98.root");
chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012_bf2/SuperSkim53X_data_bf1_12C2_99.root");
}

if(useD1){
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_94.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_19.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_15.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_64.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_68.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_93.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_18.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_20.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_56.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_34.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_59.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_35.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_57.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_65.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_31.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_52.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_67.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_38.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_61.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_30.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_69.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_27.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_84.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_70.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_96.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_81.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_92.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_16.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_46.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_95.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_22.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_102.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_86.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_28.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_60.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_77.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_25.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_58.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_85.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_62.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_33.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_78.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_82.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_26.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_71.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_48.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_63.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_10.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_5.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_23.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_91.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_9.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_74.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_12.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_50.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_17.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_89.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_32.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_47.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_83.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_13.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_100.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_36.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_49.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_51.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_37.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_101.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_24.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_3.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_53.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_4.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_72.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_11.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_75.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_97.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_76.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_43.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_66.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_98.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_90.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_54.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_14.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_55.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_44.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_7.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_99.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_73.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_103.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_45.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_42.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_79.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_80.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_8.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_6.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_0.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_29.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_40.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_88.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_2.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_41.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_1.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_21.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_87.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_39.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D1_104.root");
}

if(useD2){
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_96.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_80.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_69.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_59.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_40.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_25.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_94.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_43.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_28.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_38.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_91.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_100.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_32.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_19.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_11.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_92.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_8.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_29.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_1.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_55.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_63.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_15.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_22.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_93.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_10.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_7.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_6.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_9.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_81.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_88.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_31.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_90.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_30.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_75.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_21.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_5.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_97.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_23.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_42.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_3.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_24.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_46.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_58.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_64.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_73.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_99.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_56.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_68.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_65.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_103.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_74.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_79.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_87.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_82.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_20.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_86.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_47.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_51.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_13.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_14.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_84.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_85.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_70.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_102.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_98.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_12.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_61.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_101.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_83.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_67.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_34.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_66.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_36.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_27.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_95.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_4.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_39.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_52.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_17.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_18.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_26.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_89.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_33.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_41.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_57.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_104.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_44.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_60.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_77.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_49.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_76.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_54.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_37.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_16.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_71.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_53.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_35.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_72.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_0.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_48.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_78.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_50.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_62.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_2.root");
chain->Add("/uscmst1b_scratch/lpc1/3DayLifetime/abarker/2012D/SuperSkim53X_data_bf1_12D2_45.root");
}

//if(useb1_dcache){
//chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_v2_2012/SuperSkim_MC_12B1_37.root");
//chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_v2_2012/SuperSkim_MC_12B1_79.root");
//}

  SusyMainAna_superskim* sea = new SusyMainAna_superskim(chain);

  // configuration parameters
  // any values given here will replace the default values
  sea->SetDataset(physics+"_"+ds);        // dataset name
  sea->SetPrintInterval(1e4);             // print frequency
  sea->SetPrintLevel(0);                  // print level for event contents
  sea->SetUseTrigger(true);
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
