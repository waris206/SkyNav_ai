#ifndef GRAPH_H
#define GRAPH_H
#include "flight.h"

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
    void insert(string val)
    {
        node *newnode = new node();
        newnode->data.departureCity = val;
        if (head == nullptr)
        {
            head = newnode;
            tail = newnode;
        }
         
    }

    void insert(Flight F)
    {
        node *newnode = new node();
        newnode->data = F;

        tail->next = newnode;
        tail = newnode;
    }
    // simpel display of linkedlist
     void Display(){
         node *temp = head;
         while (temp!=nullptr)
         {
            if (temp == head)
            {
               cout << temp->data.departureCity << endl;
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
            cout << "Vertex " << ": ";
            arr[i].Display();
            cout << endl;
        }
    }
    void dijkstraByDate(string source, string destination) {
    // Map each city to an index
    string cityMap[vert];
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
        cout << "Source or destination city not found." << endl;
        return;
    }

    // Arrays for earliest dates, visited status, and parent tracking
    string earliestDate[vert];
    bool visited[vert];
    int parent[vert];

    // Initialize earliest dates to a very late date, visited to false, and parents to -1
    for (int i = 0; i < vert; i++) {
        earliestDate[i] = "2025-12-31"; // A far future date
        visited[i] = false;
        parent[i] = -1;
    }

    earliestDate[srcIdx] = "2018-01-01"; // Source starts with the earliest possible date

    for (int i = 0; i < vert; i++) {
        // Find the unvisited node with the earliest date
        string minDate = "2025-12-31";
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
                }
            }
            temp = temp->next;
        }
    }

    // Print the shortest path by date
    if (earliestDate[destIdx] == "9999-12-31") {
        cout << "No path exists from " << source << " to " << destination << endl;
        return;
    }

    cout << "Earliest Path from " << source << " to " << destination << " arrives on: " << earliestDate[destIdx] << endl;
    cout << "Path: ";
    int path[vert], pathLen = 0;
    for (int at = destIdx; at != -1; at = parent[at]) {
        path[pathLen++] = at;
    }
    for (int i = pathLen - 1; i >= 0; i--) {
        cout << cityMap[path[i]];
        if (i > 0) cout << " -> ";
    }
   cout <<endl;
}
void dijkstra(string source, string destination) {
    // Map each city to an index
    string cityMap[vert];
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
        cout << "Source or destination city not found." << endl;
        return;
    }

    // Arrays for distances, visited status, and parent tracking
    int distances[vert];
    bool visited[vert];
    int parent[vert];

    // Initialize distances to infinity, visited to false, and parents to -1
    for (int i = 0; i < vert; i++) {
        distances[i] = 1e9; // Large value representing infinity
        visited[i] = false;
        parent[i] = -1;
    }

    distances[srcIdx] = 0; // Distance to the source is 0

    for (int i = 0; i < vert; i++) {
        // Find the unvisited node with the smallest distance
        int minDist = 1e9, minIndex = -1;
        for (int j = 0; j < vert; j++) {
            if (!visited[j] && distances[j] < minDist) {
                minDist = distances[j];
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
                int newDist = distances[minIndex] + temp->data.price; // Use price as weight
                if (newDist < distances[neighborIndex]) {
                    distances[neighborIndex] = newDist;
                    parent[neighborIndex] = minIndex;
                }
            }
            temp = temp->next;
        }
    }

    // Print the shortest path and total price
    if (distances[destIdx] == 1e9) {
        cout << "No path exists from " << source << " to " << destination << endl;
        return;
    }

    cout << "Cheapest Path from " << source << " to " << destination << " costs: " << distances[destIdx] << endl;
    cout << "Path: ";
    int path[vert], pathLen = 0;
    for (int at = destIdx; at != -1; at = parent[at]) {
        path[pathLen++] = at;
    }
    for (int i = pathLen - 1; i >= 0; i--) {
        cout << cityMap[path[i]];
        if (i > 0) cout << " -> ";
    }
    cout<< endl;
}
   void drawGraph() {
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const int RADIUS = 200; // Radius of the circular layout
    const float CITY_RADIUS = 15.0f; // Radius of city circles
    const float ARROW_SIZE = 10.0f; // Size of arrowheads for directed edges

    // Create a window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Directed Flight Graph Visualization");

    // Calculate positions for each city in a circular layout
    sf::Vector2f* positions = new sf::Vector2f[vert];
    float centerX = WINDOW_WIDTH / 2.0f;
    float centerY = WINDOW_HEIGHT / 2.0f;
    float angleIncrement = 2 * M_PI / vert;

    for (int i = 0; i < vert; i++) {
        float angle = i * angleIncrement;
        positions[i].x = centerX + RADIUS * cos(angle);
        positions[i].y = centerY + RADIUS * sin(angle);
    }

    // Load a default font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Font not found. Make sure 'arial.ttf' is in the project directory." << endl;
        delete[] positions;
        return;
    }

    // Run the SFML visualization loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

        // Draw edges (directed flights)
        for (int i = 0; i < vert; i++) {
            node* temp = arr[i].head->next; // Skip the head node
            while (temp != nullptr) {
                // Find the index of the destination city
                int destIndex = -1;
                for (int j = 0; j < vert; j++) {
                    if (arr[j].head->data.departureCity == temp->data.destinationCity) {
                        destIndex = j;
                        break;
                    }
                }

                if (destIndex != -1) {
                    // Draw the line (edge)
                    sf::Vertex line[] = {
                        sf::Vertex(positions[i], sf::Color::Red),
                        sf::Vertex(positions[destIndex], sf::Color::Red)
                    };
                    window.draw(line, 2, sf::Lines);

                    // Draw the arrowhead
                    sf::Vector2f direction = positions[destIndex] - positions[i];
                    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
                    direction /= length; // Normalize

                    sf::Vector2f perpendicular(-direction.y, direction.x); // Perpendicular vector

                    sf::Vector2f arrowPoint1 = positions[destIndex] - direction * ARROW_SIZE + perpendicular * (ARROW_SIZE / 2);
                    sf::Vector2f arrowPoint2 = positions[destIndex] - direction * ARROW_SIZE - perpendicular * (ARROW_SIZE / 2);

                    sf::Vertex arrow[] = {
                        sf::Vertex(positions[destIndex], sf::Color::Red),
                        sf::Vertex(arrowPoint1, sf::Color::Red),
                        sf::Vertex(arrowPoint2, sf::Color::Red)
                    };
                    window.draw(arrow, 3, sf::Triangles);

                    // Check if mouse is near the edge (hover detection)
                    sf::Vector2f midPoint = (positions[i] + positions[destIndex]) / 2.0f;
                    if (sqrt(pow(mousePosF.x - midPoint.x, 2) + pow(mousePosF.y - midPoint.y, 2)) < 10.0f) {
                        // Display flight details
                        sf::Text flightDetails;
                        flightDetails.setFont(font);
                        flightDetails.setString(
                            "Flight: " + temp->data.airline + "\nPrice: " + to_string(temp->data.price) +
                            "\nDate: " + temp->data.date + "\nTime: " + temp->data.time1 + " - " + temp->data.time2);
                        flightDetails.setCharacterSize(15);
                        flightDetails.setFillColor(sf::Color::Black);
                        flightDetails.setPosition(mousePosF.x + 15, mousePosF.y + 15);
                        window.draw(flightDetails);
                    }
                }

                temp = temp->next;
            }
        }

        // Draw cities and their names
        for (int i = 0; i < vert; i++) {
            // Draw the city circle
            sf::CircleShape cityCircle(CITY_RADIUS);
            cityCircle.setFillColor(sf::Color::Blue);
            cityCircle.setPosition(positions[i].x - CITY_RADIUS, positions[i].y - CITY_RADIUS);
            window.draw(cityCircle);

            // Draw the city name
            sf::Text cityName(arr[i].head->data.departureCity, font, 15);
            cityName.setFillColor(sf::Color::Black);
            cityName.setPosition(positions[i].x + CITY_RADIUS + 5, positions[i].y - CITY_RADIUS);
            window.draw(cityName);
        }

        window.display();
    }

    delete[] positions; // Clean up dynamically allocated memory
}



};

#endif