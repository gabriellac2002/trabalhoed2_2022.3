#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <array>
#include <cstdlib> 
#include <ctime>   
#include "string.h"
#include "../Headers/ProductReview.h"
#include "../Headers/HashTable.h"
#include "../Headers/ListaDupla.h"
#include "../Headers/NoDuplo.h"
// #include "../source/ListaDupla.cpp"



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


void fixAndAddBuffer(fstream &reader,fstream &pointer, string buffer[])
{
    char trim[] = {',', '\n'};
    for(int i=0;i<15;i++){
        char container [buffer[i].length() + 1];
        strcpy(container, buffer[i].c_str());
        char *separated = strtok(container, trim);
        int counter = 0, tam,total = 0;
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

// calcula o número de registros no arquivo passado como parâmetro (número de reviews)s

int numberOfRegisters(fstream& archive) 
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

// Funções Obrigatórias da 1ª Etapa

void createBinary(string &path)
{
    std::fstream csvArchive;
    csvArchive.open(path + "test.csv", ios::in | ios::binary);
    std::fstream binaryArchive;
    binaryArchive.open("test.bin", ios::out | ios::binary);
    int sizeofFile = sizeOfArchive(csvArchive);
    string buffer[15],buffer1;

    if (csvArchive.is_open())
    {
        while (!csvArchive.eof())
        {
            for(int i =0;i<15;i++){
                getline(csvArchive,buffer1);
                buffer[i] = buffer1;
            }
            // csvArchive.read((char *)buffer, size);
            fixAndAddBuffer(csvArchive,binaryArchive, buffer);
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

    binaryArchive.open("test.bin", ios::in);

    char review[PRODUCT_REVIEW_SIZE];
    char *separated;

    if (binaryArchive.is_open())
    {
        binaryArchive.seekg(x * PRODUCT_REVIEW_SIZE, ios_base::beg);
        // binaryArchive.read((char*) buffer, sizeOfArchive(binaryArchive));
        binaryArchive.read((char *)&review, PRODUCT_REVIEW_SIZE);
        separated = strtok(review, "?");
        for(int i = 0; i < 4;i++){
            cout<<separated<<endl;
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

bool exists(int ocurrences[], int number,int pos)
{
    for(int i = 0; i <=pos; i++)
        if(ocurrences[i] == number)
            return true;
    return false;        
}

ProductReview *import(int n)
{
    ProductReview *productReview = new ProductReview[n];
    ifstream binaryArchive;
    fstream textArchive;

    int ocurrences [n];
    int pos=0;
    binaryArchive.open("test.bin",ios::in);
    textArchive.open("test.csv",ios::in);
    int size = numberOfRegisters(textArchive);
    cout<<"numero total de registros no arquivo = "<<size<<endl;
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
                while(exists(ocurrences,random,pos))
                {
                    random = rand() % size;
                }
                ocurrences[pos] = random;
                pos++;
                if(pos == size)
                {
                    cout<<"coletou todos os registros"<<endl;
                    return productReview;
                }

                cout << "numero aleatorio gerado= " << random << endl;
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

int funcaoHash(const string& string)
{
    int p = 31, m = 1e9 + 7;
    int tam_string = string.length();

    int hash_value = 0;
    long p_pow = 1;
    for(int i = 0; i < tam_string; i++) {
        hash_value = (hash_value + (string[i] - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return abs(hash_value);
}

int numAleatorio(int a, int b)
{
    return a + rand()%(b - a + 1); /// retorna um numero inteiro aleat�rio entre a e b
}

int main()
{
    // string path_teste(argv[1]);
    // ProductReview productReview;
    // createBinary(path_teste);
    // getReview(1);
    // ProductReview *teste = new ProductReview[5];
    // teste = import(5);

    // for (int i = 0; i < 5; i++)
    // {
    //     teste[i].print();
    // }

    // const string s = "geeksforgeeks";
    // int hash = funcaoHash(s);
    // cout << "Hash of " << s << " is: " << hash << '\n';

    // ListaDupla l; /// cria lista vazia
    // int NumNos = 10;

    // srand(time(NULL));

    // /// ATENCAO: os valores inseridos na lista sao gerados
    // /// aleatoriamente e mudam em cada execucao do programa!!!
    // cout << "Inserindo valores: ";
    // for(int i = 1; i <= NumNos; i++)
    // {
    //     int val =  numAleatorio(0, 50); /// cria um valor aleat�rio entre 0 e 50
    //     cout << val << ", ";
    //     l.insereInicio(val);
    // }
    // cout << endl;

    // bool existe = l.busca(20);
    // cout << "O valor 20 esta na lista? ";
    // if(existe)
    //     cout << "Sim" << endl;
    // else
    //     cout << "Nao" << endl;

    // return 0;
}