#include "Digraph.h"
#include <cstddef>

Digraph::Digraph(State* stateList, Transition** transitions, unsigned n, unsigned m) {
  stateCount = n;
  alphaCount = m;
  states = new State[n];
  transLists = new Transition*[n];

  for (unsigned i = 0; i < n; i++) {
    transLists[i] = new Transition[m];
    states[i] = stateList[i];
    states[i].setID(i);

    for (unsigned j = 0; j < m; j++) {
      transLists[i][j] = transitions[i][j];
    }
  }
}

Digraph::Digraph(const Digraph& d) {
  stateCount = d.stateCount;
  alphaCount = d.alphaCount;
  states = new State[stateCount];
  transLists = new Transition*[stateCount];

  for (unsigned i = 0; i < stateCount; i++) {
    transLists[i] = new Transition[stateCount];
    states[i] = d.states[i];
    states[i].setID(i);

    for (unsigned j = 0; j < stateCount; j++) {
      transLists[i][j] = d.transLists[i][j];
    }
  }
}

Digraph::Digraph() {
  stateCount = 0;
  alphaCount = 0;
  states = nullptr;
  transLists = nullptr;
}

Digraph::~Digraph() {
  if (states != nullptr) { delete[] states; }

  if (transLists != nullptr) {
    for (int i = 0; i < stateCount; i++) {
      delete[] transLists[i];
    }
    delete[] transLists;
  }
}

Transition** Digraph::getTransitions() {
  return transLists;
}

unsigned Digraph::getStateCount() {
  return stateCount;
}

unsigned Digraph::getAlphaCount() {
  return alphaCount;
}

State Digraph::getNextState(State node, char symbol) {
  unsigned j = node.getID();
  Transition t;

  for (unsigned i = 0; i < alphaCount; i++) {
    t = transLists[j][i];

    if (t.getSymbol() == symbol) {
      return t.getEndState();
    }
  }

  throw InvalidNode();
}

Digraph& Digraph::operator=(const Digraph& d) {
  unsigned i, j;
  unsigned n = d.stateCount;
  unsigned m = d.alphaCount;

  if (states != nullptr) {
    delete[] states;
  }

  if (transLists != nullptr) {
    for (i = 0; i < stateCount; i++) {
      delete[] transLists[i];
    }

    delete[] transLists;
  }

  stateCount = n;
  alphaCount = m;
  states = new State[n];
  transLists = new Transition*[n];

  for (i = 0; i < n; i++) {
    transLists[i] = new Transition[m];
    states[i] = d.states[i];
    states[i].setID(i);

    for (j = 0; j < m; j++) {
      transLists[i][j] = d.transLists[i][j];
    }
  }

  return *this;
}
