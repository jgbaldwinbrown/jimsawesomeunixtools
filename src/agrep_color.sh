#!/bin/bash

cat $3 | tre-agrep --color -E $2 -e "$1"
