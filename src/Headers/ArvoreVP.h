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
        NodeAvp libera(NodeAvp* node);
        void rotateLeft(NodeAvp* node);
        void rotateRight(NodeAvp* node);
        void repair(NodeAvp* node1, NodeAvp* node2);
        Node insertHelp(NodeAvp* raiz, int data);
        void insert(int data);
       


    private:
        NodeAvp raiz;

    
};

#endif // ArvoreVP_H_INCLUDED