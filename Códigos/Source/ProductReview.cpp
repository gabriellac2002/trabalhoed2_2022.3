#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <string>

#include "../Headers/ProductReview.h"

using namespace std;



ProductReview::ProductReview(int n)
{
    tamanho = n;
}

void ProductReview::print(Product product, fstream &file)
{
    product.LerDoArquivoBinario(file);
    product.Imprimir();
}

int sizeOfArchive(ifstream& archive) 
{
    archive.seekg(0, archive.end);
    int size = archive.tellg();
    archive.seekg(0);
    return size;
}

void ProductReview::createBinary(string& path)
{
    std::ifstream csv(path+"a.csv");
    std::fstream binario("ratings_Electronics.bin", ios::out | ios::in | ios::ate | ios::binary | ios::trunc);

    

    string str, str2;
    char* buffer = new char[sizeOfArchive(csv)];
    
    if(csv.is_open())
    {
        int tamanho = sizeOfArchive(csv);
        csv.read((char*) buffer, tamanho);

        for(int i=0; i<= sizeOfArchive(csv); i++){
            cout << buffer[i] << endl;
            str = buffer[i];
            binario.write(reinterpret_cast<const char*>(&str), sizeof(str));
        }   
        
        // binario.write(reinterpret_cast<const char*>(&str), sizeof(str));
        binario.read(reinterpret_cast<char*>(&str2), sizeof(str2));

        cout << str2;
        
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;

<<<<<<< HEAD:Codigos/source/ProductReview.cpp
    csv.close();
    binario.close();
   
   
=======
    ler.close();
    Product produto2 = Product();
    escrever.seekg(0, ios::beg);
    print(produto2, escrever);
    // produto2.LerDoArquivoBinario(escrever);
    // produto2.Imprimir();
    // produto2.LerDoArquivoBinario(escrever);
    // produto2.Imprimir();
    // produto2.LerDoArquivoBinario(escrever);
    // produto2.Imprimir();
    escrever.close();
    // std::fstream escrever2("ratings_Electronics.bin", ios::out | ios::in | ios::ate | ios::binary);
>>>>>>> main:Códigos/Source/ProductReview.cpp

}