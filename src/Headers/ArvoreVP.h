#ifndef ArvoreVP_H_INCLUDED
#define ArvoreVP_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "string.h"

#include "../Headers/NodeAvp.h"
#include "../Source/NodeAvp.cpp"

using namespace std;

class ArvoreVP
{
    public:
        ArvoreVP();
        ~ArvoreVP();
        Node libera(Node* node);
        Node rotateLeft(Node* node);
        Node rotateRight(Node* node);
        Node insertHelp(Node* raiz, int data);
        void insert(int data);
        void printTreeHelper(Node* root, int space);


    private:
        NodeAvp raiz;

    
};

#endif // ArvoreVP_H_INCLUDED