#!/bin/bash

#convert fq to qual and calculate stats:
cat - | fq2qualpar $1 | qualstats
