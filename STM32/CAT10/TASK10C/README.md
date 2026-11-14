# TASK10C – Wi-Fi Station Mode and Network Connectivity

## Experiment Details

**EXP:** CONTINUOUS ASSESSMENT 10 – TASK C
**DATE:** 12/10/2026
**NAME:** STM32–Wemos Wi-Fi Modem Interface Using AT Commands
**PLATFORM:** STM32 Blue Pill (STM32F103C8T6) + Wemos D1 Mini (ESP8266)

## Objective

Connect the ESP8266 to a Wi-Fi access point in station mode and confirm network
connectivity by retrieving the DHCP-assigned IP address.

## Working Principle

The STM32 issues `AT+CWMODE=1` (station mode), then `AT+CWJAP` to associate with the
Wi-Fi network, and finally `AT+CIFSR` to read the IP address. The full connection
sequence is validated and the IP is forwarded to the USART1 debug console.

## Project Files

- `Core/Src/main.c` – Wi-Fi association and IP retrieval sequence
- See TASK10A project for shared hardware configuration
