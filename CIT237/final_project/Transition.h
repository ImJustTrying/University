/*
 * Kevin Fernandes
 * December 2017
 *
 * This is the Transition class, which is used to represent arrows in the
 * Directed graph between states for the machine.
 */

#ifndef TRANSITION_H
#define TRANSITION_H
#include "State.h"

class Transition {
private:
  char symbol;
  State startState;
  State endState;

public:
  Transition();
  Transition(char, State, State);
  Transition(const Transition&);

  char getSymbol();
  State getStartState();
  State getEndState();
  void setStartState(State);
  void setEndState(State);
  Transition& operator=(const Transition&);
};

#endif // TRANSITION_H
