#ifndef CodigoLZ77_H_INCLUDED
#define CodigoLZ77_H_INCLUDED


using namespace std;

class CodigoLZ77
{
    private:
    int id;
    int p;//posicao do inicio da sequencia antes do ponteiro no dicionario
    int l;//tamanho da sequencia, que pode ir do dicionario ao buffer
    char c;//caractere apos o fim da sequencia

    public:
    CodigoLZ77();
    int setId(int n);
    int setP(int P);
    int setL(int L);
    char setC(char c);
    int getId();
    int getP();
    int getL();
    char getC();
};


#endif // CodigoLZ77_H_INCLUDED