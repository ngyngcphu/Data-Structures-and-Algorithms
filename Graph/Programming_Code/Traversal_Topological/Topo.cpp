#include "graph.h"

void Graph::topologicalSort(void (Graph::*action)(int))
{
    vector<int> indegree(nover, 0);
    for (int i = 0; i < nover; ++i)
    {
        Link<GEdge>* temp = srclst[i].next;
        while (temp)
        {
            ++indegree[temp->element.index];
            temp = temp->next;
        }
    }
    LQueue<int>* lq = new LQueue<int>;
    for (int i = 0; i < nover; ++i)
    {
        if (!indegree[i])
        {
            lq->enqueue(i);
        }
    }
    while (lq->length())
    {
        int pos = lq->dequeue();
        (this->*action)(pos);
        Link<GEdge>* temp = srclst[pos].next;
        while (temp)
        {
            int idx = temp->element.index;
            --indegree[idx];
            if (!indegree[idx])
            {
                lq->enqueue(idx);
            }
            temp = temp->next;
        }
    }
    delete lq;
}

void test1()
{
    char x[] = {'a', 'b', 'c', 'd'};
    Graph* g = new Graph(x, 4);
    g->addEdge_Direct(0, 1);
    g->addEdge_Direct(0, 2);
    g->addEdge_Direct(1, 2);
    g->addEdge_Direct(1, 3);
    g->addEdge_Direct(2, 3);
    g->topologicalSort(&Graph::print);
    /*
    INPUT:
        a->b->c
        b->c->d
        c->d
    OUTPUT:
        a
        b
        c
        d
    */
}

void test2()
{
    char x[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    Graph* g = new Graph(x, 6);
    g->addEdge_Direct(0, 1);
    g->addEdge_Direct(0, 2);
    g->addEdge_Direct(1, 2);
    g->addEdge_Direct(1, 3);
    g->addEdge_Direct(1, 4);
    g->addEdge_Direct(2, 3);
    g->addEdge_Direct(3, 4);
    g->addEdge_Direct(4, 5);
    g->topologicalSort(&Graph::print);
    /*
    INPUT:
        a->b->c
        b->c->d->e
        c->d
        d->e
        e->f
    OUTPUT:
        a
        b
        c
        d
        e
        f
    */
}

void test3()
{
    char x[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    Graph* g = new Graph(x, 6);
    g->addEdge_Direct(0, 2);
    g->addEdge_Direct(1, 0);
    g->addEdge_Direct(1, 2);
    g->addEdge_Direct(1, 3);
    g->addEdge_Direct(1, 4);
    g->addEdge_Direct(2, 3);
    g->addEdge_Direct(4, 3);
    g->addEdge_Direct(5, 4);
    g->topologicalSort(&Graph::print);
    /*
    INPUT:
        a->c
        b->a->c->d->e
        c->d
        e->d
        f->e
    OUTPUT:
        b
        f
        a
        e
        c
        d
    */
}

void test4()
{
    char x[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    Graph* g = new Graph(x, 6);
    g->addEdge_Direct(0, 2);
    g->addEdge_Direct(1, 0);
    g->addEdge_Direct(1, 2);
    g->addEdge_Direct(1, 4);
    g->addEdge_Direct(2, 3);
    g->addEdge_Direct(3, 1);
    g->addEdge_Direct(4, 3);
    g->addEdge_Direct(5, 4);
    g->topologicalSort(&Graph::print);
    /*
    INPUT:
        a->c
        b->a->c->e
        c->d
        d->b
        e->d
        f->e
    OUTPUT: // graph does not have topo-ordering because it has a cyclic: a->c->d->b->a
        f
    */
}

void test5()
{
    char x[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    Graph* g = new Graph(x, 6);
    g->addEdge_Direct(0, 2);
    g->addEdge_Direct(1, 0);
    g->addEdge_Direct(1, 2);
    g->addEdge_Direct(1, 3);
    g->addEdge_Direct(2, 3);
    g->addEdge_Direct(4, 1);
    g->addEdge_Direct(4, 3);
    g->addEdge_Direct(5, 4);
    g->topologicalSort(&Graph::print);
    /*
    INPUT:
        a->c
        b->a->c->d
        c->d
        e->b->d
        f->e
    OUTPUT:
        f
        e
        b
        a
        c
        d
    */
}

void test6()
{
    char x[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    Graph* g = new Graph(x, 18);
    g->addEdge_Direct(0, 1);
    g->addEdge_Direct(0, 7);
    g->addEdge_Direct(0, 14);
    g->addEdge_Direct(1, 4);
    g->addEdge_Direct(2, 3);
    g->addEdge_Direct(2, 6);
    g->addEdge_Direct(4, 5);
    g->addEdge_Direct(5, 6);
    g->addEdge_Direct(6, 9);
    g->addEdge_Direct(7, 8);
    g->addEdge_Direct(8, 11);
    g->addEdge_Direct(8, 12);
    g->addEdge_Direct(9, 12);
    g->addEdge_Direct(10, 13);
    g->addEdge_Direct(10, 17);
    g->addEdge_Direct(11, 12);
    g->addEdge_Direct(12, 15);
    g->addEdge_Direct(12, 16);
    g->addEdge_Direct(13, 16);
    
    g->topologicalSort(&Graph::print);
}

int main()
{
    //test1();
    //test2();
    //test3();
    //test4();
    //test5();
    test6();
}