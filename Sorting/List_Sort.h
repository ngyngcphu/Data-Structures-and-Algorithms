#ifndef LIST_SORT_H
#define LIST_SORT_H

#include "main.h"

template <class T>
class SLinkedList
{
private:
    class Node;

private:
    Node *head;
    Node *tail;
    int count;

public:
    SLinkedList()
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->count = 0;
    }
    ~SLinkedList(){};
    void add(T e)
    {
        Node *pNew = new Node{e};
        if (!count)
        {
            head = tail = pNew;
        }
        else
        {
            tail->next = pNew;
            tail = pNew;
        }
        ++count;
    }
    int size()
    {
        return count;
    }
    void printList()
    {
        stringstream ss;
        ss << "[";
        Node *ptr = head;
        while (ptr != tail)
        {
            ss << ptr->data << ",";
            ptr = ptr->next;
        }
        if (count > 0)
        {
            ss << ptr->data << "]";
        }
        else
        {
            ss << "]";
        }
        cout << ss.str() << endl;
    }
    void bubbleSort()
    {
        if (count <= 1)
        {
            return;
        }
        Node *unsorted = this->head;
        Node *sorted = nullptr;
        bool isSorted = false;
        while (!isSorted)
        {
            unsorted = this->head;
            isSorted = true;
            while (unsorted->next != sorted)
            {
                if (unsorted->data > unsorted->next->data)
                {
                    swap(unsorted->data, unsorted->next->data);
                    isSorted = false;
                }
                unsorted = unsorted->next;
            }
            sorted = unsorted;
            if (!isSorted)
            {
                this->printList();
            }
        }
    }
private:
    class Node
    {
    private:
        T data;
        Node *next;
        friend class SLinkedList;

    public:
        Node()
        {
            this->data = T();
            this->next = nullptr;
        }
        Node(T data)
        {
            this->data = data;
            this->next = nullptr;
        }
    };
};

#endif // LIST_SORT_H