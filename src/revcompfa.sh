#!/bin/bash

bioawk -c fastx '{print ">"$name;print revcomp($seq)}' "$@"
