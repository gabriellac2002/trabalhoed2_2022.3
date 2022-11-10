#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>

#include "../Headers/ProductReview.h"

#define STRING_MAX_SIZE 128
#define PRODUCT_REVIEW_SIZE (2*sizeof(char)*STRING_MAX_SIZE + sizeof(float) + sizeof(long))

using namespace std;

int sizeOfArchive(ifstream& archive) 
{
    archive.seekg(0, archive.end);
    int size = archive.tellg();
    archive.seekg(0);
    return size;
}

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
void ProductReview::setRating(float rat){
    this->rating = rat;
}
void ProductReview::setTimestamp(long time){
    this->timestamp = time;
}