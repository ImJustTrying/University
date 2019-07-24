/*
  Kevin Fernandes
  October 2017

  This program takes in an input file (say "foo.txt"), a string to replace,
  and a string to replace it with. It writes to a new file (called 
  "fooS_REPL.txt"). The program writes the input file to the new file except 
  that every string that is identicle to the string to replace is
  replaced with the cahracter to replace with.

*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string findAndReplace(string, string, string);

int main() {
  ifstream input;
  ofstream output;
  string find, replace, filename, buffer, outputName;

  cout << "Enter a filename: ";
  cin >> filename;

  outputName = filename.substr(0, filename.length() - 4).append("S_REPL");
  outputName += filename.substr(filename.length() - 4, 4);

  cout << "Enter a substring to find: ";
  cin >> find;
  cout << "Enter a substring to replace with: ";
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

string findAndReplace(string s, string find, string replace) {
  string buffer = s;
  short len = find.length();
  size_t found = buffer.find(find);

  // if the substring was found
  while (found != string::npos) {
    buffer.erase(found, len);
    buffer.insert(found, replace);
    found = buffer.find(find);
  }

  return buffer;
}

