#!/usr/bin/env python
import fileinput

myhead=""
myseq=""
for l in fileinput.input():
    l = l.rstrip('\n')
    if l[0]==">":
        if len(myhead) > 0:
            print myhead + "\t" + myseq
        myhead = l
        myseq = ""
    else:
        myseq = myseq + l

if len(myhead) > 0:
    print myhead + "\t" + myseq
