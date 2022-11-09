#ifndef ProductReview_H_INCLUDED
#define ProductReview_H_INCLUDED

using namespace std;

class ProductReview
{
    private:
        char userId[14];
        char productId[10];
        float rating;
        long timestamp;

    public:
        void print();
        // void createBinary(string& path);
        // void getReview(int i);
        // ProductReview* import(int n);
};

#endif // ProductReview_H_INCLUDED