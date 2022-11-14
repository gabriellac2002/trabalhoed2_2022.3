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

// calcula o tamanho do arquivo passado como parâmetro

int sizeOfArchive(fstream& archive) 
{
    archive.seekg(0, archive.end);
    int size = archive.tellg();
    archive.seekg(0);
    return size;
}

void fixAndAddBuffer(fstream &reader, fstream &pointer, string buffer[])
{
    char trim[] = {',', '\n'};
    for(int i = 0; i < 15; i++)
    {
        char container [buffer[i].length() + 1];
        strcpy(container, buffer[i].c_str());
        char *separated = strtok(container, trim);
        int counter = 0, size, total = 0;
        string line;

        while (separated)
        {
            line = separated;
            switch (counter)
            {
            case 0: // userId
                size = 21 - line.length();
                for (int i = 0; i < size; i++)
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
                size = 10 - line.length();
                for (int i = 0; i < size; i++)
                {
                    line += "?";
                }
                pointer.write((char *)line.c_str(), 10);
                counter++;
                break;
            default:
                counter = 0;
                break;
            }
            separated = strtok(NULL, trim);
        }
    }    
}

// calcula o número de registros no arquivo passado como parâmetro (número de reviews)

int numberOfRegisters(ifstream& archive) 
{
    if (archive.is_open())
    {
        int number = 0;
        string line;
        while(!archive.eof())
        {
            getline(archive,line);
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
    // correção do índice a ser buscado
    int x = n - 1;

    fstream binaryArchive;

    binaryArchive.open("test.bin", ios::in);

    std::string::size_type sz;

    // char* buffer = new char[sizeOfArchive(binaryArchive)];

    ProductReview productReview;

    string userId;
    string productId;
    string rating;
    string timestamp;

    char review[PRODUCT_REVIEW_SIZE];

    if (binaryArchive.is_open())
    {
        binaryArchive.seekg(x * PRODUCT_REVIEW_SIZE, ios_base::beg);
        // binaryArchive.read((char*) buffer, sizeOfArchive(binaryArchive));
        binaryArchive.read((char *)&review, PRODUCT_REVIEW_SIZE);
        userId = strtok(review, "?");
        productReview.setUserId(userId);
        productId = strtok(NULL, "?");
        productReview.setProductId(productId);
        rating = strtok(NULL, "?");
        productReview.setRating(rating);
        timestamp = strtok(NULL, "?");
        productReview.setTimestamp(timestamp);
    }
    binaryArchive.close();
    return productReview;
}

// Funções Obrigatórias da 1ª Etapa (createBinary, getReview, import)

void createBinary(string &path)
{
    std::fstream csvArchive;
    csvArchive.open(path + "test.csv", ios::in | ios::binary);

    std::fstream binaryArchive;
    binaryArchive.open("test.bin", ios::out | ios::binary);

    int sizeofFile = sizeOfArchive(csvArchive);
    string buffer[15], bufferAux;

    if (csvArchive.is_open())
    {
        while (!csvArchive.eof())
        {
            for(int i = 0; i < 15; i++)
            {
                getline(csvArchive, bufferAux);
                buffer[i] = bufferAux;
            }
            // csvArchive.read((char *)buffer, size);
            fixAndAddBuffer(csvArchive, binaryArchive, buffer);
        }
    }
    else
    {
        cout << "Não foi possível abrir o arquivo!" << endl;
        cout << "Erro encontrado na função void createBinary(string& path)" << endl;
    }

    csvArchive.close();
    binaryArchive.close();
}

void getReview(int i)
{
    // correção do índice a ser buscado
    int x = i - 1;

    fstream binaryArchive;

    binaryArchive.open("test.bin", ios::in);

    char review[PRODUCT_REVIEW_SIZE];
    char *separated;

    if (binaryArchive.is_open())
    {
        binaryArchive.seekg(x * PRODUCT_REVIEW_SIZE, ios_base::beg);
        // binaryArchive.read((char*) buffer, sizeOfArchive(binaryArchive));
        binaryArchive.read((char *)&review, PRODUCT_REVIEW_SIZE);
        separated = strtok(review, "?");
        for(int i = 0; i < 4; i++)
        {
            cout << separated << endl;
            separated = strtok(NULL, "?");
        }
    }
    else
    {
        cout << "Não foi possível abrir o arquivo!" << endl;
        cout << "Erro encontrado na função void getReview(int i)" << endl;
    }

    binaryArchive.close();
}

bool exists(int ocurrences[], int number, int position)
{
    for(int i = 0; i <=position; i++)
        if(ocurrences[i] == number)
            return true;
    return false;        
}

ProductReview *import(int n)
{
    ProductReview *productReview = new ProductReview[n];
    ifstream binaryArchive;
    ifstream textArchive;

    int ocurrences [n];
    int position = 0;
    binaryArchive.open("test.bin",ios::in);
    textArchive.open("test.csv",ios::in);
    int size = numberOfRegisters(textArchive);
    cout<< "Número total de registros no arquivo = " << size <<endl;
    if (binaryArchive.is_open() && textArchive.is_open())
    {
        if (size >= n)
        {
            srand(time(0));
            int random;
            // bool exists = std::find(std::begin(a), std::end(a), x) != std::end(a);
            for (int i = 0; i < n; i++)
            {
                // cout<<"cheguei"<<endl;
                random = rand() % size;
                while(exists(ocurrences, random, position))
                {
                    random = rand() % size;
                }
                ocurrences[position] = random;
                position++;
                if(position == size)
                {
                    cout<< "Coletou todos os registros!" <<endl;
                    return productReview;
                }

                cout << "Número aleatório gerado = " << random << endl;
                productReview[i] = returnRegister(random);
            }
        }
        else
        {
            cout << "O número passado excede a quantidade de registros disponíveis a serem acessados!" << endl;
            return productReview;
        }
    }
    else
    {
        cout << "Não foi possível abrir o arquivo!" << endl;
        cout << "Erro encontrado na função ProductReview *import(int n)" << endl;
    }

    return productReview;
}

// Funções Obrigatórias da 2ª Etapa

void sort(ProductReview *vet, int n, int methodId)
{
    switch(methodId)
    {
        case 0:
            // espaço para a chamada do MergeSort
            break;
        case 1:
            // espaço para a chamada do QuickSort
            break;
        case 2:
            // espaço para a chamada do CountingSort
            break;  
        default:
            cout <<"Método de organização não encontrado!";              
    }
}

// Função para criar as Métricas de desempenho dos algoritmos de sorting

void metricsFunction()
{
    
}

int main(int argc, char** argv)
{
    string path_teste(argv[1]);
    ProductReview productReview;

    createBinary(path_teste);
    getReview(1);
    cout << "-------------------------" << endl;
    ProductReview *teste = new ProductReview[5];
    teste = import(5);

    for (int i = 0; i < 5; i++)
    {
        teste[i].print();
    }
}