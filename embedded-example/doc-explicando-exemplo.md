---

## 🔗 Exemplo prático completo deste capítulo

🧠 O cenário (mundo real)

Imagine um dispositivo embarcado (uma placa) ligado a outro equipamento por UART.

Esse outro equipamento manda comandos assim, em bytes crus:

[0xAA] [CMD] [VALUE] [CHECKSUM]


Exemplo real que chega pelo fio:

0xAA  0x01  0x05  0xB0


Isso não chega “organizado”.
Chega um byte por vez, muito rápido.


📦 O que cada byte significa

| Byte     | Nome    | Significado                    |
| -------- | ------- | ------------------------------ |
| 0xAA     | HEADER  | Marca o início de um pacote    |
| CMD      | Comando | O que o dispositivo deve fazer |
| VALUE    | Valor   | Parâmetro do comando           |
| CHECKSUM | Soma    | Validação do pacote            |


Regras do sistema:
Header tem que ser 0xAA

Checksum = soma dos 3 primeiros bytes % 256

CMD 0x01 → ligar motor

CMD 0x02 → desligar motor

Se qualquer coisa estiver errada → ignora

⚡ O que acontece na vida real (UART de verdade)

A UART não entrega isso:

“Aqui está um pacote completo”

Ela entrega assim:

chega 0xAA
chega 0x01
chega 0x05
chega 0xB0


Um por vez. Interrupção por interrupção.

Então alguém precisa:

Juntar esses bytes e entender quando virou um pacote.

Esse alguém é o uart_handler.

🧩 As 3 partes do exemplo (as 3 camadas do capítulo)
1️⃣ uart_handler (Presentation Layer)

Responsável por:

Receber byte por byte

Montar um pacote quando tiver 4 bytes

Entregar o pacote pronto para a lógica

Ele não sabe o que é ligar motor.
Só sabe juntar bytes.

2️⃣ packet_processor (Business Layer) ⭐ a parte mais importante

Responsável por:

Verificar header

Verificar checksum

Entender o comando

Decidir o que fazer

Ele não sabe que veio da UART.

Ele só recebe:

uint8_t packet[4]


E decide.

3️⃣ motor_driver (Data Layer)

Responsável por:

Ligar motor

Desligar motor

Nada mais.

🔄 O fluxo completo (vida real)
Fio UART → uart_handler → packet_processor → motor_driver

🧪 Agora vem a parte GENIAL: o teste

Para testar a regra de negócio, você NÃO usa UART.
NÃO usa placa.
NÃO usa motor.

Você testa só isso aqui:

packet_processor(packet)


Passando pacotes falsos.

✅ Teste 1 — pacote correto para ligar motor

Você inventa:

[0xAA] [0x01] [0x05] [checksum certo]


E verifica:

O motor foi mandado ligar?

❌ Teste 2 — header errado
[0x00] [0x01] [0x05] [...]


Verifica:

Nada aconteceu.

❌ Teste 3 — checksum errado
[0xAA] [0x01] [0x05] [0x00]


Verifica:

Nada aconteceu.

❌ Teste 4 — comando inválido
[0xAA] [0x99] [0x05] [...]


Verifica:

Nada aconteceu.

🤯 O que é mágico aqui

Você está testando 100% da inteligência do sistema:

Sem UART.
Sem hardware.
Sem motor.
Sem interrupção.

Só lógica.

Isso é exatamente o Capítulo 10 vivo.

💡 Por que isso é importante para quem é leigo

Porque normalmente a pessoa acha que testar firmware é:

“Gravar na placa e ver se funciona”

Aqui ela entende que:

Firmware bem feito pode ser testado como um programa normal.

