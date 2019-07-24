/*
  This file contains the declarations for the CashRegister class
*/

#ifndef CASH_REGISTER_H
#define CASH_REGISTER_H

class CashRegister {
private:
  // we don't include half-dollars or $100 bills
  double changeValues[9];
  unsigned changeAmounts[9];
  double overage;

  // this finds the index of the corresponding coin or bill in changeValues
  int search(double);

public:
  CashRegister();

  // this removes the number of bills and coins neccessary to give the customer
  // their change
  void takeOutChange(double);

  // adds some number of bills or coins to the register
  void addChange(double, int);

  // this returns however many of a coin or bill are in the register
  int howMany(double);

  // returns the total amount of money stored in the cash register
  double countChange();

  /* 
  // since the cash register may not have the bills neccessary to pay change
  // we need to compensate by keeping track of how much extra cash was taken
  // to pay back change. This function returns the amount of money that was
  // added to the cash register during operation, without being added explicitly
  // i.e. calling the addChange function.
  */
  double getOverage();
};

#endif
