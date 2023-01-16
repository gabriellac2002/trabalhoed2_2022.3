#ifndef Huffman_H_INCLUDED
#define Huffman_H_INCLUDED

#include "NodeHuffman.h"
#include "string.h"

using namespace std;


class Huffman {
    private:
        long size; //Tamanho da MinHeap
        long capacity; //Capadcidade da MinHeap
        NodeHuffman** array; // Array de ponteiros de nós da MinHeap
        NodeHuffman* root;
        bool** codeTable;
        int sizeTable[256];
        long compressionSize;
        long originalSize;

    public:
        Huffman(long capacity, long size);

        virtual ~Huffman();

        NodeHuffman* getRoot();

        long getSize();
        void setSize(long size);

        long getCapacity();
        void setCapacity(long capacity);

        NodeHuffman **getHeapArray();
        void setHeapArray(NodeHuffman **array);

        void minHeapify(int index, int* comparisons);

        bool isSizeOne();

        NodeHuffman *extractMin(int* comparisons);

        void insertAtHeapArray(NodeHuffman *node, int* comparisons);

        void buildMinHeap(int* comparisons);

        void createBuildMinHeap(char *content, long *frequence, int* comparisons);

        void printArray();

        void huffmanCodes(char *content, long *frequence, int* comparisons);

        void swapNodeHuffman(NodeHuffman **a, NodeHuffman **b);

        void storeArray(int *array, int n, bool *code);

        void storeCodes(NodeHuffman* root, int array[], int top);

        void calculateSizes(char *content, long *frequence, long total);

        NodeHuffman* buildHuffmanTree(char *content, long *frequence, int* comparisons);

        void calculateSize(char* content, long* frequence, long total);

        bool* huffmanCompression(char *content, long *frequence, string uncompressed, long total,string path);
        char* decompress(bool *compression);

        long getCompressionSize();
        void setCompressionSize(long compressionSize);

        long getOriginalSize();
        void setOriginalSize(long originalSize);

};


#endif //Huffman_H_INCLUDED