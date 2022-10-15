#include <string>
#include "ProductReview.h"
using namespace std;

class Sort
{
private:
    ProductReview *file;

public:
    Sort(ProductReview *archive);
    ~Sort();
    void MergeSort(int tam);
    void QuickSort(int low, int high);
    void PigeonholeSort(int tam);
    void TimSort(int tam);
    int GetExtremes(int *low, int *high);
};