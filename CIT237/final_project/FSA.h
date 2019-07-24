/*
 * Kevin Fernandes
 * December 2017
 *
 * This is the FSA class; it consits of all the things in the Machine
 * class, as well as a Directed graph (Digraph) for the representation
 * of transitions between states.
 */

#ifndef FSA_H
#define FSA_H
#include "Machine.h"
#include "Digraph.h"
#include "Dictionary.h"
#include <string>

using std::string;

struct BinData {
  unsigned alphaSize, stateSize, finalSize;
  char* alphabet;
  State* states;
  State* finals;
  State start;
  Transition** trans;
};

struct BinTrans {
  unsigned startID, endID;
  char symbol;
};

class FSA : public Machine {
private:
  State start;
  Digraph graph;

public:
  class FileError {};

  FSA();
  FSA(StateSet, StateSet, SymbolSet, State, Digraph);
  FSA(const FSA&);

  virtual void delta(char);
  void deltaHat(char*, unsigned);
  void deltaHat(string);

  SymbolSet getAlphabet();
  Digraph& getDigraph();
  bool isAccepting();

  void writeBinary(Dictionary<string, State>);
  void readBinary(Dictionary<string, State>&);
  FSA& operator=(const FSA&);
};

#endif // FSA_H
