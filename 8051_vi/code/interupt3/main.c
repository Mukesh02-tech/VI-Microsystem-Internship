#include <reg51.h>

#define MAX_LENGTH 20

char buffer[MAX_LENGTH];
unsigned char index = 0;

void UART_Init()
{
    TMOD = 0x20;     // Timer1, Mode 2 (Auto-reload)
    TH1 = 0xFD;      // Baud rate 9600 for 11.0592 MHz
    SCON = 0x50;     // Serial Mode 1, 8-bit UART, REN enabled
    TR1 = 1;         // Start Timer1
    EA = 1;          // Enable global interrupt
    ES = 1;          // Enable serial interrupt
}

void UART_TxChar(char ch)
{
    SBUF = ch;
    while (TI == 0);
    TI = 0;
}

void UART_PrintString(char *str)
{
    while (*str)
        UART_TxChar(*str++);
}

void Serial_ISR() interrupt 4
{
    char ch = SBUF;
    RI = 0;

    if (ch == '! ')   // End of string (custom terminator)
    {
        buffer[index] = '\0';       // Null-terminate string
        UART_PrintString("\r\nReceived: ");
        UART_PrintString(buffer);
        UART_TxChar('\n');
        index = 0;                  // Reset index
    }
    else if (index < MAX_LENGTH - 1)
    {
        buffer[index++] = ch;       // Store received char
    }
}

void main()
{
    UART_Init();
    UART_PrintString("Send a string ending with #: \n");
    while (1);
}