#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

#include "Headers/ProductReview.h"
#include "Headers/QuickSort.h"

using namespace std;

int quickSortMovements= 0;
int quickSortComparisons = 0;

void swap(ProductReview* a, ProductReview* b)
{
    ProductReview aux = *a;
    *a = *b;
    *b = aux;
}

int partition(ProductReview* array, int low, int high)
{
    ProductReview pivot = array[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
  
    for (int j = low; j <= high - 1; j++) 
    {
        // Se o elemento atual é menor do que o pivô
        if (array[j] < pivot) 
        {
            i++; // incrementa o índice do menor elemento
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quickSort(ProductReview* array, int low, int high)
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

void quickSortmetrics(string quick, string archiveName)
{

}