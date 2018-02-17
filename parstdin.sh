#!/bin/bash
parallel -l 1000 -k --spreadstdin "$@" 2>/dev/null
