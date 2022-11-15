#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

#include "Headers/ProductReview.h"
#include "Headers/TimSort.h"

using namespace std;

const int RUN = 32;
 
void insertionSort(ProductReview* array, int left, int right, int comparisons, int movements)
{
    for (int i = left + 1; i <= right; i++)
    {
        ProductReview aux = array[i];
        int j = i - 1;
        while (j >= left && array[j].getUserId() > aux.getUserId())
        {
            array[j+1] = array[j];
            j--;
            comparisons++;
        }
        array[j+1] = aux;
        movements++;
    }
}
 
void merge(ProductReview* array, int l, int m, int r, int comparisons, int movements)
{
    int len1 = m - l + 1;
    int len2 = r - m;
    ProductReview left[len1], right[len2];

    for (int i = 0; i < len1; i++)
    {
        left[i] = array[l + i];
    }
        
    for (int i = 0; i < len2; i++)
    {
        right[i] = array[m + 1 + i];
    }
        
    int i = 0;
    int j = 0;
    int k = l;
 
    while (i < len1 && j < len2)
    {
        if (left[i].getUserId() <= right[j].getUserId())
        {
            array[k] = left[i];
            i++;
            comparisons++;
            movements++;
        }
        else 
        {
            array[k] = right[j];
            j++;
            movements++;
        }
        k++;
    }
 
    while (i < len1)
    {
        array[k] = left[i];
        k++;
        i++;
    }

    while (j < len2)
    {
        array[k] = right[j];
        k++;
        j++;
    }
}
 
int* timSort(ProductReview* array, int comparisons, int movements)
{
    int n = sizeof(array);

    int metrics[2];
     
    for (int i = 0; i < n; i+=RUN)
    {
        insertionSort(array, i, min((i+RUN-1), (n-1)), comparisons, movements);
    }
        
    for (int size = RUN; size < n; size = 2*size)
    {
        for (int left = 0; left < n; left += 2*size)
        {
            int mid = left + size - 1;
            int right = min((left + 2*size - 1), (n-1));
 
            if(mid < right)
            {
                merge(array, left, mid, right, comparisons, movements);
            }    
        }
    }

    metrics[0] = comparisons;
    metrics[1] = movements;
}