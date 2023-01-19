// Compute the square root of a huge integer.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;
using std::setfill;

#include <cstring>
#include <cmath>

struct HugeInt
{
   size_t size = 0;
   int *integer = nullptr;
};

// put the square root of hugeInt into the array squareRoot
void compSquareRoot( HugeInt &hugeInt, HugeInt &squareRoot );

// put the square of hugeInt into the array square
void compSquare( HugeInt &hugeInt, HugeInt &square );

// if hugeInt1 == hugeInt2, return true; otherwise, return false
bool equal( HugeInt &hugeInt1, HugeInt &hugeInt2 );

// if hugeInt1 < hugeInt2, return true; otherwise, return false
bool less( HugeInt &hugeInt1, HugeInt &hugeInt2 );

int main()
{
   int testCase;
   cin >> testCase;
   for( int i = 1; i <= testCase; i++ )
   {
      char str[ 1010 ] = {};
      cin >> str;

      size_t numDigits = strlen( str );
      if( numDigits < 10 )
         cout << sqrt( atoi( str ) ) << endl;
      else
      {
         int *digits = new int[ numDigits + 2 ]();
         for( size_t j = 0; j < numDigits; ++j )
            digits[ j ] = str[ numDigits - 1 - j ] - '0';

         size_t last = ( numDigits - 1 ) / 3;
         HugeInt hugeInt;
         hugeInt.size = last + 1;
         hugeInt.integer = new int[ hugeInt.size ]();
         for( size_t j = 0; j <= last; j++ )
            hugeInt.integer[ j ] = digits[ 3 * j ] + digits[ 3 * j + 1 ] * 10 + digits[ 3 * j + 2 ] * 100;

         HugeInt squareRoot; // the square root of hugeInt
         squareRoot.size = ( hugeInt.size + 1 ) / 2; // the number of digits of squareRoot
         squareRoot.integer = new int[ squareRoot.size ](); // the square root of hugeInt

         // put the square root of hugeInt into the array squareRoot
         compSquareRoot( hugeInt, squareRoot );

         cout << squareRoot.integer[ squareRoot.size - 1 ];
         for( int j = squareRoot.size - 2; j >= 0; j-- )
            cout << setw( 3 ) << setfill( '0' ) << squareRoot.integer[ j ];
         cout << endl;

         delete[] squareRoot.integer;
         delete[] hugeInt.integer;
         delete[] digits;
      }

      if( i < testCase )
         cout << endl;
   }

//   system( "pause" );
}

// put the square root of hugeInt into the array squareRoot
void compSquareRoot( HugeInt &hugeInt, HugeInt &squareRoot )
{



}

// put the square of hugeInt into the array square
void compSquare( HugeInt &hugeInt, HugeInt &square )
{



}

// if hugeInt1 == hugeInt2, return true; otherwise, return false
bool equal( HugeInt &hugeInt1, HugeInt &hugeInt2 )
{
   if( hugeInt1.size != hugeInt2.size )
      return false;

   for( int i = hugeInt1.size - 1; i >= 0; i-- )
      if( hugeInt1.integer[ i ] != hugeInt2.integer[ i ] )
         return false;

   return true;
}

// if hugeInt1 < hugeInt2, retuen true; otherwise, return false
bool less( HugeInt &hugeInt1, HugeInt &hugeInt2 )
{



}