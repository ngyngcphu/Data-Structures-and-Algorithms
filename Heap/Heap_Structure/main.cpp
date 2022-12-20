#include "heap.h"

void test1()
{
    int arr[6] = {5, 9, 4, 2, 1, 6};
    Heap<int> *h = new Heap<int>{arr, 6};
    h->printHeap();
    delete h;
}

void test2()
{
    int arr[7] = {78, 56, 32, 45, 8, 23, 19};
    Heap<int> *h = new Heap<int>{arr, 7};
    h->push(67);
    h->printHeap();
    h->pop();
    h->printHeap();
    delete h;
}

void test3()
{
    int arr[] = {42, 35, 30, 15, 20, 21, 18, 3, 7, 14};
    Heap<int>* h = new Heap<int>{arr, 10};
    h->remove(42);
    h->remove(35);
    h->remove(30);
    h->printHeap();
    h->clear();
    h->printHeap();
    delete h;
}

int main()
{
    //test1();
    //test2();
    test3();
}