/*
  Kevin Fernandes
  September 2017

  This program creates an array of 3 birthday structures, which are composed of
  a Date, Time, Name, Address, and a Phone number, all of which are also
  structures. Then, we create three birthdays in an array and print all of them
*/

#include <iostream>

struct Name {
  std::string first, last, mid;
};

struct Address {
  std::string city, state, zip, street;
  int num;
};

struct Phone {
  int areaCode;
  std::string number;
};

struct Date {
  int year, day, month;
};

struct Time {
  int hour, min;
  double sec;
};

struct Birthday {
  Name name;
  Date date;
  Time time;
  Address address;
  Phone phoneNum;
};

void printBirthday(Birthday);


int main() {
  const int SIZE = 3;
  Birthday bdays[SIZE];

  for (int i = 0; i < SIZE; i++) {
    bdays[i].name.first = "Kevin";
    bdays[i].name.last = "Fernandes";
    bdays[i].name.mid = "V";

    bdays[i].date.year = 2000;
    bdays[i].date.month = 10;
    bdays[i].date.day = 10;

    bdays[i].time.hour = 10;
    bdays[i].time.min = 20;
    bdays[i].time.sec = 2.342;

    bdays[i].phoneNum.areaCode = 857;
    bdays[i].phoneNum.number = "310-9501";
 
    bdays[i].address.num = 172;
    bdays[i].address.city = "Boston";
    bdays[i].address.state = "MA";
    bdays[i].address.zip = "02125";
    bdays[i].address.street = "Magnolia";

    printBirthday(bdays[i]);
    std::cout << std::endl;
  }


  return 0;
}

void printBirthday(Birthday bday) {
  std::cout << bday.name.first << ' ' << bday.name.mid << ' ' << bday.name.last;
  std::cout << "'s Birthday\nDate: " << bday.date.month << '/';
  std::cout << bday.date.day << '/' << bday.date.year << "\nTime: ";
  std::cout << bday.time.hour << ':' << bday.time.min << ':' << bday.time.sec;
  std::cout << "\nAddress: " << bday.address.num << ' ' << bday.address.street;
  std::cout << " St. " << bday.address.city << ", " << bday.address.state;
  std::cout << ' ' << bday.address.zip << "\nPhone: (" << bday.phoneNum.areaCode;
  std::cout << ") " << bday.phoneNum.number << '\n';
}

