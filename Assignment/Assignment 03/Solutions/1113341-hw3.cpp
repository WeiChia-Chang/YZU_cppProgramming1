```cpp
// Polynomial division provided that the quotient and remainder have integer coefficients

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

// outputs the specified polynomial
void output(int polynomial[], int degree);

// returns true if and only if the specified polynomial is zero polynomial
bool isZero(int polynomial[], int degree);

// returns true if and only if polynomial1 == polynomial2
bool equal(int polynomial1[], int polynomial2[], int degree1, int degree2);

// polynomial1 = -polynomial2
void minus(int polynomial1[], int polynomial2[], int& degree1, int degree2);

// addend += adder
void addition(int addend[], int adder[], int& addendDegree, int adderDegree);

// minuend -= subtrahend
void subtraction(int minuend[], int subtrahend[], int& minuendDegree, int subtrahendDegree);

// product = multiplicand * multiplier
void multiplication(int multiplicand[], int multiplier[], int product[],
    int multiplicandDegree, int multiplierDegree, int& productDegree);

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendDegree >= divisorDegree
void division(int dividend[], int divisor[], int quotient[], int remainder[],
    int dividendDegree, int divisorDegree, int& quotientDegree, int& remainderDegree);

const int numTestCases = 200; // the number of test cases
const int arraySize = 20;

int main()
{
    ifstream inFile("Polynomials.dat", ios::in | ios::binary);

    // exit program if ifstream could not open file
    if (!inFile)
    {
        cout << "File could not be opened\n";
        system("pause");
        exit(1);
    }

    int numErrors = numTestCases;
    for (int i = 0; i < numTestCases; i++)
    {
        int dividend[arraySize] = {};
        int divisor[arraySize] = {};

        // input dividend and divisor from the file Polynomials.dat
        inFile.read(reinterpret_cast<char*>(dividend), 80);
        inFile.read(reinterpret_cast<char*>(divisor), 80);

        int dividendDegree = arraySize - 1;
        while (dividendDegree > 0 && dividend[dividendDegree] == 0)
            dividendDegree--;

        int divisorDegree = arraySize - 1;
        while (divisorDegree > 0 && divisor[divisorDegree] == 0)
            divisorDegree--;

        cout << "dividend: ";
        output(dividend, dividendDegree);
        cout << "divisor : ";
        output(divisor, divisorDegree);
        cout << endl;

        int quotient[arraySize] = {};
        int remainder[arraySize] = {};
        int quotientDegree = 0;
        int remainderDegree = 0;

        // quotient = dividend / divisor; remainder = dividend % divisor
        // thus, dividend == divisor * quotient + remainder
        division(dividend, divisor, quotient, remainder,
            dividendDegree, divisorDegree, quotientDegree, remainderDegree);

        if (quotientDegree != 0 && quotient[quotientDegree] == 0)
            cout << "Leading coefficient of quotient cannot be zero!\n";

        if (remainderDegree != 0 && remainder[remainderDegree] == 0)
            cout << "Leading coefficient of remainder cannot be zero!\n";

        int buffer[arraySize] = {};
        int bufferDegree = 1;

        // buffer = divisor * quotient
        multiplication(divisor, quotient, buffer, divisorDegree, quotientDegree, bufferDegree);
        /*cout << "BD(mul): " << bufferDegree << endl;*/

        if (bufferDegree != 0 && buffer[bufferDegree] == 0)
            cout << "Leading coefficient of buffer cannot be zero!\n";

        // buffer = buffer + remainder = divisor * quotient + remainder
        addition(buffer, remainder, bufferDegree, remainderDegree);

        if (bufferDegree != 0 && buffer[bufferDegree] == 0)
            cout << "Leading coefficient of buffer cannot be zero!\n";

        //cout << "BD: " << bufferDegree << "DD: " << dividendDegree << endl;


        // if buffer != dividend, an error occurred!
        if (equal(buffer, dividend, bufferDegree, dividendDegree)) {
            numErrors--;
            cout << "correct\n";
        }


    }

    inFile.close();

    cout << "There are " << numErrors << " errors!\n\n";

    system("pause");
}

// outputs the specified polynomial
void output(int polynomial[], int degree)
{
    if (isZero(polynomial, degree)) // zero polynomial
        cout << 0;
    else
    {
        if (degree == 0) // constant polynomial
        {
            if (polynomial[0] < 0)
                cout << "-" << -polynomial[0];
            else if (polynomial[0] > 0)
                cout << polynomial[0];
        }
        else
        {
            if (degree == 1) // polynomial of degree 1
            {
                if (polynomial[1] < 0)
                    cout << "-" << -polynomial[1] << "x";
                else if (polynomial[1] > 0)
                    cout << polynomial[1] << "x";
            }
            else // polynomial of degree at least 2
            {
                // display the leading term
                if (polynomial[degree] < 0)
                    cout << "-" << -polynomial[degree] << "x^" << degree;
                else if (polynomial[degree] > 0)
                    cout << polynomial[degree] << "x^" << degree;

                // display all other terms
                for (int i = degree - 1; i > 1; i--)
                    if (polynomial[i] < 0)
                        cout << " - " << -polynomial[i] << "x^" << i;
                    else if (polynomial[i] > 0)
                        cout << " + " << polynomial[i] << "x^" << i;

                // display the term of degree 1
                if (polynomial[1] < 0)
                    cout << " - " << -polynomial[1] << "x";
                else if (polynomial[1] > 0)
                    cout << " + " << polynomial[1] << "x";
            }

            // display the constant term
            if (polynomial[0] < 0)
                cout << " - " << -polynomial[0];
            else if (polynomial[0] > 0)
                cout << " + " << polynomial[0];
        }
    }

    cout << endl;
}

// returns true if and only if the specified polynomial is zero polynomial
bool isZero(int polynomial[], int degree)
{  // leading term is 0
    if (degree == 0 && polynomial[0] == 0)
        return true;
    return false;
}

// returns true if and only if polynomial1 == polynomial2
bool equal(int polynomial1[], int polynomial2[], int degree1, int degree2)
{
    if (degree1 != degree2)
        return false;

   for (int i = 0; i <= degree1; i++)
        if (polynomial1[i] != polynomial2[i])
            return false;

    return true;
}

// polynomial1 = -polynomial2
void minus(int polynomial1[], int polynomial2[], int& degree1, int degree2)
{
    degree1 = degree2;
    for (int i = 0; i <= degree1; i++)
        polynomial1[i] = -polynomial2[i];
}

// addend += adder
void addition( int addend[], int adder[], int &addendDegree, int adderDegree )
{
    if (addendDegree < adderDegree) {
        addendDegree = adderDegree;
    }

    for (int i = 0; i <= addendDegree; i++) {
        addend[i] += adder[i];
    }

    while (addendDegree != 0 && addend[addendDegree] == 0) {
        addendDegree--;
    }

   if( addendDegree != 0 && addend[ addendDegree ] == 0 )
      cout << "Leading coefficient of addend cannot be zero!\n";
}

// minuend -= subtrahend
void subtraction(int minuend[], int subtrahend[], int& minuendDegree, int subtrahendDegree)
{
    int buffer[arraySize] = {};
    int bufferDegree = 0;

    // buffer = -subtrahend
    minus(buffer, subtrahend, bufferDegree, subtrahendDegree);

    // minuend = minuend + buffer = minuend - subtrahend
    addition(minuend, buffer, minuendDegree, bufferDegree);

    if (minuendDegree != 0 && minuend[minuendDegree] == 0)
        cout << "Leading coefficient of minuend cannot be zero!\n";
}

// product = multiplicand * multiplier
void multiplication(int multiplicand[], int multiplier[], int product[],
    int multiplicandDegree, int multiplierDegree, int& productDegree)
{
    int i, j;

    productDegree = multiplicandDegree + multiplierDegree;

    for (j = 0; j <= multiplicandDegree; j++) {
        for (i = 0; i <= multiplierDegree; i++) {
            product[i + j] += multiplicand[j] * multiplier[i];
        }
    }

    while (productDegree != 0 && product[productDegree] == 0) {
        productDegree--;
    }

    if (productDegree != 0 && product[productDegree] == 0)
        cout << "Leading coefficient of product cannot be zero!\n";
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendDegree >= divisorDegree
void division(int dividend[], int divisor[], int quotient[], int remainder[],
    int dividendDegree, int divisorDegree, int& quotientDegree, int& remainderDegree)
{
    if (isZero(dividend, dividendDegree))
    {
        quotientDegree = 0;
        quotient[0] = 0;

        remainderDegree = 0;
        remainder[0] = 0;
        return;
    }

    int Buffer[arraySize] = {};
    int BufferDegree = 0;

    for (int k = dividendDegree; k >= 0; k--) {
        remainder[k] = dividend[k];
    }
    remainderDegree = dividendDegree;
    quotientDegree = dividendDegree - divisorDegree;

    for (int j = quotientDegree; j >= 0; j--) {
        quotient[j] = remainder[remainderDegree] / divisor[divisorDegree];
        for (int i = divisorDegree; i >= 0; i--) {
            Buffer[j + i] = divisor[i] * quotient[j];
        }

        for (int k = remainderDegree; k >= 0; k--) {
            remainder[k] -= Buffer[k];
        }

        while (remainderDegree != 0 && remainder[remainderDegree] == 0) {
            remainderDegree--;
        }

        if (remainderDegree < divisorDegree || remainderDegree == 0) {
            break;
        }

        j = remainderDegree - divisorDegree + 1;
    }

    if (quotientDegree != 0 && quotient[quotientDegree] == 0)
        cout << "Leading coefficient of quotient cannot be zero!\n";

    if (remainderDegree != 0 && remainder[remainderDegree] == 0)
        cout << "Leading coefficient of remainder cannot be zero!\n";
}
```
