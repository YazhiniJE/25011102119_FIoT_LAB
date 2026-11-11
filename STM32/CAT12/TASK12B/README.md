# CAT12 TASK12B: BME280 Environmental Sensor Calibration & Measurement Driver

**Course:** 25CS2741 Fundamentals of Internet of Things + Lab  
**Student:** Yazhini J E (Reg No: 25011102119)  
**Institution:** Shiv Nadar University Chennai  
**Date:** 26/10/2026  
**Platform:** STM32 NUCLEO-F401RE / STM32F103C8T6  
**Core Clock:** 84 MHz  

---

## 1. Overview & Objectives
This experiment develops a direct register-level driver for the Bosch BME280 combined temperature, pressure, and humidity sensor over I2C. The driver reads the 24-byte factory calibration trimming parameters from non-volatile memory, captures raw 20-bit ADC burst registers, and executes the proprietary Bosch compensation algorithms to extract true physical values.

---

## 2. Register Architecture & Compensation
1. **Device ID (`0xD0`):** Reads `0x60` to verify genuine BME280.
2. **Trimming Registers (`0x88–0xA1`, `0xE1–0xE7`):** Loads calibration coefficients ($dig\_T1..T3$, $dig\_P1..P9$, $dig\_H1..H6$).
3. **Data Registers (`0xF7–0xFE`):** 8-byte continuous burst read capturing uncompensated pressure (`msb, lsb, xlsb`), temperature (`msb, lsb, xlsb`), and humidity (`msb, lsb`).
4. **Calculated outputs:** Temperature in °C, Pressure in hPa, Humidity in %RH.

---

## 3. Circuit Schematic
![Circuit Diagram](circuit.png)

---

## 4. Build, Flashing & Execution
1. Open `MDK-ARM/MQTT.uvprojx` in Keil µVision.
2. Build and flash firmware.
3. Serial monitor displays calibrated temperature, pressure, and relative humidity.
