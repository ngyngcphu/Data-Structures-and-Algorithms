#include "graph.h"

void Graph::DFS(char startlabel, void (Graph::*action)(int))
{
    int root = startlabel - labels[0];
    AStack<int>* as = new AStack<int>;
    vector<bool> visited(nover, false);
    as->push(root);
    visited[root] = true;
    while (as->length())
    {
        int pos = as->pop();
        visited[pos] = true;
        (this->*action)(pos);
        Link<GEdge>* temp = srclst[pos].next;
        while (temp)
        {
            int idx = temp->element.index;
            if (!visited[idx])
            {
                as->push(idx);
                visited[idx] = true;
            }
            temp = temp->next;
        }
    }
    delete as;
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
    g->DFS('a', &Graph::print);
    delete g;
    /*
    INTPUT:
        a->b->c
        b->a->c->d
        c->a->b->d
        d->b->c
    OUTPUT:
        a
        c
        b
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
    g->DFS('a', &Graph::print);
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
        c
        d
        e
        f
        b
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
    g->DFS('e', &Graph::print);
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
        f
        d
        c
        a
        b
    */
}

int main()
{
    //test1();
    //test2();
    test3();
}