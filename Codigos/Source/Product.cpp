#include <cstring>
#include <iostream>
#include <fstream>

#include "../Headers/Product.h"

Product::Product(): _userId(""), _productId(""), _rating(0), _timestamp(0)
{};

Product::Product(const char* userId, const char* productId, float rating, long timestamp)
{
    strcpy(_userId,userId);
    strcpy(_productId,productId);
    _rating = rating;
    _timestamp = timestamp;
}

void Product::LerDoArquivoBinario(fstream &file)
{
    file.read((char*)&_userId, sizeof(_userId));
    file.read((char*)&_productId, sizeof(_productId));
    file.read((char*)&_rating, sizeof(_rating));
    file.read((char*)&_timestamp, sizeof(_timestamp));
}

void Product::EscreverNoArquivoBinario(fstream &file)
{
    file.write((char*)&_userId, sizeof(_userId));
    file.write((char*)&_productId, sizeof(_productId));
    file.write((char*)&_rating, sizeof(_rating));
    file.write((char*)&_timestamp, sizeof(_timestamp));
}

void Product::Imprimir()
{
    cout <<"userId: "      << this->_userId << endl;
    cout <<"productId: " << this->_productId << endl;
    cout <<"rating: "       << this->_rating << endl; 
    cout <<"timestamp: "       << this->_timestamp << endl;
}