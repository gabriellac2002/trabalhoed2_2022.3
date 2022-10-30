#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <string>

#include "../Headers/ProductReview.h"

#define STRING_MAX_SIZE 128
#define PRODUCT_REVIEW_SIZE (2 * sizeof(char) * STRING_MAX_SIZE + sizeof(float) + sizeof(long))

using namespace std;

// void ProductReview::print()
// {

// }

void ProductReview::createBinary(string &path)
{
    std::ifstream ler(path + "test.csv");
    std::fstream escrever("test.bin", ios::out | ios::in | ios::ate | ios::binary);

    string s;
    // le linha a linha do arquivo
    while (getline(ler, s))
    {
        string userId;
        string productId;
        float rating;
        long timestamp;
        stringstream temp(s); // lendo o dado do arquivo da serialização
        // Product produto;
        int z = 0;
        while (getline(temp, s, ','))
        { // separa por virgula
            switch (z)
            {
            case 0:
                userId = s;
                z++;
                break;
            case 1:
                productId = s;
                z++;
                break;
            case 2:
                rating = stof(s); // converte string pra float
                z++;
                break;

            default:
                timestamp = stoi(s); // converte string pra int
                z++;
                break;
            }
        }

        Product produto(userId.c_str(), productId.c_str(), rating, timestamp);

        produto.EscreverNoArquivoBinario(escrever);
        // produto2.LerDoArquivoBinario(escrever);
        // produto.Imprimir();

        // cout<< prduto2.userId << "," << produto.productId << "," << produto.rating << "," << produto.timestamp<< '\n';
    }

    ler.close();
    Product produto2 = Product();
    escrever.seekg(0, ios::beg);
    produto2.LerDoArquivoBinario(escrever);
    produto2.Imprimir();
    produto2.LerDoArquivoBinario(escrever);
    produto2.Imprimir();
    produto2.LerDoArquivoBinario(escrever);
    produto2.Imprimir();
    escrever.close();
    // std::fstream escrever2("ratings_Electronics.bin", ios::out | ios::in | ios::ate | ios::binary);
}

void ProductReview::getReview(int i)
{

    std::ifstream is("test.txt", ios::binary);

    int registerSize = PRODUCT_REVIEW_SIZE;

    for (int j = 0; j < i; j++)
    {
        is.seekg(0, is.beg);
        int position = i + 1;
        int startPosition = (position * registerSize);
        int endPosition = startPosition + registerSize;
        is.seekg(startPosition, is.end);
    }
}

void ProductReview::setUserId(string uId)
{
    this->userId = uId;
}

void ProductReview::setProductId(string pId)
{
    this->productId = pId;
}

void ProductReview::setRating(float rat)
{
    this->rating = rat;
}

void ProductReview::setTimestamp(long time)
{
    this->timestamp = time;
}

ProductReview *import(int n)
{

    std::ifstream is("test.txt", ios::binary | ios::in);

    ProductReview *binaryVector = new ProductReview[n];
    int registerSize = PRODUCT_REVIEW_SIZE;
    char *data = new char[registerSize];
    string dataString;
    string *vector = new string[4];
    stringstream s_stream(dataString);
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        is.seekg(0, is.beg);
        int position = rand() % n;
        int startPosition = (position * registerSize);
        int endPosition = startPosition + registerSize;
        is.seekg(startPosition, is.end);
        is.read(data, registerSize);
        dataString = data;
        while (s_stream.good())
        {
            string substr;
            getline(s_stream, substr, ','); // get first string delimited by comma
            vector[count] = substr;
            count++;
        }
        ProductReview item;
        item.setProductId(vector[0]);
        item.setUserId(vector[1]);
        item.setRating(stol(vector[2]));
        item.setRating(stoi(vector[3]));

        binaryVector[i] = item;
    }

    return binaryVector;
}
