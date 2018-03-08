#!/bin/bash
[ $# -ge 1 -a -f "$1" ] && input="$1" || input="-"
echo -n "	" && cat $input | sed 's/^$/\~/g' | tr '\n' ' ' | sed 's/\~/\~	/g' | tr '~' '\n'
