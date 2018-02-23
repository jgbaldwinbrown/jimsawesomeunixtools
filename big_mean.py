#!/usr/bin/env python

import fileinput

def sum(l):
    return float(sum(l))

def mean(l):
    return float(sum(l))/len(l) if len(l) > 0 else float('nan')

bigsum=0
bigcount=0
for l in fileinput.input():
    l=l.rstrip('\n')
    if l[0]==">":
        print l
        continue
    sl=l.split()
    linesum = sum(map(float,sl))
    linecount = len(sl)
    bigsum += linesum
    bigcount += linecount
    print str(float(bigsum) / float(bigcount))
