#include <iostream>
#include <cstdlib>

#include "ProductReview.h"
#include "Sort.h"
#include <bits/stdc++.h>

using namespace std;

Sort::Sort(ProductReview *archive)
{
    file = archive;
}

void Sort::PigeonholeSort(int n)
{
    // Find minimum and maximum values in file[]
    ProductReview min = this->file[0], max = this->file[0];
    for (int i = 1; i < n; i++)
    {
        if (this->file[i].GetuserId() < min.GetuserId())
            min = this->file[i];
        if (this->file[i].GetuserId() > max.GetuserId())
            max = this->file[i];
    }
    int range = max.GetuserId() - min.GetuserId() + 1; // Find range

    // Create an fileay of vectors. Size of fileay
    // range. Each vector represents a hole that
    // is going to contain matching elements.
    vector<ProductReview> holes[range];

    // Traverse through input fileay and put every
    // element in its respective hole
    for (int i = 0; i < n; i++)
        holes[this->file[i].GetuserId() - min.GetuserId()].push_back(this->file[i]);

    // Traverse through all holes one by one. For
    // every hole, take its elements and put in
    // fileay.
    int index = 0; // index in sorted fileay
    for (int i = 0; i < range; i++)
    {
        vector<ProductReview>::iterator it;
        for (it = holes[i].begin(); it != holes[i].end(); ++it)
            file[index++] = *it;
    }
}

void swap(ProductReview *a, ProductReview *b)
{
    ProductReview t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(ProductReview arr[],int low, int high)
{
    int pivot = arr[high].GetuserId(); // pivot
    int i = (low - 1);                    // Index of smaller element and indicates
                                          // the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j].GetuserId() < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void Sort::QuickSort(int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, file[p] is now
        at right place */
        int pi = partition(this->file,low, high);

        // Separately sort elements before
        // partition and after partition
        QuickSort(low, pi - 1);
        QuickSort(pi + 1, high);
    }
}

int Sort::GetExtremes(int *low,int *high){
    low = 0;
    high =  0;
    int val;
    for(int i=0;i<sizeof(this->file);i++){
        val = this->file[i].GetuserId();
        if(val>=*high)
            *high = val;
        if(val<*low)
            *low = val;    
    }
}   