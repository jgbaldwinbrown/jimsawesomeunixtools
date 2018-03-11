#!/usr/bin/env python

import sys
import argparse

################################################################################
################################################################################
#functions:

def printem(p,q,a,b,c,d):
    print "p = " + str(p)
    print "q = " + str(q)
    print "Homozygous dominant genotype frequency = " + str(a)
    print "Homozygous recessive genotype frequency = " + str(b)
    print "Heterozygote frequency = " + str(c)
    print "Dominant phenotype frequency = " + str(d)
    print "Recessive phenotype frequency = " + str(b)

################################################################################
################################################################################

parser = argparse.ArgumentParser(description = 'Calculate allele, genotype, and phenotype frequencies.')
#parser.add_argument("-i", "--input", help="input values (semicolon separated text of the form p=0.5;q=0.5).")
parser.add_argument("-p", "--p", help="Dominant allele frequency.")
parser.add_argument("-q", "--q", help="Recessive allele frequency.")
parser.add_argument("-a", "--a", help="Homozygous dominant allele frequency.")
parser.add_argument("-b", "--b", help="Homozygous recessive allele frequency.")
parser.add_argument("-c","--c", help="Heterozygote frequency.")
parser.add_argument("-d","--d", help="Dominant phenotype frequency.")
parser.add_argument("-r","--r", help="Recessive phenotype frequency.")

args=parser.parse_args()

if not (args.p or args.q or args.a or args.b or args.c or args.d or args.r):
    exit("Need to specify at least one argument!")

gota=False
gotb=False
gotc=False
gotd=False
gotp=False
gotq=False
if args.d:
    d = float(args.d)
    gotd = True
if args.r:
    b = float(args.r)
    gotb = True
if args.a:
    a = float(args.a)
    gota = True
if args.b:
    b = float(args.b)
    gotb = True
if args.c:
    c = float(args.c)
    gotc = True

if args.p:
    p = float(args.p)
    gotp = True
if args.q:
    q = float(args.q)
    gotq = True

#if gota and gotb and gotc:
if gota + gotb + gotc >= 2:
    if not gota:
        a = 1 - (b+c)
    if not gotb:
        b = 1 - (a+c)
    if not gotc:
        c = 1 - (a+b)
    if not gotp:
        p = a + (c / 2.0)
    if not gotq:
        q = b + (c / 2.0)
    if not gotd:
        d = a + c
    printem(p,q,a,b,c,d)
elif gotd or gotb or gotp or gotq or gota:
    if not gotq:
        if gotp:
            q = 1 - p
        elif gotb:
            q = b**0.5
        elif gotd:
            q = (1 - d)**0.5
        elif gota:
            q = 1 - (a)**0.5
    if not gotp:
        if gotq:
            p = 1 - q
        elif gotb:
            p = 1 - (b)**0.5
        elif gotd:
            p = 1 - (1 - d)**0.5
        elif gota:
            p = (a)**0.5
    if not gotb:
        if gotd:
            b = 1 - d
        elif gotq:
            b = q**2
        elif gotp:
            b = (1-p)**2
        elif gota:
            b = (1 - (a)**0.5)**2
    if not gotd:
        if gotb:
            d = 1-b
        elif gotq:
            d = 1-(q**2)
        elif gotp:
            d = 1-((1-p)**2)
        elif gota:
            d = 1-((1-(a)**0.5)**2)
    if not gota:
        a = p**2
    if not gotb:
        b = q**2
    if not gotc:
        c = 2 * p * q
    printem(p,q,a,b,c,d)
elif gotc:
    #c = 2pq
    #c = 2p(1-p)
    #c = -2*p**2 + 2p
    #0 = -2*p**2 + 2p - c
    #p = (-2 +(2**2 - (4 * (-2) * (-c) )**0.5) / (2 * -2)
    p = (-2 +(2**2 - (4 * (-2) * (-c) ))**0.5) / (2 * -2)
    q = 1-p
    a = p**2
    b = q**2
    d = 1 - b
    printem(p,q,a,b,c,d)
