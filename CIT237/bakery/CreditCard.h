#ifndef CREDIT_CARD_H
#define CREDIT_CARD_H

class CreditCard {
private:
  int sumFinal;
  int lastDigit;

  int newDigit(int, int);

public:
  class ParseError {}; // thrown when the credit card number is non-numeric

  void promptCardNumber();
  bool checksum();
};

#endif // CREDIT_CARD_H
