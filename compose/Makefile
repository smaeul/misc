#
# Copyright © 2016 Samuel Holland <samuel@sholland.org>
# See LICENSE in the project directory for license terms.
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
