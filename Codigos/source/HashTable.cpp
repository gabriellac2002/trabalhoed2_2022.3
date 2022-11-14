#include <iostream>
#include <iomanip>
#include <string.h>

#include "../Headers/HashTable.h"
#include "../Headers/ProductReview.h"

using namespace std;

HashTable::HashTable(int tamanho, funcaoHash(string& s, int linhas))
{
    this->tamanho = tamanho;
    this->funcaoHash = funcaoHash;
    this->colisoes = 0;
    this->table = new list<ProductReview>[this->tamanho]
}

HashTable::~HashTable()
{
    delete[] this->table;
}