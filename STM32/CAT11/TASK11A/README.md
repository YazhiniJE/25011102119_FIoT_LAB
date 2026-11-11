# CAT11 TASK11A: NUCLEO-F401RE / Blue Pill Heartbeat LED Blinker

**Course:** 25CS2741 Fundamentals of Internet of Things + Lab  
**Student:** Yazhini J E (Reg No: 25011102119)  
**Institution:** Shiv Nadar University Chennai  
**Date:** 19/10/2026  
**Platform:** STM32 NUCLEO-F401RE / STM32F103C8T6  
**Core Clock:** 84 MHz (F401RE) / 72 MHz (F103)  

---

## 1. Overview & Objectives
This experiment verifies the hardware board bring-up and toolchain setup for the STM32 ARM Cortex-M platform. An on-board user LED (`PA5` on NUCLEO-F401RE or `PC13` on Blue Pill) is configured as a general-purpose digital output and toggled at a 1 Hz heartbeat frequency (500 ms ON, 500 ms OFF) using `HAL_GPIO_TogglePin()` and `HAL_Delay()`.

---

## 2. Hardware Pinout Table
| Board | User LED Pin | Active State | Drive Configuration |
|---|---|---|---|
| **NUCLEO-F401RE** | `PA5` (LD2) | Active HIGH | Push-Pull, No-Pull, High Speed |
| **Blue Pill (F103)**| `PC13` | Active LOW | Push-Pull, No-Pull, Low Speed |

---

## 3. Circuit Schematic
![Circuit Diagram](circuit.png)

---

## 4. Build, Flashing & Execution
1. Open `MDK-ARM/Led-Blink.uvprojx` in Keil µVision.
2. Compile project (`F7`) and download to board (`F8`).
3. Verify regular 1 Hz blinking of user LED LD2.
