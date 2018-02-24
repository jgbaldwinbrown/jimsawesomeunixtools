#!/usr/bin/env python

import fileinput
import math

def getprobs(x):
    out = []
    xf = map(float,x)
    for i in xf:
        out.append(getprob(i))
    return out

def getprob(x):
    x=float(x)
    return(1- (float(10) ** (-float(x)/float(10))))

def n50_stats(x,halftot):
    templen=0
    numconts=0
    for i in x:
        templen=templen+i
        numconts=numconts+1
        if templen >= halftot:
            n50=i
            break
    return([i,templen,numconts])

def get_n50(n50_stats):
    return(n50_stats[0])

def get_bp_in_n50(n50_stats):
    return(n50_stats[1])

def get_l50(n50_stats):
    return(n50_stats[2])

def mean(l):
    return float(sum(l))/len(l) if len(l) > 0 else float('nan')

header=""
seq=""
all_lengths=[]

header=""
phreds=[]
linemeansum=0
cumsum=0
for entry in enumerate(fileinput.input()):
    index=entry[0]
    line=entry[1].rstrip('\n')
    if line[0]==">":
        if len(header) > 0 and len(phreds) > 0:
            all_lengths.append(len(phreds))
            probs = getprobs(phreds)
            linemeansum += mean(probs)
            cumsum += sum(probs)
        header=line
        phreds=[]
    else:
        phreds.extend(map(int,line.split()))
if len(header) > 0 and len(phreds) > 0:
    all_lengths.append(len(phreds))
    probs = getprobs(phreds)
    linemeansum += mean(probs)
    cumsum += sum(probs)

totbp=sum(all_lengths)
halftot=int(math.ceil(float(totbp)/2.0))
revsort_lengths=sorted(all_lengths,reverse=True)

stats=n50_stats(revsort_lengths,halftot)
n50=get_n50(stats)
l50=get_l50(stats)
bp_in_n50=get_bp_in_n50(stats)
meanlength=mean(revsort_lengths)
readnum=len(revsort_lengths)
linemeanavg = linemeansum / len(all_lengths)
cumavg = cumsum / sum(all_lengths)

print "total bp: " + str(int(totbp))
print "mean length: " + str(meanlength)
print "number of sequences: " + str(readnum)
print "N50: " + str(int(n50))
print "L50: " + str(int(l50))
print "basepairs in N50: " + str(int(bp_in_n50))
print "average read correctness: " + str(linemeanavg)
print "per basepair correctness: " + str(cumavg)
