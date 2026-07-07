#include<reg51.h>
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
        P1=0x40; 
        delay(100);
        P1=0x00; 
        delay(100);
				P1=0x20; 
        delay(100);
        P1=0x00; 
        delay(100);
    } 
}