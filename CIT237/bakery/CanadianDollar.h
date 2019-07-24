#ifndef NEWMONEYCLASS_CANADIANDOLLAR_H
#define NEWMONEYCLASS_CANADIANDOLLAR_H
#include "Money.h"
#include <string>

using std::string;

class CanadianDollar : public Money {
private:
    const string CAD = "CAD";
    const float RATE = 0.79;

public:
    CanadianDollar() : Money(){
        this->setName(CAD);
        this->setRate(RATE);
    }

    CanadianDollar(float a) : Money(){
        this->setName(CAD);
        this->setRate(RATE);
        this->setAmount(a);
        this->convertToUsd();
    }

    virtual bool isValidBill(double billValue) {
      const double validVals[] = { 0.05, 0.1, 0.25, 0.5, 1, 2, 5, 10, 20, 50, 100 };
      for (int i = 0; i < 11; i++) {
        if (validVals[i] == billValue) { return true; }
      }
      return false;
    }
};


#endif //NEWMONEYCLASS_CANADIANDOLLAR_H
