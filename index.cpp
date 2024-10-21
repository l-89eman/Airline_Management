#include <iostream>
#include <fstream>
#ifdef _WIN32
#include <windows.h>
#endif
#include <sstream>
#include <unistd.h>
using namespace std;

class Airline
{
private:
    string flightNumber, destination, departure;
    int availableSeats;

public:
    Airline(string flight, string dest, string dep, int seats)
    {
        this->flightNumber = flight;
        this->destination = dest;
        this->departure = dep;
        this->availableSeats = seats;
    }

    string getFlightNumber()
    {
        return flightNumber;
    }

    string getDestination()
    {
        return destination;
    }

    string getDeparture()
    {
        return departure;
    }

    int getAvailableSeats()
    {
        return availableSeats;
    }

    void updateSeats()
    {
        ifstream in("/home/iman/Documents/flight.txt");
        ofstream out("/home/iman/Documents/flight_temp.txt");
        string line;

        while (getline(in, line))
        {
            int pos = line.find(flightNumber);
            if (pos != string::npos)
            {
                availableSeats--;
                stringstream ss;
                ss << availableSeats;
                string strSeats = ss.str();
                int seatPos = line.find_last_of(":");
                line.replace(seatPos + 2, string::npos, strSeats);
            }
            out << line << endl;
        }

        out.close();
        in.close();
        remove("/home/iman/Documents/flight.txt");
        rename("/home/iman/Documents/flight_temp.txt", "/home/iman/Documents/flight.txt");
    }

    void displayFlightInfo()
    {
        cout << "\nFlight Information:" << endl;
        cout << "Flight No: " << flightNumber << endl;
        cout << "Destination: " << destination << endl;
        cout << "Departure: " << departure << endl;
        cout << "Available Seats: " << availableSeats << endl;
    }
};

void displayFlights()
{
    ifstream in("/home/iman/Documents/flight.txt");
    if (!in.is_open())
    {
        cerr << "Error: Cannot open the file!" << endl;
    }
    else
    {
        string line;
        while (getline(in, line))
        {
            cout << line << endl;
        }
    }
}

int main()
{
    Airline flight1("a1", "UAE", "Pakistan", 50);
    Airline flight2("a2", "AE", "Qatar", 20);

    ofstream out("/home/iman/Documents/flight.txt");
    if (!out)
    {
        cerr << "Error: Cannot open the file!" << endl;
    }
    else
    {
        out << flight1.getFlightNumber() << "  : " << flight1.getDestination() << " : " << flight1.getDeparture() << " : " << flight1.getAvailableSeats() << endl;
        out << flight2.getFlightNumber() << "  : " << flight2.getDestination() << " : " << flight2.getDeparture() << " : " << flight2.getAvailableSeats() << endl;
        cout << "Data saved successfully!" << endl;
        out.close();
    }

    bool exit = false;
    while (!exit)
    {
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif

        cout << "\t Welcome To Airline Management System" << endl;
        cout << "\t *************************************" << endl;
        cout << "\t1. Reserve A Seat." << endl;
        cout << "\t2. Exit" << endl;
        cout << "\tEnter Your Choice: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            #ifdef _WIN32
            system("cls");
            #else
            system("clear");
            #endif

            displayFlights();
            string flightNo;
            cout << "Enter Your Flight No: ";
            cin >> flightNo;

            if (flightNo == flight1.getFlightNumber() && flight1.getAvailableSeats() > 0)
            {
                flight1.updateSeats();
                cout << "\nSeat reserved successfully!" << endl;
                flight1.displayFlightInfo();
            }
            else if (flightNo == flight2.getFlightNumber() && flight2.getAvailableSeats() > 0)
            {
                flight2.updateSeats();
                cout << "\nSeat reserved successfully!" << endl;
                flight2.displayFlightInfo();
            }
            else
            {
                cout << "\nSorry, seats are not available for the selected flight!" << endl;
            }
            usleep(4000000);
        }
        else if (choice == 2)
        {
            #ifdef _WIN32
            system("cls");
            #else
            system("clear");
            #endif

            exit = true;
            cout << "Good Luck!" << endl;
            usleep(3000000);
        }
    }

    return 0;
}
