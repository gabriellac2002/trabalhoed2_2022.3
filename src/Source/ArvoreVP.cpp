#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "string.h"

#include "../Headers/NodeAvp.h"
#include "./NodeAvp.cpp"
#include "../Headers/ArvoreVP.h"

using namespace std;

ArvoreVP::ArvoreVP()
{
    this->raiz = NULL;
}

ArvoreVP::~ArvoreVP()
{
    this->raiz = libera(raiz);
}

NodeAvp ArvoreVP::libera(NodeAvp* node)
{
    if(node != NULL)
    {
        node->getLeft(libera(node->getLeft()));
        node->getRigth(libera(node->getRigth()));
        delete node;
        node = NULL:
    }

    return NULL; 
}

// this function performs left rotation
void ArvoreVP::rotateLeft(NodeAvp* node)
{
    NodeAvp* p_rigth = node->getRigth();
    node->setRigth(p_rigth->getLeft());

    if(node->getRigth() != NULL)
        node->getRigth()->setParent(node);
    p_rigth->setParent(node->getParent());

    if(node->getParent() == NULL)
        raiz = p_rigth;
    else if( node == node->getParent()->getLeft())
        node->getParent()->setLeft(p_rigth);
    else
        node->getParent()->setRigth(p_rigth);
    
    p_rigth->setLeft(node);
    node->setParent(p_rigth);
}

void ArvoreVP::rotateRight(NodeAvp* node)
{
    NodeAvp* p_left = node->getLeft();
    node->setLeft(p_left->getRigth());

    if(node->getLeft() != NULL)
        node->getLeft()->setParent(node);
    p_left->setParent(node->getParent());

    if(node->getParent() == NULL)
        raiz = p_left;
    else if(node == node->getParent()->getLeft())
        node->getParent()->setLeft(p_left);
    else
        node->getParent()->setRigth(p_left);
    
    p_left->setRigth(node);
    node->setParent(p_left);
}

void ArvoreVP::repair(NodeAvp* node1, NodeAvp* node2)
{
    //node1 -> raiz local
    //node2 -> no inserido/no local

    NodeAvp* pai = NULL;
    NodeAvp* avo = NULL;

    //enquanto node2 for diferente de node1,node2 for diferente de preto e o pai de node2 for vermelho
    while((node2 !=  node1) && (node2->getColor() != 0) && (node2->getParent()->getColor() == 1))
    {
        pai = node2->getParent();
        avo = node2->getParent()->getParent();

        //Caso : 1
        //pai do no conflitante está a esquerda do avo de pai
        if(pai == avo->getLeft())
        {
            NodeAvp* tio = avo->getRigth();

            //o avo é vermelho
            if(tio != NULL && tio->getColor() == 1)
            {
                avo->setColor(1); // avo vira vermelho
                pai->setColor(0); // pai vira preto
                tio->setColor(0); // tio vira preto
                node2 = avo;
            }
            else
            {
                // o no conflitante esta a direita de seu pai entao rotaciona para a esquerda
                if(node2 == pai->getRigth())
                {
                    rotateLeft(pai);
                    node2 = pai;
                    pai = node2->getParent();
                }

                //o no conflitante esta a esquerda de seu pai entao rotaciona para a direita
                rotateRight(avo);

                //ajuste de cores
                int corAux = pai->getColor();
                pai->setColor(avo->getColor());
                avo->setColor(corAux);

                node1 = pai;
            }
        }
        else
        {
            // Caso : 2
            // pai do no conflitante é o filho da direita de seu avo

            NodeAvp* tio = avo->getLeft();

            // o tio do no conflitante tambem e vermelho
            if((tio != NULL) && (tio->getColor() == 1))
            {
                avo->setColor(1);
                pai->setColor(0);
                tio->setColor(0);
                node2 = avo;
            }
            else
            {
                // o no conflitante esta a esquerda de seu pai entao rotaciona para a direita
                if(node2 == pai->getLeft())
                {
                    rotateRight(pai);
                    node2 = pai;
                    pai = node2->getParent();
                }

                // o no conflitante esta a direita de seu pai entao rotaciona para a esquerda
                rotateLeft(avo);

                //ajuste de cores
                int corAux = pai->getColor();
                pai->setColor(avo->getColor());
                avo->setColor(corAux);

                node2 = pai;
            }  
           
        }
    }

    node1->setColor(0);
}

void ArvoreVP::insere(ProductReview *pr)
{
    string concatenacao = pr->getUserId.append(pr->getProductId);
    NodeAvp* p = new NodeAvp(concatenacao,)
}