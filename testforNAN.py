import os,sys
import string
import math

fin = open("tmva_bkg_data.txt")
#fin = open("tmva_signal_MC.txt")
ln = 1
avg = [0]*33
getfirst = True
head = ""
for line in fin.readlines():
    if getfirst: 
	head = line
	getfirst = False
	continue
    words = line.split(' ')
    ln+=1
    iword = 0;
    for word in words:
	#if(word.isdigit()):
	word = word.strip()
	try:
    		f = float(word)
                if(math.isnan(f) or math.isinf(f)):
			print ""
			print "line %i"%(ln)
                        print "recieved nan "+word+" in line \n"+line
		else:
			#print f+1
			avg[iword]+=f
			iword+=1	
	except (ValueError, IndexError):
		print ""
		print "line %i"%(ln), "exception"
		print "recieved "+word+" in line \n"+line 

for i in range(33):
	avg[i]/=ln
print "Averages"
#print avg
heads = head.split(':')
for i in range(33):
	print heads[i].strip('/\IF'), avg[i]
