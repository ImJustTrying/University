#include "FSA.h"
#include <fstream>

using std::ofstream;
using std::ifstream;
using std::ios_base;
using std::ios;

FSA::FSA() {}

FSA::FSA(StateSet Q, StateSet F, SymbolSet S, State q0, Digraph D) {
  states = Q;
  finalStates = F;
  alphabet = S;
  current = q0;
  start = q0;
  graph = D;
}

FSA::FSA(const FSA& fsa) {
  states = fsa.states;
  finalStates = fsa.finalStates;
  alphabet = fsa.alphabet;
  current = fsa.current;
  graph = fsa.graph;
}

bool FSA::isAccepting() {
  return finalStates.isElement(current);
}

void FSA::delta(char symbol) {
  current = graph.getNextState(current, symbol);
  return;
}

SymbolSet FSA::getAlphabet() {
  return alphabet;
}

/*
 * Recrusive solutions
 *
 * For c-string --
 * void deltaHat(char* str, unsigned beg, unsigned end) {
 *   if (beg >= end) {
 *     return;
 *   }
 *   current = delta(str[0]);
 *   deltaHat(str, beg + 1, end);
 * }
 *
 * For std::string -- 
 * void deltaHat(string s) {
 *   if (s.length() == 0) { return; }
 *   current = delta(s[0]);
 *   deltaHat(s.substr(1, s.length()-1));
 * }
 */

// Iterative solutions
void FSA::deltaHat(char* str, unsigned n) {
  // we use a temporary variable so we don't update `current` every iteration
  // incase there is an invalid symbol in `str`
  State temp = current;

  for (int i = 0; i < n; i++) {
    temp = graph.getNextState(temp, str[i]);
  }

  current = temp;
  return;
}

void FSA::deltaHat(string s) {
  int n = s.length();
  for (int i = 0; i < n; i++) {
    delta(s[i]);
  }
}

Digraph& FSA::getDigraph() {
  return graph;
}

/*
 * Here we write the FSA components in the following order:
 * 1. Size of alphabet
 * 2. Size of state set
 * 3. Size of final state set
 * 4. The alphabet (as char's)
 * 5. The state set (as ID's)
 * 6. The final state set
 * 7. The start state
 * 8. The transitions (as BinTrans's)
 */
void FSA::writeBinary(Dictionary<string, State> dict) {
  ofstream bin;
  try {
    bin.open("save.dat", ios::out | ios::binary | ios::trunc);
  } catch (ios_base::failure& f) {
    throw FileError();
  }

  unsigned i, j, index, buf, counter = 0;
  unsigned alphaSize = alphabet.getSize();
  unsigned stateSize = states.getSize();
  unsigned finalSize = finalStates.getSize();

  char* alpha = alphabet.getData();
  State* ss = states.getData();
  State* fs = finalStates.getData();
  Transition** ts = graph.getTransitions();
  BinTrans bt;


  // write sizes
  bin.write(reinterpret_cast<char*>(&alphaSize), sizeof(alphaSize));
  bin.write(reinterpret_cast<char*>(&stateSize), sizeof(stateSize));
  bin.write(reinterpret_cast<char*>(&finalSize), 
            sizeof(finalSize));

  // write sets
  bin.write(alpha, sizeof(char) * alphaSize);

  for (i = 0; i < stateSize; i++) {
    buf = ss[i].getID();
    bin.write(reinterpret_cast<char*>(&buf), sizeof(buf));
  }

  for (i = 0; i < finalSize; i++) {
    buf = fs[i].getID();
    bin.write(reinterpret_cast<char*>(&buf), sizeof(buf));
  }

  buf = start.getID();
  bin.write(reinterpret_cast<char*>(&buf), sizeof(buf));

  // copy transition data into BinTrans structure and write that structure
  for (i = 0; i < stateSize; i++) {
    for (j = 0; j < alphaSize; j++) {
      bt.symbol = ts[i][j].getSymbol();
      bt.startID = ts[i][j].getStartState().getID();
      bt.endID = ts[i][j].getEndState().getID();
      bin.write(reinterpret_cast<char*>(&bt), sizeof(bt));
      counter++;
    }
  }

  // write state names
  for (i = 0; i < stateSize; i++) {
    // write length of string
    buf = dict.getKey(ss[i]).size();
    bin.write(reinterpret_cast<char*>(&buf), sizeof(buf));

    const char* strBuf = dict.getKey(ss[i]).c_str();
    bin.write(strBuf, buf);
  }

  bin.close();
  return;
}

// This reads data from the binary file and copies it to the current instance's
// machine componants
void FSA::readBinary(Dictionary<string, State>& dict) {
  ifstream bin;
  try {
    bin.open("save.dat", ios::out | ios::binary);
  } catch (ios_base::failure& f) {
    throw FileError();
  }

  // counters and buffers
  unsigned i, j, stateSize, alphaSize, finalSize, buf, counter = 0;
  char* symsBuf;
  char* strBuf;
  BinTrans bt;

  // machine components
  SymbolSet syms;
  StateSet ss, fs;
  State* stateBuf;
  Transition** tranBuf;
  Digraph d;

  // Reading begins
  bin.read(reinterpret_cast<char*>(&stateSize), sizeof(stateSize));
  bin.read(reinterpret_cast<char*>(&alphaSize), sizeof(alphaSize));
  bin.read(reinterpret_cast<char*>(&finalSize), sizeof(finalSize));


  // read alphabet, copy, and delete variable
  stateBuf = new State[stateSize];
  symsBuf = new char[alphaSize];
  tranBuf = new Transition*[stateSize];

  bin.read(symsBuf, alphaSize);
  for (i = 0; i < alphaSize; i++) {
    syms.insertElement(symsBuf[i]);
  }
  delete[] symsBuf;

  for (i = 0; i < stateSize; i++) {
    bin.read(reinterpret_cast<char*>(&buf), sizeof(buf));
    stateBuf[i] = State(buf);
    ss.insertElement(State(buf));
  }

  for (i = 0; i < finalSize; i++) {
    bin.read(reinterpret_cast<char*>(&buf), sizeof(buf));
    fs.insertElement(State(buf));
  }

  bin.read(reinterpret_cast<char*>(&buf), sizeof(buf));
  start = State(buf);

  for (i = 0; i < stateSize; i++) {
    tranBuf[i] = new Transition[alphaSize];

    for (j = 0; j < alphaSize; j++) {
    bin.read(reinterpret_cast<char*>(&bt), sizeof(bt));
      tranBuf[i][j] = Transition(bt.symbol, State(bt.startID), State(bt.endID));
      counter++;
    }
  }

  for (i = 0; i < stateSize; i++) {
    bin.read(reinterpret_cast<char*>(&buf), sizeof(buf));
    strBuf = new char[buf+1];
    bin.read(strBuf, buf);
    strBuf[buf] = '\0';
    dict.addKeyValue(string(strBuf), State(i));
    delete[] strBuf;
  }

  d = Digraph(stateBuf, tranBuf, stateSize, alphaSize);

  states = ss;
  finalStates = fs;
  alphabet = syms;
  graph = d;

  for (i = 0; i < stateSize; i++) {
    delete[] tranBuf[i];
  }
  delete[] tranBuf;
  delete[] stateBuf;

  return;
}

FSA& FSA::operator=(const FSA& fsa) {
  states = fsa.states;
  finalStates = fsa.finalStates;
  alphabet = fsa.alphabet;
  current = fsa.current;
  graph = fsa.graph;

  return *this;
}
