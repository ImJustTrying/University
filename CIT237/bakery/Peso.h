#ifndef NEWMONEYCLASS_PESO_H
#define NEWMONEYCLASS_PESO_H
#include "Money.h"
#include <string>

using std::string;

class Peso : public Money {
private:
  const string PESO = "MXN";
  const float RATE = 0.052;

public:
  Peso() : Money() {
    this->setName(PESO);
    this->setRate(RATE);
  }

  Peso(float a) : Money() {
    this->setName(PESO);
    this->setRate(RATE);
    this->setAmount(a);
    this->convertToUsd();
  }

  virtual bool isValidBill(double billVal) {
    const double validVals[] = { 0.1, 0.5, 1, 5, 10, 20, 50, 100, 200, 500, 1000 };
    for (int i = 0; i < 11; i++) {
      if (billVal == validVals[i]) {
        return true;
      }
    }
    return false;
  }
};


#endif //NEWMONEYCLASS_PESO_H
