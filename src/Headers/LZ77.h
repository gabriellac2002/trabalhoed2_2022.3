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
    string mensagem;
    char *buffer;//o cursos aponta para a primeira casa do buffer
    char *dicio;
    char *pointer;
    CodigoLZ77 *Cod;

    public:
    LZ77(int ND,int NB,string str);
    string comprime();
    string descomprime();
};

#endif // LZ77_H_INCLUDED