#include "CreditCard.h"
#include <iostream>
#include <cctype>

using std::cout;
using std::cin;
using std::cerr;

bool CreditCard::checksum() {
  if (sumFinal % 10 == 0) {
    cout << "Card number is valid!\n";
  } else {
    cout << "Card number is invalid:\n";
    // adding new line for modification (9-30-2017)
    cout << "The last digit should be: " << newDigit(sumFinal, lastDigit) << '\n';
  }

  return sumFinal % 10 == 0;
}

int CreditCard::newDigit(int sum, int lastDigit){
  return (lastDigit + 10 - (sum % 10)) % 10;
}

void CreditCard::promptCardNumber() {
  int bufEven, bufOdd;
  int sumEven = 0, sumOdd = 0;
  char buffer;
  // assuming there is an odd number of digits, don't double the first digit
  bool isOther = false;

  cout << "Enter the credit card number:\n";
  // do twice to clear the newline
  cin.get(buffer);
  cin.get(buffer);

  do {
    if (!isdigit(buffer)) {
      cerr << "Error: credit card number contains non-numeric values\n";
      throw ParseError();
    }

    lastDigit = bufOdd = bufEven = buffer - '0';
    if (isOther) {
      bufOdd *= 2;

      if (bufOdd >= 10) {
        // the largest double is 9 * 2 = 18, and thus all doubles will have a
        // one in the tens place, that's why we add 1.
        bufOdd = (bufOdd % 10) + 1;
      }
    } else {
      bufEven *= 2;

      if (bufEven >= 10) {
        bufEven = (bufEven % 10) + 1;
      }
    }

    sumOdd += bufOdd;
    sumEven += bufEven;
    isOther = !isOther;

    cin.get(buffer);
  } while (buffer != '\n');

  // isOther == true ==> odd number of digits
  if (isOther) {
    sumFinal = sumOdd;
  } else {
    sumFinal = sumEven;
  }
}
