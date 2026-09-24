#ifndef PONTO_HPP
#define PONTO_HPP

#include <iostream>

using namespace std;

struct Ponto {

    int x, y;

    Ponto(int = 0, int = 0);
    void setPonto(int, int);
    int getX() const { return x; };
    int getY() const { return y; };

};

#endif