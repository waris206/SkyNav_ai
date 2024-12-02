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
};

#endif