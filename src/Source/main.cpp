#include <iostream>
#include <cstdlib>
#include "../Headers/ProductReview.h"

using namespace std;

int main(int argc, char** argv)
{
    string qualquer_nome(argv[1]);
    ProductReview product(5);
    product.createBinary(qualquer_nome);

    return 0;
}