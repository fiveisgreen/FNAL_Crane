#!/usr/bin/env python
import os,sys
import string

"""
Reaches into this directory and fetches what you tell it. It can handle regular expressions in quotes. 
Examples: 
./send.py somefile.txt
./send.py "*.gif"
"""
partial = "abarker@lxplus.cern.ch:~/hggx/AN/notes/AN-13-061/trunk/"
ext = sys.argv[1]
ext = ext.strip()
full = "scp "+ ext + " "+ partial
print "running",full
os.system(full)

