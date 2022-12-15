#ifndef LIST_GRAPH_H_
#define LIST_GRAPH_H_

#include <iostream>

using namespace std;

template<class T>
class Link
{
public:
    T element;
    Link* next;

public:
    Link(const T& elemval, Link* nextval = nullptr)
    {
        this->element = elemval;
        this->next = nextval;
    }
    Link(Link* nextval = nullptr)
    {
        this->next = nextval;
    }
};

//Declaration of node in the adjacent list
class GEdge
{
public:
    char label; // label of the destination vertex of the edge
    int weight; // weight of the edge
    GEdge(char l = '\0', int w = 0)
    {
        this->label = l;
        this->weight = w;
    }
};

struct Edge;

class Graph
{
private:
    int nover;
    Link<GEdge>* srclst;

public:
    Graph(char vertices[], int n)
    {
        this->nover = n;
        this->srclst = new Link<GEdge>[n];
        for (int i = 0; i < n; ++i)
        {
            srclst[i].element.label = vertices[i];
        }
    }
    void printGraph()
    {
        for (int i = 0; i < nover; ++i)
        {
            Link<GEdge>* temp = srclst[i].next;
            while (temp)
            {
                cout << "from " << srclst[i].element.label << " to " << temp->element.label << " weight "
                    << temp->element.weight << endl;
                temp = temp->next; 
            }
        }
    }
    void clear()
    {
        for (int i = 0; i < nover; ++i)
        {
            Link<GEdge>* temp = &srclst[i];
            while (temp)
            {
                Link<GEdge>* dlt = temp;
                temp = temp->next;
                delete dlt;
                dlt = nullptr;
            }
        }
        this->nover = 0;
        this->srclst = nullptr;
    }
    ~Graph()
    {
        this->clear();
    }
    void addEdge(struct Edge edges[], int n);
};

#endif //LIST_GRAPH_H_