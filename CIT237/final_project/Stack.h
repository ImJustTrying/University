/*
 * Kevin Fernandes
 * December 2017
 *
 * This is a simple implementation of a stack, intended for use by the PDA
 * class. Though it is not used in the project, the data structure is still
 * useful for a multitude of purposes, e.g. parsing.
 */

#ifndef STACK_H
#define STACK_H
#include "SymbolSet.h"

class Stack {
private:
  char* data;
  SymbolSet alphabet;
  unsigned size, capacity;
  void resize();

public:
  class InvalidSymbol {};

  Stack(unsigned, SymbolSet);
  ~Stack();

  char pop();
  void push(char);
  unsigned getSize();
};

#endif // STACK_H
