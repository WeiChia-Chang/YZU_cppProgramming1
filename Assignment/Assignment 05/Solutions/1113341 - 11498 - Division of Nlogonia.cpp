#include <iostream>
using namespace std;

void recDivisionNlogonia( int N, int M, int numQueriesRemaining );

int main()
{
	int K, N, M;
	cin >> K;
	while( K > 0 )
	{
		cin >> N >> M;
		recDivisionNlogonia( N, M, K );
		cin >> K;
	}

	system( "pause" );
}

void recDivisionNlogonia( int N, int M, int numQueriesRemaining )
{
	int x, y;
	cin >> x >> y;

	if (N < x && M < y) {
		cout << "NE\n";
	}
	else if (N > x && M < y) {
		cout << "NO\n";
	}
	else if (N > x && M > y) {
		cout << "SO\n";
	}
	else if (N < x && M > y) {
		cout << "SE\n";
	}
	else {
		cout << "divisa\n";
	}

	if (numQueriesRemaining == 1) {
		return;
	}
	else {
		recDivisionNlogonia(N, M, numQueriesRemaining - 1);
	}

}