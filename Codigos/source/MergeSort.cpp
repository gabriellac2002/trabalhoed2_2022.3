#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

#include "Headers/ProductReview.h"
#include "Headers/MergeSort.h"

using namespace std;

int mergeSortMovements = 0;
int mergeSortComparisons = 0;

void merge(ProductReview* array, int left, int mid, int right)
{
    int subArrayOne = mid - left + 1;
    int subArrayTwo = right - mid;
 
    // Criando arrays temporárias
    ProductReview *leftArray = new ProductReview[subArrayOne];
    ProductReview *rightArray = new ProductReview[subArrayTwo];
 
    // Copia dados para os arrays auxiliares leftArray[] e rightArray[]
    for (int i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
 
    int indexOfSubArrayOne = 0; // Índice inicial do primeiro sub-array
    int indexOfSubArrayTwo = 0; // Índice inicial do segundo sub-array
    int indexOfMergedArray = left; // Índice inicial do merged array
 
    // Faz o Merge das arrays temporárias de volta na array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) 
    {
        mergeSortComparisons++;

        if (leftArray[indexOfSubArrayOne].getUserId() <= rightArray[indexOfSubArrayTwo].getUserId())
        {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
            mergeSortMovements++;
        }
        else 
        {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
            mergeSortMovements++;
        }

        indexOfMergedArray++;
    }

    // Copia os elementos restantes de left[] se houver algum
    while (indexOfSubArrayOne < subArrayOne) 
    {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
        mergeSortMovements++
    }

    // Copia os elementos restantes de right[] se houver algum
    while (indexOfSubArrayTwo < subArrayTwo) 
    {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
        mergeSortMovements++
    }

    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(ProductReview* array, int begin, int end)
{
    if (begin >= end)
        return; // Retorna recursivamente
 
    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);

}

void mergeSortMetrics(string pathToFolder, string archiveName, int repetition)
{
    ifstream inputArchive(pathToFolder + "input.dat");
    ofstream resultArchive(pathToFolder + "saida.txt", ios_base::app);

    resultArchive << "Resultados das métricas para o MergeSort:\n";

    string strN, strM;
    int n, m;

    long long time = 0;
    long long averageTime = 0;
    float averageMergeSortMovements = 0;
    float averageMergeSortComparisons = 0;

    int i = 0;
    while (inputArchive.good() && i < repetition)
    {
        // obtemos os valores M e N do input.dat
        i++;
        getline(inputArchive, strN, ',');
        getline(inputArchive, strM);
        n = stoi(strN);
        m = stoi(strM);

        resultArchive << "\nResultados para N = " << n <<"\n";

        for(int j = 0; j < m; j++)
        {
            ProductReview *array = import(n);
            auto begin = chrono::high_resolution_clock::now();

            // chamando o merge sort para o array
            mergeSort(array, 0, n-1);
            auto final = chrono::high_resolution_clock::now() - begin;
            time = chrono::duration_cast<chrono::microseconds>(final).count();

            delete[] array;

            //ESCREVENDO NO OUTFILE
            resultArchive << "\nMovimentações: " << mergeSortMovements << " Comparações: " << mergeSortComparisons <<" Tempo de Execução(s): "<< time/1000000.0 << "\n";

            //INCREMENTO DAS MEDIAS
            averageMergeSortComparisons += mergeSortComparisons; 
            averageMergeSortMovements += mergeSortMovements; 
            averageTime += time;
            
            // zerando as movimentações e comparações
            mergeSortMovements = 0;
            mergeSortComparisons = 0;
            
        }

        // calculando as médias
        averageMergeSortComparisons /= m;
        averageTime /= m;
        averageMergeSortMovements /= m;

        // escrevendo as informações no arquivo saida.txt
        if(repetition>1)
        resultArchive << "____________________\n";
        resultArchive << "\nMédia das Movimentações: " << averageMergeSortMovements << " Média das Comparações: " << averageMergeSortComparisons <<" Média do tempo de execução: "<< averageTime/1000000.0 <<"\n\n";
        resultArchive << "____________________\n";

        // zerando as médias
        averageMergeSortComparisons = 0;
        averageMergeSortMovements = 0;
        averageTime = 0;

    }   



    inputArchive.close();
    resultArchive.close();
    
}