#!/usr/bin/env python

import sys
import re

args=sys.argv[1:]
pattern = args[0]
inconn = open(args[1],"r")

reg = re.compile(pattern)

for e in enumerate(inconn):
    i=e[0]
    l=e[1].strip('\n')
    sl=l.split('\t')
    if i<=0:
        goodcols = []
        for j in xrange(len(sl)):
            if bool(re.search(reg,sl[j])):
                goodcols.append(j)
    print "\t".join([sl[x] for x in goodcols])

