/* frb fame stuff */
/* m1fxt00 Dec 1994 for Perl5 */

#include <memory.h>
#include <malloc.h>
#include <errno.h>
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "hli.h"
#ifdef FRB
#include "hliutils.h"
#endif


/* misc function declarations */
int             fameinit();
/*
 * #include "fameperl.h"
 */

#include "fame.xtra"

int             f_status;
char            *version="2.00";

#include "fame.i"

/* include constants code */
#include "famecons.i"

XS(Fame_constant)
{
    dXSARGS;
    if (items != 2) {
        croak("Usage: Fame::HLI::constant(name,arg)");
    }
    {
        char *  name = (char *)SvPV(ST(0),na);
        int     arg = (int)SvIV(ST(1));
        double  RETVAL;
 
        RETVAL = constant(name, arg);
        ST(0) = sv_newmortal();
        sv_setnv(ST(0), (double)RETVAL);
    }
    XSRETURN(1);
}


XS(Fame_cfmgatt)
{
  dXSARGS;
  if (items != 6)
    croak("Usage: &cfmgatt($status, $dbkey, $objnam, $atttyp, $attnam, $value)");
  else {
    int             retval = 1;
    int             status;
    int             dbkey = (int) SvIV(ST(1));
    char           *objnam = (char *) SvPV(ST(2), na);
    int             atttyp = (int) SvIV(ST(3));
    char           *attnam = (char *) SvPV(ST(4), na);
    char           *value;
    int            *pi;
    float          *pf;
    double         *pd;

    value = (char *) malloc(133 * sizeof(char));
    (void) cfmgatt(&status, dbkey, objnam, &atttyp, attnam, value);
    pd = (double *) value;
    pf = (float *) value;
    pi = (int *) value;

    sv_setiv(ST(0), status);
    sv_setpv(ST(2), (char *) objnam);
    sv_setiv(ST(3), atttyp);
    sv_setpv(ST(4), (char *) attnam);

    if (atttyp >= 8) { atttyp = HBOOLN; }

    switch (atttyp) {
    case HNUMRC:
      if (*pf == FNUMNC)
        sv_setpv(ST(5), "NC");
      else if (*pf == FNUMND)
        sv_setpv(ST(5), "ND");
      else if (*pf == FNUMNA)
        sv_setpv(ST(5), "NA");
      else
        sv_setnv(ST(5), (double) *pf);
      break;
    case HBOOLN:
      if (*pi == FBOONC)
        sv_setpv(ST(5), "NC");
      else if (*pi == FBOOND)
        sv_setpv(ST(5), "ND");
      else if (*pi == FBOONA)
        sv_setpv(ST(5), "NA");
      else
        sv_setiv(ST(5), (int) *pi);
      break;
    case HNAMEL:
    case HSTRNG:
      if (memcmp(value, FSTRNC, HSMLEN) == 0)
        sv_setpv(ST(5), "NC");
      else if (memcmp(value, FSTRND, HSMLEN) == 0)
        sv_setpv(ST(5), "ND");
      else if (memcmp(value, FSTRNA, HSMLEN) == 0)
        sv_setpv(ST(5), "NA");
      else
        sv_setpv(ST(5), value);
      break;
    case HPRECN:
      if (*pd == FPRCNC)
        sv_setpv(ST(5), "NC");
      else if (*pd == FPRCND)
        sv_setpv(ST(5), "ND");
      else if (*pd == FPRCNA)
        sv_setpv(ST(5), "NA");
      else
        sv_setnv(ST(5), (double) *pd);
      break;
    }
    free(value);
    ST(0) = sv_newmortal();
    sv_setiv(ST(0), status);
  }
  XSRETURN(1);
}


XS(Fame_cfmsatt)
{
  dXSARGS;
  if (items != 6)
    croak("Usage: &cfmgatt($status, $dbkey, $objnam, $atttyp, $attnam, $value)");
  else {
    int             retval = 1;
    int             status;
    int             dbkey = (int) SvIV(ST(1));
    char           *objnam = (char *) SvPV(ST(2), na);
    int             atttyp = (int) SvIV(ST(3));
    char           *attnam = (char *) SvPV(ST(4), na);
    char           *value;
    char            space[255];
    char           *ss;
    int             pi;
    float           pf;
    double          pd;

    ss = SvPV(ST(5),na);

    if (atttyp >= 8) { atttyp = HBOOLN; }

    switch (atttyp) {
    case HNUMRC:
      value = (char *) &pf;
      if (ss[0] == 'N') {
        if (strcmp(ss, "NC") == 0)
          pf = FNUMNC;
        else if (strcmp(ss, "ND") == 0)
          pf = FNUMND;
        else if (strcmp(ss, "NA") == 0)
          pf = FNUMNA;
      } else
        pf = (float) SvNV(ST(5));
      break;
    case HNAMEL:
    case HSTRNG:
      value = space;
      if (ss[0] == 'N') {
        if (strcmp(ss, "NC") == 0)
          memcpy(value, FSTRNC, HSMLEN);
        else if (strcmp(ss, "ND") == 0)
          memcpy(value, FSTRND, HSMLEN);
        else if (strcmp(ss, "NA") == 0)
          memcpy(value, FSTRNA, HSMLEN);
      } else
        value = SvPV(ST(5), na);
      break;
    case HBOOLN:
      value = (char *) &pi;
      if (ss[0] == 'N') {
        if (strcmp(ss, "NC") == 0)
          pi = FBOONC;
        else if (strcmp(ss, "ND") == 0)
          pi = FBOOND;
        else if (strcmp(ss, "NA") == 0)
          pi = FBOONA;
      } else
        pi = (int) SvIV(ST(5));
      break;
    case HPRECN:
      value = (char *) &pd;
      if (ss[0] == 'N') {
        if (strcmp(ss, "NC") == 0)
          pd = FPRCNC;
        else if (strcmp(ss, "ND") == 0)
          pd = FPRCND;
        else if (strcmp(ss, "NA") == 0)
          pd = FPRCNA;
      } else
        pd = (double) SvNV(ST(6));
      break;
    }

    (void) cfmsatt(&status, dbkey, objnam, atttyp, attnam, value);

    sv_setiv(ST(0), status);
    sv_setpv(ST(2), objnam);
    sv_setpv(ST(4), attnam);

    ST(0) = sv_newmortal();
    sv_setiv(ST(0), status);
  }
  XSRETURN(1);
}


XS(Fame_famestart)
{
  dXSARGS;
  if (items != 0)
    croak("Usage: &famestart()");
  else {
    int retval;
    cfmini(&retval);
    f_status = retval;
    ST(0) = sv_newmortal();
    sv_setiv(ST(0), retval);
  }
  XSRETURN(1);
}


XS(Fame_famestop)
{
  dXSARGS;
  if (items != 0)
    croak("Usage: &famestop()");
  else {
    int retval;
    cfmfin(&retval);
    f_status = retval;
    ST(0) = sv_newmortal();
    sv_setiv(ST(0), retval);
  }
  XSRETURN(1);
}


XS(Fame_fameopen)
{
  dXSARGS;
  if (items < 1 || items > 2)
    croak("Usage: $dbkey=&fameopen($name [,$mode])");
  else {
    int             retval = 1;
    char           *name = (char *) SvPV(ST(0), na);
    char            name2[1024];
    int             mode;
    int             status;

#ifdef FRB
    char           path[256];

    (void) getdbpath(name, path);
    if (path != NULL && *path != '\n')
      name = path;
    if (name[strlen(name) - 1] == '\n')
      name[strlen(name) - 1] = '\0';
#endif

    if (items == 1)
      mode = HRMODE;
    else
      mode = (int) SvIV(ST(1));
    cfmopdb(&status, &retval, name, mode);
    f_status = status;
    if (status != HSUCC) retval=-1;
    ST(0) = sv_newmortal();
    sv_setiv(ST(0), retval);
  }
  XSRETURN(1);
}


XS(Fame_fameclose)
{
  dXSARGS;
  if (items != 1)
    croak("Usage: &fameclose($dbkey)");
  else {
    int             retval = 1;
    int             dbkey = (int) SvIV(ST(0));
    int             status;

    cfmcldb(&status, dbkey);
    f_status = status;
    if (status != HSUCC)
      retval = 0;
    ST(0) = sv_newmortal();
    sv_setiv(ST(0), retval);
  }
  XSRETURN(1);
}


XS(Fame_famegetinfo)
{
  dXSARGS;
  if (items != 2)
    croak("Usage: @list=&famegetinfo($dbkey,$objnam)");
  else {
    int             retval = 1;
    int             dbkey = (int) SvIV(ST(0));
    char           *objnam = (char *) SvPV(ST(1), na);
    int             p[16], i;
    char           *p1;
    char           *p2;
    int             d1, d2;

    cfmdlen(&p[0], dbkey, objnam, &d1, &d2);
    f_status = p[0];
    if (p[0] != HSUCC) {
      /* croak("Fame error: famegetinfo failed"); */
      XSRETURN_UNDEF;  /* error in reading - prob. doesn't exist */
    }

    d1++;
    d2++;
    p1 = (char *) malloc(d1 * sizeof(char));
    p2 = (char *) malloc(d2 * sizeof(char));
    for (i = 0; i < d1; i++) {
      p1[i] = ' ';
    } p1[d1 - 1] = '\n';
    p1[d1] = 0;
    for (i = 0; i < d2; i++) {
      p2[i] = ' ';
    } p2[d2 - 1] = '\n';
    p2[d2] = 0;

    cfmwhat(&p[0], dbkey, objnam, &p[1], &p[2], &p[3], &p[4], &p[5], &p[6],
      &p[7], &p[8], &p[9], &p[10], &p[11], &p[12], &p[13], &p[14], 
      &p[15], p1, p2);
    f_status = p[0];

    if (p[0] != HSUCC) {
      /* croak("Fame error: famegetinfo failed on cfmwhats"); */
      free(p1);
      free(p2);
      XSRETURN_UNDEF;  /* error in reading */
    }

    EXTEND(sp, 17);  /* extend stack by 17 entries */
    for (i = 0; i < 15; i++) {
      ST(i) = sv_newmortal();
      sv_setiv(ST(i), p[i + 1]);
    }
    ST(15) = sv_newmortal();
    sv_setpv(ST(15), p1);
    ST(16) = sv_newmortal();
    sv_setpv(ST(16), p2);
    free(p1);
    free(p2);
  }
  XSRETURN(17);
}


XS(Fame_fameread)
{
  dXSARGS;
  if (items != 6 && items != 5)
    croak("Usage: @list=&fameread($db,$onam,[$r1,r1,r3]|[$syear,$sprd,$eyear,$eprd])");
  else {
    int             retval = 1;
    int             dbkey = (int) SvIV(ST(0));
    char           *series = (char *) SvPV(ST(1), na);

    int             status;
    int             freq, typ, class;
    int             range[3];
    int             numobs = -1;
    float          *valary;
    float          *mistt;
    int             sz;
    float          *pf;
    double         *pd;
    int            *pi;
    int             i;

    freq = famegetfreq(dbkey, series);
    typ = famegettype(dbkey, series);
    if (typ >= 8) { typ = HBOOLN; }
    class = famegetclass(dbkey, series);
    if (class==HSERIE) {
      if (items == 6) {
        int             syear = (int) SvIV(ST(2));
        int             sprd = (int) SvIV(ST(3));
        int             eyear = (int) SvIV(ST(4));
        int             eprd = (int) SvIV(ST(5));
        cfmsrng(&status, freq, &syear, &sprd, &eyear, &eprd, range, &numobs);
        f_status = status;
        if (status != HSUCC) {
          /* fprintf(stderr,"HLI(%d)",status); */
          /* croak("Fame error: Read failed to set range"); */
          XSRETURN_UNDEF;
        }
      } else {
        range[0] = (int) SvIV(ST(2));
        range[1] = (int) SvIV(ST(3));
        range[2] = (int) SvIV(ST(4));
      }
    } else if (class==HSCALA) { 
      numobs=1;
    }

    switch (typ) {
    case HNUMRC:
      sz = sizeof(float);
      break;
    case HBOOLN:
      sz = sizeof(int);
      break;
    case HPRECN:
      sz = sizeof(double);
      break;
    case HUNDFT:
      sz = 0;
  defalut:  sz = 0;
    }
    if (sz == 0) {
      /* croak("Fame error: Invalid data type"); */
      XSRETURN_UNDEF;
    }
    valary = (float *) malloc(numobs * sz);

    cfmrrng(&status, dbkey, series, range, valary, HNTMIS, mistt);
    f_status = status;
    if (status != HSUCC) {
      /* fprintf(stderr,"HLI(%d)",status); */
      /* croak("Fame error: Read failed"); */
      XSRETURN_UNDEF;
    }

    EXTEND(sp, numobs);

    switch (typ) {
    case HNUMRC:
      pf = (float *) valary;
      break;
    case HBOOLN:
      pi = (int *) valary;
      break;
    case HPRECN:
      pd = (double *) valary;
      break;
    }
    for (i = 0; i < numobs; i++) {
      switch (typ) {
      case HNUMRC:
        if (pf[i] == FNUMNC) {
          ST(i)=sv_newmortal();
          sv_setpv(ST(i),"NC");
        }
        else if (pf[i] == FNUMND) {
          ST(i)=sv_newmortal();
          sv_setpv(ST(i),"ND");
        }
        else if (pf[i] == FNUMNA) {
          ST(i)=sv_newmortal();
          sv_setpv(ST(i),"NA");
        }
        else {
          ST(i)=sv_newmortal();
          sv_setnv(ST(i),(double) pf[i]);
        }
        break;
      case HBOOLN:
        if (pi[i] == FBOONC) {
          ST(i)=sv_newmortal();
          sv_setpv(ST(i),"NC");
        }
        else if (pi[i] == FBOOND) {
          ST(i)=sv_newmortal();
          sv_setpv(ST(i),"ND");
        }
        else if (pi[i] == FBOONA) {
          ST(i)=sv_newmortal();
          sv_setpv(ST(i),"NA");
        }
        else {
          ST(i)=sv_newmortal();
          sv_setiv(ST(i),(int) pi[i]);
        }
        break;
      case HPRECN:
        if (pd[i] == FPRCNC) {
          ST(i)=sv_newmortal();
          sv_setpv(ST(i),"NC");
        }
        else if (pd[i] == FPRCND) {
          ST(i)=sv_newmortal();
          sv_setpv(ST(i),"ND");
        }
        else if (pd[i] == FPRCNA) {
          ST(i)=sv_newmortal();
          sv_setpv(ST(i),"NA");
        }
        else {
          ST(i)=sv_newmortal();
          sv_setnv(ST(i),(double) pd[i]);
        }
        break;
      }
    }
    free(valary);
    if (numobs > 0) {
      XSRETURN(numobs);
    } 
    else { 
      XSRETURN_UNDEF;
    }
  }
  XSRETURN_UNDEF;
}


XS(Fame_famereadn)
{
  dXSARGS;
  if (items != 10)
    croak("Usage: @list=&famereadn($dbkey,$objnam,$num,$r1,$r2,$r3,$tmiss,$m1,$m2,$m3)");
  else {
    int             retval = 1;
    int             dbkey = (int) SvIV(ST(0));
    char           *series = (char *) SvPV(ST(1), na);
    int             wntobs = (int) SvIV(ST(2));
    int             tmiss = (int) SvIV(ST(6));

    int             i;
    float          *pf;
    int            *pi;
    double         *pd;
    char          **cv;
    int             sz;
    int            *misary;
    int            *lenary;

    int             status;
    int             typ;
    int             syear;
    int             sprd;
    float          *valary;
    float          *mistt;
    double          md[3];
    float           mf[3];
    int             mi[3];
    int             range[3];

    range[0] = (int) SvIV(ST(3));
    range[1] = (int) SvIV(ST(4));
    range[2] = (int) SvIV(ST(5));

    typ = famegettype(dbkey, series);
    if (typ >= 8) { typ = HBOOLN; }

    switch (typ) {
    case HNUMRC:
      mf[0] = (float) SvNV(ST(7));
      mf[1] = (float) SvNV(ST(8));
      mf[2] = (float) SvNV(ST(9));
      sz = sizeof(float);
      mistt = (float *) mf;
      break;
    case HSTRNG:
    case HNAMEL:
      sz = sizeof(char);
      break;
    case HBOOLN:
      mi[0] = (int) SvIV(ST(7));
      mi[1] = (int) SvIV(ST(8));
      mi[2] = (int) SvIV(ST(9));
      sz = sizeof(int);
      mistt = (float *) mi;
      break;
    case HPRECN:
      md[0] = (double) SvIV(ST(7));
      md[1] = (double) SvIV(ST(8));
      md[2] = (double) SvIV(ST(9));
      sz = sizeof(double);
      mistt = (float *) md;
      break;
    default:
      sz = 0;
    }

    if (typ != HNAMEL && typ != HSTRNG) {
      valary = (float *) malloc(wntobs * sz);
      cfmrrng(&status, dbkey, series, range, valary, tmiss, mistt);
      f_status = status;
    } else {
      cv = (char **) malloc(wntobs * sizeof(char *));
      misary = (int *) malloc(wntobs * sizeof(int));
      lenary = (int *) malloc(wntobs * sizeof(int));
      for (i = 0; i < wntobs; i++)
        cv[i] = (char *) malloc(100 * sizeof(char));
      cfmrsts(&status, dbkey, series, range, cv, misary, lenary);
      f_status = status;
    }

    EXTEND(sp, wntobs);

    switch (typ) {
    case HNUMRC:
      pf = (float *) valary;
      break;
    case HBOOLN:
      pi = (int *) valary;
      break;
    case HPRECN:
      pd = (double *) valary;
      break;
    }
    for (i = 0; i < wntobs; i++) {
      switch (typ) {
      case HNUMRC:
        ST(i)=sv_newmortal();
        sv_setnv(ST(i), (double) pf[i]);
        break;
      case HSTRNG:
      case HNAMEL:
        ST(i)=sv_newmortal();
        sv_setpv(ST(i), cv[i]);
        break;
      case HBOOLN:
        ST(i)=sv_newmortal();
        sv_setiv(ST(i), (int) pi[i]);
        break;
      case HPRECN:
        ST(i)=sv_newmortal();
        sv_setnv(ST(i), (double) pd[i]);
        break;
      }
    }
    if (typ != HNAMEL && typ != HSTRNG)
      free(valary);
    else {
      free(misary);
      free(lenary);
      for (i = 0; i < wntobs; i++)
        free(cv[i]);
      free(cv);
    }
    if (wntobs > 0) {
      XSRETURN(wntobs);
    }
    else {
      XSRETURN_UNDEF;
    }
  }
  XSRETURN_UNDEF;
}


XS(Fame_famewrite)
{
  dXSARGS;
  if (items <= 4)
    croak("Usage: &famewrite($dbkey,$objnam,$year,$prd,@list)");
  else {
    int             retval = 1;
    int             dbkey = (int) SvIV(ST(0));
    char           *series = (char *) SvPV(ST(1), na);
    int             year = (int) SvIV(ST(2));
    int             prd = (int) SvIV(ST(3));
    int             eyear = -1;
    int             eprd = -1;

    int             status;
    int             freq;
    int             range[3];
    int             numobs;
    float          *valary;
    float          *mistt;
    int             typ;
    int             sz;
    float          *pf;
    double         *pd;
    int            *pi;
    char           *ss;
    int             i;

    numobs = items - 4;
    freq = famegetfreq(dbkey, series);
    typ = famegettype(dbkey, series);
    cfmsrng(&status, freq, &year, &prd, &eyear, &eprd, range, &numobs);
    f_status = status;
    switch (typ) {
    case HNUMRC:
      sz = sizeof(float);
      break;
    case HBOOLN:
      sz = sizeof(int);
      break;
    case HPRECN:
      sz = sizeof(double);
      break;
    case HUNDFT:
      sz = 0;
    default:
      sz = 0;
    }
    if (sz == 0) {
      /* croak("Fame error: unsupported data type"); */
      XSRETURN(1);
    }
    valary = (float *) malloc(numobs * sz);
    mistt = (float *) malloc(3 * sz);
    switch (typ) {
    case HNUMRC:
      pf = (float *) valary;
      break;
    case HBOOLN:
      pi = (int *) valary;
      break;
    case HPRECN:
      pd = (double *) valary;
      break;
    }
    for (i = 0; i < numobs; i++) {
      ss = SvPV(ST(i+4), na);
      switch (typ) {
      case HNUMRC:
        if (ss[0] == 'N') {
          if (strcmp(ss, "NC") == 0)
            pf[i] = FNUMNC;
          else if (strcmp(ss, "ND") == 0)
            pf[i] = FNUMND;
          else if (strcmp(ss, "NA") == 0)
            pf[i] = FNUMNA;
        } else
          pf[i] = (float) SvNV(ST(i + 4));
        break;
      case HBOOLN:
        if (ss[0] == 'N') {
          if (strcmp(ss, "NC") == 0)
            pi[i] = FBOONC;
          else if (strcmp(ss, "ND") == 0)
            pi[i] = FBOOND;
          else if (strcmp(ss, "NA") == 0)
            pi[i] = FBOONA;
        } else
          pi[i] = (int) SvIV(ST(i + 4));
        break;
      case HPRECN:
        if (ss[0] == 'N') {
          if (strcmp(ss, "NC") == 0)
            pd[i] = FPRCNC;
          else if (strcmp(ss, "ND") == 0)
            pd[i] = FPRCND;
          else if (strcmp(ss, "NA") == 0)
            pd[i] = FPRCNA;
        } else
          pd[i] = (double) SvNV(ST(i + 4));
        break;
      }
    }
    cfmwrng(&status, dbkey, series, range, valary, HNTMIS, mistt);
    f_status = status;
    if (status != HSUCC) {
      /* fprintf(stderr,"HLI(%d)",status); */
      /* croak("Fame error: Write failed"); */
      XSRETURN_UNDEF;
    }
    free(valary);
    ST(0)=sv_newmortal();
    sv_setiv(ST(0), status);
  }
  XSRETURN(1);
}

XS(boot_Fame__HLI)
{
  dXSARGS;
  char           *fn = __FILE__;
  int status;

#include "fameinit.i"

  /* set up constants for the autoloader */
  newXS("Fame::HLI::constant", Fame_constant, fn);

  /* register BEGIN, but it won't call it for some reason, so
     added cfmini below */
  /* newXS("Fame::HLI::BEGIN", Fame_famestart, fn); */
  /* it will, however, call END when terminating */
  newXS("Fame::HLI::END", Fame_famestop, fn);

  newXS("Fame::HLI::famestart", Fame_famestart, fn);
  newXS("Fame::HLI::famestop", Fame_famestop, fn);
  newXS("Fame::HLI::cfmgatt", Fame_cfmgatt, fn);
  newXS("Fame::HLI::cfmsatt", Fame_cfmsatt, fn);
  newXS("Fame::HLI::famestart", Fame_famestart, fn);
  newXS("Fame::HLI::famestop", Fame_famestop, fn);
  newXS("Fame::HLI::fameopen", Fame_fameopen, fn);
  newXS("Fame::HLI::fameclose", Fame_fameclose, fn);
  newXS("Fame::HLI::fameread", Fame_fameread, fn);
  newXS("Fame::HLI::famereadn", Fame_famereadn, fn);
  newXS("Fame::HLI::famewrite", Fame_famewrite, fn);
  newXS("Fame::HLI::famegetinfo", Fame_famegetinfo, fn);

  cfmini(&status);
  if (status != HSUCC) {
    errno=status;
    ST(0) = &sv_no;
  } else {
    ST(0) = &sv_yes;
  }
  XSRETURN(1);
}
