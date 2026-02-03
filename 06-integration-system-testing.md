# Capítulo 6 — Módulo → Integração → Sistema → Mundo Real

Este capítulo ensina a maior virada de chave do livro:

> Cada nível de teste encontra um tipo diferente de bug.

Testar não é só testar código.  
É testar a **tradução completa**:

Objetivos → Especificação → Código → Sistema em uso real

---

## 🧠 Mapa mental dos níveis de teste

| Nível | Descobre |
|---|---|
| Module Test | erros de código e lógica |
| Function Test | erros entre código e especificação |
| System Test | erros entre especificação e objetivos reais |
| Acceptance Test | erros entre sistema e necessidade do usuário |

---

## 🎯 O que é System Test de verdade?

System test responde:

> O sistema resolve o problema real para o qual foi criado?

Aqui aparecem erros que passaram por todos os testes anteriores.

---

# 🧪 As categorias de System Test (transformadas em ações práticas)

## ✅ 1. Facility Testing — A função realmente existe no fluxo real?

### Embarcado
- [ ] Modo sleep realmente reduz consumo?
- [ ] Sensores/atuadores funcionam no fluxo normal?
- [ ] Funções implementadas realmente são chamadas?

### Backend
- [ ] Fluxos completos funcionam do início ao fim?
- [ ] Todas as rotas descritas realmente funcionam integradas?

---

## ✅ 2. Volume Testing — Dados demais

### Embarcado
- [ ] Buffer recebe milhares de pacotes sem travar?
- [ ] Flash/EEPROM quase cheia continua estável?

### Backend
- [ ] Funciona com milhões de registros?
- [ ] Paginação e queries continuam performáticas?

---

## ✅ 3. Stress Testing — Tudo ao mesmo tempo

### Embarcado
- [ ] Interrupções + comunicação + gravação simultânea funcionam?
- [ ] Não ocorre race condition?

### Backend
- [ ] Muitas requisições simultâneas não derrubam?
- [ ] Recursos compartilhados não entram em deadlock?

---

## ✅ 4. Configuration Testing — Outros ambientes

### Embarcado
- [ ] Revisões diferentes de hardware?
- [ ] Sensores alternativos?
- [ ] Clocks diferentes?

### Backend
- [ ] SOs diferentes?
- [ ] Docker / VM / físico?

---

## ✅ 5. Storage Testing — Quando o armazenamento acaba

### Embarcado
- [ ] Flash cheia não causa falha?
- [ ] SD corrompido é tratado?

### Backend
- [ ] Disco cheio não derruba?
- [ ] Logs têm controle de tamanho?

---

## ✅ 6. Recovery Testing — Quebrou no meio, volta?

### Embarcado
- [ ] Queda de energia durante gravação é recuperável?
- [ ] Reset durante update não corrompe?

### Backend
- [ ] Reinício no meio da transação mantém consistência?
- [ ] Banco fora do ar é tratado?

---

## ✅ 7. Security Testing — Como eu invado isso?

### Embarcado
- [ ] Pacotes malformados não causam overflow?
- [ ] Entradas inválidas não travam?

### Backend
- [ ] JSON malformado não quebra?
- [ ] SQL injection impossível?
- [ ] Tokens inválidos rejeitados?

---

## ✅ 8. Usability Testing — Usuário faz coisa absurda

### Embarcado
- [ ] Botões simultâneos não travam?
- [ ] Uso fora da ordem funciona?

### Backend
- [ ] Requisições fora de ordem não quebram fluxo?
- [ ] Repetições rápidas não causam erro?

---

## ✅ 9. Performance Testing — Tempo prometido é real?

### Embarcado
- [ ] Tempo de resposta a interrupções aceitável?
- [ ] Wake-up do sleep aceitável?

### Backend
- [ ] Endpoints dentro do tempo esperado?
- [ ] Throughput sob carga?

---

## ✅ 10. Installation Testing — Instalar já é teste

### Embarcado
- [ ] Update de firmware funciona sempre?
- [ ] Primeira inicialização sem falhas?

### Backend
- [ ] Ambiente sobe do zero?
- [ ] Migrations corretas?

---

## ✅ 11. Compatibility / Conversion

### Backend
- [ ] Nova versão lê dados antigos?
- [ ] APIs antigas continuam válidas?

---

## ✅ 12. Procedure Testing — O manual funciona?

### Embarcado
- [ ] Procedimentos do manual funcionam?

### Backend
- [ ] Runbook realmente funciona?

---

# 📋 O que um Test Plan precisa ter (segundo o capítulo)

- [ ] Objetivos
- [ ] Critérios de término
- [ ] Cronograma
- [ ] Responsáveis
- [ ] Biblioteca de testes (regressão)
- [ ] Ferramentas
- [ ] Configuração de hardware/ambiente
- [ ] Plano de integração
- [ ] Rastreamento de erros
- [ ] Plano de debug
- [ ] Plano de regressão

---

## ⛔ Piores critérios para parar de testar

- “Acabou o tempo”
- “Nenhum teste falhou”

---

## ✅ Critérios inteligentes de parada

- Aplicou técnicas formais (boundary, cause-effect, multicondition)
- Meta de erros estimados por tamanho do sistema
- Gráfico erros vs tempo:
  - Ainda encontra muitos → continue
  - Caiu muito → mudar fase

---

## 🧠 Regra de ouro do Capítulo 6

Esses erros:

- Não aparecem no unit test
- Não aparecem no module test

Eles aparecem:
> em produção  
> no cliente  
> depois de meses

Este checklist existe para encontrá-los **antes**.
