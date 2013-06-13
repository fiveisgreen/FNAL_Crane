// Original Author:  Dongwook Jang
// $Id: ana_firstskim_multisave.C,v 1.8 2011/11/01 22:14:51 dwjang Exp $
//
// Jet energy correction is possible at ntuple level.
// $ cd ../jec/JetMETObjects
// $ make
// This will create a shared library in jec/lib
// which is included below as libJetMETObjects.so
//
// Come back to this directory and do
// $ make
// $ root -b -q -l ana_firstskim_multisave.C
// will produce hist_"physics"_"ds".root

void ana_firstskim_multisave(TString ds="relval", TString physics="ttbar") {

  gSystem->Load("libSusyEvent.so");

  // Look ../jec/JetMETObjects/README
  gSystem->Load("../jec/lib/libJetMETObjects.so");

  // Printing utility for ntuple variables
  gROOT->LoadMacro("SusyEventPrinter.cc+");

  // Main ana_firstskim_multisavelysis code
  gROOT->LoadMacro("SusyAna_firstskim_multisave.cc+");

  // chain of inputs
  TChain* chain = new TChain("susyTree");
  //chain->Add("Susyskim2.root");

int which_data = 4; 
//which data = -1 something else
//which_data = 0: 2012A
//which_data = 1: 2012B part 1
//which_data = 2: 2012B part 2
//which_data = 3: 2012C part 1
//which_data = 4: 2012C part 2
if(which_data == -1){
chain->Add("looseSkims/SuperSkim_12ABC_0.root");
//chain->Add("looseSkims/SusyskimA.root");
//chain->Add("../../../MC_susysignal_1030evt.root");
//chain->Add("looseSkims/Susyskim_12ABC.root");
}
else if(which_data == 0){

} 


else if(which_data == 1){
chain->Add("looseSkims/SuperSkim_12B_0.root");
chain->Add("looseSkims/SuperSkim_12B_1.root");
chain->Add("looseSkims/SuperSkim_12B_2.root");
chain->Add("looseSkims/SuperSkim_12B_3.root");
chain->Add("looseSkims/SuperSkim_12B_4.root");
chain->Add("looseSkims/SuperSkim_12B_5.root");
chain->Add("looseSkims/SuperSkim_12B_6.root");
chain->Add("looseSkims/SuperSkim_12B_7.root");
chain->Add("looseSkims/SuperSkim_12B_8.root");
chain->Add("looseSkims/SuperSkim_12B_9.root");
chain->Add("looseSkims/SuperSkim_12B_10.root");
chain->Add("looseSkims/SuperSkim_12B_11.root");
chain->Add("looseSkims/SuperSkim_12B_12.root");
chain->Add("looseSkims/SuperSkim_12B_13.root");
chain->Add("looseSkims/SuperSkim_12B_14.root");
chain->Add("looseSkims/SuperSkim_12B_15.root");
chain->Add("looseSkims/SuperSkim_12B_16.root");
chain->Add("looseSkims/SuperSkim_12B_17.root");
chain->Add("looseSkims/SuperSkim_12B_18.root");
chain->Add("looseSkims/SuperSkim_12B_19.root");
chain->Add("looseSkims/SuperSkim_12B_20.root");
chain->Add("looseSkims/SuperSkim_12B_21.root");
chain->Add("looseSkims/SuperSkim_12B_22.root");
chain->Add("looseSkims/SuperSkim_12B_23.root");
chain->Add("looseSkims/SuperSkim_12B_24.root");
chain->Add("looseSkims/SuperSkim_12B_25.root");
chain->Add("looseSkims/SuperSkim_12B_26.root");
chain->Add("looseSkims/SuperSkim_12B_27.root");
chain->Add("looseSkims/SuperSkim_12B_28.root");
chain->Add("looseSkims/SuperSkim_12B_29.root");
chain->Add("looseSkims/SuperSkim_12B_30.root");
chain->Add("looseSkims/SuperSkim_12B_31.root");
chain->Add("looseSkims/SuperSkim_12B_32.root");
chain->Add("looseSkims/SuperSkim_12B_33.root");
chain->Add("looseSkims/SuperSkim_12B_34.root");
chain->Add("looseSkims/SuperSkim_12B_35.root");
chain->Add("looseSkims/SuperSkim_12B_36.root");
chain->Add("looseSkims/SuperSkim_12B_37.root");
chain->Add("looseSkims/SuperSkim_12B_38.root");
chain->Add("looseSkims/SuperSkim_12B_39.root");
chain->Add("looseSkims/SuperSkim_12B_40.root");
chain->Add("looseSkims/SuperSkim_12B_41.root");
chain->Add("looseSkims/SuperSkim_12B_42.root");
chain->Add("looseSkims/SuperSkim_12B_43.root");
chain->Add("looseSkims/SuperSkim_12B_44.root");
chain->Add("looseSkims/SuperSkim_12B_45.root");
chain->Add("looseSkims/SuperSkim_12B_46.root");
chain->Add("looseSkims/SuperSkim_12B_47.root");
chain->Add("looseSkims/SuperSkim_12B_48.root");
chain->Add("looseSkims/SuperSkim_12B_49.root");
chain->Add("looseSkims/SuperSkim_12B_50.root");
chain->Add("looseSkims/SuperSkim_12B_51.root");
chain->Add("looseSkims/SuperSkim_12B_52.root");
chain->Add("looseSkims/SuperSkim_12B_53.root");
chain->Add("looseSkims/SuperSkim_12B_54.root");
chain->Add("looseSkims/SuperSkim_12B_55.root");
chain->Add("looseSkims/SuperSkim_12B_56.root");
chain->Add("looseSkims/SuperSkim_12B_57.root");
chain->Add("looseSkims/SuperSkim_12B_58.root");
chain->Add("looseSkims/SuperSkim_12B_59.root");
chain->Add("looseSkims/SuperSkim_12B_60.root");
chain->Add("looseSkims/SuperSkim_12B_61.root");
chain->Add("looseSkims/SuperSkim_12B_62.root");
chain->Add("looseSkims/SuperSkim_12B_63.root");
chain->Add("looseSkims/SuperSkim_12B_64.root");
chain->Add("looseSkims/SuperSkim_12B_65.root");
chain->Add("looseSkims/SuperSkim_12B_66.root");
chain->Add("looseSkims/SuperSkim_12B_67.root");
chain->Add("looseSkims/SuperSkim_12B_68.root");
chain->Add("looseSkims/SuperSkim_12B_69.root");
chain->Add("looseSkims/SuperSkim_12B_70.root");
chain->Add("looseSkims/SuperSkim_12B_71.root");
chain->Add("looseSkims/SuperSkim_12B_72.root");
chain->Add("looseSkims/SuperSkim_12B_73.root");
chain->Add("looseSkims/SuperSkim_12B_74.root");
chain->Add("looseSkims/SuperSkim_12B_75.root");
chain->Add("looseSkims/SuperSkim_12B_76.root");
chain->Add("looseSkims/SuperSkim_12B_78.root");
chain->Add("looseSkims/SuperSkim_12B_79.root");
chain->Add("looseSkims/SuperSkim_12B_80.root");
chain->Add("looseSkims/SuperSkim_12B_81.root");
chain->Add("looseSkims/SuperSkim_12B_82.root");
chain->Add("looseSkims/SuperSkim_12B_83.root");
chain->Add("looseSkims/SuperSkim_12B_84.root");
chain->Add("looseSkims/SuperSkim_12B_85.root");
chain->Add("looseSkims/SuperSkim_12B_86.root");
chain->Add("looseSkims/SuperSkim_12B_87.root");
chain->Add("looseSkims/SuperSkim_12B_88.root");
chain->Add("looseSkims/SuperSkim_12B_89.root");
chain->Add("looseSkims/SuperSkim_12B_90.root");
chain->Add("looseSkims/SuperSkim_12B_91.root");
chain->Add("looseSkims/SuperSkim_12B_92.root");
chain->Add("looseSkims/SuperSkim_12B_93.root");
chain->Add("looseSkims/SuperSkim_12B_94.root");
chain->Add("looseSkims/SuperSkim_12B_95.root");
chain->Add("looseSkims/SuperSkim_12B_96.root");
chain->Add("looseSkims/SuperSkim_12B_97.root");
chain->Add("looseSkims/SuperSkim_12B_98.root");
chain->Add("looseSkims/SuperSkim_12B_99.root");
chain->Add("looseSkims/SuperSkim_12B_100.root");
chain->Add("looseSkims/SuperSkim_12B_101.root");
chain->Add("looseSkims/SuperSkim_12B_102.root");
chain->Add("looseSkims/SuperSkim_12B_103.root");
chain->Add("looseSkims/SuperSkim_12B_104.root");
chain->Add("looseSkims/SuperSkim_12B_105.root");
chain->Add("looseSkims/SuperSkim_12B_106.root");
chain->Add("looseSkims/SuperSkim_12B_107.root");
chain->Add("looseSkims/SuperSkim_12B_108.root");
chain->Add("looseSkims/SuperSkim_12B_109.root");
chain->Add("looseSkims/SuperSkim_12B_110.root");
chain->Add("looseSkims/SuperSkim_12B_111.root");
chain->Add("looseSkims/SuperSkim_12B_112.root");
chain->Add("looseSkims/SuperSkim_12B_113.root");
chain->Add("looseSkims/SuperSkim_12B_114.root");
chain->Add("looseSkims/SuperSkim_12B_115.root");
chain->Add("looseSkims/SuperSkim_12B_116.root");
chain->Add("looseSkims/SuperSkim_12B_117.root");
chain->Add("looseSkims/SuperSkim_12B_118.root");
chain->Add("looseSkims/SuperSkim_12B_119.root");
chain->Add("looseSkims/SuperSkim_12B_120.root");
chain->Add("looseSkims/SuperSkim_12B_121.root");
chain->Add("looseSkims/SuperSkim_12B_122.root");
chain->Add("looseSkims/SuperSkim_12B_123.root");
chain->Add("looseSkims/SuperSkim_12B_124.root");
chain->Add("looseSkims/SuperSkim_12B_125.root");
chain->Add("looseSkims/SuperSkim_12B_126.root");
chain->Add("looseSkims/SuperSkim_12B_127.root");
chain->Add("looseSkims/SuperSkim_12B_128.root");
chain->Add("looseSkims/SuperSkim_12B_129.root");
chain->Add("looseSkims/SuperSkim_12B_130.root");
chain->Add("looseSkims/SuperSkim_12B_131.root");
chain->Add("looseSkims/SuperSkim_12B_132.root");
chain->Add("looseSkims/SuperSkim_12B_133.root");
chain->Add("looseSkims/SuperSkim_12B_134.root");
chain->Add("looseSkims/SuperSkim_12B_135.root");
chain->Add("looseSkims/SuperSkim_12B_136.root");
chain->Add("looseSkims/SuperSkim_12B_137.root");
chain->Add("looseSkims/SuperSkim_12B_138.root");
chain->Add("looseSkims/SuperSkim_12B_139.root");
chain->Add("looseSkims/SuperSkim_12B_140.root");
chain->Add("looseSkims/SuperSkim_12B_141.root");
chain->Add("looseSkims/SuperSkim_12B_142.root");
chain->Add("looseSkims/SuperSkim_12B2_0.root");
chain->Add("looseSkims/SuperSkim_12B2_1.root");
chain->Add("looseSkims/SuperSkim_12B2_2.root");
chain->Add("looseSkims/SuperSkim_12B2_3.root");
chain->Add("looseSkims/SuperSkim_12B2_4.root");
chain->Add("looseSkims/SuperSkim_12B2_5.root");
chain->Add("looseSkims/SuperSkim_12B2_6.root");
chain->Add("looseSkims/SuperSkim_12B2_7.root");
chain->Add("looseSkims/SuperSkim_12B2_8.root");
chain->Add("looseSkims/SuperSkim_12B2_9.root");
}

else if(which_data == 0){

}

else if(which_data == 0){

}

else if(which_data == 0){
chain->Add("looseSkims/SuperSkim_12C1_0.root");
chain->Add("looseSkims/SuperSkim_12C1_1.root");
chain->Add("looseSkims/SuperSkim_12C1_2.root");
chain->Add("looseSkims/SuperSkim_12C1_3.root");
chain->Add("looseSkims/SuperSkim_12C1_4.root");
chain->Add("looseSkims/SuperSkim_12C1_5.root");
chain->Add("looseSkims/SuperSkim_12C1_6.root");
chain->Add("looseSkims/SuperSkim_12C1_7.root");
chain->Add("looseSkims/SuperSkim_12C1_8.root");
chain->Add("looseSkims/SuperSkim_12C1_9.root");
chain->Add("looseSkims/SuperSkim_12C1_10.root");
chain->Add("looseSkims/SuperSkim_12C1_11.root");
chain->Add("looseSkims/SuperSkim_12C1_12.root");
chain->Add("looseSkims/SuperSkim_12C1_13.root");
chain->Add("looseSkims/SuperSkim_12C2_0.root");
chain->Add("looseSkims/SuperSkim_12C2_1.root");
chain->Add("looseSkims/SuperSkim_12C2_2.root");
chain->Add("looseSkims/SuperSkim_12C2_3.root");
chain->Add("looseSkims/SuperSkim_12C2_4.root");
chain->Add("looseSkims/SuperSkim_12C2_5.root");
chain->Add("looseSkims/SuperSkim_12C2_6.root");
chain->Add("looseSkims/SuperSkim_12C2_7.root");
chain->Add("looseSkims/SuperSkim_12C2_8.root");
chain->Add("looseSkims/SuperSkim_12C2_9.root");
chain->Add("looseSkims/SuperSkim_12C2_10.root");
chain->Add("looseSkims/SuperSkim_12C2_11.root");
chain->Add("looseSkims/SuperSkim_12C2_12.root");
chain->Add("looseSkims/SuperSkim_12C2_13.root");
chain->Add("looseSkims/SuperSkim_12C2_14.root");

}

  SusyAna_firstskim_multisave* sea = new SusyAna_firstskim_multisave(chain);

  // configuration parameters
  // any values given here will replace the default values
  sea->SetDataset(physics+"_"+ds);        // dataset name
  sea->SetPrintInterval(1e4);             // print frequency
  sea->SetPrintLevel(0);                  // print level for event contents
  sea->SetUseTrigger(true);
//  sea->AddHltName("HLT_Photon36_CaloIdL_Photon22_CaloIdL");  // add HLT trigger path name
//  sea->AddHltName("HLT_Photon32_CaloIdL_Photon26_CaloIdL");  // add HLT trigger path name
/*
  sea->AddHltName("HLT_Photon26_R9Id85_Photon18_R9Id85_Mass60_v4");
  sea->AddHltName("HLT_Photon26_R9Id85_Photon18_CaloId10_Iso50_Mass60_v6");
  sea->AddHltName("HLT_Photon26_CaloId10_Iso50_Photon18_R9Id85_Mass60_v6");
  sea->AddHltName("HLT_Photon26_CaloId10_Iso50_Photon18_CaloId10_Iso50_Mass60_v6");
  sea->AddHltName("HLT_Photon26_R9Id85_OR_CaloId10_Iso50_Photon18_R9Id85_OR_CaloId10_Iso50_Mass60_v6");
  sea->AddHltName("HLT_Photon26_R9Id85_OR_CaloId10_Iso50_Photon18_R9Id85_OR_CaloId10_Iso50_Mass70_v2");

  sea->AddHltName("HLT_Photon36_R9Id85_Photon22_R9Id85_v4");
  sea->AddHltName("HLT_Photon36_R9Id85_Photon22_CaloId10_Iso50_v6");
  sea->AddHltName("HLT_Photon36_CaloId10_Iso50_Photon22_R9Id85_v6");
  sea->AddHltName("HLT_Photon36_CaloId10_Iso50_Photon22_CaloId10_Iso50_v6");
  sea->AddHltName("HLT_Photon36_R9Id85_OR_CaloId10_Iso50_Photon22_R9Id85_OR_CaloId10_Iso50_v6");

  sea->AddHltName("HLT_DoublePhoton48_HEVT_v8");	//cut at 0.05
  sea->AddHltName("HLT_DoublePhoton53_HEVT_v2");
*/
  sea->SetFilter(true);                  // filter events passing final cuts
  sea->SetProcessNEvents(-1);             // number of events to be processed

  // as an example -- add your favorite Json here.  More than one can be "Include"ed
  //  sea->IncludeAJson("Cert_161079-161352_7TeV_PromptReco_Collisions11_JSON_noESpbl_v2.txt");
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
