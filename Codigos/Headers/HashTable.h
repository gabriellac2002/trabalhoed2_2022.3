#ifndef HashTable_H_INCLUDED
#define HashTable_H_INCLUDED

#include <fstream>
#include <vector>
#include <bitset>

#include "../Headers/ProductReview.h"

using namespace std;


class HashTable
{
    private:
        int tamanho; //tamanho da tabela
        list<ProductReview> *table;  //Ponteiro para um array de listas Encadeadas
        int funcaoHash(string& s, int tamanho);
        int colisoes; //Número de Colisões

    public:
        HashTable(int tamanho, funcaoHash(string& s, int tamanho)); //construtor
        ~HashTable(); // destrutor
        void insertItem(); //Insere um valor na tabela Hash
        void displayHash(); //Imprime a Tabela Hash
        void imprimeColisoes(); //Imprime o Número de colisões 
};

#endif // HashTable_H_INCLUDED