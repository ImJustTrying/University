/*
 * This Directed graph implementation is specific to FSA's and PDA's, since
 * the following requirements must be made:
 * 1. Every vertex must have an edge between it and every other vertex
 * 2. Every edge from one vertex must have a unique weight (i.e. a unique symbol)
 */

#ifndef DIGRAPH_H
#define DIGRAPH_H
#include "State.h"
#include "Transition.h"

class Digraph {
private:
  Transition** transLists;
  State* states;
  unsigned stateCount;
  unsigned alphaCount;

public:
  class InvalidNode {};

  Digraph();
  Digraph(const Digraph&);
  Digraph(State*, Transition**, unsigned, unsigned);
  ~Digraph();

  Transition** getTransitions();
  unsigned getStateCount();
  unsigned getAlphaCount();
  State getNextState(State, char);
  Digraph& operator=(const Digraph&);
};

#endif // DIGRAPH_H
