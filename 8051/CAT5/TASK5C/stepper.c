#include <reg51.h>

/*
 * Task 5C: Stepper Motor Commutation Controller (ULN2003 Driver)
 * Student: Yazhini J E (25011102119)
 * Target: AT89S52 @ 11.0592 MHz
 */

// 4-Phase Full-Step drive sequence: A, B, C, D on P2.0 - P2.3
code unsigned char step_seq[4] = {0x09, 0x0C, 0x06, 0x03};

unsigned char step_idx = 0;
unsigned int timer_ticks = 0;

void timer0_isr(void) interrupt 1 {
    // 1 ms periodic tick: TH0=0xFC, TL0=0x66
    TH0 = 0xFC;
    TL0 = 0x66;

    timer_ticks++;
    if (timer_ticks >= 10) { // 10 ms per step -> 100 steps/sec
        timer_ticks = 0;
        P2 = (P2 & 0xF0) | step_seq[step_idx];
        step_idx = (step_idx + 1) % 4;
    }
}

void main(void) {
    TMOD = 0x01; // Timer0 Mode 1
    TH0 = 0xFC;
    TL0 = 0x66;
    ET0 = 1;
    EA = 1;
    TR0 = 1;

    while (1) {
        // Continuous commutation paced by Timer0 ISR
    }
}
