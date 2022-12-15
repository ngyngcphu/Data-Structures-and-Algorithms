#ifndef HEAP_H
#define HEAP_H

#include "main.h"

template<class T>
class Heap
{
private:
    T* arr;
    int count;
    int cap;

    void copyFromArray(int* arr, int n)
    {
        this->clear();
        this->count = n;
        this->cap = this->count * 3 / 2;
        this->arr = new T[this->cap];
        for (int i = 0; i < count; ++i)
        {
            this->arr[i] = arr[i];
        }
    }
    void buildHeap(int* arr, int n)
    {
        this->copyFromArray(arr, n);
        for (int i = n / 2 - 1; i >= 0; --i)
        {
            reHeapDown(i);
        }
    }
public:
    Heap()
    {
        this->cap = 10;
        this->count = 0;
        this->arr = new T[this->cap];
    }
    Heap(int* arr, int n)
    {
        this->buildHeap(arr, n);

    }
    ~Heap()
    {
        this->clear();
    }
    int size()
    {
        return count;
    }
    bool isEmpty()
    {
        return count == 0;
    }
    T peek()
    {
        return arr[0];
    }
    bool contains(T item)
    {
        if (!count)
        {
            return false;
        }
        for (int i = 0; i < count; ++i)
        {
            if (arr[i] == item)
            {
                return true;
            }
        }
        return false;
    }
    void reHeapUp(int index)
    {
        if (index > 0)
        {
            int parent = (index - 1) / 2;
            if (arr[parent] < arr[index])
            {
                swap(arr[parent], arr[index]);
                reHeapUp(parent);
            }
        }
    }
    void reHeapDown(int index)
    {
        if (index < 0)
        {
            return;
        }
        int leftChild = 2 * index + 1;
        if (leftChild >= count)
        {
            return;
        }
        int bigChild = leftChild;
        int rightChild = leftChild + 1;
        if (rightChild < count && arr[rightChild] > arr[leftChild])
        {
            bigChild = rightChild;
        }
        if (arr[bigChild] > arr[index])
        {
            swap(arr[bigChild], arr[index]);
            reHeapDown(bigChild);
        }
    }
    bool pop()
    {
        if (!count)
        {
            return false;
        }
        arr[0] = arr[--count];
        reHeapDown(0);
        return true;
    }
    void ensureCap(int minCap)
    {
        this->cap = this->cap + minCap;
        T* newArr = new T[cap];
        for (int i = 0; i < count; ++i)
        {
            newArr[i] = arr[i];
        }
        delete[] arr;
        this->arr = newArr;
    }
    void push(T item)
    {
        if (this->count >= this->cap)
        {
            ensureCap(10);
        }
        arr[count++] = item;
        reHeapUp(count - 1);
    }
    int getItem(T item)
    {
        for (int i = 0; i < count; ++i)
        {
            if (item == arr[i])
            {
                return i;
            }
        }
        return -1;
    }
    void remove(T item)
    {
        if (!count)
        {
            return;
        }
        int index = this->getItem(item);
        if (index == -1)
        {
            return;
        }
        arr[index] = arr[--count];
        reHeapUp(index);
        reHeapDown(index);
    }
    void printHeap()
    {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; ++i)
        {
            cout << arr[i] << " ";
        }
        cout << "]\n";
    }
    void clear()
    {
        this->cap = 10;
        this->count = 0;
        delete[] this->arr;
    }
};
#endif //HEAP_H
