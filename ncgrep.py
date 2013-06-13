#! /usr/bin/env python
import os,sys
import string

"""Same as grep, but excludes lines that are
obviously commented out. If a line is inside long comments
but does not contain a comment mark it will be listed"""

if len(sys.argv) <=1:
        sys.exit()

def figure(file,rest,line):
	if (".cpp" in file) or \
		(".C" in file) or \
		(".h" in file) or \
		(".c" in file) or \
		(".CPP" in file):
		if not("/*" in rest or "*/" in rest or rest.startswith("//")):
			print line
	elif ".py" in file:
		if not('"""' in rest or rest.startswith("#")):
			print line
	else:
		if not(rest.startswith("#")):
			print line
	
instring = "grep"
for arg in sys.argv[1:]:
	instring = instring + ' ' + arg
instring = instring.strip()	

def isfile(path):
	return os.path.exists(path) and not os.path.isdir(path)

type = 0
adj = 0
if sys.argv[1].strip().startswith("-"):
	adj = 1
	
if len(sys.argv)==3+adj and \
	isfile(sys.argv[2+adj].strip()) and \
	not "*" in sys.argv[2+adj]:
	type = 1+adj
	

if type == 0:
	for line in os.popen(instring).readlines():
		line = line.rstrip()
		colon = line.find(':')
		if colon >= 0:
			file = line[0:colon]
			rest = line[colon+1:].strip()
			figure(file,rest,line.rstrip())
		else:
			print line
elif type == 1:
	for line in os.popen(instring).readlines():
			figure(sys.argv[2].strip(),line.strip(),line.rstrip())
elif type == 2:
	for line in os.popen(instring).readlines():
			figure(sys.argv[3].strip(),line.strip(),line.rstrip())
	

