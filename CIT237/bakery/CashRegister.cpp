#include "CashRegister.h"

CashRegister::CashRegister() {
  overage = 0;
  double values[] = { 0.01, 0.05, 0.1, 0.25, 1.0, 5.0, 10.0, 20.0, 50.0 };
  unsigned amounts[] = { 22, 21, 20, 10, 10, 5, 4, 3, 0 };
  for (int i = 0; i < 9; i++) {
    changeAmounts[i] = amounts[i];
    changeValues[i] = values[i];
  }
}

int CashRegister::search(double val) {
  for (int i = 0; i < 9; i++) {
    if (val == changeValues[i]) { return i; }
  }
  return -1;
}

// assumes change is rounded to the nearest hundreth
void CashRegister::takeOutChange(double change) {
  int index = 8;
  while (change > 0.0 && index >= 0) {
   if (change < changeValues[index]) {
      index--;
      continue;
    } else {
      change -= changeValues[index];

      // adding 5 bills to the register, using one to pay
      if (changeAmounts[index] == 0) {
        changeAmounts[index] += 4;
        overage += changeAmounts[index] * 5;
      } else {
        changeAmounts[index] -= 1;
      }
    }
  }
  return;
}

void CashRegister::addChange(double val, int amount) {
  changeAmounts[search(val)] += amount;
}

int CashRegister::howMany(double val) {
  return changeAmounts[search(val)];
}

double CashRegister::countChange() {
  double total = 0;
  for (int i = 0; i < 8; i++) {
    total += changeValues[i] * changeAmounts[i];
  }
  return total;
}

double CashRegister::getOverage() {
  return overage;
}
