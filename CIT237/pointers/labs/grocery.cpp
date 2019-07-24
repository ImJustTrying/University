/* 
  Kevin Fernandes
  September 2017 
  Check if there is a file "grocery.txt" exists. If so, read the values into an
  array. Otherwise, begin from here: Ask the user to input the number of items
  they want to enter, and to enter the values. Then, display all of the values
  to the user and write them to "grocery.txt" (create it if it does not exist).
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void writeItems(string*, int, ofstream*);
void readItems(string*, int, ifstream*); 
void getItems(string*, int);

int main() {
  const string file = "grocery.txt";
  ifstream in;
  ofstream out;
  char buffer;
  int fileItemSize = 0;
  int inputItemSize = 0;
  string* fileItems;
  string* inputItems;

  
  // we want to do this at least once, so we use do-while
  do {
    cout << "Would you like to discard the current grocery list? (Y or N): ";
    cin >> buffer;

    if (buffer == 'n' || buffer == 'N') {
      in.open(file);
      in >> fileItemSize;
      fileItems = new string[fileItemSize];
      readItems(fileItems, fileItemSize, &in);
      in.close();

      // set the seeker to the top of the file to rewrite the # of items
      out.open(file);
    } else if (buffer == 'y' || buffer == 'Y') {
      // truncates file before opening
      out.open(file, ios::out | ios::trunc);
    } else {
      cout << "Error: invalid character\n";
    }
  } while (!out);
 
  cout << "Please enter the number of items you would like to input: ";
  cin >> inputItemSize;
  inputItems = new string[inputItemSize];
  getItems(inputItems, inputItemSize);

  if (inputItemSize > 0) {
    out << fileItemSize + inputItemSize << '\n';
    out.close();
    // ios::app sets seeker to the end of the file
    out.open(file, ios::out | ios::app);
    long pos = out.tellp();
    pos = ;
    
    writeItems(inputItems, inputItemSize, &out);
  }

  out.close();

  delete[] fileItems;
  fileItems = nullptr;
  delete[] inputItems;
  inputItems = nullptr;

  return 0;
}

void getItems(string* items, int itemCount) {
  for (int i = 0; i < itemCount; i++) {
    cout << "Item " << i+1 << ": ";
    cin >> items[i];
  }
}

void readItems(string* items, int itemCount, ifstream* in) {
  for (int i = 0; i < itemCount; i++) {
    *in >> items[i];
  }
}

void writeItems(string* items, int count, ofstream* out) {
  for (int i = 0; i < count; i++) {
    *out << items[i] << '\n';
  }
}

