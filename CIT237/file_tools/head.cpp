/*
  Kevin Fernandes
  October 2017

  This program prints the first 10 lines of a file (the filename is entered
  by the user). If the file has less than 10 lines, only show those 10 lines.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
  ifstream in;
  string filename, buffer;
  short counter = 0;

  cout << "Enter filename: ";
  cin >> filename;

  in.open(filename);
  cout << '\n';

  while (!in.eof() && counter < 10) {
    getline(in, buffer);
    if (in.bad()) {
      throw "Error: badbit or failbit set to 1"; 
    }
    cout << buffer << '\n';
    counter++;
  }

  cout << '\n';

  system("pause");
  return 0;
}

