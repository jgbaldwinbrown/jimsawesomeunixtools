#!/bin/bash
set -e

first=$1
shift

fq2fa "$@" | fagrep "${first}"
