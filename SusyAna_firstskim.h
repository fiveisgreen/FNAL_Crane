// -*- C++ -*-
//
// Package:    SusyNtuplizer
// Class:      SusyAna_firstskim.h
// 
/*

 Description: an analyzer for susy::Event

 Implementation:

*/
//
// Original Author:  Dongwook Jang
// $Id: SusyAna_firstskim.h,v 1.4 2011/06/08 16:28:40 dmason Exp $
//

#ifndef SusyAna_firstskim_h
#define SusyAna_firstskim_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>

#include <iostream>
#include <fstream>
#include <map>

#include "../src/SusyEvent.h"


class SusyAna_firstskim {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Declaration of leaf types
  susy::Event     *event;

  // List of branches
  TBranch        *b_Event;

  SusyAna_firstskim(TTree *tree=0);
  virtual ~SusyAna_firstskim();
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();                          // event loop for main analysis

  // utility functions
  bool isSameObject(TLorentzVector& p1, TLorentzVector& p2);
  float d0correction(TVector3& beamSpot, susy::Track& track) const;
  void IncludeAJson(std::string jsonfile);  // Call to pull in a json file 
  bool isInJson(Int_t run,Int_t lumi);      // JSON based good run list cut...
  bool PassTrigger(TString v); // return true if path v is fired
  bool PassTriggers(); // return true if any of names in hltNames are fired

  // parameter configuration functions
  void Initialize();         // global variables needed to be initialized just once
  void InitializePerEvent(); // global variables needed to be initialized per event
  void SetDataset(TString& v) {          ds = v; }
  void SetPrintInterval(int v) {         printInterval = v; }
  void SetPrintLevel(int v) {            printLevel = v; }
  void SetProcessNEvents(int v) {        processNEvents = v; }
  void SetUseTrigger(bool v) {           useTrigger = v; }
  void AddHltName(TString v) {           hltNames.push_back(v); }
  void SetFilter(bool v) {               enableFilter = v; }
  void SetFilteredFileName(TString v) {  filtered_file_name = v; }
  TString label;

 private:

  TString ds;               // dataset name to be used for output histfile name

  // printLevel
  // 0 : default - no printout
  // 1 : print functional step in every event
  // 2 : print values in collections
  int printLevel;           // print frequency

  int printInterval;        // print level for event content: defined in Event.h
  int processNEvents;       // number of events to be processed
  bool useTrigger;          // flag for using trigger bit selection.
  std::vector<TString> hltNames;          // HLT trigger path names
  bool enableFilter;        // filter events of interest
  TString filtered_file_name; // filtered output file name

  typedef std::map<int,std::map<int,bool> > RunLumiFlagHolder;  //define map that holds json list
  RunLumiFlagHolder goodrunlumilist;  // instantiate it

};

#endif

#ifdef SusyAna_firstskim_cxx
SusyAna_firstskim::SusyAna_firstskim(TTree *tree)
{
  if (tree == 0) {
    std::cout << "Error!!! There is no file containing a tree." << std::endl;
  }
  Init(tree);
  Initialize();
}

SusyAna_firstskim::~SusyAna_firstskim()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t SusyAna_firstskim::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t SusyAna_firstskim::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fChain;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
  }
  return centry;
}

void SusyAna_firstskim::Init(TTree *tree)
{
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  //   fChain->SetMakeClass(1);

  event = new susy::Event;

  fChain->SetBranchAddress("susyEvent", &event, &b_Event);
}

void SusyAna_firstskim::Initialize() {

  ds = "test";
  printLevel = 0;
  printInterval = 10000;
  processNEvents = -1;
  useTrigger = false;
  enableFilter = true;
  filtered_file_name = "filtered.root";

}

void SusyAna_firstskim::IncludeAJson(std::string jsonfile) {


// Fairly primitive brute force json parser -- opens the json file named in the argument
// and adds that to the goodrunlumilist map.  Overlapping jsons are merged inclusively.

 char thing;

 ifstream jsonInput;

 std::cout << "Sucking in Json file: " << jsonfile << " which includes: " << std::endl;

 jsonInput.open(jsonfile.c_str());
 
 if (!jsonInput.good()) {
   std::cout << "Problem reading Json file...  Didn't suck anything in... " << std::endl;
   return;
 }
 
 jsonInput.get(thing);
 
 while (jsonInput.good()) {
   if (thing=='{') {  // start of list
     while (thing != '}') {
       int runnum;
       if (thing == '"') {
         std::string srunnum;
         jsonInput.get(thing); // get stuff inside ""

         while (thing != '"') {
           srunnum+=thing; // get stuff inside ""
           jsonInput.get(thing);

	   }
         sscanf(srunnum.c_str(),"%i",&runnum);
         std::cout << " runnum: " << runnum << std::endl;
         bool newrun=true;
         
       } // inside ""
       if (thing == '[') {
          jsonInput.get(thing); // get stuff inside []
	 while (thing != ']') {
           if (thing == '[') {
             jsonInput.get(thing); // get stuff inside series []

             std::string lumiseries;
             int firstlumi,lastlumi;
             while (thing !=']') {
               lumiseries+=thing;
                jsonInput.get(thing); // get stuff inside series []
             }
             sscanf(lumiseries.c_str(),"%i,%i",&firstlumi,&lastlumi);
             std::cout << "  lumis  " << firstlumi << " to " << lastlumi << std::endl;

	     // At this point have runnum, first lumi, last lumi -- so can fill map here...
	     for (int l=firstlumi;l<=lastlumi;l++) {
               goodrunlumilist[runnum][l]=true;
	     }

           } // inside actual series []
             jsonInput.get(thing); // get stuff inside []
         }
       } // inside []
         jsonInput.get(thing); // get another char looking for "

     } 
   } // inside {}
    jsonInput.get(thing); // get another char looking for {

 } // EOF 

 jsonInput.close();

}


bool SusyAna_firstskim::isInJson(Int_t run,Int_t lumi) {

//#ifdef MC
//  return 1;
//#endif

if (goodrunlumilist[run][lumi]) return true;

return false;

}



#endif // #ifdef SusyAna_firstskim_cxx
