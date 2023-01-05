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
    char* mensagem;
    char *buffer;//o cursos aponta para a primeira casa do buffer
    char *dicio;
    char *pointer;
    CodigoLZ77 *Cod;

    public:
    LZ77(string str);
    string comprime(string str);
    string descomprime(string str);
};

#endif // LZ77_H_INCLUDED