#ifndef GraphVisualizer_H
#define GraphVisualizer_H

#include "Graph.h"
#include <random>
#include <unordered_map>
#include <vector>
#include <cmath>

class FlightInfo {
public:
    std::vector<Flight> flights;

    void addFlight(const Flight& flight) {
        flights.push_back(flight);
    }

    void displayFlights() const {
        std::cout << "Flights:\n";
        for (const auto& flight : flights) {
            flight.display();
        }
    }
};

// Vertex and edge properties
struct Vertex {
    std::string name;
    sf::Vector2f position;
    //sf::CircleShape shape;
    sf::RectangleShape shape;
};

struct Edge {
    sf::Vertex line[2];
    sf::Color color;
    std::string source;
    std::string destination;
};

class GraphVisualizer {
private:
    // Screen dimensions
    const int SCREEN_WIDTH = 1792;
    const int SCREEN_HEIGHT = 1008;

    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    std::unordered_map<std::string, std::unordered_map<std::string, FlightInfo>> flightConnections;
    sf::RenderWindow window;
    sf::Font font;

    // Generate random color
    sf::Color getRandomColor() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> r(50, 200);
        std::uniform_int_distribution<> g(50, 200);
        std::uniform_int_distribution<> b(50, 200);
        return sf::Color(r(gen), g(gen), b(gen));
    }

    void arrangeVerticesCircularly() {
        float centerX = SCREEN_WIDTH / 2.0f;
        float centerY = SCREEN_HEIGHT / 2.0f;
        float radius = std::min(SCREEN_WIDTH, SCREEN_HEIGHT) * 0.4f;
        float angleStep = 2 * 3.14159f / vertices.size();

        for (size_t i = 0; i < vertices.size(); ++i) {
            float angle = i * angleStep;
            vertices[i].position = sf::Vector2f(
                centerX + radius * std::cos(angle),
                centerY + radius * std::sin(angle)
            );

            // Setup vertex shape as a rectangle
            vertices[i].shape.setSize({ 100.0, 30.0f });
            vertices[i].shape.setFillColor(sf::Color::Yellow);
            vertices[i].shape.setOutlineColor(sf::Color::Black);
            vertices[i].shape.setOutlineThickness(2);

            // Position the rectangle
            vertices[i].shape.setPosition(
                vertices[i].position.x - vertices[i].shape.getSize().x / 2.0f,
                vertices[i].position.y - vertices[i].shape.getSize().y / 2.0f
            );
        }
    }

    // Draw text for vertex names
    void drawVertexNames(sf::RenderWindow& window) {
        for (const auto& vertex : vertices) {
            sf::Text text;
            text.setFont(font);
            text.setString(vertex.name);
            text.setCharacterSize(16);
            text.setFillColor(sf::Color::Black);    // vertex text color

            // Center the text on the vertex
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                textBounds.top + textBounds.height / 2.0f);
            text.setPosition(vertex.position);

            window.draw(text);
        }
    }

    // Check if mouse is near an edge
    Edge* findNearestEdge(const sf::Vector2f& mousePos) {
        for (auto& edge : edges) {
            // Create a line segment
            sf::Vector2f lineVec = edge.line[1].position - edge.line[0].position;
            sf::Vector2f perpVec(-lineVec.y, lineVec.x);
            perpVec /= std::sqrt(perpVec.x * perpVec.x + perpVec.y * perpVec.y);

            // Calculate distance from mouse to line
            float dist = std::abs((mousePos - edge.line[0].position).x * perpVec.x +
                (mousePos - edge.line[0].position).y * perpVec.y);

            // Check if mouse is close to the line and within line segment
            if (dist < 10.0f) {
                return &edge;
            }
        }
        return nullptr;
    }

    sf::VertexArray createFlightPath(const sf::Vector2f& start, const sf::Vector2f& end) {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = start;
        line[1].position = end;
        line[0].color = sf::Color::Red;
        line[1].color = sf::Color::Red;
        return line;
    }

    sf::Vector2f getCityPosition(const string& cityName) {
        // Implement this function to return the position of the city on your map
        // You might need to have a predefined mapping of cities to coordinates
        // For example:
        if (cityName == "New York") return sf::Vector2f(100, 100);
        if (cityName == "London") return sf::Vector2f(300, 200);
        // ... add more cities as needed
        return sf::Vector2f(0, 0); // Default position if city not found
    }

public:
    GraphVisualizer(const std::string* uniqueCities, int numCities) :
        window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Airline Network Graph") {



        // Load font
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error loading font" << std::endl;
        }

        // Create vertices
        for (int i = 0; i < numCities; ++i) {
            Vertex v;
            v.name = uniqueCities[i];
            vertices.push_back(v);
        }

        // Arrange vertices in a circular layout
        arrangeVerticesCircularly();
    }

    // Add flight connections as edges with detailed flight information
    void addEdge(const std::string& src, const std::string& dest, const Flight& flight) {
        // Find source and destination vertices
        sf::Vector2f srcPos, destPos;
        bool srcFound = false, destFound = false;

        for (const auto& vertex : vertices) {
            if (vertex.name == src) {
                srcPos = vertex.position;
                srcFound = true;
            }
            if (vertex.name == dest) {
                destPos = vertex.position;
                destFound = true;
            }
        }

        // Only add edge if both vertices exist
        if (srcFound && destFound) {
            Edge edge;
            edge.line[0] = sf::Vertex(srcPos);
            edge.line[1] = sf::Vertex(destPos);

            // Random color for each edge
            edge.color = getRandomColor();
            edge.line[0].color = edge.color;
            edge.line[1].color = edge.color;

            // Set source and destination
            edge.source = src;
            edge.destination = dest;

            edges.push_back(edge);

            // Store flight information
            flightConnections[src][dest].addFlight(flight);
        }
    }

    void visualizeDirectFlight(const Flight& flight) {
        sf::Vector2f startPos = getCityPosition(flight.departureCity);
        sf::Vector2f endPos = getCityPosition(flight.destinationCity);

        sf::VertexArray flightPath = createFlightPath(startPos, endPos);
        window.draw(flightPath);
    }

    void visualizeConnectingFlights(const Flight& flight1, const Flight& flight2) {
        sf::Vector2f startPos = getCityPosition(flight1.departureCity);
        sf::Vector2f transitPos = getCityPosition(flight1.destinationCity); // Same as flight2.departureCity
        sf::Vector2f endPos = getCityPosition(flight2.destinationCity);

        sf::VertexArray flightPath1 = createFlightPath(startPos, transitPos);
        sf::VertexArray flightPath2 = createFlightPath(transitPos, endPos);

        window.draw(flightPath1);
        window.draw(flightPath2);
    }

    // Main rendering loop
    void render() {
        sf::Text flightInfoText;
        flightInfoText.setFont(font);
        flightInfoText.setCharacterSize(14);
        flightInfoText.setFillColor(sf::Color::Magenta);
        flightInfoText.setPosition(10, SCREEN_HEIGHT - 300);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    return;

                // Handle mouse move to show flight info
                if (event.type == sf::Event::MouseMoved) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    Edge* nearestEdge = findNearestEdge(mousePos);

                    if (nearestEdge) {
                        // Prepare flight info text
                        std::string infoText = "Flights from " + nearestEdge->source + " -> " + nearestEdge->destination + ":\n";
                        for (const auto& flight : flightConnections[nearestEdge->source][nearestEdge->destination].flights) {
                            infoText += "Date: " + flight.date +
                                ", Time: " + flight.time1 + "-" + flight.time2 +
                                ", Price: " + std::to_string(flight.price) +
                                ", Airline: " + flight.airline + "\n";
                        }

                        infoText += "\nFlights from " + nearestEdge->destination + " -> " + nearestEdge->source + ":\n";
                        for (const auto& flight : flightConnections[nearestEdge->destination][nearestEdge->source].flights) {
                            infoText += "Date: " + flight.date +
                                ", Time: " + flight.time1 + "-" + flight.time2 +
                                ", Price: " + std::to_string(flight.price) +
                                ", Airline: " + flight.airline + "\n";
                        }

                        flightInfoText.setString(infoText);
                    }
                }
            }

            window.clear(sf::Color(0, 0, 0)); // black background

            // Draw edges
            for (const auto& edge : edges) {
                window.draw(edge.line, 2, sf::Lines);
            }

            // Draw vertices
            for (const auto& vertex : vertices) {
                window.draw(vertex.shape);
            }

            // Draw vertex names
            drawVertexNames(window);

            // Draw flight info text
            window.draw(flightInfoText);
            window.display();
        }
    }

};



#endif // !GraphVisualizer_H
