/*
 * Kevin Fernandes
 * December 2017
 *
 * This file impelements a Dictionary (aka associative array, map, symbol 
 * table) for use in the Parser class. This is a template class, so we
 * do not seperate the .h file from the .cpp, and implement the functions
 * directly in this file.
 *
 * Here, we implement it using arrays. With a BST or Hash table it is more
 * efficient, but it's unneccesary given how few variables there are in a given
 * machine text file.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <vector>
#include <iostream>

using std::vector;
using std::cout;

template <typename T1, typename T2>
class Dictionary {
private:
  vector<T1> keys;
  vector<T2> values;

public:
  class InvalidKey {};
  class InvalidValue {};

  void addKeyValue(T1, T2);
  T2 getValue(T1);
  T1 getKey(T2);
  void printKeys();
  unsigned getSize();
};

template <typename T1, typename T2>
unsigned Dictionary<T1, T2>::getSize() {
  return keys.size();
}

template <typename T1, typename T2>
T2 Dictionary<T1, T2>::getValue(T1 key) {
  unsigned len = keys.size();

  for (unsigned i = 0; i < len; i++) {
    if (keys[i] == key) {
      return values[i];
    }
  }

  throw InvalidKey();
}

template <typename T1, typename T2>
T1 Dictionary<T1, T2>::getKey(T2 val) {
  unsigned len = values.size();

  for (unsigned i = 0; i < len; i++) {
    if (values[i] == val) {
      return keys[i];
    }
  }

  throw InvalidValue();
}

template <typename T1, typename T2>
void Dictionary<T1, T2>::printKeys() {
  unsigned n = keys.size();
  cout << "Keys = [";

  for (unsigned i = 0; i < n; i++) {
    cout << keys[i];
    i == n - 1 ? cout << "]\n" : cout << ", ";
  }
}

template <typename T1, typename T2>
void Dictionary<T1, T2>::addKeyValue(T1 key, T2 val) {
  keys.push_back(key);
  values.push_back(val);
  return;
}

#endif // DICTIONARY_H
