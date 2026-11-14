# TASK12B – On-board Switch Control with State Remembrance

## Experiment Details

**EXP:** CONTINUOUS ASSESSMENT 12 – TASK B
**DATE:** 23/10/2026
**NAME:** STM32F401RE Cortex-M4: GPIO and User Input Programming
**PLATFORM:** ST NUCLEO-F401RE (STM32F401RET6, ARM Cortex-M4 @ 84 MHz)

## Objective

Read the on-board Blue User Button (PC13) with debounce filtering and use it to
toggle and latch the Green LED (PA5) state on each valid press.

## Working Principle

PC13 reads HIGH (idle) and LOW (pressed). An edge-detection algorithm detects
falling edges. A 30 ms debounce window filters contact bounce. On a valid release,
`HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5)` latches the new LED state.

## Project Files

- `Core/Src/main.c` – Edge detection, debounce, state latch
- `Led-Blink.ioc` – STM32CubeMX configuration
