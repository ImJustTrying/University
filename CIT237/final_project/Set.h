/*
 * Kevin Fernandes
 * December 2017
 *
 * This is a small class that, given more time, will generalize the two classes
 * StateSet and SymbolSet. For now, it is an abstract class, used for 
 * polymorphism.
 */

#ifndef SET_H
#define SET_H

class Set {
public:
  unsigned capacity, size;

  virtual unsigned getSize() = 0;
};

#endif // SET_H
