# Capítulo 5 — Nunca teste o sistema. Teste a função isolada.

Testar função **sem**:
- hardware
- banco
- rede
- RTOS
- dependências

Aqui nasce o que hoje chamamos de **mock**.

---

# 🧪 Module (Unit) Testing

Até aqui o livro ensinou **como criar bons testes**.  
Agora ele ensina **como testar programas grandes de forma organizada**.

> Primeiro testa o módulo isolado. Depois pensa no sistema.

---

## 🎯 O que é Module Testing?

Testar cada função/módulo/classe **isoladamente**.

**Objetivo não é provar que funciona.**  
É provar que **viola a especificação**.

**Por quê?**
1. Menor complexidade
2. Debug fácil (erro está dentro do módulo)
3. Times podem testar em paralelo

---

## 🧠 Como projetar os testes do módulo?

Regra do livro:

1. **White-box** olhando os `IFs` do código
2. **Black-box** usando boundary da especificação

Nenhum dos dois sozinho é suficiente.

---

# 🧩 Exemplo REAL (firmware)

## Especificação do pacote

```c
typedef struct {
    uint16_t id;
    int16_t  temperature;   // décimos de grau
    uint16_t voltage;       // mV
    uint8_t  checksum;
} sensor_pkt_t;
```

Regras:

- id != 0
- temperature: -400 a 1250
- voltage: 3000 a 4200
- checksum = soma dos bytes % 256
- inválido → ERR_INVALID
- válido → OK e converte valores

Função:

```c
int process_sensor_pkt(const sensor_pkt_t* pkt, float* temp, float* volt);
```

---

## 🧩 Implementação

```c
int process_sensor_pkt(const sensor_pkt_t* pkt, float* temp, float* volt)
{
    if (!pkt || !temp || !volt)
        return ERR_INVALID;

    if (pkt->id == 0)
        return ERR_INVALID;

    if (pkt->temperature < -400 || pkt->temperature > 1250)
        return ERR_INVALID;

    if (pkt->voltage < 3000 || pkt->voltage > 4200)
        return ERR_INVALID;

    uint8_t sum = 0;
    const uint8_t* p = (const uint8_t*)pkt;
    for (int i = 0; i < sizeof(sensor_pkt_t) - 1; i++)
        sum += p[i];

    if (sum != pkt->checksum)
        return ERR_INVALID;

    *temp = pkt->temperature / 10.0f;
    *volt = pkt->voltage / 1000.0f;

    return OK;
}
```

---

## 🧠 Passo 1 — White-box (todos os IFs)

Decisões:
- ponteiros nulos
- id == 0
- temp fora
- volt fora
- checksum errado
- caminho feliz

➡️ mínimo 6 testes

---

## 🧠 Passo 2 — Black-box (boundary)

| Campo | Boundary |
|---|---|
| id | 0 / 1 |
| temp | -401, -400, 1250, 1251 |
| volt | 2999, 3000, 4200, 4201 |

---

## 🧪 Driver de teste (C puro)

```c
uint8_t calc_checksum(sensor_pkt_t* pkt)
{
    uint8_t sum = 0;
    uint8_t* p = (uint8_t*)pkt;
    for (int i = 0; i < sizeof(sensor_pkt_t) - 1; i++)
        sum += p[i];
    return sum;
}

void run_test(sensor_pkt_t pkt, int expected_ret)
{
    float t, v;
    int ret = process_sensor_pkt(&pkt, &t, &v);
    assert(ret == expected_ret);
}
```

### Testes

```c
void test_valid_pkt()
{
    sensor_pkt_t pkt = {1, 253, 3300, 0};
    pkt.checksum = calc_checksum(&pkt);
    run_test(pkt, OK);
}

void test_id_zero()
{
    sensor_pkt_t pkt = {0, 253, 3300, 0};
    pkt.checksum = calc_checksum(&pkt);
    run_test(pkt, ERR_INVALID);
}

void test_temp_low()
{
    sensor_pkt_t pkt = {1, -401, 3300, 0};
    pkt.checksum = calc_checksum(&pkt);
    run_test(pkt, ERR_INVALID);
}

void test_voltage_high()
{
    sensor_pkt_t pkt = {1, 253, 4201, 0};
    pkt.checksum = calc_checksum(&pkt);
    run_test(pkt, ERR_INVALID);
}

void test_bad_checksum()
{
    sensor_pkt_t pkt = {1, 253, 3300, 99};
    run_test(pkt, ERR_INVALID);
}
```

---

## ▶️ Execução

```c
int main()
{
    test_valid_pkt();
    test_id_zero();
    test_temp_low();
    test_voltage_high();
    test_bad_checksum();
    printf("All tests passed\n");
}
```

Isso é **unit test raiz**, do jeito que o livro ensina.

---

# 🧠 Como isso vira Unit Test moderno (pytest)

Agora a mesma mentalidade em Python.

Imagine a mesma regra implementada em Python:

```python
def process_sensor_pkt(pkt: dict):
    if pkt is None:
        return "ERR_INVALID"

    if pkt["id"] == 0:
        return "ERR_INVALID"

    if not (-400 <= pkt["temperature"] <= 1250):
        return "ERR_INVALID"

    if not (3000 <= pkt["voltage"] <= 4200):
        return "ERR_INVALID"

    return "OK"
```

## 🧪 pytest

```python
import pytest

@pytest.mark.parametrize("pkt,expected", [
    ({"id":1,"temperature":253,"voltage":3300}, "OK"),
    ({"id":0,"temperature":253,"voltage":3300}, "ERR_INVALID"),
    ({"id":1,"temperature":-401,"voltage":3300}, "ERR_INVALID"),
    ({"id":1,"temperature":253,"voltage":4201}, "ERR_INVALID"),
])
def test_process_sensor(pkt, expected):
    assert process_sensor_pkt(pkt) == expected
```

Mesma lógica:
- white-box (ifs)
- boundary
- casos inválidos
- função isolada

---

# 🧠 Onde entra MOCK (quando tem dependência)

Se a função chamasse hardware:

```python
def read_voltage_from_adc():
    ...
```

No teste:

```python
from unittest.mock import patch

@patch("module.read_voltage_from_adc", return_value=3300)
def test_ok(mock_adc):
    pkt = {"id":1,"temperature":253,"voltage":read_voltage_from_adc()}
    assert process_sensor_pkt(pkt) == "OK"
```

Isso é exatamente o que o capítulo descreve como:
> testar módulo sem depender do resto do sistema

---

# 🧠 Integração de módulos (resumo do capítulo)

Depois dos módulos testados:

- ❌ Big Bang
- ✅ Incremental

Preferência leve do livro:
> Bottom-Up (drivers simples, testes fáceis)

---

# ✅ Checklist mental do Capítulo 5

- Testei todos os `IFs`? (white-box)
- Testei boundaries? (black-box)
- Testei inválidos?
- Testei ponteiros/None?
- Tenho driver/stub/mock?
- Posso rodar isso sem hardware?
- Esses testes viram regressão depois?

---

## 💬 Frase final

> Unit test não é testar função.  
> É escrever o programa de um jeito que **permita testar**.
