# TASK10A – STM32 and Wemos UART Communication

## Experiment Details

**EXP:** CONTINUOUS ASSESSMENT 10 – TASK A
**DATE:** 12/10/2026
**NAME:** STM32–Wemos Wi-Fi Modem Interface Using AT Commands
**PLATFORM:** STM32 Blue Pill (STM32F103C8T6) + Wemos D1 Mini (ESP8266)

## Objective

Establish basic UART communication between the STM32 and the Wemos D1 Mini (ESP8266).
Verify modem responsiveness using the `AT` command.

## Circuit

- `PA2` : USART2_TX → RXD of ESP8266
- `PA3` : USART2_RX → TXD of ESP8266
- `PA9` : USART1_TX → PC Serial Console
- `PC13` : Status LED

## Working Principle

The STM32 transmits `AT\r\n` over USART2 and verifies the modem replies with `OK`,
confirming the UART link between the host MCU and the ESP8266 Wi-Fi modem is operational.

## Project Files

- `Core/Src/main.c` – UART dual-interface setup and AT handshake
- `Wemos.ioc` – STM32CubeMX configuration
