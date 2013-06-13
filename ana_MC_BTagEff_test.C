//#include "params.h"
#include "TString.h"
#include "MCpoint2.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "TString.h"
#include "params_arg.h"
using namespace std;
using namespace params;

//std::vector<MCpoint2*> setupMCpoints();
//MCpoint2 * setupMCpoint(string pointname, string filepath="");



//std::vector<MCpoint2*> setupMCpoints(){
//vector<MCpoint2*> setupMCpoints(){
MCpoint2** setupMCpoints(int & Asize){
	cout<<"hello world"<<endl;
	std::vector<MCpoint2*> MCpoints;

	MCpoints.push_back(new MCpoint2(350,5025,225,       2500000,      517.0E-12,   0, "/uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/susyEvents_newNatural.root"));


	MCpoints.push_back(new MCpoint2(250,5025,200,       2500000,      3311.0E-12,  0,  "/eos/uscms/store/user/abarker/MC/st_250_ho_200/MC_AB_2500k_st_250_ho_200.root"));//mst_250_M3_5025_mu_200
	MCpoints.push_back(new MCpoint2(250,5025,150,       2500000,      2000.0E-12,  0,  "/eos/uscms/store/user/abarker/MC/st_250_ho_150/MC_AB_2500k_st_250_ho_150.root"));//mst_250_M3_5025_mu_150
	MCpoints.push_back(new MCpoint2(350,5025,200,       2500000,      864.0E-12,  0,  "/eos/uscms/store/user/abarker/MC/st_350_ho_200/MC_AB_2500k_mst_350_mu_200.root"));//mst_350_M3_5025_mu_200
	MCpoints.push_back(new MCpoint2(0,0,140,       2500000,      1833.0E-12, 1, "/eos/uscms/store/user/abarker/MC/ho_140/MC_AB_2500k_ho_140.root"));//ho_140
	MCpoints.push_back(new MCpoint2(0,0,200,       2500000,      463.0E-12,  1, "/eos/uscms/store/user/abarker/MC/ho_200/MC_AB_2500k_ho_200.root"));//ho_200

	string type2filedir = "dcache:/pnfs/cms/WAX/resilient/lpcpjm/PrivateMC/FastSim/533p3_full/naturalHiggsinoNLSP_try4/SusyNtuple/cms533v1_v1/";
	int ngen = 1000000;
	MCpoints.push_back(new MCpoint2(1010,5050,150,ngen,5.937E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1010,5050,175,ngen,3.265E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1010,5050,200,ngen,1.930E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1010,5050,225,ngen,1.202E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1010,5050,250,ngen,7.791E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1010,5050,275,ngen,5.212E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1010,5050,300,ngen,3.576E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1010,5050,325,ngen,2.512E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1010,5050,375,ngen,1.307E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1010,5050,425,ngen,7.182E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1010,5050,475,ngen,4.119E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1010,5050,525,ngen,2.449E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1010,5050,575,ngen,1.498E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1010,5050,625,ngen,9.405E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1010,5050,675,ngen,6.074E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1010,5050,725,ngen,4.021E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1010,5050,825,ngen,1.859E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1010,5050,925,ngen,8.410E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,1025,ngen,7.224E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,1125,ngen,3.279E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,1225,ngen,1.537E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,150,ngen,5.960E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,175,ngen,3.278E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,200,ngen,1.936E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,225,ngen,1.205E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,250,ngen,7.811E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,275,ngen,5.223E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,300,ngen,3.589E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,325,ngen,2.522E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,375,ngen,1.309E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,425,ngen,7.170E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,475,ngen,4.091E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,525,ngen,2.412E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,575,ngen,1.455E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,625,ngen,8.966E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,675,ngen,5.618E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,725,ngen,3.564E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,825,ngen,1.486E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint2(1510,5050,925,ngen,6.386E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint2(185,5050,150,ngen,1.123E-09,2,type2filedir));
	MCpoints.push_back(new MCpoint2(185,5050,175,ngen,8.638E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,1025,ngen,7.090E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,1125,ngen,3.136E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,1225,ngen,1.394E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,150,ngen,5.961E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,1525,ngen,1.217E-15,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,175,ngen,3.276E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,200,ngen,1.939E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,225,ngen,1.206E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,250,ngen,7.807E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,275,ngen,5.231E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,300,ngen,3.593E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,325,ngen,2.523E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,375,ngen,1.312E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,425,ngen,7.188E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,475,ngen,4.098E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,525,ngen,2.415E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,575,ngen,1.459E-12,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,625,ngen,8.974E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,675,ngen,5.629E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,725,ngen,3.569E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,825,ngen,1.485E-13,2,type2filedir));
	MCpoints.push_back(new MCpoint2(2010,5050,925,ngen,6.341E-14,2,type2filedir));
	MCpoints.push_back(new MCpoint2(210,5050,150,ngen,9.297E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(210,5050,175,ngen,6.704E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(210,5050,200,ngen,5.423E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(235,5050,150,ngen,8.072E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(235,5050,175,ngen,5.472E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(235,5050,200,ngen,4.183E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(235,5050,225,ngen,3.488E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(260,5050,150,ngen,7.298E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(260,5050,175,ngen,4.686E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(260,5050,200,ngen,3.383E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(260,5050,225,ngen,2.684E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(260,5050,250,ngen,2.276E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(285,5050,150,ngen,6.923E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(285,5050,175,ngen,4.186E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(285,5050,200,ngen,2.880E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(285,5050,225,ngen,2.168E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(285,5050,250,ngen,1.764E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(285,5050,275,ngen,1.519E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(310,5050,150,ngen,6.929E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(310,5050,175,ngen,3.862E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(310,5050,200,ngen,2.553E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(310,5050,225,ngen,1.843E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(310,5050,250,ngen,1.434E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(310,5050,275,ngen,1.186E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(310,5050,300,ngen,1.031E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(335,5050,150,ngen,6.676E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(335,5050,175,ngen,3.957E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(335,5050,200,ngen,2.340E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(335,5050,225,ngen,1.631E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(335,5050,250,ngen,1.219E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(335,5050,275,ngen,9.683E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(335,5050,300,ngen,8.115E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(335,5050,325,ngen,7.102E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(360,5050,150,ngen,6.481E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(360,5050,175,ngen,3.793E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(360,5050,200,ngen,2.410E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(360,5050,225,ngen,1.490E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(360,5050,250,ngen,1.075E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(360,5050,275,ngen,8.257E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(360,5050,300,ngen,6.654E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(360,5050,325,ngen,5.637E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(385,5050,150,ngen,6.310E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(385,5050,175,ngen,3.656E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(385,5050,200,ngen,2.307E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(385,5050,225,ngen,1.535E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(385,5050,250,ngen,9.811E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(385,5050,300,ngen,5.698E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(385,5050,325,ngen,4.662E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(385,5050,375,ngen,3.509E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(410,5050,150,ngen,6.205E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(410,5050,175,ngen,3.546E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(410,5050,200,ngen,2.213E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(410,5050,225,ngen,1.468E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(410,5050,250,ngen,1.011E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(410,5050,275,ngen,6.641E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(410,5050,325,ngen,4.010E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(410,5050,375,ngen,2.839E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(460,5050,150,ngen,6.061E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(460,5050,175,ngen,3.404E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(460,5050,200,ngen,2.077E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(460,5050,225,ngen,1.349E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(460,5050,250,ngen,9.256E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(460,5050,275,ngen,6.601E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(460,5050,300,ngen,4.757E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(460,5050,375,ngen,2.067E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(460,5050,425,ngen,1.497E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(510,5050,150,ngen,5.986E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(510,5050,175,ngen,3.334E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(510,5050,200,ngen,2.002E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(510,5050,225,ngen,1.279E-10,2,type2filedir));
	MCpoints.push_back(new MCpoint2(510,5050,250,ngen,8.598E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(510,5050,275,ngen,6.021E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(510,5050,300,ngen,4.371E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(510,5050,325,ngen,3.251E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(510,5050,375,ngen,1.693E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(510,5050,425,ngen,1.119E-11,2,type2filedir));
	MCpoints.push_back(new MCpoint2(510,5050,475,ngen,8.233E-12,2,type2filedir));

//	return MCpoints;
//ok, it doesnt' like returning a MCpoin vector, but it doesn't seem to mind a pointer. Lets try that. 
	Asize = MCpoints.size();
	MCpoint2* asdf[Asize];
	for(int i = 0;i<MCpoints.size();i++){
		asfd[i] = *MCpoints[i];
	}
	return asdf;
}//end setup



MCpoint2 * setupMCpoint(string pointname, string filepath){
	//returns a pointer to a fully setup MC point, ready to use. 
	//you should add a check that the file exists. 

	if(pointname.compare("Data") ==0 ){
		MCpoint2 *d = new MCpoint2(1,1,1,1,1,1);
		d->setType(-1);
		if(filepath.compare("")!=0) d->filepath = filepath;
		return d;
	}
	//std::vector<MCpoint2*> vp = setupMCpoints();
	int size;
	MCpoints** = setupMCpoints(size);
	//std::vector<MCpoint2*> vp = setupMCpoints();
	//std::map<string, int> pmap = makemap(vp);
	//string s_pointname = pointname;
	MCpoint2* thispoint;// = vp[pmap[s_pointname]];
	bool foundit = false;
	//std::vector<MCpoint2*>::iterator it = vp.begin();
	for(int i = 0; i< size; i++){
	//while (it != vp.end() ){
		if(MCpoints[i]->pointName.compare(pointname) == 0){ // they are the same
			foundit = true;
			thispoint = MCpoints[i];
		//	it++;
		}
		//else{
			//vp.erase(it);	//delete and go to the next one. 
		//}
	}//end while
	if(!foundit) cout<<"WARNING !! DID NOT FIND MC POINT!!"<<endl;
	if(filepath.compare("")!=0) thispoint->filepath = filepath; // its not ""
	return thispoint;

}//end setupMCpoint







void ana_MC_BTagEff_test(TString ds="relval", TString physics="ttbar") {
{
  gSystem->Load("libSusyEvent.so");

  // Look ../jec/JetMETObjects/README
  gSystem->Load("../jec/lib/libJetMETObjects.so");

  // Printing utility for ntuple variables
  gROOT->LoadMacro("SusyEventPrinter.cc+");

  // Main analysis code
  gROOT->LoadMacro("SusyAna_MC_BTagEff_test.cc+"); //this line causes everything to segfault at the end.

  // chain of inputs
  TChain* chain = new TChain("susyTree");

//////////////// MC files /////////////////
  //MCpoint* thisMCpoint = setupMCpoint(which_MC_to_use); 
//cout<<"try to add "<<thisMCpoint->filepath.c_str()<<endl;
  //chain->Add(thisMCpoint->filepath.c_str()); 
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
   chain->Add("../susyEvents_newNatural.root");
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


  SusyAna_MC_BTagEff_test* sea = new SusyAna_MC_BTagEff_test(chain);

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






