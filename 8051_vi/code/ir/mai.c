#include <reg51.h>
#include <string.h>
#include "stdio.h"
#define lcd_data P2

sbit rs=P1^0;
sbit rw=P1^1;
sbit en=P1^2;

sbit LED1 = P1^5; 
sbit ir=P3^2;
int count = 0;

void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);
void lcd_delay();
void delay(k)  /* Delay for msec. (here Xtal freq. is 11.0592 MHz) */
{
	int i,j;
	for (i=0;i<k;i++)
		for (j=0;j<112;j++);
}
void lcd_init()
{
    cmd(0x38);
    cmd(0x0e);
    cmd(0x01);
    cmd(0x06);
    cmd(0x0c);
    cmd(0x80);
}

void cmd(unsigned char a)
{
    lcd_data=a;
    rs=0;
    rw=0;
    en=1;
    lcd_delay();
    en=0;
}

void dat(unsigned char b)
{
    lcd_data=b;
    rs=1;
    rw=0;
    en=1;
    lcd_delay();
    en=0;
}

void show(unsigned char *s)
{
    while(*s) {
        dat(*s++);
    }
}

void lcd_delay()
{
    unsigned int lcd_delay;
    for(lcd_delay=0;lcd_delay<=6000;lcd_delay++);
}

int main()
{
    unsigned int j,i;
		char buffer[5];
    lcd_init();

	while(1)
		
	{

   
if(ir==0)
{
  LED1=1;
	count +=1;
  cmd(0x8d);
	sprintf(buffer,"%d",count);
  show(buffer);
	while(ir==0);
  delay(20);
}
else
{
LED1=0;
}

}
	}