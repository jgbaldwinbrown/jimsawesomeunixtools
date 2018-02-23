#!/usr/bin/env python

import fileinput

def mean(l):
    return float(sum(l))/len(l) if len(l) > 0 else float('nan')

for l in fileinput.input():
    l=l.rstrip('\n')
    if l[0]==">":
        print l
        continue
    sl=l.split()
    linemean = mean(map(float,sl))
    print str(linemean)
