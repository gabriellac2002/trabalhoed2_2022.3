#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

#include "../Headers/LZW.h"

using namespace std;

LZW::LZW(string str)
{
    this->mensagem = str;
    
    //o vetor de codificação é inicializado com um tamanho equivalente a menor taxa de compressao
    int size = str.size();

    this->sequencia = new string [size*0.6]; //compressao de 40% do tamanho da string
    this->codigo = new int [size*0.6]; //compressao de 40% do tamanho da string
}

string LZW::comprime()
{

}

string LZW::descomprime()
{

}