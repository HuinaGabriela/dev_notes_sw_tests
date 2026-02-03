# Capítulo 9 — Testar o tempo todo, não no final

> Testar não é verificar o código.  
> **Testar é moldar o código.**

Este capítulo conecta diretamente com o que hoje chamamos de:

- TDD
- Testes automatizados
- Regressão constante
- Integração contínua
- Agile / XP

---

## 🎯 O problema que o capítulo resolve

O mercado exige:

- Software rápido
- Software com qualidade
- Cliente participando
- Mudanças frequentes de requisito

Processos tradicionais (cascata, RUP clássico) não acompanham isso.

Surge o **Agile**.

---

## 🧠 O Manifesto Ágil (2001)

Valorizamos mais | Do que
---|---
Pessoas e interações | Processos e ferramentas
Software funcionando | Documentação extensa
Colaboração com cliente | Negociação contratual
Responder a mudanças | Seguir plano rígido

> Agile não é método. É filosofia.

---

## 🧵 O que metodologias Agile têm em comum

- Cliente muito envolvido
- Ciclos curtos
- Entregas frequentes
- Mudanças bem-vindas
- Muito teste

Ex: Scrum, XP, FDD, DSDM…

O livro foca em **XP (Extreme Programming)**.

---

## 🚀 Extreme Programming (XP)

Criado por Kent Beck.

Resolve um problema moderno:

> Linguagens rápidas geraram sistemas rápidos e ruins.

XP traz qualidade sem perder velocidade.

### Essência do XP

- Ouvir cliente e time
- Histórias do usuário
- Programação em pares
- **Testar o tempo todo**

---

## 🧪 Extreme Testing (XT)

Modelo de testes do XP.

Tipo | Quem faz | Quando
---|---|---
Unit Test | Desenvolvedor | **Antes** de programar
Acceptance Test | Cliente | Após cada release

> Você escreve os testes ANTES do código.

---

## 🧠 Por que escrever testes antes muda tudo

Se começa pelo código:
> "Depois eu testo"

Se começa pelo teste:
> "O código tem que nascer certo"

Isso força:

- Entender a especificação
- Pensar nos limites
- Pensar nos erros
- Melhor arquitetura
- Baixo acoplamento
- Funções pequenas
- Código testável

> O teste molda a arquitetura.

---

## 📘 Exemplo clássico — verificador de número primo

Especificação:

- Entrada: 0 ≤ n ≤ 1000
- Saída: primo ou não
- Erros: mostrar ajuda

### Casos criados ANTES do código

Entrada | Esperado
---|---
3 | Primo
1000 | Não primo
0 | Não primo
-1 | Erro
1001 | Erro
"a" | Erro
2 inputs | Erro
vazio | Erro

Depois criam o test harness.  
Só então escrevem o código.

---

## 💎 Ideia profunda

No exemplo, nasce um método só porque o teste precisa:

```java
public boolean primeCheck(int num)
```

O teste forçou a arquitetura limpa.

---

## 🔄 Fluxo de um projeto XP

1. Cliente cria User Stories
2. Time estima
3. Cliente prioriza
4. Criam testes
5. Codam para passar
6. Integração diária
7. Cliente testa (aceitação)
8. Release

---

## 🧠 Ligação com Cap. 8 (debug)

Cap. 8 → Como achar bugs  
Cap. 9 → Como evitar que surjam

XP + XT = debugging preventivo.

---

# ✅ Checklist mental de TDD / XT

- [ ] Escrevi o teste antes do código?
- [ ] Pensei nos erros antes da implementação?
- [ ] Pensei nos limites?
- [ ] O design nasceu para ser testável?
- [ ] Os testes são automatizados?
- [ ] Vou reaproveitar isso como regressão?

---

# 🧪 TDD moderno — Exemplo com pytest (Python)

## 1️⃣ Teste nasce primeiro

`test_prime_checker.py`

```python
import pytest
from prime_checker import is_prime

def test_prime_number():
    assert is_prime(3) is True

def test_negative_number():
    with pytest.raises(ValueError):
        is_prime(-1)
```

Arquivo não existe. Perfeito.

---

## 2️⃣ Código mínimo

```python
def is_prime(number):
    return True
```

Roda → falha.

---

## 3️⃣ Implementa para passar

```python
import math

def is_prime(number):
    if number < 0:
        raise ValueError()
    if number <= 1:
        return False

    for i in range(2, int(math.sqrt(number)) + 1):
        if number % i == 0:
            return False
    return True
```

---

## 🧠 O ponto profissional

Você pensou em:

- Erros
- Limites
- Regras

Antes da implementação.

---

# 🧨 Problema real: "meu código depende de banco/API/hardware"

Resposta profissional: **Mock**.

Você testa a regra. Não a tecnologia.

---

## ✅ Exemplo — regra de negócio com banco (mock)

### Teste primeiro

```python
from unittest.mock import Mock
from user_service import UserService
import pytest

def test_should_fail_if_email_exists():
    repo = Mock()
    repo.email_exists.return_value = True

    service = UserService(repo)

    with pytest.raises(Exception):
        service.create_user("a@a.com")
```

### Código mínimo

```python
class UserService:
    def __init__(self, repo):
        self.repo = repo

    def create_user(self, email):
        if self.repo.email_exists(email):
            raise Exception("Email exists")
        self.repo.save(email)
```

Sem banco. Sem API.

---

## 🧪 No mundo embarcado (C)

Função depende de hardware:

```c
int read_temperature_sensor();
```

Você não testa com sensor real.

```c
int fake_sensor() { return 100; }
```

Isso é mock em C.

---

## 💎 Insight profissional

Se é difícil mockar:

> A arquitetura está ruim.

TDD revela arquitetura ruim automaticamente.

---

## 🧭 Fluxo real nas empresas

1. Escreve unit test com mock
2. Implementa regra
3. Teste passa
4. Depois cria integration test separado

Tipo | Testa o quê | Usa mock?
---|---|---
Unit test | Regra de negócio | ✅
Integration test | Banco/API real | ❌
System test | Sistema completo | ❌

Misturar isso é erro clássico.

---

## 💎 Frase final do capítulo

> Testar não é uma fase.  
> Testar é o processo inteiro.
