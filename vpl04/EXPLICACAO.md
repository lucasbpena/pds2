# VPL04 — Ponto2D e Robo (explicação detalhada)

## 1. Visão geral

O exercício pede a implementação de **dois TADs** (Tipos Abstratos de Dados) usando
`struct`: `Ponto2D` e `Robo`. A `main` **já está pronta** (`vpl04.cpp`) — ela é o
"cliente" que só conhece o **contrato** (os cabeçalhos). Você não deve tocar nela.

Arquivos do projeto:

| Arquivo        | Papel                                                        |
|----------------|-------------------------------------------------------------|
| `Ponto2D.hpp`  | **Declaração** do TAD Ponto2D (o que existe)                |
| `Ponto2D.cpp`  | **Implementação** do TAD Ponto2D (como funciona)            |
| `Robo.hpp`     | **Declaração** do TAD Robo                                  |
| `Robo.cpp`     | **Implementação** do TAD Robo                              |
| `vpl04.cpp`    | `main` fornecida — lê a entrada e chama os métodos          |
| `EXPLICACAO.md`| este documento                                              |

---

## 2. Por que separar `.hpp` e `.cpp`

### 2.1 O modelo de compilação do C++

O C++ compila **cada `.cpp` separadamente** (cada um é uma *translation unit*).
O compilador transforma cada `.cpp` em um arquivo-objeto `.o`; depois o **linker**
junta todos os `.o` em um único executável.

```
Ponto2D.cpp  ──g++──►  Ponto2D.o  ─┐
Robo.cpp     ──g++──►  Robo.o     ─┼──linker──►  executável (a.out / prog)
vpl04.cpp    ──g++──►  vpl04.o    ─┘
```

Quando `vpl04.cpp` é compilado, o compilador **não enxerga** o conteúdo de
`Robo.cpp`. Ele só precisa saber a **assinatura** dos métodos (nome, parâmetros,
tipo de retorno) para gerar o código que os chama. Essa assinatura vem do `.hpp`
via `#include`. Na hora do link, o linker resolve cada chamada apontando para o
corpo real que veio de `Robo.o`.

### 2.2 O que vai em cada arquivo

- **`.hpp` (cabeçalho / *header*)** — a **declaração**, o "contrato":
  - atributos do `struct`;
  - assinaturas dos métodos, **sem corpo** (terminam em `;`).

- **`.cpp` (implementação)** — a **definição**:
  - o corpo de cada método, escrito como `TipoRetorno NomeDoStruct::metodo(...) { ... }`.

### 2.3 Vantagens

1. **Compilação incremental.** Mudou só o corpo de `mover()`? Recompila apenas
   `Robo.cpp`. Em projetos grandes isso economiza minutos a cada build.
2. **Separação contrato × implementação.** Quem usa o TAD (a `main`) inclui só o
   `.hpp`. Ele não depende de — nem precisa ver — como você implementou.
3. **Evita violar a ODR** (*One Definition Rule*, "regra da definição única").
   Um `.hpp` pode ser incluído por vários `.cpp`. Se o **corpo** de uma função
   comum estivesse no `.hpp`, cada `.cpp` que o inclui teria a sua própria cópia
   da definição → o linker acusaria *"multiple definition"*. No `.hpp` ficam só
   **declarações** (que podem se repetir); a **definição** fica em um único `.cpp`.

> Observação: dá para fazer *header-only* (corpo dentro do `struct`, no `.hpp`).
> Funciona porque métodos definidos dentro da classe são implicitamente `inline`
> (o `inline` diz ao linker "pode haver cópias idênticas, funde todas"). Mas o
> enunciado pede explicitamente a modularização `.hpp` + `.cpp`.

---

## 3. Include guard: `#ifndef / #define / #endif`

```cpp
#ifndef PONTO2D_HPP     // "if not defined": se a macro PONTO2D_HPP NÃO existe...
#define PONTO2D_HPP     // ...define a macro e segue lendo o conteúdo

// ... struct Ponto2D { ... };

#endif                  // fim do trecho protegido
```

`#include "X.hpp"` significa literalmente **"copie e cole X.hpp aqui"**. No nosso
projeto isso acontece em cascata:

```
vpl04.cpp
 ├── #include "Ponto2D.hpp"         → traz  struct Ponto2D   (1ª vez)
 └── #include "Robo.hpp"
      └── #include "Ponto2D.hpp"    → traria struct Ponto2D   (2ª vez)  ← problema
```

Sem o guard, `struct Ponto2D { ... }` apareceria **duas vezes** dentro de
`vpl04.cpp` → erro de compilação:

```
error: redefinition of 'struct Ponto2D'
```

Com o guard: na 1ª inclusão a macro `PONTO2D_HPP` ainda não existe, então o bloco
é lido e a macro passa a existir. Na 2ª inclusão a macro **já existe**, o
`#ifndef` é falso e o pré-processador **pula tudo** até o `#endif`. Resultado: o
`struct` é definido exatamente uma vez.

- O nome da macro é convenção: arquivo em MAIÚSCULAS, `.` vira `_`
  (`Ponto2D.hpp` → `PONTO2D_HPP`). Precisa ser **único** no projeto.
- Alternativa moderna: `#pragma once` na primeira linha (mais curto; suportado por
  praticamente todos os compiladores, mas não é padrão oficial). O trio
  `#ifndef/#define/#endif` é 100% portável.

---

## 4. O operador `::` (resolução de escopo)

`::` liga um nome ao **escopo** a que ele pertence.

No `.cpp` usamos para dizer que um método definido "solto" pertence ao `struct`:

```cpp
// Robo.hpp — declaração DENTRO do struct
struct Robo {
    void mover(double v, double th, double t);
};
```

```cpp
// Robo.cpp — definição FORA do struct
void Robo::mover(double v, double th, double t) {
//   ^^^^^^  "este 'mover' é o de Robo"
    _posicao.x += ...;   // aqui dentro, os atributos do objeto estão visíveis
}
```

Sem o `Robo::`, o compilador entenderia `mover` como uma função **global**
independente — que não teria acesso a `_posicao`, `_energia`, etc., e não
casaria com a declaração feita no `.hpp`.

Ler em voz alta: `Robo::mover` = "o `mover` **de** `Robo`".

Outros usos do mesmo operador:

| Uso                    | Significado                                  |
|------------------------|---------------------------------------------|
| `std::cout`, `std::sqrt` | nome dentro do *namespace* `std`          |
| `Robo::mover`          | método `mover` do `struct` `Robo`           |
| `::algo`               | o `algo` do escopo global                    |

Diferente de `.` e `->`, que operam sobre **objetos** em tempo de execução
(`time[i]->mover(...)`, `_posicao.x`). O `::` opera sobre **tipos/namespaces**.

---

## 5. O ponteiro `this` e o `this->`

Dentro de qualquer método, `this` é um ponteiro para o **objeto que recebeu a
chamada**. `this->x` é o atributo `x` desse objeto.

Você **só precisa** de `this->` quando existe uma variável local (normalmente um
parâmetro) com o **mesmo nome** de um atributo:

### `Ponto2D` — há conflito

```cpp
Ponto2D::Ponto2D(double x, double y) {   // parâmetros: x, y  (mesmo nome dos atributos)
    this->x = x;   // this->x = atributo   |   x = parâmetro
    this->y = y;
}
```

Se escrevesse `x = x;`, os dois lados seriam o **parâmetro** — o atributo nunca
seria preenchido.

### `Robo` — não há conflito

```cpp
Robo::Robo(int id, Ponto2D posicao, bool com_bola) {  // parâmetros SEM "_"
    _id       = id;         // _id é atributo (nome único) — dispensa this->
    _posicao  = posicao;
    _energia  = 100;
    _com_bola = com_bola;
}
```

Como os atributos usam o prefixo `_` e os parâmetros não, não há ambiguidade.
Essa é justamente a razão de a convenção `_atributo` (ou `m_atributo`) ser comum.

---

## 6. TAD `Ponto2D`

### 6.1 Declaração (`Ponto2D.hpp`)

```cpp
struct Ponto2D {
    double x;
    double y;

    Ponto2D(double x = 0.0, double y = 0.0);
    double calcular_distancia(Ponto2D* ponto);
};
```

### 6.2 Construtor com valores padrão (Dica 1)

```cpp
Ponto2D(double x = 0.0, double y = 0.0);
```

Os `= 0.0` são **argumentos padrão**: se o chamador não passar valor, entra `0.0`.
Consequência prática — todas estas formas passam a ser válidas:

```cpp
Ponto2D a;             // a.x = 0.0, a.y = 0.0   ← necessário p/ variável na stack
Ponto2D b(3.0);        // b.x = 3.0, b.y = 0.0
Ponto2D c(3.0, 4.0);   // c.x = 3.0, c.y = 4.0
```

Por que isso importa: no `struct Robo` existe o atributo `Ponto2D _posicao;`.
Para o compilador conseguir construir um `Robo`, ele precisa saber construir um
`Ponto2D` **sem argumentos** (construção padrão). Sem o construtor padrão (ou
sem os `= 0.0`), você teria o erro *"no matching function for call to
Ponto2D::Ponto2D()"*.

> Alternativa citada no enunciado: escrever **dois** construtores — um vazio
> `Ponto2D() {}` e outro `Ponto2D(double, double)`. O efeito é o mesmo; usar
> argumentos padrão só evita repetição.

### 6.3 `calcular_distancia` (`Ponto2D.cpp`)

```cpp
double Ponto2D::calcular_distancia(Ponto2D* ponto) {
    double dx = x - ponto->x;
    double dy = y - ponto->y;
    return std::sqrt(dx * dx + dy * dy);
}
```

Distância euclidiana: `√((x₁−x₂)² + (y₁−y₂)²)`.

- `x` e `y` (sem `this->`) são os atributos do objeto atual — não há variável
  local com esse nome, então não há ambiguidade.
- `ponto->x` acessa o atributo `x` do objeto apontado por `ponto` (`->` =
  "desreferencia o ponteiro e pega o membro").
- `std::sqrt` vem de `<cmath>`, incluído no `.cpp`.

---

## 7. TAD `Robo`

### 7.1 Declaração (`Robo.hpp`)

```cpp
#include "Ponto2D.hpp"      // Robo TEM um Ponto2D dentro dele

struct Robo {
    int     _id;
    Ponto2D _posicao;       // objeto por valor (na stack), não ponteiro
    double  _energia;
    bool    _com_bola;

    Robo(int id, Ponto2D posicao, bool com_bola);
    void   mover(double v, double th, double t);
    double calcular_distancia(Robo* robo);
    Robo*  determinar_robo_mais_proximo(Robo** naves, int n);
    void   passar_bola(Robo** time, int n);
    void   imprimir_status();
};
```

Pontos de atenção pedidos pelo enunciado:

- **`_energia` sempre começa em 100** — não vem de parâmetro.
- **`_com_bola`** é `bool`.
- A posição é **um `Ponto2D` por valor**, na stack. O construtor recebe
  `Ponto2D posicao` (cópia), **não** `Ponto2D*`.
- Atributos extras (`_id`, `_posicao`) são livres — o enunciado permite adicionar
  o que for necessário.

### 7.2 Construtor (`Robo.cpp`)

```cpp
Robo::Robo(int id, Ponto2D posicao, bool com_bola) {
    _id       = id;
    _posicao  = posicao;   // cópia do Ponto2D recebido por valor
    _energia  = 100;       // regra fixa do enunciado
    _com_bola = com_bola;
}
```

Na `main`: `time[i] = new Robo(i, Ponto2D(x, y), com_bola);`
Um `Ponto2D` temporário é criado, copiado para o parâmetro `posicao` e daí
copiado para `_posicao`. O temporário some ao fim da linha; `_posicao` guarda a
sua própria cópia.

### 7.3 `mover(v, th, t)` — a física

Parâmetros:
- `v`  — magnitude (módulo) do vetor velocidade;
- `th` — orientação do vetor velocidade, **em radianos**;
- `t`  — tempo durante o qual a velocidade foi aplicada.

**Passo 1 — decomposição vetorial.** Um vetor de módulo `v` e ângulo `th` tem
componentes:

```
vx = v · cos(th)
vy = v · sin(th)
```

**Passo 2 — cinemática (velocidade constante).** Deslocamento = velocidade × tempo:

```
dx = vx · t = v · cos(th) · t
dy = vy · t = v · sin(th) · t
```

**Passo 3 — atualizar a posição:**

```
_posicao.x += dx
_posicao.y += dy
```

**Passo 4 — descontar energia.** A distância percorrida é o módulo do vetor
deslocamento; ela sai de `_energia`:

```
distancia = √(dx² + dy²)
_energia -= distancia
```

Código:

```cpp
void Robo::mover(double v, double th, double t) {
    double dx = v * std::cos(th) * t;
    double dy = v * std::sin(th) * t;

    _posicao.x += dx;
    _posicao.y += dy;

    double distancia = std::sqrt(dx * dx + dy * dy);
    _energia -= distancia;
}
```

**Conferindo com o Exemplo 1:** comando `m 0 1.0 0.0 1.0` → `v=1`, `th=0`, `t=1`.
`dx = 1·cos(0)·1 = 1`, `dy = 1·sin(0)·1 = 0`.
Nova posição do robô 0: `(1.00, 0.00)`.
`distancia = √(1² + 0²) = 1` → `_energia = 100 − 1 = 99.00`. ✔ (bate com a saída)

> Note que, com velocidade constante, `distancia` é sempre `v · t`. Calcular
> `√(dx²+dy²)` é o "caminho geral" pedido pela dica e funciona igual.

### 7.4 `calcular_distancia(Robo*)`

```cpp
double Robo::calcular_distancia(Robo* robo) {
    return _posicao.calcular_distancia(&robo->_posicao);
}
```

Reaproveita o método de `Ponto2D` (como sugere a dica):
- `_posicao` é o `Ponto2D` deste robô;
- `robo->_posicao` é o `Ponto2D` do outro robô;
- `&robo->_posicao` pega o **endereço** desse `Ponto2D`, porque
  `Ponto2D::calcular_distancia` espera um `Ponto2D*`.

Precedência: `&robo->_posicao` é lido como `&(robo->_posicao)` — primeiro acessa
o membro, depois pega o endereço.

### 7.5 `determinar_robo_mais_proximo(naves, n)`

```cpp
Robo* Robo::determinar_robo_mais_proximo(Robo** naves, int n) {
    int result = ((1 & 2) ^ (~3 | (4 << 2)));   // linha exigida pelo enunciado
    (void) result;                              // silencia "unused variable"

    Robo*  mais_proximo = nullptr;
    double menor_dist   = -1.0;

    for (int i = 0; i < n; i++) {
        if (naves[i] == this) continue;         // pula o próprio robô

        double dist = calcular_distancia(naves[i]);
        if (menor_dist < 0.0 || dist < menor_dist) {
            menor_dist   = dist;
            mais_proximo = naves[i];
        }
    }
    return mais_proximo;
}
```

- `Robo** naves` é um **array de ponteiros** para `Robo` (o "time"). `naves[i]` é
  um `Robo*`.
- `naves[i] == this`: compara **endereços**. Serve para não medir a distância do
  robô para ele mesmo. (`this` é o robô que invocou o método.)
- `menor_dist = -1.0` funciona como sentinela "ainda não achei ninguém"; como
  distância nunca é negativa, o primeiro candidato sempre entra.
- Retorna `Robo*` — a `main` faz `robo->imprimir_status()` no resultado.

**Sobre a linha `int result = ...`:** o enunciado obriga a incluí-la
literalmente (provavelmente é uma "marca d'água" para detecção de cópia). Ela não
tem efeito na lógica. O `(void) result;` evita que o compilador reclame de
variável não usada quando se compila com `-Wall -Wextra`. É só isso:

| Sub-expressão | Valor |
|---|---|
| `1 & 2`      | `0`  (AND bit a bit) |
| `4 << 2`     | `16` (desloca bits p/ esquerda) |
| `~3`         | `-4` (complemento de 1) |
| `~3 \| 16`   | `-4` (OR bit a bit) |
| `0 ^ -4`     | `-4` (XOR) |

`result` acaba valendo `-4`, e nunca é usado.

### 7.6 `passar_bola(time, n)`

```cpp
void Robo::passar_bola(Robo** time, int n) {
    if (!_com_bola) {
        std::cout << "Estou sem a bola!" << std::endl;
        return;
    }

    Robo* alvo = determinar_robo_mais_proximo(time, n);
    if (alvo != nullptr) {
        _com_bola       = false;
        alvo->_com_bola = true;
    }
}
```

- "Passar a bola" = **apenas** trocar os `bool _com_bola` (nada de mover robô).
- Se quem chamou não está com a bola: imprime exatamente
  `Estou sem a bola!` + quebra de linha (`std::endl`) e retorna.
- Senão: acha o mais próximo, zera a própria posse e marca a do alvo.

**Conferindo com o Exemplo 2:** `b 0` com robôs em `x = 0, 2, 4`. O mais próximo
do robô 0 é o robô 1 (distância 2 < 4). Depois do passe: robô 0 → `_com_bola = 0`,
robô 1 → `_com_bola = 1`. ✔

### 7.7 `imprimir_status()`

```cpp
void Robo::imprimir_status() {
    std::cout << _id        << "\t"
              << _posicao.x  << "\t"
              << _posicao.y  << "\t"
              << _com_bola    << "\t"
              << _energia     << std::endl;
}
```

Formato: `id \t x \t y \t com_bola \t energia`, com `\t` (tab) entre os campos e
quebra de linha no fim.

- `_com_bola` (bool) imprime como `1` / `0` — que é o formato do exemplo.
- Os números aparecem como `0.00`, `100.00`, `99.00` porque a **`main`** já
  configurou o `cout` com `fixed` e `setprecision(2)`:

  ```cpp
  cout << fixed << setprecision(2);
  ```

  Essa formatação "pega" em todo `cout` seguinte, inclusive o de dentro de
  `imprimir_status()`. Por isso não é preciso (nem desejável) reconfigurar aqui.

---

## 8. Como a `main` (`vpl04.cpp`) usa tudo

```cpp
int num_robos;  cin >> num_robos;
Robo *time[num_robos];                       // array de ponteiros para Robo

for (int i = 0; i < num_robos; i++) {
    cin >> x >> y >> com_bola;
    time[i] = new Robo(i, Ponto2D(x, y), com_bola);   // aloca no heap
}

cout << fixed << setprecision(2);            // formatação dos números

while (cin >> data) {                        // lê o caractere do comando
    switch (data) {
        case 's': /* time[i]->imprimir_status() para todos */          break;
        case 'd': /* time[i]->calcular_distancia(time[j]) impresso */   break;
        case 'm': /* cin >> idx,v,th,t; time[idx]->mover(v,th,t) */     break;
        case 'p': /* time[idx]->determinar_robo_mais_proximo(...) */    break;
        case 'b': /* time[idx]->passar_bola(time, num_robos) */         break;
    }
}

for (int i = 0; i < num_robos; i++) delete time[i];   // libera a memória
```

- Os robôs são criados com `new` (heap) e o array guarda **ponteiros**
  (`Robo*`). Por isso os métodos recebem `Robo**` (ponteiro para os elementos do
  array).
- Cada `new` tem seu `delete` no fim — sem vazamento de memória.
- A leitura de comandos e dados **já está feita**; você só implementa os TADs.

Comandos usados nos exemplos do enunciado:
`s` (status de todos), `m idx v th t` (mover), `b idx` (passar bola).
O `vpl04.cpp` deste projeto ainda traz `d` (matriz de distâncias) e `p idx`
(imprime o status do robô mais próximo de `idx`).

---

## 9. Compilar e executar

### 9.1 Compilar (todos os `.cpp` no comando)

```bash
cd ~/GoogleDrive/DataSci_Files/PDS/PDS2/vpl04

g++ -std=c++17 -Wall -Wextra -o prog vpl04.cpp Ponto2D.cpp Robo.cpp
# ou, mais curto (pega todos os .cpp da pasta):
g++ -std=c++17 -Wall -Wextra -o prog *.cpp
```

- **Não** se coloca `.hpp` no comando — eles entram sozinhos via `#include`.
- `-o prog` define o nome do executável. Sem `-o`, o g++ gera `a.out`.
- `-Wall -Wextra` ligam avisos úteis (recomendado); `-std=c++17` fixa o padrão.

### 9.2 Executar (entrada pela stdin)

```bash
# 1) digitando na mão (encerra com Ctrl+D)
./prog

# 2) a partir de um arquivo
./prog < teste1.txt

# 3) via pipe
printf '3\n0.0 0.0 1\n2.0 0.0 0\n4.0 0.0 0\ns\nm 0 1.0 0.0 1.0\ns\n' | ./prog
```

### 9.3 Conferir com a saída esperada

```bash
./prog < teste1.txt > saida.txt
diff saida.txt esperado1.txt && echo "OK: saída idêntica"
```

### 9.4 Resultado esperado (exemplos do enunciado)

Exemplo 1 (`s`, `m 0 1.0 0.0 1.0`, `s`):

```
0	0.00	0.00	1	100.00
1	2.00	0.00	0	100.00
2	4.00	0.00	0	100.00
0	1.00	0.00	1	99.00
1	2.00	0.00	0	100.00
2	4.00	0.00	0	100.00
```

Exemplo 2 (`s`, `b 0`, `s`):

```
0	0.00	0.00	1	100.00
1	2.00	0.00	0	100.00
2	4.00	0.00	0	100.00
0	0.00	0.00	0	100.00
1	2.00	0.00	1	100.00
2	4.00	0.00	0	100.00
```

---

## 10. Checklist do enunciado

- [x] `Ponto2D(double, double)` com coordenadas guardadas internamente.
- [x] Construção sem argumentos possível (`Ponto2D p;`) — argumentos padrão.
- [x] `Ponto2D::calcular_distancia(Ponto2D*)` — distância euclidiana.
- [x] `Robo` com `_energia` (double, sempre 100) e `_com_bola` (bool).
- [x] `Robo(int, Ponto2D, bool)` — `Ponto2D` **por valor** (stack, sem ponteiro).
- [x] `Robo::mover(double, double, double)` — decomposição vetorial + cinemática,
      desconta a distância percorrida da energia.
- [x] `Robo::calcular_distancia(Robo*)` — reaproveita o método de `Ponto2D`.
- [x] `Robo::determinar_robo_mais_proximo(Robo**, int)` — retorna `Robo*`;
      contém a linha `int result = ((1 & 2) ^ (~3 | (4 << 2)));`.
- [x] `Robo::passar_bola(Robo**, int)` — troca `_com_bola`; imprime
      `Estou sem a bola!` quando aplicável.
- [x] `Robo::imprimir_status()` — `id \t x \t y \t com_bola \t energia`.
- [x] Modularização com `.hpp` (declaração) e `.cpp` (implementação).
- [x] Sem `main` própria — a de `vpl04.cpp` é usada.
