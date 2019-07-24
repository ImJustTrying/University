#include "Stack.h"

Stack::Stack(unsigned n, SymbolSet s) {
  capacity = n;
  data = new char[n];
  size = 0;
  alphabet = s;
}

Stack::~Stack() {
  delete[] data;
}

unsigned Stack::getSize() {
  return size;
}

char Stack::pop() {
  size--;
  return data[size];
}

void Stack::push(char s) {
  if (capacity == size) {
    resize();
  }

  if (!alphabet.isElement(s)) {
    throw InvalidSymbol();
  }

  data[size] = s;
  size++;
  return;
}

void Stack::resize() {
  if (capacity == 0) { capacity = 1; }
  char* temp = new char[capacity * 2];

  for (unsigned i = 0; i < capacity; i++) {
    temp[i] = data[i];
  }

  capacity *= 2;
  delete[] data;
  data = temp;
  return;
}
