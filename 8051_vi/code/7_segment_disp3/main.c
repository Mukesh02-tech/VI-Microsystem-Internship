#include <reg51.h>    // Header for 8051
sbit q1 = P1 ^ 1;
sbit q5 = P1 ^ 0;
int i, one, ten;
// Delay function (approximate)
void delay(k)  /* Delay for msec. (here Xtal freq. is 11.0592 MHz) */
{
  int i, j;
  for (i = 0; i < k; i++)
    for (j = 0; j < 112; j++);
}
unsigned int ms_count = 0;      // Millisecond counter
unsigned int last_time = 0;     // Stores last execution time

void Timer0_ISR(void) interrupt 1  // Timer0 overflow interrupt
{
  TH0 = 0xFC;  // Reload for 1ms
  TL0 = 0x66;
  ms_count++;  // Increment every 1ms
}

void Timer0_Init(void)
{
  TMOD |= 0x01;     // Timer0 Mode 1 (16-bit)
  TH0 = 0xFC;
  TL0 = 0x66;
  ET0 = 1;          // Enable Timer0 interrupt
  EA = 1;           // Enable global interrupts
  TR0 = 1;          // Start Timer0
}

unsigned char seg_pattern[10] = {
  0x3F, // 0 ? 0011 1111
  0x06, // 1 ? 0000 0110
  0x5B, // 2 ? 0101 1011
  0x4F, // 3 ? 0100 1111
  0x66, // 4 ? 0110 0110
  0x6D, // 5 ? 0110 1101
  0x7D, // 6 ? 0111 1101
  0x07, // 7 ? 0000 0111
  0x7F, // 8 ? 0111 1111
  0x6F  // 9 ? 0110 1111
};

void main(void)
{
  unsigned char i;
	int f=1;
  while (f==1)
  {
    Timer0_Init();

    if (ms_count - last_time >= 100)
    {
      last_time = ms_count;

      if (i < 100)
      {
        one = i / 10;
        ten = i % 10;
        i += 1;
      }


    }


    q1 = 0;
    q5 = 1;
    P2 = seg_pattern[one];

    delay(10);
    q1 = 1;
    q5 = 0;
    P2 = seg_pattern[ten];
    delay(10);
		if(i==99)
			f=0;
  }
	while(f==0)
	{
		 Timer0_Init();

    if (ms_count - last_time >= 100)
    {
      last_time = ms_count;

      if (i >0)
      {
        one = i / 10;
        ten = i % 10;
        i -= 1;
      }


    }


    q1 = 0;
    q5 = 1;
    P2 = seg_pattern[one];

    delay(10);
    q1 = 1;
    q5 = 0;
    P2 = seg_pattern[ten];
    delay(10);
		if(i==1)
			f=1;
		
	}
} 