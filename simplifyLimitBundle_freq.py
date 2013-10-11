#! /usr/bin/env python
import os,sys
import string

"""
syntax: simplifyLimitBundle.py limitbundle.txt
produces a file limitbundle_reduced.txt

an input limit bundle such as LimitResult_freq_st_350_mu_225_bbaa_bbin3_MET.txt

takes in a big long file, limitbundle.txt, of the form 
{
garbage
Limit: r < 0.079 +/- 0.0162 @ 95% CL
garbage
Limit: r < 0.079 +/- 0.0162 @ 95% CL
garbage
Limit: r < 0.079 +/- 0.0162 @ 95% CL
garbage
Limit: r < 0.079 +/- 0.0162 @ 95% CL
garbage
Limit: r < 0.079 +/- 0.0162 @ 95% CL
garbage
Limit: r < 0.079 +/- 0.0162 @ 95% CL
garbage
}
and returns a file, limitbundle_reduced.txt, with the form
{
bbin3
MET
5.0119
1.8288
2.5127
3.6719
5.5307
8.0620
}
"""

if len(sys.argv) != 2:
    print "syntax: simplifyLimitBundle.py limitbundle.txt"
    sys.exit()
infileName = sys.argv[1]
if not os.path.exists(infileName):
    print "ERROR! cannot find file ",infileName
    sys.exit()
#foutName =infileName[:-4]+"_reduced.txt" 
#LimitResult_freq_st_350_mu_225_bbaa_bbin3_MET.txt -> LimitResultBundle_st_500_mu_150_bbaa_reduced.txt
foutName ="LimitResultBundle_"+infileName[17:30]+"_bbaa_reduced.txt"


nfound = 0
rvals = []
armed = True
for line in open(infileName, 'r'):
	if "Limit" in line and armed:
		words = line.split()
		#Limit: r < 0.079 +/- 0.0162 @ 95% CL
		rvals.append( words[3] )
		#fout.write(words[3]+'\n')
		nfound += 1
	if "before fit" in line: #then skip the next line
		armed = False
	else:
		armed = True
	if nfound >= 6:
		break
		
if(nfound == 6):
	fout = open(foutName ,'w') #open output file fout;
	fout.write("bbin3\n")
	fout.write("MET\n")
	for rval in rvals:
		fout.write(rval+'\n')
	fout.close()
	print  "made "+foutName
else:
	print "Error! Found %i Limits instead of 6!"%(nfound)

