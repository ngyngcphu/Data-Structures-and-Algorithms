#include <iostream>
using namespace std;

enum STATUS_TYPE
{
    NIL,
    NON_EMPTY,
    DELETED
};
class OpenHash
{
private:
    int (*hp)(int, int);
    STATUS_TYPE *status;
    int *data;
    int size;

public:
    OpenHash()
    {
        throw "Cannot create a hash with no hash function!";
    }
    OpenHash(int size, int (*hp)(int, int))
    {
        this->hp = hp;
        this->size = size;
        this->data = new int[size];
        this->status = new STATUS_TYPE[size];
        for (int i{0}; i < size; ++i)
        {
            this->status[i] = NIL;
        }
    }

    int insert(int key);
    void remove(int key);
    int search(int key);

    void dump()
    {
        for (int i{0}; i < size; ++i)
        {
            if (this->status[i] != NON_EMPTY)
            {
                cout << "Slot " << i << ": Empty" << endl;
            }
            else
            {
                cout << "Slot " << i << ": " << this->data[i] << endl;
            }
        }
    }
};

int linearProbing(int key, int i)
{
    return ((key % 11) + i) % 11;
}

int quadraticProbing(int key, int i)
{
    return ((key % 11) + i + 3 * i * i) % 11;
}

int doubleHashing(int key, int i)
{
    int h1{key % 11};
    int h2{1 + (key % 10)};
    return (h1 + i * h2) % 11;
}

int OpenHash::insert(int key)
{
    for (int i{0}; i < size; ++i)
    {
        int slot{(*hp)(key, i)};
        if (status[slot] == NIL || status[slot] == DELETED)
        {
            data[slot] = key;
            status[slot] = NON_EMPTY;
            return slot;
        }
    }
    throw "Overflow!";
}

void OpenHash::remove(int key)
{
    for (int i{0}; i < size; ++i)
    {
        int slot{(*hp)(key, i)};
        if (status[slot] == NIL)
        {
            throw "Not found!";
        }
        if (status[slot] == NON_EMPTY && data[slot] == key)
        {
            status[slot] = DELETED;
            return;
        }
    }
    throw "Not found!";
}

int OpenHash::search(int key)
{
    for (int i{0}; i < size; ++i)
    {
        int slot{(*hp)(key, i)};
        if (status[slot] == NIL)
        {
            return -1;
        }
        if (status[slot] == NON_EMPTY && data[slot] == key)
        {
            return slot;
        }
    }
    return -1;
}

int main()
{
    OpenHash *hashTable{new OpenHash{11, doubleHashing}};
    int data[]{10, 22, 31, 4, 15, 28, 17, 88, 59};
    int size{sizeof(data) / sizeof(int)};
    for (int i{0}; i < size; ++i)
    {
        hashTable->insert(data[i]);
    }
    hashTable->dump();
}