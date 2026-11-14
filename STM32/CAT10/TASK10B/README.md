# TASK10B – ESP8266 AT Command Interface

## Experiment Details

**EXP:** CONTINUOUS ASSESSMENT 10 – TASK B
**DATE:** 12/10/2026
**NAME:** STM32–Wemos Wi-Fi Modem Interface Using AT Commands
**PLATFORM:** STM32 Blue Pill (STM32F103C8T6) + Wemos D1 Mini (ESP8266)

## Objective

Exercise the full AT command set on the ESP8266 Wi-Fi modem:
set station mode, connect to an access point, and retrieve the assigned IP address.

## Working Principle

The STM32 sequences AT commands (`AT+CWMODE=1`, `AT+CWJAP`, `AT+CIFSR`) over USART2
and logs responses via USART1 to a PC terminal, exercising the AT command interface.

## Project Files

- `Core/Src/main.c` – AT command sequencer
- `Wemos.ioc` – STM32CubeMX configuration
