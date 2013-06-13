#! /usr/bin/env python
import os,sys
import string

"""
syntax: 
./Shuffel.py [File A] [File B]

prints 
Aline1
Bline1
Aline2
Bline2
Aline3
Bline3
and so on.
	once one file runs out of lines it just prints the rest of the second file. 
"""


#check inputs
if(len(sys.argv) != 3):
	print "syntax is"
	print "./Shuffel.py [File A] [File B]"
	sys.exit()

fileNameA= sys.argv[1]
fileNameB= sys.argv[2]

#check that those exist
if not os.path.exists(fileNameA):
	print "cannot find file", fileNameA
	sys.exit()
if not os.path.exists(fileNameB):
	print "cannot find file", fileNameB
	sys.exit()

#make and open new jdl file
linesA = open(fileNameA,'r').readlines()
linesB = open(fileNameB,'r').readlines()

i = 0
lenA = len(linesA)
lenB = len(linesB)
while i<lenA and i<lenB:
	print linesA[i].strip()
	print linesB[i].strip()
	i+= 1
if i>= lenA:
	while i<len(linesB):
		print linesB[i].strip()
		i+= 1
elif i>= lenB:
	while i<len(linesA):
		print linesA[i].strip()
		i+= 1

