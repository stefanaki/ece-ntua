#include <iostream>
#ifndef CONTEST
#include "fullratio.hpp"
#endif

using namespace std;

rational::rational(int n, int d) {
  nom = n / gcd(n, d);
  den = d / gcd(n, d);

  if (nom == 0) {
    den = 1;
  } else if (den < 0) {
    nom *= -1;
    den *= -1;
  }

  return;
}

rational operator+(const rational &x, const rational &y) {
  rational result(x.nom * y.den + y.nom * x.den, x.den * y.den);
  return result;
}

rational operator-(const rational &x, const rational &y) {
  rational result(x.nom * y.den - y.nom * x.den, x.den * y.den);
  return result;
}

rational operator*(const rational &x, const rational &y) {
  rational result(x.nom * y.nom, x.den * y.den);
  return result;
}

rational operator/(const rational &x, const rational &y) {
  rational result(x.nom * y.den, y.nom * x.den);
  return result;
}

ostream &operator<<(ostream &out, const rational &x) {
  out << x.nom << "/" << x.den;
  return out;
}

int rational::gcd(int a, int b) {
  a = abs(a);
  b = abs(b);

  while (a > 0 && b > 0) {
    if (a > b)
      a = a % b;
    else
      b = b % a;
  }

  return a + b;
}
