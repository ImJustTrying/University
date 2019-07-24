/*
 Kevin Fernandes
 September 2017

  Creates 3 integer values and 1 pointer, prints the values, their adresses, 
  the value of a pointer looking at that value, and the value the pointer is 
  pointing to.
*/

#include <iostream>

void printPointer(int*);

int main() {
  int a = 10, b = 50, c = 1000;

  int* ptr = &a;
  // can't do this in a function, since it will create a copy of `a` at a new
  // memory address
  std::cout << "value: " << a << '\n';
  std::cout << "address of value: " << &a << '\n';
  printPointer(ptr);
  *ptr *= 2;
  std::cout << "value: " << a << '\n';
  std::cout << "address of value: " << &a << '\n'; 
  printPointer(ptr);
  std::cout << std::string(10, '-') << std::endl;

  ptr = &b;
  std::cout << "value: " << b << '\n';
  std::cout << "address of value: " << &b << '\n'; 
  printPointer(ptr);
  *ptr *= 3;
  std::cout << "value: " << b << '\n';
  std::cout << "address of value: " << &b << '\n'; 
  printPointer(ptr);
  std::cout << std::string(10, '-') << std::endl;

  ptr = &c;
  std::cout << "value: " << c << '\n';
  std::cout << "address of value: " << &c << '\n'; 
  printPointer(ptr);
  *ptr *= 4;
  std::cout << "value: " << c << '\n';
  std::cout << "address of value: " << &c << '\n'; 
  printPointer(ptr);
  std::cout << std::string(10, '-') << std::endl;

  return 0;
}

void printPointer(int* ptr) {
  std::cout << "value of pointer: " << ptr << '\n';
  std::cout << "value where pointer is looking: " << *ptr << "\n\n";
  return;
}

