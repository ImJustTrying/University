/*
  Kevin Fernandes
  October 2017

  This program takes a filename as input. It propts the user for the type of
  data conversion they would like; Prompts include:
  * Fahrenheit to Celcius and vice versa
  * Feet to Meters and vice versa
  * Grams to Pounds and vice versa
  The program enters this converted data into a new file.
*/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

double f_to_c(double);
double c_to_f(double);
double ft_to_m(double);
double m_to_ft(double);
double g_to_lb(double);
double lb_to_g(double);
void writeConvertedData(ifstream*, ofstream*, char);
string removeZeros(string);

int main() {
  ifstream input;
  ofstream output;
  string filename;
  double buffer;
  char convertType;

  cout << "Enter filename: ";
  cin >> filename;

  cout << "Enter one of the following digits for the corresponding data ";
  cout << "conversion:\n";

  cout << "1 - Fahrenheit to Celsius\n2 - Celsius to Fahrenheit\n";
  cout << "3 - Feet to Meters\n4 - Meters to Feet\n";
  cout << "5 - Grams to Pounds\n6 - Pounds to Grams\n> ";
  cin >> convertType;

  while (!isdigit(convertType)) {
    cerr << "Error: Input value is not an integer\n";
    cout << "Enter a digit between 1-6\n> ";
    cin.get(convertType);
  }

  input.open(filename);
  output.open("converted_data.txt");
  writeConvertedData(&input, &output, convertType);
  input.close();
  output.close();

  system("pause");
  return 0;
}

void writeConvertedData(ifstream* in, ofstream* out, char convertType) {
  double buffer;
  string space(10, ' '), space2, buf;

  switch (convertType) {
    case '1': *out << 'F' << space << "C\n"; break;
    case '2': *out << 'C' << space << "F\n"; break;
    case '3': *out << "ft" << space << "m\n"; break;
    case '4': *out << 'm' << space << "ft\n"; break;
    case '5': *out << 'g' << space << "lb\n"; break;
    case '6': *out << "lb" << space << "g\n"; break;
  }

  while (!in->eof()) {
    *in >> buffer;
    if (in->fail()) {
      break;
    }
    if (in->bad()) {
      break;
    }

    buf = removeZeros(to_string(buffer));
    space2 = string((11 - buf.size()), ' ');
    *out << setprecision(10) << buffer << space2;

    switch (convertType) {
      case '1': *out << f_to_c(buffer) << '\n'; break;
      case '2': *out << c_to_f(buffer) << '\n'; break;
      case '3': *out << ' ' << ft_to_m(buffer) << '\n'; break;
      case '4': *out << m_to_ft(buffer) << '\n'; break;
      case '5': *out << g_to_lb(buffer) << '\n'; break;
      case '6': *out << ' ' << lb_to_g(buffer) << '\n'; break;
    }
  }

  return;
}

string removeZeros(string real) {
  unsigned short eraseLen = 0;
  for (int i = real.size() - 1; i >= 0; i--) {
    if (real[i] == '.') {
      eraseLen++;
      break;
    }
    if (real[i] != '0') {
      break;
    } else {
      eraseLen++;
    }
  }
  real.erase(real.size() - eraseLen, eraseLen);
  return real;
}

double f_to_c(double f) {
  return f * (5/9) - 32;
}

double c_to_f(double c) {
  return c * (9/5) + 32;
}

double ft_to_m(double ft) {
  return ft * 0.3048;
}

double m_to_ft(double m) {
  return m * 3.28084;
}

double g_to_lb(double g) {
  return g * 0.00220462;
}

double lb_to_g(double lb) {
  return lb * 453.59237;
}

