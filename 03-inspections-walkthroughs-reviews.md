# Capítulo 3 — [O jeito mais barato de encontrar bug não é rodando o código.]

Antes de executar:

ler código

revisar lógica

fazer alguém explicar o que escreveu

Esse capítulo ensina que a maioria dos bugs já está visível no papel.

Para embarcado isso é ouro: pegar bug antes de gravar firmware.


## 🎯 Ideia central
Nem todo teste precisa do computador.

Ler código em grupo encontra **30% a 70%** dos erros de lógica e implementação **antes** de rodar o programa.

> Quanto mais cedo o erro é encontrado, mais barato e mais fácil de corrigir.

---

## 🧠 Mudança de mentalidade

Errado:
> “Programa se testa executando”

Correto:
> “Programa também se testa lendo”

A simples leitura em grupo muda a forma como os erros aparecem.

---

## 👥 Por que funciona?

- O autor é péssimo testando o próprio código
- Outras pessoas enxergam o que o autor não vê
- Ler em voz alta expõe falhas lógicas
- Erros são encontrados **direto na linha do problema** (não só no sintoma)
- Funciona muito bem para **modificações** (onde mais surgem bugs)

---

## 🛠️ Técnicas principais

### 🔍 Code Inspection (Inspeção)

- 4 pessoas: moderador, autor, designer, especialista em testes
- Reunião 90–120 min, sem interrupções
- Autor lê o código linha por linha
- Grupo usa **checklist de erros comuns**
- Objetivo é **achar erros**, não corrigir na hora

### 🚶 Walkthrough

- 3–5 pessoas
- Alguém traz casos de teste em papel
- O grupo “executa o código na cabeça” (play computer)
- Foco em questionar a lógica do autor

### 🪑 Desk Checking

- Pessoa sozinha lendo o código
- Pouco efetivo (falta o efeito do grupo)

### 🧑‍🤝‍🧑 Peer Review (avaliação entre pares)

- Não é para achar bug
- É para melhorar qualidade, clareza e manutenibilidade

---

## 📋 Tipos de erros mais encontrados (checklist mental)

Durante a leitura, procurar principalmente:

- Variáveis não inicializadas
- Índices fora do limite (off-by-one)
- Ponteiros/referências inválidas
- Tipos incompatíveis
- Divisão por zero
- Overflow / underflow
- Comparações lógicas erradas (`and/or`, precedência)
- Loops que não terminam ou não executam
- Parâmetros trocados entre funções
- Problemas de I/O (arquivo não aberto, EOF, etc.)
- Uso incorreto de variáveis globais
- Falta de validação de entrada

---

## 💰 Benefícios econômicos

Encontrar erro aqui é muito mais barato do que:
- Durante execução
- Em teste de sistema
- Em produção

E programadores cometem **mais erros ao corrigir bugs sob pressão** do que quando corrigem erros achados cedo.

---

## 💻 Aplicação direta (embarcado / back-end)

Essas técnicas são **ouro** para:

- Revisão de drivers e firmware crítico
- Revisão de protocolos e parsing
- Revisão de regras de negócio complexas
- Revisão de refactors e manutenções
- Revisão antes de iniciar testes automatizados

---

## ✅ Checklist mental antes de rodar o código

- Outra pessoa já leu isso?
- Eu já li isso em voz alta explicando a lógica?
- Já passamos um checklist de erros comuns?
- Já “executei no papel” alguns cenários?

Se não fez isso, você ainda não começou a testar.

---

## 🧠 Frases-chave

> Ler código em grupo é uma das formas mais eficientes de achar bugs.  
> Testar não começa executando, começa lendo.

## ################################################

Bug → O que a inspeção enxerga → Por que é perigoso → Como corrigir



💎 Modelo ideal (pra todos os exemplos)
### 🧪 Exemplo — Variável não inicializada


#### Código
```c
int total;
for (int i = 0; i < n; i++) {
    total += valores[i];
}
return total;


👀 O que a inspeção enxerga

A variável total nunca foi inicializada.

⚠️ Por que é perigoso

Pode assumir lixo de memória → resultado imprevisível.

✅ Como corrigir

int total = 0;

##
################################################

🧪 Exemplo 2 — Off-by-one / estouro de buffer (Control Flow)
Código

for (int i = 0; i <= 10; i++) {
    buffer[i] = 0;
}

👀 O que a inspeção enxerga

O laço executa 11 vezes. Se o buffer tem 10 posições (0–9), há acesso inválido.

⚠️ Por que é perigoso

Estouro de memória. Em embarcado pode travar o sistema.

✅ Como corrigir

for (int i = 0; i < 10; i++) {
    buffer[i] = 0;
}

#################################################

🧪 Exemplo 3 — Divisão por zero escondida (Computation)
Código

if (x == 0 && (y / x) > 10) {
    ...
}
👀 O que a inspeção enxerga

Dependência do comportamento de short-circuit do compilador.

⚠️ Por que é perigoso

Pode ocorrer divisão por zero dependendo do compilador.

✅ Como corrigir
if (x != 0 && (y / x) > 10) {
    ...
}
##############################################

🧪 Exemplo 4 — Comparação lógica errada (Comparison)
Código

if (2 < x < 10) {
    ...
}
👀 O que a inspeção enxerga

Expressão lógica inválida para C/Java.

⚠️ Por que é perigoso

A condição não funciona como esperado.

✅ Como corrigir
if (x > 2 && x < 10) {
    ...
}
###############################################

🧪 Exemplo 5 — Parâmetros trocados (Interface)
Código
sendTemperature(pressure, temperature);
👀 O que a inspeção enxerga

Ordem dos parâmetros invertida.

⚠️ Por que é perigoso

Erro silencioso, difícil de detectar por testes superficiais.

✅ Como corrigir
sendTemperature(temperature, pressure);

################################################

🧪 Exemplo 6 — Loop que nunca executa (Control Flow)
Código

for (int i = start; i > end; i++) {
    process(i);
}
👀 O que a inspeção enxerga

Dependendo dos valores, o loop nunca executa.

⚠️ Por que é perigoso

Parte do código nunca é exercitada.

✅ Como corrigir
for (int i = start; i < end; i++) {
    process(i);
}

##############################################
🧪 Exemplo 7 — Falta de validação de I/O (Input/Output)
Código
read(fd, buffer, size);
process(buffer);

👀 O que a inspeção enxerga

Não há verificação do retorno da função read.

⚠️ Por que é perigoso

Pode processar dados incompletos ou inválidos.

✅ Como corrigir

int bytes = read(fd, buffer, size);
if (bytes <= 0) {
    // tratar erro
}
process(buffer);

#############################################

🧪 Exemplo 8 — Retorno de ponteiro inválido (Data Reference)
Código

char* getBuffer() {
    char temp[100];
    return temp;
}

👀 O que a inspeção enxerga

Retorno de memória alocada na stack.

⚠️ Por que é perigoso

Após sair da função, a memória deixa de existir.

✅ Como corrigir

char* getBuffer() {
    static char temp[100];
    return temp;
}
ou
char* getBuffer() {
    char* temp = malloc(100);
    return temp;
}

Agora temp não vai mais para a stack.

Ele vai para a área estática do programa (segmento .data / .bss).

Isso significa:

Ele é alocado uma única vez

Ele existe do início ao fim do programa

Ele não é destruído ao sair da função

Sempre ocupa o mesmo endereço de memória

##############################################

# ⚠️ Armadilha Clássica em C — `static` não resolve tudo

Este exemplo mostra um erro muito comum ao tentar corrigir o retorno de ponteiros para memória local usando `static`.

---

## ❌ Código original (bug grave)

```c
char* getBuffer() {
    char temp[100];
    return temp;   // ERRO: retorna memória da stack
}
👀 O que a inspeção enxerga

temp é alocado na stack e deixa de existir quando a função termina.

⚠️ Por que é perigoso

O ponteiro retornado aponta para memória inválida.

🟡 Tentativa de correção com static

char* getBuffer() {
    static char temp[100];
    return temp;
}


✅ O que isso resolve

A memória deixa de ser stack

Passa a existir durante toda a execução do programa

O ponteiro não fica inválido

❗ O que isso NÃO resolve
char* a = getBuffer();
char* b = getBuffer();

Agora a e b apontam para o mesmo buffer.

┌───────────────────┐
│ temp[100]         │
└───────────────────┘
        ↑        ↑
        a        b

💥 Bug silencioso
strcpy(a, "HELLO");
strcpy(b, "WORLD");

printf("%s\n", a);  // imprime WORLD

O segundo uso sobrescreve o primeiro.

🧠 Lição de inspeção (o mais importante)

Quando você vê:

return static_buffer;

Pergunta obrigatória:

Essa função pode ser chamada duas vezes antes do uso do resultado?

Se sim → bug esperando acontecer.

✅ Forma correta #1 — Chamador fornece o buffer (padrão ouro em embarcado)

void getBuffer(char* out) {
    strcpy(out, "data");
}

char a[100], b[100];
getBuffer(a);
getBuffer(b);

Vantagens

Sem heap

Sem conflito

Totalmente previsível

####  OU #####

✅ Forma correta #2 — Usando malloc

char* getBuffer() {
    char* temp = malloc(100);
    return temp;
}

Cada chamada tem sua própria memória.

⚠️ Requer free.

### ou ####

🟠 Forma alternativa — Múltiplos buffers estáticos (legado/controlado)

char* getBuffer() {
    static char buffers[2][100];
    static int idx = 0;
    idx = (idx + 1) % 2;
    return buffers[idx];
}
Usado quando:

Não pode usar heap

Precisa evitar conflito simples

🧩 Conceito-chave

static resolve tempo de vida da memória.
Ele não resolve compartilhamento da memória.

🧪 Regra mental para inspeção

Sempre que encontrar static retornado por função:

Pode haver concorrência?

Pode haver múltiplas chamadas seguidas?

O chamador guarda o ponteiro?

Se qualquer resposta for sim, investigue.


########################################################################################################################
            Guia Mestre de Bugs Recorrentes
########################################################################################################################


Quando você olha código, você passa a perguntar automaticamente:

Onde pode estourar limite?

Onde pode usar lixo de memória?

Onde uma condição pode estar sempre verdadeira?

Onde um ponteiro pode ser inválido?

Onde um dado externo não foi validado?

####################################################

# 🧠 Guia Mestre de Bugs Recorrentes (para inspeção de código)

Use isto como checklist mental ao revisar qualquer função.

---

## 🔢 1. Off-by-one / limites errados

- `<=` no lugar de `<`
- `>=` no lugar de `>`
- Esqueceu primeiro ou último índice
- Loop passa do tamanho do array

---

## 📦 2. Acesso fora do array (buffer overflow)

- Índice vindo de input externo
- Falta de validação de tamanho
- Copiar string sem limite (`strcpy`, `sprintf`)

---

## 🧮 3. Variável não inicializada

- Variável local usada antes de setar
- Acumuladores sem valor inicial
- Estruturas parcialmente inicializadas

---

## ⚖️ 4. `=` no lugar de `==`

Clássico invisível.

---

## 🧩 5. Condição lógica sempre verdadeira ou sempre falsa

Ex:
```c
if (x > 0 || x < 10)


🧱 6. Esquecendo casos de fronteira (boundary)

zero

negativo

máximo

mínimo

exatamente o limite

🧵 7. Uso de ponteiro sem validar NULL

Ordem errada:

ptr->x && ptr != NULL

💾 8. Uso de memória após free / memória inválida

Retornar ponteiro de variável local

Usar buffer já liberado

Duplo free

🔁 9. Função que depende de estado interno escondido (static)

Segunda chamada retorna diferente da primeira

Não é reentrante

Não é thread-safe

📂 10. Falta de checar retorno de função

malloc

fopen

read

write

recv

send

🧪 11. Supor que input sempre é válido

String vazia

Tipo errado

Valor fora do esperado

⏱️ 12. Problemas de concorrência (embarcardo ama isso)

Variável global sem proteção

ISR mexendo na mesma variável

Falta de volatile

Condição de corrida

🔄 13. Estado não resetado entre chamadas

Buffer reaproveitado

Flags que não voltam ao padrão

🧮 14. Erro de precedência de operadores
if (a & b == 0)

📉 15. Conversão de tipo perigosa (cast implícito)

int → char

signed ↔ unsigned

Overflow silencioso

🧾 16. Suposições erradas sobre tamanho de tipos

int não tem tamanho fixo

Dependência de arquitetura

🧯 17. Falta de tratamento de erro

Código continua mesmo após falha.

🧠 18. Código faz o que não deveria fazer (efeito colateral)

Sobrescreve dado indevido

Altera estado global sem necessidade

🔍 19. Caminho lógico faltando (missing path)

if sem else quando precisava

switch sem default

🧨 20. Erros que só aparecem com valores específicos

Comparações sem abs

Divisão por zero em casos raros

Overflow matemático



