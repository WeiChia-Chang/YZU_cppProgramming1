#include <iostream>
using namespace std;

int main() {
	double cases, number, size, animal, level, result = 0;
	cin >> cases;


	for (int j = 1; j <= cases; j++) {
		result = 0;
		cin >> number;
		for (int i = 1; i <= number; i++) {
			cin >> size >> animal >> level;
			result += (size / animal) * level * animal;
		}

		cout << result << endl;
		
	}
	
	
	







}