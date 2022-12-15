#include "List_Graph.h"

struct Edge
{
    char ver1, ver2; // labels of vertices of the edge
    int weight;      // weight of the edge
    Edge(char ver1, char ver2, int weight)
    {
        this->ver1 = ver1;
        this->ver2 = ver2;
        this->weight = weight;
    }
};

void Graph::addEdge(struct Edge edges[], int n)
{
    char root = srclst[0].element.label;
    for (int i = 0; i < n; ++i)
    {
        char s1 = edges[i].ver1;
        char s2 = edges[i].ver2;
        Link<GEdge> *e1 = new Link<GEdge>(GEdge(edges[i].ver2, edges[i].weight));
        Link<GEdge> *e2 = new Link<GEdge>(GEdge(edges[i].ver1, edges[i].weight));
        Link<GEdge> *temp1 = &srclst[s1 - root];
        Link<GEdge> *temp2 = &srclst[s2 - root];
        while (temp1->next && edges[i].ver2 > temp1->next->element.label)
        {
            temp1 = temp1->next;
        }
        e1->next = temp1->next;
        temp1->next = e1;
        while (temp2->next && edges[i].ver1 > temp2->next->element.label)
        {
            temp2 = temp2->next;
        }
        e2->next = temp2->next;
        temp2->next = e2;
    }
}

void test1()
{
    char x[] = {'a', 'b', 'c', 'd'};
    Edge t[] = {Edge('a', 'c', 3), Edge('a', 'b', 4), Edge('b', 'c', 2), Edge('c', 'd', 5), Edge('d', 'b', 6)};
    Graph *g = new Graph(x, 4);
    g->addEdge(t, 5);
    g->printGraph();
    delete g;
    /*
    OUTPUT:
        from a to b weight 4
        from a to c weight 3
        from b to a weight 4
        from b to c weight 2
        from b to d weight 6
        from c to a weight 3
        from c to b weight 2
        from c to d weight 5
        from d to b weight 6
        from d to c weight 5
    */
}

void test2()
{
    char x[] = {'a', 'b', 'c', 'd'};
    Edge t[] = {Edge('a', 'c', 3), Edge('c', 'd', 5), Edge('c', 'b', 6), Edge('b', 'a', 1)};
    Graph *g = new Graph(x, 4);
    g->addEdge(t, 4);
    g->printGraph();
    delete g;
    /*
    OUTPUT:
        from a to b weight 1
        from a to c weight 3
        from b to a weight 1
        from b to c weight 6
        from c to a weight 3
        from c to b weight 6
        from c to d weight 5
        from d to c weight 5

    */
}

void test3()
{
    char x[] = {'a', 'b', 'c', 'd', 'e'};
    Edge t[] = {Edge('a', 'c', 3), Edge('b', 'c', 4), Edge('d', 'c', 2),
                Edge('c', 'e', 5), Edge('e', 'b', 6), Edge('b', 'a', 1)};
    Graph *g = new Graph(x, 5);
    g->addEdge(t, 6);
    g->printGraph();
    delete g;
    /*
    OUTPUT:
        from a to b weight 1
        from a to c weight 3
        from b to a weight 1
        from b to c weight 4
        from b to e weight 6
        from c to a weight 3
        from c to b weight 4
        from c to d weight 2
        from c to e weight 5
        from d to c weight 2
        from e to b weight 6
        from e to c weight 5
    */
}

int main()
{
    // test1();
    // test2();
    test3();
}