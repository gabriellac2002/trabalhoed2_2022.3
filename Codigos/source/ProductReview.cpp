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

int sizeOfArchive(ifstream& archive) 
{
    archive.seekg(0, archive.end);
    int size = archive.tellg();
    archive.seekg(0);
    return size;
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

    csvArchive.close();
    binaryArchive.close();

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

    std::ifstream is("test.bin", ios::binary | ios::in);

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
        item.setRating(stof(vector[2]));
        item.setTimestamp(stol(vector[3]));

        binaryVector[i] = item;
    }

    return binaryVector;
}
