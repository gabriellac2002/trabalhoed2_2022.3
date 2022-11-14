#include <iostream>
#include <iomanip>
#include <string.h>

#include "../Headers/HashTable.h"
#include "../Headers/ProductReview.h"

using namespace std;

HashTable::HashTable(unsigned int tam, string enderecoArqBin)
{
    this->enderecoArqBin = enderecoArqBin; // Definindo o endereço do arquivo
    this->tamVetHash = 0;
    this->tamanho = tam; // Tamanho do vetor da Hash

    table = new ProductReview *[tamanho]; // Alocando dinamicamente o vetor contendo ProductReview

    for(int i = 0; i < tamanho; i++)
        table[i] = nullptr; // Inicializando todas as posições como nullptr
}

