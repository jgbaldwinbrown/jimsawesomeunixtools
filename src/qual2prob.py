#!/usr/bin/env python

import fileinput

def getprobs(x):
    out = []
    xf = map(float,x)
    for i in xf:
        out.append(getprob(i))
    return out

def getprob(x):
    x=float(x)
    return(1- (float(10) ** (-float(x)/float(10))))

for l in fileinput.input():
    l=l.rstrip('\n')
    if l[0]==">":
        print l
        continue
    sl=l.split()
    problist = getprobs(sl)
    print "\t".join(map(str,problist))

def mean(l):
    return float(sum(l))/len(l) if len(l) > 0 else float('nan')
