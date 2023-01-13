#ifndef LZ77_H_INCLUDED
#define LZ77_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "string.h"
#include "CodigoLZ77.h"

using namespace std;

class LZ77
{
    private:
    int Nd;
    int Nb; 
    string ant;
    CodigoLZ77 *Cod;

    public:
    LZ77();
    string comprime(string str);
    string descomprime(string str);
};

#endif // LZ77_H_INCLUDED