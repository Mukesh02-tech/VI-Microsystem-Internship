#include <reg51.h>		/* Include x51 header file */
#include "stdio.h"
sbit swit1=P1^3;
sbit swit2=P1^4;
sbit led1=P1^5;
sbit led2=P1^6;
char buffer[20];	
int cnt=1;


void UART_Init()
{
	TMOD = 0x20;		/* Timer 1, 8-bit auto reload mode */
	TH1 = 0xFD;		/* Load value for 9600 baud rate */
	SCON = 0x50;		/* Mode 1, reception enable */
	TR1 = 1;		/* Start timer 1 */
}

void Transmit_data(char tx_data)
{
	SBUF = tx_data;		/* Load char in SBUF register */
	while (TI==0);		/* Wait until stop bit transmit */
	TI = 0;			/* Clear TI flag */
}
void delay(k)  /* Delay for msec. (here Xtal freq. is 11.0592 MHz) */
{
	int i,j;
	for (i=0;i<k;i++)
		for (j=0;j<112;j++);
}
void String(char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)
	{
		Transmit_data(str[i]);	
	}
}	

void main()
{
	UART_Init();		
	
	
	while(1)
	{
		if(swit1==0)
		{
			delay(20);
				if(swit1==0)
				{
					cnt=cnt+1;
					sprintf(buffer, "Int: %d", cnt);
					String(buffer);       
					String("\n");
					while(swit1==0)
						delay(20);
				}
			}
		if(swit2==0)
		{
			delay(20); 
				if(swit2==0)
				{
					cnt=cnt-1;
					sprintf(buffer, "Int: %d", cnt);
					String(buffer);       
					String("\n");
					while(swit2==0)
						delay(20);
				}
			}
		led1=0;
		led2=0;
		if(cnt>=6)
			led1=1;
		else
			led1=0;
		if(cnt>=0)
			led2=1;			
	}
}