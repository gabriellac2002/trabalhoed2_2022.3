#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

#include "../Headers/LZ77.h"
#include "../Headers/CodigoLZ77.h"

using namespace std;

LZ77::LZ77(int ND,int NB,string str)
{
    this->Nd = ND;
    this->Nb = NB;
    this->mensagem = str;
    
    this->buffer = new char [Nb];
    this->dicio = new char [Nd];
    //o vetor de codificação é inicializado com um tamanho equivalente a menor taxa de compressao
    int size = str.size();

    this->Cod = new CodigoLZ77 [size*0.6]; //compressao de 40% do tamanho da string
}

string LZ77::comprime()
{

}

string LZ77::descomprime()
{

}