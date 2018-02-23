#!/usr/bin/env python
import sys
import argparse
import subprocess

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
parser.add_argument("-e","--no_check_evals", help="if multiple hits exist, show all of them, not only the best hit.",action="store_true")
parser.add_argument("-o","--output_AB", help="write the output of the A to B blast in the specified file.")
parser.add_argument("-p","--output_BA", help="write the output of the B to A blast in the specified file.")

args=parser.parse_args()
if args.e_value_cutoff:
    cutoff = float(args.e_value_cutoff)
else:
    cutoff = 1e-5
if args.no_check_evals:
    no_check_evals = True
else:
    no_check_evals = False

in_a = args.a_blast
in_b = args.b_blast

bt1 = args.blast_type
btconv = {"blastn":"blastn","blastp":"blastp","blastx":"tblastn","tblastn":"blastx","tblastx":"tblastx"}
bt2 = btconv[bt1]

#print bt1
#print bt2
#print in_a
#print in_b
#print cutoff

in_a2b = subprocess.check_output([bt1,"-query",in_a,"-subject",in_b,"-evalue",str(cutoff),"-outfmt","6"]).rstrip('\n').split('\n')
in_b2a = subprocess.check_output([bt2,"-query",in_b,"-subject",in_a,"-evalue",str(cutoff),"-outfmt","6"]).rstrip('\n').split('\n')

if args.output_AB:
    oab = open(args.output_AB,"w")
    oab.write("\n".join(in_a2b))
    oab.close()
if args.output_BA:
    oba = open(args.output_BA,"w")
    oba.write("\n".join(in_b2a))
    oba.close()

#0,1,10 = query,subject,evalue
if no_check_evals:
    #loop through a, build query dict:
    a2b = {}
    for l in in_a2b:
        sl = l.rstrip('\n').split("\t")
        q=sl[0]
        s=sl[1]
        e=float(sl[10])
        if e < cutoff:
            a2b[q] = [s,e]

    #print first line
    print "A_ident  B_ident A_eval  B_eval"

    #loop through b, build final pairing:
    for l in in_b2a:
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
    for l in in_a2b:
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
    for l in in_b2a:
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

    #print first line
    print "A_ident  B_ident A_eval  B_eval"

    for key,value in b2am.iteritems():
        q=key
        s=value[0]
        e=value[1]
        if s in a2bm:
            if a2bm[s][0] == q:
                print "\t".join(map(str,[s,q,a2bm[s][1],e]))

