#include "Ponto2D.hpp"
#include <cmath>

Ponto2D::Ponto2D(double x, double y) {
    this->x = x;
    this->y = y;
}

double Ponto2D::calcular_distancia(Ponto2D* ponto) {
    double dx = x - ponto->x;
    double dy = y - ponto->y;
    return std::sqrt(dx * dx + dy * dy);
}
