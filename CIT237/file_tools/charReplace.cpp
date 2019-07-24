/*
  Kevin Fernandes
  October 2017

  This program takes in an input file (say "foo.txt"), a character to replace,
  and a character to replace it with. It writes to a new file (called 
  "fooC_REPL.txt"). The program writes the input file to the new file except 
  that every character that is identicle to the character to replace is
  replaced with the cahracter to replace with.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string findAndReplace(string, char, char);

int main() {
  ifstream input;
  ofstream output;
  char find, replace;
  string filename, buffer;
  string outputName;

  cout << "Enter a filename: ";
  cin >> filename;

  outputName = filename.substr(0, filename.length() - 4).append("C_REPL");
  outputName += filename.substr(filename.length() - 4, 4);

  cout << "Enter a character to find: ";
  cin >> find;
  cout << "Enter a character to replace with: ";
  cin >> replace;

  input.open(filename);
  output.open(outputName);

  while (!input.eof()) {
    getline(input, buffer);
    if (input.bad()) {
      cerr << "Error: badbit read from input file\n";
    }
    output << findAndReplace(buffer, find, replace) << '\n';
  }

  input.close();
  output.close();

  system("pause");
  return 0;
}

string findAndReplace(string s, char find, char replace) {
  string buffer = s;
  for (int i = 0; i < s.length(); i++) {
    if (buffer[i] == find) {
      buffer[i] = replace;
    }
  }
  return buffer;
}

