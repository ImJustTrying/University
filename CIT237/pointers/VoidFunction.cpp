/*
Kevin Fernandes
September 9, 2017
*/

#include <iostream>

// This will not alter the contents since the `i` in the funciton context is a
// duplicate, not the actual variable (i.e. not the  pointer to the value of 
// `i`).
void add(int i) {
  i += 10;
}

int main() {
  int i = 5;
  std::cout << "Integer before add: " << i << '\n';
  add(i);
  std::cout << "Integer after add: " << i << std::endl; 
  return 0;
}

