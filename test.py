#!/usr/bin/env/python
import os,sys
import math
import string
import ROOT
from ROOT import gROOT, TCanvas, TH1F, TFile

define GetBkgUC(TH1F):
	sum = 0
	for i in range(1,TH1F.GetXaxis().GetNbins()):
		sum += pow(TH1F.GetBinError(i),2)	
	return sqrt(sum)


backgrounds=   "plotsWithBackground_dataGLL12.root"

allthere = True
if not os.path.exists(backgrounds):
	print "cannot find data driven backgrounds file %s "%(backgrounds)
allthere &= os.path.exists(backgrounds)

if not allthere:
	print "Some cards not found, exiting"
	sys.exit()

bkgUC = [0.0, 0.0, 0.0, 0.0]

#fetch histograms
TFile_bkg = Open(backgrounds)
TH1F_2B_on = TFile_bkg.Get("hMET2JbML!Gbar2Mbb_bkg")
TH1F_2B_off = TFile_bkg.Get("hMET2JbML!Gbar2Mbb!_bkg")
TH1F_3B = TFile_bkg.Get("hMET3JbMLLGbar2_bkg")
#calculate the limits
bkgUC[0] = GetBkgUC(TH1F_3B)
bkgUC[1] = GetBkgUC(TH1F_2B_on)
bkgUC[2] = GetBkgUC(TH1F_2B_off)
bkgUC[3] = sqrt(bkgUC[0]*bkgUC[0] + bkgUC[1]*bkgUC[1] + bkgUC[2]*bkgUC[2]);

print "0 ", bkgUC[0]
print "1 ", bkgUC[1]
print "2 ", bkgUC[2]
print "3 ", bkgUC[3]

