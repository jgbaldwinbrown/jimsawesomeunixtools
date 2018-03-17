#!/bin/bash

bioawk -c fastx 'BEGIN{chr = '$1'; start='$2'; end='$3'-start + 1}{if ($name == chr) {print ">"$name; print substr($seq,start,end)}}'
