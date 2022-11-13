#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>

#include "../Headers/ProductReview.h"

#define PRODUCT_REVIEW_SIZE (44*sizeof(char))

using namespace std;

// Funções Obrigatórias da 1ª Etapa

void ProductReview::print()
{
    cout << "____________________" << endl;

    cout <<"userId: " << getUserId() << endl;
    cout <<"productId: " << getProductId() << endl;
    cout <<"rating: " << getRating() << endl; 
    cout <<"timestamp: " << getTimestamp() << endl;
    cout << "____________________" << endl;
}


void ProductReview::setProductId(string product)
{
    this->productId = product;
}
void ProductReview::setUserId(string userid)
{
    this->userId = userid;
}
void ProductReview::setRating(string rat)
{
    this->rating = rat;
}
void ProductReview::setTimestamp(string time)
{
    this->timestamp = time;
}

string ProductReview::getProductId()
{
    return this->userId;
}
string ProductReview::getUserId()
{
    return this->productId;
}
string ProductReview::getRating()
{
    return this->rating;
}
string ProductReview::getTimestamp()
{
    return this->timestamp;
}