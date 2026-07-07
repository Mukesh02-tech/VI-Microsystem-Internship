#include <reg51.h>
sbit swit1=P0^0;
sbit swit2=P0^1;
sbit swit3=P0^2;
sbit swit4=P0^3;
sbit led1=P0^4;
sbit led2=P0^5;
sbit led3=P0^6;
sbit led4=P0^7;
void delay(k)
{
	int i,j;
	for (i=0;i<k;i++)
		for (j=0;j<112;j++);
}

void main()
{
		led1=0;
		led2=0;
		led3=0;
		led4=0;
		while(1)
		{
			if(swit1==1)
			{
				led1=1;
			}
			else
				led1=0;
			if(swit2==1)
			{
				led2=1;
			}
			else
				led2=0;
			if(swit3==1)
			{
				led3=1;
			}
			else
				led3=0;
			if(swit4==1)
			{
				led4=1;
			}
			else
				led4=0;
		}
}