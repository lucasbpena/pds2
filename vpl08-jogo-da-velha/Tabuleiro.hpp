#ifndef TABULEIRO
#define TABULEIRO
#include <string>
class Tabuleiro{
    public:
        char tabuleiro[3][3];
  

    bool validaJogada(int linha, int coluna, char simbolo);

    void fazerJogada(int linha, int coluna, char simbolo);

    char verificarEstadoPartida();

    void imprimir();

    Tabuleiro(){
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                this->tabuleiro[i][j] = ' ';
            }
        }
    }

};


#endif