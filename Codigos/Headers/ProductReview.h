#ifndef ProductReview_H_INCLUDED
#define ProductReview_H_INCLUDED
#include "string"

using namespace std;

class ProductReview
{
    private:
        string userId;
        string productId;
        float rating;
        long timestamp;

    public:
        void print();
        void createBinary(string& path);
        void getReview(int i);
        // ProductReview* import(int n);
};

#endif // ProductReview_H_INCLUDED