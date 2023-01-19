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
using std::fstream;

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
    ifstream member("Members.dat", ios::in | ios::binary);
    if (!member) {
        cout << "Members.dat cannot be opened in loadMemberDetails!\n";
        exit(1);
    }

    member.seekg(0, ios::end);
    int memberNum = member.tellg() / sizeof(MemberRecord);
    member.seekg(0, ios::beg);
    MemberRecord buf{};
    for (int i = 1; i <= memberNum; i++) {
        member.read(reinterpret_cast<char*>(&buf), sizeof(MemberRecord));
        memberDetails.push_back(buf);
    }

    member.clear(); member.close();
}

void loadReservations( vector< ReservationRecord > &reservations )
{
    ifstream res("Reservations.dat", ios::in | ios::binary);
    if (!res) {
        cout << "Reservations.dat cannot be opened in loadReservations!\n";
        exit(1);
    }

    res.seekg(0, ios::end);
    int resNum = res.tellg() / sizeof(ReservationRecord);
    res.seekg(0, ios::beg);
    ReservationRecord buf{};
    Date current = compCurrentDate();
    for (int i = 1; i <= resNum; i++) {
        res.read(reinterpret_cast<char*>(&buf), sizeof(ReservationRecord));
        if (lessEqual(current, buf.date)) {
            reservations.push_back(buf);
        }
    }
    //cout << "\nresNum: " << reservations.size();
    res.clear(); res.close();
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
    if (date1.year < date2.year) return true;
    else if (date1.year > date2.year) return false;
    
    if (date1.month < date2.month) return true;
    else if (date1.month > date2.month) return false;

    if (date1.day < date2.day) return true;
    else if (date1.day > date2.day) return false;

    if (date1.hour <= date2.hour) return true;
    else return false;

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
    int numMembers = memberDetails.size();
    bool have = false;
    for (int i = 0; i <= numMembers - 1; i++) {
        if (strcmp(idNumber, memberDetails[i].idNumber) == 0 &&
            strcmp(password, memberDetails[i].password) == 0) {
            have = true;
        }
    }

    if (!have)
        cout << "\nInvalid account number or password.Please try again.\n\n";
    
    return have;
}

void reservation( char idNumber[], vector< ReservationRecord > &reservations )
{
    ReservationRecord newReservation;
    Date now = compCurrentDate();
    Date available[7];
    int chBranch, begBranch{ 1 }, endBranch{18}; /*input and choice from 1 to 18*/
    for (int i = 1; i <= 18; i++) {
        cout << std::right << setw(2) << i << ". " << branchNames[i] << endl;
    }
    strcpy_s(newReservation.idNumber, 12, idNumber);
    do {
        cout << "\nEnter Your Choice (0 to end): ";
        cin >> newReservation.branchCode;
        if (newReservation.branchCode == 0) {
            cin.ignore();
            return;
        }
    } while (newReservation.branchCode < 0 || newReservation.branchCode > 18);

    cout << "\nThe current hour is " << now.year << "/"
        << now.month << "/" << now.day << ":" << now.hour << endl;

    cout << "\nAvailable days:\n";

    compAvailableDates(available);
    int chDay;
    do {
        cout << "\nEnter your choice (0 to end): ";
        cin >> chDay;
        if (chDay == 0) {
            cin.ignore();
            return;
        }
    } while (chDay < 0 || chDay > 7);
    
    newReservation.date.day = (now.hour == 23 ? (now.day + chDay) : (now.day + chDay - 1));
    newReservation.date.month = now.month;
    newReservation.date.year = now.year;

    if (newReservation.date.day > 31) {
        newReservation.date.day -= 31;
        newReservation.date.month++;
    }
    if (newReservation.date.month > 12) {
        newReservation.date.month -= 12;
        newReservation.date.year++;
    }
    
    cin.ignore();

    int beg, end{ 23 };
    do {
        if (now.hour == 23 || chDay != 1) {
            cout << "\nEnter time (0 ~ 23): ";
            beg = 0;
        }
        else {
            cout << "\nEnter time (" << now.hour + 1 << " ~ 23): ";
            beg = now.hour + 1;
        }
    } while ((newReservation.date.hour = inputAnInteger(beg, end)) == -1);
    cout << newReservation.date.year << " " << newReservation.date.month << " " << newReservation.date.day << " " << newReservation.date.hour << endl;
    
    do {
        cout << "\nEnter the number of customers (1~30, 0 to end): ";
        cin >> newReservation.numCustomers;
        if (newReservation.numCustomers == 0) {
            cin.ignore();
            return;
        }
    } while (newReservation.numCustomers < 0 || newReservation.numCustomers > 30);
    cin.ignore();

    cout << endl << setw( 26 ) << "Branch"
                << setw( 14 ) << "Date" << setw( 8 ) << "Hour"
                << setw( 19 ) << "No of Customers" << endl;

    output( newReservation );
    reservations.push_back( newReservation );
    cout << reservations[reservations.size() - 1].date.year << " " << reservations[reservations.size() - 1].date.month 
        << " " << reservations[reservations.size() - 1].date.day << " " << reservations[reservations.size() - 1].date.hour << endl;
    
    cout << "\nReservation Completed!\n";

}

void compAvailableDates( Date availableDates[] )
{
    Date currentDate = compCurrentDate();
    Date buf = compCurrentDate(); /*to change days*/

    for (int i = 1; i <= 7; i++, buf.day++) {
        if (buf.hour == 23 && currentDate.day == buf.day) { //modify
            buf.day++;
        }
        if (buf.day > 31) { /*test cases in Final Exam.docx only December & January*/
            buf.day -= 31;
            buf.month++;
        } 
        if (buf.month > 12) {
            buf.month -= 12;
            buf.year++;
        }
        cout << i << ". " << buf.year << "/" << buf.month
            << "/" << buf.day << endl;
    }
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
    //vector<ReservationRecord> buf;
    bool have = false;
    int MaxnumRes = 0;

    if (reservations.size() == 0) {
        cout << "No reservations!\n"; return;
    }

    for (int i = 0; i <= reservations.size() - 1; i++){
        if (strcmp (reservations[i].idNumber, idNumber) == 0
            && (lessEqual(currentDate, reservations[i].date))) {
            have = true; break;
        }
    }

    if (have) {
        cout << endl << setw(26) << "Branch"
            << setw(14) << "Date" << setw(8) << "Hour"
            << setw(19) << "No of Customers" << endl;

        for (int i = 0; i <= reservations.size() - 1; i++) {
            if (strcmp(reservations[i].idNumber, idNumber) == 0
                && (lessEqual(currentDate, reservations[i].date))
                && reservations[i].date.year != 0
                && reservations[i].date.month != 0
                && reservations[i].date.day != 0
                && reservations[i].date.hour != 0) {
                cout << endl << ++MaxnumRes << ". "; 
                output(reservations[i]);
            }
        }
    }
    else {
        cout << "No reservations!\n"; return;
    }

    int del;

    do {
        cout << "\nChoose a reservation to cancel (0: keep all reservations): ";
        cin >> del;
        int numRes = 0;
        if (del == 0) {
            cin.ignore();
            return;
        }
        for (int i = 0; i <= reservations.size() - 1; i++) {
            if (strcmp(reservations[i].idNumber, idNumber) == 0
                && (lessEqual(currentDate, reservations[i].date))) {
                numRes++;
                if (del == numRes) {
                    reservations[i].date.year = 0;
                    reservations[i].date.month = 0;
                    reservations[i].date.day = 0;
                    reservations[i].date.hour = 0;
                }
            }
        }
    } while (del < 0 || del > MaxnumRes);
    
    cin.ignore();
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

    memberDetails.push_back( newMember );

    cout << "\nRegistration Completed!\n\n";

    cin.ignore();
}

bool existingID( char idNumber[], const vector< MemberRecord > &memberDetails )
{
    if (memberDetails.size() == 0) {
        return false;
    }

    for (int i = 0; i <= memberDetails.size() - 1; i++) {
        if (strcmp(idNumber, memberDetails[i].idNumber) == 0) {
            return true;
        }
    }

    return false;
}

void saveMemberDetails( const vector< MemberRecord > &memberDetails )
{
    ofstream saveMember("Members.dat", ios::out | ios::binary);

    if (!saveMember) {
        cout << "Members.dat in f(saveMemberDetails) cannot be opened!\n";
        exit(1);
    }

    for (int i = 0; i <= memberDetails.size() - 1; i++) {
        saveMember.write(reinterpret_cast<const char*>(&memberDetails[i]), sizeof(MemberRecord));
    }

    saveMember.clear(); saveMember.close();
}

void saveReservations( const vector< ReservationRecord > &reservations )
{
    ofstream saveRes("Reservations.dat", ios::out | ios::binary);

    if (!saveRes) {
        cout << "Reservations.dat in f(saveReservations) cannot be opened!\n";
        exit(1);
    }
    //cout << reservations.size() << endl;
    for (int i = 0; i <= reservations.size() - 1; i++) {
        if (reservations[i].date.year == 0 &&
            reservations[i].date.month == 0 &&
            reservations[i].date.day == 0 &&
            reservations[i].date.hour == 0) continue;
        saveRes.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(ReservationRecord));
    }

    saveRes.clear(); saveRes.close();
}
