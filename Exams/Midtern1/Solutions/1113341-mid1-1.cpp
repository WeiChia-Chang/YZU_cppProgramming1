// Computes the square root of a polynomial provided that
// all polynomials in this program have integer coefficients

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

// outputs the specified polynomial
void output( int coefficient[], int exponent[], int size );

// returns true if and only if the specified polynomial has at least a zero term
bool zeroTerms( int coefficient[], int size );

// returns true if and only if the specified polynomial is zero polynomial
bool isZero( int coefficient[], int size );

// returns true if and only if polynomial1 == polynomial2
bool equal( int coefficient1[], int exponent1[], int size1,
            int coefficient2[], int exponent2[], int size2 );

// polynomial1 = -polynomial2
void minus( int coefficient1[], int exponent1[], int &size1,
            int coefficient2[], int exponent2[], int size2 );

// addend += adder
void addAssign( int addendCoef[], int addendExpon[], int &addendSize,
               int adderCoef[], int adderExpon[], int adderSize );

// minuend -= subtrahend
void subtraAssign( int minuendCoef[], int minuendExpon[], int &minuendSize,
                  int subtrahendCoef[], int subtrahendExpon[], int subtrahendSize );

// product = multiplicand * multiplier
void multiplication( int multiplicandCoef[], int multiplicandExpon[], int multiplicandSize,
                     int multiplierCoef[], int multiplierExpon[], int multiplierSize,
                     int productCoef[], int productExpon[], int &productSize );

// computes the square root of a polynomial provided that
// all polynomials in this function have integer coefficients
void compSquareRoot( int coefficient[], int exponent[], int size,
   int squareRootCoef[], int squareRootExpon[], int &squareRootSize );

const int numTestCases = 200; // the number of test cases
const int arraySize = 20;

int main()
{
   ifstream inFile( "Polynomials.dat", ios::in | ios::binary );

   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   int numErrors = numTestCases;
   for( int i = 0; i < numTestCases; i++ )
   {
      int coefficient[ arraySize ] = {};
      int exponent[ arraySize ] = {};
      int size;

      // input dividend and divisor from the file Polynomials.dat
      inFile.read( reinterpret_cast< char * >( coefficient ), arraySize * sizeof( int ) );
      inFile.read( reinterpret_cast< char * >( exponent ), arraySize * sizeof( int ) );

      size = arraySize;
      while( size > 0 && coefficient[ size - 1 ] == 0 )
         size--;

      output( coefficient, exponent, size );

      int squareRootCoef[ arraySize ] = {};
      int squareRootExpon[ arraySize ] = {};
      int squareRootSize = 1;

      compSquareRoot( coefficient, exponent, size,
         squareRootCoef, squareRootExpon, squareRootSize );

      cout << "squareRoot:  ";
      output( squareRootCoef, squareRootExpon, squareRootSize );
      cout << endl;

      if( zeroTerms( squareRootCoef, squareRootSize ) )
         cout << "squareRoot has at least a zero term!\n";

      int bufferCoef[ arraySize ];
      int bufferExpon[ arraySize ];
      int bufferSize = 1;

      // buffer = squareRoot * squareRoot
      multiplication( squareRootCoef, squareRootExpon, squareRootSize,
                      squareRootCoef, squareRootExpon, squareRootSize,
                      bufferCoef, bufferExpon, bufferSize );

      if( zeroTerms( bufferCoef, bufferSize ) )
         cout << "buffer has at least a zero term!\n";

      // if buffer != polynomial, an error occurred!
      if (equal(bufferCoef, bufferExpon, bufferSize, coefficient, exponent, size)) {
                   numErrors--;
      }

   }

   inFile.close();

   cout << "There are " << numErrors << " errors!\n\n";

   system( "pause" );
}

// outputs the specified polynomial
void output( int coefficient[], int exponent[], int size )
{
   // the specified polynomial is zero polynomial
   if( isZero( coefficient, size ) )
      cout << 0;
   else
   {
      if( coefficient[ size - 1 ] < 0 )
         cout << "-" << -coefficient[ size - 1 ];
      else if( coefficient[ size - 1 ] > 0 )
         cout << coefficient[ size - 1 ];

      if( exponent[ size - 1 ] > 0 )
      {
         if( exponent[ size - 1 ] == 1 )
            cout << "x";
         else
            cout << "x^" << exponent[ size - 1 ];
      }

      for( int i = size - 2; i >= 0; i-- )
      {
         if( coefficient[ i ] < 0 )
            cout << " - " << -coefficient[ i ];
         else if( coefficient[ i ] > 0 )
            cout << " + " << coefficient[ i ];

         if( exponent[ i ] > 0 )
         {
            if( exponent[ i ] == 1 )
               cout << "x";
            else
               cout << "x^" << exponent[ i ];
         }
      }
   }

   cout << endl;
}

// returns true if and only if the specified polynomial has at least a zero term
bool zeroTerms( int coefficient[], int size )
{
   if( !isZero( coefficient, size ) )
      for( int i = 0; i < size; i++ )
         if( coefficient[ i ] == 0 )
            return true;

   return false;
}

// returns true if and only if the specified polynomial is zero polynomial
bool isZero( int coefficient[], int size )
{
   if( size == 1 && coefficient[ 0 ] == 0 )
      return true;
   return false;
}

// returns true if and only if polynomial1 == polynomial2
bool equal( int coefficient1[], int exponent1[], int size1,
            int coefficient2[], int exponent2[], int size2 )
{
   if( size1 != size2 )
      return false;

   for( int i = 0; i < size1; i++ )
      if( coefficient1[ i ] != coefficient2[ i ] || exponent1[ i ] != exponent2[ i ] )
         return false;

   return true;
}

// polynomial1 = -polynomial2
void minus( int coefficient1[], int exponent1[], int &size1,
            int coefficient2[], int exponent2[], int size2 )
{
   size1 = size2;
   for( int i = 0; i < size1; i++ )
   {
      coefficient1[ i ] = -coefficient2[ i ];
      exponent1[ i ] = exponent2[ i ];
   }
}

// addend += adder
void addAssign( int addendCoef[], int addendExpon[], int &addendSize,
               int adderCoef[], int adderExpon[], int adderSize )
{
   // if( adder == 0 )
   if( isZero( adderCoef, adderSize ) )
      return;

   // if( addend == 0 )
   if( isZero( addendCoef, addendSize ) )
   {
      // addend = adder
      addendSize = adderSize;
      for( int i = 0; i < addendSize; i++ )
      {
         addendCoef[ i ] = adderCoef[ i ];
         addendExpon[ i ] = adderExpon[ i ];
      }
      return;
   }

   // buffer = 0
   int bufferCoef[ arraySize ] = {};
   int bufferExpon[ arraySize ] = {};
   int bufferSize = 1;

   // buffer = -adder
   minus( bufferCoef, bufferExpon, bufferSize, adderCoef, adderExpon, adderSize );

   // if( addend == -adder )
   if( equal( addendCoef, addendExpon, addendSize, bufferCoef, bufferExpon, bufferSize ) )
   {
      addendSize = 1;     // addend = 0;
      addendCoef[ 0 ] = 0;
      addendExpon[ 0 ] = 0;
      return;
   }

   int sumCoef[ arraySize ] = {};
   int sumExpon[ arraySize ] = {};
   int i = 0;
   int j = 0;
   int k = 0;
   while( i < addendSize && j < adderSize )
   {
       if (addendExpon[i] > adderExpon[j]) {
           sumExpon[k] = adderExpon[j];
           sumCoef[k] = adderCoef[j];
           j++; k++;
       }
       else if (addendExpon[i] < adderExpon[j]) {
           sumExpon[k] = addendExpon[i];
           sumCoef[k] = addendCoef[i];
           i++; k++;
       }
       else if (addendExpon[i] = adderExpon[j]) {
           if (addendCoef[i] + adderCoef[j] == 0) {
               i++; j++;
               continue;
           }
           sumExpon[k] = addendExpon[i];
           sumCoef[k] = addendCoef[i] + adderCoef[j];
           i++; j++; k++;
       }

   }

   while( i < addendSize )
   {
       sumExpon[k] = addendExpon[i];
       sumCoef[k] = addendCoef[i];
       i++; k++;
   }

   while( j < adderSize )
   {
       sumExpon[k] = adderExpon[j];
       sumCoef[k] = adderCoef[j];
       j++; k++;
   }

   addendSize = k;
   for( int i = 0; i < addendSize; i++ ) // addend = sum
   {
      addendCoef[ i ] = sumCoef[ i ];
      addendExpon[ i ] = sumExpon[ i ];
   }

   if( zeroTerms( addendCoef, addendSize ) )
      cout << "addend has at least a zero term!\n";
}

// minuend -= subtrahend
void subtraAssign( int minuendCoef[], int minuendExpon[], int &minuendSize,
                  int subtrahendCoef[], int subtrahendExpon[], int subtrahendSize )
{
   // minuend == subtrahend
   if( equal( minuendCoef, minuendExpon, minuendSize, subtrahendCoef, subtrahendExpon, subtrahendSize ) )
   {
      minuendSize = 1;     // minuend = 0;
      minuendCoef[ 0 ] = 0;
      minuendExpon[ 0 ] = 0;
      return;
   }

   // buffer = 0
   int bufferCoef[ arraySize ] = {};
   int bufferExpon[ arraySize ] = {};
   int bufferSize = 1;

   // buffer = -subtrahend
   minus( bufferCoef, bufferExpon, bufferSize, subtrahendCoef, subtrahendExpon, subtrahendSize );

   // minuend = minuend + buffer = minuend - subtrahend
   addAssign( minuendCoef, minuendExpon, minuendSize, bufferCoef, bufferExpon, bufferSize );

   if( zeroTerms( minuendCoef, minuendSize ) )
      cout << "minuend has at least a zero term!\n";
}

// product = multiplicand * multiplier
void multiplication( int multiplicandCoef[], int multiplicandExpon[], int multiplicandSize,
                     int multiplierCoef[], int multiplierExpon[], int multiplierSize,
                     int productCoef[], int productExpon[], int &productSize )
{
   // product = 0;
   productSize = 1;
   productCoef[ 0 ] = 0;
   productExpon[ 0 ] = 0;
   int bufferCoef[ arraySize ] = {};
   int bufferExpon[ arraySize ] = {};
   int bufferSize = multiplicandSize;

   for (int i = 0; i < multiplierSize; i++) {
       for (int j = 0; j < multiplicandSize; j++) {
           bufferExpon[j] = multiplicandExpon[j] + multiplierExpon[i];
           bufferCoef[j] = multiplicandCoef[j] * multiplierCoef[i];
       }
       addAssign(productCoef, productExpon, productSize, bufferCoef, bufferExpon, bufferSize);
   }



   if( zeroTerms( productCoef, productSize ) )
      cout << "product has at least a zero term!\n";
}

void compSquareRoot( int coefficient[], int exponent[], int size,
               int squareRootCoef[], int squareRootExpon[], int &squareRootSize )
{
    int remainderCoef[arraySize]{};
    int remainderExpon[arraySize]{};
    int remainderSize = size;

    int monomialCoef[1]{};
    int monomialExpon[1]{};
    int monomialSize = 1;

    int divisorCoef[arraySize]{};
    int divisorExpon[arraySize]{};
    int divisorSize = 1;

    int bufferCoef[arraySize]{};
    int bufferExpon[arraySize]{};
    int bufferSize = 1;

    for (int i = 0; i < size; i++) {
        remainderExpon[i] = exponent[i];
        remainderCoef[i] = coefficient[i];
    }

    monomialExpon[0] = remainderExpon[remainderSize - 1] / 2;
    monomialCoef[0] = sqrt(remainderCoef[remainderSize - 1]);
    
    addAssign(squareRootCoef, squareRootExpon, squareRootSize,
                 monomialCoef, monomialExpon, monomialSize);
    addAssign(divisorCoef, divisorExpon, divisorSize,
                 monomialCoef, monomialExpon, monomialSize);
    multiplication(divisorCoef, divisorExpon, divisorSize, monomialCoef, monomialExpon, monomialSize,
        bufferCoef, bufferExpon, bufferSize);

    subtraAssign(remainderCoef, remainderExpon, remainderSize, bufferCoef, bufferExpon, bufferSize);

    while (remainderCoef[0] != 0) {
        divisorCoef[0] *= 2;
        monomialExpon[0] = remainderExpon[remainderSize - 1] - divisorExpon[divisorSize - 1];
        monomialCoef[0] = remainderCoef[remainderSize - 1] / divisorCoef[divisorSize - 1];

        addAssign(squareRootCoef, squareRootExpon, squareRootSize,
            monomialCoef, monomialExpon, monomialSize);
        addAssign(divisorCoef, divisorExpon, divisorSize,
            monomialCoef, monomialExpon, monomialSize);
        multiplication(divisorCoef, divisorExpon, divisorSize, monomialCoef, monomialExpon, monomialSize,
            bufferCoef, bufferExpon, bufferSize);
        subtraAssign(remainderCoef, remainderExpon, remainderSize, bufferCoef, bufferExpon, bufferSize);
    }
    
}