/*
 * Kevin Fernandes
 * September 10, 2017
*/

#include <iostream>

void getData(double*, const int, int*);
double total(double*, int);
double average(double*, int);
double min(double*, int);
double max(double*, int);
void printFormat(std::string, double);

// take up to 10 double inputs
// output average, min, max, and sum
int main() { 
  const int SIZE = 10;
  int length = 0;
  double data[SIZE];

  getData(data, SIZE, &length);
  printFormat("Total", total(data, length));
  printFormat("Average", average(data, length));
  printFormat("Maximum", max(data, length));
  printFormat("Minimum", min(data, length));
  return 0;
}

void getData(double* data, const int size, int* length) {
  std::cout << "Enter up to 10 real data values (enter '-999' to stop input)\n";
  double temp;

  for (int i = 0; i < size; i++) {
    std::cout << "Enter value " << i + 1 << ": ";
    // will only take real numbers as input since temp is of type double
    std::cin >> temp;
    if (temp == -999) {
      // this keeps the program from acessing garbage data 
      if (i == 0) {
        data[0] = 0;
      }
      *length = i;
      return;
    }
    data[i] = temp;
  }
  *length = 10;
  return;
}

void printFormat(std::string type, double num) {
  std::cout << type << ": " << num << '\n';
}

double total(double* data, int n) {
  double sum = 0;
  for (int i = 0; i < n; i++) {
    sum += data[i];
  }
  return sum;
}

double average(double* data, int n) {
  return total(data, n) / n;
}

double min(double* data, int n) {
  double min = data[0];
  for (int i = 1; i < n; i++) {
    if (data[i] < min) {
      min = data[i];
    }
  }
  return min;
}

double max(double* data, int n) {
  double max = data[0];
  for (int i = 1; i < n; i++) {
    if (data[i] > max) {
      max = data[i];
    }
  }
  return max;
}

