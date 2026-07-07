#include <reg51.h>
sbit swit=P1^3;
sbit led=P1^5;
void delay(k)
{
	int i,j;
	for (i=0;i<k;i++)
		for (j=0;j<112;j++);
}

void main()
{
		led=0;
		while(1)
		{
			if(swit==0)
			{
				
				led=1;
				delay(100);
				led=0;
				delay(100);
			}
			else
				led=0;
				delay(50);
		}
}