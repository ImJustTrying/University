#include "SymbolSet.h"
#include <cstddef>

SymbolSet::SymbolSet() {
  size = 0;
  capacity = 1;
  data = new char[1];
}

SymbolSet::SymbolSet(const SymbolSet& s) {
  size = s.size;
  capacity = s.capacity;
  data = new char[s.capacity];

  for (unsigned i = 0; i < s.size; i++) {
    data[i] = s.data[i];
  }
}

SymbolSet::SymbolSet(char* elems, unsigned n) {
  size = 0;
  data = new char[n];
  capacity = n;

  for (int i = 0; i < n; i++) {
    if (!isElement(elems[i])) {
      data[size] = elems[i];
      size++;
    }
  }
}

SymbolSet::~SymbolSet() {
  delete[] data;
}

char* SymbolSet::getData() {
  return data;
}

bool SymbolSet::isElement(char t) {
  if (size == 0) { return false; }
  for (unsigned i = 0; i < size; i++) {
    if (data[i] == t) { return true; }
  }
  return false;
}

void SymbolSet::insertElement(char t) {
  if (size >= capacity) {
    resize();
  }

  data[size] = t;
  size++;
  return; 
}

void SymbolSet::resize() {
  if (capacity == 0) { capacity = 1; }
  char* temp = new char[capacity * 2];

  for (int i = 0; i < capacity; i++) {
    temp[i] = data[i];
  }

  capacity *= 2;
  delete[] data;
  data = temp;
  return;
}

bool SymbolSet::isImproperSubset(SymbolSet S) {
  if (S.getSize() < size) { return false; }

  for (unsigned i = 0; i < size; i++) {
    if (!S.isElement(data[i])) {
      return false;
    }
  }
  return true;
}

bool SymbolSet::isSubset(SymbolSet S) {
  if (S.getSize() <= size) { return false; }

  for (unsigned i = 0; i < size; i++) {
    if (!S.isElement(data[i])) {
      return false;
    }
  }
  return true;
}

unsigned SymbolSet::getSize() {
  return size;
}

SymbolSet& SymbolSet::operator=(const SymbolSet& S) {
  capacity = S.capacity;
  size = S.size;

  delete[] data;
  data = new char[capacity];

  for (unsigned i = 0; i < size; i++) {
    data[i] = S.data[i];
  }

  return *this;
}
