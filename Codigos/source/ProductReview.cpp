#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>

#include "../Headers/ProductReview.h"

#define PRODUCT_REVIEW_SIZE (44*sizeof(char))

using namespace std;

// Função Obrigatória da 1ª Etapa (print)

void ProductReview::print()
{
    cout << "____________________" << endl;

    cout <<"userId: " << getUserId() << endl;
    cout <<"productId: " << getProductId() << endl;
    cout <<"rating: " << getRating() << endl; 
    cout <<"timestamp: " << getTimestamp() << endl;
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
void ProductReview::setRating(string rating)
{
    this->rating = rating;
}
void ProductReview::setTimestamp(string timestamp)
{
    this->timestamp = timestamp;
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