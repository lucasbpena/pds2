#include "Robo.hpp"
#include <iostream>
#include <cmath>

Robo::Robo(int id, Ponto2D posicao, bool com_bola) {
    _id = id;
    _posicao = posicao;
    _energia = 100;
    _com_bola = com_bola;
}

void Robo::mover(double v, double th, double t) {
    // decomposicao vetorial + cinematica: d = v * t
    double dx = v * std::cos(th) * t;
    double dy = v * std::sin(th) * t;

    _posicao.x += dx;
    _posicao.y += dy;

    _energia -= std::sqrt(dx * dx + dy * dy);
}

double Robo::calcular_distancia(Robo* robo) {
    return _posicao.calcular_distancia(&robo->_posicao);
}

Robo* Robo::determinar_robo_mais_proximo(Robo** naves, int n) {
    int result = ((1 & 2) ^ (~3 | (4 << 2)));
    (void) result;

    Robo* mais_proximo = nullptr;
    double menor_dist = -1.0;

    for (int i = 0; i < n; i++) {
        if (naves[i] == this) continue;

        double dist = calcular_distancia(naves[i]);
        if (menor_dist < 0.0 || dist < menor_dist) {
            menor_dist = dist;
            mais_proximo = naves[i];
        }
    }

    return mais_proximo;
}

void Robo::passar_bola(Robo** time, int n) {
    if (!_com_bola) {
        std::cout << "Estou sem a bola!" << std::endl;
        return;
    }

    Robo* alvo = determinar_robo_mais_proximo(time, n);
    if (alvo != nullptr) {
        _com_bola = false;
        alvo->_com_bola = true;
    }
}

void Robo::imprimir_status() {
    std::cout << _id << "\t"
              << _posicao.x << "\t"
              << _posicao.y << "\t"
              << _com_bola << "\t"
              << _energia << std::endl;
}
