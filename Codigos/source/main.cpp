#include <iostream>
#include <cstdlib>
#include "ProductReview.h"
#include "Sort.h"

using namespace std;

void sort(ProductReview *vet, int n, int methodId);

int main()
{
    return 0;
}


void sort(ProductReview *vet, int n, int methodId)
{
    Sort sort = new Sort(vet);
    int low,high;
    sort.GetExtremes(&low,&high);
    switch(methodId){
        case 0:
            sort.QuickSort(low,high);
            break;
        case 1:
            sort.MergeSort(n);
            break;
        case 2:
            sort.PigeonholeSort(n);
            break;
        default:
            cout <<"Metodo de organização nao encontrado";              
    }
}


