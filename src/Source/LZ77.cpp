#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

#include "../Headers/LZ77.h"
#include "../Headers/CodigoLZ77.h"

using namespace std;

LZ77::LZ77(string str)
{
    this->Nd = 4096;
    this->Nb = 18;
    
    this->buffer = new char [Nb];
    this->dicio = new char [Nd];
    //o vetor de codificação é inicializado com um tamanho equivalente a menor taxa de compressao
    int size = str.size();

    this->Cod = new CodigoLZ77 [size*0.6]; //compressao de 40% do tamanho da string
}

string LZ77::comprime(string str)
{
    string ret;
    this->Cod = new CodigoLZ77 [str.size()*0.6];
    int buffer_size = 0, dicio_size = 0,pos=0;
    this->mensagem = new char [str.size() + 1];
    strcpy(mensagem, str.c_str());
    for(int i =0;i<str.size();i++){
        this->buffer[buffer_size] = this->mensagem[i];
        int offset = 0,length = 0;
        for (int j = 0; j < dicio_size; j++) {
            if(buffer[0] == dicio[j] ){
                int k = 0;
                while (buffer[k] == dicio[j+k] && k < buffer_size) {
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
        cod.setC(buffer[length]);
        this->Cod[pos] = cod;

        buffer_size -= length;

        // std::memmove(buffer, buffer + length, buffer_size);

        // // Shift the matching substring and the next character into the sliding window
        // std::memmove(window + length + 1, window, WINDOW_SIZE - length - 1);
        // std::memcpy(window, input.c_str() + i - offset, length + 1);
        // window_size = std::min(window_size + length + 1, WINDOW_SIZE); AAAAAAAAAA REVER ESSA PARTE COMEENTADA AAAAAAAAA
    }

    // Return the compressed output as a string
    return ret;
}

string LZ77::descomprime(string str)
{
    
}