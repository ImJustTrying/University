/*
 * "Day.h" header file for the day class
 * Bakery group project part 4
 * Nikita Voronin, Kevin Fernandes, Dmitry Volodkevich, Artem Roy
 * Basic Bakery Setup
 */

#ifndef BAKEKYSETUP_DAY_H
#define BAKEKYSETUP_DAY_H
#include "Item.h"
#include <string>

using std::string;

// we use ID to tell what item the data is for instead of using a string
// since the string cannot be read reliably (it has varying size)
struct ItemData {
  unsigned ID;
  unsigned dozensSold;
  unsigned singlesSold;
  double pricePerOne;
  double pricePerDozen;
};


class Day {
private:
    int numOfItems; // items per day
    double revenue;
    Item* items;   // pointer to an Item array

    int indexOfItem(string); // utility function

public:
    class NoRemainingItems {}; // thrown if there are not enough items left to sell
    class NoItem {}; // thrown if an item is not found in the items list
    class FileError {}; // thrown if an error occurs while writing to binary file

    //Constructor
    Day();
    ~Day();

    // Mutators
    void sellItem(string);
    void sellDozen(string);
    void setRevenue(double);

    // Accessors
    double getRevenue() const;
    int getNumOfItems() const;
    void printMenu();
    double getPriceSingle(string);
    double getPriceDozen(string);
    int getStock(string);

    // checks if an item is on the menu
    bool isInStock(string);
    // Write to binary file
    void writeReport();
};

#endif // BAKEKYSETUP_DAY_H
