#!../../../perl

use ExtUtils::MakeMaker;

&WriteMakefile(
               "NAME" => "Fame",
	       "VERSION" => "2"
		);

sub MY::test {'
test: fame.test
	$(PERL_SRC)/perl fame.test

patchperl:
	mv $(PERL_SRC)/perl $(PERL_SRC)/perl.old
	$(PERL_SRC)/perl.old -p -e s/_Error/_ErroX/g $(PERL_SRC)/perl.old \
	> $(PERL_SRC)/perl
	chmod +x $(PERL_SRC)/perl

patchperl:
	mv $(PERL_SRC)/perl $(PERL_SRC)/perl.old
	$(PERL_SRC)/perl.old -p -e s/Error/ErroX/g $(PERL_SRC)/perl.old \
	> $(PERL_SRC)/perl
	chmod +x $(PERL_SRC)/perl

maildist:
	uuencode Fame-2.tar.Z Fame-2.tar.Z >Fame-2.uue
	split -200 Fame-2.uue Fame-2.
'}
