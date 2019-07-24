/*
 * Kevin Fernandes
 * September 2017
 */
#include <iostream>
#include <cmath>

// returns array in the form [f, i] where `f` is the number of feet and `i` is
// the number of remaining inches; both are integers.
int* inches_to_feet(double inches) {
  static int array[2];
  array[0] = floor(floor(inches) / 12);
  array[1] = (int)floor(inches) % 12;
  return array;
}

int main() {
  double inches = 38.7;
  int* array = inches_to_feet(inches);
  std::cout << "Inches before: " << inches << '\n';
  std::cout << "Feet: " << *array << "\nInches: " << *(array + 1) << std::endl;
  return 0;
}
