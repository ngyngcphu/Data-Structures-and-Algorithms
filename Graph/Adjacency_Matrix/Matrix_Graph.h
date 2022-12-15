#ifndef MATRIX_GRAPH_H_
#define MATRIX_GRAPH_H_

#include <iostream>
#include <climits>

using namespace std;

struct Edge;

class Graph
{
private:
    int nover;
    char* labels;
    int** wm; // weight matrix

public:
    Graph(char vertices[], const int n)
    {
        this->nover = n;
        this->labels = vertices;
        this->wm = new int*[n];
        for (int i = 0; i < n; ++i)
        {
            wm[i] = new int[n];
        }
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i == j)
                {
                    wm[i][j] = 0;
                }
                else
                {
                    wm[i][j] = INT_MAX;
                }
            }
        }
    }
    void printGraph()
    {
        for (int i = 0; i < nover; ++i)
        {
            for (int j = 0; j < nover; ++j)
            {
                if (j == i)
                {
                    continue;
                }
                if (wm[i][j] > 0 && wm[i][j] < INT_MAX)
                {
                    cout << "from " << labels[i] << " to " << labels[j] << " weight " << wm[i][j] << endl;
                }
            }
        }
    }
    void clear()
    {
        for (int i = 0; i < nover; ++i)
        {
            delete[] wm[i];
        }
        delete[] wm;
        this->nover = 0;
        this->labels = nullptr;
        this->wm = nullptr;
    }
    ~Graph()
    {
        this->clear();
    }
    void addEdge(struct Edge edges[], int n);
};

#endif //MATRIX_GRAPH_H_