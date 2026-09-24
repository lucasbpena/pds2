#ifndef ROBO_HPP
#define ROBO_HPP

#include "Ponto2D.hpp"

struct Robo {
    int _id;
    Ponto2D _posicao;
    double _energia;
    bool _com_bola;

    Robo(int id, Ponto2D posicao, bool com_bola);

    void mover(double v, double th, double t);
    double calcular_distancia(Robo* robo);
    Robo* determinar_robo_mais_proximo(Robo** naves, int n);
    void passar_bola(Robo** time, int n);
    void imprimir_status();
};

#endif
