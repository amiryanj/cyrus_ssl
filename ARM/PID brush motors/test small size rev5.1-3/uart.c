#include "lpc17xx.h"                              /* LPC17xx definitions    */
#include "uart.h"

#define FOSC                        12000000                            /*  Oscillator frequency                  */

#define FCCLK                      (FOSC  * 8)                          /*  Master clock frequency <= 100Mhz          */
                                                                        /*  Multiples of FOSC                */
#define FCCO                       (FCCLK * 3)                          /*  PLL frequency (275Mhz ~ 550Mhz)      */
                                                                        /*  And FCCLK the same or an even multiple of its */
#define FPCLK                      (FCCLK / 4)                          /*  Peripheral clock frequency, FCCLK 1 / 2, 1 / 4*/
                                                                        /*  The same or FCCLK               */

#define UART2_BPS     36500                                             /* 3 Serial communication baud rate            */
#define UART3_BPS     14900                                             /* 2 serial communication baud rate             */
/*********************************************************************************************************
** Function name:       UART3_Init
** Descriptions:        By default initialize the serial port 0 pins and communication parameters. Set to 8 data bits, 1 stop bit, no parity
** input parameters:    No
** output parameters:   No
** Returned value:      No
*********************************************************************************************************/
void UART3_Init (void)
{
	uint16_t usFdiv;
    /* UART3 */
    LPC_PINCON->PINSEL0 |= (1 << 1);             /* Pin P0.0 used as TXD3 (Com3) */
    LPC_PINCON->PINSEL0 |= (1 << 3);             /* Pin P0.1 used as RXD0 (Com3) */
  	LPC_SC->PCONP = LPC_SC->PCONP|(1<<25);

	
  	LPC_UART3->LCR  = 0x83;                      /* Allows you to set the baud rate               */
    usFdiv = (FPCLK / 16) / UART3_BPS;           /* Set baud rate                   */
    LPC_UART3->FDR  = 0x85;						// muLVAL = 8    ---DIV = 5 
	LPC_UART3->DLM  = usFdiv / 256;
    LPC_UART3->DLL  = usFdiv % 256; 
    LPC_UART3->LCR  = 0x03;                      /* Locked baud rate                   */
    LPC_UART3->FCR  = 0x06; 				   
	
	NVIC_EnableIRQ(UART3_IRQn);					//interrupt for Uart3
	LPC_UART3->IER=1;							//interrupt on data deceived
}

/*********************************************************************************************************
** Function name:       UART0_SendByte
** Descriptions: send data from serial port 0
** Input parameters: data: data sent
** Output parameters: None
** Returned value: None
*********************************************************************************************************/
int UART3_SendByte (int ucData)
{
	while (!(LPC_UART3->LSR & 0x20));
    return (LPC_UART3->THR = ucData);
}

/*----------------------------------------------------------------------------
  Read character from Serial Port   (blocking read)
 *----------------------------------------------------------------------------*/
int UART3_GetChar (void) 
{
  	while (!(LPC_UART3->LSR & 0x01));
  	return (LPC_UART3->RBR);
}


/*********************************************************************************************************
** Function name:       UART2_Init
** Descriptions: by default initialize the serial port 2 pins and communication parameters. Set to 8 data bits, 1 stop bit, no parity
** Input parameters: None
** Output parameters: None
** Returned value: None
*********************************************************************************************************/
void UART2_Init (void)
{
	uint16_t usFdiv;
    /* UART2 */
    LPC_PINCON->PINSEL0 |= (1 << 20);             /* Pin P0.10 used as TXD2 (Com2) */
    LPC_PINCON->PINSEL0 |= (1 << 22);             /* Pin P0.11 used as RXD2 (Com2) */

   	LPC_SC->PCONP = LPC_SC->PCONP|(1<<24);	      /*Open UART2 power control bit	           */

    LPC_UART2->LCR  = 0x83;                       /* Allows you to set the baud rate                */
    usFdiv = (FPCLK / 16) / UART2_BPS;            /* Set baud rate                    */
    LPC_UART2->DLM  = usFdiv / 256;
    LPC_UART2->DLL  = usFdiv % 256; 
    LPC_UART2->LCR  = 0x03;                       /* Locked baud rate                    */
    LPC_UART2->FCR  = 0x06;

	NVIC_EnableIRQ(UART2_IRQn);						//interrupt for Uart2
	LPC_UART2->IER=1;								//interrupt on received data
}

/***********************************************************************************************
** Function name:       UART2_SendByte
** Descriptions: send data from serial port 2
** Input parameters: data: data sent
** Output parameters: None
** Returned value: None
*********************************************************************************************************/
int UART2_SendByte (int ucData)
{
	while (!(LPC_UART2->LSR & 0x20));
    return (LPC_UART2->THR = ucData);
}

/*----------------------------------------------------------------------------
  Read character from Serial Port   (blocking read)
 *----------------------------------------------------------------------------*/
int UART2_GetChar (void) 
{
  	while (!(LPC_UART2->LSR & 0x01));
  	return (LPC_UART2->RBR);
}

void UART3_SendChar(uint16_t disp)
{
	uint16_t dispbuf[4];
	uint8_t i;

	dispbuf[3] = disp%10 + '0';
	dispbuf[2] = disp/10%10 + '0';
	dispbuf[1] = disp/10/10%10 + '0';
	dispbuf[0] = disp/10/10/10%10 + '0';
	for(i=0;i<4;i++)
		UART3_SendByte(dispbuf[i]);	
}

void UART2_SendChar(uint16_t disp)
{
	uint16_t dispbuf[4];
	uint8_t i;

	dispbuf[3] = disp%10 + '0';
	dispbuf[2] = disp/10%10 + '0';
	dispbuf[1] = disp/10/10%10 + '0';
	dispbuf[0] = disp/10/10/10%10 + '0';
	for(i=0;i<4;i++)
		UART2_SendByte(dispbuf[i]);	
}

void UART2_SendString (unsigned char *s) 
{
  	while (*s != 0) 
	{
   		UART2_SendByte(*s++);
	}
}

