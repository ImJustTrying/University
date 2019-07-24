#include "NumberList.h"
#include <iostream>

using namespace std;

void initInsert(NumberList);
void initAppend(NumberList);
void searchTest(NumberList);
void deleteElements(NumberList);
void test(NumberList);

int main() {
  NumberList list; 
  list.appendNode(3.1);
  list.appendNode(7.2);
  list.appendNode(4);
  list.appendNode(2.3);
  list.appendNode(3.5);

  cout << "list: ";
  list.displayList();

  cout << "Found 2.3? " << list.search(2.3) << " At? " << list.search(2.3, 0) << '\n';
  cout << "Found 1? " << list.search(1) << " At? " << list.search(1, 0) << '\n';
  cout << "Found 8? " << list.search(8) << " At? " << list.search(8, 0) << '\n';

  list.deleteNode(3.1);
  list.deleteNode(7.2);
  list.deleteNode(4);
  list.deleteNode(2.3);
  list.deleteNode(3.5);

  NumberList list2;
  list2.insertNode(3.1);
  list2.insertNode(7.2);
  list2.insertNode(4);
  list2.insertNode(2.3);
  list2.insertNode(3.5);

  cout << "list: ";
  list2.displayList();

  cout << "Found 2.3? " << list2.search(2.3) << " At? " << list2.search(2.3, 0) << '\n';
  cout << "Found 1? " << list2.search(1) << " At? " << list2.search(1, 0) << '\n';
  cout << "Found 8? " << list2.search(8) << " At? " << list2.search(8, 0) << '\n';
  system("pause");
}
