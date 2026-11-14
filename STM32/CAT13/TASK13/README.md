# TASK13 – BME280 Sensor Interfacing, HTTP Communication and Node-RED Analytics

## Experiment Details

**EXP:** CONTINUOUS ASSESSMENT 13
**DATE:** 27/10/2026
**NAME:** Sensor Interfacing (BME280) - STM32 (Debug) - ESP8266 (Wi-Fi) HTTP - Node Analytics
**PLATFORM:** ST NUCLEO-F401RE + Bosch BME280 (I2C) + ESP8266 Wi-Fi + Node-RED

## Objective

Interface the BME280 environmental sensor with STM32 over I2C, transmit sensor
readings (temperature, pressure, humidity) via ESP8266 over HTTP to a Node-RED
analytics dashboard.

## Circuit

- `PB8` : I2C1_SCL → BME280 SCL
- `PB9` : I2C1_SDA → BME280 SDA
- `PA9` : USART1_TX → ESP8266 RXD
- `PA10` : USART1_RX → ESP8266 TXD
- `PA5` : Status LED (LD2)

## Implementation

1. BME280 reads temperature (°C), pressure (hPa), humidity (%RH) via I2C using the Bosch Sensortec API.
2. STM32 formats readings into an HTTP GET request and sends it via ESP8266 AT commands.
3. A Node-RED HTTP-in node receives the data and routes it to gauge and chart dashboard widgets.

## Project Files

- `Core/Src/main.c` – Sensor acquisition, HTTP transmission loop
- `Core/Inc/` – BME280 driver headers
- `circuit.png` – Hardware wiring diagram
- `flows.json` – Node-RED analytics flow
