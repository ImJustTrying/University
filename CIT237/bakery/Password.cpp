#include "Password.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

using std::cerr;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::ios_base;

Password::Password(char* pword, unsigned len) {
  password = pword;
  length = len;
  isDynamic = false;
}

Password::Password() {
  password = nullptr;
  length = 0;
  isDynamic = false;
}

Password::~Password() {
  if (isDynamic) {
    delete[] password;
  }
}

bool Password::isInArray (char* array, int size, char value) {
  for (int i = 0; i < size; i++) {
    if (value == array[i]) { return true; }
  }
  return false;
}

// check all properties of password 
bool Password::validate() {
  if (password == nullptr) {
    return false;
  }

  bool digits = false, len = false, special = false, extra = false, 
       upper = false, lower = false, valid;
  int index = 0;
  char specialChars[] = { '!', '@', '#', '$', '%' };
  char buffer = password[index];

  while (buffer != '\0' && index < length) {
    if (isdigit(buffer)) {
      digits = true;
    }

    if (isupper(buffer)) {
      upper = true;
    }

    if (islower(buffer)) {
      lower = true;
    }

    if (!(isalnum(buffer) || isInArray(specialChars, 5, buffer))) {
      extra = true;
    }

    if (isInArray(specialChars, 5, buffer)) {
      special = true;
    }

    buffer = password[++index]; 
  }

  len = (index >= 5) && (index <= 14);
  cout << len << '\n' << digits << '\n' << special << '\n' << extra << '\n';
  cout << upper << '\n' << lower << '\n';
  valid = len && digits && special && !extra && upper && lower;

  if (!valid) {
    throw InvalidPassword();
  }
  return valid;
}

void Password::writePassword() {
  ofstream out;
  try {
    out.open("pass.bin", ios::out | ios::binary | ios::trunc);
  } catch (ios_base::failure& fail) {
    throw FileError();
    return;
  }

  out.write(reinterpret_cast<char*>(&length), sizeof(length));
  out.write(password, length);
  out.close();
  return;
}

void Password::readPassword() {
  ifstream in;
  try {
    in.open("pass.bin", ios::in | ios::binary);
  } catch (ios_base::failure& fail) {
    throw FileError();
    return;
  }

  in.read(reinterpret_cast<char*>(&length), sizeof(length));
  if (password == nullptr) {
    password = new char[length];
    isDynamic = true;
  }
  in.read(password, length);
  in.close();
  return;
}

void Password::setPassword(char* pword, unsigned len) {
  password = pword;
  length = len;
  return;
}

bool Password::isPassword(char* pword, unsigned len) {
  if (password == nullptr || len != length) {
    return false;
  }

  for (int i = 0; i < len; i++) {
    if (pword[i] != password[i]) {
      return false;
    }
  }
  return true;
}
