#include "Partida.hpp"
#include <iostream>

int main() {
    Jogador jogador1("Ana", 'X');
    Jogador jogador2("Bernardo", 'O');
    Partida partida(jogador1, jogador2);

    int linha, coluna;

    while (partida.statusPartida() == 'P') {
        partida.exibirPartida();

        const Jogador& atual = partida.getJogadorAtual();
        std::cout << "\nVez de " << atual.getNome()
                  << " (" << atual.getSimbolo() << ")\n";

        std::cout << "Digite linha e coluna: ";
        std::cin >> linha >> coluna;
        std::cout << "\n";

        partida.executarJogada(linha, coluna);
    }

    partida.exibirPartida();

    char status = partida.statusPartida();

    if (status == 'X' || status == 'O') {
        const Jogador& vencedor =
            (jogador1.getSimbolo() == status) ? jogador1 : jogador2;
        std::cout << "Vencedor: " << vencedor.getNome() << " " << status << std::endl;
    } else if (status == 'E') {
        std::cout << "Empate!" << std::endl;
    }

    return 0;
}