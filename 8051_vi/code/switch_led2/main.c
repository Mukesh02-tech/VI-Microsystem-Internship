#include <reg51.h>

sbit LED1 = P0^5;       
sbit LED2 = P0^6;    

sbit SWITCH1 = P1^6;  
sbit SWITCH2 = P1^7;    

void main()
{
    LED1 = 0;    // Initially OFF
    LED2 = 0;

    while (1)
    {
     
        if (SWITCH2 == 0)    
        {
            LED1 = 1; 
						
        }
				if(SWITCH2==0)
				{
					LED1=0;
				}
        
    }
}