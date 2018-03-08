#!/usr/bin/env python

import fileinput

for e in enumerate(fileinput.input()):
    i=e[0]
    l=e[1].rstrip('\n')
    sl=l.split('\t')
    if i<=0:
        esl = enumerate(sl[1:])
        sort_esl = sorted(esl,key=lambda x: x[1])
        sort_esl_indices = [x[0]+1 for x in sort_esl]
        final_indices = [0] + sort_esl_indices
    outlist = [sl[x] for x in final_indices]
    print "\t".join(outlist)
    
