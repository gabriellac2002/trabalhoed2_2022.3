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
        double timestamp;

    public:
        void print();
        void setProductId(string usId);
        void setUserId(string prodId);
        void setRating(float rat);
        void setTimestamp(long time);
        string getProductId();
        string getUserId();
        float getRating();
        long getTimestamp();

};

#endif // ProductReview_H_INCLUDED