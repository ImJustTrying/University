/*
  Kevin Fernandes 
  September 2017

  This program defines a Cup structure and creates three instances of it
*/

#include <iostream>

struct Cup {
  double topWidth, botWidth, height, capacity;
  std::string color, manufacturer, material;
  bool hasHandle;
};

void printCups(Cup[], const int);
template <typename T>
void printProperty(std::string, T);
void getCups(Cup[], const int);


int main() {
  const int SIZE = 3;
  Cup cups[SIZE];

  getCups(cups, SIZE);
  printCups(cups, SIZE);

  return 0;  
}


void getCups(Cup cups[], const int count) {
  for (int i = 0; i < count; i++) {
    std::cout << "Please enter the following about cup " << i+1 << '\n';
    std::cout << "Color: ";
    std::cin >> cups[i].color;

    std::cout << "Material: ";
    std::cin >> cups[i].material;

    std::cout << "Manufacturer: ";
    std::cin >> cups[i].manufacturer;

    std::cout << "Capacity (fl oz): ";
    std::cin >> cups[i].capacity;

    std::cout << "Height (cm): ";
    std::cin >> cups[i].height;

    std::cout << "Top width (cm): ";
    std::cin >> cups[i].topWidth;

    std::cout << "Bottom width (cm): ";
    std::cin >> cups[i].botWidth;

    std::cout << "Does it have a handle? (1 for yes, 0 for no): ";
    std::cin >> cups[i].hasHandle;
  }
}

template <typename T>
void printProperty(std::string propName, T prop) {
  std::cout << propName << " = " << prop << '\n';
}

void printCups(Cup cups[], const int count) {
  for (int i = 0; i < count; i++) {
    std::cout << "Cup " << i+1 << '\n';
    printProperty<std::string>("Color", cups[i].color);
    printProperty<std::string>("Material", cups[i].material);
    printProperty<std::string>("Manufacturer", cups[i].manufacturer);
    printProperty<double>("Capacity", cups[i].capacity);
    printProperty<double>("Height", cups[i].height);
    printProperty<double>("Top width", cups[i].topWidth);
    printProperty<double>("Bottom width", cups[i].botWidth);
    printProperty<bool>("Handle", cups[i].hasHandle);
    std::cout << std::endl;
  }
}

