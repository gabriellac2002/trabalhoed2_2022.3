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

void createBinary(string& path) 
{
    std::ifstream csvArchive(path+"test.csv");
    std::fstream binaryArchive("test.bin", ios::out | ios::in | ios::ate | ios::binary | ios::trunc);

    string str, str2;
    char* buffer = new char[sizeOfArchive(csvArchive)];
    
    if(csvArchive.is_open())
    {
        int size = sizeOfArchive(csvArchive);
        csvArchive.read((char*) buffer, size);

        for(int i=0; i<=sizeOfArchive(csvArchive); i++)
        {
            cout << buffer[i] << endl;
            str = buffer[i];
            binaryArchive.write(reinterpret_cast<const char*>(&str), sizeof(str));
        }   
        
        binaryArchive.read(reinterpret_cast<char*>(&str2), sizeof(str2));

        cout << str2;
        
    }
    else
    {
        cerr << "ERRO: O arquivo não pôde ser aberto!" << endl;
    }

}

void ProductReview::getReview(int i) 
{
    std::ifstream binaryArchive("test.bin");
}

ProductReview *import(int n)
{

}