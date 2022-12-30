#ifndef LZW_H_INCLUDED
#define LZW_H_INCLUDED

#include <iostream>
#include <fstream>
#include "string.h"

using namespace std;

class LZW
{
    private:
    string mensagem;
    char *buffer;//o cursos aponta para a primeira casa do buffer
    //dicionario é a tabela ascii
    char *pointer;
    string *sequencia;//pega apenas os items que nao estao na ascii = com mais de 1 char
    int *codigo;

    public:
    LZW(string str);
    string comprime();
    string descomprime();
};

#endif // LZW_H_INCLUDED