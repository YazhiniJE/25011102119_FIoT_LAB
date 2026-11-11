#include <reg51.h>

/*
 * Task 5B.2: Square Wave Generation (1 kHz and 2 kHz Frequencies)
 * Student: Yazhini J E (25011102119)
 * Target: AT89S52 @ 11.0592 MHz
 */

sbit WAVE_OUT = P1^1;
sbit FREQ_SEL = P3^2; // Switch to select 1 kHz (high) or 2 kHz (low)

// Half-period counts:
// 1 kHz = 1000 us period -> 500 us half-period = 461 machine cycles (65536 - 461 = 0xFE33)
// 2 kHz = 500 us period -> 250 us half-period = 230 machine cycles (65536 - 230 = 0xFF1A)

void timer0_isr(void) interrupt 1 {
    if (FREQ_SEL == 1) {
        // 1 kHz: 500 us half-period
        TH0 = 0xFE;
        TL0 = 0x33;
    } else {
        // 2 kHz: 250 us half-period
        TH0 = 0xFF;
        TL0 = 0x1A;
    }
    WAVE_OUT = !WAVE_OUT;
}

void main(void) {
    FREQ_SEL = 1; // Pull-up mode
    TMOD = 0x01;  // Timer0 Mode 1 (16-bit)
    TH0 = 0xFE;
    TL0 = 0x33;
    ET0 = 1;      // Enable Timer0 interrupt
    EA = 1;       // Enable Global interrupts
    TR0 = 1;      // Start Timer0

    while (1) {
        // Continuous square wave generation
    }
}
