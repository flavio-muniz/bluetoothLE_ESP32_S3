# ESP32-S3 BLE UART (NimBLE)  

Conectar **ESP32-S3-WROOM-1 N16R8** via **Bluetooth Low Energy (BLE) UART** com dispositivos iOS e Android.  

Para Android, recomendo o app **Bluetooth Serial**, e para iOS, recomendo **BLE Serial nRF52**.  

---

## Descrição

Este projeto implementa uma **comunicação UART via BLE** usando a biblioteca **NimBLE**.  
Ele permite que dispositivos móveis enviem comandos para o ESP32-S3 e recebam respostas de forma simples.  

O ESP32-S3 está configurado para **máxima potência BLE (+9 dBm)**, melhorando o alcance da comunicação.  

---

## Funcionalidades

- Inicializa o ESP32-S3 como **periférico BLE**.
- Cria um serviço UART com **UUIDs compatíveis com Nordic UART Service (NUS)**:
  - TX (notify) – leitura de dados pelo celular
  - RX (write) – escrita de dados pelo celular
- Recebe comandos do celular e envia respostas automáticas:
  - `"1"` → envia `"Ola"`
  - `"2"` → envia `"Hello, from ESP32-S3! mandando com +9 dBm"`
  - Qualquer outro comando → envia `"Comando desconhecido"`
- Compatível com **iOS e Android**.

---

## Hardware Necessário

- ESP32-S3-WROOM-1 N16R8
- Cabo USB para programação
- Dispositivo Android ou iOS com app de terminal BLE  

---

## Software Necessário

- **PlatformIO** / VSCode
- Biblioteca **NimBLE-Arduino** (PlatformIO/Arduino)
- App BLE UART:
  - Android: [Bluetooth Serial](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal)
  - iOS: [BLE Serial nRF52](https://apps.apple.com/br/app/bleserial-nrf/id1632235163)

> **Observação:** No app Android, vá em **Settings > Send > New Line > None** para que os comandos sejam enviados corretamente.

---

## Bibliotecas

Para adicionar a biblioteca no **PlatformIO**, basta abrir a parte de bibliotecas e procurar por **NimBLE-Arduino**.  

No arquivo `platformio.ini`, você verá algo como:

```ini
lib_deps =  h2zero/NimBLE-Arduino@^2.3.6
```
---

## Configuração

1. Abra o projeto no VSCode/PlatformIO.
2. Adicione a biblioteca
3. Conecte o ESP32-S3 ao computador via USB.
4. Compile e faça o upload do código para o ESP32-S3.
5. Abra o **Monitor Serial** para acompanhar mensagens de debug.
6. Abra o app BLE no celular e conecte ao dispositivo **ESP32-S3-NimBLE**.
7. Envie comandos `"1"`,  `"2"` ou outro comando que deseje e veja a resposta do ESP32-S3.

---
