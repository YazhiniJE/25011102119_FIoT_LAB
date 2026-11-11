# CAT5 TASK5B.2: Precision Square Wave Generation (1 kHz and 2 kHz Frequencies)

**Course:** 25CS2741 Fundamentals of Internet of Things + Lab  
**Student:** Yazhini J E (Reg No: 25011102119)  
**Institution:** Shiv Nadar University Chennai  
**Date:** 10/08/2026  
**Platform:** 8051 Microcontroller (AT89S52)  
**Clock Frequency:** 11.0592 MHz  

---

## 1. Overview & Objectives
This task demonstrates deterministic square wave pulse generation with an exact 50% duty cycle on GPIO pin `P1.1`. By dynamically altering the Timer0 reload parameters, the system outputs either a **1 kHz** or **2 kHz** square wave, selectable via a hardware selector switch on `P3.2`.

---

## 2. Timer Reload Calculations
For a 50% duty cycle square wave with frequency $f$:
$$T_{half} = \frac{1}{2 \times f}$$

### 1 kHz Square Wave:
- $T_{half} = \frac{1}{2000} = 500 \text{ }\mu\text{s}$.
- Counts $= \frac{500 \mu\text{s}}{1.08507 \mu\text{s}} = 461 \text{ cycles}$.
- $\text{Reload} = 65536 - 461 = 65075 = 0\text{xFE33} \implies \mathbf{TH0=0\text{xFE}, TL0=0\text{x33}}$.

### 2 kHz Square Wave:
- $T_{half} = \frac{1}{4000} = 250 \text{ }\mu\text{s}$.
- Counts $= \frac{250 \mu\text{s}}{1.08507 \mu\text{s}} = 230 \text{ cycles}$.
- $\text{Reload} = 65536 - 230 = 65306 = 0\text{xFF1A} \implies \mathbf{TH0=0\text{xFF}, TL0=0\text{x1A}}$.

---

## 3. Circuit Schematic
![Circuit Diagram](circuit.png)

---

## 4. Build, Flashing & Execution
1. Open `square_wave.uvproj` in Keil µVision.
2. Build project to output `Objects/square_wave.hex`.
3. Flash the AT89S52 microcontroller.
4. Connect an oscilloscope or logic analyzer to `P1.1`; observe crisp 1 kHz and 2 kHz square waves when toggling `P3.2`.
