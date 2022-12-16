#ifndef GRAPH_H_
#define GRAPH_H

#include <iostream>
#include <vector>

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
    void addEdge_Undirect(int i, int j)
    {
        Link<GEdge>* e1 = new Link<GEdge>(GEdge(j));
        Link<GEdge>* e2 = new Link<GEdge>(GEdge(i));
        Link<GEdge>* temp1 = &srclst[i];
        Link<GEdge>* temp2 = &srclst[j];
        while (temp1->next && j > temp1->next->element.index)
        {
            temp1 = temp1->next;
        }
        e1->next = temp1->next;
        temp1->next = e1;
        while (temp2->next && i > temp2->next->element.index)
        {
            temp2 = temp2->next;
        }
        e2->next = temp2->next;
        temp2->next = e2;
    }
    void addEdge_Direct(int i, int j)
    {
        Link<GEdge>* e = new Link<GEdge>(GEdge(j));
        Link<GEdge>* temp = &srclst[i];
        while (temp->next && j > temp->next->element.index)
        {
            temp = temp->next;
        }
        e->next = temp->next;
        temp->next = e;
    }
    void print(int index)
    {
        cout << labels[index] << endl;
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
        delete[] srclst;
        this->srclst = nullptr;
        this->labels = nullptr;
        this->nover = 0;
    }
    ~Graph()
    {
        this->clear();
    }
    void BFS(char startlabel, void (Graph::*action)(int));
    void DFS(char startlabel, void (Graph::*action)(int));
    void topologicalSort(void (Graph::*action)(int));
};

//Abstract queue class
template<class T>
class Queue
{
private:
    void operator=(const Queue&) {} // Protect assignment
    Queue(const Queue&) {} // Protect copy constructor

public:
    Queue() {}
    virtual ~Queue() {}
    virtual void clear() = 0;
    virtual void enqueue(const T&) = 0;
    virtual T dequeue() = 0;
    virtual const T& frontValue() const = 0;
    virtual int length() const = 0;
};

//Linked queue implementation
template<class T>
class LQueue : public Queue<T>
{
private:
    Link<T>* front; //Pointer to front queue node
    Link<T>* rear; // Pointer to rear queue node
    int size;

public:
    LQueue()
    {
        front = rear = nullptr;
        size = 0;
    }
    ~LQueue()
    {
        this->clear();
    }
    void clear()
    {
        while (front)
        {
            rear = front;
            front = front->next;
            delete rear;
        }
        rear = nullptr;
        size = 0;
    }
    void enqueue(const T& it)
    {
        if (!size)
        {
            front = rear = new Link<T>(it);
        }
        else
        {
            rear->next = new Link<T>(it);
            rear = rear->next;
        }
        ++size;
    }
    T dequeue()
    {
        if (!size)
        {
            throw "Queue is empty";
        }
        T it = front->element;
        Link<T>* temp = front;
        if (rear == temp)
        {
            rear = nullptr;
        }
        front = front->next;
        delete temp;
        --size;
        return it;
    }
    const T& frontValue() const
    {
        if (!size)
        {
            throw "Queue is empty";
        }
        return front->element;
    }
    int length() const
    {
        return size;
    }
};

//Stack abstract class
template<class T>
class Stack
{
private:
    void operator=(const Stack&) {} //Protect assignment
    Stack(const Stack&) {}          // Protect copy constructor

public:
    Stack() {}
    virtual ~Stack() {}
    virtual void clear() = 0;
    virtual void push(const T& it) = 0;
    virtual T pop() = 0;
    virtual const T& topValue() const = 0;
    virtual int length() const = 0;
};

//Array-base stack implementation
template<class T>
class AStack : public Stack<T>
{
private:
    int maxSize;
    int top;
    T* listArray;

public:
    AStack(int size = 10)
    {
        this->maxSize = size;
        this->top = -1;
        this->listArray = new T[size];
    }
    ~AStack()
    {
        this->clear();
    }
    void clear()
    {
        this->maxSize = 0;
        this->top = -1;
        delete[] listArray;
        this->listArray = nullptr;
    }
    void push(const T& it)
    {
        if (top >= maxSize - 1)
        {
            throw "StackOverflow";
        }
        listArray[++top] = it;
    }
    T pop()
    {
        if (top == -1)
        {
            throw "StackEmpty";
        }
        return listArray[top--];
    }
    const T& topValue() const
    {
        if (top == -1)
        {
            throw "StackEmpty";
        }
        return listArray[top];
    }
    int length() const
    {
        return top + 1;
    }
};


#endif //GRAPH_H_