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
    int result{};
    long long int size;
    int numAnimals;
    long long int friendliness;
    cin >> size >> numAnimals >> friendliness;

    if (numFarmersRemaining == 1){
        return size * friendliness;
    }
    else {
        return size* friendliness + recFinalPremium(numFarmersRemaining - 1);
    }




}