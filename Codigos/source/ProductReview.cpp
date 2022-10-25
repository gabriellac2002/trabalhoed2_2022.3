#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>

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

void ProductReview::createBinary(string& path)
{
    std::ifstream ler(path+"a.csv");
    std::fstream escrever("ratings_Electronics.bin", ios::out | ios::in | ios::ate | ios::binary);
    
    string s;
    //le linha a linha do arquivo
    while(getline(ler, s)) {
        string userId;    
        string productId;    
        float rating;
        long timestamp;
        stringstream temp(s); //lendo o dado do arquivo da serialização
        // Product produto;
        int z = 0;
        while(getline(temp,s,',')){  //separa por virgula
           switch(z){
            case 0:
                userId = s;
                z++;
                break;
            case 1:
                productId = s; 
                z++;
                break;
            case 2:
                rating = stof(s); //converte string pra float
                z++;
                break; 

            default:
                timestamp = stoi(s); //converte string pra int
                z++;
                break;
           }
            
        }
        
        Product produto(userId.c_str(), productId.c_str(), rating, timestamp);

        produto.EscreverNoArquivoBinario(escrever);
        // produto2.LerDoArquivoBinario(escrever);
        // produto.Imprimir();

        

        //cout<< prduto2.userId << "," << produto.productId << "," << produto.rating << "," << produto.timestamp<< '\n';

    }

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

}