#include "Transition.h"

Transition::Transition() {};

Transition::Transition(char sym, State start, State end) {
  symbol = sym;
  startState = start;
  endState = end;
}

Transition::Transition(const Transition& t) {
  symbol = t.symbol;
  startState = t.startState;
  endState = t.endState;
}

char Transition::getSymbol() {
  return symbol;
}

State Transition::getStartState() {
  return startState;
}

State Transition::getEndState() {
  return endState;
}

void Transition::setStartState(State s) {
  startState = s;
  return;
}

void Transition::setEndState(State s) {
  endState = s;
  return;
}

Transition& Transition::operator=(const Transition& t) {
  symbol = t.symbol;
  startState = t.startState;
  endState = t.endState;

  return *this;
}
