# CAT5 TASK5C: Stepper Motor Commutation Controller (ULN2003 Driver)

**Course:** 25CS2741 Fundamentals of Internet of Things + Lab  
**Student:** Yazhini J E (Reg No: 25011102119)  
**Institution:** Shiv Nadar University Chennai  
**Date:** 10/08/2026  
**Platform:** 8051 Microcontroller (AT89S52)  
**Clock Frequency:** 11.0592 MHz  

---

## 1. Overview & Objectives
This task implements a 4-phase unipolar stepper motor drive controller using an AT89S52 microcontroller and a ULN2003 Darlington transistor array. Paced by Timer0 interrupts at 10 ms step intervals, the motor commutates smoothly in full-step mode to achieve controlled angular velocity and positioning.

---

## 2. Motor Commutation Sequence
The 4 coils (A, B, C, D) are driven via Port 2 pins `P2.0`–`P2.3`. In 2-phase full-step excitation mode, two coils are energized simultaneously to maximize torque:
| Step | Coil A (`P2.0`) | Coil B (`P2.1`) | Coil C (`P2.2`) | Coil D (`P2.3`) | Hex Nibble |
|---|---|---|---|---|---|
| **1** | 1 | 0 | 0 | 1 | `0x09` |
| **2** | 1 | 1 | 0 | 0 | `0x0C` |
| **3** | 0 | 1 | 1 | 0 | `0x06` |
| **4** | 0 | 0 | 1 | 1 | `0x03` |

---

## 3. Circuit Schematic
![Circuit Diagram](circuit.png)

---

## 4. Build, Flashing & Execution
1. Open `stepper.uvproj` in Keil µVision.
2. Build project to produce `Objects/stepper.hex`.
3. Connect 28BYJ-48 stepper motor through ULN2003 driver board to `P2.0`–`P2.3`.
4. Power motor with external +5V DC supply; verify continuous, steady rotation.
