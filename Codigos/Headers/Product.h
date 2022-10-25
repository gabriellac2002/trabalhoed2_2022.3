#ifndef PRODUTO_H
#define PRODUTO_H

#include <fstream>

using namespace std;

#define STR_MAX_SIZE 128
#define PRODUTO_SIZE (sizeof(char)STR_MAX_SIZE + 2sizeof(int) + sizeof(float))

class Product
{
    public:
        Product();
        Product(const char* userId, const char* productId, float rating, long timestamp);

        void LerDoArquivoBinario(fstream &file);
        void EscreverNoArquivoBinario(fstream &file);
        void Imprimir();
        void printId();

    private:
        char _userId[STR_MAX_SIZE];
        char _productId[STR_MAX_SIZE];
        float _rating;
        long _timestamp;
};


#endif /* ESTUDENT_H__ */