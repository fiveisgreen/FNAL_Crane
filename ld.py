#!/usr/bin/env python   
import os,sys,string,re

"""
This lists directories. 
You can do 
ls
ls -whatever_options
ls *some*dirs*
ls -ltrbtq my*dirs
"""

list_command = "ls"
list_options = ""
#specifier = ""
options_provided = False
#specifier_provided = False
if len(sys.argv) == 1:	#ld
	pass
elif len(sys.argv) == 2:
	if sys.argv[1].strip()[0] is '-':	#there's an option #ld -ltr
		options_provided = True
		list_options = sys.argv[1].strip()
		
		if len(sys.argv) > 2:	#ld -ltr mystuff -->Forbidden
			print "you can do ld and ld -options"	
			sys.exit()
#			specifier = sys.argv[2].strip()	
#			specifier_provided = True
	else: #no options, ld *myfile* 
		print "you can do ld and ld -options"
		sys.exit()	
#		specifier = sys.argv[1].strip()
#		specifier_provided = True
else:
	print "you can do ld and ld -options"
	sys.exit()	

		
	#manipulate specifier_provided to have a usable regex in python
#if specifier_provided:
#	specifier = string.replace(specifier, '.', '\.') #. is a single char wild card, replace it with the litteral
#	specifier = '^'+specifier+'$'	#require the match to begin at the beginning and end at the end of the string.
#	specifier = string.replace(specifier, '?', '.')	#convert single char wild card
#	specifier = string.replace(specifier, '*', '[\S]*') #convert * to match any non-whitespace character.


		
if options_provided:
	list_command = list_command + ' ' + list_options #+ ' ' + specifier
#else:
#	list_command = list_command + specifier

dirs = []
for entry in os.popen("ls -la").readlines()[1:]:
	entry = entry.strip()
	if entry is "." or entry is "..": 
		continue
	words = entry.split()
	type = words[0].strip()
	if type[0] is '-':
		continue
	elif type[0] is 'd' or type[0] is 'l':
		#if specifier_provided:
		#	if re.match(specifier_provided, words[-1].strip()):	
		#		dirs.append(words[-1].strip())
		#else:
		dirs.append(words[-1].strip())
	else:
		print "I don't know what the heck this is:"
		print entry, '\n'
		
#now have a list of the directories that match the specifier if there is one. 

#option p tacks a / onto the dir, which messes with the search.
if options_provided and 'p' in list_options:
	for i,dir in enumerate(dirs):
		dirs[i] = dir + '/'

entries = []
for entry in os.popen(list_command).readlines():
	match = False
	for word in entry.strip().split():
		if word in dirs:
			match = True
			break
	if match:
		print entry.strip()
		
		
		"""
		so if you list a specifier it tries to list the contents of the directory, not just it's presence. 
		"""
		
		
