// Specification file for the NumberList class
#ifndef NUMBERLIST_H
#define NUMBERLIST_H
#include <cstddef> // nullptr

class NumberList
{
private:
   // Declare a structure for the list
   struct ListNode
   {
      int value;           // The value in this node
      struct ListNode *next;  // To point to the next node
   }; 

   ListNode *head;            // List head pointer
   int size;    // adding to print middle 300 elements

public:
   // Constructor
   NumberList()
      { head = nullptr;
        size = 0; }
      
   // Destructor
   ~NumberList();
      
   // Linked list operations
   void appendNode(int);
   void insertNode(int);
   // Adding another insert function to keep the list sorted while inserting
   void insertSorted(int);
   void deleteNode(int);
   void displayList() const;
   // adding functions for printing, accessing, checking the list ordering
   int getSize();
   void print300();
   bool isSorted();
};

#endif
