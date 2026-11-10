# Fundamentals of Internet of Things — Laboratory Assessment Repository

**Course:** 25CS2741 Fundamentals of Internet of Things + Lab  
**Institution:** Shiv Nadar University Chennai  
**Department:** Department of Computer Science and Engineering  
**Class:** II Year / 3rd Semester B.Tech CSE (IoT)  
**Student Name:** Yazhini J E  
**Register Number:** 25011102119  
**GitHub Repository:** [25011102119_FIoT_LAB](https://github.com/YazhiniJE/25011102119_FIoT_LAB)  

---

## 1. Laboratory Experiments Index

| CAT | Platform | Date | Experiment Title | Key Tasks & Objectives | Experiment Folder |
|:---:|:---|:---:|:---|:---|:---:|
| **CAT 2** | 8051 (AT89S52) | 20/07/2026 | 8051 Tool Chain Setup, Bare-Metal LED Blink | • Board bring-up & toolchain setup<br>• Bare-metal LED blink ~1 Hz on P1.0<br>• Custom calibrated delay library (`delay.c`/`delay.h`) | [8051/CAT2](8051/CAT2/) |
| **CAT 3** | 8051 (AT89S52) | 27/07/2026 | Timer-Based LED Pattern Generator and Button Interrupt Controller | • 4 LEDs + matrix tactile push button<br>• Debounced state controller<br>• 4 modes: Running LED, Binary Counter, Alternate 1010/0101, All Flash | [8051/CAT3](8051/CAT3/) |
| **CAT 4** | 8051 (AT89S52) | 03/08/2026 | Human-Machine Interface using Matrix Keypad, LEDs, and Seven-Segment Display | • 4x4 matrix keypad scanner<br>• 7-segment display numeric feedback (0–9)<br>• Multi-mode LED controller (individual, running, alternate, binary 0–15, blink, reset) | [8051/CAT4](8051/CAT4/) |
| **CAT 5** | 8051 (AT89S52) | 10/08/2026 | Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control | • Hardware Timer 0 in 16-bit Mode 1<br>• Deterministic 1.0 s interval (200 overflows)<br>• 0.5 Hz symmetric square wave pulse generation without software loops | [8051/CAT5](8051/CAT5/) |
| **CAT 6** | 8051 (AT89S52) | 17/08/2026 | UART Driver and Serial Debugging | • 9600-8-N-1 UART framing (Timer 1 Mode 2 auto-reload)<br>• Task A: Continuous string transmission (`"Hello from 8051"`)<br>• Task B: Full-duplex interactive character echo | [8051/CAT6](8051/CAT6/) |
| **CAT 7** | 8051 (AT89S52) | 24/08/2026 | 16x2 LCD Driver Development and Dynamic Display Control | • 4-bit HD44780 LCD driver (`lcd_init`, `lcd_cmd`, `lcd_data`)<br>• Dynamic cursor DDRAM addressing (`lcd_goto`) & counter display<br>• Keypad 2/8/4/6 interactive directional character movement | [8051/CAT7](8051/CAT7/) |
| **CAT 8** | STM32 Blue Pill (STM32F103C8T6) | 18/09/2026 | STM32 GPIO Bring-Up and Switch-Controlled LED | • Task 8A: GPIO input/output level tracking<br>• Task 8B: Software debounced toggle control<br>• Task 8C: Non-blocking dual-mode duration controller (Short <1s vs Long ≥1s press) | [STM32/CAT8](STM32/CAT8/) |
| **CAT 9** | STM32 Blue Pill (STM32F103C8T6) | 28/09/2026 | STM32 UART Command Controlled LED | • Task 9A: USART1 character transmission and echo<br>• Task 9B: Interactive ASCII command decoder (`LED ON`, `LED OFF`, `LED TOGGLE`) with `\r` and `\n` handling | [STM32/CAT9](STM32/CAT9/) |
| **CAT 10** | STM32 Blue Pill + Wemos D1 Mini (ESP8266) | 12/10/2026 | STM32-Wemos Wi-Fi Modem Using AT Commands / HTTP Server | • Dual USART modem architecture (AT commands at 115200 baud)<br>• Multi-connection TCP Server binding on Port 80 (`AT+CIPSERVER`)<br>• Incoming HTTP `+IPD` frame parsing and HTTP 200 OK dynamic web server | [STM32/CAT10](STM32/CAT10/) |
| **CAT 11** | ST NUCLEO-F401RE (ARM Cortex-M4) | 14/10/2026 | STM32F401RE Cortex-M4: GPIO and User Input Programming | • Task 1: Bare-metal on-board user LED blink (LD2 / PA5)<br>• Task 2: Push button (PC13) latching with 30 ms debounce<br>• Task 3: Short tap toggle vs Long hold (≥500 ms) rapid alert blink | [STM32/CAT11](STM32/CAT11/) |
| **CAT 12** | ST NUCLEO-F401RE + Bosch BME280 | 23/10/2026 | BME280 Sensor Interfacing Using I2C and Bosch Sensor API | • Standard Mode (100 kHz) I2C1 communication with BME280 (0x76)<br>• Bosch Sensortec API integration (`bme280.c`/`bme280.h`)<br>• High-precision compensation for Temperature, Pressure, and Humidity | [STM32/CAT12](STM32/CAT12/) |
| **CAT 13** | ST NUCLEO-F401RE + BME280 + ESP8266 | 27/10/2026 | BME280 Sensor Interfacing Using I2C and MQTT using Custom Built ESP8266 API | • Custom modem API (`ESPLib.c`/`ESPLib.h`)<br>• JSON environmental telemetry payload formatting<br>• TCP connection and MQTT publishing to `broker.emqx.io:1883`<br>• Real-time Node-RED telemetry dashboard visualization | [STM32/CAT13](STM32/CAT13/) |

---

## 2. Repository Structure

The directory hierarchy strictly adheres to the course submission specification:

```text
25011102119_FIoT_LAB/
├── README.md                           # Main index and laboratory summary
├── .gitignore                          # Build artifact and temporary file exclusions
│
├── 8051/                               # 8051 Microcontroller (AT89S52) Experiments
│   ├── CAT2/                           # Bare-Metal LED Blink & Custom Delay Library
│   │   ├── README.md
│   │   ├── circuit.png
│   │   ├── TASK_2_Bare_Metal_LED_Blink/
│   │   └── TASK_3_Custom_Delay_Library/
│   ├── CAT3/                           # 4-Mode LED Pattern Generator & Button Controller
│   │   ├── README.md
│   │   ├── circuit.png
│   │   ├── day2.c, day2.uvproj, STARTUP.A51
│   │   └── Objects/ (day2.hex)
│   ├── CAT4/                           # HMI: 4x4 Matrix Keypad, 7-Segment & LEDs
│   │   ├── README.md
│   │   ├── circuit.png
│   │   ├── sevensg.c, sevenseg.uvproj, STARTUP.A51
│   │   └── Objects/ (sevenseg.hex)
│   ├── CAT5/                           # Hardware Timer 0 Accurate Timing
│   │   ├── README.md
│   │   ├── circuit.png
│   │   ├── timer.c, timers.uvproj, STARTUP.A51
│   │   └── Objects/ (timers.hex)
│   ├── CAT6/                           # UART Serial Driver & Echo Terminal
│   │   ├── README.md
│   │   ├── circuit.png
│   │   ├── TASK_A_UART_Initialization_and_Character_Transmission/
│   │   └── TASK_B_UART_Echo/
│   └── CAT7/                           # 16x2 HD44780 LCD Driver & Dynamic Navigation
│       ├── README.md
│       ├── circuit.png
│       ├── TASK_7A_LCD_Initialization_and_Character_String_Display/
│       ├── TASK_7B_Cursor_Positioning_and_Dynamic_Value_Update/
│       └── TASK_7C_Keypad_Based_Character_Movement/
│
├── STM32/                              # STM32 Microcontroller Experiments
│   ├── CAT8/                           # STM32F103 Blue Pill GPIO & Switch Control
│   │   ├── README.md
│   │   ├── circuit.png
│   │   ├── TASK_8A_GPIO_Input_Output/
│   │   ├── TASK_8B_Event_Based_Control/
│   │   └── TASK_8C_Short_Press_vs_Long_Press/
│   ├── CAT9/                           # STM32F103 UART Command Controlled LED
│   │   ├── README.md
│   │   ├── circuit.png
│   │   ├── TASK_9A_Basic_UART_Communication/
│   │   └── TASK_9B_String_Based_Application_Logic/
│   ├── CAT10/                          # STM32 + Wemos D1 Mini Wi-Fi HTTP Server
│   │   ├── README.md
│   │   ├── circuit.png
│   │   ├── TASK_10A_AT_Commands/
│   │   ├── TASK_10C_TCP_Server/
│   │   └── TASK_10D_HTTP_Response/
│   ├── CAT11/                          # NUCLEO-F401RE Cortex-M4 GPIO Bring-Up
│   │   ├── README.md
│   │   ├── circuit.png
│   │   └── NUCLEO_GPIO_BringUp/
│   ├── CAT12/                          # NUCLEO-F401RE + BME280 I2C Telemetry
│   │   ├── README.md
│   │   ├── circuit.png
│   │   └── NUCLEO_BME280_I2C/
│   └── CAT13/                          # NUCLEO-F401RE + BME280 + ESP8266 MQTT Publisher
│       ├── README.md
│       ├── circuit.png
│       └── NUCLEO_BME280_ESP8266_MQTT/
│
└── tools/                              # Automation and schematic generation scripts
    ├── circuits.py                     # Matplotlib schematic drawing engine
    ├── generate_all_circuits.py        # Automated generator for all 12 circuit.png diagrams
    └── setup_stm32.py                  # Project sanitization and configuration utility
```

---

## 3. Hardware & Software Requirements

### Hardware Platforms
1. **8051 Kit:** Atmel AT89S52 (40-pin DIP) running with an 11.0592 MHz crystal oscillator.
2. **STM32 Blue Pill:** STM32F103C8T6 (ARM Cortex-M3, 72 MHz, 64 KB Flash, 20 KB SRAM).
3. **STM32 Nucleo:** STMicroelectronics NUCLEO-F401RE (ARM Cortex-M4 with FPU, 84 MHz, 512 KB Flash, 96 KB SRAM).
4. **Wireless & Sensors:** Wemos D1 Mini (ESP8266 Wi-Fi SoC with AT firmware), Bosch Sensortec BME280 digital environmental sensor (I2C address `0x76`).

### Toolchains & IDEs
- **Keil µVision C51 (v9.x)** for 8051 compilation and debugging.
- **Keil MDK-ARM (v5.x)** with ARM Compiler 5 / 6 for STM32 firmware build.
- **STM32CubeMX** for pinout, clock tree, and peripheral initialization generation.
- **ST-LINK Utility / STM32CubeProgrammer** for flashing and firmware verification.
- **PuTTY / Serial Terminal** for serial console debugging at 9600 and 115200 baud.
- **Node-RED** for cloud MQTT subscriber dashboard and HTTP request client validation.

---
