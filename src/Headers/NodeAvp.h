#ifndef NodeAvp_H_INCLUDED
#define NodeAvp_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "string.h"

#include "./ProductReview.h"

using namespace std;

class NodeAvp
{
    public:

    NodeAvp(string id);
    ~NodeAvp();
    void setId(string id);
    void setParent(NodeAvp *parent);
    void setLeft(NodeAvp *left);
    void setRigth(NodeAvp *right);
    void setColor(int color);
    void setProduct(ProductReview *product);
    string getId();
    NodeAvp* getParent();
    NodeAvp* getLeft();
    NodeAvp* getRigth();
    int getColor();
    ProductReview* getProduct();
    
    


    private:
    
    string id; // id
	NodeAvp *parent; // ponteiro para o pai
	NodeAvp *left; // ponteiro para o nó a esuqerda
	NodeAvp *right; // ponteiro para o nó a direita
	int color; // 1 -> vermelho   0-> preto
    ProductReview *product;

};

#endif // NodeAvp_H_INCLUDED