#include <reg51.h>

/*
 * Task 5B.3: Dual-Tone / Frequency Sweep Pulse Generator (100 Hz - 5 kHz)
 * Student: Yazhini J E (25011102119)
 * Target: AT89S52 @ 11.0592 MHz
 */

sbit TONE_OUT = P1^2;

// Frequency reload table for 100 Hz, 500 Hz, 1 kHz, 2.5 kHz, 5 kHz
code unsigned int reload_table[] = {
    60928, // 100 Hz (5 ms half-period)
    64614, // 500 Hz (1 ms half-period)
    65075, // 1 kHz (500 us half-period)
    65352, // 2.5 kHz (200 us half-period)
    65444  // 5 kHz (100 us half-period)
};

unsigned char tone_idx = 0;
unsigned int duration_counter = 0;

void timer0_isr(void) interrupt 1 {
    unsigned int reload = reload_table[tone_idx];
    TH0 = (unsigned char)(reload >> 8);
    TL0 = (unsigned char)(reload & 0xFF);
    TONE_OUT = !TONE_OUT;

    duration_counter++;
    if (duration_counter >= 1000) { // Tone switch interval
        duration_counter = 0;
        tone_idx++;
        if (tone_idx >= 5) {
            tone_idx = 0;
        }
    }
}

void main(void) {
    TMOD = 0x01; // Timer0 Mode 1 (16-bit)
    TH0 = (unsigned char)(reload_table[0] >> 8);
    TL0 = (unsigned char)(reload_table[0] & 0xFF);
    ET0 = 1;
    EA = 1;
    TR0 = 1;

    while (1) {
        // Continuous tone sweeping
    }
}
