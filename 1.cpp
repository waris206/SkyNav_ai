#include"graph.h"

int main() {
    // Pointer for dynamic array of Flight objects
    Flight* flights = nullptr;
    int flightCount = 0; // Number of flights read

    // Read flights from the file into the array
    readFlights(flights, flightCount);

    // Display the flights to verify
    /*cout << "\nAll Flights:\n";
    for (int i = 0; i < flightCount; i++) {
        cout << "Flight " << i + 1 << ": ";
        flights[i].display();
    }*/

    // Extract unique cities
    string* uniqueCities = nullptr;
    int uniqueCount = 0;
    getUniqueCities(flights, flightCount, uniqueCities, uniqueCount);

    // Display unique cities
     ///displayUniqueCities(uniqueCities, uniqueCount);


     Graph my_air_ai(uniqueCities,uniqueCount);
     
     for (int i = 0; i < flightCount ; i++)
     {
         my_air_ai.insertEdge(flights[i]);
     }
          my_air_ai.showGraphStructure();
     


    // Free dynamically allocated memory
    delete[] flights;
    delete[] uniqueCities;

    return 0;
}
