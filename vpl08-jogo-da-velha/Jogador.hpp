#ifndef JOGADOR
#define JOGADOR
#include <string>
class Jogador{
    public:
        std::string nome;
        char simbolo;

    Jogador(std::string nome, char simbolo) : nome(nome), simbolo(simbolo){}

    std::string getNome() const;

    char getSimbolo() const;

};


#endif