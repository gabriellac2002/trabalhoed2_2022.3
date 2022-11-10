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
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo])
        {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else 
        {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }

        indexOfMergedArray++;
    }

    // Copia os elementos restantes de left[] se houver algum
    while (indexOfSubArrayOne < subArrayOne) 
    {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    // Copia os elementos restantes de right[] se houver algum
    while (indexOfSubArrayTwo < subArrayTwo) 
    {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
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

void mergeSortmetrics(string pathToFolder, string archiveName, int repetition)
{
    
}