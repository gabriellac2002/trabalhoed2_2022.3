#ifndef LZW_H_INCLUDED
#define LZW_H_INCLUDED

#include <iostream>
#include <fstream>
#include "string.h"

using namespace std;

class LZW
{
    private:
    char *mensagem;
    string buffer;//o cursos aponta para a primeira casa do buffer
    string *dicionariobase;//parte da tabela ascii
    string *dicionario;//contem as partes que nao estao na tabela ascii
    int ver;
    string *sequencia;//pega apenas os items que nao estao na ascii = com mais de 1 char
    int *codigo;

    public:
    LZW();
    int existDicio(string str);
    void adicionaDicio(string str);
    string comprime(string str);
    string descomprime(string str);
};

#endif // LZW_H_INCLUDED