#include "Tabuleiro.hpp"
#include <iostream>

bool Tabuleiro::validaJogada(int linha, int coluna, char simbolo){
    // posicoes linha coluna
    if (linha < 0 || linha > 2){
        return 0;
    } else if (coluna < 0 || coluna > 2){
        return 0;
    }
    // simbolo
    if (simbolo !='X' && simbolo!='O'){
        return 0;
    }
    // celula
    if (this->tabuleiro[linha][coluna] != ' ') {
        return 0;
    }

    return 1;
}


void Tabuleiro::fazerJogada(int linha, int coluna, char simbolo){
    this->tabuleiro[linha][coluna] = simbolo;
}

char Tabuleiro::verificarEstadoPartida(){
    // linhas
    for (int i = 0; i < 3; i++){
        if (this->tabuleiro[i][0] == this->tabuleiro[i][1] && this->tabuleiro[i][0] == this->tabuleiro[i][2]){
            if(this->tabuleiro[i][0] != ' '){
               return this->tabuleiro[i][0];
            }
        }
    }
    //colunas
    for (int j = 0; j < 3; j++){
        if (this->tabuleiro[0][j] == this->tabuleiro[1][j] && this->tabuleiro[0][j] == this->tabuleiro[2][j]){
            if(this->tabuleiro[0][j] != ' '){
               return this->tabuleiro[0][j];
            }
        }
    }
    //diagonais
    if (this->tabuleiro[0][0] == this->tabuleiro[1][1] && this->tabuleiro[0][0] == this->tabuleiro[2][2]){
        if(this->tabuleiro[0][0] != ' '){
            return this->tabuleiro[0][0];
        }
    } else if (this->tabuleiro[0][2] == this->tabuleiro[1][1] && this->tabuleiro[0][2] == this->tabuleiro[2][0]){
        if(this->tabuleiro[0][2] != ' '){
            return this->tabuleiro[0][2];
        }
    }
    // verificar se existe vazio
    for (int i=0; i<3;i++){
        for (int j=0; j<3; j++){
            if(this->tabuleiro[i][j]==' ')
                return 'P';
        }
    }
    // empate
    return 'E';
}

void Tabuleiro::imprimir() {
    for (int i = 0; i < 3; i++) {
        std::cout << ' ' << tabuleiro[i][0] << " | "
                  << tabuleiro[i][1] << " | "
                  << tabuleiro[i][2] << "\n";
        if (i < 2)
            std::cout << "-----------\n";
    }
}

