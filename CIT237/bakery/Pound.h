#ifndef NEWMONEYCLASS_POUND_H
#define NEWMONEYCLASS_POUND_H
#include "Money.h"
#include <string>

using std::string;

class Pound : public Money {
private:
    const string GBP = "GBP";
    const float RATE = 1.32;
public:

    Pound() : Money(){
        this->setName(GBP);
        this->setRate(RATE);
    }

    Pound(float a) : Money(){
        this->setName(GBP);
        this->setRate(RATE);
        this->setAmount(a);
        this->convertToUsd();
    }

    virtual bool isValidBill(double billValue) {
      const double validVals[] = { 0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1, 2, 5, 10, 20, 50 };
      for (int i = 0; i < 12; i++) {
        if (validVals[i] == billValue) { return true; }
      }
      return false;
    }
};


#endif //NEWMONEYCLASS_POUND_H
