/*
  Kevin Fernandes
  November 2017

  This program reads a binary file, converts the contents, and writes it to
  both a binary and a text file.
*/

#include <fstream>
#include <iostream>
#include <new>

using namespace std;

// data structure for binary data
// all temperatures are in celsius, and precipitation in centimeters
struct Data {
  int year;
  double lowestT, highestT;
  double warmestMinT, coolestMaxT;
  double avgMinT, avgMaxT, meanT;
  double totalPrecip, totalSnow;
  double max24HrPrecip, max24HrSnow;
};

// all temperatures are in fahrenheit and precipitation in inches
struct OtherData {
  int year;
  double lowestT, highestT;
  double avgMinT, avgMaxT, meanT;
  double totalPrecip, totalSnow;
  double max24HrPrecip, max24HrSnow;
};

double CtoF(double);
double CmtoIn(double);
void printData(Data);
void DataToOtherData(OtherData*, Data*, unsigned short);

void readBinaryData(Data*, unsigned short);
void writeBinaryData(OtherData*, unsigned short);
void writeTextData(OtherData*, unsigned short);

int main() {
  Data* dataArray;
  OtherData* otherDataArray;
  unsigned short count; 

  // calculate the number of Data structures in the binary file 
  {
    fstream binIn("wxdata.dat", ios::in | ios::binary);
    if (!binIn.is_open()) {
      cerr << "Error: input file wxdata.dat could not be opened\n";
      exit(EXIT_FAILURE);
    }

    streampos begin, end;
    begin = binIn.tellg();
    binIn.seekg(0, ios::end);
    end = binIn.tellg();
    // num of bytes in file / num of bytes in Data structure
    count = (unsigned short)(end - begin) / sizeof(Data);
  }

  try {
    dataArray = new Data[count];
    otherDataArray = new OtherData[count];
  } catch (bad_alloc ba) {
    cerr << "Error: Bad allocation\n";
    exit(EXIT_FAILURE);
  }

  readBinaryData(dataArray, count);
  printData(dataArray[0]);
  DataToOtherData(otherDataArray, dataArray, count);
  delete[] dataArray;

  writeTextData(otherDataArray, count);
  writeBinaryData(otherDataArray, count);
  delete[] otherDataArray;
}

void DataToOtherData(OtherData* od, Data* d, unsigned short len) {
  for (int i = 0; i < len; i++) {
    od[i].year = d[i].year;
    od[i].lowestT = CtoF(d[i].lowestT);
    od[i].highestT = CtoF(d[i].highestT);
    od[i].avgMinT = CtoF(d[i].avgMinT);
    od[i].avgMaxT = CtoF(d[i].avgMaxT);
    od[i].meanT = CtoF(d[i].meanT);
    od[i].totalPrecip = CmtoIn(d[i].totalPrecip);
    od[i].totalSnow = CmtoIn(d[i].totalSnow);
    od[i].max24HrPrecip = CmtoIn(d[i].max24HrPrecip);
    od[i].max24HrSnow = CmtoIn(d[i].max24HrSnow);
  }
  return;
}

void writeBinaryData(OtherData* d, unsigned short len) {
  ofstream out("wxdata.bin", ios::binary);
  if (!out.is_open()) {
    cerr << "Error: ouput file wxdata.txt could not be opened\n";
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < len; i++) {
    out.write(reinterpret_cast<char*>(&d[i]), sizeof(OtherData));
    if (out.bad() || out.fail()) {
      cerr << "Warning: Badbit or Failbit set while writing to wxdata.bin\n";
    }
  }
}

void writeTextData(OtherData* d, unsigned short len) {
  ofstream out("wxdata.txt");
  if (!out.is_open()) {
    cerr << "Error: ouput file wxdata.txt could not be opened\n";
    exit(EXIT_FAILURE);
  }

  // header line
  out << "year | lowest temperature | highest temperature | average minimum ";
  out << "temperature | average maximum temperature | mean temperature | ";
  out << "total precipitation | total snow | max 24 hour precipitation | ";
  out << "max 24 hour snow\n";

  for (int i = 0; i < len; i++) {
    if (out.bad() || out.fail()) {
      cerr << "Warning: Badbit or Failbit set while writing to wxdata.txt\n";
    }
    out << d[i].year << ' ' << d[i].lowestT << ' ' << d[i].highestT << ' ';
    out << d[i].avgMinT << ' ' << d[i].avgMaxT << ' ' << d[i].meanT << ' ';
    out << d[i].totalPrecip << ' ' << d[i].totalSnow << ' ';
    out << d[i].max24HrPrecip << ' ' << d[i].max24HrSnow << '\n';
  }
  out.close();
  return;
}

void readBinaryData(Data* dataArray, unsigned short len) {
  fstream binIn("wxdata.dat", ios::in | ios::binary);
  if (!binIn.is_open()) {
    cerr << "Error: input file wxdata.dat could not be opened\n";
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < len; i++) {
    binIn.read(reinterpret_cast<char*>(&dataArray[i]), sizeof(Data));
    if (binIn.bad() || binIn.fail()) {
      cerr << "Warning: Badbit or Failbit set on input file wxdata.dat\n";
    }
 }
  binIn.close();
  return;
}

double CtoF(double temp) {
  return temp * 9/5 + 32;
}

double CmtoIn(double dist) {
  return dist / 2.54;
}

void printData(Data d) {
  cout << "Year: " << d.year << "\nLowest temperature: " << d.lowestT << "°C";
  cout << "\nHighest temperature: " << d.highestT << "°C";
  cout << "\nGreatest minimum temperature: " << d.warmestMinT << "°C\n";
  cout << "Least maximum temperature: " << d.coolestMaxT << "°C\n";
  cout << "Average minimum temperature: " << d.avgMinT << "°C\n";
  cout << "Average maximum temperature: " << d.avgMaxT << "°C\n";
  cout << "Mean temperature: " << d.meanT << "°C\n";
  cout << "Total precipitation: " << d.totalPrecip << "cm\n";
  cout << "Total snow: " << d.totalSnow << "cm\n";
  cout << "Maximum 24 hour precipitation: " << d.max24HrPrecip << "cm\n";
  cout << "Maximum 24 hour snow: " << d.max24HrSnow << "cm" << endl;
}
