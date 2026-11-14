EXPERIMENT DETAILS
EXP: CONTINUOUS ASSESSMENT 12
DATE: 14/10/2026
NAME OF EXP: STM32F401RE Cortex-M4: GPIO and User Input Programming
HARDWARE SETUP / PLATFORM: STM32F401RB development board (physical board unconfirmed) + STM32F401RBT6 + GPIO LED and input + STM32CubeMX (MDK-ARM project)
TASK 12C : Short-Press and Long-Press Detection

1. Circuit Diagram
Service the half-second blink interval while continuing to read the switch to demonstrate 12C with the shown signals.

* Microcontroller / Board: STM32F401RB development board (physical board unconfirmed) + STM32F401RBT6.
* GPIO / Peripheral pins: PC13 / GPIOC GPIO_PIN_13 -> B1 button to GND, pull-up; PA5 / GPIOA GPIO_PIN_5 -> LED + 330 ohm to GND.
* Clock: HSI 16 MHz PLL to 84 MHz.
* External components / Peripheral: B1 button to GND, pull-up; LED + 330 ohm to GND.
* Power Supply: 3.3 V board logic, common ground; board regulator / USB supply.

![Circuit Diagram](circuit.png)

2. Core Logic / Pseudocode / Code Base
Working Principle: This USER CODE measures the interval between stable PC13 press and release events. It starts a timed PA5 blink after a long press and stops blinking with a toggle after a short press.

Pseudocode:

1. Qualify the button level with elapsed ticks.
2. Save started on a low input event.
3. Use a one-second threshold on release.
4. Service the half-second blink interval while continuing to read the switch.

Code Base:
The program is written in Embedded C using STM32 HAL (STM32CubeMX).

* `main.h` provides the project HAL declarations in this program.
* `HAL_GetTick()` returns the millisecond time used for event comparisons here.
* `HAL_GPIO_ReadPin()` reads the application switch level here.
* `HAL_GPIO_TogglePin()` changes the stored LED output state here.

3. Inference
The intended behavior combines press classification with a separate blink timer. PA5 and PC13 GPIO setup has been added; hardware testing remains pending.

Configuration correction: PA5 push-pull output, initial LOW, PC13 input with pull-up (active LOW assumed). The existing STM32F401RB target is retained until the actual board is confirmed; if using NUCLEO-F401RE, migrate the project to that target in CubeMX/Keil. No target build or hardware test performed.
