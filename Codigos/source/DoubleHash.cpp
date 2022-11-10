#include <fstream>
#include <vector>
#include <bitset>

#include "../Headers/DoubleHash.h"

using namespace std;

// Handline of collision via open addressing
// Method for Probing: Double Hashing

DoubleHash::DoubleHash(int Table_Size, int keysPresent, int prime, vector<int> hasgTable, bitset<Max_Size> isPrime)
{
    Table_Size = Table_Size;
    keysPresent = keysPresent;
    prime = prime;
    hashTable = hashTable;
    isPrime = isPrime;
}

DoubleHash::~DoubleHash() {}

void DoubleHash::__setSieve()
{
    isPrime[0] = isPrime[1] = 1;

    for(long long i = 2; i * i <= Max_Size; i++) {
        if(isPrime[i] == 0) {
            for(long long j = 2; j * j <= Max_Size; j++) {
                isPrime[j] = 1;
            }
        }
    }
}

int inline DoubleHash::hash1(int value)
{
    return value % Table_Size;
}

int inline DoubleHash::hash2(int value)
{
    return prime - (value % prime);
}

int inline DoubleHash::isFull()
{
    return (Table_Size == keysPresent);
}