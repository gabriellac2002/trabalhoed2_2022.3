#ifndef ProductReview_H_INCLUDED
#define ProductReview_H_INCLUDED
#include "string"

using namespace std;

class ProductReview
{
    private:
        int tamanho;

    public:
        ProductReview(int n);

        void print(Product product, fstream &file);
        void createBinary(string& path);
        void getReview(int i);

        ProductReview* import(int n);
};

#endif // ProductReview_H_INCLUDED