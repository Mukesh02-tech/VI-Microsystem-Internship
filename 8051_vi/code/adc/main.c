#include <reg51.h>
#include "i2c.h"
#include <stdio.h>

char buffer[30];
int ch0, ch1, ch2, ch3;
float v=0;
void UART_Init()
{
	TMOD = 0x20;		// Timer 1, mode 2
	TH1 = 0xFD;			// 9600 baud @ 11.0592MHz
	SCON = 0x50;		// Mode 1, enable reception
	TR1 = 1;			// Start timer 1
}

void Transmit_data(char tx_data)
{
	SBUF = tx_data;
	while (TI == 0);
	TI = 0;
}

void String(char *str)
{
	int i;
	for (i = 0; str[i] != 0; i++)
		Transmit_data(str[i]);
}

void main()
{
	UART_Init();
	while (1)
	{
		IE = 0x90;	// Optional: Enable interrupt
		ch0 = i2c_Readch0();
		msDelay(200);
    v = ch0*(5.0/255.0);
		sprintf(buffer, "ch0: %d\r\n", ch0);
		String(buffer);
		sprintf(buffer, "ch0: %.2f\r\n", v);
		String(buffer);
	}
}