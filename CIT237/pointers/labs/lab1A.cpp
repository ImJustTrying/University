/*
  Kevin Fernandes
  September, 2017

  Create 1 variable and 1 pointer to a float, an int, a short, a long, a double
  and a character. Print out the variable, its adress, the pointer, and the
  value the pointer is looking at.
*/

#include <iostream>

template <typename T> void printPointer(T* ptr) {
  std::cout << "value of pointer: " << ptr << "\n";
  std::cout << "value where pointer is looking: " << *ptr << "\n\n";
}

int main() {
  int i = 100;
  short s = 10;
  long l = 1;
  float f = 1.0;
  double d = 10.0;
  char c = 'a';

  int* pi = &i;
  short* ps = &s;
  long* pl = &l;
  float* pf = &f;
  double* pd = &d;
  char* pc = &c;

  std::cout << "int value: " << i << '\n';
  std::cout << "address of value: " << &i << '\n';
  printPointer<int>(pi);
  *pi *= 5;
  std::cout << "int value: " << i << '\n';
  std::cout << "address of value: " << &i << '\n';
  printPointer<int>(pi);
  std::cout << std::string(15, '-') << '\n';

 
  std::cout << "short value: " << s << '\n';
  std::cout << "address of value: " << &s << '\n';
  printPointer<short>(ps);
  *ps *= 20;
  std::cout << "short value: " << s << '\n';
  std::cout << "address of value: " << &s << '\n';
  printPointer<short>(ps);
  std::cout << std::string(15, '-') << '\n';

  std::cout << "long value: " << l << '\n';
  std::cout << "address of value: " << &l << '\n';
  printPointer<long>(pl);
  *pl *= 1000;
  std::cout << "long value: " << l << '\n';
  std::cout << "address of value: " << &l << '\n';
  printPointer<long>(pl);
  std::cout << std::string(15, '-') << '\n';


  std::cout << "float value: " << f << '\n';
  std::cout << "address of value: " << &f << '\n';
  printPointer<float>(pf);
  *pf *= 21;
  std::cout << "float value: " << f << '\n';
  std::cout << "address of value: " << &f << '\n';
  printPointer<float>(pf);
  std::cout << std::string(15, '-') << '\n';


  std::cout << "double value: " << d << '\n';
  std::cout << "address of value: " << &d << '\n';
  printPointer<double>(pd);
  *pd *= 9 + 10;
  std::cout << "double value: " << d << '\n';
  std::cout << "address of value: " << &d << '\n';
  printPointer<double>(pd);
  std::cout << std::string(15, '-') << '\n';


  std::cout << "char value: " << c << '\n';
  std::cout << "address of value: " << &c << '\n';
  printPointer<char>(pc);
  *pc = 'A';
  std::cout << "char value: " << c << '\n';
  std::cout << "address of value: " << &c << '\n';
  printPointer<char>(pc);
  std::cout << std::string(15, '-') << '\n';

  return 0; 
}

