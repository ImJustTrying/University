#ifndef NEWMONEYCLASS_EURO_H
#define NEWMONEYCLASS_EURO_H
#include "Money.h"
#include <string>
#include <iostream>
using namespace std;

class Euro : public Money {
private:
    const string EUR = "EUR";
    const float RATE = 1.17;
public:

    Euro() : Money(){
        this->setName(EUR);
        this->setRate(RATE);
    }
    Euro(float a) : Money(){
        this->setName(EUR);
        this->setRate(RATE);
        this->setAmount(a);
        this->convertToUsd();
    }

    bool isValidBill(double billValue) {
      const double validVals[] = { 0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1, 2, 5, 10, 20, 50, 100, 200, 500 };
      for (int i = 0; i < 15; i++) {
        if (billValue == validVals[i]) { return true; }
      }
      return false;
    }
};


#endif //NEWMONEYCLASS_EURO_H
