/*
  Kevin Fernandes
  October 2017

  This program takes in the name of a text file, and prints the following:
  * The number of words in the document
  * The longest word in the document
  * The average number of letters per word
  * The number of sentences in the document
*/

#include <iostream>
#include <fstream>

using namespace std;

string removePunctuation(string);

int main() {
  ifstream file;
  string filename, longWord = "", buffer;
  double avgLetters = 0;
  unsigned short len;
  unsigned sentenceCount = 0;
  unsigned long wordCount = 0;

  cout << "Enter filename: ";
  cin >> filename;
  file.open(filename);

  while (!file.eof()) {
    file >> buffer;
    len = buffer.length();

    // If the text formatted correctly, then periods should only appear at the
    // end of the word.
    if (buffer[len-1] == '.') {
      sentenceCount++;
    }

    buffer = removePunctuation(buffer);
    len = buffer.length();
    if (len > longWord.length()) {
      longWord = buffer;
    }

    avgLetters += len;
    wordCount++;
  }

  file.close();
  wordCount--;
  avgLetters -= len;

  if (wordCount != 0) {
    avgLetters /= wordCount;
  }

  cout << "Number of words: " << wordCount << '\n';
  cout << "Longest word: " << longWord << '\n';
  cout << "Average number of letters per word: " << avgLetters << '\n';
  cout << "Number of sentences: " << sentenceCount << '\n';

  system("pause");
  return 0;
}

string removePunctuation(string s) {
  for (int i = 0; i < s.length(); i++) {
    if (!isalpha(s[i])) {
      s.erase(i, 1);
    }
  }
  return s;
}

