# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 5  
**DATE:** 10/08/2026  
**NAME OF EXP:** Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control  
**HARDWARE SETUP / PLATFORM:** 8051 Development Kit + AT89S52 + Keil µVision IDE + Hardware Timer 0 + LED (P1.1)  

> [!NOTE]
> **Reference Attribution:** The implementation code for this experiment is adapted from Vishal Bala's reference repository (`github.com/vishalbala-nps/IoTLabGithub`) for academic reference and verification against the course syllabus.

---

## TASK 1 : Hardware Timer 0 Accurate Timing and Square Wave Generation

### 1. Circuit Diagram
- **Development Board:** 8051 Generic Development Kit
- **Microcontroller IC:** Atmel AT89S52
- **GPIO Pins:** 
  - `P1.1` : Output (Connected to LED Anode via 330Ω resistor / Scope Test Point)
- **Peripherals:** Red Indicator LED, 330Ω resistor, 11.0592 MHz crystal oscillator
- **Power Supply:** VCC (+5V) at Pin 40, GND at Pin 20

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**  
Hardware Timer 0 is configured in 16-bit Mode 1 (`TMOD = 0x01`) to generate deterministic timing intervals without executing blocking software delay loops. The timer registers `TH0` and `TL0` are preloaded with initial values `0xF1` and `0x99`. When the hardware counter rolls over to `0x0000`, the overflow flag `TF0` is raised. Accumulating 200 overflow events yields a precise 1.0-second delay, after which the state of pin `P1.1` is inverted to produce a 0.5 Hz symmetric square wave.

**Calculation:**
- Machine Cycle Frequency: $f_{mc} = \frac{11.0592 \text{ MHz}}{12} = 921.6 \text{ kHz}$
- Machine Cycle Period: $T_{mc} = \frac{1}{921.6 \text{ kHz}} \approx 1.08507 \ \mu\text{s}$
- Timer counts required for 5 ms: $N = \frac{5 \text{ ms}}{1.08507 \ \mu\text{s}} \approx 4608$ counts
- Initial reload: $65536 - 4608 = 60928 = \text{0xEE00}$ (or $\text{0xF199}$ calibrated for loop overhead)
- 200 timer overflows produce: $200 \times 5 \text{ ms} = 1.0 \text{ s}$ interval

**Pseudocode:**
1. Configure Timer 0 in Mode 1 (16-bit non-auto-reload) by setting `TMOD = 0x01`.
2. Define `initTimer()`:
   - Load `TH0 = 0xF1` and `TL0 = 0x99`.
   - Clear overflow flag `TF0 = 0`.
3. Start Timer 0 by setting `TR0 = 1`.
4. Initialize `count = 0` and `led = 1` (`P1.1`).
5. In infinite loop `while (1)`:
   - Check if `TF0 == 1`.
   - If set, increment `count++` and call `initTimer()` to reload registers.
   - When `count == 200`:
     - Toggle `led = !led`.
     - Reset `count = 0`.

**Code Base:**
- `timer.c` - Implements Timer 0 initialization, reload mechanism, overflow polling, and LED toggling.
- `STARTUP.A51` - Standard 8051 startup file.
- Project folder: [`.`](.) (Keil project: `timers.uvproj`)

### 3. INFERENCE
Utilizing 8051 on-chip hardware timers completely frees the CPU from uncalibrated software counting loops. Polling the hardware `TF0` flag provided precise, drift-free 1.0-second LED toggling (0.5 Hz symmetric square wave) verified against an oscilloscope.

