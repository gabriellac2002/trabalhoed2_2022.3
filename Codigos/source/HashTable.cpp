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

// Conferir a desalocação da tabela
HashTable::~HashTable()
{
    for(int i = 0; i < tamanho; ++i) {
        ProductReview *entrada = table[i];
        ProductReview *proximo = table[i + 1];

        while (entrada != nullptr) // percorre por todos os registros contidos no mesmo endereço da Tabela Hash e os desaloca
        {
            ProductReview *anterior = entrada;
            //entrada = entrada->proximo
            delete anterior;
        }
        
    }

    delete [] table;
}

int HashTable::convertToInt(char *id)
{
    int valor, tam;
    valor = 7;
    tam = strlen(id);

    for(int i = 0; i < tam; i++) {
        valor = 31 * valor + (int)id[i];
    }

    return valor;
}

void HashTable::inserir(char *id)
{

}

void HashTable::printHash()
{
    ProductReview **aux = table;
    ProductReview *no;

    for(int i = 0; i < tamanho; i++) {
        no = aux[i];

        if(no != nullptr) {
            while (no != nullptr)
            {
                cout << "Posiçãp da Hash: " << i << "; ID do usuário: " << no->getUserId() << endl;
                //Para a proxima posicao da tabela
            }
            
        }

        else
            cout << "Posição da Hash: " << i << " = NULL" << endl;
    }
}