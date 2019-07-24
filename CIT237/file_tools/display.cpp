/*
  Kevin Fernandes
  October 2017

  This program displays 24 lines of a file (user provides filename), and waits
  for the user to respond to the prompt, and either displays the next 24 lines,
  or terminates the program.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
  ifstream file;
  string filename, buffer, output = "";
  char buf;

  cout << "Enter filename: ";
  cin >> filename;

  file.open(filename);

  do {
    for (int i = 0; i < 24; i++) {
      getline(file, buffer);
      if (file.bad() || file.fail() || file.eof()) { break; }
      output.append(buffer).append("\n"); 
    }

    cout << output << "\nContinue? (Y or N): ";
    output = "";
    cin >> buf;
    if (file.fail() || file.bad() || file.eof()) { break; }
  } while (toupper(buf) != 'N');

  file.close();
  return 0;
}
