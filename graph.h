#ifndef GRAPH_H
#define GRAPH_H
#include "flight.h"
#include "color.h"
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
    void dijkstraByDate(string source, string destination)
    {
        // Map each city to an index
        string cityMap[vert];
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
            return;
        }

        // Arrays for earliest dates, visited status, and parent tracking
        string earliestDate[vert];
        bool visited[vert];
        int parent[vert];

        // Initialize earliest dates to a very late date, visited to false, and parents to -1
        for (int i = 0; i < vert; i++)
        {
            earliestDate[i] = "9999-12-31"; // A far future date
            visited[i] = false;
            parent[i] = -1;
        }

        earliestDate[srcIdx] = "0000-01-01"; // Source starts with the earliest possible date

        for (int i = 0; i < vert; i++)
        {
            // Find the unvisited node with the earliest date
            string minDate = "9999-12-31";
            int minIndex = -1;
            for (int j = 0; j < vert; j++)
            {
                if (!visited[j] && earliestDate[j] < minDate)
                {
                    minDate = earliestDate[j];
                    minIndex = j;
                }
            }

            if (minIndex == -1)
                break; // No more reachable nodes
            visited[minIndex] = true;

            // Relax the edges from the current node
            node *temp = arr[minIndex].head->next;
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
                    // Check if the current flight's date is earlier
                    if (temp->data.date > earliestDate[minIndex] && temp->data.date < earliestDate[neighborIndex])
                    {
                        earliestDate[neighborIndex] = temp->data.date;
                        parent[neighborIndex] = minIndex;
                    }
                }
                temp = temp->next;
            }
        }

        // Print the shortest path by date
        if (earliestDate[destIdx] == "9999-12-31")
        {
            cout << "\033[1;31mNo path exists from " << source << " to " << destination << "\033[0m" << endl;
            return;
        }

        cout << "\033[1;32mEarliest Path from " << source << " to " << destination << " arrives on: " << earliestDate[destIdx] << "\033[0m" << endl;
        cout << "\033[1;33mPath: \033[0m";
        int path[vert], pathLen = 0;
        for (int at = destIdx; at != -1; at = parent[at])
        {
            path[pathLen++] = at;
        }
        for (int i = pathLen - 1; i >= 0; i--)
        {
            cout << "\033[1;34m" << cityMap[path[i]] << "\033[0m";
            if (i > 0)
                cout << " \033[1;33m-> \033[0m";
        }
        cout << endl;
    }
    void dijkstra(string source, string destination)
    {
        // Map each city to an index
        string cityMap[vert];
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
            return;
        }

        // Arrays for distances, visited status, and parent tracking
        int distances[vert];
        bool visited[vert];
        int parent[vert];

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
            node *temp = arr[minIndex].head->next;
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
            return;
        }

        cout << "\033[1;32mCheapest Path from " << source << " to " << destination << " costs: " << distances[destIdx] << "\033[0m" << endl;
        cout << "\033[1;33mPath: \033[0m";
        int path[vert], pathLen = 0;
        for (int at = destIdx; at != -1; at = parent[at])
        {
            path[pathLen++] = at;
        }
        for (int i = pathLen - 1; i >= 0; i--)
        {
            cout << "\033[1;34m" << cityMap[path[i]] << "\033[0m";
            if (i > 0)
                cout << " \033[1;33m-> \033[0m";
        }
        cout << endl;
    }

    // for bokkign of flight
    void directFlight(string src, string des)
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
                }
                else
                {
                    cout << "\033[1;31mNo direct flight from " << src << " to " << des << "\033[0m\n";
                }
                return;
            }
        }
    }

    void directFlight_withDate(string src, string des, string d)
    {
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
                        flight_found = true;
                    }
                    temp = temp->next;
                }
                if (!flight_found)
                {
                    cout << "\033[1;31mNo direct flight found from " << src << " to " << des << " on " << d << "\033[0m\n";
                }
                return;
            }
        }
        cout << "\033[1;31mNo direct flight found from " << src << " to " << des << "\033[0m\n";
    }

    void directFlight_withAIRLINE(string src, string des, string AIRLINE)
    {
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
                        flight_found = true;
                    }
                    temp = temp->next;
                }
                if (!flight_found)
                {
                    cout << "\033[1;31mNo direct flight found from " << src << " to " << des << " on " << AIRLINE << "\033[0m\n";
                }
                return;
            }
        }
        cout << "\033[1;31mNo direct flight found from " << src << " to " << des << "\033[0m\n";
    }

    // fucntion to have transit between . two locations.. and after find inter location we ask from user also after showing
    bool transitFlight(string src, string inter, string des)
    {

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
                                        second_half->data.time1 > first_half->data.time2 and second_half->data.date >first_half->data.date)
                                    {

                                        cout << "\033[1;32mTransit Flight Found:\033[0m\n";
                                        cout << "\033[1;33mFirst Half:\033[0m\n";
                                        first_half->data.display();
                                        cout << "\033[1;33mSecond Half:\033[0m\n";
                                        second_half->data.display();
                                        return true;
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
        return false;
    }

    // now we have trasnit function with airline if someone want same flight airline
    bool transitFlight_airline_matters(string src, string inter, string des, string air)
    {

        for (int i = 0; i < vert; i++)
        {
            if (arr[i].head->data.departureCity == src)
            {
                node *first_half = arr[i].head->next; // First half of the journey
                while (first_half)
                {
                    if (first_half->data.destinationCity == inter and first_half->data.airline == air)
                    {
                        // Find the second half...
                        for (int j = 0; j < vert; j++)
                        {
                            if (arr[j].head->data.departureCity == inter)
                            {
                                node *second_half = arr[j].head->next;
                                while (second_half)
                                {
                                    if (second_half->data.destinationCity == des and second_half->data.airline == air)
                                    {

                                        cout << "\033[1;32mTransit Flight Found with Airline " << air << ":\033[0m\n";
                                        cout << "\033[1;33mFirst Half:\033[0m\n";
                                        first_half->data.display();
                                        cout << "\033[1;33mSecond Half:\033[0m\n";
                                        second_half->data.display();
                                        return true;
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
        return false;
    }
};

#endif