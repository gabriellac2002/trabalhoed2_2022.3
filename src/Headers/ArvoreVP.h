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
        Node libera(NodeAvp* node);
        Node rotateLeft(NodeAvp* node);
        Node rotateRight(NodeAvp* node);
        Node insertHelp(NodeAvp* raiz, int data);
        void insert(int data);
       


    private:
        NodeAvp raiz;

    
};

#endif // ArvoreVP_H_INCLUDED