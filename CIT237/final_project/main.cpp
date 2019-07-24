/*
 * Kevin Fernandes
 * December 2017
 *
 * This is the main file, where the user sends in symbols or strings and the
 * machine (read from the file also input by the user) is emulated on those
 * symbols or strings.
 */

#include <iostream>
#include <cctype>
#include <fstream>

#include "FSAParser.h"

using namespace std;

int main() {
  FSAParser parser;
  FSA fsa;
  SymbolSet alphabet;
  string filename, inputString;
  char* buffer = new char[80];
  char temp = '\0', trash = '\0';
  unsigned i;
  bool errFlag = false;

  while (tolower(trash) != 'y' || tolower(trash) != 'n') {
    cout << "Would you like to use your saved file? (y or n): ";
    cin.get(trash);

    if (tolower(trash) == 'y') {
      try {
        fsa.readBinary(parser.getDictionary());
      } catch (FSA::FileError& e) {
        cout << "Error occurred while reading save.dat\n";
        exit(EXIT_FAILURE);
      }
      
      break;

    } else if (tolower(trash) == 'n') {
      cout << "Please enter the name of the file containing your machine: ";
      cin >> filename;

      parser.setFilename(filename);
      try {
        parser.readFile();
      } catch (FSAParser::FileError& e) {
        cout << "Error occurred while opening file.\nTerminating program\n";
        exit(EXIT_FAILURE);
      }

      try {
        fsa = parser.genFSA();
      } catch (FSAParser::ParseError& e) {
        cout << "FSAParser -- Error occurred during parsing:\nError -- code: ";
        cout << e.code() << " line: " << e.linenumber() << " pos: ";
        cout << e.position();
        if (e.symbol() != '\0') { cout << " symbol: " << e.symbol(); }
        cout << "\nTerminating program\n";

        exit(EXIT_FAILURE);
      }
      break;

    } else {
      cout << "Invalid character\n";
      continue;
    }
  }

  alphabet = fsa.getAlphabet();
  cout << "Please enter a symbol or string of symbols to input to input to ";
  cout << "the machine\nNote: enter a single semicolon ';' to end input\n";
  buffer[0] = temp;

  // Main loop
  while (buffer[0] != ';') {
    cout << "> ";
    trash = cin.peek(); // clear newline
    if (trash == '\n') { cin.get(trash); }
    cin.get(temp);

    if (temp == '\n') { continue; }
    buffer[0] = temp;
    temp = cin.peek(); // here we peek

    // if the string is longer than one character
    if (temp != '\n') {
      cin.get(temp); // then we read what we peeked
      i = 1;

      // read in chars and check if they are valid
      while (temp != '\n') {
        if (temp == ';') { break; }
        if (alphabet.isElement(temp)) { buffer[i] = temp; i++; }
        else { 
          cout << "Error: one or more of the symbols entered are invalid\n";
          errFlag = true;
          break;
        }

        cin.get(temp);
      }

      if (errFlag) { continue; }
      buffer[i] = '\0';

      try {
        fsa.deltaHat(buffer, i);
      } catch (Digraph::InvalidNode& e) {
        cout << "Error: one or more of the symbols entered are invalid\n";
        continue;
      }

      inputString.append(buffer);
      if (temp == ';') { break; }

      // If there is only one input symbol
    } else if (temp == '\n') {
      if (buffer[0] == ';') { break; }

      try {
        fsa.delta(buffer[0]);
      } catch (Digraph::InvalidNode& e) {
        cout << "Error: the symbol entered is invalid\n";
        continue;
      }

      inputString.append(1, buffer[0]);
    }

    cout << "Current state: ";
    cout << parser.getDictionary().getKey(fsa.getCurrentState()) << '\n';
  }

  delete[] buffer;
  if (fsa.isAccepting()) {
    cout << "FSA Accepted the string: " << inputString << "\non state: ";
    cout << parser.getDictionary().getKey(fsa.getCurrentState()) << '\n';
  } else {
    cout << "FSA Denied the string: " << inputString << "\non state: ";
    cout << parser.getDictionary().getKey(fsa.getCurrentState()) << '\n';
  }

  try {
    fsa.writeBinary(parser.getDictionary());
  } catch (FSA::FileError& e) {
    cout << "Error occurred while writing FSA to save.dat\n";
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
