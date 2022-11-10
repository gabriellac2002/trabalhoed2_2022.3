#include <fstream>
#include <vector>
#include <bitset>

#include "../Headers/DoubleHash.h"

using namespace std;

// Handline of collision via open addressing
// Method for Probing: Double Hashing


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

DoubleHash::DoubleHash(int n)
{
    __setSieve();
    Table_Size = n;

    // Find the largest prime number smaller than table's size
    prime = Table_Size - 1;
    while (isPrime[prime] == 1) {
        prime--;
    }
    
    keysPresent = 0;

    //Fill the hash table with -1 (empty entries)
    for(int i = 0; i < Table_Size; i++) {
        hashTable.push_back(-1);
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
