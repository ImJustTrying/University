/*
 * Kevin Fernandes
 * September 2017
*/

#include <iostream>

double cubeit1(double d);
void cubeit2(double& d);
void cubeit3(double* d);

int main() {
  double d = 3;
  std::cout << "cubeit1: " << cubeit1(d) << '\n';
  cubeit2(d);
  std::cout << "cubeit2: " << d << '\n';
  cubeit3(&d);
  std::cout << "cubeit3: " << d << '\n';
  return 0;
}

double cubeit1(double d) {
  return d * d * d;
}

void cubeit2(double& d) {
  d = d * d * d;
}

void cubeit3(double* d) {
  *d = *d * *d * *d;
}

