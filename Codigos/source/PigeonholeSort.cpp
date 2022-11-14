#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

#include "Headers/ProductReview.h"
#include "Headers/PigeonholeSort.h"

using namespace std;

int pigeonholeSortMovements = 0;
int pigeonholeSortComparisons = 0;

void pigeonholeSort(ProductReview* array)
{
    int size = sizeof(array);
    // Find minimum and maximum values in file[]
    ProductReview min = array[0];
    ProductReview max = array[0];

    for (int i = 1; i < size; i++)
    {
        if (array[i].getUserId() < min.getUserId())
            min = array[i];
        if (array[i].getUserId() > max.getUserId())
            max = array[i];
    }

    int range = max.getUserId() - min.getUserId() + 1; // Find range

    // Create an fileay of vectors. Size of fileay range. 
    // Each vector represents a hole that is going to contain matching elements.
    vector<ProductReview> holes[range];

    // Traverse through input fileay and put every element in its respective hole
    for (int i = 0; i < size; i++)
        holes[array[i].getUserId() - min.getUserId()].push_back(array[i]);

    // Traverse through all holes one by one. For
    // every hole, take its elements and put in
    // fileay.
    int index = 0; // index in sorted fileay
    for (int i = 0; i < range; i++)
    {
        vector<ProductReview>::iterator it;
        for (it = holes[i].begin(); it != holes[i].end(); ++it)
            array[index++] = *it;
    }
}


