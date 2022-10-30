#ifndef ProductReview_H_INCLUDED
#define ProductReview_H_INCLUDED
#include "Product.h"
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
        ProductReview* import(int n);
        void setUserId(string uId);
        void setProductId(string pId);
        void setRating(float rat);
        void setTimestamp(long time);

};

#endif // ProductReview_H_INCLUDED