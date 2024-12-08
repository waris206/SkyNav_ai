#include <SFML/Graphics.hpp>
#include "GraphVisualizer.h"
#include "ascii.h"

#include <stdexcept>
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
    cout << BOLD_RED << "| 5. Shortest path options                      |\n"
        << RESET;
    cout << BOLD_RED << "| 6. Exit                                       |\n"
        << RESET;
    cout << BOLD_CYAN << "-------------------------------------------------\n"
        << RESET;
    cout << BOLD_WHITE << "Enter your choice: " << RESET;
}

// Function to print sub-menu for Shortest Path Options
void printShortestPathMenu()
{
    cout << BOLD_YELLOW << "\n------------ Shortest Path Options ------------\n"
        << RESET;
    cout << BOLD_GREEN << "| 1. Shortest path by cost                     |\n"
        << RESET;
    cout << BOLD_MAGENTA << "| 2. Shortest path by date                     |\n"
        << RESET;
    cout << BOLD_RED << "| 3. Back to Main Menu                         |\n"
        << RESET;
    cout << BOLD_YELLOW << "-----------------------------------------------\n"
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

// Example usage in main function
int main() {
    // Pointer for dynamic array of Flight objects
    Flight* flights = nullptr;
    int flightCount = 0; // Number of flights read

    // Read flights from the file into the array
    readFlights(flights, flightCount);

    // Extract unique cities
    string* uniqueCities = nullptr;
    int uniqueCount = 0;
    getUniqueCities(flights, flightCount, uniqueCities, uniqueCount);

    // Create graph
    Graph my_air_ai(uniqueCities, uniqueCount);

    // Main Menu Loop
    SoundPlayer player;
    int mainChoice = 0;
    string input;
    player.playSound("sound.wav");
    displayWelcome();
    printAsciiArtWithDelay();
    player.playSound("welcome.wav");
    cout << BOLD_MAGENTA << "\nPress Enter to continue..." << RESET;
    cin.get();

    // You would typically populate this from your graph data
    int numCities = uniqueCount;
    GraphVisualizer visualizer(uniqueCities, numCities);

    // Add edges to the graph
    for (int i = 0; i < flightCount; i++)
    {
        my_air_ai.insertEdge(flights[i]);
        visualizer.addEdge(flights[i].departureCity, flights[i].destinationCity, flights[i]);
    }

    do
    {
        printMenu();
        cin >> input;
        try
        {
            mainChoice = stoi(input);
        }
        catch (const invalid_argument&)
        {
            cout << BOLD_RED << "Invalid choice! Try again.\n" << RESET;
            continue;
        }
        catch (const out_of_range&)
        {
            cout << BOLD_RED << "Input is out of range for an integer. Try again.\n" << RESET;
            continue;
        }

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
            visualizer.render();
            break;

        case 2:
        {
            // Direct Flight Options
            int directChoice = 0;
            do
            {
                printDirectFlightMenu();
                cin >> input;
                try
                {
                    directChoice = stoi(input);
                }
                catch (const invalid_argument&)
                {
                    cout << BOLD_RED << "Invalid choice! Try again.\n" << RESET;
                    continue;
                }
                catch (const out_of_range&)
                {
                    cout << BOLD_RED << "Input is out of range for an integer. Try again.\n" << RESET;
                    continue;
                }

                if (directChoice == 1)
                {
                    string from, to;
                    cout << CYAN << "Enter source city: " << RESET;
                    cin >> from;
                    cout << CYAN << "Enter destination city: " << RESET;
                    cin >> to;
                    AdjLst* myDirectList = my_air_ai.directFlight(from, to);

                    if (myDirectList)
                    {
                        node* temp = myDirectList->head;
                        temp = temp->next;

                        GraphVisualizer direcectGraph(uniqueCities, numCities);
                        // Add edges to the graph
                        while(temp)
                        {
                            direcectGraph.addEdge(temp->data.departureCity, temp->data.destinationCity, temp->data);
                            temp = temp->next;
                        }
                        direcectGraph.render();
                    }
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
                    Journey* myDirectList = my_air_ai.directFlight_withDate(from, to, date);

                    if (myDirectList)
                    {
                        JourneyNode* temp = myDirectList->head;

                        GraphVisualizer direcectGraph(uniqueCities, numCities);
                        // Add edges to the graph
                        while (temp)
                        {
                            direcectGraph.addEdge(temp->data.departureCity, temp->data.destinationCity, temp->data);
                            temp = temp->next;
                        }
                        direcectGraph.render();
                    }
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
                    
                    Journey* myDirectList = my_air_ai.directFlight_withAIRLINE(from, to, airline);

                    if (myDirectList)
                    {
                        JourneyNode* temp = myDirectList->head;

                        GraphVisualizer direcectGraph(uniqueCities, numCities);
                        // Add edges to the graph
                        while (temp)
                        {
                            direcectGraph.addEdge(temp->data.departureCity, temp->data.destinationCity, temp->data);
                            temp = temp->next;
                        }
                        direcectGraph.render();
                    }
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
                cin >> input;
                try
                {
                    transitChoice = stoi(input);
                }
                catch (const invalid_argument&)
                {
                    cout << BOLD_RED << "Invalid choice! Try again.\n" << RESET;
                    continue;
                }
                catch (const out_of_range&)
                {
                    cout << BOLD_RED << "Input is out of range for an integer. Try again.\n" << RESET;
                    continue;
                }

                if (transitChoice == 1)
                {
                    string from, to, transit;
                    cout << GREEN << "Enter source city: " << RESET;
                    cin >> from;
                    cout << GREEN << "Enter destination city: " << RESET;
                    cin >> to;
                    cout << GREEN << "Enter transit city: " << RESET;
                    cin >> transit;          
                    Journey* myTransitList = my_air_ai.transitFlight(from, transit, to);

                    if (myTransitList)
                    {
                        JourneyNode* temp = myTransitList->head;

                        GraphVisualizer direcectGraph(uniqueCities, numCities);
                        // Add edges to the graph
                        while (temp)
                        {
                            direcectGraph.addEdge(temp->data.departureCity, temp->data.destinationCity, temp->data);
                            temp = temp->next;
                        }
                        direcectGraph.render();
                    }
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
                    Journey* myTransitList = my_air_ai.transitFlight_airline_matters(from, transit, to, airline);

                    if (myTransitList)
                    {
                        JourneyNode* temp = myTransitList->head;

                        GraphVisualizer direcectGraph(uniqueCities, numCities);
                        // Add edges to the graph
                        while (temp)
                        {
                            direcectGraph.addEdge(temp->data.departureCity, temp->data.destinationCity, temp->data);
                            temp = temp->next;
                        }
                        direcectGraph.render();
                    }
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
                cin >> input;
                try
                {
                    multiChoice = stoi(input);
                }
                catch (const invalid_argument&)
                {
                    cout << BOLD_RED << "Invalid choice! Try again.\n" << RESET;
                    continue;
                }
                catch (const out_of_range&)
                {
                    cout << BOLD_RED << "Input is out of range for an integer. Try again.\n" << RESET;
                    continue;
                }

                if (multiChoice == 1)
                {
                    int numStops;
                    cout << CYAN << "Enter the number of stops: " << RESET;
                    cin >> numStops;

                    string source, destination;
                    cout << CYAN << "Enter the source city: " << RESET;
                    cin >> source;

                    string* stops = new string[numStops];
                    for (int i = 0; i < numStops; i++)
                    {
                        cout << CYAN << "Enter stop " << i + 1 << ": " << RESET;
                        cin >> stops[i];
                    }

                    cout << CYAN << "Enter the destination city: " << RESET;
                    cin >> destination;


                    Journey* journey = my_air_ai.planMultiLegJourney(source, stops, numStops, destination);

                    // Display the result
                    cout << BOLD_MAGENTA << "Multi-leg journey flights:\n"
                        << RESET;

                    if (journey)
                    {
                        journey->printJourney();
                        JourneyNode* temp = journey->head;

                        GraphVisualizer direcectGraph(uniqueCities, numCities);
                        // Add edges to the graph
                        while (temp)
                        {
                            direcectGraph.addEdge(temp->data.departureCity, temp->data.destinationCity, temp->data);
                            temp = temp->next;
                        }
                        direcectGraph.render();
                    }
                    else
                    {
                        cout << "No flights planned in the journey." << endl;
                    }

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
        {
            // Shortest Path Options
            int shortestChoice = 0;
            do
            {
                printShortestPathMenu();
                cin >> input;
                try
                {
                    shortestChoice = stoi(input);
                }
                catch (const invalid_argument&)
                {
                    cout << BOLD_RED << "Invalid choice! Try again.\n" << RESET;
                    continue;
                }
                catch (const out_of_range&)
                {
                    cout << BOLD_RED << "Input is out of range for an integer. Try again.\n" << RESET;
                    continue;
                }

                if (shortestChoice == 1)
                {
                    string from, to;
                    cout << GREEN << "Enter source city: " << RESET;
                    cin >> from;
                    cout << GREEN << "Enter destination city: " << RESET;
                    cin >> to;
                    
                    Journey* journey = my_air_ai.dijkstra(from, to);

                    // Display the result
                    cout << BOLD_MAGENTA << "Multi-leg journey flights:\n"
                        << RESET;

                    if (journey)
                    {
                        journey->printJourney();
                        JourneyNode* temp = journey->head;

                        GraphVisualizer direcectGraph(uniqueCities, numCities);
                        // Add edges to the graph
                        while (temp)
                        {
                            direcectGraph.addEdge(temp->data.departureCity, temp->data.destinationCity, temp->data);
                            temp = temp->next;
                        }
                        direcectGraph.render();
                    }
                    else
                    {
                        cout << "No flights planned in the journey." << endl;
                    }
                }
                else if (shortestChoice == 2)
                {
                    string from, to;
                    cout << GREEN << "Enter source city: " << RESET;
                    cin >> from;
                    cout << GREEN << "Enter destination city: " << RESET;
                    cin >> to;

                    Journey* journey = my_air_ai.dijkstraByDate(from, to);

                    // Display the result
                    if (journey)
                    {
                        JourneyNode* temp = journey->head;

                        GraphVisualizer direcectGraph(uniqueCities, numCities);
                        // Add edges to the graph
                        while (temp)
                        {
                            direcectGraph.addEdge(temp->data.departureCity, temp->data.destinationCity, temp->data);
                            temp = temp->next;
                        }
                        direcectGraph.render();
                    }
                    else
                    {
                        cout << "No flights planned in the journey." << endl;
                    }
                }
                else if (shortestChoice != 3)
                {
                    cout << BOLD_RED << "Invalid choice! Try again.\n"
                        << RESET;
                }
            } while (shortestChoice != 3);
            break;
        }

        case 6:
            displayGoodbyeScreen();
            player.playSound("contributions_habib.wav");
            printContributors();
            cout << BOLD_GREEN << "Exiting the program. Goodbye!\n"
                << RESET;
            break;

        default:
            cout << BOLD_RED << "Invalid choice! Try again.\n"
                << RESET;
        }
    } while (mainChoice != 6);


    // Free memory allocated for flights
    delete[] flights;

    return 0;
}