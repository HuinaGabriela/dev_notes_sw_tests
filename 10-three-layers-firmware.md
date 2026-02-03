# Capítulo 10 — Sistema em 3 camadas (que não é só web)

O livro fala em:

- Presentation layer
- Business layer
- Data layer

Isso NÃO é conceito de web.

Isso é conceito de **arquitetura testável**.

---

## 🧩 As 3 camadas no mundo embarcado

Livro | Embarcado
---|---
Presentation layer | GPIO, UART, SPI, I2C, CAN, ADC, IRQ
Business layer | Máquina de estados, regras, controle, lógica
Data layer | Drivers, buffers, memória, protocolo, flash/EEPROM

É a mesma teoria. Só muda o palco.

---

## 🎯 O ensinamento central do capítulo

> ❌ Não teste o firmware inteiro na placa  
> ✅ Teste por camadas, isoladamente

Porque **cada camada revela um tipo diferente de bug**.

---

# ✅ O que você realmente testa no firmware

## 1️⃣ Teste de I/O (Presentation Layer)

Aqui você testa o **contato com o mundo externo**.

- [ ] GPIO muda quando deveria?
- [ ] Interrupção dispara?
- [ ] UART recebe lixo?
- [ ] SPI recebe pacote truncado?
- [ ] ADC retorna valor fora do range?

Esses erros **não aparecem** quando você testa a lógica.

---

## 2️⃣ Teste da lógica (Business Layer — TDD puro)

Aqui está a parte mais importante: **sem hardware**.

- [ ] Estado muda corretamente?
- [ ] Timer expira como esperado?
- [ ] Condição de erro leva ao estado seguro?
- [ ] Sequência errada de eventos quebra?
- [ ] Ordem inesperada de entradas é tratada?

Aqui você testa **somente regras**.

---

## 3️⃣ Teste de drivers / memória / protocolo (Data Layer)

Aqui você testa os **limites físicos do sistema**.

- [ ] Buffer overflow
- [ ] Ponteiro inválido
- [ ] Perda de pacote
- [ ] Escrita na flash falha
- [ ] Leitura parcial
- [ ] Dados corrompidos

Esses erros não aparecem na lógica nem no I/O.

---

## 💣 Bug clássico real de firmware

```c
void processPacket(uint8_t* data) {
    if (data[0] == 0xAA) {
        startMotor();
    }
}
```

Na placa funciona.  
Em campo trava.

Por quê?

Ninguém testou:

- Pacote com 1 byte
- Pacote NULL
- Pacote lixo
- Pacote atrasado
- Pacote fora de ordem

Isso é exatamente o Capítulo 10.

---

## ✅ Como isso vira teste unitário (sem hardware)

Você testa a **lógica**, não o hardware.

Exemplo conceitual em Python:

```python
def test_packet_too_small():
    assert not process_packet(b'\xAA')

def test_null_packet():
    assert not process_packet(None)

def test_wrong_header():
    assert not process_packet(b'\x00\xFF\xFF')
```

O hardware não participa.

---

## 🧠 A virada mental do capítulo

A maioria testa assim:

> “Grava na placa e vê se funciona”

O livro ensina:

> Teste I/O separado  
> Teste lógica separado  
> Teste drivers separado

Porque firmware testável **não nasce por acaso**.  
Ele nasce dividido em camadas.

---

## 🧭 Checklist prático (firmware)

- [ ] Nunca testar firmware inteiro de uma vez
- [ ] Separar I/O, lógica e driver
- [ ] Testar a lógica sem hardware
- [ ] Simular entradas erradas
- [ ] Testar ordem errada de eventos
- [ ] Testar perda de dados
- [ ] Testar buffers e memória
- [ ] Testar tempo (timers / atraso)
- [ ] Testar pacotes incompletos e corrompidos

---

## 💎 Frase que resume o capítulo

> Firmware testável é firmware dividido em camadas.
