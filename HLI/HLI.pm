# Fame/HLI.pm
#
# FT 9/95
#

package Fame::HLI;

use Carp;
use Exporter;
use DynaLoader;
@ISA = (Exporter, DynaLoader);

@EXPORT = 
qw( cfmgatt cfmsatt famestart famestop fameopen fameclose fameread
famereadn famewrite famegetinfo cfmalob cfmbwdy cfmchfr cfmcldb
cfmcpob cfmdatd cfmdatf cfmdati cfmdatl cfmdatp cfmdatt cfmddat
cfmddes cfmddoc cfmdlen cfmdlob cfmfame cfmfdat cfmfdiv cfmferr
cfmfin cfmgali cfmgaso cfmgdat cfmgdba cfmgdbd cfmglen cfmgnam
cfmgsln cfmidat cfmini cfminwc cfmisbm cfmisdm cfmislp cfmisnm
cfmispm cfmissm cfmlali cfmlaso cfmlatt cfmldat cfmlerr cfmlsts
cfmncnt cfmnlen cfmnwob cfmnxwc cfmopdb cfmopre cfmopwk cfmosiz
cfmpack cfmpdat cfmpfrq cfmpind cfmpinm cfmpiny cfmpodb cfmrdfa
cfmrdfm cfmrdnl cfmrmev cfmrnob cfmrrng cfmrsdb cfmrstr cfmsali
cfmsaso cfmsbas cfmsbm cfmsdes cfmsdm cfmsdoc cfmsfis cfmsinp
cfmsnm cfmsobs cfmsopt cfmspm cfmsrng cfmssln cfmtdat cfmtody
cfmufrq cfmver cfmwhat cfmwkdy cfmwrng cfmwstr cfmwtnl famegettype
fameopen fameclose
hlierr getsta getcls gettyp getbas getobs getfrq);

sub AUTOLOAD {
    local($constname);
    ($constname = $AUTOLOAD) =~ s/.*:://;
    # print STDERR "find $AUTOLOAD\n";
    $val = &Fame::HLI::constant($constname, @_ ? $_[0] : 0);
    if ($! != 0) {
        if ($! =~ /Invalid/) {
            $AutoLoader::AUTOLOAD = $AUTOLOAD;
            goto &AutoLoader::AUTOLOAD;
        }
        else {
            Carp::croak("Your vendor has not defined Fame macro $constname, used");
        }
    }
    eval "sub $AUTOLOAD { $val }";
    goto &$AUTOLOAD;
}

bootstrap Fame::HLI;

tie $status, Fame::HLI::var_status, "status";
tie $version, Fame::HLI::var_version, "version";

package Fame::HLI;
# HLI.pm version number
sub version {2.0;}

1;
