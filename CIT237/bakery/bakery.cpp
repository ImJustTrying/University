/*
 * Group Final Project: Main program
 * Goup #1:
 * Artem Roy
 * Nikita Voronin
 * Kevin Fernandes
 * Dmitry Volodkevich
 *
 * This is the main program that simulates one day of the bakery operating
 */

#include <cstdlib>
#include <algorithm>
#include <exception>
#include <cmath>
#include <iostream>

#include "CashRegister.h"
#include "Day.h"
#include "CreditCard.h"

#include "Money.h"
#include "Dollar.h"
#include "Ruble.h"
#include "Pound.h"
#include "Euro.h"
#include "CanadianDollar.h"
#include "Peso.h"

using namespace std;

void promptCustomer(Day*, CashRegister*);
void sellItems(Day*, string, int);
void payment(CashRegister*, bool, double);
double parseCash(Money*);

int main() {
  Day d;
  CashRegister r;
  unsigned customerCount;

  srand(time(NULL));
  customerCount = rand() % 5 + 1;

  cout.precision(2);

  d.printMenu();
  for (int i = 0; i < customerCount; i++) {
    promptCustomer(&d, &r);
    if (i != customerCount - 1) { cout << " Next!\n\n"; }
  }

  cout << "\nClosing for the day!\n" << endl;
  d.setRevenue(d.getRevenue() - r.getOverage());
  d.writeReport();

  system("pause");
  return 0;
}


/*
 * This function will prompt the user for input such as the item name and
 * the number of items they would like, then calls the payment and sellItems
 * functions (and possibly the parseCash function as well).
*/

void promptCustomer(Day* d, CashRegister* r) {
  string itemName, payMethod = "";
  int amount;
  double total;

  cout << "Please enter what item you would like:\n> ";
  cin >> itemName;
  transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);

  while (!d->isInStock(itemName)) {
    cout << "Sorry, that is not an item on the menu!\n";
    cout << "Please enter what item you would like:\n> ";
    cin >> itemName;
    transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);
  }

  cout << "How many would you like?\n> ";
  cin >> amount;

  while (amount <= 0) {
    cout << "Sorry, that is an invalid number of items!\n";
    cout << "How many would you like?\n> ";
    cin >> amount;
  }

  while (amount > d->getStock(itemName)) {
    cout << "Sorry, we don't have that many of that item!\n";
    cout << "How many would you like?\n> ";
    cin >> amount;
  }

  {
    int singles = amount % 12;
    int dozens = (amount - singles) / 12;
    total = (d->getPriceSingle(itemName) * (double)singles) + 
            (d->getPriceDozen(itemName) * (double)dozens);
  }

  // only allow credit card where the price is at or over $20.00  
  if (total >= 20) {
    cout << "How would you like to pay? (type \"cash\" for cash, \"card\" for ";
    cout << "credit card)\n> ";
    cin >> payMethod;
    transform(payMethod.begin(), payMethod.end(), payMethod.begin(), ::tolower);

    while (payMethod != "cash" && payMethod != "card") {
      cout << "Sorry, I couldn't understand that.\n";
      cout << "How would you like to pay?\n> ";
      cin >> payMethod;
      transform(payMethod.begin(), payMethod.end(), payMethod.begin(), ::tolower);
    }
  }

  try { 
    payment(r, payMethod == "card", total);
  } catch (exception& e) {
    cout << "Transaction failed. Next!\n\n";
    return; 
  }

  sellItems(d, itemName, amount);
  cout << "Transaction successful.";
}


// we assume amount > 0
void sellItems(Day* d, string itemName, int amount) {
  if (amount >= 12) {
    int singles = amount % 12;
    int dozens = (amount - singles) / 12;

    // no need to exception handling since amount must be greater than zero
    // and cannot be greater than the number of pieces of the item `itemName`
    for (int i = 0; i < dozens; i++) {
        d->sellDozen(itemName);
    }

    for (int i = 0; i < singles; i++) {
        d->sellItem(itemName);        
    }

  } else {
    for (int i = 0; i < amount; i++) {
        d->sellItem(itemName);        
    }
  } 
}


/* 
 * If `isCard` is true, the customer pays with credit card, otherwise they pay
 * with cash. For cash, we prompt them for bills, and for card we prompt them
 * for a credit card number. We also take into consideration validation and
 * fake bills.
*/

void payment(CashRegister* r, bool isCard, double total) {
  if (isCard) {
    CreditCard cc;
    bool checkSum;

    try {
      cc.promptCardNumber();
    } catch (CreditCard::ParseError& pe) {
      cout << "Transaction terminated. Next!\n\n";
      throw exception();
    }

    // checksum() will print out error messages if needed
    checkSum = cc.checksum();

    if (!checkSum) {
      throw exception();
    } else {
      cout << "Payment successful!\n";
    }

  } else {
    // here, sum, total, and change will be in USD, and convertedTotal will be
    // in whatever currency the customer is using
    double sum = 0, buf, change, convertedTotal, temp;
    char buffer;
    string currencyBuf;
    Money* currency = nullptr;

    cout << "What currency are you paying in?\n";
    cout << "\"USD\" ==> US Dollar\n\"MXN\" ==> Peso\n\"CAD\" ==> CA Dollar\n";
    cout << "\"EUR\" ==> Euro\n\"GBP\" ==> Pound\n\"RUB\" ==> Ruble\n> ";

    while (currency == nullptr) {
      cin >> currencyBuf;
      transform(currencyBuf.begin(), currencyBuf.end(), currencyBuf.begin(), ::toupper);

        if ("USD" == currencyBuf) {
          currency = new Dollar();
          break;
        }
        if ("MXN" == currencyBuf) {
          currency = new Peso();
          break;
        }
        if ("EUR" == currencyBuf) {
          currency = new Euro();
          break;
        }
        if ("RUB" == currencyBuf) {
          currency = new Ruble();
          break;
        }
        if ("CAD" == currencyBuf) {
          currency = new CanadianDollar();
          break;
        }
        if ("GBP" == currencyBuf) {
          currency = new Pound();
          break;
        } else {
          cout << "Sorry, I couldn't understand that. What currency are you paying in?\n> ";
        }
    }

    convertedTotal = total / currency->getRate();
    cout << "That will be " << total << " USD (";
    cout << convertedTotal << ' ' << currencyBuf << ")\n";

    cout << "Please enter the value of the bill or coin you want to pay and ";
    cout << "how many you want to give\n(e.g. Assuming you are paying in USD, ";
    cout << "if you want to pay 2 quarters, type \"0.25 : 2\")\nMore prompts ";
    cout << "will show if you need different types of change.\n> ";

    // clear the new line
    cin.get(buffer);

    while (sum < total) {
      buf = parseCash(currency);
      if (buf <= 0) {
        cout << "Sorry, that's not a possible combination of bills or coins.";
        cout << "What else do you have?\n> ";
        continue;
      } else {
        currency->setAmount(currency->getAmount() + buf);
        currency->convertToUsd();
        sum = currency->getAmountUsd();

        if (sum >= total) {
          break;
        } else {
          cout << "Got it! You've paid $" << sum << " (" << currency->getAmount();
          cout << ' ' << currencyBuf << ") so far, and need ";
          (total - sum < 0) ? cout << "0.00" : cout << total - sum;
          cout << " USD (";
          (convertedTotal - currency->getAmount() < 0) ? 
            cout << "0.00" : 
            cout << convertedTotal - currency->getAmount();
          cout << ' ' << currencyBuf << ") more.\n> ";
        }
      }
    }

    change = abs(total - sum);
    if (change == 0) {
      cout << "You have no change\n";
    } else {
      currency->setAmount(change / currency->getRate());
      cout << "You have " << change << " dollars in change (";
      cout << currency->getAmount() << ' ' << currencyBuf << ")\n";
    }
    r->takeOutChange(change);
    delete currency;
  }
 
  return;
}


/*
 * This function parses the string "a : b" for a real number `a` and an integer
 * `b`. We would interpret this as "`b` bills (or coins) of value `a`". For
 * example, say a = 0.25 and b = 3, this would be interpreted as 3 quarters
 * i.e. 3 coins of value $0.25.
*/

double parseCash(Money* currency) {
  double billValue = 0, posCounter = 0.1;
  int billCount = 0;
  char buffer;
  bool isReal = false, readingLeft = true;

  do {
    cin.get(buffer);
    if (readingLeft) {
      if (buffer == ':') {
        readingLeft = false;
        continue;
      }

      if (buffer == '.' || isReal) {
        if (isdigit(buffer)) {
          billValue += (buffer - '0') * posCounter;
          posCounter /= 10;
          continue;
        } else {
          isReal = true;
          continue;
        }
      }

      if (isdigit(buffer)) {
        billValue *= 10;
        billValue += buffer - '0';
        continue;
      }

      if (buffer == ' ') {
        continue;
      }
    } else {

      if (isdigit(buffer)) {
        billCount *= 10;
        billCount += buffer - '0';
        continue;
      } 

      if (buffer == ' ') {
        continue;
      } 

      if (buffer == '\n') { 
        break;
      }
    }
  } while (buffer != '\n');

  if (!currency->isValidBill(billValue)) {
    return 0;
  }

  if (billCount <= 0) {
    return 0;
  }

  return (double)billCount * billValue;
}
