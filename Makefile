SHELL := /bin/bash

all: bins altbins

bins: bin/transpose bin/fq2fa bin/fq2qual bin/fq2qualpar bin/parstdin

altbins: altbin/fq2fa_cpp altbin/par1line

clean:
	-rm bin/*
	-rm altbin/*
.PHONY: all bins altbins clean

.DELETE_ON_ERROR:

bin/transpose: transpose.awk
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/fq2fa: fq2fa.c
	mkdir -p `dirname $@`
	gcc -Wall -o3 -o $@ $<

altbin/fq2fa_cpp: fq2fa.cpp
	mkdir -p `dirname $@`
	g++ -Wall -o3 -o $@ $<

bin/fq2qual: fq2qual.cpp
	mkdir -p `dirname $@`
	g++ -Wall -o3 -o $@ $<

bin/fq2qualpar: fq2qualpar.sh
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

altbin/par1line: par1line.sh
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/parstdin: parstdin.sh
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@
