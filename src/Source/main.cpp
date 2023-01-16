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
#include <unordered_map>

#include <cstdlib>
#include <string>
#include <ctime>

#include "../Headers/ProductReview.h"
#include "../Headers/MergeSort.h"
#include "../Headers/QuickSort.h"
#include "../Headers/TimSort.h"
#include "../Headers/HashTable.h"
#include "../Headers/RegistroHash.h"
#include "../Headers/LZ77.h"
#include "../Headers/LZW.h"
#include "../Headers/Huffman.h"
#include "../Headers/ArvoreVp.h"

#define PRODUCT_REVIEW_SIZE (41 + sizeof(float))

using namespace std;
using namespace chrono;

string PATH;
unordered_map<char, long> FREQUENCEMAP;
Huffman *huffmanGlobal;

string PATH;
unordered_map<char, long> FREQUENCEMAP;
Huffman *huffmanGlobal;

// COMANDOS PARA RODAR O PROGRAMA:
// g++ *.cpp* -o final
// .\final.exe ../Archives/ 

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
        int pos;

        for (int i = 0; i < size; i++)
        {
            getline(csvArchive, strUserId, ',');
            getline(csvArchive, strProductId, ',');
            getline(csvArchive, strRating, ',');
            getline(csvArchive, strTimestamp, '\n');
            rating = stof(strRating);
            pos = binaryArchive.tellp();
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
    ifstream binaryArchive(PATH + "ratings_Electronics.bin", ios::binary);

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
    binaryArchive.open(PATH + "ratings_Electronics.bin", ios::in | ios::binary);
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
    ifstream inputArchive(PATH + "input.txt");
    ofstream resultArchive(PATH + "saida.txt", ios_base::app);

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

//  Funções Auxiliares da SegundaEtapa

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

unordered_map<char,long> createFrequenceMap(string str)
{
    int size = str.length();
    unordered_map<char, long> frequenceMap;
    for (int i = 0; i < size; i++)
    {
        frequenceMap[str[i]]++;
    }       

    return frequenceMap;
}

Huffman* instantiateHuffman(unordered_map<char, long> frequenceMap, long* frequence, char* content, long n, int* comparisons)
{
    Huffman* huffman = new Huffman(10000, n);
    

    for (int i = 0; i < n; i++)
    {
        content[i] = frequenceMap.begin()->first;
        frequence[i] = frequenceMap.begin()->second;
        frequenceMap.erase(frequenceMap.begin());
    }
    
    huffman->buildHuffmanTree(content, frequence, comparisons);
    int array[1000];
    huffman->storeCodes(huffman->getRoot(), array, 0);

    return huffman;
}


 // Funções de Compresssão

 string comprime(string str, int metodo){

    string ret;
    switch (metodo) // estrutura de decisão para escolher o método de compressão a partir do número passado como parâmetro em metodo
    {
    case 1:
    { 
        int comparisons = 0;
        FREQUENCEMAP = createFrequenceMap(str);
        int relevantes = FREQUENCEMAP.size();
        long* frequence = new long[relevantes];
        char* content = new char[relevantes];
        huffmanGlobal = instantiateHuffman(FREQUENCEMAP, frequence, content, relevantes, &comparisons);
        huffmanGlobal->setOriginalSize(str.size());
        cout<<"tamanho original"<<str.size()<<endl;
        bool* compressionArray = huffmanGlobal->huffmanCompression(content, frequence, str, relevantes,PATH);
        cout<<"teste"<<endl;
        cout<<huffmanGlobal->getCompressionSize()<<endl;
        cout<<huffmanGlobal->getOriginalSize()<<endl;
        for(int i = 0;i<huffmanGlobal->getCompressionSize();i++)
        {
            if(compressionArray[i] == 1)
                ret += "1";
            else
                ret += "0";
        }
        cout << "Comprimida: " << ret << endl;
        break;
    }    
    case 2:
    {
        LZ77 *lz77 = new LZ77();
        ret = lz77->comprime(str,PATH);
        break;
    }
    case 3:
    {
        LZW *lzw = new LZW();
        ret = lzw->comprime(str,PATH);  
        break;  
    }

    default:
    {
        cout<<"Método de compressão não encontrado"<<endl;
        break;
    }

    }

    return ret;
}

string descomprime(string str, int metodo){
    string ret =  "";
    switch (metodo)
    {
        case 1:
        {
            bool *compressionArray = new bool[str.size()];
            for(int i = 0;i<=huffmanGlobal->getCompressionSize();i++)
            {
                if(str[i] == '1')
                    compressionArray[i] = 1;
                else
                    compressionArray[i] = 0;
            }
            ret = huffmanGlobal->decompress(compressionArray);

            break;
        }
        case 2:
        {
            LZ77 *lz77 = new LZ77();
            ret = lz77->descomprime(str);
            break;
        }
        case 3:
        {
            LZW *lzw = new LZW();
            ret = lzw->descomprime(str);  
            break;
        }
        default:
        {
            cout<<"Método de descompressão não encontrado"<<endl;
            break;
        }
    }
    return ret;
}

void comprime(int metodo){
    fstream reviewsOriginP,saida;
    ofstream reviewsComprimedP;
    string str = "\nMensagem Original : ",aux = "\nMensagem Comprimida: ",ret = "";
    char *buffer;
    int size;
    reviewsOriginP.open(PATH +"reviewsOrig.txt",ios::in | ios::binary);
    reviewsComprimedP.open(PATH + "reviewsComp.bin", ios::binary | ios::out);//apaga tudo que tem no arquivo para uma nova compressao
    if(reviewsOriginP.is_open() && reviewsComprimedP.is_open()){
        int begin = reviewsOriginP.tellg();
        reviewsOriginP.seekg(0, ios::end);
        int end = reviewsOriginP.tellg();
        size = end - begin;
        buffer = new char[size+1];
        reviewsOriginP.seekg(0, ios::beg);
        reviewsOriginP.read(buffer, size);
        buffer[size] = '\0';
        str += buffer;
        cout<<"Size :"<<size<<endl;
        cout<<"Buffer :"<<str<<endl;
        ret = comprime(str, metodo);
        aux += ret;
        //reviewsComprimedP.write(reinterpret_cast<const char*>(ret.c_str()), ret.size());
        reviewsComprimedP.write((ret.c_str()), ret.size());
    }
    saida.open(PATH +"saida.txt", ios::out | ios::app);
    if(saida.is_open()){
        saida.write((str.c_str()), str.size());
        saida.write((aux.c_str()), aux.size());
    }
    reviewsOriginP.close();
    reviewsComprimedP.close();
}

void descomprime(int metodo){
    fstream reviewsComprimedP;
    string str,ret = "\nMensagem descomprimida : ",comp = "";
    float sizeComp = 0, sizeDescomp = 0;
    reviewsComprimedP.open(PATH + "reviewsComp.bin", ios::in | ios::binary);
    if(reviewsComprimedP.is_open()){
        while(getline(reviewsComprimedP, str)){
            comp += str; 
            ret += descomprime(str, metodo);
            sizeComp += str.size();
        }
    }
    fstream saida;
    saida.open(PATH +"saida.txt", ios::out | ios::app);
    if(saida.is_open())
        saida.write((ret.c_str()), ret.size());
    reviewsComprimedP.close();
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


 void printPrompt(ProductReview *vet, int n)
    {
        char imp;
        cout << "Imprimir (s/n): ";
        cin >> imp;

        if(vet == NULL)
            cout << "ALERTA: ponteiro nulo, nada a imprimir!" << endl;
        else if(imp == 's')
        {
            for(int i = 0; i < n; i++)
                vet[i].print();
        }
    }

    void printPrompt(ArvoreVP *arv, int n)
    {
        char imp;
        cout << "Imprimir (s/n): ";
        cin >> imp;

        if(arv == NULL)
            cout << "ALERTA: ponteiro nulo, nada a imprimir!" << endl;
        else if(imp == 's')
            arv->print();
    }

    ProductReview* randomTest(int n)
    {
        ProductReview *vet = new ProductReview[n];

        for(int i = 0; i < n; i++)
        {
            string u("STR");
            u += 'a'+rand()%('z'-'a');
            // vet[i].userId = u; // ou essa linha ou a de baixo pode ser usada, dependendo de como foi implementado (a de baixo é preferencial)
            vet[i].setUserId(u);
        }

        return vet;
    }

    template<typename T>
    void treeTest(T arv, ProductReview *vet, int n)
    {
        int comparacoes = 0;
        for(int i = 0; i < n; i++)
            arv->insere(&vet[i], &comparacoes);
        printPrompt(vet, n);

        string userId, productId;
        cout << "Digite um par (userId, productId) para busca: ";
        cin >> userId >> productId;
        while(userId != "quit")
        {
            ProductReview *p = arv->busca(userId, productId, &comparacoes);
            if(p != NULL)
                p->print();
            else
                cout << "Produto nao encontrado!" << endl;
            
            cout << "Digite outro par (userId, productId) para busca: ";
            cin >> userId >> productId;
        }
    }

// 

 void doRedAndBlackTreeTest()
{
    ArvoreVP* arv_vp = new ArvoreVP();

    int n = 0;
    ProductReview* vet;
    cout << "Quantos registros deseja importar? ";
    cin >> n;
    vet = import(n);

    cout << n << endl;

    for(int i=0; i<n; i++)
    {
        arv_vp->insere(&vet[i]);
    }
    // cout << arv_vp->count << endl;
    arv_vp->print();

    ProductReview pp = vet[0];
    ProductReview *pr = arv_vp->busca(pp.getUserId(), pp.getProductId());
    
    cout << "Esse é o userId" << endl;
    cout << pr->getUserId() << endl;
}

void metricasVp()
{
    ofstream resultArchive("../Archives/saidaVP.txt", ios_base::app);

    ArvoreVP* arv_vp = new ArvoreVP();

    int n = 0;
    ProductReview* vet;
    ProductReview* vet_um;
    cout << "Quantos registros deseja importar? ";
    cin >> n;
    vet = import(n);

    cout << n << endl;

    for(int i=0; i<n; i++)
    {
        arv_vp->insere(&vet[i]);

    }

    cout << "Insere" <<endl;
    resultArchive << "Resultados das comparações e de tempo para " << n << " arquivos na insercao: \n" << endl;
    cout<<  arv_vp->comparacoes << " -> Comparacoes" << endl;
    resultArchive << "comparacoes: "<< arv_vp->comparacoes << endl;
    cout<<  arv_vp->tempo << "-> Tempo" << endl;
    resultArchive << "tempo: "<< arv_vp->tempo << endl;
    resultArchive << "============================="<< endl;

    vet_um = import(n);
    for(int i=0; i<n; i++)
    {
        ProductReview y = vet_um[i];
        ProductReview *x;
        x = arv_vp->busca(y.getUserId(), y.getProductId());

        cout << "Busca" <<endl;
        resultArchive << "Resultados das comparações e de tempo para" << n << "arquivos na busca: \n" << endl;
        cout<<  arv_vp->comparacoes << " -> Comparacoes" << endl;
        resultArchive << "comparacoes: "<< arv_vp->comparacoes << endl;
        cout<<  arv_vp->tempo << "-> Tempo" << endl;
        resultArchive << "tempo: "<< arv_vp->tempo << endl;
        resultArchive << "============================="<< endl;
    }

    

}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    // if(argc < 2)
    // {
    //     return 0;
    // }
    string path(argv[1]);


    PATH = path;

    cout << "Converting cvs file to binary..." << endl;
    //createBinary(PATH);
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
        doSorting(PATH);
        break;
    case 2:
        doHashing(PATH);
        break;
    case 3:
        cout << "_____________________________________________" << endl;
        cout << "Selecione a opção de compressao que deseja: " << endl;
        cout << "1) Huffman" << endl;//nao colocar esse ainda
        cout << "2) LZ77" << endl;
        cout << "3) LZW" << endl;
        cout << "_____________________________________________" << endl;

        int compressionOption;
        cin >> compressionOption;

        comprime(compressionOption);
        descomprime(compressionOption);
        break;            
    default:
        cout << "This is not a valid option!" << endl;
        break;
    }

    return 0;
}