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

	if (numQueriesRemaining == 0) {
		return;
	}
	else {

		int x, y;
		cin >> x >> y;

		if (x > N && y > M) {
			cout << "NE\n";
		}
		else if (x < N && y > M) {
			cout << "NO\n";
		}
		else if (x < N && y < M) {
			cout << "SO\n";
		}
		else if (x > N && y < M) {
			cout << "SE\n";
		}
		else {
			cout << "Divisa\n";
		}

		recDivisionNlogonia(N, M, numQueriesRemaining - 1);
	}


}