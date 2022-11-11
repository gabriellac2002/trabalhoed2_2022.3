#ifndef ProductReview_H_INCLUDED
#define ProductReview_H_INCLUDED

using namespace std;

class ProductReview
{
    private:
        string userId;
        string productId;
        float rating;
        long timestamp;

    public:
        ProductReview();//construtor vazio
        ProductReview(string userId, string productId, float rating, long timestamp);
        ~ProductReview(); //destrutor

        //getters e setters
        string getUserId();
        void setUserId(string userId);
        string getProductId();
        void setProductId(string productId);
        float getRating();
        void setRating(float rating);
        void setUserId(float rating);
        long getTimesTamp();
        void setTimesTamp(long timestamp);

        //funções solicitadas na etapa 1
        void print();
        void createBinary(string& path);
        void getReview(int i);
        ProductReview* import(int n);
};

#endif // ProductReview_H_INCLUDED