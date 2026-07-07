#include <reg51.h>
#include <stdio.h>

#define sound_velocity 34300       // in cm/s
#define period_in_us 1e-6
#define Clock_period (1.085 * period_in_us)

#define lcd_data P2

sbit rs = P1^0;
sbit rw = P1^1;
sbit en = P1^2;

sbit Trigger_pin = P3^5;
sbit Echo_pin = P3^7;  

void delay(unsigned int ms);
void Delay_us();
void init_timer();
void send_trigger_pulse();
void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);
void lcd_delay();

void lcd_init()
{
    cmd(0x38);  // 2 lines, 5x7 matrix
    cmd(0x0e);  // Display ON, cursor ON
    cmd(0x01);  // Clear screen
    cmd(0x06);  // Increment cursor
    cmd(0x0c);  // Display ON, cursor OFF
    cmd(0x80);  // Cursor to first line
}

void cmd(unsigned char a)
{
    lcd_data = a;
    rs = 0;
    rw = 0;
    en = 1;
    lcd_delay();
    en = 0;
}

void dat(unsigned char b)
{
    lcd_data = b;
    rs = 1;
    rw = 0;
    en = 1;
    lcd_delay();
    en = 0;
}

void show(unsigned char *s)
{
    while (*s) {
        dat(*s++);
    }
}

void lcd_delay()
{
    unsigned int i;
    for (i = 0; i < 6000; i++);
}

void delay(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 1275; j++);
}

void Delay_us()
{
    TL0 = 0xF5;
    TH0 = 0xFF;
    TR0 = 1;
    while (TF0 == 0);
    TR0 = 0;
    TF0 = 0;
}

void init_timer()
{
    TMOD = 0x01;  // Timer0 Mode 1
    TF0 = 0;
    TR0 = 0;
}

void send_trigger_pulse()
{
    Trigger_pin = 1;
    Delay_us();  // ~10us pulse
    Trigger_pin = 0;
}

void main()
{
    float time_in_seconds, distance_cm;
    char distance_str[16];

    lcd_init();
    cmd(0x80);
    show("Distance:");

    init_timer();

    while (1)
    {
        send_trigger_pulse();
        while (!Echo_pin);  // Wait for echo high
        TR0 = 1;
        while (Echo_pin && !TF0);  // Wait for echo low or timeout
        TR0 = 0;

        // Read timer and reset
        time_in_seconds = (TH0 << 8 | TL0) * Clock_period;
        TH0 = 0;
        TL0 = 0;
        TF0 = 0;

        // Calculate distance
        distance_cm = (time_in_seconds * sound_velocity) / 2.0;

        sprintf(distance_str, "%.2f cm", distance_cm);

        cmd(0xc0);  // Second line
        show(distance_str);

        delay(100);
    }
}