# Capítulo 8 — Debugging
> Debug não é sair printando variável.

Teste encontra o erro.  
**Debugging encontra a causa do erro.**

E segundo Myers:

> 95% do debugging é localizar, não corrigir.

---

## ❌ O que todo mundo faz (Brute Force Debugging)

- Prints espalhados pelo código
- Logs infinitos
- Breakpoints aleatórios
- Step-by-step no debugger
- Dump de memória
- "Vou mudar isso aqui pra ver se resolve"

Funciona às vezes? Sim.  
É eficiente? Quase nunca.

Porque isso ignora o principal:

> Você não está pensando. Está caçando.

---

## ✅ As 4 formas corretas de debugar

### 1) Indução (dos sintomas → causa)

Observar padrões no erro.

Pergunta:
> "O que esses sintomas têm em comum?"

**Exemplo real:**

- Só falha com número ímpar de registros
- Valor errado sempre pequeno
- Não depende dos dados

💡 Hipótese: está usando índice do vetor no lugar do valor.

---

### 2) Dedução (das hipóteses → eliminações)

Listar TODAS as causas possíveis e ir eliminando.

**Exemplo real:**

Erro ao interpretar comando `DISPLAY 8000`.

Hipóteses:
- não aceita DISPLAY
- não aceita ponto
- não aceita default
- não aceita hexadecimal

Ao cruzar com outros testes, sobra:

💡 Está interpretando tudo como decimal.

---

### 3) Backtracking (voltar do erro até a origem)

Você olha o valor errado e pensa:

> "Para esse valor sair assim, antes ele tinha que ser X."

E vai subindo mentalmente o fluxo do código.

Extremamente forte em sistemas embarcados.

---

### 4) Debugging com testes "magros"

Depois de suspeitar da causa, você cria testes variando **uma única coisa por vez**.

Esses testes não são para encontrar bug.  
São para **provar a hipótese**.

---

## 🧠 Armadilhas psicológicas (muito reais)

- Ego do programador
- Cansaço mental
- Pressão por corrigir rápido
- Sair mudando código no desespero
- Confiar demais no debugger
- Achar que a primeira correção está certa
- Corrigir sintoma, não causa

---

## ⚠️ Verdades duras do capítulo

- Onde há um bug, quase sempre há outro perto
- Correções geram mais bugs que o código original
- Sempre fazer regressão após corrigir
- Nunca alterar object code, sempre source code

---

## 🧭 Processo mental correto de debug

1. Pensar longe do código
2. Relembrar como deveria funcionar
3. Imaginar onde pode estar errado
4. Criar hipóteses
5. Só depois abrir o código

Se travar:
> Pare, descanse, explique para alguém.

---

# ✅ Checklist de Debug Profissional

- [ ] Eu observei padrões no erro?
- [ ] Listei hipóteses possíveis antes de mexer no código?
- [ ] Eliminei hipóteses com testes magros?
- [ ] Voltei do erro até a origem (backtracking)?
- [ ] Evitei sair alterando código por tentativa?
- [ ] Após corrigir, fiz regressão?
- [ ] Analisei por que o bug nasceu?

---

## 🧩 Exemplos reais

### Embarcado — travamento aleatório

Sintoma:
- Só trava quando buffer enche
- Nunca trava no começo
- Sempre após muitas mensagens

💡 Indução: overflow silencioso.

---

### Backend — cálculo financeiro errado

Sintoma:
- Só quando lista tem número ímpar
- Valor errado é sempre pequeno
- Não depende dos dados

💡 Índice usado no lugar do valor.

---

### Correção errada (clássica)

Trocar:

```c
if (x > 10)
```

por

```c
if (x >= 10)
```

Bug some.

Mas quebra outro fluxo.

➡️ Corrigiu sintoma, não causa.

---

## 🧪 A parte mais profissional: análise pós-bug

Depois de corrigir, perguntar:

- Onde o erro nasceu?
- Quem fez?
- Por quê?
- Como evitar no próximo projeto?
- Por que não foi pego antes?
- Qual teste encontrou ele?

Isso transforma debugging em melhoria de processo.

---

## 💎 Frase mais importante do capítulo

> Think.
