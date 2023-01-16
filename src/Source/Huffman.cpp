#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>
#include <unordered_map>
#include "string.h"


#include "../Headers/NodeHuffman.h"
#include "../Headers/Huffman.h"

using namespace std;

// Construtor

Huffman::Huffman(long capacity, long size) 
{
    this->size = size;
    this->capacity = capacity;
    this->array = new NodeHuffman*[capacity];
    this->root = nullptr;
    this->codeTable = new bool*[256];
    this->compressionSize = 0;
    this->originalSize = 0;

    for(int i = 0; i < 256; i++)
    {
        this->sizeTable[i] = 0;
    }
}

// Destrutor

Huffman::~Huffman() 
{
    for(int i = 0; i < size; i++)
    {
        if(array[i] != nullptr)
        {
            delete array[i];
        }
    }

    delete [] array;
}

// Getters e Setters

NodeHuffman* Huffman::getRoot()
{
    return this->root;
}

long Huffman::getSize() 
{
    return size;
}

void Huffman::setSize(long size) 
{
    Huffman::size = size;
}

long Huffman::getCapacity() 
{
    return capacity;
}

void Huffman::setCapacity(long capacity) 
{
    Huffman::capacity = capacity;
}

long Huffman::getCompressionSize()
{
    return this->compressionSize;
}

void Huffman::setCompressionSize(long compressionSize)
{
    this->compressionSize = compressionSize;
}

long Huffman::getOriginalSize()
{
    return this->originalSize;
}

void Huffman::setOriginalSize(long originalSize)
{
    this->originalSize = originalSize;
}

// Outras Funções

bool Huffman::isSizeOne()
{
    return this->size == 1;
}

void Huffman::swapNodeHuffman(NodeHuffman **a, NodeHuffman **b)
{
    NodeHuffman* t = *a;
    *a = *b;
    *b = t;
}

void Huffman::minHeapify(int index, int *comparisons)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
 
    if (left < this->size && this->array[left]->getFrequence() < this->array[smallest]->getFrequence())
    {
        (*comparisons) += 2;
        smallest = left;
    }
 
    if (right < this->size && this->array[right]->getFrequence() < this->array[smallest]->getFrequence())
    {
        (*comparisons) += 2;
        smallest = right;
    }       
 
    if (smallest != index) 
    {
        (*comparisons)++;
        swapNodeHuffman(&this->array[smallest], &this->array[index]);
        minHeapify(smallest, comparisons);
    }
}

NodeHuffman* Huffman::extractMin(int* comparisons) 
{
    NodeHuffman *aux = this->array[0];
    this->array[0] = this->array[this->size - 1];
    this->size--;

    minHeapify(0, comparisons);

    return aux;
}

void Huffman::insertAtHeapArray(NodeHuffman *node, int *comparisons)
{
    this->size++;
    int i = this->size - 1;

    (*comparisons) += 2;
    while (i && node->getFrequence() < this->array[(i - 1) / 2]->getFrequence()) 
    {
        (*comparisons) += 2;
        this->array[i] = this->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    this->array[i] = node;
}

void Huffman::buildMinHeap(int *comparisons)
{
    int n = this->size - 1;
    int i;
 
    for (i = (n - 1) / 2; i >= 0; --i)
    {
        minHeapify(i, comparisons);
    }
}

void Huffman::createBuildMinHeap(char *content, long *frequence, int* comparisons)
{
    for (int i = 0; i < this->size; ++i)
    {
        this->array[i] = new NodeHuffman(content[i], frequence[i]);
    }

    this->buildMinHeap(comparisons);
}

NodeHuffman* Huffman::buildHuffmanTree(char *content, long *frequence, int* comparisons)
{
    NodeHuffman *left, *right, *top;
    createBuildMinHeap(content, frequence, comparisons);
    while (!isSizeOne()) 
    {
        left = extractMin(comparisons);
        right = extractMin(comparisons);

        top = new NodeHuffman('\0', left->getFrequence() + right->getFrequence());

        top->setLeft(left);
        top->setRight(right);

        insertAtHeapArray(top, comparisons);
    }

    root = extractMin(comparisons);
}

void Huffman::printArray()
{
    for (int i = 0; i < 255; ++i)
    {
        if(this->sizeTable[i] > 0)
        {
            cout << (char) i << ": ";
            for(int j = 0; j < this->sizeTable[i]; j++)
            {
                cout << this->codeTable[i][j];
            }
            cout << endl;
        }
    }

    for(int i = 0; i < this->capacity; i++)
    {
        cout << "c: " << this->array[i]->getContent() << endl;
    }

    cout << endl;
}

void Huffman::storeArray(int array[], int n, bool* code)
{
    for (int i = 0; i < n; ++i)
    {
        code[i] = array[i];
    }
}

void Huffman::storeCodes(NodeHuffman* root, int array[], int top)
{
    if (root->getLeft()) 
    {
        array[top] = 0;
        storeCodes(root->getLeft(), array, top + 1);
    }
 
    if (root->getRight()) 
    {
        array[top] = 1;
        storeCodes(root->getRight(), array, top + 1);
    }
 
    if (root->isLeaf()) 
    {
        int nodeValue = root->getContent();
        this->codeTable[nodeValue] = new bool[top];
        this->sizeTable[nodeValue] = top;
        this->storeArray(array, top, this->codeTable[nodeValue]);
    }
}

void Huffman::calculateSize(char* content, long* frequence, long total)
{
    this->compressionSize = 0;
    for(int i = 0; i < total; i++)
    {
        int nodeValue = content[i];
        this->compressionSize += (this->sizeTable[nodeValue] * frequence[i]);
    }
}

bool* Huffman::huffmanCompression(char *content, long *frequence, string uncompressed, long total,string path)
{
    this->calculateSize(content, frequence, total);
    bool* compressionArray = new bool[(int)this->compressionSize];
    int aux = 0;
    string str = "";
    
    for(int i = 0; i < this->originalSize; i++)
    {
        int nodeValue = uncompressed[i];
        
        for(int j = 0; j < this->sizeTable[nodeValue]; j++)
        {
            compressionArray[aux] = this->codeTable[nodeValue][j];
            aux++;
        }
    }

    for(int i = 0;i<sizeof(compressionArray);i++)
    {
        if(compressionArray[i] == 1)
            str += "1";
        else
            str += "0";
    }

    float comp = 1 - (float)this->compressionSize/((float)this->originalSize*8);
    string inp = "\n\nTaxa de compressao: " + to_string(comp) + "\n";
    fstream saida;
    saida.open(path + "saida.txt", ios::out | ios::app);
    if(saida.is_open()){
        saida.write((inp.c_str()), inp.size());
    }
    saida.close();

    return compressionArray;
}

char* Huffman::decompress(bool *compression)
{
    char* decoded = new char[(originalSize)];
    int aux = 0;
    NodeHuffman* node = this->root;

    for (int i = 0; i <= this->compressionSize; i++)
    {
        if (node->isLeaf())
        {
            decoded[aux] = node->getContent();
            aux++;
            node = this->root;
        }

        if (compression[i])
        {
            node = node->getRight();
        }
        else{
            node = node->getLeft();
        }

        
    }
    cout<<decoded<<endl;

    // decoded[(originalSize)] = '\0';

    return decoded;
}

void Huffman::huffmanCodes(char *content, long *frequence, int* comparisons) 
{
    buildHuffmanTree(content, frequence, comparisons);
    int array[capacity], top = 0;
    storeCodes(this->root, array, top);
}