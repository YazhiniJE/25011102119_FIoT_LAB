# CAT5 TASK5B.1: Software PWM LED Fading via Timer Interrupt

**Course:** 25CS2741 Fundamentals of Internet of Things + Lab  
**Student:** Yazhini J E (Reg No: 25011102119)  
**Institution:** Shiv Nadar University Chennai  
**Date:** 10/08/2026  
**Platform:** 8051 Microcontroller (AT89S52)  
**Clock Frequency:** 11.0592 MHz  

---

## 1. Overview & Objectives
This experiment designs a high-resolution software Pulse Width Modulation (PWM) engine on the 8051 microcontroller to smoothly modulate LED brightness. Using Timer0 interrupts, a 100-step PWM waveform is generated on `P1.0`. The duty cycle is dynamically swept from 0% to 100% and back to 0% to produce a smooth, breathing/fading visual effect without CPU blocking.

---

## 2. Software PWM Synthesis Math
- **PWM Base Frequency ($f_{pwm}$):** $100 \text{ Hz}$ (sufficiently above human eye persistence of vision flicker threshold).
- **PWM Resolution:** 100 discrete duty cycle steps (0% to 100%).
- **Timer Interrupt Tick Period:** $T_{step} = \frac{1}{100 \text{ Hz} \times 100} = 100 \text{ }\mu\text{s}$.
- Machine cycles per $100 \text{ }\mu\text{s}$: $\frac{100 \mu\text{s}}{1.085 \mu\text{s}} \approx 92 \text{ cycles}$.
- Timer reload: $65536 - 92 = 65444 = 0\text{xFFA4} \implies \mathbf{TH0=0\text{xFF}, TL0=0\text{xA4}}$.

In the ISR, a tick counter increments from 0 to 99:
- If `counter < duty_cycle`, `LED = 0` (Active-low ON).
- Else, `LED = 1` (Active-low OFF).
- Every 20 ms, the duty cycle increments or decrements by 1 step.

---

## 3. Circuit Schematic
![Circuit Diagram](circuit.png)

---

## 4. Build, Flashing & Execution
1. Open `pwm_fade.uvproj` in Keil µVision.
2. Build project to output `Objects/pwm_fade.hex`.
3. Flash the AT89S52 microcontroller.
4. Verify smooth, continuous illumination fading on `P1.0`.
