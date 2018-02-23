#!/usr/bin/env python
import subprocess
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
parser.add_argument("blast_type", help="BLAST type to use (options are blastn, blastp, blastx, tblastn, tblastx).")
parser.add_argument("a_blast", help="Fasta file of entries in dataset A.")
parser.add_argument("b_blast", help="Fasta file of entries in dataset B.")
parser.add_argument("-c","--e_value_cutoff", help="e-value cutoff for hits (default=1e-5).")

args=parser.parse_args()
if args.e_value_cutoff:
    cutoff = float(args.e_value_cutoff)
else:
    cutoff = 1e-5

bt = args.blast_type

in_a = args.a_blast
in_b = args.b_blast

incon = subprocess.check_output([bt,"-query",in_a,"-subject",in_b,"-evalue",str(cutoff),"-outfmt","6"]).rstrip('\n').split('\n')

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
