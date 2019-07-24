/*
  Kevin Fernandes
  September, 2017

  This program verifies a password entered by the user with the following
  constraints: 1. The password should be between 6 and 15 characters in length
  2. The password should contain at least one uppercase and lowercase letter
  3. The password should have at least one digit
  4. The password should contain one of the following characters: "! @ # $ %"
*/

#include <iostream>
#include <cctype>

bool checkPassword(char*);

bool checkLength(char*);
bool checkDigit(char*);
bool checkCase(char*);
bool checkSpecialChar(char*);
// This returns true when there are not invalid characters (e.g. '^', ' ', '&')
bool checkExtraChars(char*);

bool isInArray(char*, int, char);

int main() {
  const int SIZE = 15;
  char pwd[SIZE];

  std::cout << "Please enter your password: ";
  std::cin.getline(pwd, SIZE);


  // functions will print out errors; no need to print them here 
  while(!checkPassword(pwd)) {
    std::cout << "Please enter your password: ";
    std::cin.getline(pwd, SIZE);
  }

  std::cout << "You entered a valid password!" << std::endl;
  system("pause");
  return 0;
}

// check all properties of password 
bool checkPassword(char* password) {
  bool checks = checkLength(password) && checkDigit(password); 
  checks = checks && checkCase(password) && checkSpecialChar(password);
  return checks && checkExtraChars(password);
}


bool isInArray(char* array, int len, char value) {
  for (int i = 0; i < len; i++) {
    if (array[i] == value) {
      return true;
    }
  }
  return false;
}

bool checkDigit(char* password) {
  unsigned index = 0;
  char buffer = password[index];
  while (buffer != '\0') {
    if (isdigit(buffer)) {
      return true;
    }
    buffer = password[++index];
  }
  std::cout << "Error: Password does not include a digit\n";
  return false;
}

bool checkLength (char* password) {
  unsigned index = 0;
  char buffer = password[index];
  while (buffer != '\0') {
    buffer = password[++index];
  }
  if (index < 5 || index > 14) {
    std::cout << "Error: Password is not between 6 and 15 characters long\n";
    return false;
  }
  return true;
}

bool checkCase(char* password) {
  unsigned index = 0;
  char buffer = password[index];
  bool upperFound = false;
  bool lowerFound = false;
  while (buffer != '\0') {
    if (isupper(buffer)) {
      upperFound = true;
    }
    if (islower(buffer)) {
      lowerFound = true;
    }
    buffer = password[++index];
  }
  if (!upperFound || !lowerFound) {
    std::cout << "Error: Password does not contain at least one upper and ";
    std::cout << "lower case letter\n";
  }
  return upperFound && lowerFound;
}

bool checkSpecialChar(char* password) {
  unsigned index = 0;
  char buffer = password[index];
  char specialChars[] = {'!', '@', '#', '$', '%'};
  while (buffer != '\0') {
    if (isInArray(specialChars, 5, buffer)) {
      return true;
    }
    buffer = password[++index];
  }
  std::cout << "Error: Password does not contain any special characters\n";
  return false; 
}

bool checkExtraChars(char* password) {
  unsigned index = 0;
  char buffer = password[index];

  while (buffer != '\0') {
    char specialChars[] = {'!', '@', '#', '$', '%'};
    if (!(isalnum(buffer) || isInArray(specialChars, 5, buffer))) {
      std::cout << isalnum(buffer) << isInArray(specialChars, 5, buffer);
      std::cout << "Error: Password contains invalid characters" << buffer << '\n';
      return false;
    }
    buffer = password[++index];
  }
  return true;
}

