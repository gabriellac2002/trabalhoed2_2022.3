#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

#include "../Headers/LZ77.h"
#include "../Headers/CodigoLZ77.h"

using namespace std;

LZ77::LZ77()
{
    this->Nd = 400;
    this->Nb = 50;
    this->ant = "";
    //o vetor de codificação é inicializado com um tamanho equivalente a menor taxa de compressao
}

string LZ77::comprime(string str)
{
    string ret,aux;
    aux = this->ant + str;
    this->Cod = new CodigoLZ77 [str.size()*0.6];
    int inicioDicioMen = 0,pos=0;
    int i = 0;
    while(i<str.size()){//ate o fim da mensagem
        int offset = 0,length = 0;
        for (int j = 0; j < i+ant.size() || j<this->Nd; j++) {//verifica cada item do inicio da mensagem ate onde o buffer inicia
            if(str[i] == aux[j] ){//se encontra alguma repeticao entre o inicio do buffer e em algum ponto do dicionario
                int k = 0;
                while (str[i+k] == aux[j+k] && k < this->Nb) {//verifica ate onde vai a sequencia
                    k++;
                }
                if(k > length){
                    length = k;
                    offset = j;
                }
            }
        }

        CodigoLZ77 cod;
        cod.setP(offset);
        cod.setL(length);
        cod.setC(str[i+length+1]);
        cod.setConfirma();
        this->Cod[pos] = cod;

        i += length + 1;//adianta o inicio do buffer para o fim da sequencia + 1 para encobrir a letra que finaliza
    }

    for(int i =0;i<str.size()*0.6;i++){
        if(this->Cod[i].getConfirma() == 1){
            ret += "(";
            ret += to_string(this->Cod[i].getP());
            ret += ",";
            ret += to_string(this->Cod[i].getL());
            ret += ",";
            ret += this->Cod[i].getC();
            ret += ")";
        }
    }

    this->ant = ret;
    // Return the compressed output as a string
    return ret;
}

string LZ77::descomprime(string str)
{
    string ret,aux;
    int i = 0;
    while(i<str.size()){
        if(str[i] == '('){
            int j = i+1;
            while(str[j] != ','){
                aux += str[j];
                j++;
            }
            int p = stoi(aux);//posicao atras do atual inicio do buffer
            aux = "";
            j++;
            while(str[j] != ','){
                aux += str[j];
                j++;
            }
            int l = stoi(aux);//tamanho da sequencia 
            aux = this->ant + str;
            j++;
            char c = str[j];//char a ser adicionado ao final da sequencia
            j++;
            i = j;
            for(int k = 0;k<l;k++){
                ret += aux[this->ant.size()-p+k];
            }
            ret += c;
            aux = "";
        }
        else{
            ret += str[i];
            i++;
        }
    }

    this->ant = ret;
    return ret;

}