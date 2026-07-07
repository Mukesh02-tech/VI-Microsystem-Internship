#include <reg51.h>

sbit LED1 = P1^5;       
sbit LED2 = P1^6;    

sbit SWITCH1 = P1^3;  
sbit SWITCH2 = P1^4;    

void main()
{
    LED1 = 0;    // Initially OFF
    LED2 = 0;
		int a=1
    while (1)
    {
     
        if (SWITCH1 == 0 && a==1)    
        {
            LED1 = 1; 
						a=0;
        }
				if(SWITCH1==0 && a==0)
				{
					LED1=0;
					a=1;
				}
        
    }
}