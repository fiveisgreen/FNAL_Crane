#!/usr/bin/env python
import os,sys
import string

"""
Reaches into this directory and fetches what you tell it. It can handle regular expressions in quotes. 
Examples: 
./get.py somefile.txt
./get.py "*.gif"
"""
partial = "/uscmst1b_scratch/lpc1/3DayLifetime/abarker/CMSSW_5_3_3/src/SusyNtuplizer/macro/"
ext = sys.argv[1]
ext = ext.strip()
full = "cp "+ ext + " "+ partial 
print "running",full 
os.system(full)
