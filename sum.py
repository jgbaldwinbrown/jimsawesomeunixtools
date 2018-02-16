#!/usr/bin/env python

import fileinput

con=fileinput.input()

sum=0.0
for l in con:
    sl=map(float,l.rstrip('\n').split())
    for x in sl:
        sum = sum + x
    [sum = sum + x for x in sl]

print sum
