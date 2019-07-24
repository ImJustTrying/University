// Implementation file for the NumberList class
#include <iostream>  // For cout
#include <new> // For bad_alloc
#include "NumberList.h"
using namespace std;

int NumberList::getSize() {
  return size;
}

bool NumberList::isSorted() {
  ListNode* temp = head;
  if (temp == nullptr) { return true; }
  while (temp->next != nullptr) {
    if (temp->value > temp->next->value) {
      return false;
    }
  }
  return true;
}

void NumberList::print300() {
  ListNode* temp = head;

  if (size < 300) {
    while (temp != nullptr) {
      cout << temp->value << '\n';
      temp = temp->next;
    }
  } else {
    int n = size / 2 - 150;
    while (n > 0) {
      temp = temp->next;
      n--;
    }

    for (int i = 0; i < 300; i++) {
      cout << temp->value << '\n';
      temp = temp->next;
    }
  }
  return;
}

void NumberList::insertSorted(int num) {
  ListNode* newNode;
  try {
    newNode = new ListNode;
  } catch (bad_alloc& ba) {
    cerr << "Error (Bad allocation): " << ba.what() << '\n';
    exit(EXIT_FAILURE);
  }
  ListNode* buf = head;

  newNode->value = num;
  newNode->next = nullptr;

  if (head == nullptr) {
    head = newNode;
    size++;
    return;
  }
  if (head->next == nullptr) {
    head->next = newNode;
    size++;
    return;
  }

  // we need to keep track of the node before the spot where our new node
  // will be inserted; this is why we check buf->next->value instead of
  // buf->value, and buf->next != nullptr instead of buf != nullptr
  while (buf->next != nullptr) {
   if (buf->next->value > num) {
      newNode->next = buf->next;
      buf->next = newNode;
      size++;
      return;
    }
    buf = buf->next;
  }
  // if `num` is the greatest value, attatch the new node to the end
  buf->next = newNode;
  size++;
  return;
}

//**************************************************
// appendNode appends a node containing the        *
// value pased into num, to the end of the list.   *
//**************************************************

void NumberList::appendNode(int num)
{
   ListNode *newNode;  // To point to a new node
   ListNode *nodePtr;  // To move through the list

   // Allocate a new node and store num there.
   newNode = new ListNode;
   newNode->value = num;
   newNode->next = nullptr;

   // If there are no nodes in the list
   // make newNode the first node.
   if (!head)
      head = newNode;
   else  // Otherwise, insert newNode at end.
   {
      // Initialize nodePtr to head of list.
      nodePtr = head;

      // Find the last node in the list.
      while (nodePtr->next)
         nodePtr = nodePtr->next;

      // Insert newNode as the last node.
      nodePtr->next = newNode;
   }
   size++;
}

//**************************************************
// displayList shows the value                     *
// stored in each node of the linked list          *
// pointed to by head.                             *
//**************************************************

void NumberList::displayList() const
{
   ListNode *nodePtr;  // To move through the list

   // Position nodePtr at the head of the list.
   nodePtr = head;

   // While nodePtr points to a node, traverse
   // the list.
   while (nodePtr)
   {
      // Display the value in this node.
      cout << nodePtr->value << endl;

      // Move to the next node.
      nodePtr = nodePtr->next;
   }
}

//**************************************************
// The insertNode function inserts a node with     *
// num copied to its value member.                 *
//**************************************************

void NumberList::insertNode(int num)
{
   ListNode *newNode;					// A new node
   ListNode *nodePtr;					// To traverse the list
   ListNode *previousNode = nullptr;	// The previous node

   // Allocate a new node and store num there.
   newNode = new ListNode;
   newNode->value = num;
   
   // If there are no nodes in the list
   // make newNode the first node
   if (!head)
   {
      head = newNode;
      newNode->next = nullptr;
   }
   else  // Otherwise, insert newNode
   {
      // Position nodePtr at the head of list.
      nodePtr = head;

      // Initialize previousNode to nullptr.
      previousNode = nullptr;

      // Skip all nodes whose value is less than num.
      while (nodePtr != nullptr && nodePtr->value < num)
      {  
         previousNode = nodePtr;
         nodePtr = nodePtr->next;
      }

      // If the new node is to be the 1st in the list,
      // insert it before all other nodes.
      if (previousNode == nullptr)
      {
         head = newNode;
         newNode->next = nodePtr;
      }
      else  // Otherwise insert after the previous node.
      {
         previousNode->next = newNode;
         newNode->next = nodePtr;
      }
   }
   size++;
}

//**************************************************
// The deleteNode function searches for a node     *
// with num as its value. The node, if found, is   *
// deleted from the list and from memory.          *
//**************************************************

void NumberList::deleteNode(int num)
{
   ListNode *nodePtr;       // To traverse the list
   ListNode *previousNode;  // To point to the previous node

   // If the list is empty, do nothing.
   if (!head)
      return;
   
   // Determine if the first node is the one.
   if (head->value == num)
   {
      nodePtr = head->next;
      delete head;
      head = nodePtr;
   }
   else
   {
      // Initialize nodePtr to head of list
      nodePtr = head;

      // Skip all nodes whose value member is 
      // not equal to num.
      while (nodePtr != nullptr && nodePtr->value != num)
      {  
         previousNode = nodePtr;
         nodePtr = nodePtr->next;
      }

      // If nodePtr is not at the end of the list, 
      // link the previous node to the node after
      // nodePtr, then delete nodePtr.
      if (nodePtr)
      {
         previousNode->next = nodePtr->next;
         delete nodePtr;
      }
   }
   size--;
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************

NumberList::~NumberList()
{
   ListNode *nodePtr;   // To traverse the list
   ListNode *nextNode;  // To point to the next node

   // Position nodePtr at the head of the list.
   nodePtr = head;

   // While nodePtr is not at the end of the list...
   while (nodePtr != nullptr)
   {
      // Save a pointer to the next node.
      nextNode = nodePtr->next;

      // Delete the current node.
      delete nodePtr;

      // Position nodePtr at the next node.
      nodePtr = nextNode;
   }
}
