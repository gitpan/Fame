#!../../../perl

use ExtUtils::MakeMaker;

$FAME="/usr/local/fame" unless $FAME=$ENV{FAME};

&WriteMakefile(
               "NAME" => "Fame::HLI",
               # substitute FAME here so W.M. can find chli
               "LIBS" => ["-L$FAME/hli -lchli"],
               #"dynamic_lib" => {"OTHERLDFLAGS" => "-Bsymbolic"},
               "OBJECT" => "fame2.o fame.o",
               "DEFINE" => "-DHLI75 -DHLILIB",
               "H" => ["fame.i","famecons.i"],
               "INC" => '-I$(FAME)/hli -I$(FAME)/demo/hli',
               "PM" => { 'hli.ph'  => '$(INST_LIBDIR)/hli.ph',
                       'HLI.pm'  => '$(INST_LIBDIR)/HLI.pm' },
	       "VERSION" => "2"
		);

sub MY::postamble {
    '
hli.ph: $(FAME)/hli/hli.h h2ph
	$(PERL_SRC)/perl h2ph < $(FAME)/hli/hli.h > hli.ph

famecons.i: $(FAME)/hli/hli.h h2c
	$(PERL_SRC)/perl h2c $(FAME)/hli/hli.h > famecons.i

fame.i: fame.cli cliperl
	/usr/lib/cpp -P $(DEFINE) fame.cli > fame.cli.out
	$(PERL_SRC)/perl cliperl Fame::HLI Fame fame.cli.out fameperl.h \
		fame.i fameinit.i fame.xtra fameval.i fameset.i

patchperl:
	mv $(PERL_SRC)/perl $(PERL_SRC)/perl~
	$(PERL_SRC)/perl~ -p -e s/_Error/_ErroX/g $(PERL_SRC)/perl~ \
	> $(PERL_SRC)/perl
	chmod +x $(PERL_SRC)/perl
';
}

sub MY::clean {
    '
clean::
	rm -f fame2.o fame.o fame.i
	rm -f fame.cli.out fameperl.h fame.i fameinit.i
	rm -f fame.xtra famecons.i
	rm -f hli.ph Fame.bs
';
}
