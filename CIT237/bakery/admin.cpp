/*
  This is the main program for the administrator access to a summary report
*/

#include <fstream>
#include <iostream>
#include <exception>

#include "Password.h"
#include "Day.h"

using namespace std;

bool getPassword();
void printTables();
void printItemData(ItemData);

int main() {
  bool success = false, first = true;
  char buffer;

  while (!success) {
    if (!first) {
      cin.get(buffer); // clear newline
    } else {
      first = !first;
    }

    try {
      success = getPassword();
    } catch (Password::FileError& e) {
      cout << "Terminating program\n";
      exit(EXIT_FAILURE);
    } catch (Password::InvalidPassword& e) {
      cout << "Terminating program\n";
      exit(EXIT_SUCCESS);
    }
  }

  try {
    printTables();
  } catch (exception& e) {
    exit(EXIT_FAILURE);
  }
}

// This function attempts to either read in a password from a binary file,
// or collects a new one from the user
bool getPassword() {
  Password p;
  ifstream in;
  char pword[15];
  unsigned len = 0, temp = 0;
  char buf;

  try {
    in.open("pass.bin", ios::binary | ios::in);
  } catch (ios_base::failure& fail) {
    cerr << "Error opening password file\n";
    throw Password::FileError();
  }

  if (in.is_open()) {
    in.seekg(0, in.end);
    long pos = in.tellg();
    in.close();

    if (pos > 0) {
      p.readPassword();
      cout << "Pleese enter your password:\n> ";
      cin.get(pword, 15);
      cin.get(buf); // clear newline

      for (int i = 0; i < 15; i++) {
        if (pword[i] == '\n' || pword[i] == '\0') {
          temp = i + 1;
          break;
        }
      }

      if (p.isPassword(pword, temp)) {
        cout << "Access granted\n";
        return true;
      } else {
        cout << "Access denied\n";
        throw Password::InvalidPassword();
      }
    }

  } else {
    cout << "Please enter a password with the following criteria:\n";
    cout << "1. Must be between 5 and 14 characters\n";
    cout << "2. Must have at least one special character ";
    cout << "(i.e. !, @, #, $, or %, and no other special character)";
    cout << "\n3. Must have at least one lowercase character\n";
    cout << "4. Must have at least one uppercase character\n";
    cout << "5. Must have at least one digit\nEnter Password: ";

    cin.get(pword, 15);
    for (int i = 0; i < 15; i++) {
      if (pword[i] == '\n' || pword[i] == '\0') {
        len = i + 1;
        break;
      }
    }
    cout << "len = " << len << '\n';
    p.setPassword(pword, len);

    try {
      bool b = p.validate();
    } catch (Password::InvalidPassword& ip) {
      cerr << "Error: invalid password entered.\n";
      return false;
    }

    p.writePassword();
    cout << "Access granted\n";
  }

  return true;
}

// This function prints the tables for the adminitrator to read
// There is one table for every day
void printTables() {
  ItemData data;
  double revenueBuf;
  ifstream in;
  long pos;
  unsigned counter = 0;

  in.open("report.bin", ios::in | ios::binary);
  cout.precision(2);
  cout.setf(ios::fixed, ios::floatfield);

  if (in.is_open()) {
    in.seekg(0, in.end);
    pos = in.tellg();
    in.seekg(0, in.beg);

    if (pos > 0) {
      while (!in.eof()) {
        in.read(reinterpret_cast<char*>(&revenueBuf), sizeof(revenueBuf));
        if (in.fail() || in.bad()) {
          break;
        }

        cout << "Day " << ++counter << " revenue: $" << revenueBuf << '\n';
        // print head of table
        cout << '|' << string(4, ' ') << "Item" << string(4, ' ') << '|';
        cout << " Price per | Price dozen | Singles sold | Dozens sold |\n";

        // print dividing line
        cout << '|' <<  string(12, '-') << '+' << string(11, '-') << '+';
        cout << string(13, '-') << '+' << string(14, '-') << '+'; 
        cout << string(13, '-') << "|\n"; 

        for (int j = 0; j < 10; j++) {
          in.read(reinterpret_cast<char*>(&data), sizeof(data));
          printItemData(data);
          cout << '|' <<  string(12, '-') << '+' << string(11, '-') << '+';
          cout << string(13, '-') << '+' << string(14, '-') << '+'; 
          cout << string(13, '-') << "|\n"; 
        }
      }
      cout << endl;

    } else {
      cout << "Report file is empty\n";
      return;
    }
  } else {
    cerr << "Error opening binary file (file may not exist)\n";
    throw exception();
  }
}


// This function prints a row of data (for one item) in the table
void printItemData(ItemData data) {
  const string names[] = {"bread","biscuits","bagel","muffin","pastry","pie",
                          "cheesecake","brownie","croissant","cake" };

  int temp = 12 - names[data.ID].length();
  cout << '|' << string(temp / 2, ' ') << names[data.ID];
  if (temp % 2 == 0) {
    cout << string(temp / 2, ' ');
  } else {
    cout << string(temp / 2 + 1, ' ');
  }

  cout << '|' << string(3, ' ') << '$' << data.pricePerOne << string(3, ' ') << '|';

  if (data.pricePerDozen >= 10) {
    cout << string(3, ' ');
  } else {
    cout << string(4, ' ');
  }
  cout << '$' << data.pricePerDozen << string(4, ' ') << '|';

  if (data.singlesSold >= 10) {
    cout << string(6, ' ');
  } else {
    cout << string(7, ' ');
  }
  cout << data.singlesSold << string(6, ' ') << '|';

  cout << string(6, ' ') << data.dozensSold << string(6, ' ') << "|\n";
  return;
}
