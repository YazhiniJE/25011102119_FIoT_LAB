EXPERIMENT DETAILS
EXP: CONTINUOUS ASSESSMENT 12
DATE: 14/10/2026
NAME OF EXP: STM32F401RE Cortex-M4: GPIO and User Input Programming
HARDWARE SETUP / PLATFORM: STM32F401RB development board (physical board unconfirmed) + STM32F401RBT6 + GPIO LED and input + STM32CubeMX (MDK-ARM project)
TASK 12A : On-board LED Bring-Up

1. Circuit Diagram
Repeat the toggle to demonstrate 12A with the shown signals.

* Microcontroller / Board: STM32F401RB development board (physical board unconfirmed) + STM32F401RBT6.
* GPIO / Peripheral pins: PA5 / GPIOA GPIO_PIN_5 -> LED + 330 ohm to GND.
* Clock: HSI 16 MHz PLL to 84 MHz.
* External components / Peripheral: LED + 330 ohm to GND.
* Power Supply: 3.3 V board logic, common ground; board regulator / USB supply.

![Circuit Diagram](circuit.png)

2. Core Logic / Pseudocode / Code Base
Working Principle: The prepared USER CODE toggles PA5 and waits five hundred milliseconds. PA5 is now initialized as a push-pull output.

Pseudocode:

1. Initialize HAL and the original clock.
2. Run the generated GPIO initialization.
3. Toggle PA5 and wait half a second.
4. Repeat the toggle.

Code Base:
The program is written in Embedded C using STM32 HAL (STM32CubeMX).

* `main.h` provides the project HAL declarations in this program.
* `HAL_GPIO_TogglePin()` changes the stored LED output state here.
* `HAL_Delay()` waits for the programmed millisecond interval here.

3. Inference
PA5 is configured as an output; target build and LED behavior remain to be tested.

Configuration correction: PA5 push-pull output, initial LOW. The existing STM32F401RB target is retained until the actual board is confirmed; if using NUCLEO-F401RE, migrate the project to that target in CubeMX/Keil. No target build or hardware test performed.
