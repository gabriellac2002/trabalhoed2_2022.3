#ifndef HashTable_H_INCLUDED
#define HashTable_H_INCLUDED

#include <fstream>
#include <vector>
#include <bitset>

#include "../Headers/ListaDupla.h"
#include "../Headers/ProductReview.h"

using namespace std;


class HashTable
{
    private:
        int tamanho; //tamanho da tabela
        ProductReview **table;  //Ponteiro para um array de listas Encadeadas
        int funcaoHash(const string& string);
        int colisoes; //Número de Colisões

    public:
        HashTable(int tamanho); //construtor
        ~HashTable(); // destrutor
        void insertItem(ProductReview product); //Insere um valor na tabela Hash
        void displayHash(); //Imprime a Tabela Hash
        void imprimeColisoes(); //Imprime o Número de colisões 
};

#endif // HashTable_H_INCLUDED