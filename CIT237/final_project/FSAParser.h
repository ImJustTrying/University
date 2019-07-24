/*
 * This is the Parser class for the FSA. The implementation is quite lengthy,
 * so this header should serve as a useful reference when looking at the
 * implementation file. This class is meant to:
 * 1. Read in the data from the file (of a given filename)
 * 2. Parse that data
 * 3. Build a new FSA, given there are no errors in the file
 * 4. Catch errors in the file
 */

#ifndef FSA_PARSER_H
#define FSA_PARSER_H
#include <string>
#include "Machine.h"
#include "FSA.h"
#include "Dictionary.h"

using std::string;

class FSAParser {
private:
  string filename;
  FSA* mach;
  char* fileContents;
  unsigned fileLength, line, pos;
  Dictionary<string, State> dict;

  // Helper functions for gen*() functions
  StateSet genStates(Dictionary<string, State>&);
  StateSet genFinals(Dictionary<string, State>);
  SymbolSet genAlphabet();
  State genStartState(Dictionary<string, State>);
  Digraph genDigraph(Dictionary<string, State>, SymbolSet);

  // Helper functions for helper functions
  void nextChar();
  char* getWord();
  void checkSymbol(char);

public:
  class FileError {};
  class ParseError {
  private:
    int errCode;
    unsigned line, pos;
    char sym;

  public:
    ParseError(int i, unsigned l, unsigned p, char s) {
      errCode = i;
      line = l;
      pos = p;
      sym = s;
    }

    ParseError(int i, unsigned l, unsigned p) {
      errCode = i;
      line = l;
      pos = p;
      sym = '\0';
    }


    unsigned linenumber() {
      return line;
    }
    unsigned position() {
      return pos;
    }
    int code() {
      return errCode;
    }
    char symbol() {
      return sym;
    }
  };


  FSAParser(string);
  FSAParser();
  ~FSAParser();

  Dictionary<string, State>& getDictionary();
  void setFilename(string);
  string getFilename();
  void readFile();
  // This will return dynamically allocated machines, used for copying, not
  // direct use.
  FSA& genFSA();
};

#endif // FSA_PARSER_H
