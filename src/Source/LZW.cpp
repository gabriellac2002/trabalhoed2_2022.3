#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>
#include <algorithm>
#include <array>

#include "../Headers/LZW.h"

using namespace std;

    // //o vetor de codificação é inicializado com um tamanho equivalente a menor taxa de compressao
    // int size = str.size();

    // this->sequencia = new string [size*0.6]; //compressao de 40% do tamanho da string
    // this->codigo = new int [size*0.6]; //compressao de 40% do tamanho da string
LZW::LZW()
{    
    this->dicionariobase = new string [91]; //parte usada da tabela ascii
    this->dicionario = new string [91];
    for (int i =0;i<91;i++){//preenchendo o dicionario
        this->dicionariobase[i] = char(i);
        this->dicionario[i] = char(i);
    }
    this->ver = 0;
}

void LZW::adicionaDicio(string str){
    int tam = sizeof(this->dicionario);
    string *newdicio = new string [tam+1];
    for(int i =0;i<tam;i++){
        newdicio[i] = this->dicionario[i];
    }

    newdicio[tam] = str;
    this->dicionario = newdicio;
}

int LZW::existDicio(string str){
//repetir a funcao ate encontrar a sequencia que nao existe
    for(int i =0;i<sizeof(this->dicionario);i++){
        if(this->dicionario[i]==str)
            return i;
    }//retorna a posicao do item se ja existir no dicionario

    return -1;
}

string LZW::comprime(string str)
{
    string ret;
    char c;
    int add;
    this->buffer = "";
    for(int i =0;i<str.size();i++){
        c = this->mensagem[i];
        add = existDicio(this->buffer + c);
        if(buffer.size()==0 || add!=-1)
            this->buffer = this->buffer + c; 
        
        else{
            adicionaDicio(this->buffer);
            this->buffer = c;
            ret = ret + "(" + to_string(add) + ")";
        }
    }
    return ret;
}

string LZW::descomprime(string str)
{
    if(this->ver == 0){
        this->dicionario = this->dicionariobase;//retorna o dicionario para o estado inicial
        this->ver = 1;
    }
    string ret,ant ="";
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '(')
        {
            int j = i + 1;
            string num = "";
            while (str[j] != ')')
            {
                num = num + str[j];
                j++;
            }
            int pos = stoi(num);//aponta o numero correto da posicao do dicionario a ser resgatada
            ret = ret + this->dicionario[pos];
            ant = ant + this->dicionario[pos][0];
            adicionaDicio(ant);
            ant = this->dicionario[pos];
        }
    }
    return ret;
}