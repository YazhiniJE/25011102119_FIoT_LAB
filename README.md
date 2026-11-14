# Fundamentals of Internet of Things - Laboratory Assessment Repository

**Course:** 25CS2741 Fundamentals of Internet of Things + Lab  
**Institution:** Shiv Nadar University Chennai  
**Department:** Department of Computer Science and Engineering  
**Class:** II Year / 3rd Semester B.Tech CSE (IoT)  
**Student Name:** Yazhini J E  
**Register Number:** 25011102119  
**GitHub Repository:** [25011102119_FIoT_LAB](https://github.com/YazhiniJE/25011102119_FIoT_LAB)  

---

## Laboratory Experiments Index (CAT 2 - CAT 15)

| CAT | Platform | Date | Experiment Title | Tasks & Subtasks | Experiment Folder |
|:---:|:---|:---:|:---|:---|:---:|
| **CAT 2** | 8051 (AT89S52) | 20/07/2026 | 8051 Tool Chain Setup, Bare-Metal LED Blink | - [TASK2B](8051/CAT2/TASK2B/): Bare-metal LED blink ~1 Hz & custom delay library | [8051/CAT2](8051/CAT2/) |
| **CAT 3** | 8051 (AT89S52) | 27/07/2026 | Timer-Based LED Pattern Generator & Button Controller | - [TASK3A](8051/CAT3/TASK3A/): 4-mode debounced pattern sequencer (Running, Counter, Alternate, Flash) | [8051/CAT3](8051/CAT3/) |
| **CAT 4** | 8051 (AT89S52) | 03/08/2026 | HMI using Matrix Keypad, LEDs, and 7-Segment Display | - [TASK4A](8051/CAT4/TASK4A/): Keypad 0-9 decoding, 7-segment display & animated LED modes | [8051/CAT4](8051/CAT4/) |
| **CAT 5** | 8051 (AT89S52) | 10/08/2026 | Hardware Timer & Interrupt Timing (PWM, Wave, Stepper) | - [TASK5A](8051/CAT5/TASK5A/): Hardware Timer0 1 ms tick & 1 s LED toggle<br>- [TASK5B.1](8051/CAT5/TASK5B/TASK5B.1/): Software PWM LED fading (0-100-0%)<br>- [TASK5B.2](8051/CAT5/TASK5B/TASK5B.2/): Square wave pulse generator (1 kHz & 2 kHz)<br>- [TASK5B.3](8051/CAT5/TASK5B/TASK5B.3/): Multi-tone sweep generator (100 Hz - 5 kHz)<br>- [TASK5C](8051/CAT5/TASK5C/): Stepper motor 4-phase commutation controller | [8051/CAT5](8051/CAT5/) |
| **CAT 6** | 8051 (AT89S52) | 17/08/2026 | UART Driver and Serial Debugging | - [TASK6A](8051/CAT6/TASK6A/): Continuous string transmitter ('Hello from 8051')<br>- [TASK6B](8051/CAT6/TASK6B/): Interactive full-duplex serial character echo console | [8051/CAT6](8051/CAT6/) |
| **CAT 7** | 8051 (AT89S52) | 24/08/2026 | 16x2 LCD Driver Development & Dynamic Display Control | - [TASK7A](8051/CAT7/TASK7A/): 4-bit HD44780 driver & static text banner<br>- [TASK7B](8051/CAT7/TASK7B/): DDRAM positioning (lcd_goto) & dynamic telemetry counter<br>- [TASK7C](8051/CAT7/TASK7C/): Keypad 2/8/4/6 interactive cursor navigation | [8051/CAT7](8051/CAT7/) |
| **CAT 8** | STM32 Blue Pill (STM32F103C8T6) | 18/09/2026 | STM32 GPIO Bring-Up and Switch-Controlled LED | - [TASK8A](STM32/CAT8/TASK8A/): GPIO input/output level tracking (LED follows switch)<br>- [TASK8B](STM32/CAT8/TASK8B/): Software debounced toggle control<br>- [TASK8C](STM32/CAT8/TASK8C/): Non-blocking Short press (<1s) vs Long press (>=1s) blink mode | [STM32/CAT8](STM32/CAT8/) |
| **CAT 9** | STM32 Blue Pill (STM32F103C8T6) | 28/09/2026 | STM32 UART Command Controlled LED | - [TASK9A](STM32/CAT9/TASK9A/): USART1 continuous heartbeat & echo console<br>- [TASK9B](STM32/CAT9/TASK9B/): String command parser ('LED ON', 'LED OFF', 'LED TOGGLE') | [STM32/CAT9](STM32/CAT9/) |
| **CAT 10** | STM32 Blue Pill (STM32F103C8T6) + Wemos D1 Mini (ESP8266) | 12/10/2026 | STM32–Wemos Wi-Fi Modem Interface Using AT Commands | - [TASK10A](STM32/CAT10/TASK10A/): STM32 and Wemos UART Communication<br>- [TASK10B](STM32/CAT10/TASK10B/): ESP8266 AT Command Interface<br>- [TASK10C](STM32/CAT10/TASK10C/): Wi-Fi Station Mode and Network Connectivity | [STM32/CAT10](STM32/CAT10/) |
| **CAT 11** | STM32 Blue Pill (STM32F103C8T6) + Wemos D1 Mini (ESP8266) | 14/10/2026 | HTTP Server - STM32–Wemos Wi-Fi Modem Using AT Commands | - [TASK11A](STM32/CAT11/TASK11A/): TCP Server Setup, IP Retrieval and +IPD Reception<br>- [TASK11B](STM32/CAT11/TASK11B/): Dynamic HTTP Webpage and Node-RED Integration | [STM32/CAT11](STM32/CAT11/) |
| **CAT 12** | ST NUCLEO-F401RE (STM32F401RET6, ARM Cortex-M4) | 23/10/2026 | STM32F401RE Cortex-M4: GPIO and User Input Programming | - [TASK12A](STM32/CAT12/TASK12A/): On-board LED Bring-Up (1 Hz blink, PA5)<br>- [TASK12B](STM32/CAT12/TASK12B/): Push-button (B1/PC13) debounced state toggle<br>- [TASK12C](STM32/CAT12/TASK12C/): Short-press vs Long-press event discrimination | [STM32/CAT12](STM32/CAT12/) |
| **CAT 13** | STM32 + BME280 + ESP8266 | 02/11/2026 | Cloud IoT Telemetry - BME280 + ESP8266 MQTT Publisher | - [TASK13](STM32/CAT13/TASK13/): Publishes environmental JSON telemetry to MQTT broker (broker.hivemq.com) | [STM32/CAT13](STM32/CAT13/) |
| **CAT 14** | STM32 Blue Pill (STM32F103C8T6) | 09/11/2026 |  MQTT Client Publishing and Node-RED Integration. | - [TASK14](STM32/CAT14/TASK14/):  MQTT Client Publishing and Node-RED Integration. | [STM32/CAT14](STM32/CAT14/) |
| **CAT 15** | STM32 NUCLEO-F401RE (ARM Cortex-M4) + BME280 + ESP8266 | 05/11/2026 | Sensor vs Chennai Weather Intelligence & Recommendations | - [TASK15](STM32/CAT15/TASK15/): BME280 I2C & ESP8266 MQTT telemetry, OpenWeather API comparison, Clothes Drying Estimator & Node-RED dashboard | [STM32/CAT15](STM32/CAT15/README.md) |
