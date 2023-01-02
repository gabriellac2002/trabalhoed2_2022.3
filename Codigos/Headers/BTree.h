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
};

#endif // BTree_H_INCLUDED