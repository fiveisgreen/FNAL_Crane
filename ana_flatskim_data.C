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

void ana_flatskim_data(TString ds="relval", TString physics="ttbar") {

  gSystem->Load("libSusyEvent.so");

  // Look ../jec/JetMETObjects/README
  gSystem->Load("../jec/lib/libJetMETObjects.so");

  // Printing utility for ntuple variables
  gROOT->LoadMacro("SusyEventPrinter.cc+");

  // Main analysis code
  gROOT->LoadMacro("SusySkimmer.cc+");


/*


DO NOT USE THIS!!!



*/


  // chain of inputs
  TChain* chain = new TChain("susyTree");
  //chain->Add("Susyskim2.root");

//////////////// controls //////////////////
bool useAB = false;
bool useC = false;
bool useMC = false;







//////////////// switches //////////////////
bool useA = false;// /eos/uscms/store/user/lpcpjm/SusyNtuples/cms525v3_jec2012/Run2012A-PromptReco-v1/Photon/Runs190456-193621/
bool useB1 = false;// /eos/uscms/store/user/lpcpjm/SusyNtuples/cms525v3_jec2012/Run2012B-PromptReco-v1/DoublePhoton/Runs193834-195937/
bool useB2 = false;// /eos/uscms/store/user/lpcpjm/SusyNtuples/cms525v3_jec2012/Run2012B-PromptReco-v1/DoublePhoton/Runs195947-196203/
bool useB3 = false;// /eos/uscms/store/user/lpcpjm/SusyNtuples/cms525v3_jec2012/Run2012B-PromptReco-v1/DoublePhoton/Runs196218-196531/
bool useC1 = false;// /eos/uscms/store/user/lpcpjm/SusyNtuples/cms525v3_jec2012/Run2012C-PromptReco-v1/DoublePhoton/Runs198022-198903/
bool useC2 = false;// /eos/uscms/store/user/lpcpjm/SusyNtuples/cms525v3_jec2012/Run2012C-PromptReco-v2/DoublePhoton/Runs198941-199103/
//sea->IncludeAJson("Cert_190456-199429_8TeV_PromptReco_Collisions12_JSON.txt");

bool useC3 = false;// /eos/uscms/store/user/lpcpjm/SusyNtuples/cms525v3_jec2012/Run2012C-PromptReco-v2/DoublePhoton/Runs199275-200190/
bool useC4 = false;// /eos/uscms/store/user/lpcpjm/SusyNtuples/cms525v3_jec2012/Run2012C-PromptReco-v2/DoublePhoton/Runs200228-200601/
bool useC5 = false;// /eos/uscms/store/user/lpcpjm/SusyNtuples/cms525v3_jec2012/Run2012C-PromptReco-v2/DoublePhoton/Runs200781-202016/
//using Cert_190456-202016_8TeV_PromptReco_Collisions12_JSON.txt

if(useAB){
useA = true;
useB1 = true;
useB2 = true;
useB3 = true;
}
if(useC){
useC1 = true;
useC2 = true;
useC3 = true;
useC4 = true;
useC5 = true;
}


//////////////// data /////////////////



if(useMC){
//chain->Add("Susysignal_1030evt.root");
//chain->Add("../susyEvents_bydmason.root");
useA = false;
useB1 = false;
useB2 = false;
useB3 = false;
useC1 = false;
useC2 = false;
useC3 = false;
useC4 = false;
useC5 = false;
}






chain->Add("Tripathi_skim_data_pi05met202.root");
//chain->Add("Tripathi_events_data_mggPlot2.root");

if(useA){ //get rid of file 36 
chain->Add("looseSkims/SuperSkim_data_12A_0.root");
chain->Add("looseSkims/SuperSkim_data_12A_1.root");
chain->Add("looseSkims/SuperSkim_data_12A_10.root");
chain->Add("looseSkims/SuperSkim_data_12A_11.root");
chain->Add("looseSkims/SuperSkim_data_12A_12.root");
chain->Add("looseSkims/SuperSkim_data_12A_13.root");
chain->Add("looseSkims/SuperSkim_data_12A_14.root");
chain->Add("looseSkims/SuperSkim_data_12A_15.root");
chain->Add("looseSkims/SuperSkim_data_12A_16.root");
chain->Add("looseSkims/SuperSkim_data_12A_17.root");
chain->Add("looseSkims/SuperSkim_data_12A_18.root");
chain->Add("looseSkims/SuperSkim_data_12A_19.root");
chain->Add("looseSkims/SuperSkim_data_12A_2.root");
chain->Add("looseSkims/SuperSkim_data_12A_20.root");
chain->Add("looseSkims/SuperSkim_data_12A_21.root");
chain->Add("looseSkims/SuperSkim_data_12A_22.root");
chain->Add("looseSkims/SuperSkim_data_12A_23.root");
chain->Add("looseSkims/SuperSkim_data_12A_24.root");
chain->Add("looseSkims/SuperSkim_data_12A_25.root");
chain->Add("looseSkims/SuperSkim_data_12A_26.root");
chain->Add("looseSkims/SuperSkim_data_12A_27.root");
chain->Add("looseSkims/SuperSkim_data_12A_28.root");
chain->Add("looseSkims/SuperSkim_data_12A_29.root");
chain->Add("looseSkims/SuperSkim_data_12A_3.root");
chain->Add("looseSkims/SuperSkim_data_12A_30.root");
chain->Add("looseSkims/SuperSkim_data_12A_31.root");
chain->Add("looseSkims/SuperSkim_data_12A_32.root");
chain->Add("looseSkims/SuperSkim_data_12A_33.root");
chain->Add("looseSkims/SuperSkim_data_12A_34.root");
chain->Add("looseSkims/SuperSkim_data_12A_35.root");
//chain->Add("looseSkims/SuperSkim_data_12A_36.root");
chain->Add("looseSkims/SuperSkim_data_12A_37.root");
chain->Add("looseSkims/SuperSkim_data_12A_38.root");
chain->Add("looseSkims/SuperSkim_data_12A_39.root");
chain->Add("looseSkims/SuperSkim_data_12A_4.root");
chain->Add("looseSkims/SuperSkim_data_12A_40.root");
chain->Add("looseSkims/SuperSkim_data_12A_41.root");
chain->Add("looseSkims/SuperSkim_data_12A_42.root");
chain->Add("looseSkims/SuperSkim_data_12A_43.root");
chain->Add("looseSkims/SuperSkim_data_12A_44.root");
chain->Add("looseSkims/SuperSkim_data_12A_45.root");
chain->Add("looseSkims/SuperSkim_data_12A_46.root");
chain->Add("looseSkims/SuperSkim_data_12A_47.root");
chain->Add("looseSkims/SuperSkim_data_12A_48.root");
chain->Add("looseSkims/SuperSkim_data_12A_49.root");
chain->Add("looseSkims/SuperSkim_data_12A_5.root");
chain->Add("looseSkims/SuperSkim_data_12A_50.root");
chain->Add("looseSkims/SuperSkim_data_12A_51.root");
chain->Add("looseSkims/SuperSkim_data_12A_52.root");
chain->Add("looseSkims/SuperSkim_data_12A_53.root");
chain->Add("looseSkims/SuperSkim_data_12A_54.root");
chain->Add("looseSkims/SuperSkim_data_12A_55.root");
chain->Add("looseSkims/SuperSkim_data_12A_56.root");
chain->Add("looseSkims/SuperSkim_data_12A_57.root");
chain->Add("looseSkims/SuperSkim_data_12A_58.root");
chain->Add("looseSkims/SuperSkim_data_12A_59.root");
chain->Add("looseSkims/SuperSkim_data_12A_6.root");
chain->Add("looseSkims/SuperSkim_data_12A_60.root");
chain->Add("looseSkims/SuperSkim_data_12A_61.root");
chain->Add("looseSkims/SuperSkim_data_12A_62.root");
chain->Add("looseSkims/SuperSkim_data_12A_63.root");
chain->Add("looseSkims/SuperSkim_data_12A_64.root");
chain->Add("looseSkims/SuperSkim_data_12A_65.root");
chain->Add("looseSkims/SuperSkim_data_12A_66.root");
chain->Add("looseSkims/SuperSkim_data_12A_67.root");
chain->Add("looseSkims/SuperSkim_data_12A_7.root");
chain->Add("looseSkims/SuperSkim_data_12A_8.root");
chain->Add("looseSkims/SuperSkim_data_12A_9.root");
}


if(useB1){//don't use file 37 or 79
chain->Add("looseSkims/SuperSkim_data_12B1_0.root");
chain->Add("looseSkims/SuperSkim_data_12B1_1.root");
chain->Add("looseSkims/SuperSkim_data_12B1_10.root");
chain->Add("looseSkims/SuperSkim_data_12B1_100.root");
chain->Add("looseSkims/SuperSkim_data_12B1_101.root");
chain->Add("looseSkims/SuperSkim_data_12B1_102.root");
chain->Add("looseSkims/SuperSkim_data_12B1_11.root");
chain->Add("looseSkims/SuperSkim_data_12B1_12.root");
chain->Add("looseSkims/SuperSkim_data_12B1_13.root");
chain->Add("looseSkims/SuperSkim_data_12B1_14.root");
chain->Add("looseSkims/SuperSkim_data_12B1_15.root");
chain->Add("looseSkims/SuperSkim_data_12B1_16.root");
chain->Add("looseSkims/SuperSkim_data_12B1_17.root");
chain->Add("looseSkims/SuperSkim_data_12B1_18.root");
chain->Add("looseSkims/SuperSkim_data_12B1_19.root");
chain->Add("looseSkims/SuperSkim_data_12B1_2.root");
chain->Add("looseSkims/SuperSkim_data_12B1_20.root");
chain->Add("looseSkims/SuperSkim_data_12B1_21.root");
chain->Add("looseSkims/SuperSkim_data_12B1_22.root");
chain->Add("looseSkims/SuperSkim_data_12B1_23.root");
chain->Add("looseSkims/SuperSkim_data_12B1_24.root");
chain->Add("looseSkims/SuperSkim_data_12B1_25.root");
chain->Add("looseSkims/SuperSkim_data_12B1_26.root");
chain->Add("looseSkims/SuperSkim_data_12B1_27.root");
chain->Add("looseSkims/SuperSkim_data_12B1_28.root");
chain->Add("looseSkims/SuperSkim_data_12B1_29.root");
chain->Add("looseSkims/SuperSkim_data_12B1_3.root");
chain->Add("looseSkims/SuperSkim_data_12B1_30.root");
chain->Add("looseSkims/SuperSkim_data_12B1_31.root");
chain->Add("looseSkims/SuperSkim_data_12B1_32.root");
chain->Add("looseSkims/SuperSkim_data_12B1_33.root");
chain->Add("looseSkims/SuperSkim_data_12B1_34.root");
chain->Add("looseSkims/SuperSkim_data_12B1_35.root");
chain->Add("looseSkims/SuperSkim_data_12B1_36.root");
//chain->Add("looseSkims/SuperSkim_data_12B1_37.root");
chain->Add("looseSkims/SuperSkim_data_12B1_38.root");
chain->Add("looseSkims/SuperSkim_data_12B1_39.root");
chain->Add("looseSkims/SuperSkim_data_12B1_4.root");
chain->Add("looseSkims/SuperSkim_data_12B1_40.root");
chain->Add("looseSkims/SuperSkim_data_12B1_41.root");
chain->Add("looseSkims/SuperSkim_data_12B1_42.root");
chain->Add("looseSkims/SuperSkim_data_12B1_43.root");
chain->Add("looseSkims/SuperSkim_data_12B1_44.root");
chain->Add("looseSkims/SuperSkim_data_12B1_45.root");
chain->Add("looseSkims/SuperSkim_data_12B1_46.root");
chain->Add("looseSkims/SuperSkim_data_12B1_47.root");
chain->Add("looseSkims/SuperSkim_data_12B1_48.root");
chain->Add("looseSkims/SuperSkim_data_12B1_49.root");
chain->Add("looseSkims/SuperSkim_data_12B1_5.root");
chain->Add("looseSkims/SuperSkim_data_12B1_50.root");
chain->Add("looseSkims/SuperSkim_data_12B1_51.root");
chain->Add("looseSkims/SuperSkim_data_12B1_52.root");
chain->Add("looseSkims/SuperSkim_data_12B1_53.root");
chain->Add("looseSkims/SuperSkim_data_12B1_54.root");
chain->Add("looseSkims/SuperSkim_data_12B1_55.root");
chain->Add("looseSkims/SuperSkim_data_12B1_56.root");
chain->Add("looseSkims/SuperSkim_data_12B1_57.root");
chain->Add("looseSkims/SuperSkim_data_12B1_58.root");
chain->Add("looseSkims/SuperSkim_data_12B1_59.root");
chain->Add("looseSkims/SuperSkim_data_12B1_6.root");
chain->Add("looseSkims/SuperSkim_data_12B1_60.root");
chain->Add("looseSkims/SuperSkim_data_12B1_61.root");
chain->Add("looseSkims/SuperSkim_data_12B1_62.root");
chain->Add("looseSkims/SuperSkim_data_12B1_63.root");
chain->Add("looseSkims/SuperSkim_data_12B1_64.root");
chain->Add("looseSkims/SuperSkim_data_12B1_65.root");
chain->Add("looseSkims/SuperSkim_data_12B1_66.root");
chain->Add("looseSkims/SuperSkim_data_12B1_67.root");
chain->Add("looseSkims/SuperSkim_data_12B1_68.root");
chain->Add("looseSkims/SuperSkim_data_12B1_69.root");
chain->Add("looseSkims/SuperSkim_data_12B1_7.root");
chain->Add("looseSkims/SuperSkim_data_12B1_70.root");
chain->Add("looseSkims/SuperSkim_data_12B1_71.root");
chain->Add("looseSkims/SuperSkim_data_12B1_72.root");
chain->Add("looseSkims/SuperSkim_data_12B1_73.root");
chain->Add("looseSkims/SuperSkim_data_12B1_74.root");
chain->Add("looseSkims/SuperSkim_data_12B1_75.root");
chain->Add("looseSkims/SuperSkim_data_12B1_76.root");
chain->Add("looseSkims/SuperSkim_data_12B1_77.root");
chain->Add("looseSkims/SuperSkim_data_12B1_78.root");
chain->Add("looseSkims/SuperSkim_data_12B1_79.root");
chain->Add("looseSkims/SuperSkim_data_12B1_8.root");
chain->Add("looseSkims/SuperSkim_data_12B1_80.root");
chain->Add("looseSkims/SuperSkim_data_12B1_81.root");
chain->Add("looseSkims/SuperSkim_data_12B1_82.root");
chain->Add("looseSkims/SuperSkim_data_12B1_83.root");
chain->Add("looseSkims/SuperSkim_data_12B1_84.root");
chain->Add("looseSkims/SuperSkim_data_12B1_85.root");
chain->Add("looseSkims/SuperSkim_data_12B1_86.root");
chain->Add("looseSkims/SuperSkim_data_12B1_87.root");
chain->Add("looseSkims/SuperSkim_data_12B1_88.root");
chain->Add("looseSkims/SuperSkim_data_12B1_89.root");
chain->Add("looseSkims/SuperSkim_data_12B1_9.root");
chain->Add("looseSkims/SuperSkim_data_12B1_90.root");
chain->Add("looseSkims/SuperSkim_data_12B1_91.root");
chain->Add("looseSkims/SuperSkim_data_12B1_92.root");
chain->Add("looseSkims/SuperSkim_data_12B1_93.root");
chain->Add("looseSkims/SuperSkim_data_12B1_94.root");
chain->Add("looseSkims/SuperSkim_data_12B1_95.root");
chain->Add("looseSkims/SuperSkim_data_12B1_96.root");
chain->Add("looseSkims/SuperSkim_data_12B1_97.root");
chain->Add("looseSkims/SuperSkim_data_12B1_98.root");
chain->Add("looseSkims/SuperSkim_data_12B1_99.root");
}

if(useB2){
chain->Add("looseSkims/SuperSkim_data_12B2_0.root");
chain->Add("looseSkims/SuperSkim_data_12B2_1.root");
chain->Add("looseSkims/SuperSkim_data_12B2_2.root");
chain->Add("looseSkims/SuperSkim_data_12B2_3.root");
chain->Add("looseSkims/SuperSkim_data_12B2_4.root");
chain->Add("looseSkims/SuperSkim_data_12B2_5.root");
chain->Add("looseSkims/SuperSkim_data_12B2_6.root");
chain->Add("looseSkims/SuperSkim_data_12B2_7.root");
chain->Add("looseSkims/SuperSkim_data_12B2_8.root");
chain->Add("looseSkims/SuperSkim_data_12B2_9.root");
}

if(useB3){
chain->Add("looseSkims/SuperSkim_data_12B3_0.root");
chain->Add("looseSkims/SuperSkim_data_12B3_1.root");
chain->Add("looseSkims/SuperSkim_data_12B3_10.root");
chain->Add("looseSkims/SuperSkim_data_12B3_11.root");
chain->Add("looseSkims/SuperSkim_data_12B3_12.root");
chain->Add("looseSkims/SuperSkim_data_12B3_13.root");
chain->Add("looseSkims/SuperSkim_data_12B3_14.root");
chain->Add("looseSkims/SuperSkim_data_12B3_15.root");
chain->Add("looseSkims/SuperSkim_data_12B3_16.root");
chain->Add("looseSkims/SuperSkim_data_12B3_17.root");
chain->Add("looseSkims/SuperSkim_data_12B3_18.root");
chain->Add("looseSkims/SuperSkim_data_12B3_19.root");
chain->Add("looseSkims/SuperSkim_data_12B3_2.root");
chain->Add("looseSkims/SuperSkim_data_12B3_3.root");
chain->Add("looseSkims/SuperSkim_data_12B3_4.root");
chain->Add("looseSkims/SuperSkim_data_12B3_5.root");
chain->Add("looseSkims/SuperSkim_data_12B3_6.root");
chain->Add("looseSkims/SuperSkim_data_12B3_7.root");
chain->Add("looseSkims/SuperSkim_data_12B3_8.root");
chain->Add("looseSkims/SuperSkim_data_12B3_9.root");
}

if(useC1){
chain->Add("looseSkims/SuperSkim_data_12C1_0.root");
chain->Add("looseSkims/SuperSkim_data_12C1_1.root");
chain->Add("looseSkims/SuperSkim_data_12C1_10.root");
chain->Add("looseSkims/SuperSkim_data_12C1_11.root");
chain->Add("looseSkims/SuperSkim_data_12C1_12.root");
chain->Add("looseSkims/SuperSkim_data_12C1_13.root");
chain->Add("looseSkims/SuperSkim_data_12C1_2.root");
chain->Add("looseSkims/SuperSkim_data_12C1_3.root");
chain->Add("looseSkims/SuperSkim_data_12C1_4.root");
chain->Add("looseSkims/SuperSkim_data_12C1_5.root");
chain->Add("looseSkims/SuperSkim_data_12C1_6.root");
chain->Add("looseSkims/SuperSkim_data_12C1_7.root");
chain->Add("looseSkims/SuperSkim_data_12C1_8.root");
chain->Add("looseSkims/SuperSkim_data_12C1_9.root");
}

if(useC2){
chain->Add("looseSkims/SuperSkim_data_12C2_0.root");
chain->Add("looseSkims/SuperSkim_data_12C2_1.root");
chain->Add("looseSkims/SuperSkim_data_12C2_10.root");
chain->Add("looseSkims/SuperSkim_data_12C2_11.root");
chain->Add("looseSkims/SuperSkim_data_12C2_12.root");
chain->Add("looseSkims/SuperSkim_data_12C2_13.root");
chain->Add("looseSkims/SuperSkim_data_12C2_14.root");
chain->Add("looseSkims/SuperSkim_data_12C2_2.root");
chain->Add("looseSkims/SuperSkim_data_12C2_3.root");
chain->Add("looseSkims/SuperSkim_data_12C2_4.root");
chain->Add("looseSkims/SuperSkim_data_12C2_5.root");
chain->Add("looseSkims/SuperSkim_data_12C2_6.root");
chain->Add("looseSkims/SuperSkim_data_12C2_7.root");
chain->Add("looseSkims/SuperSkim_data_12C2_8.root");
chain->Add("looseSkims/SuperSkim_data_12C2_9.root");
}

if(useC3){
chain->Add("looseSkims/SuperSkim_data_12C3_0.root");
chain->Add("looseSkims/SuperSkim_data_12C3_1.root");
chain->Add("looseSkims/SuperSkim_data_12C3_10.root");
chain->Add("looseSkims/SuperSkim_data_12C3_11.root");
chain->Add("looseSkims/SuperSkim_data_12C3_12.root");
chain->Add("looseSkims/SuperSkim_data_12C3_13.root");
chain->Add("looseSkims/SuperSkim_data_12C3_14.root");
chain->Add("looseSkims/SuperSkim_data_12C3_15.root");
chain->Add("looseSkims/SuperSkim_data_12C3_16.root");
chain->Add("looseSkims/SuperSkim_data_12C3_17.root");
chain->Add("looseSkims/SuperSkim_data_12C3_18.root");
chain->Add("looseSkims/SuperSkim_data_12C3_19.root");
chain->Add("looseSkims/SuperSkim_data_12C3_2.root");
chain->Add("looseSkims/SuperSkim_data_12C3_20.root");
chain->Add("looseSkims/SuperSkim_data_12C3_21.root");
chain->Add("looseSkims/SuperSkim_data_12C3_22.root");
chain->Add("looseSkims/SuperSkim_data_12C3_23.root");
chain->Add("looseSkims/SuperSkim_data_12C3_24.root");
chain->Add("looseSkims/SuperSkim_data_12C3_25.root");
chain->Add("looseSkims/SuperSkim_data_12C3_26.root");
chain->Add("looseSkims/SuperSkim_data_12C3_27.root");
chain->Add("looseSkims/SuperSkim_data_12C3_28.root");
chain->Add("looseSkims/SuperSkim_data_12C3_29.root");
chain->Add("looseSkims/SuperSkim_data_12C3_3.root");
chain->Add("looseSkims/SuperSkim_data_12C3_30.root");
chain->Add("looseSkims/SuperSkim_data_12C3_31.root");
chain->Add("looseSkims/SuperSkim_data_12C3_32.root");
chain->Add("looseSkims/SuperSkim_data_12C3_33.root");
chain->Add("looseSkims/SuperSkim_data_12C3_34.root");
chain->Add("looseSkims/SuperSkim_data_12C3_35.root");
chain->Add("looseSkims/SuperSkim_data_12C3_36.root");
chain->Add("looseSkims/SuperSkim_data_12C3_37.root");
chain->Add("looseSkims/SuperSkim_data_12C3_38.root");
chain->Add("looseSkims/SuperSkim_data_12C3_39.root");
chain->Add("looseSkims/SuperSkim_data_12C3_4.root");
chain->Add("looseSkims/SuperSkim_data_12C3_40.root");
chain->Add("looseSkims/SuperSkim_data_12C3_41.root");
chain->Add("looseSkims/SuperSkim_data_12C3_42.root");
chain->Add("looseSkims/SuperSkim_data_12C3_43.root");
chain->Add("looseSkims/SuperSkim_data_12C3_44.root");
chain->Add("looseSkims/SuperSkim_data_12C3_45.root");
chain->Add("looseSkims/SuperSkim_data_12C3_46.root");
chain->Add("looseSkims/SuperSkim_data_12C3_47.root");
chain->Add("looseSkims/SuperSkim_data_12C3_48.root");
chain->Add("looseSkims/SuperSkim_data_12C3_49.root");
chain->Add("looseSkims/SuperSkim_data_12C3_5.root");
chain->Add("looseSkims/SuperSkim_data_12C3_50.root");
chain->Add("looseSkims/SuperSkim_data_12C3_51.root");
chain->Add("looseSkims/SuperSkim_data_12C3_52.root");
chain->Add("looseSkims/SuperSkim_data_12C3_53.root");
chain->Add("looseSkims/SuperSkim_data_12C3_54.root");
chain->Add("looseSkims/SuperSkim_data_12C3_55.root");
chain->Add("looseSkims/SuperSkim_data_12C3_56.root");
chain->Add("looseSkims/SuperSkim_data_12C3_57.root");
chain->Add("looseSkims/SuperSkim_data_12C3_58.root");
chain->Add("looseSkims/SuperSkim_data_12C3_59.root");
chain->Add("looseSkims/SuperSkim_data_12C3_6.root");
chain->Add("looseSkims/SuperSkim_data_12C3_60.root");
chain->Add("looseSkims/SuperSkim_data_12C3_61.root");
chain->Add("looseSkims/SuperSkim_data_12C3_62.root");
chain->Add("looseSkims/SuperSkim_data_12C3_63.root");
chain->Add("looseSkims/SuperSkim_data_12C3_64.root");
chain->Add("looseSkims/SuperSkim_data_12C3_65.root");
chain->Add("looseSkims/SuperSkim_data_12C3_66.root");
chain->Add("looseSkims/SuperSkim_data_12C3_67.root");
chain->Add("looseSkims/SuperSkim_data_12C3_68.root");
chain->Add("looseSkims/SuperSkim_data_12C3_69.root");
chain->Add("looseSkims/SuperSkim_data_12C3_7.root");
chain->Add("looseSkims/SuperSkim_data_12C3_70.root");
chain->Add("looseSkims/SuperSkim_data_12C3_71.root");
chain->Add("looseSkims/SuperSkim_data_12C3_72.root");
chain->Add("looseSkims/SuperSkim_data_12C3_8.root");
chain->Add("looseSkims/SuperSkim_data_12C3_9.root");
}


if(useC4){
chain->Add("looseSkims/SuperSkim_data_12C4_0.root");
chain->Add("looseSkims/SuperSkim_data_12C4_1.root");
chain->Add("looseSkims/SuperSkim_data_12C4_10.root");
chain->Add("looseSkims/SuperSkim_data_12C4_11.root");
chain->Add("looseSkims/SuperSkim_data_12C4_12.root");
chain->Add("looseSkims/SuperSkim_data_12C4_2.root");
chain->Add("looseSkims/SuperSkim_data_12C4_3.root");
chain->Add("looseSkims/SuperSkim_data_12C4_4.root");
chain->Add("looseSkims/SuperSkim_data_12C4_5.root");
chain->Add("looseSkims/SuperSkim_data_12C4_6.root");
chain->Add("looseSkims/SuperSkim_data_12C4_7.root");
chain->Add("looseSkims/SuperSkim_data_12C4_8.root");
chain->Add("looseSkims/SuperSkim_data_12C4_9.root");
}


if(useC5){
chain->Add("looseSkims/SuperSkim_data_12C5_0.root");
chain->Add("looseSkims/SuperSkim_data_12C5_1.root");
chain->Add("looseSkims/SuperSkim_data_12C5_10.root");
chain->Add("looseSkims/SuperSkim_data_12C5_11.root");
chain->Add("looseSkims/SuperSkim_data_12C5_12.root");
chain->Add("looseSkims/SuperSkim_data_12C5_13.root");
chain->Add("looseSkims/SuperSkim_data_12C5_14.root");
chain->Add("looseSkims/SuperSkim_data_12C5_15.root");
chain->Add("looseSkims/SuperSkim_data_12C5_16.root");
chain->Add("looseSkims/SuperSkim_data_12C5_17.root");
chain->Add("looseSkims/SuperSkim_data_12C5_18.root");
chain->Add("looseSkims/SuperSkim_data_12C5_19.root");
chain->Add("looseSkims/SuperSkim_data_12C5_2.root");
chain->Add("looseSkims/SuperSkim_data_12C5_20.root");
chain->Add("looseSkims/SuperSkim_data_12C5_21.root");
chain->Add("looseSkims/SuperSkim_data_12C5_22.root");
chain->Add("looseSkims/SuperSkim_data_12C5_23.root");
chain->Add("looseSkims/SuperSkim_data_12C5_24.root");
chain->Add("looseSkims/SuperSkim_data_12C5_25.root");
chain->Add("looseSkims/SuperSkim_data_12C5_26.root");
chain->Add("looseSkims/SuperSkim_data_12C5_27.root");
chain->Add("looseSkims/SuperSkim_data_12C5_28.root");
chain->Add("looseSkims/SuperSkim_data_12C5_29.root");
chain->Add("looseSkims/SuperSkim_data_12C5_3.root");
chain->Add("looseSkims/SuperSkim_data_12C5_30.root");
chain->Add("looseSkims/SuperSkim_data_12C5_31.root");
chain->Add("looseSkims/SuperSkim_data_12C5_32.root");
chain->Add("looseSkims/SuperSkim_data_12C5_33.root");
chain->Add("looseSkims/SuperSkim_data_12C5_4.root");
chain->Add("looseSkims/SuperSkim_data_12C5_5.root");
chain->Add("looseSkims/SuperSkim_data_12C5_6.root");
chain->Add("looseSkims/SuperSkim_data_12C5_7.root");
chain->Add("looseSkims/SuperSkim_data_12C5_8.root");
chain->Add("looseSkims/SuperSkim_data_12C5_9.root");
}
//if(useb1_dcache){
//chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_v2_2012/SuperSkim_data_12B1_37.root");
//chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_v2_2012/SuperSkim_data_12B1_79.root");
//}

  SusySkimmer* sea = new SusySkimmer(chain);

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
