#include "List_Graph.h"

struct Edge
{
    char src, dst; // labels of source and destination of the directed edge
    int weight;    // weight of the edge
    Edge(char src, char dst, int weight)
    {
        this->src = src;
        this->dst = dst;
        this->weight = weight;
    }
};

void Graph::addEdge(struct Edge edges[], int n)
{
    char root = srclst[0].element.label;
    for (int i = 0; i < n; ++i)
    {
        char s = edges[i].src;
        Link<GEdge> *e = new Link<GEdge>(GEdge(edges[i].dst, edges[i].weight));
        Link<GEdge> *temp = &srclst[s - root];
        while (temp->next && edges[i].dst > temp->next->element.label)
        {
            temp = temp->next;
        }
        e->next = temp->next;
        temp->next = e;
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
        from b to c weight 2
        from c to d weight 5
        from d to b weight 6
    */
}

void test2()
{
    char x[] = {'a', 'b', 'c', 'd'};
    Edge t[] = {Edge('a', 'c', 3), Edge('a', 'b', 4), Edge('b', 'c', 2), Edge('c', 'd', 5),
                Edge('c', 'b', 6), Edge('b', 'a', 1), Edge('b', 'd', 2)};
    Graph *g = new Graph(x, 4);
    g->addEdge(t, 7);
    g->printGraph();
    delete g;
    /*
    OUTPUT:
        from a to b weight 4
        from a to c weight 3
        from b to a weight 1
        from b to c weight 2
        from b to d weight 2
        from c to b weight 6
        from c to d weight 5
    */
}

void test3()
{
    char x[] = {'a', 'b', 'c', 'd'};
    Edge t[] = {Edge('a', 'c', 3), Edge('b', 'c', 4), Edge('d', 'c', 2), Edge('c', 'd', 5),
                Edge('c', 'b', 6), Edge('b', 'a', 1)};
    Graph *g = new Graph(x, 4);
    g->addEdge(t, 6);
    g->printGraph();
    delete g;
    /*
    OUTPUT:
        from a to c weight 3
        from b to a weight 1
        from b to c weight 4
        from c to b weight 6
        from c to d weight 5
        from d to c weight 2
    */
}

int main()
{
    // test1();
    // test2();
    test3();
}