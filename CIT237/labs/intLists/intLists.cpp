/*
  Kevin Fernandes
  November 2017

  This program inserts 10000 random integers into an array and a vector, doing
  so so that the arrays are always in sorted order, and timing the process.

  Along with this, we make a new linked list class and do the same as we have
  done with the array and vector, as well as adding new functions that print
  the middle 300 elements in all data structures.
*/

#include <cstdlib>
#include <ctime>
#include <new>
#include <iostream>
#include <vector>
#include "NumberList.h"

using namespace std;

void insertIntoArray(int*, int, int);
void shift(int*, int, int);
bool isSorted(int*, int);
void printArray(int*, int);

void insertIntoVector(vector<int>*, int, int);
void shiftVector(vector<int>*, int, int);
bool isVectorSorted(vector<int>*);
void printVector(vector<int>*);


int main() {
  const int SIZE = 10000;
  const int LL_SIZE = 50000;
  int* A;
  NumberList LL;
  vector<int> V(SIZE);
  clock_t timer;

  try {
    A = new int[SIZE]();
  } catch (bad_alloc& ba) {
    cout << "Allocation error: " << ba.what() << endl;
    exit(EXIT_FAILURE);
  }

  srand(time(NULL));

  // Array timer
    timer = clock();
    for (int i = 0; i < SIZE; i++) {
      insertIntoArray(A, i + 1, rand() + 1);
    }
    timer = clock() - timer;

    cout << "Sorted: " << isSorted(A, SIZE) << endl;
    cout << "Runtime: " << ((double)timer) / CLOCKS_PER_SEC << " seconds\n";

  // Vector timer
    timer = clock();
    for (int i = 0; i < SIZE; i++) {
      insertIntoVector(&V, i + 1, rand() + 1);
    }
    timer = clock() - timer;

    cout << "Sorted: " << isVectorSorted(&V) << endl;
    cout << "Runtime: " << ((double)timer) / CLOCKS_PER_SEC << " seconds\n";


  // Linked List timer
    timer = clock();
    for (int i = 0; i < LL_SIZE; i++) {
      LL.insertSorted(rand() + 1);
    }
    timer = clock() - timer;

    cout << "Sorted: " << LL.isSorted() << endl;
    cout << "Runtime: " << ((double)timer) / CLOCKS_PER_SEC << " seconds\n";

  cout << "Array: ";
  printArray(A, SIZE);
  cout << '\n';

  cout << "Vector: ";
  printVector(&V);
  cout << '\n';

  cout << "Linked List: ";
  LL.print300();
  cout << endl;

  delete[] A;
  system("pause");
  return 0;
}


void insertIntoArray(int* A, int n, int value) {
  for (int i = 0; i < n; i++) {
    if (A[i] > value || A[i] == 0) {
      shift(A, n, i);
      A[i] = value;
      return;
    }
  }
  return;
}

void insertIntoVector(vector<int>* V, int n, int value) {
  for (int i = 0; i < n; i++) {
    if (V->at(i) > value || V->at(i) == 0) {
      shiftVector(V, n, i);
      V->at(i) = value;
      return;
    }
  }
  return;
}

// shifts all of the values in the array one space to the right
void shift(int* A, int n, int from) {
  int temp;
  for (int i = from+1; i < n; i++) {
    temp = A[from];
    A[from] = A[i];
    A[i] = temp;
  }
  return;
}

void shiftVector(vector<int>* V, int n, int from) {
  int temp;
  for (int i = from+1; i < n; i++) {
    temp = V->at(from);
    V->at(from) = V->at(i);
    V->at(i) = temp;
  }
  return;
}

bool isSorted(int* A, int n) {
  for (int i = 0; i < n-1; i++) {
    if (A[i] > A[i+1]) {
      return false;
    }
  }
  return true;
}

bool isVectorSorted(vector<int>* V) {
  int n = V->size();
  for (int i = 0; i < n-1; i++) {
    if (V->at(i) > V->at(i+1)) {
      return false;
    }
  }
  return true;
}

void printArray(int* A, int n) {
  for (int i = n / 2 - 150; i < n / 2 + 150; i++) {
    cout << A[i] << '\n';
  }
}

void printVector(vector<int>* V) {
  int n = V->size() / 2;
  for (int i = n - 150; i < n + 150; i++) {
    cout << V->at(i) << '\n';
  }
}
