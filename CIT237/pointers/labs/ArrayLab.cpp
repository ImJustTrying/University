/*
  Kevin Fernandes
  September, 2017

  Create an array of 63 random integers, and print them out in the following 
  ways: 1. Print all values, with 3 values per line
  2. Print all values that are divisible by 7
  3. Print every sixth value
*/

#include <iostream>
#include <cstdlib>

void printEverySixth(int[], int);
void printDivisible(int[], int);
void printPerLine(int[], int);

int main() {
  const int SIZE = 63;
  int array[SIZE];

  for (int i = 0; i < SIZE; i++) {
    array[i] = rand() % 20 + 1;
  }

  printPerLine(array, SIZE);
  printDivisible(array, SIZE);
  printEverySixth(array, SIZE);

  return 0;
}

void printPerLine(int array[], int n) {
  std::cout << "3 Elements per line: \n";
  int counter = 0;
  for (int i = 0; i < n; i++) {
    std::cout << array[i] << ' ';
    if (counter == 2) {
      std::cout << '\n';
    }
    counter++;
    counter %= 3;
  }
  std::cout << std::endl;
  return;
}

void printDivisible(int array[], int n) {
  std::cout << "Elements divisible by 7:\n";
  for (int i = 0; i < n; i++) {
    if (array[i] % 7 == 0) {
      std::cout << array[i] << ' ';
    }
  }
  std::cout << std::endl;
  return;
}

void printEverySixth(int array[], int n) {
  std::cout << "Every sixth element:\n";
  for (int i = 0; i < n; i+=6) {
    std::cout << array[i] << ' ';
  }
  std::cout << std::endl;
  return;
}

