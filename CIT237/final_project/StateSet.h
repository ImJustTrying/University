/*
 * Kevin Fernandes
 * December 2017
 *
 * The state set is a container for an array of state objects, used to
 * encapsulate the data, and to compute set operations such as the subset
 * operator (whether a set is a subset of another set).
 */

#ifndef STATE_SET_H
#define STATE_SET_H

#include "Set.h"
#include "State.h"

class StateSet : public Set {
private:
  State* data;
  
  void resize();

public:
  StateSet();
  StateSet(const StateSet&);
  StateSet(State*, unsigned);
  ~StateSet();

  State* getData();
  bool isElement(State);
  void insertElement(State);
  bool isImproperSubset(StateSet);
  bool isSubset(StateSet);
  virtual unsigned getSize();
  StateSet& operator=(const StateSet&);
};

#endif // SYMBOL_SET_H
