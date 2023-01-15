#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>
#include <algorithm>
#include <array>

#include "../Headers/LZW.h"

using namespace std;

LZW::LZW()
{    
    this->dicionariobase = new string [256]; //parte usada da tabela ascii
    this->dicionario = new string [256]; // tem-se a utilização de 2 dicionarios para agilizar o processo de descompressão
    for (int i =33;i<256;i++){//preenchendo o dicionario
        this->dicionariobase[i] = char(i);
        this->dicionario[i] = char(i);
    }
    this->sizedicio = 256;
    this->ver = 0; //verificador para saber se o dicionario esta no estado inicial
}

void LZW::adicionaDicio(string str){//adiciona uma sequencia ao dicionario
    int tam = this->sizedicio;
    this->sizedicio++;//aumenta o tamanho do dicionario
    string *newdicio = new string [this->sizedicio];//realoca o vetor do dicionario
    for(int i =0;i<tam;i++){
        newdicio[i] = this->dicionario[i];//realoca todos os itens do dicionario
    }

    newdicio[tam] = str;
    this->dicionario = newdicio;
}

int LZW::existDicio(string str){//verifica se uma sequencia existe no dicionario
    for(int i =0;i<this->sizedicio;i++){
        if(this->dicionario[i] == str)
            return i;
    }
    return -1;
}

string LZW::comprime(string str)
{
    string ret,ant,atual;
    int add;
    this->buffer = "";
    for(int i =0;i<str.size();i++){//para cada caractere da mensagem
        atual = str[i];
        add = existDicio(this->buffer + atual); //verifica se a sequencia ja existe no dicionario
        if(buffer.size()==0 || add!=-1){
            this->buffer = this->buffer + atual; //caso exista, adiciona o proximo caractere a sequencia
            ant = atual;
        }
        
        else{//caso ela nao exista no dicionario
            adicionaDicio(this->buffer + atual); //adiciona a sequencia no dicionario
            ret = ret + "(" + to_string(existDicio(this->buffer)) + ")";
            this->buffer = atual;
        }
    }

    if(this->buffer.size()>0){//caso a sequencia nao tenha sido adicionada ao dicionario
        ret = ret + "(" + to_string(existDicio(this->buffer)) + ")";
    }
    return ret;
}

string LZW::descomprime(string str)
{
    if(this->ver == 0){//caso o dicionario ainda nao tenha sido reiciado para a descompressao da mensagem total
        this->dicionario = this->dicionariobase;//retorna o dicionario para o estado inicial
        this->ver = 1;//evita que ele seja reinciado a cada descompressao
    }
    string ret,ant ="";
    int i =0;
    while (i < str.size()/2)//para cada caractere da mensagem comprimida
    {
        if (str[i] == '(')//encontra o inicio de uma indicação de compressao
        {   
            int j = i + 1;
            string num = "";
            while (str[j] != ')')//encontra o final da indicação de compressao, totalizando seu numero
            {
                num = num + str[j];
                j++;
            }
            i = j + 1; 
            int pos = stoi(num);//aponta o numero correto da posicao do dicionario a ser resgatada
            ret = ret + this->dicionario[pos];//concatena a mensagem descomprimida com a sequencia resgatada do dicionario
            ant = ant + this->dicionario[pos][0];
            if(ant.size()>1){
                adicionaDicio(ant);//adiciona a mensagem descomprimida ao dicionario, tendo em vista que nao havera outra sequencia igual  no dicionario
            }
            ant = this->dicionario[pos];
        }
    }
    return ret;
}