/*
  Kevin Fernandes
  September 2017
  
  This program initializes and declares 3 integers and an integer pointer,
  and prints the following values:
  1. The value of the integers
  2. The address of the integers
  3. The value of the pointer
  4. The value the pointer is pointing to
*/

#include <iostream>

int main() {
  int a = 10; b = 1000, c = 30;
  int* ptr = &a;
  
  std::cout << "Value: " << a << "\nAddress of value: " << &a;
  std::cout << "Pointer: " << ptr << "\nValue pointer is looking at: " << *ptr;
  *ptr *= 2;
  std::cout << "Value: " << a << "\nAddress of value: " << &a;
  std::cout << "Pointer: " << ptr << "\nValue pointer is looking at: " << *ptr;
  
  ptr = &b;
  std::cout << "Value: " << a << "\nAddress of value: " << &a;
  std::cout << "Pointer: " << ptr << "\nValue pointer is looking at: " << *ptr;
  *ptr += 21;
  std::cout << "Value: " << a << "\nAddress of value: " << &a;
  std::cout << "Pointer: " << ptr << "\nValue pointer is looking at: " << *ptr;
  
  ptr = &c;
  std::cout << "Value: " << a << "\nAddress of value: " << &a;
  std::cout << "Pointer: " << ptr << "\nValue pointer is looking at: " << *ptr;
  *ptr -= 19;
  std::cout << "Value: " << a << "\nAddress of value: " << &a;
  std::cout << "Pointer: " << ptr << "\nValue pointer is looking at: " << *ptr;

  return 0;
}
