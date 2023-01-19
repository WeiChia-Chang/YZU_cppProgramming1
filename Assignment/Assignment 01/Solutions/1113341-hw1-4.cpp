// Exercise 4.18 Solution: ex04_18.cpp
// Display decimal, binary, octal and hexadecimal numbers.
#include <iostream>
using namespace std; 

int main()
{
   int number; // a positive integer less than 32
   int bit[5];
   int i = 0;

   cout << "Enter a positive integer less than 32: ";
   cin >> number;

   while (i<=4) {
	   bit[i] = (number % 2) == 0 ? 0 : 1;
	   number /= 2;
	   i++;
   }

   for (int j = 4; j >= 0; j--) {
	   cout << bit[j];
   }

   return 0;

}