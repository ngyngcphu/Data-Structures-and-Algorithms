#include "graph.h"

void Graph::BFS(char startlabel, void (Graph::*action)(int))
{
    int root = startlabel - labels[0];
    LQueue<int>* lq = new LQueue<int>;
    vector<bool> visited(nover, false);
    lq->enqueue(root);
    visited[root] = true;
    while (lq->length())
    {
        int pos = lq->dequeue();
        (this->*action)(pos);
        Link<GEdge>* temp = srclst[pos].next;
        while (temp)
        {
            int idx = temp->element.index;
            if (!visited[idx])
            {
                lq->enqueue(idx);
                visited[idx] = true;
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
    g->addEdge_Undirect(0, 1);
    g->addEdge_Undirect(0, 2);
    g->addEdge_Undirect(1, 2);
    g->addEdge_Undirect(1, 3);
    g->addEdge_Undirect(2, 3);
    g->BFS('a', &Graph::print);
    delete g;
    /*
    INTPUT:
        a->b->c
        b->a->c->d
        c->a->b->d
        d->b->c
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
    g->addEdge_Undirect(0, 1);
    g->addEdge_Undirect(0, 2);
    g->addEdge_Undirect(1, 2);
    g->addEdge_Undirect(1, 3);
    g->addEdge_Undirect(1, 4);
    g->addEdge_Undirect(2, 3);
    g->addEdge_Undirect(3, 4);
    g->addEdge_Undirect(4, 5);
    g->BFS('a', &Graph::print);
    delete g;
    /*
    INPUT:
        a->b->c
        b->a->c->d->e
        c->a->b->d
        d->b->c->e
        e->b->d->f
        f->e
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
    g->addEdge_Undirect(0, 1);
    g->addEdge_Undirect(0, 2);
    g->addEdge_Undirect(1, 2);
    g->addEdge_Undirect(1, 3);
    g->addEdge_Undirect(1, 4);
    g->addEdge_Undirect(2, 3);
    g->addEdge_Undirect(3, 4);
    g->addEdge_Undirect(4, 5);
    g->BFS('e', &Graph::print);
    delete g;
    /*
    INPUT:
        a->b->c
        b->a->c->d->e
        c->a->b->d
        d->b->c->e
        e->b->d->f
        f->e
    OUTPUT:
        e
        b
        d
        f
        a
        c
    */
}

int main()
{
    //test1();
    //test2();
    test3();
}