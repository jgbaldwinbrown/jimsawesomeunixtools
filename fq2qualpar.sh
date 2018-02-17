#!/bin/bash
parallel -l 1000 -j$1 -k --spreadstdin fq2qual 2>/dev/null
