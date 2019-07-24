/*
  Kevin Fernandes
  September, 2017
<<<<<<< HEAD

=======
>>>>>>> 2e78f51d0cdc209387a3e155c402425e89871c45
  Create an array of 63 random integers, and print them out in the following 
  ways: 1. Print all values, with 3 values per line
  2. Print all values that are divisible by 7
  3. Print every sixth value
*/

#include <iostream>

double* createArray(int);
void printArray(double*, int);
void initArray(double*, int, double);

int main() {
	int size;
	double* arr;
	std::cout << "Please enter the size of the array: ";
	std::cin >> size;

	arr = createArray(size);
	initArray(arr, size, 0);
	printArray(arr, size);


	delete[] arr;
	arr = nullptr;

	system("pause");
    return 0;
}

double* createArray(int size) {
	double* arr = new double[size];
	return arr;
}

void printArray(double* arr, int size) {
	std::cout << '[';
	for (int i = 0; i < size; i++) {
		std::cout << arr[i];
		i == size - 1 ? std::cout << "]\n" : std::cout << ',';
    }
}

void initArray(double* arr, int size, double value) {
	for (int i = 0; i < size; i++) {
		arr[i] = value;
	}
}
<<<<<<< HEAD
=======

>>>>>>> 2e78f51d0cdc209387a3e155c402425e89871c45
