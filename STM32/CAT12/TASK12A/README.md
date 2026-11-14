# TASK12A – On-board LED Bring-Up (Bare-Metal Blink)

## Experiment Details

**EXP:** CONTINUOUS ASSESSMENT 12 – TASK A
**DATE:** 23/10/2026
**NAME:** STM32F401RE Cortex-M4: GPIO and User Input Programming
**PLATFORM:** ST NUCLEO-F401RE (STM32F401RET6, ARM Cortex-M4 @ 84 MHz)

## Objective

Configure PA5 as a GPIO output and toggle the on-board Green LED LD2 at 1 Hz
using non-blocking SysTick timing.

## Working Principle

The STM32F401RE clock is configured to 84 MHz. PA5 is set as push-pull output.
In the main loop, `HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5)` is called every 500 ms
using `HAL_GetTick()` for non-blocking timing, producing a 1 Hz blink.

## Circuit

- `PA5` : GPIO Output (LD2 Green LED)
- Powered via ST-LINK USB

## Project Files

- `Core/Src/main.c` – Clock config, GPIO init, non-blocking LED toggle
- `Led-Blink.ioc` – STM32CubeMX configuration
