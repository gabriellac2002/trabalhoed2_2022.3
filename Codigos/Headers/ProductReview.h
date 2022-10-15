#ifndef ProductReview_H_INCLUDED
#define ProductReview_H_INCLUDED

#include <string>

using namespace std;

class ProductReview
{
private:
    int tamanho;
    int userId;
    int productId;
    float rating;
    string timestamp;

public:
    ProductReview(int n);

    void print(int n);
    void createBinary(string &path);
    void getReview(int i);
    int GetuserId();

    ProductReview *import(int n);
};

#endif // ProductReview_H_INCLUDED