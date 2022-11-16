#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <array>
#include "string.h"
#include "../Headers/ProductReview.h"

#define PRODUCT_REVIEW_SIZE (46 * sizeof(char))

using namespace std;

void fixAndAddBuffer(fstream &pointer, string buffer[], int sizeOfBuffer)
{
    for (int i = 0; i < sizeOfBuffer; i++)
    {
        char container[buffer[i].length() + 1];
        strcpy(container, buffer[i].c_str());
        char *separated = strtok(container, ",\\n");
        int counter = 0, tam, total = 0;
        string line;
        while (separated)
        {
            line = separated;
            switch (counter)
            {
            case 0: // userId
                tam = 21 - line.length();
                for (int i = 0; i < tam; i++)
                {
                    line += "?";
                }
                pointer.write((char *)line.c_str(), 21);
                counter++;
                break;
            case 1: // productId
                line += "?";
                pointer.write((char *)line.c_str(), 11);
                counter++;
                break;
            case 2: // rating
                line += "?";
                pointer.write((char *)line.c_str(), 4);
                counter++;
                break;
            case 3: // timestamp
                tam = 10 - line.length();
                for (int i = 0; i < tam; i++)
                {
                    line += "?";
                }
                line += "??";
                pointer.write((char *)line.c_str(), 10);
                counter++;
                break;
            default:
                counter = 0;
                break;
            }
            separated = strtok(NULL, ",\\n");
        }
    }
}

// calcula o número de registros no arquivo passado como parâmetro (número de reviews)s

int numberOfRegisters(fstream &archive)
{
    if (archive.is_open())
    {
        int number = 0;
        string line;
        while (!archive.eof())
        {
            getline(archive, line);
            number++;
        }
        return number;
    }
    else
    {
        cout << "Não foi possível abrir o arquivo!" << endl;
        return 0;
    }
}

// acessa o i-ésimo registro do arquivo binário e o retorna

ProductReview returnRegister(int n)
{
    fstream binaryArchive;
    binaryArchive.open("ratings_Electronics.bin", ios::in);
    // correção do índice a ser buscado
    int x = n - 1;

    ProductReview productReview;

    char *separated;

    char review[PRODUCT_REVIEW_SIZE];

    if (binaryArchive.is_open())
    {
        binaryArchive.seekg(x * PRODUCT_REVIEW_SIZE, ios_base::beg);
        binaryArchive.read((char *)&review, PRODUCT_REVIEW_SIZE);
        separated = strtok(review, "?");
        productReview.setUserId(separated);
        separated = strtok(NULL, "?");
        productReview.setProductId(separated);
        separated = strtok(NULL, "?");
        productReview.setRating(separated);
        separated = strtok(NULL, "?");
        productReview.setTimestamp(separated);
    }
    else
    {
        cout << "Não foi possível abrir o arquivo!" << endl;
        cout << "Erro encontrado na função ProductReview *import(int n), em returnRegister" << endl;
    }
    binaryArchive.close();
    return productReview;
}

// Funções Obrigatórias da 1ª Etapa

void createBinary(string &path, char **argv)
{
    std::fstream csvArchive;
    csvArchive.open(path + "ratings_Electronics.csv", ios::in | ios::binary);
    std::fstream binaryArchive;
    binaryArchive.open("ratings_Electronics.bin", ios::out | ios::binary);
    int numberofRegisters = 7824483;
    cout << "numero de registros = " << numberofRegisters << endl;
    csvArchive.seekg(0, csvArchive.beg);
    string buffer[10000], buffer1;
    if (csvArchive.is_open())
    {
        for (int j = 0; j < 10000 && !csvArchive.eof(); j++)
        {
            getline(csvArchive, buffer1, '\n');
            buffer1.erase(std::remove(buffer1.begin(), buffer1.end(), '\n'), buffer1.cend());
            buffer[j] = buffer1;
        }
        fixAndAddBuffer(binaryArchive, buffer, 10000);
    }
    else
    {
        cout << "Erro encontrado na funcao void createBinary(string& path)" << endl;
    }
    csvArchive.close();
    binaryArchive.close();
}

void getReview(int i)
{
    // correção do índice a ser buscado
    int x = i - 1;

    fstream binaryArchive;

    binaryArchive.open("ratings_Electronics.bin", ios::in);

    char review[PRODUCT_REVIEW_SIZE];
    char *separated;

    if (binaryArchive.is_open())
    {
        binaryArchive.seekg(x * PRODUCT_REVIEW_SIZE, ios_base::beg);
        binaryArchive.read((char *)&review, PRODUCT_REVIEW_SIZE);
        separated = strtok(review, "?");
        for (int i = 0; i < 4; i++)
        {
            cout << separated << endl;
            separated = strtok(NULL, "?");
        }
    }
    else
    {
        cout << "Nao foi possivel abrir o arquivo!" << endl;
        cout << "Erro encontrado na função void getReview(int i)" << endl;
    }

    binaryArchive.close();
}

ProductReview *import(int n)
{
    ProductReview *productReview = new ProductReview[n];
    fstream binaryArchive;
    fstream textArchive;

    int size = 7824483;
    if (size >= n)
    {
        int random;
        srand((unsigned)time(NULL));
        cout << "chegou no import" << endl;
        for (int i = 0; i < n; i++)
        {
            int random;
            srand((unsigned)time(NULL));
            for (int i = 0; i < n; i++)
            {
                random = (rand() % size) + 1;
                productReview[i] = returnRegister(random);
                if (i == n - 1)
                {
                    cout << "cabo o for" << endl;
                }
            }
        }
    }

    else
    {
        cout << "O número passado excede a quantidade de registros disponíveis a serem acessados!" << endl;
        return productReview;
        cout << "Nao foi possivel abrir o arquivo!" << endl;
        cout << "Erro encontrado na funcao ProductReview *import(int n)" << endl;
    }

    return productReview;
}

int main(int argc, char **argv)
{
    string path_teste(argv[1]);
    ProductReview productReview;
    createBinary(path_teste, argv);
    getReview(1);
    ProductReview *teste = new ProductReview[10000];
    teste = import(50000);

    for (int i = 0; i < 5; i++)
    {
        teste[i].print();
    }

    return 0;
}