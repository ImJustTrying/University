/*
  Kevin Fernandes
  September 2017

  Here we list structures of miscellaneous objects, namely:
  Books, Boxes, Bottle, Chemical Elements, Gemstones, Pens, Address, Names,
  Item on a menu, Playing Cards, Canned Food, and Music Tracks
*/

#include <string>

struct Book {
  std::string title, publisher;
  int isbn;
};

struct Box {
  std::string contents, material;
};

struct Bottle {
  std::string manufacturer, brand;
  double capacity, height;
};

struct Element {
  int atomicNum, isotope, row, col; 
  bool isMetal;
  std::string name, symbol;
  double mass;
};

struct Gemstone {
  std::strint name, color;
  double width, heigth;
};

struct Pen {
  std::string manufacturer, brand, inkColor;
  double length;
};

struct MenuItem {
  std::string name;
  double cost;
  int quantity, calPerServ, servings;
};

struct Card {
  // use 10, 11, and 12 for joker, queen, and king respectively
  int num, type;
  bool isRed;
  std::string manufacturer, brand;
};

struct CannedFood {
  std::string food, manufacturer;
  int quantity, calPerServ, servings;
};

struct MusicTrack {
  int lenHour, lenSec;
  std::string title, artist, album;
};

struct Name {
  std::string first, last, suffix, prefix;
  char midInitial;
};

struct Address {
  std::string street, city, state, zip, streetSuffix;
  int doorNum;
};

