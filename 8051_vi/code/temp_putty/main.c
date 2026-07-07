#include <reg51.h>		/* Include x51 header file */
#include "stdio.h"

char buffer[20];	
int value = 1234;
float temp = 36.57;

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
	String("\n test");	
  String("\n");
	sprintf(buffer, "Int: %d", value);
	String(buffer);       
	String("\n");
	sprintf(buffer, "Float: %.2f", temp);  
	String(buffer);
	
	while(1);
}