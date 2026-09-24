# VPL07 — Conceitos discutidos

Resumo das explicações da sessão de mentoria sobre `Processo` e `FilaProcessos`.

## Declaração × definição, e o papel do linker
- Declaração: só a assinatura (`Tipo nome(params);`), termina em `;`. Definição: tem corpo `{ ... }`.
- Compilação é por arquivo (`.cpp` → `.o`); basta a declaração pra compilar uma chamada.
- O *linker* junta os `.o` e resolve cada chamada com a definição correspondente.
- Falta de definição ⇒ compila, mas dá `undefined reference` (erro de linkedição, não de sintaxe).
- Toda função com retorno não-`void` precisa de `return` em **todos** os caminhos (senão, comportamento indefinido).

## Lista encadeada (sem containers prontos)
- Nó (`No`): guarda um `Processo*` (não por valor) + `proximo`. Guardar ponteiro é o que permite devolver `Processo*` válido depois de remover o nó da lista.
- Percurso: `atual = atual->proximo` até `nullptr`.
- Inserção ordenada (decrescente, estável): andar enquanto `atual->prioridade >= nova` — parar só num valor **menor** garante que o novo entra depois dos iguais (ordem de inserção preservada).
- Religar sempre na ordem: `novo->proximo = ...` **antes** de redirecionar quem apontava pra frente (senão perde o resto da lista).
- Remover exige guardar o nó **anterior** (lista simplesmente encadeada não anda pra trás); casos especiais: lista vazia, remover o primeiro, remover o último (atualizar `_fim`).
- `delete` só no nó — o `Processo` continua vivo pois é o valor retornado.

## Erros recorrentes corrigidos
- `struct X { ... }` sem `;` final.
- Includes ausentes (`<string>`, header próprio) ou com `< >` em vez de `" "` para arquivo do projeto.
- Definição sem tipo de retorno, ou com assinatura diferente da declaração (parâmetros sem tipo, ordem trocada).
- Atributo com nome errado (`this->id` vs `this->_id`).
- Container pronto (`std::vector`) usado onde o enunciado exige estrutura própria.
- Comparação de string sensível a acento/caixa (`"MÉDIA"` vs `"MEDIA"` exigido).

## Saída formatada
- `\t` entre campos, `\n`/`std::endl` ao final, conforme o formato pedido.
- Uma casa decimal: `#include <iomanip>` + `std::fixed << std::setprecision(1)`.
