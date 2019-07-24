/*
 * Kevin Fernandes
 * December 2017
 *
 * This is the symbol set, essentially a set of char's. It behaves similarly to
 * the state set. It is primarily used to hold characters, tell whether a given
 * char is part of the set, and whether another symbol set is a subset of this
 * instance of the set.
 */

#ifndef SYMBOL_SET_H
#define SYMBOL_SET_H
#include "Set.h"

class SymbolSet : public Set {
private:
  char* data;
  void resize();

public:
  SymbolSet();
  SymbolSet(const SymbolSet&);
  SymbolSet(char*, unsigned);
  ~SymbolSet();

  char* getData();
  bool isElement(char);
  void insertElement(char);
  bool isImproperSubset(SymbolSet);
  bool isSubset(SymbolSet);
  virtual unsigned getSize();
  SymbolSet& operator=(const SymbolSet&);
};

#endif // SYMBOL_SET_H
