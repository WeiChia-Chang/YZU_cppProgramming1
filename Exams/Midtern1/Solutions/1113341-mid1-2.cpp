#include <iostream>
using namespace std;

// returns the summation of all the odd integers in the range [a, b]
int oddSum( int a, int b )
{
	if (a == b) {
		return a;
	}
	else {
		return oddSum(a + 2, b) + a;
	}




}

int main()
{
   int a, b;
   int numCases;
   cin >> numCases;

   for (int i = 1; i <= numCases; i++) {
	   cin >> a >> b;
	   if (a % 2 == 0 && b % 2 == 0 && a == b) {
		   cout << "Case " << i << ": " << 0 << endl;
		   continue;
	   }
	   if (a % 2 == 0) {
		   a++;
	   }
	   if (b % 2 == 0) {
		   b--;
	   }
	   cout << "Case " << i << ": " << oddSum(a, b) << endl;
   }



}