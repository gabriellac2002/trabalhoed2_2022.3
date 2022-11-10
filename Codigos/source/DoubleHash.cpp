#include <iostream>
#include <vector>
#include <bitset>

#include "../Headers/DoubleHash.h"

using namespace std;

#define Max_Size 130

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

void DoubleHash::__printPrime(long long n)
{
    for(long long i = 0; i <= n; i++) {
        cout << i << ", ";
    }

    cout << endl;
}

// Function to insert value in hash table
void DoubleHash::insert(int value)
{
    if(value == -1 || value == -2) {
        cout << "ERROR: -1 and -2 can't be inserted in the table" << endl;
    }

    if(isFull()) {
        cout << "ERROR: Hash Table Full" << endl;
    }

    int probe = hash1(value), offset = hash2(value); // In linear probing offset = -1

    while (hashTable[probe] != -1) {
        if(-2 == hashTable[probe])
            break;
        probe = (probe + offset) % Table_Size;
    }

    hashTable[probe] = value;
    keysPresent += 1;
}

void DoubleHash::erase(int value)
{
    // Return if element is not present
    if(!search(value)) {
        return;
    }

    int probe = hash1(value), offset = hash2(value);

    while(hashTable[probe] != -1){
        if(hashTable[probe] == value) {
            hashTable[probe] = -2; //mark element as deleted (rather than unvisited(-1))
            keysPresent--;
            return;
        }

        else
            probe = (probe + offset) % Table_Size;
    }
}

bool DoubleHash::search(int value)
{
    int probe = hash1(value), offset = hash2(value), initialPos = probe;
    bool firstItr = true;

    while (1) {
        if(hashTable[probe] == -1)
            break;
        else if(hashTable[probe] == value)
            return true;
        else if(probe == initialPos && !firstItr)
            return false;
        else
            probe = ((probe +  offset) % Table_Size);

        firstItr = false;
    }

    return;    
}

// Function to display the hash table
void DoubleHash::print()
{
    for(int i = 0; i < Table_Size; i++) {
        cout << hashTable[i];
    }

    cout << endl;
}