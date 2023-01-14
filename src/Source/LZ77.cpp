#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

#include "../Headers/LZ77.h"
#include "../Headers/CodigoLZ77.h"

using namespace std;

LZ77::LZ77()
{
    this->Nd = 400;//aloca tamanhos do dicionario e do buffer
    this->Nb = 50;
    this->antc = "";
    this->antd = "";
    //o vetor de codificação é inicializado com um tamanho equivalente a menor taxa de compressao
}

string LZ77::comprime(string str)
{
    string ret,aux;
    aux = this->antc + str;//concatena a mensagem anterior com a atual
    int inicioDicioMen = 0,pos=0;
    int i = 0;
    while(i<str.size()){//ate o fim da mensagem
        int P = 0,L = 0;
        for (int j = 0; j < i+antc.size() || j<this->Nd; j++) {//verifica cada item do inicio da mensagem ate onde o buffer inicia
            if(str[i] == aux[j] ){//se encontra alguma repeticao entre o inicio do buffer e em algum ponto do dicionario
                int k = 0;
                while (str[i+k] == aux[j+k] && k < this->Nb) {//verifica ate onde vai a sequencia
                    k++;//indica o tamanho da sequencia
                }
                if(k > L){
                    L = k;//comprimento da sequencia
                    P = i-j;//posicao atras do inicio do buffer
                }
            }
        }

        ret +="(";//adiciona o termo comprimido a string de retorno
        ret+=to_string(P);
        ret+=",";
        ret+=to_string(L);
        ret+=",";
        ret+=str[i+L];
        ret+=")";

        i += L + 1;//adianta o inicio do buffer para o fim da sequencia + 1 para encobrir a letra que finaliza
    }

    this->antc = str;
    // Return the compressed output as a string
    return ret;
}

string LZ77::descomprime(string str)
{
    string ret,aux;
    int i = 0;
    while(i<str.size()){//para cada termo da string comprimida
        if(str[i] == '('){//encontra cada termo da string comprimida
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
            aux = this->antd + str;
            j++;
            char c = str[j];//char a ser adicionado ao final da sequencia
            j++;
            i = j;
            for(int k = 0;k<l;k++){//concatena a sequencia com os termos a serem repetidos
                ret += aux[this->antd.size()-p+k];
            }
            ret += c;//adiciona o char ao final
            aux = "";
        }
        else{
            ret += str[i];
            i++;
        }
    }

    this->antd = ret;//salva a mensagem descomprimida para ser usada na proxima descompressao
    return ret;

}