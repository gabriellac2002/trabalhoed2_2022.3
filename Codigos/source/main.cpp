#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <ctime>
#include "time.h"
#include <algorithm>
#include <array>
#include <chrono>
#include "string.h"
#include "../Headers/ProductReview.h"
#include "../Headers/MergeSort.h"
#include "../Headers/QuickSort.h"
#include "../Headers/TimSort.h"

#define PRODUCT_REVIEW_SIZE (46 * sizeof(char))

using namespace std;

void fixAndAddBuffer(fstream &reader, fstream &pointer, string buffer[], int numberOfRegisters)
{
    char trim[] = {',', '\n'};
    for (int i = 0; i < numberOfRegisters; i++)
    {
        // cout<<"cheguei"<<endl;
        char container[buffer[i].length() + 1];
        strcpy(container, buffer[i].c_str());
        char *separated = strtok(container, trim);
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

    // correção do índice a ser buscado
    int x = n - 1;

    fstream binaryArchive;

    binaryArchive.open("ratings_Electronics.bin", ios::in);

    std::string::size_type sz;

    ProductReview productReview;

    string userId;
    string productId;
    string rating;
    string timestamp;

    char review[PRODUCT_REVIEW_SIZE];

    if (binaryArchive.is_open())
    {
        binaryArchive.seekg(x * PRODUCT_REVIEW_SIZE, ios_base::beg);
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
    binaryArchive.open("ratings_Electronics.bin", ios::out | ios::binary);
    int numberofRegisters = numberOfRegisters(csvArchive);
    csvArchive.seekg(0, csvArchive.beg);
    cout << numberofRegisters << endl;
    string buffer[numberofRegisters], buffer1;

    if (csvArchive.is_open())
    {
        while (!csvArchive.eof())
        {
            for (int i = 0; i < numberofRegisters; i++)
            {
                getline(csvArchive, buffer1);
                buffer[i] = buffer1;
            }
            // csvArchive.read((char *)buffer, size);
            fixAndAddBuffer(csvArchive, binaryArchive, buffer, numberofRegisters);
        }
    }
    else
    {
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
    fstream textArchive;

    int ocurrences[n];
    int pos = 0;
    binaryArchive.open("ratings_Electronics.bin", ios::in);
    textArchive.open("test.csv", ios::in);
    int size = numberOfRegisters(textArchive);
    // cout<<"numero total de registros no arquivo = "<<size<<endl;
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
                random = (rand() % size) + 1;
                while (exists(ocurrences, random, pos))
                {
                    random = rand() % size;
                }
                ocurrences[pos] = random;
                pos++;
                if (pos == size)
                {
                    cout << "coletou todos os registros" << endl;
                    return productReview;
                }

                // cout << "numero aleatorio gerado= " << random << endl;
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

int* sort(ProductReview *vet, int n, int methodId)
{
    int comparisons = 0;
    int movements = 0;
    int* metrics;

    switch(methodId)
    {
        case 0:
            metrics = mergeSort(vet, 0, n-1, comparisons, movements);
            break;
        case 1:
            metrics = quickSort(vet, 0, n-1, comparisons, movements);
            break;
        case 2:
            metrics = timSort(vet, comparisons, movements);
            break;  
        default:
            cout <<"Método de organização não encontrado!";
            break;              
    }

    int* metricsSort = metrics;

    return metrics;
}

// Função para criar as Métricas de desempenho dos algoritmos de sorting

void metricsFunction(string pathToFolder, int repetition, int methodId)
{
    ifstream inputArchive(pathToFolder + "input.txt");
    ofstream resultArchive(pathToFolder + "saida.txt", ios_base::app);

    switch(methodId)
    {
        case 0:
            resultArchive << "Resultados das métricas para o MergeSort:\n";
            break;
        case 1:
            resultArchive << "Resultados das métricas para o QuickSort:\n";
            break;
        case 2:
            resultArchive << "Resultados das métricas para o TimSort:\n";
            break;  
        default:
            cout << "Método de organização não encontrado!" << endl;            
    }

    string strN;
    int n;

    int m = 3;

    int comparisons = 0;
    int movements = 0;

    clock_t averageTime = 0;
    float averageMovements = 0;
    float averageComparisons = 0;

    int i = 0;
    while (inputArchive.good() && i < repetition)
    {
        // obtemos os valores de N do input.txt
        i++;
        getline(inputArchive, strN, ',');
        n = stoi(strN);

        resultArchive << "\n______________\n" << "\n";
        resultArchive << "\nResultados para N = " << n <<"\n";

        for(int j = 0; j < m; j++)
        {
            ProductReview *array = import(n);
            // auto start = chrono::high_resolution_clock::now();
            clock_t start_time = clock();
            int* metrics = sort(array, n, methodId);
            clock_t end_time = clock();
            clock_t result  = end_time - start_time;
            // auto stop = chrono::high_resolution_clock::now();
            // auto time = chrono::duration_cast<chrono::microseconds>(stop - start);

            int comparisons = metrics[0];
            int movements = metrics[1];

            delete[] array;

            resultArchive << "\nPara o " << (j+1) << "° conjunto" << "\n";
            resultArchive << "Movimentações: " << movements << " --- Comparações: " << comparisons <<" --- Tempo de Execução(microsegundos): "<< result << "\n";

            averageComparisons += comparisons; 
            averageMovements += movements; 
            averageTime += result;
            
        }

        // calculando as médias
        averageComparisons /= m;
        averageTime /= m;
        averageMovements /= m;

        // escrevendo as informações no arquivo saida.txt
        if(repetition>1)
        resultArchive << "MÉDIAS\n";
        resultArchive << "\nMédia das Movimentações: " << (float)averageMovements << " --- Média das Comparações: " << (float)averageComparisons << " --- Média do tempo de execução: "<< (float)averageTime <<"\n\n";
        resultArchive << "\n______________\n" << "\n";

        // zerando as médias
        averageComparisons = 0;
        averageMovements = 0;
        averageTime = 0;

    }   

    inputArchive.close();
    resultArchive.close();
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

    metricsFunction(path_teste, 5, 1);
}