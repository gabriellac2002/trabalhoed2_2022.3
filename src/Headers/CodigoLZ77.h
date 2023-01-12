#ifndef CodigoLZ77_H_INCLUDED
#define CodigoLZ77_H_INCLUDED


using namespace std;

class CodigoLZ77
{
    private:
    int p;//posicao do inicio da sequencia antes do ponteiro no dicionario
    int l;//tamanho da sequencia, que pode ir do dicionario ao buffer
    char c;//caractere apos o fim da sequencia
    int confirma =0;

    public:
    CodigoLZ77();
    void setP(int P);
    void setL(int L);
    void setC(char c);
    void setConfirma();
    int getP();
    int getL();
    char getC();
    int getConfirma();
};


#endif // CodigoLZ77_H_INCLUDED