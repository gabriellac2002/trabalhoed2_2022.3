#ifndef ProductReview_H_INCLUDED
#define ProductReview_H_INCLUDED

class ProductReview
{
    private:
        int tamanho;

    public:
        ProductReview(int n);

        void print();
        void createBinary(string& path);
        void getReview(int i);

        ProductReview* import(int n);
};

#endif // ProductReview_H_INCLUDED