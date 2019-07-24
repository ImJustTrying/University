/*
  Kevin Fernandes
  October 2017

  This program take in two filenames, and compares each corresponding line in
  each file. If they are identicle, than write that line to a new file. If not,
  write the name of the file, line number, and the line itself for both lines
  in the new file.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void writeRemainingLines(ofstream*, ifstream*);

int main() {
  ifstream in1, in2;
  ofstream out;
  string file1, file2, buf1, buf2;
  short line1 = 0, line2 = 0;
  
  cout << "Enter filename 1: ";
  cin >> file1;
  cout << "Enter filename 2: ";
  cin >> file2;

  in1.open(file1);
  in2.open(file2);
  out.open("output.txt");  

  while (!in1.eof() && !in2.eof()) {
    getline(in1, buf1);
    getline(in2, buf2);
    line1++; line2++;

    if (in1.bad() || in2.bad()) {
      cerr << "Error: badbit read from input file\n";
    }

    if (buf1 != buf2) {
      out << ">>>> " << file1 << " L: " << line1 << '\n' << buf1 << '\n';
      out << ">>>> " << file2 << " L: " << line2 << '\n' << buf2 << '\n';
    } else {
      out << buf1 << '\n';
    }
  }

  if (in1.eof() && !in2.eof()) {
    writeRemainingLines(&out, &in2);
  } else if (!in1.eof() && in2.eof()) {
    writeRemainingLines(&out, &in1);
  }

  in1.close();
  in2.close();
  out.close();

  system("pause");
  return 0;
}

void writeRemainingLines(ofstream* out, ifstream* in) {
  string buffer;

  while (!in->eof()) {
    getline(*in, buffer);
    if (in->bad()) {
      cerr << "Error: badbit read from input file\n";
    }
    *out << buffer << '\n';
  }
}


