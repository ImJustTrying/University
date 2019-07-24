/*
 * "Item.h" header file for the Item class
 * Bakery group project part 4
 * Nikita Voronin, Kevin Fernandes, Dmitry Volodkevich, Artem Roy
 * Basic Bakery Setup
 */

#ifndef BAKEKYSETUP_ITEM_H
#define BAKEKYSETUP_ITEM_H
#include <string>

using std::string;

class Item {
private:
    string itemName;
    double pricePerOne;
    double pricePerDozen;
    int amount, dozensSold, singlesSold;

public:
    // Accessors
    string getName() const;
    double getPricePerOne() const;
    double getPricePerDozen() const;
    int getAmount() const;
    int getDozensSold() const;
    int getSinglesSold() const;

    // Mutators
    void setName(string name);
    void setPricePerOne(double priceOne);
    void setPricePerDozen(double priceDozen);
    void setAmount(int a);
    void setDozensSold(int);
    void setSinglesSold(int);

    // Constructors
    Item();
    Item(string name, double priceOne, double priceDozen, int amount);
};

#endif //BAKEKYSETUP_ITEM_H
