#ifndef PARTIDA
#define PARTIDA
#include "Tabuleiro.hpp"
#include "Jogador.hpp"


class Partida{
    public:
        Tabuleiro tabuleiro;
        Jogador jogador1;
        Jogador jogador2;
        Jogador* atual;

    Partida(Jogador jogador1, Jogador jogador2) : jogador1(jogador1), jogador2(jogador2){
        this->atual = &(this->jogador1);
        this->tabuleiro = Tabuleiro();
    };

    Jogador& getJogadorAtual();

    void executarJogada(int linha, int coluna);

    char statusPartida();

    void exibirPartida();


};

#endif