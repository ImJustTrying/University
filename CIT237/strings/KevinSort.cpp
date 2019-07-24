/*
  Kevin Fernandes
  September 2017
<<<<<<< HEAD

=======
>>>>>>> 2e78f51d0cdc209387a3e155c402425e89871c45
  Sorts an array of strings alphabetically and removes duplicates elements
*/

#include <iostream>

<<<<<<< HEAD
std::string* removeDupes(std::string[], int);
void sort(std::string[], int);
void printArray(std::string, std::string[], int);
=======
std::string* removeDupes(std::string[], int, int*);
void printArray(std::string, std::string[], int);
void sort(std::string[], int);
>>>>>>> 2e78f51d0cdc209387a3e155c402425e89871c45
void swap(std::string[], int, int);
bool isSorted(std::string[], int);

int main() {
  const int SIZE = 8;
  std::string list[] = {"cat","giraffe","gorilla","cat","dog","lion","tiger","giraffe"};
  std::string* newList;
<<<<<<< HEAD

  std::cout << "Before removing duplicates: ";
  printArray("list", list, SIZE);
  std::cout << "After removing duplicates: ";  
  newList = removeDupes(list, SIZE);
  printArray("list", newList, newList->length());
=======
  int newLen;

  std::cout << "Before removing duplicates: ";
  printArray("list", list, SIZE);

  newList = removeDupes(list, SIZE, &newLen);
  std::cout << "After removing duplicates: ";
  printArray("list", newList, newLen);

  sort(newList, newLen);
  std::cout << "After sorting: ";
  printArray("list", newList, newLen);
>>>>>>> 2e78f51d0cdc209387a3e155c402425e89871c45

  delete[] newList; 
  return 0;
}

void printArray(std::string name, std::string array[], int len) {
  std::cout << name << ": [";
  for (int i = 0; i < len; i++) {
    if (array[i] == "") { continue; }
    std::cout << array[i];
    i == len - 1 ? std::cout << "]\n" : std::cout << ',';
  }
}

<<<<<<< HEAD
std::string* removeDupes(std::string array[], int len) {
  
=======
// this will return an array without duplicates, and sets the value of `lenPtr`
// to the length of the new array
std::string* removeDupes(std::string array[], int len, int* lenPtr) {
  int newLen = len;

  for (int i = 0; i < len; i++) {
    if (array[i] == "") { continue; }
    for (int j = 0; j < len; j++) {
      if (j == i) { continue; }
      if (array[j] == array[i]) { 
        array[j] = "";
        newLen--;
      }
    }
  }

  std::string* newArr = new std::string[newLen];
  int t = 0;

  for (int k = 0; k < len; k++) {
    if (array[k] != "") {
      newArr[t] = array[k];
      t++;
    }
  }

  *lenPtr = newLen;
  return newArr;
>>>>>>> 2e78f51d0cdc209387a3e155c402425e89871c45
}

// this is the bubblesort algorithm
void sort(std::string array[], int len) {
  for (int i = 1; i < len; i++) {
   if (array[i].at(0) < array[i-1].at(0)) {
<<<<<<< HEAD
      swap(array, i, i+1);
=======
      swap(array, i, i-1);
>>>>>>> 2e78f51d0cdc209387a3e155c402425e89871c45
    }
  }
  if (!isSorted(array, len)) {
    sort(array, len);
  }
  return;
}

bool isSorted(std::string array[], int len) {
<<<<<<< HEAD
  for (int i = 0; i < len-1; i++) {
=======
  for (int i = 0; i < (len-1); i++) {
>>>>>>> 2e78f51d0cdc209387a3e155c402425e89871c45
    if (array[i] > array[i+1]) {
      return false;
    }
  }
  return true;
}

void swap(std::string array[], int index1, int index2) {
  std::string temp = array[index1];
  array[index1] = array[index2];
  array[index2] = temp;
  return;
}

<<<<<<< HEAD
bool isInArrayPast(std::string array[], int len, std::string value, int index) {
  for (int i = 0; i < len; i++) {
    if (array[i] == value) {
      return true;
    }
  }
  return false;
}
=======
>>>>>>> 2e78f51d0cdc209387a3e155c402425e89871c45
