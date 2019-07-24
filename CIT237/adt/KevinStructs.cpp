/*
  Kevin Fernandes
<<<<<<< HEAD
  September, 2017

  This program creates the following structures:
  1. GPS, which includes longitude, altitude, and latitude
  2. Trajectory Position, which includes an (x,y) pair, and a direction (i.e. 
  N, E, W, S)
  3. Phone Number, which contains the area code and the actual number
  4. Address, which has the street name, city, state, and zip code
  5. Temperature, which has the date, time, temperature, and the units of 
  temperature
=======
  September 2017

  Here we create the following structures:
  1. A GPS struct with longitutde, latitude, and altitude variables
  2. A trajectory struct with (x,y) coordinates and a direction ('N', 'S', etc)
  3. A Phone number struct with the area code and the actual number
  4. An address struct with a street, city, state, and zip-code
  5. A Temperature data struct with date and time, along with a unit ('F' or
  'C'), and finally the actual measurement
>>>>>>> 2e78f51d0cdc209387a3e155c402425e89871c45
*/

#include <string>

struct GPS {
  double lon, lat, alt;
};

struct trajectory {
  double x, y;
  char direction;
};

struct phoneNumber {
<<<<<<< HEAD
  std::string areaCode, number;
};

struct address {
  std::string street, city, state, zip; 
};

struct temp {
  std::string date;
  double time, temp;
  char unit;
=======
  int areaCode;
  std::string number;
};

struct address {
  std::string street, city, state, zip;
};

struct tempData {
  std::string date, time;
  char unit;
  double temp;
>>>>>>> 2e78f51d0cdc209387a3e155c402425e89871c45
};

int main() {
  return 0;
}

