#ifndef QuickSort_H_INCLUDED
#define QuickSort_H_INCLUDED

#include "ProductReview.h"
#include <fstream>

using namespace std;

void swap(ProductReview* a, ProductReview* b);
int partition(ProductReview* array, int low, int high);
void quickSort(ProductReview* array, int low, int high);

void quickSortmetrics(string quick, string archiveName);

#endif // QuickSort_H_INCLUDED