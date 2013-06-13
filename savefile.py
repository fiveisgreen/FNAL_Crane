#!/usr/bin/env python
import os,sys
import string
import time

filestr = sys.argv[1]
print "try to save "+filestr+" to dcache"
save_str = 'srmcp "file://///////uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/%s" "srm://cmssrm.fnal.gov:8443/resilient/abarker/SusyLooseSkim_53X_2012_bf2/%s"'%(filestr,filestr)
#print save_str
os.system(save_str)
#time.sleep(1)

