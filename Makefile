SHELL := /bin/bash

all: bins altbins

bins: bin/transpose bin/fq2fa bin/fq2qual bin/fq2qualpar bin/parstdin bin/describe bin/qual2prob bin/mean_lines bin/cum_mean bin/full_blast_recips bin/full_best_blast_hit bin/get_best_blast_hit bin/get_blast_recips bin/qualstats bin/fqstatsfull

altbins: altbin/fq2fa_cpp altbin/par1line

clean:
	-rm bin/*
	-rm altbin/*

install: all
	cp bin/* ~/mybin

uninstall:
	ls bin/* | while read line ; do rm ~/mybin/`basename $${line}` ; done$

.PHONY: all bins altbins clean install uninstall

.DELETE_ON_ERROR:

bin/transpose: src/transpose.awk
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/fq2fa: src/fq2fa.c
	mkdir -p `dirname $@`
	gcc -Wall -o3 -o $@ $<

altbin/fq2fa_cpp: src/fq2fa.cpp
	mkdir -p `dirname $@`
	g++ -Wall -o3 -o $@ $<

bin/fq2qual: src/fq2qual.cpp
	mkdir -p `dirname $@`
	g++ -Wall -o3 -o $@ $<

bin/fq2qualpar: src/fq2qualpar.sh
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

altbin/par1line: src/par1line.sh
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/parstdin: src/parstdin.sh
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/describe: src/describe.R
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/qual2prob: src/qual2prob.py
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/mean_lines: src/mean_lines.py
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/cum_mean: src/cum_mean.py
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/get_best_blast_hit: src/get_best_blast_hit.py
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/get_blast_recips: src/get_blast_recips.py
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/full_blast_recips: src/full_blast_recips.py
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/full_best_blast_hit: src/full_best_blast_hit.py
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/qualstats: src/qualstats.py
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/fqstatsfull: src/fqstatsfull.sh
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@
