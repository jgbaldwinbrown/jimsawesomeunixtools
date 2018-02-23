#!/usr/bin/env python
import fileinput
import sys
import argparse

################################################################################
################################################################################
#functions:
def sort_by_2num(x):
    out = sorted(x,key=lambda x: x[1],reverse=False)
    return(out)

def sort_dict_by_2num(x):
    outdict = {}
    for key,value in x.iteritems():
        outdict[key] = sort_by_2num(value)
    return(outdict)

def mini_dict(x):
    outdict = {}
    for key,value in x.iteritems():
        outdict[key] = value[0]
    return(outdict)

################################################################################
################################################################################

parser = argparse.ArgumentParser(description = 'run mummer and the merge program.')
parser.add_argument("tabular_blast_output", help="path to tabular BLAST input (put \"-\" for STDIN)")
parser.add_argument("-c","--e_value_cutoff", help="e-value cutoff for hits (default=1e-5).")

args=parser.parse_args()
if args.e_value_cutoff:
    cutoff = float(args.e_value_cutoff)
else:
    cutoff = 1e-5

in_a2b = args.tabular_blast_output
if in_a2b == "-":
    incon = sys.stdin
else:
    incon = open(in_a2b,"r")

#0,1,10 = query,subject,evalue

#loop through a, build query dict:
a2b = {}
for l in incon:
    sl = l.rstrip('\n').split("\t")
    q=sl[0]
    s=sl[1]
    e=float(sl[10])
    if e < cutoff:
        if q in a2b:
            a2b[q].append([s,e,l])
        else:
            a2b[q] = [[s,e,l]]

a2bs = sort_dict_by_2num(a2b)
a2bm = mini_dict(a2bs)

for key,value in a2bm.iteritems():
    print value[2].rstrip('\n')
