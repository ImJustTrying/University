/*
 * "Item.cpp" file for the Item class
 * Bakery group project part 4
 * Nikita Voronin, Kevin Fernandes, Dmitry Volodkevich, Artem Roy
 * Basic Bakery Setup
 */

#include "Item.h"
#include <ctime>
using namespace std;

//Accessors
string Item::getName() const{
    return itemName;
}       // get Name of the object

double Item::getPricePerOne() const{
    return pricePerOne;
}   // get Price for one piece of the object

double Item::getPricePerDozen() const{
    return pricePerDozen;
}   // get Price for a dozen of pieces of the object

int Item::getAmount() const{
    return amount;
}   // get Amount of pieces of the object

int Item::getDozensSold() const {
    return dozensSold;
}

int Item::getSinglesSold() const {
    return singlesSold;
}

//Mutators
void Item::setName(string name){
    itemName = name;
}   // set Name of the object

void Item::setPricePerOne(double priceOne){
    pricePerOne = priceOne;
}   // set Price for one piece of the object

void Item::setPricePerDozen(double priceDozen){
    pricePerDozen = priceDozen;
}   // set Price for a dozen of pieces of the object

void Item::setAmount(int a){
    amount = a;
}   // set the amount of pieces of the object

void Item::setDozensSold(int a) {
    dozensSold = a;
}

void Item::setSinglesSold(int a) {
    singlesSold = a;
}

//Constructors
Item::Item(){
    setName("");
    setPricePerOne(0);
    setPricePerDozen(0);
    setAmount(0);
}

Item::Item(string name, double priceOne, double priceDozen, int amount){
    setName(name);
    setPricePerOne(priceOne);
    setPricePerDozen(priceDozen);
    setAmount(amount);
}

