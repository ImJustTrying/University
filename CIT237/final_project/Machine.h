/*
 * Kevin Fernandes
 * December 2017
 *
 * This is the abstract class for the machine types. Originally intended
 * to be a base class to multiple classes (for the different machines),
 * This machine contains all the things these machines share in common.
 */
#ifndef MACHINE_H
#define MACHINE_H
#include "StateSet.h"
#include "SymbolSet.h"

class Machine {
public: 
  StateSet states; 
  StateSet finalStates;
  SymbolSet alphabet;
  State current;

  Machine() {}
  Machine(StateSet Q, StateSet F, SymbolSet S, State q0) {
    states = Q;
    finalStates = F;
    alphabet = S;
    current = q0;
  }

/*  Machine& operator=(const Machine& m) {
    states = m.states;
    finalStates = m.finalStates;
    alphabet = m.alphabet;
    current = m.current;
    return *this;
  }
*/

  virtual void delta(char) = 0;
  State getCurrentState() { return current; }
};

#endif // MACHINE_H
