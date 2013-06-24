#!/usr/bin/env/python
import os,sys
import math

nMCpoints = 3
MCstopMasses =     [200,225,250]
MChiggsinoMasses = [150,215,150]
#MCstopMasses =     [185,210,235]
#MChiggsinoMasses = [150,150,150]
#nMCpoints = 2
#MCstopMasses =     [185,235]
#MChiggsinoMasses = [150,150]


if nMCpoints <1:
	print "there are no supplied MC points, I dont' know what I'm supposed to do"
	sys.exit()
if len(MCstopMasses) != nMCpoints:
	print "MCstopMasses is the wrong length"
	sys.exit()
if len(MChiggsinoMasses) != nMCpoints:
	print "MChiggsinoMasses is the wrong length"
	sys.exit()

#bbin_cards = []
#for a,b in zip(MCstopMasses, MChiggsinoMasses):
#	bbin_cards.append( "LimitCard_mst_%i_mu_%i_bbin3_MET.txt"%(a,b) )

bbin_cards =   [ "LimitCard_st_%i_mu_%i_bbaa_bbin3_MET.txt"%(a,b)         for a,b in zip(MCstopMasses,MChiggsinoMasses) ]
simple_cards = [ "LimitCard_st_%i_mu_%i_bbaa_2JbMLgbar2_MET.txt"%(a,b) for a,b in zip(MCstopMasses,MChiggsinoMasses) ]
#bbin_cards =   [ "LimitCard_mst_%i_mu_%i_bbin3_MET.txt"%(a,b)         for a,b in zip(MCstopMasses,MChiggsinoMasses) ]
#simple_cards = [ "LimitCard_mst_%i_mu_%i_2JbMLgbar2_MET.txt"%(a,b) for a,b in zip(MCstopMasses,MChiggsinoMasses) ]

allthere = True
for card in bbin_cards:
	if not os.path.exists(card):
		print "cannot find card file %s "%(card)
	allthere &= os.path.exists(card)
for card in simple_cards:
	if not os.path.exists(card):
		print "cannot find card file %s "%(card)
	allthere &= os.path.exists(card)

if not allthere:
	print "Some cards not found, exiting"
	sys.exit()

#order: 3+ 2on 2off total
bkg = [0.0, 0.0, 0.0, 0.0]
observed = [0, 0, 0, 0]
exp = []
for i in range(nMCpoints):
	exp.append([0.0, 0.0, 0.0, 0.0])

#get simple total
for line in open(simple_cards[0],'r').readlines():
	if "observation" in line: 
		words = line.split()
		observed[3] = int(words[1])
	elif "rate" in line: 
		words = line.split()
		bkg[3] = float(words[2])

#get bined data
for line in open(bbin_cards[0],'r').readlines():
	if "observation" in line: 
		words = line.split()
		observed[1] = int(words[1])
		observed[2] = int(words[2])
		observed[0] = int(words[3])
	elif "rate" in line: 
		words = line.split()
		bkg[1] = float(words[2])
		bkg[2] = float(words[4])
		bkg[0] = float(words[6])
#get simple MC
for imc in range(nMCpoints):
	for line in open(simple_cards[imc],'r').readlines():
		if "rate" in line: 
			words = line.split()
			exp[imc][3] = float(words[1])
#get bbined MC
for imc in range(nMCpoints):
	for line in open(bbin_cards[imc],'r').readlines():
		if "rate" in line: 
			words = line.split()
			exp[imc][1] = float(words[1])
			exp[imc][2] = float(words[3])
			exp[imc][0] = float(words[5])

#print table
print ""
print "Table for M_stop = %i, M_higgsino = %i"%(MCstopMasses[imc],MChiggsinoMasses[imc])
print ""
print "\\begin{table*}[htbp]"
print "\\begin{center}"
print "\caption{Expected and observed event counts \label{tab_observed}}"
print "\\begin{tabular}{|c|c|c|c||c|}"
print "\hline \hine"
print "    & $3+~b$-jets & on $h$ mass & off $h$ mass & total \\\\"
print "\hline"
for imc in range(nMCpoints):
	print "signal %i / %i GeV & %.1f & %.1f & %.1f & %.1f \\\\"%(MCstopMasses[imc],MChiggsinoMasses[imc],exp[imc][0],exp[imc][1],exp[imc][2],exp[imc][3])
#print "signal 235 / 150 GeV & 8.5  & 6.8 & 7.6 & 22.9 \\\\"
#print "signal 210 / 150 GeV & 9.8  & 7.9 & 9.5 & 27.2 \\\\"
#print "signal 185 / 150 GeV & 12.7 &10.6 &12.4 & 35.7\\\\"
print "\hline"
print "expected BG & %.1f & %.1f & %.1f & %.1f\\\\"%(bkg[0],bkg[1],bkg[2],bkg[3])
print "\hline \hline"
print "observed   & %i & %i & %i & %i\\\\"%(observed[0],observed[1],observed[2],observed[3])
print "\hline \hline"
print "\end{tabular}"
print "\end{center}"
print "\end{table*}"
print ""
print ""

#check that everything makes sense, yell if it doesn't 
sumbkg = bkg[0]+bkg[1]+bkg[2] 
if abs(sumbkg-bkg[3]) > 0.15:
	print "WARNING!! bkg does not add up! Total %s vs supposed sum %f"%(sumbkg,bkg[3])
if observed[0]+observed[1]+observed[2] != observed[3]:
	print "WARNING!! observed does not add up! Total %s vs supposed sum %f"%(observed[0]+observed[1]+observed[2],observed[3])
for imc in range(nMCpoints):
	mcsum = exp[imc][0] + exp[imc][1]+exp[imc][2]
	if abs(mcsum-exp[imc][3]) > 0.15:
		print "WARNING!! mc %i / %i does not add up! Total %s vs supposed sum %f"%(MCstopMasses[imc],MChiggsinoMasses[imc],mcsum,exp[imc][3])
for ibin in range(0,4):
	if bkg[ibin] > 0 and abs(observed[ibin] - bkg[ibin]) > math.sqrt(bkg[ibin])*1.5:
		if ibin is 3:
			print "WARNING!! Data sum and bkg sum differ by a surprising amount. Look Closely"
		else:
			print "WARNING!! Data and bkg %i differ by a surprising amount. Look Closely"%(ibin+1)
