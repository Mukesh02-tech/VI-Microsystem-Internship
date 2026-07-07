#include<reg51.h>
sbit LED1 = P1^5;       
sbit LED2 = P1^6;  

void delay(k)  /* Delay for msec. (here Xtal freq. is 11.0592 MHz) */
{
	int i,j;
	for (i=0;i<k;i++)
		for (j=0;j<112;j++);
}

void main()
{ 
    while(1) 
    { 
        LED1=1;
        delay(100);
       LED1=0;
        delay(100);
    } 
}