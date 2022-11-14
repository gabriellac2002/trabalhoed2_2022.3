#ifndef HashTable_H_INCLUDED
#define HashTable_H_INCLUDED

#include <fstream>
#include <vector>
#include <bitset>

#include "../Headers/ProductReview.h"

using namespace std;

#define Max_Size 130

class HashTable
{
    private:
        ProductReview **table;
        unsigned int tamanho;
        string enderecoArqBin;
        int tamVetHash;

    public:
        HashTable(unsigned int tam, string enderecoArqBin);
        ~HashTable();

        int get(int key);
        void inserir(char *id);
        void printHash();
        int convertToInt(char *id);
        int busca(char *id);
        void maisFreq(int m, bool teste);
        void quickHash(ProductReview **vet, int p, int r);
        int particionamentoHash(ProductReview **vet, int p, int q);
};

#endif // HashTable_H_INCLUDED