/*
 * Kevin Fernandes
 * December 2017
 *
 * This is the main testing file for the entire project.
 * This includes tests for all classes.
 */

#include <iostream>

#include "Set.h"
#include "SymbolSet.h"
#include "State.h"
#include "Transition.h"
#include "Stack.h"
#include "Digraph.h"
#include "StateSet.h"
#include "FSA.h"
#include "FSAParser.h"
#include "Dictionary.h"

bool testState();
bool testTransition();
bool testSymbolSet();
bool testStateSet();
bool testStack();
bool testDigraph();
bool testFSA();
bool testDictionary();
bool testParserFSA();

using namespace std;

int main() {
  bool test = testState() && testTransition() && testSymbolSet() && testStack();
  test = test && testDigraph() && testStateSet() && testFSA();
  test = test && testDictionary() && testParserFSA();

  if (test) {
    cout << "All tests passed!\n";
    exit(EXIT_SUCCESS);
  } else {
    cout << "Some tests failed!\n";
    exit(EXIT_FAILURE);
  }
}

bool testParserFSA() {
  FSAParser p("test_machine.txt");
  FSA fsa;
  Digraph d;

  try {
    p.readFile();
  } catch (FSAParser::FileError& e) {
    cout << "FSAParser -- Error occrrued while opening test file\n";
    return false;
  }

  try {
    fsa = p.genFSA();
  } catch (FSAParser::ParseError& e) {
    cout << "FSAParser -- Error occurred during parsing:\nError -- code: ";
    cout << e.code() << " line: " << e.linenumber() << " pos: ";
    cout << e.position();
    if (e.symbol() != '\0') { cout << " symbol: " << e.symbol(); }
    cout << '\n';

    return false;
  }

  d = fsa.getDigraph();

  try {
    fsa.delta('0');
  } catch (Digraph::InvalidNode& e) {
    cout << "FSAParser -- Digraph is misinterpreted\n";
    return false;
  }

  if (fsa.getCurrentState().getID() != 0) {
    cout << "FSAParser -- FSA is incorrect\n";
    return false;
  }

  return true;
}

bool testDictionary() {
  Dictionary<string, int> dict;
  dict.addKeyValue("lul", 0);
  dict.addKeyValue("rofl", 2);

  try {
    dict.getValue("lul");
  } catch (Dictionary<string, int>::InvalidKey& e) {
    cout << "Dictionary -- getValue() failed on valid key\n";
    return false;
  }

  try {
    dict.getValue("omg");
  } catch (Dictionary<string, int>::InvalidKey& e) {
    return true;
  }

  cout << "Dictionary -- getValue() succeeded on invalid key\n";
  return false;
}

bool testFSA() {
  char syms[2] = { '0', '1' };
  SymbolSet symSet(syms, 2);

  State s0(0);
  State s1(1);
  State states[2] = { s0, s1 };
  State finals[1] = { s1 };
  StateSet ss(states, 2);
  StateSet sf(finals, 1);

  Transition t0('0', s0, s1);
  Transition t1('1', s0, s0);
  Transition t2('0', s1, s0);
  Transition t3('1', s1, s1);

  Transition ts0[2] = { t0, t1 };
  Transition ts1[2] = { t2, t3 };

  Transition* trans[2] = { ts0, ts1 };

  Digraph d(states, trans, 2, 2);
  FSA fsa(ss, sf, symSet, s0, d);
  FSA temp;
  temp = fsa;

  // testing section
  if (fsa.getCurrentState() != s0) {
    cout << "FSA -- Start state is not initialized\n";
    return false;
  }

  if (temp.getCurrentState() != s0) {
    cout << "FSA -- Start state is not initialized\n";
    return false;
  }

  try {
    fsa.delta('0');
  } catch (Digraph::InvalidNode& e) {
    cout << "FSA -- delta function is disfunctional\n";
    return false;
  }

  try {
    fsa.delta('1');
  } catch (Digraph::InvalidNode& e) {
    cout << "FSA -- delta function is incorrect\n";
    return false;
  }

  try {
    temp.delta('0');
  } catch (Digraph::InvalidNode& e) {
    cout << "FSA -- delta function is disfunctional\n";
    return false;
  }

  try {
    temp.delta('1');
  } catch (Digraph::InvalidNode& e) {
    cout << "FSA -- delta function is incorrect\n";
    return false;
  }

  if (s1 != fsa.getCurrentState()) {
    cout << "FSA -- delta function is disfunctional or transitions were not ";
    cout << "copied correctly\n";
    return false;
  }

  if (s1 != temp.getCurrentState()) {
    cout << "FSA -- delta function is disfunctional or transitions were not ";
    cout << "copied correctly\n";
    return false;
  }

  return true;
}

bool testDigraph() {
  State s0(0);
  State s1(1);
  State states[2] = { s0, s1 };

  Transition t0('0', s0, s1);
  Transition t1('1', s0, s0);
  Transition t2('0', s1, s0);
  Transition t3('1', s1, s1);

  Transition ts0[2] = { t0, t1 };
  Transition ts1[2] = { t2, t3 };

  Transition* trans[2] = { ts0, ts1 };

  Digraph d(states, trans, 2, 2);

  if (d.getNextState(s0, '0') != s1) {
    cout << "Digraph -- Next state accessor is disfunctional\n";
    return false;
  }

  if (d.getStateCount() != 2 || d.getAlphaCount() != 2) {
    cout << "Digraph -- State/Alpha counters are incorrect\n";
    return false;
  }

  return true;
}

bool testStateSet() {
  State s0(0);
  State s1(1);
  State s2(2);
  State ss[3] = { s0, s1, s2 };

  StateSet sSet(ss, 3);

  if (sSet.getSize() != 3) {
    cout << "StateSet -- Size is not responding to repeated symbols\n";
    return false;
  }
 
  if (!sSet.isElement(s0) || !sSet.isElement(s1)) {
    cout << "StateSet -- States are not being copied correctly\n";
    return false;
  }

  sSet.insertElement(s0);
  if (!sSet.isElement(s0)) {
    cout << "StateSet -- States are not being inserted correctly\n";
    return false;
  }

  if (sSet.getSize() != 3) {
    cout << "StateSet -- Size is not responding to insertion\n";
    return false;
  }

  if (!sSet.isImproperSubset(sSet)) {
    cout << "StateSet -- Improper subset procedure is disfunctional\n";
    return false;
  }

  return true;
}

bool testSymbolSet() {
  char symbols[] = { '0', '1', '0'};
  char symbols2[] = { '0' };
  SymbolSet symSet(symbols, 2);
  SymbolSet symSet2(symbols2, 1);

  if (symSet.getSize() != 2) {
    cout << "SymbolSet -- Size is not responding to repeated symbols\n";
    return false;
  }
 
  if (!symSet.isElement(symbols[0]) || !symSet.isElement(symbols[1])) {
    cout << "SymbolSet -- Symbols are not being copied correctly\n";
    return false;
  }

  symSet.insertElement('a');
  if (!symSet.isElement('a')) {
    cout << "SymbolSet -- Symbols are not being inserted correctly\n";
    return false;
  }

  if (symSet.getSize() != 3) {
    cout << "SymbolSet -- Size is not responding to insertion\n";
    return false;
  }

  if (!symSet2.isSubset(symSet)) {
    cout << "SymbolSet -- Subset procedure is disfunctional\n";
    return false;
  }

  if (!symSet.isImproperSubset(symSet)) {
    cout << "SymbolSet -- Improper subset procedure is disfunctional\n";
    return false;
  }

  return true;
}

bool testState() {
  State s0(1);
  State s1(1);
  State s2(2);
  State s3;
  s3 = s2;

  if (s1.getID() != s0.getID()) {
    cout << "State -- ID's are not equivalent\n";
    return false;
  }

  if (s2.getID() == s0.getID()) {
    cout << "State -- ID's are equivalent\n";
    return false;
  }

  if (s2 != s3) {
    cout << "State -- Assignment operator is disfunctional\n";
    return false;
  }

  return true;
}

bool testTransition() {
  State s0(1);
  State s1(1);
  State s2(2);

  Transition t0('0', s0, s1);
  Transition t1('1', s1, s0);
  Transition t2('0', s1, s2);
  Transition t3('1', s2, s0);

  if (t0.getSymbol() != '0') {
    cout << "Transitions -- Symbols are not entered correctly\n";
    return false;
  }

  if (t0.getSymbol() != t2.getSymbol()) {
    cout << "Transitions -- Symbols are not equivalent\n";
    return false;
  }

  return true;
}


bool testStack() {
  char alphabet[] = { 'a', 'b', 'c', 'd', 'e' };
  SymbolSet ss(alphabet, 5);
  Stack s(6, ss);
  
  for (int i = 0; i < 5; i++) {
    if (s.getSize() != i) {
      cout << "Stack -- Size is not changing on push\n";
      return false;
    }

    try {
      s.push(alphabet[i]);
    } catch (Stack::InvalidSymbol& e) {
      cout << "Stack -- Invalid symbol \"" << alphabet[i] << "\" detected\n";
    }
  }

  char buf = s.pop();
  if (buf != alphabet[4]) {
    cout << "Stack -- pop is not returning the correct symbols\n";
    return false;
  }

  return true;
}
