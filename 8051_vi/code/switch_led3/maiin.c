#include <reg51.h>

sbit LED1 = P1^5;       
sbit LED2 = P1^6;    

sbit SWITCH1 = P1^3;  
sbit SWITCH2 = P1^4;    
int flag =0;
void delay(k)  /* Delay for msec. (here Xtal freq. is 11.0592 MHz) */
{
	int i,j;
	for (i=0;i<k;i++)
		for (j=0;j<112;j++);
}
void main()
{
    LED1 = 0;    // Initially OFF
    LED2 = 0;

    while (1)
    {
     
        if (SWITCH1 == 0)    
        {

           flag= !flag;   
            
         while(1)
            {
                  
              if (SWITCH1 == 1)
                {
                 delay(20) ;
                 break;

                } 
            }
					
        }
         LED1 = flag?1:0;


    }
}