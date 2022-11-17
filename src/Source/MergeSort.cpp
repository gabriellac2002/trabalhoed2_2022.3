#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

#include "../Headers/ProductReview.h"
#include "../Headers/MergeSort.h"

using namespace std;

void merge(ProductReview* array, int left, int mid, int right, int* comparisons, int* movements)
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
        (*comparisons)++;

        if (leftArray[indexOfSubArrayOne].getUserId() <= rightArray[indexOfSubArrayTwo].getUserId())
        {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
            (*movements)++;
        }
        else 
        {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
            (*movements)++;
        }

        indexOfMergedArray++;
    }

    // Copia os elementos restantes de left[] se houver algum
    while (indexOfSubArrayOne < subArrayOne) 
    {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
        (*movements)++;
    }

    // Copia os elementos restantes de right[] se houver algum
    while (indexOfSubArrayTwo < subArrayTwo) 
    {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
        (*movements)++;
    }

    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(ProductReview* array, int begin, int end, int* comparisons, int* movements)
{
    int aux[2];

    if (begin >= end)
        return;
 
    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid, comparisons, movements);
    mergeSort(array, mid + 1, end, comparisons, movements);
    merge(array, begin, mid, end, comparisons, movements);

}