// This program reads a binary file,
// updates grades previously written to the file,
// adds new grades in the file,
// and deletes data previously stored in the file.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
using namespace std;

struct StudentData
{
   char studentId[ 8 ];
   char lastName[ 12 ];
   char firstName[ 12 ];
   int grade;
};

enum class Choices{ PRINT = 1, UPDATE, NEW, DELETE, END };

// enable user to input menu choice
Choices enterChoice();

// create text file for printing
void createTextFile( fstream &readFromFile );

// update grade in record
void updateRecord( fstream &updateFile );

// add a new grade in record
void newRecord( fstream &insertInFile );

// delete an existing record
void deleteRecord( fstream &deleteFromFile );

// obtain student ID from user
void getID( const char * const prompt, char studentId[] );

int main()
{
   // open file for reading and writing
   fstream inOutGrade( "grades.dat", ios::in | ios::out | ios::binary );

   // exit program if fstream cannot open file
   if( !inOutGrade )
   {
      cerr << "File could not be opened." << endl;
      system( "pause" );
      exit( 1 );
   }

   Choices choice; // store user choice

   // enable user to specify action
   while( ( choice = enterChoice() ) != Choices::END )
   {
      switch( choice )
      {
      case Choices::PRINT:
         createTextFile( inOutGrade ); // create text file from binary file
         break;
      case Choices::UPDATE:
         updateRecord( inOutGrade ); // update grade
         break;
      case Choices::NEW:
         newRecord( inOutGrade ); // add a new grade
         break;
      case Choices::DELETE:
         deleteRecord( inOutGrade ); // delete existing record
         break;
      default:
         cerr << "Incorrect choice" << endl;
         break;
      }






      cout << endl;
   }

   inOutGrade.close();

   system( "pause" );
}

// enable user to input menu choice
Choices enterChoice()
{
   // display available options
   cout << "Enter your choice" << endl
      << "1 - store a text file of all students' information" << endl
      << "    called \"grades.txt\" for printing" << endl
      << "2 - update a student's grade" << endl
      << "3 - add a student's grade" << endl
      << "4 - delete a student's information" << endl
      << "5 - end program\n? ";

   int menuChoice;
   cin >> menuChoice;
   return static_cast< Choices >( menuChoice );
}

// create text file for printing
void createTextFile( fstream &readFromFile )
{





}

// update grade in record
void updateRecord( fstream &updateFile )
{
   char studentId[ 8 ];
   getID( "\nEnter student ID to update", studentId );





}

// add a new grade in record
void newRecord( fstream &insertInFile )
{
   char studentId[ 8 ];
   getID( "\nEnter student ID to add", studentId );





}

// delete an existing record
void deleteRecord( fstream &deleteFromFile )
{
   char studentId[ 8 ];
   getID( "\nEnter student ID to delete", studentId );





}

// obtain student ID from user
void getID( const char * const prompt, char studentId[] )
{
   do
   {
      cout << prompt << " ( 1111401 - 1111450 ): ";
      cin >> studentId;
   } while( strcmp( studentId, "1111401" ) == -1 || strcmp( studentId, "1111450" ) == 1 );
}