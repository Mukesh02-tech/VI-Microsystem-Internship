#include <reg51.h>	/* Include x51 header file */
sbit LED = P1^5;	/* set LED on port1 */ 

void Ext_int_Init()				
{
	EA  = 1;	/* Enable global interrupt */
	EX1 = 1;      	/* Enable Ext. interrupt0 */
	IT1 = 1;      	/* Select Ext. interrupt0 on falling edge */
}
											
void External1_ISR() interrupt 2
{
	LED = ~LED;	/* Toggle pin on falling edge on INT0 pin */
} 

void main()
{
	Ext_int_Init(); /* Call initialize */
	while(1);
}