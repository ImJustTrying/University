#include "Money.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void Money::toString(){
    cout << "Name: " << this->getName() << ".\n";
    cout << "Amount: " << this->getAmount() << ".\n";
    if(this->getAmount()!=this->getAmountUsd()){
        cout << "Amount in USD: " << this->getAmountUsd() << ".\n";
        cout << "Rate: " << this->getRate() << ".\n";
    }
}

void Money::makePayment(){
    bool approved = false;
    float am = 0;
    cout << "amount to pay in " << this->getName() << ": ";
    while(!approved)
    {
        try {
            cin >> am;
            if (am <= 0) {

                throw NegativeAmount();
            }
            approved = true;
        }
        catch (NegativeAmount) {
            cout << "Not enough funds." << endl;
        }
    }
    this->setAmount(am);
    this->convertToUsd();
}

Money::Money() {
  this->setAmount(0);
  this->setAmountUsd(0);
}

Money::Money(double a){
    this->setAmount(a);
    this->convertToUsd();
}
