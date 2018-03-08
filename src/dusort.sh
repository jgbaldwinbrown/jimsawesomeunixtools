#!/bin/bash
#gdu -bs "$@" | sort -k 1,1nr | rev | cut -d '	' -f 1 | rev | xargs du -shc
du -shc "$@" | sort -k 1,1hr
