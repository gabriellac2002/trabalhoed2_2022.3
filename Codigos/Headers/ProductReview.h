#ifndef ProductReview_H_INCLUDED
#define ProductReview_H_INCLUDED
#include "string"

using namespace std;

class ProductReview
{
    private:
        string userId;
        string productId;
        string rating;
        string timestamp;

    public:
        void print();
        void setProductId(string userId);
        void setUserId(string productId);
        void setRating(string rating);
        void setTimestamp(string timestamp);
        string getProductId();
        string getUserId();
        string getRating();
        string getTimestamp();

};

#endif // ProductReview_H_INCLUDED