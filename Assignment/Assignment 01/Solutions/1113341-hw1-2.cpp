#include <iostream> // allows program to perform input and output
using namespace std; // program uses names from the std namespace

int main()
{
	int number1; // first integer read from user
	int number2; // second integer read from user
	int number3; // third integer read from user
	int change = 0;

	cout << "Enter three distict integers: ";
	cin >> number1 >> number2 >> number3;

	if (number1 > number2) {
		change = number2;
		number2 = number1;
		number1 = change;
		if (number2 > number3) {
			change = number3;
			number3 = number2;
			number2 = change;
			if (number1 > number2) {
				change = number2;
				number2 = number1;
				number1 = change;
			}
		}
	}else if (number2 > number3) {
		change = number3;
		number3 = number2;
		number2 = change;
		if (number1 > number2) {
			change = number2;
			number2 = number1;
			number1 = change;
		}
	}

	cout << "These numbers in ascending order: " << number1 << " " << number2 << " " << number3;
	return 0;
}