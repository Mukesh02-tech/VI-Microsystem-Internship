#include <reg51.h>    // Header for 8051
sbit q1 = P1^1; 
sbit q5 = P1^0; 
// Delay function (approximate)
void delay(k)  /* Delay for msec. (here Xtal freq. is 11.0592 MHz) */
{
	int i,j;
	for (i=0;i<k;i++)
		for (j=0;j<112;j++);
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

void main(void) {
    unsigned char i;
    while(1) {
			q1 = 1;
			q5 = 0;
        for(i = 0; i < 10; i++) {
            P2 = seg_pattern[i];   // Output pattern to 7-segment
            delay(1000);        // 1-second delay
        }
    }
}