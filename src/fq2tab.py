#!/usr/bin/env python
import fileinput

mydats = ["","","",""]
for i,l in enumerate(fileinput.input()):
    l = l.rstrip('\n')
    i4 = i % 4
    if not i4 == 3:
        mydats[i4] = l
    else:
        mydats[i4] = l
        print "\t".join(mydats)
