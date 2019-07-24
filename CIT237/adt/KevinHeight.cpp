/*
  Kevin Fernandes
  September, 2017

  This program uses the Height struct which contains feet and inches.
  We pass pointers to Height structs as arguments, and return them from 
  functions. We also take user input to get our feet and inch values.
*/

#include <iostream>

struct Height {
  int feet;
  double inches;
};
 

void printHeight(Height);
void inputHeight(Height*);
Height getHeight();

int main() {
  std::cout << "For person 1:\n";
  Height h = getHeight();

  Height* ptr = new Height;
  std::cout << "For person 2:\n";
  inputHeight(ptr);

  std::cout << "Person 1's height: ";
  printHeight(h);
  std::cout << "Person 2's height: ";
  std::cout << ptr->feet << "' " << ptr->inches << "\"\n";

  delete ptr;
  return 0;
}

Height getHeight() { 
  Height h;
  std::cout << "Please enter your height\nFeet: ";
  std::cin >> h.feet;
  std::cout << "Inches: ";
  std::cin >> h.inches;
  std::cout << '\n';
  return h;
}

void inputHeight(Height* h) {
  std::cout << "Please enter your height\nFeet: ";
  std::cin >> h->feet;
  std::cout << "Inches: ";
  std::cin >> h->inches;
  std::cout << '\n'; 
}

void printHeight(Height h) {
  std::cout << h.feet << "' " << h.inches << "\"\n";
}
 
