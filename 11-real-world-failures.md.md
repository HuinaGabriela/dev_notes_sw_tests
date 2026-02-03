# Capítulo 11 — O mundo real é instável

O livro fala de:

- Rede cair
- Bateria acabar
- Dispositivo travar
- Interrupções externas
- Variações de hardware

Isso é literalmente:

> IoT / firmware em campo / dispositivo real.

Este capítulo NÃO é sobre “app mobile”.

É sobre sistemas que:

- Dependem de rede instável
- Rodam em hardware limitado
- Sofrem interrupções externas
- Têm múltiplas variações de dispositivo
- Precisam sobreviver a condições ruins do mundo real

Isso descreve perfeitamente firmware conectado.

---

# ✅ Checklist Profissional — Sistemas Embarcados Conectados (IoT / GSM / WiFi / LTE)

_Baseado no Capítulo 11 — The Art of Software Testing_

---

## 🌐 1️⃣ Conectividade (o ponto mais crítico)

- [ ] O que acontece quando a rede cai no meio da operação?
- [ ] O que acontece quando a rede volta?
- [ ] O que acontece com sinal fraco / alta latência?
- [ ] O que acontece se o pacote chega incompleto?
- [ ] O que acontece se o pacote chega duplicado?
- [ ] O que acontece se os pacotes chegam fora de ordem?
- [ ] Existe retry? Ele pode duplicar a operação?

Exemplo conceitual:

```python
def test_packet_loss_during_send():
    device.send(data)
    network.drop()
    network.restore()
    assert device.state_consistent()
```

---

## 🧠 2️⃣ Interrupções externas (muito comum em campo)

Equivalente a “receber ligação enquanto usa app”.

- [ ] Interrupção de energia
- [ ] Watchdog reset
- [ ] Reset manual
- [ ] Interrupção por outra tarefa
- [ ] Interrupção por IRQ inesperada

```python
def test_reset_during_operation():
    device.start_update()
    device.reset()
    assert device.recovers_safely()
```

---

## 💾 3️⃣ Memória baixa / recursos limitados

- [ ] Heap cheio
- [ ] Stack perto do limite
- [ ] Buffer quase estourando
- [ ] Falta de CPU (loop pesado)
- [ ] Falta de RAM durante operação crítica

```python
def test_low_memory_condition():
    device.consume_memory()
    assert device.handles_low_memory()
```

---

## 🔋 4️⃣ Energia / Bateria / Escrita em memória

- [ ] Perde energia no meio da escrita em flash?
- [ ] Liga com bateria fraca?
- [ ] Entra em modo carga durante operação?
- [ ] Sai do modo carga?

```python
def test_power_loss_during_flash_write():
    device.write_flash()
    device.power_off()
    device.power_on()
    assert device.flash_integrity()
```

---

## 📦 5️⃣ Instalação / Atualização (firmware update / OTA)

- [ ] Update interrompido no meio
- [ ] Update com pacote corrompido
- [ ] Versão errada enviada
- [ ] Falha ao aplicar patch
- [ ] Rollback funciona?

```python
def test_interrupted_firmware_update():
    device.start_update()
    device.network_down()
    assert device.rollback_ok()
```

---

## 🧩 6️⃣ Diversidade de dispositivos (o mais ignorado)

Mesmo firmware, hardwares levemente diferentes:

- [ ] Tamanho de memória diferente
- [ ] Versão de chip diferente
- [ ] Clock diferente
- [ ] Periférico diferente
- [ ] Driver levemente diferente

Funciona na placa A. Falha na B.

---

## ⏱️ 7️⃣ Latência e lentidão da rede

- [ ] Timeout muito curto?
- [ ] Timeout muito longo trava o sistema?
- [ ] Sistema trava esperando resposta?

```python
def test_high_latency():
    network.delay(10)
    assert device.does_not_freeze()
```

---

## 🔁 8️⃣ Sincronização de dados (problema clássico)

- [ ] Dados enviados duas vezes?
- [ ] Dados perdidos?
- [ ] Estado local diferente do servidor?
- [ ] Reconexão duplica operação?

```python
def test_duplicate_send_after_reconnect():
    device.send()
    network.drop()
    network.restore()
    assert server.received_once()
```

---

## 🧪 9️⃣ Simulador vs dispositivo real

| Simulador                | Dispositivo real |
|--------------------------|------------------|
| Barato                   | Caro             |
| Automatizado             | Manual           |
| Rápido                   | Lento            |
| Não pega bug de hardware | Pega bug real    |

Use simulador para ~80%.  
Use dispositivo real para validar o restante.

---

## 🧭 10️⃣ Roteiro genérico de teste manual (device real)

Script genérico que serve para qualquer hardware:

1. Iniciar operação principal
2. Derrubar rede
3. Restaurar rede
4. Resetar dispositivo
5. Continuar operação
6. Verificar consistência
7. Desligar energia
8. Ligar novamente
9. Verificar integridade

Sem falar qual botão apertar. Funciona para qualquer dispositivo.

---

## 🏁 Regra de ouro do capítulo

> Seu sistema não falha quando tudo está perfeito.  
> Ele falha quando o mundo real acontece.

Teste o mundo real.
