#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

#include "Headers/ProductReview.h"
#include "Headers/QuickSort.h"

using namespace std;

void swap(ProductReview* a, ProductReview* b)
{
    ProductReview aux = *a;
    *a = *b;
    *b = aux;
}

int partition(ProductReview* array, int low, int high, int comparisons, int movements)
{
    ProductReview pivot = array[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
  
    for (int j = low; j <= high - 1; j++) 
    {
        // Se o elemento atual (userId do ProductReview) é menor do que o pivô
        (comparisons)++;
        if (array[j].getUserId() < pivot.getUserId()) 
        {
            i++; // incrementa o índice do menor elemento
            swap(&array[i], &array[j]);
            (movements)++;
        }
    }

    swap(&array[i + 1], &array[high]);
    (movements)++;
    return (i + 1);
}

int* quickSort(ProductReview* array, int low, int high, int comparisons, int movements)
{
    int metrics[2];

    if (low < high) 
    {
        // pi é o índice de particionamento
        int pi = partition(array, low, high, comparisons, movements);
  
        // Separadamente ordena os elementos anteriores partição após partição
        quickSort(array, low, pi - 1, comparisons, movements);
        quickSort(array, pi + 1, high, comparisons, movements);
    }

    metrics[0] = comparisons;
    metrics[1] = movements;

    return metrics;
}