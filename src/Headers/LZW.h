#ifndef LZW_H_INCLUDED
#define LZW_H_INCLUDED

#include <iostream>
#include <fstream>
#include "string.h"

using namespace std;

class LZW
{
    private:
    string buffer;//o cursos aponta para a primeira casa do buffer
    string *dicionariobase;//parte da tabela ascii
    string *dicionario;//contem as partes que nao estao na tabela ascii
    int sizedicio;//tamanho do dicionario atual
    int ver;//verificação para a reinicialização do dicionario
    string *sequencia;//pega apenas os items que nao estao na ascii = com mais de 1 char
    float sizeOri;//tamanho da mensagem original
    float sizeComp;//tamanho da mensagem comprimida

    public:
    LZW();
    int existDicio(string str);
    void adicionaDicio(string str);
    string comprime(string str,string path);
    string descomprime(string str);
};

#endif // LZW_H_INCLUDED