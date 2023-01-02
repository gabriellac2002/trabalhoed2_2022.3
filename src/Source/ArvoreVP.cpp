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

Node ArvoreVP::insertHelp(Node raiz, int data)
{
    // f is true when RED RED conflict is there.
    boolean rr = false;

    //recursive calls to insert at proper position according to BST properties.
    if(raiz == NULL)
     return(new Node(data));
    else if(data < raiz->data)
    {
        raiz->setLeft(insertHelp(raiz->getLeft(),data));
        raiz->
    }
}