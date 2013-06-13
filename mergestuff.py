#!/usr/bin/env python
import os,sys
import string


fn1 = sys.argv[1]
fn2 = sys.argv[2]# the cross sections
F1 = open(fn1,'r')
F2 = open(fn2,'r')

code = []
cs = []
for line in F2.readlines():
    words = line.split()
    if len(words) < 2:
        break
    code.append(words[0].strip())
    cs.append(words[1].strip())

points = []
for line in F1.readlines():
    points.append(line.strip())

print len(points)
print len(code),len(cs)

for icode, ics in zip(code,cs):
    #print icode, ics
    for point in points:
        #print point
        if string.find(point,icode) != -1:
             print string.replace(point,"crossection",ics )
             break
