#ifndef NEWMONEYCLASS_RUBLE_H
#define NEWMONEYCLASS_RUBLE_H
#include "Money.h"
#include <string>

using std::string;

class Ruble : public Money {
private:
    const string RUB = "RUB";
    const float RATE = 0.017;
public:

    Ruble() : Money(){
        this->setName(RUB);
        this->setRate(RATE);
    }

    Ruble(float a) : Money(){
        this->setName(RUB);
        this->setRate(RATE);
        this->setAmount(a);
        this->convertToUsd();
    }

    virtual bool isValidBill(double billValue) {
      const double validVals[] = { 0.1, 0.5, 1, 5, 10, 50, 100, 200, 500, 1000, 2000, 5000 };
      for (int i = 0; i < 12; i++) {
        if (billValue == validVals[i]) { return true; }
      }
      return false;
    }
};


#endif //NEWMONEYCLASS_RUBLE_H
