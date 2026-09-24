#include "Tabuleiro.hpp"
#include "Jogador.hpp"
#include "Partida.hpp"
#include <iostream>

Jogador& Partida::getJogadorAtual(){
    return *(this->atual);
}

void Partida::executarJogada(int linha, int coluna){
    if (this->tabuleiro.validaJogada(linha, coluna, this->atual->simbolo)){
        this->tabuleiro.fazerJogada(linha, coluna, this->atual->simbolo);
        if (this->atual == &(this->jogador1)){
            this->atual = &jogador2;
        } else {
            this->atual = &jogador1;
        }
    } else {
        std::cout << "Jogada invalida!\n";
    }
}

char Partida::statusPartida(){
    return this->tabuleiro.verificarEstadoPartida();
}

void Partida::exibirPartida(){
    this->tabuleiro.imprimir();
}