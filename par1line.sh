#!/bin/bash
parallel -l 1000 -j$2 -k --spreadstdin $1 2>/dev/null
