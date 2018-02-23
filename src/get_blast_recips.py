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
parser.add_argument("a_to_b_blast", help="BLAST tabular output for the queries of A to B.")
parser.add_argument("b_to_a_blast", help="BLAST tabular output for the queries of B to A.")
parser.add_argument("-c","--e_value_cutoff", help="e-value cutoff for hits (default=1e-5).")
parser.add_argument("-e","--no_check_evals", help="if multiple hits exist, show all of them, not only the best hit.",action="store_true")

args=parser.parse_args()
if args.e_value_cutoff:
    cutoff = float(args.e_value_cutoff)
else:
    cutoff = 1e-5
if args.no_check_evals:
    no_check_evals = True
else:
    no_check_evals = False

in_a2b = args.a_to_b_blast
in_b2a = args.b_to_a_blast

#0,1,10 = query,subject,evalue
if no_check_evals:
    #loop through a, build query dict:
    a2b = {}
    for l in open(in_a2b,"r"):
        sl = l.rstrip('\n').split("\t")
        q=sl[0]
        s=sl[1]
        e=float(sl[10])
        if e < cutoff:
            a2b[q] = [s,e]

    #print first line
    print "A_ident  B_ident A_eval  B_eval"

    #loop through b, build final pairing:
    for l in open(in_b2a,"r"):
        sl = l.rstrip('\n').split("\t")
        q=sl[0]
        s=sl[1]
        e=float(sl[10])
        if e < cutoff:
            if a2b[s][0] == q:
                print "\t".join(map(str,[s,q,a2b[s][1],e]))
else:
    #loop through a, build query dict:
    a2b = {}
    for l in open(in_a2b,"r"):
        sl = l.rstrip('\n').split("\t")
        q=sl[0]
        s=sl[1]
        e=float(sl[10])
        if e < cutoff:
            if q in a2b:
                a2b[q].append([s,e])
            else:
                a2b[q] = [[s,e]]
    #loop through b, build final pairing:
    b2a = {}
    for l in open(in_b2a,"r"):
        sl = l.rstrip('\n').split("\t")
        q=sl[0]
        s=sl[1]
        e=float(sl[10])
        if e < cutoff:
            if q in b2a:
                b2a[q].append([s,e])
            else:
                b2a[q] = [[s,e]]
    
    
    a2bs = sort_dict_by_2num(a2b)
    a2bm = mini_dict(a2bs)
    b2as = sort_dict_by_2num(b2a)
    b2am = mini_dict(b2as)

    #print "\n".join(["\t".join([key,"; ".join([", ".join(map(str,x)) for x in value])]) for key,value in a2b.iteritems()][0:5])
    #print "-"
    #print "\n".join(["\t".join([key,"; ".join([", ".join(map(str,x)) for x in value])]) for key,value in a2bs.iteritems()][0:5])
    #print "-"
    #print "\n".join(["\t".join([key,"; ".join([", ".join(map(str,x)) for x in value])]) for key,value in a2bs.iteritems()][0:5])

    #print first line
    print "A_ident  B_ident A_eval  B_eval"

    for key,value in b2am.iteritems():
        q=key
        s=value[0]
        e=value[1]
        if s in a2bm:
            if a2bm[s][0] == q:
                print "\t".join(map(str,[s,q,a2bm[s][1],e]))

