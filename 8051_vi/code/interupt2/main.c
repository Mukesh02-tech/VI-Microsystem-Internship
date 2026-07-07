#include <reg51.h>		/* Include x51 header file */
sbit LED1 = P0^5;
sbit LED2=P0^6;
sbit LED3 = P0^4;
sbit LED4=P0^7;
void Ext_int_Init()				
{
	EA = 1;		/* Enable global interrupts */
	ES = 1;		/* Enable serial interrupt */			
}

void UART_Init()
{
	TMOD = 0x20;	/* Timer1 Mode 2: 8-bit auto-reload */
	TH1 = 0xFD;	/* 9600 baud rate at 11.0592 MHz */
	SCON = 0x50;	/* Serial mode 1, REN enabled */
	TR1 = 1;	/* Start Timer1 */
}

void Serial_ISR() interrupt 4
{
	char received_char = SBUF;	/* Read received byte */

	if (received_char == '3') {
		LED1=1;
		LED2=1;
		LED3=1;
		LED4=1;
	
	} else if (received_char == '4') {
		LED1=0;
		LED2=0;
		LED3=0;
		LED4=0;
	}

	RI = 0;	// Clear receive interrupt flag
}

void main()
{
	LED1=0;
	LED3=0;
	LED4=0;
	LED2=0;
	Ext_int_Init();		/* Enable serial interrupts */
	UART_Init();		/* Initialize UART */
	while(1);		/* Infinite loop, wait for UART input */
}\