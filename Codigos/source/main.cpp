#include <iostream>
#include <cstdlib>
#include "../Headers/ProductReview.h"

using namespace std;

int main(int argc, char** argv)
{
    string qualquer_nome(argv[1]);
    ProductReview product;
    product.createBinary(qualquer_nome);
    product.getReview(4);

    return 0;
}