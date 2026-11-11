# CAT14 TASK14: Interactive Dual-MCU UART Game Controller (PingPong Player Node)

**Course:** 25CS2741 Fundamentals of Internet of Things + Lab  
**Student:** Yazhini J E (Reg No: 25011102119)  
**Institution:** Shiv Nadar University Chennai  
**Date:** 09/11/2026  
**Platform:** STM32F103C8T6 (Blue Pill ARM Cortex-M3)  
**Core Clock:** 72 MHz  

---

## 1. Overview & Objectives
This project implements the dedicated Player Node for an interactive dual-MCU networked PingPong game system. Built upon Yazhini's original hardware and Keil implementation, the STM32F103C8T6 interfaces with push-button controls (Paddle UP / DOWN), status indicators (Hit / Miss LEDs), and communicates with the opponent MCU over a full-duplex UART game bus at 115200 baud.

---

## 2. Hardware Pinout Table
| STM32 Pin | Function | Hardware Connection | Description |
|---|---|---|---|
| **PA0** | GPIO Input (Pull-Up) | Push Button UP | Moves paddle upwards |
| **PA1** | GPIO Input (Pull-Up) | Push Button DOWN | Moves paddle downwards |
| **PC13** | GPIO Output | Hit / Status LED | Indicates successful ball return |
| **PA4** | GPIO Output | Miss / Penalty LED | Indicates missed ball / game loss |
| **PA9 / PA10** | USART1 TX / RX | Game Bus Interconnect | Transmits paddle movements & hits |

---

## 3. Game State Machine & Packet Protocol
The player node runs a real-time event loop processing inputs and incoming game packets:
- **`[MOVE_UP]` / `[MOVE_DN]`**: Transmitted upon button press to update paddle position on host/display MCU.
- **`[BALL_INCOMING]`**: Received when the ball enters the player's court. If paddle position matches ball trajectory, sends `[HIT]` and flashes Hit LED (`PC13`).
- **`[MISS]`**: Triggered if paddle misses the incoming ball; illuminates Miss LED (`PA4`).

---

## 4. Circuit Schematic
![Circuit Diagram](circuit.png)

---

## 5. Build, Flashing & Execution
1. Open `MDK-ARM/Player.uvprojx` in Keil µVision.
2. Build project (`F7`) to compile source files.
3. Flash the STM32F103 Blue Pill using ST-LINK V2 (`F8`).
4. Interconnect USART TX/RX pins with the opponent game node and participate in real-time interactive gameplay.
