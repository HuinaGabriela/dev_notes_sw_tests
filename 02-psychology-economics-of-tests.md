# Capítulo 2 — A Psicologia e a Economia dos Testes

Esse capítulo explica **por que testamos mal**, mesmo sabendo testar.

O problema não é técnico.

É humano. E financeiro.

- Ego do programador
- Pressão por prazo
- Custo de testar vs custo do bug
- Ilusão de que “já testamos o suficiente”

Você entende que:

> Bug em produção não é acidente.  
> É uma decisão tomada durante o desenvolvimento.

---

## 🎯 Ideia central do capítulo

> Testar é executar o software com a intenção de encontrar erros.

Não é provar que funciona.

Se seu teste não encontra erro, pode ser que o teste seja fraco.

---

## 🧠 Mudança obrigatória de mentalidade

Errado:

> “Vou testar para ver se está funcionando.”

Correto:

> “Vou testar para fazer isso quebrar.”

---

## 💰 A limitação real dos testes

Você nunca vai conseguir testar tudo.

- Black-box → combinações de entradas são infinitas
- White-box → caminhos do código são infinitos

O objetivo **não é provar ausência de bugs**.

O objetivo é:

> Maximizar a probabilidade de encontrar erros.

---

## ⚠️ Erros clássicos que esse capítulo denuncia

- Testar só casos válidos
- Não definir claramente o output esperado
- Parar de testar depois que já achou alguns bugs
- Não guardar testes para regressão
- Testar tentando confirmar que está certo

---

## 🧩 Princípios práticos que saem daqui

- Todo teste precisa de output esperado
- Entradas inválidas são mais valiosas que válidas
- Testar o que *não deveria acontecer*
- Onde já teve bug, vai ter mais (error clustering)
- Testes precisam virar regressão
- Assumir sempre que existem erros

---

## 💻 Aplicação direta (embarcado / back-end)

- Inputs inválidos de protocolo / API
- Estados de sistema que “nunca deveriam acontecer”
- Testes reaproveitados após correções
- Foco redobrado nas áreas historicamente problemáticas

---

## ✅ Checklist mental antes de testar

- [ ] Estou tentando provar que quebra?
- [ ] Defini claramente o resultado esperado?
- [ ] Testei entradas inválidas?
- [ ] Vou reaproveitar esse teste depois (regressão)?
- [ ] Testei mais onde já deu problema antes?

---

## 🧠 Frases-chave do capítulo

> Teste bom encontra erro.  
> Não é possível provar que não há bugs.  
> Testar bem é uma decisão consciente.
