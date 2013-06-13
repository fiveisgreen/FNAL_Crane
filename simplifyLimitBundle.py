#! /usr/bin/env python
import os,sys
import string

"""
syntax: simplifyLimitBundle.py limitbundle.txt
produces a file limitbundle_reduced.txt

takes in a big long file, limitbundle.txt, of the form 
{
garbage
garbage
************* DO COMBINE FOR topo kinvar **************
garbage
Limits on n2n1_135_8_hh_bbaa scaled to 1498.8 pb
 -- Asymptotic --
Observed Limit: r < 5.0119
Expected  2.5%: r < 1.8288
Expected 16.0%: r < 2.5127
Expected 50.0%: r < 3.6719
Expected 84.0%: r < 5.5307
Expected 97.5%: r < 8.0620
and repete
}
and returns a file, limitbundle_reduced.txt, with the form
{
2JbMLm20 
MET
5.0119
1.8288
2.5127
3.6719
5.5307
8.0620
2JbMLm20gbar1	#that is, topo 
MET		#kinvar	
6.0119
1.9288
2.6127
3.7719
5.8307
8.3620
...
}
//this sure seems to work withotu bugs. 
"""

if len(sys.argv) != 2:
    print "syntax: simplifyLimitBundle.py limitbundle.txt"
    sys.exit()
infileName = sys.argv[1]
if not os.path.exists(infileName):
    print "ERROR! cannot find file ",infileName
    sys.exit()
foutName =infileName[:-4]+"_reduced.txt" 

fout = open(foutName ,'w') #open output file fout;

mode = 0
sout1 = ""
#mode 0: search for the tag.
for line in open(infileName, 'r'):
	#in whatever mode you're in, if you see this, start going into mode 1
	if "DO COMBINE FOR" in line:
		mode = 1 #found line, look for
		words = line.split()
		if len(words) <6:
			print "Error! too few words in line",line
			continue
		topo = words[4].strip()
		kinvar = words[5].strip()
		sout1 = "%s\n%s\n"%(topo,kinvar) 			#fout.write("%s\n%s\n"%(topo,kinvar)) #don't write here, there may be no numbers following.
		continue
	if mode == 1 and "Observed Limit" in line:
		words = line.split()
		if len(line.split())<5:
			print "Error! too few words in line",line
	                continue
		mode = 2
		fout.write(sout1) #modification
		fout.write(words[4].strip() + '\n')
	elif mode == 2 and "Expected" in line and "2.5" in line:
		words = line.split()
		if len(line.split())<5:
			print "Error! too few words in line",line
	                continue
		mode = 3
		fout.write(words[4].strip() + '\n')
	elif mode == 3 and "Expected" in line and "16.0" in line:
		words = line.split()
		if len(line.split())<5:
			print "Error! too few words in line",line
	                continue
		mode = 4
		fout.write(words[4].strip() + '\n')
	elif mode == 4 and "Expected" in line and "50.0" in line:
		words = line.split()
		if len(line.split())<5:
			print "Error! too few words in line",line
	                continue
		mode = 5
		fout.write(words[4].strip() + '\n')
	elif mode == 5 and "Expected" in line and "84.0" in line:
		words = line.split()
		if len(line.split())<5:
			print "Error! too few words in line",line
	                continue
		mode = 6
		fout.write(words[4].strip() + '\n')
	elif mode == 6 and "Expected" in line and "97.5" in line:
		words = line.split()
		if len(line.split())<5:
			print "Error! too few words in line",line
	                continue
		mode = 0
		fout.write(words[4].strip() + '\n')
fout.close()
print  "made "+foutName
