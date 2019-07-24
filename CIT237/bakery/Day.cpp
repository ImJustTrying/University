/*
 * "Day.cpp" file for the Day class
 * Bakery group project part 4
 * Nikita Voronin, Kevin Fernandes, Dmitry Volodkevich, Artem Roy
 * Basic Bakery Setup
 */

#include "Day.h"
#include "Item.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// Constructor
Day::Day() {
    numOfItems = 10;
    revenue = 0;

    items = new Item[numOfItems];
    // 10 possible items
    const string names[] = {"bread","biscuits","bagel","muffin","pastry","pie",
                                "cheesecake","brownie","croissant","cake" };
    const double priceOne[] = {1.5,0.4,0.9,0.9,1.2,2.25,2.25,1.75,1.25,2.25};
    const double priceDozen[] = {16.2,4.2,9.0,9.0,12.9,20,20,16.5,12.9,20};

    for (int i = 0; i < numOfItems; i++) {
        // num is a random integer in the interval [13,48]
        int num = 12 + rand() % 36 + 1;
        items[i] = Item(names[i], priceOne[i], priceDozen[i], num);
    }
}

// Deconstructor
Day::~Day() {
  delete[] items;
}

// prints all the information about Item objects for a particular Day
void Day::printMenu() {
    cout << fixed << setprecision(2);
    cout << "Menu:\n";

    for (int i = 0; i < numOfItems;i++) {
        cout << items[i].getName() << ", cost per: $" << items[i].getPricePerOne();
        cout << ", cost per dozen: $" << items[i].getPricePerDozen();
        cout << ", amount: " << items[i].getAmount() << ".\n";
    }
    cout << endl;
}

// Accessor
int Day::getNumOfItems() const{
    return numOfItems;
}

double Day::getRevenue() const {
    return revenue;
}

void Day::writeReport() {
  ofstream bin;
  ItemData* data = new ItemData[numOfItems];

  // write todays data to the structures
  for (int i = 0; i < numOfItems; i++) {
    data[i].ID = i;
    data[i].pricePerOne = items[i].getPricePerOne();
    data[i].pricePerDozen = items[i].getPricePerDozen();
    data[i].dozensSold = items[i].getDozensSold();
    data[i].singlesSold = items[i].getSinglesSold();
  }

  bin.open("report.bin", ios::out | ios::binary | ios::app);

  // write the new data to the binary file
  if (bin.is_open()) {
    bin.write(reinterpret_cast<char*>(&revenue), sizeof(revenue));
    for (int i = 0; i < numOfItems; i++) {
      bin.write(reinterpret_cast<char*>(&data[i]), sizeof(data[i]));
    }
    bin.close();
  } else {
    cerr << "Error: could not open output file.\n";
    delete[] data;
    throw FileError();
  }

  delete[] data;
  return;
}

void Day::setRevenue(double d) {
  revenue = d;
}

int Day::indexOfItem(string name) {
  for (int i = 0; i < numOfItems; i++) {
    if (items[i].getName() == name) {
      return i;
    }
  }
  return (-1);
}

// throws NoRemainingItems if there are no items left in stock
void Day::sellItem(string name) {
  int index = indexOfItem(name);

  if (index < 0) {
    throw NoItem();
  } else if (items[index].getAmount() <= 0) {
    throw NoRemainingItems();
  } else {
    items[index].setAmount(items[index].getAmount() - 1);
    items[index].setSinglesSold(items[index].getSinglesSold() + 1);
    revenue += items[index].getPricePerOne();
  }
}

// throws NoRemainingItems if there are not at least one dozen of the item
void Day::sellDozen(string name) {
  int index = indexOfItem(name);

  if (index < 0) {
    throw NoItem();
  } else if (items[index].getAmount() < 12) {
    throw NoRemainingItems();
  } else {
    items[index].setAmount(items[index].getAmount() - 12);
    items[index].setDozensSold(items[index].getDozensSold() + 1);
    revenue += items[index].getPricePerDozen();
  }
}

double Day::getPriceSingle(string name) {
  int index = indexOfItem(name);
  if (index < 0) {
    throw NoItem();
  } else {
    return items[index].getPricePerOne();
  }
}

double Day::getPriceDozen(string name) {
  int index = indexOfItem(name);
  if (index < 0) {
    throw NoItem();
  } else {
    return items[index].getPricePerDozen();
  }
}

bool Day::isInStock(string name) {
  if (indexOfItem(name) >= 0) {
    return true;
  } else {
    return false;
  }
}

int Day::getStock(string name) {
  int index = indexOfItem(name);
  if (index < 0) {
    throw NoItem();
  } else {
    return items[index].getAmount();
  }
}
