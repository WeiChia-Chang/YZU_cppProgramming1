#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;
using std::setfill;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include <vector>
using std::vector;

struct Date
{
   int year;
   int month;
   int day;
   int hour;
};

struct MemberRecord
{
   char idNumber[ 12 ];   // account number
   char password[ 24 ];   // password
   char name[ 8 ];        // name
};

struct ReservationRecord
{
   char idNumber[ 12 ]; // account number
   int branchCode;      // branch code
   Date date;           // reservation date
   int numCustomers;    // number of customers
};

char branchNames[ 19 ][ 24 ] = { "", "Taipei Dunhua South",   "Taipei Zhongxiao",
                                     "Taipei Songjiang",    "Taipei Nanjing",
                                     "Taipei Linsen",       "Taipei Zhonghua New",
                                     "Banqiao Guanqian",    "Yonghe Lehua",
                                     "Taoyuan Zhonghua",    "Taoyuan Nankan",
                                     "Zhongli Zhongyang",   "Hsinchu Beida",
                                     "Taichung Ziyou",      "Chiayi Ren'ai",
                                     "Tainan Ximen",        "Kaohsiung Zhonghua New",
                                     "Kaohsiung Jianxing",  "Pingtung Kending" };

// read all memberDetails from the file Members.dat
void loadMemberDetails( vector< MemberRecord > &memberDetails );

// read all reservations that are not out of date, from the file Reservations.dat
void loadReservations( vector< ReservationRecord > &reservations );

// compute the current date
Date compCurrentDate();

// return true if and only if date1 <= date2
bool lessEqual( const Date &date1, const Date &date2 );

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

// login and display the submenu
void login( const vector< MemberRecord > &memberDetails,
            vector< ReservationRecord > &reservations );

// there exists a member with specified idNumber and password
bool valid( char idNumber[], char password[],
            const vector< MemberRecord > &memberDetails );

// add a new reservation for the member with specified IDnumber
void reservation( char idNumber[], vector< ReservationRecord > &reservations );

// compute 7 dates which is starting from the current date
void compAvailableDates( Date availableDates[] );

// display all fields of reservation
void output( ReservationRecord reservation );

// display all reservations for the member with specified IDnumber,
// then let the member to choose one of them to delete
void queryDelete( char idNumber[], vector< ReservationRecord > &reservations );

// add a new member
void registration( vector< MemberRecord > &memberDetails );

// return true if idNumber is a legal ID number
//bool legalID( char idNumber[] );

// return true if idNumber belongs to memberDetails
bool existingID( char idNumber[], const vector< MemberRecord > &memberDetails );

// write all memberDetails into the file Members.dat
void saveMemberDetails( const vector< MemberRecord > &memberDetails );

// write all reservations that are not out of date, into the file Reservations.dat
void saveReservations( const vector< ReservationRecord > &reservations );

int main()
{
   vector< MemberRecord > memberDetails; // member details for all members
   vector< ReservationRecord > reservations; // all reservations

   loadMemberDetails( memberDetails );
   loadReservations( reservations );

   cout << "Welcome to the Cashbox Party World!\n\n";

   int choice;
   while( true )
   {
      cout << "1 - Login\n";
      cout << "2 - Registration\n";
      cout << "3 - End\n";

      do cout << "\nEnter your choice (1~3): ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch ( choice )
      {
      case 1:
         login( memberDetails, reservations );
         break;

      case 2:
         registration( memberDetails );
         break;

      case 3:
         saveMemberDetails( memberDetails );
         saveReservations( reservations );
         cout << "Thank you! Goodbye!\n\n";
         system( "pause" );
         return 0;

      default:
         cout << "\nIncorrect choice!\n";
         break;
      }
   }

   system( "pause" );
}

void loadMemberDetails( vector< MemberRecord > &memberDetails )
{




}

void loadReservations( vector< ReservationRecord > &reservations )
{




}

Date compCurrentDate()
{
   Date currentDate;
   tm structuredTime;
   time_t rawTime = time( 0 );
   localtime_s( &structuredTime, &rawTime );

   currentDate.year = structuredTime.tm_year + 1900;
   currentDate.month = structuredTime.tm_mon + 1;
   currentDate.day = structuredTime.tm_mday;
   currentDate.hour = structuredTime.tm_hour;

   return currentDate;
}

bool lessEqual( const Date &date1, const Date &date2 )
{




}

int inputAnInteger( int begin, int end )
{
   char string[ 80 ];
   cin.getline( string, 80, '\n' );

   if( strlen( string ) == 0 )
      exit( 0 );

   for( unsigned int i = 0; i < strlen( string ); i++ )
      if( string[ i ] < '0' || string[ i ] > '9' )
         return -1;

   int number = atoi( string );
   if( number >= begin && number <= end )
      return number;
   else
      return -1;
}

void login( const vector< MemberRecord > &memberDetails,
            vector< ReservationRecord > &reservations )
{
   char idNumber[ 12 ] = "";
   char password[ 24 ] = "";

   do {
      cout << "Please enter your ID number: ";
      cin >> idNumber;
      cout << "Enter your password: ";
      cin >> password;
   } while( !valid( idNumber, password, memberDetails ) );

   cin.ignore();

   int choice;

   while( true )
   {      
      cout << "\n1 - Make Reservation\n";
      cout << "2 - Reservation Enquiry/Canceling\n";
      cout << "3 - End\n";

      do cout << "\nEnter your choice (1~3): ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch ( choice )
      {
      case 1:
         reservation( idNumber, reservations );
         break;

      case 2:
         queryDelete( idNumber, reservations );
         break;

      case 3:
         return;

      default:
         cout << "\nIncorrect choice!\n";
         break;
      }
   }
}

bool valid( char idNumber[], char password[], const vector< MemberRecord > &memberDetails )
{




}

void reservation( char idNumber[], vector< ReservationRecord > &reservations )
{
   ReservationRecord newReservation;




   cout << endl << setw( 26 ) << "Branch"
                << setw( 14 ) << "Date" << setw( 8 ) << "Hour"
                << setw( 19 ) << "No of Customers" << endl;

   output( newReservation );

   cout << "\nReservation Completed!\n";

   reservations.push_back( newReservation );
}

void compAvailableDates( Date availableDates[] )
{
   Date currentDate = compCurrentDate();




}

void output( ReservationRecord reservation )
{
   cout << setw( 26 ) << branchNames[ reservation.branchCode ]
        << setw( 8 ) << reservation.date.year << '-'
        << setw( 2 ) << setfill( '0' ) << reservation.date.month << '-'
        << setw( 2 ) << setfill( '0' ) << reservation.date.day
        << setw( 8 ) << setfill( ' ' ) << reservation.date.hour
        << setw( 19 ) << reservation.numCustomers << endl;
}

void queryDelete( char idNumber[], vector< ReservationRecord > &reservations )
{
   Date currentDate = compCurrentDate();



}

void registration( vector< MemberRecord > &memberDetails )
{
   MemberRecord newMember;

   cout << "Input your ID Number: ";
   cin >> newMember.idNumber;
   cin.ignore();

   if( existingID( newMember.idNumber, memberDetails ) )
   {
      cout << "\nYou are already a member!\n\n";
      return;
   }

   cout << "Input your Name: ";
   cin >> newMember.name;

   cout << "Choose a password: ";
   cin >> newMember.password;

   cin.ignore();

   memberDetails.push_back( newMember );

   cout << "\nRegistration Completed!\n\n";
}

bool existingID( char idNumber[], const vector< MemberRecord > &memberDetails )
{




}

void saveMemberDetails( const vector< MemberRecord > &memberDetails )
{




}

void saveReservations( const vector< ReservationRecord > &reservations )
{




}