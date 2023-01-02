#ifndef BTree_H_INCLUDED
#define BTree_H_INCLUDED

#include "BTreeNode.h"

using namespace std;

class BTree
{
    private:
        BTreeNode *root; //Ponteiro para a raiz
        int t; // Grau minimo

    public:
        BTree(int _t); // Construtor
        
        //Uma função para percorrer todos os nós em uma subárvore com raiz enraizada com este nó
        void traverse();

        //Uma função para pesquisar uma chave na subárvore com raiz enraizada com este nó
        BTreeNode *search(int k); //retorna NULL se a chave não for encontrada
};

#endif // BTree_H_INCLUDED