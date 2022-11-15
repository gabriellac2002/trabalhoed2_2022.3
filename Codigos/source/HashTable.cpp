#include <iostream>
#include <iomanip>
#include <string.h>

#include "../Headers/HashTable.h"
#include "../Headers/ProductReview.h"

using namespace std;

// HashTable::HashTable(int tamanho)
// {
//     this->tamanho = tamanho;
//     this->colisoes = 0;
//     this->table = new list<ProductReview>[this->tamanho]
// }

// HashTable::~HashTable()
// {
//     delete[] this->table;
// }


//a função hash escolhida foi a função de hash de rolamento polinomial, tirada do site geekforgeeks
// int HashTable::funcaoHash(string& string, int tamanho)
// {
//   int p = 31, m = 1e9 + 7;
    // int tam_string = string.length();

    // int hash_value = 0;
    // long p_pow = 1;
    // for(int i = 0; i < tam_string; i++) {
    //     hash_value = (hash_value + (string[i] - 'a' + 1) * p_pow) % m;
    //     p_pow = (p_pow * p) % m;
    // }
    // return abs(hash_value);
// }

// void HashTable::insertItem(ProductReview product)
// {
//     int valor = stoi(insert.getProductId());
//     int i = this->funcaoHash(value, this->tamanho);

//     //verifica se vai haver uma colisão e se tem algum valor repetido
//     if( !this->table[i].isEmpty() && !this->table[i].search(valor))
//     {
//         this->colisoes = this->colisoes +1;
//     }

//     this->table[i].insert(value);
// }