#include <reg51.h>

/*
 * Task 5B.1: Software PWM LED Fading using Timer0 Interrupt
 * Student: Yazhini J E (25011102119)
 * Target: AT89S52 @ 11.0592 MHz
 */

sbit LED = P1^0;

unsigned char pwm_counter = 0;
unsigned char duty_cycle = 0;
bit fade_direction = 1; // 1 = brightening, 0 = dimming
unsigned int step_ticks = 0;

void timer0_isr(void) interrupt 1 {
    // 100 us periodic tick for software PWM: TH0=0xFF, TL0=0xA4 @ 11.0592 MHz
    TH0 = 0xFF;
    TL0 = 0xA4;

    pwm_counter++;
    if (pwm_counter >= 100) {
        pwm_counter = 0;
    }

    if (pwm_counter < duty_cycle) {
        LED = 0; // Active-low LED ON
    } else {
        LED = 1; // Active-low LED OFF
    }

    step_ticks++;
    if (step_ticks >= 200) { // Update duty cycle every 20 ms
        step_ticks = 0;
        if (fade_direction) {
            duty_cycle++;
            if (duty_cycle >= 100) {
                fade_direction = 0;
            }
        } else {
            if (duty_cycle > 0) {
                duty_cycle--;
            } else {
                fade_direction = 1;
            }
        }
    }
}

void main(void) {
    TMOD = 0x01; // Timer0 Mode 1 (16-bit)
    TH0 = 0xFF;
    TL0 = 0xA4;
    ET0 = 1;     // Enable Timer0 interrupt
    EA = 1;      // Enable Global interrupts
    TR0 = 1;     // Start Timer0

    while (1) {
        // Main loop idle; PWM handled deterministically in ISR
    }
}
