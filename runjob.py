#! /usr/bin/env python
import os,sys
import string
import ROOT
from ROOT import gROOT, TCanvas, TH1F, TFile

print "hello world"
gROOT.Reset('a')

gROOT.ProcessLine(".L ana_job_2photon_2012b_PRv1_skim.C+")
gROOT.ProcessLine("ana_job_2photon_2012b_PRv1_skim f")
gROOT.ProcessLine("f.Loop()")
