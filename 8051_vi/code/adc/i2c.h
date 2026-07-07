
#include <intrins.h>
#define  HIGH	     0x01			         // Value representing ON
#define	 LOW	     0x00			         // Value representing OFF
#define  SlvAdr_Wr   0x90					 	// PCF 8591 addresses//write address
#define  SlvAdr_Rd   0x91						//read address


sbit SCLK=P3^4;
sbit SDATA=P3^5;

//Variable declaration
bit initOver    ;                                // Bit set at the end of LCD init
bit DelayOver   ;                                // To flag the end of a set delay
bit F_Clk_Adj   ;
bit F_I2C_Busy  ;
bit F_I2C_NoAck ;
bit F_I2C_Fault ;
//int mode;
unsigned int   msTick_1 = 0 ;
unsigned char  ByteCnt = 0;
unsigned char  tempVal[8];                       		// I2C storage buffer used for write and read
unsigned int adc1,adc2,adc3,adc4;


/*=============================================*/
void SCL_High (void )							 // Raise the SCLK high. But...
{
  SCLK = HIGH;
  
}


void bitDelay (void)							 // For use in clock pulse in I2C routines..
{
  _nop_ ();								 // 10 nop x 0.54 micro = 5.4microsec
  _nop_ ();								 // I2C needs a min of 4.7microsec. Adjust 
  _nop_ ();								 //   suitably for other clocks..
  _nop_ ();
  _nop_ ();
  _nop_ ();
  _nop_ ();
  _nop_ ();
  _nop_ ();
  _nop_ ();
}

/*=============================================*/
void msDelay (int DelayVal)				//DELAY FUNCTION
{
  int j;
  for(j=0;j<1000;j++);
}


/*=============================================*/

unsigned char i2c_RcvByte (void)				 // Recieve one byte from the I2C slave
{
  unsigned char index, input_data ;
  input_data = 0x00;
  for(index = 0; index < 8; index++)  	     // Get 8 bits from the I2C Bus
  {
    input_data <<= 1;		                     // Shift the byte by one bit
    SCLK = HIGH;           			         // Clock the data into the I2C Bus
    bitDelay();
    input_data |= SDATA; 		   	             // Input the data from the I2C Bus
    SCLK = LOW;
    bitDelay();					
  } 
  if ( ByteCnt == 1 )
  {
    SDATA = HIGH;					         // Last byte. No Acknowledge to slave
  }
  else
  {										 
    SDATA = LOW ;							 // Not last byte. Acknowledge the slave.
  }  	 							 
  SCL_High();							         // Clock the Ack state
  bitDelay();
  SCLK = LOW;
  SDATA = HIGH;						         // Restore the Data pin
  bitDelay();
  tempVal[ByteCnt] = input_data;
  return input_data;
}


/*=============================================*/
void i2c_stop (void)
{
  SDATA = LOW;								 // Prepare data pin for Stop..
  SCL_High();								 // Set Clock high 
  bitDelay();								 
  SDATA = HIGH;							 // Stop I2C ( SCLK is High already)
  bitDelay();
  F_I2C_Busy = 0;							 // Release the busy flag.
}

/*=============================================*/
void i2c_WrByte (unsigned char output_data)		 // Write 1 byte to I2C slave 
{
  unsigned char index;
  for(index = 0; index < 8; index++)  	     // Send 8 bits to the I2C Bus
  {
    SDATA = ((output_data & 0x80) ? 1 : 0);	 // Output the data bit to the I2C Bus
    output_data  <<= 1;            		     // Shift the byte by one bit
    bitDelay();								 // for stabilizing the data 
    SCLK = HIGH;   		        		     // Clock the data into the I2C Bus
    bitDelay();
    SCLK = LOW;
    bitDelay();								 // 1 clock pulse completed
  }
  SDATA = HIGH;							     // Data line with Acknowledge bit.
  SCLK = HIGH;   		        			     // Clock the ACK on the I2C Bus
  bitDelay();									 // Wait for peripheral response
  if (SDATA) F_I2C_NoAck = 1;					 // Set NoAck flag if SADAT still high
  SCLK = LOW;									 // Finish ACK procedure
  bitDelay();
}


/*=============================================*/  
void i2c_GoMaster (unsigned char SlvAdr)		 // Start I2C and Address the slave.
{
  F_I2C_Busy = 1;							 // I2C frame is in progress
  F_I2C_NoAck = 0;
  F_I2C_Fault = 0;                            // Clear Flags
  if (!SDATA ) F_I2C_Fault = 1;
  if (!SCLK )  F_I2C_Fault = 1;
  SDATA = LOW;								 // I2C start( SCLK is High already)
  bitDelay();
  SCLK = LOW ;
  bitDelay();                                 // Complete I2C Start.
  i2c_WrByte(SlvAdr) ;                        // Address the slave
}

/*=============================================*/ 
void i2c_clkRun (void)							 // Routine to start the RTC internal updates
{
  i2c_GoMaster (SlvAdr_Wr);	                 // Address of PCF8583 for write
  i2c_WrByte(0x00);							 // Control register address								 
  i2c_WrByte(0x00);							 // Command for Start count
  i2c_stop();
}   
/*=============================================*/
     
 
void i2c_clkFreeze (void)						 // Routine to stop the RTC internal updates
{
  i2c_GoMaster( SlvAdr_Wr);	                 // Address of PCF8583 for write
  i2c_WrByte(0x00);							 // Control register address								 
  i2c_WrByte(0x10);							 // Command for Stop count
  i2c_stop();
}


/*=============================================*/

void i2c_RcvData ( unsigned char NoOfByte, unsigned char SlaveAdd )
{
  i2c_GoMaster( SlaveAdd);
  for ( NoOfByte ; NoOfByte > 0; NoOfByte--)
  {
    ByteCnt = NoOfByte;
    i2c_RcvByte();
  }
  ByteCnt = 0;                              // Global will be used by other routines..
  i2c_stop();
}
/*=============================================*/
void i2c_WrData ( unsigned char bytecount, unsigned char DataAdrs )
{
  i2c_GoMaster ( SlvAdr_Wr );	             // Address the RTC  
  i2c_clkFreeze();							 // Stop clock when updating registers
  i2c_GoMaster ( SlvAdr_Wr );	             // Address the RTC for Write mode
  i2c_WrByte (DataAdrs);						 // Send the address to write
  for ( bytecount ; bytecount >0 ; bytecount--)
  {
    i2c_WrByte( tempVal[bytecount] );
  }
  i2c_clkRun();
}


/*=============================================*/ 
int i2c_Readch0 (void)						 // Read the clock registers
{											 // Disable interrupts
  i2c_GoMaster(SlvAdr_Wr);
  i2c_WrByte(0x40);							 // Seconds register address
  i2c_stop();								 
  i2c_RcvData (1, SlvAdr_Rd);
  adc1 = tempVal[1];						 // Save Seconds value
  i2c_stop();
  return adc1;
}

/*=============================================*/
int i2c_Readch1 (void)						 // Read the clock registers
{											 // Disable interrupts
  i2c_GoMaster(SlvAdr_Wr);
  i2c_WrByte(0x41);							 // Seconds register address
  i2c_stop();								 
  i2c_RcvData (1, SlvAdr_Rd);
  adc2 = tempVal[1];						 // Save Seconds value
  i2c_stop();
    return adc2;
}

int i2c_Readch2 (void)						 // Read the clock registers
{											 // Disable interrupts
  i2c_GoMaster(SlvAdr_Wr);
  i2c_WrByte(0x42);							 // Seconds register address
  i2c_stop();								 
  i2c_RcvData (1, SlvAdr_Rd);
  adc3 = tempVal[1];						 // Save Seconds value
  i2c_stop();
  return adc3;
} 
int i2c_Readch3 (void)						 // Read the clock registers
{											 // Disable interrupts
  i2c_GoMaster(SlvAdr_Wr);
  i2c_WrByte(0x43);							 // Seconds register address
  i2c_stop();								 
  i2c_RcvData (1, SlvAdr_Rd);
  adc4 = tempVal[1];						 // Save Seconds value
  i2c_stop();
  return adc4;
}


