#include <reg51.h>			/* Include x51 header file */
sbit test = P0^6;			/* set test pin 0 of port1 */ 

void timer_delay()			/* Timer0 delay function */
{
	TH0 = 0xE3;			/* Load 8-bit in TH0 (here Timer0 used) */
	TL0 = 0x14;			/* Load 5-bit in TL0 */
	TR0 = 1;			/* Start timer0 */
	while(TF0 == 0);		/* Wait until timer0 flag set */
	TR0 = 0;			/* Stop timer0 */
	TF0 = 0;			/* Clear timer0 flag */
}
void main()
{
	TMOD = 0x00;			/* Timer0/1 mode0 (13-bit timer mode) */
	while(1)
	{
		test = ~test;		/* Toggle test pin */
		timer_delay();		/* Call timer0 delay */
	}
}