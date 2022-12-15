#include "List_Sort.h"
#include "Array_Sort.h"

void bubbleSort()
{
    int arr[] = {9, 2, 8, 4, 1};
    SLinkedList<int> list;
    for (int i = 0; i < int(sizeof(arr)) / 4; ++i)
    {
        list.add(arr[i]);
    }
    list.bubbleSort();
}

void selectionSort()
{
    int arr[] = {9, 2, 8, 1, 0, -2};
    Sorting<int>::selectionSort(&arr[0], &arr[6]);
}

void insertionSort()
{
    int arr[] = {9, 2, 8, 1, 0, -2};
    Sorting<int>::insertionSort(&arr[0], &arr[6]);
}

void shellSort()
{
    int num_segment_list[] = {1, 3, 5};
    int num_phases = 3;
    int array[] = { 10, 9, 8 , 7 , 6, 5, 4, 3, 2, 1 };

    Sorting<int>::shellSort(&array[0], &array[10], &num_segment_list[0], num_phases);
}

void quickSort()
{
    int array[] = { 3, 5, 7, 10 ,12, 14, 15, 13, 1, 2, 9, 6, 4, 8, 11, 16, 17, 18, 20, 19 };
    cout << "Index of pivots: ";
    Sorting<int>::quickSort(&array[0], &array[20]);
    cout << "\n";
    cout << "Array after sorting: ";
    for (int i : array) cout << i << " ";
}

void mergeSort()
{
    int arr[] = {0,2,4,3,1,4};
    Sorting<int>::mergeSort(&arr[0], &arr[5]);
}

int main()
{
    //bubbleSort();
    //selectionSort();
    //insertionSort();
    //shellSort();
    //quickSort();
    mergeSort();
}