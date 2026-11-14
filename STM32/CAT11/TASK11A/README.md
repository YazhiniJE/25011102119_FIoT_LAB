# TASK11A – TCP Server Setup and IP Retrieval

## Experiment Details

**EXP:** CONTINUOUS ASSESSMENT 11 – TASK A
**DATE:** 14/10/2026
**NAME:** HTTP Server – STM32–Wemos Wi-Fi Modem Using AT Commands
**PLATFORM:** STM32 Blue Pill (STM32F103C8T6) + Wemos D1 Mini (ESP8266)

## Objective

Enable the ESP8266 as a multi-connection TCP server on port 80, retrieve the
device IP address, and capture incoming `+IPD` data frames from HTTP clients.

## Working Principle

After Wi-Fi association, the STM32 sends:
- `AT+CIPMUX=1` – enable multi-connection mode
- `AT+CIPSERVER=1,80` – open TCP listener on port 80
- `AT+CIFSR` – retrieve and log the device IP address

The STM32 then monitors USART2 for incoming `+IPD,<id>,<len>:<data>` frames
indicating an HTTP client has connected.

## Circuit

- `PA2` : USART2_TX → RXD of ESP8266
- `PA3` : USART2_RX → TXD of ESP8266
- `PA9` : USART1_TX → PC Debug Console
- `PC13` : Status LED

## Project Files

- `Core/Src/main.c` – TCP server configuration and +IPD frame capture
- `Task-10C.ioc` – STM32CubeMX configuration
