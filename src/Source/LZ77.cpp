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
    this->Cod = new CodigoLZ77 [str.size()*0.6];//cria um vetor de codificação com o tamanho da mensagem * 0.6, como a taxa de compressao é de 40%, media/pior caso
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

        CodigoLZ77 cod;
        cod.setP(P);
        cod.setL(L);
        cod.setC(str[i+L+1]);
        cod.setConfirma();
        this->Cod[pos] = cod;

        i += L + 1;//adianta o inicio do buffer para o fim da sequencia + 1 para encobrir a letra que finaliza
    }

    for(int i =0;i<str.size()*0.6;i++){//para cada item no vetor de compressao, concatena a string de retorno com o codigo
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

    this->antc = ret;
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