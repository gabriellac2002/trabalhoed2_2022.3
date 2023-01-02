#ifndef NodeAvp_H_INCLUDED
#define NodeAvp_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "string.h"

using namespace std;

class NodeAvp
{
    public:

    NodeAvp(string id, int endMemory);
    ~NodeAvp();
    void setId(string id);
    void setParent(NodeAvp *parent);
    void setLeft(NodeAvp *left);
    void setRigth(NodeAvp *right);
    void setColor(int color);
    void setEndMemory(int endMemory);
    string getId();
    NodeAvp* getParent();
    NodeAvp* getLeft();
    NodeAvp* getRigth();
    int getColor();
    int getEndMemory();


    private:
    
    int id; // holds the key
	NodeAvp *parent; // pointer to the parent
	NodeAvp *left; // pointer to left child
	NodeAvp *right; // pointer to right child
	int color; // 1 -> Red, 0 -> Black
    int endMemory; //endereço no arquivo binario

};

#endif // NodeAvp_H_INCLUDED