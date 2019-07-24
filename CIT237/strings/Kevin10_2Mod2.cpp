// This program tests a customer number to determine whether
// it is in the proper format.
#include <iostream>
#include <cctype>
using namespace std;

// Function prototype
bool testNum(char [], int);

int main()
{
   const int SIZE = 8;   // Array size
   char customer[SIZE];  // To hold a customer number

   // Get the customer number.
   cout << "Enter a customer number in the form ";
   cout << "LLLNNNN\n";
   cout << "(LLL = letters and NNNN = numbers): ";
   cin.getline(customer, SIZE);

   // Determine whether it is valid.
   /* EDITED PORTION */
   while(!testNum(customer, SIZE)) {
      cout << "That is not the proper format of the ";
      cout << "customer number.\nHere is an example:\n";
      cout << "   ABC1234\n";

      cout << "Enter a customer number in the form ";
      cout << "LLLNNNN\n";
      cout << "(LLL = letters and NNNN = numbers): ";
      cin.getline(customer, SIZE);
   }

   for (int i = 0; i < SIZE-1; i++) 
      cout << customer[i];
 
   cout << " is a valid customer number.\n";
   /* END EDIT */

   return 0;
}

//**********************************************************
// Definition of function testNum.                         *
// This function determines whether the custNum parameter  *
// holds a valid customer number. The size parameter is    *
// the size of the custNum array.                          *
//**********************************************************

bool testNum(char custNum[], int size)
{
   int count;  // Loop counter

   // Test the first three characters for alphabetic letters.
   for (count = 0; count < 3; count++)
   {
      if (!isalpha(custNum[count]))
         return false;

      if (!isupper(custNum[count]))
         custNum[count] = toupper(custNum[count]);
   }
   
   // Test the remaining characters for numeric digits.
   for (count = 3; count < size - 1; count++)
   {
      if (!isdigit(custNum[count]))
         return false;
   }
   return true;
}

