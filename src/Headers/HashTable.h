#ifndef HashTable_H_INCLUDED
#define HashTable_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "string.h"

#include "../Headers/ProductReview.h"
#include "../Headers/RegistroHash.h"

#define MAX_SIZE 7824483

using namespace std;


class HashTable
{
    int tamanho_tabela, quant_chaves, n_primo;
    vector<RegistroHash> hashTable; //tabela hash
    bitset<MAX_SIZE> isPrime; 

    //garante que isPrime é primo
    void __setSieve()
    {
        isPrime[0] = isPrime[1] = 1;
        for(long i = 2; i*i <= MAX_SIZE; i++)
            if(isPrime[i] == 0)
                for(long j = i*i; j <= MAX_SIZE; j += i)
                    isPrime[j] = 1;
 
    }

    int converterInteiro(string idRegistro)
    {
        char id[ idRegistro.length() + 1];
        strcpy(id, idRegistro.c_str());


        int i, valor = 7;
        int tam = strlen(id);
        for (int i = 0; i < tam; i++)
        {
            valor += ((int)id[i]);
        }
        return 31 * valor;
    }

    int inline hash1(int valor){
        return valor % tamanho_tabela;
    }

    int inline hash2(int valor){      
        return n_primo - (valor % n_primo);
    }

    bool inline estaCheio(){
        return (tamanho_tabela == quant_chaves);
    }

    public:

    HashTable(int n){
        // cout << "a" << endl;
        __setSieve();
        tamanho_tabela = n;
        // cout << "b" << endl;
        n_primo = tamanho_tabela - 1;
        while(isPrime[n_primo] == 1)
            n_primo--;
        // cout << "c" << endl;
        quant_chaves = 0;

        // cout << "d" << endl;

        for(int i = 0; i < tamanho_tabela; i++){
            RegistroHash r1;
            r1.productId = "";
            r1.qtdReviews = 0;
            hashTable.push_back(r1);
        }
        // cout << "e" << endl;
    }

    void __printPrime(long long n){
        for(long long i = 0; i <= n; i++)
            if(isPrime[i] == 0)
                cout<<i<<", ";
        cout<<endl;
    }

    /* Function to insert value in hash table */
    void insert(RegistroHash registro)
    {
        // cout << "id: " << registro.productId << endl;
        // cout << "inteiro: " << converterInteiro(registro.productId) << endl;
        int valor = converterInteiro(registro.productId);
 
        if(valor == -1 || valor == -2){
            cout<<"ERROR : -1 and -2 can't be inserted in the table\n" << endl;
        }
 
        if(estaCheio()){
            cout<<"ERROR : Hash Table Full\n" <<endl;
            return;
        }
         
        int probe = hash1(valor), offset = hash2(valor); 
        // cout << "offset: " << offset << endl;

        //mapeando onde o valor vai entrar na tabela hash 
        // -1 -> quando não tem valor
        while(hashTable[probe].qtdReviews != 0 && hashTable[probe].productId != registro.productId)
        {
            probe = (probe+31) % tamanho_tabela;
        }
 
        hashTable[probe].productId = registro.productId;
        hashTable[probe].qtdReviews++;
        quant_chaves += 1;
    }


    /* Function to display the hash table. */
    void print(){
        for(int i = 0; i < tamanho_tabela; i++)
            cout<<hashTable[i].productId<<", ";
        cout<<"\n";
    }

    RegistroHash getHashTable(int i)
    {
        return hashTable[i];
    }
};

#endif // HashTable_H_INCLUDED