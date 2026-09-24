#include <string>
#include <iostream>
#include <iomanip>
#include "FilaProcessos.hpp"

FilaProcessos::FilaProcessos()
    : _inicio(nullptr), _fim(nullptr), _proximo_id(1), _tamanho(0) {}

void FilaProcessos::adicionar_processo(std::string nome, int prioridade) {
    int id = this->_proximo_id;
    this->_proximo_id++;

    Processo* p = new Processo(id, nome, prioridade);
    No* novo = new No;
    novo->processo = p;
    novo->proximo = nullptr;

    No* anterior = nullptr;
    No* atual = this->_inicio;
    while (atual != nullptr && atual->processo->getPrioridade() >= prioridade) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (anterior == nullptr) {
        novo->proximo = this->_inicio;
        this->_inicio = novo;
    } else {
        novo->proximo = atual;
        anterior->proximo = novo;
    }

    if (novo->proximo == nullptr) {
        this->_fim = novo;
    }

    this->_tamanho++;
}

Processo* FilaProcessos::remover_processo_maior_prioridade() {
    if (this->_inicio == nullptr) {
        return nullptr;
    }

    No* alvo = this->_inicio;
    Processo* p = alvo->processo;

    this->_inicio = alvo->proximo;
    if (this->_inicio == nullptr) {
        this->_fim = nullptr;
    }

    delete alvo;
    this->_tamanho--;
    return p;
}

Processo* FilaProcessos::remover_processo_por_id(int id) {
    No* anterior = nullptr;
    No* atual = this->_inicio;

    while (atual != nullptr && atual->processo->getID() != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == nullptr) {
        return nullptr;
    }

    if (anterior == nullptr) {
        this->_inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    if (atual == this->_fim) {
        this->_fim = anterior;
    }

    Processo* p = atual->processo;
    delete atual;
    this->_tamanho--;
    return p;
}

void FilaProcessos::estimativa_tempo_para_execucao(int id) {
    double tempo = 0.0;
    No* atual = this->_inicio;

    while (atual != nullptr && atual->processo->getID() != id) {
        tempo += atual->processo->tempo_reservado_processo();
        atual = atual->proximo;
    }

    if (atual == nullptr) {
        return;
    }

    std::cout << "Tempo estimado para execução do processo "
              << atual->processo->getNome()
              << " (id=" << atual->processo->getID() << ") eh "
              << std::fixed << std::setprecision(1) << tempo
              << " segundos." << std::endl;
}

void FilaProcessos::imprimir_fila() {
    No* atual = this->_inicio;
    while (atual != nullptr) {
        atual->processo->imprimir_dados();
        atual = atual->proximo;
    }
}
