/*
Kevin Fernandes
September 9, 2017
*/

#include <iostream>

int main() {
  // declare and initialize an integer
  int i = 0;
  // decalre and initialize a pointer to `i`
  int* p = &i;
  // print them out
  std::cout << "i: " << i << "\n*p: " << *p << std::endl;

  // change the value of `i` with the pointer `p`
  *p = 100;

  // print again
  std::cout << "i: " << i << "\n*p: " << *p << std::endl;
  return 0;
}

