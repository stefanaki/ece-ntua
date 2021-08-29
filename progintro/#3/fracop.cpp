#include "pzhelp"
#include <cstdio>

FUNC int gcd(int a, int b){ // megistos koinos diairetis twn a, b

  a = abs(a); b = abs(b);

  while(a>0 && b>0){

    if (a>b)  a = a%b;
    else b=b%a;

  }

  return a+b;

}

PROC emfanisi_miktou(int ar, int par){

  // diadikasia pou tupwnei to apotelesma se mikto arithmo me aplopoihmeno klasma
  // apotelesma ths morfhs M AR PAR an apotelesma > 0, -abs(M) abs(AR) abs(PAR) an apotelesma < 0

  int akeraio = abs(ar/par);
  int upoloipo = abs(ar%par);
  int mkd = gcd(upoloipo,par);

  if ((ar<0 && par>0) || (ar>0 && par<0)){

    WRITE("-"); WRITELN(akeraio,upoloipo/mkd,abs(par)/mkd);

  }else{

    WRITELN(akeraio,upoloipo/mkd,abs(par)/mkd);

  }

}


PROGRAM { // prakseis

  int N, i;
  char symbol;
  int a_ar, a_par, b_ar, b_par, c_ar, c_par;

  N = READ_INT();

  for(i=1;i<=N;i++){

    scanf(" %c %d %d %d %d",&symbol, &a_ar, &a_par, &b_ar, &b_par);

    if(a_par == 0 || b_par == 0){

      WRITELN("error");
      continue;

    }

    switch(symbol){

      case '+':
        c_ar = a_ar*b_par + b_ar*a_par;
        c_par = a_par*b_par;
        break;

      case '-':
        c_ar = a_ar*b_par - b_ar*a_par;
        c_par = a_par*b_par;
        break;

      case '*':
        c_ar = a_ar*b_ar;
        c_par = a_par*b_par;
        break;

      case '/':
        if(b_ar == 0){
          WRITELN("error");
          continue;
        }else{
          c_ar = a_ar*b_par;
          c_par = b_ar*a_par;
          break;
        }

      default:
        WRITELN("error");
        continue;

    }

   emfanisi_miktou(c_ar,c_par);

  }

}  
