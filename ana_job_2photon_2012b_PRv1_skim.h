//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jul 30 21:14:40 2012 by ROOT version 5.22/00d
// from TTree EventTree/Event data
// found on file: rfio:///castor/cern.ch/user/c/cmkuo/ggNtuple52/V05-02-05-00_pre9/job_2photon_2012b_PRv1_skim.root
//////////////////////////////////////////////////////////

#ifndef ana_job_2photon_2012b_PRv1_skim_h
#define ana_job_2photon_2012b_PRv1_skim_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
   const Int_t kMaxeleESEffSigmaRR = 1;
   const Int_t kMaxphoESEffSigmaRR = 1;
   const Int_t kMaxnPFPho = 8;
   const Int_t kMaxPFPhoE = 1;
   const Int_t kMaxPFPhoEt = 1;
   const Int_t kMaxPFPhoEta = 1;
   const Int_t kMaxPFPhoPhi = 1;
   const Int_t kMaxPFPhoHoverE = 1;
   const Int_t kMaxPFPhoSCPos = 1;
   const Int_t kMaxPFPhoSCEta = 1;
   const Int_t kMaxPFPhoSCPhi = 1;
   const Int_t kMaxnPFEle = 6;
   const Int_t kMaxPFElePt = 1;
   const Int_t kMaxPFEleEta = 1;
   const Int_t kMaxPFElePhi = 1;
   const Int_t kMaxPFEleEn = 1;
   const Int_t kMaxPFEleCharge = 1;

class ana_job_2photon_2012b_PRv1_skim {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           run;
   Long64_t        event;
   Int_t           lumis;
   Bool_t          isData;
   Int_t           nHLT;
   Int_t           HLT[441];   //[nHLT]
   Int_t           HLTIndex[70];
   Float_t         bspotPos[3];
   Int_t           nVtx;
   Float_t         vtx[49][3];   //[nVtx]
   Int_t           IsVtxGood;
   Int_t           nVtxBS;
   Float_t         vtxbs[49][3];   //[nVtxBS]
   Float_t         vtxbsPtMod[49];   //[nVtxBS]
   Float_t         vtxbsSumPt2[49];   //[nVtxBS]
//   vector<int> *vtxbsTkIndex;
//   vector<float> *vtxbsTkWeight;
   Int_t           nTrk;
   Float_t         trkP[8495][3];   //[nTrk]
   Float_t         trkVtx[8495][3];   //[nTrk]
   Float_t         trkd0[8495];   //[nTrk]
   Float_t         trkd0Err[8495];   //[nTrk]
   Float_t         trkdz[8495];   //[nTrk]
   Float_t         trkdzErr[8495];   //[nTrk]
   Float_t         trkPtErr[8495];   //[nTrk]
   Int_t           trkQuality[8495];   //[nTrk]
   Int_t           nGoodTrk;
   Int_t           IsTracksGood;
   Float_t         MET;
   Float_t         METPhi;
   Float_t         METsumEt;
   Float_t         tcMET;
   Float_t         tcMETPhi;
   Float_t         tcMETsumEt;
   Float_t         tcMETmEtSig;
   Float_t         tcMETSig;
   Float_t         pfMET;
   Float_t         pfMETPhi;
   Float_t         pfMETsumEt;
   Float_t         pfMETmEtSig;
   Float_t         pfMETSig;
   Float_t         recoPfMET;
   Float_t         recoPfMETPhi;
   Float_t         recoPfMETsumEt;
   Float_t         recoPfMETmEtSig;
   Float_t         recoPfMETSig;
   Int_t           nEle;
   Int_t           eleTrg[10][13];   //[nEle]
   Int_t           eleClass[10];   //[nEle]
   Int_t           eleIsEcalDriven[10];   //[nEle]
   Int_t           eleCharge[10];   //[nEle]
   Float_t         eleEn[10];   //[nEle]
   Float_t         eleEcalEn[10];   //[nEle]
   Float_t         eleSCRawEn[10];   //[nEle]
   Float_t         eleSCEn[10];   //[nEle]
   Float_t         eleESEn[10];   //[nEle]
   Float_t         elePt[10];   //[nEle]
   Float_t         eleEta[10];   //[nEle]
   Float_t         elePhi[10];   //[nEle]
   Float_t         eleEtaVtx[10][70];   //[nEle]
   Float_t         elePhiVtx[10][70];   //[nEle]
   Float_t         eleEtVtx[10][70];   //[nEle]
   Float_t         eleSCEta[10];   //[nEle]
   Float_t         eleSCPhi[10];   //[nEle]
   Float_t         eleSCEtaWidth[10];   //[nEle]
   Float_t         eleSCPhiWidth[10];   //[nEle]
   Float_t         eleVtx[10][3];   //[nEle]
   Float_t         eleD0[10];   //[nEle]
   Float_t         eleDz[10];   //[nEle]
   Float_t         eleD0Vtx[10][70];   //[nEle]
   Float_t         eleDzVtx[10][70];   //[nEle]
   Float_t         eleHoverE[10];   //[nEle]
   Float_t         eleHoverE12[10];   //[nEle]
   Float_t         eleEoverP[10];   //[nEle]
   Float_t         elePin[10];   //[nEle]
   Float_t         elePout[10];   //[nEle]
   Float_t         eleBrem[10];   //[nEle]
   Float_t         eledEtaAtVtx[10];   //[nEle]
   Float_t         eledPhiAtVtx[10];   //[nEle]
   Float_t         eleSigmaIEtaIEta[10];   //[nEle]
   Float_t         eleSigmaIEtaIPhi[10];   //[nEle]
   Float_t         eleSigmaIPhiIPhi[10];   //[nEle]
   Float_t         eleEmax[10];   //[nEle]
   Float_t         eleE1x5[10];   //[nEle]
   Float_t         eleE3x3[10];   //[nEle]
   Float_t         eleE5x5[10];   //[nEle]
   Float_t         eleE2x5Right[10];   //[nEle]
   Float_t         eleE2x5Left[10];   //[nEle]
   Float_t         eleE2x5Top[10];   //[nEle]
   Float_t         eleE2x5Bottom[10];   //[nEle]
   Float_t         eleRegrE[10];   //[nEle]
   Float_t         eleRegrEerr[10];   //[nEle]
   Float_t         eleSeedTime[10];   //[nEle]
   Int_t           eleRecoFlag[10];   //[nEle]
   Float_t         eleIsoTrkDR03[10];   //[nEle]
   Float_t         eleIsoEcalDR03[10];   //[nEle]
   Float_t         eleIsoHcalDR03[10];   //[nEle]
   Float_t         eleIsoHcalDR0312[10];   //[nEle]
   Float_t         eleIsoHcalSolidDR03[10];   //[nEle]
   Float_t         eleIsoTrkDR04[10];   //[nEle]
   Float_t         eleIsoEcalDR04[10];   //[nEle]
   Float_t         eleIsoHcalDR04[10];   //[nEle]
   Float_t         eleIsoHcalDR0412[10];   //[nEle]
   Float_t         eleIsoHcalSolidDR04[10];   //[nEle]
   Int_t           eleMissHits[10];   //[nEle]
   Float_t         eleConvDist[10];   //[nEle]
   Float_t         eleConvDcot[10];   //[nEle]
   Int_t           eleConvVtxFit[10];   //[nEle]
   Float_t         eleIDMVANonTrig[10];   //[nEle]
   Float_t         eleIDMVATrig[10];   //[nEle]
   Float_t         elePFChIso[10];   //[nEle]
   Float_t         elePFPhoIso[10];   //[nEle]
   Float_t         elePFNeuIso[10];   //[nEle]
   Float_t         eleESEffSigmaRR[10][3];   //[nEle]
   Int_t           nPho;
   Int_t           phoTrg[13][8];   //[nPho]
   Int_t           phoTrgFilter[13][50];   //[nPho]
   Bool_t          phoIsPhoton[13];   //[nPho]
   Float_t         phoSCPos[13][3];   //[nPho]
   Float_t         phoCaloPos[13][3];   //[nPho]
   Float_t         phoE[13];   //[nPho]
   Float_t         phoEt[13];   //[nPho]
   Float_t         phoEta[13];   //[nPho]
   Float_t         phoVtx[13][3];   //[nPho]
   Float_t         phoPhi[13];   //[nPho]
   Float_t         phoEtVtx[13][70];   //[nPho]
   Float_t         phoEtaVtx[13][70];   //[nPho]
   Float_t         phoPhiVtx[13][70];   //[nPho]
   Float_t         phoR9[13];   //[nPho]
   Float_t         phoTrkIsoSolidDR03[13];   //[nPho]
   Float_t         phoTrkIsoHollowDR03[13];   //[nPho]
   Float_t         phoEcalIsoDR03[13];   //[nPho]
   Float_t         phoHcalIsoDR03[13];   //[nPho]
   Float_t         phoHcalIsoDR0312[13];   //[nPho]
   Float_t         phoHcalIsoSolidDR03[13];   //[nPho]
   Float_t         phoTrkIsoSolidDR04[13];   //[nPho]
   Float_t         phoTrkIsoHollowDR04[13];   //[nPho]
   Float_t         phoCiCTrkIsoDR03[13][70];   //[nPho]
   Float_t         phoCiCTrkIsoDR04[13][70];   //[nPho]
   Float_t         phoCiCdRtoTrk[13];   //[nPho]
   Float_t         phoEcalIsoDR04[13];   //[nPho]
   Float_t         phoHcalIsoDR04[13];   //[nPho]
   Float_t         phoHcalIsoDR0412[13];   //[nPho]
   Float_t         phoHcalIsoSolidDR04[13];   //[nPho]
   Float_t         phoHoverE[13];   //[nPho]
   Float_t         phoHoverE12[13];   //[nPho]
   Int_t           phoEleVeto[13];   //[nPho]
   Float_t         phoSigmaIEtaIEta[13];   //[nPho]
   Float_t         phoSigmaIEtaIPhi[13];   //[nPho]
   Float_t         phoSigmaIPhiIPhi[13];   //[nPho]
   Float_t         phoCiCPF4phopfIso03[13];   //[nPho]
   Float_t         phoCiCPF4phopfIso04[13];   //[nPho]
   Float_t         phoCiCPF4chgpfIso02[13][70];   //[nPho]
   Float_t         phoCiCPF4chgpfIso03[13][70];   //[nPho]
   Float_t         phoCiCPF4chgpfIso04[13][70];   //[nPho]
   Float_t         phoEmax[13];   //[nPho]
   Float_t         phoEtop[13];   //[nPho]
   Float_t         phoEbottom[13];   //[nPho]
   Float_t         phoEleft[13];   //[nPho]
   Float_t         phoEright[13];   //[nPho]
   Float_t         phoE3x3[13];   //[nPho]
   Float_t         phoE3x1[13];   //[nPho]
   Float_t         phoE1x3[13];   //[nPho]
   Float_t         phoE5x5[13];   //[nPho]
   Float_t         phoE1x5[13];   //[nPho]
   Float_t         phoE2x2[13];   //[nPho]
   Float_t         phoE2x5Max[13];   //[nPho]
   Float_t         phoE2x5Right[13];   //[nPho]
   Float_t         phoE2x5Left[13];   //[nPho]
   Float_t         phoE2x5Top[13];   //[nPho]
   Float_t         phoE2x5Bottom[13];   //[nPho]
   Float_t         phoPFChIso[13];   //[nPho]
   Float_t         phoPFPhoIso[13];   //[nPho]
   Float_t         phoPFNeuIso[13];   //[nPho]
   Float_t         phoPFIsoNeutral[13][8];   //[nPho]
   Float_t         phoPFIsoPhoton[13][8];   //[nPho]
   Float_t         phoPFIsoCharged[49][20][8];   //[nVtx]
   Float_t         phoRegrE[13];   //[nPho]
   Float_t         phoRegrEerr[13];   //[nPho]
   Float_t         phoSeedTime[13];   //[nPho]
   Int_t           phoSeedDetId1[13];   //[nPho]
   Int_t           phoSeedDetId2[13];   //[nPho]
   Int_t           phoRecoFlag[13];   //[nPho]
   Int_t           phoPos[13];   //[nPho]
   Float_t         phoSCE[13];   //[nPho]
   Float_t         phoSCRawE[13];   //[nPho]
   Float_t         phoESEn[13];   //[nPho]
   Float_t         phoSCEt[13];   //[nPho]
   Float_t         phoSCEta[13];   //[nPho]
   Float_t         phoSCPhi[13];   //[nPho]
   Float_t         phoSCEtaWidth[13];   //[nPho]
   Float_t         phoSCPhiWidth[13];   //[nPho]
   Float_t         phoSCBrem[13];   //[nPho]
   Int_t           phoOverlap[13];   //[nPho]
   Int_t           phohasPixelSeed[13];   //[nPho]
   Int_t           PFRecoMatch[13];   //[nPho]
   Int_t           PFEleMatch[13];   //[nPho]
   Int_t           PFEleVeto[13];   //[nPho]
   Int_t           pho_hasConvPf[13];   //[nPho]
   Int_t           pho_hasSLConvPf[13];   //[nPho]
   Float_t         MustacheEin[13];   //[nPho]
   Float_t         MustacheEOut[13];   //[nPho]
   Float_t         MustacheEtOut[13];   //[nPho]
   Float_t         PFLowestClustE[13];   //[nPho]
   Float_t         PFClustdEta[13];   //[nPho]
   Float_t         PFClustdPhi[13];   //[nPho]
   Float_t         PFClustRMSPhi[13];   //[nPho]
   Float_t         PFClustRMSPhiMust[13];   //[nPho]
   Float_t         PFPreShowerE1[13];   //[nPho]
   Float_t         PFPreShowerE2[13];   //[nPho]
   Float_t         pho_pfconvVtxZ[13];   //[nPho]
   Float_t         pho_pfconvVtxZErr[13];   //[nPho]
   Int_t           pho_nSLConv[13];   //[nPho]
   Float_t         pho_pfSLConvPos[13][3];   //[nPho]
   Float_t         pho_pfSLConvVtxZ[13][20];   //[nPho]
   Int_t           phoIsConv[13];   //[nPho]
   Int_t           phoNConv[13];   //[nPho]
   Float_t         phoConvInvMass[13];   //[nPho]
   Float_t         phoConvCotTheta[13];   //[nPho]
   Float_t         phoConvEoverP[13];   //[nPho]
   Float_t         phoConvZofPVfromTrks[13];   //[nPho]
   Float_t         phoConvMinDist[13];   //[nPho]
   Float_t         phoConvdPhiAtVtx[13];   //[nPho]
   Float_t         phoConvdPhiAtCalo[13];   //[nPho]
   Float_t         phoConvdEtaAtCalo[13];   //[nPho]
   Float_t         phoConvTrkd0[13][2];   //[nPho]
   Float_t         phoConvTrkPin[13][2];   //[nPho]
   Float_t         phoConvTrkPout[13][2];   //[nPho]
   Float_t         phoConvTrkdz[13][2];   //[nPho]
   Float_t         phoConvTrkdzErr[13][2];   //[nPho]
   Float_t         phoConvChi2[13];   //[nPho]
   Float_t         phoConvChi2Prob[13];   //[nPho]
   Int_t           phoConvNTrks[13];   //[nPho]
   Float_t         phoConvCharge[13][2];   //[nPho]
   Float_t         phoConvValidVtx[13];   //[nPho]
   Float_t         phoConvLikeLihood[13];   //[nPho]
   Float_t         phoConvP4[13][4];   //[nPho]
   Float_t         phoConvVtx[13][3];   //[nPho]
   Float_t         phoConvVtxErr[13][3];   //[nPho]
   Float_t         phoConvPairMomentum[13][3];   //[nPho]
   Float_t         phoConvRefittedMomentum[13][3];   //[nPho]
   Float_t         phoESEffSigmaRR[13][3];   //[nPho]
   Int_t           nMu;
   Int_t           muTrg[23][6];   //[nMu]
   Float_t         muEta[23];   //[nMu]
   Float_t         muPhi[23];   //[nMu]
   Int_t           muCharge[23];   //[nMu]
   Float_t         muPt[23];   //[nMu]
   Float_t         muPz[23];   //[nMu]
   Float_t         muIsoTrk[23];   //[nMu]
   Float_t         muIsoCalo[23];   //[nMu]
   Float_t         muIsoEcal[23];   //[nMu]
   Float_t         muIsoHcal[23];   //[nMu]
   Float_t         muChi2NDF[23];   //[nMu]
   Float_t         muInnerChi2NDF[23];   //[nMu]
   Float_t         muPFIsoR04_CH[23];   //[nMu]
   Float_t         muPFIsoR04_NH[23];   //[nMu]
   Float_t         muPFIsoR04_Pho[23];   //[nMu]
   Float_t         muPFIsoR04_PU[23];   //[nMu]
   Float_t         muPFIsoR04_CPart[23];   //[nMu]
   Float_t         muPFIsoR04_NHHT[23];   //[nMu]
   Float_t         muPFIsoR04_PhoHT[23];   //[nMu]
   Float_t         muPFIsoR03_CH[23];   //[nMu]
   Float_t         muPFIsoR03_NH[23];   //[nMu]
   Float_t         muPFIsoR03_Pho[23];   //[nMu]
   Float_t         muPFIsoR03_PU[23];   //[nMu]
   Float_t         muPFIsoR03_CPart[23];   //[nMu]
   Float_t         muPFIsoR03_NHHT[23];   //[nMu]
   Float_t         muPFIsoR03_PhoHT[23];   //[nMu]
   Int_t           muType[23];   //[nMu]
   Bool_t          muID[23][6];   //[nMu]
   Float_t         muD0[23];   //[nMu]
   Float_t         muDz[23];   //[nMu]
   Float_t         muD0Vtx[23][70];   //[nMu]
   Float_t         muDzVtx[23][70];   //[nMu]
   Float_t         muInnerD0[23];   //[nMu]
   Float_t         muInnerDz[23];   //[nMu]
   Int_t           muNumberOfValidTrkLayers[23];   //[nMu]
   Int_t           muNumberOfValidTrkHits[23];   //[nMu]
   Int_t           muNumberOfValidPixelLayers[23];   //[nMu]
   Int_t           muNumberOfValidPixelHits[23];   //[nMu]
   Int_t           muNumberOfValidMuonHits[23];   //[nMu]
   Int_t           muStations[23];   //[nMu]
   Int_t           muChambers[23];   //[nMu]
   Int_t           nPFPho_;
   Float_t         PFPhoE_[kMaxnPFPho];   //[nPFPho_]
   Float_t         PFPhoEt_[kMaxnPFPho];   //[nPFPho_]
   Float_t         PFPhoEta_[kMaxnPFPho];   //[nPFPho_]
   Float_t         PFPhoPhi_[kMaxnPFPho];   //[nPFPho_]
   Float_t         PFPhoHoverE_[kMaxnPFPho];   //[nPFPho_]
   Float_t         PFPhoSCPos_[kMaxnPFPho][3];   //[nPFPho_]
   Float_t         PFPhoSCEta_[kMaxnPFPho];   //[nPFPho_]
   Float_t         PFPhoSCPhi_[kMaxnPFPho];   //[nPFPho_]
   Int_t           nPFEle_;
   Float_t         PFElePt_[kMaxnPFEle];   //[nPFEle_]
   Float_t         PFEleEta_[kMaxnPFEle];   //[nPFEle_]
   Float_t         PFElePhi_[kMaxnPFEle];   //[nPFEle_]
   Float_t         PFEleEn_[kMaxnPFEle];   //[nPFEle_]
   Int_t           PFEleCharge[kMaxnPFEle];   //[nPFEle_]
   Float_t         rho25;
   Float_t         rho25_neu;
   Float_t         rho25_muPFiso;
   Float_t         rho25_elePFiso;
   Float_t         rho2011;
   Float_t         rho2012;
   Int_t           nJet;
   Int_t           jetTrg[85][14];   //[nJet]
   Float_t         jetEn[85];   //[nJet]
   Float_t         jetPt[85];   //[nJet]
   Float_t         jetEta[85];   //[nJet]
   Float_t         jetPhi[85];   //[nJet]
   Float_t         jetCharge[85];   //[nJet]
   Float_t         jetEt[85];   //[nJet]
   Float_t         jetRawPt[85];   //[nJet]
   Float_t         jetRawEn[85];   //[nJet]
   Float_t         jetArea[85];   //[nJet]
   Float_t         jetCHF[85];   //[nJet]
   Float_t         jetNHF[85];   //[nJet]
   Float_t         jetCEF[85];   //[nJet]
   Float_t         jetNEF[85];   //[nJet]
   Int_t           jetNCH[85];   //[nJet]
   Float_t         jetHFHAE[85];   //[nJet]
   Float_t         jetHFEME[85];   //[nJet]
   Int_t           jetNConstituents[85];   //[nJet]
   Float_t         jetCombinedSecondaryVtxBJetTags[85];   //[nJet]
   Float_t         jetCombinedSecondaryVtxMVABJetTags[85];   //[nJet]
   Float_t         jetJetProbabilityBJetTags[85];   //[nJet]
   Float_t         jetJetBProbabilityBJetTags[85];   //[nJet]
   Float_t         jetTrackCountingHighPurBJetTags[85];   //[nJet]
   Float_t         jetBetaStar[85][70];   //[nJet]
   Bool_t          jetPFLooseId[85];   //[nJet]
   Float_t         jetDRMean[85];   //[nJet]
   Float_t         jetDR2Mean[85];   //[nJet]
   Float_t         jetDZ[85];   //[nJet]
   Float_t         jetFrac01[85];   //[nJet]
   Float_t         jetFrac02[85];   //[nJet]
   Float_t         jetFrac03[85];   //[nJet]
   Float_t         jetFrac04[85];   //[nJet]
   Float_t         jetFrac05[85];   //[nJet]
   Float_t         jetFrac06[85];   //[nJet]
   Float_t         jetFrac07[85];   //[nJet]
   Float_t         jetBeta[85];   //[nJet]
   Float_t         jetBetaStarCMG[85];   //[nJet]
   Float_t         jetBetaStarClassic[85];   //[nJet]
   Float_t         jetBetaExt[85][70];   //[nJet]
   Float_t         jetBetaStarCMGExt[85][70];   //[nJet]
   Float_t         jetBetaStarClassicExt[85][70];   //[nJet]
   Float_t         jetNNeutrals[85];   //[nJet]
   Float_t         jetNCharged[85];   //[nJet]
   Float_t         jetMVAs[85][4];   //[nJet]
   Int_t           jetWPLevels[85][4];   //[nJet]
   Float_t         jetMVAsExt[85][4][70];   //[nJet]
   Int_t           jetWPLevelsExt[85][4][70];   //[nJet]
   Int_t           nLowPtJet;
   Float_t         jetLowPtEn[67];   //[nLowPtJet]
   Float_t         jetLowPtPt[67];   //[nLowPtJet]
   Float_t         jetLowPtEta[67];   //[nLowPtJet]
   Float_t         jetLowPtPhi[67];   //[nLowPtJet]
   Float_t         jetLowPtCharge[67];   //[nLowPtJet]
   Float_t         jetLowPtEt[67];   //[nLowPtJet]
   Float_t         jetLowPtRawPt[67];   //[nLowPtJet]
   Float_t         jetLowPtRawEn[67];   //[nLowPtJet]
   Float_t         jetLowPtArea[67];   //[nLowPtJet]
   Int_t           nConv;
   Float_t         convP4[500][4];   //[nConv]
   Float_t         convVtx[500][3];   //[nConv]
   Float_t         convVtxErr[500][3];   //[nConv]
   Float_t         convPairMomentum[500][3];   //[nConv]
   Float_t         convRefittedMomentum[500][3];   //[nConv]
   Int_t           convNTracks[500];   //[nConv]
   Float_t         convPairInvMass[500];   //[nConv]
   Float_t         convPairCotThetaSep[500];   //[nConv]
   Float_t         convEoverP[500];   //[nConv]
   Float_t         convDistOfMinApproach[500];   //[nConv]
   Float_t         convDPhiTrksAtVtx[500];   //[nConv]
   Float_t         convDPhiTrksAtEcal[500];   //[nConv]
   Float_t         convDEtaTrksAtEcal[500];   //[nConv]
   Float_t         convDxy[500];   //[nConv]
   Float_t         convDz[500];   //[nConv]
   Float_t         convLxy[500];   //[nConv]
   Float_t         convLz[500];   //[nConv]
   Float_t         convZofPrimVtxFromTrks[500];   //[nConv]
   Int_t           convNHitsBeforeVtx[500][2];   //[nConv]
   Int_t           convNSharedHits[500];   //[nConv]
   Int_t           convValidVtx[500];   //[nConv]
   Float_t         convMVALikelihood[500];   //[nConv]
   Float_t         convChi2[500];   //[nConv]
   Float_t         convChi2Probability[500];   //[nConv]
   Float_t         convTk1Dz[500];   //[nConv]
   Float_t         convTk2Dz[500];   //[nConv]
   Float_t         convTk1DzErr[500];   //[nConv]
   Float_t         convTk2DzErr[500];   //[nConv]
   Int_t           convCh1Ch2[500];   //[nConv]
   Float_t         convTk1D0[500];   //[nConv]
   Float_t         convTk1Pout[500];   //[nConv]
   Float_t         convTk1Pin[500];   //[nConv]
   Float_t         convTk2D0[500];   //[nConv]
   Float_t         convTk2Pout[500];   //[nConv]
   Float_t         convTk2Pin[500];   //[nConv]

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumis;   //!
   TBranch        *b_isData;   //!
   TBranch        *b_nHLT;   //!
   TBranch        *b_HLT;   //!
   TBranch        *b_HLTIndex;   //!
   TBranch        *b_bspotPos;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_vtx;   //!
   TBranch        *b_IsVtxGood;   //!
   TBranch        *b_nVtxBS;   //!
   TBranch        *b_vtxbs;   //!
   TBranch        *b_vtxbsPtMod;   //!
   TBranch        *b_vtxbsSumPt2;   //!
//   TBranch        *b_vtxbsTkIndex;   //!
//   TBranch        *b_vtxbsTkWeight;   //!
   TBranch        *b_nTrk;   //!
   TBranch        *b_trkP;   //!
   TBranch        *b_trkVtx;   //!
   TBranch        *b_trkd0;   //!
   TBranch        *b_trkd0Err;   //!
   TBranch        *b_trkdz;   //!
   TBranch        *b_trkdzErr;   //!
   TBranch        *b_trkPtErr;   //!
   TBranch        *b_trkQuality;   //!
   TBranch        *b_nGoodTrk;   //!
   TBranch        *b_IsTracksGood;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_METPhi;   //!
   TBranch        *b_METsumEt;   //!
   TBranch        *b_tcMET;   //!
   TBranch        *b_tcMETPhi;   //!
   TBranch        *b_tcMETsumEt;   //!
   TBranch        *b_tcMETmEtSig;   //!
   TBranch        *b_tcMETSig;   //!
   TBranch        *b_pfMET;   //!
   TBranch        *b_pfMETPhi;   //!
   TBranch        *b_pfMETsumEt;   //!
   TBranch        *b_pfMETmEtSig;   //!
   TBranch        *b_pfMETSig;   //!
   TBranch        *b_recoPfMET;   //!
   TBranch        *b_recoPfMETPhi;   //!
   TBranch        *b_recoPfMETsumEt;   //!
   TBranch        *b_recoPfMETmEtSig;   //!
   TBranch        *b_recoPfMETSig;   //!
   TBranch        *b_nEle;   //!
   TBranch        *b_eleTrg;   //!
   TBranch        *b_eleClass;   //!
   TBranch        *b_eleIsEcalDriven;   //!
   TBranch        *b_eleCharge;   //!
   TBranch        *b_eleEn;   //!
   TBranch        *b_eleEcalEn;   //!
   TBranch        *b_eleSCRawEn;   //!
   TBranch        *b_eleSCEn;   //!
   TBranch        *b_eleESEn;   //!
   TBranch        *b_elePt;   //!
   TBranch        *b_eleEta;   //!
   TBranch        *b_elePhi;   //!
   TBranch        *b_eleEtaVtx;   //!
   TBranch        *b_elePhiVtx;   //!
   TBranch        *b_eleEtVtx;   //!
   TBranch        *b_eleSCEta;   //!
   TBranch        *b_eleSCPhi;   //!
   TBranch        *b_eleSCEtaWidth;   //!
   TBranch        *b_eleSCPhiWidth;   //!
   TBranch        *b_eleVtx;   //!
   TBranch        *b_eleD0;   //!
   TBranch        *b_eleDz;   //!
   TBranch        *b_eleD0Vtx;   //!
   TBranch        *b_eleDzVtx;   //!
   TBranch        *b_eleHoverE;   //!
   TBranch        *b_eleHoverE12;   //!
   TBranch        *b_eleEoverP;   //!
   TBranch        *b_elePin;   //!
   TBranch        *b_elePout;   //!
   TBranch        *b_eleBrem;   //!
   TBranch        *b_eledEtaAtVtx;   //!
   TBranch        *b_eledPhiAtVtx;   //!
   TBranch        *b_eleSigmaIEtaIEta;   //!
   TBranch        *b_eleSigmaIEtaIPhi;   //!
   TBranch        *b_eleSigmaIPhiIPhi;   //!
   TBranch        *b_eleEmax;   //!
   TBranch        *b_eleE1x5;   //!
   TBranch        *b_eleE3x3;   //!
   TBranch        *b_eleE5x5;   //!
   TBranch        *b_eleE2x5Right;   //!
   TBranch        *b_eleE2x5Left;   //!
   TBranch        *b_eleE2x5Top;   //!
   TBranch        *b_eleE2x5Bottom;   //!
   TBranch        *b_eleRegrE;   //!
   TBranch        *b_eleRegrEerr;   //!
   TBranch        *b_eleSeedTime;   //!
   TBranch        *b_eleRecoFlag;   //!
   TBranch        *b_eleIsoTrkDR03;   //!
   TBranch        *b_eleIsoEcalDR03;   //!
   TBranch        *b_eleIsoHcalDR03;   //!
   TBranch        *b_eleIsoHcalDR0312;   //!
   TBranch        *b_eleIsoHcalSolidDR03;   //!
   TBranch        *b_eleIsoTrkDR04;   //!
   TBranch        *b_eleIsoEcalDR04;   //!
   TBranch        *b_eleIsoHcalDR04;   //!
   TBranch        *b_eleIsoHcalDR0412;   //!
   TBranch        *b_eleIsoHcalSolidDR04;   //!
   TBranch        *b_eleMissHits;   //!
   TBranch        *b_eleConvDist;   //!
   TBranch        *b_eleConvDcot;   //!
   TBranch        *b_eleConvVtxFit;   //!
   TBranch        *b_eleIDMVANonTrig;   //!
   TBranch        *b_eleIDMVATrig;   //!
   TBranch        *b_elePFChIso;   //!
   TBranch        *b_elePFPhoIso;   //!
   TBranch        *b_elePFNeuIso;   //!
   TBranch        *b_eleESEffSigmaRR;   //!
   TBranch        *b_nPho;   //!
   TBranch        *b_phoTrg;   //!
   TBranch        *b_phoTrgFilter;   //!
   TBranch        *b_phoIsPhoton;   //!
   TBranch        *b_phoSCPos;   //!
   TBranch        *b_phoCaloPos;   //!
   TBranch        *b_phoE;   //!
   TBranch        *b_phoEt;   //!
   TBranch        *b_phoEta;   //!
   TBranch        *b_phoVtx;   //!
   TBranch        *b_phoPhi;   //!
   TBranch        *b_phoEtVtx;   //!
   TBranch        *b_phoEtaVtx;   //!
   TBranch        *b_phoPhiVtx;   //!
   TBranch        *b_phoR9;   //!
   TBranch        *b_phoTrkIsoSolidDR03;   //!
   TBranch        *b_phoTrkIsoHollowDR03;   //!
   TBranch        *b_phoEcalIsoDR03;   //!
   TBranch        *b_phoHcalIsoDR03;   //!
   TBranch        *b_phoHcalIsoDR0312;   //!
   TBranch        *b_phoHcalIsoSolidDR03;   //!
   TBranch        *b_phoTrkIsoSolidDR04;   //!
   TBranch        *b_phoTrkIsoHollowDR04;   //!
   TBranch        *b_phoCiCTrkIsoDR03;   //!
   TBranch        *b_phoCiCTrkIsoDR04;   //!
   TBranch        *b_phoCiCdRtoTrk;   //!
   TBranch        *b_phoEcalIsoDR04;   //!
   TBranch        *b_phoHcalIsoDR04;   //!
   TBranch        *b_phoHcalIsoDR0412;   //!
   TBranch        *b_phoHcalIsoSolidDR04;   //!
   TBranch        *b_phoHoverE;   //!
   TBranch        *b_phoHoverE12;   //!
   TBranch        *b_phoEleVeto;   //!
   TBranch        *b_phoSigmaIEtaIEta;   //!
   TBranch        *b_phoSigmaIEtaIPhi;   //!
   TBranch        *b_phoSigmaIPhiIPhi;   //!
   TBranch        *b_phoCiCPF4phopfIso03;   //!
   TBranch        *b_phoCiCPF4phopfIso04;   //!
   TBranch        *b_phoCiCPF4chgpfIso02;   //!
   TBranch        *b_phoCiCPF4chgpfIso03;   //!
   TBranch        *b_phoCiCPF4chgpfIso04;   //!
   TBranch        *b_phoEmax;   //!
   TBranch        *b_phoEtop;   //!
   TBranch        *b_phoEbottom;   //!
   TBranch        *b_phoEleft;   //!
   TBranch        *b_phoEright;   //!
   TBranch        *b_phoE3x3;   //!
   TBranch        *b_phoE3x1;   //!
   TBranch        *b_phoE1x3;   //!
   TBranch        *b_phoE5x5;   //!
   TBranch        *b_phoE1x5;   //!
   TBranch        *b_phoE2x2;   //!
   TBranch        *b_phoE2x5Max;   //!
   TBranch        *b_phoE2x5Right;   //!
   TBranch        *b_phoE2x5Left;   //!
   TBranch        *b_phoE2x5Top;   //!
   TBranch        *b_phoE2x5Bottom;   //!
   TBranch        *b_phoPFChIso;   //!
   TBranch        *b_phoPFPhoIso;   //!
   TBranch        *b_phoPFNeuIso;   //!
   TBranch        *b_phoPFIsoNeutral;   //!
   TBranch        *b_phoPFIsoPhoton;   //!
   TBranch        *b_phoPFIsoCharged;   //!
   TBranch        *b_phoRegrE;   //!
   TBranch        *b_phoRegrEerr;   //!
   TBranch        *b_phoSeedTime;   //!
   TBranch        *b_phoSeedDetId1;   //!
   TBranch        *b_phoSeedDetId2;   //!
   TBranch        *b_phoRecoFlag;   //!
   TBranch        *b_phoPos;   //!
   TBranch        *b_phoSCE;   //!
   TBranch        *b_phoSCRawE;   //!
   TBranch        *b_phoESEn;   //!
   TBranch        *b_phoSCEt;   //!
   TBranch        *b_phoSCEta;   //!
   TBranch        *b_phoSCPhi;   //!
   TBranch        *b_phoSCEtaWidth;   //!
   TBranch        *b_phoSCPhiWidth;   //!
   TBranch        *b_phoSCBrem;   //!
   TBranch        *b_phoOverlap;   //!
   TBranch        *b_phohasPixelSeed;   //!
   TBranch        *b_PFRecoMatch;   //!
   TBranch        *b_PFEleMatch;   //!
   TBranch        *b_PFEleVeto;   //!
   TBranch        *b_pho_hasConvPf;   //!
   TBranch        *b_pho_hasSLConvPf;   //!
   TBranch        *b_MustacheEin;   //!
   TBranch        *b_MustacheEOut;   //!
   TBranch        *b_MustacheEtOut;   //!
   TBranch        *b_PFLowestClustE;   //!
   TBranch        *b_PFClustdEta;   //!
   TBranch        *b_PFClustdPhi;   //!
   TBranch        *b_PFClustRMSPhi;   //!
   TBranch        *b_PFClustRMSPhiMust;   //!
   TBranch        *b_PFPreShowerE1;   //!
   TBranch        *b_PFPreShowerE2;   //!
   TBranch        *b_pho_pfconvVtxZ;   //!
   TBranch        *b_pho_pfconvVtxZErr;   //!
   TBranch        *b_pho_nSLConv;   //!
   TBranch        *b_pho_pfSLConvPos;   //!
   TBranch        *b_pho_pfSLConvVtxZ;   //!
   TBranch        *b_phoIsConv;   //!
   TBranch        *b_phoNConv;   //!
   TBranch        *b_phoConvInvMass;   //!
   TBranch        *b_phoConvCotTheta;   //!
   TBranch        *b_phoConvEoverP;   //!
   TBranch        *b_phoConvZofPVfromTrks;   //!
   TBranch        *b_phoConvMinDist;   //!
   TBranch        *b_phoConvdPhiAtVtx;   //!
   TBranch        *b_phoConvdPhiAtCalo;   //!
   TBranch        *b_phoConvdEtaAtCalo;   //!
   TBranch        *b_phoConvTrkd0;   //!
   TBranch        *b_phoConvTrkPin;   //!
   TBranch        *b_phoConvTrkPout;   //!
   TBranch        *b_phoConvTrkdz;   //!
   TBranch        *b_phoConvTrkdzErr;   //!
   TBranch        *b_phoConvChi2;   //!
   TBranch        *b_phoConvChi2Prob;   //!
   TBranch        *b_phoConvNTrks;   //!
   TBranch        *b_phoConvCharge;   //!
   TBranch        *b_phoConvValidVtx;   //!
   TBranch        *b_phoConvLikeLihood;   //!
   TBranch        *b_phoConvP4;   //!
   TBranch        *b_phoConvVtx;   //!
   TBranch        *b_phoConvVtxErr;   //!
   TBranch        *b_phoConvPairMomentum;   //!
   TBranch        *b_phoConvRefittedMomentum;   //!
   TBranch        *b_phoESEffSigmaRR;   //!
   TBranch        *b_nMu;   //!
   TBranch        *b_muTrg;   //!
   TBranch        *b_muEta;   //!
   TBranch        *b_muPhi;   //!
   TBranch        *b_muCharge;   //!
   TBranch        *b_muPt;   //!
   TBranch        *b_muPz;   //!
   TBranch        *b_muIsoTrk;   //!
   TBranch        *b_muIsoCalo;   //!
   TBranch        *b_muIsoEcal;   //!
   TBranch        *b_muIsoHcal;   //!
   TBranch        *b_muChi2NDF;   //!
   TBranch        *b_muInnerChi2NDF;   //!
   TBranch        *b_muPFIsoR04_CH;   //!
   TBranch        *b_muPFIsoR04_NH;   //!
   TBranch        *b_muPFIsoR04_Pho;   //!
   TBranch        *b_muPFIsoR04_PU;   //!
   TBranch        *b_muPFIsoR04_CPart;   //!
   TBranch        *b_muPFIsoR04_NHHT;   //!
   TBranch        *b_muPFIsoR04_PhoHT;   //!
   TBranch        *b_muPFIsoR03_CH;   //!
   TBranch        *b_muPFIsoR03_NH;   //!
   TBranch        *b_muPFIsoR03_Pho;   //!
   TBranch        *b_muPFIsoR03_PU;   //!
   TBranch        *b_muPFIsoR03_CPart;   //!
   TBranch        *b_muPFIsoR03_NHHT;   //!
   TBranch        *b_muPFIsoR03_PhoHT;   //!
   TBranch        *b_muType;   //!
   TBranch        *b_muID;   //!
   TBranch        *b_muD0;   //!
   TBranch        *b_muDz;   //!
   TBranch        *b_muD0Vtx;   //!
   TBranch        *b_muDzVtx;   //!
   TBranch        *b_muInnerD0;   //!
   TBranch        *b_muInnerDz;   //!
   TBranch        *b_muNumberOfValidTrkLayers;   //!
   TBranch        *b_muNumberOfValidTrkHits;   //!
   TBranch        *b_muNumberOfValidPixelLayers;   //!
   TBranch        *b_muNumberOfValidPixelHits;   //!
   TBranch        *b_muNumberOfValidMuonHits;   //!
   TBranch        *b_muStations;   //!
   TBranch        *b_muChambers;   //!
   TBranch        *b_nPFPho_;   //!
   TBranch        *b_PFPhoE_;   //!
   TBranch        *b_PFPhoEt_;   //!
   TBranch        *b_PFPhoEta_;   //!
   TBranch        *b_PFPhoPhi_;   //!
   TBranch        *b_PFPhoHoverE_;   //!
   TBranch        *b_PFPhoSCPos_;   //!
   TBranch        *b_PFPhoSCEta_;   //!
   TBranch        *b_PFPhoSCPhi_;   //!
   TBranch        *b_nPFEle_;   //!
   TBranch        *b_PFElePt_;   //!
   TBranch        *b_PFEleEta_;   //!
   TBranch        *b_PFElePhi_;   //!
   TBranch        *b_PFEleEn_;   //!
   TBranch        *b_PFEleCharge;   //!
   TBranch        *b_rho25;   //!
   TBranch        *b_rho25_neu;   //!
   TBranch        *b_rho25_muPFiso;   //!
   TBranch        *b_rho25_elePFiso;   //!
   TBranch        *b_rho2011;   //!
   TBranch        *b_rho2012;   //!
   TBranch        *b_nJet;   //!
   TBranch        *b_jetTrg;   //!
   TBranch        *b_jetEn;   //!
   TBranch        *b_jetPt;   //!
   TBranch        *b_jetEta;   //!
   TBranch        *b_jetPhi;   //!
   TBranch        *b_jetCharge;   //!
   TBranch        *b_jetEt;   //!
   TBranch        *b_jetRawPt;   //!
   TBranch        *b_jetRawEn;   //!
   TBranch        *b_jetArea;   //!
   TBranch        *b_jetCHF;   //!
   TBranch        *b_jetNHF;   //!
   TBranch        *b_jetCEF;   //!
   TBranch        *b_jetNEF;   //!
   TBranch        *b_jetNCH;   //!
   TBranch        *b_jetHFHAE;   //!
   TBranch        *b_jetHFEME;   //!
   TBranch        *b_jetNConstituents;   //!
   TBranch        *b_jetCombinedSecondaryVtxBJetTags;   //!
   TBranch        *b_jetCombinedSecondaryVtxMVABJetTags;   //!
   TBranch        *b_jetJetProbabilityBJetTags;   //!
   TBranch        *b_jetJetBProbabilityBJetTags;   //!
   TBranch        *b_jetTrackCountingHighPurBJetTags;   //!
   TBranch        *b_jetBetaStar;   //!
   TBranch        *b_jetPFLooseId;   //!
   TBranch        *b_jetDRMean;   //!
   TBranch        *b_jetDR2Mean;   //!
   TBranch        *b_jetDZ;   //!
   TBranch        *b_jetFrac01;   //!
   TBranch        *b_jetFrac02;   //!
   TBranch        *b_jetFrac03;   //!
   TBranch        *b_jetFrac04;   //!
   TBranch        *b_jetFrac05;   //!
   TBranch        *b_jetFrac06;   //!
   TBranch        *b_jetFrac07;   //!
   TBranch        *b_jetBeta;   //!
   TBranch        *b_jetBetaStarCMG;   //!
   TBranch        *b_jetBetaStarClassic;   //!
   TBranch        *b_jetBetaExt;   //!
   TBranch        *b_jetBetaStarCMGExt;   //!
   TBranch        *b_jetBetaStarClassicExt;   //!
   TBranch        *b_jetNNeutrals;   //!
   TBranch        *b_jetNCharged;   //!
   TBranch        *b_jetMVAs;   //!
   TBranch        *b_jetWPLevels;   //!
   TBranch        *b_jetMVAsExt;   //!
   TBranch        *b_jetWPLevelsExt;   //!
   TBranch        *b_nLowPtJet;   //!
   TBranch        *b_jetLowPtEn;   //!
   TBranch        *b_jetLowPtPt;   //!
   TBranch        *b_jetLowPtEta;   //!
   TBranch        *b_jetLowPtPhi;   //!
   TBranch        *b_jetLowPtCharge;   //!
   TBranch        *b_jetLowPtEt;   //!
   TBranch        *b_jetLowPtRawPt;   //!
   TBranch        *b_jetLowPtRawEn;   //!
   TBranch        *b_jetLowPtArea;   //!
   TBranch        *b_nConv;   //!
   TBranch        *b_convP4;   //!
   TBranch        *b_convVtx;   //!
   TBranch        *b_convVtxErr;   //!
   TBranch        *b_convPairMomentum;   //!
   TBranch        *b_convRefittedMomentum;   //!
   TBranch        *b_convNTracks;   //!
   TBranch        *b_convPairInvMass;   //!
   TBranch        *b_convPairCotThetaSep;   //!
   TBranch        *b_convEoverP;   //!
   TBranch        *b_convDistOfMinApproach;   //!
   TBranch        *b_convDPhiTrksAtVtx;   //!
   TBranch        *b_convDPhiTrksAtEcal;   //!
   TBranch        *b_convDEtaTrksAtEcal;   //!
   TBranch        *b_convDxy;   //!
   TBranch        *b_convDz;   //!
   TBranch        *b_convLxy;   //!
   TBranch        *b_convLz;   //!
   TBranch        *b_convZofPrimVtxFromTrks;   //!
   TBranch        *b_convNHitsBeforeVtx;   //!
   TBranch        *b_convNSharedHits;   //!
   TBranch        *b_convValidVtx;   //!
   TBranch        *b_convMVALikelihood;   //!
   TBranch        *b_convChi2;   //!
   TBranch        *b_convChi2Probability;   //!
   TBranch        *b_convTk1Dz;   //!
   TBranch        *b_convTk2Dz;   //!
   TBranch        *b_convTk1DzErr;   //!
   TBranch        *b_convTk2DzErr;   //!
   TBranch        *b_convCh1Ch2;   //!
   TBranch        *b_convTk1D0;   //!
   TBranch        *b_convTk1Pout;   //!
   TBranch        *b_convTk1Pin;   //!
   TBranch        *b_convTk2D0;   //!
   TBranch        *b_convTk2Pout;   //!
   TBranch        *b_convTk2Pin;   //!

   ana_job_2photon_2012b_PRv1_skim(TTree *tree=0);
   virtual ~ana_job_2photon_2012b_PRv1_skim();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ana_job_2photon_2012b_PRv1_skim_cxx
ana_job_2photon_2012b_PRv1_skim::ana_job_2photon_2012b_PRv1_skim(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("rfio:/castor/cern.ch/user/c/cmkuo/ggNtuple52/V05-02-05-00_pre9/job_2photon_2012b_PRv1_skim.root");
      if (!f) {
         f = new TFile("rfio:/castor/cern.ch/user/c/cmkuo/ggNtuple52/V05-02-05-00_pre9/job_2photon_2012b_PRv1_skim.root");
         //f->cd("rfio:/castor/cern.ch/user/c/cmkuo/ggNtuple52/V05-02-05-00_pre9/job_2photon_2012b_PRv1_skim.root:/ggNtuplizer");
         f=TFile::Open("rfio:/castor/cern.ch/user/c/cmkuo/ggNtuple52/V05-02-05-00_pre9/job_2photon_2012b_PRv1_skim.root");
         f->cd("ggNtuplizer");

      }
      tree = (TTree*)gDirectory->Get("EventTree");

   }
   Init(tree);
}

ana_job_2photon_2012b_PRv1_skim::~ana_job_2photon_2012b_PRv1_skim()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ana_job_2photon_2012b_PRv1_skim::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ana_job_2photon_2012b_PRv1_skim::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ana_job_2photon_2012b_PRv1_skim::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
//   vtxbsTkIndex = 0;
//   vtxbsTkWeight = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumis", &lumis, &b_lumis);
   fChain->SetBranchAddress("isData", &isData, &b_isData);
   fChain->SetBranchAddress("nHLT", &nHLT, &b_nHLT);
   fChain->SetBranchAddress("HLT", HLT, &b_HLT);
   fChain->SetBranchAddress("HLTIndex", HLTIndex, &b_HLTIndex);
   fChain->SetBranchAddress("bspotPos", bspotPos, &b_bspotPos);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
   fChain->SetBranchAddress("vtx", vtx, &b_vtx);
   fChain->SetBranchAddress("IsVtxGood", &IsVtxGood, &b_IsVtxGood);
   fChain->SetBranchAddress("nVtxBS", &nVtxBS, &b_nVtxBS);
   fChain->SetBranchAddress("vtxbs", vtxbs, &b_vtxbs);
   fChain->SetBranchAddress("vtxbsPtMod", vtxbsPtMod, &b_vtxbsPtMod);
   fChain->SetBranchAddress("vtxbsSumPt2", vtxbsSumPt2, &b_vtxbsSumPt2);
//   fChain->SetBranchAddress("vtxbsTkIndex", &vtxbsTkIndex, &b_vtxbsTkIndex);
//   fChain->SetBranchAddress("vtxbsTkWeight", &vtxbsTkWeight, &b_vtxbsTkWeight);
   fChain->SetBranchAddress("nTrk", &nTrk, &b_nTrk);
   fChain->SetBranchAddress("trkP", trkP, &b_trkP);
   fChain->SetBranchAddress("trkVtx", trkVtx, &b_trkVtx);
   fChain->SetBranchAddress("trkd0", trkd0, &b_trkd0);
   fChain->SetBranchAddress("trkd0Err", trkd0Err, &b_trkd0Err);
   fChain->SetBranchAddress("trkdz", trkdz, &b_trkdz);
   fChain->SetBranchAddress("trkdzErr", trkdzErr, &b_trkdzErr);
   fChain->SetBranchAddress("trkPtErr", trkPtErr, &b_trkPtErr);
   fChain->SetBranchAddress("trkQuality", trkQuality, &b_trkQuality);
   fChain->SetBranchAddress("nGoodTrk", &nGoodTrk, &b_nGoodTrk);
   fChain->SetBranchAddress("IsTracksGood", &IsTracksGood, &b_IsTracksGood);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
   fChain->SetBranchAddress("METsumEt", &METsumEt, &b_METsumEt);
   fChain->SetBranchAddress("tcMET", &tcMET, &b_tcMET);
   fChain->SetBranchAddress("tcMETPhi", &tcMETPhi, &b_tcMETPhi);
   fChain->SetBranchAddress("tcMETsumEt", &tcMETsumEt, &b_tcMETsumEt);
   fChain->SetBranchAddress("tcMETmEtSig", &tcMETmEtSig, &b_tcMETmEtSig);
   fChain->SetBranchAddress("tcMETSig", &tcMETSig, &b_tcMETSig);
   fChain->SetBranchAddress("pfMET", &pfMET, &b_pfMET);
   fChain->SetBranchAddress("pfMETPhi", &pfMETPhi, &b_pfMETPhi);
   fChain->SetBranchAddress("pfMETsumEt", &pfMETsumEt, &b_pfMETsumEt);
   fChain->SetBranchAddress("pfMETmEtSig", &pfMETmEtSig, &b_pfMETmEtSig);
   fChain->SetBranchAddress("pfMETSig", &pfMETSig, &b_pfMETSig);
   fChain->SetBranchAddress("recoPfMET", &recoPfMET, &b_recoPfMET);
   fChain->SetBranchAddress("recoPfMETPhi", &recoPfMETPhi, &b_recoPfMETPhi);
   fChain->SetBranchAddress("recoPfMETsumEt", &recoPfMETsumEt, &b_recoPfMETsumEt);
   fChain->SetBranchAddress("recoPfMETmEtSig", &recoPfMETmEtSig, &b_recoPfMETmEtSig);
   fChain->SetBranchAddress("recoPfMETSig", &recoPfMETSig, &b_recoPfMETSig);
   fChain->SetBranchAddress("nEle", &nEle, &b_nEle);
   fChain->SetBranchAddress("eleTrg", eleTrg, &b_eleTrg);
   fChain->SetBranchAddress("eleClass", eleClass, &b_eleClass);
   fChain->SetBranchAddress("eleIsEcalDriven", eleIsEcalDriven, &b_eleIsEcalDriven);
   fChain->SetBranchAddress("eleCharge", eleCharge, &b_eleCharge);
   fChain->SetBranchAddress("eleEn", eleEn, &b_eleEn);
   fChain->SetBranchAddress("eleEcalEn", eleEcalEn, &b_eleEcalEn);
   fChain->SetBranchAddress("eleSCRawEn", eleSCRawEn, &b_eleSCRawEn);
   fChain->SetBranchAddress("eleSCEn", eleSCEn, &b_eleSCEn);
   fChain->SetBranchAddress("eleESEn", eleESEn, &b_eleESEn);
   fChain->SetBranchAddress("elePt", elePt, &b_elePt);
   fChain->SetBranchAddress("eleEta", eleEta, &b_eleEta);
   fChain->SetBranchAddress("elePhi", elePhi, &b_elePhi);
   fChain->SetBranchAddress("eleEtaVtx", eleEtaVtx, &b_eleEtaVtx);
   fChain->SetBranchAddress("elePhiVtx", elePhiVtx, &b_elePhiVtx);
   fChain->SetBranchAddress("eleEtVtx", eleEtVtx, &b_eleEtVtx);
   fChain->SetBranchAddress("eleSCEta", eleSCEta, &b_eleSCEta);
   fChain->SetBranchAddress("eleSCPhi", eleSCPhi, &b_eleSCPhi);
   fChain->SetBranchAddress("eleSCEtaWidth", eleSCEtaWidth, &b_eleSCEtaWidth);
   fChain->SetBranchAddress("eleSCPhiWidth", eleSCPhiWidth, &b_eleSCPhiWidth);
   fChain->SetBranchAddress("eleVtx", eleVtx, &b_eleVtx);
   fChain->SetBranchAddress("eleD0", eleD0, &b_eleD0);
   fChain->SetBranchAddress("eleDz", eleDz, &b_eleDz);
   fChain->SetBranchAddress("eleD0Vtx", eleD0Vtx, &b_eleD0Vtx);
   fChain->SetBranchAddress("eleDzVtx", eleDzVtx, &b_eleDzVtx);
   fChain->SetBranchAddress("eleHoverE", eleHoverE, &b_eleHoverE);
   fChain->SetBranchAddress("eleHoverE12", eleHoverE12, &b_eleHoverE12);
   fChain->SetBranchAddress("eleEoverP", eleEoverP, &b_eleEoverP);
   fChain->SetBranchAddress("elePin", elePin, &b_elePin);
   fChain->SetBranchAddress("elePout", elePout, &b_elePout);
   fChain->SetBranchAddress("eleBrem", eleBrem, &b_eleBrem);
   fChain->SetBranchAddress("eledEtaAtVtx", eledEtaAtVtx, &b_eledEtaAtVtx);
   fChain->SetBranchAddress("eledPhiAtVtx", eledPhiAtVtx, &b_eledPhiAtVtx);
   fChain->SetBranchAddress("eleSigmaIEtaIEta", eleSigmaIEtaIEta, &b_eleSigmaIEtaIEta);
   fChain->SetBranchAddress("eleSigmaIEtaIPhi", eleSigmaIEtaIPhi, &b_eleSigmaIEtaIPhi);
   fChain->SetBranchAddress("eleSigmaIPhiIPhi", eleSigmaIPhiIPhi, &b_eleSigmaIPhiIPhi);
   fChain->SetBranchAddress("eleEmax", eleEmax, &b_eleEmax);
   fChain->SetBranchAddress("eleE1x5", eleE1x5, &b_eleE1x5);
   fChain->SetBranchAddress("eleE3x3", eleE3x3, &b_eleE3x3);
   fChain->SetBranchAddress("eleE5x5", eleE5x5, &b_eleE5x5);
   fChain->SetBranchAddress("eleE2x5Right", eleE2x5Right, &b_eleE2x5Right);
   fChain->SetBranchAddress("eleE2x5Left", eleE2x5Left, &b_eleE2x5Left);
   fChain->SetBranchAddress("eleE2x5Top", eleE2x5Top, &b_eleE2x5Top);
   fChain->SetBranchAddress("eleE2x5Bottom", eleE2x5Bottom, &b_eleE2x5Bottom);
   fChain->SetBranchAddress("eleRegrE", eleRegrE, &b_eleRegrE);
   fChain->SetBranchAddress("eleRegrEerr", eleRegrEerr, &b_eleRegrEerr);
   fChain->SetBranchAddress("eleSeedTime", eleSeedTime, &b_eleSeedTime);
   fChain->SetBranchAddress("eleRecoFlag", eleRecoFlag, &b_eleRecoFlag);
   fChain->SetBranchAddress("eleIsoTrkDR03", eleIsoTrkDR03, &b_eleIsoTrkDR03);
   fChain->SetBranchAddress("eleIsoEcalDR03", eleIsoEcalDR03, &b_eleIsoEcalDR03);
   fChain->SetBranchAddress("eleIsoHcalDR03", eleIsoHcalDR03, &b_eleIsoHcalDR03);
   fChain->SetBranchAddress("eleIsoHcalDR0312", eleIsoHcalDR0312, &b_eleIsoHcalDR0312);
   fChain->SetBranchAddress("eleIsoHcalSolidDR03", eleIsoHcalSolidDR03, &b_eleIsoHcalSolidDR03);
   fChain->SetBranchAddress("eleIsoTrkDR04", eleIsoTrkDR04, &b_eleIsoTrkDR04);
   fChain->SetBranchAddress("eleIsoEcalDR04", eleIsoEcalDR04, &b_eleIsoEcalDR04);
   fChain->SetBranchAddress("eleIsoHcalDR04", eleIsoHcalDR04, &b_eleIsoHcalDR04);
   fChain->SetBranchAddress("eleIsoHcalDR0412", eleIsoHcalDR0412, &b_eleIsoHcalDR0412);
   fChain->SetBranchAddress("eleIsoHcalSolidDR04", eleIsoHcalSolidDR04, &b_eleIsoHcalSolidDR04);
   fChain->SetBranchAddress("eleMissHits", eleMissHits, &b_eleMissHits);
   fChain->SetBranchAddress("eleConvDist", eleConvDist, &b_eleConvDist);
   fChain->SetBranchAddress("eleConvDcot", eleConvDcot, &b_eleConvDcot);
   fChain->SetBranchAddress("eleConvVtxFit", eleConvVtxFit, &b_eleConvVtxFit);
   fChain->SetBranchAddress("eleIDMVANonTrig", eleIDMVANonTrig, &b_eleIDMVANonTrig);
   fChain->SetBranchAddress("eleIDMVATrig", eleIDMVATrig, &b_eleIDMVATrig);
   fChain->SetBranchAddress("elePFChIso", elePFChIso, &b_elePFChIso);
   fChain->SetBranchAddress("elePFPhoIso", elePFPhoIso, &b_elePFPhoIso);
   fChain->SetBranchAddress("elePFNeuIso", elePFNeuIso, &b_elePFNeuIso);
   fChain->SetBranchAddress("eleESEffSigmaRR", eleESEffSigmaRR, &b_eleESEffSigmaRR);
   fChain->SetBranchAddress("nPho", &nPho, &b_nPho);
   fChain->SetBranchAddress("phoTrg", phoTrg, &b_phoTrg);
   fChain->SetBranchAddress("phoTrgFilter", phoTrgFilter, &b_phoTrgFilter);
   fChain->SetBranchAddress("phoIsPhoton", phoIsPhoton, &b_phoIsPhoton);
   fChain->SetBranchAddress("phoSCPos", phoSCPos, &b_phoSCPos);
   fChain->SetBranchAddress("phoCaloPos", phoCaloPos, &b_phoCaloPos);
   fChain->SetBranchAddress("phoE", phoE, &b_phoE);
   fChain->SetBranchAddress("phoEt", phoEt, &b_phoEt);
   fChain->SetBranchAddress("phoEta", phoEta, &b_phoEta);
   fChain->SetBranchAddress("phoVtx", phoVtx, &b_phoVtx);
   fChain->SetBranchAddress("phoPhi", phoPhi, &b_phoPhi);
   fChain->SetBranchAddress("phoEtVtx", phoEtVtx, &b_phoEtVtx);
   fChain->SetBranchAddress("phoEtaVtx", phoEtaVtx, &b_phoEtaVtx);
   fChain->SetBranchAddress("phoPhiVtx", phoPhiVtx, &b_phoPhiVtx);
   fChain->SetBranchAddress("phoR9", phoR9, &b_phoR9);
   fChain->SetBranchAddress("phoTrkIsoSolidDR03", phoTrkIsoSolidDR03, &b_phoTrkIsoSolidDR03);
   fChain->SetBranchAddress("phoTrkIsoHollowDR03", phoTrkIsoHollowDR03, &b_phoTrkIsoHollowDR03);
   fChain->SetBranchAddress("phoEcalIsoDR03", phoEcalIsoDR03, &b_phoEcalIsoDR03);
   fChain->SetBranchAddress("phoHcalIsoDR03", phoHcalIsoDR03, &b_phoHcalIsoDR03);
   fChain->SetBranchAddress("phoHcalIsoDR0312", phoHcalIsoDR0312, &b_phoHcalIsoDR0312);
   fChain->SetBranchAddress("phoHcalIsoSolidDR03", phoHcalIsoSolidDR03, &b_phoHcalIsoSolidDR03);
   fChain->SetBranchAddress("phoTrkIsoSolidDR04", phoTrkIsoSolidDR04, &b_phoTrkIsoSolidDR04);
   fChain->SetBranchAddress("phoTrkIsoHollowDR04", phoTrkIsoHollowDR04, &b_phoTrkIsoHollowDR04);
   fChain->SetBranchAddress("phoCiCTrkIsoDR03", phoCiCTrkIsoDR03, &b_phoCiCTrkIsoDR03);
   fChain->SetBranchAddress("phoCiCTrkIsoDR04", phoCiCTrkIsoDR04, &b_phoCiCTrkIsoDR04);
   fChain->SetBranchAddress("phoCiCdRtoTrk", phoCiCdRtoTrk, &b_phoCiCdRtoTrk);
   fChain->SetBranchAddress("phoEcalIsoDR04", phoEcalIsoDR04, &b_phoEcalIsoDR04);
   fChain->SetBranchAddress("phoHcalIsoDR04", phoHcalIsoDR04, &b_phoHcalIsoDR04);
   fChain->SetBranchAddress("phoHcalIsoDR0412", phoHcalIsoDR0412, &b_phoHcalIsoDR0412);
   fChain->SetBranchAddress("phoHcalIsoSolidDR04", phoHcalIsoSolidDR04, &b_phoHcalIsoSolidDR04);
   fChain->SetBranchAddress("phoHoverE", phoHoverE, &b_phoHoverE);
   fChain->SetBranchAddress("phoHoverE12", phoHoverE12, &b_phoHoverE12);
   fChain->SetBranchAddress("phoEleVeto", phoEleVeto, &b_phoEleVeto);
   fChain->SetBranchAddress("phoSigmaIEtaIEta", phoSigmaIEtaIEta, &b_phoSigmaIEtaIEta);
   fChain->SetBranchAddress("phoSigmaIEtaIPhi", phoSigmaIEtaIPhi, &b_phoSigmaIEtaIPhi);
   fChain->SetBranchAddress("phoSigmaIPhiIPhi", phoSigmaIPhiIPhi, &b_phoSigmaIPhiIPhi);
   fChain->SetBranchAddress("phoCiCPF4phopfIso03", phoCiCPF4phopfIso03, &b_phoCiCPF4phopfIso03);
   fChain->SetBranchAddress("phoCiCPF4phopfIso04", phoCiCPF4phopfIso04, &b_phoCiCPF4phopfIso04);
   fChain->SetBranchAddress("phoCiCPF4chgpfIso02", phoCiCPF4chgpfIso02, &b_phoCiCPF4chgpfIso02);
   fChain->SetBranchAddress("phoCiCPF4chgpfIso03", phoCiCPF4chgpfIso03, &b_phoCiCPF4chgpfIso03);
   fChain->SetBranchAddress("phoCiCPF4chgpfIso04", phoCiCPF4chgpfIso04, &b_phoCiCPF4chgpfIso04);
   fChain->SetBranchAddress("phoEmax", phoEmax, &b_phoEmax);
   fChain->SetBranchAddress("phoEtop", phoEtop, &b_phoEtop);
   fChain->SetBranchAddress("phoEbottom", phoEbottom, &b_phoEbottom);
   fChain->SetBranchAddress("phoEleft", phoEleft, &b_phoEleft);
   fChain->SetBranchAddress("phoEright", phoEright, &b_phoEright);
   fChain->SetBranchAddress("phoE3x3", phoE3x3, &b_phoE3x3);
   fChain->SetBranchAddress("phoE3x1", phoE3x1, &b_phoE3x1);
   fChain->SetBranchAddress("phoE1x3", phoE1x3, &b_phoE1x3);
   fChain->SetBranchAddress("phoE5x5", phoE5x5, &b_phoE5x5);
   fChain->SetBranchAddress("phoE1x5", phoE1x5, &b_phoE1x5);
   fChain->SetBranchAddress("phoE2x2", phoE2x2, &b_phoE2x2);
   fChain->SetBranchAddress("phoE2x5Max", phoE2x5Max, &b_phoE2x5Max);
   fChain->SetBranchAddress("phoE2x5Right", phoE2x5Right, &b_phoE2x5Right);
   fChain->SetBranchAddress("phoE2x5Left", phoE2x5Left, &b_phoE2x5Left);
   fChain->SetBranchAddress("phoE2x5Top", phoE2x5Top, &b_phoE2x5Top);
   fChain->SetBranchAddress("phoE2x5Bottom", phoE2x5Bottom, &b_phoE2x5Bottom);
   fChain->SetBranchAddress("phoPFChIso", phoPFChIso, &b_phoPFChIso);
   fChain->SetBranchAddress("phoPFPhoIso", phoPFPhoIso, &b_phoPFPhoIso);
   fChain->SetBranchAddress("phoPFNeuIso", phoPFNeuIso, &b_phoPFNeuIso);
   fChain->SetBranchAddress("phoPFIsoNeutral", phoPFIsoNeutral, &b_phoPFIsoNeutral);
   fChain->SetBranchAddress("phoPFIsoPhoton", phoPFIsoPhoton, &b_phoPFIsoPhoton);
   fChain->SetBranchAddress("phoPFIsoCharged", phoPFIsoCharged, &b_phoPFIsoCharged);
   fChain->SetBranchAddress("phoRegrE", phoRegrE, &b_phoRegrE);
   fChain->SetBranchAddress("phoRegrEerr", phoRegrEerr, &b_phoRegrEerr);
   fChain->SetBranchAddress("phoSeedTime", phoSeedTime, &b_phoSeedTime);
   fChain->SetBranchAddress("phoSeedDetId1", phoSeedDetId1, &b_phoSeedDetId1);
   fChain->SetBranchAddress("phoSeedDetId2", phoSeedDetId2, &b_phoSeedDetId2);
   fChain->SetBranchAddress("phoRecoFlag", phoRecoFlag, &b_phoRecoFlag);
   fChain->SetBranchAddress("phoPos", phoPos, &b_phoPos);
   fChain->SetBranchAddress("phoSCE", phoSCE, &b_phoSCE);
   fChain->SetBranchAddress("phoSCRawE", phoSCRawE, &b_phoSCRawE);
   fChain->SetBranchAddress("phoESEn", phoESEn, &b_phoESEn);
   fChain->SetBranchAddress("phoSCEt", phoSCEt, &b_phoSCEt);
   fChain->SetBranchAddress("phoSCEta", phoSCEta, &b_phoSCEta);
   fChain->SetBranchAddress("phoSCPhi", phoSCPhi, &b_phoSCPhi);
   fChain->SetBranchAddress("phoSCEtaWidth", phoSCEtaWidth, &b_phoSCEtaWidth);
   fChain->SetBranchAddress("phoSCPhiWidth", phoSCPhiWidth, &b_phoSCPhiWidth);
   fChain->SetBranchAddress("phoSCBrem", phoSCBrem, &b_phoSCBrem);
   fChain->SetBranchAddress("phoOverlap", phoOverlap, &b_phoOverlap);
   fChain->SetBranchAddress("phohasPixelSeed", phohasPixelSeed, &b_phohasPixelSeed);
   fChain->SetBranchAddress("PFRecoMatch", PFRecoMatch, &b_PFRecoMatch);
   fChain->SetBranchAddress("PFEleMatch", PFEleMatch, &b_PFEleMatch);
   fChain->SetBranchAddress("PFEleVeto", PFEleVeto, &b_PFEleVeto);
   fChain->SetBranchAddress("pho_hasConvPf", pho_hasConvPf, &b_pho_hasConvPf);
   fChain->SetBranchAddress("pho_hasSLConvPf", pho_hasSLConvPf, &b_pho_hasSLConvPf);
   fChain->SetBranchAddress("MustacheEin", MustacheEin, &b_MustacheEin);
   fChain->SetBranchAddress("MustacheEOut", MustacheEOut, &b_MustacheEOut);
   fChain->SetBranchAddress("MustacheEtOut", MustacheEtOut, &b_MustacheEtOut);
   fChain->SetBranchAddress("PFLowestClustE", PFLowestClustE, &b_PFLowestClustE);
   fChain->SetBranchAddress("PFClustdEta", PFClustdEta, &b_PFClustdEta);
   fChain->SetBranchAddress("PFClustdPhi", PFClustdPhi, &b_PFClustdPhi);
   fChain->SetBranchAddress("PFClustRMSPhi", PFClustRMSPhi, &b_PFClustRMSPhi);
   fChain->SetBranchAddress("PFClustRMSPhiMust", PFClustRMSPhiMust, &b_PFClustRMSPhiMust);
   fChain->SetBranchAddress("PFPreShowerE1", PFPreShowerE1, &b_PFPreShowerE1);
   fChain->SetBranchAddress("PFPreShowerE2", PFPreShowerE2, &b_PFPreShowerE2);
   fChain->SetBranchAddress("pho_pfconvVtxZ", pho_pfconvVtxZ, &b_pho_pfconvVtxZ);
   fChain->SetBranchAddress("pho_pfconvVtxZErr", pho_pfconvVtxZErr, &b_pho_pfconvVtxZErr);
   fChain->SetBranchAddress("pho_nSLConv", pho_nSLConv, &b_pho_nSLConv);
   fChain->SetBranchAddress("pho_pfSLConvPos", pho_pfSLConvPos, &b_pho_pfSLConvPos);
   fChain->SetBranchAddress("pho_pfSLConvVtxZ", pho_pfSLConvVtxZ, &b_pho_pfSLConvVtxZ);
   fChain->SetBranchAddress("phoIsConv", phoIsConv, &b_phoIsConv);
   fChain->SetBranchAddress("phoNConv", phoNConv, &b_phoNConv);
   fChain->SetBranchAddress("phoConvInvMass", phoConvInvMass, &b_phoConvInvMass);
   fChain->SetBranchAddress("phoConvCotTheta", phoConvCotTheta, &b_phoConvCotTheta);
   fChain->SetBranchAddress("phoConvEoverP", phoConvEoverP, &b_phoConvEoverP);
   fChain->SetBranchAddress("phoConvZofPVfromTrks", phoConvZofPVfromTrks, &b_phoConvZofPVfromTrks);
   fChain->SetBranchAddress("phoConvMinDist", phoConvMinDist, &b_phoConvMinDist);
   fChain->SetBranchAddress("phoConvdPhiAtVtx", phoConvdPhiAtVtx, &b_phoConvdPhiAtVtx);
   fChain->SetBranchAddress("phoConvdPhiAtCalo", phoConvdPhiAtCalo, &b_phoConvdPhiAtCalo);
   fChain->SetBranchAddress("phoConvdEtaAtCalo", phoConvdEtaAtCalo, &b_phoConvdEtaAtCalo);
   fChain->SetBranchAddress("phoConvTrkd0", phoConvTrkd0, &b_phoConvTrkd0);
   fChain->SetBranchAddress("phoConvTrkPin", phoConvTrkPin, &b_phoConvTrkPin);
   fChain->SetBranchAddress("phoConvTrkPout", phoConvTrkPout, &b_phoConvTrkPout);
   fChain->SetBranchAddress("phoConvTrkdz", phoConvTrkdz, &b_phoConvTrkdz);
   fChain->SetBranchAddress("phoConvTrkdzErr", phoConvTrkdzErr, &b_phoConvTrkdzErr);
   fChain->SetBranchAddress("phoConvChi2", phoConvChi2, &b_phoConvChi2);
   fChain->SetBranchAddress("phoConvChi2Prob", phoConvChi2Prob, &b_phoConvChi2Prob);
   fChain->SetBranchAddress("phoConvNTrks", phoConvNTrks, &b_phoConvNTrks);
   fChain->SetBranchAddress("phoConvCharge", phoConvCharge, &b_phoConvCharge);
   fChain->SetBranchAddress("phoConvValidVtx", phoConvValidVtx, &b_phoConvValidVtx);
   fChain->SetBranchAddress("phoConvLikeLihood", phoConvLikeLihood, &b_phoConvLikeLihood);
   fChain->SetBranchAddress("phoConvP4", phoConvP4, &b_phoConvP4);
   fChain->SetBranchAddress("phoConvVtx", phoConvVtx, &b_phoConvVtx);
   fChain->SetBranchAddress("phoConvVtxErr", phoConvVtxErr, &b_phoConvVtxErr);
   fChain->SetBranchAddress("phoConvPairMomentum", phoConvPairMomentum, &b_phoConvPairMomentum);
   fChain->SetBranchAddress("phoConvRefittedMomentum", phoConvRefittedMomentum, &b_phoConvRefittedMomentum);
   fChain->SetBranchAddress("phoESEffSigmaRR", phoESEffSigmaRR, &b_phoESEffSigmaRR);
   fChain->SetBranchAddress("nMu", &nMu, &b_nMu);
   fChain->SetBranchAddress("muTrg", muTrg, &b_muTrg);
   fChain->SetBranchAddress("muEta", muEta, &b_muEta);
   fChain->SetBranchAddress("muPhi", muPhi, &b_muPhi);
   fChain->SetBranchAddress("muCharge", muCharge, &b_muCharge);
   fChain->SetBranchAddress("muPt", muPt, &b_muPt);
   fChain->SetBranchAddress("muPz", muPz, &b_muPz);
   fChain->SetBranchAddress("muIsoTrk", muIsoTrk, &b_muIsoTrk);
   fChain->SetBranchAddress("muIsoCalo", muIsoCalo, &b_muIsoCalo);
   fChain->SetBranchAddress("muIsoEcal", muIsoEcal, &b_muIsoEcal);
   fChain->SetBranchAddress("muIsoHcal", muIsoHcal, &b_muIsoHcal);
   fChain->SetBranchAddress("muChi2NDF", muChi2NDF, &b_muChi2NDF);
   fChain->SetBranchAddress("muInnerChi2NDF", muInnerChi2NDF, &b_muInnerChi2NDF);
   fChain->SetBranchAddress("muPFIsoR04_CH", muPFIsoR04_CH, &b_muPFIsoR04_CH);
   fChain->SetBranchAddress("muPFIsoR04_NH", muPFIsoR04_NH, &b_muPFIsoR04_NH);
   fChain->SetBranchAddress("muPFIsoR04_Pho", muPFIsoR04_Pho, &b_muPFIsoR04_Pho);
   fChain->SetBranchAddress("muPFIsoR04_PU", muPFIsoR04_PU, &b_muPFIsoR04_PU);
   fChain->SetBranchAddress("muPFIsoR04_CPart", muPFIsoR04_CPart, &b_muPFIsoR04_CPart);
   fChain->SetBranchAddress("muPFIsoR04_NHHT", muPFIsoR04_NHHT, &b_muPFIsoR04_NHHT);
   fChain->SetBranchAddress("muPFIsoR04_PhoHT", muPFIsoR04_PhoHT, &b_muPFIsoR04_PhoHT);
   fChain->SetBranchAddress("muPFIsoR03_CH", muPFIsoR03_CH, &b_muPFIsoR03_CH);
   fChain->SetBranchAddress("muPFIsoR03_NH", muPFIsoR03_NH, &b_muPFIsoR03_NH);
   fChain->SetBranchAddress("muPFIsoR03_Pho", muPFIsoR03_Pho, &b_muPFIsoR03_Pho);
   fChain->SetBranchAddress("muPFIsoR03_PU", muPFIsoR03_PU, &b_muPFIsoR03_PU);
   fChain->SetBranchAddress("muPFIsoR03_CPart", muPFIsoR03_CPart, &b_muPFIsoR03_CPart);
   fChain->SetBranchAddress("muPFIsoR03_NHHT", muPFIsoR03_NHHT, &b_muPFIsoR03_NHHT);
   fChain->SetBranchAddress("muPFIsoR03_PhoHT", muPFIsoR03_PhoHT, &b_muPFIsoR03_PhoHT);
   fChain->SetBranchAddress("muType", muType, &b_muType);
   fChain->SetBranchAddress("muID", muID, &b_muID);
   fChain->SetBranchAddress("muD0", muD0, &b_muD0);
   fChain->SetBranchAddress("muDz", muDz, &b_muDz);
   fChain->SetBranchAddress("muD0Vtx", muD0Vtx, &b_muD0Vtx);
   fChain->SetBranchAddress("muDzVtx", muDzVtx, &b_muDzVtx);
   fChain->SetBranchAddress("muInnerD0", muInnerD0, &b_muInnerD0);
   fChain->SetBranchAddress("muInnerDz", muInnerDz, &b_muInnerDz);
   fChain->SetBranchAddress("muNumberOfValidTrkLayers", muNumberOfValidTrkLayers, &b_muNumberOfValidTrkLayers);
   fChain->SetBranchAddress("muNumberOfValidTrkHits", muNumberOfValidTrkHits, &b_muNumberOfValidTrkHits);
   fChain->SetBranchAddress("muNumberOfValidPixelLayers", muNumberOfValidPixelLayers, &b_muNumberOfValidPixelLayers);
   fChain->SetBranchAddress("muNumberOfValidPixelHits", muNumberOfValidPixelHits, &b_muNumberOfValidPixelHits);
   fChain->SetBranchAddress("muNumberOfValidMuonHits", muNumberOfValidMuonHits, &b_muNumberOfValidMuonHits);
   fChain->SetBranchAddress("muStations", muStations, &b_muStations);
   fChain->SetBranchAddress("muChambers", muChambers, &b_muChambers);
   fChain->SetBranchAddress("nPFPho_", &nPFPho_, &b_nPFPho_);
   fChain->SetBranchAddress("PFPhoE_", PFPhoE_, &b_PFPhoE_);
   fChain->SetBranchAddress("PFPhoEt_", PFPhoEt_, &b_PFPhoEt_);
   fChain->SetBranchAddress("PFPhoEta_", PFPhoEta_, &b_PFPhoEta_);
   fChain->SetBranchAddress("PFPhoPhi_", PFPhoPhi_, &b_PFPhoPhi_);
   fChain->SetBranchAddress("PFPhoHoverE_", PFPhoHoverE_, &b_PFPhoHoverE_);
   fChain->SetBranchAddress("PFPhoSCPos_", PFPhoSCPos_, &b_PFPhoSCPos_);
   fChain->SetBranchAddress("PFPhoSCEta_", PFPhoSCEta_, &b_PFPhoSCEta_);
   fChain->SetBranchAddress("PFPhoSCPhi_", PFPhoSCPhi_, &b_PFPhoSCPhi_);
   fChain->SetBranchAddress("nPFEle_", &nPFEle_, &b_nPFEle_);
   fChain->SetBranchAddress("PFElePt_", PFElePt_, &b_PFElePt_);
   fChain->SetBranchAddress("PFEleEta_", PFEleEta_, &b_PFEleEta_);
   fChain->SetBranchAddress("PFElePhi_", PFElePhi_, &b_PFElePhi_);
   fChain->SetBranchAddress("PFEleEn_", PFEleEn_, &b_PFEleEn_);
   fChain->SetBranchAddress("PFEleCharge", PFEleCharge, &b_PFEleCharge);
   fChain->SetBranchAddress("rho25", &rho25, &b_rho25);
   fChain->SetBranchAddress("rho25_neu", &rho25_neu, &b_rho25_neu);
   fChain->SetBranchAddress("rho25_muPFiso", &rho25_muPFiso, &b_rho25_muPFiso);
   fChain->SetBranchAddress("rho25_elePFiso", &rho25_elePFiso, &b_rho25_elePFiso);
   fChain->SetBranchAddress("rho2011", &rho2011, &b_rho2011);
   fChain->SetBranchAddress("rho2012", &rho2012, &b_rho2012);
   fChain->SetBranchAddress("nJet", &nJet, &b_nJet);
   fChain->SetBranchAddress("jetTrg", jetTrg, &b_jetTrg);
   fChain->SetBranchAddress("jetEn", jetEn, &b_jetEn);
   fChain->SetBranchAddress("jetPt", jetPt, &b_jetPt);
   fChain->SetBranchAddress("jetEta", jetEta, &b_jetEta);
   fChain->SetBranchAddress("jetPhi", jetPhi, &b_jetPhi);
   fChain->SetBranchAddress("jetCharge", jetCharge, &b_jetCharge);
   fChain->SetBranchAddress("jetEt", jetEt, &b_jetEt);
   fChain->SetBranchAddress("jetRawPt", jetRawPt, &b_jetRawPt);
   fChain->SetBranchAddress("jetRawEn", jetRawEn, &b_jetRawEn);
   fChain->SetBranchAddress("jetArea", jetArea, &b_jetArea);
   fChain->SetBranchAddress("jetCHF", jetCHF, &b_jetCHF);
   fChain->SetBranchAddress("jetNHF", jetNHF, &b_jetNHF);
   fChain->SetBranchAddress("jetCEF", jetCEF, &b_jetCEF);
   fChain->SetBranchAddress("jetNEF", jetNEF, &b_jetNEF);
   fChain->SetBranchAddress("jetNCH", jetNCH, &b_jetNCH);
   fChain->SetBranchAddress("jetHFHAE", jetHFHAE, &b_jetHFHAE);
   fChain->SetBranchAddress("jetHFEME", jetHFEME, &b_jetHFEME);
   fChain->SetBranchAddress("jetNConstituents", jetNConstituents, &b_jetNConstituents);
   fChain->SetBranchAddress("jetCombinedSecondaryVtxBJetTags", jetCombinedSecondaryVtxBJetTags, &b_jetCombinedSecondaryVtxBJetTags);
   fChain->SetBranchAddress("jetCombinedSecondaryVtxMVABJetTags", jetCombinedSecondaryVtxMVABJetTags, &b_jetCombinedSecondaryVtxMVABJetTags);
   fChain->SetBranchAddress("jetJetProbabilityBJetTags", jetJetProbabilityBJetTags, &b_jetJetProbabilityBJetTags);
   fChain->SetBranchAddress("jetJetBProbabilityBJetTags", jetJetBProbabilityBJetTags, &b_jetJetBProbabilityBJetTags);
   fChain->SetBranchAddress("jetTrackCountingHighPurBJetTags", jetTrackCountingHighPurBJetTags, &b_jetTrackCountingHighPurBJetTags);
   fChain->SetBranchAddress("jetBetaStar", jetBetaStar, &b_jetBetaStar);
   fChain->SetBranchAddress("jetPFLooseId", jetPFLooseId, &b_jetPFLooseId);
   fChain->SetBranchAddress("jetDRMean", jetDRMean, &b_jetDRMean);
   fChain->SetBranchAddress("jetDR2Mean", jetDR2Mean, &b_jetDR2Mean);
   fChain->SetBranchAddress("jetDZ", jetDZ, &b_jetDZ);
   fChain->SetBranchAddress("jetFrac01", jetFrac01, &b_jetFrac01);
   fChain->SetBranchAddress("jetFrac02", jetFrac02, &b_jetFrac02);
   fChain->SetBranchAddress("jetFrac03", jetFrac03, &b_jetFrac03);
   fChain->SetBranchAddress("jetFrac04", jetFrac04, &b_jetFrac04);
   fChain->SetBranchAddress("jetFrac05", jetFrac05, &b_jetFrac05);
   fChain->SetBranchAddress("jetFrac06", jetFrac06, &b_jetFrac06);
   fChain->SetBranchAddress("jetFrac07", jetFrac07, &b_jetFrac07);
   fChain->SetBranchAddress("jetBeta", jetBeta, &b_jetBeta);
   fChain->SetBranchAddress("jetBetaStarCMG", jetBetaStarCMG, &b_jetBetaStarCMG);
   fChain->SetBranchAddress("jetBetaStarClassic", jetBetaStarClassic, &b_jetBetaStarClassic);
   fChain->SetBranchAddress("jetBetaExt", jetBetaExt, &b_jetBetaExt);
   fChain->SetBranchAddress("jetBetaStarCMGExt", jetBetaStarCMGExt, &b_jetBetaStarCMGExt);
   fChain->SetBranchAddress("jetBetaStarClassicExt", jetBetaStarClassicExt, &b_jetBetaStarClassicExt);
   fChain->SetBranchAddress("jetNNeutrals", jetNNeutrals, &b_jetNNeutrals);
   fChain->SetBranchAddress("jetNCharged", jetNCharged, &b_jetNCharged);
   fChain->SetBranchAddress("jetMVAs", jetMVAs, &b_jetMVAs);
   fChain->SetBranchAddress("jetWPLevels", jetWPLevels, &b_jetWPLevels);
   fChain->SetBranchAddress("jetMVAsExt", jetMVAsExt, &b_jetMVAsExt);
   fChain->SetBranchAddress("jetWPLevelsExt", jetWPLevelsExt, &b_jetWPLevelsExt);
   fChain->SetBranchAddress("nLowPtJet", &nLowPtJet, &b_nLowPtJet);
   fChain->SetBranchAddress("jetLowPtEn", jetLowPtEn, &b_jetLowPtEn);
   fChain->SetBranchAddress("jetLowPtPt", jetLowPtPt, &b_jetLowPtPt);
   fChain->SetBranchAddress("jetLowPtEta", jetLowPtEta, &b_jetLowPtEta);
   fChain->SetBranchAddress("jetLowPtPhi", jetLowPtPhi, &b_jetLowPtPhi);
   fChain->SetBranchAddress("jetLowPtCharge", jetLowPtCharge, &b_jetLowPtCharge);
   fChain->SetBranchAddress("jetLowPtEt", jetLowPtEt, &b_jetLowPtEt);
   fChain->SetBranchAddress("jetLowPtRawPt", jetLowPtRawPt, &b_jetLowPtRawPt);
   fChain->SetBranchAddress("jetLowPtRawEn", jetLowPtRawEn, &b_jetLowPtRawEn);
   fChain->SetBranchAddress("jetLowPtArea", jetLowPtArea, &b_jetLowPtArea);
   fChain->SetBranchAddress("nConv", &nConv, &b_nConv);
   fChain->SetBranchAddress("convP4", convP4, &b_convP4);
   fChain->SetBranchAddress("convVtx", convVtx, &b_convVtx);
   fChain->SetBranchAddress("convVtxErr", convVtxErr, &b_convVtxErr);
   fChain->SetBranchAddress("convPairMomentum", convPairMomentum, &b_convPairMomentum);
   fChain->SetBranchAddress("convRefittedMomentum", convRefittedMomentum, &b_convRefittedMomentum);
   fChain->SetBranchAddress("convNTracks", convNTracks, &b_convNTracks);
   fChain->SetBranchAddress("convPairInvMass", convPairInvMass, &b_convPairInvMass);
   fChain->SetBranchAddress("convPairCotThetaSep", convPairCotThetaSep, &b_convPairCotThetaSep);
   fChain->SetBranchAddress("convEoverP", convEoverP, &b_convEoverP);
   fChain->SetBranchAddress("convDistOfMinApproach", convDistOfMinApproach, &b_convDistOfMinApproach);
   fChain->SetBranchAddress("convDPhiTrksAtVtx", convDPhiTrksAtVtx, &b_convDPhiTrksAtVtx);
   fChain->SetBranchAddress("convDPhiTrksAtEcal", convDPhiTrksAtEcal, &b_convDPhiTrksAtEcal);
   fChain->SetBranchAddress("convDEtaTrksAtEcal", convDEtaTrksAtEcal, &b_convDEtaTrksAtEcal);
   fChain->SetBranchAddress("convDxy", convDxy, &b_convDxy);
   fChain->SetBranchAddress("convDz", convDz, &b_convDz);
   fChain->SetBranchAddress("convLxy", convLxy, &b_convLxy);
   fChain->SetBranchAddress("convLz", convLz, &b_convLz);
   fChain->SetBranchAddress("convZofPrimVtxFromTrks", convZofPrimVtxFromTrks, &b_convZofPrimVtxFromTrks);
   fChain->SetBranchAddress("convNHitsBeforeVtx", convNHitsBeforeVtx, &b_convNHitsBeforeVtx);
   fChain->SetBranchAddress("convNSharedHits", convNSharedHits, &b_convNSharedHits);
   fChain->SetBranchAddress("convValidVtx", convValidVtx, &b_convValidVtx);
   fChain->SetBranchAddress("convMVALikelihood", convMVALikelihood, &b_convMVALikelihood);
   fChain->SetBranchAddress("convChi2", convChi2, &b_convChi2);
   fChain->SetBranchAddress("convChi2Probability", convChi2Probability, &b_convChi2Probability);
   fChain->SetBranchAddress("convTk1Dz", convTk1Dz, &b_convTk1Dz);
   fChain->SetBranchAddress("convTk2Dz", convTk2Dz, &b_convTk2Dz);
   fChain->SetBranchAddress("convTk1DzErr", convTk1DzErr, &b_convTk1DzErr);
   fChain->SetBranchAddress("convTk2DzErr", convTk2DzErr, &b_convTk2DzErr);
   fChain->SetBranchAddress("convCh1Ch2", convCh1Ch2, &b_convCh1Ch2);
   fChain->SetBranchAddress("convTk1D0", convTk1D0, &b_convTk1D0);
   fChain->SetBranchAddress("convTk1Pout", convTk1Pout, &b_convTk1Pout);
   fChain->SetBranchAddress("convTk1Pin", convTk1Pin, &b_convTk1Pin);
   fChain->SetBranchAddress("convTk2D0", convTk2D0, &b_convTk2D0);
   fChain->SetBranchAddress("convTk2Pout", convTk2Pout, &b_convTk2Pout);
   fChain->SetBranchAddress("convTk2Pin", convTk2Pin, &b_convTk2Pin);
   Notify();
}

Bool_t ana_job_2photon_2012b_PRv1_skim::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ana_job_2photon_2012b_PRv1_skim::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ana_job_2photon_2012b_PRv1_skim::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ana_job_2photon_2012b_PRv1_skim_cxx
