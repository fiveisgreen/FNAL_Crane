#!/usr/bin/env python
import os,sys
import string

"""
This script compares events lists stored in two text files. 
Syntax: 
./CompareEventLists.py first_event_list.txt second_event_list.txt
It returns three text files: 
"inCommon.txt", "firstOnly.txt", "secondOnly.txt". 
It expects the lists to be in the format 
[run] [lumi] [event]
with one entry per line and no extra text. 
"""
if(len(sys.argv)!=3):
	print "Syntax:"
	print "./CompareEventLists.py first_event_list.txt second_event_list.txt"
	sys.exit()

f1name = sys.argv[1].strip()
f2name = sys.argv[2].strip()

f1 = open(f1name,'r')
f2 = open(f2name,'r')

f1lines = f1.readlines()

common = open("inCommon.txt",'w')
f1_only = open("firstOnly.txt",'w')
f2_only = open("secondOnly.txt",'w')

i_first_total = 0
i_second_total = 0
i_first_only = 0
i_second_only = 0
i_common = 0

print "List2 only"
i_first_total = len(f1lines)
for line2 in f2.readlines():
	i_second_total+=1
	line2 = line2.strip()
	foundMatch = False
	for line1 in f1lines:
		line1b = line1.strip()
#		print "is %s in %s?"%(line1b,line2)
		if line1b in line2:
			common.write(line2+'\n')
			i_common+=1
			f1lines.remove(line1)
			foundMatch = True
	if not foundMatch:
		f2_only.write(line2+'\n')
		print line2
		i_second_only+=1
			
print "\n\nList1 only"
for line in f1lines:
	i_first_only+=1
	line = line.strip()
	f1_only.write(line+'\n')
	print line

common.close()
f1_only.close()
f2_only.close()
f1.close()
f2.close()

print "*****Summary****"
print "%s Total: %i. %s Total: %i"%(f1name,i_first_total,f2name,i_second_total)
print "Common:",i_common
print f1name+" only ",i_first_only
print f2name+" only ",i_second_total














