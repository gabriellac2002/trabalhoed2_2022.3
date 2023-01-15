#ifndef TREEB_H_INCLUDED
#define TREEB_H_INCLUDED

#include <iostream>
#include <bits/stdc++.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <algorithm>

#include "TreeBNo.h" //incluindo o '.h' do Nó da Árvore B
#include "ProductReview.h" //incluindo o '.h' do ProductReview

using namespace std;

class TreeB 
{
    private:
        TreeBNo *raiz; //Ponteiro para o nó raiz
        int t; //grau minimo
        string id; //id da árvore
        int memory; //memória da árvore 

    public:
        TreeB(int grau); //Construtor

        //Função para percorrer a árvore
        void percorrer()
        { if(raiz != NULL) raiz->percorrer(); }

        //Função para buscar chave na árvore
        TreeBNo *buscar(int k)
        {return (raiz == NULL)? NULL : raiz->buscar(k); }

        // A função main que insere uma nova chave
        void inserir(ProductReview *pr, int comparacoes); 

        // Função obrigatória
        void insere(ProductReview *pr, int comparacoes);
        void print();
        ProductReview* busca(string userId, string productId);

        //Funções auxiliares
        void printAux(TreeBNo *p);
};

#endif //TREEB_H_INCLUDED