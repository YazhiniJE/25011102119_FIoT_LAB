# CAT12 TASK12C: Environmental Telemetry Serial Streamer (JSON / CSV Format)

**Course:** 25CS2741 Fundamentals of Internet of Things + Lab  
**Student:** Yazhini J E (Reg No: 25011102119)  
**Institution:** Shiv Nadar University Chennai  
**Date:** 26/10/2026  
**Platform:** STM32 NUCLEO-F401RE / STM32F103C8T6  
**Core Clock:** 84 MHz  

---

## 1. Overview & Objectives
This experiment packages environmental sensor data acquired from the BME280 into standardized IoT telemetry payloads formatted as JSON and CSV strings. The serialized telemetry packet is streamed at 1-second intervals across USART2 at 115200 baud for consumption by cloud gateways and edge computers.

---

## 2. Serial Telemetry Schema
```json
{
  "device_id": "SNUC_STM32_25011102119",
  "temperature_C": 26.45,
  "pressure_hPa": 1012.30,
  "humidity_pct": 58.70,
  "uptime_ms": 14500
}
```

---

## 3. Circuit Schematic
![Circuit Diagram](circuit.png)

---

## 4. Build, Flashing & Execution
1. Open `MDK-ARM/MQTT.uvprojx` in Keil µVision.
2. Build and flash target firmware.
3. View serial terminal output; observe structured JSON telemetry streaming continuously.
