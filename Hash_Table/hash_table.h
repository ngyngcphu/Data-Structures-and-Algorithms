#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "main.h"

template<class T>
class Hash_Table;

template<class T>
class Element
{
public:
    T data;
    int key;

public:
    Element(int key = 0, T data = T())
    {
        this->key = key;
        this->data = data;
    }
    friend bool operator==(const Element<T>& e, const Element<T>& f)
    {
        return e.key == f.key;
    }
};

template<class T>
int linear_probing(int size, const Element<T>& e, int i)
{
    return ((e.key % size) + i) % size;
}

template<class T>
int quadratic_probing(int size, const Element<T>& e, int i)
{
    return (e.key % size + i + 3 * i * i) % size;
}

template<class T>
int double_hashing(int size, const Element<T>& e, int i)
{
    int h1 = e.key % size;
    int h2 = 1 + (e.key % (size - 1));
    return (h1 + i * h2) % size;
}

enum status
{
    NIL,
    NON_EMPTY,
    DELETED
};

template<class T>
class Hash_Table
{
private:
    vector<Element<T>> hash;
    vector<status> s;
    double load_factor, lamda;
    int (*hp)(int, const Element<T>&, int);
    int curSize;

    void reHashing()
    {
        vector<Element<T>> newHashTable(2 * (int)hash.size());
        vector<status> newStatus(newHashTable.size(), NIL);
        for (int i = 0; i < (int)hash.size(); ++i)
        {
            if (s[i] == NON_EMPTY)
            {
                int j;
                for (j = 0; j < (int)newHashTable.size(); ++j)
                {
                    int index = this->hp((int)newHashTable.size(), hash[i], j);
                    if (newStatus[index] != NON_EMPTY)
                    {
                        newHashTable[index] = hash[i];
                        newStatus[index] = NON_EMPTY;
                        break;
                    }
                }
                if (j == (int)newHashTable.size())
                {
                    throw overflow_error("No possible slot!");
                }
            }
        }
        this->hash = newHashTable;
        this->s = newStatus;
    }

public:
    Hash_Table(int size, int (*hp)(int, const Element<T>&, int), double lamda = 0.75)
    {
        this->hash = vector<Element<T>>(size);
        this->s = vector<status>(size, NIL);
        this->hp = hp;
        this->curSize = 0;
        this->load_factor = 0;
        this->lamda = lamda;
    }
    int insert(const Element<T>& e)
    {
        for (int i = 0; i < (int)hash.size(); ++i)
        {
            int index = this->hp((int)hash.size(), e, i);
            if (s[index] != NON_EMPTY)
            {
                hash[index] = e;
                s[index] = NON_EMPTY;
                this->curSize++;
                this->load_factor = (this->curSize * 1.0) / (int)this->hash.size();
                if (this->load_factor > this->lamda)
                {
                    reHashing();
                }
                return index;
            }
        }
        throw overflow_error("No possible slot!");
    }
    int remove(const Element<T>& e)
    {
        for (int i = 0; i < (int)hash.size(); ++i)
        {
            int index = this->hp((int)hash.size(), e, i);
            if (s[index] == NIL)
            {
                break;
            }
            if (s[index] == NON_EMPTY && hash[index] == e)
            {
                s[index] = DELETED;
                this->curSize--;
                for (int j = i + 1; j < (int)hash.size(); ++j)
                {
                    int index1 = this->hp((int)hash.size(), e, j);
                    if (s[index1] == NON_EMPTY)
                    {
                        s[index1] = NIL;
                        this->curSize--;
                        insert(hash[index1]);
                        return index;
                    }
                }
            }
        }
        throw logic_error("Element does not appear in Hash Table!");
    }
    int search(const Element<T>& e)
    {
        for (int i = 0; i < (int)hash.size(); ++i)
        {
            int index = this->hp((int)hash.size(), e, i);
            if (s[index] == NIL)
            {
                return -1;
            }
            if (s[index] == NON_EMPTY && hash[index] == e)
            {
                return index;
            }
        }
        return -1;
    }
    void print()
    {
        cout << "Hash table: [";
        for (int i = 0; i < (int)hash.size(); ++i)
        {
            if (s[i] == NON_EMPTY)
            {
                cout << "(" << hash[i].data << "," << hash[i].key << ")";
            }
            else
            {
                cout << "()";
            }
            cout << (i == (int)hash.size() -1 ? "" : ";");
        }
        cout << "]";
    }
};

#endif //HASH_TABLE_H