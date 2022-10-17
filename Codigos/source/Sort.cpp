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
int partition(ProductReview arr[], int low, int high)
{
    int pivot = arr[high].GetuserId(); // pivot
    int i = (low - 1);                 // Index of smaller element and indicates
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
        int pi = partition(this->file, low, high);

        // Separately sort elements before
        // partition and after partition
        QuickSort(low, pi - 1);
        QuickSort(pi + 1, high);
    }
}

int Sort::GetExtremes(int *low, int *high)
{
    low = 0;
    high = 0;
    int val;
    for (int i = 0; i < sizeof(this->file); i++)
    {
        val = this->file[i].GetuserId();
        if (val >= *high)
            *high = val;
        if (val < *low)
            *low = val;
    }
}

void Sort::CountingSort(int n)
{
    // The output character array
    // that will have sorted arr
    ProductReview output[sizeof(this->file)];

    // Create a count array to store count of individual
    // characters and initialize count array as 0
    int count[n + 1], i;
    memset(count, 0, sizeof(count));

    // Store count of each character
    for (i = 0; i < n + 1; ++i)
        ++count[this->file[i]];

    // Change count[i] so that count[i] now contains actual
    // position of this character in output array
    for (i = 1; i <= n; ++i)
        count[i] += count[i - 1];

    // Build the output character array
    for (i = 0; i < n + 1; ++i)
    {
        output[count[this->file[i]] - 1] = this->file[i];
        --count[this->file[i]];
    }

    /*
    For Stable algorithm
    for (i = sizeof(arr)-1; i>=0; --i)
    {
        output[count[arr[i]]-1] = arr[i];
        --count[arr[i]];
    }

    For Logic : See implementation
    */

    // Copy the output array to arr, so that arr now
    // contains sorted characters
    for (i = 0; i < n + 1; ++i)
        this->file[i] = output[i];
}

void merge(int array[], int const left, int const mid,
           int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    // Create temp arrays
    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne = 0,   // Initial index of first sub-array
        indexOfSubArrayTwo = 0;    // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array

    // Merge the temp arrays back into array[left..right]
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
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne)
    {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo)
    {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void Sort::MergeSort( int begin, int end)
{
    if (begin >= end)
        return; // Returns recursively

    auto mid = begin + (end - begin) / 2;
    MergeSort(begin, mid);
    MergeSort(mid + 1, end);
    merge(begin, mid, end);
}