#ifndef SEARCH_h
#define SEARCH_H

#include "main.h"

int binarySearch(int arr[], int left, int right, int x)
{
    if (left > right)
    {
        return -1;
    }
    int mid = (left + right) / 2;
    if (x == arr[mid])
    {
        cout << "We traverse on index: " << mid << endl;
        return mid;
    }
    else if (x < arr[mid])
    {
        cout << "We traverse on index: " << mid << endl;
        right = mid - 1;
    }
    else
    {
        cout << "We traverse on index: " << mid << endl;
        left = mid + 1;
    }
    return binarySearch(arr, left, right, x);
}

int interpolationSearch(int arr[], int left, int right, int x)
{
    if (left > right || x < arr[left] || x > arr[right])
    {
        return -1;
    }
    int mid = left + (x - arr[left]) * (right - left) / (arr[right] - arr[left]);
    if (x == arr[mid])
    {
        cout << "We traverse on index: " << mid << endl;
        return mid;
    }
    else if (x < arr[mid])
    {
        cout << "We traverse on index: " << mid << endl;
        right = mid - 1;
    }
    else
    {
        cout << "We traverse on index: " << mid << endl;
        left = mid + 1;
    }
    return interpolationSearch(arr, left, right, x);
}

int jumpSearch(int arr[], int x, int n)
{
    int jum_space = sqrt(n);
    int i = 0;
    while (arr[i] < x && i < n)
    {
        cout << i << " ";
        i += jum_space;
        if (arr[i] == x)
        {
            cout << i << " ";
            return i;
        }
        if (i < n && arr[i] > x)
        {
            cout << i << " ";
        }
        else if (i > n)
        {
            break;
        }
    }
    if (i > n || arr[i] > x)
    {
        i -= jum_space;
        ++i;
    }
    int save_jump = i + jum_space;
    for (; i < save_jump - 1; ++i)
    {
        cout << i << " ";
        if (x == arr[i])
        {
            return i;
        }
    }
    return -1;
}

#endif //SEARCH_H