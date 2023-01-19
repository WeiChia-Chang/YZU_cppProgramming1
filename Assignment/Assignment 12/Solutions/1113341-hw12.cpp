#include <iostream>
#include <iomanip>
#include <fstream>
//#include <ctime>
using namespace std;

struct Date
{
    int year;
    int month;
    int day;
};

struct Reservation
{
    char flightNo[ 8 ]; // flight number
    char id[ 12 ];      // ID number
    char name[ 8 ];     // name
    char mobile[ 12 ];  // mobile phone number
    char date[ 12 ];    // departure date
    int tickets[ 8 ];
    // tickets[ 0 ]: not used
    // tickets[ 1 ]: number of full fare tickets
    // tickets[ 2 ]: number of child tickets
    // tickets[ 3 ]: number of infant tickets
    // tickets[ 4 ]: number of senior citizen tickets
    // tickets[ 5 ]: number of impaired tickets
    // tickets[ 6 ]: number of impaired companion tickets
    // tickets[ 7 ]: number of military tickets
};

struct Flight
{
    char flightNo[ 8 ];      // flight number
    char aircraft[ 8 ];      // aircraft model
    int departureAirport;    // departure airport code
    int arrivalAirport;      // arrival airport code
    char departureTime[ 8 ]; // departure time
    char arrivalTime[ 8 ];   // arrival time
    int dayWeek[ 7 ];        // the value of dayWeek[ i ] is 0 or 1
    // dayWeek[ 0 ] == 1 if and only if the flight flies on Sunday
    // dayWeek[ 1 ] == 1 if and only if the flight flies on Monday
    // dayWeek[ 2 ] == 1 if and only if the flight flies on Tuesday
    // dayWeek[ 3 ] == 1 if and only if the flight flies on Wednesday
    // dayWeek[ 4 ] == 1 if and only if the flight flies on Thursday
    // dayWeek[ 5 ] == 1 if and only if the flight flies on Friday
    // dayWeek[ 6 ] == 1 if and only if the flight flies on Saturday
};

struct FlightSeats
{
    char date[ 12 ];      // date
    char flightNo[ 8 ];   // flight number
    int departureAirport; // departure airport code
    int arrivalAirport;   // arrival airport code
    int availableSeats;   // the number of available seats
};

const char airportName[ 12 ][ 12 ] = { "", "Taipei",    "Taichung", "Chiayi",  "Tainan",
                                            "Kaohsiung", "Hualien", "Taitung",
                                            "Penghu",    "Kinmen",   "Beigan",  "Nangan" };

// row 0 and column 0 are not used,
// fullFare[ i ][ j ] is the full fare from airport i to airport j
const int fullFare[ 12 ][ 12 ] = {
    { 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { 0,    0,    0,    0,    0,    0, 1781, 2460, 2296, 2618, 2197, 2197 },
    { 0,    0,    0,    0,    0,    0,    0,    0, 1769, 2236,    0, 2686 },
    { 0,    0,    0,    0,    0,    0,    0,    0, 1721, 2217,    0,    0 },
    { 0,    0,    0,    0,    0,    0,    0,    0, 1697, 2231,    0,    0 },
    { 0,    0,    0,    0,    0,    0,    0,    0, 1876, 2393,    0,    0 },
    { 0, 1781,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { 0, 2460,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { 0, 2296, 1769, 1721, 1697, 1876,    0,    0,    0, 1768,    0,    0 },
    { 0, 2618, 2236, 2217, 2231, 2393,    0,    0, 1768,    0,    0,    0 },
    { 0, 2197,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { 0, 2197, 2686,    0,    0,    0,    0,    0,    0,    0,    0,    0 } };

const int discount[ 8 ] = { 0, 100, 75, 0, 50, 50, 50, 95 };
// discount[ 0 ]: not used
// discount[ 1 ]: Full Fare Ticket (全額票)
// discount[ 2 ]: Child Ticket (兒童票):                 25% off of the full fare
// discount[ 3 ]: Infant Ticket (嬰兒票):                Free of charge
// discount[ 4 ]: Senior Citizen Ticket (敬老票):        50% off of the full fare
// discount[ 5 ]: Impaired Ticket (愛心票):              50% off of the full fare
// discount[ 6 ]: Impaired Companion Ticket (愛心陪同票): 50% off of the full fare
// discount[ 7 ]: Military Ticket (軍人票):               5% off of the full fare

const int maxNumReservations = 1000;

int enterChoice();

// perform booking
void booking();

// choose arrival airport by input its code, and assign the code to arrivalAirport
void chooseArrivalAirport( int departureAirport, int &arrivalAirport );

// input the departure date
void inputDepartureDate( char date[], int &departureDayWeek );

// return the number of days between currentDate and departureDate
int difference( Date departureDate, Date currentDate );

bool leapYear( int year );

// load all flights from Flight Schedule.dat and put them into the array flights
void loadFlightSchedules( Flight flights[], int &numFlights );

// load all flights from departureAirport to arrivalAirport,
// and put them into the array flights
void loadFlightSchedules( Flight flights[], int &numFlights,
        int departureAirport, int arrivalAirport, int departureDayWeek );

// load all flightSeats from departureAirport to arrivalAirport on departureDate,
// and put them into the array flightSeats
void loadFlightSeats( FlightSeats flightSeats[], int &numFlightSeats, char departureDate[],
                        int departureAirport, int arrivalAirport );

// display all flights from departureAirport to arrivalAirport
void displayFlights( const Flight flights[], int numFlights,
                    FlightSeats flightSeats[], int &numFlightSeats,
                    int departureAirport, int arrivalAirport, char date[] );

// choose a flight by input its number,
// and assign the number to reservation.flightNo
void chooseFlight( Reservation &reservation, const Flight flights[], int numFlights );

// input the number of tickets for each ticket type,
// and assign them to reservation.tickets
void inputNumTickets( Reservation &reservation, FlightSeats flightSeats[], int &numFlightSeats );

// during booking and refund application,
// the corresponding availableSeats in Flight Seats.dat should be modified
void modifyFlightSeatsFile( Reservation &reservation, int totalNumTickets );

void displayReservation( const Reservation reservation,
                        const Flight flights[], int numFlights );

// append reservation to the end of Reservations.dat
void saveReservation( const Reservation reservation );

// perform booking inquiry
bool bookingInquiry( const char id[] );

// perform refund application
void refundApplication();

// load all reservations from Reservations.dat and put them to the array reservations
void loadReservations( Reservation reservations[], int &numReservations );

int main()
{
    cout << "Welcome to UNI Air Domestic Flights Booking System\n";
    char id[ 12 ];
    int choice;

    while( ( choice = enterChoice() ) != 4 )
    {
        switch( choice )
        {
        case 1:
            booking(); // perform booking
            break;
        case 2:
            cout << "\nEnter ID number: ";
            cin >> id;
            bookingInquiry( id ); // perform booking inquiry
            break;
        case 3:
            refundApplication(); // perform refund application
            break;

        default:
            cerr << "\nInput error!\n";
            break;
        }
    }

    cout << endl;
    system( "pause" );
}

int enterChoice()
{
    cout << "\nInput your choice:\n"
        << "1. Booking\n"
        << "2. Booking enquiry\n"
        << "3. Refund application\n"
        << "4. End\n? ";

    int menuChoice;
    cin >> menuChoice;
    return menuChoice;
}

// perform booking
void booking()
{
    // choose departure airport by input its code,
    // and assign the code to departureAirport
    int departureAirport;
    do {
        cout << "\nDeparture airport:\n";
        for (int i = 1; i <= 11; i++)
            cout << setw(2) << i << ". " << airportName[i] << endl;
        cout << "? ";

        cin >> departureAirport;
    } while (departureAirport < 1 || departureAirport > 11);

    int arrivalAirport;
    // choose arrival airport by input its code, and assign the code to arrivalAirport
    chooseArrivalAirport(departureAirport, arrivalAirport);

    Reservation reservation = { "", "", "", "", "", 0, 0, 0, 0, 0, 0, 0, 0 };

    int departureDayWeek; // departureDayWeek == 0 if departure date is Sunday
    // departureDayWeek == 1 if departure date is Monday
    // departureDayWeek == 2 if departure date is Tuesday
    // departureDayWeek == 3 if departure date is Wednesday
    // departureDayWeek == 4 if departure date is Thursday
    // departureDayWeek == 5 if departure date is Friday
    // departureDayWeek == 6 if departure date is Saturday

    inputDepartureDate(reservation.date, departureDayWeek);

    Flight flights[20];
    int numFlights = 0;

    // load all flights from departureAirport to arrivalAirport,
    // and put them into the array flights
    loadFlightSchedules(flights, numFlights, departureAirport, arrivalAirport,
        departureDayWeek);

    if (numFlights == 0) {
        cout << "No flights from " << airportName[departureAirport] <<
            " to " << airportName[arrivalAirport] << " on " << reservation.date << "! \n";
            return;
    }

    FlightSeats flightSeats[20];
    int numFlightSeats = 0;

    loadFlightSeats(flightSeats, numFlightSeats, reservation.date,
        departureAirport, arrivalAirport);

    int maxNumSeats = 0;
    for (int i = 1; i <= numFlights; i++)
        if (maxNumSeats < flightSeats[i].availableSeats)
            maxNumSeats = flightSeats[i].availableSeats;

    if (maxNumSeats == 0)
    {
        cout << "No available seats from " << airportName[departureAirport] <<
            " to " << airportName[arrivalAirport] << " on " << reservation.date << "!\n";
        return;
    }

    // display all flights from departureAirport to arrivalAirport
    displayFlights(flights, numFlights, flightSeats, numFlightSeats,
        departureAirport, arrivalAirport, reservation.date);

    // choose a flight by input its number, and assign the number to reservation.flightNo
    chooseFlight(reservation, flights, numFlights);

    // input the number of tickets for each ticket type,
    // and assign them to reservation.tickets
    inputNumTickets(reservation, flightSeats, numFlightSeats);

    int totalNumTickets = -reservation.tickets[3];
    for (int i = 1; i < 8; i++)
        totalNumTickets += reservation.tickets[i];

    if (totalNumTickets > 0)
        modifyFlightSeatsFile(reservation, totalNumTickets);
    else
    {
        cout << "Your booking could not be completed!\n";
        return;
    }

    displayReservation(reservation, flights, numFlights);

    cout << "\nID number: ";
    cin >> reservation.id;
    cout << "\nName: ";
    cin >> reservation.name;
    cout << "\nMobile: ";
    cin >> reservation.mobile;

    // append reservation to the end of Reservations.dat
    saveReservation(reservation);

    cout << "\nBooking completed!\n";
}
// choose arrival airport by input its code, and assign the code to arrivalAirport
void chooseArrivalAirport( int departureAirport, int &arrivalAirport )
{
    int canArrive[100]{}; /*a boolean array, if the flight exists, the value is 1; while not, 0*/

    do {
        cout << "\nArriving Airport:\n";
        for (int i = 1; i <= 11; i++) {
            if (fullFare[departureAirport][i] == 0) continue;
            cout << right << setw(2) << i << ". " << airportName[i] << endl;
            canArrive[i] = 1; /*if the flight exists, set its canArrive value to 1*/
        }
        cout << "? ";
        cin >> arrivalAirport;
    } while (canArrive[arrivalAirport] == 0);

}

void inputDepartureDate( char date[], int &departureDayWeek )
{
    tm structuredTime;
    time_t rawTime = time( nullptr );
    localtime_s( &structuredTime, &rawTime );

    int year = structuredTime.tm_year + 1900;
    int month = structuredTime.tm_mon + 1;
    int day = structuredTime.tm_mday;
    departureDayWeek = structuredTime.tm_wday;

    char date_year[5];
    char date_month[3];
    char date_day[3];
    char buffer[12] = ""; /*store departure information then copy to char array "date"*/

    Date current;
    current.year = year; current.month = month; current.day = day;

    int arrYear[6], arrMon[6]; /*store numbers of year and month which show up in departure date choices*/
    int de; /*the choice user choose for departure date (month)*/
   
    cout << "\nDeparture Date (Month):\n";
    for (int i = 1; i <= 6; i++) {
        if (month > 12) {
            year++;
            month = 1;
        }
        arrYear[i - 1] = year; arrMon[i - 1] = month;
        cout << i << ". " << year << "-" << month << endl;
        month++;
    }

    cout << "? ";
    cin >> de;

    Date departure;
    departure.year = arrYear[de - 1]; departure.month = arrMon[de - 1];

    cout << endl;

    if (departure.month == current.month) {
        cout << "Day (" << current.day << " ~ 31): ";
    }
    else {
        switch (departure.month) {
        case 2:
            if (leapYear(departure.month)) cout << "Day (1 ~ 29): ";
            else cout << "Day (1 ~ 28): ";
            break;
        case 4:
            cout << "Day (1 ~ 30): ";
            break;
        case 6:
            cout << "Day (1 ~ 30): ";
            break;
        case 9:
            cout << "Day (1 ~ 30): ";
            break;
        case 11:
            cout << "Day (1 ~ 30): ";
            break;
        default:
            cout << "Day (1 ~ 31): ";
            break;
        }
    }
    cin >> departure.day;

    _itoa_s(departure.year, date_year, 10);
    _itoa_s(departure.month, date_month, 10);
    _itoa_s(departure.day, date_day, 10);

    strcat_s(buffer, 12, date_year);
    strcat_s(buffer, 12, "/");
    strcat_s(buffer, 12, date_month);
    strcat_s(buffer, 12, "/");
    strcat_s(buffer, 12, date_day);
    strcpy_s(date, 12, buffer);

    int diffDays = difference(departure, current);
    diffDays %= 7; /*calculate departure date is which day in a week*/
    departureDayWeek += diffDays;

    if (departureDayWeek > 6)
        departureDayWeek -= 7;

    cout << endl;
}

int difference( Date departureDate, Date currentDate )
{
    int mdNormal[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; /*days of each month in normal year*/
    int mdLeap[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; /*days of each month in leap year*/
    
    int differMon; /*difference of month(s)*/
    int diffDays{}; /*difference of day(s)*/

    if (departureDate.month > currentDate.month)
        differMon = departureDate.month - currentDate.month;
    else if (departureDate.month == currentDate.month)
        differMon = 0;
    else
        differMon = 12 - currentDate.month + departureDate.month;
    int bufYear = currentDate.year;
    if (leapYear(currentDate.year)) {
        if (differMon > 1) { /*using mdLeap directly*/
            diffDays += mdLeap[currentDate.month] - currentDate.day;
            int diffBuf = currentDate.month + 1;
            int bufYear = currentDate.year;
            if (diffBuf > 12) diffBuf -= 12;
            for (int i = diffBuf, times = 1; times <= differMon - 1; i++, times++) {
                if (i > 12) {
                    i -= 12;
                    bufYear++;
                }
                diffDays += mdLeap[i];
            }
            diffDays += departureDate.day;
        }
        else if (differMon == 1) { /*cannot use mdLeap directly*/
            diffDays += mdLeap[currentDate.month] - currentDate.day;
            diffDays += departureDate.day;
        }
        else { /*departure day is in current month*/
            diffDays = departureDate.day - currentDate.day;
        }
    }
    else {
        if (differMon > 1) { /*using mdNormal directly*/
            diffDays += mdNormal[currentDate.month] - currentDate.day;
            int diffBuf = currentDate.month + 1;
            if (diffBuf > 12) diffBuf -= 12;
            for (int i = diffBuf, times = 1; times <= differMon - 1; i++, times++) {
                if (i > 12) {
                    i -= 12;
                    bufYear++;
                }
                diffDays += mdNormal[i];
            }
            diffDays += departureDate.day;
        }
        else if (differMon == 1) { /*cannot using mdNormal directly*/
            diffDays = mdNormal[currentDate.month] - currentDate.day;
            diffDays += departureDate.day;
        }
        else {
            diffDays += departureDate.day - currentDate.day;
        }
    }
    return diffDays;
}

bool leapYear( int year )
{
    return ( year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) );
}

// load all flights from Flight Schedule.dat and put them into the array flights
void loadFlightSchedules( Flight flights[], int &numFlights )
{
    fstream inOutFlight("Flight Schedule.dat", ios::in | ios::out | ios::binary);

    if (!inOutFlight) {
        cerr << "Flight Schedual in f(loadFlightSchedules) cannot be opened!\n";
        exit(1);
    }
    inOutFlight.seekg(0, ios::end);
    numFlights = static_cast<int>(inOutFlight.tellg()) / sizeof(Flight);
    inOutFlight.seekg(0, ios::beg);

    for (int i = 1; i <= numFlights; i++) 
        inOutFlight.read(reinterpret_cast<char*>(&flights[i]), sizeof(Flight));
    
    inOutFlight.clear();
    inOutFlight.close();

}

// load all flights from departureAirport to arrivalAirport,
// and put them into the array flights
void loadFlightSchedules( Flight flights[], int &numFlights,
        int departureAirport, int arrivalAirport, int departureDayWeek )
{
    Flight buf[200];
    int maxNumFlights;

    loadFlightSchedules(buf, maxNumFlights);

    for (int i = 1; i <= maxNumFlights; i++) {
        if (buf[i].departureAirport == departureAirport && buf[i].arrivalAirport == arrivalAirport &&
            buf[i].dayWeek[departureDayWeek] == 1) {
            flights[++numFlights] = buf[i];
        }
    }
}

void loadFlightSeats( FlightSeats flightSeats[], int &numFlightSeats, char departureDate[],
        int departureAirport, int arrivalAirport )
{
    fstream fsFile("Flight Seats.dat", ios::in | ios::out | ios::binary);

    if (!fsFile) {
        cerr << "Flight Seat in f(loadFlightSeats) couldn't be opened!\n";
        exit(1);
    }

    fsFile.seekg(0, ios::end);

    FlightSeats buf;
    int numBuf = fsFile.tellg() / sizeof(FlightSeats);
    fsFile.seekg(0, ios::beg);

    for (int i = 0; i <= numBuf; i++) {
        fsFile.read(reinterpret_cast<char*>(&buf), sizeof(FlightSeats));
        if (strcmp(buf.date, departureDate) == 0 && buf.departureAirport == departureAirport
            && buf.arrivalAirport == arrivalAirport) {
            flightSeats[++numFlightSeats] = buf;
        }
    }

    fsFile.clear();
    fsFile.close();
}

// display all flights from departureAirport to arrivalAirport
void displayFlights( const Flight flights[], int numFlights,
                    FlightSeats flightSeats[], int &numFlightSeats,
                    int departureAirport, int arrivalAirport, char date[] )
{
    cout << airportName[ departureAirport ] << " to " << airportName[ arrivalAirport ]
        << " / Depart date: " << date << ".\n\n";
    cout << "Flight   Departure   Arrival   Fare   No. Available Seats\n";

    for (int i = 1; i <= numFlights; i++)
        if (flightSeats[i].availableSeats > 0)
            cout << setw(6) << flights[i].flightNo
            << setw(12) << flights[i].departureTime
            << setw(10) << flights[i].arrivalTime
            << setw(7) << fullFare[departureAirport][arrivalAirport]
            << setw(22) << flightSeats[i].availableSeats << endl;
}

// choose a flight by input its number, and assign the number to reservation.flightNo
void chooseFlight( Reservation &reservation, const Flight flights[], int numFlights )
{
    char fliNo[8];
    bool haveTheFlight = false;

    do {
        cout << "\nFlight number: ";
        cin >> fliNo;
        for (int i = 1; i <= numFlights; i++) {
            if (strcmp(fliNo, flights[i].flightNo) == 0) {
                haveTheFlight = true;
                strcpy_s(reservation.flightNo, 8, fliNo);
            }
        }
    } while (!haveTheFlight);

}

// input the number of tickets for each ticket type, and assign them to reservation.tickets
void inputNumTickets( Reservation &reservation, FlightSeats flightSeats[], int &numFlightSeats )
{
    int i;
    for( i = 1; i <= numFlightSeats; i++ )
        if( strcmp( reservation.flightNo, flightSeats[ i ].flightNo ) == 0 )
            break;

    int numAvailableSeats = flightSeats[ i ].availableSeats;
    int maxNumTickets = ( numAvailableSeats < 4 ) ? numAvailableSeats : 4;

    do {
        cout << "\nNumber of infant tickets (0 ~ " << maxNumTickets << "): ";
        cin >> reservation.tickets[ 3 ];
    } while( reservation.tickets[ 3 ] < 0 || reservation.tickets[ 3 ] > maxNumTickets );

    int numTickets = 0;
    int numAdults = 0;
    do
    {
        numTickets = 0;

        cout << "\nNumber of full fare tickets (0 ~ " << maxNumTickets << "): ";
        cin >> reservation.tickets[ 1 ];
        numTickets += reservation.tickets[ 1 ];

        cout << "\nNumber of child tickets (0 ~ " << maxNumTickets << "): ";
        cin >> reservation.tickets[ 2 ];
        numTickets += reservation.tickets[ 2 ];

        cout << "\nNumber of senior citizen tickets (0 ~ " << maxNumTickets << "): ";
        cin >> reservation.tickets[ 4 ];
        numTickets += reservation.tickets[ 4 ];

        cout << "\nNumber of impaired tickets (0 ~ " << maxNumTickets << "): ";
        cin >> reservation.tickets[ 5 ];
        numTickets += reservation.tickets[ 5 ];

        cout << "\nNumber of impaired companion tickets (0 ~ " << maxNumTickets << "): ";
        cin >> reservation.tickets[ 6 ];
        numTickets += reservation.tickets[ 6 ];

        cout << "\nNumber of military tickets (0 ~ " << maxNumTickets << "): ";
        cin >> reservation.tickets[ 7 ];
        numTickets += reservation.tickets[ 7 ];

        numAdults = reservation.tickets[ 1 ] + reservation.tickets[ 4 ] +
                    reservation.tickets[ 5 ] + reservation.tickets[ 6 ] +
                    reservation.tickets[ 7 ];

        if( numTickets > maxNumTickets )
            cout << "\nYou can books a maximum of " << maxNumTickets
                << " passengers ( including children ).\n";
        else if( numAdults < reservation.tickets[ 3 ] )
            cout << "\nEach infant must always be accompanied by at least one adult.\n";
    } while( numTickets > maxNumTickets || numAdults < reservation.tickets[ 3 ] );

    cout << endl;
}

void modifyFlightSeatsFile( Reservation &reservation, int totalNumTickets )
{
    fstream editFS("Flight Seats.dat", ios::in | ios::out | ios::binary);

    if (!editFS) {
        cerr << "Flight Seats in f(modifyFlightSeatsFile) cannot be opened!\n";
        exit(1);
    }

    editFS.seekg(0, ios::end);
    FlightSeats bufFS;
    int numFS = editFS.tellg() / sizeof(FlightSeats);
    editFS.seekg(0, ios::beg);

    for (int i = 1; i <= numFS; i++) {
        editFS.read(reinterpret_cast<char*>(&bufFS), sizeof(FlightSeats));
        if ((strcmp(bufFS.flightNo, reservation.flightNo) == 0) && (strcmp(bufFS.date, reservation.date) == 0)) {
            bufFS.availableSeats -= totalNumTickets;
            break;
        }
    }
    
    editFS.seekp(-(int)sizeof(FlightSeats), ios::cur);

    editFS.write(reinterpret_cast<char*>(&bufFS), sizeof(FlightSeats));

    editFS.clear();
    editFS.close();
}

void displayReservation( const Reservation reservation,
                            const Flight flights[], int numFlights )
{
    int k;
    for( k = 1; k <= numFlights; k++ )
        if( strcmp( reservation.flightNo, flights[ k ].flightNo ) == 0 )
            break;

    cout << "Ticket information:\n\n";
    cout << "Date: " << reservation.date << endl;
    cout << "Flight: B7-" << reservation.flightNo << endl << endl;

    int departureAirport = flights[ k ].departureAirport;
    int arrivalAirport = flights[ k ].arrivalAirport;

    cout << setw( 9 ) << right << airportName[ departureAirport ] << " -> "
        << setw( 9 ) << left << airportName[ arrivalAirport ] << endl;

    cout << setw( 9 ) << right << flights[ k ].departureTime << "    ";
    cout << setw( 9 ) << left << flights[ k ].arrivalTime << endl << endl;

    char ticketType[ 8 ][ 24 ] = { "", "Full Fare", "Child Fare", "Infant Fare",
                                        "Senior Citizen Fare",     "Impaired Fare",
                                        "Impaired Companion Fare", "Military Fare" };

    int total = 0;
    int fare;
    for( int i = 1; i <= 7; i++ )
        if( reservation.tickets[ i ] > 0 )
        {
            fare = fullFare[ departureAirport ][ arrivalAirport ] * discount[ i ] / 100;
            total += ( fare * reservation.tickets[ i ] );
            cout << right << setw( 23 ) << ticketType[ i ] << "  TWD "
                << setw( 4 ) << fare << " x " << reservation.tickets[ i ] << endl;
        }

    cout << "\nTotal: " << total << endl;
}

// append reservation to the end of Reservations.dat
void saveReservation( const Reservation reservation )
{
    ofstream writeRes("Reservations.dat", ios::app | ios::binary);

    if (!writeRes) {
        cerr << "Reservations in f(saveReservation) could not be opened!\n";
        exit(1);
    }

    writeRes.write(reinterpret_cast<const char*>(&reservation), sizeof(Reservation));

    writeRes.clear();
    writeRes.close();
}

// perform booking inquiry
bool bookingInquiry( const char id[] )
{
    Flight bufFli[200];
    int numFli;
    loadFlightSchedules(bufFli, numFli);

    Reservation bufRes[maxNumReservations];
    int numRes;
    loadReservations(bufRes, numRes);

    bool has = false;
    int numBooking{ 1 };

    cout << endl;

    for (int i = 1; i <= numRes; i++) {
        if (strcmp(bufRes[i].id, id) == 0) {
            cout << numBooking << ".  ";
            displayReservation(bufRes[i], bufFli, numFli);
            cout << endl;
            has = true;
            numBooking++;
        }
    }

    if (has) {
        return true;
    }
    else {
        cout << "No reservations!\n";
        return false;
    }

}

// perform refund application
void refundApplication()
{
    char id[ 12 ];

    cout << "\nEnter ID number: ";
    cin >> id;

    if( !bookingInquiry( id ) )
        return;

    int choice;
    cout << "\nEnter your choice: ";
    cin >> choice;

    Reservation reservations[ maxNumReservations ];
    int numReservations;
    loadReservations( reservations, numReservations );
    
    int bookingOftheId{ 0 };
    int totalTickets{};

    for (int i = 1; i <= numReservations; i++) {
        if (strcmp(id, reservations[i].id) == 0) {
            bookingOftheId++;
            if (bookingOftheId == choice) {
                for (int j = 1; j <= 7; j++) {
                    if (j == 3) continue;
                    totalTickets += reservations[i].tickets[j];
                }
                modifyFlightSeatsFile(reservations[i], -totalTickets);
                reservations[i].flightNo[0] = ' ';
                break;
            }
        }
    }

    ofstream editRes("Reservations.dat", ios::out | ios::binary);

    if (!editRes) {
        cerr << "Reservations in f(refundApplication) could not be opened!\n";
        exit(1);
    }

    editRes.seekp(0, ios::beg);

    for (int i = 1; i <= numReservations; i++) {
        if (reservations[i].flightNo[0] == ' ') continue;
        editRes.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(Reservation));
    }
    
    editRes.clear();
    editRes.close();

    cout << "\nThe seleted booking has been deleted.\n";
}

// load all reservations from Reservations.dat and put them to the array reservations
void loadReservations( Reservation reservations[], int &numReservations )
{
    fstream loadRes("Reservations.dat", ios::in | ios::out | ios::binary);

    if (!loadRes) {
        cerr << "Reservations in f(loadReservtions) could not be opened!\n";
        exit(1);
    }
    loadRes.seekg(0, ios::end);
    numReservations = loadRes.tellp() / sizeof(Reservation);
    loadRes.seekg(0, ios::beg);

    for (int i = 1; i <= numReservations; i++) {
        loadRes.read(reinterpret_cast<char*>(&reservations[i]), sizeof(Reservation));
    }

    loadRes.clear();
    loadRes.close();
}
