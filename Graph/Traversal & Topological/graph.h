#ifndef GRAPH_H_
#define GRAPH_H

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

//Declaration of node in the adjacent list implementation
class GEdge
{
public:
    int index; //index of the destination vertex of the edge
    int weight; // weight of the edge
    GEdge(int i = 0, int w = 0)
    {
        this->index = i;
        this->weight = w;
    }
};

//Declaration of the adjacent list implementation of a weighted undirected graph
class Graph
{
private:
    int nover;
    char* labels;
    Link<GEdge>* srclst;

public:
    Graph(char vertices[], int n)
    {
        this->nover = n;
        this->labels = vertices;
        this->srclst = new Link<GEdge>[n];
    }
    static void print()
    {

    }    
    void clear()
    {

    }
    ~Graph()
    {
        this->clear();
    }
    void BFS(char startlabel, void (Graph::*action)(int));
    void DFS(char startlabel, void (Graph::*action)(int));
    void topologicalSort(void (Graph::*action)(int));
};

#endif //GRAPH_H_