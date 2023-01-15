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

#include <cstdlib>
#include <string>
#include <ctime>

#include "../Headers/ProductReview.h"
#include "../Headers/MergeSort.h"
#include "../Headers/QuickSort.h"
#include "../Headers/TimSort.h"
#include "../Headers/HashTable.h"
#include "../Headers/RegistroHash.h"
#include "../Headers/ArvoreVp.h"

#define PRODUCT_REVIEW_SIZE (41 + sizeof(float))

using namespace std;
using namespace chrono;

// função para gerar um número aleatório do intervalo entre a e b

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
        cout << "Error! Could not open cvs file!" << endl;
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

ProductReview returnRegister(ifstream *file, int i)
{
    int userIdSize = 21;
    int productIdSize = 10;
    int timestampSize = 10;

    file->seekg(i * PRODUCT_REVIEW_SIZE);
    int pos = file->tellp();
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
    file->read(reinterpret_cast<char *>(&pos), sizeof(int));

    productReview->setUserId(userId);
    productReview->setProductId(productId);
    productReview->setRating(rating);
    productReview->setTimestamp(timestamp);
    productReview->setPos(pos);

    delete[] userId;
    delete[] productId;
    delete[] timestamp;

    return *productReview;
}

ProductReview returnarRegistroAvp(ifstream *file,int endMemory)
{
    int userIdSize = 21;
    int productIdSize = 10;
    int timestampSize = 10;

    file->seekg(endMemory);
    int pos = file->tellp();
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
    file->read(reinterpret_cast<char *>(&pos), sizeof(int));

    productReview->setUserId(userId);
    productReview->setProductId(productId);
    productReview->setRating(rating);
    productReview->setTimestamp(timestamp);
    productReview->setPos(pos);

    delete[] userId;
    delete[] productId;
    delete[] timestamp;

    return *productReview;
}


ProductReview *import(int n)
{
    int size = 7824483;
    ifstream binaryArchive;
    binaryArchive.open("ratings_Electronics.bin", ios::in | ios::binary);
    if (!binaryArchive.is_open())
    {
        cout << "Erro: Arquivo de entrada nao encontrado." << endl;
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
            vet[i].userId = u; // ou essa linha ou a de baixo pode ser usada, dependendo de como foi implementado (a de baixo é preferencial)
            //vet[i].setUserId(u);
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

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        // OBS.: TODOS OS ARQUIVOS USADOS NO PROGRAMA (TANTO DE ENTRADA QUANTO DE SAÍDA) DEVEM ESTAR LOCALIZADOS NO DIRETÓRIO FORNECIDO
        // PELO USUÁRIO COMO ARGUMENTO DA LINHA DE COMANDO
        std::string path(argv[1]);
        createBinary(path);

        int registerIdx;
        cout << "Digite um indice de registro (-1 para sair): ";
        cin >> registerIdx;
        while (registerIdx != -1)
        {
            getReview(registerIdx);
            cout << "Digite outro indice de registro (-1 para sair): ";
            cin >> registerIdx;
        }

        ProductReview *vet = 0;
        ArvoreVP *arv_vp = 0;
        ArvoreB *arv_b = 0;
        int option, n;
        do
        {
            cout << "[1] Vetor de teste" << endl 
                << "[2] Importar registros" << endl
                << "[3] Arvore vermelho-preto" << endl
                // << "[4] Arvore B" << endl
                // << "[5] Huffman" << endl
                // << "[6] LZ77" << endl
                // << "[7] LZW" << endl
                << "[0] Sair" << endl;

            cout << "Digite uma opcao de menu: ";
            cin >> option;
            switch (option)
            {
                case 1:
                    n = 10;
                    delete [] vet;
                    vet = randomTest(n);
                    printPrompt(vet, n);
                    break;
                case 2:
                    cout << "Quantos registros deseja importar? ";
                    cin >> n;
                    delete [] vet;
                    vet = import(n);
                    printPrompt(vet, n);
                    break;
                case 3:
                    delete arv_vp;
                    arv_vp = new ArvoreVP();
                    treeTest(arv_vp, vet, n);
                    break;
                // case 4:
                //     delete arv_b;
                //     arv_b = new ArvoreB();
                //     treeTest(arv_b, vet, n);
                //     break;
                // case 5:
                //     compressTest(0);
                //     break;
                // case 6:
                //     compressTest(1);
                //     break;
                // case 7:
                //     compressTest(2);
                //     break;
                default:
                    break;
            }
        } while(option != 0);

        delete [] vet;
        delete arv_vp;
        // delete arv_b;
    }

    return 0;
}