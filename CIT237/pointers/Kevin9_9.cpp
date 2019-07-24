// This program uses a pointer to display the contents of an array.
#include <iostream>
using namespace std;

int main()
{
   const int SIZE = 8;
   int set[SIZE] = {5, 10, 15, 20, 25, 30, 35, 40};
   int *numPtr = nullptr;   // Pointer
   int count;				// Counter variable for loops

   // Make numPtr point to the set array.
   numPtr = set;

   // Use the pointer to display the array contents.
   cout << "The numbers in set are:\n";
   for (count = 0; count < SIZE; count++)
   {
      cout << *numPtr << " ";
      numPtr++;
   }

   // Display the array contents in reverse order.
   /* This works because `numPtr` is now pointing to the adress proceeding that
      final element in `set`. Thus, we decrement `numPtr` before dereferencing, 
      and when we do dereference, we get the final element in `set`, then the
      one preceeding that, etc. */
   cout << "\nThe numbers in set backward are:\n";
   for (count = 0; count < SIZE; count++)
   {
      numPtr--;
      cout << *numPtr << " ";
   }
   return 0;
   /* If we move this code to line 14, it will no longer work as intended.
      Since `numPtr` is pointing to the beginning of the array, decrementing
      would move the pointer into memory that has not been allocated, and cause
      runtime errors. */
}

