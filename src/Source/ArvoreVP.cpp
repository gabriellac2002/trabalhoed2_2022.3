#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "string.h"

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

Node ArvoreVP::libera(Node* node)
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
Node ArvoreVP::rotateLeft(Node* node)
{
    Node x = node->getRigth();
    Node y = x->getLeft();

    x->setLeft(node);

    node->setRigth(y);
    node->setParent(x);

    if( y != NULL)
        y->setParent(node);
    return(x);
}

Node ArvoreVP::rotateRight(Node* node)
{
    Node x = node.left;
    Node y = x.right;
    x.right = node;
    node.left = y;
    node.parent = x;
    if(y!=null)
        y.parent = node;
    return(x);
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