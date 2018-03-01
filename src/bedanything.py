#!/usr/bin/env python

import sys
import argparse
import subprocess
import os
import tempfile

parser=argparse.ArgumentParser("Use bedtools to do range comparisons on any two tab-separated files.")
parser.add_argument("bedcommand", help="The bedtools command to use.")
parser.add_argument("file_a", help="The first (A) file for comparison.")
parser.add_argument("file_b", help="The second (B) file for comparison.")
parser.add_argument("-1","--file_a_cols", help="Three comma-separated values representing the chromosome, range start, and range end for the first file (default \"1,2,3\").")
parser.add_argument("-2","--file_b_cols", help="Three comma-separated values representing the chromosome, range start, and range end for the second file (default \"1,2,3\").")
parser.add_argument("-f","--for_bedtools", help="All arguments to be passed to bedtools, surrounded by quotes (default none).")
parser.add_argument("-s","--separator", help="Separator for columns for all files (default whitespace).")
parser.add_argument("-a","--separator_1", help="Separator for columns for file A (default whitespace, overrides -s).")
parser.add_argument("-b","--separator_2", help="Separator for columns for file B (default whitespace, overrides -s).")
parser.add_argument("-o","--separator_o", help="Separator for columns for output file (default whitespace, overrides -s).")
parser.add_argument("-c","--cut_first_3", help="Remove the first 3 columns from the output (default False).",action="store_true")

args=parser.parse_args()

as_sep = "no_separator"
bs = "no_separator"
o_sep = "\t"

if args.separator:
    as_sep=args.separator
    bs=args.separator
    o_sep=args.separator
if args.separator_1:
    as_sep=args.separator_1
if args.separator_2:
    bs=args.separator_2
if args.separator_o:
    o_sep=args.separator_o

conn1=open(args.file_a,"r")
conn2=open(args.file_b,"r")
acols=[0,1,2]
bcols=[0,1,2]

if args.file_a_cols:
    acols=map(int,args.file_a_cols.split(","))
if args.file_b_cols:
    bcols=map(int,args.file_b_cols.split(","))

bedcommand=args.bedcommand

extra_args = False
if args.for_bedtools:
    bedtools_args=args.for_bedtools.split()
    extra_args = True

cutfirst3 = False
if args.cut_first_3:
    cutfirst3 = True

atxt=""
for l in conn1:
    lr = l.rstrip('\n')
    if not as_sep == "no_separator":
        sl=lr.split(as_sep)
    else:
        sl=lr.split()
    ccols = [sl[x] for x in acols]
    ccols.append(l)
    if not as_sep == "no_separator":
        myline = as_sep.join(ccols)
    else:
        myline = "\t".join(ccols)
    atxt = atxt + myline

btxt=""
for l in conn2:
    lr = l.rstrip('\n')
    if not bs == "no_separator":
        sl=lr.split(bs)
    else:
        sl=lr.split()
    ccols = [sl[x] for x in bcols]
    ccols.append(l)
    if not bs == "no_separator":
        myline = bs.join(ccols)
    else:
        myline = "\t".join(ccols)
    btxt = btxt + myline

#run the bedtools command:
#...
#bedtools_command = ["bedtools",bedcommand,]
#if extra_args:
#    bedtools_command.append(extra_args)
#subprocess.Popen(bedtools_command)

with tempfile.NamedTemporaryFile() as file1:
    file1.write(atxt)
    file1.delete = False
    print file1.closed
    print file1.closed

print file1.closed

with tempfile.NamedTemporaryFile() as file2:
    file2.write(btxt)
    file2.delete = False

try:
    commandlist = ["bedtools",bedcommand,"-a",file1.name,"-b",file2.name]
    if extra_args:
        commandlist.extend(bedtools_args)
        print commandlist
    p = subprocess.Popen(commandlist,
              stdout=subprocess.PIPE,stderr=subprocess.PIPE)
    #p=subprocess.Popen(["echo","hat"],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
    bedout = p.communicate()[0].decode('utf-8').strip()
    bederr = p.communicate()[1].decode('utf-8').strip()
finally:
    os.remove(file1.name)
    os.remove(file2.name)

print bedout
print bederr

#if the user opted to remove the first 3 columns, do it:

for line in bedout.split('\n'):
    if not cutfirst3:
        sl = line.split("\t")
        print o_sep.join(sl)
    else:
        sl=line.split("\t")
        print o_sep.join(sl[3:])
