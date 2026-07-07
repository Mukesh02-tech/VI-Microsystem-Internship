#include <reg51.h>	/* Include x51 header file */
sbit LED = P1^5;	/* set LED on port1 */ 
int f=0;
void delay(k)  /* Delay for msec. (here Xtal freq. is 11.0592 MHz) */
{
	int i,j;
	for (i=0;i<k;i++)
		for (j=0;j<112;j++);
}
void Ext_int_Init()				
{
	EA  = 1;	/* Enable global interrupt */
	EX0 = 1;      	/* Enable Ext. interrupt0 */
	IT0 = 1;      	/* Select Ext. interrupt0 on falling edge */
}
											
void External0_ISR() interrupt 0
{	/* Toggle pin on falling edge on INT0 pin */
	f=1;
} 

void main()
{
	Ext_int_Init(); /* Call initialize */
	
	while(1)
	{
		if(f==1)
		{
			LED=1;
			delay(3000);
			f=0;
		}
		LED=1;
		delay(100);
		LED=0;
		delay(100);
	}
}