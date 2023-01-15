#ifndef TREEBNO_H_INCLUDED
#define TREEBNO_H_INCLUDED

#include <iostream>
#include <bits/stdc++.h>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

class TreeBNo 
{
    public:
        int *chave; //Série de Chaves
        int t; //Grau mínimo (define o intervalo para o número de chaves)
        TreeBNo **C; //Série de ponteiros filhos
        int n; //Número atual de chaves
        bool folha; //É verdadeiro quando o nó é folha. Caso contrário, falso 
        
        
        TreeBNo(int t, bool leaf); //Construtor 1
        TreeBNo(string id, int memory); //Construtor 2
        ~TreeBNo(); //Destrutor

        void inserirNaoCheia(ProductReview *pr, int k); //Inserir uma nova chave
        void dividirFilho(int i, TreeBNo *y); //Dividir nó
        void percorrer(); //Percorrer todos os nós em uma subarvore onde esse nó é a raiz

        //Buscar nó
        TreeBNo *buscar(string k); //Retorna NULL se k não estiver presente
        void print(); //Imprimir nó
        
    friend class BTree;
};

#endif //TREEBNO_H_INCLUDED