#include <iostream>
using namespace std;

void recCompNumJumps( int &highJumps, int &lowJumps, int preHeight, int numWallsRemaining );

int main()
{
   int T;
   cin >> T;
   for( int i = 1; i <= T; i++ )
   {
      int highJumps = 0;
      int lowJumps = 0;
      int preHeight;
      int numWalls;
      cin >> numWalls;
      cin >> preHeight;
      
      recCompNumJumps( highJumps, lowJumps, preHeight, numWalls - 1 );

      cout << "Case " << i << ": " << highJumps << ' ' << lowJumps << endl;
   }

   system( "pause" );
}

void recCompNumJumps( int &highJumps, int &lowJumps, int preHeight, int numWallsRemaining )
{



   int height;
   cin >> height;




}