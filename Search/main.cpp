#include "Search.h"

void binarySearch()
{
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    int x = 10;
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = binarySearch(arr, 0, n - 1, x);
    (result == -1) ? cout << "Element is not present in array"
                    : cout << "Element is present at index " << result;
}

void interpolationSearch()
{
    int arr[] = { 1,2,3,4,5,6,7,8,9 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 3;
    int result = interpolationSearch(arr, 0, n - 1, x);
    (result == -1) ? cout << "Element is not present in array"
                : cout << "Element is present at index " << result;

    cout << endl << "#----------------------------------------------#" << endl;

    int arr1[] = { 1,2,3,4,5,6,7,8,9 };
    n = sizeof(arr1) / sizeof(arr1[0]);
    x = 0;
    result = interpolationSearch(arr1, 0, n - 1, x);
    (result == -1) ? cout << "Element is not present in array"
                : cout << "Element is present at index " << result;
}

void jumpSearch()
{
    int arr[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 };
    int x = 55;
    int n = sizeof(arr) / sizeof(arr[0]);
    int index = jumpSearch(arr, x, n);

    if (index != -1) {
        cout << "\nNumber " << x << " is at index " << index;
    }
    else {
        cout << "\n" << x << " is not in array!";
    }

    cout << endl << "#----------------------------------------------#" << endl;

    int arr1[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 };
    x = 144;
    n = sizeof(arr1) / sizeof(arr1[0]);
    index = jumpSearch(arr1, x, n);

    if (index != -1) {
        cout << "\nNumber " << x << " is at index " << index;
    }
    else {
        cout << "\n" << x << " is not in array!";
    }
}

/*
Given an array of distinct integers, find if there are two pairs (a, b) and (c, d) such that a+b = c+d, 
and a, b, c and d are distinct elements. If there are multiple answers, you can find any of them.
INPUT:
    int arr[] = { 3, 4, 7, 1, 2, 9, 8 };
    int n = sizeof arr / sizeof arr[0];
    pair<int, int> pair1, pair2;
    if (findPairs(arr, n, pair1, pair2)) {
        if (checkAnswer(arr, n, pair1, pair2)) {
            printf("Your answer is correct.\n");
        }
        else printf("Your answer is incorrect.\n");
    }
    else printf("No pair found.\n");

    int arr[] = { 3, 4, 7 };
    int n = sizeof arr / sizeof arr[0];
    pair<int, int> pair1, pair2;
    if (findPairs(arr, n, pair1, pair2)) {
        if (checkAnswer(arr, n, pair1, pair2)) {
            printf("Your answer is correct.\n");
        }
        else printf("Your answer is incorrect.\n");
    }
    else printf("No pair found.\n");
OUTPUT:
    Your answer is correct.
    No pair found.
*/
bool findPairs(int arr[], int n, pair<int,int>& pair1, pair<int,int>& pair2)
{
    map<int,pair<int,int>> m;
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            int sum = arr[i] + arr[j];
            if (m.find(sum) == m.end())
            {
                pair<int,int> p;
                p.first = i;
                p.second = j;
                m[sum] = p;
            }
            else
            {
                pair1.first = arr[m[sum].first];
                pair1.second = arr[m[sum].second];
                pair2.first = arr[i];
                pair2.second = arr[j];
                return true;
            }
        }
    }
    return false;
}

int main()
{
    //binarySearch();
    //interpolationSearch();
    //jumpSearch();
}