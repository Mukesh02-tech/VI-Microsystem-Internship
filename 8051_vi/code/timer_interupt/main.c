#include<reg51.h>		/* Include x51 header file */
sbit test1 = P0^4;		/* set test pin0 of port1 */
sbit test2= P0^5;		
sbit test3= P0^6;		
sbit test4= P0^7;		
void Timer_init()
{
	TMOD = 0x01;		/* Timer0 mode1 */
	TH0 = 0x3C;		/* 50ms timer value */
	TL0 = 0x00;      
	TR0 = 1;  	      	/* Start timer0 */
}

void Timer0_ISR() interrupt 1	/* Timer0 interrupt service routine (ISR) */
{
	test1 = ~test1;  		/* Toggle port pin */
	test2=~test2;
	test3=~test3;
	test4=~test4;
	TH0 = 0x4C;      	/* 50ms timer value */
	TL0 = 0x00;      
}

int main(void)
{
	EA  = 1;         	/* Enable global interrupt */
	ET0 = 1;         	/* Enable timer0 interrupt */
	Timer_init();
  	while(1);
}