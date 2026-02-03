# Capítulo 7 — Usability (User) Testing
> O usuário quebra o que você nunca imaginou.

Usability Test **não é sobre UI bonita**.

É sobre:

- mensagens ruins
- fluxo confuso
- comportamento inesperado
- erro humano
- falta de feedback

Para embarcado e backend isso vira:

> operador, técnico, usuário de campo usando o sistema “errado” — e o sistema não sabendo lidar com isso.

Usability Test é um **System Test do fator humano**.

É black-box total.

---

## 🎯 Objetivo do Usability Test

Descobrir problemas que **nunca aparecem** em:

- unit test
- module test
- code review
- system test técnico

Descobrir:

- Interface confusa
- Fluxos ilógicos
- Mensagens inúteis
- Falta de feedback ao usuário
- Operações difíceis de repetir
- Design que induz erro humano
- Software que funciona, mas é horrível de usar

---

# ✅ Checklist de Usabilidade (Embarcado e Backend)

## 1. A interface combina com o tipo de usuário?

- [ ] O sistema exige conhecimento técnico que o usuário não tem?
- [ ] Os termos usados fazem sentido para quem usa?

**Embarcado:** mensagens no display são claras?  
**Backend:** logs e respostas da API fazem sentido para quem consome?

---

## 2. As mensagens são úteis?

- [ ] Existe mensagem do tipo: "Erro desconhecido"?
- [ ] Mensagens ajudam a resolver o problema?

**Ruim:** `ERROR CODE 0x802A`  
**Bom:** `Falha ao gravar na memória — espaço insuficiente`

---

## 3. Existe consistência na interface?

- [ ] Botões fazem sempre a mesma coisa?
- [ ] Comandos seguem padrão?
- [ ] Menus seguem lógica?

Bug clássico: cada tela funciona de um jeito.

---

## 4. O sistema confirma que recebeu a ação do usuário?

- [ ] Botão dá feedback?
- [ ] Ação muda algo visível?
- [ ] Operações demoradas mostram que estão processando?

**Backend:** endpoint demora e não retorna nada.  
**Embarcado:** usuário aperta botão e nada acontece por segundos.

Usuário acha que travou.

---

## 5. É fácil navegar e voltar?

- [ ] Usuário sabe voltar ao menu principal?
- [ ] Fluxos são claros?

---

## 6. O design induz o usuário ao erro?

- [ ] Usuário erra muito ao usar?
- [ ] Erros quebram o sistema ou são recuperáveis?

---

## 7. O usuário aprende a usar mais rápido com o tempo?

- [ ] Operações são fáceis de repetir?
- [ ] Sistema ajuda a memória do usuário?

---

## 8. O usuário se sente confiante ou estressado?

Pergunta real após o teste:

> “Você usaria isso no seu dia a dia?”

---

## 9. O sistema cumpre o que promete do ponto de vista do usuário?

Não do programador.  
Do usuário.

---

# 🧪 Como executar o Usability Test na prática

Você **não pede opinião**.

Você dá **tarefas reais**.

Exemplo (backend de clientes):

Peça para o usuário:

- [ ] Criar um cliente
- [ ] Editar cliente
- [ ] Deletar cliente
- [ ] Gerar relatório
- [ ] Exportar dados
- [ ] Importar dados
- [ ] Repetir uma operação feita antes

E observe.

---

## 👀 O que observar durante o teste

- Onde ele para e pensa
- Onde ele se perde
- Onde ele clica errado
- Onde ele espera algo que não acontece
- Onde ele demonstra frustração

---

## 🎤 Técnica poderosa — Think-Aloud

Peça para o usuário falar em voz alta o que está pensando:

> "Estou procurando onde cria cliente..."  
> "Não sei o que esse botão faz..."  
> "Isso aqui parece errado..."

Isso revela problemas invisíveis ao desenvolvedor.

---

## 🧍 Quem escolher para testar?

### Sistema específico (industrial, firmware técnico)
➡️ Usuários experientes da área

### Sistema geral (app, site, backend comum)
➡️ Pessoas aleatórias (hallway testing)

Usuário leigo quebra coisas que especialista nunca quebra.

---

## 🔢 Quantos usuários?

Regra prática (Nielsen):

> 5 usuários encontram ~83% dos problemas.

Mais que isso traz pouco ganho.

Para sistemas críticos:
➡️ usar mais.

---

## 📊 Como coletar dados

- Observação direta
- Gravação de vídeo
- Think-aloud
- Questionário após teste
- Medir tempo das tarefas
- Contar erros do usuário

---

## 📝 Perguntas pós-teste (escala 1 a 5)

- [ ] O menu foi fácil de navegar
- [ ] Foi fácil encontrar o que eu queria
- [ ] As mensagens me ajudaram
- [ ] Consegui repetir tarefas facilmente
- [ ] O sistema dá pouco feedback das ações
- [ ] Foi mais difícil que outros sistemas parecidos

---

## 🚨 Sinal de alerta do capítulo

Se **ninguém encontra problema nenhum**:

> O teste está errado  
> Ou os usuários são poucos demais

É impossível um sistema real não ter problemas de usabilidade.

---

## 🧠 Verdade absoluta

> O desenvolvedor nunca encontra esses problemas.  
> O usuário encontra em 5 minutos.

---

# 🧩 Exemplos reais

### Embarcado

Usuário precisa segurar botão 10s para reset.  
Ele segura 5s, solta, tenta de novo, acha que travou.

➡️ Problema de usabilidade, não de código.

---

### Backend

Fluxo:
Menu → Configurações → Sistema → Avançado → Exportar

Usuário nunca acha.

➡️ Funciona, mas é inutilizável.

---

### Firmware com display

Mensagem:
`ERR 23`

Usuário não sabe o que fazer.

---

## 🛑 Quando parar o Usability Test?

Quando:

- Usuários param de se perder
- Usuários cometem poucos erros
- Conseguem repetir tarefas facilmente
- Entendem as mensagens
- Dizem que usariam o sistema

---

## 💎 Frase mais importante do capítulo

> O software pode estar correto tecnicamente e mesmo assim ser um fracasso total para o usuário.
