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
#include "../Headers/HashTable.h"
#include "../Headers/RegistroHash.h"
#include "../Headers/LZ77.h"
#include "../Headers/LZW.h"
#include "../Headers/Huffman.h"

#define PRODUCT_REVIEW_SIZE (41 + sizeof(float))

using namespace std;
using namespace chrono;

// COMANDOS PARA RODAR O PROGRAMA:
// g++ *.cpp -o final
// .\final.exe .\ 

// Função para gerar um número aleatório do intervalo entre a e b

int randomNumber(int a, int b)
{
    return a + rand()%(b - a + 1); 
}

// Funções Obrigatórias da 1ª Etapa (createBinary, getReview, import)

void createBinary(string &path)
{
    ifstream csvArchive(path + "/ratings_Electronics.csv");

    int size = 7824483;
    int userIdSize = 21;
    int productIdSize = 10;
    int timestampSize = 10;

    if (csvArchive.is_open())
    {
        ofstream binaryArchive(path + "ratings_Electronics.bin", ios::binary);
        string strUserId, strProductId, strRating, strTimestamp;
        float rating;

        for (int i = 0; i < size; i++)
        {
            getline(csvArchive, strUserId, ',');
            getline(csvArchive, strProductId, ',');
            getline(csvArchive, strRating, ',');
            getline(csvArchive, strTimestamp, '\n');
            rating = stof(strRating);
            binaryArchive.write(reinterpret_cast<const char*>(strUserId.c_str()), userIdSize);
            binaryArchive.write(reinterpret_cast<const char*>(strProductId.c_str()), productIdSize);
            binaryArchive.write(reinterpret_cast<const char*>(&rating), sizeof(float));
            binaryArchive.write(reinterpret_cast<const char*>(strTimestamp.c_str()), timestampSize);
        }

        binaryArchive.close();
        csvArchive.close();
    }
    else
    {
        cout << "Error! Could not open cvs file! (Error at createBinary)" << endl;
    }
}

void getReview(int i, string &path)
{
    ifstream binaryArchive(path + "ratings_Electronics.bin", ios::binary);

    int userIdSize = 21;
    int productIdSize = 10;
    int timestampSize = 10;

    binaryArchive.seekg((i-1) * PRODUCT_REVIEW_SIZE);
    ProductReview productReview;

    char *userId = new char[userIdSize];
    userId[21] = '\0';
    char *productId = new char[productIdSize];
    productId[10] = '\0';
    char *timestamp = new char[timestampSize];
    timestamp[10] = '\0';
    float rating;

    binaryArchive.read(reinterpret_cast<char *>(userId), userIdSize);
    binaryArchive.read(reinterpret_cast<char *>(productId), productIdSize);
    binaryArchive.read(reinterpret_cast<char *>(&rating), sizeof(float));
    binaryArchive.read(reinterpret_cast<char *>(timestamp), timestampSize);

    productReview.setUserId(userId);
    productReview.setProductId(productId);
    productReview.setRating(rating);
    productReview.setTimestamp(timestamp);

    delete[] userId;
    delete[] productId;
    delete[] timestamp;

    binaryArchive.close();

    productReview.print();
}

// Função para retornar um registro x

ProductReview returnRegister(ifstream *file, int i)
{
    int userIdSize = 21;
    int productIdSize = 10;
    int timestampSize = 10;

    file->seekg(i * PRODUCT_REVIEW_SIZE);
    ProductReview *productReview = new ProductReview();

    char *userId = new char[userIdSize];
    userId[21] = '\0';
    char *productId = new char[productIdSize];
    productId[10] = '\0';
    char *timestamp = new char[timestampSize];
    timestamp[10] = '\0';
    float rating;

    file->read(reinterpret_cast<char *>(userId), userIdSize);
    file->read(reinterpret_cast<char *>(productId), productIdSize);
    file->read(reinterpret_cast<char *>(&rating), sizeof(float));
    file->read(reinterpret_cast<char *>(timestamp), timestampSize);

    productReview->setUserId(userId);
    productReview->setProductId(productId);
    productReview->setRating(rating);
    productReview->setTimestamp(timestamp);

    delete[] userId;
    delete[] productId;
    delete[] timestamp;

    return *productReview;
}

// Função para importar um vetor de n registros aleatórios

ProductReview *import(int n)
{
    int size = 7824483;
    ifstream binaryArchive;
    binaryArchive.open("ratings_Electronics.bin", ios::in | ios::binary);
    if (!binaryArchive.is_open())
    {
        cout << "Error! Could not open binary file! (Error at import)" << endl;
        return NULL;
    }

    ProductReview* productReviews = new ProductReview[n];
    for (int i = 0; i < n; i++)
    {
        productReviews[i] = returnRegister(&binaryArchive, i+1);
        // productReviews[i].print();
    }

    binaryArchive.close();

    return productReviews;
}

// Funções Obrigatórias da 2ª Etapa

void sort(ProductReview *vet, int n, int methodId, int* comparisons, int* movements)
{
    switch(methodId)
    {
        case 0:
            mergeSort(vet, 0, n-1, comparisons, movements);
            break;
        case 1:
            quickSort(vet, 0, n-1, comparisons, movements);
            break;
        case 2:
            timSort(vet, comparisons, movements);
            break;  
        default:
            cout <<"Sorting method not found!";
            break;              
    }
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

    double averageTime = 0;
    int averageMovements = 0;
    int averageComparisons = 0;

    int i = 0;
    while (inputArchive.good() && i < repetition)
    {
        // obtemos os valores de N do input.txt
        getline(inputArchive, strN);
        n = stoi(strN);

        resultArchive << "\n______________\n" << "\n";
        resultArchive << "\nResultados para N = " << n <<"\n";

        // ProductReview *array = import(n);

        for(int j = 0; j < m; j++)
        {
            int comparisons;
            int movements;
            double time = 0;

            comparisons = 0;
            movements = 0;

            ProductReview *array = import(n);
            high_resolution_clock::time_point start = high_resolution_clock::now();
            // clock_t start_time = clock();
            sort(array, n, methodId, &comparisons, &movements);
            // clock_t end_time = clock();
            // clock_t result  = end_time - start_time;
            high_resolution_clock::time_point stop = high_resolution_clock::now();
            time = duration_cast<duration<double>>(stop - start).count();

            delete[] array;

            resultArchive << "\nPara o " << (j+1) << "° conjunto" << "\n";
            resultArchive << "Movimentações: " << movements << " --- Comparações: " << comparisons <<" --- Tempo de Execução(segundos): "<< time << "\n";

            averageComparisons += comparisons; 
            averageMovements += movements; 
            averageTime += time;
            
        }

        // delete[] array;

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

        i++;

    }   

    inputArchive.close();
    resultArchive.close();
}


// quicksort para o hashing

void swap(RegistroHash* a, RegistroHash* b)
{
    RegistroHash aux = *a;
    *a = *b;
    *b = aux;
}

int partition(RegistroHash* array, int low, int high)
{
    RegistroHash pivot = array[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
  
    for (int j = low; j <= high - 1; j++) 
    {
        if (array[j].qtdReviews >= pivot.qtdReviews) 
        {
            i++; // incrementa o índice do menor elemento
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quickSort(RegistroHash* array, int low, int high)
{
    if (low < high) 
    {
        // pi é o índice de particionamento
        int pi = partition(array, low, high);
  
        // Separadamente ordena os elementos anteriores partição após partição
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

RegistroHash* createTable(int n)
{
    ProductReview* productReviews = import(n);
    HashTable *tabela = new HashTable(n);

    for(int i = 0; i < n; i++)
    {
        RegistroHash r;
        r.productId = productReviews[i].getProductId();
        r.qtdReviews = 1;
        tabela->insert(r);
    }

    RegistroHash *registro = new RegistroHash[n];

    for(int i=0; i<n; i++)
    {
        registro[i] = tabela->getHashTable(i);
    }

    return registro;
}

 void orderByRating(RegistroHash *registro, int p, int n)
 {
    // int c = sizeof(registro);
    quickSort(registro, 0, n-1);
    for(int i = 0; i < p; i++)
            cout<< "ID do produto: " << registro[i].productId << " --- Reviews: " << registro[i].qtdReviews << endl;
 }

 //  Funções Auxiliares daSegundaEtapa

 string concatRegisters(ProductReview *vet, int n)
 {
    string str = " ";
    for(int i = 0; i<n; i++)
    {
        string aux = vet[i].getProductId() + vet[i].getUserId() + to_string(vet[i].getRating()) + vet[i].getTimestamp();
        str += aux;
    }

    return str;

 }

 char* returnContent (string str)
 {
    
 }

 long* returnFrequence (string str)
 {

 }

 // Funções de Compresssão

 string comprime(string str, int metodo){

    string ret;
    switch (metodo)
    {
    case 1:
        Huffman *huffman = new Huffman();
        break;

    case 2:
        LZ77 *lz77 = new LZ77();
        ret = lz77->comprime(str);
        break;

    case 3:
        LZW *lzw = new LZW();
        ret = lzw->comprime(str);    
    default:
        break;
    }

    return ret;
}

string descomprime(string str, int metodo){
    string ret;
    switch (metodo)
    {
    case 1:
        Huffman *huffman = new Huffman();//arrumar o huffman
        break;

    case 2:
        LZ77 *lz77 = new LZ77();
        ret = lz77->descomprime(str);
        break;

    case 3:
        LZW *lzw = new LZW();
        ret = lzw->descomprime(str);    
    default:
        break;
    }

    return ret;
}

void comprime(int metodo){
    fstream reviewsOriginP, reviewsComprimedP;
    string str,ret;
    reviewsOriginP.open("reviewsOrig.txt", ios::in);
    reviewsComprimedP.open("reviewsComp.bin", ios::out | ios::binary);
    if(reviewsOriginP.is_open() && reviewsComprimedP.is_open()){
        while(getline(reviewsOriginP, str)){
            ret = "";
            ret = comprime(str, metodo);
            reviewsComprimedP.write(ret.c_str(), ret.size());
        }
    }
    reviewsOriginP.close();
    reviewsComprimedP.close();
}

void descomprime(int metodo){
    fstream reviewsComprimedP, reviewsDescomprimedP;
    string str,ret;
    reviewsComprimedP.open("reviewsComp.bin", ios::in | ios::binary);
    reviewsDescomprimedP.open("reviewsDescomp.txt", ios::out);
    if(reviewsComprimedP.is_open() && reviewsDescomprimedP.is_open()){
        while(getline(reviewsComprimedP, str)){
            ret = "";
            ret = descomprime(str, metodo);
            reviewsDescomprimedP.write(ret.c_str(), ret.size());
        }
    }
    reviewsComprimedP.close();
    reviewsDescomprimedP.close();
}

// Função de Métricas para a Segunda Etapa

 // Funções de Chamada

void doSorting(string pathToFolder)
{
    cout << "_____________________________________________" << endl;
    cout << "Select which method you would like to use: " << endl;
    cout << "0) Merge Sort" << endl;
    cout << "1) Quick Sort" << endl;
    cout << "2) Tim Sort" << endl;
    cout << "_____________________________________________" << endl;

    int sortingOption;
    cin >> sortingOption;

    string path = pathToFolder;

    cout << "Initializing..." << endl;
    metricsFunction(path, 5, sortingOption);
    cout << "It's done!" << endl;
}

void doHashing(string pathToFolder)
{
    cout << "_____________________________________________" << endl;
    cout << "How many registers do you want to hash?" << endl;
    cout << "_____________________________________________" << endl;

    int n;
    cin >> n;

    RegistroHash *registro = createTable(n);

    cout << "Generating table..." << endl;

    cout << "_____________________________________________" << endl;
    cout << "How many do you want to order by number of reviews?" << endl;
    cout << "_____________________________________________" << endl;

    int p;
    cin >> p;

    orderByRating(registro, p, n);

    delete[] registro;

}

string comprime(string str, int metodo){

    string ret;
    switch (metodo)
    {
    case 1:
        break;

    case 2:
        LZ77 *lz77 = new LZ77();
        ret = lz77->comprime(str);
        break;

    case 3:
        LZW *lzw = new LZW();
        ret = lzw->comprime(str);    
    default:
        break;
    }

    return ret;
}

string descomprime(string str, int metodo){
    string ret;
    switch (metodo)
    {
    case 1:
        break;

    case 2:
        LZ77 *lz77 = new LZ77();
        ret = lz77->descomprime(str);
        break;

    case 3:
        LZW *lzw = new LZW();
        ret = lzw->descomprime(str);    
    default:
        break;
    }

    return ret;
}

void comprime(int metodo){
    fstream reviewsOriginP, reviewsComprimedP;
    string str,ret;
    reviewsOriginP.open("reviewsOrig.txt", ios::in);
    reviewsComprimedP.open("reviewsComp.bin", ios::out | ios::binary);
    if(reviewsOriginP.is_open() && reviewsComprimedP.is_open()){
        while(getline(reviewsOriginP, str)){
            ret = "";
            ret = comprime(str, metodo);
            reviewsComprimedP.write(ret.c_str(), ret.size());
        }
    }
    reviewsOriginP.close();
    reviewsComprimedP.close();
}

void descomprime(int metodo){
    fstream reviewsComprimedP, reviewsDescomprimedP;
    string str,ret;
    reviewsComprimedP.open("reviewsComp.bin", ios::in | ios::binary);
    reviewsDescomprimedP.open("reviewsDescomp.txt", ios::out);
    if(reviewsComprimedP.is_open() && reviewsDescomprimedP.is_open()){
        while(getline(reviewsComprimedP, str)){
            ret = "";
            ret = descomprime(str, metodo);
            reviewsDescomprimedP.write(ret.c_str(), ret.size());
        }
    }
    reviewsComprimedP.close();
    reviewsDescomprimedP.close();
}

int main(int argc, char** argv)
{
    srand(time(NULL));
    
    // if(argc < 2)
    // {
    //     return 0;
    // }

    string path_teste(argv[1]);

    cout << "Converting cvs file to binary..." << endl;
    createBinary(path_teste);
    cout << "Binary file ready!" << endl;

    cout << "_____________________________________________" << endl;
    cout << "Pick one of the following options:" << endl;
    cout << "1) Sorting" << endl;
    cout << "2) Hashing" << endl;
    cout << "_____________________________________________" << endl;

    int mainOption;
    cin >> mainOption;

    switch (mainOption)
    {
    case 1: 
        doSorting(path_teste);
        break;
    case 2:
        doHashing(path_teste);
        break;
    default:
        cout << "This is not a valid option!" << endl;
        break;
    }

}