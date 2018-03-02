#!/bin/bash

cat $2 | grep --color=always -e "$1" -e '$'
