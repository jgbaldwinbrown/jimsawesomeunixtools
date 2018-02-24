#!/bin/bash

#print results of fqstats:
fqstats $1

#print results of read quality averaging:
echo -n "per basepair read quality:"
cat $1 | fq2qualpar $2 | qual2prob | cum_mean | tail -n 1
