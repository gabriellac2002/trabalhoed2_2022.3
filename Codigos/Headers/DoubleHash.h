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
        DoubleHash(int Table_Size, int keysPresent, int prime, vector<int> hasgTable, bitset<Max_Size> isPrime);
        ~DoubleHash();
        void __setSieve();
        int inline hash1(int value);
        int inline hash2(int value);
        int inline isFull();
};

#endif // DoubleHash_H_INCLUDED