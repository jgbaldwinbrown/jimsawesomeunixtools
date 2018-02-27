#!/bin/bash

hc=`echo $1 | awk '{split($1,a,","); print a[2]}'`
tc=`echo $1 | awk '{split($1,a,","); print (a[2] - a[1]) + 1}'`

cat $2 | head -n $hc | tail -n $tc
