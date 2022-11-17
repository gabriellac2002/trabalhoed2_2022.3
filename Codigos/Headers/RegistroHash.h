#ifndef RegistroHash_H_INCLUDED
#define RegistroHash_H_INCLUDED

#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

typedef struct
{
    string productId;
    int qtdReviews;
} RegistroHash;

RegistroHash SetRegistro(string productId, int qtdReviews)
{
    RegistroHash registro;
    registro.productId = productId;
    registro.qtdReviews = qtdReviews;
    return registro;
}

string getProductId(RegistroHash registro)
{
    return registro.productId;
}

int getQtdReviews(RegistroHash registro)
{
    return registro.qtdReviews;
}

#endif // HashTable_H_INCLUDED