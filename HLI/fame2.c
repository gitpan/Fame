/* frb fame stuff */
/* m1fxt00 Aug 13, 1993 */

#include "EXTERN.h"
#include "perl.h"
#include "hli.h"

#ifdef FRB
#include "hliutils.h"
#endif

#ifdef HLILIB
#include "chlilib.c"
#endif

void 
unsupported()
{
  croak("Unsupported HLI function call");
}

void            u_cfmlsts() {
  croak("&cfmlsts() not implemented");
}
void            u_cfmrdfa() {
  croak("&cfmrdfa() not implemented");
}
void            u_cfmrrng() {
  croak("&cfmrrng() not implemented");
}
void            u_cfmrsts() {
  croak("&cfmrsts() not implemented");
}
void            u_cfmwrng() {
  croak("&cfmwrng() not implemented");
}

void 
cfmrstra(status, dbkey, objnam, r1, r2, r3, strval, ismiss, length)
  int            *status;
  int             dbkey;
  char           *objnam;
  int            *r1;
  int            *r2;
  int            *r3;
  char           *strval;
  int            *ismiss;
  int            *length;
{
  int             range[3];
  range[0] = *r1;
  range[1] = *r2;
  range[2] = *r3;
  cfmrstr(status, dbkey, objnam, range, strval, ismiss, length);
  *r1 = range[0];
  *r2 = range[1];
  *r3 = range[2];
}

void 
cfmsbma(p1, p2, p3, p4, b1, b2, b3)
  int            *p1;
  int             p2;
  int             p3;
  int             p4;
  int            *b1;
  int            *b2;
  int            *b3;
{
  int             b[3];
  b[0] = *b1;
  b[1] = *b2;
  b[2] = *b3;
  cfmsbm(p1, p2, p3, p4, b);
  *b1 = b[0];
  *b2 = b[1];
  *b3 = b[2];
}

void 
cfmsdma(p1, p2, p3, p4, b1, b2, b3)
  int            *p1;
  int             p2;
  int             p3;
  int             p4;
  int            *b1;
  int            *b2;
  int            *b3;
{
  int             b[3];
  b[0] = *b1;
  b[1] = *b2;
  b[2] = *b3;
  cfmsdm(p1, p2, p3, p4, b);
  *b1 = b[0];
  *b2 = b[1];
  *b3 = b[2];
}

void 
cfmsfisa(p1, p2, p3, p4, p5, p6, r1, r2, r3, p7, p8, p9)
  int            *p1;
  int             p2;
  int            *p3;
  int            *p4;
  int            *p5;
  int            *p6;
  int            *r1;
  int            *r2;
  int            *r3;
  int            *p7;
  int             p8;
  int             p9;
{
  int             r[3];
  r[0] = *r1;
  r[1] = *r2;
  r[2] = *r3;
  cfmsfis(p1, p2, p3, p4, p5, p6, r, p7, p8, p9);
  *r1 = r[0];
  *r2 = r[1];
  *r3 = r[2];
}

void 
cfmsnma(p1, p2, p3, p4, b1, b2, b3)
  int            *p1;
  float           p2;
  float           p3;
  float           p4;
  float          *b1;
  float          *b2;
  float          *b3;
{
  float           b[3];
  b[0] = *b1;
  b[1] = *b2;
  b[2] = *b3;
  cfmsnm(p1, p2, p3, p4, b);
  *b1 = b[0];
  *b2 = b[1];
  *b3 = b[2];
}

void 
cfmspma(p1, p2, p3, p4, b1, b2, b3)
  int            *p1;
  double          p2;
  double          p3;
  double          p4;
  double         *b1;
  double         *b2;
  double         *b3;
{
  double          b[3];
  b[0] = *b1;
  b[1] = *b2;
  b[2] = *b3;
  cfmspm(p1, p2, p3, p4, b);
  *b1 = b[0];
  *b2 = b[1];
  *b3 = b[2];
}

void 
cfmsrnga(p1, p2, p3, p4, p5, p6, r1, r2, r3, p7)
  int            *p1;
  int             p2;
  int            *p3;
  int            *p4;
  int            *p5;
  int            *p6;
  int            *r1;
  int            *r2;
  int            *r3;
  int            *p7;
{
  int             r[3];
  r[0] = *r1;
  r[1] = *r2;
  r[2] = *r3;
  cfmsrng(p1, p2, p3, p4, p5, p6, r, p7);
  *r1 = r[0];
  *r2 = r[1];
  *r3 = r[2];
}

void 
cfmwrnga(p1, p2, p3, r1, r2, r3, p4, p5, p6)
  int            *p1;
  int             p2;
  char           *p3;
  int            *r1;
  int            *r2;
  int            *r3;
  float          *p4;
  int             p5;
  float          *p6;
{
  int             r[3];
  r[0] = *r1;
  r[1] = *r2;
  r[2] = *r3;
  cfmwrng(p1, p2, p3, r, p4, p5, p6);
  *r1 = r[0];
  *r2 = r[1];
  *r3 = r[2];
}

void 
cfmwstra(p1, p2, p3, r1, r2, r3, p4, p5, p6)
  int            *p1;
  int             p2;
  char           *p3;
  int            *r1;
  int            *r2;
  int            *r3;
  char           *p4;
  int             p5;
  int             p6;
{
  int             r[3];
  r[0] = *r1;
  r[1] = *r2;
  r[2] = *r3;
  cfmwstr(p1, p2, p3, r, p4, p5, p6);
  *r1 = r[0];
  *r2 = r[1];
  *r3 = r[2];
}

int 
famegettype(dbkey, objnam)
  int             dbkey;
  char           *objnam;
{
  int             typ;
  int             status;
  int             c, f, b, o, fy, fp, ly, lp, cy, cm, cd, my, mm,
                  md;
  char            desc[100], doc[100];

  cfmwhat(&status, dbkey, objnam, &c, &typ, &f, &b, &o, &fy,
    &fp, &ly, &lp, &cy, &cm, &cd, &my, &mm, &md, desc, doc);
  return typ;
}

int 
famegetfreq(dbkey, objnam)
  int             dbkey;
  char           *objnam;
{
  int             freq;
  int             status;
  int             c, t, b, o, fy, fp, ly, lp, cy, cm, cd, my, mm,
                  md;
  char            desc[100], doc[100];

  cfmwhat(&status, dbkey, objnam, &c, &t, &freq, &b, &o, &fy,
    &fp, &ly, &lp, &cy, &cm, &cd, &my, &mm, &md, desc, doc);
  return freq;
}

int 
famegetclass(dbkey, objnam)
  int             dbkey;
  char           *objnam;
{
  int             freq;
  int             status;
  int             c, t, b, o, fy, fp, ly, lp, cy, cm, cd, my, mm,
                  md;
  char            desc[100], doc[100];

  cfmwhat(&status, dbkey, objnam, &c, &t, &freq, &b, &o, &fy,
    &fp, &ly, &lp, &cy, &cm, &cd, &my, &mm, &md, desc, doc);
  return c;
}
