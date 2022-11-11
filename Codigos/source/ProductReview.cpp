#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <ctime>

#include "../Headers/ProductReview.h"

#define STRING_MAX_SIZE 128
#define PRODUCT_REVIEW_SIZE (2*sizeof(char)*STRING_MAX_SIZE + sizeof(float) + sizeof(long))

using namespace std;

//construtor vazio
ProductReview::ProductReview()
{

}

ProductReview::ProductReview(char* userId, char* productId, float rating, long timestamp)
{
    strcpy(this->userId,userId);
    strcpy(this->productId,productId);
    this->rating = rating;
    this->timestamp = timestamp;
}

//getters and setters

string ProductReview::getUserId(){
    return this->userId;
}

void ProductReview::setUserId(string userId){
    this->userId = userId;
}

string ProductReview::getProductId(){
    return productId;
}

void ProductReview::setProductId(string productId){
    this->productId = productId;
}

float ProductReview::getRating(){
    return this->rating;
}

void ProductReview::setRating(float rating){
    this->rating = rating;
}

long ProductReview::getTimesTamp(){
    return this->timestamp;
}

void ProductReview::setTimesTamp(long timestamp){
    this->timestamp = timestamp;
}

// // calcula o tamanho do arquivo passado como parâmetro

// int sizeOfArchive(ifstream& archive) 
// {
//     archive.seekg(0, archive.end);
//     int size = archive.tellg();
//     archive.seekg(0);
//     return size;
// }

// // calcula o número de registros no arquivo passado como parâmetro (número de reviews)s

// int numberOfRegisters(ifstream& archive) 
// {
//     if(archive.is_open())
//     {
//         archive.seekg(0, ios_base::end);
//         int number = int(archive.tellg()/sizeof(ProductReview)); 
//         return number; 
//     }
//     else
//     {
//         cout << "Não foi possível abrir o arquivo!" << endl;
//         return 0;
//     }
// }

// // acessa o i-ésimo registro do arquivo binário e o retorna

// ProductReview returnRegister(int n)
// {
//     // correção do índice a ser buscado
//     int x = n - 1;

//     std::ifstream binaryArchive("test.bin");

//     // char* buffer = new char[sizeOfArchive(binaryArchive)];

//     ProductReview productReview;

//     if(binaryArchive.is_open())
//     {
//         binaryArchive.seekg(x*sizeof(ProductReview), ios_base::beg);
//         // binaryArchive.read((char*) buffer, sizeOfArchive(binaryArchive));
//         binaryArchive.read((char *) &productReview, sizeof(ProductReview));
//     }
//     else
//     {
//         cout << "Não foi possível abrir o arquivo!" << endl;
//         cout << "Erro encontrado na função void getReview(int i)" << endl;
//     }

//     return productReview;
// }

// Funções Obrigatórias da 1ª Etapa

void ProductReview::print()
{
    cout << "____________________" << endl;

    // cout <<"userId: " << this->userId << endl;
    for(int i=0; i<14; i++)
    {
        cout << userId[i] << " ";
    }

    // cout <<"productId: " << this->productId << endl;
    for(int i=0; i<10; i++)
    {
        cout << productId[i] << " ";
    }


    cout <<"rating: " << this->rating << endl; 
    cout <<"timestamp: " << this->timestamp << endl;
    cout << "____________________" << endl;

}

void createBinary(string& path) 
{
    std::ifstream csvArchive(path+"test.csv");
    std::fstream binaryArchive("test.bin", ios::out | ios::in | ios::ate | ios::binary | ios::trunc);

    string s;

    while(getline(csvArchive, s)) {
        string userId_;
        string productId_;
        string rating_;
        string timestamp_;

        stringstream temp(s); //lendo o dado do arquivo da serialização

        getline(temp, userId_, ',');
        getline(temp, productId_, ',');
        getline(temp, rating_, ',');
        getline(temp, timestamp_, ',');

        float rating = stof(rating_);

        ProductReview *product = new ProductReview(); 

        product->setUserId(userId_);
        product->setProductId(productId_);
        product->setRating(rating);
        product->setTimesTamp(timestamp_);

        if(csvArchive.is_open())
        {
            binaryArchive.write(reinterpret_cast<const char*>(&product), sizeof(product));
            binaryArchive.read(reinterpret_cast<const char*>(&product), sizeof(product));
        }
        else
        {
            cout << "Erro encontrado na função void createBinary(string& path)" << endl;
        }

    }
    
    

    csvArchive.close();
    binaryArchive.close();

}

// void getReview(int i) 
// {
//     // correção do índice a ser buscado
//     int x = i - 1;

//     std::ifstream binaryArchive("test.bin");

//     // char* buffer = new char[sizeOfArchive(binaryArchive)];

//     ProductReview productReview;

//     if(binaryArchive.is_open())
//     {
//         binaryArchive.seekg(x*sizeof(ProductReview), ios_base::beg);
//         // binaryArchive.read((char*) buffer, sizeOfArchive(binaryArchive));
//         binaryArchive.read((char *) &productReview, sizeof(ProductReview));
//     }
//     else
//     {
//         cout << "Não foi possível abrir o arquivo!" << endl;
//         cout << "Erro encontrado na função void getReview(int i)" << endl;
//     }

//     productReview.print();

// }

// ProductReview *import(int n)
// {
//     ProductReview *productReview =  new ProductReview[n];
//     std::ifstream binaryArchive("test.bin");

//     if(binaryArchive.is_open())
//     {
//         if(numberOfRegisters(binaryArchive) >= n)
//         {
//             srand(time(0));
//             int random;

//             for(int i = 0; i < n ;i++)
//             {
//                 random = rand() % numberOfRegisters(binaryArchive);
//                 productReview[i] = returnRegister(random);
//             }
//         }
//         else
//         {
//             cout << "O número passado excede a quantidade de registros disponíveis a serem acessados!" << endl;
//             return productReview;
//         }

//     }
//     else
//     {
//         cout << "Não foi possível abrir o arquivo!" << endl;
//         cout << "Erro encontrado na função ProductReview *import(int n)" << endl;
//     }
// }