# Capítulo 1 — A Mentalidade do Testador (Bug Hunter Mindset)

Esse capítulo não ensina técnica.

O autor mostra que:

> O programador quer provar que o código funciona.  
> O testador quer provar que o código falha.

E que o maior obstáculo para testar bem é o apego emocional ao que você escreveu.

Para testar bem, você precisa abandonar o orgulho de autor e adotar a postura de investigador.

👉 Aqui nasce a mentalidade de caçador de bugs.

---

## 🎯 Ideia central do capítulo

Regra mental obrigatória:

> “Antes de escrever testes, eu penso primeiro em como quebrar isso.”

> “Todo input precisa de casos inválidos, limites e combinações — não só casos felizes.”

---

## ✅ Checklist pessoal antes de dizer “eu testei isso”

### 🔹 Entradas

- [ ] Casos válidos óbvios  
- [ ] Casos inválidos  
- [ ] Zero  
- [ ] Negativos  
- [ ] Limites máximos  
- [ ] Limites mínimos  
- [ ] Ordem diferente dos parâmetros  
- [ ] Ausência de parâmetro  
- [ ] Quantidade errada de parâmetros  
- [ ] Tipo errado (string vs int, etc.)  
- [ ] Entrada vazia / nula  

---

### 🔹 Regras e lógica

- [ ] Combinações que quebram a regra de negócio  
- [ ] Situações que “não deveriam acontecer”  
- [ ] Violações das premissas do código  
- [ ] Estados inválidos do sistema  
- [ ] Transições de estado inesperadas  

---

### 🔹 Qualidade do teste

- [ ] O output esperado está claro  
- [ ] O teste tenta provar que quebra, não só que funciona  
- [ ] Se falhar, fica claro qual regra foi violada  
- [ ] O teste não é redundante  

---

### 🔹 Pergunta final (obrigatória)

- [ ] **Se eu quisesse quebrar isso de propósito, o que eu faria?**

---

## 🧩 O que esse capítulo prepara para os próximos

Esse capítulo é a base de:

- Cap. 4 — Test-Case Design  
- Cap. 5 — Unit Testing  
- Cap. 8 — Debugging  
- Cap. 9 — TDD / Agile  

Sem essa mentalidade, o resto do livro não funciona.

---

## ✅ Conclusão

Esse capítulo não ensina a testar.

Ele ensina **como pensar para conseguir testar bem**.

Se você não internalizar isso, qualquer técnica de teste vira apenas uma formalidade.
