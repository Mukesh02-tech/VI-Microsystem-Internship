#include <reg51.h>

sbit test = P0^6;  // LED connected to P1.0

void Timer0_Delay_50ms()
{
    TMOD = 0x01;      // Timer0, Mode 1 (16-bit)
    TH0 = 0x4C;       // Load high byte
    TL0 = 0x00;       // Load low byte
    TF0 = 0;          // Clear overflow flag
    TR0 = 1;          // Start Timer0

    while (TF0 == 0); // Wait until overflow

    TR0 = 0;          // Stop Timer0
    TF0 = 0;          // Clear overflow flag again
}

void main()
{
    while (1)
    {
        test = ~test;        // Toggle P1.0
        Timer0_Delay_50ms(); // Delay of 50 ms
    }
}