#include <iostream>
using namespace std;

int main()
{
   int number;
   int reverse = 0;

   cout << "Enter a 5 - digit positive integer : ";
   cin >> number;
   while(number != 0) {
	   reverse *= 10;
	   reverse += (number % 10); 
	   number /= 10;
   }

   cout << "The digits in the reverse order : " <<reverse ;

   return 0;
}