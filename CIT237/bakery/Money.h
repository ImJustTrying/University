#ifndef NEWMONEYCLASS_MONEY_H
#define NEWMONEYCLASS_MONEY_H
#include <string>
#include <cmath>

using std::string;

class Money {
protected:
    string name;
    double amount;
    double amount_usd;
    double rate;

public:
    string getName() const { return name; }
    double getAmount() const { return amount; }
    double getAmountUsd() const { return amount_usd; }
    double getRate() const { return rate; }

    void setName(string n) { name = n; }
    void setAmount(double a) { amount = a; }
    void setAmountUsd(double aU) { amount_usd = aU; }
    void setRate(double r) { rate = r; }

    void convertToUsd() {
      // use round to keep it rounded to two decimal places
      amount_usd = round(amount * rate * 100) / 100;
    }

    void toString();
    void makePayment();
    virtual bool isValidBill(double) = 0;

    Money();
    Money(double a);

    class NegativeAmount{}; // for catching negative amount exceptions
};


#endif //NEWMONEYCLASS_MONEY_H
