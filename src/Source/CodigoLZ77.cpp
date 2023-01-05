#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

#include "../Headers/CodigoLZ77.h"

using namespace std;

CodigoLZ77::CodigoLZ77(){}

int CodigoLZ77::setP(int P)
{
    this->p = P;
}

int CodigoLZ77::setL(int L)
{
    this->l = L;
}

char CodigoLZ77::setC(char C)
{
    this->c = C;
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