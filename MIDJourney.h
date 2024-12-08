#ifndef MIDJOURNEY_H
#define MIDJOURNEY_H
#include"flight.h"
class JourneyNode
{
public:
    Flight data;
    JourneyNode *next;

    JourneyNode(Flight f)
    {
        data = f;
        next = nullptr;
    }
};
class Journey
{
public:
    JourneyNode *head; // Head of the linked list
    JourneyNode *tail; // Tail of the linked list

    Journey()
    {
        head = nullptr;
        tail = nullptr;
    }

    // Insert a new flight into the journey
    void insertFlight(Flight f)
    {
        JourneyNode *newNode = new JourneyNode(f);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void clearJourney()
    {
        JourneyNode *temp = head;
        while (temp)
        {
            JourneyNode *toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        tail = nullptr;
    }

    // Print the journey
    void printJourney()
    {        
        JourneyNode *temp = head;
        cout << "Planned Flights:" << endl;
        while (temp)
        {
            temp->data.display();
            temp = temp->next;
        }
    }
    
};

#endif