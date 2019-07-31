#!/usr/bin/env python3

def print_fa_entry(header, seq, cols):
    print(header)
    if not cols:
        print(seq)
    else:
        print("\n".join([seq[i:i+cols] for i in range(0,len(seq), cols)]))

#def print_fa_entry(header, seq, cols):
#    if not cols:
#        print(header)
#        print(seq)
#    else:
#        print(header)
#        seqlen = len(seq)
#        start = 0
#        while start < seqlen:
#            if start + cols < seqlen:
#                print(seq[start:start+cols])
#            else:
#                print(seq[start:])
#            start += cols

if __name__ == "__main__":
    import argparse
    import sys

    parser = argparse.ArgumentParser("Wrap fasta files to a specified number of columns.")
    parser.add_argument("fasta", nargs="?", help="Input fasta file. Default = stdin.")
    parser.add_argument("-c", "--cols", help="Number of characters per line (default infinite).")

    args = parser.parse_args()

    if not args.fasta:
        inconn = sys.stdin
    else:
        inconn = open(args.fasta, "r")
    if not args.cols:
        cols = None
    else:
        cols = int(args.cols)

    header = ""
    seq = ""
    for l in inconn:
        l=l.rstrip('\n')
        if len(l) <= 0:
            pass
        elif l[0] == ">":
            if len(header) > 0 and len(seq) > 0:
                print_fa_entry(header, seq, cols)
            header = l
            seq = ""
        else:
            seq += l
    if len(header) > 0 and len(seq) > 0:
        print_fa_entry(header, seq, cols)
    
    inconn.close()
