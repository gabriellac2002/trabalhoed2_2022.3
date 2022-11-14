#ifndef MergeSort_H_INCLUDED
#define MergeSort_H_INCLUDED

#include "ProductReview.h"
#include <fstream>

using namespace std;

void merge(ProductReview* vet, int left, int mid, int right);
void mergeSort(ProductReview* vet, int begin, int end);

void mergeSortMetrics(string pathToFolder, string archiveName, int repetition);

#endif // MergeSort_H_INCLUDED