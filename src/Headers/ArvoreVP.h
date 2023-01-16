#ifndef ArvoreVP_H_INCLUDED
#define ArvoreVP_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "string.h"

#include "../Headers/NodeAvp.h"
#include "../Headers/ProductReview.h"


using namespace std;

class ArvoreVP
{
    public:
        ArvoreVP();
        ~ArvoreVP();
        void setRaiz(NodeAvp* raiz);
        NodeAvp* getRaiz();
        NodeAvp* libera(NodeAvp* node);
        void rotateLeft(NodeAvp* node);
        void rotateRight(NodeAvp* node);
        void repair(NodeAvp* node1, NodeAvp* node2);
        void insere(ProductReview *pr); // funcao obrigatoria
        NodeAvp* insereAux(NodeAvp* p, NodeAvp* no);
        ProductReview* busca(string userId, string productId); // funcao obrigatoria
        NodeAvp* buscaAux(NodeAvp * no, string id);
        void print(); // funcao obrigatoria
        void printAux(NodeAvp* p);
        int count=0;

    private:
        NodeAvp* raiz;
        int tempo;
        int comparacoes = 0;

    
};

#endif // ArvoreVP_H_INCLUDED