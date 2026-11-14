# TASK11B – Dynamic HTTP Webpage and Node-RED Integration

## Experiment Details

**EXP:** CONTINUOUS ASSESSMENT 11 – TASK B
**DATE:** 14/10/2026
**NAME:** HTTP Server – STM32–Wemos Wi-Fi Modem Using AT Commands
**PLATFORM:** STM32 Blue Pill (STM32F103C8T6) + Wemos D1 Mini (ESP8266)

## Objective

Parse incoming HTTP GET requests (`+IPD` frames) and respond with a dynamic
`HTTP/1.1 200 OK` HTML webpage. Integrate with Node-RED via HTTP request nodes.

## Working Principle

The STM32 reads the connection link ID from the `+IPD` frame, constructs a valid
HTTP response (`Content-Type: text/html`, `Connection: close`), issues
`AT+CIPSEND=<id>,<len>`, transmits the HTML payload, then closes the socket
with `AT+CIPCLOSE=<id>`.

Node-RED uses an HTTP request node pointed at the STM32's IP address to poll
the embedded web server and feed sensor data to dashboard widgets.

## Circuit

- `PA2` : USART2_TX → RXD of ESP8266
- `PA3` : USART2_RX → TXD of ESP8266
- `PA9` : USART1_TX → PC Debug Console

## Project Files

- `Core/Src/main.c` – HTTP response handler, +IPD parser, socket lifecycle
- `Task-10C.ioc` – STM32CubeMX configuration
