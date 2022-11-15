#ifndef NODUPLO_H_INCLUDED
#define NODUPLO_H_INCLUDED

class NoDuplo
{
public:
    NoDuplo()                { contador = 0; };
    ~NoDuplo()               { } ;
    void setAnt(NoDuplo *p)  { ant = p; };
    void setProx(NoDuplo *p) { prox = p; };
    void setInfo(int val)    { info = val; };
    void incrementaContador()  { contador += 1;};
    void decrementaContador()  { contador -= 1;};
    NoDuplo* getAnt()        { return ant; };
    NoDuplo* getProx()       { return prox; };
    int getInfo()            { return info; };
private:
    NoDuplo *ant;  /// ponteiro para anterior
    int info;      /// informacao do no
    int contador; //contador
    NoDuplo *prox; /// ponteiro para proximo
};
#endif