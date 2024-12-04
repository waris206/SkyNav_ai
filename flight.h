#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// Class to represent a Flight
class Flight {
public:
    string departureCity;    // Source city
    string destinationCity;  // Destination city
    string date;             // Date of flight
    string time1;            // Start time
    string time2;            // End time
    int price;               // Ticket price
    string airline;          // Airline name

    // Constructor to initialize the flight data
    Flight(string dep = "", string dest = "", string d = "", string t1 = "", string t2 = "", int p = 0, string air = "")
        : departureCity(dep), destinationCity(dest), date(d), time1(t1), time2(t2), price(p), airline(air) {}

    // Display flight information
    void display() const {
        cout << departureCity << " -> " << destinationCity
             << ", Date: " << date
             << ", Time: " << time1 << " to " << time2
             << ", Price: " << price
             << ", Airline: " << airline << endl;
    }
};

// Function to read flights from a file and store them in an array of `Flight` objects
void readFlights(Flight*& flights, int& count) {
    // Allocate memory for up to 1000 flights (adjust as needed)
    flights = new Flight[1000];

    // Open the file
    ifstream file("Flights.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    count = 0; // Counter to track the number of flights

    while (getline(file, line)) { // Read each line from the file
        if (line.empty()) continue; // Skip empty lines

        // Parse the line into components
        string dep, dest, date, t1, t2, air;
        int price;
        istringstream ss(line);
        ss >> dep >> dest >> date >> t1 >> t2 >> price >> air;

        // Create a Flight object and store it in the array
        flights[count] = Flight(dep, dest, date, t1, t2, price, air);
        count++;
    }

    file.close();
}

// Function to get unique cities from flights
void getUniqueCities(const Flight* flights, int flightCount, string*& uniqueCities, int& uniqueCount) {
    uniqueCities = new string[flightCount * 2]; // Allocate memory for a maximum of 2 * flightCount cities
    uniqueCount = 0;

    // Loop through all flights to extract cities
    for (int i = 0; i < flightCount; i++) {
        // Check departure city
        bool isUnique = true;
        for (int j = 0; j < uniqueCount; j++) {
            if (uniqueCities[j] == flights[i].departureCity) {
                isUnique = false;
                break;
            }
        }
        if (isUnique) {
            uniqueCities[uniqueCount++] = flights[i].departureCity;
        }

        // Check destination city
        isUnique = true;
        for (int j = 0; j < uniqueCount; j++) {
            if (uniqueCities[j] == flights[i].destinationCity) {
                isUnique = false;
                break;
            }
        }
        if (isUnique) {
            uniqueCities[uniqueCount++] = flights[i].destinationCity;
        }
    }
}

// Function to display unique cities
void displayUniqueCities(const string* uniqueCities, int uniqueCount) {
    cout << "\nUnique Cities (" << uniqueCount << "):\n";
    for (int i = 0; i < uniqueCount; i++) {
        cout << uniqueCities[i] << endl;
    }
}

#endif