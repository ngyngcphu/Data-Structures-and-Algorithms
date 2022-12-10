#include "hash_table.h"

void base()
{
    Hash_Table<int> *hashTable = new Hash_Table<int>{11, double_hashing, 0.82};
    Element<int> e[] = {Element<int>(10, 0), Element<int>(22, 0), Element<int>(31, 0), Element<int>(4, 0),
                        Element<int>(15, 0), Element<int>(28, 0), Element<int>(17, 0), Element<int>(88, 0),
                        Element<int>(59, 0)};
    int size = sizeof(e) / sizeof(Element<int>);
    for (int i = 0; i < size; ++i)
    {
        hashTable->insert(e[i]);
    }
    hashTable->remove(e[1]);
    cout << hashTable->search(e[7]) << endl;
    hashTable->print();
    delete hashTable;
}

/*
There are n people, each person has a number between 1 and 100000 (1 ≤ n ≤ 100000). 
Given a number target. Two people can be matched as a perfect pair if the sum of numbers they have 
is equal to target. A person can be matched no more than 1 time.
INPUT:
    vector<int>items{1, 3, 5, 3, 7};
    int target = 6;
    cout << pairMatching(items, target);

    int target = 6;
    vector<int>items{4,4,2,1,2};
    cout << pairMatching(items, target);
OUTPUT:
    2
    2
*/
int pairMatching(vector<int>& nums, int target)
{
    int count = 0;
    map<int, int> m;
    for (int i = 0; i < (int)nums.size(); ++i)
    {
        m[nums[i]]++;
    }
    for (int i = 0; i < (int)nums.size(); ++i)
    {
        if (m[nums[i]] > 0)
        {
            if (nums[i] == target / 2 && m[nums[i]] == 1)
            {
                continue;
            }
            if (m[target - nums[i]] > 0)
            {
                count++;
                m[nums[i]]--;
                m[target - nums[i]]--;
            }
        }
    }
    return count;
}

int main()
{
    base();
}