#!/usr/bin/env/python
import os,sys,string
from decimal import *

"""
sucks in a file full of lines such as 
#185 5050 150    261 68387 8.469D-11 264 374751 4.644D-10
#(0   1    2      3    4    5         6  7         8      index numbers)
and makes a line to go in MCpoint.h:
        MCpoints.push_back(new MCpoint(2010,5050,575,5,7.601000E-18,2,type2filedir));

words 0,1,2 are obviously masses. 
[3] and [6] are process names: 261= qq_bar goes to stop pair, 264 = gluglu to stops
[4] and [7] are the numbers generated
[5] and [8] are the cross sections in milli-barns

we'll add [4] and [7] to get our nGen
we'll add [5] and [8] to get our xsec

The input data came from Dave Mason's email on May 1, 2013
the output was installed into MCpoint_noHiggsino.h
"""

dmason = sys.argv[1]
dmfile = open(dmason,'r')
fout = open("dmout.txt",'w')
for line in dmfile.readlines():
	words = line.strip().split()
	if len(words)!=9:
		print "warning, rx line: ",line
		continue
	words[5] = string.replace(words[5],'D','E')
	words[8] = string.replace(words[8],'D','E')
	fout.write("        MCpoints.push_back(new MCpoint(%s,%s,%s,%i,%E,2,type2filedir));\n"%(words[0],words[1],words[2],int(words[4])+int(words[7]),Decimal(words[5]) + Decimal(words[8])   ))



