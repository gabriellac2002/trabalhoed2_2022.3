#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "string.h"

#include "../Headers/NodeAvp.h"

using namespace std;

NodeAvp::NodeAvp(string id) //constructor
{
    this->id = id;
    this->parent = NULL;
    this->left = NULL;
    this->right = NULL;
    this->color = 1; // Em uma arvore vermelho e preto, o nó sempre começa com a cor vermelha
    this->product = NULL;
}

NodeAvp::~NodeAvp() //destrutor
{

}

//setters
void NodeAvp::setColor(int color)
{
    this->color = color;
}


void NodeAvp::setId(string id)
{
    this->id = id;
}

void NodeAvp::setParent(NodeAvp *parent)
{
    this->parent = parent;
}

 void NodeAvp::setLeft(NodeAvp *left)
{
    this->left = left;
}

void NodeAvp::setRigth(NodeAvp *right)
{
    this->right = right;
}


void NodeAvp::setProduct(ProductReview *product)
{
    this->product = product;
}

//getters

string NodeAvp::getId()
{
    return id;  
}

NodeAvp *NodeAvp::getParent()
{
    return parent;
}

NodeAvp *NodeAvp::getLeft() //esquerda
{
    return left;
}

NodeAvp *NodeAvp::getRigth() //direita
{
    return right;
}

int NodeAvp::getColor()
{
    return color;
}


ProductReview* NodeAvp::getProduct()
{
    return product;
}