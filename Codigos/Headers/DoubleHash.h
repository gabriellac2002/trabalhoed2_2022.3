#ifndef DoubleHash_H_INCLUDED
#define DoubleHash_H_INCLUDED

#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

#define Max_Size 130

class DoubleHash
{
    private:
        int Table_Size, keysPresent, prime;
        vector<int> hashTable;
        bitset<Max_Size> isPrime;

    public:
        void __setSieve();
        DoubleHash(int n);
        int inline hash1(int value);
        int inline hash2(int value);
        int inline isFull();
        void __printPrime(long long n);
        void insert(int value);
        void erase(int value);
        bool search(int value);
        void print();
};

#endif // DoubleHash_H_INCLUDED