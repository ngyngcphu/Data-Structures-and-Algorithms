#ifndef ARRAY_SORT_
#define ARRAY_SORT

#include "main.h"

template<class T>
class Sorting
{
private:
    static void printArray(T* start, T* end)
    {
        int size = end - start;
        for (int i = 0; i < size - 1; ++i)
        {
            cout << start[i] << ", ";
        }
        cout << start[size - 1];
        cout << endl;
    }
    static void sortSegment(T* start, T* end, int segment_idx, int cur_segment_total)
    {
        int size = end - start;
        for (int i = segment_idx; i < size - cur_segment_total ; i += cur_segment_total)
        {
            for (int j = i + cur_segment_total; j < size; j += cur_segment_total)
            {
                if (start[i] > start[j])
                {
                    swap(start[i], start[j]);
                }
            }
        }
    }
    static T* partition(T* start, T* end)
    {
        int size = end - start;
        int i = 1;
        int j = size - 1;
        while (i <= j)
        {
            while (i <= j && start[i] < start[0])
            {
                ++i;
            }
            while (i <= j && start[j] >= start[0])
            {
                --j;
            }
            if (i <= j)
            {
                swap(start[i], start[j]);
                ++i;
                --j;
            }
        }
        swap(start[0], start[j]);
        return &start[j];
    }
    static void merge(T* left, T* middle, T* right)
    {
        int size1 = middle - left;
        int size2 = right - left;
        int i = 0;
        int j = size1 + 1;
        int k = 0;
        T* newArr = new T[right - left + 1];
        while (i <= size1 && j <= size2)
        {
            if (left[i] < left[j])
            {
                newArr[k] = left[i];
                ++k;
                ++i;
            }
            else
            {
                newArr[k] = left[j];
                ++k;
                ++j;
            }
        }
        while (i <= size1)
        {
            newArr[k] = left[i];
            ++k;
            ++i;
        }
        while (j <= size2)
        {
            newArr[k] = left[j];
            ++k;
            ++j;
        }
        for (int i = 0; i < k; ++i)
        {
            left[i] = newArr[i];
        }
        delete[] newArr;
        printArray(left, right);
    }

public:
    static void selectionSort(T* start, T* end)
    {
        int size = end - start;
        for (int i = 0; i < size - 1; ++i)
        {
            int min_idx = i;
            for (int j = i + 1; j < size; ++j)
            {
                if (start[min_idx] > start[j])
                {
                    min_idx = j;
                }
            }
            swap(start[i], start[min_idx]);
            printArray(start, end);
        }
    }
    static void insertionSort(T* start, T* end)
    {
        int size = end - start;
        for (int i = 1; i < size; ++i)
        {
            int temp = start[i];
            int j = i - 1;
            while (j >= 0 && temp < start[j])
            {
                start[j + 1] = start[j];
                --j;
            }
            start[j + 1] = temp;
            printArray(start, end);
        }
    }
    static void shellSort(T* start, T* end, int* num_segment_list, int num_phases)
    {
        for (int i = num_phases - 1; i >= 0; --i)
        {
            for (int j = 0; j < num_segment_list[i]; ++j)
            {
                sortSegment(start, end, j, num_segment_list[i]);
            }
            cout << num_segment_list[i] << " segments: ";
            printArray(start, end);
        }
    }
    static void quickSort(T* start, T* end)
    {
        int size = end - start;
        if (size > 0)
        {
            T* j = partition(start, end);
            cout << j - start << " ";
            quickSort(start, &start[j - start]);
            quickSort(&start[j - start + 1], end);
        }
    }
    static void mergeSort(T* start, T* end)
    {
        int size = end - start;
        if (size > 0)
        {
            int middle = size / 2;
            mergeSort(start, &start[middle]);
            mergeSort(&start[middle + 1], end);
            merge(start, &start[middle], end);
        }
    }
};

#endif // ARRAY_SORT_H