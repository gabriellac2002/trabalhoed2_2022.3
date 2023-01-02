#ifndef ArvoreVP_H_INCLUDED
#define ArvoreVP_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "string.h"

#include "../Headers/NodeAvp.h"
#include "../Source/NodeAvp.cpp"
#include "../Headers/ProductReview.h"
#include "../Source/ProductReview.cpp"

using namespace std;

class ArvoreVP
{
    public:
        ArvoreVP();
        ~ArvoreVP();
        NodeAvp libera(NodeAvp* node);
        void rotateLeft(NodeAvp* node);
        void rotateRight(NodeAvp* node);
        void repair(NodeAvp* node1, NodeAvp* node2);
        void insere(ProductReview *pr); // funcao obrigatoria
        ProductReview* busca(string userId, string productId); // funcao obrigatoria
        void print(); // funcao obrigatoria

    private:
        NodeAvp raiz;

    
};

#endif // ArvoreVP_H_INCLUDED