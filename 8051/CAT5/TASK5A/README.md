# CAT5 TASK5A: Hardware Timer0 Periodic Interrupt and Heartbeat LED Blink

**Course:** 25CS2741 Fundamentals of Internet of Things + Lab  
**Student:** Yazhini J E (Reg No: 25011102119)  
**Institution:** Shiv Nadar University Chennai  
**Date:** 10/08/2026  
**Platform:** 8051 Microcontroller (AT89S52)  
**Clock Frequency:** 11.0592 MHz  

---

## 1. Overview & Objectives
This experiment develops a hardware timer interrupt driver on the 8051 architecture using **Timer0 in 16-bit Mode 1**. A deterministic 1 ms periodic interrupt tick is synthesized without CPU-blocking software delay loops. An ISR software counter counts 1000 ticks to toggle a heartbeat LED connected to `P1.0` precisely every 1.0 second.

---

## 2. Hardware Timer Mathematical Derivations
- **Crystal Frequency ($f_{osc}$):** $11.0592 \text{ MHz}$
- **Machine Cycle Clock ($f_{mc}$):** $\frac{11.0592 \text{ MHz}}{12} = 921.6 \text{ kHz}$
- **Machine Cycle Period ($T_{mc}$):** $1.0850694 \text{ }\mu\text{s}$
- **Target Interrupt Period ($T_{int}$):** $1.0 \text{ ms} = 1000 \text{ }\mu\text{s}$

Number of timer counts per 1 ms:
$$N = \frac{1000 \text{ }\mu\text{s}}{1.0850694 \text{ }\mu\text{s}} = 921.6 \approx 922 \text{ counts}$$

16-Bit Timer Initial Reload Value:
$$\text{Reload} = 65536 - 922 = 64614 = 0\text{xFC66}$$
$$\implies \mathbf{TH0 = 0\text{xFC}}, \quad \mathbf{TL0 = 0\text{x66}}$$

---

## 3. Register Configuration
- **`TMOD = 0x01`**: Configures Timer0 in Mode 1 (16-bit Timer/Counter).
- **`TH0 = 0xFC`, `TL0 = 0x66`**: Preloads the 1 ms overflow timing constant.
- **`ET0 = 1`**: Enables Timer0 Overflow Interrupt.
- **`EA = 1`**: Enables Global Interrupts.
- **`TR0 = 1`**: Starts Timer0 counting.

---

## 4. Circuit Schematic
![Circuit Diagram](circuit.png)

---

## 5. Build, Flashing & Execution
1. Open `timers.uvproj` in Keil µVision.
2. Build project (`F7`) to generate `Objects/timers.hex`.
3. Program into AT89S52 using an ISP programmer.
4. Probe `P1.0` with an oscilloscope or observe the on-board LED; confirm exact 1.000 Hz toggle frequency.
