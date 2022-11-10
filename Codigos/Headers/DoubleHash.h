#ifndef DoubleHash_H_INCLUDED
#define DoubleHash_H_INCLUDED

#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

#define Max_Size 10000001ll

class DoubleHash
{
    private:
        int Table_Size, keysPresent, prime;
        vector<int> hashTable;
        bitset<Max_Size> isPrime;

    public:
        void __setSieve();
        int inline hash1(int value);
        int inline hash2(int value);
        int inline isFull();
};

#endif // DoubleHash_H_INCLUDED