#include <iostream>
#ifndef CONTEST
#include "babyratio.hpp"
#endif

using namespace std;

rational::rational(int n, int d) {
  nom = n / gcd(n, d);
  den = d / gcd(n, d);

  if(nom == 0) {
    den = 1;
  } else if(den < 0) {
    nom *= -1;
    den *= -1;
  }

  return;
}

rational rational::add(rational r) {
  rational result(nom * r.den + r.nom * den, den * r.den);
  return result;
}

rational rational::sub(rational r) {
  rational result(nom * r.den - r.nom * den, den * r.den);
  return result;
}

rational rational::mul(rational r) {
  rational result(nom * r.nom, den * r.den);
  return result;
}

rational rational::div(rational r) {
  rational result(nom * r.den, den * r.nom);
  return result;
}

int rational::gcd(int a, int b) {
  a = abs(a);
  b = abs(b);

  while(a > 0 && b > 0) {
    if(a > b)
      a = a % b;
    else
      b = b % a;
  }

  return a + b;
}

void rational::print() {
  cout << nom << "/" << den;
  return;
}
