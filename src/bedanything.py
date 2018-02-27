#!/usr/bin/env python

import sys
import argparse

parser=argparse.ArgumentParser("Use bedtools to do range comparisons on any two tab-separated files.")
parser.add_argument("bedcommand", help="The bedtools command to use.")
parser.add_argument("file_a", help="The first (A) file for comparison.")
parser.add_argument("file_b", help="The second (B) file for comparison.")
parser.add_argument("-1","--file_a_cols", help="Three comma-separated values representing the chromosome, range start, and range end for the first file (default \"1,2,3\").")
parser.add_argument("-2","--file_b_cols", help="Three comma-separated values representing the chromosome, range start, and range end for the second file (default \"1,2,3\").")
parser.add_argument("-b","--for_bedtools", help="All arguments to be passed to bedtools, surrounded by quotes (default none).")
parser.add_argument("-s","--separator", help="separator for columns for all files (default whitespace).")
parser.add_argument("-a","--separator_1", help="separator for columns for file A (default whitespace, overrides -s).")
parser.add_argument("-b","--separator_2", help="separator for columns for file B (default whitespace, overrides -s).")
parser.add_argument("-o","--separator_o", help="separator for columns for output file (default whitespace, overrides -s).")

args=parser.parse_args()

if args.separator:
    as=args.separator
    bs=args.separator
    os=args.separator
if args.separator_1:
    as=args.separator_1
if args.separator_2:
    bs=args.separator_2
if args.separator_o:
    os=args.separator_o

conn1=open(args.file_a,"r")
conn2=open(args.file_b,"r")
acols=[0,1,2]
bcols=[0,1,2]

if args.file_a_cols:
    acols=map(int,args.file_a_cols.split(","))
if args.file_b_cols:
    bcols=map(int,args.file_b_cols.split(","))

bedcommand=args.bedcommand

if args.for_bedtools:
    bedtools_args=args.for_bedtools.split()

atxt=""
for l in conn1:
    lr = l.rstrip('\n')
    if not as = "no_separator":
        sl=lr.split(as)
    else:
        sl=lr.split()
    ccols = [sl[x] for x in acols]
    atxt = atxt + ccols + as + l

btxt=""
for l in conn2:
    lr = l.rstrip('\n')
    if not bs = "no_separator":
        sl=lr.split(bs)
    else:
        sl=lr.split()
    ccols = [sl[x] for x in bcols]
    btxt = btxt + ccols + bs + l
