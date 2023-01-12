#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

#include "../Headers/CodigoLZ77.h"

using namespace std;

CodigoLZ77::CodigoLZ77(){}

void CodigoLZ77::setP(int P)
{
    this->p = P;
}

void CodigoLZ77::setL(int L)
{
    this->l = L;
}

void CodigoLZ77::setC(char C)
{
    this->c = C;
}

void CodigoLZ77::setConfirma()
{
    this->confirma = 1;
}

int CodigoLZ77::getP()
{
    return this->p;
}

int CodigoLZ77::getL()
{
    return this->l;
}

char CodigoLZ77::getC()
{
    return this->c;
}

int CodigoLZ77::getConfirma()
{
    return this->confirma;
}