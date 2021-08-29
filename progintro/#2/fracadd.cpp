#include "pzhelp"

PROGRAM {

  int a_ar, a_par, b_ar, b_par;
  a_ar = READ_INT();  a_par = READ_INT();
  b_ar = READ_INT();  b_par = READ_INT();

  int par = a_par * b_par;
  int ar = a_ar * b_par + b_ar * a_par;

  WRITELN(ar,par);

}
