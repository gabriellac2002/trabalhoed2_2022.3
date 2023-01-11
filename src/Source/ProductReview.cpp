#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <string>

#include "../Headers/ProductReview.h"

#define PRODUCT_REVIEW_SIZE (44*sizeof(char))

using namespace std;

// Função Obrigatória da 1ª Etapa (print)

void ProductReview::print()
{
    cout << "____________________" << endl;
    cout <<"userId: " << this->getUserId() << endl;
    cout <<"productId: " << this->getProductId() << endl;
    cout <<"rating: " << this->getRating() << endl; 
    cout <<"timestamp: " << this->getTimestamp() << endl;
    cout << "____________________" << endl;
}

// getters  e setters do TAD

void ProductReview::setUserId(string userId)
{
    this->userId = userId;
}
void ProductReview::setProductId(string productId)
{
    this->productId = productId;
}
void ProductReview::setRating(float rating)
{
    this->rating = rating;
}
void ProductReview::setTimestamp(string timestamp)
{
    this->timestamp = timestamp;
}

string ProductReview::getProductId()
{
    return this->productId;
}
string ProductReview::getUserId()
{
    return this->userId;
}
float ProductReview::getRating()
{
    return this->rating;
}
string ProductReview::getTimestamp()
{
    return this->timestamp;
}