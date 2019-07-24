/*
  Kevin Fernandes
<<<<<<< HEAD
  September, 2017

  Here, we define the GPS and Temp data structures, and prompt the user for
  their gps location and 10 temperature data points
*/

#include <iostream>
=======
  September 2017

  This program uses two structures:
  1. GPS - with longitude, latitude, and altitude as members
  2. TempData - with date, time, unit of temperature, and a measurement
  The program prompts the user to enter the GPS data and 10 pieces of TempData 
*/


#include <iostream>
#include <string>

>>>>>>> 2e78f51d0cdc209387a3e155c402425e89871c45

struct GPS {
  double lon, lat, alt;
};

<<<<<<< HEAD
struct Temperature {
=======
struct TempData {
>>>>>>> 2e78f51d0cdc209387a3e155c402425e89871c45
  std::string date, time;
  char unit;
  double temp;
};

<<<<<<< HEAD
int main() {
  const int POINTS = 10;
  GPS local;
  Temperature data[POINTS];
  char unit;

  std::cout << "Please enter your longitude: ";
  std::cin >> local.lon;
  std::cout << "\nPlease enter your latitude: ";
  std::cin >> local.lat;
  std::cout << "\nPlease enter your altitude: ";
  std::cin >> local.alt;

  std::cout << "\nPlease enter your unit of measurment for temperature";
  std::cout <<  "('C' for celcius, 'F' for fahrenheit): ";
  std::cin >> unit;

  std::cout << local.lon << '\n' << local.lat << '\n' << local.alt << '\n';
  std::cout << unit << '\n';  
=======

void getGPSData(GPS*);
void printGPSData(GPS*);
// returns the number of TempData structs entered
int getTempData(TempData*, const int);
void printTempData(TempData*, const int);

// Adding min and max functions for TempData arrays
double min(TempData*, const int);
double max(TempData*, const int);
// if passed `true`, this will convert from celsius to fahrenheit, otherwise
// it will assume the double is in fahrenheit and convert to celsius
double convertUnits(double, bool);

int main() {
  int const POINTS = 10;
  int length;
  GPS local;
  TempData set[POINTS];

  // allows us to show more decimals in a double
  std::cout.precision(10);

  getGPSData(&local);
  length = getTempData(set, POINTS);

  std::cout << std::endl;

  printGPSData(&local);
  printTempData(set, length);

  system("pause");
  return 0;  
}


double max(TempData* data, const int count) {
  double max = data[0].temp;
  for (int i = 1; i < count; i++) {
    if (data[i].temp < max) {
      max = data[i].temp;
    }
  }
  return max;
}

double min(TempData* data, const int count) {
  double min = data[0].temp;
  for (int i = 1; i < count; i++) {
    if (data[i].temp < min) {
      min = data[i].temp;
    }
  }
  return min;
}

double convertUnits(double temp, bool isCelsius) {
  if (!isCelsius) {
    return (5/9 * temp) - (160/9);
  } else {
    return (temp * (9/5) + 32);
  }
}

void getGPSData(GPS* gps) {
  std::cout << "Please enter your longitude: ";
  std::cin >> gps->lon;
  std::cout << "Please enter your latitude: ";
  std::cin >> gps->lat;
  std::cout << "Please enter your altitude: ";
  std::cin >> gps->alt; 
}

void printGPSData(GPS* gps) {
  std::cout << "Your location:\nLongitude: " << gps->lon << "\nLatitude: ";
  std::cout << gps->lat << "\nAltitude: " << gps->alt << "\n\n";
}

int getTempData(TempData* data, const int count) {
  char unit;
  std::cout << "Enter your unit of temperature ('C' for celsius or 'F' for ";
  std::cout << "fahrenheit): ";
  std::cin >> unit;

  if (unit != 'C' && unit != 'F') {
    throw "Error: Unit of temperature is invalid\n";
  }

  std::cout << "Note: enter \"stop\" to stop entering data and print\n";
  std::string buffer;
  for (int i = 0; i < count; i++) {
    data[i].unit = unit;

    std::cout << "Enter the date (YYYY/MM/DD) and time (HH:MM:SS)\nDate:";
    std::cin >> buffer;
    if (buffer == "stop") { return i; }
    data[i].date = buffer;

    std::cout << "Time: ";
    std::cin >> buffer;
    if (buffer == "stop") { return i; }
    data[i].time = buffer;

    std::cout << "Enter the temperature measurment: ";
    std::cin >> buffer; 
    if (buffer == "stop") { return i; }
    data[i].temp = std::stod(buffer);
  }
  return count;
}

void printTempData(TempData* data, const int count) {
  // all data points will have the same unit
  bool isCelsius = (data[0].unit == 'C');
  // degree symbol in ASCII
  char degree = '\370';
  for (int i = 0; i < count; i++) {
    std::cout << "Data point " << i + 1 << ":\nDate: " << data[i].date << '\n';
    std::cout << "Time: " << data[i].time << "\nTemperature (" << degree;

    // added to show both units of temperature
    if (isCelsius) {
      std::cout << "C): " << data[i].temp << "\nTemperature (" << degree; 
      std::cout << "F): " << convertUnits(data[i].temp, isCelsius) << "\n\n";
    } else {
      std::cout << "F): " << data[i].temp << "\nTemperature (" << degree;
      std::cout << "C): " << convertUnits(data[i].temp, isCelsius) << "\n\n";
    }
  }
  return;
>>>>>>> 2e78f51d0cdc209387a3e155c402425e89871c45
}

