#include <iostream>
#include <algorithm>
using namespace std;

int recMaxSpeed( int numRemaining );

int main()
{
	int T;
	cin >> T;
	for( int i = 1; i <= T; i++ )
	{
		int N;
		cin >> N;
		cout << "Case " << i << ": " << recMaxSpeed( N ) << endl;
	}

	system( "pause" );
}

int recMaxSpeed( int numRemaining )
{



	int speed;
	cin >> speed;


}