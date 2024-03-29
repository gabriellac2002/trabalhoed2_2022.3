#ifndef TimSort_H_INCLUDED
#define TimSort_H_INCLUDED

#include "ProductReview.h"
#include <fstream>

using namespace std;

void insertionSort(ProductReview* array, int left, int right, int* comparisons, int* movements);
void mergeTim(ProductReview* array, int l, int m, int r, int* comparisons, int* movements);
void timSort(ProductReview* array, int* comparisons, int* movements);


#endif // TimSort_H_INCLUDED