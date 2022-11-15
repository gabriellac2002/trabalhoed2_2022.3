#ifndef HashTable_H_INCLUDED
#define HashTable_H_INCLUDED

#include <fstream>
#include <vector>
#include <bitset>

#include "../Headers/ProductReview.h"
#include "../Headers/RegistroHash.h"

#define MAX_SIZE 1000000111

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
        for(long long i = 2; i*i <= MAX_SIZE; i++)
            if(isPrime[i] == 0)
                for(long long j = i*i; j <= MAX_SIZE; j += i)
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
            valor = 31 * valor + (int)id[i];
        }
        return valor;
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
        __setSieve();
        tamanho_tabela = n;
 
        n_primo = tamanho_tabela - 1;
        while(isPrime[n_primo] == 1)
            n_primo--;
 
        quant_chaves = 0;

        

        for(int i = 0; i < tamanho_tabela; i++){
            RegistroHash r1;
            r1.productId = " ";
            r1.qtdReviews = -1;
            hashTable.push_back(r1);
        }
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
        int valor = converterInteiro(registro.productId);
 
        if(valor == -1 || valor == -2){
            cout<<("ERROR : -1 and -2 can't be inserted in the table\n"); 
        }
 
        if(estaCheio()){
            cout<<("ERROR : Hash Table Full\n");
            return;
        }
         
        int probe = hash1(valor), offset = hash2(valor); 

        //mapeando onde o valor vai entrar na tabela hash 
        // -1 -> quando não tem valor
        while(hashTable[probe].qtdReviews != -1){
            if(-2 == hashTable[probe].qtdReviews)                 
                break;                                  
            probe = (probe+offset) % tamanho_tabela;
        }
 
        hashTable[probe] = registro;
        quant_chaves += 1;
    }

    // bool search(int value){
    //     int probe = hash1(value), offset = hash2(value), initialPos = probe;
    //     bool firstItr = true;
 
    //     while(1){
    //         if(hashTable[probe] == -1)                   // Stop search if -1 is encountered.
    //             break;
    //         else if(hashTable[probe] == value)           // Stop search after finding the element.
    //             return true;
    //         else if(probe == initialPos && !firstItr)    // Stop search if one complete traversal of hash table is completed.
    //             return false;
    //         else
    //             probe = ((probe + offset) % tamanho_tabela);  // if none of the above cases occur then update the index and check at it.
 
    //         firstItr = false;
    //     }
    //     return false;
    // }

    /* Function to display the hash table. */
    void print(){
        for(int i = 0; i < tamanho_tabela; i++)
            cout<<hashTable[i].productId<<", ";
        cout<<"\n";
    }
};

#endif // HashTable_H_INCLUDED