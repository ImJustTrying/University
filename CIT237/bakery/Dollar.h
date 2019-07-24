#ifndef NEWMONEYCLASS_DOLLAR_H
#define NEWMONEYCLASS_DOLLAR_H
#include "Money.h"
#include <string>

using std::string;

class Dollar : public Money {
private:
    const string USD = "USD";
    const float RATE = 1;
public:

    Dollar() : Money(){
        this->setName(USD);
        this->setRate(RATE);
    }

    Dollar(float a) : Money(a){
        this->setName(USD);
        this->setRate(RATE);
        this->convertToUsd();
    }

    virtual bool isValidBill(double billValue) {
      const double validVals[] = { 0.01, 0.05, 0.1, 0.25, 1, 5, 10, 20, 50 };
      for (int i = 0; i < 9; i++) {
        if (billValue == validVals[i]) { return true; }
      }
      return false;
    }
};


#endif //NEWMONEYCLASS_DOLLAR_H
