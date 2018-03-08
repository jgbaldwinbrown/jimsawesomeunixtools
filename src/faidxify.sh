#!/bin/bash

cat $1 | awk '{printf ">%d\n",NR; print}' > $2
samtools faidx $2
