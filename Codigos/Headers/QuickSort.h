#ifndef QuickSort_H_INCLUDED
#define QuickSort_H_INCLUDED

#include "ProductReview.h"
#include <fstream>

using namespace std;

void swap(ProductReview* a, ProductReview* b);
int partition(ProductReview* array, int low, int high, int* comparisons, int* movements);
void quickSort(ProductReview* array, int low, int high, int* comparisons, int* movements);

#endif // QuickSort_H_INCLUDED