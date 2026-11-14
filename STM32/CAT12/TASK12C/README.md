# TASK12C – Short-Press and Long-Press Detection

## Experiment Details

**EXP:** CONTINUOUS ASSESSMENT 12 – TASK C
**DATE:** 23/10/2026
**NAME:** STM32F401RE Cortex-M4: GPIO and User Input Programming
**PLATFORM:** ST NUCLEO-F401RE (STM32F401RET6, ARM Cortex-M4 @ 84 MHz)

## Objective

Discriminate between short press (30–500 ms) and long press (≥500 ms) on the
on-board button (PC13) to control two distinct LED (PA5) behaviours.

## Working Principle

Button press duration is measured using `HAL_GetTick()` timestamps.
- **Short press (30–500 ms):** Toggles and latches LED state.
- **Long press (≥500 ms):** Enters rapid auto-blink mode (200 ms period).
  A subsequent short press cancels blink mode and restores manual control.

## Project Files

- `Core/Src/main.c` – Duration classifier, non-blocking blink scheduler
- `Led-Blink.ioc` – STM32CubeMX configuration
