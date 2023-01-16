#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

#include "../Headers/NodeHuffman.h"
#include "../Headers/Huffman.h"

using namespace std;

// Construtor

NodeHuffman::NodeHuffman(char content, long frequence)
{
    this->content = content;
    this->frequence = frequence;
    this->left = nullptr;
    this->right = nullptr;
}

// Destrutor

NodeHuffman::~NodeHuffman() { }

// Getters e Setters

char NodeHuffman::getContent() 
{
    return content;
}

void NodeHuffman::setContent(char content) 
{
    NodeHuffman::content = content;
}

long NodeHuffman::getFrequence() 
{
    return frequence;
}

void NodeHuffman::setFrequence(long frequence) 
{
    NodeHuffman::frequence = frequence;
}

NodeHuffman *NodeHuffman::getLeft() 
{
    return left;
}

void NodeHuffman::setLeft(NodeHuffman *left) 
{
    NodeHuffman::left = left;
}

NodeHuffman *NodeHuffman::getRight() 
{
    return right;
}

void NodeHuffman::setRight(NodeHuffman *right) 
{
    NodeHuffman::right = right;
}

int NodeHuffman::isLeaf() 
{
    return !(this->left) && !(this->right);
}