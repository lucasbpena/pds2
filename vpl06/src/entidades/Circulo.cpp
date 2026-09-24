#include<iomanip>

#include "Circulo.hpp"

using namespace std;

Circulo::Circulo(double r, int x, int y) {
    setRaio(r);
}

void Circulo::setRaio(double r) {
    this->raio = (r >= 0) ? r : 0;
}

double Circulo::getRaio() const {
    return this->raio;
}

double Circulo::area() const {
    return 3.14159 * this->raio * this->raio;
}