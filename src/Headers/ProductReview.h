#ifndef ProductReview_H_INCLUDED
#define ProductReview_H_INCLUDED
#include "string"
#include "../Headers/Product.h"

using namespace std;

class ProductReview
{
    private:
        string userId;
        string productId;
        float rating;
        string timestamp;

    public:
        ProductReview();
        void print(Product product, fstream &file);
        void createBinary(string& path);
        void getReview(int i);
        void print();
        void setProductId(string userId);
        void setUserId(string productId);
        void setRating(float rating);
        void setTimestamp(string timestamp);
        string getProductId();
        string getUserId();
        float getRating();
        string getTimestamp();

};

#endif // ProductReview_H_INCLUDED