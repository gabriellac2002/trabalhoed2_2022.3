#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "string.h"

#include "../Headers/NodeAvp.h"

using namespace std;

NodeAvp::NodeAvp(int id) //constructor
{
    this->id = id;
    this->parent = NULL;
    this->left = NULL;
    this->right = NULL;
    this->color = 1; // Em uma arvore vermelho e preto, o nó sempre começa com a cor vermelha
}

NodeAvp::~NodeAvp() //destrutor
{

}

NodeAvp::setId(int id)
{
    this->id = id;
}

NodeAvp::setParent(NodeAvp *parent)
{
    this->parent = parent;
}

NodeAvp::setLeft(NodeAvp *left)
{
    this->left = left;
}

NodeAvp::setRigth(NodeAvp *right)
{
    this->right = right;
}

NodeAvp::setEndMemory(int endMemory)
{
    this->endMemory = endMemory;
}

int NodeAvp::getId()
{
    return this->id;  
}

NodeAvp *NodeAvp::getParent()
{
    return this->parent;
}

NodeAvp *NodeAvp::getLeft()
{
    return this->left;
}

NodeAvp *NodeAvp::getRigth()
{
    return this->right;
}

int NodeAvp::getColor()
{
    return this->color;
}

int NodeAvp::getEndMemory()
{
    return this->endMemory;
}