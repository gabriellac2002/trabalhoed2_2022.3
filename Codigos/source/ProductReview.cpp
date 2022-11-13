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

    cout <<"userId: " << this->userId << endl;
    cout <<"productId: " << this->productId << endl;
    cout <<"rating: " << this->rating << endl; 
    cout <<"timestamp: " << this->timestamp << endl;
    cout << "____________________" << endl;
}


void ProductReview::setProductId(string usId)
{
    this->userId = userId;
}
void ProductReview::setUserId(string prodId)
{
    this->productId = prodId;
}
void ProductReview::setRating(float rat)
{
    this->rating = rat;
}
void ProductReview::setTimestamp(long time)
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