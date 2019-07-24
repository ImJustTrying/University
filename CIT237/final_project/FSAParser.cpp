#include "FSAParser.h"
#include "Dictionary.h"

#include <fstream> // ifstream, fstream::failure
#include <new> // std::bad_alloc
#include <cstring> // strncpy(char*, char*, size_t);
#include <cctype> // isspace(char)
#include <string>

using std::fstream;
using std::bad_alloc;
using std::ifstream;
using std::string;
using std::ios;

FSAParser::FSAParser() {
  filename = "";
  fileLength = 0;
  line = 2;
  pos = 5;
  fileContents = nullptr;
  mach = nullptr;
}

FSAParser::FSAParser(string fn) {
  filename = fn;
  mach = nullptr;
  pos = 5;
  fileContents = nullptr;
  fileLength = 0;
  line = 2;
}

FSAParser::~FSAParser() {
  if (fileContents != nullptr) { delete[] fileContents; }
  if (mach != nullptr) { delete mach; }
}

Dictionary<string, State>& FSAParser::getDictionary() {
  return dict;
}

void FSAParser::setFilename(string s) {
  filename = s;
}

string FSAParser::getFilename() {
  return filename;
}

// main function of this program
void FSAParser::readFile() {
  ifstream in;
  try {
    in.open(filename, ios::in);
  } catch(fstream::failure& f) {
    throw FileError();
  }

  in.seekg(0, in.end);
  fileLength = in.tellg();

  try {
    fileContents = new char[fileLength];
  } catch (bad_alloc& e) {
    throw FileError();
  }

  if (in.is_open()) {
    in.seekg(0, in.beg);
    in.read(fileContents, fileLength);
  }

  return;
}

void FSAParser::checkSymbol(char s) {
  char buf;
  nextChar();
  buf = fileContents[pos];
  if (buf != s) { throw ParseError(0, line, pos, buf); }
}

void FSAParser::nextChar() {
  if (pos >= fileLength) { throw ParseError(3, line, pos); }
  pos++;
  char buf = fileContents[pos];

  while (isspace(buf)) {
    if (pos >= fileLength) { throw ParseError(3, line, pos); }
    if (buf == '\n' || buf == '\r') { line++; }
    buf = fileContents[++pos];
  }
}

// this returns a dynamically allocated buffer containing the next whole word
// in the file
char* FSAParser::getWord() {
  char* wordBuf = new char[80];
  unsigned i = 0;
  nextChar();

  while (i < 80 && !isspace(fileContents[pos])) {
    if (fileContents[pos] == ';') { i++; pos++; continue; }
    wordBuf[i] = fileContents[pos];
    i++; pos++;
  }

  if (i == 80 && !isspace(fileContents[pos])) {
    throw ParseError(2, line, pos);
  }

  wordBuf[i] = '\0';
  return wordBuf;
}

SymbolSet FSAParser::genAlphabet() {
  SymbolSet alphabet;
  char wordBuf[6];
  char buf;

   // find "ALPHA" keyword
  nextChar();
  strncpy(wordBuf, fileContents + pos, 5);
  pos += 5;
  wordBuf[5] = '\0';
  if (strcmp(wordBuf, "ALPHA") != 0) { throw ParseError(4, line, pos); }

  // find colon (for syntax)
  checkSymbol(':');

  // find open bracket
  checkSymbol('{');

  // copy alphabet symbols
  nextChar();
  buf = fileContents[pos];
  while (buf != '}') {
    alphabet.insertElement(buf);
    nextChar();
    buf = fileContents[pos];
  }

  // error check
  checkSymbol(';');

  return alphabet;
}

State FSAParser::genStartState(Dictionary<string, State> dict) {
  char wordBuf[80];
  char keywordBuf[6];
  char buf;
  unsigned i = 0;
  State s;

  // Do it again for "START"
  nextChar();
  strncpy(keywordBuf, fileContents + pos, 5);
  keywordBuf[5] = '\0';
  pos += 5;
  if (strcmp(keywordBuf, "START") != 0) { throw ParseError(4, line, pos); }

  // find colon (for syntax)
  checkSymbol(':');

  nextChar();
  while (i < 80 && !isspace(fileContents[pos])) {
    if (fileContents[pos] == ';') { break; }
    wordBuf[i] = fileContents[pos];
    i++; pos++;
  }
  pos--;
  wordBuf[i] = '\0';

  // check if the name of the state extends past 80 characters
  if (i == 80 && !isspace(fileContents[pos])) {
    throw ParseError(2, line, pos);
  }

  try {
    s = dict.getValue(string(wordBuf));
  } catch (Dictionary<string, State>::InvalidKey& e) {
    throw ParseError(2, line, pos);
  }

  checkSymbol(';');
  return s;
}

StateSet FSAParser::genStates(Dictionary<string, State>& dict) {
  StateSet states;
  unsigned stateCount = 0;
  char* word;
  char wordBuf[6];
  char buf;

  // find "STATE" keyword
  nextChar();
  strncpy(wordBuf, fileContents + pos, 5);
  wordBuf[5] = '\0';
  pos += 5;
  if (strcmp(wordBuf, "STATE") != 0) { throw ParseError(4, line, pos); }

  // find colon (for syntax)
  checkSymbol(':');

  // find open bracket
  checkSymbol('{');
 
  // Read all the state names and make a dictionary with the names as keys and
  // their state ID's as values
  nextChar();
  buf = fileContents[pos];
  pos--;
  while (buf != '}') {
    word = getWord();

    dict.addKeyValue(string(word), State(stateCount));
    states.insertElement(dict.getValue(string(word)));
    delete[] word;
    stateCount++;

    nextChar();
    buf = fileContents[pos];
    pos--;
  }

  pos++;
  checkSymbol(';');

  return states;
}

StateSet FSAParser::genFinals(Dictionary<string, State> dict) {
  char buf;
  char* word;
  char wordBuf[6];
  StateSet states;

  nextChar();
  strncpy(wordBuf, fileContents + pos, 5);
  wordBuf[5] = '\0';
  pos += 5;
  if (strcmp(wordBuf, "FINAL") != 0) { throw ParseError(4, line, pos); }

  // find colon (for syntax)
  checkSymbol(':');

  // find open bracket
  checkSymbol('{');
 
  // Read all the state names and check if they are in the dictionary
  // if they are, then push the state they correspond to into `states`
  nextChar();
  buf = fileContents[pos];
  while (buf != '}') {
    pos--;
    word = getWord();

    states.insertElement(dict.getValue(string(word)));
    delete[] word;
    nextChar();
    buf = fileContents[pos];
  }

  checkSymbol(';');
  return states;
}

Digraph FSAParser::genDigraph (Dictionary<string, State> dict, SymbolSet alpha) {
  char* word;
  char buffer;
  State fromBuf, toBuf;
  unsigned stateCount = dict.getSize();
  unsigned alphaSize = alpha.getSize();
  State* states = new State[stateCount];
  Transition** trans = new Transition*[stateCount];
  Digraph d;

  for (unsigned i = 0; i < stateCount; i++) {
    trans[i] = new Transition[alphaSize];

    word = getWord();

    try {
      fromBuf = dict.getValue(string(word));
    } catch (Dictionary<string, State>::InvalidKey& e) {
      throw ParseError(2, line, pos);
    }

    states[i] = fromBuf;
    delete[] word;
    checkSymbol(':');

    for (unsigned j = 0; j < alphaSize; j++) {
      checkSymbol('(');
      word = getWord();

      try {
        toBuf = dict.getValue(string(word));
      } catch (Dictionary<string, State>::InvalidKey& e) {
        throw ParseError(2, line, pos);
      }
      delete[] word;

      nextChar();
      buffer = fileContents[pos];
      if (!alpha.isElement(buffer)) { throw ParseError(2, line, pos, buffer); }
      trans[i][j] = Transition(buffer, fromBuf, toBuf);

      checkSymbol(')');
    }

    checkSymbol(';');
  }

  for (int i = 0; i < stateCount; i++) {
  }

  for (int i = 0; i < stateCount; i++) {
    for (int j = 0; j < alphaSize; j++) {
    }
  }

  d = Digraph(states, trans, stateCount, alphaSize);

  delete[] states;
  for (unsigned i = 0; i < stateCount; i++) {
    delete[] trans[i];
  }
  delete[] trans;

  return d;
}

// Reads file for machine parts (i.e. states, alphabet, transitions)
FSA& FSAParser::genFSA() {
  // machine parts
  SymbolSet alphabet;
  StateSet states, finals;
  State start;
  Digraph graph;
  State temp;

  // These NEED TO BE DONE IN THIS ORDER
  alphabet = genAlphabet();
  states = genStates(dict);
  start = genStartState(dict);
  finals = genFinals(dict);
  graph = genDigraph(dict, alphabet);

  mach = new FSA(states, finals, alphabet, start, graph);
  return *mach;
}
