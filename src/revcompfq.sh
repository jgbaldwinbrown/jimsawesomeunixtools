#!/bin/bash

bioawk -c fastx '{
print "@"$name
print revcomp($seq)
print "+"
b=split($qual,a,"")
for (i=b;i>=1;i--){
    printf(a[i])
}
printf("\n")
}' "$@"
