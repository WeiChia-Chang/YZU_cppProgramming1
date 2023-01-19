#include <iostream>
using namespace std;

long long int recFinalPremium( int numFarmersRemaining );

int main()
{
   int n;
   cin >> n;
   for( int i = 0; i < n; i++ )
   {
      int f;
      cin >> f;
      cout << recFinalPremium( f ) << endl;
   }

   system( "pause" );
}

long long int recFinalPremium( int numFarmersRemaining )
{



   long long int size;
   int numAnimals;
   long long int friendliness;
   cin >> size >> numAnimals >> friendliness;


}