#include <iostream>
#include <cstdlib>
#include "BTree.h"
#include "BTreeNode.h"

using namespace std;

//Contrutor (inicializa a árvore como vazia)
BTree::BTree(int _t)
{
    root = NULL;
    t = _t;
}

//Função para percorrer a árvore
void BTree::traverse()
{
    if (root != NULL)
        root->traverse();
}