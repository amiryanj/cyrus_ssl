#ifndef __UART_H
#define __UART_H

void UART3_Init (void);
int  UART3_SendByte (int ucData);
int  UART3_GetChar (void);
void UART3_SendChar(uint16_t disp);
 
void UART2_Init (void);
int  UART2_SendByte (int ucData);
int  UART2_GetChar (void);
void UART2_SendString (unsigned char *s);
void UART2_SendChar(uint16_t disp);  

#endif
