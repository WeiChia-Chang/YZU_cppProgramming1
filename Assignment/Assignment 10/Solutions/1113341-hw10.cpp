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

        inOutGrade.clear();
        inOutGrade.seekg(0, ios::beg);
       



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
    readFromFile.seekg(0, ios::end);
    int sNumbers = static_cast<int>(readFromFile.tellg()) / sizeof(StudentData);
    readFromFile.seekg(0, ios::beg);

    StudentData buf[50];

    for (int i = 0; i < sNumbers; i++)
        readFromFile.read(reinterpret_cast<char*> (&buf[i]), sizeof(StudentData));

    ofstream outFile("grades.txt", ios::out);
    
    if (!outFile) {
        cerr << "File couldn't be opened!!!\n";
        exit(1);
    }

    cout << endl;
    cout << left << setw(10) << "ID" << setw(12) << "Last Name" << setw(13) << "First Name" << setw(5) << "Grade" << endl;
    
    outFile << left << setw(10) << "ID" << setw(12) << "Last Name" << setw(13) << "First Name" << setw(5) << "Grade" << endl;


    
    for (int i = 0; i < sNumbers; i++) {
        if (buf[i].studentId[0] == ' ') continue;
        cout << left << setw(10) << buf[i].studentId << setw(12) << buf[i].lastName
            << setw(13) << buf[i].firstName << right << setw(5) << buf[i].grade << endl;

        outFile << left << setw(10) << buf[i].studentId << setw(12) << buf[i].lastName
               << setw(13) << buf[i].firstName << right << setw(5) << buf[i].grade << endl;

    }

    outFile.close();

}

// update grade in record
void updateRecord( fstream &updateFile )
{
    char studentId[ 8 ];
    getID( "\nEnter student ID to update", studentId );

    int id = 10 * (studentId[5] - '0') + (studentId[6] - '0');
    updateFile.seekg((id - 1) * sizeof(StudentData));

    StudentData updateBuf;

    updateFile.read(reinterpret_cast<char*>(&updateBuf), sizeof(StudentData));
    
    if (updateBuf.studentId[0] == ' ')
        cout << "\nStudent ID " << studentId << " is empty.\n";
    else if (updateBuf.grade == -1)
        cout << "\nStudent ID " << studentId << " has no grade.\n";
    else {
        cout << endl;
        cout << left << setw(10) << updateBuf.studentId << setw(12) << updateBuf.lastName
            << setw(13) << updateBuf.firstName << right << setw(5) << updateBuf.grade << endl;
        cout << "\nEnter grade: ";
        cin >> updateBuf.grade;

        cout << endl;
        cout << left << setw(10) << updateBuf.studentId << setw(12) << updateBuf.lastName
            << setw(13) << updateBuf.firstName << right << setw(5) << updateBuf.grade << endl;

        updateFile.seekp((id - 1) * sizeof(StudentData));
        updateFile.write(reinterpret_cast<const char*>(&updateBuf), sizeof(StudentData));
    }

}

// add a new grade in record
void newRecord( fstream &insertInFile )
{
    char studentId[ 8 ];
    getID( "\nEnter student ID to add", studentId );

    int id = 10 * (studentId[5] - '0') + (studentId[6] - '0');
    insertInFile.seekg((id - 1) * sizeof(StudentData));

    StudentData addBuf;

    insertInFile.read(reinterpret_cast<char*>(&addBuf), sizeof(StudentData));

    if (addBuf.studentId[0] == ' ')
        cout << "\nStudent ID " << studentId << " is empty.\n";
    else {
        cout << "\nEnter Grade: ";
        cin >> addBuf.grade;

        cout << endl;
        cout << left << setw(10) << addBuf.studentId << setw(12) << addBuf.lastName
            << setw(13) << addBuf.firstName << right << setw(5) << addBuf.grade << endl;

        insertInFile.seekp((id - 1) * sizeof(StudentData));
        insertInFile.write(reinterpret_cast<const char*>(&addBuf), sizeof(StudentData));
    }

}

// delete an existing record
void deleteRecord( fstream &deleteFromFile )
{
    char studentId[ 8 ];
    getID( "\nEnter student ID to delete", studentId );

    int id = 10 * (studentId[5] - '0') + (studentId[6] - '0');
    deleteFromFile.seekg((id - 1) * sizeof(StudentData));

    StudentData deleteBuf;

    deleteFromFile.read(reinterpret_cast<char*>(&deleteBuf), sizeof(StudentData));

    if (deleteBuf.studentId[0] == ' ')
        cout << "\nStudent ID " << studentId << " is empty.\n";
    else {
        deleteBuf.studentId[0] = ' ';
        cout << "\nStudent ID " << studentId << " deleted\n";

        deleteFromFile.seekp((id - 1) * sizeof(StudentData));
        deleteFromFile.write(reinterpret_cast<const char*>(&deleteBuf), sizeof(StudentData));
    }

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
