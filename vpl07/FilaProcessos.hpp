#ifndef FILAPROC
#define FILAPROC
#include <string>
#include "Processo.hpp"

struct No {
    Processo* processo;
    No* proximo;
};

struct FilaProcessos {

    No* _inicio;
    No* _fim;
    int _proximo_id;
    int _tamanho;

    FilaProcessos();

    void adicionar_processo(std::string nome, int prioridade);

    Processo* remover_processo_maior_prioridade();

    Processo* remover_processo_por_id(int id);

    void estimativa_tempo_para_execucao(int id);

    void imprimir_fila();
};

#endif
