#ifndef HASH_FUNCTION_H
#define HASH_FUNCTION_H

#include "main.h"

/* In midSquare function: we eliminate 2 last digits and get the 4 next digits.
INPUT:
    cout << midSquare(9452);
OUTPUT:
    3403    
*/
long int midSquare(long int seed)
{
    return (seed * seed / 100) % 10000;
}
long int moduloDivision(long int seed, long int mod)
{
    return seed % mod;
}

/* In digitExtraction: extractDigits is a sorted array from smallest to largest index of digit in seed 
(index starts from 0). The array has size size.
INPUT:
    int a[]={1,2,5};
    cout << digitExtraction(122443,a,3);
OUTPUT:
    223
*/
long int digitExtraction(long int seed, int *extractDigits, int size)
{
    string s{to_string(seed)};
    int res{};
    for (int i{0}; i < size; ++i)
    {
        res = 10 * res + (s[extractDigits[i]] - '0');
    }
    return res;
}

int foldShift(long long key, int addressSize)
{
    string s{to_string(key)};
    int res{};
    while ((int)s.size() > 0)
    {
        res += stoi(s.substr(0, addressSize));
        s.erase(0, addressSize);
    }
    return res % (int)(pow(10, addressSize));
}

int rotation(long long key, int addressSize)
{
    string s{to_string(key)};
    long long res = key / 10 + pow(10, s.size() - 1) * (key % 10);
    return foldShift(res, addressSize);
}

#endif // HASH_FUNCTION_H