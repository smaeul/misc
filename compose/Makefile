#
# Copyright © 2016-2017 Samuel Holland <samuel@sholland.org>
# SPDX-License-Identifier: 0BSD
# vim: ft=make:noexpandtab:sts=8:sw=8:ts=8:tw=80
#

all: XCompose

clean:
	rm -fr __pycache__ UnicodeData.txt XCompose keysyms.py

install: XCompose
	cp $< $(HOME)/.XCompose

XCompose: gencompose tables.py UnicodeData.txt keysyms.py
	./$< > $@

UnicodeData.txt:
	curl -o $@ http://www.unicode.org/Public/UCD/latest/ucd/UnicodeData.txt

keysyms.py: genkeysyms
	./$< > $@

.PHONY: all clean install
