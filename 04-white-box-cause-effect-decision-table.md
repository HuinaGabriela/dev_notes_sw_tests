# Capítulo 4 — Como pensar casos de teste que realmente encontram bug

Esse capítulo vira seu **checklist pessoal**.

Aqui você aprende a gerar casos de teste **de forma sistemática**, sem esquecer combinações importantes.

Testar:
- inválido
- limites
- ordem errada
- ausência
- tipo errado

---

# 🧩 Cause-Effect Graphing → Decision Table → Test Cases

Quando a especificação tem **muitas combinações**, testar no “achismo” faz você esquecer casos.

O método:

1. Traduz a especificação para lógica booleana (grafo)
2. Aplica restrições (o que é impossível)
3. Converte em tabela de decisão
4. Extrai casos de teste

---

## 🎯 Ideia central

> Definir o que deve acontecer **antes** de executar o teste.

---

## 🔣 Símbolos do Cause-Effect Graph

| Função | Significado |
|---|---|
| Identidade | se a=1 → b=1 |
| NOT | se a=1 → b=0 |
| OR | qualquer 1 → saída 1 |
| AND | todos 1 → saída 1 |

---

## ⛔ Restrições (constraints)

| Símbolo | Regra |
|---|---|
| E | no máximo um pode ser 1 |
| I | pelo menos um deve ser 1 |
| O | exatamente um deve ser 1 |
| R | se a=1 então b=1 |
| M | se A ocorre, B vira 0 |

---

## ⚠️ Observação crucial do livro

Cause-Effect **não cobre bem boundary**.

Boundary Value Analysis deve ser feito **separado** e depois **misturado** aos testes.

---

## 🧭 Estratégia final recomendada

Ordem ideal para projetar testes:

1. Cause-Effect Graph
2. Boundary Value
3. Equivalence Classes (válidos e inválidos)
4. Error Guessing
5. White-box (caminhos do código)

---

# 🧪 Exemplo REAL de firmware

## API

```c
int read_memory(uint32_t addr, uint32_t size, bool safe_mode);
```

## 📜 Especificação

- addr: 0x0000–0x7FFF
- size > 0
- addr + size ≤ 0x8000
- se safe_mode=true → size ≤ 128
- inválido → ERR_PARAM
- ultrapassa memória → ERR_RANGE
- válido → SUCCESS

---

## 🧠 Passo 1 — CAUSAS

| Nº | Causa |
|---|---|
| C1 | addr dentro do range |
| C2 | size > 0 |
| C3 | addr + size ≤ 0x8000 |
| C4 | safe_mode = true |
| C5 | size ≤ 128 |

---

## 🎯 Passo 2 — EFEITOS

| Nº | Efeito |
|---|---|
| E1 | SUCCESS |
| E2 | ERR_PARAM |
| E3 | ERR_RANGE |

---

## 🔗 Passo 3 — Regras lógicas

- Se C1=0 → ERR_PARAM
- Se C2=0 → ERR_PARAM
- Se C3=0 → ERR_RANGE
- Se C4=1 e C5=0 → ERR_PARAM
- Senão → SUCCESS

---

## 🧮 Passo 4 — Decision Table

| Teste | C1 | C2 | C3 | C4 | C5 | Resultado |
|---|---|---|---|---|---|---|
| T1 | 0 | 1 | 1 | 0 | 1 | ERR_PARAM |
| T2 | 1 | 0 | 1 | 0 | 1 | ERR_PARAM |
| T3 | 1 | 1 | 0 | 0 | 1 | ERR_RANGE |
| T4 | 1 | 1 | 1 | 1 | 0 | ERR_PARAM |
| T5 | 1 | 1 | 1 | 0 | 1 | SUCCESS |

Esses 5 testes cobrem **todas as regras**.

---

## 🧪 Passo 5 — Testes reais

| Teste | Parâmetros | Esperado |
|---|---|---|
| T1 | addr=0x9000, size=10, safe=false | ERR_PARAM |
| T2 | addr=0x1000, size=0, safe=false | ERR_PARAM |
| T3 | addr=0x7FF0, size=32, safe=false | ERR_RANGE |
| T4 | addr=0x1000, size=200, safe=true | ERR_PARAM |
| T5 | addr=0x1000, size=200, safe=false | SUCCESS |

---

## 📏 Passo 6 — Boundary misturado

Troque valores:

- addr = 0x0000
- addr = 0x7FFF
- addr = 0x8000 ❌
- size = 1
- size = 128
- size = 129 ❌

Sem criar novos testes — só fortalecendo.

---

## 🐛 Passo 7 — Error Guessing

Adicionar:

| Caso extra | Por quê |
|---|---|
| addr muito grande | overflow clássico |
| size muito grande | overflow na soma |
| safe_mode lixo de memória | clássico embarcado |

---

## 🧠 O que você aprendeu (essência do capítulo)

Você aplicou no mundo real:

- Cause-Effect Graph
- Decision Table
- Boundary Value
- Error Guessing

E gerou **poucos testes**, extremamente poderosos.

---

## 🧠 Frase final

> Nenhuma técnica sozinha é suficiente.  
> A combinação gera testes pequenos, mas muito inteligentes.
