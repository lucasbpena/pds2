#include <iostream>
#include <string>
#include "Processo.hpp"

Processo::Processo(int id, std::string nome, int prioridade)
    : _id(id), _prioridade(prioridade), _nome(nome) {}

int Processo::getID() {
    return this->_id;
}

int Processo::getPrioridade() {
    return this->_prioridade;
}

std::string Processo::getNome() {
    return this->_nome;
}

double Processo::tempo_reservado_processo() {
    if (this->_prioridade == 0) {
        return 0.5;
    } else if (this->_prioridade == 1) {
        return 1.5;
    } else {
        return 3.0;
    }
}

void Processo::imprimir_dados() {
    std::string texto;

    if (this->_prioridade == 0) {
        texto = "BAIXA";
    } else if (this->_prioridade == 1) {
        texto = "MEDIA";
    } else {
        texto = "ALTA";
    }

    std::cout << this->_id << "\t" << this->_nome << "\t" << texto << std::endl;
}
