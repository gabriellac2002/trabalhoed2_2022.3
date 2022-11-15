#ifndef MergeSort_H_INCLUDED
#define MergeSort_H_INCLUDED

#include "ProductReview.h"
#include <fstream>

using namespace std;

void merge(ProductReview* vet, int left, int mid, int right, int* comparisons, int* movements);
void mergeSort(ProductReview* vet, int begin, int end, int* comparisons, int* movements);

#endif // MergeSort_H_INCLUDED