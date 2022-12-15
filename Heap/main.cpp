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
/*
Different kinds of food take different amounts of time to cook. And he can't cook food for two customers 
at the same time, which means when he start cooking for customer A, he has to finish A 's order before 
cooking for customer B. For example, if there are 3 customers and they come at time 0, 1, 2 respectively, 
the time needed to cook their food is 3, 9, 6 respectively. If the manager uses first-come, 
first-served rule to serve his customer, the total waiting time will be 3 + 11 + 16 = 30. 
In case the manager serves his customer in order 1, 3, 2, the total waiting time will be 3 + 7 + 17 = 27.  
INPUT:
    int n = 3; 
    int arrvalTime[] = { 0, 1, 2 };
    int completeTime[] = { 3, 9, 6 };
    cout << minWaitingTime(n, arrvalTime, completeTime);

    int n = 4; 
    int arrvalTime[] = { 0, 4, 2, 5 };
    int completeTime[] = { 4, 2, 3, 4 };

    cout << minWaitingTime(n, arrvalTime, completeTime);
OUTPUT:
    27
    21
*/
int minWaitingTime(int n, int arrvalTime[], int completeTime[])
{
    
}

int main()
{
    test3();
}