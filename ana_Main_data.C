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

void ana_Main_data(TString ds="relval", TString physics="ttbar") {

  gSystem->Load("libSusyEvent.so");

  // Look ../jec/JetMETObjects/README
  gSystem->Load("../jec/lib/libJetMETObjects.so");

  // Printing utility for ntuple variables
  gROOT->LoadMacro("SusyEventPrinter.cc+");

  // Main analysis code
  gROOT->LoadMacro("SusyMainAna.cc+");

  // chain of inputs
  TChain* chain = new TChain("susyTree");
  //chain->Add("Susyskim2.root");

//chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012/ReSkim53X_data_susyEvents_998_1_Xk3_D.root");
//chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012/ReSkim53X_data_susyEvents_99_1_Frm_A.root");
////


chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1000_1_6cI_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1019_3_0Ot_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1037_1_29y_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1064_1_3Ur_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1091_1_YqB_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1127_1_rLf_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1154_1_k5M_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1181_1_hNQ_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1226_2_QQQ_B.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1253_1_hOK_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_128_1_8x2_B.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1307_1_EaG_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1334_1_cgK_B.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_137_1_lET_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1406_1_Nhx_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1451_1_2CN_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_148_1_Ijh_B.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1523_1_QtU_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_155_1_T4L_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1596_1_SjJ_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1631_1_VKh_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1668_1_3W7_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1712_1_9Du_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1749_1_AXO_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1785_3_IF7_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1820_1_wYA_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1857_1_QRm_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1901_1_eig_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1938_1_cnS_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1974_1_h8v_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_1_1_I3c_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_2027_1_IS1_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_2090_1_LdY_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_214_2_up1_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_227_1_kzr_A.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_24_1_5Zp_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_263_1_1B9_A.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_278_2_7QN_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_292_1_Sy2_B.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_312_1_PAF_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_328_1_wKK_B.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_349_1_FRp_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_367_1_ONS_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_382_1_HD1_B.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_409_1_zs4_B.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_425_1_VDu_A.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_45_1_ycw_A.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_470_1_dz3_A.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_489_2_Tcy_A.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_510_1_Eax_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_535_1_qTm_B.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_556_2_Cjf_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_58_1_0Ia_B.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_607_1_QRZ_B.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_63_1_IfQ_A.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_652_1_LKr_B.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_682_1_9Bj_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_715_2_yQY_B.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_74_1_06Z_C1.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_763_1_K9e_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_79_1_5S6_C2.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_82_1_xGy_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_841_1_r3o_B.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_871_1_eh1_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_899_2_CH9_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_922_1_s33_B.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_952_1_QB4_D.root");
chain->Add("/eos/uscms/store/user/abarker/SusyLooseSkim_v3_2012_phopho2/ReSkim53X_data_ReSkim53X_data_susyEvents_977_1_oWs_B.root");



  SusyMainAna* sea = new SusyMainAna(chain);

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
  sea->IncludeAJson("Cert_190456-208686_8TeV_Collisions12_Abarker_Combined_JSON.txt"); //combined json
  //sea->IncludeAJson("anotherJSON.txt");

  TStopwatch ts;

  ts.Start();

  sea->Loop();

  ts.Stop();

  std::cout << "RealTime : " << ts.RealTime()/60.0 << " minutes" << std::endl;
  std::cout << "CPUTime  : " << ts.CpuTime()/60.0 << " minutes" << std::endl;

}
