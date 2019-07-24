#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool isValid(string);
void readWords(vector<string>*, string);
void writeWords(vector<string>*, string);
int findWord(vector<string>*, string);
int binarySearch(vector<string>*, string, int, int);

int main() {
	string filename, buffer = "";
	const string OUTPUT_FILE = "letters.txt";
	vector<string> words;
	unsigned index = 0, wordSize;
  int wordIndex;

	cout << "Please enter the name of the input file: ";
	getline(cin, filename);

	readWords(&words, filename);
	wordSize = words[0].length();
	writeWords(&words, OUTPUT_FILE);

	cout << "Please enter a word of length " << words[0].size() << ": ";
	cin >> buffer;
	while (buffer.length() != wordSize) {
    cerr << "Error: word is not " << wordSize << " characters long\n";
    cout << "Please enter a word of length " << wordSize << ": ";
    cin >> buffer;
	}

  try {
    wordIndex = findWord(&words, buffer);
  } catch (exception& e) {
    cout << "word \"" << buffer << "\" not found\n";
    system("pause");
    return 0;
  }

  cout << "Your word was found at index: " << wordIndex << endl;	
	system("pause");
}

// a word is valid if it has no repeating characters
bool isValid(string word) {
	const int n = word.size();
	if (n <= 1) { return true; }

	char character = word[0];
	for (int i = 1; i < n; i++) {
		if (character == word[i]) {
			return false;
		}
	}
	return isValid(word.substr(1, n - 1));
}

void readWords(vector<string>* wordList, string filename) {
	ifstream in;
	char* buffer = new char[20];
	char* tempBuf;
	char buf;
	int counter = 0;

	try {
		in.open(filename, fstream::in);
	}	catch (ifstream::failure& fail) {
		cerr << "Error: failbit set while opening file\n";
		system("pause");
		exit(EXIT_FAILURE);
	}

	if (in.is_open()) {
		in.get(buf);
		do {
			buffer[counter] = buf;
			counter++;
			in.get(buf);
		} while (buf != ' ' && buf != '\t' && buf != '\n' && buf != '\r');

		buffer[counter] = '\0';
		counter++;
		tempBuf = new char[counter];

		for (int i = 0; i < counter; i++) {
			tempBuf[i] = buffer[i];
		}

		delete[] buffer;
		wordList->push_back(string(tempBuf));
		delete[] tempBuf;
		buffer = new char[counter];

		while (!(in.eof())) {
      // remove all tabs, spaces, and newlines
      while (true) {
        buf = in.peek();
        if (buf != ' ' && buf != '\n' && buf != '\t' && buf != '\r') {
          break;
        } else if (in.eof()) {
          delete[] buffer;
          return;
        } else {
          in.get(buf);
        }
      }

			in.read(buffer, counter);
			wordList->push_back(string(buffer));

			if (in.bad()) {
				cerr << "Warning: badbit set while reading file\n";
				break;
			}
			if (in.fail()) {
				cerr << "Warning: failbit set while reading file\n";
				break;
			}
		}
		delete[] buffer;
		in.close();
	}
	
	return;
}

void writeWords(vector<string>* wordList, string filename) {
	ofstream out;
  int lineCounter = 0;
	const int SIZE = wordList->size();

	try {
		out.open(filename, fstream::out | fstream::trunc);
	}	catch (ifstream::failure& fail) {
		cerr << "Error: failure occured while opening file\n";
		system("pause");
		exit(EXIT_FAILURE);
	}

	for (int i = 1; i < SIZE; i++) {
		if (isValid(wordList->at(i))) {

      if (lineCounter == 0) {
        out.write(wordList->at(i).c_str(), wordList->at(i).length() - 1);

      } else if (lineCounter % 10 == 0) {
				out.put('\n');
        out.write(wordList->at(i).c_str(), wordList->at(i).length() - 1);

      } else {
        out.put(' ');
        out.write(wordList->at(i).c_str(), wordList->at(i).length() - 1);
      }

      lineCounter++;
    }
	}
	out.close();
}

int findWord(vector<string>* wordList, string word) {
  const int SIZE = wordList->size();

  for (int i = 0; i < SIZE; i++) {
    if (word == wordList->at(i)) { return i; }
  }
  throw exception();
}

int binarySearch(vector<string>* wordList, string word, int first, int last) {
  if (first > last) { return (-1); }
  int mid = (last - first) / 2;

  if (wordList->at(mid) == word) {
    return mid;
  }

  if (wordList->at(mid)[0] < word[0]) {
    return binarySearch(wordList, word, mid, last);
  }

  if (wordList->at(mid)[0] > word[0]) {
    return binarySearch(wordList, word, first, mid + 1);
  }
}
