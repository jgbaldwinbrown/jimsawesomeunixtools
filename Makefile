SHELL := /bin/bash

all: bins altbins

bins: bin/transpose bin/fq2fa bin/fq2qual bin/fq2qualpar bin/parstdin bin/describe bin/qual2prob bin/mean_lines bin/cum_mean bin/full_blast_recips bin/full_best_blast_hit bin/get_best_blast_hit bin/get_blast_recips bin/qualstats bin/fqstatsfull bin/sf bin/bedanything bin/grep_color bin/agrep_color bin/tab2fa bin/tab2fq bin/fa2tab bin/fq2tab bin/alphacolsort bin/faidxify bin/cless

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

bin/sf: src/sf.sh
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/bedanything: src/bedanything.py
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/grep_color: src/grep_color.sh
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/agrep_color: src/agrep_color.sh
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/fq2tab: src/fq2tab.py
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/fa2tab: src/fa2tab.py
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/tab2fq: src/tab2fq.py
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/tab2fa: src/tab2fa.py
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/alphacolsort: src/alphacolsort.py
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/faidxify: src/faidxify.sh
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@

bin/cless: src/cless
	mkdir -p `dirname $@`
	cp $< $@
	chmod +x $@
