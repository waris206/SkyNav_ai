#include "graph.h"
#include "MIDJourney.h"
#include "color.h"
#include "ascii.h"
#include <iostream>
using namespace std;



// Function to print the main menu
void printMenu()
{
    cout << BOLD_CYAN << "\n------------------- Main Menu -------------------\n"
         << RESET;
    cout << BOLD_GREEN << "| 1. Show all flights                           |\n"
         << RESET;
    cout << BOLD_YELLOW << "| 2. Direct flight options                      |\n"
         << RESET;
    cout << BOLD_BLUE << "| 3. Transit flight options                     |\n"
         << RESET;
    cout << BOLD_MAGENTA << "| 4. Multi-leg journey options                  |\n"
         << RESET;
    cout << BOLD_RED << "| 5. Exit                                       |\n"
         << RESET;
    cout << BOLD_CYAN << "-------------------------------------------------\n"
         << RESET;
    cout << BOLD_WHITE << "Enter your choice: " << RESET;
}

// Function to print sub-menu for Direct Flight Options
void printDirectFlightMenu()
{
    cout << BOLD_BLUE << "\n----------- Direct Flight Options ------------\n"
         << RESET;
    cout << BOLD_GREEN << "| 1. Check direct flight                      |\n"
         << RESET;
    cout << BOLD_YELLOW << "| 2. Check direct flight by date              |\n"
         << RESET;
    cout << BOLD_MAGENTA << "| 3. Check direct flight by airline           |\n"
         << RESET;
    cout << BOLD_RED << "| 4. Back to Main Menu                        |\n"
         << RESET;
    cout << BOLD_BLUE << "-----------------------------------------------\n"
         << RESET;
    cout << BOLD_WHITE << "Enter your choice: " << RESET;
}

// Function to print sub-menu for Transit Flight Options
void printTransitFlightMenu()
{
    cout << BOLD_MAGENTA << "\n------------ Transit Flight Options ------------\n"
         << RESET;
    cout << BOLD_GREEN << "| 1. Check transit flight                      |\n"
         << RESET;
    cout << BOLD_YELLOW << "| 2. Transit flight with specific airline      |\n"
         << RESET;
    cout << BOLD_RED << "| 3. Back to Main Menu                         |\n"
         << RESET;
    cout << BOLD_MAGENTA << "------------------------------------------------\n"
         << RESET;
    cout << BOLD_WHITE << "Enter your choice: " << RESET;
}

// Function to print sub-menu for Multi-leg Journey
void printMultiLegJourneyMenu()
{
    cout << BOLD_MAGENTA << "\n------------ Multi-leg Journey Options ------------\n"
         << RESET;
    cout << BOLD_GREEN << "| 1. Plan and check a multi-leg journey         |\n"
         << RESET;
    cout << BOLD_RED << "| 2. Back to Main Menu                          |\n"
         << RESET;
    cout << BOLD_MAGENTA << "--------------------------------------------------\n"
         << RESET;
    cout << BOLD_WHITE << "Enter your choice: " << RESET;
}

// Main function
int main()
{
    // Pointer for dynamic array of Flight objects
    Flight *flights = nullptr;
    int flightCount = 0; // Number of flights read

    // Read flights from the file into the array
    readFlights(flights, flightCount);

    // Extract unique cities
    string *uniqueCities = nullptr;
    int uniqueCount = 0;
    getUniqueCities(flights, flightCount, uniqueCities, uniqueCount);

    // Create graph
    Graph my_air_ai(uniqueCities, uniqueCount);

    // Add edges to the graph
    for (int i = 0; i < flightCount; i++)
    {
        my_air_ai.insertEdge(flights[i]);
    }

    // Main Menu Loop
    playSound();
          
          displayWelcome();

     
          printAsciiArtWithDelay();
          
          playwelcomesound();
          cout << BOLD_MAGENTA << "\nPress Enter to continue..." << RESET;
          cin.get();
    int mainChoice = 0;
    do
    {
          
        
        printMenu();
        cin >> mainChoice;

        switch (mainChoice)
        {
        case 1:
            // Show all flights
            cout << BOLD_YELLOW << "\nList of all flights:\n"
                 << RESET;
            for (int i = 0; i < flightCount; i++)
            {
                cout << BOLD_MAGENTA << "Flight " << i + 1 << ":" << RESET << " ";
                flights[i].display();
            }
            break;

        case 2:
        {
            // Direct Flight Options
            int directChoice = 0;
            do
            {
                printDirectFlightMenu();
                cin >> directChoice;

                if (directChoice == 1)
                {
                    string from, to;
                    cout << CYAN << "Enter source city: " << RESET;
                    cin >> from;
                    cout << CYAN << "Enter destination city: " << RESET;
                    cin >> to;
                    my_air_ai.directFlight(from, to);
                }
                else if (directChoice == 2)
                {
                    string from, to, date;
                    cout << CYAN << "Enter source city: " << RESET;
                    cin >> from;
                    cout << CYAN << "Enter destination city: " << RESET;
                    cin >> to;
                    cout << CYAN << "Enter date (DD/MM/YYYY): " << RESET;
                    cin >> date;
                    my_air_ai.directFlight_withDate(from, to, date);
                }
                else if (directChoice == 3)
                {
                    string from, to, airline;
                    cout << CYAN << "Enter source city: " << RESET;
                    cin >> from;
                    cout << CYAN << "Enter destination city: " << RESET;
                    cin >> to;
                    cout << CYAN << "Enter airline: " << RESET;
                    cin >> airline;
                    my_air_ai.directFlight_withAIRLINE(from, to, airline);
                }
                else if (directChoice != 4)
                {
                    cout << BOLD_RED << "Invalid choice! Try again.\n"
                         << RESET;
                }
            } while (directChoice != 4);
            break;
        }

        case 3:
        {
            // Transit Flight Options
            int transitChoice = 0;
            do
            {
                printTransitFlightMenu();
                cin >> transitChoice;

                if (transitChoice == 1)
                {
                    string from, to, transit;
                    cout << GREEN << "Enter source city: " << RESET;
                    cin >> from;
                    cout << GREEN << "Enter destination city: " << RESET;
                    cin >> to;
                    cout << GREEN << "Enter transit city: " << RESET;
                    cin >> transit;
                    my_air_ai.transitFlight(from, transit, to);
                }
                else if (transitChoice == 2)
                {
                    string from, to, transit, airline;
                    cout << GREEN << "Enter source city: " << RESET;
                    cin >> from;
                    cout << GREEN << "Enter destination city: " << RESET;
                    cin >> to;
                    cout << GREEN << "Enter transit city: " << RESET;
                    cin >> transit;
                    cout << GREEN << "Enter airline: " << RESET;
                    cin >> airline;
                    my_air_ai.transitFlight_airline_matters(from, transit, to, airline);
                }
                else if (transitChoice != 3)
                {
                    cout << BOLD_RED << "Invalid choice! Try again.\n"
                         << RESET;
                }
            } while (transitChoice != 3);
            break;
        }

        case 4:
        {
            // Multi-leg Journey Options
            int multiChoice = 0;
            do
            {
                printMultiLegJourneyMenu();
                cin >> multiChoice;

                if (multiChoice == 1)
                {
                    int numStops;
                    cout << CYAN << "Enter the number of stops: " << RESET; 
                    cin >> numStops;

                    string source, destination;
                    cout << CYAN << "Enter the source city: " << RESET;
                    cin >> source;

                    string *stops = new string[numStops];
                    for (int i = 0; i < numStops; i++)
                    {
                        cout << CYAN << "Enter stop " << i + 1 << ": " << RESET;
                        cin >> stops[i];
                    }

                    cout << CYAN << "Enter the destination city: " << RESET;
                    cin >> destination;

                    
                    Journey journey = my_air_ai.planMultiLegJourney(source, stops, numStops, destination);

                    // Display the result
                    cout << BOLD_MAGENTA << "Multi-leg journey flights:\n"
                         << RESET;
                    journey.printJourney(); 

                    delete[] stops; 
                }
                else if (multiChoice != 2)
                {
                    cout << BOLD_RED << "Invalid choice! Try again.\n"
                         << RESET;
                }

            } while (multiChoice != 2);
            break;
        }

        case 5:
            cout << BOLD_GREEN << "Exiting the program. Goodbye!\n"
                 << RESET;
            break;

        default:
            cout << BOLD_RED << "Invalid choice! Try again.\n"
                 << RESET;
        }
    } while (mainChoice != 5);

    // Free memory allocated for flights
    delete[] flights;

    return 0;
}
