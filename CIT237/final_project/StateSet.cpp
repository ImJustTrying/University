#include "StateSet.h"
#include <cstddef>

StateSet::StateSet() {
  size = 0;
  capacity = 1;
  data = new State[1];
}

StateSet::StateSet(const StateSet& s) {
  size = s.size;
  capacity = s.capacity;
  data = new State[s.capacity];

  for (unsigned i = 0; i < s.size; i++) {
    data[i] = s.data[i];
  }
}

StateSet::StateSet(State* elems, unsigned n) {
  size = 0;
  capacity = n;
  data = new State[n];

  for (int i = 0; i < n; i++) {
    if (!isElement(elems[i])) {
      data[size] = elems[i];
      size++;
    }
  }
}

StateSet::~StateSet() {
  delete[] data;
}

State* StateSet::getData() {
  return data;
}

bool StateSet::isElement(State t) {
  if (size == 0) { return false; }
  for (unsigned i = 0; i < size; i++) {
    if (data[i] == t) { return true; }
  }
  return false;
}

void StateSet::insertElement(State t) {
  if (size >= capacity) {
    resize();
  }

  if (!isElement(t)) {
    data[size] = t;
    size++;
  }

  return; 
}

void StateSet::resize() {
  if (capacity == 0) { capacity = 1; }
  State* temp = new State[capacity * 2];

  for (int i = 0; i < capacity; i++) {
    temp[i] = data[i];
  }

  capacity *= 2;
  delete[] data;
  data = temp;
  return;
}

bool StateSet::isImproperSubset(StateSet S) {
  if (S.getSize() < size) { return false; }

  for (unsigned i = 0; i < size; i++) {
    if (!S.isElement(data[i])) {
      return false;
    }
  }
  return true;
}

bool StateSet::isSubset(StateSet S) {
  if (S.getSize() <= size) { return false; }

  for (unsigned i = 0; i < size; i++) {
    if (!S.isElement(data[i])) {
      return false;
    }
  }
  return true;
}

unsigned StateSet::getSize() {
  return size;
}

StateSet& StateSet::operator=(const StateSet& S) {
  capacity = S.capacity;
  size = S.size;

  delete[] data;
  data = new State[capacity];

  for (unsigned i = 0; i < size; i++) {
    data[i].setID( S.data[i].getID() );
  }

  return *this;
}
