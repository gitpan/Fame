#!../../../perl

use ExtUtils::MakeMaker;

&WriteMakefile(
               "NAME" => "Fame",
	       "VERSION" => "2.0c"
		);

sub MY::test {'
test: fame.test
	$(FULLPERL) fame.test

patchperl:
	mv $(FULLPERL) $(FULLPERL).old
	$(FULLPERL).old -p -e s/_Error/_ErroX/g $(FULLPERL).old \
	> $(FULLPERL)
	chmod +x $(FULLPERL)
	touch patch.log

patchsolaris:
	mv $(FULLPERL) $(FULLPERL).old
	$(FULLPERL).old -p -e s/Error/ErroX/g $(FULLPERL).old \
	> $(FULLPERL)
	chmod +x $(FULLPERL)
	touch patch.log

maildist: dist
	uncompress Fame-$(VERSION).tar.Z
	gzip Fame-$(VERSION).tar
	uuencode Fame-$(VERSION).tar.gz Fame-$(VERSION).tar.gz >Fame-$(VERSION).uue
	split -200 Fame-$(VERSION).uue Fame-$(VERSION).
'}
