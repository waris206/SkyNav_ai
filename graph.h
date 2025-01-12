#ifndef GRAPH_H
#define GRAPH_H
#include "flight.h"
#include "color.h"
#include"MIDJourney.h"
#include <iostream>
using namespace std;

class node
{
public:
    Flight data;
    node *next;
    node() { next = nullptr; }
};
class AdjLst
{
public:
    node *head;
    node *tail;
    int charges;

    void insert(string val)
    {
        node *newnode = new node();
        newnode->data.departureCity = val;
        if (head == nullptr)
        {
            head = newnode;
            tail = newnode;
            charges = getCharges(val);
        }
    }

    void insert(Flight F)
    {
        node *newnode = new node();
        newnode->data = F;

        /*
        if (head == nullptr)
        {
            head = newnode;
            tail = newnode;
            charges = getCharges(F)
        }
        */

        tail->next = newnode;
        tail = newnode;
    }

    int getCharges(string val)
    {
        ifstream file("HotelCharges_perday.txt"); // File containing the city and charge data
        if (!file.is_open())
        {
            cerr << "\033[1;31mUnable to open the file.\033[0m" << endl;
            return -1;
        }

        string line, city;
        int charge;

        while (getline(file, line))
        {
            stringstream iss(line);
            iss >> city >> charge; // Extract city and charge from each line
            if (city == val)
            {
                file.close(); // Close the file once the value is found
                return charge;
            }
        }

        file.close(); // Close the file if the city isn't found.
        return -1;
    }

    AdjLst *findFlight(string dest)
    {
        node *temp = head;
        AdjLst *Nodelist = new AdjLst();
        Nodelist->insert(this->head->data.departureCity);

        while (temp)
        {
            if (dest == temp->data.destinationCity)
            {
                // if (!Nodelist) {Nodelist = new AdjLst();}
                Nodelist->insert(temp->data);
            }
            temp = temp->next;
        }
        return Nodelist;
    }

    AdjLst *findFlight(string dest, string airline)
    {
        node *temp = head;
        AdjLst *Nodelist = new AdjLst();
        Nodelist->insert(this->head->data.departureCity);

        while (temp)
        {
            if (dest == temp->data.destinationCity && airline == temp->data.airline)
            {
                // if (!Nodelist) {Nodelist = new AdjLst();}
                Nodelist->insert(temp->data);
            }
            temp = temp->next;
        }
        return Nodelist;
    }

    // simpel display of linkedlist
    void Display()
    {
        node *temp = head;
        while (temp != nullptr)
        {
            if (temp == head)
            {
                cout << "\033[1;34m" << temp->data.departureCity << " \033[1;32m" << charges << "\033[0m" << endl;
                temp = temp->next;
                continue;
            }

            temp->data.display();
            temp = temp->next;
        }
    }
    AdjLst()
    {
        head = nullptr;
        tail = nullptr;
    }
    // we need to update in future a fucntion names IsRepititve()
};
class Graph
{
public:
    AdjLst *arr;
    int vert;
    Graph(string *Unique_Cities, int size)
    {
        arr = new AdjLst[size];
        vert = size;
        // put as vertices
        for (int i = 0; i < vert; i++)
        {
            arr[i].insert(Unique_Cities[i]);
        }
    }
    void insertEdge(Flight f)
    {
        for (int i = 0; i < vert; i++)
        {
            if (arr[i].head->data.departureCity == f.departureCity)
            {
                arr[i].insert(f);
            }
        }
    }
    void showGraphStructure()
    {
        for (int i = 0; i < vert; i++)
        {
            cout << "\033[1;36mVertex " << i << " : \033[0m";
            arr[i].Display();
            cout << endl;
        }
    }

    Journey* dijkstraByDate(string source, string destination) {
        Journey* journey = new Journey();
        // Map each city to an index
        string* cityMap = new string[vert];
        for (int i = 0; i < vert; i++) {
            cityMap[i] = arr[i].head->data.departureCity;
        }
        // Find indices for source and destination
        int srcIdx = -1, destIdx = -1;
        for (int i = 0; i < vert; i++) {
            if (cityMap[i] == source) srcIdx = i;
            if (cityMap[i] == destination) destIdx = i;
        }
        if (srcIdx == -1 || destIdx == -1) {
            cout << "\033[1;31mSource or destination city not found.\033[0m" << endl;
            return NULL;
        }
        // Arrays for earliest dates, visited status, and parent tracking
        string* earliestDate = new string[vert];
        bool* visited = new bool[vert];
        int* parent = new int[vert];
        Flight* parentFlight = new Flight[vert]; // Store the actual flight for each path segment

        // Initialize earliest dates to a very late date, visited to false, and parents to -1
        for (int i = 0; i < vert; i++) {
            earliestDate[i] = "9999-12-31"; // A far future date
            visited[i] = false;
            parent[i] = -1;
        }
        earliestDate[srcIdx] = "0000-01-01"; // Source starts with the earliest possible date
        for (int i = 0; i < vert; i++) {
            // Find the unvisited node with the earliest date
            string minDate = "9999-12-31";
            int minIndex = -1;
            for (int j = 0; j < vert; j++) {
                if (!visited[j] && earliestDate[j] < minDate) {
                    minDate = earliestDate[j];
                    minIndex = j;
                }
            }
            if (minIndex == -1) break; // No more reachable nodes
            visited[minIndex] = true;
            // Relax the edges from the current node
            node* temp = arr[minIndex].head->next;
            while (temp != nullptr) {
                int neighborIndex = -1;
                for (int k = 0; k < vert; k++) {
                    if (cityMap[k] == temp->data.destinationCity) {
                        neighborIndex = k;
                        break;
                    }
                }
                if (neighborIndex != -1 && !visited[neighborIndex]) {
                    // Check if the current flight's date is earlier
                    if (temp->data.date > earliestDate[minIndex] && temp->data.date < earliestDate[neighborIndex]) {
                        earliestDate[neighborIndex] = temp->data.date;
                        parent[neighborIndex] = minIndex;
                        parentFlight[neighborIndex] = temp->data; // Store the actual flight
                    }
                }
                temp = temp->next;
            }
        }
        // Check if a path exists
        if (earliestDate[destIdx] == "9999-12-31") {
            cout << "\033[1;31mNo path exists from " << source << " to " << destination << "\033[0m" << endl;
            return NULL;
        }

        // Print the shortest path by date
        cout << "\033[1;32mEarliest Path from " << source << " to " << destination
            << " arrives on: " << earliestDate[destIdx] << "\033[0m" << endl;
        cout << "\033[1;33mPath: \033[0m";

        int pathLen = 0;
        int* path = new int[vert];
        for (int at = destIdx; at != -1; at = parent[at]) {
            path[pathLen++] = at;
        }

        // Insert flights into the journey and print path
        for (int i = pathLen - 1; i > 0; i--) {
            journey->insertFlight(parentFlight[path[i-1]]);

            // Print path
            cout << "\033[1;34m" << cityMap[path[i]] << "\033[0m" << " \033[1;33m-> \033[0m";
        }
        // Print final destination
        cout << "\033[1;34m" << cityMap[path[0]] << "\033[0m" << endl;

        return journey;
    }

    Journey* dijkstra(string source, string destination)
    {
        Journey* journey = new Journey();
        // Map each city to an index
        string* cityMap = new string[vert];
        for (int i = 0; i < vert; i++)
        {
            cityMap[i] = arr[i].head->data.departureCity;
        }
        // Find indices for source and destination
        int srcIdx = -1, destIdx = -1;
        for (int i = 0; i < vert; i++)
        {
            if (cityMap[i] == source)
                srcIdx = i;
            if (cityMap[i] == destination)
                destIdx = i;
        }
        if (srcIdx == -1 || destIdx == -1)
        {
            cout << "\033[1;31mSource or destination city not found.\033[0m" << endl;
            return NULL; // returns null invalid src / des
        }
        // Arrays for distances, visited status, and parent tracking
        int* distances = new int[vert];
        bool* visited = new bool[vert];
        int* parent = new int[vert];
        // Initialize distances to infinity, visited to false, and parents to -1
        for (int i = 0; i < vert; i++)
        {
            distances[i] = 1e9; // Large value representing infinity
            visited[i] = false;
            parent[i] = -1;
        }
        distances[srcIdx] = 0; // Distance to the source is 0
        for (int i = 0; i < vert; i++)
        {
            // Find the unvisited node with the smallest distance
            int minDist = 1e9, minIndex = -1;
            for (int j = 0; j < vert; j++)
            {
                if (!visited[j] && distances[j] < minDist)
                {
                    minDist = distances[j];
                    minIndex = j;
                }
            }
            if (minIndex == -1)
                break; // No more reachable nodes
            visited[minIndex] = true;
            // Relax the edges from the current node
            node* temp = arr[minIndex].head->next;
            while (temp != nullptr)
            {
                int neighborIndex = -1;
                for (int k = 0; k < vert; k++)
                {
                    if (cityMap[k] == temp->data.destinationCity)
                    {
                        neighborIndex = k;
                        break;
                    }
                }
                if (neighborIndex != -1 && !visited[neighborIndex])
                {
                    int newDist = distances[minIndex] + temp->data.price; // Use price as weight
                    if (newDist < distances[neighborIndex])
                    {
                        distances[neighborIndex] = newDist;
                        parent[neighborIndex] = minIndex;
                    }
                }
                temp = temp->next;
            }
        }
        // Print the shortest path and total price
        if (distances[destIdx] == 1e9)
        {
            cout << "\033[1;31mNo path exists from " << source << " to " << destination << "\033[0m" << endl;
            return NULL;
        }
        cout << "\033[1;32mCheapest Path from " << source << " to " << destination << " costs: " << distances[destIdx] << "\033[0m" << endl;
        cout << "\033[1;33mPath: \033[0m";
        int pathLen = 0;
        int* path = new int[vert];
        for (int at = destIdx; at != -1; at = parent[at])
        {
            path[pathLen++] = at;
        }

        // Find the actual flight details for each path segment
        for (int i = pathLen - 1; i > 0; i--)
        {
            // Find the flight connecting the current two cities
            node* temp = arr[path[i]].head->next;
            while (temp != nullptr)
            {
                if (temp->data.destinationCity == cityMap[path[i - 1]])
                {
                    // Insert the flight with its actual details
                    journey->insertFlight(temp->data);
                    break;
                }
                temp = temp->next;
            }

            // Print path
            cout << "\033[1;34m" << cityMap[path[i]] << "\033[0m" << " \033[1;33m-> \033[0m";
        }
        // Print final destination
        cout << "\033[1;34m" << cityMap[path[0]] << "\033[0m" << endl;

        delete[] cityMap;
        delete[] distances;
        delete[] visited;
        delete[] parent;
        delete[] path;
        return journey;
    }

    // for bokkign of flight
    AdjLst* directFlight(string src, string des)
    {
        for (int i = 0; i < vert; i++)
        {
            if (arr[i].head->data.departureCity == src)
            {
                AdjLst *possibleDirectFlights = arr[i].findFlight(des);
                if (possibleDirectFlights->head->next)
                {
                    cout << "\033[1;32mDirect flights from " << src << " to " << des << ":\033[0m\n";
                    possibleDirectFlights->Display();
                    return possibleDirectFlights;
                }
                else
                {
                    cout << "\033[1;31mNo direct flight from " << src << " to " << des << "\033[0m\n";
                    return nullptr;
                }
            }
        }
    }

    Journey* directFlight_withDate(string src, string des, string d)
    {
        Journey* returnList = new Journey();

        for (int i = 0; i < vert; i++)
        {
            if (arr[i].head->data.departureCity == src)
            {
                node *temp = arr[i].head->next;
                bool flight_found = false;
                while (temp)
                {
                    if (temp->data.destinationCity == des && temp->data.date == d)
                    {
                        cout << "\033[1;32mDirect flight found from " << src << " to " << des << " on " << d << ":\033[0m\n";
                        temp->data.display();
                        returnList->insertFlight(temp->data);
                        flight_found = true;
                    }
                    temp = temp->next;
                }
                if (!flight_found)
                {
                    cout << "\033[1;31mNo direct flight found from " << src << " to " << des << " on " << d << "\033[0m\n";
                    return NULL;
                }
                return returnList;
            }
        }
        cout << "\033[1;31mNo direct flight found from " << src << " to " << des << "\033[0m\n";
        return NULL;
    }

    Journey* directFlight_withAIRLINE(string src, string des, string AIRLINE)
    {
        Journey* returnList = new Journey();
        for (int i = 0; i < vert; i++)
        {
            if (arr[i].head->data.departureCity == src)
            {
                node *temp = arr[i].head->next;
                bool flight_found = false;
                while (temp)
                {
                    if (temp->data.destinationCity == des && temp->data.airline == AIRLINE)
                    {
                        cout << "\033[1;32mDirect flight found from " << src << " to " << des << " on " << AIRLINE << ":\033[0m\n";
                        temp->data.display();
                        returnList->insertFlight(temp->data);
                        flight_found = true;
                    }
                    temp = temp->next;
                }
                if (!flight_found)
                {
                    cout << "\033[1;31mNo direct flight found from " << src << " to " << des << " on " << AIRLINE << "\033[0m\n";
                    return NULL;
                }
                return returnList;
            }
        }
        cout << "\033[1;31mNo direct flight found from " << src << " to " << des << "\033[0m\n";
        return NULL;
    }

    // fucntion to have transit between . two locations.. and after find inter location we ask from user also after showing
    Journey* transitFlight(string src, string inter, string des)
    {
        Journey* returnList = new Journey();
        for (int i = 0; i < vert; i++)
        {
            if (arr[i].head->data.departureCity == src)
            {
                node *first_half = arr[i].head->next; // First half of the journey
                while (first_half)
                {
                    if (first_half->data.destinationCity == inter)
                    {
                        // Find the second half...
                        for (int j = 0; j < vert; j++)
                        {
                            if (arr[j].head->data.departureCity == inter)
                            {
                                node *second_half = arr[j].head->next;
                                while (second_half)
                                {
                                    if (second_half->data.destinationCity == des &&
                                        second_half->data.time1 > first_half->data.time2 && second_half->data.date == first_half->data.date)
                                    {

                                        cout << "\033[1;32mTransit Flight Found:\033[0m\n";
                                        cout << "\033[1;33mFirst Half:\033[0m\n";
                                        first_half->data.display();
                                        returnList->insertFlight(first_half->data);
                                        cout << "\033[1;33mSecond Half:\033[0m\n";
                                        second_half->data.display();
                                        returnList->insertFlight(second_half->data);
                                        return returnList;
                                    }
                                    else if (second_half->data.destinationCity == des &&
                                             second_half->data.date > first_half->data.date)
                                    {
                                        cout << "\033[1;32mTransit Flight Found:\033[0m\n";
                                        cout << "\033[1;33mFirst Half:\033[0m\n";
                                        first_half->data.display();
                                        returnList->insertFlight(first_half->data);
                                        cout << "\033[1;33mSecond Half:\033[0m\n";
                                        second_half->data.display();
                                        returnList->insertFlight(second_half->data);
                                        return returnList;
                                    }

                                    second_half = second_half->next;
                                }
                            }
                        }
                    }
                    first_half = first_half->next;
                }
            }
        }

        cout << "\033[1;31mNo transit flight found from " << src << " to " << des << " via " << inter << "\033[0m\n";
        return NULL;
    }

    // now we have trasnit function with airline if someone want same flight airline
    Journey* transitFlight_airline_matters(string src, string inter, string des, string air)
    {
        Journey* returnList = new Journey();
        for (int i = 0; i < vert; i++)
        {
            if (arr[i].head->data.departureCity == src)
            {
                node *first_half = arr[i].head->next; // First half of the journey
                while (first_half)
                {
                    if (first_half->data.destinationCity == inter && first_half->data.airline == air)
                    {
                        // Find the second half...
                        for (int j = 0; j < vert; j++)
                        {
                            if (arr[j].head->data.departureCity == inter)
                            {
                                node *second_half = arr[j].head->next;
                                while (second_half)
                                {
                                    if (second_half->data.destinationCity == des && second_half->data.airline == air)
                                    {

                                        if (second_half->data.time1 > first_half->data.time2 && second_half->data.date == first_half->data.date && second_half->data.time1.size() >= first_half->data.time2.size())
                                        {
                                            cout << "\033[1;32mTransit Flight Found:\033[0m\n";
                                            cout << "\033[1;33mFirst Half:\033[0m\n";
                                            first_half->data.display();
                                            returnList->insertFlight(first_half->data);
                                            cout << "\033[1;33mSecond Half:\033[0m\n";
                                            second_half->data.display();
                                            returnList->insertFlight(second_half->data);
                                            return returnList;
                                        }
                                        else if (second_half->data.date > first_half->data.date)
                                        {
                                            cout << "\033[1;32mTransit Flight Found:\033[0m\n";
                                            cout << "\033[1;33mFirst Half:\033[0m\n";
                                            first_half->data.display();
                                            returnList->insertFlight(first_half->data);
                                            cout << "\033[1;33mSecond Half:\033[0m\n";
                                            second_half->data.display();
                                            returnList->insertFlight(second_half->data);
                                            return returnList;
                                        }
                                    }

                                    second_half = second_half->next;
                                }
                            }
                        }
                    }
                    first_half = first_half->next;
                }
            }
        }

        cout << "\033[1;31mNo transit flight found from " << src << " to " << des << " via " << inter << " with airline " << air << "\033[0m\n";
        return NULL;
    }
    /****************************************************MID JOURNEY **************************** */
    Journey* planMultiLegJourney(string source, string stops[], int numStops, string destination)
    {
        Journey* journey = new Journey();
        string currentCity = source;


        for (int i = 0; i <= numStops; i++)
        {
            string nextCity = (i == numStops) ? destination : stops[i];

            bool flightFound = false;


            for (int j = 0; j < vert; j++)
            {
                if (arr[j].head->data.departureCity == currentCity)
                {
                    node* temp = arr[j].head->next;
                    while (temp)
                    {
                        if (temp->data.destinationCity == nextCity)
                        {

                            if (!journey->head || temp->data.date > journey->tail->data.date)
                            {
                                journey->insertFlight(temp->data);
                                flightFound = true;
                                break;
                            }
                            else if (temp->data.date == journey->tail->data.date && temp->data.time1.size() > journey->tail->data.time2.size()) 
                            {
                                journey->insertFlight(temp->data);
                                flightFound = true;
                                break;
                            }

                        }
                        temp = temp->next;
                    }
                }

                if (flightFound)
                    break;
            }

            // If no flight is found for the current segment
            if (!flightFound)
            {
                cout << RED << "No valid flight from " << currentCity << " to " << nextCity << RESET << endl;
                journey->clearJourney(); // Cleanup
                return journey;
            }

            currentCity = nextCity; // Move to the next city
        }

        return journey; // Return the completed journey
    }

};


#endif