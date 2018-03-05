#!/usr/bin/env python
import fileinput

for l in fileinput.input():
    l = l.rstrip('\n')
    sl = l.split('\t')
    print sl[0]
    print sl[1]
