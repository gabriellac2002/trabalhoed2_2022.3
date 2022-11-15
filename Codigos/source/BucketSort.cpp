#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

#include "Headers/ProductReview.h"
#include "Headers/BucketSort.h"

using namespace std;

void bucketSort(ProductReview* array, int n, int comparisons, int movements)
{
    int n = sizeof(array) / sizeof(array[0]);

    // cria n baldes vazios
    ProductReview* bucket = new ProductReview[n];
  
    // Put array elements in different buckets
    for (int i = 0; i < n; i++) 
    {
        int bi = n * array[i]; // Index in bucket
        bucket[bi].push_back(array[i]);
    }
  
    // 3) Sort individual buckets
    for (int i = 0; i < n; i++)
        sort(b[i].begin(), b[i].end());
  
    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b[i].size(); j++)
            array[index++] = b[i][j];
}


