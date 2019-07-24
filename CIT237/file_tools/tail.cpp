/*
  Kevin Fernandes
  October 2017

  Here, we print out the last 15 lines of the file, whose name is input by the
  user. If there are 15 or less lines, notify the user of the fact that the
  whole file is being displayed.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void pushBackEveryElement(string*, int);

int main() {
  ifstream file;
  string filename, buffer[15];

  for (int i = 0; i < 15; i++) {
    buffer[i] = "\0";
  }

  cout << "Enter filename: ";
  cin >> filename;
  file.open(filename);

  if (file) {
    while (!file.eof()) {
      pushBackEveryElement(buffer, 15);
      getline(file, buffer[14]);

      if (file.bad()) {
        break;
      }
      if (file.fail()) {
        break;
      }
    }
  }

  for (int i = 0; i < 15; i++) {
    if (buffer[i] == "\0") { continue; }
    cout << buffer[i] << '\n';
  }

  file.close();

  system("pause");
  return 0;
}

void pushBackEveryElement(string* arr, int n) {
  string temp;
  for (int i = n-2; i >= 0; i--) {
    temp = arr[n-1];
    arr[n-1] = arr[i];
    arr[i] = temp;
  }
}

